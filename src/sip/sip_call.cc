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
        case STATE_WAITING_ACK_IN:  return "Waiting ACK In";
        case STATE_WAITING_ACK_OUT: return "Waiting ACK Out";
        case STATE_ACTIVE:          return "Active";
        case STATE_CLOSING_IN:      return "Closing In";
        case STATE_CLOSING_OUT:     return "Closing Out";
        case STATE_CLOSED:          return "Closed";
        default:                    return "Invalid";
    }
}

//-------------------------------------------

void SIP_Call::set_create_response_callback(create_response_callback *callback, void *data)
{
    _create_response_callback = callback;
    _create_response_data = data;
}

//-------------------------------------------

SIP_Response *SIP_Call::call_create_response_callback(SIP_Request *request, unsigned short status_code)
{
    try
    {
        if (_create_response_callback)
        {
            _logger.trace("Calling create response callback");
            return _create_response_callback(_create_response_data, this, request, status_code);
        }

        _logger.trace("Create response callback not configured");
        return NULL;
    }catch (std::exception &e)
    {
        _logger.warning("Exception when calling create response callback (msg=%s)", e.what());
        return NULL;
    }catch (...)
    {
        _logger.warning("Exception when calling create response callback");
        return NULL;
    }
}

//-------------------------------------------

void SIP_Call::set_send_response_callback(send_response_callback *callback, void *data)
{
    _send_response_callback = callback;
    _send_response_data = data;
}

//-------------------------------------------

bool SIP_Call::call_send_response_callback(SIP_Request *request, SIP_Response *response)
{
    try
    {
        if (_send_response_callback)
        {
            _logger.trace("Calling send response callback");
            return _send_response_callback(_send_response_data, this, request, response);
        }

        _logger.trace("Send response callback not configured");
        return false;
    }catch (std::exception &e)
    {
        _logger.warning("Exception when calling send response callback (msg=%s)", e.what());
        return false;
    }catch (...)
    {
        _logger.warning("Exception when calling send response callback");
        return false;
    }
}

//-------------------------------------------

