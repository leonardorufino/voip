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

#include "sip_transactions.h"
#include "sip_functions.h"

//-------------------------------------------

SIP_Transaction::SIP_Transaction()
{
    _saved_request = NULL;

    for (unsigned short i = 0; i < SIP_TIMER_COUNT; i++)
    {
        _timer_values[i] = 0;
        _timer_ids[i] = Timer::INVALID_TIMER_ID;
    }
}

//-------------------------------------------

SIP_Transaction::~SIP_Transaction()
{
    for (unsigned short i = 0; i < SIP_TIMER_COUNT; i++)
    {
        if (_timer_ids[i] != Timer::INVALID_TIMER_ID)
            stop_timer((SIP_Timer) i);
    }

    if (_saved_request)
        delete _saved_request;
}

//-------------------------------------------

SIP_Transaction *SIP_Transaction::match_transaction(SIP_Message *msg)
{
    switch (get_transaction_type())
    {
        case SIP_TRANSACTION_CLIENT_INVITE:
        case SIP_TRANSACTION_CLIENT_NON_INVITE:
            if (msg->get_message_type() != SIP_RESPONSE)
            {
                std::cout << "SIP_Transaction::match_transaction -> Invalid message type (transaction=" << get_transaction_type() << "\n";
                return NULL;
            }

            return match_transaction_client(msg);

        case SIP_TRANSACTION_SERVER_INVITE:
            if ((msg->get_message_type() != SIP_REQUEST_INVITE) && (msg->get_message_type() != SIP_REQUEST_ACK))
            {
                std::cout << "SIP_Transaction::match_transaction -> Invalid message type (transaction=" << get_transaction_type() << "\n";
                return NULL;
            }

            return match_transaction_server(msg);

        case SIP_TRANSACTION_SERVER_NON_INVITE:
            if ((msg->get_message_type() == SIP_REQUEST_INVITE) || (msg->get_message_type() == SIP_REQUEST_ACK) ||
                (msg->get_message_type() == SIP_RESPONSE))
            {
                std::cout << "SIP_Transaction::match_transaction -> Invalid message type (transaction=" << get_transaction_type() << "\n";
                return NULL;
            }

            return match_transaction_server(msg);

        default:
            std::cout << "SIP_Transaction::match_transaction -> Invalid message type (transaction=" << get_transaction_type() << "\n";
            return NULL;
    }
}

//-------------------------------------------

SIP_Transaction *SIP_Transaction::match_transaction_client(SIP_Message *msg)
{
    if (!_saved_request)
    {
        std::cout << "SIP_Transaction::match_transaction_client -> Invalid saved request message\n";
        return NULL;
    }

    SIP_Header_Via *saved_request_via = dynamic_cast<SIP_Header_Via *>(_saved_request->get_header(SIP_HEADER_VIA));
    SIP_Header_CSeq *saved_request_cseq = dynamic_cast<SIP_Header_CSeq *>(_saved_request->get_header(SIP_HEADER_CSEQ));

    if ((!saved_request_via) || (!saved_request_cseq))
    {
        std::cout << "SIP_Transaction::match_transaction_client -> Failed to get Via or CSeq header from saved request\n";
        return NULL;
    }

    std::string saved_request_via_branch = saved_request_via->get_branch();
    SIP_Method_Type saved_request_cseq_method = saved_request_cseq->get_method();

    if ((saved_request_via_branch.empty()) || (saved_request_cseq_method == SIP_METHOD_TYPE_INVALID))
    {
        std::cout << "SIP_Transaction::match_transaction_client -> Invalid Via branch or CSeq method from saved request\n";
        return NULL;
    }

    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        std::cout << "SIP_Transaction::match_transaction_client -> Invalid response message\n";
        return NULL;
    }

    SIP_Header_Via *response_via = dynamic_cast<SIP_Header_Via *>(response->get_header(SIP_HEADER_VIA));
    SIP_Header_CSeq *response_cseq = dynamic_cast<SIP_Header_CSeq *>(response->get_header(SIP_HEADER_CSEQ));

    if ((!response_via) || (!response_cseq))
    {
        std::cout << "SIP_Transaction::match_transaction_client -> Failed to get Via or CSeq header from response\n";
        return NULL;
    }

    std::string response_via_branch = response_via->get_branch();
    SIP_Method_Type response_cseq_method = response_cseq->get_method();

    if ((response_via_branch.empty()) || (response_cseq_method == SIP_METHOD_TYPE_INVALID))
    {
        std::cout << "SIP_Transaction::match_transaction_client -> Invalid Via branch or CSeq method from response\n";
        return NULL;
    }

    if ((saved_request_via_branch != response_via_branch) || (saved_request_cseq_method != response_cseq_method))
    {
        std::cout << "SIP_Transaction::match_transaction_client -> Via branch or CSeq method do not match\n";
        return NULL;
    }

    return this;
}

