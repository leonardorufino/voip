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

bool SIP_Transaction_Test::init()
{
    std::cout << "SIP transaction test initialized\n";

    if (!run<SIP_Transaction_Client_Invite_Accepted_Test>())
        return false;

    if (!run<SIP_Transaction_Client_Invite_Rejected_Test>())
        return false;

    if (!run<SIP_Transaction_Client_Invite_Retransmission_Test>())
        return false;

    if (!run<SIP_Transaction_Client_Non_Invite_Accepted_Test>())
        return false;

    if (!run<SIP_Transaction_Client_Non_Invite_Retransmission_Test>())
        return false;

    if (!run<SIP_Transaction_Server_Invite_Accepted_Test>())
        return false;

    if (!run<SIP_Transaction_Server_Invite_Rejected_Test>())
        return false;

    if (!run<SIP_Transaction_Server_Invite_Retransmission_Test>())
        return false;

    if (!run<SIP_Transaction_Server_Non_Invite_Accepted_Test>())
        return false;

    if (!run<SIP_Transaction_Server_Non_Invite_Retransmission_Test>())
        return false;

    std::cout << "SIP transaction test completed successfully\n";
    return true;
}

//-------------------------------------------

template<class T> bool SIP_Transaction_Test::run()
{
    T test;
    test._thread = std::thread(thread, &test);

    bool ret = test.run();

    test._stop_thread = true;
    test._thread.join();
    return ret;
}

//-------------------------------------------

void SIP_Transaction_Test::thread(SIP_Transaction_Test *test)
{
    Timer_Manager &timer = Timer_Manager::instance();

    while (!test->_stop_thread)
    {
        Util_Functions::delay(THREAD_DELAY);

        std::lock_guard<std::mutex> lock(test->_thread_mutex);
        timer.run();
    }
}

//-------------------------------------------
//-------------------------------------------

SIP_Transaction_Test::SIP_Transaction_Test() : _transaction(NULL), _sent_message(false), _received_request(false),
    _received_response(false), _stop_thread(false)
{
}

//-------------------------------------------

SIP_Transaction_Test::~SIP_Transaction_Test()
{
    if (_transaction)
        delete _transaction;
}

//-------------------------------------------

bool SIP_Transaction_Test::set_callbacks()
{
    if (!_transaction)
    {
        std::cout << "SIP_Transaction_Test::set_callbacks -> Invalid transaction\n";
        return false;
    }

    _transaction->set_send_message_callback(send_message_callback, this);
    _transaction->set_receive_request_callback(receive_request_callback, this);
    _transaction->set_receive_response_callback(receive_response_callback, this);
    return true;
}

//-------------------------------------------

