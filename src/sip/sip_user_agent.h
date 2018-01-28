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
#include "sip_call.h"
#include "sip_transport.h"
#include "util/timer_manager.h"
#include "util/socket.h"
#include <list>
#include <map>

class SIP_User_Agent;

class SIP_User_Agent_Client
{
public:
    typedef bool (receive_response_callback)(void *data, SIP_User_Agent *user_agent, unsigned int call_id, SIP_Request *request,
                                             SIP_Response *response);

public:
    SIP_User_Agent_Client(SIP_User_Agent *ua) : _user_agent(ua), _receive_response_callback(NULL), _receive_response_callback_data(NULL) {}
    ~SIP_User_Agent_Client() {}

    void set_receive_response_callback(receive_response_callback *callback, void *data);

    SIP_Request *create_request(unsigned int call_id, SIP_Method_Type method);
    bool send_request(unsigned int call_id, SIP_Request *request);

    bool receive_response(SIP_Response *response);
    bool receive_response(SIP_Call *call, SIP_Request *request, SIP_Response *response);

private:
    SIP_User_Agent *_user_agent;

    receive_response_callback *_receive_response_callback;
    void *_receive_response_callback_data;

    static Logger _logger;
};

//-------------------------------------------

class SIP_User_Agent_Server
{
public:
    typedef bool (receive_request_callback)(void *data, SIP_User_Agent *user_agent, unsigned int call_id, SIP_Request *request);

public:
    SIP_User_Agent_Server(SIP_User_Agent *ua) : _user_agent(ua), _receive_request_callback(NULL), _receive_request_callback_data(NULL) {}
    ~SIP_User_Agent_Server() {}

    void set_receive_request_callback(receive_request_callback *callback, void *data);

    SIP_Response *create_response(unsigned int call_id, SIP_Request *request, unsigned short status_code);
    bool send_response(unsigned int call_id, SIP_Response *response);

    bool receive_request(SIP_Request *request);
    bool receive_request(SIP_Call *call, SIP_Request *request);

private:
    SIP_User_Agent *_user_agent;

    receive_request_callback *_receive_request_callback;
    void *_receive_request_callback_data;

    static Logger _logger;
};

//-------------------------------------------

class SIP_User_Agent
{
public:
    static const unsigned int MAX_CALLS = 5000;
    static const unsigned short SEND_BUFFER_SIZE = 5000;
    static const unsigned short INVALID_PORT = INVALID_UNSIGNED_SHORT;

public:
    SIP_User_Agent(SIP_Object_ID id);
    ~SIP_User_Agent();

    bool init(std::string address, unsigned short port);
    bool close();

    SIP_Object_ID get_id() { return _id; }

    std::string get_address() { return _address; }
    unsigned short get_port() { return _port; }

    SIP_User_Agent_Client &get_user_agent_client() { return _user_agent_client; }
    SIP_User_Agent_Server &get_user_agent_server() { return _user_agent_server; }

    SIP_Call *get_call(SIP_Message *msg);
    SIP_Call *get_call(unsigned int id);
    void add_call(SIP_Call *call);
    void remove_call(SIP_Call *call);
    void remove_closed_calls();
    void clear_calls();
    unsigned int get_free_call_id();

    SIP_Transport *get_transport(SIP_Transport_Type type, std::string address, unsigned short port);
    void add_transport(SIP_Transport *transport);
    void remove_transport(SIP_Transport *transport);
    void clear_transports();

    void add_pending_message(SIP_Transport *transport, const char *message, unsigned short size);
    void clear_pending_messages();

    bool send_message(SIP_Message *msg);

    bool update();

public:
    static bool call_send_message_callback(void *data, SIP_Call *call, SIP_Message *msg);
    static bool call_receive_request_callback(void *data, SIP_Call *call, SIP_Request *request);
    static bool call_receive_response_callback(void *data, SIP_Call *call, SIP_Request *request, SIP_Response *response);

    static bool transport_connect_callback(void *data, SIP_Transport *transport, bool success);
    static bool transport_accept_callback(void *data, SIP_Transport *transport, SIP_Transport_TCP_Client *accepted,
                                          std::string address, unsigned short port);
    static bool transport_receive_callback(void *data, SIP_Transport *transport, SIP_Message *msg, std::string address,
                                           unsigned short port);

private:
    SIP_Object_ID _id;

    std::string _address;
    unsigned short _port;

    SIP_User_Agent_Client _user_agent_client;
    SIP_User_Agent_Server _user_agent_server;

    std::list<SIP_Call *> _calls;

    unsigned int _next_transport_id;
    std::list<SIP_Transport *> _transports;

    char _send_buffer[SEND_BUFFER_SIZE + 1];
    std::map<SIP_Transport *, std::list<std::pair<const char *, unsigned short>>> _pending_messages;

    static Logger _logger;
};

//-------------------------------------------
