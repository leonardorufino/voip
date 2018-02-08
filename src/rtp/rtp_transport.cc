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

#include "rtp_transport.h"

Logger RTP_Transport::_logger(Log_Manager::LOG_RTP_TRANSPORT);

//-------------------------------------------

RTP_Transport::RTP_Transport(RTP_Object_ID id) : _id(id), _port(INVALID_PORT), _socket(NULL), _receive_callback(NULL),
    _receive_callback_data(NULL)
{
}

//-------------------------------------------

RTP_Transport::~RTP_Transport()
{
    if (_socket)
        close();
}

//-------------------------------------------

void RTP_Transport::set_receive_callback(receive_callback *callback, void *data)
{
    _receive_callback = callback;
    _receive_callback_data = data;
}

//-------------------------------------------

bool RTP_Transport::init(std::string address, unsigned short port)
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

bool RTP_Transport::close()
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

bool RTP_Transport::send_message(const char *buffer, int size, std::string address, unsigned short port)
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

    _logger.trace("Message sent (address=%s, port=%d, size=%d) [%s]", address.c_str(), port, size, _id.to_string().c_str());
    return true;
}

//-------------------------------------------

bool RTP_Transport::receive_message(const char *buffer, int size, std::string address, unsigned short port)
{
    if ((!buffer) || (size <= 0))
    {
        _logger.trace("Empty message received (address=%s, port=%d, size=%d) [%s]", address.c_str(), port, size, _id.to_string().c_str());
        return true;
    }

    _logger.trace("Message received (address=%s, port=%d, size=%d) [%s]", address.c_str(), port, size, _id.to_string().c_str());

    RTP_Packet *packet = new RTP_Packet();
    if (!packet->decode(buffer, size))
    {
        _logger.warning("Failed to receive message: decode packet failed (address=%s, port=%d, size=%d) [%s]",
                        address.c_str(), port, size, _id.to_string().c_str());
        return false;
    }

    return _receive_callback(_receive_callback_data, this, packet, address, port);
}

//-------------------------------------------

bool RTP_Transport::socket_receive_callback(void *data, const char *buffer, int size, std::string address, unsigned short port)
{
    RTP_Transport *transport = reinterpret_cast<RTP_Transport *>(data);
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

        return transport->receive_message(buffer, size, address, port);

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

bool RTP_Transport_UDP::init(std::string address, unsigned short port)
{
    if (_socket)
    {
        _logger.warning("Failed to init: UDP socket already initialized [%s]", _id.to_string().c_str());
        return false;
    }

    _socket = new Socket_UDP();
    return RTP_Transport::init(address, port);
}

//-------------------------------------------