//-------------------------------------------

SIP_Transaction *SIP_Transaction::match_transaction_server(SIP_Message *msg)
{
    if (!_saved_request)
    {
        std::cout << "SIP_Transaction::match_transaction_server -> Invalid saved request message\n";
        return NULL;
    }

    SIP_Header_Via *saved_request_via = dynamic_cast<SIP_Header_Via *>(_saved_request->get_header(SIP_HEADER_VIA));

    if (!saved_request_via)
    {
        std::cout << "SIP_Transaction::match_transaction_server -> Failed to get Via header from saved request\n";
        return NULL;
    }

    SIP_Method_Type saved_request_method = _saved_request->get_message_type();
    std::string saved_request_via_branch = saved_request_via->get_branch();
    std::string saved_request_via_host = saved_request_via->get_host();
    unsigned short saved_request_via_port = saved_request_via->get_port();

    if ((saved_request_method == SIP_METHOD_TYPE_INVALID) || (saved_request_via_branch.empty()) || (saved_request_via_host.empty()))
    {
        std::cout << "SIP_Transaction::match_transaction_server -> Invalid method, Via branch or Via host from saved request\n";
        return NULL;
    }

    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        std::cout << "SIP_Transaction::match_transaction_server -> Invalid request message\n";
        return NULL;
    }

    SIP_Header_Via *request_via = dynamic_cast<SIP_Header_Via *>(request->get_header(SIP_HEADER_VIA));

    if (!request_via)
    {
        std::cout << "SIP_Transaction::match_transaction_server -> Failed to get Via header from request\n";
        return NULL;
    }

    SIP_Method_Type request_method = request->get_message_type();
    std::string request_via_branch = request_via->get_branch();
    std::string request_via_host = request_via->get_host();
    unsigned short request_via_port = request_via->get_port();

    if ((request_method == SIP_METHOD_TYPE_INVALID) || (request_via_host.empty()))
    {
        std::cout << "SIP_Transaction::match_transaction_server -> Invalid method or Via host from request\n";
        return NULL;
    }

    bool magic_cookie = false; // SIP 2.0
    if ((!request_via_branch.empty()) && (SIP_Functions::start_with(request_via_branch.c_str(), "z9hG4bK")))
        magic_cookie = true;

    if (!magic_cookie)
    {
        std::cout << "SIP_Transaction::match_transaction_server -> Invalid Via branch from request (magic cookie is not present)\n";
        return NULL;
    }

    if ((request_via_branch != saved_request_via_branch) || (request_via_host != saved_request_via_host) ||
        ((request_method != saved_request_method) && ((saved_request_method != SIP_REQUEST_INVITE) ||
         (request_method != SIP_REQUEST_ACK))))
    {
        std::cout << "SIP_Transaction::match_transaction_server -> Method, Via branch or Via host do not match\n";
        return NULL;
    }

    return this;
}

//-------------------------------------------

