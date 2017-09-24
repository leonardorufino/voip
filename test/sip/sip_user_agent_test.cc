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

#include "sip_user_agent_test.h"
#include <iostream>

//-------------------------------------------

SIP_User_Agent_Test::SIP_User_Agent_Test() : _call_id_callback(SIP_Call::INVALID_CALL_ID), _request_callback(NULL),
    _response_callback(NULL)
{
}

//-------------------------------------------

SIP_User_Agent_Test::~SIP_User_Agent_Test()
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

bool SIP_User_Agent_Test::init()
{
    std::cout << "SIP user agent test initialized\n";

    Socket::Address_Family family_ipv4 = Socket::ADDRESS_FAMILY_IPv4;
    std::string address_ipv4 = "127.0.0.1";
    unsigned short port_ipv4 = 33445;

    if (check_network_address(family_ipv4, address_ipv4))
    {
        std::cout << "IPv4 SIP user agent test initialized\n";

        if (!run<SIP_User_Agent_Call_Success_Test>(family_ipv4, address_ipv4, port_ipv4, SIP_TRANSPORT_UDP))
            return false;

        if (!run<SIP_User_Agent_Call_Success_Test>(family_ipv4, address_ipv4, port_ipv4, SIP_TRANSPORT_TCP))
            return false;
    }else
        std::cout << "IPv4 SIP user agent test disabled\n";


    Socket::Address_Family family_ipv6 = Socket::ADDRESS_FAMILY_IPv6;
    std::string address_ipv6 = "::1";
    unsigned short port_ipv6 = 33445;

    if (check_network_address(family_ipv6, address_ipv6))
    {
        std::cout << "IPv6 SIP user agent test initialized\n";

        if (!run<SIP_User_Agent_Call_Success_Test>(family_ipv6, address_ipv6, port_ipv6, SIP_TRANSPORT_UDP))
            return false;

        if (!run<SIP_User_Agent_Call_Success_Test>(family_ipv6, address_ipv6, port_ipv6, SIP_TRANSPORT_TCP))
            return false;
    }else
        std::cout << "IPv6 SIP user agent test disabled\n";

    std::cout << "SIP user agent test completed successfully\n";
    return true;
}

//-------------------------------------------

template<class T> bool SIP_User_Agent_Test::run(Socket::Address_Family family, std::string address, unsigned short port,
                                                SIP_Transport_Type transport)
{
    T test;
    if (!test.run(family, address, port, transport))
        return false;
    return true;
}

//-------------------------------------------

