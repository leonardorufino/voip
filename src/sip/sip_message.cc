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

#include "sip_message.h"
#include "sip_functions.h"
#include "util/string_functions.h"

Logger SIP_Message::_logger(Log_Manager::LOG_SIP_MESSAGE);

//-------------------------------------------

SIP_Message::SIP_Message(const SIP_Message &message)
{
    sip_header_map::const_iterator it1 = message._headers.begin();
    while (it1 != message._headers.end())
    {
        sip_header_list headers = it1->second;
        it1++;

        sip_header_list::const_iterator it2 = headers.begin();
        while (it2 != headers.end())
        {
            SIP_Header *header = *it2++;
            SIP_Header *new_header = SIP_Header::create_header(header->get_header_type(), header);
            add_header(new_header);
        }
    }
}

//-------------------------------------------

SIP_Message::~SIP_Message()
{
    sip_header_map::const_iterator it1 = _headers.begin();
    while (it1 != _headers.end())
    {
        sip_header_list headers = it1->second;
        it1++;

        sip_header_list::const_iterator it2 = headers.begin();
        while (it2 != headers.end())
        {
            SIP_Header *header = *it2++;
            delete header;
        }
    }

    _headers.clear();
}

//-------------------------------------------

SIP_Message *SIP_Message::decode_msg(std::string sip_msg)
{
    String_Functions::remove_lws(sip_msg);

    std::string msg;
    String_Functions::match(sip_msg, " ", msg);
    String_Functions::trim(msg);

    SIP_Method_Type method = SIP_Functions::get_method_type(msg);
    if (method == SIP_METHOD_INVALID)
    {
        _logger.warning("SIP_Message::decode_msg -> Invalid method (method=%s)", msg.c_str());
        return NULL;
    }

    SIP_Message *message;
    if (method != SIP_RESPONSE)
        message = new SIP_Request(method);
    else
        message = new SIP_Response();

    if (!message->decode(sip_msg))
    {
        _logger.warning("SIP_Message::decode_msg -> Failed to decode message (method=%s)", msg.c_str());
        delete message;
        return NULL;
    }

    return message;
}

//-------------------------------------------

bool SIP_Message::decode(std::string &sip_msg)
{
    if (!decode_start_line(sip_msg))
        return false;

    if (!decode_header(sip_msg))
        return false;

    if (!decode_body(sip_msg))
        return false;

    return true;
}

//-------------------------------------------

bool SIP_Message::decode_header(std::string &sip_msg)
{
    std::string line;
    while (true)
    {
        bool ret = String_Functions::get_line(sip_msg, line);
        if ((!ret) || (line.empty()))
            return true;

        sip_header_list headers;

        if (!SIP_Header::decode_headers(line, headers))
            return false;

        add_headers(headers);
    }

    return true;
}

//-------------------------------------------

bool SIP_Message::decode_body(std::string &sip_msg)
{
    SIP_Header_Content_Type *content_type = (SIP_Header_Content_Type *) get_header(SIP_HEADER_CONTENT_TYPE);
    if (content_type)
    {
        //TODO: Decode body
    }

    return true;
}

//-------------------------------------------

bool SIP_Message::encode(std::string &sip_msg)
{
    std::string body_msg;

    if (!encode_start_line(sip_msg))
        return false;

    if (!encode_body(body_msg))
        return false;

    if (!encode_header(sip_msg, body_msg))
        return false;

    return true;
}

//-------------------------------------------

bool SIP_Message::encode_header(std::string &sip_msg, std::string &body_msg)
{
    sip_header_map::const_iterator it = _headers.begin();
    while (it != _headers.end())
    {
        sip_header_list headers = it->second;
        it++;

        if (!SIP_Header::encode_headers(sip_msg, headers))
            return false;
    }

    sip_msg += "\r\n";
    sip_msg += body_msg;
    return true;
}

//-------------------------------------------

