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

#include "rtp_session.h"

Logger RTP_Session::_logger(Log_Manager::LOG_RTP_SESSION);

//-------------------------------------------

RTP_Session::~RTP_Session()
{
    remove_transport();
}

//-------------------------------------------

void RTP_Session::set_receive_packet_callback(receive_packet_callback *callback, void *data)
{
    _receive_packet_callback = callback;
    _receive_packet_callback_data = data;
}

//-------------------------------------------

bool RTP_Session::init(std::string local_address, unsigned short local_port, std::string remote_address, unsigned short remote_port,
                       RTP_Transport_Type transport)
{
    if ((local_address.empty()) || (local_port == INVALID_PORT) || (remote_address.empty()) || (remote_port == INVALID_PORT) ||
        (transport != RTP_TRANSPORT_UDP))
    {
        _logger.warning("Failed to init: invalid parameters [%s]", _id.to_string().c_str());
        return false;
    }

    _local_address = local_address;
    _local_port = local_port;

    _remote_address = remote_address;
    _remote_port = remote_port;

    RTP_Object_ID transport_id = _id;
    transport_id._transport = 0;

    RTP_Transport_UDP *udp = new RTP_Transport_UDP(transport_id);
    add_transport(udp);

    if (!udp->init(_local_address, _local_port))
    {
        _logger.warning("Failed to init: UDP transport init failed [%s]", _id.to_string().c_str());
        remove_transport();
        return false;
    }

    _logger.trace("RTP session initialized [%s]", _id.to_string().c_str());
    return true;
}

//-------------------------------------------

bool RTP_Session::close()
{
    remove_transport();

    _logger.trace("RTP session closed [%s]", _id.to_string().c_str());
    return true;
}

//-------------------------------------------

void RTP_Session::add_transport(RTP_Transport *transport)
{
    if (!transport)
        return;

    if (_transport)
        delete _transport;

    transport->set_receive_callback(transport_receive_callback, this);
    _transport = transport;
}

//-------------------------------------------

void RTP_Session::remove_transport()
{
    if (_transport)
    {
        _transport->close();
        delete _transport;
        _transport = NULL;
    }
}

//-------------------------------------------

bool RTP_Session::send_packet(RTP_Packet *packet)
{
    if (!packet)
    {
        _logger.warning("Failed to send packet: invalid parameter [%s]", _id.to_string().c_str());
        return false;
    }

    if (!_transport)
    {
        _logger.warning("Failed to send packet: invalid transport [%s]", _id.to_string().c_str());
        return false;
    }

    if ((_remote_address.empty()) || (_remote_port == INVALID_PORT))
    {
        _logger.warning("Failed to send packet: invalid remote address (address=%s, port=%d) [%s]",
                        _remote_address.c_str(), _remote_port, _id.to_string().c_str());
        return false;
    }

    unsigned short size = SEND_BUFFER_SIZE;
    if (!packet->encode(_send_buffer, size))
    {
        _logger.warning("Failed to send packet: encode packet failed (address=%s, port=%d, size=%d) [%s]",
                        _remote_address.c_str(), _remote_port, size, _id.to_string().c_str());
        return false;
    }

    _logger.trace("Sending packet (address=%s, port=%d, size=%d) [%s]", _remote_address.c_str(), _remote_port,
                  size, _id.to_string().c_str());

    return _transport->send_message(_send_buffer, (int) size, _remote_address, _remote_port);
}

//-------------------------------------------

bool RTP_Session::receive_packet(RTP_Packet *packet)
{
    try
    {
        if (!_receive_packet_callback)
        {
            _logger.warning("Receive packet callback not configured [%s]", _id.to_string().c_str());
            return false;
        }

        _logger.trace("Calling receive packet callback [%s]", _id.to_string().c_str());
        return _receive_packet_callback(_receive_packet_callback_data, this, packet);

    }catch (std::exception &e)
    {
        _logger.warning("Exception in receive packet (msg=%s) [%s]", e.what(), _id.to_string().c_str());
        return false;
    }catch (...)
    {
        _logger.warning("Exception in receive packet [%s]", _id.to_string().c_str());
        return false;
    }
}

//-------------------------------------------

bool RTP_Session::transport_receive_callback(void *data, RTP_Transport *transport, RTP_Packet *packet, std::string address,
                                             unsigned short port)
{
    RTP_Session *session = reinterpret_cast<RTP_Session *>(data);
    if ((!session) || (!transport) || (!packet))
    {
        _logger.warning("Invalid transport receive callback parameters");
        return false;
    }

    _logger.trace("Packet received [%s]", session->_id.to_string().c_str());

    if (!session->receive_packet(packet))
    {
        _logger.warning("Failed in transport receive callback: receive packet failed [%s]", session->_id.to_string().c_str());
        return false;
    }

    return true;
}

//-------------------------------------------
