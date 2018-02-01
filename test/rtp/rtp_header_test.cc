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
#include <iostream>

//-------------------------------------------

RTP_Header_Test::RTP_Header_Test()
{
    unsigned short id = 1;

    RTP_Header_Input_Output hdr1;
    hdr1._id = id++;
    hdr1._payload_type = 0;
    hdr1._sequence_number = 37595;
    hdr1._timestamp = 160;
    hdr1._ssrc_id = 876456347;
    hdr1._header_size = 12;
    hdr1._header[0] = 0x80;     hdr1._header[1] = 0x80;     hdr1._header[2] = 0x92;     hdr1._header[3] = 0xdb;
    hdr1._header[4] = 0x00;     hdr1._header[5] = 0x00;     hdr1._header[6] = 0x00;     hdr1._header[7] = 0xa0;
    hdr1._header[8] = 0x34;     hdr1._header[9] = 0x3d;     hdr1._header[10] = 0xa9;    hdr1._header[11] = 0x9b;
    _header_input_output.push_back(hdr1);

    RTP_Header_Input_Output hdr2;
    hdr2._id = id++;
    hdr2._payload_type = 8;
    hdr2._sequence_number = 19705;
    hdr2._timestamp = 64480;
    hdr2._ssrc_id = 876608052;
    hdr2._header_size = 12;
    hdr2._header[0] = 0x80;     hdr2._header[1] = 0x08;     hdr2._header[2] = 0x4c;     hdr2._header[3] = 0xf9;
    hdr2._header[4] = 0x00;     hdr2._header[5] = 0x00;     hdr2._header[6] = 0xfb;     hdr2._header[7] = 0xe0;
    hdr2._header[8] = 0x34;     hdr2._header[9] = 0x3f;     hdr2._header[10] = 0xfa;    hdr2._header[11] = 0x34;
    _header_input_output.push_back(hdr2);

    RTP_Header_Input_Output hdr3;
    hdr3._id = id++;
    hdr3._payload_type = 18;
    hdr3._sequence_number = 62188;
    hdr3._timestamp = 57280;
    hdr3._ssrc_id = 71653793;
    hdr3._header_size = 12;
    hdr3._header[0] = 0x80;     hdr3._header[1] = 0x12;     hdr3._header[2] = 0xf2;     hdr3._header[3] = 0xec;
    hdr3._header[4] = 0x00;     hdr3._header[5] = 0x00;     hdr3._header[6] = 0xdf;     hdr3._header[7] = 0xc0;
    hdr3._header[8] = 0x04;     hdr3._header[9] = 0x45;     hdr3._header[10] = 0x59;    hdr3._header[11] = 0xa1;
    _header_input_output.push_back(hdr3);

    RTP_Header_Input_Output hdr4;
    hdr4._id = id++;
    hdr4._payload_type = 99;
    hdr4._sequence_number = 23845;
    hdr4._timestamp = 960;
    hdr4._ssrc_id = 71233028;
    hdr4._header_size = 12;
    hdr4._header[0] = 0x80;     hdr4._header[1] = 0xe3;     hdr4._header[2] = 0x5d;     hdr4._header[3] = 0x25;
    hdr4._header[4] = 0x00;     hdr4._header[5] = 0x00;     hdr4._header[6] = 0x03;     hdr4._header[7] = 0xc0;
    hdr4._header[8] = 0x04;     hdr4._header[9] = 0x3e;     hdr4._header[10] = 0xee;    hdr4._header[11] = 0x04;
    _header_input_output.push_back(hdr4);

    RTP_Header_Input_Output hdr5;
    hdr5._id = id++;
    hdr5._payload_type = 3;
    hdr5._sequence_number = 32646;
    hdr5._timestamp = 68000;
    hdr5._ssrc_id = 71150321;
    hdr5._header_size = 12;
    hdr5._header[0] = 0x80;     hdr5._header[1] = 0x03;     hdr5._header[2] = 0x7f;     hdr5._header[3] = 0x86;
    hdr5._header[4] = 0x00;     hdr5._header[5] = 0x01;     hdr5._header[6] = 0x09;     hdr5._header[7] = 0xa0;
    hdr5._header[8] = 0x04;     hdr5._header[9] = 0x3d;     hdr5._header[10] = 0xaa;    hdr5._header[11] = 0xf1;
    _header_input_output.push_back(hdr5);

    RTP_Header_Input_Output hdr6;
    hdr6._id = id++;
    hdr6._payload_type = 9;
    hdr6._sequence_number = 36204;
    hdr6._timestamp = 4160;
    hdr6._ssrc_id = 71150266;
    hdr6._header_size = 12;
    hdr6._header[0] = 0x80;     hdr6._header[1] = 0x09;     hdr6._header[2] = 0x8d;     hdr6._header[3] = 0x6c;
    hdr6._header[4] = 0x00;     hdr6._header[5] = 0x00;     hdr6._header[6] = 0x10;     hdr6._header[7] = 0x40;
    hdr6._header[8] = 0x04;     hdr6._header[9] = 0x3d;     hdr6._header[10] = 0xaa;    hdr6._header[11] = 0xba;
    _header_input_output.push_back(hdr6);

    RTP_Header_Input_Output hdr7;
    hdr7._id = id++;
    hdr7._payload_type = 96;
    hdr7._sequence_number = 18074;
    hdr7._timestamp = 270080;
    hdr7._ssrc_id = 71233079;
    hdr7._header_size = 16;
    hdr7._header[0] = 0x81;     hdr7._header[1] = 0x60;     hdr7._header[2] = 0x46;     hdr7._header[3] = 0x9a;
    hdr7._header[4] = 0x00;     hdr7._header[5] = 0x04;     hdr7._header[6] = 0x1f;     hdr7._header[7] = 0x00;
    hdr7._header[8] = 0x04;     hdr7._header[9] = 0x3e;     hdr7._header[10] = 0xee;    hdr7._header[11] = 0x37;
    hdr7._header[12] = 0xaa;    hdr7._header[13] = 0xbb;    hdr7._header[14] = 0xcc;    hdr7._header[15] = 0xdd;
    _header_input_output.push_back(hdr7);

    RTP_Header_Input_Output hdr8;
    hdr8._id = id++;
    hdr8._payload_type = 127;
    hdr8._sequence_number = 65535;
    hdr8._timestamp = 4294967295;
    hdr8._ssrc_id = 4294967295;
    hdr8._header_size = 72;
    hdr8._header[0] = 0x8f;     hdr8._header[1] = 0xff;     hdr8._header[2] = 0xff;     hdr8._header[3] = 0xff;
    hdr8._header[4] = 0xff;     hdr8._header[5] = 0xff;     hdr8._header[6] = 0xff;     hdr8._header[7] = 0xff;
    hdr8._header[8] = 0xff;     hdr8._header[9] = 0xff;     hdr8._header[10] = 0xff;    hdr8._header[11] = 0xff;
    hdr8._header[12] = 0xff;    hdr8._header[13] = 0xff;    hdr8._header[14] = 0xff;    hdr8._header[15] = 0xff;
    hdr8._header[16] = 0xff;    hdr8._header[17] = 0xff;    hdr8._header[18] = 0xff;    hdr8._header[19] = 0xff;
    hdr8._header[20] = 0xff;    hdr8._header[21] = 0xff;    hdr8._header[22] = 0xff;    hdr8._header[23] = 0xff;
    hdr8._header[24] = 0xff;    hdr8._header[25] = 0xff;    hdr8._header[26] = 0xff;    hdr8._header[27] = 0xff;
    hdr8._header[28] = 0xff;    hdr8._header[29] = 0xff;    hdr8._header[30] = 0xff;    hdr8._header[31] = 0xff;
    hdr8._header[32] = 0xff;    hdr8._header[33] = 0xff;    hdr8._header[34] = 0xff;    hdr8._header[35] = 0xff;
    hdr8._header[36] = 0xff;    hdr8._header[37] = 0xff;    hdr8._header[38] = 0xff;    hdr8._header[39] = 0xff;
    hdr8._header[40] = 0xff;    hdr8._header[41] = 0xff;    hdr8._header[42] = 0xff;    hdr8._header[43] = 0xff;
    hdr8._header[44] = 0xff;    hdr8._header[45] = 0xff;    hdr8._header[46] = 0xff;    hdr8._header[47] = 0xff;
    hdr8._header[48] = 0xff;    hdr8._header[49] = 0xff;    hdr8._header[50] = 0xff;    hdr8._header[51] = 0xff;
    hdr8._header[52] = 0xff;    hdr8._header[53] = 0xff;    hdr8._header[54] = 0xff;    hdr8._header[55] = 0xff;
    hdr8._header[56] = 0xff;    hdr8._header[57] = 0xff;    hdr8._header[58] = 0xff;    hdr8._header[59] = 0xff;
    hdr8._header[60] = 0xff;    hdr8._header[61] = 0xff;    hdr8._header[62] = 0xff;    hdr8._header[63] = 0xff;
    hdr8._header[64] = 0xff;    hdr8._header[65] = 0xff;    hdr8._header[66] = 0xff;    hdr8._header[67] = 0xff;
    hdr8._header[68] = 0xff;    hdr8._header[69] = 0xff;    hdr8._header[70] = 0xff;    hdr8._header[71] = 0xff;
    _header_input_output.push_back(hdr8);

    RTP_Header_Input_Output hdr9;
    hdr9._id = id++;
    hdr9._payload_type = 0;
    hdr9._sequence_number = 0;
    hdr9._timestamp = 0;
    hdr9._ssrc_id = 0;
    hdr9._header_size = 40;
    hdr9._header[0] = 0xe7;     hdr9._header[1] = 0x00;     hdr9._header[2] = 0x00;     hdr9._header[3] = 0x00;
    hdr9._header[4] = 0x00;     hdr9._header[5] = 0x00;     hdr9._header[6] = 0x00;     hdr9._header[7] = 0x00;
    hdr9._header[8] = 0x00;     hdr9._header[9] = 0x00;     hdr9._header[10] = 0x00;    hdr9._header[11] = 0x00;
    hdr9._header[12] = 0x00;    hdr9._header[13] = 0x00;    hdr9._header[14] = 0x00;    hdr9._header[15] = 0x00;
    hdr9._header[16] = 0x00;    hdr9._header[17] = 0x00;    hdr9._header[18] = 0x00;    hdr9._header[19] = 0x00;
    hdr9._header[20] = 0x11;    hdr9._header[21] = 0x22;    hdr9._header[22] = 0x33;    hdr9._header[23] = 0x44;
    hdr9._header[24] = 0x44;    hdr9._header[25] = 0x55;    hdr9._header[26] = 0x66;    hdr9._header[27] = 0x77;
    hdr9._header[28] = 0x88;    hdr9._header[29] = 0x99;    hdr9._header[30] = 0xaa;    hdr9._header[31] = 0xbb;
    hdr9._header[32] = 0xcc;    hdr9._header[33] = 0xdd;    hdr9._header[34] = 0xee;    hdr9._header[35] = 0xff;
    hdr9._header[36] = 0x00;    hdr9._header[37] = 0x00;    hdr9._header[38] = 0x00;    hdr9._header[39] = 0x00;
    _header_input_output.push_back(hdr9);
}

