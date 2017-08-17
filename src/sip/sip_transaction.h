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
#include "sip_address.h"
#include "sip_header.h"
#include "sip_message.h"
#include "util/log_manager.h"
#include "util/timer_manager.h"
#include <string>

class SIP_Transaction
{
public:
    typedef bool (send_message_callback)(void *data, SIP_Transaction *transaction, SIP_Message *msg);
    typedef bool (receive_request_callback)(void *data, SIP_Transaction *transaction, SIP_Request *request);
    typedef bool (receive_response_callback)(void *data, SIP_Transaction *transaction, SIP_Request *request, SIP_Response *response);

    enum SIP_Transaction_Type
    {
        SIP_TRANSACTION_CLIENT_INVITE,
        SIP_TRANSACTION_CLIENT_NON_INVITE,
        SIP_TRANSACTION_SERVER_INVITE,
        SIP_TRANSACTION_SERVER_NON_INVITE,
        SIP_TRANSACTION_TYPE_INVALID
    };

    enum SIP_Timer
    {
        SIP_TIMER_A,
        SIP_TIMER_B,
        SIP_TIMER_C,
        SIP_TIMER_D,
        SIP_TIMER_E,
        SIP_TIMER_F,
        SIP_TIMER_G,
        SIP_TIMER_H,
        SIP_TIMER_I,
        SIP_TIMER_J,
        SIP_TIMER_K,
        SIP_TIMER_COUNT
    };

    static const unsigned long SIP_TIMER_1 = 500;     // 500 milliseconds
    static const unsigned long SIP_TIMER_2 = 4000;    // 4 seconds
    static const unsigned long SIP_TIMER_4 = 5000;    // 5 seconds
    static const unsigned long SIP_TIMER_32s = 32000; // 32 seconds

public:
    SIP_Transaction();
    virtual ~SIP_Transaction();

    virtual SIP_Transaction_Type get_transaction_type() = 0;

    SIP_Transaction *match_transaction(SIP_Message *msg);
    SIP_Transaction *match_transaction_client(SIP_Message *msg);
    SIP_Transaction *match_transaction_server(SIP_Message *msg);

    void set_send_message_callback(send_message_callback *callback, void *data);
    void set_receive_request_callback(receive_request_callback *callback, void *data);
    void set_receive_response_callback(receive_response_callback *callback, void *data);

    unsigned long get_timer_value(SIP_Timer timer);
    void set_timer_value(SIP_Timer timer, unsigned long timer_value);
    void start_timer(SIP_Timer timer, SIP_Transaction *p);
    void stop_timer(SIP_Timer timer);

protected:
    SIP_Request *_saved_request;

    send_message_callback *_send_message_callback;
    void *_send_message_data;

    receive_request_callback *_receive_request_callback;
    void *_receive_request_data;

    receive_response_callback *_receive_response_callback;
    void *_receive_response_data;

    unsigned long _timer_values[SIP_TIMER_COUNT];
    timer_id_t _timer_ids[SIP_TIMER_COUNT];

    static Logger _logger;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Transaction_Client_Invite : public SIP_Transaction
{
public:
    enum State
    {
        sttIdle,
        sttCalling,
        sttProceeding,
        sttCompleted,
        sttTerminated
    };

public:
    SIP_Transaction_Client_Invite() : _state(sttIdle) {}
    ~SIP_Transaction_Client_Invite() {}

    SIP_Transaction_Type get_transaction_type() { return SIP_TRANSACTION_CLIENT_INVITE; }

    State get_state() { return _state; }
    std::string get_state_str();

    bool send_invite(SIP_Request *msg);
    bool send_ack(SIP_Response *msg);
    bool receive_1xx(SIP_Response *msg);
    bool receive_2xx(SIP_Response *msg);
    bool receive_3xx_6xx(SIP_Response *msg);

    static bool timer_A_callback(void *p);
    static bool timer_B_callback(void *p);
    static bool timer_D_callback(void *p);

private:
    State _state;
};

//-------------------------------------------

class SIP_Transaction_Client_Non_Invite : public SIP_Transaction
{
public:
    enum State
    {
        sttIdle,
        sttTrying,
        sttProceeding,
        sttCompleted,
        sttTerminated
    };

public:
    SIP_Transaction_Client_Non_Invite() : _state(sttIdle) {}
    ~SIP_Transaction_Client_Non_Invite() {}

    SIP_Transaction_Type get_transaction_type() { return SIP_TRANSACTION_CLIENT_NON_INVITE; }

    State get_state() { return _state; }
    std::string get_state_str();

    bool send_request(SIP_Request *msg);
    bool receive_1xx(SIP_Response *msg);
    bool receive_2xx_6xx(SIP_Response *msg);

    static bool timer_E_callback(void *p);
    static bool timer_F_callback(void *p);
    static bool timer_K_callback(void *p);

private:
    State _state;
};

//-------------------------------------------

class SIP_Transaction_Server_Invite : public SIP_Transaction
{
public:
    enum State
    {
        sttIdle,
        sttProceeding,
        sttCompleted,
        sttConfirmed,
        sttTerminated
    };

public:
    SIP_Transaction_Server_Invite() : _state(sttIdle), _last_response(NULL) {}
    ~SIP_Transaction_Server_Invite();

    SIP_Transaction_Type get_transaction_type() { return SIP_TRANSACTION_SERVER_INVITE; }

    State get_state() { return _state; }
    std::string get_state_str();

    bool receive_invite(SIP_Request *msg);
    bool receive_ack(SIP_Request *msg);
    bool send_1xx(SIP_Response *msg);
    bool send_2xx(SIP_Response *msg);
    bool send_3xx_6xx(SIP_Response *msg);

    static bool timer_G_callback(void *p);
    static bool timer_H_callback(void *p);
    static bool timer_I_callback(void *p);

private:
    State _state;
    SIP_Response *_last_response;
};

//-------------------------------------------

class SIP_Transaction_Server_Non_Invite : public SIP_Transaction
{
public:
    enum State
    {
        sttIdle,
        sttTrying,
        sttProceeding,
        sttCompleted,
        sttTerminated
    };

public:
    SIP_Transaction_Server_Non_Invite() : _state(sttIdle), _last_response(NULL) {}
    ~SIP_Transaction_Server_Non_Invite();

    SIP_Transaction_Type get_transaction_type() { return SIP_TRANSACTION_SERVER_NON_INVITE; }

    State get_state() { return _state; }
    std::string get_state_str();

    bool receive_request(SIP_Request *msg);
    bool send_1xx(SIP_Response *msg);
    bool send_2xx_6xx(SIP_Response *msg);

    static bool timer_J_callback(void *p);

private:
    State _state;
    SIP_Response *_last_response;
};

//-------------------------------------------