bool SIP_User_Agent_Test::init_user_agent(std::string address, unsigned short port)
{
    if (!SIP_Transport::start())
    {
        std::cout << "SIP_User_Agent_Test::init_user_agent -> Failed to start SIP transport\n";
        return false;
    }

    set_callbacks();

    if (!_user_agent.init(address, port))
    {
        std::cout << "SIP_User_Agent_Test::init_user_agent -> Failed to init user agent\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_User_Agent_Test::close_user_agent()
{
    if (!_user_agent.close())
    {
        std::cout << "SIP_User_Agent_Invite_UDP_Test::close_user_agent -> Failed to close user agent\n";
        return false;
    }

    if (!SIP_Transport::stop())
    {
        std::cout << "SIP_User_Agent_Invite_UDP_Test::close_user_agent -> Failed to stop SIP transport\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_User_Agent_Test::set_callbacks()
{
    _user_agent.get_user_agent_server().set_receive_request_callback(receive_request_callback, this);
    _user_agent.get_user_agent_client().set_receive_response_callback(receive_response_callback, this);
    return true;
}

//-------------------------------------------

void SIP_User_Agent_Test::clear_callback_params()
{
    _call_id_callback = SIP_Call::INVALID_CALL_ID;

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

bool SIP_User_Agent_Test::process_request(unsigned int call_id, SIP_Method_Type method, std::string address, unsigned short port,
                                          SIP_Transport_Type transport)
{
    SIP_User_Agent_Client &user_agent_client = _user_agent.get_user_agent_client();

    SIP_Request *request = user_agent_client.create_request(call_id, method);
    if (!request)
    {
        std::cout << "SIP_User_Agent_Test::process_request -> Failed to create request (call_id=" << call_id
                  << ", method=" << method << ")\n";
        return false;
    }

    if ((!address.empty()) && (port != SIP_URI::INVALID_PORT) && (transport != SIP_Transport_Type::SIP_TRANSPORT_INVALID))
    {
        SIP_Header_To *header_to = dynamic_cast<SIP_Header_To *>(request->get_header(SIP_HEADER_TO));
        SIP_Header_Via *header_via = dynamic_cast<SIP_Header_Via *>(request->get_header(SIP_HEADER_VIA));
        if ((!header_to) || (!header_via))
        {
            std::cout << "SIP_User_Agent_Test::process_request -> Failed to get headers\n";
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

    if (!user_agent_client.send_request(call_id, request))
    {
        std::cout << "SIP_User_Agent_Test::process_request -> Failed to send request (call_id=" << call_id
                  << ", method=" << method << ")\n";
        delete request;
        return false;
    }

    unsigned long start = Util_Functions::get_tick();

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if ((_call_id_callback != SIP_Call::INVALID_CALL_ID) && (_request_callback))
            break;

        Util_Functions::delay(DELAY);
    }

    if ((_call_id_callback == SIP_Call::INVALID_CALL_ID) || (!_request_callback))
    {
        std::cout << "SIP_User_Agent_Test::process_request -> Request not received (call_id=" << call_id
                  << ", method=" << method << ")\n";
        delete request;
        return false;
    }

    delete request;
    return true;
}

//-------------------------------------------

bool SIP_User_Agent_Test::process_response(unsigned int call_id, SIP_Method_Type method, unsigned short status_code)
{
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
        std::cout << "SIP_User_Agent_Test::process_response -> Invalid request (call_id=" << call_id
                  << ", method=" << method << ", status_code=" << status_code << ")\n";
        return false;
    }

    SIP_User_Agent_Server &user_agent_server = _user_agent.get_user_agent_server();

    SIP_Response *response = user_agent_server.create_response(call_id, request, status_code);
    if (!response)
    {
        std::cout << "SIP_User_Agent_Test::process_response -> Failed to create response (call_id=" << call_id
                  << ", method=" << method << ", status_code=" << status_code << ")\n";
        return false;
    }

    clear_callback_params();

    if (!user_agent_server.send_response(call_id, response))
    {
        std::cout << "SIP_User_Agent_Test::process_response -> Failed to send response (call_id=" << call_id
                  << ", method=" << method << ", status_code=" << status_code << ")\n";
        delete response;
        return false;
    }

    unsigned long start = Util_Functions::get_tick();

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if ((_call_id_callback != SIP_Call::INVALID_CALL_ID) && (_request_callback) && (_response_callback))
            break;

        Util_Functions::delay(DELAY);
    }

    if ((_call_id_callback == SIP_Call::INVALID_CALL_ID) || (!_request_callback) || (!_response_callback))
    {
        std::cout << "SIP_User_Agent_Test::process_response -> Response not received (call_id=" << call_id
                  << ", method=" << method << ", status_code=" << status_code << ")\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_User_Agent_Test::receive_request_callback(void *data, SIP_User_Agent *user_agent, unsigned int call_id, SIP_Request *request)
{
    SIP_User_Agent_Test *test = reinterpret_cast<SIP_User_Agent_Test *>(data);
    if ((!test) || (!user_agent) || (call_id == SIP_Call::INVALID_CALL_ID) || (!request))
    {
        std::cout << "SIP_User_Agent_Test::receive_request_callback -> Invalid parameters\n";
        return false;
    }

    if (!test->_request_callback)
        delete test->_request_callback;

    test->_call_id_callback = call_id;
    test->_request_callback = new SIP_Request(*request);
    test->_received_requests.push_back(new SIP_Request(*request));
    return true;
}

//-------------------------------------------

bool SIP_User_Agent_Test::receive_response_callback(void *data, SIP_User_Agent *user_agent, unsigned int call_id,
                                                    SIP_Request *request, SIP_Response *response)
{
    SIP_User_Agent_Test *test = reinterpret_cast<SIP_User_Agent_Test *>(data);
    if ((!test) || (!user_agent) || (call_id == SIP_Call::INVALID_CALL_ID) || (!request) || (!response))
    {
        std::cout << "SIP_User_Agent_Test::receive_response_callback -> Invalid parameters\n";
        return false;
    }

    if (!test->_request_callback)
        delete test->_request_callback;

    if (!test->_response_callback)
        delete test->_response_callback;

    test->_call_id_callback = call_id;
    test->_request_callback = new SIP_Request(*request);
    test->_response_callback = new SIP_Response(*response);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_User_Agent_Test::get_network_addresses(std::list<Socket::Network_Address> &addresses)
{
    if (!Socket::get_network_addresses(addresses))
    {
        std::cout << "SIP_User_Agent_Test::get_network_addresses -> Failed to get network addresses\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_User_Agent_Test::check_network_address(Socket::Address_Family family, std::string address)
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

bool SIP_User_Agent_Call_Success_Test::run(Socket::Address_Family family, std::string address, unsigned short port,
                                           SIP_Transport_Type transport)
{
    if (!init_user_agent(address, port))
        return false;

    unsigned int call_id_1 = 0;

    if (!process_request(call_id_1, SIP_REQUEST_INVITE, address, port, transport))
        return false;

    unsigned int call_id_2 = _call_id_callback;

    if (!process_response(call_id_2, SIP_REQUEST_INVITE, 100))
        return false;

    if (!process_response(call_id_2, SIP_REQUEST_INVITE, 180))
        return false;

    if (!process_response(call_id_2, SIP_REQUEST_INVITE, 183))
        return false;

    if (!process_response(call_id_2, SIP_REQUEST_INVITE, 200))
        return false;

    if (!process_request(call_id_1, SIP_REQUEST_ACK))
        return false;

    if (!process_request(call_id_1, SIP_REQUEST_INFO))
        return false;

    if (!process_response(call_id_2, SIP_REQUEST_INFO, 200))
        return false;

    if (!process_request(call_id_2, SIP_REQUEST_MESSAGE))
        return false;

    if (!process_response(call_id_1, SIP_REQUEST_MESSAGE, 200))
        return false;

    if (!process_request(call_id_1, SIP_REQUEST_BYE))
        return false;

    if (!process_response(call_id_2, SIP_REQUEST_BYE, 200))
        return false;

    if (!close_user_agent())
        return false;

    return true;
}

//-------------------------------------------
