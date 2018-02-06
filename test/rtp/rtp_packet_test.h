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

#include "rtp/rtp_packet.h"
#include <list>
#include <iomanip>

class RTP_Packet_Test
{
public:
    static const unsigned short MAX_PACKET_SIZE = 1000;

public:
    RTP_Packet_Test();
    virtual ~RTP_Packet_Test() {}

    static bool init();
    template<class T> static bool run();

protected:
    bool run();

protected:
    class RTP_Packet_Input_Output
    {
    public:
        unsigned short _id;
        unsigned short _payload_size;
        unsigned char _packet[MAX_PACKET_SIZE];
        unsigned short _packet_size;
    };

    std::list<RTP_Packet_Input_Output> _packet_input_output;
};

//-------------------------------------------
