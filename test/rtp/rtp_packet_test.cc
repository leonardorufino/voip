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

#include "rtp_packet_test.h"
#include <iostream>

//-------------------------------------------

RTP_Packet_Test::RTP_Packet_Test()
{
    unsigned short id = 1;

    RTP_Packet_Input_Output pkt1;
    pkt1._id = id++;
    pkt1._payload_size = 160;
    pkt1._packet_size = 12 + pkt1._payload_size;
    pkt1._packet[0] = 0x80;     pkt1._packet[1] = 0x80;     pkt1._packet[2] = 0x92;     pkt1._packet[3] = 0xdb;
    pkt1._packet[4] = 0x00;     pkt1._packet[5] = 0x00;     pkt1._packet[6] = 0x00;     pkt1._packet[7] = 0xa0;
    pkt1._packet[8] = 0x34;     pkt1._packet[9] = 0x3d;     pkt1._packet[10] = 0xa9;    pkt1._packet[11] = 0x9b;

    for (unsigned short i = 0; i < pkt1._payload_size; i++)
        pkt1._packet[12 + i] = 0xff;

    _packet_input_output.push_back(pkt1);


    RTP_Packet_Input_Output pkt2;
    pkt2._id = id++;
    pkt2._payload_size = 20;
    pkt2._packet_size = 12 + pkt2._payload_size;
    pkt2._packet[0] = 0x80;     pkt2._packet[1] = 0x12;     pkt2._packet[2] = 0xf2;     pkt2._packet[3] = 0xec;
    pkt2._packet[4] = 0x00;     pkt2._packet[5] = 0x00;     pkt2._packet[6] = 0xdf;     pkt2._packet[7] = 0xc0;
    pkt2._packet[8] = 0x04;     pkt2._packet[9] = 0x45;     pkt2._packet[10] = 0x59;    pkt2._packet[11] = 0xa1;

    for (unsigned short i = 0; i < pkt2._payload_size; i++)
        pkt2._packet[12 + i] = (unsigned char) i;

    _packet_input_output.push_back(pkt2);


    RTP_Packet_Input_Output pkt3;
    pkt3._id = id++;
    pkt3._payload_size = 33;
    pkt3._packet_size = 16 + pkt3._payload_size;
    pkt3._packet[0] = 0x81;     pkt3._packet[1] = 0x03;     pkt3._packet[2] = 0x7f;     pkt3._packet[3] = 0x86;
    pkt3._packet[4] = 0x00;     pkt3._packet[5] = 0x01;     pkt3._packet[6] = 0x09;     pkt3._packet[7] = 0xa0;
    pkt3._packet[8] = 0x04;     pkt3._packet[9] = 0x3d;     pkt3._packet[10] = 0xaa;    pkt3._packet[11] = 0xf1;
    pkt3._packet[12] = 0xaa;    pkt3._packet[13] = 0xbb;    pkt3._packet[14] = 0xcc;    pkt3._packet[15] = 0xdd;

    for (unsigned short i = 0; i < pkt3._payload_size; i++)
        pkt3._packet[16 + i] = (unsigned char) (0xff - i);

    _packet_input_output.push_back(pkt3);


    RTP_Packet_Input_Output pkt4;
    pkt4._id = id++;
    pkt4._payload_size = 900;
    pkt4._packet_size = 72 + pkt4._payload_size;
    pkt4._packet[0] = 0x8f;     pkt4._packet[1] = 0xff;     pkt4._packet[2] = 0xff;     pkt4._packet[3] = 0xff;
    pkt4._packet[4] = 0xff;     pkt4._packet[5] = 0xff;     pkt4._packet[6] = 0xff;     pkt4._packet[7] = 0xff;
    pkt4._packet[8] = 0xff;     pkt4._packet[9] = 0xff;     pkt4._packet[10] = 0xff;    pkt4._packet[11] = 0xff;
    pkt4._packet[12] = 0xff;    pkt4._packet[13] = 0xff;    pkt4._packet[14] = 0xff;    pkt4._packet[15] = 0xff;
    pkt4._packet[16] = 0xff;    pkt4._packet[17] = 0xff;    pkt4._packet[18] = 0xff;    pkt4._packet[19] = 0xff;
    pkt4._packet[20] = 0xff;    pkt4._packet[21] = 0xff;    pkt4._packet[22] = 0xff;    pkt4._packet[23] = 0xff;
    pkt4._packet[24] = 0xff;    pkt4._packet[25] = 0xff;    pkt4._packet[26] = 0xff;    pkt4._packet[27] = 0xff;
    pkt4._packet[28] = 0xff;    pkt4._packet[29] = 0xff;    pkt4._packet[30] = 0xff;    pkt4._packet[31] = 0xff;
    pkt4._packet[32] = 0xff;    pkt4._packet[33] = 0xff;    pkt4._packet[34] = 0xff;    pkt4._packet[35] = 0xff;
    pkt4._packet[36] = 0xff;    pkt4._packet[37] = 0xff;    pkt4._packet[38] = 0xff;    pkt4._packet[39] = 0xff;
    pkt4._packet[40] = 0xff;    pkt4._packet[41] = 0xff;    pkt4._packet[42] = 0xff;    pkt4._packet[43] = 0xff;
    pkt4._packet[44] = 0xff;    pkt4._packet[45] = 0xff;    pkt4._packet[46] = 0xff;    pkt4._packet[47] = 0xff;
    pkt4._packet[48] = 0xff;    pkt4._packet[49] = 0xff;    pkt4._packet[50] = 0xff;    pkt4._packet[51] = 0xff;
    pkt4._packet[52] = 0xff;    pkt4._packet[53] = 0xff;    pkt4._packet[54] = 0xff;    pkt4._packet[55] = 0xff;
    pkt4._packet[56] = 0xff;    pkt4._packet[57] = 0xff;    pkt4._packet[58] = 0xff;    pkt4._packet[59] = 0xff;
    pkt4._packet[60] = 0xff;    pkt4._packet[61] = 0xff;    pkt4._packet[62] = 0xff;    pkt4._packet[63] = 0xff;
    pkt4._packet[64] = 0xff;    pkt4._packet[65] = 0xff;    pkt4._packet[66] = 0xff;    pkt4._packet[67] = 0xff;
    pkt4._packet[68] = 0xff;    pkt4._packet[69] = 0xff;    pkt4._packet[70] = 0xff;    pkt4._packet[71] = 0xff;

    for (unsigned short i = 0; i < pkt4._payload_size; i++)
        pkt4._packet[72 + i] = (unsigned char) i;

    _packet_input_output.push_back(pkt4);
}