SIP_Dialog *SIP_Call::get_client_dialog(SIP_Message *msg)
{
    SIP_Header_Call_ID *header_call_id = dynamic_cast<SIP_Header_Call_ID *>(msg->get_header(SIP_HEADER_CALL_ID));
    SIP_Header_From *header_from = dynamic_cast<SIP_Header_From *>(msg->get_header(SIP_HEADER_FROM));
    SIP_Header_To *header_to = dynamic_cast<SIP_Header_To *>(msg->get_header(SIP_HEADER_TO));

    if ((!header_call_id) || (!header_from) || (!header_to))
    {
        _logger.warning("Failed to get client dialog: invalid headers");
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
        _logger.warning("Failed to get server dialog: invalid headers");
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

        if ((dialog->get_call_id() == call_id) && (dialog->get_local_tag() == local_tag) && (dialog->get_remote_tag() == remote_tag))
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

bool SIP_Call::process_send_request(SIP_Request *request)
{
    if (!request)
    {
        _logger.warning("Failed to process send request: invalid request");
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
        {
            _logger.warning("Failed to process send request: invalid state (state=%d, method=%d)", _state, request->get_message_type());
            return false;
        }
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_request(SIP_Request *request)
{
    if (!request)
    {
        _logger.warning("Failed to process receive request: invalid request");
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
        {
            _logger.warning("Failed to process receive request: invalid state (state=%d, method=%d)", _state, request->get_message_type());
            return false;
        }
    }
}

//-------------------------------------------

bool SIP_Call::process_send_response(SIP_Request *request, SIP_Response *response)
{
    if ((!request) || (!response))
    {
        _logger.warning("Failed to process send response: invalid messages");
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

        case STATE_ACTIVE:
            return process_send_response_active(request, response);

        case STATE_CLOSING_IN:
            return process_send_response_closing_in(request, response);

        default:
        {
            _logger.warning("Failed to process receive request: invalid state (state=%d, method=%d, status_code=%d)",
                            _state, request->get_message_type(), response->get_status_code());
            return false;
        }
    };
}

//-------------------------------------------

bool SIP_Call::process_receive_response(SIP_Request *request, SIP_Response *response)
{
    if ((!request) || (!response))
    {
        _logger.warning("Failed to process receive response: invalid messages");
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

        case STATE_ACTIVE:
            return process_receive_response_active(request, response);

        case STATE_CLOSING_OUT:
            return process_receive_response_closing_out(request, response);

        default:
        {
            _logger.warning("Failed to process receive request: invalid state (state=%d, method=%d, status_code=%d)",
                            _state, request->get_message_type(), response->get_status_code());
            return false;
        }
    };
}

//-------------------------------------------

bool SIP_Call::process_send_request_idle(SIP_Request *request)
{
    SIP_Method_Type method = request->get_message_type();

    SIP_Dialog *dialog = get_client_dialog(request);
    if (dialog)
    {
        _logger.warning("Failed to process send request idle: invalid dialog (method=%d)", method);
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_INVITE:
            _state = STATE_CALLING_OUT;
            _logger.trace("Changed state in process send request idle (state=%d, method=%d)", _state, method);
            return true;

        default:
            _logger.warning("Failed to process request idle: invalid method (method=%d)", method);
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_request_idle(SIP_Request *request)
{
    SIP_Method_Type method = request->get_message_type();

    SIP_Dialog *dialog = get_server_dialog(request);
    if (dialog)
    {
        _logger.warning("Failed to process receive request idle: invalid dialog (method=%d)", method);

        SIP_Response *response = call_create_response_callback(request, 481);
        if (response)
        {
            call_send_response_callback(request, response);
            delete response;
        }

        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_INVITE:
        {
            SIP_Header_To *header_to = dynamic_cast<SIP_Header_To *>(request->get_header(SIP_HEADER_TO));
            if (!header_to)
            {
                _logger.warning("Failed to process receive request idle: invalid TO header (method=%d)", method);
                return false;
            }

            if (!header_to->get_tag().empty())
            {
                _logger.warning("Failed to process receive request idle: invalid TO header tag (method=%d)", method);

                SIP_Response *response = call_create_response_callback(request, 481);
                if (response)
                {
                    call_send_response_callback(request, response);
                    delete response;
                }

                return false;
            }

            _state = STATE_CALLING_IN;
            _logger.trace("Changed state in process receive request idle (state=%d, method=%d)", _state, method);
            return true;
        }

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
        _logger.warning("Failed to process send response calling in: invalid dialog (method=%d, status_code=%d)", method, status_code);
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
                    _logger.warning("Failed to process send response calling in: invalid TO header (method=%d, status_code=%d)",
                                    method, status_code);
                    return false;
                }

                if ((!header_to->get_tag().empty()) && (response->get_header_size(SIP_HEADER_CONTACT) > 0))
                {
                    SIP_Dialog *new_dialog = new SIP_Dialog();
                    if (!new_dialog->set_server_dialog(request, response))
                    {
                        delete new_dialog;
                        _logger.warning("Failed to process send response calling in: set server dialog failed (method=%d, status_code=%d)",
                                        method, status_code);
                        return false;
                    }

                    add_dialog(new_dialog);
                }

                _state = STATE_RINGING_IN;
                _logger.trace("Changed state in process send response calling in (state=%d, method=%d, status_code=%d)",
                              _state, method, status_code);
                return true;

            }else if ((status_code >= 200) && (status_code <= 299))
            {
                SIP_Dialog *new_dialog = new SIP_Dialog();
                if (!new_dialog->set_server_dialog(request, response))
                {
                    delete new_dialog;
                    _logger.warning("Failed to process send response calling in: set server dialog failed (method=%d, status_code=%d)",
                                    method, status_code);
                    return false;
                }

                add_dialog(new_dialog);

                _state = STATE_WAITING_ACK_IN;
                _logger.trace("Changed state in process send response calling in (state=%d, method=%d, status_code=%d)",
                              _state, method, status_code);
                return true;

            }else if ((status_code >= 300) && (status_code <= 699))
            {
                _state = STATE_CLOSED;
                _logger.trace("Changed state in process send response calling in (state=%d, method=%d, status_code=%d)",
                              _state, method, status_code);
                return true;
            }

        default:
            _logger.warning("Failed to process send response calling in (method=%d, status_code=%d)", method, status_code);
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
        _logger.warning("Failed to process receive response calling out: invalid dialog (method=%d, status_code=%d)", method, status_code);
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
                    _logger.warning("Failed to process receive response calling out: invalid TO header (method=%d, status_code=%d)",
                                    method, status_code);
                    return false;
                }

                if ((!header_to->get_tag().empty()) && (response->get_header_size(SIP_HEADER_CONTACT) > 0))
                {
                    SIP_Dialog *new_dialog = new SIP_Dialog();
                    if (!new_dialog->set_client_dialog(request, response))
                    {
                        delete new_dialog;
                        _logger.warning("Failed to process receive response calling out: set client dialog failed (method=%d, status_code=%d)",
                                        method, status_code);
                        return false;
                    }

                    add_dialog(new_dialog);
                }

                _state = STATE_RINGING_OUT;
                _logger.trace("Changed state in process receive response calling out (state=%d, method=%d, status_code=%d)",
                              _state, method, status_code);
                return true;

            }else if ((status_code >= 200) && (status_code <= 299))
            {
                SIP_Dialog *new_dialog = new SIP_Dialog();
                if (!new_dialog->set_client_dialog(request, response))
                {
                    delete new_dialog;
                    _logger.warning("Failed to process receive response calling out: set client dialog failed (method=%d, status_code=%d)",
                                    method, status_code);
                    return false;
                }

                add_dialog(new_dialog);

                _state = STATE_WAITING_ACK_OUT;
                _logger.trace("Changed state in process receive response calling out (state=%d, method=%d, status_code=%d)",
                              _state, method, status_code);
                return true;

            }else if ((status_code >= 300) && (status_code <= 699))
            {
                _state = STATE_CLOSED;
                _logger.trace("Changed state in process receive response calling out (state=%d, method=%d, status_code=%d)",
                              _state, method, status_code);
                return true;
            }

        default:
            _logger.warning("Failed to process receive response calling out (method=%d, status_code=%d)", method, status_code);
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
                _logger.warning("Failed to process send request ringing in: invalid dialog (method=%d)", method);
                return false;
            }

            //_state = STATE_RINGING_IN;
            _logger.trace("Changed state in process send request ringing in (state=%d, method=%d)", _state, method);
            return true;
        }

        default:
            _logger.warning("Failed to process send request ringing in: invalid method (method=%d)", method);
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_receive_request_ringing_in(SIP_Request *request)
{
    SIP_Method_Type method = request->get_message_type();

    switch (method)
    {
        case SIP_REQUEST_UPDATE:
        {
            SIP_Dialog *dialog = get_server_dialog(request);
            if (!dialog)
            {
                _logger.warning("Failed to process receive request ringing in: invalid dialog (method=%d)", method);
                return false;
            }

            //_state = STATE_RINGING_IN;
            _logger.trace("Changed state in process receive request ringing in (state=%d, method=%d)", _state, method);
            return true;
        }

        default:
            _logger.warning("Failed to process receive request ringing in: invalid method (method=%d)", method);
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
                    _logger.warning("Failed to process send response ringing in: invalid TO header (method=%d, status_code=%d)",
                                    method, status_code);
                    return false;
                }

                if ((!header_to->get_tag().empty()) && (response->get_header_size(SIP_HEADER_CONTACT) > 0))
                {
                    SIP_Dialog *dialog = get_server_dialog(response);
                    if (!dialog)
                    {
                        SIP_Dialog *new_dialog = new SIP_Dialog();
                        if (!new_dialog->set_server_dialog(request, response))
                        {
                            delete new_dialog;
                            _logger.warning("Failed to process send response ringing in: set server dialog failed (method=%d, status_code=%d)",
                                            method, status_code);
                            return false;
                        }

                        add_dialog(new_dialog);
                    }
                }

                //_state = STATE_RINGING_IN;
                _logger.trace("Changed state in process send response ringing in (state=%d, method=%d, status_code=%d)",
                              _state, method, status_code);
                return true;

            }else if ((status_code >= 200) && (status_code <= 299))
            {
                SIP_Dialog *dialog = get_server_dialog(response);
                if (!dialog)
                {
                    SIP_Dialog *new_dialog = new SIP_Dialog();
                    if (!new_dialog->set_server_dialog(request, response))
                    {
                        delete new_dialog;
                        _logger.warning("Failed to process send response ringing in: set server dialog failed (method=%d, status_code=%d)",
                                        method, status_code);
                        return false;
                    }

                    add_dialog(new_dialog);
                }

                _state = STATE_WAITING_ACK_IN;
                _logger.trace("Changed state in process send response ringing in (state=%d, method=%d, status_code=%d)",
                              _state, method, status_code);
                return true;

            }else if ((status_code >= 300) && (status_code <= 699))
            {
                SIP_Dialog *dialog = get_server_dialog(response);
                if (dialog)
                    remove_dialog(dialog);

                _state = STATE_CLOSED;
                _logger.trace("Changed state in process send response ringing in (state=%d, method=%d, status_code=%d)",
                              _state, method, status_code);
                return true;
            }

        case SIP_REQUEST_UPDATE:
        {
            SIP_Dialog *dialog = get_server_dialog(response);
            if (!dialog)
            {
                _logger.warning("Failed to process send response ringing in: invalid dialog (method=%d, status_code=%d)",
                                method, status_code);
                return false;
            }

            //_state = STATE_RINGING_IN;
            _logger.trace("Changed state in process send response ringing in (state=%d, method=%d, status_code=%d)",
                          _state, method, status_code);
            return true;
        }

        default:
            _logger.warning("Failed to process send response ringing in: invalid method (method=%d, status_code=%d)",
                            method, status_code);
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
                _logger.warning("Failed to process receive response ringing in: invalid dialog (method=%d, status_code=%d)",
                                method, status_code);
                return false;
            }

            //_state = STATE_RINGING_IN;
            _logger.trace("Changed state in process receive response ringing in (state=%d, method=%d, status_code=%d)",
                          _state, method, status_code);
            return true;
        }

        default:
            _logger.warning("Failed to process receive response ringing in: invalid method (method=%d, status_code=%d)",
                            method, status_code);
            return false;
    }
}

