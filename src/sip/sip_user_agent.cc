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

void SIP_User_Agent_Client::set_receive_response_callback(receive_response_callback *callback, void *data)
{
    _receive_response_callback = callback;
    _receive_response_callback_data = data;
}

//-------------------------------------------

SIP_Request *SIP_User_Agent_Client::create_request(unsigned int call_id, SIP_Method_Type method)
{
    Logger &logger = SIP_User_Agent::get_logger();

    if (method >= SIP_RESPONSE)
    {
        logger.warning("Failed to send request: invalid request (call_id=%d)", call_id);
        return false;
    }

    SIP_Request *request = new SIP_Request(method);

    SIP_Header_Via *header_via = new SIP_Header_Via();
    header_via->set_protocol_name(SIP_Header_Via::PROTOCOL_NAME_SIP);
    header_via->set_protocol_version(SIP_Header_Via::PROTOCOL_VERSION_2_0);
    header_via->set_transport(SIP_TRANSPORT_UDP);
    header_via->get_host().set_address(_user_agent->get_address());
    header_via->set_port(_user_agent->get_port());
    header_via->set_random_branch();
    request->add_header(header_via);

    SIP_Header_Call_ID *header_call_id = new SIP_Header_Call_ID();
    request->add_header(header_call_id);

    SIP_Header_CSeq *header_cseq = new SIP_Header_CSeq();
    request->add_header(header_cseq);

    SIP_Header_From *header_from = new SIP_Header_From();
    request->add_header(header_from);

    SIP_Header_To *header_to = new SIP_Header_To();
    request->add_header(header_to);

    SIP_Header_Max_Forwards *header_max_forwards = new SIP_Header_Max_Forwards();
    header_max_forwards->set_max_forwards(70);
    request->add_header(header_max_forwards);

    SIP_Header_Contact *header_contact = new SIP_Header_Contact();
    request->add_header(header_contact);

    SIP_Call *call = _user_agent->get_call(call_id);
    if (!call)
    {
        header_call_id->set_random_call_id(_user_agent->get_address());

        header_cseq->set_sequence(1);
        header_cseq->set_method(method);

        header_from->get_address().set_scheme(SIP_Address::SCHEME_SIP);
        header_from->get_address().get_sip_uri().get_host().set_address(_user_agent->get_address());
        header_from->get_address().get_sip_uri().set_port(_user_agent->get_port());
        header_from->set_random_tag();

        header_contact->get_address().set_scheme(SIP_Address::SCHEME_SIP);
        header_contact->get_address().get_sip_uri().get_host().set_address(_user_agent->get_address());
        header_contact->get_address().get_sip_uri().set_port(_user_agent->get_port());
    }else
    {
        SIP_Dialog *dialog = call->get_dialog();
        if (!dialog)
        {
            logger.warning("Failed to create request: invalid dialog (call_id=%d, method=%d)", call_id, method);
            delete request;
            return NULL;
        }

        header_call_id->set_call_id(dialog->get_call_id());

        header_cseq->set_sequence(dialog->get_local_sequence(request));
        header_cseq->set_method(method);

        header_from->set_address(dialog->get_local_uri());
        header_from->set_tag(dialog->get_local_tag());

        header_to->set_address(dialog->get_remote_uri());
        header_to->set_tag(dialog->get_remote_tag());

        header_contact->set_address(dialog->get_local_uri());

        SIP_Address request_uri;
        unsigned short route_size = dialog->get_route_size();
        if (route_size > 0)
        {
            SIP_Header_Route *first_header_route = dialog->get_route(0);
            if (!first_header_route)
            {
                logger.warning("Failed to create request: invalid route header from dialog (call_id=%d, method=%d)", call_id, method);
                delete request;
                return NULL;
            }

            if (first_header_route->get_address().get_sip_uri().is_lr())
            {
                request_uri = dialog->get_remote_target();

                for (unsigned short i = 0; i < route_size; i++)
                {
                    SIP_Header_Route *header_route = dialog->get_route(i);
                    if (header_route)
                        request->add_header(new SIP_Header_Route(*header_route));
                }
            }else
            {
                request_uri = first_header_route->get_address();

                for (unsigned short i = 1; i < route_size; i++)
                {
                    SIP_Header_Route *header_route = dialog->get_route(i);
                    if (header_route)
                        request->add_header(new SIP_Header_Route(*header_route));
                }

                SIP_Header_Route *last_header_route = new SIP_Header_Route();
                last_header_route->set_address(dialog->get_remote_target());
                last_header_route->get_address().get_sip_uri().set_lr(true);
                request->add_header(last_header_route);
            }
        }else
            request_uri = dialog->get_remote_target();

        request->set_request_line(method, request_uri, SIP_VERSION);
    }

    return request;
}

