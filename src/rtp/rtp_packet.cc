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

#include "rtp_packet.h"

Logger RTP_Packet::_logger(Log_Manager::LOG_RTP_PACKET);

//-------------------------------------------

RTP_Packet::RTP_Packet(const RTP_Packet &packet) : _header(packet._header), _payload(NULL)
{
    set_payload(packet._payload, packet._payload_size);
}

//-------------------------------------------

RTP_Packet::~RTP_Packet()
{
    if (_payload)
        delete _payload;
}

//-------------------------------------------

bool RTP_Packet::decode(const char *buffer, unsigned short size)
{
    if (!_header.decode(buffer, size))
        return false;

    unsigned short header_size = RTP_Header::MIN_RTP_HEADER_SIZE + (_header.get_csrc_count() * RTP_Header::CSRC_SIZE);
    unsigned short payload_size = size - header_size;

    if (payload_size == 0)
    {
        _logger.warning("Failed to decode: invalid payload size (size=%d, payload_size=%d)", size, payload_size);
        return false;
    }

    set_payload(&buffer[header_size], payload_size);
    return true;
}

//-------------------------------------------

bool RTP_Packet::encode(char *buffer, unsigned short &size)
{
    unsigned short header_size = size;

    if (!_header.encode(buffer, header_size))
        return false;

    unsigned short total = header_size + _payload_size;

    if (size < total)
    {
        _logger.warning("Failed to decode: size parameter too small (size=%d, expected=%d)", size, total);
        return false;
    }

    memcpy(&buffer[header_size], _payload, _payload_size);

    size = total;
    return true;
}

//-------------------------------------------

void RTP_Packet::set_payload(const char *payload, unsigned short size)
{
    if (_payload)
        delete _payload;

    if (size > 0)
    {
        _payload = new char[size];
        memcpy(_payload, payload, size);
        _payload_size = size;
    }else
    {
        _payload = NULL;
        _payload_size = 0;
    }
}

//-------------------------------------------