//-------------------------------------------

bool SIP_Call::process_send_request_ringing_out(SIP_Request *request)
{
    SIP_Method_Type method = request->get_message_type();

    switch (method)
    {
        case SIP_REQUEST_UPDATE:
        {
            SIP_Dialog *dialog = get_client_dialog(request);
            if (!dialog)
            {
                _logger.warning("Failed to process send request ringing out: invalid dialog (method=%d)", method);
                return false;
            }

            //_state = STATE_RINGING_OUT;
            _logger.trace("Changed state in process send request ringing out (state=%d, method=%d)", _state, method);
            return true;
        }

        default:
            _logger.warning("Failed to process send request ringing out: invalid method (method=%d)", method);
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
                _logger.warning("Failed to process receive request ringing out: invalid dialog (method=%d)", method);
                return false;
            }

            //_state = STATE_RINGING_OUT;
            _logger.trace("Changed state in process receive request ringing out (state=%d, method=%d)", _state, method);
            return true;
        }

        default:
            _logger.warning("Failed to process receive request ringing out: invalid method (method=%d)", method);
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
                _logger.warning("Failed to process send response ringing out: invalid dialog (method=%d, status_code=%d)",
                                method, status_code);
                return false;
            }

            //_state = STATE_RINGING_OUT;
            _logger.trace("Changed state in process send response ringing out (state=%d, method=%d, status_code=%d)",
                          _state, method, status_code);
            return true;
        }

        default:
            _logger.warning("Failed to process receive response ringing out: invalid method (method=%d, status_code=%d)",
                            method, status_code);
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
                    _logger.warning("Failed to process receive response ringing out: invalid TO header (method=%d, status_code=%d)",
                                    method, status_code);
                    return false;
                }

                if ((!header_to->get_tag().empty()) && (response->get_header_size(SIP_HEADER_CONTACT) > 0))
                {
                    SIP_Dialog *dialog = get_client_dialog(response);
                    if (!dialog)
                    {
                        SIP_Dialog *new_dialog = new SIP_Dialog();
                        if (!new_dialog->set_client_dialog(request, response))
                        {
                            delete new_dialog;
                            _logger.warning("Failed to process receive response ringing out: set client dialog failed (method=%d, status_code=%d)",
                                            method, status_code);
                            return false;
                        }

                        add_dialog(new_dialog);
                    }else
                    {
                        SIP_Header_Contact *header_contact = dynamic_cast<SIP_Header_Contact *>(response->get_header(SIP_HEADER_CONTACT));
                        if (header_contact)
                            dialog->set_remote_target(header_contact->get_address());
                    }
                }

                //_state = STATE_RINGING_OUT;
                _logger.trace("Changed state in process receive response ringing out (state=%d, method=%d, status_code=%d)",
                              _state, method, status_code);
                return true;

            }else if ((status_code >= 200) && (status_code <= 299))
            {
                SIP_Dialog *dialog = get_client_dialog(response);
                if (!dialog)
                {
                    SIP_Dialog *new_dialog = new SIP_Dialog();
                    if (!new_dialog->set_client_dialog(request, response))
                    {
                        delete new_dialog;
                        _logger.warning("Failed to process receive response ringing out: set client dialog failed (method=%d, status_code=%d)",
                                        method, status_code);
                        return false;
                    }

                    add_dialog(new_dialog);
                }else
                {
                    SIP_Header_Contact *header_contact = dynamic_cast<SIP_Header_Contact *>(response->get_header(SIP_HEADER_CONTACT));
                    if (header_contact)
                        dialog->set_remote_target(header_contact->get_address());
                }

                _state = STATE_WAITING_ACK_OUT;
                _logger.trace("Changed state in process receive response ringing out (state=%d, method=%d, status_code=%d)",
                              _state, method, status_code);
                return true;

            }else if ((status_code >= 300) && (status_code <= 699))
            {
                SIP_Dialog *dialog = get_client_dialog(response);
                if (dialog)
                    remove_dialog(dialog);

                _state = STATE_CLOSED;
                _logger.trace("Changed state in process receive response ringing out (state=%d, method=%d, status_code=%d)",
                              _state, method, status_code);
                return true;
            }

        case SIP_REQUEST_UPDATE:
        {
            SIP_Dialog *dialog = get_client_dialog(response);
            if (!dialog)
            {
                _logger.warning("Failed to process receive response ringing out: invalid dialog (method=%d, status_code=%d)",
                                method, status_code);
                return false;
            }

            //_state = STATE_RINGING_OUT;
            _logger.trace("Changed state in process receive response ringing out (state=%d, method=%d, status_code=%d)",
                          _state, method, status_code);
            return true;
        }

        default:
            _logger.warning("Failed to process receive response ringing out: invalid method (method=%d, status_code=%d)",
                            method, status_code);
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
        _logger.warning("Failed to process receive request waiting ack in: invalid dialog (method=%d)", method);
        return false;
    }

    SIP_Header_CSeq *header_cseq = dynamic_cast<SIP_Header_CSeq *>(request->get_header(SIP_HEADER_CSEQ));
    if (!header_cseq)
    {
        _logger.warning("Failed to process receive request waiting ack in: invalid CSeq header (method=%d)", method);
        return false;
    }

    unsigned long cseq_sequence = header_cseq->get_sequence();
    unsigned long dialog_sequence = dialog->get_remote_sequence();

    if ((dialog_sequence == SIP_Header_CSeq::INVALID_SEQUENCE) || (cseq_sequence != dialog_sequence))
    {
        _logger.warning("Failed to process receive request waiting ack in: incorrect CSeq sequence (method=%d, seq=%d, expected=%d)",
                        method, cseq_sequence, dialog_sequence);
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_ACK:
            _state = STATE_ACTIVE;
            _logger.trace("Changed state in process receive request waiting ack in (state=%d, method=%d)", _state, method);
            return true;

        default:
            _logger.warning("Failed to process receive request waiting ack in: invalid method (method=%d)", method);
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
        _logger.warning("Failed to process send request waiting ack out: invalid dialog (method=%d)", method);
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_ACK:
            _state = STATE_ACTIVE;
            _logger.trace("Changed state in process send request waiting ack out (state=%d, method=%d)", _state, method);
            return true;

        default:
            _logger.warning("Failed to process send request waiting ack out: invalid method (method=%d)", method);
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
        _logger.warning("Failed to process send request active: invalid dialog (method=%d)", method);
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_BYE:
            _state = STATE_CLOSING_OUT;
            _logger.trace("Changed state in process send request active (state=%d, method=%d)", _state, method);
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
            _logger.trace("Changed state in process send request active (state=%d, method=%d)", _state, method);
            return true;

        default:
            _logger.warning("Failed to process send request active: invalid method (method=%d)", method);
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
        _logger.warning("Failed to process receive request active: invalid dialog (method=%d)", method);
        return false;
    }

    SIP_Header_CSeq *header_cseq = dynamic_cast<SIP_Header_CSeq *>(request->get_header(SIP_HEADER_CSEQ));
    if (!header_cseq)
    {
        _logger.warning("Failed to process receive request active: invalid CSeq header (method=%d)", method);
        return false;
    }

    unsigned long cseq_sequence = header_cseq->get_sequence();
    unsigned long dialog_sequence = dialog->get_remote_sequence();

    if ((dialog_sequence == SIP_Header_CSeq::INVALID_SEQUENCE) || (cseq_sequence > dialog_sequence))
    {
        dialog->set_remote_sequence(cseq_sequence);

    }else if (cseq_sequence < dialog_sequence)
    {
        _logger.warning("Failed to process receive request active: CSeq sequence is lower than the last one (method=%d, seq=%d, last=%d)",
                        method, cseq_sequence, dialog_sequence);

        SIP_Response *response = call_create_response_callback(request, 500);
        if (response)
        {
            call_send_response_callback(request, response);
            delete response;
        }

        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_BYE:
            _state = STATE_CLOSING_IN;
            _logger.trace("Changed state in process receive request active (state=%d, method=%d)", _state, method);
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
            _logger.trace("Changed state in process receive request active (state=%d, method=%d)", _state, method);
            return true;

        default:
            _logger.warning("Failed to process receive request active: invalid method (method=%d)", method);
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
        _logger.warning("Failed to process send response active: invalid dialog (method=%d, status_code=%d)", method, status_code);
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
                _logger.trace("Changed state in process send response active (state=%d, method=%d, status_code=%d)",
                              _state, method, status_code);
                return true;
            }

            //_state = STATE_ACTIVE;
            _logger.trace("Changed state in process send response active (state=%d, method=%d, status_code=%d)",
                          _state, method, status_code);
            return true;

        default:
            _logger.warning("Failed to process send response active: invalid method (method=%d, status_code=%d)", method, status_code);
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
        _logger.warning("Failed to process receive response active: invalid dialog (method=%d, status_code=%d)", method, status_code);
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
                _logger.trace("Changed state in process receive response active (state=%d, method=%d, status_code=%d)",
                              _state, method, status_code);
                return true;
            }

            //_state = STATE_ACTIVE;
            _logger.trace("Changed state in process receive response active (state=%d, method=%d, status_code=%d)",
                          _state, method, status_code);
            return true;

        default:
            _logger.warning("Failed to process receive response active: invalid method (method=%d, status_code=%d)", method, status_code);
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
        _logger.warning("Failed to process send response closing in: invalid dialog (method=%d, status_code=%d)",
                        method, status_code);
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_BYE:
            remove_dialog(dialog);

            _state = STATE_CLOSED;
            _logger.trace("Changed state in process send response closing in (state=%d, method=%d, status_code=%d)",
                          _state, method, status_code);
            return true;

        default:
            _logger.warning("Failed to process send response closing in: invalid method (method=%d, status_code=%d)",
                            method, status_code);
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
        _logger.warning("Failed to process receive response closing out: invalid dialog (method=%d, status_code=%d)", method, status_code);
        return false;
    }

    switch (method)
    {
        case SIP_REQUEST_BYE:
            remove_dialog(dialog);

            _state = STATE_CLOSED;
            _logger.trace("Changed state in process receive response closing out (state=%d, method=%d, status_code=%d)",
                          _state, method, status_code);
            return true;

        default:
            _logger.warning("Failed to process receive response closing out: invalid method (method=%d, status_code=%d)",
                            method, status_code);
            return false;
    }
}

//-------------------------------------------
