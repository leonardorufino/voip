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

#include "sip_defs.h"
#include "sip_header.h"
#include "sip_message.h"
#include "sip_request.h"
#include "sip_response.h"
#include "common/timer_manager.h"

class SIP_Transaction
{
public:
    SIP_Transaction();
    virtual ~SIP_Transaction();

    virtual SIP_Transaction_Type get_transaction_type() = 0;

    SIP_Transaction *match_transaction(SIP_Message *msg);
    SIP_Transaction *match_transaction_client(SIP_Message *msg);
    SIP_Transaction *match_transaction_server(SIP_Message *msg);

    SIP_Request *get_saved_request() { return _saved_request; }

    unsigned long get_timer_value(SIP_Timer timer);
    void set_timer_value(SIP_Timer timer, unsigned long timer_value);
    void start_timer(SIP_Timer timer, SIP_Transaction *p);
    void stop_timer(SIP_Timer timer);

protected:
    SIP_Request *_saved_request;

    unsigned long _timer_values[SIP_TIMER_COUNT];
    Timer_Id _timer_ids[SIP_TIMER_COUNT];
};
