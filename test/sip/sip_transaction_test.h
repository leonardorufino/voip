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
#include <iomanip>

class SIP_Transaction_Test
{
public:
    SIP_Transaction_Test() {}
    virtual ~SIP_Transaction_Test() {}

    static bool init();

protected:
    virtual bool run() = 0;

    static bool send_message_callback(SIP_Message *msg);
    static bool receive_request_callback(SIP_Request *request, SIP_Transaction *transaction);
    static bool receive_response_callback(SIP_Request *request, SIP_Response *response, SIP_Transaction *transaction);

protected:
    static bool sent_message;
    static bool received_request;
    static bool received_response;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Transaction_Client_Invite_Test : public SIP_Transaction_Test
{
public:
    SIP_Transaction_Client_Invite_Test() {}
    virtual ~SIP_Transaction_Client_Invite_Test() {}

protected:
    bool send_invite();
    bool send_response_100();
    bool send_response_180();
    bool send_response_200();

protected:
    SIP_Transaction_Client_Invite transaction;
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
