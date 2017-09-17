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

#include "sip_user_agent.h"

Logger SIP_User_Agent::_logger(Log_Manager::LOG_SIP_USER_AGENT);

//-------------------------------------------

SIP_User_Agent::SIP_User_Agent() : _user_agent_client(this), _user_agent_server(this)
{
}

//-------------------------------------------

SIP_User_Agent::~SIP_User_Agent()
{
    clear_calls();
    clear_transports();
}

//-------------------------------------------

bool SIP_User_Agent::init(std::string address, unsigned short port)
{
    _address = address;
    _port = port;

    SIP_Transport_UDP *udp = new SIP_Transport_UDP();
    add_transport(udp);

    if (!udp->init(_address, _port))
    {
        _logger.warning("Failed to init: UDP transport");
        clear_transports();
        return false;
    }

    SIP_Transport_TCP_Server *tcp_server = new SIP_Transport_TCP_Server();
    add_transport(tcp_server);

    if (!tcp_server->init(_address, _port))
    {
        _logger.warning("Failed to init: TCP server transport");
        clear_transports();
        return false;
    }

    if (!tcp_server->listen(MAX_CALLS))
    {
        _logger.warning("Failed to init: TCP server transport listen");
        clear_transports();
        return false;
    }

    _logger.trace("User agent initialized");
    return true;
}

//-------------------------------------------

bool SIP_User_Agent::close()
{
    clear_calls();
    clear_transports();

    _logger.trace("User agent closed");
    return true;
}

//-------------------------------------------

SIP_Call *SIP_User_Agent::get_call(SIP_Message *msg)
{
    SIP_Header_Call_ID *header_call_id = dynamic_cast<SIP_Header_Call_ID *>(msg->get_header(SIP_HEADER_CALL_ID));
    SIP_Header_From *header_from = dynamic_cast<SIP_Header_From *>(msg->get_header(SIP_HEADER_FROM));
    SIP_Header_To *header_to = dynamic_cast<SIP_Header_To *>(msg->get_header(SIP_HEADER_TO));
    if ((!header_call_id) || (!header_from) || (!header_to))
    {
        _logger.warning("Failed to get call: invalid headers");
        return NULL;
    }

    std::string call_id = header_call_id->get_call_id();
    std::string local_tag = (msg->get_message_type() == SIP_RESPONSE) ? header_from->get_tag() : header_to->get_tag();

    std::list<SIP_Call *>::iterator it = _calls.begin();
    while (it != _calls.end())
    {
        SIP_Call *call = *it++;

        if ((call->get_header_call_id() == call_id) && (call->get_local_tag() == local_tag))
            return call;
    }

    return NULL;
}

//-------------------------------------------

SIP_Call *SIP_User_Agent::get_call(unsigned int call_id)
{
    std::list<SIP_Call *>::iterator it = _calls.begin();
    while (it != _calls.end())
    {
        SIP_Call *call = *it++;

        if (call->get_call_id() == call_id)
            return call;
    }

    return NULL;
}

//-------------------------------------------

void SIP_User_Agent::add_call(SIP_Call *call)
{
    call->set_send_message_callback(call_send_message_callback, this);
    call->set_receive_request_callback(call_receive_request_callback, this);
    call->set_receive_response_callback(call_receive_response_callback, this);

    _calls.push_back(call);
}

//-------------------------------------------

void SIP_User_Agent::remove_call(SIP_Call *call)
{
    _calls.remove(call);
    delete call;
}

//-------------------------------------------

void SIP_User_Agent::clear_calls()
{
    std::list<SIP_Call *>::iterator it = _calls.begin();
    while (it != _calls.end())
    {
        SIP_Call *call = *it++;
        _calls.pop_front();
        delete call;
    }
}

//-------------------------------------------

unsigned int SIP_User_Agent::get_free_call_id()
{
    unsigned int call_id = MAX_CALLS - 1;

    while (call_id >= 0)
    {
        if (!get_call(call_id))
            return call_id;

        call_id--;
    }

    return SIP_Call::INVALID_CALL_ID;
}

