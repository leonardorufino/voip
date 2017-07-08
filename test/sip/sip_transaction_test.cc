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

//-------------------------------------------

bool SIP_Transaction_Test::sent_message = false;
bool SIP_Transaction_Test::received_request = false;
bool SIP_Transaction_Test::received_response = false;

//-------------------------------------------

bool SIP_Transaction_Test::init()
{
    std::cout << "SIP transaction test initialized\n";

    SIP_Transaction_Client_Invite_Accepted_Test client_invite_accepted_test;
    if (!client_invite_accepted_test.run())
        return false;

    std::cout << "SIP transaction test completed successfully\n";
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Test::send_message_callback(SIP_Message *msg)
{
    if (!msg)
    {
        std::cout << "SIP_Transaction_Test::send_message_callback -> Invalid parameter\n";
        return false;
    }

    sent_message = true;
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

    received_request = true;
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

    received_response = true;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Client_Invite_Accepted_Test::run()
{
    transaction.set_send_message_callback(send_message_callback);
    transaction.set_receive_request_callback(receive_request_callback);
    transaction.set_receive_response_callback(receive_response_callback);

    if (!send_invite())
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

bool SIP_Transaction_Client_Invite_Accepted_Test::send_invite()
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
    if (!msg)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_invite -> Failed to decode request\n";
        return false;
    }

    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_invite -> Failed to get request\n";
        return false;
    }

    sent_message = false;
    transaction.send_invite(request);

    if (!sent_message)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_invite -> Request not sent\n";
        return false;
    }

    if (transaction.get_state() != SIP_Transaction_Client_Invite::sttCalling)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_invite -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Calling" << "\n";
        std::cout << std::setw(12) << "State: " << transaction.get_state_str().c_str() << "\n";
        return false;
    }

    delete msg;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Accepted_Test::send_response_100()
{
    std::string str;
    str  = "SIP/2.0 100 OK\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds;received=192.0.2.1\r\n";
    str += "To: Bob <sip:bob@biloxi.com>\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: 314159 INVITE\r\n";
    str += "Content-Length: 0\r\n";

    SIP_Message *msg = SIP_Message::decode_msg(str);
    if (!msg)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_response_100 -> Failed to decode response\n";
        return false;
    }

    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_response_100 -> Failed to get response\n";
        return false;
    }

    SIP_Transaction *t = transaction.match_transaction(response);
    if (&transaction != t)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_response_100 -> Failed to match transaction\n";
        return false;
    }

    received_response = false;
    transaction.receive_1xx(response);

    if (!received_response)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_response_100 -> Response not received\n";
        return false;
    }

    if (transaction.get_state() != SIP_Transaction_Client_Invite::sttProceeding)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_response_100 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding " << "\n";
        std::cout << std::setw(12) << "State: " << transaction.get_state_str().c_str() << "\n";
        return false;
    }

    delete msg;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Accepted_Test::send_response_180()
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
    if (!msg)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_response_180 -> Failed to decode response\n";
        return false;
    }

    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_response_180 -> Failed to get response\n";
        return false;
    }

    SIP_Transaction *t = transaction.match_transaction(response);
    if (&transaction != t)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_response_180 -> Failed to match transaction\n";
        return false;
    }

    received_response = false;
    transaction.receive_1xx(response);

    if (!received_response)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_response_180 -> Response not received\n";
        return false;
    }

    if (transaction.get_state() != SIP_Transaction_Client_Invite::sttProceeding)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_response_180 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding" << "\n";
        std::cout << std::setw(12) << "State: " << transaction.get_state_str().c_str() << "\n";
        return false;
    }

    delete msg;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Accepted_Test::send_response_200()
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
    if (!msg)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_response_200 -> Failed to decode response\n";
        return false;
    }

    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_response_200 -> Failed to get response\n";
        return false;
    }

    SIP_Transaction *t = transaction.match_transaction(response);
    if (&transaction != t)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_response_200 -> Failed to match transaction\n";
        return false;
    }

    received_response = false;
    transaction.receive_2xx(response);

    if (!received_response)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_response_200 -> Response not received\n";
        return false;
    }

    if (transaction.get_state() != SIP_Transaction_Client_Invite::sttTerminated)
    {
        std::cout << "SIP_Transaction_Client_Invite_Accepted_Test::send_response_200 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << transaction.get_state_str().c_str() << "\n";
        return false;
    }

    delete msg;
    return true;
}

//-------------------------------------------