//-------------------------------------------

bool SIP_User_Agent_Client::send_request(unsigned int call_id, SIP_Request *request)
{
    Logger &logger = SIP_User_Agent::get_logger();

    if (!request)
    {
        logger.warning("Failed to send request: invalid request (call_id=%d)", call_id);
        return false;
    }

    SIP_Method_Type method = request->get_message_type();
    bool call_created = false;

    SIP_Call *call = _user_agent->get_call(call_id);
    if (!call)
    {
        if ((method == SIP_REQUEST_INVITE) || (method == SIP_REQUEST_MESSAGE) || (method == SIP_REQUEST_OPTIONS) ||
            (method == SIP_REQUEST_PUBLISH) || (method == SIP_REQUEST_REGISTER) || (method == SIP_REQUEST_SUBSCRIBE))
        {
            SIP_Header_Call_ID *header_call_id = dynamic_cast<SIP_Header_Call_ID *>(request->get_header(SIP_HEADER_CALL_ID));
            SIP_Header_From *header_from = dynamic_cast<SIP_Header_From *>(request->get_header(SIP_HEADER_FROM));
            if ((!header_call_id) || (!header_from))
            {
                logger.warning("Failed to send request: invalid headers (call_id=%d, method=%d)", call_id, method);
                return false;
            }

            if (call_id >= SIP_User_Agent::MAX_CALLS)
            {
                logger.warning("Failed to send request: invalid call-id (call_id=%d, method=%d)", call_id, method);
                return false;
            }

            call = new SIP_Call(call_id);
            call->set_header_call_id(header_call_id->get_call_id());
            call->set_local_tag(header_from->get_tag());
            _user_agent->add_call(call);
            call_created = true;
        }else
        {
            logger.warning("Failed to send request: invalid call (call_id=%d, method=%d)", call_id, method);
            return false;
        }
    }

    if (!call->send_request(request))
    {
        logger.warning("Failed to send request: process send request returned false (call_id=%d, method=%d)", call_id, method);
        if (call_created)
            _user_agent->remove_call(call);
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_User_Agent_Client::receive_response(SIP_Response *response)
{
    Logger &logger = SIP_User_Agent::get_logger();

    unsigned short status_code = response->get_status_code();

    unsigned short via_size = response->get_header_size(SIP_HEADER_VIA);
    if (via_size != 1)
    {
        logger.warning("Failed to receive response: invalid Via header size (size=%d, status_code=%d)", via_size, status_code);
        return false;
    }

    SIP_Call *call = _user_agent->get_call(response);
    if (!call)
    {
        logger.warning("Failed to receive response: invalid call (status_code=%d)", status_code);
        return false;
    }

    if (!call->receive_response(response))
    {
        logger.warning("Failed to receive response: process receive response returned false (status_code=%d)", status_code);
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_User_Agent_Client::receive_response(SIP_Call *call, SIP_Request *request, SIP_Response *response)
{
    Logger &logger = SIP_User_Agent::get_logger();

    try
    {
        if (_receive_response_callback)
        {
            logger.trace("Calling receive response callback");
            return _receive_response_callback(_receive_response_callback_data, _user_agent, call->get_call_id(), request, response);
        }

        logger.trace("Receive response callback not configured");
        return false;
    }catch (std::exception &e)
    {
        logger.warning("Exception when calling receive response callback (msg=%s)", e.what());
        return false;
    }catch (...)
    {
        logger.warning("Exception when calling receive response callback");
        return false;
    }
}

//-------------------------------------------
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
