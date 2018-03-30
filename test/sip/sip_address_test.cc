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

#include "sip_address_test.h"

//-------------------------------------------

bool SIP_Address_Test::init()
{
    std::cout << "SIP address test initialized\n";

    if (!run<SIP_Address_Decode_Encode_Test>())
        return false;

    std::cout << "SIP address test completed successfully\n";
    return true;
}

//-------------------------------------------

template<class T> bool SIP_Address_Test::run()
{
    T test;
    if (!test.run())
        return false;
    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Address_Decode_Encode_Test::SIP_Address_Decode_Encode_Test()
{
    SIP_Address_Input_Output hdr1;
    hdr1._input          = "<sip:Marconi@radio.org>";
    hdr1._output         = "<sip:Marconi@radio.org>";
    _address_input_output.push_back(hdr1);

    SIP_Address_Input_Output hdr2;
    hdr2._input          = "sip:+12125551212@server.phone2net.com";
    hdr2._output         = "sip:+12125551212@server.phone2net.com";
    _address_input_output.push_back(hdr2);

    SIP_Address_Input_Output hdr3;
    hdr3._input          = "\" Name  \" <sip:+12125551212@server.phone2net.com ;par1 ;par2>";
    hdr3._output         = "\"Name\" <sip:+12125551212@server.phone2net.com;par1;par2>";
    _address_input_output.push_back(hdr3);

    SIP_Address_Input_Output hdr4;
    hdr4._input          = "<sip:server.phone2net.com ;par1 ; lr ; maddr= 10.10.10.10 ;ttl=20; method= BYE; user=ip;transport= udp ;par2>";
    hdr4._output         = "<sip:server.phone2net.com;transport=udp;user=ip;method=BYE;ttl=20;maddr=10.10.10.10;lr;par1;par2>";
    _address_input_output.push_back(hdr4);

    SIP_Address_Input_Output hdr5;
    hdr5._input          = "The Operator <sip:operator@cs.columbia.edu>";
    hdr5._output         = "The Operator <sip:operator@cs.columbia.edu>";
    _address_input_output.push_back(hdr5);

    SIP_Address_Input_Output hdr6;
    hdr6._input          = "\"  \" <sip:operator:123456@cs.columbia.edu ; par1>";
    hdr6._output         = "<sip:operator:123456@cs.columbia.edu;par1>";
    _address_input_output.push_back(hdr6);

    SIP_Address_Input_Output hdr7;
    hdr7._input          = "G. Marconi <sip:Marconi@[1111:2222:3333:4444:5555:6666:7777:8888];maddr=[fe80::10fe:234f]>";
    hdr7._output         = "G. Marconi <sip:Marconi@[1111:2222:3333:4444:5555:6666:7777:8888];maddr=[fe80::10fe:234f]>";
    _address_input_output.push_back(hdr7);

    SIP_Address_Input_Output hdr8;
    hdr8._input          = "sip:[2001:0db8:85a3:08d3:1319:8a2e:0370:7344]:5060;par1>";
    hdr8._output         = "sip:[2001:0db8:85a3:08d3:1319:8a2e:0370:7344]:5060;par1>";
    _address_input_output.push_back(hdr8);

    SIP_Address_Input_Output hdr9;
    hdr9._input          = "tel:+33225566;par1";
    hdr9._output         = "tel:+33225566;par1";
    _address_input_output.push_back(hdr9);
}

//-------------------------------------------

bool SIP_Address_Decode_Encode_Test::run()
{
    std::list<SIP_Address_Input_Output>::const_iterator it = _address_input_output.begin();
    while (it != _address_input_output.end())
    {
        SIP_Address_Input_Output address_input_output = *it++;

        std::cout << "SIP address decode encode test initialized\n";

        SIP_Address *sip_address = new SIP_Address();

        if (!sip_address->decode(address_input_output._input))
        {
            std::cout << "SIP_Address_Decode_Encode_Test::run -> Failed to decode address:\n";
            std::cout << std::setw(12) << "Input: " << address_input_output._input.c_str() << "\n";
            delete sip_address;
            return false;
        }

        SIP_Address *copy = new SIP_Address(*sip_address);
        delete sip_address;
        sip_address = NULL;

        std::string output;
        if (!copy->encode(output))
        {
            std::cout << "SIP_Address_Decode_Encode_Test::run -> Failed to encode address:\n";
            std::cout << std::setw(12) << "Input: " << address_input_output._input.c_str() << "\n";
            delete copy;
            return false;
        }

        if (output != address_input_output._output)
        {
            std::cout << "SIP_Address_Decode_Encode_Test::run -> Invalid encoded address:\n";
            std::cout << std::setw(12) << "Input: " << address_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << address_input_output._output.c_str() << "\n";
            std::cout << std::setw(12) << "Output: " << output.c_str() << "\n";
            delete copy;
            return false;
        }

        delete copy;
        copy = NULL;

        std::cout << "SIP address decode encode test completed successfully\n";
    }

    return true;
}

//-------------------------------------------