//-------------------------------------------

SIP_Transport *SIP_User_Agent::get_transport(SIP_Transport_Type type, std::string address, unsigned short port)
{
    std::list<SIP_Transport *>::iterator it = _transports.begin();
    while (it != _transports.end())
    {
        SIP_Transport *transport = *it++;

        switch (type)
        {
            case SIP_TRANSPORT_UDP:
            {
                SIP_Transport_UDP *transport_udp = dynamic_cast<SIP_Transport_UDP *>(transport);
                if (!transport_udp)
                    continue;

                return transport;
            }

            case SIP_TRANSPORT_TCP:
            {
                SIP_Transport_TCP_Client *transport_tcp = dynamic_cast<SIP_Transport_TCP_Client *>(transport);
                if (!transport_tcp)
                    continue;

                if ((transport_tcp->get_remote_address() == address) && (transport_tcp->get_remote_port() == port))
                    return transport;
            }

            default:
                break;
        }
    }

    return NULL;
}

//-------------------------------------------

void SIP_User_Agent::add_transport(SIP_Transport *transport)
{
    transport->set_connect_callback(transport_connect_callback, this);
    transport->set_accept_callback(transport_accept_callback, this);
    transport->set_receive_callback(transport_receive_callback, this);

    _transports.push_back(transport);
}

//-------------------------------------------

void SIP_User_Agent::remove_transport(SIP_Transport *transport)
{
    transport->close();
    _transports.remove(transport);
    delete transport;
}

//-------------------------------------------

void SIP_User_Agent::clear_transports()
{
    std::list<SIP_Transport *>::iterator it = _transports.begin();
    while (it != _transports.end())
    {
        SIP_Transport *transport = *it++;
        transport->close();
        _transports.pop_front();
        delete transport;
    }
}

//-------------------------------------------