//-------------------------------------------

bool RTP_Header_Test::init()
{
    if (!run<RTP_Header_Test>())
        return false;

    return true;
}

//-------------------------------------------

template<class T> bool RTP_Header_Test::run()
{
    T test;
    if (!test.run())
        return false;
    return true;
}

//-------------------------------------------

bool RTP_Header_Test::run()
{
    std::list<RTP_Header_Input_Output>::const_iterator it = _header_input_output.begin();
    while (it != _header_input_output.end())
    {
        RTP_Header_Input_Output header_input_output = *it++;

        std::cout << "RTP header test initialized (id: " << header_input_output._id << ")\n";

        RTP_Header *header = new RTP_Header();
        if (!header->decode((const char *) header_input_output._header, header_input_output._header_size))
        {
            std::cout << "RTP_Header_Test::run -> Failed to decode header:\n";
            std::cout << std::setw(12) << "ID: " << header_input_output._id << "\n";
            return false;
        }

        RTP_Header *copy = new RTP_Header(*header);
        if (!copy)
        {
            std::cout << "RTP_Header_Test::run -> Failed to copy header:\n";
            std::cout << std::setw(12) << "ID: " << header_input_output._id << "\n";
            delete header;
            return false;
        }

        delete header;
        header = NULL;

        if (copy->get_payload_type() != header_input_output._payload_type)
        {
            std::cout << "RTP_Header_Test::run -> Invalid payload type:\n";
            std::cout << std::setw(12) << "ID: " << header_input_output._id << "\n";
            std::cout << std::setw(12) << "Expected: " << (unsigned short) header_input_output._payload_type << "\n";
            std::cout << std::setw(12) << "Payload: " << (unsigned short) copy->get_payload_type() << "\n";
            delete copy;
            return false;
        }

        if (copy->get_sequence_number() != header_input_output._sequence_number)
        {
            std::cout << "RTP_Header_Test::run -> Invalid sequence number:\n";
            std::cout << std::setw(12) << "ID: " << header_input_output._id << "\n";
            std::cout << std::setw(12) << "Expected: " << header_input_output._sequence_number << "\n";
            std::cout << std::setw(12) << "Sequence: " << copy->get_sequence_number() << "\n";
            delete copy;
            return false;
        }

        if (copy->get_timestamp() != header_input_output._timestamp)
        {
            std::cout << "RTP_Header_Test::run -> Invalid timestamp:\n";
            std::cout << std::setw(12) << "ID: " << header_input_output._id << "\n";
            std::cout << std::setw(12) << "Expected: " << header_input_output._timestamp << "\n";
            std::cout << std::setw(12) << "Timestamp: " << copy->get_timestamp() << "\n";
            delete copy;
            return false;
        }

        if (copy->get_ssrc_id() != header_input_output._ssrc_id)
        {
            std::cout << "RTP_Header_Test::run -> Invalid SSRC ID:\n";
            std::cout << std::setw(12) << "ID: " << header_input_output._id << "\n";
            std::cout << std::setw(12) << "Expected: " << header_input_output._ssrc_id << "\n";
            std::cout << std::setw(12) << "SSRC: " << copy->get_ssrc_id() << "\n";
            delete copy;
            return false;
        }

        char output[MAX_PACKET_SIZE] = {0};
        unsigned short size = sizeof(output);

        if (!copy->encode(output, size))
        {
            std::cout << "RTP_Header_Test::run -> Failed to encode header:\n";
            std::cout << std::setw(12) << "ID: " << header_input_output._id << "\n";
            delete copy;
            return false;
        }

        if ((size != header_input_output._header_size) || (memcmp(output, header_input_output._header, size) != 0))
        {
            std::cout << "RTP_Header_Test::run -> Invalid encoded header:\n";
            std::cout << std::setw(15) << "ID: " << header_input_output._id << "\n";
            std::cout << std::setw(15) << "Header Size: " << header_input_output._header_size << "\n";
            std::cout << std::setw(15) << "Size: " << size << "\n";
            delete copy;
            return false;
        }

        delete copy;
        copy = NULL;

        std::cout << "RTP header test completed successfully (id: " << header_input_output._id << ")\n";
    }

    return true;
}

//-------------------------------------------
