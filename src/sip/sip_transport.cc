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

#include "sip_transport.h"

Logger SIP_Transport::_logger(Log_Manager::LOG_SIP_TRANSPORT);

//-------------------------------------------

SIP_Transport::SIP_Transport(SIP_Object_ID id) : _id(id), _port(INVALID_PORT), _socket(NULL), _connect_callback(NULL),
    _connect_callback_data(NULL), _accept_callback(NULL), _accept_callback_data(NULL), _receive_callback(NULL),
    _receive_callback_data(NULL)
{
}

//-------------------------------------------

SIP_Transport::~SIP_Transport()
{
    if (_socket)
        close();
}

//-------------------------------------------

void SIP_Transport::set_connect_callback(connect_callback *callback, void *data)
{
    _connect_callback = callback;
    _connect_callback_data = data;
}

//-------------------------------------------


void SIP_Transport::set_accept_callback(accept_callback *callback, void *data)
{
    _accept_callback = callback;
    _accept_callback_data = data;
}

//-------------------------------------------

void SIP_Transport::set_receive_callback(receive_callback *callback, void *data)
{
    _receive_callback = callback;
    _receive_callback_data = data;
}

//-------------------------------------------

bool SIP_Transport::init(std::string address, unsigned short port)
{
    Socket_Control &control = Socket_Control::instance();

    if (!_socket)
    {
        _logger.warning("Failed to init: invalid socket [%s]", _id.to_string().c_str());
        return false;
    }

    if ((address.empty()) || (port == INVALID_PORT))
    {
        _logger.warning("Failed to init: invalid parameters (address=%s, port=%d) [%s]", address.c_str(), port, _id.to_string().c_str());
        return false;
    }

    _address = address;
    _port = port;

    Socket::Address_Family family = Socket::address_to_address_family(_address);
    if (family == Socket::ADDRESS_FAMILY_INVALID)
    {
        _logger.warning("Failed to init: invalid address family (address=%s) [%s]", address.c_str(), _id.to_string().c_str());
        return false;
    }

    _socket->set_connect_callback(socket_connect_callback, this);
    _socket->set_accept_callback(socket_accept_callback, this);
    _socket->set_receive_callback(socket_receive_callback, this);

    if (!_socket->create(family))
    {
        _logger.warning("Failed to init: create failed [%s]", _id.to_string().c_str());
        return false;
    }

    _socket->set_so_snd_buf();
    _socket->set_so_rcv_buf();
    _socket->set_so_reuse_addr();

    if (!_socket->bind(_address, _port))
    {
        _logger.warning("Failed to init: bind failed (address=%s, port=%d) [%s]", address.c_str(), port, _id.to_string().c_str());
        return false;
    }

    if (!_socket->set_non_blocking())
    {
        _logger.warning("Failed to init: set non-blocking failed [%s]", _id.to_string().c_str());
        return false;
    }

    if (!control.add_socket(*_socket))
    {
        _logger.warning("Failed to init: add socket failed [%s]", _id.to_string().c_str());
        return false;
    }

    _logger.trace("Transport initialized (address=%s, port=%d) [%s]", address.c_str(), port, _id.to_string().c_str());
    return true;
}

//-------------------------------------------

bool SIP_Transport::close()
{
    Socket_Control &control = Socket_Control::instance();
    bool ret = true;

    if (!_socket)
    {
        _logger.warning("Failed to close: invalid socket [%s]", _id.to_string().c_str());
        return false;
    }

    if (!control.remove_socket(*_socket))
    {
        _logger.warning("Failed to close: remove socket failed [%s]", _id.to_string().c_str());
        ret = false;
    }

    if (!_socket->close())
    {
        _logger.warning("Failed to close: close failed [%s]", _id.to_string().c_str());
        ret = false;
    }

    delete _socket;
    _socket = NULL;

    _logger.trace("Transport closed [%s]", _id.to_string().c_str());
    return ret;
}

//-------------------------------------------

bool SIP_Transport::send_message(const char *buffer, int size, std::string address, unsigned short port)
{
    if (!_socket)
    {
        _logger.warning("Failed to send message: invalid socket [%s]", _id.to_string().c_str());
        return false;
    }

    bool ret;
    if (_socket->get_socket_type() == Socket::SOCKET_UDP)
        ret = _socket->send(buffer, size, address, port);
    else
        ret = _socket->send(buffer, size);

    if (!ret)
    {
        _logger.warning("Failed to send message: send failed (address=%s, port=%d) [%s]", address.c_str(), port, _id.to_string().c_str());
        return false;
    }

    _logger.trace("Message sent (address=%s, port=%d, size=%d) [%s]:\n%s", address.c_str(), port, size, _id.to_string().c_str(), buffer);
    return true;
}

