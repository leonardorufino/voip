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

#include "sip_message_test.h"
#include <iostream>

//-------------------------------------------

bool SIP_Message_Test::init()
{
    std::cout << "SIP message test initialized\n";

    if (!run<SIP_Request_Test>())
        return false;

    if (!run<SIP_Response_Test>())
        return false;

    if (!run<SIP_Response_Answer_Test>())
        return false;

    std::cout << "SIP message test completed successfully\n";
    return true;
}

//-------------------------------------------

template<class T> bool SIP_Message_Test::run()
{
    T test;
    if (!test.run())
        return false;
    return true;
}

//-------------------------------------------

bool SIP_Message_Test::run()
{
    std::list<SIP_Message_Input_Output>::const_iterator it = _message_input_output.begin();
    while (it != _message_input_output.end())
    {
        SIP_Message_Input_Output message_input_output = *it++;

        std::cout << "SIP message test initialized (type: " << message_input_output._method_type << ")\n";

        std::string input = message_input_output._input;
        unsigned short read = 0;
        SIP_Message *message = SIP_Message::decode_message(input.c_str(), (unsigned short) input.size(), read);
        if ((!message) || (read != input.size()))
        {
            std::cout << "SIP_Message_Test::run -> Failed to decode message:\n";
            std::cout << std::setw(12) << "Type: " << message_input_output._method_type << "\n";
            std::cout << std::setw(12) << "Input: " << message_input_output._input.c_str() << "\n";
            return false;
        }

        SIP_Message *copy = copy_message(*message, message_input_output._response_answer);
        if (!copy)
        {
            std::cout << "SIP_Message_Test::run -> Failed to copy message:\n";
            std::cout << std::setw(12) << "Type: " << message_input_output._method_type << "\n";
            std::cout << std::setw(12) << "Input: " << message_input_output._input.c_str() << "\n";
            delete message;
            return false;
        }

        delete message;
        message = NULL;

        char output[1000] = {0};
        unsigned short size = sizeof(output);

        if (!copy->encode(output, size))
        {
            std::cout << "SIP_Message_Test::run -> Failed to encode message:\n";
            std::cout << std::setw(12) << "Type: " << message_input_output._method_type << "\n";
            std::cout << std::setw(12) << "Input: " << message_input_output._input.c_str() << "\n";
            delete copy;
            return false;
        }

        if (strcmp(output, message_input_output._output.c_str()) != 0)
        {
            std::cout << "SIP_Message_Test::run -> Invalid encoded message:\n";
            std::cout << std::setw(12) << "Type: " << message_input_output._method_type << "\n";
            std::cout << std::setw(12) << "Input: " << message_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << message_input_output._output.c_str() << "\n";
            std::cout << std::setw(12) << "Output: " << output << "\n";
            delete copy;
            return false;
        }

        delete copy;
        copy = NULL;

        std::cout << "SIP message test completed successfully (type: " << message_input_output._method_type << ")\n";
    }

    return true;
}

//-------------------------------------------

SIP_Message *SIP_Message_Test::copy_message(SIP_Message &message, bool response_answer)
{
    SIP_Message *copy = NULL;

    switch (message.get_message_type())
    {
        case SIP_RESPONSE:
        {
            SIP_Response &response = dynamic_cast<SIP_Response &>(message);
            copy = new SIP_Response(response);
            break;
        }

        case SIP_METHOD_INVALID:
            break;

        default:
        {
            SIP_Request &request = dynamic_cast<SIP_Request &>(message);
            if (!response_answer)
                copy = new SIP_Request(request);
            else
                copy = new SIP_Response(200, request);
            break;
        }
    }

    return copy;
}

//-------------------------------------------
//-------------------------------------------

SIP_Request_Test::SIP_Request_Test()
{
    SIP_Message_Input_Output msg1;
    msg1._method_type = SIP_REQUEST_INVITE;

    msg1._input   = "INVITE sip:bob@biloxi.com SIP/2.0\r\n";
    msg1._input  += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds\r\n";
    msg1._input  += "Max-Forwards: 70\r\n";
    msg1._input  += "To: Bob <sip:bob@biloxi.com>\r\n";
    msg1._input  += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    msg1._input  += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    msg1._input  += "CSeq: 314159 INVITE\r\n";
    msg1._input  += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    msg1._input  += "X-Header: xyz\r\n";
    msg1._input  += "X-Header: foo, bar\r\n";
    msg1._input  += "Unknown: test\r\n";
    msg1._input  += "Content-Type: application/sdp\r\n";
    msg1._input  += "Content-Length: 0\r\n";
    msg1._input  += "\r\n";

    msg1._output  = "INVITE sip:bob@biloxi.com SIP/2.0\r\n";
    msg1._output += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    msg1._output += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    msg1._output += "Content-Length: 0\r\n";
    msg1._output += "Content-Type: application/sdp\r\n";
    msg1._output += "CSeq: 314159 INVITE\r\n";
    msg1._output += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    msg1._output += "Max-Forwards: 70\r\n";
    msg1._output += "To: Bob <sip:bob@biloxi.com>\r\n";
    msg1._output += "X-Header: xyz\r\n";
    msg1._output += "X-Header: foo, bar\r\n";
    msg1._output += "Unknown: test\r\n";
    msg1._output += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds\r\n";
    msg1._output += "\r\n";

    msg1._response_answer = false;
    _message_input_output.push_back(msg1);
}

