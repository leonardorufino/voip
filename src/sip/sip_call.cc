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

#include "sip_call.h"

Logger SIP_Call::_logger(Log_Manager::LOG_SIP_CALL);

//-------------------------------------------

SIP_Call::~SIP_Call()
{
    clear_dialogs();
    clear_transactions();
}

//-------------------------------------------

std::string SIP_Call::get_state_str()
{
    switch (_state)
    {
        case STATE_IDLE:            return "Idle";
        case STATE_CALLING_IN:      return "Calling In";
        case STATE_CALLING_OUT:     return "Calling Out";
        case STATE_RINGING_IN:      return "Ringing In";
        case STATE_RINGING_OUT:     return "Ringing Out";
        case STATE_CANCELING_OUT:   return "Canceling Out";
        case STATE_CANCELING_IN:    return "Canceling In";
        case STATE_CANCELED_OUT:    return "Canceled Out";
        case STATE_CANCELED_IN:     return "Canceled In";
        case STATE_WAITING_ACK_IN:  return "Waiting ACK In";
        case STATE_WAITING_ACK_OUT: return "Waiting ACK Out";
        case STATE_ACTIVE:          return "Active";
        case STATE_CLOSING_IN:      return "Closing In";
        case STATE_CLOSING_OUT:     return "Closing Out";
        case STATE_REGISTER_IN:     return "Register In";
        case STATE_REGISTER_OUT:    return "Register Out";
        case STATE_OPTIONS_IN:      return "Options In";
        case STATE_OPTIONS_OUT:     return "Options Out";
        case STATE_CLOSED:          return "Closed";
        default:                    return "Invalid";
    }
}

//-------------------------------------------

void SIP_Call::set_send_message_callback(send_message_callback *callback, void *data)
{
    _send_message_callback = callback;
    _send_message_callback_data = data;
}

//-------------------------------------------

void SIP_Call::set_receive_request_callback(receive_request_callback *callback, void *data)
{
    _receive_request_callback = callback;
    _receive_request_callback_data = data;
}

//-------------------------------------------

void SIP_Call::set_receive_response_callback(receive_response_callback *callback, void *data)
{
    _receive_response_callback = callback;
    _receive_response_callback_data = data;
}

//-------------------------------------------

SIP_Dialog *SIP_Call::get_client_dialog(SIP_Message *msg)
{
    SIP_Header_Call_ID *header_call_id = dynamic_cast<SIP_Header_Call_ID *>(msg->get_header(SIP_HEADER_CALL_ID));
    SIP_Header_From *header_from = dynamic_cast<SIP_Header_From *>(msg->get_header(SIP_HEADER_FROM));
    SIP_Header_To *header_to = dynamic_cast<SIP_Header_To *>(msg->get_header(SIP_HEADER_TO));

    if ((!header_call_id) || (!header_from) || (!header_to))
    {
        _logger.warning("Failed to get client dialog: invalid headers [%s]", _id.to_string().c_str());
        return NULL;
    }

    std::string call_id = header_call_id->get_call_id();
    std::string local_tag = header_from->get_tag();
    std::string remote_tag = header_to->get_tag(); // Remote tag can be empty: compatibility with RFC 2543

    return get_dialog(call_id, local_tag, remote_tag);
}

//-------------------------------------------

SIP_Dialog *SIP_Call::get_server_dialog(SIP_Message *msg)
{
    SIP_Header_Call_ID *header_call_id = dynamic_cast<SIP_Header_Call_ID *>(msg->get_header(SIP_HEADER_CALL_ID));
    SIP_Header_From *header_from = dynamic_cast<SIP_Header_From *>(msg->get_header(SIP_HEADER_FROM));
    SIP_Header_To *header_to = dynamic_cast<SIP_Header_To *>(msg->get_header(SIP_HEADER_TO));

    if ((!header_call_id) || (!header_from) || (!header_to))
    {
        _logger.warning("Failed to get server dialog: invalid headers [%s]", _id.to_string().c_str());
        return NULL;
    }

    std::string call_id = header_call_id->get_call_id();
    std::string local_tag = header_to->get_tag();
    std::string remote_tag = header_from->get_tag(); // Remote tag can be empty: compatibility with RFC 2543

    return get_dialog(call_id, local_tag, remote_tag);
}

//-------------------------------------------

SIP_Dialog *SIP_Call::get_dialog(std::string call_id, std::string local_tag, std::string remote_tag)
{
    std::list<SIP_Dialog *>::iterator it = _dialogs.begin();
    while (it != _dialogs.end())
    {
        SIP_Dialog *dialog = *it++;

        if ((dialog->get_call_id() == call_id) && ((local_tag.empty()) || (dialog->get_local_tag() == local_tag)) &&
            ((remote_tag.empty()) || (dialog->get_remote_tag() == remote_tag)))
            return dialog;
    }

    return NULL;
}

//-------------------------------------------

SIP_Dialog *SIP_Call::get_dialog()
{
    if (_dialogs.empty())
        return NULL;

    return _dialogs.front();
}

//-------------------------------------------

void SIP_Call::add_dialog(SIP_Dialog *dialog)
{
    _dialogs.push_back(dialog);
}

//-------------------------------------------

void SIP_Call::remove_dialog(SIP_Dialog *dialog)
{
    _dialogs.remove(dialog);
    delete dialog;
}

//-------------------------------------------

void SIP_Call::clear_dialogs()
{
    std::list<SIP_Dialog *>::iterator it = _dialogs.begin();
    while (it != _dialogs.end())
    {
        SIP_Dialog *dialog = *it++;
        _dialogs.pop_front();
        delete dialog;
    }
}

//-------------------------------------------

SIP_Transaction *SIP_Call::get_transaction(SIP_Message *msg)
{
    std::list<SIP_Transaction *>::iterator it = _transactions.begin();
    while (it != _transactions.end())
    {
        SIP_Transaction *transaction = *it++;

        if (transaction->match_transaction(msg))
            return transaction;
    }

    return NULL;
}

//-------------------------------------------

void SIP_Call::add_transaction(SIP_Transaction *transaction)
{
    transaction->set_send_message_callback(transaction_send_message_callback, this);
    transaction->set_receive_request_callback(transaction_receive_request_callback, this);
    transaction->set_receive_response_callback(transaction_receive_response_callback, this);

    _transactions.push_back(transaction);
}

//-------------------------------------------

void SIP_Call::remove_transaction(SIP_Transaction *transaction)
{
    _transactions.remove(transaction);
    delete transaction;
}

//-------------------------------------------

void SIP_Call::clear_transactions()
{
    std::list<SIP_Transaction *>::iterator it = _transactions.begin();
    while (it != _transactions.end())
    {
        SIP_Transaction *transaction = *it++;
        _transactions.pop_front();
        delete transaction;
    }
}

//-------------------------------------------

