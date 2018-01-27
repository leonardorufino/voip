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
        if (!message)
        {
            std::cout << "SIP_Message_Test::run -> Failed to decode message:\n";
            std::cout << std::setw(12) << "Type: " << message_input_output._method_type << "\n";
            std::cout << std::setw(12) << "Input: " << message_input_output._input.c_str() << "\n";
            return false;
        }

        if (read != input.size())
        {
            std::cout << "SIP_Message_Test::run -> Invalid decoded message size:\n";
            std::cout << std::setw(12) << "Type: " << message_input_output._method_type << "\n";
            std::cout << std::setw(12) << "Input: " << message_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << input.size() << "\n";
            std::cout << std::setw(12) << "Read: " << read << "\n";
            delete message;
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

        char output[MAX_MESSAGE_SIZE] = {0};
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
    msg1._input  += "Content-Length: 335\r\n";
    msg1._input  += "\r\n";
    msg1._input  += "v=0\r\n";
    msg1._input  += "o=jdoe 2890844526 2890842807 IN IP4 10.47.16.5\r\n";
    msg1._input  += "s=SDP Seminar\r\n";
    msg1._input  += "i=A Seminar on the session description protocol\r\n";
    msg1._input  += "u=http://www.example.com/seminars/sdp.pdf\r\n";
    msg1._input  += "e=j.doe@example.com (Jane Doe)\r\n";
    msg1._input  += "c=IN IP4 224.2.17.12/127\r\n";
    msg1._input  += "t=2873397496 2873404696\r\n";
    msg1._input  += "a=recvonly\r\n";
    msg1._input  += "m=audio 49170 RTP/AVP 0\r\n";
    msg1._input  += "m=video 51372 RTP/AVP 99\r\n";
    msg1._input  += "a=rtpmap:99 h263-1998/90000\r\n";

    msg1._output  = "INVITE sip:bob@biloxi.com SIP/2.0\r\n";
    msg1._output += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    msg1._output += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    msg1._output += "Content-Length: 335\r\n";
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
    msg1._output += "v=0\r\n";
    msg1._output += "o=jdoe 2890844526 2890842807 IN IP4 10.47.16.5\r\n";
    msg1._output += "s=SDP Seminar\r\n";
    msg1._output += "i=A Seminar on the session description protocol\r\n";
    msg1._output += "u=http://www.example.com/seminars/sdp.pdf\r\n";
    msg1._output += "e=j.doe@example.com (Jane Doe)\r\n";
    msg1._output += "c=IN IP4 224.2.17.12/127\r\n";
    msg1._output += "t=2873397496 2873404696\r\n";
    msg1._output += "a=recvonly\r\n";
    msg1._output += "m=audio 49170 RTP/AVP 0\r\n";
    msg1._output += "m=video 51372 RTP/AVP 99\r\n";
    msg1._output += "a=rtpmap:99 h263-1998/90000\r\n";

    msg1._response_answer = false;
    _message_input_output.push_back(msg1);


    SIP_Message_Input_Output msg2;
    msg2._method_type = SIP_REQUEST_INFO;

    msg2._input   = "INFO sip:bob@biloxi.com SIP/2.0\r\n";
    msg2._input  += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK983hja\r\n";
    msg2._input  += "Max-Forwards: 70\r\n";
    msg2._input  += "To: Bob <sip:bob@biloxi.com>\r\n";
    msg2._input  += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    msg2._input  += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    msg2._input  += "CSeq: 314160 INFO\r\n";
    msg2._input  += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    msg2._input  += "Content-Type: test/unknown\r\n";
    msg2._input  += "Content-Length: 10\r\n";
    msg2._input  += "\r\n";
    msg2._input  += "0123456789";

    msg2._output  = "INFO sip:bob@biloxi.com SIP/2.0\r\n";
    msg2._output += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    msg2._output += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    msg2._output += "Content-Length: 10\r\n";
    msg2._output += "Content-Type: test/unknown\r\n";
    msg2._output += "CSeq: 314160 INFO\r\n";
    msg2._output += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    msg2._output += "Max-Forwards: 70\r\n";
    msg2._output += "To: Bob <sip:bob@biloxi.com>\r\n";
    msg2._output += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK983hja\r\n";
    msg2._output += "\r\n";
    msg2._output += "0123456789";

    msg2._response_answer = false;
    _message_input_output.push_back(msg2);


    SIP_Message_Input_Output msg3;
    msg3._method_type = SIP_REQUEST_OPTIONS;

    msg3._input   = "OPTIONS sip:carol@chicago.com SIP/2.0\r\n";
    msg3._input  += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKhjhs8ass877\r\n";
    msg3._input  += "Max-Forwards: 70\r\n";
    msg3._input  += "To: <sip:carol@chicago.com>\r\n";
    msg3._input  += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    msg3._input  += "Call-ID: a84b4c76e66710\r\n";
    msg3._input  += "CSeq: 63104 OPTIONS\r\n";
    msg3._input  += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    msg3._input  += "Accept: application/sdp\r\n";
    msg3._input  += "Content-Length: 0\r\n";
    msg3._input  += "\r\n";

    msg3._output  = "OPTIONS sip:carol@chicago.com SIP/2.0\r\n";
    msg3._output += "Accept: application/sdp\r\n";
    msg3._output += "Call-ID: a84b4c76e66710\r\n";
    msg3._output += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    msg3._output += "Content-Length: 0\r\n";
    msg3._output += "CSeq: 63104 OPTIONS\r\n";
    msg3._output += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    msg3._output += "Max-Forwards: 70\r\n";
    msg3._output += "To: <sip:carol@chicago.com>\r\n";
    msg3._output += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKhjhs8ass877\r\n";
    msg3._output += "\r\n";

    msg3._response_answer = false;
    _message_input_output.push_back(msg3);
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
    msg1._input  += "Allow: INVITE, ACK, OPTIONS, CANCEL, BYE\r\n";
    msg1._input  += "Content-Type: application/sdp\r\n";
    msg1._input  += "Content-Length: 148\r\n";
    msg1._input  += "\r\n";
    msg1._input  += "v=0\r\n";
    msg1._input  += "o=UserA 2890844526 2890844526 IN IP4 here.com\r\n";
    msg1._input  += "s=Session SDP\r\n";
    msg1._input  += "c=IN IP4 pc33.atlanta.com\r\n";
    msg1._input  += "t=0 0\r\n";
    msg1._input  += "m=audio 49172 RTP/AVP 0\r\n";
    msg1._input  += "a=rtpmap:0 PCMU/8000\r\n";

    msg1._output  = "SIP/2.0 200 OK\r\n";
    msg1._output += "Allow: INVITE, ACK, OPTIONS, CANCEL, BYE\r\n";
    msg1._output += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    msg1._output += "Contact: <sip:bob@192.0.2.4>\r\n";
    msg1._output += "Content-Length: 148\r\n";
    msg1._output += "Content-Type: application/sdp\r\n";
    msg1._output += "CSeq: 314159 INVITE\r\n";
    msg1._output += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    msg1._output += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    msg1._output += "Via: SIP/2.0/UDP server10.biloxi.com;branch=z9hG4bKnashds8;received=192.0.2.3\r\n";
    msg1._output += "Via: SIP/2.0/UDP bigbox3.site3.atlanta.com;branch=z9hG4bK77ef4c2312983.1;received=192.0.2.2\r\n";
    msg1._output += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n";
    msg1._output += "\r\n";
    msg1._output += "v=0\r\n";
    msg1._output += "o=UserA 2890844526 2890844526 IN IP4 here.com\r\n";
    msg1._output += "s=Session SDP\r\n";
    msg1._output += "c=IN IP4 pc33.atlanta.com\r\n";
    msg1._output += "t=0 0\r\n";
    msg1._output += "m=audio 49172 RTP/AVP 0\r\n";
    msg1._output += "a=rtpmap:0 PCMU/8000\r\n";

    msg1._response_answer = false;
    _message_input_output.push_back(msg1);


    SIP_Message_Input_Output msg2;
    msg2._method_type = SIP_RESPONSE;

    msg2._input   = "SIP/2.0 200 OK\r\n";
    msg2._input  += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK0192oa ;received=192.0.2.1\r\n";
    msg2._input  += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    msg2._input  += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    msg2._input  += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    msg2._input  += "CSeq: 314160 OPTIONS\r\n";
    msg2._input  += "Contact: <sip:bob@192.0.2.4>\r\n";
    msg2._input  += "Content-Length: 0\r\n";
    msg2._input  += "\r\n";

    msg2._output  = "SIP/2.0 200 OK\r\n";
    msg2._output += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    msg2._output += "Contact: <sip:bob@192.0.2.4>\r\n";
    msg2._output += "Content-Length: 0\r\n";
    msg2._output += "CSeq: 314160 OPTIONS\r\n";
    msg2._output += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    msg2._output += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    msg2._output += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK0192oa;received=192.0.2.1\r\n";
    msg2._output += "\r\n";

    msg2._response_answer = false;
    _message_input_output.push_back(msg2);
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
    msg1._input  += "Content-Length: 160\r\n";
    msg1._input  += "\r\n";
    msg1._input  += "v=0\r\n";
    msg1._input  += "o=alice 53655765 2353687637 IN IP4 pc33.atlanta.com\r\n";
    msg1._input  += "s=Session SDP\r\n";
    msg1._input  += "t=0 0\r\n";
    msg1._input  += "c=IN IP4 pc33.atlanta.com\r\n";
    msg1._input  += "m=audio 3456 RTP/AVP 0 1 3 99\r\n";
    msg1._input  += "a=rtpmap:0 PCMU/8000\r\n";

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