bool SIP_User_Agent::send_message(SIP_Message *msg)
{
    if (!msg)
    {
        _logger.warning("Failed to send message: invalid parameter");
        return false;
    }

    SIP_Method_Type method = msg->get_message_type();

    SIP_Header_Via *header_via = dynamic_cast<SIP_Header_Via *>(msg->get_header(SIP_HEADER_VIA));
    if (!header_via)
    {
        _logger.warning("Failed to send request: invalid Via header (method=%d)", method);
        return false;
    }

    SIP_Transport_Type transport_type = header_via->get_transport();

    std::string remote_address;
    unsigned short remote_port = SIP_Transport::INVALID_PORT;

    if (method != SIP_RESPONSE)
    {
        SIP_Header_Route *header_route = dynamic_cast<SIP_Header_Route *>(msg->get_header(SIP_HEADER_ROUTE));

        if ((header_route) && (header_route->get_address().get_sip_uri().is_lr()))
        {
            remote_address = header_route->get_address().get_sip_uri().get_host().get_address();
            remote_port = header_route->get_address().get_sip_uri().get_port();
        }else
        {
            SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
            if (!request)
            {
                _logger.warning("Failed to send message: invalid request (method=%d)", method);
                return false;
            }

            remote_address = request->get_request_uri().get_sip_uri().get_host().get_address();
            remote_port = request->get_request_uri().get_sip_uri().get_port();
        }
    }else
    {
        remote_address = header_via->get_received();
        if (remote_address.empty())
            remote_address = header_via->get_host().get_address();

        remote_port = header_via->get_port(); //TODO: get Via rport or SIP default
    }

    if ((remote_address.empty()) || (remote_port == SIP_Transport::INVALID_PORT))
    {
        _logger.warning("Failed to send message: invalid remote address (method=%d, address=%s, port=%d)",
                        method, remote_address.c_str(), remote_port);
        return false;
    }

    std::string send_buffer;
    msg->encode(send_buffer);
    int size = (int) send_buffer.size();

    SIP_Transport *transport = get_transport(transport_type, remote_address, remote_port);
    if (!transport)
    {
        if (transport_type == SIP_TRANSPORT_TCP)
        {
            SIP_Transport_TCP_Client *tcp_client = new SIP_Transport_TCP_Client();
            add_transport(tcp_client);

            if (!tcp_client->init(_address, 0))
            {
                _logger.warning("Failed to send message: failed to init TCP client transport (address=%s)", _address.c_str());
                remove_transport(transport);
                return false;
            }

            if (!tcp_client->connect(remote_address, remote_port))
            {
                _logger.warning("Failed to send message: failed to connect TCP client transport (address=%s, port=%d)",
                                remote_address.c_str(), remote_port);
                remove_transport(transport);
                return false;
            }

            std::list<std::string> messages;
            messages.push_back(send_buffer);

            _pending_messages[tcp_client] = messages;

            _logger.trace("Connecting TCP client transport: send message is pending (method=%d, address=%s, port=%d, size=%d)",
                          method, remote_address.c_str(), remote_port, size);
            return true;
        }else
        {
            _logger.warning("Failed to send request: transport not found (method=%d, transport=%d, address=%s, port=%d)",
                            method, transport_type, remote_address.c_str(), remote_port);
            return false;
        }
    }else
    {
        SIP_Transport_TCP_Client *tcp_client = dynamic_cast<SIP_Transport_TCP_Client *>(transport);
        if ((tcp_client) && (!tcp_client->is_connected()))
        {
            std::map<SIP_Transport *, std::list<std::string>>::iterator it = _pending_messages.find(tcp_client);
            if (it != _pending_messages.end())
            {
                _pending_messages[tcp_client].push_back(send_buffer);

                _logger.trace("Waiting TCP client transport connection: send message is pending (method=%d, address=%s, port=%d, size=%d)",
                                method, remote_address.c_str(), remote_port, size);
                return true;
            }else
            {
                _logger.warning("Failed to send request: invalid TCP client transport state (method=%d, address=%s, port=%d)",
                                method, remote_address.c_str(), remote_port);
                return false;
            }
        }
    }

    _logger.trace("Sending message (method=%d, address=%s, port=%d, size=%d)", method, remote_address.c_str(), remote_port, size);
    return transport->send_message(send_buffer.c_str(), size, remote_address, remote_port);
}

//-------------------------------------------

bool SIP_User_Agent::call_send_message_callback(void *data, SIP_Call *call, SIP_Message *msg)
{
    SIP_User_Agent *user_agent = reinterpret_cast<SIP_User_Agent *>(data);
    if ((!user_agent) || (!call) || (!msg))
    {
        _logger.warning("Invalid call send message callback parameters");
        return NULL;
    }

    return user_agent->send_message(msg);
}

//-------------------------------------------

bool SIP_User_Agent::call_receive_request_callback(void *data, SIP_Call *call, SIP_Request *request)
{
    SIP_User_Agent *user_agent = reinterpret_cast<SIP_User_Agent *>(data);
    if ((!user_agent) || (!call) || (!request))
    {
        _logger.warning("Invalid call receive request callback parameters");
        return NULL;
    }

    return user_agent->_user_agent_server.receive_request(call, request);
}

//-------------------------------------------

bool SIP_User_Agent::call_receive_response_callback(void *data, SIP_Call *call, SIP_Request *request, SIP_Response *response)
{
    SIP_User_Agent *user_agent = reinterpret_cast<SIP_User_Agent *>(data);
    if ((!user_agent) || (!call) || (!request) || (!response))
    {
        _logger.warning("Invalid call receive response callback parameters");
        return NULL;
    }

    return user_agent->_user_agent_client.receive_response(call, request, response);
}

//-------------------------------------------