bool SIP_Message::encode_body(std::string &sip_msg)
{
    //TODO: Encode body
    return true;
}

//-------------------------------------------

void SIP_Message::add_header(SIP_Header *header)
{
    if (!header)
        return;

    SIP_Header_Type header_type = header->get_header_type();

    if (_headers.count(header_type) > 0)
    {
        sip_header_list &headers = _headers.at(header_type);
        headers.push_back(header);
    }else
    {
        sip_header_list headers;
        headers.push_back(header);
        _headers[header_type] = headers;
    }
}

//-------------------------------------------

void SIP_Message::add_headers(sip_header_list &headers)
{
    if (headers.empty())
        return;

    sip_header_list::const_iterator it = headers.begin();
    while (it != headers.end())
    {
        SIP_Header *header = *it++;
        add_header(header);
    }
}

//-------------------------------------------

SIP_Header *SIP_Message::get_header(SIP_Header_Type header_type, unsigned short pos)
{
    if (_headers.count(header_type) == 0)
        return NULL;

    unsigned int count = 0;

    sip_header_list &headers = _headers.at(header_type);
    sip_header_list::const_iterator it = headers.begin();
    while (it != headers.end())
    {
        SIP_Header *header = *it++;

        if (count++ == pos)
            return header;
    }

    return NULL;
}

//-------------------------------------------

unsigned short SIP_Message::get_header_size(SIP_Header_Type header_type)
{
    if (_headers.count(header_type) == 0)
        return 0;

    sip_header_list &headers = _headers.at(header_type);
    return (unsigned short) headers.size();
}

//-------------------------------------------
//-------------------------------------------

SIP_Request::SIP_Request(const SIP_Request &request) : SIP_Message(request)
{
    _method = request._method;
    _request_uri = request._request_uri;
    _sip_version = request._sip_version;
}

//-------------------------------------------

