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

#include "rtp_header.h"
#include "util/log_manager.h"
#include <cstring>

class RTP_Packet
{
public:
    RTP_Packet() : _payload(NULL), _payload_size(0) {}
    RTP_Packet(const RTP_Packet &packet);
    ~RTP_Packet();

    bool decode(const char *buffer, unsigned short size);
    bool encode(char *buffer, unsigned short &size);

    RTP_Header &get_header() { return _header; }

    void set_payload(const char *payload, unsigned short size);
    char *get_payload() { return _payload; }
    unsigned short get_payload_size() { return _payload_size; }

private:
    RTP_Header _header;
    char *_payload;
    unsigned short _payload_size;

    static Logger _logger;
};
