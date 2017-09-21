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

#pragma once

#include "sip/sip_user_agent.h"
#include "sip/sip_call.h"
#include "util/util_functions.h"
#include <iomanip>

class SIP_User_Agent_Test
{
public:
    static const unsigned long MAX_WAIT_TIME = 5000;
    static const unsigned long DELAY = 500;

public:
    SIP_User_Agent_Test();
    virtual ~SIP_User_Agent_Test();

    static bool init();
    template<class T> static bool run(Socket::Address_Family family, std::string address, unsigned short port,
                                      SIP_Transport_Type transport);

protected:
    virtual bool run(Socket::Address_Family family, std::string address, unsigned short port, SIP_Transport_Type transport) = 0;

    virtual bool init_user_agent(std::string address, unsigned short port);
    virtual bool close_user_agent();

    static bool get_network_addresses(std::list<Socket::Network_Address> &addresses);
    static bool check_network_address(Socket::Address_Family family, std::string address);

protected:
    SIP_User_Agent _user_agent;

    unsigned int _call_id_callback;
    std::list<SIP_Request *> _received_requests;
    SIP_Request *_request_callback;
    SIP_Response *_response_callback;
};
