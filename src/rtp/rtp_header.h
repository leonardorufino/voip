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

#include "util/util_functions.h"
#include "util/log_manager.h"
#include <vector>

#ifdef WIN32
    #include <winsock2.h>
#else
    #include <arpa/inet.h>
#endif

class RTP_Header
{
public:
    static const unsigned short MIN_RTP_HEADER_SIZE = 12;
    static const unsigned char VERSION_2_0 = 2;
    static const unsigned short CSRC_SIZE = 4;

    enum Payload_Type
    {
        PAYLOAD_PCMU    = 0,    PAYLOAD_1016    = 1,    PAYLOAD_G721        = 2,     PAYLOAD_GSM         = 3,
        PAYLOAD_G723    = 4,    PAYLOAD_DVI4_8  = 5,    PAYLOAD_DVI4_16     = 6,     PAYLOAD_LPC         = 7,
        PAYLOAD_PCMA    = 8,    PAYLOAD_G722    = 9,    PAYLOAD_L16_STEREO  = 10,    PAYLOAD_L16_MONO    = 11,
        PAYLOAD_QCELP   = 12,   PAYLOAD_CN      = 13,   PAYLOAD_MPA         = 14,    PAYLOAD_G728        = 15,
        PAYLOAD_DVI4_11 = 16,   PAYLOAD_DVI4_22 = 17,   PAYLOAD_G729        = 18,    PAYLOAD_CELLB       = 25,
        PAYLOAD_JPEG    = 26,   PAYLOAD_NV      = 28,   PAYLOAD_H261        = 31,    PAYLOAD_MPV         = 32,
        PAYLOAD_MP2T    = 33,   PAYLOAD_H263    = 34,   PAYLOAD_MIN_DYNAMIC = 96,    PAYLOAD_MAX_DYNAMIC = 127
    };

public:
    RTP_Header();
    RTP_Header(const RTP_Header &header) { *this = header; }
    ~RTP_Header() {}

    bool decode(const char *buffer, unsigned short size);
    bool encode(char *buffer, unsigned short &size);

    void set_version_number(unsigned char version) { _version_number = version; }
    unsigned char get_version_number() { return _version_number; }

    void set_extensions(unsigned char extensions) { _extensions = extensions; }
    unsigned char get_extensions() { return _extensions; }

    void set_csrc_count(unsigned char count) { _csrc_count = count; }
    unsigned char get_csrc_count() { return _csrc_count; }

    void set_marker(unsigned char marker) { _marker = marker; }
    unsigned char get_marker() { return _marker; }

    void set_payload_type(unsigned char payload) { _payload_type = payload; }
    unsigned char get_payload_type() { return _payload_type; }

    void set_sequence_number(unsigned short sequence) { _sequence_number = sequence; }
    void increment_sequence_number() { _sequence_number++; }
    void set_random_sequence_number();
    unsigned short get_sequence_number() { return _sequence_number; }

    void set_timestamp(unsigned int timestamp) { _timestamp = timestamp; }
    void increment_timestamp(unsigned int value) { _timestamp += value; }
    void set_random_timestamp();
    unsigned int get_timestamp() { return _timestamp; }

    void set_ssrc_id(unsigned int id) { _ssrc_id = id; }
    void set_random_ssrc_id();
    unsigned int get_ssrc_id() { return _ssrc_id; }

    std::vector<unsigned int> &get_csrcs() { return _csrcs; }

    void init_random(unsigned char _payload_type);

private:
    unsigned char _version_number:2;
    unsigned char _padding:1;
    unsigned char _extensions:1;
    unsigned char _csrc_count:4;

    unsigned char _marker:1;
    unsigned char _payload_type:7;

    unsigned short _sequence_number;
    unsigned int _timestamp;
    unsigned int _ssrc_id;

    std::vector<unsigned int> _csrcs;

    static Logger _logger;
};
