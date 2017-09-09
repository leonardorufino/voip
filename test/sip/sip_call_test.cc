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

#include "sip_call_test.h"
#include <iostream>

//-------------------------------------------

SIP_Call_Test::SIP_Call_Test() : _client_call(0), _server_call(1), _use_prack(false), _client_sequence(314158), _server_sequence(230),
    _invite_sequence(0), _prack_rseq(988788), _sent_message(false), _received_request(false), _received_response(false)
{
}

//-------------------------------------------

bool SIP_Call_Test::init()
{
    std::cout << "SIP call test initialized\n";

    if (!run<SIP_Call_Success_Test>())
        return false;

    if (!run<SIP_Call_Success_No_100_Test>())
        return false;

    if (!run<SIP_Call_Success_No_1xx_Test>())
        return false;

    if (!run<SIP_Call_Reject_Test>())
        return false;

    if (!run<SIP_Call_Reject_No_100_Test>())
        return false;

    if (!run<SIP_Call_Reject_No_1xx_Test>())
        return false;

    if (!run<SIP_Call_Update_Test>())
        return false;

    if (!run<SIP_Call_Cancel_Test>())
        return false;

    if (!run<SIP_Call_Prack_Test>())
        return false;

    if (!run<SIP_Call_Prack_No_100_Test>())
        return false;

    if (!run<SIP_Call_Options_Test>())
        return false;

    if (!run<SIP_Call_Options_With_100_Test>())
        return false;

    std::cout << "SIP call test completed successfully\n";
    return true;
}

//-------------------------------------------