bool SIP_Request::decode_start_line(std::string &sip_msg)
{
    std::string line;
    String_Functions::get_line(sip_msg, line);

    _method = get_message_type(); // The method was already decoded by SIP_Message::decode_msg

    std::string result;
    String_Functions::skip(line, " \t");
    if (!String_Functions::match(line, " ", result))
    {
        _logger.warning("SIP_Request::decode_start_line -> Failed to decode request URI (request_uri=%s)", line.c_str());
        return false;
    }

    if (!_request_uri.decode(result))
        return false;

    String_Functions::trim(line);
    _sip_version = line;
    if ((_sip_version.empty()) || (_sip_version != SIP_VERSION))
    {
        _logger.warning("SIP_Request::decode_start_line -> Failed to decode SIP version (version=%s)", _sip_version.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Request::encode_start_line(std::string &sip_msg)
{
    std::string method = SIP_Functions::get_method_type(_method);
    if ((method.empty()) || (_sip_version.empty()))
        return false;

    sip_msg += method;
    sip_msg += " ";

    if (!_request_uri.encode(sip_msg))
        return false;

    sip_msg += " ";
    sip_msg += _sip_version;
    sip_msg += "\r\n";
    return true;
}

//-------------------------------------------

void SIP_Request::set_request_line(SIP_Method_Type msg_type, const SIP_Address &request_uri, std::string sip_version)
{
    _method = msg_type;
    _request_uri = request_uri;
    _sip_version = sip_version;
}

//-------------------------------------------
//-------------------------------------------

SIP_Response::SIP_Response(unsigned short status_code) : _status_code(INVALID_STATUS_CODE)
{
    unsigned short i = 0;
    while (_status_codes[i]._code != INVALID_STATUS_CODE)
    {
        if (_status_codes[i]._code == status_code)
        {
            set_status_line(SIP_VERSION, status_code, _status_codes[i]._reason_phrase);
            return;
        }
        i++;
    }
}

//-------------------------------------------

SIP_Response::SIP_Response(const SIP_Response &response) : SIP_Message(response)
{
    _sip_version = response._sip_version;
    _status_code = response._status_code;
    _reason_phrase = response._reason_phrase;
}

//-------------------------------------------

bool SIP_Response::decode_start_line(std::string &sip_msg)
{
    std::string line;
    String_Functions::get_line(sip_msg, line);

    _sip_version = SIP_VERSION; // The version was already decoded by SIP_Message::decode_msg

    std::string result;
    String_Functions::skip(line, " \t");
    if (!String_Functions::match(line, " ", result))
    {
        _logger.warning("SIP_Response::decode_start_line -> Failed to decode status code (status_code=%s)", line.c_str());
        return false;
    }

    _status_code = String_Functions::str_to_us(result);
    if ((_status_code < 100) || (_status_code > 699))
    {
        _logger.warning("SIP_Response::decode_start_line -> Invalid status code (status_code=%d)", _status_code);
        return false;
    }

    String_Functions::trim(line);
    _reason_phrase = line; //It can be empty!
    return true;
}

//-------------------------------------------

bool SIP_Response::encode_start_line(std::string &sip_msg)
{
    if ((_sip_version.empty()) || (_status_code < 100) || (_status_code > 699))
        return false;

    sip_msg += _sip_version;
    sip_msg += " ";
    sip_msg += std::to_string(_status_code);
    sip_msg += " ";
    sip_msg += _reason_phrase;
    sip_msg += "\r\n";
    return true;
}

//-------------------------------------------

void SIP_Response::set_status_line(std::string sip_version, unsigned short status_code, std::string reason_phrase)
{
    _sip_version = sip_version;
    _status_code = status_code;
    _reason_phrase = reason_phrase;
}

//-------------------------------------------

SIP_Response::SIP_Status_Code SIP_Response::_status_codes[] =
{
    //Informational
    { 100, "Trying" },
    { 180, "Ringing" },
    { 181, "Call is Being Forwarded" },
    { 182, "Queued" },
    { 183, "Session Progress" },

    //Success
    { 200, "OK" },
    { 202, "Accepted" },

    //Redirection
    { 300, "Multiple Choices" },
    { 301, "Moved Permanently" },
    { 302, "Moved Temporarily" },
    //{ 303, "See Other" },
    { 305, "Use Proxy" },
    { 380, "Alternative Service" },

    //Client-Error
    { 400, "Bad Request" },
    { 401, "Unauthorized" },
    { 402, "Payment Required" },
    { 403, "Forbidden" },
    { 404, "Not Found" },
    { 405, "Method Not Allowed" },
    { 406, "Not Acceptable" },
    { 407, "Proxy Authentication Required" },
    { 408, "Request Timeout" },
    { 409, "Conflict" },
    { 410, "Gone" },
    //{ 411, "Length Required" },
    { 413, "Request Entity Too Large" },
    { 414, "Request-URI Too Large" },
    { 415, "Unsupported Media Type" },
    { 420, "Bad Extension" },
    { 480, "Temporarily Unavailable" },
    { 481, "Call Leg/Transaction Does Not Exist" },
    { 482, "Loop Detected" },
    { 483, "Too Many Hops" },
    { 484, "Address Incomplete" },
    { 485, "Ambiguous" },
    { 486, "Busy Here" },
    { 487, "Request Terminated" },
    { 488, "Not Acceptable Here" },
    { 489, "Bad Event" },

    //Server-Error
    { 500, "Server Internal Error" },
    { 501, "Not Implemented" },
    { 502, "Bad Gateway" },
    { 503, "Service Unavailable" },
    { 504, "Server Timed-out" },
    { 505, "Version Not Supported" },
    { 513, "Message Too Large" },

    //Global-Failure
    { 600, "Busy Everywhere" },
    { 603, "Decline" },
    { 604, "Does Not Exist Anywhere" },
    { 606, "Not Acceptable" },

    { INVALID_STATUS_CODE, "Unknown" },
};

//-------------------------------------------
