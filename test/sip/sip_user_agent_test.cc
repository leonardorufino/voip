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

    }else
        std::cout << "IPv4 SIP user agent test disabled\n";


    Socket::Address_Family family_ipv6 = Socket::ADDRESS_FAMILY_IPv6;
    std::string address_ipv6 = "::1";
    unsigned short port_ipv6 = 33445;

    if (check_network_address(family_ipv6, address_ipv6))
    {
        std::cout << "IPv6 SIP user agent test initialized\n";

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