bool SIP_User_Agent::transport_connect_callback(void *data, SIP_Transport *transport, bool success)
{
    SIP_User_Agent *user_agent = reinterpret_cast<SIP_User_Agent *>(data);
    SIP_Transport_TCP_Client *transport_tcp = dynamic_cast<SIP_Transport_TCP_Client *>(transport);
    if ((!user_agent) || (!transport) || (!transport_tcp))
    {
        _logger.warning("Invalid transport connect callback parameters");
        return false;
    }

    _logger.trace("Transport connect callback (success=%d)", success);

    std::map<SIP_Transport *, std::list<std::string>>::iterator it = user_agent->_pending_messages.find(transport);
    if (it != user_agent->_pending_messages.end())
    {
        if (success)
        {
            std::list<std::string> &messages = it->second;
            std::list<std::string>::iterator it2 = messages.begin();
            while (it2 != messages.end())
            {
                std::string &message = *it2++;
                int size = (int) message.size();

                _logger.trace("Sending pending message (size=%d)", size);

                if (!transport->send_message(message.c_str(), size, transport_tcp->get_remote_address(), transport_tcp->get_remote_port()))
                    _logger.warning("Failed to send message in transport connect callback (size=%d)", size);
            }
        }

        user_agent->_pending_messages.erase(transport);
    }else
        _logger.warning("Failed in transport connect callback: invalid pending messages (success=%d)", success);

    return true;
}

//-------------------------------------------

bool SIP_User_Agent::transport_accept_callback(void *data, SIP_Transport *transport, SIP_Transport_TCP_Client *accepted,
                                               std::string address, unsigned short port)
{
    SIP_User_Agent *user_agent = reinterpret_cast<SIP_User_Agent *>(data);
    if ((!user_agent) || (!transport))
    {
        _logger.warning("Invalid transport connect callback parameters");
        return false;
    }

    _logger.trace("Transport accept callback (address=%s, port=%d)", address.c_str(), port);

    user_agent->add_transport(accepted);
    return true;
}

//-------------------------------------------

bool SIP_User_Agent::transport_receive_callback(void *data, SIP_Transport *transport, const char *buffer, int size,
                                                std::string address, unsigned short port)
{
    SIP_User_Agent *user_agent = reinterpret_cast<SIP_User_Agent *>(data);
    if ((!user_agent) || (!transport))
    {
        _logger.warning("Invalid transport receive callback parameters");
        return false;
    }

    SIP_Message *msg = SIP_Message::decode_msg(buffer);
    if (!msg)
    {
        _logger.warning("Failed to decode SIP message received");
        return false;
    }

    SIP_Method_Type method = msg->get_message_type();
    SIP_Header_Via *header_via = dynamic_cast<SIP_Header_Via *>(msg->get_header(SIP_HEADER_VIA));

    if ((!msg->get_header(SIP_HEADER_CALL_ID)) || (!msg->get_header(SIP_HEADER_CSEQ)) || (!msg->get_header(SIP_HEADER_FROM)) ||
        (!msg->get_header(SIP_HEADER_TO)) || (!header_via))
    {
        _logger.warning("Invalid SIP message received: required headers are not present (method=%d)", method);
        delete msg;
        return false;
    }

    _logger.trace("Message received (method=%d)", method);

    if (method != SIP_RESPONSE)
    {
        SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
        if (!request)
        {
            _logger.warning("Invalid SIP request received (method=%d)", method);
            delete msg;
            return false;
        }

        if (!user_agent->_user_agent_server.receive_request(request))
        {
            _logger.warning("Receive request returned false (method=%d)", method);
            delete msg;
            return false;
        }

        delete msg;
        return true;
    }else
    {
        if (header_via->get_host().get_address() != address)
            header_via->set_received(address);

        SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
        if (!response)
        {
            _logger.warning("Invalid SIP response received (method=%d)", method);
            delete msg;
            return false;
        }

        if (!user_agent->_user_agent_client.receive_response(response))
        {
            _logger.warning("Receive response returned false (method=%d)", method);
            delete msg;
            return false;
        }

        delete msg;
        return true;
    }
}

//-------------------------------------------
