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

    SIP_Request_Test request;
    if (!request.run())
        return false;

    SIP_Response_Test response;
    if (!response.run())
        return false;

    std::cout << "SIP message test completed successfully\n";
    return true;
}

//-------------------------------------------

bool SIP_Message_Test::run()
{
    std::list<SIP_Message_Input_Output>::const_iterator it = _message_input_output.begin();
    while (it != _message_input_output.end())
    {
        SIP_Message_Input_Output message_input_output = *it++;

        std::string input = message_input_output._input;
        SIP_Message *message = SIP_Message::decode_msg(input);
        if (!message)
        {
            std::cout << "SIP_Message_Test::run -> Failed to decode message:\n";
            std::cout << std::setw(12) << "Input: " << message_input_output._input.c_str() << "\n";
            return false;
        }

        SIP_Message *copy = copy_message(*message);
        if (!copy)
        {
            std::cout << "SIP_Message_Test::run -> Failed to copy message:\n";
            std::cout << std::setw(12) << "Input: " << message_input_output._input.c_str() << "\n";
            delete message;
            return false;
        }

        delete message;
        message = NULL;

        std::string output;
        if (!copy->encode(output))
        {
            std::cout << "SIP_Message_Test::run -> Failed to encode message:\n";
            std::cout << std::setw(12) << "Input: " << message_input_output._input.c_str() << "\n";
            delete copy;
            return false;
        }

        if (output != message_input_output._output)
        {
            std::cout << "SIP_Message_Test::run -> Invalid encoded message:\n";
            std::cout << std::setw(12) << "Input: " << message_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << message_input_output._output.c_str() << "\n";
            std::cout << std::setw(12) << "Output: " << output.c_str() << "\n";
            delete copy;
            return false;
        }

        delete copy;
        copy = NULL;
    }

    return true;
}

//-------------------------------------------

SIP_Message *SIP_Message_Test::copy_message(SIP_Message &message)
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
            copy = new SIP_Request(request);
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
    msg1._input   = "INVITE sip:bob@biloxi.com SIP/2.0\r\n";
    msg1._input  += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds\r\n";
    msg1._input  += "Max-Forwards: 70\r\n";
    msg1._input  += "To: Bob <sip:bob@biloxi.com>\r\n";
    msg1._input  += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    msg1._input  += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    msg1._input  += "CSeq: 314159 INVITE\r\n";
    msg1._input  += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    msg1._input  += "Content-Type: application/sdp\r\n";
    msg1._input  += "Content-Length: 0\r\n\r\n";

    msg1._output  = "INVITE sip:bob@biloxi.com SIP/2.0\r\n";
    msg1._output += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    msg1._output += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    msg1._output += "Content-Length: 0\r\n";
    msg1._output += "Content-Type: application/sdp\r\n";
    msg1._output += "CSeq: 314159 INVITE\r\n";
    msg1._output += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    msg1._output += "Max-Forwards: 70\r\n";
    msg1._output += "To: Bob <sip:bob@biloxi.com>\r\n";
    msg1._output += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds\r\n\r\n";
    _message_input_output.push_back(msg1);
}

//-------------------------------------------
//-------------------------------------------

SIP_Response_Test::SIP_Response_Test()
{
    SIP_Message_Input_Output msg1;
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
    msg1._input  += "Content-Length: 0\r\n\r\n";

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
    msg1._output += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n\r\n";
    _message_input_output.push_back(msg1);
}

//-------------------------------------------
