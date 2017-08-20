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

SIP_Call_Test::SIP_Call_Test() : use_prack(false), _client_sequence(314158), _server_sequence(230), _invite_sequence(0),
    _prack_rseq(988788), _invite(NULL), _bye(NULL), _update(NULL), _cancel(NULL), _prack(NULL), _info(NULL), _request(NULL),
    _response(NULL), _status_code(0)
{
}

//-------------------------------------------

SIP_Call_Test::~SIP_Call_Test()
{
    if (_invite)
        delete _invite;

    if (_bye)
        delete _bye;

    if (_update)
        delete _update;

    if (_cancel)
        delete _cancel;

    if (_info)
        delete _info;

    if (_request)
        delete _request;

    if (_response)
        delete _response;
}

//-------------------------------------------

bool SIP_Call_Test::init()
{
    std::cout << "SIP call test initialized\n";

    SIP_Call_Success_Test success_test;
    if (!success_test.run())
        return false;

    SIP_Call_Success_No_100_Test success_no_100_test;
    if (!success_no_100_test.run())
        return false;

    SIP_Call_Success_No_1xx_Test success_no_1xx_test;
    if (!success_no_1xx_test.run())
        return false;

    SIP_Call_Reject_Test reject_test;
    if (!reject_test.run())
        return false;

    std::cout << "SIP call test completed successfully\n";
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::init_call()
{
    _server_call.set_call_id(_call_id);
    _client_call.set_call_id(_call_id);
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::set_callbacks()
{
    _server_call.set_create_response_callback(create_response_callback, this);
    _server_call.set_send_response_callback(send_response_callback, this);
    _client_call.set_create_response_callback(create_response_callback, this);
    _client_call.set_send_response_callback(send_response_callback, this);
    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Request *SIP_Call_Test::create_invite()
{
    std::string str;
    str  = "INVITE sip:bob@biloxi.com SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
    str += "CSeq: " + std::to_string(++_client_sequence) + " INVITE\r\n";
    str += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    str += "Content-Length: 0\r\n";

    if (use_prack)
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
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " INVITE\r\n";
    str += "Contact: <sip:bob@192.0.2.4>\r\n";
    str += "Content-Length: 0\r\n";

    if (use_prack)
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
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
    str += "CSeq: " + std::to_string(_client_sequence) + " INVITE\r\n";
    str += "Contact: <sip:bob@192.0.2.4>\r\n";
    str += "Content-Length: 0\r\n";

    if (use_prack)
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
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    std::string str;
    str  = "ACK sip:bob@192.0.2.4 SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK798711\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    std::string str;
    str  = "BYE sip:bob@192.0.2.4 SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKjhfuosd\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKjhfuosd\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    std::string str;
    str  = "BYE sip:alice@pc33.atlanta.com SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP 192.0.2.4;branch=z9hG4bKiefjddf\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "From: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "To: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    str += "Via: SIP/2.0/UDP 192.0.2.4;branch=z9hG4bKiefjddf\r\n";
    str += "From: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "To: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    std::string str;
    str  = "UPDATE sip:bob@192.0.2.4 SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKoi900ks\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKoi900ks\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    std::string str;
    str  = "UPDATE sip:alice@pc33.atlanta.com SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP 192.0.2.4;branch=z9hG4bKppi56f\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "From: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "To: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    str += "Via: SIP/2.0/UDP 192.0.2.4;branch=z9hG4bKppi56f\r\n";
    str += "From: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "To: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKp02s2\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKp02s2\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    std::string str;
    str  = "PRACK sip:bob@192.0.2.4 SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK99231\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK99231\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    std::string str;
    str  = "INFO sip:bob@192.0.2.4 SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKqqr712\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bKqqr712\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: " + _call_id + "\r\n";
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
//-------------------------------------------

bool SIP_Call_Test::process_invite()
{
    SIP_Request *invite = create_invite();
    if (!invite)
    {
        std::cout << "SIP_Call_Test::process_invite -> Failed to create request\n";
        return false;
    }

    if (!_client_call.process_send_request(invite))
    {
        std::cout << "SIP_Call_Test::process_invite -> Failed to process send request\n";
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

    if (!_server_call.process_receive_request(invite))
    {
        std::cout << "SIP_Call_Test::process_invite -> Failed to process receive request\n";
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

    if (_invite)
        delete _invite;

    _invite = invite;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_invite_response_100()
{
    if (!_invite)
    {
        std::cout << "SIP_Call_Test::process_invite_response_100 -> Invalid request\n";
        return false;
    }

    SIP_Response *invite_response_100 = create_invite_response_100();
    if (!invite_response_100)
    {
        std::cout << "SIP_Call_Test::process_invite_response_100 -> Failed to create response\n";
        return false;
    }

    if (!_server_call.process_send_response(_invite, invite_response_100))
    {
        std::cout << "SIP_Call_Test::process_invite_response_100 -> Failed to process send response\n";
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

    if (!_client_call.process_receive_response(_invite, invite_response_100))
    {
        std::cout << "SIP_Call_Test::process_invite_response_100 -> Failed to process receive response\n";
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
    if (!_invite)
    {
        std::cout << "SIP_Call_Test::process_invite_response_180 -> Invalid request\n";
        return false;
    }

    SIP_Response *invite_response_180 = create_invite_response_180();
    if (!invite_response_180)
    {
        std::cout << "SIP_Call_Test::process_invite_response_180 -> Failed to create response\n";
        return false;
    }

    if (!_server_call.process_send_response(_invite, invite_response_180))
    {
        std::cout << "SIP_Call_Test::process_invite_response_180 -> Failed to process send response\n";
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

    if (!_client_call.process_receive_response(_invite, invite_response_180))
    {
        std::cout << "SIP_Call_Test::process_invite_response_180 -> Failed to process receive response\n";
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
    if (!_invite)
    {
        std::cout << "SIP_Call_Test::process_invite_response_183 -> Invalid request\n";
        return false;
    }

    SIP_Response *invite_response_183 = create_invite_response_183();
    if (!invite_response_183)
    {
        std::cout << "SIP_Call_Test::process_invite_response_183 -> Failed to create response\n";
        return false;
    }

    if (!_server_call.process_send_response(_invite, invite_response_183))
    {
        std::cout << "SIP_Call_Test::process_invite_response_183 -> Failed to process send response\n";
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

    if (!_client_call.process_receive_response(_invite, invite_response_183))
    {
        std::cout << "SIP_Call_Test::process_invite_response_183 -> Failed to process receive response\n";
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
    if (!_invite)
    {
        std::cout << "SIP_Call_Test::process_invite_response_200 -> Invalid request\n";
        return false;
    }

    SIP_Response *invite_response_200 = create_invite_response_200();
    if (!invite_response_200)
    {
        std::cout << "SIP_Call_Test::process_invite_response_200 -> Failed to create response\n";
        return false;
    }

    if (!_server_call.process_send_response(_invite, invite_response_200))
    {
        std::cout << "SIP_Call_Test::process_invite_response_200 -> Failed to process send response\n";
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

    if (!_client_call.process_receive_response(_invite, invite_response_200))
    {
        std::cout << "SIP_Call_Test::process_invite_response_200 -> Failed to process receive response\n";
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
    if (!_invite)
    {
        std::cout << "SIP_Call_Test::process_invite_response_480 -> Invalid request\n";
        return false;
    }

    SIP_Response *invite_response_480 = create_invite_response_480();
    if (!invite_response_480)
    {
        std::cout << "SIP_Call_Test::process_invite_response_480 -> Failed to create response\n";
        return false;
    }

    if (!_server_call.process_send_response(_invite, invite_response_480))
    {
        std::cout << "SIP_Call_Test::process_invite_response_480 -> Failed to process send response\n";
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

    if (!_client_call.process_receive_response(_invite, invite_response_480))
    {
        std::cout << "SIP_Call_Test::process_invite_response_480 -> Failed to process receive response\n";
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
    if (!_invite)
    {
        std::cout << "SIP_Call_Test::process_invite_response_487 -> Invalid request\n";
        return false;
    }

    SIP_Response *invite_response_487 = create_invite_response_487();
    if (!invite_response_487)
    {
        std::cout << "SIP_Call_Test::process_invite_response_487 -> Failed to create response\n";
        return false;
    }

    if (!_server_call.process_send_response(_invite, invite_response_487))
    {
        std::cout << "SIP_Call_Test::process_invite_response_487 -> Failed to process send response\n";
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

    if (!_client_call.process_receive_response(_invite, invite_response_487))
    {
        std::cout << "SIP_Call_Test::process_invite_response_487 -> Failed to process receive response\n";
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
    if (!_invite)
    {
        std::cout << "SIP_Call_Test::process_ack -> Invalid request\n";
        return false;
    }

    SIP_Request *ack = create_ack();
    if (!ack)
    {
        std::cout << "SIP_Call_Test::process_ack -> Failed to create request\n";
        return false;
    }

    if (!_client_call.process_send_request(ack))
    {
        std::cout << "SIP_Call_Test::process_ack -> Failed to process send request\n";
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

    if (!_server_call.process_receive_request(ack))
    {
        std::cout << "SIP_Call_Test::process_ack -> Failed to process receive request\n";
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

    if (!_client_call.process_send_request(bye))
    {
        std::cout << "SIP_Call_Test::process_client_bye -> Failed to process send request\n";
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

    if (!_server_call.process_receive_request(bye))
    {
        std::cout << "SIP_Call_Test::process_client_bye -> Failed to process receive request\n";
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

    if (_bye)
        delete _bye;

    _bye = bye;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_server_bye_response_200()
{
    if (!_bye)
    {
        std::cout << "SIP_Call_Test::process_server_bye_response_200 -> Invalid request\n";
        return false;
    }

    SIP_Response *bye_response_200 = create_server_bye_response_200();
    if (!bye_response_200)
    {
        std::cout << "SIP_Call_Test::process_server_bye_response_200 -> Failed to create response\n";
        return false;
    }

    if (!_server_call.process_send_response(_bye, bye_response_200))
    {
        std::cout << "SIP_Call_Test::process_server_bye_response_200 -> Failed to process send response\n";
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

    if (!_client_call.process_receive_response(_bye, bye_response_200))
    {
        std::cout << "SIP_Call_Test::process_server_bye_response_200 -> Failed to process receive response\n";
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

    if (!_server_call.process_send_request(bye))
    {
        std::cout << "SIP_Call_Test::process_server_bye -> Failed to process send request\n";
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

    if (!_client_call.process_receive_request(bye))
    {
        std::cout << "SIP_Call_Test::process_server_bye -> Failed to process receive request\n";
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

    if (_bye)
        delete _bye;

    _bye = bye;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_client_bye_response_200()
{
    if (!_bye)
    {
        std::cout << "SIP_Call_Test::process_client_bye_response_200 -> Invalid request\n";
        return false;
    }

    SIP_Response *bye_response_200 = create_client_bye_response_200();
    if (!bye_response_200)
    {
        std::cout << "SIP_Call_Test::process_client_bye_response_200 -> Failed to create response\n";
        return false;
    }

    if (!_client_call.process_send_response(_bye, bye_response_200))
    {
        std::cout << "SIP_Call_Test::process_client_bye_response_200 -> Failed to process send response\n";
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

    if (!_server_call.process_receive_response(_bye, bye_response_200))
    {
        std::cout << "SIP_Call_Test::process_client_bye_response_200 -> Failed to process receive response\n";
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

    if (!_client_call.process_send_request(update))
    {
        std::cout << "SIP_Call_Test::process_client_update -> Failed to process send request\n";
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

    if (!_server_call.process_receive_request(update))
    {
        std::cout << "SIP_Call_Test::process_client_update -> Failed to process receive request\n";
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

    if (_update)
        delete _update;

    _update = update;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_server_update_response_200()
{
    if (!_update)
    {
        std::cout << "SIP_Call_Test::process_server_update_response_200 -> Invalid request\n";
        return false;
    }

    SIP_Response *update_response_200 = create_server_update_response_200();
    if (!update_response_200)
    {
        std::cout << "SIP_Call_Test::process_server_update_response_200 -> Failed to create response\n";
        return false;
    }

    if (!_server_call.process_send_response(_update, update_response_200))
    {
        std::cout << "SIP_Call_Test::process_server_update_response_200 -> Failed to process send response\n";
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

    if (!_client_call.process_receive_response(_update, update_response_200))
    {
        std::cout << "SIP_Call_Test::process_server_update_response_200 -> Failed to process receive response\n";
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

    if (!_server_call.process_send_request(update))
    {
        std::cout << "SIP_Call_Test::process_server_update -> Failed to process send request\n";
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

    if (!_client_call.process_receive_request(update))
    {
        std::cout << "SIP_Call_Test::process_server_update -> Failed to process receive request\n";
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

    if (_update)
        delete _update;

    _update = update;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_client_update_response_200()
{
    if (!_update)
    {
        std::cout << "SIP_Call_Test::process_client_update_response_200 -> Invalid request\n";
        return false;
    }

    SIP_Response *update_response_200 = create_client_update_response_200();
    if (!update_response_200)
    {
        std::cout << "SIP_Call_Test::process_client_update_response_200 -> Failed to create response\n";
        return false;
    }

    if (!_client_call.process_send_response(_update, update_response_200))
    {
        std::cout << "SIP_Call_Test::process_client_update_response_200 -> Failed to process send response\n";
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

    if (!_server_call.process_receive_response(_update, update_response_200))
    {
        std::cout << "SIP_Call_Test::process_client_update_response_200 -> Failed to process receive response\n";
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

    if (!_client_call.process_send_request(cancel))
    {
        std::cout << "SIP_Call_Test::process_cancel -> Failed to process send request\n";
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

    if (!_server_call.process_receive_request(cancel))
    {
        std::cout << "SIP_Call_Test::process_cancel -> Failed to process receive request\n";
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

    if (_cancel)
        delete _cancel;

    _cancel = cancel;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_cancel_response_200()
{
    if (!_cancel)
    {
        std::cout << "SIP_Call_Test::process_cancel_response_200 -> Invalid request\n";
        return false;
    }

    SIP_Response *cancel_response_200 = create_cancel_response_200();
    if (!cancel_response_200)
    {
        std::cout << "SIP_Call_Test::process_cancel_response_200 -> Failed to create response\n";
        return false;
    }

    if (!_server_call.process_send_response(_cancel, cancel_response_200))
    {
        std::cout << "SIP_Call_Test::process_cancel_response_200 -> Failed to process send response\n";
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

    if (!_client_call.process_receive_response(_cancel, cancel_response_200))
    {
        std::cout << "SIP_Call_Test::process_cancel_response_200 -> Failed to process receive response\n";
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

    if (!_client_call.process_send_request(prack))
    {
        std::cout << "SIP_Call_Test::process_prack -> Failed to process send request\n";
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

    if (!_server_call.process_receive_request(prack))
    {
        std::cout << "SIP_Call_Test::process_prack -> Failed to process receive request\n";
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

    if (_prack)
        delete _prack;

    _prack = prack;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_prack_response_200()
{
    if (!_prack)
    {
        std::cout << "SIP_Call_Test::process_prack_response_200 -> Invalid request\n";
        return false;
    }

    SIP_Response *prack_response_200 = create_prack_response_200();
    if (!prack_response_200)
    {
        std::cout << "SIP_Call_Test::process_prack_response_200 -> Failed to create response\n";
        return false;
    }

    if (!_server_call.process_send_response(_prack, prack_response_200))
    {
        std::cout << "SIP_Call_Test::process_prack_response_200 -> Failed to process send response\n";
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

    if (!_client_call.process_receive_response(_prack, prack_response_200))
    {
        std::cout << "SIP_Call_Test::process_prack_response_200 -> Failed to process receive response\n";
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

    if (!_client_call.process_send_request(info))
    {
        std::cout << "SIP_Call_Test::process_info -> Failed to process send request\n";
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

    if (!_server_call.process_receive_request(info))
    {
        std::cout << "SIP_Call_Test::process_info -> Failed to process receive request\n";
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

    if (_info)
        delete _info;

    _info = info;
    return true;
}

//-------------------------------------------

bool SIP_Call_Test::process_info_response_200()
{
    if (!_info)
    {
        std::cout << "SIP_Call_Test::process_info_response_200 -> Invalid request\n";
        return false;
    }

    SIP_Response *info_response_200 = create_info_response_200();
    if (!info_response_200)
    {
        std::cout << "SIP_Call_Test::process_info_response_200 -> Failed to create response\n";
        return false;
    }

    if (!_server_call.process_send_response(_info, info_response_200))
    {
        std::cout << "SIP_Call_Test::process_info_response_200 -> Failed to process send response\n";
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

    if (!_client_call.process_receive_response(_info, info_response_200))
    {
        std::cout << "SIP_Call_Test::process_info_response_200 -> Failed to process receive response\n";
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
//-------------------------------------------

SIP_Response *SIP_Call_Test::create_response_callback(void *data, SIP_Call *call, SIP_Request *request, unsigned short status_code)
{
    SIP_Call_Test *test = reinterpret_cast<SIP_Call_Test *>(data);
    if ((!test) || (!call) || (!request))
    {
        std::cout << "SIP_Call_Test::create_response_callback -> Invalid parameters\n";
        return NULL;
    }

    test->_request = request;
    test->_status_code = status_code;
    return NULL;
}

//-------------------------------------------

bool SIP_Call_Test::send_response_callback(void *data, SIP_Call *call, SIP_Request *request, SIP_Response *response)
{
    SIP_Call_Test *test = reinterpret_cast<SIP_Call_Test *>(data);
    if ((!test) || (!call) || (!request) || (!response))
    {
        std::cout << "SIP_Call_Test::send_response_callback -> Invalid parameters\n";
        return false;
    }

    test->_request = request;
    test->_response = response;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call_Success_Test::run()
{
    set_callbacks();
    set_call_id("a84b4c76e66710@pc33.atlanta.com");

    init_call();

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
    set_call_id("a84b4c76e66710@pc33.atlanta.com");

    init_call();

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
    set_call_id("a84b4c76e66710@pc33.atlanta.com");

    init_call();

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
    set_call_id("a84b4c76e66710@pc33.atlanta.com");

    init_call();

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
