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
#include "util/string_functions.h"
#include "util/util_functions.h"
#include <iomanip>

class SIP_Call_Test
{
public:
    static const unsigned long MAX_WAIT_TIME = 5000;
    static const unsigned long DELAY = 500;

public:
    SIP_Call_Test();
    virtual ~SIP_Call_Test();

    static bool init();
    template<class T> static bool run();

protected:
    virtual bool run() = 0;

    virtual bool set_callbacks();
    virtual void set_use_prack(bool prack) { _use_prack = prack; }

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

    SIP_Request *create_register();
    SIP_Response *create_register_response_100();
    SIP_Response *create_register_response_401();
    SIP_Response *create_register_response_200();

    SIP_Request *create_options();
    SIP_Response *create_options_response_100();
    SIP_Response *create_options_response_200();

    bool process_invite();
    bool process_invite_response_100();
    bool process_invite_response_180();
    bool process_invite_response_183();
    bool process_invite_response_200();
    bool process_invite_response_480();
    bool process_invite_response_487();
    bool process_ack();
    bool wait_invite_timeout();

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

    bool process_register();
    bool process_register_response_100();
    bool process_register_response_401();
    bool process_register_response_200();

    bool process_options();
    bool process_options_response_100();
    bool process_options_response_200();

    static bool send_message_callback(void *data, SIP_Call *call, SIP_Message *msg);
    static bool receive_request_callback(void *data, SIP_Call *call, SIP_Request *request);
    static bool receive_response_callback(void *data, SIP_Call *call, SIP_Request *request, SIP_Response *response);

protected:
    SIP_Call *_client_call;
    SIP_Call *_server_call;

    bool _use_prack;

    unsigned long _client_sequence;
    unsigned long _server_sequence;
    unsigned long _invite_sequence;
    unsigned long _prack_rseq;

    std::string _invite_branch;
    std::string _bye_branch;
    std::string _update_branch;
    std::string _prack_branch;
    std::string _info_branch;
    std::string _register_branch;
    std::string _options_branch;

    bool _sent_message;
    bool _received_request;
    bool _received_response;
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
//-------------------------------------------

class SIP_Call_Reject_No_100_Test : public SIP_Call_Test
{
public:
    SIP_Call_Reject_No_100_Test() {}
    virtual ~SIP_Call_Reject_No_100_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Call_Reject_No_1xx_Test : public SIP_Call_Test
{
public:
    SIP_Call_Reject_No_1xx_Test() {}
    virtual ~SIP_Call_Reject_No_1xx_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Call_No_Answer_Test : public SIP_Call_Test
{
public:
    SIP_Call_No_Answer_Test() {}
    virtual ~SIP_Call_No_Answer_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Call_Update_Test : public SIP_Call_Test
{
public:
    SIP_Call_Update_Test() {}
    virtual ~SIP_Call_Update_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Call_Cancel_Test : public SIP_Call_Test
{
public:
    SIP_Call_Cancel_Test() {}
    virtual ~SIP_Call_Cancel_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Call_Prack_Test : public SIP_Call_Test
{
public:
    SIP_Call_Prack_Test() {}
    virtual ~SIP_Call_Prack_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Call_Prack_No_100_Test : public SIP_Call_Test
{
public:
    SIP_Call_Prack_No_100_Test() {}
    virtual ~SIP_Call_Prack_No_100_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Call_Register_Test : public SIP_Call_Test
{
public:
    SIP_Call_Register_Test() {}
    virtual ~SIP_Call_Register_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Call_Register_With_100_Test : public SIP_Call_Test
{
public:
    SIP_Call_Register_With_100_Test() {}
    virtual ~SIP_Call_Register_With_100_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Call_Register_Reject_Test : public SIP_Call_Test
{
public:
    SIP_Call_Register_Reject_Test() {}
    virtual ~SIP_Call_Register_Reject_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Call_Options_Test : public SIP_Call_Test
{
public:
    SIP_Call_Options_Test() {}
    virtual ~SIP_Call_Options_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Call_Options_With_100_Test : public SIP_Call_Test
{
public:
    SIP_Call_Options_With_100_Test() {}
    virtual ~SIP_Call_Options_With_100_Test() {}

    bool run();
};

//-------------------------------------------
