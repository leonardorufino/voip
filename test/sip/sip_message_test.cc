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
#include <assert.h>

//-------------------------------------------

void SIP_Message_Test::init()
{
    std::cout << "SIP message test initialized.\n";

    SIP_Request_Test request;
    request.run();

    SIP_Response_Test response;
    response.run();

    std::cout << "SIP message test completed successfully.\n";
}

//-------------------------------------------

void SIP_Message_Test::run()
{
    std::list<SIP_Message_Input_Output>::iterator it = _message_input_output.begin();
    while (it != _message_input_output.end())
    {
        SIP_Message_Input_Output message_input_output = *it++;

        SIP_Message *message = SIP_Message::decode_msg(message_input_output._input);
        assert(message != NULL);

        std::string msg;
        assert(message->encode(msg));
        assert(msg == message_input_output._output);

        delete message;
    }
}

//-------------------------------------------
//-------------------------------------------

SIP_Request_Test::SIP_Request_Test()
{
    SIP_Message_Input_Output msg1(
"INVITE sip:bob@biloxi.com SIP/2.0\r\n\
Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds\r\n\
Max-Forwards: 70\r\n\
To: Bob <sip:bob@biloxi.com>\r\n\
From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n\
Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n\
CSeq: 314159 INVITE\r\n\
Contact: <sip:alice@pc33.atlanta.com>\r\n\
Content-Type: application/sdp\r\n\
Content-Length: 0\r\n\r\n",
"INVITE sip:bob@biloxi.com SIP/2.0\r\n\
Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n\
Contact: <sip:alice@pc33.atlanta.com>\r\n\
Content-Length: 0\r\n\
Content-Type: application/sdp\r\n\
CSeq: 314159 INVITE\r\n\
From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n\
Max-Forwards: 70\r\n\
To: Bob <sip:bob@biloxi.com>\r\n\
Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds\r\n\r\n");
    _message_input_output.push_back(msg1);
}

//-------------------------------------------
//-------------------------------------------

SIP_Response_Test::SIP_Response_Test()
{
    SIP_Message_Input_Output msg1(
"SIP/2.0 200 OK\r\n\
Via: SIP/2.0/UDP server10.biloxi.com;branch=z9hG4bKnashds8;received=192.0.2.3,\
 SIP/2.0/UDP bigbox3.site3.atlanta.com;branch=z9hG4bK77ef4c2312983.1;received=192.0.2.2\r\n\
Via: SIP/2.0/UDP pc33.atlanta.com\r\n\
\t;branch=z9hG4bK776asdhds ;received=192.0.2.1\r\n\
To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n\
From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n\
Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n\
CSeq: 314159 INVITE\r\n\
Contact: <sip:bob@192.0.2.4>\r\n\
Content-Type: application/sdp\r\n\
Content-Length: 0\r\n\r\n",
"SIP/2.0 200 OK\r\n\
Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n\
Contact: <sip:bob@192.0.2.4>\r\n\
Content-Length: 0\r\n\
Content-Type: application/sdp\r\n\
CSeq: 314159 INVITE\r\n\
From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n\
To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n\
Via: SIP/2.0/UDP server10.biloxi.com;branch=z9hG4bKnashds8;received=192.0.2.3\r\n\
Via: SIP/2.0/UDP bigbox3.site3.atlanta.com;branch=z9hG4bK77ef4c2312983.1;received=192.0.2.2\r\n\
Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n\r\n");
    _message_input_output.push_back(msg1);
}

//-------------------------------------------
