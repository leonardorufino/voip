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

#include "sip_transaction_test.h"
#include <iostream>

//-------------------------------------------

bool SIP_Transaction_Test::_sent_message = false;
bool SIP_Transaction_Test::_received_request = false;
bool SIP_Transaction_Test::_received_response = false;

//-------------------------------------------

bool SIP_Transaction_Test::init()
{
    std::cout << "SIP transaction test initialized\n";

    SIP_Transaction_Client_Invite_Accepted_Test client_invite_accepted_test;
    if (!client_invite_accepted_test.run())
        return false;

    SIP_Transaction_Client_Invite_Rejected_Test client_invite_rejected_test;
    if (!client_invite_rejected_test.run())
        return false;

    SIP_Transaction_Client_Invite_Retransmission_Test client_invite_retransmission_test;
    if (!client_invite_retransmission_test.run())
        return false;

    SIP_Transaction_Client_Non_Invite_Accepted_Test client_non_invite_accepted_test;
    if (!client_non_invite_accepted_test.run())
        return false;

    SIP_Transaction_Client_Non_Invite_Retransmission_Test client_non_invite_retransmission_test;
    if (!client_non_invite_retransmission_test.run())
        return false;

    SIP_Transaction_Server_Invite_Accepted_Test server_invite_accepted_test;
    if (!server_invite_accepted_test.run())
        return false;

    SIP_Transaction_Server_Invite_Rejected_Test server_invite_rejected_test;
    if (!server_invite_rejected_test.run())
        return false;

    SIP_Transaction_Server_Invite_Retransmission_Test server_invite_retransmission_test;
    if (!server_invite_retransmission_test.run())
        return false;

    SIP_Transaction_Server_Non_Invite_Accepted_Test server_non_invite_accepted_test;
    if (!server_non_invite_accepted_test.run())
        return false;

    SIP_Transaction_Server_Non_Invite_Retransmission_Test server_non_invite_retransmission_test;
    if (!server_non_invite_retransmission_test.run())
        return false;

    std::cout << "SIP transaction test completed successfully\n";
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Test::set_callbacks()
{
    SIP_Transaction &transaction = get_transaction();

    transaction.set_send_message_callback(send_message_callback);
    transaction.set_receive_request_callback(receive_request_callback);
    transaction.set_receive_response_callback(receive_response_callback);
    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Request *SIP_Transaction_Test::create_invite()
{
    std::string str;
    str  = "INVITE sip:bob@biloxi.com SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: 314159 INVITE\r\n";
    str += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Transaction_Test::create_invite -> Failed to decode message\n";
        return NULL;
    }

    return request;
}

//-------------------------------------------

SIP_Request *SIP_Transaction_Test::create_ack()
{
    std::string str;
    str  = "ACK sip:bob@192.0.2.4 SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: 314159 ACK\r\n";
    str += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Transaction_Test::create_ack -> Failed to decode message\n";
        return NULL;
    }

    return request;
}

//-------------------------------------------