unsigned int SIP_Transaction_Test::get_next_transaction_id()
{
    static unsigned int NEXT_TRANSACTION_ID = 0;
    return NEXT_TRANSACTION_ID++;
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
    str += "\r\n";

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
    str += "\r\n";

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
    str += "\r\n";

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
    str += "\r\n";

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
    str += "\r\n";

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
    str += "\r\n";

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
    str += "\r\n";

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
    str += "\r\n";

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
    str += "\r\n";

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

bool SIP_Transaction_Test::send_message_callback(void *data, SIP_Transaction *transaction, SIP_Message *msg)
{
    SIP_Transaction_Test *test = reinterpret_cast<SIP_Transaction_Test *>(data);
    if ((!test) || (!transaction) || (!msg))
    {
        std::cout << "SIP_Transaction_Test::send_message_callback -> Invalid parameters\n";
        return false;
    }

    test->_sent_message = true;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Test::receive_request_callback(void *data, SIP_Transaction *transaction, SIP_Request *request)
{
    SIP_Transaction_Test *test = reinterpret_cast<SIP_Transaction_Test *>(data);
    if ((!test) || (!transaction) || (!request))
    {
        std::cout << "SIP_Transaction_Test::receive_request_callback -> Invalid parameters\n";
        return false;
    }

    test->_received_request = true;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Test::receive_response_callback(void *data, SIP_Transaction *transaction, SIP_Request *request, SIP_Response *response)
{
    SIP_Transaction_Test *test = reinterpret_cast<SIP_Transaction_Test *>(data);
    if ((!test) || (!transaction) || (!request) || (!response))
    {
        std::cout << "SIP_Transaction_Test::receive_response_callback -> Invalid parameters\n";
        return false;
    }

    test->_received_response = true;
    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Transaction_Client_Invite_Test::SIP_Transaction_Client_Invite_Test()
{
    SIP_Object_ID id;
    id._transaction = get_next_transaction_id();
    _transaction = new SIP_Transaction_Client_Invite(id);
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Test::send_invite()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Client_Invite *transaction_client_invite = dynamic_cast<SIP_Transaction_Client_Invite *>(_transaction);
    if (!transaction_client_invite)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::send_invite -> Invalid transaction\n";
        return false;
    }

    SIP_Request *request = create_invite();
    if (!request)
        return false;

    if (transaction_client_invite->match_transaction(request))
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::send_invite -> Failed to match transaction\n";
        delete request;
        return false;
    }

    _sent_message = false;

    if (!transaction_client_invite->send_invite(request))
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::send_invite -> Failed to send INVITE\n";
        delete request;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::send_invite -> INVITE not sent\n";
        delete request;
        return false;
    }

    if (transaction_client_invite->get_state() != SIP_Transaction_Client_Invite::STATE_CALLING)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::send_invite -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Calling" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_client_invite->get_state_str().c_str() << "\n";
        delete request;
        return false;
    }

    delete request;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Test::receive_response_100()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Client_Invite *transaction_client_invite = dynamic_cast<SIP_Transaction_Client_Invite *>(_transaction);
    if (!transaction_client_invite)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_100 -> Invalid transaction\n";
        return false;
    }

    SIP_Response *response = create_invite_response_100();
    if (!response)
        return false;

    if (!transaction_client_invite->match_transaction(response))
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_100 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _received_response = false;

    if (!transaction_client_invite->receive_1xx(response))
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_100 -> Failed to receive response\n";
        delete response;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_100 -> Response not received\n";
        delete response;
        return false;
    }

    if (transaction_client_invite->get_state() != SIP_Transaction_Client_Invite::STATE_PROCEEDING)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_100 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding " << "\n";
        std::cout << std::setw(12) << "State: " << transaction_client_invite->get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Test::receive_response_180()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Client_Invite *transaction_client_invite = dynamic_cast<SIP_Transaction_Client_Invite *>(_transaction);
    if (!transaction_client_invite)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_180 -> Invalid transaction\n";
        return false;
    }

    SIP_Response *response = create_invite_response_180();
    if (!response)
        return false;

    if (!transaction_client_invite->match_transaction(response))
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_180 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _received_response = false;

    if (!transaction_client_invite->receive_1xx(response))
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_180 -> Failed to receive response\n";
        delete response;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_180 -> Response not received\n";
        delete response;
        return false;
    }

    if (transaction_client_invite->get_state() != SIP_Transaction_Client_Invite::STATE_PROCEEDING)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_180 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_client_invite->get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Test::receive_response_200()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Client_Invite *transaction_client_invite = dynamic_cast<SIP_Transaction_Client_Invite *>(_transaction);
    if (!transaction_client_invite)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_200 -> Invalid transaction\n";
        return false;
    }

    SIP_Response *response = create_invite_response_200();
    if (!response)
        return false;

    if (!transaction_client_invite->match_transaction(response))
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_200 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _received_response = false;

    if (!transaction_client_invite->receive_2xx(response))
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_200 -> Failed to receive response\n";
        delete response;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_200 -> Response not received\n";
        delete response;
        return false;
    }

    if (transaction_client_invite->get_state() != SIP_Transaction_Client_Invite::STATE_TERMINATED)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_200 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_client_invite->get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Test::receive_response_480()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Client_Invite *transaction_client_invite = dynamic_cast<SIP_Transaction_Client_Invite *>(_transaction);
    if (!transaction_client_invite)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_480 -> Invalid transaction\n";
        return false;
    }

    SIP_Response *response = create_invite_response_480();
    if (!response)
        return false;

    if (!transaction_client_invite->match_transaction(response))
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_480 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _received_response = false;
    _sent_message = false; // ACK is sent by SIP transaction

    if (!transaction_client_invite->receive_3xx_6xx(response))
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_480 -> Failed to receive response\n";
        delete response;
        return false;
    }

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

    if (transaction_client_invite->get_state() != SIP_Transaction_Client_Invite::STATE_COMPLETED)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::receive_response_480 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Completed" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_client_invite->get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Test::wait_timer_B()
{
    SIP_Transaction_Client_Invite *transaction_client_invite = dynamic_cast<SIP_Transaction_Client_Invite *>(_transaction);
    if (!transaction_client_invite)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::wait_timer_B -> Invalid transaction\n";
        return false;
    }

    unsigned long start = Util_Functions::get_tick();
    unsigned long max_wait_time = (SIP_Transaction::SIP_TIMER_1 * 64) + MAX_WAIT_TIME;

    unsigned short invite_retransmissions = 0;
    const unsigned short expected_invite_retransmissions = 6;

    _sent_message = false; // INVITE retransmission
    _received_response = false; // Final rejection response

    while ((Util_Functions::get_tick() - start) < max_wait_time)
    {
        if (_sent_message)
        {
            invite_retransmissions++;
            _sent_message = false;
        }

        if ((transaction_client_invite->get_state() == SIP_Transaction_Client_Invite::STATE_TERMINATED) && (_received_response))
            break;

        Util_Functions::delay(DELAY);
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

    if (transaction_client_invite->get_state() != SIP_Transaction_Client_Invite::STATE_TERMINATED)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::wait_timer_B -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_client_invite->get_state_str().c_str() << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite_Test::wait_timer_D()
{
    SIP_Transaction_Client_Invite *transaction_client_invite = dynamic_cast<SIP_Transaction_Client_Invite *>(_transaction);
    if (!transaction_client_invite)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::wait_timer_D -> Invalid transaction\n";
        return false;
    }

    unsigned long start = Util_Functions::get_tick();
    unsigned long max_wait_time = SIP_Transaction::SIP_TIMER_32s + MAX_WAIT_TIME;

    while ((Util_Functions::get_tick() - start) < max_wait_time)
    {
        if (transaction_client_invite->get_state() == SIP_Transaction_Client_Invite::STATE_TERMINATED)
            break;

        Util_Functions::delay(DELAY);
    }

    if (transaction_client_invite->get_state() != SIP_Transaction_Client_Invite::STATE_TERMINATED)
    {
        std::cout << "SIP_Transaction_Client_Invite_Test::wait_timer_D -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_client_invite->get_state_str().c_str() << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Client_Invite_Accepted_Test::run()
{
    std::cout << "SIP transaction client invite accepted test initialized\n";

    if (!set_callbacks())
        return false;

    if (!send_invite())
        return false;

    if (!receive_response_100())
        return false;

    if (!receive_response_180())
        return false;

    if (!receive_response_200())
        return false;

    std::cout << "SIP transaction client invite accepted test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Client_Invite_Rejected_Test::run()
{
    std::cout << "SIP transaction client invite rejected test initialized\n";

    if (!set_callbacks())
        return false;

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

    std::cout << "SIP transaction client invite rejected test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Client_Invite_Retransmission_Test::run()
{
    std::cout << "SIP transaction client invite retransmission test initialized\n";

    if (!set_callbacks())
        return false;

    if (!send_invite())
        return false;

    if (!wait_timer_B())
        return false;

    std::cout << "SIP transaction client invite retransmission test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Transaction_Client_Non_Invite_Test::SIP_Transaction_Client_Non_Invite_Test()
{
    SIP_Object_ID id;
    id._transaction = get_next_transaction_id();
    _transaction = new SIP_Transaction_Client_Non_Invite(id);
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite_Test::send_bye()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Client_Non_Invite *transaction_client_non_invite = dynamic_cast<SIP_Transaction_Client_Non_Invite *>(_transaction);
    if (!transaction_client_non_invite)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::send_bye -> Invalid transaction\n";
        return false;
    }

    SIP_Request *request = create_bye();
    if (!request)
        return false;

    if (transaction_client_non_invite->match_transaction(request))
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::send_bye -> Failed to match transaction\n";
        delete request;
        return false;
    }

    _sent_message = false;

    if (!transaction_client_non_invite->send_request(request))
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::send_bye -> Failed to send BYE\n";
        delete request;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::send_bye -> BYE not sent\n";
        delete request;
        return false;
    }

    if (transaction_client_non_invite->get_state() != SIP_Transaction_Client_Non_Invite::STATE_TRYING)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::send_bye -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Trying" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_client_non_invite->get_state_str().c_str() << "\n";
        delete request;
        return false;
    }

    delete request;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite_Test::receive_response_100()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Client_Non_Invite *transaction_client_non_invite = dynamic_cast<SIP_Transaction_Client_Non_Invite *>(_transaction);
    if (!transaction_client_non_invite)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_100 -> Invalid transaction\n";
        return false;
    }

    SIP_Response *response = create_bye_response_100();
    if (!response)
        return false;

    if (!transaction_client_non_invite->match_transaction(response))
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_100 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _received_response = false;

    if (!transaction_client_non_invite->receive_1xx(response))
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_100 -> Failed to receive response\n";
        delete response;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_100 -> Response not received\n";
        delete response;
        return false;
    }

    if (transaction_client_non_invite->get_state() != SIP_Transaction_Client_Non_Invite::STATE_PROCEEDING)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_100 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding " << "\n";
        std::cout << std::setw(12) << "State: " << transaction_client_non_invite->get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite_Test::receive_response_200()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Client_Non_Invite *transaction_client_non_invite = dynamic_cast<SIP_Transaction_Client_Non_Invite *>(_transaction);
    if (!transaction_client_non_invite)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_200 -> Invalid transaction\n";
        return false;
    }

    SIP_Response *response = create_bye_response_200();
    if (!response)
        return false;

    if (!transaction_client_non_invite->match_transaction(response))
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_200 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _received_response = false;

    if (!transaction_client_non_invite->receive_2xx_6xx(response))
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_200 -> Failed to receive response\n";
        delete response;
        return false;
    }

    if (!_received_response)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_200 -> Response not received\n";
        delete response;
        return false;
    }

    if (transaction_client_non_invite->get_state() != SIP_Transaction_Client_Non_Invite::STATE_COMPLETED)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::receive_response_200 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Completed" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_client_non_invite->get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite_Test::wait_timer_F()
{
    SIP_Transaction_Client_Non_Invite *transaction_client_non_invite = dynamic_cast<SIP_Transaction_Client_Non_Invite *>(_transaction);
    if (!transaction_client_non_invite)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::wait_timer_F -> Invalid transaction\n";
        return false;
    }

    unsigned long start = Util_Functions::get_tick();
    unsigned long max_wait_time = (SIP_Transaction::SIP_TIMER_1 * 64) + MAX_WAIT_TIME;

    unsigned short request_retransmissions = 0;
    const unsigned short expected_request_retransmissions = 10;

    _sent_message = false; // Request retransmission
    _received_response = false; // Final rejection response

    while ((Util_Functions::get_tick() - start) < max_wait_time)
    {
        if (_sent_message)
        {
            request_retransmissions++;
            _sent_message = false;
        }

        if ((transaction_client_non_invite->get_state() == SIP_Transaction_Client_Non_Invite::STATE_TERMINATED) && (_received_response))
            break;

        Util_Functions::delay(DELAY);
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

    if (transaction_client_non_invite->get_state() != SIP_Transaction_Client_Non_Invite::STATE_TERMINATED)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::wait_timer_F -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_client_non_invite->get_state_str().c_str() << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite_Test::wait_timer_K()
{
    SIP_Transaction_Client_Non_Invite *transaction_client_non_invite = dynamic_cast<SIP_Transaction_Client_Non_Invite *>(_transaction);
    if (!transaction_client_non_invite)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::wait_timer_K -> Invalid transaction\n";
        return false;
    }

    unsigned long start = Util_Functions::get_tick();
    unsigned long max_wait_time = SIP_Transaction::SIP_TIMER_4 + MAX_WAIT_TIME;

    while ((Util_Functions::get_tick() - start) < max_wait_time)
    {
        if (transaction_client_non_invite->get_state() == SIP_Transaction_Client_Non_Invite::STATE_TERMINATED)
            break;

        Util_Functions::delay(DELAY);
    }

    if (transaction_client_non_invite->get_state() != SIP_Transaction_Client_Non_Invite::STATE_TERMINATED)
    {
        std::cout << "SIP_Transaction_Client_Non_Invite_Test::wait_timer_K -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_client_non_invite->get_state_str().c_str() << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite_Accepted_Test::run()
{
    std::cout << "SIP transaction client non-invite accepted test initialized\n";

    if (!set_callbacks())
        return false;

    if (!send_bye())
        return false;

    if (!receive_response_100())
        return false;

    if (!receive_response_200())
        return false;

    if (!wait_timer_K())
        return false;

    std::cout << "SIP transaction client non-invite accepted test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite_Retransmission_Test::run()
{
    std::cout << "SIP transaction client non-invite retransmission test initialized\n";

    if (!set_callbacks())
        return false;

    if (!send_bye())
        return false;

    if (!wait_timer_F())
        return false;

    std::cout << "SIP transaction client non-invite retransmission test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Transaction_Server_Invite_Test::SIP_Transaction_Server_Invite_Test()
{
    SIP_Object_ID id;
    id._transaction = get_next_transaction_id();
    _transaction = new SIP_Transaction_Server_Invite(id);
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::receive_invite(bool retransmission)
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Server_Invite *transaction_server_invite = dynamic_cast<SIP_Transaction_Server_Invite *>(_transaction);
    if (!transaction_server_invite)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::receive_invite -> Invalid transaction\n";
        return false;
    }

    SIP_Request *request = create_invite();
    if (!request)
        return false;

    if (((!retransmission) && (transaction_server_invite->match_transaction(request))) ||
        ((retransmission) && (!transaction_server_invite->match_transaction(request))))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::receive_invite -> Failed to match transaction\n";
        delete request;
        return false;
    }

    _received_request = false;

    if (!transaction_server_invite->receive_invite(request))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::receive_invite -> Failed to receive INVITE\n";
        delete request;
        return false;
    }

    if ((!_received_request) && (!retransmission))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::receive_invite -> INVITE not received\n";
        delete request;
        return false;
    }

    if ((transaction_server_invite->get_state() != SIP_Transaction_Server_Invite::STATE_PROCEEDING) && (!retransmission))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::receive_invite -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_server_invite->get_state_str().c_str() << "\n";
        delete request;
        return false;
    }

    delete request;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::receive_ack()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Server_Invite *transaction_server_invite = dynamic_cast<SIP_Transaction_Server_Invite *>(_transaction);
    if (!transaction_server_invite)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::receive_ack -> Invalid transaction\n";
        return false;
    }

    SIP_Request *request = create_ack();
    if (!request)
        return false;

    if (!transaction_server_invite->match_transaction(request))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::receive_ack -> Failed to match transaction\n";
        delete request;
        return false;
    }

    if (!transaction_server_invite->receive_ack(request))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::receive_ack -> Failed to receive ACK\n";
        delete request;
        return false;
    }

    if (transaction_server_invite->get_state() != SIP_Transaction_Server_Invite::STATE_CONFIRMED)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::receive_ack -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Confirmed" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_server_invite->get_state_str().c_str() << "\n";
        delete request;
        return false;
    }

    delete request;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::send_response_100()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Server_Invite *transaction_server_invite = dynamic_cast<SIP_Transaction_Server_Invite *>(_transaction);
    if (!transaction_server_invite)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_100 -> Invalid transaction\n";
        return false;
    }

    SIP_Response *response = create_invite_response_100();
    if (!response)
        return false;

    if (!transaction_server_invite->match_transaction(response))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_100 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _sent_message = false;

    if (!transaction_server_invite->send_1xx(response))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_100 -> Failed to send response\n";
        delete response;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_100 -> Response not sent\n";
        delete response;
        return false;
    }

    if (transaction_server_invite->get_state() != SIP_Transaction_Server_Invite::STATE_PROCEEDING)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_100 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding " << "\n";
        std::cout << std::setw(12) << "State: " << transaction_server_invite->get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::send_response_180()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Server_Invite *transaction_server_invite = dynamic_cast<SIP_Transaction_Server_Invite *>(_transaction);
    if (!transaction_server_invite)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_180 -> Invalid transaction\n";
        return false;
    }

    SIP_Response *response = create_invite_response_180();
    if (!response)
        return false;

    if (!transaction_server_invite->match_transaction(response))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_180 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _sent_message = false;

    if (!transaction_server_invite->send_1xx(response))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_180 -> Failed to send response\n";
        delete response;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_180 -> Response not sent\n";
        delete response;
        return false;
    }

    if (transaction_server_invite->get_state() != SIP_Transaction_Server_Invite::STATE_PROCEEDING)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_180 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_server_invite->get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::send_response_200()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Server_Invite *transaction_server_invite = dynamic_cast<SIP_Transaction_Server_Invite *>(_transaction);
    if (!transaction_server_invite)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_200 -> Invalid transaction\n";
        return false;
    }

    SIP_Response *response = create_invite_response_200();
    if (!response)
        return false;

    if (!transaction_server_invite->match_transaction(response))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_200 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _sent_message = false;

    if (!transaction_server_invite->send_2xx(response))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_200 -> Failed to send response\n";
        delete response;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_200 -> Response not sent\n";
        delete response;
        return false;
    }

    if (transaction_server_invite->get_state() != SIP_Transaction_Server_Invite::STATE_TERMINATED)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_200 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_server_invite->get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::send_response_480()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Server_Invite *transaction_server_invite = dynamic_cast<SIP_Transaction_Server_Invite *>(_transaction);
    if (!transaction_server_invite)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_480 -> Invalid transaction\n";
        return false;
    }

    SIP_Response *response = create_invite_response_480();
    if (!response)
        return false;

    if (!transaction_server_invite->match_transaction(response))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_480 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _sent_message = false;

    if (!transaction_server_invite->send_3xx_6xx(response))
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_480 -> Failed to send response\n";
        delete response;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_480 -> Response not sent\n";
        delete response;
        return false;
    }

    if (transaction_server_invite->get_state() != SIP_Transaction_Server_Invite::STATE_COMPLETED)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::send_response_480 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Completed" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_server_invite->get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::wait_timer_H()
{
    SIP_Transaction_Server_Invite *transaction_server_invite = dynamic_cast<SIP_Transaction_Server_Invite *>(_transaction);
    if (!transaction_server_invite)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::wait_timer_H -> Invalid transaction\n";
        return false;
    }

    unsigned long start = Util_Functions::get_tick();
    unsigned long max_wait_time = (SIP_Transaction::SIP_TIMER_1 * 64) + MAX_WAIT_TIME;

    unsigned short response_retransmissions = 0;
    const unsigned short expected_response_retransmissions = 10;

    _sent_message = false; // Response retransmission

    while ((Util_Functions::get_tick() - start) < max_wait_time)
    {
        if (_sent_message)
        {
            response_retransmissions++;
            _sent_message = false;
        }

        if (transaction_server_invite->get_state() == SIP_Transaction_Server_Invite::STATE_TERMINATED)
            break;

        Util_Functions::delay(DELAY);
    }

    if (response_retransmissions != expected_response_retransmissions)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::wait_timer_H -> Failed to retransmit response:\n";
        std::cout << std::setw(12) << "Expected: " << expected_response_retransmissions << "\n";
        std::cout << std::setw(12) << "Count: " << response_retransmissions << "\n";
        return false;
    }

    if (transaction_server_invite->get_state() != SIP_Transaction_Server_Invite::STATE_TERMINATED)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::wait_timer_H -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_server_invite->get_state_str().c_str() << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite_Test::wait_timer_I()
{
    SIP_Transaction_Server_Invite *transaction_server_invite = dynamic_cast<SIP_Transaction_Server_Invite *>(_transaction);
    if (!transaction_server_invite)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::wait_timer_I -> Invalid transaction\n";
        return false;
    }

    unsigned long start = Util_Functions::get_tick();
    unsigned long max_wait_time = SIP_Transaction::SIP_TIMER_4 + MAX_WAIT_TIME;

    while ((Util_Functions::get_tick() - start) < max_wait_time)
    {
        if (transaction_server_invite->get_state() == SIP_Transaction_Server_Invite::STATE_TERMINATED)
            break;

        Util_Functions::delay(DELAY);
    }

    if (transaction_server_invite->get_state() != SIP_Transaction_Server_Invite::STATE_TERMINATED)
    {
        std::cout << "SIP_Transaction_Server_Invite_Test::wait_timer_I -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_server_invite->get_state_str().c_str() << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Server_Invite_Accepted_Test::run()
{
    std::cout << "SIP transaction server invite accepted test initialized\n";

    if (!set_callbacks())
        return false;

    if (!receive_invite())
        return false;

    if (!send_response_100())
        return false;

    if (!send_response_180())
        return false;

    if (!send_response_200())
        return false;

    std::cout << "SIP transaction server invite accepted test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Server_Invite_Rejected_Test::run()
{
    std::cout << "SIP transaction server invite rejected test initialized\n";

    if (!set_callbacks())
        return false;

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

    std::cout << "SIP transaction server invite rejected test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Server_Invite_Retransmission_Test::run()
{
    std::cout << "SIP transaction server invite retransmission test initialized\n";

    if (!set_callbacks())
        return false;

    if (!receive_invite())
        return false;

    if (!send_response_480())
        return false;

    if (!receive_invite(true))
        return false;

    if (!wait_timer_H())
        return false;

    std::cout << "SIP transaction server invite retransmission test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Transaction_Server_Non_Invite_Test::SIP_Transaction_Server_Non_Invite_Test()
{
    SIP_Object_ID id;
    id._transaction = get_next_transaction_id();
    _transaction = new SIP_Transaction_Server_Non_Invite(id);
}

//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite_Test::receive_bye(bool retransmission)
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Server_Non_Invite *transaction_server_non_invite = dynamic_cast<SIP_Transaction_Server_Non_Invite *>(_transaction);
    if (!transaction_server_non_invite)
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::receive_bye -> Invalid transaction\n";
        return false;
    }

    SIP_Request *request = create_bye();
    if (!request)
        return false;

    if (((!retransmission) && (transaction_server_non_invite->match_transaction(request))) ||
        ((retransmission) && (!transaction_server_non_invite->match_transaction(request))))
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::receive_bye -> Failed to match transaction\n";
        delete request;
        return false;
    }

    _received_request = false;

    if (!transaction_server_non_invite->receive_request(request))
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::receive_bye -> Failed to receive BYE\n";
        delete request;
        return false;
    }

    if ((!_received_request) && (!retransmission))
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::receive_bye -> BYE not received\n";
        delete request;
        return false;
    }

    if ((transaction_server_non_invite->get_state() != SIP_Transaction_Server_Non_Invite::STATE_TRYING) && (!retransmission))
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::receive_bye -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Trying" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_server_non_invite->get_state_str().c_str() << "\n";
        delete request;
        return false;
    }

    delete request;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite_Test::send_response_100()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Server_Non_Invite *transaction_server_non_invite = dynamic_cast<SIP_Transaction_Server_Non_Invite *>(_transaction);
    if (!transaction_server_non_invite)
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::send_response_100 -> Invalid transaction\n";
        return false;
    }

    SIP_Response *response = create_bye_response_100();
    if (!response)
        return false;

    if (!transaction_server_non_invite->match_transaction(response))
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::send_response_100 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _sent_message = false;

    if (!transaction_server_non_invite->send_1xx(response))
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::send_response_100 -> Failed to send response\n";
        delete response;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::send_response_100 -> Response not sent\n";
        delete response;
        return false;
    }

    if (transaction_server_non_invite->get_state() != SIP_Transaction_Server_Non_Invite::STATE_PROCEEDING)
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::send_response_100 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Proceeding " << "\n";
        std::cout << std::setw(12) << "State: " << transaction_server_non_invite->get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite_Test::send_response_200()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    SIP_Transaction_Server_Non_Invite *transaction_server_non_invite = dynamic_cast<SIP_Transaction_Server_Non_Invite *>(_transaction);
    if (!transaction_server_non_invite)
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::send_response_200 -> Invalid transaction\n";
        return false;
    }

    SIP_Response *response = create_bye_response_200();
    if (!response)
        return false;

    if (!transaction_server_non_invite->match_transaction(response))
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::send_response_200 -> Failed to match transaction\n";
        delete response;
        return false;
    }

    _sent_message = false;

    if (!transaction_server_non_invite->send_2xx_6xx(response))
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::send_response_200 -> Failed to send response\n";
        delete response;
        return false;
    }

    if (!_sent_message)
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::send_response_200 -> Response not sent\n";
        delete response;
        return false;
    }

    if (transaction_server_non_invite->get_state() != SIP_Transaction_Server_Non_Invite::STATE_COMPLETED)
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::send_response_200 -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Completed" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_server_non_invite->get_state_str().c_str() << "\n";
        delete response;
        return false;
    }

    delete response;
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite_Test::wait_timer_J()
{
    SIP_Transaction_Server_Non_Invite *transaction_server_non_invite = dynamic_cast<SIP_Transaction_Server_Non_Invite *>(_transaction);
    if (!transaction_server_non_invite)
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::wait_timer_J -> Invalid transaction\n";
        return false;
    }

    unsigned long start = Util_Functions::get_tick();
    unsigned long max_wait_time = (SIP_Transaction::SIP_TIMER_1 * 64) + MAX_WAIT_TIME;

    while ((Util_Functions::get_tick() - start) < max_wait_time)
    {
        if (transaction_server_non_invite->get_state() == SIP_Transaction_Server_Non_Invite::STATE_TERMINATED)
            break;

        Util_Functions::delay(DELAY);
    }

    if (transaction_server_non_invite->get_state() != SIP_Transaction_Server_Non_Invite::STATE_TERMINATED)
    {
        std::cout << "SIP_Transaction_Server_Non_Invite_Test::wait_timer_J -> Invalid transaction state:\n";
        std::cout << std::setw(12) << "Expected: " << "Terminated" << "\n";
        std::cout << std::setw(12) << "State: " << transaction_server_non_invite->get_state_str().c_str() << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite_Accepted_Test::run()
{
    std::cout << "SIP transaction server non-invite accepted test initialized\n";

    if (!set_callbacks())
        return false;

    if (!receive_bye())
        return false;

    if (!send_response_100())
        return false;

    if (!send_response_200())
        return false;

    if (!wait_timer_J())
        return false;

    std::cout << "SIP transaction server non-invite accepted test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite_Retransmission_Test::run()
{
    std::cout << "SIP transaction server non-invite retransmission test initialized\n";

    if (!set_callbacks())
        return false;

    if (!receive_bye())
        return false;

    if (!send_response_200())
        return false;

    if (!receive_bye(true))
        return false;

    if (!wait_timer_J())
        return false;

    std::cout << "SIP transaction server non-invite retransmission test completed successfully\n";
    return true;
}

//-------------------------------------------
