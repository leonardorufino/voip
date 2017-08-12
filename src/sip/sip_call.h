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
#include <list>

class SIP_Call
{
public:
    typedef SIP_Response *(create_response_callback)(void *data, SIP_Call *call, SIP_Request *request, unsigned short status_code);
    typedef bool (send_response_callback)(void *data, SIP_Call *call, SIP_Request *request, SIP_Response *response);

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
    SIP_Call() : _state(STATE_IDLE) {}
    ~SIP_Call();

    void set_state(State state) { _state = state; }
    State get_state() { return _state; }
    std::string get_state_str();

    void set_call_id(std::string call_id) { _call_id = call_id; }
    std::string get_call_id() { return _call_id; }

    void set_create_response_callback(create_response_callback *callback, void *data);
    SIP_Response *call_create_response_callback(SIP_Request *request, unsigned short status_code);

    void set_send_response_callback(send_response_callback *callback, void *data);
    bool call_send_response_callback(SIP_Request *request, SIP_Response *response);

    SIP_Dialog *get_client_dialog(SIP_Message *msg);
    SIP_Dialog *get_server_dialog(SIP_Message *msg);
    SIP_Dialog *get_dialog(std::string call_id, std::string local_tag, std::string remote_tag);
    SIP_Dialog *get_dialog();
    void add_dialog(SIP_Dialog *dialog);
    void remove_dialog(SIP_Dialog *dialog);
    void clear_dialogs();

    bool process_send_request(SIP_Request *request);
    bool process_receive_request(SIP_Request *request);
    bool process_send_response(SIP_Request *request, SIP_Response *response);
    bool process_receive_response(SIP_Request *request, SIP_Response *response);

private:
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

private:
    State _state;
    std::string _call_id;

    create_response_callback *_create_response_callback;
    void *_create_response_data;

    send_response_callback *_send_response_callback;
    void *_send_response_data;

    std::list<SIP_Dialog *> _dialogs;

    static Logger _logger;
};