SIP_Response *SIP_Transaction_Test::create_invite_response_100()
{
    std::string str;
    str  = "SIP/2.0 100 Trying\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: 314159 INVITE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Transaction_Test::create_invite_response_100 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Response *SIP_Transaction_Test::create_invite_response_180()
{
    std::string str;
    str  = "SIP/2.0 180 Ringing\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: 314159 INVITE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Transaction_Test::create_invite_response_180 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Response *SIP_Transaction_Test::create_invite_response_200()
{
    std::string str;
    str  = "SIP/2.0 200 OK\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: 314159 INVITE\r\n";
    str += "Contact: <sip:bob@192.0.2.4>\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Transaction_Test::create_invite_response_200 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Response *SIP_Transaction_Test::create_invite_response_480()
{
    std::string str;
    str  = "SIP/2.0 480 Temporarily Unavailable\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: 314159 INVITE\r\n";
    str += "Contact: <sip:bob@192.0.2.4>\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Transaction_Test::create_invite_response_480 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------
//-------------------------------------------

SIP_Request *SIP_Transaction_Test::create_bye()
{
    std::string str;
    str  = "BYE sip:alice@pc33.atlanta.com SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP 192.0.2.4;branch=z9hG4bKnashds10\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "From: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "To: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710\r\n";
    str += "CSeq: 231 BYE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Transaction_Test::create_bye -> Failed to decode message\n";
        return NULL;
    }

    return request;
}

//-------------------------------------------

SIP_Response *SIP_Transaction_Test::create_bye_response_100()
{
    std::string str;
    str  = "SIP/2.0 100 Trying\r\n";
    str += "Via: SIP/2.0/UDP 192.0.2.4;branch=z9hG4bKnashds10\r\n";
    str += "From: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "To: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710\r\n";
    str += "CSeq: 231 BYE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Transaction_Test::create_bye_response_100 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------

SIP_Response *SIP_Transaction_Test::create_bye_response_200()
{
    std::string str;
    str  = "SIP/2.0 200 OK\r\n";
    str += "Via: SIP/2.0/UDP 192.0.2.4;branch=z9hG4bKnashds10\r\n";
    str += "From: Bob <sip:bob@biloxi.com>;tag=a6c85cf\r\n";
    str += "To: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710\r\n";
    str += "CSeq: 231 BYE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Transaction_Test::create_bye_response_200 -> Failed to decode message\n";
        return NULL;
    }

    return response;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Test::send_message_callback(SIP_Message *msg)
{
    if (!msg)
    {
        std::cout << "SIP_Transaction_Test::send_message_callback -> Invalid parameter\n";
        return false;
    }

    _sent_message = true;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Test::receive_request_callback(SIP_Request *request, SIP_Transaction *transaction)
{
    if ((!request) || (!transaction))
    {
        std::cout << "SIP_Transaction_Test::receive_request_callback -> Invalid parameters\n";
        return false;
    }

    _received_request = true;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Test::receive_response_callback(SIP_Request *request, SIP_Response *response, SIP_Transaction *transaction)
{
    if ((!request) || (!response) || (!transaction))
    {
        std::cout << "SIP_Transaction_Test::receive_response_callback -> Invalid parameters\n";
        return false;
    }

    _received_response = true;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Client_Invite_Test::send_invite()
{
    SIP_Request *request = create_invite();
    if (!request)
        return false;

    _sent_message = false;
    _transaction.send_invite(request);

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::send_invite -> INVITE not sent\n";
        delete request;
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Client_Invite::sttCalling)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::send_invite -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Calling" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete request;
        return false;
    }

    delete request;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Test::receive_response_100()
{
    SIP_Response *response = create_invite_response_100();
    if (!response)
        return false;

    SIP_Transaction *t = _transaction.match_transaction(response);
    if (&_transaction != t)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_100 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _received_response = false;
    _transaction.receive_1xx(response);

    if (!_received_response)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_100 -> Response not received\n";
        delete response;
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Client_Invite::sttProceeding)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_100 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding " << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Test::receive_response_180()
{
    SIP_Response *response = create_invite_response_180();
    if (!response)
        return false;

    SIP_Transaction *t = _transaction.match_transaction(response);
    if (&_transaction != t)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_180 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _received_response = false;
    _transaction.receive_1xx(response);

    if (!_received_response)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_180 -> Response not received\n";
        delete response;
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Client_Invite::sttProceeding)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_180 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Test::receive_response_200()
{
    SIP_Response *response = create_invite_response_200();
    if (!response)
        return false;

    SIP_Transaction *t = _transaction.match_transaction(response);
    if (&_transaction != t)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_200 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _received_response = false;
    _transaction.receive_2xx(response);

    if (!_received_response)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_200 -> Response not received\n";
        delete response;
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Client_Invite::sttTerminated)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_200 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Test::receive_response_480()
{
    SIP_Response *response = create_invite_response_480();
    if (!response)
        return false;

    SIP_Transaction *t = _transaction.match_transaction(response);
    if (&_transaction != t)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_480 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _received_response = false;
    _sent_message = false; // ACK is sent by SIP transaction

    _transaction.receive_3xx_6xx(response);

    if (!_received_response)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_480 -> Response not received\n";
        delete response;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_480 -> ACK not sent\n";
        delete response;
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Client_Invite::sttCompleted)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_480 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Completed" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Test::wait_timer_B()
{
    unsigned long start = Common_Functions::get_tick();
    unsigned long max_wait_time = (SIP_Transaction::SIP_TIMER_1 * 64) + 5000;

    unsigned short invite_retransmissions = 0;
    const unsigned short expected_invite_retransmissions = 6;

    _sent_message = false; // INVITE retransmission
    _received_response = false; // Final rejection response

    while ((Common_Functions::get_tick() - start) < max_wait_time)
    {
        if (_sent_message)
        {
            invite_retransmissions++;
            _sent_message = false;
        }

        if ((_transaction.get_state() == SIP_Transaction_Client_Invite::sttTerminated) && (_received_response))
            break;

        Common_Functions::delay(500);
    }

    if (!_received_response)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::wait_timer_B -> Response not received\n";
        return false;
    }

    if (invite_retransmissions != expected_invite_retransmissions)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::wait_timer_B -> Failed to retransmit INVITE:\n";
        std::cout << std::setw(12) << "Expected: " << expected_invite_retransmissions << "\n";
        std::cout << std::setw(12) << "Count: " << invite_retransmissions << "\n";
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Client_Invite::sttTerminated)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::wait_timer_B -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Test::wait_timer_D()
{
    unsigned long start = Common_Functions::get_tick();
    unsigned long max_wait_time = SIP_Transaction::SIP_TIMER_32s + 5000;

    while ((Common_Functions::get_tick() - start) < max_wait_time)
    {
        if (_transaction.get_state() == SIP_Transaction_Client_Invite::sttTerminated)
            break;

        Common_Functions::delay(500);
    }

    if (_transaction.get_state() != SIP_Transaction_Client_Invite::sttTerminated)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::wait_timer_D -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Client_Invite_Accepted_Test::run()
{
    set_callbacks();

    if (!send_invite())
        return false;

    if (!receive_response_100())
        return false;

    if (!receive_response_180())
        return false;

    if (!receive_response_200())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Client_Invite_Rejected_Test::run()
{
    set_callbacks();

    if (!send_invite())
        return false;

    if (!receive_response_100())
        return false;

    if (!receive_response_180())
        return false;

    if (!receive_response_480())
        return false;

    if (!wait_timer_D())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Client_Invite_Retransmission_Test::run()
{
    set_callbacks();

    if (!send_invite())
        return false;

    if (!wait_timer_B())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite_Test::send_bye()
{
    SIP_Request *request = create_bye();
    if (!request)
        return false;

    _sent_message = false;
    _transaction.send_request(request);

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::send_bye -> BYE not sent\n";
        delete request;
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Client_Non_Invite::sttTrying)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::send_bye -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Trying" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete request;
        return false;
    }

    delete request;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite_Test::receive_response_100()
{
    SIP_Response *response = create_bye_response_100();
    if (!response)
        return false;

    SIP_Transaction *t = _transaction.match_transaction(response);
    if (&_transaction != t)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_100 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _received_response = false;
    _transaction.receive_1xx(response);

    if (!_received_response)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_100 -> Response not received\n";
        delete response;
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Client_Non_Invite::sttProceeding)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_100 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding " << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite_Test::receive_response_200()
{
    SIP_Response *response = create_bye_response_200();
    if (!response)
        return false;

    SIP_Transaction *t = _transaction.match_transaction(response);
    if (&_transaction != t)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_200 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _received_response = false;
    _transaction.receive_2xx_6xx(response);

    if (!_received_response)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_200 -> Response not received\n";
        delete response;
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Client_Non_Invite::sttCompleted)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_200 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Completed" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite_Test::wait_timer_F()
{
    unsigned long start = Common_Functions::get_tick();
    unsigned long max_wait_time = (SIP_Transaction::SIP_TIMER_1 * 64) + 5000;

    unsigned short request_retransmissions = 0;
    const unsigned short expected_request_retransmissions = 10;

    _sent_message = false; // Request retransmission
    _received_response = false; // Final rejection response

    while ((Common_Functions::get_tick() - start) < max_wait_time)
    {
        if (_sent_message)
        {
            request_retransmissions++;
            _sent_message = false;
        }

        if ((_transaction.get_state() == SIP_Transaction_Client_Non_Invite::sttTerminated) && (_received_response))
            break;

        Common_Functions::delay(500);
    }

    if (!_received_response)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::wait_timer_F -> Response not received\n";
        return false;
    }

    if (request_retransmissions != expected_request_retransmissions)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::wait_timer_F -> Failed to retransmit request:\n";
        std::cout << std::setw(12) << "Expected: " << expected_request_retransmissions << "\n";
        std::cout << std::setw(12) << "Count: " << request_retransmissions << "\n";
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Client_Non_Invite::sttTerminated)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::wait_timer_F -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite_Test::wait_timer_K()
{
    unsigned long start = Common_Functions::get_tick();
    unsigned long max_wait_time = SIP_Transaction::SIP_TIMER_4 + 5000;

    while ((Common_Functions::get_tick() - start) < max_wait_time)
    {
        if (_transaction.get_state() == SIP_Transaction_Client_Non_Invite::sttTerminated)
            break;

        Common_Functions::delay(500);
    }

    if (_transaction.get_state() != SIP_Transaction_Client_Non_Invite::sttTerminated)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::wait_timer_K -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite_Accepted_Test::run()
{
    set_callbacks();

    if (!send_bye())
        return false;

    if (!receive_response_100())
        return false;

    if (!receive_response_200())
        return false;

    if (!wait_timer_K())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite_Retransmission_Test::run()
{
    set_callbacks();

    if (!send_bye())
        return false;

    if (!wait_timer_F())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::receive_invite(bool retransmission)
{
    SIP_Request *request = create_invite();
    if (!request)
        return false;

    if (retransmission)
    {
        SIP_Transaction *t = _transaction.match_transaction(request);
        if (&_transaction != t)
        {
            std::cout << "SIP_Transaction_Server_Invite_Test::receive_invite -> Failed to match transaction\n";
            delete request;
            return false;
        }
    }

    _received_request = false;
    _transaction.receive_invite(request);

    if ((!_received_request) && (!retransmission))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::receive_invite -> INVITE not received\n";
        delete request;
        return false;
    }

    if ((_transaction.get_state() != SIP_Transaction_Server_Invite::sttProceeding) && (!retransmission))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::receive_invite -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete request;
        return false;
    }

    delete request;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::receive_ack()
{
    SIP_Request *request = create_ack();
    if (!request)
        return false;

    SIP_Transaction *t = _transaction.match_transaction(request);
    if (&_transaction != t)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::receive_ack -> Failed to match transaction\n";
        delete request;
        return false;
    }

    _transaction.receive_ack(request);

    if (_transaction.get_state() != SIP_Transaction_Server_Invite::sttConfirmed)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::receive_ack -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Confirmed" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete request;
        return false;
    }

    delete request;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::send_response_100()
{
    SIP_Response *response = create_invite_response_100();
    if (!response)
        return false;

    _sent_message = false;
    _transaction.send_1xx(response);

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_100 -> Response not sent\n";
        delete response;
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Server_Invite::sttProceeding)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_100 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding " << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::send_response_180()
{
    SIP_Response *response = create_invite_response_180();
    if (!response)
        return false;

    _sent_message = false;
    _transaction.send_1xx(response);

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_180 -> Response not sent\n";
        delete response;
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Server_Invite::sttProceeding)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_180 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::send_response_200()
{
    SIP_Response *response = create_invite_response_200();
    if (!response)
        return false;

    _sent_message = false;
    _transaction.send_2xx(response);

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_200 -> Response not sent\n";
        delete response;
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Server_Invite::sttTerminated)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_200 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::send_response_480()
{
    SIP_Response *response = create_invite_response_480();
    if (!response)
        return false;

    _sent_message = false;
    _transaction.send_3xx_6xx(response);

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_480 -> Response not sent\n";
        delete response;
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Server_Invite::sttCompleted)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_480 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Completed" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::wait_timer_H()
{
    unsigned long start = Common_Functions::get_tick();
    unsigned long max_wait_time = (SIP_Transaction::SIP_TIMER_1 * 64) + 5000;

    unsigned short response_retransmissions = 0;
    const unsigned short expected_response_retransmissions = 10;

    _sent_message = false; // Response retransmission

    while ((Common_Functions::get_tick() - start) < max_wait_time)
    {
        if (_sent_message)
        {
            response_retransmissions++;
            _sent_message = false;
        }

        if (_transaction.get_state() == SIP_Transaction_Server_Invite::sttTerminated)
            break;

        Common_Functions::delay(500);
    }

    if (response_retransmissions != expected_response_retransmissions)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::wait_timer_H -> Failed to retransmit response:\n";
        std::cout << std::setw(12) << "Expected: " << expected_response_retransmissions << "\n";
        std::cout << std::setw(12) << "Count: " << response_retransmissions << "\n";
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Server_Invite::sttTerminated)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::wait_timer_H -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::wait_timer_I()
{
    unsigned long start = Common_Functions::get_tick();
    unsigned long max_wait_time = SIP_Transaction::SIP_TIMER_4 + 5000;

    while ((Common_Functions::get_tick() - start) < max_wait_time)
    {
        if (_transaction.get_state() == SIP_Transaction_Server_Invite::sttTerminated)
            break;

        Common_Functions::delay(500);
    }

    if (_transaction.get_state() != SIP_Transaction_Server_Invite::sttTerminated)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::wait_timer_I -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Server_Invite_Accepted_Test::run()
{
    set_callbacks();

    if (!receive_invite())
        return false;

    if (!send_response_100())
        return false;

    if (!send_response_180())
        return false;

    if (!send_response_200())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Server_Invite_Rejected_Test::run()
{
    set_callbacks();

    if (!receive_invite())
        return false;

    if (!send_response_100())
        return false;

    if (!send_response_180())
        return false;

    if (!send_response_480())
        return false;

    if (!receive_ack())
        return false;

    if (!wait_timer_I())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Server_Invite_Retransmission_Test::run()
{
    set_callbacks();

    if (!receive_invite())
        return false;

    if (!send_response_480())
        return false;

    if (!receive_invite(true))
        return false;

    if (!wait_timer_H())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite_Test::receive_bye(bool retransmission)
{
    SIP_Request *request = create_bye();
    if (!request)
        return false;

    if (retransmission)
    {
        SIP_Transaction *t = _transaction.match_transaction(request);
        if (&_transaction != t)
        {
            std::cout << "SIP_Transaction_Server_Non_Invite_Test::receive_bye -> Failed to match transaction\n";
            delete request;
            return false;
        }
    }

    _received_request = false;
    _transaction.receive_request(request);

    if ((!_received_request) && (!retransmission))
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::receive_bye -> BYE not received\n";
        delete request;
        return false;
    }

    if ((_transaction.get_state() != SIP_Transaction_Server_Non_Invite::sttTrying) && (!retransmission))
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::receive_bye -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Trying" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete request;
        return false;
    }

    delete request;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite_Test::send_response_100()
{
    SIP_Response *response = create_bye_response_100();
    if (!response)
        return false;

    _sent_message = false;
    _transaction.send_1xx(response);

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::send_response_100 -> Response not sent\n";
        delete response;
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Server_Non_Invite::sttProceeding)
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::send_response_100 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding " << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite_Test::send_response_200()
{
    SIP_Response *response = create_bye_response_200();
    if (!response)
        return false;

    _sent_message = false;
    _transaction.send_2xx_6xx(response);

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::send_response_200 -> Response not sent\n";
        delete response;
        return false;
    }

    if (_transaction.get_state() != SIP_Transaction_Server_Non_Invite::sttCompleted)
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::send_response_200 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Completed" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite_Test::wait_timer_J()
{
    unsigned long start = Common_Functions::get_tick();
    unsigned long max_wait_time = (SIP_Transaction::SIP_TIMER_1 * 64) + 5000;

    while ((Common_Functions::get_tick() - start) < max_wait_time)
    {
        if (_transaction.get_state() == SIP_Transaction_Server_Non_Invite::sttTerminated)
            break;

        Common_Functions::delay(500);
    }

    if (_transaction.get_state() != SIP_Transaction_Server_Non_Invite::sttTerminated)
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::wait_timer_J -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << _transaction.get_state_str().c_str() << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite_Accepted_Test::run()
{
    set_callbacks();

    if (!receive_bye())
        return false;

    if (!send_response_100())
        return false;

    if (!send_response_200())
        return false;

    if (!wait_timer_J())
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite_Retransmission_Test::run()
{
    set_callbacks();

    if (!receive_bye())
        return false;

    if (!send_response_200())
        return false;

    if (!receive_bye(true))
        return false;

    if (!wait_timer_J())
        return false;

    return true;
}

//-------------------------------------------
