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

SIP_Call_Test::SIP_Call_Test() : _client_sequence(314158), _server_sequence(230), _invite_sequence(0),
        _request(NULL), _response(NULL), _status_code(0)
{
}

//-------------------------------------------

SIP_Call_Test::~SIP_Call_Test()
{
    if (_request)
        delete _request;

    if (_response)
        delete _response;
}

//-------------------------------------------

bool SIP_Call_Test::init()
{
    std::cout << "SIP call test initialized\n";

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
    str += "Content-Length: 0\r\n";

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
    str += "Contact: <sip:bob@192.0.2.4>\r\n";
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
    str += "Contact: <sip:bob@192.0.2.4>\r\n";
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
