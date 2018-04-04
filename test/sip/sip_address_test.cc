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

    if (!run<SIP_Address_Query_Test>())
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
//-------------------------------------------

SIP_Address_Query_Test::SIP_Address_Query_Test()
{
    _address_query.emplace_back(QUERY_SET, "Display-Name-Double-Quote.False", "", true);
    _address_query.emplace_back(QUERY_GET, "Display-Name-Double-Quote", "False", true);
    _address_query.emplace_back(QUERY_SET, "Display-Name-Double-Quote.True", "", true);
    _address_query.emplace_back(QUERY_GET, "Display-Name-Double-Quote", "True", true);
    _address_query.emplace_back(QUERY_SET, "Display-Name.Test User", "", true);
    _address_query.emplace_back(QUERY_GET, "Display-Name", "Test User", true);
    _address_query.emplace_back(QUERY_SET, "Scheme.tel", "", true);
    _address_query.emplace_back(QUERY_GET, "Scheme", "tel", true);
    _address_query.emplace_back(QUERY_SET, "URI-Angle-Quote.False", "", true);
    _address_query.emplace_back(QUERY_GET, "URI-Angle-Quote", "False", true);
    _address_query.emplace_back(QUERY_SET, "URI-Angle-Quote.True", "", true);
    _address_query.emplace_back(QUERY_GET, "URI-Angle-Quote", "True", true);
    _address_query.emplace_back(QUERY_SET, "SIP-URI.User.test1", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.User", "test1", true);
    _address_query.emplace_back(QUERY_SET, "SIP-URI.Password.mypass", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Password", "mypass", true);
    _address_query.emplace_back(QUERY_SET, "SIP-URI.Host.Address.10.10.10.10", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Host.Address", "10.10.10.10", true);
    _address_query.emplace_back(QUERY_SET, "SIP-URI.Port.65000", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Port", "65000", true);
    _address_query.emplace_back(QUERY_SET, "SIP-URI.Transport.TCP", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Transport", "TCP", true);
    _address_query.emplace_back(QUERY_SET, "SIP-URI.User-Param.phone", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.User-Param", "phone", true);
    _address_query.emplace_back(QUERY_SET, "SIP-URI.Method.BYE", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Method", "BYE", true);
    _address_query.emplace_back(QUERY_SET, "SIP-URI.TTL.2", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.TTL", "2", true);
    _address_query.emplace_back(QUERY_SET, "SIP-URI.Multicast-Address.Address.1111::2222", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Multicast-Address.Address", "1111::2222", true);
    _address_query.emplace_back(QUERY_SET, "SIP-URI.LR.False", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.LR", "False", true);
    _address_query.emplace_back(QUERY_SET, "SIP-URI.LR.True", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.LR", "True", true);
    _address_query.emplace_back(QUERY_ADD, "SIP-URI.Parameters.0.parameter1", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Parameters.Size", "1", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Parameters.0", "parameter1", true);
    _address_query.emplace_back(QUERY_ADD, "SIP-URI.Parameters.1.par2=test", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Parameters.Size", "2", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Parameters.1", "par2=test", true);
    _address_query.emplace_back(QUERY_ADD, "SIP-URI.Parameters.0.parameter0", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Parameters.Size", "3", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Parameters.0", "parameter0", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Parameters.0", "parameter0", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Parameters.1", "parameter1", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Parameters.2", "par2=test", true);
    _address_query.emplace_back(QUERY_DEL, "SIP-URI.Parameters.1", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Parameters.Size", "2", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Parameters.0", "parameter0", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Parameters.1", "par2=test", true);
    _address_query.emplace_back(QUERY_DEL, "SIP-URI.Parameters.0", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Parameters.Size", "1", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Parameters.0", "par2=test", true);
    _address_query.emplace_back(QUERY_DEL, "SIP-URI.Parameters.0", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Parameters.Size", "0", true);
    _address_query.emplace_back(QUERY_ADD, "SIP-URI.Headers.0.header1=test", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Headers.Size", "1", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Headers.0", "header1=test", true);
    _address_query.emplace_back(QUERY_DEL, "SIP-URI.Headers.0", "", true);
    _address_query.emplace_back(QUERY_GET, "SIP-URI.Headers.Size", "0", true);
    _address_query.emplace_back(QUERY_SET, "Absolute-URI.Address.192.168.1.240", "", true);
    _address_query.emplace_back(QUERY_GET, "Absolute-URI.Address", "192.168.1.240", true);
}

//-------------------------------------------

bool SIP_Address_Query_Test::run()
{
    SIP_Address sip_address;

    std::list<SIP_Address_Query>::const_iterator it = _address_query.begin();
    while (it != _address_query.end())
    {
        SIP_Address_Query address_query = *it++;

        std::cout << "SIP address query test initialized\n";

        std::string result;
        bool success = sip_address.query(address_query._cmd, address_query._query, result);

        if (address_query._success != success)
        {
            std::cout << "SIP_Address_Query_Test::run -> Query failed:\n";
            std::cout << std::setw(12) << "Cmd: " << address_query._cmd << "\n";
            std::cout << std::setw(12) << "Query: " << address_query._query.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << (address_query._success ? "true" : "false") << "\n";
            std::cout << std::setw(12) << "Success: " << (success ? "true" : "false") << "\n";
            return false;
        }

        if ((!address_query._expected_result.empty()) && (result != address_query._expected_result))
        {
            std::cout << "SIP_Address_Query_Test::run -> Query result failed:\n";
            std::cout << std::setw(12) << "Cmd: " << address_query._cmd << "\n";
            std::cout << std::setw(12) << "Query: " << address_query._query.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << address_query._expected_result.c_str() << "\n";
            std::cout << std::setw(12) << "Result: " << result.c_str() << "\n";
            return false;
        }

        std::cout << "SIP address query test completed successfully\n";
    }

    return true;
}

//-------------------------------------------