//-------------------------------------------

bool SIP_Transport::socket_connect_callback(void *data, bool success)
{
    SIP_Transport *transport = reinterpret_cast<SIP_Transport *>(data);
    if (!transport)
    {
        _logger.warning("Invalid socket connect callback parameter (success=%d)", success);
        return false;
    }

    try
    {
        if (!transport->_connect_callback)
        {
            _logger.warning("Connect callback not configured (success=%d) [%s]", success, transport->_id.to_string().c_str());
            return false;
        }

        _logger.trace("Socket connected (success=%d) [%s]", success, transport->_id.to_string().c_str());
        return transport->_connect_callback(transport->_connect_callback_data, transport, success);

    }catch (std::exception &e)
    {
        _logger.warning("Exception in socket connect callback (success=%d, msg=%s) [%s]", success, e.what(),
                        transport->_id.to_string().c_str());
        return false;
    }catch (...)
    {
        _logger.warning("Exception in socket connect callback (success=%d) [%s]", success, transport->_id.to_string().c_str());
        return false;
    }
}

//-------------------------------------------

bool SIP_Transport::socket_accept_callback(void *data, Socket_TCP_Client *accepted, std::string address, unsigned short port)
{
    SIP_Transport *transport = reinterpret_cast<SIP_Transport *>(data);
    if ((!transport) || (!accepted))
    {
        _logger.warning("Invalid socket accept callback parameters (address=%s, port=%d)", address.c_str(), port);
        return false;
    }

    try
    {
        if (!transport->_accept_callback)
        {
            _logger.warning("Accept callback not configured (socket=%d, address=%s, port=%d) [%s]", accepted->get_socket(),
                            address.c_str(), port, transport->_id.to_string().c_str());
            return false;
        }

        SIP_Object_ID id;
        SIP_Transport_TCP_Client *accepted_transport = new SIP_Transport_TCP_Client(id);
        accepted_transport->_socket = accepted;
        accepted_transport->_address = transport->_address;
        accepted_transport->_port = transport->_port;
        accepted_transport->set_remote_address(address);
        accepted_transport->set_remote_port(port);

        accepted->set_connect_callback(socket_connect_callback, accepted_transport);
        accepted->set_accept_callback(socket_accept_callback, accepted_transport);
        accepted->set_receive_callback(socket_receive_callback, accepted_transport);

        accepted->set_so_snd_buf();
        accepted->set_so_rcv_buf();
        accepted->set_so_reuse_addr();

        if (!accepted->set_non_blocking())
        {
            _logger.warning("Failed in socket accept callback: set non-blocking failed (socket=%d, address=%s, port=%d) [%s]",
                            accepted->get_socket(), address.c_str(), port, transport->_id.to_string().c_str());
            delete accepted_transport;
            return false;
        }

        Socket_Control &control = Socket_Control::instance();
        if (!control.add_socket(*accepted))
        {
            _logger.warning("Failed in socket accept callback: add socket failed (socket=%d, address=%s, port=%d) [%s]",
                            accepted->get_socket(), address.c_str(), port, transport->_id.to_string().c_str());
            delete accepted_transport;
            return false;
        }

        _logger.trace("Socket accepted (socket=%d, address=%s, port=%d) [%s]", accepted->get_socket(), address.c_str(),
                      port, transport->_id.to_string().c_str());

        if (!transport->_accept_callback(transport->_accept_callback_data, transport, accepted_transport, address, port))
        {
            _logger.warning("Failed in socket accept callback: accept callback failed (socket=%d, address=%s, port=%d) [%s]",
                            accepted->get_socket(), address.c_str(), port, transport->_id.to_string().c_str());

            if (!control.remove_socket(*accepted))
            {
                _logger.warning("Failed in socket accept callback: remove socket failed (socket=%d, address=%s, port=%d) [%s]",
                                accepted->get_socket(), address.c_str(), port, transport->_id.to_string().c_str());
            }

            delete accepted_transport;
            return false;
        }

        return true;
    }catch (std::exception &e)
    {
        _logger.warning("Exception in socket accept callback (socket=%d, address=%s, port=%d, msg=%s) [%s]",
                        accepted->get_socket(), address.c_str(), port, e.what(), transport->_id.to_string().c_str());
        return false;
    }catch (...)
    {
        _logger.warning("Exception in socket accept callback (socket=%d, address=%s, port=%d) [%s]",
                        accepted->get_socket(), address.c_str(), port, transport->_id.to_string().c_str());
        return false;
    }
}

