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
#include <list>

class SIP_Dialog
{
public:
    enum State
    {
        STATE_IDLE,
        STATE_EARLY,
        STATE_CONFIRMED,
        STATE_TERMINATED
    };

public:
    SIP_Dialog(SIP_Object_ID id);
    ~SIP_Dialog();

    bool set_client_dialog(SIP_Request *request, SIP_Response *response);
    bool set_server_dialog(SIP_Request *request, SIP_Response *response);

    void set_state(State state) { _state = state; }
    State get_state() { return _state; }

    void set_call_id(std::string call_id) { _call_id = call_id; }
    std::string get_call_id() { return _call_id; }

    void set_local_tag(std::string tag) { _local_tag = tag; }
    std::string get_local_tag() { return _local_tag; }

    void set_remote_tag(std::string tag) { _remote_tag = tag; }
    std::string get_remote_tag() { return _remote_tag; }

    void set_local_sequence(unsigned long sequence) { _local_sequence = sequence; }
    unsigned long get_local_sequence() { return _local_sequence; }
    unsigned long get_local_sequence(SIP_Request *request);

    void set_remote_sequence(unsigned long sequence) { _remote_sequence = sequence; }
    unsigned long get_remote_sequence() { return _remote_sequence; }
    bool check_remote_sequence(SIP_Request *request);

    void set_local_uri(const SIP_Address &uri) { _local_uri = uri; }
    SIP_Address &get_local_uri() { return _local_uri; }

    void set_remote_uri(const SIP_Address &uri) { _remote_uri = uri; }
    SIP_Address &get_remote_uri() { return _remote_uri; }

    void set_remote_target(const SIP_Address &target) { _remote_target = target; }
    void set_remote_target(SIP_Message *message);
    SIP_Address &get_remote_target() { return _remote_target; }

    void add_route_back(SIP_Header_Route *route);
    void add_route_front(SIP_Header_Route *route);
    void clear_routes();
    unsigned short get_route_size();
    SIP_Header_Route *get_route(int pos);

private:
    SIP_Object_ID _id;

    State _state;
    std::string _call_id;
    std::string _local_tag;
    std::string _remote_tag;
    unsigned long _local_sequence;
    unsigned long _remote_sequence;
    unsigned long _invite_local_sequence;
    unsigned long _invite_remote_sequence;
    SIP_Address _local_uri;
    SIP_Address _remote_uri;
    SIP_Address _remote_target;
    std::list<SIP_Header_Route *> _routes;

    static Logger _logger;
};