bool SIP_Call::send_request(SIP_Request *request)
{
    if (!request)
    {
        _logger.warning("Failed to send request: invalid request [%s]", _id.to_string().c_str());
        return false;
    }

    SIP_Method_Type method = request->get_message_type();

    SIP_Transaction *transaction = get_transaction(request);
    if (transaction)
    {
        _logger.warning("Failed to send request: transaction already exist (method=%d) [%s]", method, _id.to_string().c_str());
        return false;
    }

    if (!process_send_request(request))
    {
        _logger.warning("Failed to send request: process send request failed (method=%d) [%s]", method, _id.to_string().c_str());
        return false;
    }

    if (method == SIP_REQUEST_INVITE)
    {
        SIP_Object_ID transaction_id = _id;
        transaction_id._transaction = _next_transaction_id++;

        SIP_Transaction_Client_Invite *transaction = new SIP_Transaction_Client_Invite(transaction_id);
        add_transaction(transaction);
        return transaction->send_invite(request);

    }else if (method == SIP_REQUEST_ACK)
    {
        if (_send_message_callback)
            return _send_message_callback(_send_message_callback_data, this, request);
        return true;
    }else
    {
        SIP_Object_ID transaction_id = _id;
        transaction_id._transaction = _next_transaction_id++;

        SIP_Transaction_Client_Non_Invite *transaction = new SIP_Transaction_Client_Non_Invite(transaction_id);
        add_transaction(transaction);
        return transaction->send_request(request);
    }
}

//-------------------------------------------

bool SIP_Call::receive_request(SIP_Request *request)
{
    if (!request)
    {
        _logger.warning("Failed to receive request: invalid request [%s]", _id.to_string().c_str());
        return false;
    }

    SIP_Method_Type method = request->get_message_type();

    SIP_Transaction *transaction = get_transaction(request);
    if (!transaction)
    {
        if (method == SIP_REQUEST_INVITE)
        {
            SIP_Object_ID transaction_id = _id;
            transaction_id._transaction = _next_transaction_id++;

            transaction = new SIP_Transaction_Server_Invite(transaction_id);
            add_transaction(transaction);

        }else if (method == SIP_REQUEST_ACK)
        {
            return process_receive_request(request);
        }else
        {
            SIP_Object_ID transaction_id = _id;
            transaction_id._transaction = _next_transaction_id++;

            transaction = new SIP_Transaction_Server_Non_Invite(transaction_id);
            add_transaction(transaction);
        }
    }

    if (transaction)
    {
        if ((method == SIP_REQUEST_INVITE) || (method == SIP_REQUEST_ACK))
        {
            SIP_Transaction_Server_Invite *transaction_server_invite = dynamic_cast<SIP_Transaction_Server_Invite *>(transaction);
            if (!transaction_server_invite)
            {
                _logger.warning("Failed to receive request: invalid invite server transaction (method=%d) [%s]",
                                method, _id.to_string().c_str());
                return false;
            }

            if (method == SIP_REQUEST_INVITE)
                return transaction_server_invite->receive_invite(request);
            else
                return transaction_server_invite->receive_ack(request);
        }else
        {
            SIP_Transaction_Server_Non_Invite *transaction_server_non_invite = dynamic_cast<SIP_Transaction_Server_Non_Invite *>(transaction);
            if (!transaction_server_non_invite)
            {
                _logger.warning("Failed to receive request: invalid non-invite server transaction (method=%d) [%s]",
                                method, _id.to_string().c_str());
                return false;
            }

            return transaction_server_non_invite->receive_request(request);
        }
    }

    _logger.warning("Failed to receive request: invalid transaction (method=%d)", method, _id.to_string().c_str());
    return false;
}

//-------------------------------------------