//-------------------------------------------

bool SIP_Transport::socket_receive_callback(void *data, const char *buffer, int size, std::string address, unsigned short port)
{
    SIP_Transport *transport = reinterpret_cast<SIP_Transport *>(data);
    if (!transport)
    {
        _logger.warning("Invalid socket receive callback parameter (address=%s, port=%d, size=%d)", address.c_str(), port, size);
        return false;
    }

    try
    {
        if (!transport->_receive_callback)
        {
            _logger.warning("Receive callback not configured (address=%s, port=%d, size=%d) [%s]", address.c_str(),
                            port, size, transport->_id.to_string().c_str());
            return false;
        }

        _logger.trace("Message received (address=%s, port=%d, size=%d) [%s]:\n%s", address.c_str(),
                      port, size, transport->_id.to_string().c_str(), buffer);
        return transport->_receive_callback(transport->_receive_callback_data, transport, buffer, size, address, port);

    }catch (std::exception &e)
    {
        _logger.warning("Exception in socket receive callback (address=%s, port=%d, size=%d, msg=%s) [%s]", address.c_str(),
                        port, size, e.what(), transport->_id.to_string().c_str());
        return false;
    }catch (...)
    {
        _logger.warning("Exception in socket receive callback (address=%s, port=%d, size=%d) [%s]", address.c_str(),
                        port, size, transport->_id.to_string().c_str());
        return false;
    }
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transport_UDP::init(std::string address, unsigned short port)
{
    if (_socket)
    {
        _logger.warning("Failed to init: UDP socket already initialized [%s]", _id.to_string().c_str());
        return false;
    }

    _socket = new Socket_UDP();
    return SIP_Transport::init(address, port);
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transport_TCP_Client::init(std::string address, unsigned short port)
{
    if (_socket)
    {
        _logger.warning("Failed to init: TCP client socket already initialized [%s]", _id.to_string().c_str());
        return false;
    }

    _socket = new Socket_TCP_Client();
    return SIP_Transport::init(address, port);
}

//-------------------------------------------

bool SIP_Transport_TCP_Client::connect(std::string address, unsigned short port)
{
    if (!_socket)
    {
        _logger.warning("Failed to connect: invalid socket [%s]", _id.to_string().c_str());
        return false;
    }

    _remote_address = address;
    _remote_port = port;

    if (!_socket->connect(address, port))
    {
        _logger.warning("Failed to connect: connect failed [%s]", _id.to_string().c_str());
        return false;
    }

    _logger.trace("Transport connected [%s]", _id.to_string().c_str());
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transport_TCP_Server::init(std::string address, unsigned short port)
{
    if (_socket)
    {
        _logger.warning("Failed to init: TCP server socket already initialized [%s]", _id.to_string().c_str());
        return false;
    }

    _socket = new Socket_TCP_Server();
    return SIP_Transport::init(address, port);
}

//-------------------------------------------

bool SIP_Transport_TCP_Server::listen(int backlog)
{
    if (!_socket)
    {
        _logger.warning("Failed to listen: invalid socket [%s]", _id.to_string().c_str());
        return false;
    }

    if (!_socket->listen(backlog))
    {
        _logger.warning("Failed to listen: listen failed [%s]", _id.to_string().c_str());
        return false;
    }

    _logger.trace("Transport listening [%s]", _id.to_string().c_str());
    return true;
}

//-------------------------------------------

bool SIP_Transport_TCP_Server::accept(socket_t &accept_socket, std::string &address, unsigned short &port)
{
    if (!_socket)
    {
        _logger.warning("Failed to accept: invalid socket [%s]", _id.to_string().c_str());
        return false;
    }

    if (!_socket->accept(accept_socket, address, port))
    {
        _logger.warning("Failed to accept: accept failed [%s]", _id.to_string().c_str());
        return false;
    }

    _logger.trace("Transport accepted [%s]", _id.to_string().c_str());
    return true;
}

//-------------------------------------------
