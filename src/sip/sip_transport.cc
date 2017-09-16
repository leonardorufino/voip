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

SIP_Transport::SIP_Transport() : _port(INVALID_PORT), _socket(NULL), _connect_callback(NULL), _connect_callback_data(NULL),
    _accept_callback(NULL), _accept_callback_data(NULL), _receive_callback(NULL), _receive_callback_data(NULL)
{
}

//-------------------------------------------

SIP_Transport::~SIP_Transport()
{
    if (_socket)
        close();
}

//-------------------------------------------

bool SIP_Transport::start()
{
    Socket_Control &control = Socket_Control::instance();
    if (!control.start())
    {
        _logger.warning("Failed to start socket control");
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Transport::stop()
{
    Socket_Control &control = Socket_Control::instance();
    if (!control.stop())
    {
        _logger.warning("Failed to stop socket control");
        return false;
    }

    return true;
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
        _logger.warning("Failed to init socket: invalid socket");
        return false;
    }

    if ((address.empty()) || (port == INVALID_PORT))
    {
        _logger.warning("Failed to init socket: invalid parameters (address=%s, port=%d)", address.c_str(), port);
        return false;
    }

    _address = address;
    _port = port;

    Socket::Address_Family family = Socket::address_to_address_family(_address);
    if (family == Socket::ADDRESS_FAMILY_INVALID)
    {
        _logger.warning("Failed to get address family");
        return false;
    }

    _socket->set_connect_callback(socket_connect_callback, this);
    _socket->set_accept_callback(socket_accept_callback, this);
    _socket->set_receive_callback(socket_receive_callback, this);

    if (!_socket->create(family))
    {
        _logger.warning("Failed to create UDP socket");
        return false;
    }

    _socket->set_so_snd_buf();
    _socket->set_so_rcv_buf();
    _socket->set_so_reuse_addr();

    if (!_socket->bind(_address, _port))
    {
        _logger.warning("Failed to bind socket (address=%s, port=%d)", _address.c_str(), _port);
        return false;
    }

    if (!_socket->set_non_blocking())
    {
        _logger.warning("Failed to set socket non-blocking");
        return false;
    }

    if (!control.add_socket(*_socket))
    {
        _logger.warning("Failed to add socket to control");
        return false;
    }

    _logger.trace("Transport initialized (address=%s, port=%d)", address.c_str(), port);
    return true;
}

//-------------------------------------------

bool SIP_Transport::close()
{
    Socket_Control &control = Socket_Control::instance();
    bool ret = true;

    if (!_socket)
    {
        _logger.warning("Failed to close socket: invalid socket");
        return false;
    }

    if (!control.remove_socket(*_socket))
    {
        _logger.warning("Failed to remove UDP socket from control");
        ret = false;
    }

    if (!_socket->close())
    {
        _logger.warning("Failed to close UDP socket");
        ret = false;
    }

    delete _socket;
    _socket = NULL;

    return ret;
}

//-------------------------------------------

bool SIP_Transport::send_message(const char *buffer, int size, std::string address, unsigned short port)
{
    if (!_socket)
    {
        _logger.warning("Failed to send message: invalid socket");
        return false;
    }

    bool ret;
    if (_socket->get_socket_type() == Socket::SOCKET_UDP)
        ret = _socket->send(buffer, size, address, port);
    else
        ret = _socket->send(buffer, size);

    if (!ret)
    {
        _logger.warning("Failed to send message (address=%s, port=%d)", address.c_str(), port);
        return false;
    }

    _logger.trace("Message sent (address=%s, port=%d, size=%d):\n%s", address.c_str(), port, size, buffer);
    return true;
}

//-------------------------------------------

bool SIP_Transport::socket_connect_callback(void *data, bool success)
{
    try
    {
        SIP_Transport *transport = reinterpret_cast<SIP_Transport *>(data);
        if (!transport)
        {
            _logger.warning("Socket connect callback invalid parameter (success=%d)", success);
            return false;
        }

        if (transport->_connect_callback)
        {
            _logger.trace("Socket connected (success=%d)", success);
            return transport->_connect_callback(transport->_connect_callback_data, transport, success);
        }

        _logger.trace("Connect callback not configured (success=%d)", success);
        return false;
    }catch (std::exception &e)
    {
        _logger.warning("Exception in socket receive callback (success=%d, msg=%s)", success, e.what());
        return false;
    }catch (...)
    {
        _logger.warning("Exception in socket receive callback (success=%d)", success);
        return false;
    }
}

//-------------------------------------------

bool SIP_Transport::socket_accept_callback(void *data, Socket_TCP_Client *accepted, std::string address, unsigned short port)
{
    try
    {
        SIP_Transport *transport = reinterpret_cast<SIP_Transport *>(data);
        if ((!transport) || (!accepted))
        {
            _logger.warning("Socket accept callback invalid parameter (address=%s, port=%d)", address.c_str(), port);
            return false;
        }

        if (transport->_accept_callback)
        {
            SIP_Transport_TCP_Client *accepted_transport = new SIP_Transport_TCP_Client();
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
                _logger.warning("Failed to set accepted socket non-blocking (socket=%d, address=%s, port=%d)", accepted->get_socket(),
                                address.c_str(), port);
                delete accepted_transport;
                return false;
            }

            Socket_Control &control = Socket_Control::instance();
            if (!control.add_socket(*accepted))
            {
                _logger.warning("Failed to add accepted socket to control (socket=%d, address=%s, port=%d)", accepted->get_socket(),
                                address.c_str(), port);
                delete accepted_transport;
                return false;
            }

            _logger.trace("TCP transport accepted (socket=%d, address=%s, port=%d)", accepted->get_socket(), address.c_str(), port);

            if (!transport->_accept_callback(transport->_accept_callback_data, transport, accepted_transport, address, port))
            {
                _logger.warning("Accept callback returned false (socket=%d, address=%s, port=%d)", accepted->get_socket(),
                                address.c_str(), port);

                if (!control.remove_socket(*accepted))
                {
                    _logger.warning("Failed to remove accepted socket from control (socket=%d, address=%s, port=%d)",
                                    accepted->get_socket(), address.c_str(), port);
                }

                delete accepted_transport;
                return false;
            }

            return true;
        }

        _logger.trace("Accept callback not configured (socket=%d, address=%s, port=%d)", accepted->get_socket(), address.c_str(), port);
        return false;
    }catch (std::exception &e)
    {
        _logger.warning("Exception in socket accept callback (socket=%d, address=%s, port=%d, msg=%s)",
                        accepted->get_socket(), address.c_str(), port, e.what());
        return false;
    }catch (...)
    {
        _logger.warning("Exception in socket accept callback (socket=%d, address=%s, port=%d)",
                        accepted->get_socket(), address.c_str(), port);
        return false;
    }
}

