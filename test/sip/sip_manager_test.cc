/*
 *                    GNU GENERAL PUBLIC LICENSE
 *                       Version 3, 29 June 2007
 *
 * Copyright (C) 2007 Free Software Foundation, Inc. <http://fsf.org/>
 * Everyone is permitted to copy and distribute verbatim copies
 * of this license document, but changing it is not allowed.
 *
 * Written by Leonardo Maccari Rufino
 */

#include "sip_manager_test.h"
#include <iostream>

//-------------------------------------------

SIP_Manager_Test::SIP_Manager_Test() : _user_agent_id_callback(SIP_Object_ID::INVALID_USER_AGENT),
    _call_id_callback(SIP_Object_ID::INVALID_CALL), _request_callback(NULL), _response_callback(NULL), _stop_thread(false)
{
}

//-------------------------------------------

SIP_Manager_Test::~SIP_Manager_Test()
{
    std::list<SIP_Request *>::iterator it = _received_requests.begin();
    while (it != _received_requests.end())
        delete *it++;

    if (_request_callback)
        delete _request_callback;

    if (_response_callback)
        delete _response_callback;
}

//-------------------------------------------

bool SIP_Manager_Test::init()
{
    std::cout << "SIP manager test initialized\n";

    Socket::Address_Family family_ipv4 = Socket::ADDRESS_FAMILY_IPv4;
    std::string address_ipv4 = "127.0.0.1";
    unsigned short port_ipv4 = 33445;

    if (check_network_address(family_ipv4, address_ipv4))
    {
        std::cout << "IPv4 SIP manager test initialized\n";

        if (!run<SIP_Manager_Call_Success_Test>(family_ipv4, address_ipv4, port_ipv4, SIP_TRANSPORT_UDP))
            return false;

        std::cout << "IPv4 SIP manager test completed successfully\n";
    }else
        std::cout << "IPv4 SIP manager test disabled\n";


    Socket::Address_Family family_ipv6 = Socket::ADDRESS_FAMILY_IPv6;
    std::string address_ipv6 = "::1";
    unsigned short port_ipv6 = 33445;

    if (check_network_address(family_ipv6, address_ipv6))
    {
        std::cout << "IPv6 SIP manager test initialized\n";

        if (!run<SIP_Manager_Call_Success_Test>(family_ipv6, address_ipv6, port_ipv6, SIP_TRANSPORT_UDP))
            return false;

        std::cout << "IPv6 SIP manager test completed successfully\n";
    }else
        std::cout << "IPv6 SIP manager test disabled\n";

    std::cout << "SIP manager test completed successfully\n";
    return true;
}

//-------------------------------------------

template<class T> bool SIP_Manager_Test::run(Socket::Address_Family family, std::string address, unsigned short port,
                                             SIP_Transport_Type transport)
{
    T test;
    test._thread = std::thread(thread, &test);

    bool ret = test.run(family, address, port, transport);

    test._stop_thread = true;
    test._thread.join();
    return ret;
}

//-------------------------------------------

void SIP_Manager_Test::thread(SIP_Manager_Test *test)
{
    while (!test->_stop_thread)
    {
        Util_Functions::delay(THREAD_DELAY);

        std::lock_guard<std::mutex> lock(test->_thread_mutex);

        SIP_Manager &manager = SIP_Manager::instance();
        manager.update();
    }
}

//-------------------------------------------

bool SIP_Manager_Test::create_user_agent(unsigned int user_agent_id, std::string address, unsigned short port)
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Manager &manager = SIP_Manager::instance();

    manager.set_receive_request_callback(receive_request_callback, this);
    manager.set_receive_response_callback(receive_response_callback, this);

    if (!manager.create_user_agent(user_agent_id, address, port))
    {
        std::cout << "SIP_Manager_Test::create_user_agent -> Failed to create user agent (user_agent_id=" << user_agent_id << ")\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Manager_Test::remove_user_agent(unsigned int user_agent_id)
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Manager &manager = SIP_Manager::instance();

    if (!manager.remove_user_agent(user_agent_id))
    {
        std::cout << "SIP_Manager_Test::remove_user_agent -> Failed to remove user agent (user_agent_id=" << user_agent_id << ")\n";
        return false;
    }

    return true;
}

