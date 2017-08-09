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

#include "sip_call_test.h"
#include <iostream>

//-------------------------------------------

SIP_Call_Test::SIP_Call_Test() : _client_sequence(314159), _server_sequence(231),
        _request(NULL), _response(NULL), _status_code(0)
{
}

//-------------------------------------------

bool SIP_Call_Test::init()
{
    std::cout << "SIP call test initialized\n";

    std::cout << "SIP call test completed successfully\n";
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::init_call()
{
    _server_call.set_call_id(_call_id);
    _client_call.set_call_id(_call_id);
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::set_callbacks()
{
    _server_call.set_create_response_callback(create_response_callback, this);
    _server_call.set_send_response_callback(send_response_callback, this);
    _client_call.set_create_response_callback(create_response_callback, this);
    _client_call.set_send_response_callback(send_response_callback, this);
    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Response *SIP_Call_Test::create_response_callback(void *data, SIP_Call *call, SIP_Request *request, unsigned short status_code)
{
    SIP_Call_Test *test = reinterpret_cast<SIP_Call_Test *>(data);
    if ((!test) || (!call) || (!request))
    {
        std::cout << "SIP_Call_Test::create_response_callback -> Invalid parameters\n";
        return NULL;
    }

    test->_request = request;
    test->_status_code = status_code;
    return NULL;
}

//-------------------------------------------

bool SIP_Call_Test::send_response_callback(void *data, SIP_Call *call, SIP_Request *request, SIP_Response *response)
{
    SIP_Call_Test *test = reinterpret_cast<SIP_Call_Test *>(data);
    if ((!test) || (!call) || (!request) || (!response))
    {
        std::cout << "SIP_Call_Test::send_response_callback -> Invalid parameters\n";
        return false;
    }

    test->_request = request;
    test->_response = response;
    return true;
}

//-------------------------------------------
