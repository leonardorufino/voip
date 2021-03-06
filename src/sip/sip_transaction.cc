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

#include "sip_transaction.h"
#include "util/string_functions.h"

Logger SIP_Transaction::_logger(Log_Manager::LOG_SIP_TRANSACTION);

//-------------------------------------------

SIP_Transaction::SIP_Transaction(SIP_Object_ID id) : _id(id), _saved_request(NULL), _send_message_callback(NULL),
    _send_message_callback_data(NULL), _receive_request_callback(NULL), _receive_request_callback_data(NULL),
    _receive_response_callback(NULL), _receive_response_callback_data(NULL)
{
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

bool SIP_Transaction::match_transaction(SIP_Message *msg)
{
    SIP_Transaction_Type transaction_type = get_transaction_type();
    SIP_Method_Type message_type = msg->get_message_type();

    switch (transaction_type)
    {
        case SIP_TRANSACTION_CLIENT_INVITE:
            if (message_type == SIP_RESPONSE)
                return match_transaction_response(msg);

            else if ((message_type == SIP_REQUEST_INVITE) || (message_type == SIP_REQUEST_ACK))
                return match_transaction_request(msg);

            return false;

        case SIP_TRANSACTION_CLIENT_NON_INVITE:
            if (message_type == SIP_RESPONSE)
                return match_transaction_response(msg);

            else if ((message_type != SIP_REQUEST_INVITE) && (message_type != SIP_REQUEST_ACK))
                return match_transaction_request(msg);

            return false;

        case SIP_TRANSACTION_SERVER_INVITE:
            if (message_type == SIP_RESPONSE)
                return match_transaction_response(msg);

            else if ((message_type == SIP_REQUEST_INVITE) || (message_type == SIP_REQUEST_ACK))
                return match_transaction_request(msg);

            return false;

        case SIP_TRANSACTION_SERVER_NON_INVITE:
            if (message_type == SIP_RESPONSE)
                return match_transaction_response(msg);

            else if ((message_type != SIP_REQUEST_INVITE) && (message_type != SIP_REQUEST_ACK))
                return match_transaction_request(msg);

            return false;

        default:
            _logger.warning("Failed to match transaction: invalid transaction type (type=%d) [%s]",
                            transaction_type, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction::match_transaction_response(SIP_Message *msg)
{
    if (!_saved_request)
    {
        //_logger.trace("Failed to match transaction response: invalid saved request message [%s]", _id.to_string().c_str());
        return false;
    }

    SIP_Header_Via *saved_request_via = dynamic_cast<SIP_Header_Via *>(_saved_request->get_header(SIP_HEADER_VIA));
    SIP_Header_CSeq *saved_request_cseq = dynamic_cast<SIP_Header_CSeq *>(_saved_request->get_header(SIP_HEADER_CSEQ));

    if ((!saved_request_via) || (!saved_request_cseq))
    {
        _logger.warning("Failed to match transaction response: invalid Via or CSeq header from saved request [%s]",
                        _id.to_string().c_str());
        return false;
    }

    std::string saved_request_via_branch = saved_request_via->get_branch();
    SIP_Method_Type saved_request_cseq_method = saved_request_cseq->get_method_enum();

    if ((saved_request_via_branch.empty()) || (saved_request_cseq_method == SIP_METHOD_INVALID))
    {
        _logger.warning("Failed to match transaction response: invalid Via branch or CSeq method from saved request [%s]",
                        _id.to_string().c_str());
        return false;
    }

    SIP_Response *response = dynamic_cast<SIP_Response *>(msg);
    if (!response)
    {
        _logger.warning("Failed to match transaction response: invalid response message [%s]", _id.to_string().c_str());
        return false;
    }

    SIP_Header_Via *response_via = dynamic_cast<SIP_Header_Via *>(response->get_header(SIP_HEADER_VIA));
    SIP_Header_CSeq *response_cseq = dynamic_cast<SIP_Header_CSeq *>(response->get_header(SIP_HEADER_CSEQ));

    if ((!response_via) || (!response_cseq))
    {
        _logger.warning("Failed to match transaction response: invalid Via or CSeq header from response [%s]", _id.to_string().c_str());
        return false;
    }

    std::string response_via_branch = response_via->get_branch();
    SIP_Method_Type response_cseq_method = response_cseq->get_method_enum();

    if ((response_via_branch.empty()) || (response_cseq_method == SIP_METHOD_INVALID))
    {
        _logger.warning("Failed to match transaction response: invalid Via branch or CSeq method from response [%s]",
                        _id.to_string().c_str());
        return false;
    }

    if ((saved_request_via_branch != response_via_branch) || (saved_request_cseq_method != response_cseq_method))
    {
        _logger.trace("Failed to match transaction response: Via branch or CSeq method do not match [%s]", _id.to_string().c_str());
        return false;
    }

    _logger.trace("Transaction response matched [%s]", _id.to_string().c_str());
    return true;
}

//-------------------------------------------

bool SIP_Transaction::match_transaction_request(SIP_Message *msg)
{
    if (!_saved_request)
    {
        //_logger.trace("Failed to match transaction request: invalid saved request message [%s]", _id.to_string().c_str());
        return false;
    }

    SIP_Header_Via *saved_request_via = dynamic_cast<SIP_Header_Via *>(_saved_request->get_header(SIP_HEADER_VIA));
    if (!saved_request_via)
    {
        _logger.warning("Failed to match transaction request: invalid Via header from saved request [%s]", _id.to_string().c_str());
        return false;
    }

    SIP_Method_Type saved_request_method = _saved_request->get_message_type();
    std::string saved_request_via_branch = saved_request_via->get_branch();
    std::string saved_request_via_host = saved_request_via->get_host().get_address();
    unsigned short saved_request_via_port = saved_request_via->get_port();

    if ((saved_request_method == SIP_METHOD_INVALID) || (saved_request_via_branch.empty()) || (saved_request_via_host.empty()))
    {
        _logger.warning("Failed to match transaction request: invalid request method, Via branch or Via host from saved request [%s]",
                        _id.to_string().c_str());
        return false;
    }

    SIP_Request *request = dynamic_cast<SIP_Request *>(msg);
    if (!request)
    {
        _logger.warning("Failed to match transaction request: invalid request message [%s]", _id.to_string().c_str());
        return false;
    }

    SIP_Header_Via *request_via = dynamic_cast<SIP_Header_Via *>(request->get_header(SIP_HEADER_VIA));
    if (!request_via)
    {
        _logger.warning("Failed to match transaction request: invalid Via header from request [%s]", _id.to_string().c_str());
        return false;
    }

    SIP_Method_Type request_method = request->get_message_type();
    std::string request_via_branch = request_via->get_branch();
    std::string request_via_host = request_via->get_host().get_address();
    unsigned short request_via_port = request_via->get_port();

    if ((request_method == SIP_METHOD_INVALID) || (request_via_host.empty()))
    {
        _logger.warning("Failed to match transaction request: invalid request method or Via host from request [%s]",
                        _id.to_string().c_str());
        return false;
    }

    bool magic_cookie = false; // SIP 2.0
    if ((!request_via_branch.empty()) && (String_Functions::start_with(request_via_branch.c_str(), "z9hG4bK")))
        magic_cookie = true;

    if (!magic_cookie)
    {
        _logger.warning("Failed to match transaction request: invalid Via branch from request (magic cookie is not present) [%s]",
                        _id.to_string().c_str());
        return false;
    }

    if ((request_via_branch != saved_request_via_branch) || (request_via_host != saved_request_via_host) ||
        (request_via_port != saved_request_via_port) || ((request_method != saved_request_method) &&
        ((saved_request_method != SIP_REQUEST_INVITE) || (request_method != SIP_REQUEST_ACK))))
    {
        _logger.trace("Failed to match transaction request: request method, Via branch, host or port do not match [%s]",
                      _id.to_string().c_str());
        return false;
    }

    _logger.trace("Transaction request matched [%s]", _id.to_string().c_str());
    return true;
}

//-------------------------------------------

void SIP_Transaction::set_send_message_callback(send_message_callback *callback, void *data)
{
    _send_message_callback = callback;
    _send_message_callback_data = data;
}

//-------------------------------------------

void SIP_Transaction::set_receive_request_callback(receive_request_callback *callback, void *data)
{
    _receive_request_callback = callback;
    _receive_request_callback_data = data;
}

//-------------------------------------------

void SIP_Transaction::set_receive_response_callback(receive_response_callback *callback, void *data)
{
    _receive_response_callback = callback;
    _receive_response_callback_data = data;
}

//-------------------------------------------

unsigned long SIP_Transaction::get_timer_value(SIP_Timer timer)
{
    if (timer >= SIP_TIMER_COUNT)
    {
        _logger.warning("Failed to get timer value: invalid timer (timer=%d) [%s]", timer, _id.to_string().c_str());
        return 0;
    }

    return _timer_values[timer];
}

//-------------------------------------------

void SIP_Transaction::set_timer_value(SIP_Timer timer, unsigned long timer_value)
{
    if (timer >= SIP_TIMER_COUNT)
    {
        _logger.warning("Failed to set timer value: invalid timer (timer=%d) [%s]", timer, _id.to_string().c_str());
        return;
    }

    _timer_values[timer] = timer_value;
}

//-------------------------------------------

void SIP_Transaction::start_timer(SIP_Timer timer)
{
    Timer_Manager &tm = Timer_Manager::instance();

    switch (timer)
    {
        case SIP_TIMER_A:
            _timer_ids[SIP_TIMER_A] = tm.start_timer(_timer_values[timer], this, SIP_Transaction_Client_Invite::timer_A_callback);
            break;
        case SIP_TIMER_B:
            _timer_ids[SIP_TIMER_B] = tm.start_timer(_timer_values[timer], this, SIP_Transaction_Client_Invite::timer_B_callback);
            break;
        case SIP_TIMER_D:
            _timer_ids[SIP_TIMER_D] = tm.start_timer(_timer_values[timer], this, SIP_Transaction_Client_Invite::timer_D_callback);
            break;
        case SIP_TIMER_E:
            _timer_ids[SIP_TIMER_E] = tm.start_timer(_timer_values[timer], this, SIP_Transaction_Client_Non_Invite::timer_E_callback);
            break;
        case SIP_TIMER_F:
            _timer_ids[SIP_TIMER_F] = tm.start_timer(_timer_values[timer], this, SIP_Transaction_Client_Non_Invite::timer_F_callback);
            break;
        case SIP_TIMER_G:
            _timer_ids[SIP_TIMER_G] = tm.start_timer(_timer_values[timer], this, SIP_Transaction_Server_Invite::timer_G_callback);
            break;
        case SIP_TIMER_H:
            _timer_ids[SIP_TIMER_H] = tm.start_timer(_timer_values[timer], this, SIP_Transaction_Server_Invite::timer_H_callback);
            break;
        case SIP_TIMER_I:
            _timer_ids[SIP_TIMER_I] = tm.start_timer(_timer_values[timer], this, SIP_Transaction_Server_Invite::timer_I_callback);
            break;
        case SIP_TIMER_J:
            _timer_ids[SIP_TIMER_J] = tm.start_timer(_timer_values[timer], this, SIP_Transaction_Server_Non_Invite::timer_J_callback);
            break;
        case SIP_TIMER_K:
            _timer_ids[SIP_TIMER_K] = tm.start_timer(_timer_values[timer], this, SIP_Transaction_Client_Non_Invite::timer_K_callback);
            break;
        default:
            _logger.warning("Failed to start timer: invalid timer (timer=%d) [%s]", timer, _id.to_string().c_str());
            return;
    }

    _logger.trace("Timer started (timer=%d) [%s]", timer, _id.to_string().c_str());
}

//-------------------------------------------

void SIP_Transaction::stop_timer(SIP_Timer timer)
{
    if (timer >= SIP_TIMER_COUNT)
    {
        _logger.warning("Failed to stop timer: invalid timer (timer=%d) [%s]", timer, _id.to_string().c_str());
        return;
    }

    if (_timer_ids[timer] == Timer::INVALID_TIMER_ID)
    {
        _logger.warning("Failed to stop timer: timer not started (timer=%d) [%s]", timer, _id.to_string().c_str());
        return;
    }

    Timer_Manager &tm = Timer_Manager::instance();
    tm.stop_timer(_timer_ids[timer]);

    _timer_ids[timer] = Timer::INVALID_TIMER_ID;
    _logger.trace("Timer stopped (timer=%d) [%s]", timer, _id.to_string().c_str());
}

//-------------------------------------------
//-------------------------------------------

std::string SIP_Transaction_Client_Invite::get_state_str()
{
    switch (_state)
    {
        case STATE_IDLE:        return "Idle";
        case STATE_CALLING:     return "Calling";
        case STATE_PROCEEDING:  return "Proceeding";
        case STATE_COMPLETED:   return "Completed";
        case STATE_TERMINATED:  return "Terminated";
        default:                return "Invalid";
    }
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite::send_invite(SIP_Request *msg)
{
    switch (_state)
    {
        case STATE_IDLE:
            _state = STATE_CALLING;
            _saved_request = new SIP_Request(*msg);

            if (_send_message_callback)
            {
                if (!_send_message_callback(_send_message_callback_data, this, _saved_request))
                    return false;
            }

            set_timer_value(SIP_TIMER_A, SIP_TIMER_1);
            start_timer(SIP_TIMER_A);
            set_timer_value(SIP_TIMER_B, SIP_TIMER_1 * 64);
            start_timer(SIP_TIMER_B);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite::send_ack(SIP_Response *msg)
{
    if (!_saved_request)
    {
        _logger.warning("Failed to send ack: invalid saved request message [%s]", _id.to_string().c_str());
        return false;
    }

    SIP_Address &saved_request_uri = _saved_request->get_request_uri();
    SIP_Header_Call_ID *saved_request_call_id = dynamic_cast<SIP_Header_Call_ID *>(_saved_request->get_header(SIP_HEADER_CALL_ID));
    SIP_Header_CSeq *saved_request_cseq = dynamic_cast<SIP_Header_CSeq *>(_saved_request->get_header(SIP_HEADER_CSEQ));
    SIP_Header_From *saved_request_from = dynamic_cast<SIP_Header_From *>(_saved_request->get_header(SIP_HEADER_FROM));
    SIP_Header_To *saved_request_to = dynamic_cast<SIP_Header_To *>(_saved_request->get_header(SIP_HEADER_TO));
    SIP_Header_Via *saved_request_via = dynamic_cast<SIP_Header_Via *>(_saved_request->get_header(SIP_HEADER_VIA));

    if ((!saved_request_call_id) || (!saved_request_cseq) || (!saved_request_from) || (!saved_request_to) || (!saved_request_via))
    {
        _logger.warning("Failed to send ack: invalid headers from saved request [%s]", _id.to_string().c_str());
        return false;
    }

    SIP_Request ack(SIP_REQUEST_ACK);
    ack.set_request_line(SIP_REQUEST_ACK, saved_request_uri, SIP_VERSION);
    ack.add_header(new SIP_Header_Call_ID(*saved_request_call_id));
    ack.add_header(new SIP_Header_From(*saved_request_from));
    ack.add_header(new SIP_Header_To(*saved_request_to)); // TODO: tag
    ack.add_header(new SIP_Header_Via(*saved_request_via));

    SIP_Header_Max_Forwards *header_max_forwards = new SIP_Header_Max_Forwards();
    header_max_forwards->set_max_forwards(70);
    ack.add_header(header_max_forwards);

    SIP_Header_CSeq *header_cseq = new SIP_Header_CSeq();
    header_cseq->set_sequence(saved_request_cseq->get_sequence());
    header_cseq->set_method(SIP_REQUEST_ACK);
    ack.add_header(header_cseq);

    unsigned short route_count = _saved_request->get_header_size(SIP_HEADER_ROUTE);
    for (unsigned short i = 0; i < route_count; i++)
    {
        SIP_Header_Route *header = (SIP_Header_Route *) _saved_request->get_header(SIP_HEADER_ROUTE, i);
        ack.add_header(new SIP_Header_Route(*header));
    }

    if (_send_message_callback)
        return _send_message_callback(_send_message_callback_data, this, &ack);

    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite::receive_1xx(SIP_Response *msg)
{
    switch (_state)
    {
        case STATE_CALLING:
            _state = STATE_PROCEEDING;
            stop_timer(SIP_TIMER_A);
            stop_timer(SIP_TIMER_B);

            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, _saved_request, msg);
            return true;

        case STATE_PROCEEDING:
            //_state = STATE_PROCEEDING;
            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, _saved_request, msg);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite::receive_2xx(SIP_Response *msg)
{
    switch (_state)
    {
        case STATE_CALLING:
            _state = STATE_TERMINATED;
            stop_timer(SIP_TIMER_A);
            stop_timer(SIP_TIMER_B);

            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, _saved_request, msg);
            return true;

        case STATE_PROCEEDING:
            _state = STATE_TERMINATED;
            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, _saved_request, msg);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite::receive_3xx_6xx(SIP_Response *msg)
{
    switch (_state)
    {
        case STATE_CALLING:
            _state = STATE_COMPLETED;
            send_ack(msg);
            set_timer_value(SIP_TIMER_D, SIP_TIMER_32s);
            start_timer(SIP_TIMER_D);
            stop_timer(SIP_TIMER_A);
            stop_timer(SIP_TIMER_B);

            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, _saved_request, msg);
            return true;

        case STATE_PROCEEDING:
            _state = STATE_COMPLETED;
            send_ack(msg);
            set_timer_value(SIP_TIMER_D, SIP_TIMER_32s);
            start_timer(SIP_TIMER_D);

            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, _saved_request, msg);
            return true;

        case STATE_COMPLETED:
            //_state = STATE_COMPLETED;
            return send_ack(msg);

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite::timer_A_expired()
{
    switch (_state)
    {
        case STATE_CALLING:
            //_state = STATE_CALLING;
            set_timer_value(SIP_TIMER_A, get_timer_value(SIP_TIMER_A) * 2);
            start_timer(SIP_TIMER_A);

            if (_send_message_callback)
                return _send_message_callback(_send_message_callback_data, this, _saved_request);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite::timer_B_expired()
{
    switch (_state)
    {
        case STATE_CALLING:
        {
            _state = STATE_TERMINATED;
            stop_timer(SIP_TIMER_A);

            SIP_Response response(408, *_saved_request);

            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, _saved_request, &response);
            return true;
        }

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite::timer_D_expired()
{
    switch (_state)
    {
        case STATE_COMPLETED:
            _state = STATE_TERMINATED;
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite::timer_A_callback(void *p)
{
    SIP_Transaction_Client_Invite *transaction = reinterpret_cast<SIP_Transaction_Client_Invite *>(p);
    if (!transaction)
    {
        _logger.warning("Invalid timer A callback parameter");
        return false;
    }

    transaction->_timer_ids[SIP_TIMER_A] = Timer::INVALID_TIMER_ID;
    transaction->timer_A_expired();
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite::timer_B_callback(void *p)
{
    SIP_Transaction_Client_Invite *transaction = reinterpret_cast<SIP_Transaction_Client_Invite *>(p);
    if (!transaction)
    {
        _logger.warning("Invalid timer B callback parameter");
        return false;
    }

    transaction->_timer_ids[SIP_TIMER_B] = Timer::INVALID_TIMER_ID;
    transaction->timer_B_expired();
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Invite::timer_D_callback(void *p)
{
    SIP_Transaction_Client_Invite *transaction = reinterpret_cast<SIP_Transaction_Client_Invite *>(p);
    if (!transaction)
    {
        _logger.warning("Invalid timer D callback parameter");
        return false;
    }

    transaction->_timer_ids[SIP_TIMER_D] = Timer::INVALID_TIMER_ID;
    transaction->timer_D_expired();
    return true;
}

//-------------------------------------------
//-------------------------------------------

std::string SIP_Transaction_Client_Non_Invite::get_state_str()
{
    switch (_state)
    {
        case STATE_IDLE:        return "Idle";
        case STATE_TRYING:      return "Trying";
        case STATE_PROCEEDING:  return "Proceeding";
        case STATE_COMPLETED:   return "Completed";
        case STATE_TERMINATED:  return "Terminated";
        default:                return "Invalid";
    }
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite::send_request(SIP_Request *msg)
{
    switch (_state)
    {
        case STATE_IDLE:
            _state = STATE_TRYING;
            _saved_request = new SIP_Request(*msg);

            if (_send_message_callback)
            {
                if (!_send_message_callback(_send_message_callback_data, this, _saved_request))
                    return false;
            }

            set_timer_value(SIP_TIMER_E, SIP_TIMER_1);
            start_timer(SIP_TIMER_E);
            set_timer_value(SIP_TIMER_F, SIP_TIMER_1 * 64);
            start_timer(SIP_TIMER_F);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite::receive_1xx(SIP_Response *msg)
{
    switch (_state)
    {
        case STATE_TRYING:
        case STATE_PROCEEDING:
            _state = STATE_PROCEEDING;
            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, _saved_request, msg);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite::receive_2xx_6xx(SIP_Response *msg)
{
    switch (_state)
    {
        case STATE_TRYING:
        case STATE_PROCEEDING:
            _state = STATE_COMPLETED;
            set_timer_value(SIP_TIMER_K, SIP_TIMER_4);
            start_timer(SIP_TIMER_K);
            stop_timer(SIP_TIMER_E);
            stop_timer(SIP_TIMER_F);

            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, _saved_request, msg);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite::timer_E_expired()
{
    switch (_state)
    {
        case STATE_TRYING:
        {
            //_state = STATE_TRYING;
            unsigned long value = ((get_timer_value(SIP_TIMER_E) * 2) < SIP_TIMER_2) ? get_timer_value(SIP_TIMER_E) * 2 : SIP_TIMER_2;
            set_timer_value(SIP_TIMER_E, value);
            start_timer(SIP_TIMER_E);

            if (_send_message_callback)
                return _send_message_callback(_send_message_callback_data, this, _saved_request);
            return true;
        }

        case STATE_PROCEEDING:
            //_state = STATE_PROCEEDING;
            set_timer_value(SIP_TIMER_E, SIP_TIMER_2);
            start_timer(SIP_TIMER_E);

            if (_send_message_callback)
                return _send_message_callback(_send_message_callback_data, this, _saved_request);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite::timer_F_expired()
{
    switch (_state)
    {
        case STATE_TRYING:
        case STATE_PROCEEDING:
        {
            _state = STATE_TERMINATED;
            stop_timer(SIP_TIMER_E);

            SIP_Response response(408, *_saved_request);

            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, _saved_request, &response);
            return true;
        }

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite::timer_K_expired()
{
    switch (_state)
    {
        case STATE_COMPLETED:
            _state = STATE_TERMINATED;
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite::timer_E_callback(void *p)
{
    SIP_Transaction_Client_Non_Invite *transaction = reinterpret_cast<SIP_Transaction_Client_Non_Invite *>(p);
    if (!transaction)
    {
        _logger.warning("Invalid timer E callback parameter");
        return false;
    }

    transaction->_timer_ids[SIP_TIMER_E] = Timer::INVALID_TIMER_ID;
    transaction->timer_E_expired();
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite::timer_F_callback(void *p)
{
    SIP_Transaction_Client_Non_Invite *transaction = reinterpret_cast<SIP_Transaction_Client_Non_Invite *>(p);
    if (!transaction)
    {
        _logger.warning("Invalid timer F callback parameter");
        return false;
    }

    transaction->_timer_ids[SIP_TIMER_F] = Timer::INVALID_TIMER_ID;
    transaction->timer_F_expired();
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Client_Non_Invite::timer_K_callback(void *p)
{
    SIP_Transaction_Client_Non_Invite *transaction = reinterpret_cast<SIP_Transaction_Client_Non_Invite *>(p);
    if (!transaction)
    {
        _logger.warning("Invalid timer K callback parameter");
        return false;
    }

    transaction->_timer_ids[SIP_TIMER_K] = Timer::INVALID_TIMER_ID;
    transaction->timer_K_expired();
    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Transaction_Server_Invite::~SIP_Transaction_Server_Invite()
{
    if (_last_response)
        delete _last_response;
}

//-------------------------------------------

std::string SIP_Transaction_Server_Invite::get_state_str()
{
    switch (_state)
    {
        case STATE_IDLE:        return "Idle";
        case STATE_PROCEEDING:  return "Proceeding";
        case STATE_COMPLETED:   return "Completed";
        case STATE_CONFIRMED:   return "Confirmed";
        case STATE_TERMINATED:  return "Terminated";
        default:                return "Invalid";
    }
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite::receive_invite(SIP_Request *msg)
{
    switch (_state)
    {
        case STATE_IDLE:
            _state = STATE_PROCEEDING;
            _saved_request = new SIP_Request(*msg);

            if (_receive_request_callback)
                return _receive_request_callback(_receive_request_callback_data, this, _saved_request);
            return true;

        case STATE_PROCEEDING:
            //_state = STATE_PROCEEDING;
            if ((_last_response) && (_send_message_callback))
                return _send_message_callback(_send_message_callback_data, this, _last_response);
            return true;

        case STATE_COMPLETED:
            //_state = STATE_COMPLETED;
            if ((_last_response) && (_send_message_callback))
                return _send_message_callback(_send_message_callback_data, this, _last_response);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite::receive_ack(SIP_Request *msg)
{
    switch (_state)
    {
        case STATE_COMPLETED:
            _state = STATE_CONFIRMED;
            set_timer_value(SIP_TIMER_I, SIP_TIMER_4);
            start_timer(SIP_TIMER_I);
            stop_timer(SIP_TIMER_G);
            stop_timer(SIP_TIMER_H);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite::send_1xx(SIP_Response *msg)
{
    switch (_state)
    {
        case STATE_PROCEEDING:
            //_state = STATE_PROCEEDING;
            if (_last_response)
                delete _last_response;
            _last_response = new SIP_Response(*msg);

            if ((_last_response) && (_send_message_callback))
                return _send_message_callback(_send_message_callback_data, this, _last_response);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite::send_2xx(SIP_Response *msg)
{
    switch (_state)
    {
        case STATE_PROCEEDING:
            _state = STATE_TERMINATED;
            if (_send_message_callback)
                return _send_message_callback(_send_message_callback_data, this, msg);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite::send_3xx_6xx(SIP_Response *msg)
{
    switch (_state)
    {
        case STATE_PROCEEDING:
            _state = STATE_COMPLETED;
            if (_last_response)
                delete _last_response;
            _last_response = new SIP_Response(*msg);

            if ((_last_response) && (_send_message_callback))
            {
                if (!_send_message_callback(_send_message_callback_data, this, _last_response))
                    return false;
            }

            set_timer_value(SIP_TIMER_G, SIP_TIMER_1);
            start_timer(SIP_TIMER_G);
            set_timer_value(SIP_TIMER_H, SIP_TIMER_1 * 64);
            start_timer(SIP_TIMER_H);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite::timer_G_expired()
{
    switch (_state)
    {
        case STATE_COMPLETED:
        {
            //_state = STATE_COMPLETED;
            unsigned long value = ((get_timer_value(SIP_TIMER_G) * 2) < SIP_TIMER_2) ? get_timer_value(SIP_TIMER_G) * 2 : SIP_TIMER_2;
            set_timer_value(SIP_TIMER_G, value);
            start_timer(SIP_TIMER_G);

            if ((_last_response) && (_send_message_callback))
                return _send_message_callback(_send_message_callback_data, this, _last_response);
            return true;
        }

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite::timer_H_expired()
{
    switch (_state)
    {
        case STATE_COMPLETED:
            _state = STATE_TERMINATED;
            stop_timer(SIP_TIMER_G);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite::timer_I_expired()
{
    switch (_state)
    {
        case STATE_CONFIRMED:
            _state = STATE_TERMINATED;
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite::timer_G_callback(void *p)
{
    SIP_Transaction_Server_Invite *transaction = reinterpret_cast<SIP_Transaction_Server_Invite *>(p);
    if (!transaction)
    {
        _logger.warning("Invalid timer G callback parameter");
        return false;
    }

    transaction->_timer_ids[SIP_TIMER_G] = Timer::INVALID_TIMER_ID;
    transaction->timer_G_expired();
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite::timer_H_callback(void *p)
{
    SIP_Transaction_Server_Invite *transaction = reinterpret_cast<SIP_Transaction_Server_Invite *>(p);
    if (!transaction)
    {
        _logger.warning("Invalid timer H callback parameter");
        return false;
    }

    transaction->_timer_ids[SIP_TIMER_H] = Timer::INVALID_TIMER_ID;
    transaction->timer_H_expired();
    return true;
}

//-------------------------------------------

bool SIP_Transaction_Server_Invite::timer_I_callback(void *p)
{
    SIP_Transaction_Server_Invite *transaction = reinterpret_cast<SIP_Transaction_Server_Invite *>(p);
    if (!transaction)
    {
        _logger.warning("Invalid timer I callback parameter");
        return false;
    }

    transaction->_timer_ids[SIP_TIMER_I] = Timer::INVALID_TIMER_ID;
    transaction->timer_I_expired();
    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Transaction_Server_Non_Invite::~SIP_Transaction_Server_Non_Invite()
{
    if (_last_response)
        delete _last_response;
}

//-------------------------------------------

std::string SIP_Transaction_Server_Non_Invite::get_state_str()
{
    switch (_state)
    {
        case STATE_IDLE:        return "Idle";
        case STATE_TRYING:      return "Trying";
        case STATE_PROCEEDING:  return "Proceeding";
        case STATE_COMPLETED:   return "Completed";
        case STATE_TERMINATED:  return "Terminated";
        default:                return "Invalid";
    }
}

//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite::receive_request(SIP_Request *msg)
{
    switch (_state)
    {
        case STATE_IDLE:
            _state = STATE_TRYING;
            _saved_request = new SIP_Request(*msg);

            if (_receive_request_callback)
                return _receive_request_callback(_receive_request_callback_data, this, _saved_request);
            return true;

        case STATE_PROCEEDING:
            //_state = STATE_PROCEEDING;
            if ((_last_response) && (_send_message_callback))
                return _send_message_callback(_send_message_callback_data, this, _last_response);
            return true;

        case STATE_COMPLETED:
            //_state = STATE_COMPLETED;
            if ((_last_response) && (_send_message_callback))
                return _send_message_callback(_send_message_callback_data, this, _last_response);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite::send_1xx(SIP_Response *msg)
{
    switch (_state)
    {
        case STATE_TRYING:
        case STATE_PROCEEDING:
            _state = STATE_PROCEEDING;
            if (_last_response)
                delete _last_response;
            _last_response = new SIP_Response(*msg);

            if ((_last_response) && (_send_message_callback))
                return _send_message_callback(_send_message_callback_data, this, _last_response);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite::send_2xx_6xx(SIP_Response *msg)
{
    switch (_state)
    {
        case STATE_TRYING:
        case STATE_PROCEEDING:
            _state = STATE_COMPLETED;
            if (_last_response)
                delete _last_response;
            _last_response = new SIP_Response(*msg);

            if ((_last_response) && (_send_message_callback))
            {
                if (!_send_message_callback(_send_message_callback_data, this, _last_response))
                    return false;
            }

            set_timer_value(SIP_TIMER_J, SIP_TIMER_1 * 64);
            start_timer(SIP_TIMER_J);
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite::timer_J_expired()
{
    switch (_state)
    {
        case STATE_COMPLETED:
            _state = STATE_TERMINATED;
            return true;

        default:
            return false;
    }
}

//-------------------------------------------

bool SIP_Transaction_Server_Non_Invite::timer_J_callback(void *p)
{
    SIP_Transaction_Server_Non_Invite *transaction = reinterpret_cast<SIP_Transaction_Server_Non_Invite *>(p);
    if (!transaction)
    {
        _logger.warning("Invalid timer J callback parameter");
        return false;
    }

    transaction->_timer_ids[SIP_TIMER_J] = Timer::INVALID_TIMER_ID;
    transaction->timer_J_expired();
    return true;
}

//-------------------------------------------
