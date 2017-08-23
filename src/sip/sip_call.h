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
#include "sip_dialog.h"
#include "sip_transaction.h"
#include <list>

class SIP_Call
{
public:
    typedef bool (send_message_callback)(void *data, SIP_Call *call, SIP_Message *msg);
    typedef bool (receive_request_callback)(void *data, SIP_Call *call, SIP_Request *request);
    typedef bool (receive_response_callback)(void *data, SIP_Call *call, SIP_Request *request, SIP_Response *response);
    typedef SIP_Response *(create_response_callback)(void *data, SIP_Call *call, SIP_Request *request, unsigned short status_code);

    static const unsigned int INVALID_CALL_ID = INVALID_UNSIGNED_INT;

    enum State
    {
        STATE_IDLE,
        STATE_CALLING_IN,
        STATE_CALLING_OUT,
        STATE_RINGING_IN,
        STATE_RINGING_OUT,
        STATE_CANCELING_IN,
        STATE_CANCELING_OUT,
        STATE_CANCELED_IN,
        STATE_CANCELED_OUT,
        STATE_WAITING_ACK_IN,
        STATE_WAITING_ACK_OUT,
        STATE_ACTIVE,
        STATE_CLOSING_IN,
        STATE_CLOSING_OUT,
        STATE_CLOSED,
        STATE_INVALID
    };

public:
    SIP_Call(unsigned int call_id) : _call_id(call_id), _state(STATE_IDLE) {}
    ~SIP_Call();

    unsigned int get_call_id() { return _call_id; }

    void set_state(State state) { _state = state; }
    State get_state() { return _state; }
    std::string get_state_str();

    void set_header_call_id(std::string header_call_id) { _header_call_id = header_call_id; }
    std::string get_header_call_id() { return _header_call_id; }

    void set_local_tag(std::string local_tag) { _local_tag = local_tag; }
    std::string get_local_tag() { return _local_tag; }

    void set_send_message_callback(send_message_callback *callback, void *data);
    void set_receive_request_callback(receive_request_callback *callback, void *data);
    void set_receive_response_callback(receive_response_callback *callback, void *data);
    void set_create_response_callback(create_response_callback *callback, void *data);

    SIP_Dialog *get_client_dialog(SIP_Message *msg);
    SIP_Dialog *get_server_dialog(SIP_Message *msg);
    SIP_Dialog *get_dialog(std::string call_id, std::string local_tag, std::string remote_tag);
    SIP_Dialog *get_dialog();
    void add_dialog(SIP_Dialog *dialog);
    void remove_dialog(SIP_Dialog *dialog);
    void clear_dialogs();

    SIP_Transaction *get_transaction(SIP_Message *msg);
    void add_transaction(SIP_Transaction *transaction);
    void remove_transaction(SIP_Transaction *transaction);
    void clear_transactions();

    bool send_request(SIP_Request *request);
    bool receive_request(SIP_Request *request);
    bool send_response(SIP_Response *response);
    bool receive_response(SIP_Response *response);

private:
    bool process_send_request(SIP_Request *request);
    bool process_receive_request(SIP_Request *request);
    bool process_send_response(SIP_Request *request, SIP_Response *response);
    bool process_receive_response(SIP_Request *request, SIP_Response *response);

    bool process_send_request_idle(SIP_Request *request);
    bool process_receive_request_idle(SIP_Request *request);

    bool process_send_response_calling_in(SIP_Request *request, SIP_Response *response);
    bool process_receive_response_calling_out(SIP_Request *request, SIP_Response *response);

    bool process_send_request_ringing_in(SIP_Request *request);
    bool process_receive_request_ringing_in(SIP_Request *request);
    bool process_send_response_ringing_in(SIP_Request *request, SIP_Response *response);
    bool process_receive_response_ringing_in(SIP_Request *request, SIP_Response *response);
    bool process_send_request_ringing_out(SIP_Request *request);
    bool process_receive_request_ringing_out(SIP_Request *request);
    bool process_send_response_ringing_out(SIP_Request *request, SIP_Response *response);
    bool process_receive_response_ringing_out(SIP_Request *request, SIP_Response *response);

    bool process_send_response_canceling_in(SIP_Request *request, SIP_Response *response);
    bool process_receive_response_canceling_out(SIP_Request *request, SIP_Response *response);

    bool process_send_response_canceled_in(SIP_Request *request, SIP_Response *response);
    bool process_receive_response_canceled_out(SIP_Request *request, SIP_Response *response);

    bool process_receive_request_waiting_ack_in(SIP_Request *request);
    bool process_send_request_waiting_ack_out(SIP_Request *request);

    bool process_send_request_active(SIP_Request *request);
    bool process_receive_request_active(SIP_Request *request);
    bool process_send_response_active(SIP_Request *request, SIP_Response *response);
    bool process_receive_response_active(SIP_Request *request, SIP_Response *response);

    bool process_send_response_closing_in(SIP_Request *request, SIP_Response *response);
    bool process_receive_response_closing_out(SIP_Request *request, SIP_Response *response);

    bool send_response(SIP_Request *request, unsigned short status_code);

public:
    static bool transaction_send_message_callback(void *data, SIP_Transaction *transaction, SIP_Message *msg);
    static bool transaction_receive_request_callback(void *data, SIP_Transaction *transaction, SIP_Request *request);
    static bool transaction_receive_response_callback(void *data, SIP_Transaction *transaction, SIP_Request *request, SIP_Response *response);

private:
    unsigned int _call_id;
    State _state;

    std::string _header_call_id;
    std::string _local_tag;

    send_message_callback *_send_message_callback;
    void *_send_message_callback_data;

    receive_request_callback *_receive_request_callback;
    void *_receive_request_callback_data;

    receive_response_callback *_receive_response_callback;
    void *_receive_response_callback_data;

    create_response_callback *_create_response_callback;
    void *_create_response_callback_data;

    std::list<SIP_Dialog *> _dialogs;
    std::list<SIP_Transaction *> _transactions;

    static Logger _logger;
};
