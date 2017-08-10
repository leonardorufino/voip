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

#include "sip/sip_call.h"
#include <iomanip>

class SIP_Call_Test
{
public:
    SIP_Call_Test();
    virtual ~SIP_Call_Test();

    static bool init();

protected:
    virtual bool run() = 0;

    virtual void set_call_id(std::string call_id) { _call_id = call_id; }

    virtual bool init_call();
    virtual bool set_callbacks();

    SIP_Request *create_invite();
    SIP_Response *create_invite_response_100();
    SIP_Response *create_invite_response_180();
    SIP_Response *create_invite_response_183();
    SIP_Response *create_invite_response_200();
    SIP_Response *create_invite_response_480();
    SIP_Response *create_invite_response_487();

    static SIP_Response *create_response_callback(void *data, SIP_Call *call, SIP_Request *request, unsigned short status_code);
    static bool send_response_callback(void *data, SIP_Call *call, SIP_Request *request, SIP_Response *response);

protected:
    SIP_Call _client_call;
    SIP_Call _server_call;

    std::string _call_id;
    unsigned long _client_sequence;
    unsigned long _server_sequence;
    unsigned long _invite_sequence;

    SIP_Request *_request;
    SIP_Response *_response;
    unsigned short _status_code;
};

//-------------------------------------------