//-------------------------------------------

void SIP_Manager_Test::clear_callback_params()
{
    _user_agent_id_callback = SIP_Object_ID::INVALID_USER_AGENT;
    _call_id_callback = SIP_Object_ID::INVALID_CALL;

    if (_request_callback)
    {
        delete _request_callback;
        _request_callback = NULL;
    }

    if (_response_callback)
    {
        delete _response_callback;
        _response_callback = NULL;
    }
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Manager_Test::send_request(unsigned int user_agent_id, unsigned int call_id, SIP_Method_Type method, std::string address,
                                    unsigned short port, SIP_Transport_Type transport)
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Manager &manager = SIP_Manager::instance();

    SIP_Request *request = manager.create_request(user_agent_id, call_id, method);
    if (!request)
    {
        std::cout << "SIP_Manager_Test::send_request -> Failed to create request (user_agent_id=" << user_agent_id
                  << ", call_id=" << call_id << ", method=" << method << ")\n";
        return false;
    }

    if ((!address.empty()) && (port != SIP_URI::INVALID_PORT) && (transport != SIP_Transport_Type::SIP_TRANSPORT_INVALID))
    {
        SIP_Header_To *header_to = dynamic_cast<SIP_Header_To *>(request->get_header(SIP_HEADER_TO));
        SIP_Header_Via *header_via = dynamic_cast<SIP_Header_Via *>(request->get_header(SIP_HEADER_VIA));
        if ((!header_to) || (!header_via))
        {
            std::cout << "SIP_Manager_Test::send_request -> Failed to get headers\n";
            delete request;
            return false;
        }

        header_via->set_transport(transport);

        header_to->get_address().set_scheme(SIP_Address::SCHEME_SIP);
        SIP_URI &header_to_uri = header_to->get_address().get_sip_uri();
        header_to_uri.get_host().set_address(address);
        header_to_uri.set_port(port);

        request->set_request_line(method, header_to->get_address(), SIP_VERSION);
    }

    clear_callback_params();

    if (!manager.send_request(user_agent_id, call_id, request))
    {
        std::cout << "SIP_Manager_Test::send_request -> Failed to send request (user_agent_id=" << user_agent_id
                  << ", call_id=" << call_id << ", method=" << method << ")\n";
        delete request;
        return false;
    }

    delete request;
    return true;
}

//-------------------------------------------