unsigned long SIP_Transaction::get_timer_value(SIP_Timer timer)
{
    if (timer >= SIP_TIMER_COUNT)
    {
        std::cout << "SIP_Transaction::get_timer_value -> Invalid timer (timer=" << timer << ")\n";
        return 0;
    }

    return _timer_values[timer];
}

//-------------------------------------------

void SIP_Transaction::set_timer_value(SIP_Timer timer, unsigned long timer_value)
{
    if (timer >= SIP_TIMER_COUNT)
    {
        std::cout << "SIP_Transaction::set_timer_value -> Invalid timer (timer=" << timer << ")\n";
        return;
    }

    _timer_values[timer] = timer_value;
}

//-------------------------------------------

void SIP_Transaction::start_timer(SIP_Timer timer, SIP_Transaction *p)
{
    Timer_Manager &tm = Timer_Manager::instance();

    switch (timer)
    {
        case SIP_TIMER_A:
            _timer_ids[SIP_TIMER_A] = tm.start_timer(_timer_values[timer], p, SIP_Transaction_Client_Invite::timer_A_Callback);
            break;
        case SIP_TIMER_B:
            _timer_ids[SIP_TIMER_B] = tm.start_timer(_timer_values[timer], p, SIP_Transaction_Client_Invite::timer_B_Callback);
            break;
        //case SIP_TIMER_C:
        //    _timer_ids[SIP_TIMER_C] = tm.start_timer(_timer_values[timer], p, timer_C_Callback);
        //    break;
        case SIP_TIMER_D:
            _timer_ids[SIP_TIMER_D] = tm.start_timer(_timer_values[timer], p, SIP_Transaction_Client_Invite::timer_D_Callback);
            break;
        case SIP_TIMER_E:
            _timer_ids[SIP_TIMER_E] = tm.start_timer(_timer_values[timer], p, SIP_Transaction_Client_Non_Invite::timer_E_Callback);
            break;
        case SIP_TIMER_F:
            _timer_ids[SIP_TIMER_F] = tm.start_timer(_timer_values[timer], p, SIP_Transaction_Client_Non_Invite::timer_F_Callback);
            break;
        case SIP_TIMER_G:
            _timer_ids[SIP_TIMER_G] = tm.start_timer(_timer_values[timer], p, SIP_Transaction_Server_Invite::timer_G_Callback);
            break;
        case SIP_TIMER_H:
            _timer_ids[SIP_TIMER_H] = tm.start_timer(_timer_values[timer], p, SIP_Transaction_Server_Invite::timer_H_Callback);
            break;
        case SIP_TIMER_I:
            _timer_ids[SIP_TIMER_I] = tm.start_timer(_timer_values[timer], p, SIP_Transaction_Server_Invite::timer_I_Callback);
            break;
        case SIP_TIMER_J:
            _timer_ids[SIP_TIMER_J] = tm.start_timer(_timer_values[timer], p, SIP_Transaction_Server_Non_Invite::timer_J_Callback);
            break;
        case SIP_TIMER_K:
            _timer_ids[SIP_TIMER_K] = tm.start_timer(_timer_values[timer], p, SIP_Transaction_Client_Non_Invite::timer_K_Callback);
            break;
        default:
            std::cout << "SIP_Transaction::start_timer -> Invalid timer (timer=" << timer << ")\n";
            return;
    }

    std::cout << "SIP_Transaction::start_timer -> Timer started (timer=" << timer << ")\n";
}

//-------------------------------------------

void SIP_Transaction::stop_timer(SIP_Timer timer)
{
    if (_timer_ids[timer] != Timer::INVALID_TIMER_ID)
    {
        Timer_Manager &tm = Timer_Manager::instance();
        tm.stop_timer(_timer_ids[timer]);

        _timer_ids[timer] = Timer::INVALID_TIMER_ID;

        std::cout << "SIP_Transaction::stop_timer -> Timer stopped (timer=" << timer << ")\n";
    }else
        std::cout << "SIP_Transaction::stop_timer -> Timer not started (timer=" << timer << ")\n";
}

//-------------------------------------------
