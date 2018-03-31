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

#include "sip_manager.h"

SIP_Manager *SIP_Manager::_instance = NULL;
std::mutex SIP_Manager::_instance_mutex;
Logger SIP_Manager::_logger(Log_Manager::LOG_SIP_MANAGER);

//-------------------------------------------

SIP_Manager::SIP_Manager() : _receive_request_callback(NULL), _receive_request_callback_data(NULL), _receive_response_callback(NULL),
    _receive_response_callback_data(NULL)
{
}

//-------------------------------------------

SIP_Manager::~SIP_Manager()
{
    clear_user_agents();
}

//-------------------------------------------

SIP_Manager &SIP_Manager::instance()
{
    std::lock_guard<std::mutex> lock(_instance_mutex);

    if (_instance == NULL)
        _instance = new SIP_Manager();

    return *_instance;
}

//-------------------------------------------

void SIP_Manager::destroy()
{
    std::lock_guard<std::mutex> lock(_instance_mutex);

    delete _instance;
    _instance = NULL;

    Timer_Manager::destroy();
    Socket_Control::destroy();
}

//-------------------------------------------
//-------------------------------------------

void SIP_Manager::set_receive_request_callback(receive_request_callback *callback, void *data)
{
    _receive_request_callback = callback;
    _receive_request_callback_data = data;
}

//-------------------------------------------

void SIP_Manager::set_receive_response_callback(receive_response_callback *callback, void *data)
{
    _receive_response_callback = callback;
    _receive_response_callback_data = data;
}

//-------------------------------------------
//-------------------------------------------

SIP_Request *SIP_Manager::create_request(unsigned int user_agent_id, unsigned int call_id, SIP_Method_Type method)
{
    SIP_User_Agent *user_agent = get_user_agent(user_agent_id);
    if (!user_agent)
    {
        _logger.warning("Failed to create request: invalid user agent (user_agent_id=%d, call_id=%d, method=%d)",
                        user_agent_id, call_id, method);
        return NULL;
    }

    return user_agent->get_user_agent_client().create_request(call_id, method);
}

//-------------------------------------------

bool SIP_Manager::send_request(unsigned int user_agent_id, unsigned int call_id, SIP_Request *request)
{
    SIP_User_Agent *user_agent = get_user_agent(user_agent_id);
    if (!user_agent)
    {
        _logger.warning("Failed to send request: invalid user agent (user_agent_id=%d, call_id=%d)", user_agent_id, call_id);
        return false;
    }

    return user_agent->get_user_agent_client().send_request(call_id, request);
}

//-------------------------------------------

SIP_Response *SIP_Manager::create_response(unsigned int user_agent_id, unsigned int call_id, SIP_Request *request, unsigned short status_code)
{
    SIP_User_Agent *user_agent = get_user_agent(user_agent_id);
    if (!user_agent)
    {
        _logger.warning("Failed to create response: invalid user agent (user_agent_id=%d, call_id=%d, status_code=%d)",
                        user_agent_id, call_id, status_code);
        return NULL;
    }

    return user_agent->get_user_agent_server().create_response(call_id, request, status_code);
}

//-------------------------------------------

bool SIP_Manager::send_response(unsigned int user_agent_id, unsigned int call_id, SIP_Response *response)
{
    SIP_User_Agent *user_agent = get_user_agent(user_agent_id);
    if (!user_agent)
    {
        _logger.warning("Failed to send response: invalid user agent (user_agent_id=%d, call_id=%d)", user_agent_id, call_id);
        return false;
    }

    return user_agent->get_user_agent_server().send_response(call_id, response);
}

//-------------------------------------------

bool SIP_Manager::receive_request(SIP_User_Agent *user_agent, unsigned int call_id, SIP_Request *request)
{
    try
    {
        if (!_receive_request_callback)
        {
            _logger.warning("Receive request callback not configured");
            return false;
        }

        _logger.trace("Calling receive request callback");
        return _receive_request_callback(_receive_request_callback_data, user_agent->get_user_agent_id(), call_id, request);

    }catch (std::exception &e)
    {
        _logger.warning("Exception in receive request (msg=%s)", e.what());
        return false;
    }catch (...)
    {
        _logger.warning("Exception in receive request");
        return false;
    }
}

//-------------------------------------------

