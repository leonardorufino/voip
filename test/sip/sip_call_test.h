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
    virtual void set_use_prack(bool prack) { use_prack = prack; }

    SIP_Request *create_invite();
    SIP_Response *create_invite_response_100();
    SIP_Response *create_invite_response_180();
    SIP_Response *create_invite_response_183();
    SIP_Response *create_invite_response_200();
    SIP_Response *create_invite_response_480();
    SIP_Response *create_invite_response_487();
    SIP_Request *create_ack();

    SIP_Request *create_client_bye();
    SIP_Response *create_server_bye_response_200();
    SIP_Request *create_server_bye();
    SIP_Response *create_client_bye_response_200();

    SIP_Request *create_client_update();
    SIP_Response *create_server_update_response_200();
    SIP_Request *create_server_update();
    SIP_Response *create_client_update_response_200();

    SIP_Request *create_cancel();
    SIP_Response *create_cancel_response_200();

    SIP_Request *create_prack();
    SIP_Response *create_prack_response_200();

    SIP_Request *create_info();
    SIP_Response *create_info_response_200();

    bool process_invite();
    bool process_invite_response_100();
    bool process_invite_response_180();
    bool process_invite_response_183();
    bool process_invite_response_200();
    bool process_invite_response_480();
    bool process_invite_response_487();
    bool process_ack();

    bool process_client_bye();
    bool process_server_bye_response_200();
    bool process_server_bye();
    bool process_client_bye_response_200();

    bool process_client_update();
    bool process_server_update_response_200();
    bool process_server_update();
    bool process_client_update_response_200();

    bool process_cancel();
    bool process_cancel_response_200();

    bool process_prack();
    bool process_prack_response_200();

    bool process_info();
    bool process_info_response_200();

    static SIP_Response *create_response_callback(void *data, SIP_Call *call, SIP_Request *request, unsigned short status_code);
    static bool send_response_callback(void *data, SIP_Call *call, SIP_Request *request, SIP_Response *response);

protected:
    SIP_Call _client_call;
    SIP_Call _server_call;

    std::string _call_id;
    bool use_prack;

    unsigned long _client_sequence;
    unsigned long _server_sequence;
    unsigned long _invite_sequence;
    unsigned long _prack_rseq;

    SIP_Request *_invite;
    SIP_Request *_bye;
    SIP_Request *_update;
    SIP_Request *_cancel;
    SIP_Request *_prack;
    SIP_Request *_info;

    SIP_Request *_request;
    SIP_Response *_response;
    unsigned short _status_code;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Call_Success_Test : public SIP_Call_Test
{
public:
    SIP_Call_Success_Test() {}
    virtual ~SIP_Call_Success_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Call_Success_No_100_Test : public SIP_Call_Test
{
public:
    SIP_Call_Success_No_100_Test() {}
    virtual ~SIP_Call_Success_No_100_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Call_Success_No_1xx_Test : public SIP_Call_Test
{
public:
    SIP_Call_Success_No_1xx_Test() {}
    virtual ~SIP_Call_Success_No_1xx_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Call_Reject_Test : public SIP_Call_Test
{
public:
    SIP_Call_Reject_Test() {}
    virtual ~SIP_Call_Reject_Test() {}

    bool run();
};

//-------------------------------------------
