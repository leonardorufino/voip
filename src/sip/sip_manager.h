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
#include "sip_message.h"
#include "sip_user_agent.h"
#include <list>
#include <map>

class SIP_Manager
{
public:
    static const unsigned int MAX_USER_AGENTS = 100;

    typedef bool (receive_request_callback)(void *data, unsigned int user_agent_id, unsigned int call_id, SIP_Request *request);
    typedef bool (receive_response_callback)(void *data, unsigned int user_agent_id, unsigned int call_id, SIP_Request *request,
                                             SIP_Response *response);

private:
    SIP_Manager();
    ~SIP_Manager();

public:
    static SIP_Manager &instance();
    static void destroy();

    void set_receive_request_callback(receive_request_callback *callback, void *data);
    void set_receive_response_callback(receive_response_callback *callback, void *data);

    SIP_Request *create_request(unsigned int user_agent_id, unsigned int call_id, SIP_Method_Type method);
    bool send_request(unsigned int user_agent_id, unsigned int call_id, SIP_Request *request);

    SIP_Response *create_response(unsigned int user_agent_id, unsigned int call_id, SIP_Request *request, unsigned short status_code);
    bool send_response(unsigned int user_agent_id, unsigned int call_id, SIP_Response *response);

    bool receive_request(SIP_User_Agent *user_agent, unsigned int call_id, SIP_Request *request);
    bool receive_response(SIP_User_Agent *user_agent, unsigned int call_id, SIP_Request *request, SIP_Response *response);

    SIP_User_Agent *get_user_agent(unsigned int id);
    bool create_user_agent(unsigned int user_agent_id, std::string address, unsigned short port);
    void add_user_agent(SIP_User_Agent *user_agent);
    bool remove_user_agent(unsigned int user_agent_id);
    void clear_user_agents();

    bool update();

public:
    static bool user_agent_receive_request_callback(void *data, SIP_User_Agent *user_agent, unsigned int call_id, SIP_Request *request);
    static bool user_agent_receive_response_callback(void *data, SIP_User_Agent *user_agent, unsigned int call_id, SIP_Request *request,
                                                     SIP_Response *response);

private:
    receive_request_callback *_receive_request_callback;
    void *_receive_request_callback_data;

    receive_response_callback *_receive_response_callback;
    void *_receive_response_callback_data;

    std::list<SIP_User_Agent *> _user_agents;

    static SIP_Manager *_instance;
    static Logger _logger;
};
