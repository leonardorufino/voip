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

#include "sip_request.h"
#include "sip_functions.h"

//-------------------------------------------

SIP_Request::SIP_Request(const SIP_Request &request) : SIP_Message(request)
{
    _method = request._method;
    _request_uri = request._request_uri;
    _sip_version = request._sip_version;
}

//-------------------------------------------

bool SIP_Request::parse_start_line(std::string &sip_msg)
{
    std::string line;
    SIP_Functions::get_line(sip_msg, line);

    _method = get_message_type(); // The method was already parsed by SIP_Message::decode_msg

    std::string result;
    SIP_Functions::skip(line, " \t");
    if (!SIP_Functions::match(line, " ", result))
    {
        std::cout << "SIP_Request::parse_start_line -> Failed to parse request URI (request_uri=" << line.c_str() << ")\n";
        return false;
    }

    _request_uri = result;

    SIP_Functions::trim(line);
    _sip_version = line;
    if ((_sip_version.empty()) || (_sip_version != SIP_VERSION))
    {
        std::cout << "SIP_Request::parse_start_line -> Failed to parse SIP version (version=" << _sip_version.c_str() << ")\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Request::encode_start_line(std::string &sip_msg)
{
    std::string method = SIP_Functions::get_method_type(_method);
    if ((method.empty()) || (_request_uri.empty()) || (_sip_version.empty()))
        return false;

    sip_msg += method;
    sip_msg += " ";
    sip_msg += _request_uri;
    sip_msg += " ";
    sip_msg += _sip_version;
    sip_msg += "\r\n";
    return true;
}

//-------------------------------------------

void SIP_Request::set_request_line(SIP_Method_Type msg_type, std::string request_uri, std::string sip_version)
{
    _method = msg_type;
    _request_uri = request_uri;
    _sip_version = sip_version;
}

//-------------------------------------------
