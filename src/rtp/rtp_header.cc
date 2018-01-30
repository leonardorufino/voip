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

#include "rtp_header.h"

Logger RTP_Header::_logger(Log_Manager::LOG_RTP_HEADER);

//-------------------------------------------

RTP_Header::RTP_Header() : _version_number(VERSION_2_0), _padding(0), _extensions(0), _csrc_count(0), _marker(0),
    _payload_type(PAYLOAD_MAX_DYNAMIC), _sequence_number(0), _timestamp(0), _ssrc_id(0)
{
}

//-------------------------------------------

bool RTP_Header::decode(const char *buffer, unsigned short size)
{
    if ((!buffer) || (size < MIN_RTP_HEADER_SIZE))
    {
        _logger.warning("Failed to decode: invalid parameters (size=%d)", size);
        return false;
    }

    _version_number = buffer[0] >> 6;
    _padding = buffer[0] >> 5;
    _extensions = buffer[0] >> 4;
    _csrc_count = buffer[0];

    unsigned short total = MIN_RTP_HEADER_SIZE + (_csrc_count * CSRC_SIZE);

    if (size < total)
    {
        _logger.warning("Failed to decode: size parameter too small (size=%d, expected=%d)", size, total);
        return false;
    }

    _marker = buffer[1] >> 7;
    _payload_type = buffer[1];

    _sequence_number = ntohs(*((unsigned short *) &buffer[2]));
    _timestamp  = ntohl(*((unsigned int *) &buffer[4]));
    _ssrc_id = ntohl(*((unsigned int *) &buffer[8]));

    _csrcs.reserve(_csrc_count);

    for (unsigned short i = 0; i < _csrc_count; i++)
    {
        unsigned int csrc = ntohl(*((unsigned int *) &buffer[12 + (i * 4)]));
        _csrcs.push_back(csrc);
    }

    return true;
}

//-------------------------------------------

bool RTP_Header::encode(char *buffer, unsigned short &size)
{
    unsigned short total = MIN_RTP_HEADER_SIZE + (_csrc_count * CSRC_SIZE);

    if ((!buffer) || (size < total))
    {
        _logger.warning("Failed to encode: invalid parameters (size=%d, expected=%d)", size, total);
        return false;
    }

    if (_csrc_count != _csrcs.size())
    {
        _logger.warning("Failed to encode: invalid CSRC size (count=%d, size=%d)", _csrc_count, _csrcs.size());
        return false;
    }

    buffer[0] = (_version_number << 6) | (_padding << 5) | (_extensions << 4) | _csrc_count;
    buffer[1] = (_marker << 7) | _payload_type;

    *((unsigned short *) &buffer[2]) = htons(_sequence_number);
    *((unsigned int *) &buffer[4]) = htonl(_timestamp);
    *((unsigned int *) &buffer[8]) = htonl(_ssrc_id);

    for (unsigned short i = 0; i < _csrcs.size(); i++)
        *((unsigned int *) &buffer[12 + (i * 4)]) = htonl(_csrcs[i]);

    size = total;
    return true;
}

//-------------------------------------------

void RTP_Header::set_random_sequence_number()
{
    _sequence_number = (unsigned short) (Util_Functions::random() & 0x07ff);
}

//-------------------------------------------

void RTP_Header::set_random_timestamp()
{
    _timestamp = (unsigned int) (Util_Functions::random() & 0x007fffff);
}

//-------------------------------------------

void RTP_Header::set_random_ssrc_id()
{
    _ssrc_id = (unsigned int) (Util_Functions::random() & 0x007fffff);
}

//-------------------------------------------

void RTP_Header::init_random(unsigned char payload_type)
{
    _version_number = VERSION_2_0;
    _padding = 0;
    _extensions = 0;
    _csrc_count = 0;

    _marker = 1;
    _payload_type = payload_type;

    set_random_sequence_number();
    set_random_timestamp();
    set_random_ssrc_id();

    _csrcs.clear();
}

//-------------------------------------------