//-------------------------------------------

bool RTP_Packet_Test::init()
{
    if (!run<RTP_Packet_Test>())
        return false;

    return true;
}

//-------------------------------------------

template<class T> bool RTP_Packet_Test::run()
{
    T test;
    if (!test.run())
        return false;
    return true;
}

//-------------------------------------------

bool RTP_Packet_Test::run()
{
    std::list<RTP_Packet_Input_Output>::const_iterator it = _packet_input_output.begin();
    while (it != _packet_input_output.end())
    {
        RTP_Packet_Input_Output packet_input_output = *it++;

        std::cout << "RTP packet test initialized (id: " << packet_input_output._id << ")\n";

        RTP_Packet *packet = new RTP_Packet();
        if (!packet->decode((const char *) packet_input_output._packet, packet_input_output._packet_size))
        {
            std::cout << "RTP_Packet_Test::run -> Failed to decode packet:\n";
            std::cout << std::setw(12) << "ID: " << packet_input_output._id << "\n";
            return false;
        }

        RTP_Packet *copy = new RTP_Packet(*packet);
        if (!copy)
        {
            std::cout << "RTP_Packet_Test::run -> Failed to copy packet:\n";
            std::cout << std::setw(12) << "ID: " << packet_input_output._id << "\n";
            delete packet;
            return false;
        }

        delete packet;
        packet = NULL;

        if (copy->get_payload_size() != packet_input_output._payload_size)
        {
            std::cout << "RTP_Packet_Test::run -> Invalid payload size:\n";
            std::cout << std::setw(12) << "ID: " << packet_input_output._id << "\n";
            std::cout << std::setw(12) << "Expected: " << packet_input_output._payload_size << "\n";
            std::cout << std::setw(12) << "Size: " << copy->get_payload_size() << "\n";
            delete copy;
            return false;
        }

        char output[MAX_PACKET_SIZE] = {0};
        unsigned short size = sizeof(output);

        if (!copy->encode(output, size))
        {
            std::cout << "RTP_Packet_Test::run -> Failed to encode packet:\n";
            std::cout << std::setw(12) << "ID: " << packet_input_output._id << "\n";
            delete copy;
            return false;
        }

        if ((size != packet_input_output._packet_size) || (memcmp(output, packet_input_output._packet, size) != 0))
        {
            std::cout << "RTP_Packet_Test::run -> Invalid encoded packet:\n";
            std::cout << std::setw(12) << "ID: " << packet_input_output._id << "\n";
            std::cout << std::setw(15) << "Packet Size: " << packet_input_output._packet_size << "\n";
            std::cout << std::setw(15) << "Size: " << size << "\n";
            delete copy;
            return false;
        }

        delete copy;
        copy = NULL;

        std::cout << "RTP packet test completed successfully (id: " << packet_input_output._id << ")\n";
    }

    return true;
}

//-------------------------------------------
