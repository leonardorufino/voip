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

#include "sip_response.h"
#include "sip_functions.h"

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
    SIP_Functions::get_line(sip_msg, line);

    _sip_version = SIP_VERSION; // The version was already decoded by SIP_Message::decode_msg

    std::string result;
    SIP_Functions::skip(line, " \t");
    if (!SIP_Functions::match(line, " ", result))
    {
        std::cout << "SIP_Response::decode_start_line -> Failed to decode status code (status_code=" << line.c_str() << ")\n";
        return false;
    }

    _status_code = (unsigned short) atol(result.c_str());
    if ((_status_code < 100) || (_status_code > 699))
    {
        std::cout << "SIP_Response::decode_start_line -> Invalid status code (status_code=" << _status_code << ")\n";
        return false;
    }

    SIP_Functions::trim(line);
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