bool SIP_Manager::receive_response(SIP_User_Agent *user_agent, unsigned int call_id, SIP_Request *request, SIP_Response *response)
{
    try
    {
        if (!_receive_response_callback)
        {
            _logger.warning("Receive response callback not configured");
            return false;
        }

        _logger.trace("Calling receive response callback");
        return _receive_response_callback(_receive_response_callback_data, user_agent->get_user_agent_id(), call_id, request, response);

    }catch (std::exception &e)
    {
        _logger.warning("Exception in receive response (msg=%s)", e.what());
        return false;
    }catch (...)
    {
        _logger.warning("Exception in receive response");
        return false;
    }
}

//-------------------------------------------
//-------------------------------------------

SIP_User_Agent *SIP_Manager::get_user_agent(unsigned int id)
{
    std::list<SIP_User_Agent *>::iterator it = _user_agents.begin();
    while (it != _user_agents.end())
    {
        SIP_User_Agent *user_agent = *it++;

        if (user_agent->get_user_agent_id() == id)
            return user_agent;
    }

    return NULL;
}

//-------------------------------------------

bool SIP_Manager::create_user_agent(unsigned int user_agent_id, std::string address, unsigned short port)
{
    if (user_agent_id >= MAX_USER_AGENTS)
    {
        _logger.warning("Failed to create user agent: invalid user agent id (user_agent_id=%d)", user_agent_id);
        return false;
    }

    SIP_User_Agent *user_agent = get_user_agent(user_agent_id);
    if (user_agent)
    {
        _logger.warning("Failed to create user agent: user agent already exist (user_agent_id=%d)", user_agent_id);
        return false;
    }

    SIP_Object_ID id;
    id._user_agent = user_agent_id;
    user_agent = new SIP_User_Agent(id);

    if (!user_agent->init(address, port))
    {
        _logger.warning("Failed to create user agent: user agent init failed (user_agent_id=%d)", user_agent_id);
        delete user_agent;
        return false;
    }

    add_user_agent(user_agent);

    _logger.trace("User agent created (user_agent_id=%d)", user_agent_id);
    return true;
}

//-------------------------------------------

void SIP_Manager::add_user_agent(SIP_User_Agent *user_agent)
{
    user_agent->get_user_agent_server().set_receive_request_callback(user_agent_receive_request_callback, this);
    user_agent->get_user_agent_client().set_receive_response_callback(user_agent_receive_response_callback, this);

    _user_agents.push_back(user_agent);
}

//-------------------------------------------

bool SIP_Manager::remove_user_agent(unsigned int user_agent_id)
{
    SIP_User_Agent *user_agent = get_user_agent(user_agent_id);
    if (!user_agent)
    {
        _logger.warning("Failed to remove user agent: invalid user agent (user_agent_id=%d)", user_agent_id);
        return false;
    }

    _user_agents.remove(user_agent);
    delete user_agent;

    _logger.trace("User agent removed (user_agent_id=%d)", user_agent_id);
    return true;
}

//-------------------------------------------

void SIP_Manager::clear_user_agents()
{
    std::list<SIP_User_Agent *>::iterator it = _user_agents.begin();
    while (it != _user_agents.end())
    {
        SIP_User_Agent *user_agent = *it++;
        _user_agents.pop_front();
        delete user_agent;
    }
}

//-------------------------------------------

bool SIP_Manager::update()
{
    Timer_Manager &timer = Timer_Manager::instance();
    timer.run();

    Socket_Control &socket = Socket_Control::instance();
    socket.run();

    std::list<SIP_User_Agent *>::iterator it = _user_agents.begin();
    while (it != _user_agents.end())
    {
        SIP_User_Agent *user_agent = *it++;
        user_agent->update();
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Manager::user_agent_receive_request_callback(void *data, SIP_User_Agent *user_agent, unsigned int call_id, SIP_Request *request)
{
    SIP_Manager *manager = reinterpret_cast<SIP_Manager *>(data);
    if ((!manager) || (!user_agent) || (call_id == SIP_Object_ID::INVALID_CALL) || (!request))
    {
        _logger.warning("Invalid user agent receive request callback parameters");
        return false;
    }

    return manager->receive_request(user_agent, call_id, request);
}

//-------------------------------------------

bool SIP_Manager::user_agent_receive_response_callback(void *data, SIP_User_Agent *user_agent, unsigned int call_id, SIP_Request *request,
                                                       SIP_Response *response)
{
    SIP_Manager *manager = reinterpret_cast<SIP_Manager *>(data);
    if ((!manager) || (!user_agent) || (call_id == SIP_Object_ID::INVALID_CALL) || (!request) || (!response))
    {
        _logger.warning("Invalid user agent receive response callback parameters");
        return false;
    }

    return manager->receive_response(user_agent, call_id, request, response);
}

//-------------------------------------------
