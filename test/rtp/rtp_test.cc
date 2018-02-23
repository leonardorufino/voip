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

#include "rtp_header_test.h"
#include "rtp_packet_test.h"
#include "rtp_transport_test.h"
#include "rtp_session_test.h"
#include <iostream>

//-------------------------------------------

int main()
{
    std::cout << "RTP test initialized\n";

    if (!RTP_Header_Test::init())
    {
        std::cout << "RTP header test FAILED!\n";
        return 1;
    }

    if (!RTP_Packet_Test::init())
    {
        std::cout << "RTP packet test FAILED!\n";
        return 1;
    }

    if (!RTP_Transport_Test::init())
    {
        std::cout << "RTP transport test FAILED!\n";
        return 1;
    }

    if (!RTP_Session_Test::init())
    {
        std::cout << "RTP session test FAILED!\n";
        return 1;
    }

    std::cout << "RTP test completed successfully\n";
    return 0;
}

//-------------------------------------------
