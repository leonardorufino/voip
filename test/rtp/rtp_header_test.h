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

#include "rtp/rtp_header.h"
#include <list>
#include <iomanip>

class RTP_Header_Test
{
public:
    static const unsigned short MAX_PACKET_SIZE = 1000;

public:
    RTP_Header_Test();
    virtual ~RTP_Header_Test() {}

    static bool init();
    template<class T> static bool run();

protected:
    bool run();

protected:
    class RTP_Header_Input_Output
    {
    public:
        unsigned short _id;
        unsigned char _payload_type;
        unsigned short _sequence_number;
        unsigned int _timestamp;
        unsigned int _ssrc_id;
        unsigned char _header[MAX_PACKET_SIZE];
        unsigned short _header_size;
    };

    std::list<RTP_Header_Input_Output> _header_input_output;
};

//-------------------------------------------