template<class T> bool SIP_Call_Test::run()
{
    T test;
    if (!test.run())
        return false;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::set_callbacks()
{
    _server_call.set_send_message_callback(send_message_callback, this);
    _server_call.set_receive_request_callback(receive_request_callback, this);
    _server_call.set_receive_response_callback(receive_response_callback, this);

    _client_call.set_send_message_callback(send_message_callback, this);
    _client_call.set_receive_request_callback(receive_request_callback, this);
    _client_call.set_receive_response_callback(receive_response_callback, this);

    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Request *SIP_Call_Test::create_invite()
{
    _invite_branch = "z9hG4bK" + String_Functions::random(10);

    std::string str;
    str  = "INVITE sip:bob@biloxi.com SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _invite_branch + "\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(++_client_sequence) + " INVITE\r\n";
    str += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    str += "Content-Length: 0\r\n";

    if (_use_prack)
        str += "Supported: 100rel\r\n";

    _invite_sequence = _client_sequence;

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Call_Test::create_invite -> Failed to decode message\n";
        return NULL;
    }

    return request;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_invite_response_100()
{
    std::string str;
    str  = "SIP/2.0 100 Trying\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _invite_branch + ";received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " INVITE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_invite_response_100 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_invite_response_180()
{
    std::string str;
    str  = "SIP/2.0 180 Ringing\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _invite_branch + ";received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " INVITE\r\n";
    str += "Contact: <sip:bob@192.0.2.4>\r\n";
    str += "Content-Length: 0\r\n";

    if (_use_prack)
    {
        str += "Require: 100rel\r\n";
        str += "RSeq: " + std::to_string(++_prack_rseq) + "\r\n";
    }

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_invite_response_180 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_invite_response_183()
{
    std::string str;
    str  = "SIP/2.0 183 Session Progress\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _invite_branch + ";received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " INVITE\r\n";
    str += "Contact: <sip:bob@192.0.2.4>\r\n";
    str += "Content-Length: 0\r\n";

    if (_use_prack)
    {
        str += "Require: 100rel\r\n";
        str += "RSeq: " + std::to_string(++_prack_rseq) + "\r\n";
    }

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_invite_response_180 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_invite_response_200()
{
    std::string str;
    str  = "SIP/2.0 200 OK\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _invite_branch + ";received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " INVITE\r\n";
    str += "Contact: <sip:bob@192.0.2.4>\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_invite_response_200 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_invite_response_480()
{
    std::string str;
    str  = "SIP/2.0 480 Temporarily Unavailable\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _invite_branch + ";received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " INVITE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_invite_response_480 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_invite_response_487()
{
    std::string str;
    str  = "SIP/2.0 487 Request Terminated\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _invite_branch + ";received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " INVITE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_invite_response_487 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Request *SIP_Call_Test::create_ack()
{
    std::string ack_branch = "z9hG4bK" + String_Functions::random(10);

    std::string str;
    str  = "ACK sip:bob@192.0.2.4 SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + ack_branch + "\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_invite_sequence) + " ACK\r\n";
    str += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Call_Test::create_ack -> Failed to decode message\n";
        return NULL;
    }

    return request;
}

//-------------------------------------------

SIP_Request *SIP_Call_Test::create_client_bye()
{
    _bye_branch = "z9hG4bK" + String_Functions::random(10);

    std::string str;
    str  = "BYE sip:bob@192.0.2.4 SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _bye_branch + "\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(++_client_sequence) + " BYE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Call_Test::create_client_bye -> Failed to decode message\n";
        return NULL;
    }

    return request;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_server_bye_response_200()
{
    std::string str;
    str  = "SIP/2.0 200 OK\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _bye_branch + "\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " BYE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_server_bye_response_200 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Request *SIP_Call_Test::create_server_bye()
{
    _bye_branch = "z9hG4bK" + String_Functions::random(10);

    std::string str;
    str  = "BYE sip:alice@pc33.atlanta.com SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP 192.0.2.4;branch=" + _bye_branch + "\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "From: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "To: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(++_server_sequence) + " BYE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Call_Test::create_server_bye -> Failed to decode message\n";
        return NULL;
    }

    return request;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_client_bye_response_200()
{
    std::string str;
    str  = "SIP/2.0 200 OK\r\n";
    str += "Via: SIP/2.0/UDP 192.0.2.4;branch=" + _bye_branch + "\r\n";
    str += "From: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "To: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_server_sequence) + " BYE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_client_bye_response_200 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Request *SIP_Call_Test::create_client_update()
{
    _update_branch = "z9hG4bK" + String_Functions::random(10);

    std::string str;
    str  = "UPDATE sip:bob@192.0.2.4 SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _update_branch + "\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(++_client_sequence) + " UPDATE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Call_Test::create_client_update -> Failed to decode message\n";
        return NULL;
    }

    return request;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_server_update_response_200()
{
    std::string str;
    str  = "SIP/2.0 200 OK\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _update_branch + "\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " UPDATE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_server_update_response_200 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Request *SIP_Call_Test::create_server_update()
{
    _update_branch = "z9hG4bK" + String_Functions::random(10);

    std::string str;
    str  = "UPDATE sip:alice@pc33.atlanta.com SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP 192.0.2.4;branch=" + _update_branch + "\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "From: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "To: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(++_server_sequence) + " UPDATE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Call_Test::create_server_update -> Failed to decode message\n";
        return NULL;
    }

    return request;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_client_update_response_200()
{
    std::string str;
    str  = "SIP/2.0 200 OK\r\n";
    str += "Via: SIP/2.0/UDP 192.0.2.4;branch=" + _update_branch + "\r\n";
    str += "From: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "To: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_server_sequence) + " UPDATE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_client_update_response_200 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Request *SIP_Call_Test::create_cancel()
{
    std::string str;
    str  = "CANCEL sip:bob@192.0.2.4 SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _invite_branch + "\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_invite_sequence) + " CANCEL\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Call_Test::create_cancel -> Failed to decode message\n";
        return NULL;
    }

    return request;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_cancel_response_200()
{
    std::string str;
    str  = "SIP/2.0 200 OK\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _invite_branch + "\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_invite_sequence) + " CANCEL\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_cancel_response_200 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Request *SIP_Call_Test::create_prack()
{
    _prack_branch = "z9hG4bK" + String_Functions::random(10);

    std::string str;
    str  = "PRACK sip:bob@192.0.2.4 SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _prack_branch + "\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(++_client_sequence) + " PRACK\r\n";
    str += "RAck: " + std::to_string(_prack_rseq) + " " + std::to_string(_invite_sequence) + " INVITE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Call_Test::create_prack -> Failed to decode message\n";
        return NULL;
    }

    return request;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_prack_response_200()
{
    std::string str;
    str  = "SIP/2.0 200 OK\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _prack_branch + "\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " PRACK\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_prack_response_200 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Request *SIP_Call_Test::create_info()
{
    _info_branch = "z9hG4bK" + String_Functions::random(10);

    std::string str;
    str  = "INFO sip:bob@192.0.2.4 SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _info_branch + "\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(++_client_sequence) + " INFO\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Call_Test::create_info -> Failed to decode message\n";
        return NULL;
    }

    return request;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_info_response_200()
{
    std::string str;
    str  = "SIP/2.0 200 OK\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _info_branch + "\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " INFO\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_info_response_200 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Request *SIP_Call_Test::create_register()
{
    _register_branch = "z9hG4bK" + String_Functions::random(10);

    std::string str;
    str  = "REGISTER sip:bob@192.0.2.4 SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _register_branch + "\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Expires: 3600\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(++_client_sequence) + " REGISTER\r\n";
    str += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Call_Test::create_register -> Failed to decode message\n";
        return NULL;
    }

    return request;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_register_response_100()
{
    std::string str;
    str  = "SIP/2.0 100 Trying\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _register_branch + "\r\n";
    str += "To: Bob <sip:bob@biloxi.com>\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " REGISTER\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_register_response_100 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_register_response_200()
{
    std::string str;
    str  = "SIP/2.0 200 OK\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _register_branch + "\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Expires: 3600\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " REGISTER\r\n";
    str += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_register_response_200 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_register_response_401()
{
    std::string str;
    str  = "SIP/2.0 401 Unauthorized\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _register_branch + "\r\n";
    str += "To: Bob <sip:bob@biloxi.com>\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " REGISTER\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_register_response_401 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Request *SIP_Call_Test::create_options()
{
    _options_branch = "z9hG4bK" + String_Functions::random(10);

    std::string str;
    str  = "OPTIONS sip:bob@192.0.2.4 SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _options_branch + "\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(++_client_sequence) + " OPTIONS\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Call_Test::create_options -> Failed to decode message\n";
        return NULL;
    }

    return request;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_options_response_100()
{
    std::string str;
    str  = "SIP/2.0 100 Trying\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _options_branch + "\r\n";
    str += "To: Bob <sip:bob@biloxi.com>\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " OPTIONS\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_options_response_100 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Response *SIP_Call_Test::create_options_response_200()
{
    std::string str;
    str  = "SIP/2.0 200 OK\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=" + _options_branch + "\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " OPTIONS\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Call_Test::create_options_response_200 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call_Test::process_invite()
{
    SIP_Request *invite = create_invite();
    if (!invite)
    {
        std::cout << "SIP_Call_Test::process_invite -> Failed to create request\n";
        return false;
    }

    _sent_message = false;

    if (!_client_call.send_request(invite))
    {
        std::cout << "SIP_Call_Test::process_invite -> Failed to send request\n";
        delete invite;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_invite -> INVITE not sent\n";
        delete invite;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_CALLING_OUT)
    {
        std::cout << "SIP_Call_Test::process_invite -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CALLING_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete invite;
        return false;
    }

    if (_client_call.get_client_dialog(invite))
    {
        std::cout << "SIP_Call_Test::process_invite -> Invalid client dialog\n";
        delete invite;
        return false;
    }

    _received_request = false;

    if (!_server_call.receive_request(invite))
    {
        std::cout << "SIP_Call_Test::process_invite -> Failed to receive request\n";
        delete invite;
        return false;
    }

    if (!_received_request)
    {
        std::cout << "SIP_Call_Test::process_invite -> INVITE not received\n";
        delete invite;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_CALLING_IN)
    {
        std::cout << "SIP_Call_Test::process_invite -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CALLING_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete invite;
        return false;
    }

    if (_server_call.get_server_dialog(invite))
    {
        std::cout << "SIP_Call_Test::process_invite -> Invalid server dialog\n";
        delete invite;
        return false;
    }

    delete invite;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_invite_response_100()
{
    SIP_Response *invite_response_100 = create_invite_response_100();
    if (!invite_response_100)
    {
        std::cout << "SIP_Call_Test::process_invite_response_100 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(invite_response_100))
    {
        std::cout << "SIP_Call_Test::process_invite_response_100 -> Failed to send response\n";
        delete invite_response_100;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_invite_response_100 -> Response not sent\n";
        delete invite_response_100;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_RINGING_IN)
    {
        std::cout << "SIP_Call_Test::process_invite_response_100 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_RINGING_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete invite_response_100;
        return false;
    }

    if (_server_call.get_server_dialog(invite_response_100))
    {
        std::cout << "SIP_Call_Test::process_invite_response_100 -> Invalid server response dialog\n";
        delete invite_response_100;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(invite_response_100))
    {
        std::cout << "SIP_Call_Test::process_invite_response_100 -> Failed to receive response\n";
        delete invite_response_100;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_invite_response_100 -> Response not received\n";
        delete invite_response_100;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_RINGING_OUT)
    {
        std::cout << "SIP_Call_Test::process_invite_response_100 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_RINGING_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete invite_response_100;
        return false;
    }

    if (_client_call.get_client_dialog(invite_response_100))
    {
        std::cout << "SIP_Call_Test::process_invite_response_100 -> Invalid client response dialog\n";
        delete invite_response_100;
        return false;
    }

    delete invite_response_100;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_invite_response_180()
{
    SIP_Response *invite_response_180 = create_invite_response_180();
    if (!invite_response_180)
    {
        std::cout << "SIP_Call_Test::process_invite_response_180 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(invite_response_180))
    {
        std::cout << "SIP_Call_Test::process_invite_response_180 -> Failed to send response\n";
        delete invite_response_180;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_invite_response_180 -> Response not sent\n";
        delete invite_response_180;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_RINGING_IN)
    {
        std::cout << "SIP_Call_Test::process_invite_response_180 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_RINGING_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete invite_response_180;
        return false;
    }

    if (!_server_call.get_server_dialog(invite_response_180))
    {
        std::cout << "SIP_Call_Test::process_invite_response_180 -> Invalid server response dialog\n";
        delete invite_response_180;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(invite_response_180))
    {
        std::cout << "SIP_Call_Test::process_invite_response_180 -> Failed to receive response\n";
        delete invite_response_180;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_invite_response_180 -> Response not received\n";
        delete invite_response_180;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_RINGING_OUT)
    {
        std::cout << "SIP_Call_Test::process_invite_response_180 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_RINGING_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete invite_response_180;
        return false;
    }

    if (!_client_call.get_client_dialog(invite_response_180))
    {
        std::cout << "SIP_Call_Test::process_invite_response_180 -> Invalid client response dialog\n";
        delete invite_response_180;
        return false;
    }

    delete invite_response_180;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_invite_response_183()
{
    SIP_Response *invite_response_183 = create_invite_response_183();
    if (!invite_response_183)
    {
        std::cout << "SIP_Call_Test::process_invite_response_183 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(invite_response_183))
    {
        std::cout << "SIP_Call_Test::process_invite_response_183 -> Failed to send response\n";
        delete invite_response_183;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_invite_response_183 -> Response not sent\n";
        delete invite_response_183;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_RINGING_IN)
    {
        std::cout << "SIP_Call_Test::process_invite_response_183 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_RINGING_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete invite_response_183;
        return false;
    }

    if (!_server_call.get_server_dialog(invite_response_183))
    {
        std::cout << "SIP_Call_Test::process_invite_response_183 -> Invalid server response dialog\n";
        delete invite_response_183;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(invite_response_183))
    {
        std::cout << "SIP_Call_Test::process_invite_response_183 -> Failed to receive response\n";
        delete invite_response_183;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_invite_response_183 -> Response not received\n";
        delete invite_response_183;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_RINGING_OUT)
    {
        std::cout << "SIP_Call_Test::process_invite_response_183 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_RINGING_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete invite_response_183;
        return false;
    }

    if (!_client_call.get_client_dialog(invite_response_183))
    {
        std::cout << "SIP_Call_Test::process_invite_response_183 -> Invalid client response dialog\n";
        delete invite_response_183;
        return false;
    }

    delete invite_response_183;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_invite_response_200()
{
    SIP_Response *invite_response_200 = create_invite_response_200();
    if (!invite_response_200)
    {
        std::cout << "SIP_Call_Test::process_invite_response_200 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(invite_response_200))
    {
        std::cout << "SIP_Call_Test::process_invite_response_200 -> Failed to send response\n";
        delete invite_response_200;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_invite_response_200 -> Response not sent\n";
        delete invite_response_200;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_WAITING_ACK_IN)
    {
        std::cout << "SIP_Call_Test::process_invite_response_200 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_WAITING_ACK_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete invite_response_200;
        return false;
    }

    if (!_server_call.get_server_dialog(invite_response_200))
    {
        std::cout << "SIP_Call_Test::process_invite_response_200 -> Invalid server response dialog\n";
        delete invite_response_200;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(invite_response_200))
    {
        std::cout << "SIP_Call_Test::process_invite_response_200 -> Failed to receive response\n";
        delete invite_response_200;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_invite_response_200 -> Response not received\n";
        delete invite_response_200;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_WAITING_ACK_OUT)
    {
        std::cout << "SIP_Call_Test::process_invite_response_200 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_WAITING_ACK_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete invite_response_200;
        return false;
    }

    if (!_client_call.get_client_dialog(invite_response_200))
    {
        std::cout << "SIP_Call_Test::process_invite_response_200 -> Invalid client response dialog\n";
        delete invite_response_200;
        return false;
    }

    delete invite_response_200;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_invite_response_480()
{
    SIP_Response *invite_response_480 = create_invite_response_480();
    if (!invite_response_480)
    {
        std::cout << "SIP_Call_Test::process_invite_response_480 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(invite_response_480))
    {
        std::cout << "SIP_Call_Test::process_invite_response_480 -> Failed to send response\n";
        delete invite_response_480;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_invite_response_480 -> Response not sent\n";
        delete invite_response_480;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_CLOSED)
    {
        std::cout << "SIP_Call_Test::process_invite_response_480 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSED << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete invite_response_480;
        return false;
    }

    if (_server_call.get_server_dialog(invite_response_480))
    {
        std::cout << "SIP_Call_Test::process_invite_response_480 -> Invalid server response dialog\n";
        delete invite_response_480;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(invite_response_480))
    {
        std::cout << "SIP_Call_Test::process_invite_response_480 -> Failed to receive response\n";
        delete invite_response_480;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_invite_response_480 -> Response not received\n";
        delete invite_response_480;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_CLOSED)
    {
        std::cout << "SIP_Call_Test::process_invite_response_480 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSED << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete invite_response_480;
        return false;
    }

    if (_client_call.get_client_dialog(invite_response_480))
    {
        std::cout << "SIP_Call_Test::process_invite_response_480 -> Invalid client response dialog\n";
        delete invite_response_480;
        return false;
    }

    delete invite_response_480;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_invite_response_487()
{
    SIP_Response *invite_response_487 = create_invite_response_487();
    if (!invite_response_487)
    {
        std::cout << "SIP_Call_Test::process_invite_response_487 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(invite_response_487))
    {
        std::cout << "SIP_Call_Test::process_invite_response_487 -> Failed to send response\n";
        delete invite_response_487;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_invite_response_487 -> Response not sent\n";
        delete invite_response_487;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_CLOSED)
    {
        std::cout << "SIP_Call_Test::process_invite_response_487 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSED << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete invite_response_487;
        return false;
    }

    if (_server_call.get_server_dialog(invite_response_487))
    {
        std::cout << "SIP_Call_Test::process_invite_response_487 -> Invalid server response dialog\n";
        delete invite_response_487;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(invite_response_487))
    {
        std::cout << "SIP_Call_Test::process_invite_response_487 -> Failed to receive response\n";
        delete invite_response_487;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_invite_response_487 -> Response not received\n";
        delete invite_response_487;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_CLOSED)
    {
        std::cout << "SIP_Call_Test::process_invite_response_487 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSED << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete invite_response_487;
        return false;
    }

    if (_client_call.get_client_dialog(invite_response_487))
    {
        std::cout << "SIP_Call_Test::process_invite_response_487 -> Invalid client response dialog\n";
        delete invite_response_487;
        return false;
    }

    delete invite_response_487;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_ack()
{
    SIP_Request *ack = create_ack();
    if (!ack)
    {
        std::cout << "SIP_Call_Test::process_ack -> Failed to create request\n";
        return false;
    }

    _sent_message = false;

    if (!_client_call.send_request(ack))
    {
        std::cout << "SIP_Call_Test::process_ack -> Failed to send request\n";
        delete ack;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_ack -> ACK not sent\n";
        delete ack;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_ACTIVE)
    {
        std::cout << "SIP_Call_Test::process_ack -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_ACTIVE << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete ack;
        return false;
    }

    if (!_client_call.get_client_dialog(ack))
    {
        std::cout << "SIP_Call_Test::process_ack -> Invalid client dialog\n";
        delete ack;
        return false;
    }

    _received_request = false;

    if (!_server_call.receive_request(ack))
    {
        std::cout << "SIP_Call_Test::process_ack -> Failed to receive request\n";
        delete ack;
        return false;
    }

    if (!_received_request)
    {
        std::cout << "SIP_Call_Test::process_ack -> Failed to receive ACK\n";
        delete ack;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_ACTIVE)
    {
        std::cout << "SIP_Call_Test::process_ack -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_ACTIVE << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete ack;
        return false;
    }

    if (!_server_call.get_server_dialog(ack))
    {
        std::cout << "SIP_Call_Test::process_ack -> Invalid server dialog\n";
        delete ack;
        return false;
    }

    delete ack;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_client_bye()
{
    SIP_Request *bye = create_client_bye();
    if (!bye)
    {
        std::cout << "SIP_Call_Test::process_client_bye -> Failed to create request\n";
        return false;
    }

    _sent_message = false;

    if (!_client_call.send_request(bye))
    {
        std::cout << "SIP_Call_Test::process_client_bye -> Failed to send request\n";
        delete bye;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_client_bye -> BYE not sent\n";
        delete bye;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_CLOSING_OUT)
    {
        std::cout << "SIP_Call_Test::process_client_bye -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSING_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete bye;
        return false;
    }

    if (!_client_call.get_client_dialog(bye))
    {
        std::cout << "SIP_Call_Test::process_client_bye -> Invalid client dialog\n";
        delete bye;
        return false;
    }

    _received_request = false;

    if (!_server_call.receive_request(bye))
    {
        std::cout << "SIP_Call_Test::process_client_bye -> Failed to receive request\n";
        delete bye;
        return false;
    }

    if (!_received_request)
    {
        std::cout << "SIP_Call_Test::process_client_bye -> Failed to receive BYE\n";
        delete bye;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_CLOSING_IN)
    {
        std::cout << "SIP_Call_Test::process_client_bye -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSING_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete bye;
        return false;
    }

    if (!_server_call.get_server_dialog(bye))
    {
        std::cout << "SIP_Call_Test::process_client_bye -> Invalid server dialog\n";
        delete bye;
        return false;
    }

    delete bye;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_server_bye_response_200()
{
    SIP_Response *bye_response_200 = create_server_bye_response_200();
    if (!bye_response_200)
    {
        std::cout << "SIP_Call_Test::process_server_bye_response_200 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(bye_response_200))
    {
        std::cout << "SIP_Call_Test::process_server_bye_response_200 -> Failed to send response\n";
        delete bye_response_200;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_server_bye_response_200 -> Response not sent\n";
        delete bye_response_200;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_CLOSED)
    {
        std::cout << "SIP_Call_Test::process_server_bye_response_200 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSED << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete bye_response_200;
        return false;
    }

    if (_server_call.get_server_dialog(bye_response_200))
    {
        std::cout << "SIP_Call_Test::process_server_bye_response_200 -> Invalid server response dialog\n";
        delete bye_response_200;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(bye_response_200))
    {
        std::cout << "SIP_Call_Test::process_server_bye_response_200 -> Failed to receive response\n";
        delete bye_response_200;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_server_bye_response_200 -> Response not received\n";
        delete bye_response_200;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_CLOSED)
    {
        std::cout << "SIP_Call_Test::process_server_bye_response_200 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSED << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete bye_response_200;
        return false;
    }

    if (_client_call.get_client_dialog(bye_response_200))
    {
        std::cout << "SIP_Call_Test::process_server_bye_response_200 -> Invalid client response dialog\n";
        delete bye_response_200;
        return false;
    }

    delete bye_response_200;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_server_bye()
{
    SIP_Request *bye = create_server_bye();
    if (!bye)
    {
        std::cout << "SIP_Call_Test::process_server_bye -> Failed to create request\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_request(bye))
    {
        std::cout << "SIP_Call_Test::process_server_bye -> Failed to send request\n";
        delete bye;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_server_bye -> BYE not sent\n";
        delete bye;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_CLOSING_OUT)
    {
        std::cout << "SIP_Call_Test::process_server_bye -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSING_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete bye;
        return false;
    }

    if (!_server_call.get_client_dialog(bye))
    {
        std::cout << "SIP_Call_Test::process_server_bye -> Invalid server dialog\n";
        delete bye;
        return false;
    }

    _received_request = false;

    if (!_client_call.receive_request(bye))
    {
        std::cout << "SIP_Call_Test::process_server_bye -> Failed to receive request\n";
        delete bye;
        return false;
    }

    if (!_received_request)
    {
        std::cout << "SIP_Call_Test::process_server_bye -> Failed to receive BYE\n";
        delete bye;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_CLOSING_IN)
    {
        std::cout << "SIP_Call_Test::process_server_bye -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSING_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete bye;
        return false;
    }

    if (!_client_call.get_server_dialog(bye))
    {
        std::cout << "SIP_Call_Test::process_server_bye -> Invalid client dialog\n";
        delete bye;
        return false;
    }

    delete bye;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_client_bye_response_200()
{
    SIP_Response *bye_response_200 = create_client_bye_response_200();
    if (!bye_response_200)
    {
        std::cout << "SIP_Call_Test::process_client_bye_response_200 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_client_call.send_response(bye_response_200))
    {
        std::cout << "SIP_Call_Test::process_client_bye_response_200 -> Failed to send response\n";
        delete bye_response_200;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_client_bye_response_200 -> Response not sent\n";
        delete bye_response_200;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_CLOSED)
    {
        std::cout << "SIP_Call_Test::process_client_bye_response_200 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSED << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete bye_response_200;
        return false;
    }

    if (_client_call.get_server_dialog(bye_response_200))
    {
        std::cout << "SIP_Call_Test::process_client_bye_response_200 -> Invalid client response dialog\n";
        delete bye_response_200;
        return false;
    }

    _received_response = false;

    if (!_server_call.receive_response(bye_response_200))
    {
        std::cout << "SIP_Call_Test::process_client_bye_response_200 -> Failed to receive response\n";
        delete bye_response_200;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_client_bye_response_200 -> Response not received\n";
        delete bye_response_200;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_CLOSED)
    {
        std::cout << "SIP_Call_Test::process_client_bye_response_200 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSED << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete bye_response_200;
        return false;
    }

    if (_server_call.get_client_dialog(bye_response_200))
    {
        std::cout << "SIP_Call_Test::process_client_bye_response_200 -> Invalid server response dialog\n";
        delete bye_response_200;
        return false;
    }

    delete bye_response_200;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_client_update()
{
    SIP_Request *update = create_client_update();
    if (!update)
    {
        std::cout << "SIP_Call_Test::process_client_update -> Failed to create request\n";
        return false;
    }

    _sent_message = false;

    if (!_client_call.send_request(update))
    {
        std::cout << "SIP_Call_Test::process_client_update -> Failed to send request\n";
        delete update;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_client_update -> UPDATE not sent\n";
        delete update;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_RINGING_OUT)
    {
        std::cout << "SIP_Call_Test::process_client_update -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_RINGING_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete update;
        return false;
    }

    if (!_client_call.get_client_dialog(update))
    {
        std::cout << "SIP_Call_Test::process_client_update -> Invalid client dialog\n";
        delete update;
        return false;
    }

    _received_request = false;

    if (!_server_call.receive_request(update))
    {
        std::cout << "SIP_Call_Test::process_client_update -> Failed to receive request\n";
        delete update;
        return false;
    }

    if (!_received_request)
    {
        std::cout << "SIP_Call_Test::process_client_update -> UPDATE not received\n";
        delete update;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_RINGING_IN)
    {
        std::cout << "SIP_Call_Test::process_client_update -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_RINGING_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete update;
        return false;
    }

    if (!_server_call.get_server_dialog(update))
    {
        std::cout << "SIP_Call_Test::process_client_update -> Invalid server dialog\n";
        delete update;
        return false;
    }

    delete update;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_server_update_response_200()
{
    SIP_Response *update_response_200 = create_server_update_response_200();
    if (!update_response_200)
    {
        std::cout << "SIP_Call_Test::process_server_update_response_200 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(update_response_200))
    {
        std::cout << "SIP_Call_Test::process_server_update_response_200 -> Failed to send response\n";
        delete update_response_200;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_server_update_response_200 -> Response not sent\n";
        delete update_response_200;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_RINGING_IN)
    {
        std::cout << "SIP_Call_Test::process_server_update_response_200 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_RINGING_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete update_response_200;
        return false;
    }

    if (!_server_call.get_server_dialog(update_response_200))
    {
        std::cout << "SIP_Call_Test::process_server_update_response_200 -> Invalid server response dialog\n";
        delete update_response_200;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(update_response_200))
    {
        std::cout << "SIP_Call_Test::process_server_update_response_200 -> Failed to receive response\n";
        delete update_response_200;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_server_update_response_200 -> Response not sent\n";
        delete update_response_200;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_RINGING_OUT)
    {
        std::cout << "SIP_Call_Test::process_server_update_response_200 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_RINGING_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete update_response_200;
        return false;
    }

    if (!_client_call.get_client_dialog(update_response_200))
    {
        std::cout << "SIP_Call_Test::process_server_update_response_200 -> Invalid client response dialog\n";
        delete update_response_200;
        return false;
    }

    delete update_response_200;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_server_update()
{
    SIP_Request *update = create_server_update();
    if (!update)
    {
        std::cout << "SIP_Call_Test::process_server_update -> Failed to create request\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_request(update))
    {
        std::cout << "SIP_Call_Test::process_server_update -> Failed to send request\n";
        delete update;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_server_update -> UPDATE not sent\n";
        delete update;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_RINGING_IN)
    {
        std::cout << "SIP_Call_Test::process_server_update -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_RINGING_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete update;
        return false;
    }

    if (!_server_call.get_client_dialog(update))
    {
        std::cout << "SIP_Call_Test::process_server_update -> Invalid server dialog\n";
        delete update;
        return false;
    }

    _received_request = false;

    if (!_client_call.receive_request(update))
    {
        std::cout << "SIP_Call_Test::process_server_update -> Failed to receive request\n";
        delete update;
        return false;
    }

    if (!_received_request)
    {
        std::cout << "SIP_Call_Test::process_server_update -> UPDATE not received\n";
        delete update;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_RINGING_OUT)
    {
        std::cout << "SIP_Call_Test::process_server_update -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_RINGING_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete update;
        return false;
    }

    if (!_client_call.get_server_dialog(update))
    {
        std::cout << "SIP_Call_Test::process_server_update -> Invalid client dialog\n";
        delete update;
        return false;
    }

    delete update;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_client_update_response_200()
{
    SIP_Response *update_response_200 = create_client_update_response_200();
    if (!update_response_200)
    {
        std::cout << "SIP_Call_Test::process_client_update_response_200 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_client_call.send_response(update_response_200))
    {
        std::cout << "SIP_Call_Test::process_client_update_response_200 -> Failed to send response\n";
        delete update_response_200;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_client_update_response_200 -> Response not sent\n";
        delete update_response_200;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_RINGING_OUT)
    {
        std::cout << "SIP_Call_Test::process_client_update_response_200 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_RINGING_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete update_response_200;
        return false;
    }

    if (!_client_call.get_server_dialog(update_response_200))
    {
        std::cout << "SIP_Call_Test::process_client_update_response_200 -> Invalid client response dialog\n";
        delete update_response_200;
        return false;
    }

    _received_response = false;

    if (!_server_call.receive_response(update_response_200))
    {
        std::cout << "SIP_Call_Test::process_client_update_response_200 -> Failed to receive response\n";
        delete update_response_200;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_client_update_response_200 -> Response not received\n";
        delete update_response_200;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_RINGING_IN)
    {
        std::cout << "SIP_Call_Test::process_client_update_response_200 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_RINGING_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete update_response_200;
        return false;
    }

    if (!_server_call.get_client_dialog(update_response_200))
    {
        std::cout << "SIP_Call_Test::process_client_update_response_200 -> Invalid server response dialog\n";
        delete update_response_200;
        return false;
    }

    delete update_response_200;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_cancel()
{
    SIP_Request *cancel = create_cancel();
    if (!cancel)
    {
        std::cout << "SIP_Call_Test::process_cancel -> Failed to create request\n";
        return false;
    }

    _sent_message = false;

    if (!_client_call.send_request(cancel))
    {
        std::cout << "SIP_Call_Test::process_cancel -> Failed to send request\n";
        delete cancel;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_cancel -> CANCEL not sent\n";
        delete cancel;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_CANCELING_OUT)
    {
        std::cout << "SIP_Call_Test::process_cancel -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CANCELING_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete cancel;
        return false;
    }

    if (!_client_call.get_client_dialog(cancel))
    {
        std::cout << "SIP_Call_Test::process_cancel -> Invalid client dialog\n";
        delete cancel;
        return false;
    }

    _received_request = false;

    if (!_server_call.receive_request(cancel))
    {
        std::cout << "SIP_Call_Test::process_cancel -> Failed to receive request\n";
        delete cancel;
        return false;
    }

    if (!_received_request)
    {
        std::cout << "SIP_Call_Test::process_cancel -> Failed to receive CANCEL\n";
        delete cancel;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_CANCELING_IN)
    {
        std::cout << "SIP_Call_Test::process_cancel -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CANCELING_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete cancel;
        return false;
    }

    if (!_server_call.get_server_dialog(cancel))
    {
        std::cout << "SIP_Call_Test::process_cancel -> Invalid server dialog\n";
        delete cancel;
        return false;
    }

    delete cancel;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_cancel_response_200()
{
    SIP_Response *cancel_response_200 = create_cancel_response_200();
    if (!cancel_response_200)
    {
        std::cout << "SIP_Call_Test::process_cancel_response_200 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(cancel_response_200))
    {
        std::cout << "SIP_Call_Test::process_cancel_response_200 -> Failed to send response\n";
        delete cancel_response_200;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_cancel_response_200 -> Response not sent\n";
        delete cancel_response_200;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_CANCELED_IN)
    {
        std::cout << "SIP_Call_Test::process_cancel_response_200 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CANCELED_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete cancel_response_200;
        return false;
    }

    if (!_server_call.get_server_dialog(cancel_response_200))
    {
        std::cout << "SIP_Call_Test::process_cancel_response_200 -> Invalid server response dialog\n";
        delete cancel_response_200;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(cancel_response_200))
    {
        std::cout << "SIP_Call_Test::process_cancel_response_200 -> Failed to receive response\n";
        delete cancel_response_200;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_cancel_response_200 -> Response not received\n";
        delete cancel_response_200;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_CANCELED_OUT)
    {
        std::cout << "SIP_Call_Test::process_cancel_response_200 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CANCELED_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete cancel_response_200;
        return false;
    }

    if (!_client_call.get_client_dialog(cancel_response_200))
    {
        std::cout << "SIP_Call_Test::process_cancel_response_200 -> Invalid client response dialog\n";
        delete cancel_response_200;
        return false;
    }

    delete cancel_response_200;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_prack()
{
    SIP_Request *prack = create_prack();
    if (!prack)
    {
        std::cout << "SIP_Call_Test::process_prack -> Failed to create request\n";
        return false;
    }

    _sent_message = false;

    if (!_client_call.send_request(prack))
    {
        std::cout << "SIP_Call_Test::process_prack -> Failed to send request\n";
        delete prack;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_prack -> PRACK not sent\n";
        delete prack;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_RINGING_OUT)
    {
        std::cout << "SIP_Call_Test::process_prack -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_ACTIVE << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete prack;
        return false;
    }

    if (!_client_call.get_client_dialog(prack))
    {
        std::cout << "SIP_Call_Test::process_prack -> Invalid client dialog\n";
        delete prack;
        return false;
    }

    _received_request = false;

    if (!_server_call.receive_request(prack))
    {
        std::cout << "SIP_Call_Test::process_prack -> Failed to receive request\n";
        delete prack;
        return false;
    }

    if (!_received_request)
    {
        std::cout << "SIP_Call_Test::process_prack -> Failed to receive PRACK\n";
        delete prack;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_RINGING_IN)
    {
        std::cout << "SIP_Call_Test::process_prack -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_ACTIVE << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete prack;
        return false;
    }

    if (!_server_call.get_server_dialog(prack))
    {
        std::cout << "SIP_Call_Test::process_prack -> Invalid server dialog\n";
        delete prack;
        return false;
    }

    delete prack;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_prack_response_200()
{
    SIP_Response *prack_response_200 = create_prack_response_200();
    if (!prack_response_200)
    {
        std::cout << "SIP_Call_Test::process_prack_response_200 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(prack_response_200))
    {
        std::cout << "SIP_Call_Test::process_prack_response_200 -> Failed to send response\n";
        delete prack_response_200;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_prack_response_200 -> Response not sent\n";
        delete prack_response_200;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_RINGING_IN)
    {
        std::cout << "SIP_Call_Test::process_prack_response_200 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_ACTIVE << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete prack_response_200;
        return false;
    }

    if (!_server_call.get_server_dialog(prack_response_200))
    {
        std::cout << "SIP_Call_Test::process_prack_response_200 -> Invalid server response dialog\n";
        delete prack_response_200;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(prack_response_200))
    {
        std::cout << "SIP_Call_Test::process_prack_response_200 -> Failed to receive response\n";
        delete prack_response_200;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_prack_response_200 -> Response not received\n";
        delete prack_response_200;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_RINGING_OUT)
    {
        std::cout << "SIP_Call_Test::process_prack_response_200 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_ACTIVE << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete prack_response_200;
        return false;
    }

    if (!_client_call.get_client_dialog(prack_response_200))
    {
        std::cout << "SIP_Call_Test::process_prack_response_200 -> Invalid client response dialog\n";
        delete prack_response_200;
        return false;
    }

    delete prack_response_200;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_info()
{
    SIP_Request *info = create_info();
    if (!info)
    {
        std::cout << "SIP_Call_Test::process_info -> Failed to create request\n";
        return false;
    }

    _sent_message = false;

    if (!_client_call.send_request(info))
    {
        std::cout << "SIP_Call_Test::process_info -> Failed to send request\n";
        delete info;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_info -> INFO not sent\n";
        delete info;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_ACTIVE)
    {
        std::cout << "SIP_Call_Test::process_info -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_ACTIVE << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete info;
        return false;
    }

    if (!_client_call.get_client_dialog(info))
    {
        std::cout << "SIP_Call_Test::process_info -> Invalid client dialog\n";
        delete info;
        return false;
    }

    _received_request = false;

    if (!_server_call.receive_request(info))
    {
        std::cout << "SIP_Call_Test::process_info -> Failed to receive request\n";
        delete info;
        return false;
    }

    if (!_received_request)
    {
        std::cout << "SIP_Call_Test::process_info -> INFO not received\n";
        delete info;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_ACTIVE)
    {
        std::cout << "SIP_Call_Test::process_info -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_ACTIVE << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete info;
        return false;
    }

    if (!_server_call.get_server_dialog(info))
    {
        std::cout << "SIP_Call_Test::process_info -> Invalid server dialog\n";
        delete info;
        return false;
    }

    delete info;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_info_response_200()
{
    SIP_Response *info_response_200 = create_info_response_200();
    if (!info_response_200)
    {
        std::cout << "SIP_Call_Test::process_info_response_200 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(info_response_200))
    {
        std::cout << "SIP_Call_Test::process_info_response_200 -> Failed to send response\n";
        delete info_response_200;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_info_response_200 -> Response not sent\n";
        delete info_response_200;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_ACTIVE)
    {
        std::cout << "SIP_Call_Test::process_info_response_200 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_ACTIVE << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete info_response_200;
        return false;
    }

    if (!_server_call.get_server_dialog(info_response_200))
    {
        std::cout << "SIP_Call_Test::process_info_response_200 -> Invalid server response dialog\n";
        delete info_response_200;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(info_response_200))
    {
        std::cout << "SIP_Call_Test::process_info_response_200 -> Failed to receive response\n";
        delete info_response_200;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_info_response_200 -> Response not received\n";
        delete info_response_200;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_ACTIVE)
    {
        std::cout << "SIP_Call_Test::process_info_response_200 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_ACTIVE << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete info_response_200;
        return false;
    }

    if (!_client_call.get_client_dialog(info_response_200))
    {
        std::cout << "SIP_Call_Test::process_info_response_200 -> Invalid client response dialog\n";
        delete info_response_200;
        return false;
    }

    delete info_response_200;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_register()
{
    SIP_Request *request = create_register();
    if (!request)
    {
        std::cout << "SIP_Call_Test::process_register -> Failed to create request\n";
        return false;
    }

    _sent_message = false;

    if (!_client_call.send_request(request))
    {
        std::cout << "SIP_Call_Test::process_register -> Failed to send request\n";
        delete request;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_register -> REGISTER not sent\n";
        delete request;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_REGISTER_OUT)
    {
        std::cout << "SIP_Call_Test::process_register -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_REGISTER_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete request;
        return false;
    }

    if (_client_call.get_client_dialog(request))
    {
        std::cout << "SIP_Call_Test::process_register -> Invalid client dialog\n";
        delete request;
        return false;
    }

    _received_request = false;

    if (!_server_call.receive_request(request))
    {
        std::cout << "SIP_Call_Test::process_register -> Failed to receive request\n";
        delete request;
        return false;
    }

    if (!_received_request)
    {
        std::cout << "SIP_Call_Test::process_register -> REGISTER not received\n";
        delete request;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_REGISTER_IN)
    {
        std::cout << "SIP_Call_Test::process_register -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_REGISTER_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete request;
        return false;
    }

    if (_server_call.get_server_dialog(request))
    {
        std::cout << "SIP_Call_Test::process_register -> Invalid server dialog\n";
        delete request;
        return false;
    }

    delete request;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_register_response_100()
{
    SIP_Response *register_response_100 = create_register_response_100();
    if (!register_response_100)
    {
        std::cout << "SIP_Call_Test::process_register_response_100 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(register_response_100))
    {
        std::cout << "SIP_Call_Test::process_register_response_100 -> Failed to send response\n";
        delete register_response_100;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_register_response_100 -> Response not sent\n";
        delete register_response_100;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_REGISTER_IN)
    {
        std::cout << "SIP_Call_Test::process_register_response_100 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_REGISTER_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete register_response_100;
        return false;
    }

    if (_server_call.get_server_dialog(register_response_100))
    {
        std::cout << "SIP_Call_Test::process_register_response_100 -> Invalid server response dialog\n";
        delete register_response_100;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(register_response_100))
    {
        std::cout << "SIP_Call_Test::process_register_response_100 -> Failed to receive response\n";
        delete register_response_100;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_register_response_100 -> Response not received\n";
        delete register_response_100;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_REGISTER_OUT)
    {
        std::cout << "SIP_Call_Test::process_register_response_100 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_REGISTER_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete register_response_100;
        return false;
    }

    if (_client_call.get_client_dialog(register_response_100))
    {
        std::cout << "SIP_Call_Test::process_register_response_100 -> Invalid client response dialog\n";
        delete register_response_100;
        return false;
    }

    delete register_response_100;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_register_response_200()
{
    SIP_Response *register_response_200 = create_register_response_200();
    if (!register_response_200)
    {
        std::cout << "SIP_Call_Test::process_register_response_200 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(register_response_200))
    {
        std::cout << "SIP_Call_Test::process_register_response_200 -> Failed to send response\n";
        delete register_response_200;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_register_response_200 -> Response not sent\n";
        delete register_response_200;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_CLOSED)
    {
        std::cout << "SIP_Call_Test::process_register_response_200 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSED << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete register_response_200;
        return false;
    }

    if (_server_call.get_server_dialog(register_response_200))
    {
        std::cout << "SIP_Call_Test::process_register_response_200 -> Invalid server response dialog\n";
        delete register_response_200;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(register_response_200))
    {
        std::cout << "SIP_Call_Test::process_register_response_200 -> Failed to receive response\n";
        delete register_response_200;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_register_response_200 -> Response not received\n";
        delete register_response_200;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_CLOSED)
    {
        std::cout << "SIP_Call_Test::process_register_response_200 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSED << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete register_response_200;
        return false;
    }

    if (_client_call.get_client_dialog(register_response_200))
    {
        std::cout << "SIP_Call_Test::process_register_response_200 -> Invalid client response dialog\n";
        delete register_response_200;
        return false;
    }

    delete register_response_200;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_register_response_401()
{
    SIP_Response *register_response_401 = create_register_response_401();
    if (!register_response_401)
    {
        std::cout << "SIP_Call_Test::process_register_response_401 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(register_response_401))
    {
        std::cout << "SIP_Call_Test::process_register_response_401 -> Failed to send response\n";
        delete register_response_401;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_register_response_401 -> Response not sent\n";
        delete register_response_401;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_CLOSED)
    {
        std::cout << "SIP_Call_Test::process_register_response_401 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSED << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete register_response_401;
        return false;
    }

    if (_server_call.get_server_dialog(register_response_401))
    {
        std::cout << "SIP_Call_Test::process_register_response_401 -> Invalid server response dialog\n";
        delete register_response_401;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(register_response_401))
    {
        std::cout << "SIP_Call_Test::process_register_response_401 -> Failed to receive response\n";
        delete register_response_401;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_register_response_401 -> Response not received\n";
        delete register_response_401;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_CLOSED)
    {
        std::cout << "SIP_Call_Test::process_register_response_401 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSED << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete register_response_401;
        return false;
    }

    if (_client_call.get_client_dialog(register_response_401))
    {
        std::cout << "SIP_Call_Test::process_register_response_401 -> Invalid client response dialog\n";
        delete register_response_401;
        return false;
    }

    delete register_response_401;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_options()
{
    SIP_Request *options = create_options();
    if (!options)
    {
        std::cout << "SIP_Call_Test::process_options -> Failed to create request\n";
        return false;
    }

    _sent_message = false;

    if (!_client_call.send_request(options))
    {
        std::cout << "SIP_Call_Test::process_options -> Failed to send request\n";
        delete options;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_options -> OPTIONS not sent\n";
        delete options;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_OPTIONS_OUT)
    {
        std::cout << "SIP_Call_Test::process_options -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_OPTIONS_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete options;
        return false;
    }

    if (_client_call.get_client_dialog(options))
    {
        std::cout << "SIP_Call_Test::process_options -> Invalid client dialog\n";
        delete options;
        return false;
    }

    _received_request = false;

    if (!_server_call.receive_request(options))
    {
        std::cout << "SIP_Call_Test::process_options -> Failed to receive request\n";
        delete options;
        return false;
    }

    if (!_received_request)
    {
        std::cout << "SIP_Call_Test::process_options -> OPTIONS not received\n";
        delete options;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_OPTIONS_IN)
    {
        std::cout << "SIP_Call_Test::process_options -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_OPTIONS_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete options;
        return false;
    }

    if (_server_call.get_server_dialog(options))
    {
        std::cout << "SIP_Call_Test::process_options -> Invalid server dialog\n";
        delete options;
        return false;
    }

    delete options;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_options_response_100()
{
    SIP_Response *options_response_100 = create_options_response_100();
    if (!options_response_100)
    {
        std::cout << "SIP_Call_Test::process_options_response_100 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(options_response_100))
    {
        std::cout << "SIP_Call_Test::process_options_response_100 -> Failed to send response\n";
        delete options_response_100;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_options_response_100 -> Response not sent\n";
        delete options_response_100;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_OPTIONS_IN)
    {
        std::cout << "SIP_Call_Test::process_options_response_100 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_OPTIONS_IN << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete options_response_100;
        return false;
    }

    if (_server_call.get_server_dialog(options_response_100))
    {
        std::cout << "SIP_Call_Test::process_options_response_100 -> Invalid server response dialog\n";
        delete options_response_100;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(options_response_100))
    {
        std::cout << "SIP_Call_Test::process_options_response_100 -> Failed to receive response\n";
        delete options_response_100;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_options_response_100 -> Response not received\n";
        delete options_response_100;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_OPTIONS_OUT)
    {
        std::cout << "SIP_Call_Test::process_options_response_100 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_OPTIONS_OUT << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete options_response_100;
        return false;
    }

    if (_client_call.get_client_dialog(options_response_100))
    {
        std::cout << "SIP_Call_Test::process_options_response_100 -> Invalid client response dialog\n";
        delete options_response_100;
        return false;
    }

    delete options_response_100;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_options_response_200()
{
    SIP_Response *options_response_200 = create_options_response_200();
    if (!options_response_200)
    {
        std::cout << "SIP_Call_Test::process_options_response_200 -> Failed to create response\n";
        return false;
    }

    _sent_message = false;

    if (!_server_call.send_response(options_response_200))
    {
        std::cout << "SIP_Call_Test::process_options_response_200 -> Failed to send response\n";
        delete options_response_200;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Call_Test::process_options_response_200 -> Response not sent\n";
        delete options_response_200;
        return false;
    }

    if (_server_call.get_state() != SIP_Call::STATE_CLOSED)
    {
        std::cout << "SIP_Call_Test::process_options_response_200 -> Invalid server call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSED << "\n";
        std::cout << std::setw(12) << "State: " << _server_call.get_state() << "\n";
        delete options_response_200;
        return false;
    }

    if (_server_call.get_server_dialog(options_response_200))
    {
        std::cout << "SIP_Call_Test::process_options_response_200 -> Invalid server response dialog\n";
        delete options_response_200;
        return false;
    }

    _received_response = false;

    if (!_client_call.receive_response(options_response_200))
    {
        std::cout << "SIP_Call_Test::process_options_response_200 -> Failed to receive response\n";
        delete options_response_200;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Call_Test::process_options_response_200 -> Response not received\n";
        delete options_response_200;
        return false;
    }

    if (_client_call.get_state() != SIP_Call::STATE_CLOSED)
    {
        std::cout << "SIP_Call_Test::process_options_response_200 -> Invalid client call state:\n";
        std::cout << std::setw(12) << "Expected: " << SIP_Call::STATE_CLOSED << "\n";
        std::cout << std::setw(12) << "State: " << _client_call.get_state() << "\n";
        delete options_response_200;
        return false;
    }

    if (_client_call.get_client_dialog(options_response_200))
    {
        std::cout << "SIP_Call_Test::process_options_response_200 -> Invalid client response dialog\n";
        delete options_response_200;
        return false;
    }

    delete options_response_200;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call_Test::send_message_callback(void *data, SIP_Call *call, SIP_Message *msg)
{
    SIP_Call_Test *test = reinterpret_cast<SIP_Call_Test *>(data);
    if ((!test) || (!call) || (!msg))
    {
        std::cout << "SIP_Call_Test::send_message_callback -> Invalid parameters\n";
        return false;
    }

    test->_sent_message = true;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::receive_request_callback(void *data, SIP_Call *call, SIP_Request *request)
{
    SIP_Call_Test *test = reinterpret_cast<SIP_Call_Test *>(data);
    if ((!test) || (!call) || (!request))
    {
        std::cout << "SIP_Call_Test::receive_request_callback -> Invalid parameters\n";
        return false;
    }

    test->_received_request = true;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::receive_response_callback(void *data, SIP_Call *call, SIP_Request *request, SIP_Response *response)
{
    SIP_Call_Test *test = reinterpret_cast<SIP_Call_Test *>(data);
    if ((!test) || (!call) || (!request) || (!response))
    {
        std::cout << "SIP_Call_Test::receive_response_callback -> Invalid parameters\n";
        return false;
    }

    test->_received_response = true;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call_Success_Test::run()
{
    set_callbacks();

    if (!process_invite())
        return false;

    if (!process_invite_response_100())
        return false;

    if (!process_invite_response_180())
        return false;

    if (!process_invite_response_183())
        return false;

    if (!process_invite_response_200())
        return false;

    if (!process_ack())
        return false;

    if (!process_info())
        return false;

    if (!process_info_response_200())
        return false;

    if (!process_client_bye())
        return false;

    if (!process_server_bye_response_200())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call_Success_No_100_Test::run()
{
    set_callbacks();

    if (!process_invite())
        return false;

    if (!process_invite_response_183())
        return false;

    if (!process_invite_response_200())
        return false;

    if (!process_ack())
        return false;

    if (!process_server_bye())
        return false;

    if (!process_client_bye_response_200())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call_Success_No_1xx_Test::run()
{
    set_callbacks();

    if (!process_invite())
        return false;

    if (!process_invite_response_200())
        return false;

    if (!process_ack())
        return false;

    if (!process_client_bye())
        return false;

    if (!process_server_bye_response_200())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call_Reject_Test::run()
{
    set_callbacks();

    if (!process_invite())
        return false;

    if (!process_invite_response_100())
        return false;

    if (!process_invite_response_180())
        return false;

    if (!process_invite_response_183())
        return false;

    if (!process_invite_response_480())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call_Reject_No_100_Test::run()
{
    set_callbacks();

    if (!process_invite())
        return false;

    if (!process_invite_response_183())
        return false;

    if (!process_invite_response_480())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call_Reject_No_1xx_Test::run()
{
    set_callbacks();

    if (!process_invite())
        return false;

    if (!process_invite_response_480())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call_Update_Test::run()
{
    set_callbacks();

    if (!process_invite())
        return false;

    if (!process_invite_response_100())
        return false;

    if (!process_invite_response_180())
        return false;

    if (!process_invite_response_183())
        return false;

    if (!process_client_update())
        return false;

    if (!process_server_update_response_200())
        return false;

    if (!process_server_update())
        return false;

    if (!process_client_update_response_200())
        return false;

    if (!process_invite_response_200())
        return false;

    if (!process_ack())
        return false;

    if (!process_client_bye())
        return false;

    if (!process_server_bye_response_200())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call_Cancel_Test::run()
{
    set_callbacks();

    if (!process_invite())
        return false;

    if (!process_invite_response_100())
        return false;

    if (!process_invite_response_180())
        return false;

    if (!process_invite_response_183())
        return false;

    if (!process_cancel())
        return false;

    if (!process_cancel_response_200())
        return false;

    if (!process_invite_response_487())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call_Prack_Test::run()
{
    set_callbacks();
    set_use_prack(true);

    if (!process_invite())
        return false;

    if (!process_invite_response_100())
        return false;

    if (!process_invite_response_180())
        return false;

    if (!process_prack())
        return false;

    if (!process_prack_response_200())
        return false;

    if (!process_invite_response_183())
        return false;

    if (!process_prack())
        return false;

    if (!process_prack_response_200())
        return false;

    if (!process_invite_response_200())
        return false;

    if (!process_ack())
        return false;

    if (!process_client_bye())
        return false;

    if (!process_server_bye_response_200())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call_Prack_No_100_Test::run()
{
    set_callbacks();
    set_use_prack(true);

    if (!process_invite())
        return false;

    if (!process_invite_response_180())
        return false;

    if (!process_prack())
        return false;

    if (!process_prack_response_200())
        return false;

    if (!process_invite_response_183())
        return false;

    if (!process_prack())
        return false;

    if (!process_prack_response_200())
        return false;

    if (!process_invite_response_200())
        return false;

    if (!process_ack())
        return false;

    if (!process_server_bye())
        return false;

    if (!process_client_bye_response_200())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call_Options_Test::run()
{
    set_callbacks();

    if (!process_options())
        return false;

    if (!process_options_response_200())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call_Options_With_100_Test::run()
{
    set_callbacks();

    if (!process_options())
        return false;

    if (!process_options_response_100())
        return false;

    if (!process_options_response_200())
        return false;

    return true;
}

//-------------------------------------------