bool SIP_Manager_Test::send_response(unsigned int user_agent_id, unsigned int call_id, SIP_Method_Type method, unsigned short status_code)
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Manager &manager = SIP_Manager::instance();

    SIP_Request *request = NULL;

    std::list<SIP_Request *>::reverse_iterator it = _received_requests.rbegin();
    while (it != _received_requests.rend())
    {
        SIP_Request *received = *it++;
        if (received->get_message_type() == method)
        {
            request = received;
            break;
        }
    }

    if (!request)
    {
        std::cout << "SIP_Manager_Test::send_response -> Invalid request (user_agent_id=" << user_agent_id
                  << ", call_id=" << call_id << ", method=" << method << ", status_code=" << status_code << ")\n";
        return false;
    }

    SIP_Response *response = manager.create_response(user_agent_id, call_id, request, status_code);
    if (!response)
    {
        std::cout << "SIP_Manager_Test::send_response -> Failed to create response (user_agent_id=" << user_agent_id
                  << ", call_id=" << call_id << ", method=" << method << ", status_code=" << status_code << ")\n";
        return false;
    }

    clear_callback_params();

    if (!manager.send_response(user_agent_id, call_id, response))
    {
        std::cout << "SIP_Manager_Test::send_response -> Failed to send response (user_agent_id=" << user_agent_id
                  << ", call_id=" << call_id << ", method=" << method << ", status_code=" << status_code << ")\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Manager_Test::receive_request(unsigned int user_agent_id, unsigned int call_id, SIP_Method_Type method)
{
    unsigned long start = Util_Functions::get_tick();

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if ((_user_agent_id_callback == user_agent_id) && (_request_callback) &&
            (((call_id == SIP_Object_ID::INVALID_CALL) && (_call_id_callback != SIP_Object_ID::INVALID_CALL)) ||
             ((call_id != SIP_Object_ID::INVALID_CALL) && (_call_id_callback == call_id))))
            break;

        Util_Functions::delay(DELAY);
    }

    if ((_user_agent_id_callback != user_agent_id) || (_call_id_callback == SIP_Object_ID::INVALID_CALL) ||
        ((call_id != SIP_Object_ID::INVALID_CALL) && (_call_id_callback != call_id)) || (!_request_callback))
    {
        std::cout << "SIP_Manager_Test::receive_request -> Request not received (user_agent_id=" << user_agent_id
                  << ", call_id=" << call_id << ", method=" << method << ")\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Manager_Test::receive_response(unsigned int user_agent_id, unsigned int call_id, SIP_Method_Type method, unsigned short status_code)
{
    unsigned long start = Util_Functions::get_tick();

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if ((_user_agent_id_callback == user_agent_id) && (_request_callback) && (_response_callback) &&
            (((call_id == SIP_Object_ID::INVALID_CALL) && (_call_id_callback != SIP_Object_ID::INVALID_CALL)) ||
             ((call_id != SIP_Object_ID::INVALID_CALL) && (_call_id_callback == call_id))))
            break;

        Util_Functions::delay(DELAY);
    }

    if ((_user_agent_id_callback != user_agent_id) || (_call_id_callback == SIP_Object_ID::INVALID_CALL) ||
        ((call_id != SIP_Object_ID::INVALID_CALL) && (_call_id_callback != call_id)) ||
        (!_request_callback) || (!_response_callback))
    {
        std::cout << "SIP_Manager_Test::receive_response -> Response not received (user_agent_id=" << user_agent_id
                  << ", call_id=" << call_id << ", method=" << method << ", status_code=" << status_code << ")\n";
        return false;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Manager_Test::receive_request_callback(void *data, unsigned int user_agent_id, unsigned int call_id, SIP_Request *request)
{
    SIP_Manager_Test *test = reinterpret_cast<SIP_Manager_Test *>(data);
    if ((!test) || (user_agent_id == SIP_Object_ID::INVALID_USER_AGENT) || (call_id == SIP_Object_ID::INVALID_CALL) || (!request))
    {
        std::cout << "SIP_Manager_Test::receive_request_callback -> Invalid parameters\n";
        return false;
    }

    if (!test->_request_callback)
        delete test->_request_callback;

    test->_user_agent_id_callback = user_agent_id;
    test->_call_id_callback = call_id;
    test->_request_callback = new SIP_Request(*request);
    test->_received_requests.push_back(new SIP_Request(*request));
    return true;
}

//-------------------------------------------

bool SIP_Manager_Test::receive_response_callback(void *data, unsigned int user_agent_id, unsigned int call_id, SIP_Request *request,
                                                 SIP_Response *response)
{
    SIP_Manager_Test *test = reinterpret_cast<SIP_Manager_Test *>(data);
    if ((!test) || (user_agent_id == SIP_Object_ID::INVALID_USER_AGENT) || (call_id == SIP_Object_ID::INVALID_CALL) || (!request) ||
        (!response))
    {
        std::cout << "SIP_Manager_Test::receive_response_callback -> Invalid parameters\n";
        return false;
    }

    if (!test->_request_callback)
        delete test->_request_callback;

    if (!test->_response_callback)
        delete test->_response_callback;

    test->_user_agent_id_callback = user_agent_id;
    test->_call_id_callback = call_id;
    test->_request_callback = new SIP_Request(*request);
    test->_response_callback = new SIP_Response(*response);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Manager_Test::get_network_addresses(std::list<Socket::Network_Address> &addresses)
{
    if (!Socket::get_network_addresses(addresses))
    {
        std::cout << "SIP_Manager_Test::get_network_addresses -> Failed to get network addresses\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Manager_Test::check_network_address(Socket::Address_Family family, std::string address)
{
    std::list<Socket::Network_Address> addresses;
    if (!get_network_addresses(addresses))
        return false;

    std::list<Socket::Network_Address>::iterator it = addresses.begin();
    while (it != addresses.end())
    {
        Socket::Network_Address &netaddr = *it++;
        if ((netaddr._family == family) && (netaddr._address == address))
            return true;
    }

    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Manager_Call_Success_Test::run(Socket::Address_Family family, std::string address, unsigned short port,
                                        SIP_Transport_Type transport)
{
    std::cout << "SIP manager call success test initialized\n";

    unsigned int user_agent_id = 0;

    if (!create_user_agent(user_agent_id, address, port))
        return false;

    unsigned int call_id_1 = 0;
    unsigned int call_id_2 = SIP_Object_ID::INVALID_CALL;

    if (!send_request(user_agent_id, call_id_1, SIP_REQUEST_INVITE, address, port, transport))
        return false;

    if (!receive_request(user_agent_id, call_id_2, SIP_REQUEST_INVITE))
        return false;

    call_id_2 = _call_id_callback;

    if (!send_response(user_agent_id, call_id_2, SIP_REQUEST_INVITE, 100))
        return false;

    if (!receive_response(user_agent_id, call_id_1, SIP_REQUEST_INVITE, 100))
        return false;

    if (!send_response(user_agent_id, call_id_2, SIP_REQUEST_INVITE, 180))
        return false;

    if (!receive_response(user_agent_id, call_id_1, SIP_REQUEST_INVITE, 180))
        return false;

    if (!send_response(user_agent_id, call_id_2, SIP_REQUEST_INVITE, 183))
        return false;

    if (!receive_response(user_agent_id, call_id_1, SIP_REQUEST_INVITE, 183))
        return false;

    if (!send_response(user_agent_id, call_id_2, SIP_REQUEST_INVITE, 200))
        return false;

    if (!receive_response(user_agent_id, call_id_1, SIP_REQUEST_INVITE, 200))
        return false;

    if (!send_request(user_agent_id, call_id_1, SIP_REQUEST_ACK))
        return false;

    if (!receive_request(user_agent_id, call_id_2, SIP_REQUEST_ACK))
        return false;

    if (!send_request(user_agent_id, call_id_1, SIP_REQUEST_INFO))
        return false;

    if (!receive_request(user_agent_id, call_id_2, SIP_REQUEST_INFO))
        return false;

    if (!send_response(user_agent_id, call_id_2, SIP_REQUEST_INFO, 200))
        return false;

    if (!receive_response(user_agent_id, call_id_1, SIP_REQUEST_INFO, 200))
        return false;

    if (!send_request(user_agent_id, call_id_2, SIP_REQUEST_MESSAGE))
        return false;

    if (!receive_request(user_agent_id, call_id_1, SIP_REQUEST_MESSAGE))
        return false;

    if (!send_response(user_agent_id, call_id_1, SIP_REQUEST_MESSAGE, 200))
        return false;

    if (!receive_response(user_agent_id, call_id_2, SIP_REQUEST_MESSAGE, 200))
        return false;

    if (!send_request(user_agent_id, call_id_1, SIP_REQUEST_BYE))
        return false;

    if (!receive_request(user_agent_id, call_id_2, SIP_REQUEST_BYE))
        return false;

    if (!send_response(user_agent_id, call_id_2, SIP_REQUEST_BYE, 200))
        return false;

    if (!receive_response(user_agent_id, call_id_1, SIP_REQUEST_BYE, 200))
        return false;

    if (!remove_user_agent(user_agent_id))
        return false;

    std::cout << "SIP manager call success test completed successfully\n";
    return true;
}

//-------------------------------------------