//-------------------------------------------

bool SIP_Transport::socket_receive_callback(void *data, const char *buffer, int size, std::string address, unsigned short port)
{
    try
    {
        SIP_Transport *transport = reinterpret_cast<SIP_Transport *>(data);
        if (!transport)
        {
            _logger.warning("Socket receive callback invalid parameter (address=%s, port=%d, size=%d)", address.c_str(), port, size);
            return false;
        }

        if (transport->_receive_callback)
        {
            _logger.trace("Message received (address=%s, port=%d, size=%d):\n%s", address.c_str(), port, size, buffer);
            return transport->_receive_callback(transport->_receive_callback_data, transport, buffer, size, address, port);
        }

        _logger.trace("Receive callback not configured (address=%s, port=%d, size=%d)", address.c_str(), port, size);
        return false;
    }catch (std::exception &e)
    {
        _logger.warning("Exception in socket receive callback (address=%s, port=%d, size=%d, msg=%s)",
                        address.c_str(), port, size, e.what());
        return false;
    }catch (...)
    {
        _logger.warning("Exception in socket receive callback (address=%s, port=%d, size=%d)", address.c_str(), port, size);
        return false;
    }
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transport_UDP::init(std::string address, unsigned short port)
{
    if (_socket)
    {
        _logger.warning("Failed to init UDP socket: already created");
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
        _logger.warning("Failed to init TCP client socket: already created");
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
        _logger.warning("Failed to connect TCP client socket: invalid socket");
        return false;
    }

    _remote_address = address;
    _remote_port = port;

    return _socket->connect(address, port);
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transport_TCP_Server::init(std::string address, unsigned short port)
{
    if (_socket)
    {
        _logger.warning("Failed to init TCP server socket: already created");
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
        _logger.warning("Failed to listen TCP server socket: invalid socket");
        return false;
    }

    return _socket->listen(backlog);
}

//-------------------------------------------

bool SIP_Transport_TCP_Server::accept(socket_t &accept_socket, std::string &address, unsigned short &port)
{
    if (!_socket)
    {
        _logger.warning("Failed to accept TCP server socket: invalid socket");
        return false;
    }

    return _socket->accept(accept_socket, address, port);
}

//-------------------------------------------
