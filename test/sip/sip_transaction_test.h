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

#include "sip/sip_header.h"
#include "sip/sip_message.h"
#include "sip/sip_transaction.h"
#include "util/util_functions.h"
#include <iomanip>

class SIP_Transaction_Test
{
public:
    static const unsigned long MAX_WAIT_TIME = 5000;
    static const unsigned long DELAY = 500;

public:
    static bool init();
    template<class T> static bool run();

protected:
    SIP_Transaction_Test() : _transaction(NULL), _sent_message(false), _received_request(false), _received_response(false) {}
    virtual ~SIP_Transaction_Test();

    virtual bool run() = 0;
    virtual bool set_callbacks();

    unsigned int get_next_transaction_id();

    SIP_Request *create_invite();
    SIP_Request *create_ack();
    SIP_Response *create_invite_response_100();
    SIP_Response *create_invite_response_180();
    SIP_Response *create_invite_response_200();
    SIP_Response *create_invite_response_480();

    SIP_Request *create_bye();
    SIP_Response *create_bye_response_100();
    SIP_Response *create_bye_response_200();

    static bool send_message_callback(void *data, SIP_Transaction *transaction, SIP_Message *msg);
    static bool receive_request_callback(void *data, SIP_Transaction *transaction, SIP_Request *request);
    static bool receive_response_callback(void *data, SIP_Transaction *transaction, SIP_Request *request, SIP_Response *response);

protected:
    SIP_Transaction *_transaction;

    bool _sent_message;
    bool _received_request;
    bool _received_response;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Transaction_Client_Invite_Test : public SIP_Transaction_Test
{
public:
    SIP_Transaction_Client_Invite_Test();
    virtual ~SIP_Transaction_Client_Invite_Test() {}

protected:
    bool send_invite();
    bool receive_response_100();
    bool receive_response_180();
    bool receive_response_200();
    bool receive_response_480();
    bool wait_timer_B();
    bool wait_timer_D();
};

//-------------------------------------------

class SIP_Transaction_Client_Invite_Accepted_Test : public SIP_Transaction_Client_Invite_Test
{
public:
    SIP_Transaction_Client_Invite_Accepted_Test() {}
    virtual ~SIP_Transaction_Client_Invite_Accepted_Test() {}

    bool run();
};

//-------------------------------------------

class SIP_Transaction_Client_Invite_Rejected_Test : public SIP_Transaction_Client_Invite_Test
{
public:
    SIP_Transaction_Client_Invite_Rejected_Test() {}
    virtual ~SIP_Transaction_Client_Invite_Rejected_Test() {}

    bool run();
};

//-------------------------------------------

class SIP_Transaction_Client_Invite_Retransmission_Test : public SIP_Transaction_Client_Invite_Test
{
public:
    SIP_Transaction_Client_Invite_Retransmission_Test() {}
    virtual ~SIP_Transaction_Client_Invite_Retransmission_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Transaction_Client_Non_Invite_Test : public SIP_Transaction_Test
{
public:
    SIP_Transaction_Client_Non_Invite_Test();
    virtual ~SIP_Transaction_Client_Non_Invite_Test() {}

protected:
    bool send_bye();
    bool receive_response_100();
    bool receive_response_200();
    bool wait_timer_F();
    bool wait_timer_K();
};

//-------------------------------------------

class SIP_Transaction_Client_Non_Invite_Accepted_Test : public SIP_Transaction_Client_Non_Invite_Test
{
public:
    SIP_Transaction_Client_Non_Invite_Accepted_Test() {}
    virtual ~SIP_Transaction_Client_Non_Invite_Accepted_Test() {}

    bool run();
};

//-------------------------------------------

class SIP_Transaction_Client_Non_Invite_Retransmission_Test : public SIP_Transaction_Client_Non_Invite_Test
{
public:
    SIP_Transaction_Client_Non_Invite_Retransmission_Test() {}
    virtual ~SIP_Transaction_Client_Non_Invite_Retransmission_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Transaction_Server_Invite_Test : public SIP_Transaction_Test
{
public:
    SIP_Transaction_Server_Invite_Test();
    virtual ~SIP_Transaction_Server_Invite_Test() {}

protected:
    bool receive_invite(bool retransmission = false);
    bool receive_ack();
    bool send_response_100();
    bool send_response_180();
    bool send_response_200();
    bool send_response_480();
    bool wait_timer_H();
    bool wait_timer_I();
};

//-------------------------------------------

class SIP_Transaction_Server_Invite_Accepted_Test : public SIP_Transaction_Server_Invite_Test
{
public:
    SIP_Transaction_Server_Invite_Accepted_Test() {}
    virtual ~SIP_Transaction_Server_Invite_Accepted_Test() {}

    bool run();
};

//-------------------------------------------

class SIP_Transaction_Server_Invite_Rejected_Test : public SIP_Transaction_Server_Invite_Test
{
public:
    SIP_Transaction_Server_Invite_Rejected_Test() {}
    virtual ~SIP_Transaction_Server_Invite_Rejected_Test() {}

    bool run();
};

//-------------------------------------------

class SIP_Transaction_Server_Invite_Retransmission_Test : public SIP_Transaction_Server_Invite_Test
{
public:
    SIP_Transaction_Server_Invite_Retransmission_Test() {}
    virtual ~SIP_Transaction_Server_Invite_Retransmission_Test() {}

    bool run();
};

//-------------------------------------------
//-------------------------------------------

class SIP_Transaction_Server_Non_Invite_Test : public SIP_Transaction_Test
{
public:
    SIP_Transaction_Server_Non_Invite_Test();
    virtual ~SIP_Transaction_Server_Non_Invite_Test() {}

protected:
    bool receive_bye(bool retransmission = false);
    bool send_response_100();
    bool send_response_200();
    bool wait_timer_J();
};

//-------------------------------------------

class SIP_Transaction_Server_Non_Invite_Accepted_Test : public SIP_Transaction_Server_Non_Invite_Test
{
public:
    SIP_Transaction_Server_Non_Invite_Accepted_Test() {}
    virtual ~SIP_Transaction_Server_Non_Invite_Accepted_Test() {}

    bool run();
};

//-------------------------------------------

class SIP_Transaction_Server_Non_Invite_Retransmission_Test : public SIP_Transaction_Server_Non_Invite_Test
{
public:
    SIP_Transaction_Server_Non_Invite_Retransmission_Test() {}
    virtual ~SIP_Transaction_Server_Non_Invite_Retransmission_Test() {}

    bool run();
};

//-------------------------------------------