bool SIP_Call::send_response(SIP_Response *response)
{
    if (!response)
    {
        _logger.warning("Failed to send response: invalid response [%s]", _id.to_string().c_str());
        return false;
    }

    unsigned short status_code = response->get_status_code();

    SIP_Transaction *transaction = get_transaction(response);
    if (!transaction)
    {
        _logger.warning("Failed to send response: transaction not found (status_code=%d) [%s]", status_code, _id.to_string().c_str());
        return false;
    }

    SIP_Request *request = transaction->get_saved_request();
    if (!request)
    {
        _logger.warning("Failed to send response: invalid request (status_code=%d) [%s]", status_code, _id.to_string().c_str());
        return false;
    }

    SIP_Method_Type method = request->get_message_type();

    if (!process_send_response(request, response))
    {
        _logger.warning("Failed to send response: process send request failed (method=%d) [%s]", method, _id.to_string().c_str());
        return false;
    }

    if (method == SIP_REQUEST_INVITE)
    {
        SIP_Transaction_Server_Invite *transaction_server_invite = dynamic_cast<SIP_Transaction_Server_Invite *>(transaction);
        if (!transaction_server_invite)
        {
            _logger.warning("Failed to send response: invalid invite server transaction (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
        }

        if ((status_code >= 100) && (status_code <= 199))
            return transaction_server_invite->send_1xx(response);

        else if ((status_code >= 200) && (status_code <= 299))
            return transaction_server_invite->send_2xx(response);

        else if ((status_code >= 300) && (status_code <= 699))
            return transaction_server_invite->send_3xx_6xx(response);
    }else
    {
        SIP_Transaction_Server_Non_Invite *transaction_server_non_invite = dynamic_cast<SIP_Transaction_Server_Non_Invite *>(transaction);
        if (!transaction_server_non_invite)
        {
            _logger.warning("Failed to send response: invalid non-invite server transaction (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
        }

        if ((status_code >= 100) && (status_code <= 199))
            return transaction_server_non_invite->send_1xx(response);

        else if ((status_code >= 200) && (status_code <= 699))
            return transaction_server_non_invite->send_2xx_6xx(response);
    }

    _logger.warning("Failed to send response: invalid status code (method=%d, status_code=%d) [%s]",
                    method, status_code, _id.to_string().c_str());
    return false;
}

//-------------------------------------------

bool SIP_Call::receive_response(SIP_Response *response)
{
    if (!response)
    {
        _logger.warning("Failed to receive response: invalid response [%s]", _id.to_string().c_str());
        return false;
    }

    unsigned short status_code = response->get_status_code();

    SIP_Transaction *transaction = get_transaction(response);
    if (!transaction)
    {
        _logger.warning("Failed to receive response: transaction not found (status_code=%d) [%s]", status_code, _id.to_string().c_str());
        return false;
    }

    SIP_Request *request = transaction->get_saved_request();
    if (!request)
    {
        _logger.warning("Failed to receive response: invalid request (status_code=%d) [%s]", status_code, _id.to_string().c_str());
        return false;
    }

    SIP_Method_Type method = request->get_message_type();

    if (transaction->get_transaction_type() == SIP_Transaction::SIP_TRANSACTION_CLIENT_INVITE)
    {
        SIP_Transaction_Client_Invite *transaction_client_invite = dynamic_cast<SIP_Transaction_Client_Invite *>(transaction);
        if (!transaction_client_invite)
        {
            _logger.warning("Failed to receive response: invalid invite client transaction (method=%d, status_code=%d)",
                            method, status_code, _id.to_string().c_str());
            return false;
        }

        if ((status_code >= 100) && (status_code <= 199))
            return transaction_client_invite->receive_1xx(response);

        else if ((status_code >= 200) && (status_code <= 299))
            return transaction_client_invite->receive_2xx(response);

        else if ((status_code >= 300) && (status_code <= 699))
            return transaction_client_invite->receive_3xx_6xx(response);

        else
        {
            _logger.warning("Failed to receive response: invalid status code (method=%d, status_code=%d, transaction=%d) [%s]",
                            method, status_code, transaction->get_transaction_type(), _id.to_string().c_str());
            return false;
        }
    }else if (transaction->get_transaction_type() == SIP_Transaction::SIP_TRANSACTION_CLIENT_NON_INVITE)
    {
        SIP_Transaction_Client_Non_Invite *transaction_client_non_invite = dynamic_cast<SIP_Transaction_Client_Non_Invite *>(transaction);
        if (!transaction_client_non_invite)
        {
            _logger.warning("Failed to receive response: invalid non-invite client transaction (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
        }

        if ((status_code >= 100) && (status_code <= 199))
            return transaction_client_non_invite->receive_1xx(response);

        else if ((status_code >= 200) && (status_code <= 699))
            return transaction_client_non_invite->receive_2xx_6xx(response);

        else
        {
            _logger.warning("Failed to receive response: invalid status code (method=%d, status_code=%d, transaction=%d) [%s]",
                            method, status_code, transaction->get_transaction_type(), _id.to_string().c_str());
            return false;
        }
    }else
    {
        _logger.warning("Failed to receive response: invalid transaction type (method=%d, status_code=%d, transaction=%d) [%s]",
                        method, status_code, transaction->get_transaction_type(), _id.to_string().c_str());
        return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_request(SIP_Request *request)
{
    if (!request)
    {
        _logger.warning("Failed to process send request: invalid request [%s]", _id.to_string().c_str());
        return false;
    }

    switch (_state)
    {
        case STATE_IDLE:
            return process_send_request_idle(request);

        case STATE_RINGING_IN:
            return process_send_request_ringing_in(request);

        case STATE_RINGING_OUT:
            return process_send_request_ringing_out(request);

        case STATE_WAITING_ACK_OUT:
            return process_send_request_waiting_ack_out(request);

        case STATE_ACTIVE:
            return process_send_request_active(request);

        default:
            _logger.warning("Failed to process send request: invalid state (state=%d, method=%d) [%s]",
                            _state, request->get_message_type(), _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_request(SIP_Request *request)
{
    if (!request)
    {
        _logger.warning("Failed to process receive request: invalid request [%s]", _id.to_string().c_str());
        return false;
    }

    switch (_state)
    {
        case STATE_IDLE:
            return process_receive_request_idle(request);

        case STATE_RINGING_IN:
            return process_receive_request_ringing_in(request);

        case STATE_RINGING_OUT:
            return process_receive_request_ringing_out(request);

        case STATE_WAITING_ACK_IN:
            return process_receive_request_waiting_ack_in(request);

        case STATE_ACTIVE:
            return process_receive_request_active(request);

        default:
            _logger.warning("Failed to process receive request: invalid state (state=%d, method=%d) [%s]",
                            _state, request->get_message_type(), _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_response(SIP_Request *request, SIP_Response *response)
{
    if ((!request) || (!response))
    {
        _logger.warning("Failed to process send response: invalid params [%s]", _id.to_string().c_str());
        return false;
    }

    switch (_state)
    {
        case STATE_CALLING_IN:
            return process_send_response_calling_in(request, response);

        case STATE_RINGING_IN:
            return process_send_response_ringing_in(request, response);

        case STATE_RINGING_OUT:
            return process_send_response_ringing_out(request, response);

        case STATE_CANCELING_IN:
            return process_send_response_canceling_in(request, response);

        case STATE_CANCELED_IN:
            return process_send_response_canceled_in(request, response);

        case STATE_ACTIVE:
            return process_send_response_active(request, response);

        case STATE_CLOSING_IN:
            return process_send_response_closing_in(request, response);

        case STATE_REGISTER_IN:
            return process_send_response_register_in(request, response);

        case STATE_OPTIONS_IN:
            return process_send_response_options_in(request, response);

        default:
            _logger.warning("Failed to process send response: invalid state (state=%d, method=%d, status_code=%d) [%s]",
                            _state, request->get_message_type(), response->get_status_code(), _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_response(SIP_Request *request, SIP_Response *response)
{
    if ((!request) || (!response))
    {
        _logger.warning("Failed to process receive response: invalid params [%s]", _id.to_string().c_str());
        return false;
    }

    switch (_state)
    {
        case STATE_CALLING_OUT:
            return process_receive_response_calling_out(request, response);

        case STATE_RINGING_IN:
            return process_receive_response_ringing_in(request, response);

        case STATE_RINGING_OUT:
            return process_receive_response_ringing_out(request, response);

        case STATE_CANCELING_OUT:
            return process_receive_response_canceling_out(request, response);

        case STATE_CANCELED_OUT:
            return process_receive_response_canceled_out(request, response);

        case STATE_ACTIVE:
            return process_receive_response_active(request, response);

        case STATE_CLOSING_OUT:
            return process_receive_response_closing_out(request, response);

        case STATE_REGISTER_OUT:
            return process_receive_response_register_out(request, response);

        case STATE_OPTIONS_OUT:
            return process_receive_response_options_out(request, response);

        default:
            _logger.warning("Failed to process receive response: invalid state (state=%d, method=%d, status_code=%d) [%s]",
                            _state, request->get_message_type(), response->get_status_code(), _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_request_idle(SIP_Request *request)
{
    SIP_Method_Type method = request->get_message_type();

    SIP_Dialog *dialog = get_client_dialog(request);
    if (dialog)
    {
        _logger.warning("Failed to process send request idle: invalid dialog (method=%d) [%s]", method, _id.to_string().c_str());
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_INVITE:
            _state = STATE_CALLING_OUT;
            _logger.trace("Changed state in process send request idle (state=%d, method=%d) [%s]", _state, method, _id.to_string().c_str());
            return true;

        case SIP_REQUEST_REGISTER:
            _state = STATE_REGISTER_OUT;
            _logger.trace("Changed state in process send request idle (state=%d, method=%d) [%s]", _state, method, _id.to_string().c_str());
            return true;

        case SIP_REQUEST_OPTIONS:
            _state = STATE_OPTIONS_OUT;
            _logger.trace("Changed state in process send request idle (state=%d, method=%d) [%s]", _state, method, _id.to_string().c_str());
            return true;

        default:
            _logger.warning("Failed to process send request idle: invalid method (method=%d) [%s]", method, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_request_idle(SIP_Request *request)
{
    SIP_Method_Type method = request->get_message_type();

    switch (method)
    {
        case SIP_REQUEST_INVITE:
        {
            SIP_Header_To *header_to = dynamic_cast<SIP_Header_To *>(request->get_header(SIP_HEADER_TO));
            if (!header_to)
            {
                _logger.warning("Failed to process receive request idle: invalid TO header (method=%d) [%s]",
                                method, _id.to_string().c_str());
                return false;
            }

            if (!header_to->get_tag().empty())
            {
                _logger.warning("Failed to process receive request idle: invalid TO header tag (method=%d) [%s]",
                                method, _id.to_string().c_str());
                _state = STATE_CALLING_IN;
                send_response(request, 481);
                return false;
            }

            _state = STATE_CALLING_IN;
            _logger.trace("Changed state in process receive request idle (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());

            if (_receive_request_callback)
                return _receive_request_callback(_receive_request_callback_data, this, request);
            return true;
        }

        case SIP_REQUEST_REGISTER:
            _state = STATE_REGISTER_IN;
            _logger.trace("Changed state in process receive request idle (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());

            if (_receive_request_callback)
                return _receive_request_callback(_receive_request_callback_data, this, request);
            return true;

        case SIP_REQUEST_OPTIONS:
            _state = STATE_OPTIONS_IN;
            _logger.trace("Changed state in process receive request idle (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());

            if (_receive_request_callback)
                return _receive_request_callback(_receive_request_callback_data, this, request);
            return true;

        default:
            _logger.warning("Failed to process receive request idle: invalid method (method=%d)", method);
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_response_calling_in(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    SIP_Dialog *dialog = get_server_dialog(response);
    if (dialog)
    {
        _logger.warning("Failed to process send response calling in: invalid dialog (method=%d, status_code=%d) [%s]",
                        method, status_code, _id.to_string().c_str());
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_INVITE:
            if ((status_code >= 100) && (status_code <= 199))
            {
                SIP_Header_To *header_to = dynamic_cast<SIP_Header_To *>(response->get_header(SIP_HEADER_TO));
                if (!header_to)
                {
                    _logger.warning("Failed to process send response calling in: invalid TO header (method=%d, status_code=%d) [%s]",
                                    method, status_code, _id.to_string().c_str());
                    return false;
                }

                if ((!header_to->get_tag().empty()) && (response->get_header_size(SIP_HEADER_CONTACT) > 0))
                {
                    SIP_Object_ID dialog_id = _id;
                    dialog_id._dialog = _next_dialog_id++;

                    SIP_Dialog *new_dialog = new SIP_Dialog(dialog_id);
                    if (!new_dialog->set_server_dialog(request, response))
                    {
                        delete new_dialog;
                        _logger.warning("Failed to process send response calling in: set server dialog failed (method=%d, status_code=%d) [%s]",
                                        method, status_code, _id.to_string().c_str());
                        return false;
                    }

                    add_dialog(new_dialog);
                }

                _state = STATE_RINGING_IN;
                _logger.trace("Changed state in process send response calling in (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());
                return true;

            }else if ((status_code >= 200) && (status_code <= 299))
            {
                SIP_Object_ID dialog_id = _id;
                dialog_id._dialog = _next_dialog_id++;

                SIP_Dialog *new_dialog = new SIP_Dialog(dialog_id);
                if (!new_dialog->set_server_dialog(request, response))
                {
                    delete new_dialog;
                    _logger.warning("Failed to process send response calling in: set server dialog failed (method=%d, status_code=%d) [%s]",
                                    method, status_code, _id.to_string().c_str());
                    return false;
                }

                add_dialog(new_dialog);

                _state = STATE_WAITING_ACK_IN;
                _logger.trace("Changed state in process send response calling in (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());
                return true;

            }else if ((status_code >= 300) && (status_code <= 699))
            {
                _state = STATE_CLOSED;
                _logger.trace("Changed state in process send response calling in (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());
                return true;
            }

            _logger.warning("Failed to process send response calling in: invalid status code (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;

        default:
            _logger.warning("Failed to process send response calling in: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_response_calling_out(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    SIP_Dialog *dialog = get_client_dialog(response);
    if (dialog)
    {
        _logger.warning("Failed to process receive response calling out: invalid dialog (method=%d, status_code=%d) [%s]",
                        method, status_code, _id.to_string().c_str());
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_INVITE:
            if ((status_code >= 100) && (status_code <= 199))
            {
                SIP_Header_To *header_to = dynamic_cast<SIP_Header_To *>(response->get_header(SIP_HEADER_TO));
                if (!header_to)
                {
                    _logger.warning("Failed to process receive response calling out: invalid TO header (method=%d, status_code=%d) [%s]",
                                    method, status_code, _id.to_string().c_str());
                    return false;
                }

                if ((!header_to->get_tag().empty()) && (response->get_header_size(SIP_HEADER_CONTACT) > 0))
                {
                    SIP_Object_ID dialog_id = _id;
                    dialog_id._dialog = _next_dialog_id++;

                    SIP_Dialog *new_dialog = new SIP_Dialog(dialog_id);
                    if (!new_dialog->set_client_dialog(request, response))
                    {
                        delete new_dialog;
                        _logger.warning("Failed to process receive response calling out: set client dialog failed (method=%d, status_code=%d) [%s]",
                                        method, status_code, _id.to_string().c_str());
                        return false;
                    }

                    add_dialog(new_dialog);
                }

                _state = STATE_RINGING_OUT;
                _logger.trace("Changed state in process receive response calling out (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());

                if (_receive_response_callback)
                    return _receive_response_callback(_receive_response_callback_data, this, request, response);
                return true;

            }else if ((status_code >= 200) && (status_code <= 299))
            {
                SIP_Object_ID dialog_id = _id;
                dialog_id._dialog = _next_dialog_id++;

                SIP_Dialog *new_dialog = new SIP_Dialog(dialog_id);
                if (!new_dialog->set_client_dialog(request, response))
                {
                    delete new_dialog;
                    _logger.warning("Failed to process receive response calling out: set client dialog failed (method=%d, status_code=%d) [%s]",
                                    method, status_code, _id.to_string().c_str());
                    return false;
                }

                add_dialog(new_dialog);

                _state = STATE_WAITING_ACK_OUT;
                _logger.trace("Changed state in process receive response calling out (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());

                if (_receive_response_callback)
                    return _receive_response_callback(_receive_response_callback_data, this, request, response);
                return true;

            }else if ((status_code >= 300) && (status_code <= 699))
            {
                _state = STATE_CLOSED;
                _logger.trace("Changed state in process receive response calling out (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());

                if (_receive_response_callback)
                    return _receive_response_callback(_receive_response_callback_data, this, request, response);
                return true;
            }

            _logger.warning("Failed to process receive response calling out: invalid status code (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;

        default:
            _logger.warning("Failed to process receive response calling out: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_request_ringing_in(SIP_Request *request)
{
    SIP_Method_Type method = request->get_message_type();

    switch (method)
    {
        case SIP_REQUEST_UPDATE:
        {
            SIP_Dialog *dialog = get_client_dialog(request);
            if (!dialog)
            {
                _logger.warning("Failed to process send request ringing in: invalid dialog (method=%d) [%s]",
                                method, _id.to_string().c_str());
                return false;
            }

            //_state = STATE_RINGING_IN;
            _logger.trace("Changed state in process send request ringing in (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());
            return true;
        }

        default:
            _logger.warning("Failed to process send request ringing in: invalid method (method=%d) [%s]",
                            method, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_request_ringing_in(SIP_Request *request)
{
    SIP_Method_Type method = request->get_message_type();

    switch (method)
    {
        case SIP_REQUEST_CANCEL:
        {
            SIP_Dialog *dialog = get_server_dialog(request);
            if (!dialog)
            {
                _logger.warning("Failed to process receive request ringing in: invalid dialog (method=%d) [%s]",
                                method, _id.to_string().c_str());
                return false;
            }

            _state = STATE_CANCELING_IN;
            _logger.trace("Changed state in process receive request ringing in (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());

            if (_receive_request_callback)
                return _receive_request_callback(_receive_request_callback_data, this, request);
            return true;
        }

        case SIP_REQUEST_UPDATE:
        {
            SIP_Dialog *dialog = get_server_dialog(request);
            if (!dialog)
            {
                _logger.warning("Failed to process receive request ringing in: invalid dialog (method=%d) [%s]",
                                method, _id.to_string().c_str());
                return false;
            }

            if (!dialog->check_remote_sequence(request))
            {
                _logger.warning("Failed to process receive request ringing in: dialog check remote sequence failed (method=%d) [%s]",
                                method, _id.to_string().c_str());
                return false;
            }

            dialog->set_remote_target(request);

            //_state = STATE_RINGING_IN;
            _logger.trace("Changed state in process receive request ringing in (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());

            if (_receive_request_callback)
                return _receive_request_callback(_receive_request_callback_data, this, request);
            return true;
        }

        case SIP_REQUEST_PRACK:
        {
            SIP_Dialog *dialog = get_server_dialog(request);
            if (!dialog)
            {
                _logger.warning("Failed to process receive request ringing in: invalid dialog (method=%d) [%s]",
                                method, _id.to_string().c_str());
                return false;
            }

            if (!dialog->check_remote_sequence(request))
            {
                _logger.warning("Failed to process receive request ringing in: dialog check remote sequence failed (method=%d) [%s]",
                                method, _id.to_string().c_str());
                return false;
            }

            //_state = STATE_RINGING_IN;
            _logger.trace("Changed state in process receive request ringing in (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());

            if (_receive_request_callback)
                return _receive_request_callback(_receive_request_callback_data, this, request);
            return true;
        }

        default:
            _logger.warning("Failed to process receive request ringing in: invalid method (method=%d) [%s]",
                            method, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_response_ringing_in(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    switch (method)
    {
        case SIP_REQUEST_INVITE:
            if ((status_code >= 100) && (status_code <= 199))
            {
                SIP_Header_To *header_to = dynamic_cast<SIP_Header_To *>(response->get_header(SIP_HEADER_TO));
                if (!header_to)
                {
                    _logger.warning("Failed to process send response ringing in: invalid TO header (method=%d, status_code=%d) [%s]",
                                    method, status_code, _id.to_string().c_str());
                    return false;
                }

                if ((!header_to->get_tag().empty()) && (response->get_header_size(SIP_HEADER_CONTACT) > 0))
                {
                    SIP_Dialog *dialog = get_server_dialog(response);
                    if (!dialog)
                    {
                        SIP_Object_ID dialog_id = _id;
                        dialog_id._dialog = _next_dialog_id++;

                        SIP_Dialog *new_dialog = new SIP_Dialog(dialog_id);
                        if (!new_dialog->set_server_dialog(request, response))
                        {
                            delete new_dialog;
                            _logger.warning("Failed to process send response ringing in: set server dialog failed (method=%d, status_code=%d) [%s]",
                                            method, status_code, _id.to_string().c_str());
                            return false;
                        }

                        add_dialog(new_dialog);
                    }
                }

                //_state = STATE_RINGING_IN;
                _logger.trace("Changed state in process send response ringing in (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());
                return true;

            }else if ((status_code >= 200) && (status_code <= 299))
            {
                SIP_Dialog *dialog = get_server_dialog(response);
                if (!dialog)
                {
                    SIP_Object_ID dialog_id = _id;
                    dialog_id._dialog = _next_dialog_id++;

                    SIP_Dialog *new_dialog = new SIP_Dialog(dialog_id);
                    if (!new_dialog->set_server_dialog(request, response))
                    {
                        delete new_dialog;
                        _logger.warning("Failed to process send response ringing in: set server dialog failed (method=%d, status_code=%d) [%s]",
                                        method, status_code, _id.to_string().c_str());
                        return false;
                    }

                    add_dialog(new_dialog);
                }

                _state = STATE_WAITING_ACK_IN;
                _logger.trace("Changed state in process send response ringing in (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());
                return true;

            }else if ((status_code >= 300) && (status_code <= 699))
            {
                SIP_Dialog *dialog = get_server_dialog(response);
                if (dialog)
                    remove_dialog(dialog);

                _state = STATE_CLOSED;
                _logger.trace("Changed state in process send response ringing in (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());
                return true;
            }

            _logger.warning("Failed to process send response ringing in: invalid status code (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;

        case SIP_REQUEST_UPDATE:
        case SIP_REQUEST_PRACK:
        {
            SIP_Dialog *dialog = get_server_dialog(response);
            if (!dialog)
            {
                _logger.warning("Failed to process send response ringing in: invalid dialog (method=%d, status_code=%d) [%s]",
                                method, status_code, _id.to_string().c_str());
                return false;
            }

            //_state = STATE_RINGING_IN;
            _logger.trace("Changed state in process send response ringing in (state=%d, method=%d, status_code=%d) [%s]",
                          _state, method, status_code, _id.to_string().c_str());
            return true;
        }

        default:
            _logger.warning("Failed to process send response ringing in: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_response_ringing_in(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    switch (method)
    {
        case SIP_REQUEST_UPDATE:
        {
            SIP_Dialog *dialog = get_client_dialog(response);
            if (!dialog)
            {
                _logger.warning("Failed to process receive response ringing in: invalid dialog (method=%d, status_code=%d) [%s]",
                                method, status_code, _id.to_string().c_str());
                return false;
            }

            dialog->set_remote_target(response);

            //_state = STATE_RINGING_IN;
            _logger.trace("Changed state in process receive response ringing in (state=%d, method=%d, status_code=%d) [%s]",
                          _state, method, status_code, _id.to_string().c_str());

            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, request, response);
            return true;
        }

        default:
            _logger.warning("Failed to process receive response ringing in: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_request_ringing_out(SIP_Request *request)
{
    SIP_Method_Type method = request->get_message_type();

    switch (method)
    {
        case SIP_REQUEST_CANCEL:
        {
            SIP_Dialog *dialog = get_client_dialog(request);
            if (!dialog)
            {
                _logger.warning("Failed to process send request ringing out: invalid dialog (method=%d) [%s]",
                                method, _id.to_string().c_str());
                return false;
            }

            _state = STATE_CANCELING_OUT;
            _logger.trace("Changed state in process send request ringing out (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());
            return true;
        }

        case SIP_REQUEST_UPDATE:
        case SIP_REQUEST_PRACK:
        {
            SIP_Dialog *dialog = get_client_dialog(request);
            if (!dialog)
            {
                _logger.warning("Failed to process send request ringing out: invalid dialog (method=%d) [%s]",
                                method, _id.to_string().c_str());
                return false;
            }

            //_state = STATE_RINGING_OUT;
            _logger.trace("Changed state in process send request ringing out (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());
            return true;
        }

        default:
            _logger.warning("Failed to process send request ringing out: invalid method (method=%d) [%s]",
                            method, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_request_ringing_out(SIP_Request *request)
{
    SIP_Method_Type method = request->get_message_type();

    switch (method)
    {
        case SIP_REQUEST_UPDATE:
        {
            SIP_Dialog *dialog = get_server_dialog(request);
            if (!dialog)
            {
                _logger.warning("Failed to process receive request ringing out: invalid dialog (method=%d) [%s]",
                                method, _id.to_string().c_str());
                return false;
            }

            if (!dialog->check_remote_sequence(request))
            {
                _logger.warning("Failed to process receive request ringing out: dialog check remote sequence failed (method=%d) [%s]",
                                method, _id.to_string().c_str());
                return false;
            }

            dialog->set_remote_target(request);

            //_state = STATE_RINGING_OUT;
            _logger.trace("Changed state in process receive request ringing out (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());

            if (_receive_request_callback)
                return _receive_request_callback(_receive_request_callback_data, this, request);
            return true;
        }

        default:
            _logger.warning("Failed to process receive request ringing out: invalid method (method=%d) [%s]",
                            method, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_response_ringing_out(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    switch (method)
    {
        case SIP_REQUEST_UPDATE:
        {
            SIP_Dialog *dialog = get_server_dialog(response);
            if (!dialog)
            {
                _logger.warning("Failed to process send response ringing out: invalid dialog (method=%d, status_code=%d) [%s]",
                                method, status_code, _id.to_string().c_str());
                return false;
            }

            //_state = STATE_RINGING_OUT;
            _logger.trace("Changed state in process send response ringing out (state=%d, method=%d, status_code=%d) [%s]",
                          _state, method, status_code, _id.to_string().c_str());
            return true;
        }

        default:
            _logger.warning("Failed to process receive response ringing out: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_response_ringing_out(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    switch (method)
    {
        case SIP_REQUEST_INVITE:
            if ((status_code >= 100) && (status_code <= 199))
            {
                SIP_Header_To *header_to = dynamic_cast<SIP_Header_To *>(response->get_header(SIP_HEADER_TO));
                if (!header_to)
                {
                    _logger.warning("Failed to process receive response ringing out: invalid TO header (method=%d, status_code=%d) [%s]",
                                    method, status_code, _id.to_string().c_str());
                    return false;
                }

                if ((!header_to->get_tag().empty()) && (response->get_header_size(SIP_HEADER_CONTACT) > 0))
                {
                    SIP_Dialog *dialog = get_client_dialog(response);
                    if (!dialog)
                    {
                        SIP_Object_ID dialog_id = _id;
                        dialog_id._dialog = _next_dialog_id++;

                        SIP_Dialog *new_dialog = new SIP_Dialog(dialog_id);
                        if (!new_dialog->set_client_dialog(request, response))
                        {
                            delete new_dialog;
                            _logger.warning("Failed to process receive response ringing out: set client dialog failed (method=%d, status_code=%d) [%s]",
                                            method, status_code, _id.to_string().c_str());
                            return false;
                        }

                        add_dialog(new_dialog);
                    }else
                        dialog->set_remote_target(response);
                }

                //_state = STATE_RINGING_OUT;
                _logger.trace("Changed state in process receive response ringing out (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());

                if (_receive_response_callback)
                    return _receive_response_callback(_receive_response_callback_data, this, request, response);
                return true;

            }else if ((status_code >= 200) && (status_code <= 299))
            {
                SIP_Dialog *dialog = get_client_dialog(response);
                if (!dialog)
                {
                    SIP_Object_ID dialog_id = _id;
                    dialog_id._dialog = _next_dialog_id++;

                    SIP_Dialog *new_dialog = new SIP_Dialog(dialog_id);
                    if (!new_dialog->set_client_dialog(request, response))
                    {
                        delete new_dialog;
                        _logger.warning("Failed to process receive response ringing out: set client dialog failed (method=%d, status_code=%d) [%s]",
                                        method, status_code, _id.to_string().c_str());
                        return false;
                    }

                    add_dialog(new_dialog);
                }else
                    dialog->set_remote_target(response);

                _state = STATE_WAITING_ACK_OUT;
                _logger.trace("Changed state in process receive response ringing out (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());

                if (_receive_response_callback)
                    return _receive_response_callback(_receive_response_callback_data, this, request, response);
                return true;

            }else if ((status_code >= 300) && (status_code <= 699))
            {
                SIP_Dialog *dialog = get_client_dialog(response);
                if (dialog)
                    remove_dialog(dialog);

                _state = STATE_CLOSED;
                _logger.trace("Changed state in process receive response ringing out (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());

                if (_receive_response_callback)
                    return _receive_response_callback(_receive_response_callback_data, this, request, response);
                return true;
            }

            _logger.warning("Failed to process receive response ringing out: invalid status code (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;

        case SIP_REQUEST_UPDATE:
        {
            SIP_Dialog *dialog = get_client_dialog(response);
            if (!dialog)
            {
                _logger.warning("Failed to process receive response ringing out: invalid dialog (method=%d, status_code=%d) [%s]",
                                method, status_code, _id.to_string().c_str());
                return false;
            }

            dialog->set_remote_target(response);

            //_state = STATE_RINGING_OUT;
            _logger.trace("Changed state in process receive response ringing out (state=%d, method=%d, status_code=%d) [%s]",
                          _state, method, status_code, _id.to_string().c_str());

            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, request, response);
            return true;
        }

        case SIP_REQUEST_PRACK:
        {
            SIP_Dialog *dialog = get_client_dialog(response);
            if (!dialog)
            {
                _logger.warning("Failed to process receive response ringing out: invalid dialog (method=%d, status_code=%d) [%s]",
                                method, status_code, _id.to_string().c_str());
                return false;
            }

            //_state = STATE_RINGING_OUT;
            _logger.trace("Changed state in process receive response ringing out (state=%d, method=%d, status_code=%d) [%s]",
                          _state, method, status_code, _id.to_string().c_str());

            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, request, response);
            return true;
        }

        default:
            _logger.warning("Failed to process receive response ringing out: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_response_canceling_in(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    switch (method)
    {
        case SIP_REQUEST_CANCEL:
        {
            SIP_Dialog *dialog = get_server_dialog(response);
            if (!dialog)
            {
                _logger.warning("Failed to process send response canceling in: invalid dialog (method=%d, status_code=%d) [%s]",
                                method, status_code, _id.to_string().c_str());
                return false;
            }

            _state = STATE_CANCELED_IN;
            _logger.trace("Changed state in process send response canceling in (state=%d, method=%d, status_code=%d) [%s]",
                          _state, method, status_code, _id.to_string().c_str());
            return true;
        }

        default:
            _logger.warning("Failed to process send response canceling in: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_response_canceling_out(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    switch (method)
    {
        case SIP_REQUEST_CANCEL:
        {
            SIP_Dialog *dialog = get_client_dialog(response);
            if (!dialog)
            {
                _logger.warning("Failed to process receive response canceling out: invalid dialog (method=%d, status_code=%d) [%s]",
                                method, status_code, _id.to_string().c_str());
                return false;
            }

            _state = STATE_CANCELED_OUT;
            _logger.trace("Changed state in process receive response canceling out (state=%d, method=%d, status_code=%d) [%s]",
                          _state, method, status_code, _id.to_string().c_str());

            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, request, response);
            return true;
        }

        default:
            _logger.warning("Failed to process receive response canceling out: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_response_canceled_in(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    switch (method)
    {
        case SIP_REQUEST_INVITE:
        {
            SIP_Dialog *dialog = get_server_dialog(response);
            if (!dialog)
            {
                _logger.warning("Failed to process send response canceled in: invalid dialog (method=%d, status_code=%d) [%s]",
                                method, status_code, _id.to_string().c_str());
                return false;
            }

            if ((status_code >= 300) && (status_code <= 699))
            {
                remove_dialog(dialog);

                _state = STATE_CLOSED;
                _logger.trace("Changed state in process send response canceled in (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());
                return true;
            }

            _logger.warning("Failed to process send response canceled in: invalid status code (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
        }

        default:
            _logger.warning("Failed to process send response canceled in: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_response_canceled_out(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    switch (method)
    {
        case SIP_REQUEST_INVITE:
        {
            SIP_Dialog *dialog = get_client_dialog(response);
            if (!dialog)
            {
                _logger.warning("Failed to process receive response canceled out: invalid dialog (method=%d, status_code=%d) [%s]",
                                method, status_code, _id.to_string().c_str());
                return false;
            }

            if ((status_code >= 300) && (status_code <= 699))
            {
                remove_dialog(dialog);

                _state = STATE_CLOSED;
                _logger.trace("Changed state in process receive response canceled out (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());

                if (_receive_response_callback)
                    return _receive_response_callback(_receive_response_callback_data, this, request, response);
                return true;
            }

            _logger.warning("Failed to process receive response canceled out: invalid status code (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
        }

        default:
            _logger.warning("Failed to process receive response canceled out: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_request_waiting_ack_in(SIP_Request *request)
{
    SIP_Method_Type method = request->get_message_type();

    SIP_Dialog *dialog = get_server_dialog(request);
    if (!dialog)
    {
        _logger.warning("Failed to process receive request waiting ack in: invalid dialog (method=%d) [%s]",
                        method, _id.to_string().c_str());
        return false;
    }

    if (!dialog->check_remote_sequence(request))
    {
        _logger.warning("Failed to process receive request waiting ack in: dialog check remote sequence failed (method=%d) [%s]",
                        method, _id.to_string().c_str());
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_ACK:
            _state = STATE_ACTIVE;
            _logger.trace("Changed state in process receive request waiting ack in (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());

            if (_receive_request_callback)
                return _receive_request_callback(_receive_request_callback_data, this, request);
            return true;

        default:
            _logger.warning("Failed to process receive request waiting ack in: invalid method (method=%d) [%s]",
                            method, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_request_waiting_ack_out(SIP_Request *request)
{
    SIP_Method_Type method = request->get_message_type();

    SIP_Dialog *dialog = get_client_dialog(request);
    if (!dialog)
    {
        _logger.warning("Failed to process send request waiting ack out: invalid dialog (method=%d) [%s]",
                        method, _id.to_string().c_str());
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_ACK:
            _state = STATE_ACTIVE;
            _logger.trace("Changed state in process send request waiting ack out (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());
            return true;

        default:
            _logger.warning("Failed to process send request waiting ack out: invalid method (method=%d) [%s]",
                            method, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_request_active(SIP_Request *request)
{
    SIP_Method_Type method = request->get_message_type();

    SIP_Dialog *dialog = get_client_dialog(request);
    if (!dialog)
    {
        _logger.warning("Failed to process send request active: invalid dialog (method=%d) [%s]",
                        method, _id.to_string().c_str());
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_BYE:
            _state = STATE_CLOSING_OUT;
            _logger.trace("Changed state in process send request active (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());
            return true;

        case SIP_REQUEST_ACK:
        case SIP_REQUEST_CANCEL:
        case SIP_REQUEST_INFO:
        case SIP_REQUEST_INVITE:
        case SIP_REQUEST_MESSAGE:
        case SIP_REQUEST_NOTIFY:
        case SIP_REQUEST_OPTIONS:
        case SIP_REQUEST_PRACK:
        case SIP_REQUEST_REFER:
        case SIP_REQUEST_UPDATE:
            //_state = STATE_ACTIVE;
            _logger.trace("Changed state in process send request active (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());
            return true;

        default:
            _logger.warning("Failed to process send request active: invalid method (method=%d) [%s]",
                            method, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_request_active(SIP_Request *request)
{
    SIP_Method_Type method = request->get_message_type();

    SIP_Dialog *dialog = get_server_dialog(request);
    if (!dialog)
    {
        _logger.warning("Failed to process receive request active: invalid dialog (method=%d) [%s]",
                        method, _id.to_string().c_str());
        return false;
    }

    if (!dialog->check_remote_sequence(request))
    {
        _logger.warning("Failed to process receive request active: dialog check remote sequence failed (method=%d) [%s]",
                        method, _id.to_string().c_str());
        send_response(request, 500);
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_BYE:
            _state = STATE_CLOSING_IN;
            _logger.trace("Changed state in process receive request active (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());

            if (_receive_request_callback)
                return _receive_request_callback(_receive_request_callback_data, this, request);
            return true;

        case SIP_REQUEST_ACK:
        case SIP_REQUEST_CANCEL:
        case SIP_REQUEST_INFO:
        case SIP_REQUEST_INVITE:
        case SIP_REQUEST_MESSAGE:
        case SIP_REQUEST_NOTIFY:
        case SIP_REQUEST_OPTIONS:
        case SIP_REQUEST_PRACK:
        case SIP_REQUEST_REFER:
        case SIP_REQUEST_UPDATE:
            //_state = STATE_ACTIVE;
            _logger.trace("Changed state in process receive request active (state=%d, method=%d) [%s]",
                          _state, method, _id.to_string().c_str());

            if (_receive_request_callback)
                return _receive_request_callback(_receive_request_callback_data, this, request);
            return true;

        default:
            _logger.warning("Failed to process receive request active: invalid method (method=%d) [%s]",
                            method, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_response_active(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    SIP_Dialog *dialog = get_server_dialog(response);
    if (!dialog)
    {
        _logger.warning("Failed to process send response active: invalid dialog (method=%d, status_code=%d) [%s]",
                        method, status_code, _id.to_string().c_str());
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_ACK:
        case SIP_REQUEST_CANCEL:
        case SIP_REQUEST_INFO:
        case SIP_REQUEST_INVITE:
        case SIP_REQUEST_MESSAGE:
        case SIP_REQUEST_NOTIFY:
        case SIP_REQUEST_OPTIONS:
        case SIP_REQUEST_PRACK:
        case SIP_REQUEST_REFER:
        case SIP_REQUEST_UPDATE:
            if ((status_code == 408) || (status_code == 481))
            {
                remove_dialog(dialog);

                _state = STATE_CLOSED;
                _logger.trace("Changed state in process send response active (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());
                return true;
            }

            //_state = STATE_ACTIVE;
            _logger.trace("Changed state in process send response active (state=%d, method=%d, status_code=%d) [%s]",
                          _state, method, status_code, _id.to_string().c_str());
            return true;

        default:
            _logger.warning("Failed to process send response active: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_response_active(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    SIP_Dialog *dialog = get_client_dialog(response);
    if (!dialog)
    {
        _logger.warning("Failed to process receive response active: invalid dialog (method=%d, status_code=%d) [%s]",
                        method, status_code, _id.to_string().c_str());
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_ACK:
        case SIP_REQUEST_CANCEL:
        case SIP_REQUEST_INFO:
        case SIP_REQUEST_INVITE:
        case SIP_REQUEST_MESSAGE:
        case SIP_REQUEST_NOTIFY:
        case SIP_REQUEST_OPTIONS:
        case SIP_REQUEST_PRACK:
        case SIP_REQUEST_REFER:
        case SIP_REQUEST_UPDATE:
            if ((status_code == 408) || (status_code == 481))
            {
                remove_dialog(dialog);

                _state = STATE_CLOSED;
                _logger.trace("Changed state in process receive response active (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());

                if (_receive_response_callback)
                    return _receive_response_callback(_receive_response_callback_data, this, request, response);
                return true;
            }

            //_state = STATE_ACTIVE;
            _logger.trace("Changed state in process receive response active (state=%d, method=%d, status_code=%d) [%s]",
                          _state, method, status_code, _id.to_string().c_str());

            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, request, response);
            return true;

        default:
            _logger.warning("Failed to process receive response active: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_response_closing_in(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    SIP_Dialog *dialog = get_server_dialog(response);
    if (!dialog)
    {
        _logger.warning("Failed to process send response closing in: invalid dialog (method=%d, status_code=%d) [%s]",
                        method, status_code, _id.to_string().c_str());
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_BYE:
            remove_dialog(dialog);

            _state = STATE_CLOSED;
            _logger.trace("Changed state in process send response closing in (state=%d, method=%d, status_code=%d) [%s]",
                          _state, method, status_code, _id.to_string().c_str());
            return true;

        default:
            _logger.warning("Failed to process send response closing in: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_response_closing_out(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    SIP_Dialog *dialog = get_client_dialog(response);
    if (!dialog)
    {
        _logger.warning("Failed to process receive response closing out: invalid dialog (method=%d, status_code=%d) [%s]",
                        method, status_code, _id.to_string().c_str());
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_BYE:
            remove_dialog(dialog);

            _state = STATE_CLOSED;
            _logger.trace("Changed state in process receive response closing out (state=%d, method=%d, status_code=%d) [%s]",
                          _state, method, status_code, _id.to_string().c_str());

            if (_receive_response_callback)
                return _receive_response_callback(_receive_response_callback_data, this, request, response);
            return true;

        default:
            _logger.warning("Failed to process receive response closing out: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_response_register_in(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    SIP_Dialog *dialog = get_server_dialog(response);
    if (dialog)
    {
        _logger.warning("Failed to process send response register in: invalid dialog (method=%d, status_code=%d) [%s]",
                        method, status_code, _id.to_string().c_str());
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_REGISTER:
            if ((status_code >= 100) && (status_code <= 199))
            {
                //_state = STATE_REGISTER_IN;
                _logger.trace("Changed state in process send response register in (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());
                return true;

            }else if ((status_code >= 200) && (status_code <= 699))
            {
                _state = STATE_CLOSED;
                _logger.trace("Changed state in process send response register in (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());
                return true;
            }

            _logger.warning("Failed to process send response register in: invalid status code (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;

        default:
            _logger.warning("Failed to process send response register in: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_response_register_out(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    SIP_Dialog *dialog = get_client_dialog(response);
    if (dialog)
    {
        _logger.warning("Failed to process receive response register out: invalid dialog (method=%d, status_code=%d) [%s]",
                        method, status_code, _id.to_string().c_str());
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_REGISTER:
            if ((status_code >= 100) && (status_code <= 199))
            {
                //_state = STATE_REGISTER_OUT;
                _logger.trace("Changed state in process receive response register out (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());

                if (_receive_response_callback)
                    return _receive_response_callback(_receive_response_callback_data, this, request, response);
                return true;

            }else if ((status_code >= 200) && (status_code <= 699))
            {
                _state = STATE_CLOSED;
                _logger.trace("Changed state in process receive response register out (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());

                if (_receive_response_callback)
                    return _receive_response_callback(_receive_response_callback_data, this, request, response);
                return true;
            }

            _logger.warning("Failed to process receive response register out: invalid status code (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;

        default:
            _logger.warning("Failed to process receive response register out: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_response_options_in(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    SIP_Dialog *dialog = get_server_dialog(response);
    if (dialog)
    {
        _logger.warning("Failed to process send response options in: invalid dialog (method=%d, status_code=%d) [%s]",
                        method, status_code, _id.to_string().c_str());
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_OPTIONS:
            if ((status_code >= 100) && (status_code <= 199))
            {
                //_state = STATE_OPTIONS_IN;
                _logger.trace("Changed state in process send response options in (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());
                return true;

            }else if ((status_code >= 200) && (status_code <= 699))
            {
                _state = STATE_CLOSED;
                _logger.trace("Changed state in process send response options in (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());
                return true;
            }

            _logger.warning("Failed to process send response options in: invalid status code (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;

        default:
            _logger.warning("Failed to process send response options in: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_response_options_out(SIP_Request *request, SIP_Response *response)
{
    SIP_Method_Type method = request->get_message_type();
    unsigned short status_code = response->get_status_code();

    SIP_Dialog *dialog = get_client_dialog(response);
    if (dialog)
    {
        _logger.warning("Failed to process receive response options out: invalid dialog (method=%d, status_code=%d) [%s]",
                        method, status_code, _id.to_string().c_str());
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_OPTIONS:
            if ((status_code >= 100) && (status_code <= 199))
            {
                //_state = STATE_OPTIONS_OUT;
                _logger.trace("Changed state in process receive response options out (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());

                if (_receive_response_callback)
                    return _receive_response_callback(_receive_response_callback_data, this, request, response);
                return true;

            }else if ((status_code >= 200) && (status_code <= 699))
            {
                _state = STATE_CLOSED;
                _logger.trace("Changed state in process receive response options out (state=%d, method=%d, status_code=%d) [%s]",
                              _state, method, status_code, _id.to_string().c_str());

                if (_receive_response_callback)
                    return _receive_response_callback(_receive_response_callback_data, this, request, response);
                return true;
            }

            _logger.warning("Failed to process receive response options out: invalid status code (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;

        default:
            _logger.warning("Failed to process receive response options out: invalid method (method=%d, status_code=%d) [%s]",
                            method, status_code, _id.to_string().c_str());
            return false;
    }
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call::send_response(SIP_Request *request, unsigned short status_code)
{
    if (!request)
    {
        _logger.warning("Failed to send response: invalid request [%s]", _id.to_string().c_str());
        return false;
    }

    SIP_Method_Type method = request->get_message_type();

    SIP_Response response(status_code, *request);
    if (!send_response(&response))
    {
        _logger.warning("Failed to send response: send response failed (method=%d, status_code=%d) [%s]",
                        method, status_code, _id.to_string().c_str());
        return false;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Call::transaction_send_message_callback(void *data, SIP_Transaction *transaction, SIP_Message *msg)
{
    SIP_Call *call = reinterpret_cast<SIP_Call *>(data);
    if ((!call) || (!transaction) || (!msg))
    {
        _logger.warning("Invalid transaction send message callback parameters");
        return false;
    }

    if (!call->_send_message_callback)
    {
        _logger.warning("Send message callback not configured [%s]", call->_id.to_string().c_str());
        return false;
    }

    if (!call->_send_message_callback(call->_send_message_callback_data, call, msg))
    {
        _logger.warning("Failed in transaction send message callback: send message callback failed [%s]", call->_id.to_string().c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Call::transaction_receive_request_callback(void *data, SIP_Transaction *transaction, SIP_Request *request)
{
    SIP_Call *call = reinterpret_cast<SIP_Call *>(data);
    if ((!call) || (!transaction) || (!request))
    {
        _logger.warning("Invalid transaction receive request callback parameters");
        return false;
    }

    return call->process_receive_request(request);
}

//-------------------------------------------

bool SIP_Call::transaction_receive_response_callback(void *data, SIP_Transaction *transaction, SIP_Request *request, SIP_Response *response)
{
    SIP_Call *call = reinterpret_cast<SIP_Call *>(data);
    if ((!call) || (!transaction) || (!request) || (!response))
    {
        _logger.warning("Invalid transaction receive response callback parameters");
        return false;
    }

    return call->process_receive_response(request, response);
}

//-------------------------------------------