//-------------------------------------------
//-------------------------------------------

SIP_Response_Test::SIP_Response_Test()
{
    SIP_Message_Input_Output msg1;
    msg1._method_type = SIP_RESPONSE;

    msg1._input   = "SIP/2.0 200 OK\r\n";
    msg1._input  += "Via: SIP/2.0/UDP server10.biloxi.com;branch=z9hG4bKnashds8;received=192.0.2.3,";
    msg1._input  += " SIP/2.0/UDP bigbox3.site3.atlanta.com;branch=z9hG4bK77ef4c2312983.1;received=192.0.2.2\r\n";
    msg1._input  += "Via: SIP/2.0/UDP pc33.atlanta.com\r\n";
    msg1._input  += "\t;branch=z9hG4bK776asdhds ;received=192.0.2.1\r\n";
    msg1._input  += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    msg1._input  += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    msg1._input  += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    msg1._input  += "CSeq: 314159 INVITE\r\n";
    msg1._input  += "Contact: <sip:bob@192.0.2.4>\r\n";
    msg1._input  += "Content-Type: application/sdp\r\n";
    msg1._input  += "Content-Length: 0\r\n";
    msg1._input  += "\r\n";

    msg1._output  = "SIP/2.0 200 OK\r\n";
    msg1._output += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    msg1._output += "Contact: <sip:bob@192.0.2.4>\r\n";
    msg1._output += "Content-Length: 0\r\n";
    msg1._output += "Content-Type: application/sdp\r\n";
    msg1._output += "CSeq: 314159 INVITE\r\n";
    msg1._output += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    msg1._output += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    msg1._output += "Via: SIP/2.0/UDP server10.biloxi.com;branch=z9hG4bKnashds8;received=192.0.2.3\r\n";
    msg1._output += "Via: SIP/2.0/UDP bigbox3.site3.atlanta.com;branch=z9hG4bK77ef4c2312983.1;received=192.0.2.2\r\n";
    msg1._output += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n";
    msg1._output += "\r\n";

    msg1._response_answer = false;
    _message_input_output.push_back(msg1);
}

//-------------------------------------------
//-------------------------------------------

SIP_Response_Answer_Test::SIP_Response_Answer_Test()
{
    SIP_Message_Input_Output msg1;
    msg1._method_type = SIP_REQUEST_INVITE;

    msg1._input   = "INVITE sip:bob@biloxi.com SIP/2.0\r\n";
    msg1._input  += "Via: SIP/2.0/UDP server10.biloxi.com;branch=z9hG4bKnashds8;received=192.0.2.3,";
    msg1._input  += " SIP/2.0/UDP bigbox3.site3.atlanta.com;branch=z9hG4bK77ef4c2312983.1\r\n";
    msg1._input  += "Via: SIP/2.0/UDP pc33.atlanta.com\r\n";
    msg1._input  += "\t;branch=z9hG4bK776asdhds ;received=192.0.2.1\r\n";
    msg1._input  += "To: Bob <sip:bob@biloxi.com>\r\n";
    msg1._input  += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    msg1._input  += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    msg1._input  += "CSeq: 314159 INVITE\r\n";
    msg1._input  += "Contact: <sip:bob@192.0.2.4>\r\n";
    msg1._input  += "Content-Type: application/sdp\r\n";
    msg1._input  += "Content-Length: 0\r\n";
    msg1._input  += "\r\n";

    msg1._output  = "SIP/2.0 200 OK\r\n";
    msg1._output += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    msg1._output += "Content-Length: 0\r\n";
    msg1._output += "CSeq: 314159 INVITE\r\n";
    msg1._output += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    msg1._output += "To: Bob <sip:bob@biloxi.com>\r\n";
    msg1._output += "Via: SIP/2.0/UDP server10.biloxi.com;branch=z9hG4bKnashds8;received=192.0.2.3\r\n";
    msg1._output += "Via: SIP/2.0/UDP bigbox3.site3.atlanta.com;branch=z9hG4bK77ef4c2312983.1\r\n";
    msg1._output += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n";
    msg1._output += "\r\n";

    msg1._response_answer = true;
    _message_input_output.push_back(msg1);
}

//-------------------------------------------
