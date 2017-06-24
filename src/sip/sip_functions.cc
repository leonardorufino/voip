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

#include "sip_functions.h"

//-------------------------------------------

SIP_Transport_Type SIP_Functions::get_transport_type(std::string transport)
{
    if (transport == "UDP")
        return SIP_TRANSPORT_UDP;
    else if (transport == "TCP")
        return SIP_TRANSPORT_TCP;
    else if (transport == "TLS")
        return SIP_TRANSPORT_TLS;
    else if (transport == "WS")
        return SIP_TRANSPORT_WS;
    else if (transport == "WSS")
        return SIP_TRANSPORT_WSS;
    else if (transport == "SCTP")
        return SIP_TRANSPORT_SCTP;

    return SIP_TRANSPORT_TYPE_INVALID;
}

//-------------------------------------------

std::string SIP_Functions::get_transport_type(SIP_Transport_Type transport)
{
    switch (transport)
    {
        case SIP_TRANSPORT_UDP:     return "UDP";
        case SIP_TRANSPORT_TCP:     return "TCP";
        case SIP_TRANSPORT_TLS:     return "TLS";
        case SIP_TRANSPORT_WS:      return "WS";
        case SIP_TRANSPORT_WSS:     return "WSS";
        case SIP_TRANSPORT_SCTP:    return "SCTP";
        default:                    return "";
    }
}

//-------------------------------------------

SIP_Method_Type SIP_Functions::get_method_type(const std::string method)
{
    if (method == "ACK")
        return SIP_REQUEST_ACK;
    else if (method == "BYE")
        return SIP_REQUEST_BYE;
    else if (method == "CANCEL")
        return SIP_REQUEST_CANCEL;
    else if (method == "INFO")
        return SIP_REQUEST_INFO;
    else if (method == "INVITE")
        return SIP_REQUEST_INVITE;
    else if (method == "MESSAGE")
        return SIP_REQUEST_MESSAGE;
    else if (method == "NOTIFY")
        return SIP_REQUEST_NOTIFY;
    else if (method == "OPTIONS")
        return SIP_REQUEST_OPTIONS;
    else if (method == "PRACK")
        return SIP_REQUEST_PRACK;
    else if (method == "PUBLISH")
        return SIP_REQUEST_PUBLISH;
    else if (method == "REFER")
        return SIP_REQUEST_REFER;
    else if (method == "REGISTER")
        return SIP_REQUEST_REGISTER;
    else if (method == "SUBSCRIBE")
        return SIP_REQUEST_SUBSCRIBE;
    else if (method == "UPDATE")
        return SIP_REQUEST_UPDATE;
    else if (method == SIP_VERSION)
        return SIP_RESPONSE;

    return SIP_METHOD_TYPE_INVALID;
}

//-------------------------------------------

std::string SIP_Functions::get_method_type(SIP_Method_Type method)
{
    switch (method)
    {
        case SIP_REQUEST_ACK:       return "ACK";
        case SIP_REQUEST_BYE:       return "BYE";
        case SIP_REQUEST_CANCEL:    return "CANCEL";
        case SIP_REQUEST_INFO:      return "INFO";
        case SIP_REQUEST_INVITE:    return "INVITE";
        case SIP_REQUEST_MESSAGE:   return "MESSAGE";
        case SIP_REQUEST_NOTIFY:    return "NOTIFY";
        case SIP_REQUEST_OPTIONS:   return "OPTIONS";
        case SIP_REQUEST_PRACK:     return "PRACK";
        case SIP_REQUEST_PUBLISH:   return "PUBLISH";
        case SIP_REQUEST_REFER:     return "REFER";
        case SIP_REQUEST_REGISTER:  return "REGISTER";
        case SIP_REQUEST_SUBSCRIBE: return "SUBSCRIBE";
        case SIP_REQUEST_UPDATE:    return "UPDATE";
        case SIP_RESPONSE:          return SIP_VERSION;
        default:                    return "";
    }
}

//-------------------------------------------

SIP_Header_Type SIP_Functions::get_header_type(std::string header)
{
    if (header == "Accept")
        return SIP_HEADER_ACCEPT;
    else if (header == "Accept-Encoding")
        return SIP_HEADER_ACCEPT_ENCODING;
    else if (header == "Accept-Language")
        return SIP_HEADER_ACCEPT_LANGUAGE;
    else if (header == "Alert-Info")
        return SIP_HEADER_ALERT_INFO;
    else if (header == "Allow")
        return SIP_HEADER_ALLOW;
    else if ((header == "Allow-Events") || (header == "u"))
        return SIP_HEADER_ALLOW_EVENTS;
    else if (header == "Authentication-Info")
        return SIP_HEADER_AUTHENTICATION_INFO;
    else if (header == "Authorization")
        return SIP_HEADER_AUTHORIZATION;
    else if ((header == "Call-ID") || (header == "i"))
        return SIP_HEADER_CALL_ID;
    else if (header == "Call-Info")
        return SIP_HEADER_CALL_INFO;
    else if ((header == "Contact") || (header == "m"))
        return SIP_HEADER_CONTACT;
    else if (header == "Content-Disposition")
        return SIP_HEADER_CONTENT_DISPOSITION;
    else if ((header == "Content-Encoding") || (header == "e"))
        return SIP_HEADER_CONTENT_ENCODING;
    else if (header == "Content-Language")
        return SIP_HEADER_CONTENT_LANGUAGE;
    else if ((header == "Content-Length") || (header == "l"))
        return SIP_HEADER_CONTENT_LENGTH;
    else if ((header == "Content-Type") || (header == "c"))
        return SIP_HEADER_CONTENT_TYPE;
    else if (header == "CSeq")
        return SIP_HEADER_CSEQ;
    else if (header == "Date")
        return SIP_HEADER_DATE;
    else if (header == "Error-Info")
        return SIP_HEADER_ERROR_INFO;
    else if ((header == "Event") || (header == "o"))
        return SIP_HEADER_EVENT;
    else if (header == "Expires")
        return SIP_HEADER_EXPIRES;
    else if ((header == "From") || (header == "f"))
        return SIP_HEADER_FROM;
    else if (header == "In-Reply-To")
        return SIP_HEADER_IN_REPLY_TO;
    else if (header == "Max-Forwards")
        return SIP_HEADER_MAX_FORWARDS;
    else if (header == "MIME-Version")
        return SIP_HEADER_MIME_VERSION;
    else if (header == "Min-Expires")
        return SIP_HEADER_MIN_EXPIRES;
    else if (header == "Organization")
        return SIP_HEADER_ORGANIZATION;
    else if (header == "Priority")
        return SIP_HEADER_PRIORITY;
    else if (header == "Proxy-Authenticate")
        return SIP_HEADER_PROXY_AUTHENTICATE;
    else if (header == "Proxy-Authorization")
        return SIP_HEADER_PROXY_AUTHORIZATION;
    else if (header == "Proxy-Require")
        return SIP_HEADER_PROXY_REQUIRE;
    else if (header == "Record-Route")
        return SIP_HEADER_RECORD_ROUTE;
    else if (header == "Reply-To")
        return SIP_HEADER_REPLY_TO;
    else if (header == "Require")
        return SIP_HEADER_REQUIRE;
    else if (header == "Retry-After")
        return SIP_HEADER_RETRY_AFTER;
    else if (header == "Route")
        return SIP_HEADER_ROUTE;
    else if (header == "Server")
        return SIP_HEADER_SERVER;
    else if ((header == "Subject") || (header == "s"))
        return SIP_HEADER_SUBJECT;
    else if (header == "Subscription-State")
        return SIP_HEADER_SUBSCRIPTION_STATE;
    else if ((header == "Supported") || (header == "k"))
        return SIP_HEADER_SUPPORTED;
    else if (header == "Timestamp")
        return SIP_HEADER_TIMESTAMP;
    else if ((header == "To") || (header == "t"))
        return SIP_HEADER_TO;
    else if (header == "Unsupported")
        return SIP_HEADER_UNSUPPORTED;
    else if (header == "User-Agent")
        return SIP_HEADER_USER_AGENT;
    else if ((header == "Via") || (header == "v"))
        return SIP_HEADER_VIA;
    else if (header == "Warning")
        return SIP_HEADER_WARNING;
    else if (header == "WWW-Authenticate")
        return SIP_HEADER_WWW_AUTHENTICATE;

    return SIP_HEADER_TYPE_INVALID;
}

//-------------------------------------------

std::string SIP_Functions::get_header_type(SIP_Header_Type header)
{
    switch (header)
    {
        case SIP_HEADER_ACCEPT:                 return "Accept";
        case SIP_HEADER_ACCEPT_ENCODING:        return "Accept-Encoding";
        case SIP_HEADER_ACCEPT_LANGUAGE:        return "Accept-Language";
        case SIP_HEADER_ALERT_INFO:             return "Alert-Info";
        case SIP_HEADER_ALLOW:                  return "Allow";
        case SIP_HEADER_ALLOW_EVENTS:           return "Allow-Events";
        case SIP_HEADER_AUTHORIZATION:          return "Authorization";
        case SIP_HEADER_AUTHENTICATION_INFO:    return "Authentication-Info";
        case SIP_HEADER_CALL_ID:                return "Call-ID";
        case SIP_HEADER_CALL_INFO:              return "Call-Info";
        case SIP_HEADER_CONTACT:                return "Contact";
        case SIP_HEADER_CONTENT_DISPOSITION:    return "Content-Disposition";
        case SIP_HEADER_CONTENT_ENCODING:       return "Content-Encoding";
        case SIP_HEADER_CONTENT_LANGUAGE:       return "Content-Language";
        case SIP_HEADER_CONTENT_LENGTH:         return "Content-Length";
        case SIP_HEADER_CONTENT_TYPE:           return "Content-Type";
        case SIP_HEADER_CSEQ:                   return "CSeq";
        case SIP_HEADER_DATE:                   return "Date";
        case SIP_HEADER_ERROR_INFO:             return "Error-Info";
        case SIP_HEADER_EVENT:                  return "Event";
        case SIP_HEADER_EXPIRES:                return "Expires";
        case SIP_HEADER_FROM:                   return "From";
        case SIP_HEADER_IN_REPLY_TO:            return "In-Reply-To";
        case SIP_HEADER_MAX_FORWARDS:           return "Max-Forwards";
        case SIP_HEADER_MIME_VERSION:           return "MIME-Version";
        case SIP_HEADER_MIN_EXPIRES:            return "Min-Expires";
        case SIP_HEADER_ORGANIZATION:           return "Organization";
        case SIP_HEADER_PRIORITY:               return "Priority";
        case SIP_HEADER_PROXY_REQUIRE:          return "Proxy-Require";
        case SIP_HEADER_PROXY_AUTHENTICATE:     return "Proxy-Authenticate";
        case SIP_HEADER_PROXY_AUTHORIZATION:    return "Proxy-Authorization";
        case SIP_HEADER_RECORD_ROUTE:           return "Record-Route";
        case SIP_HEADER_REPLY_TO:               return "Reply-To";
        case SIP_HEADER_REQUIRE:                return "Require";
        case SIP_HEADER_RETRY_AFTER:            return "Retry-After";
        case SIP_HEADER_ROUTE:                  return "Route";
        case SIP_HEADER_SERVER:                 return "Server";
        case SIP_HEADER_SUBJECT:                return "Subject";
        case SIP_HEADER_SUBSCRIPTION_STATE:     return "Subscription-State";
        case SIP_HEADER_SUPPORTED:              return "Supported";
        case SIP_HEADER_TIMESTAMP:              return "Timestamp";
        case SIP_HEADER_TO:                     return "To";
        case SIP_HEADER_UNSUPPORTED:            return "Unsupported";
        case SIP_HEADER_USER_AGENT:             return "User-Agent";
        case SIP_HEADER_VIA:                    return "Via";
        case SIP_HEADER_WARNING:                return "Warning";
        case SIP_HEADER_WWW_AUTHENTICATE:       return "WWW-Authenticate";
        default:                                return "";
    }
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Functions::start_with(const std::string &str1, const std::string &str2)
{
    return (str1.compare(0, str2.size(), str2) == 0);
}

//-------------------------------------------

bool SIP_Functions::contains(const std::string &str1, const std::string &str2)
{
    return (str1.find(str2) != std::string::npos);
}

//-------------------------------------------

void SIP_Functions::remove_lws(std::string &str)
{
    skip(str, " \t");

    std::string::size_type found = str.find("\r\n");
    while (found != std::string::npos)
    {
        std::string::size_type pos1 = str.find_last_not_of(" \t", found - 1);
        std::string::size_type pos2 = str.find_first_not_of(" \t", found + 2);

        if ((pos1 != std::string::npos) && (pos1 != found - 1) &&
            (pos2 != std::string::npos) && (pos2 != found + 2))
        {
            str.erase(pos1 + 1, pos2 - pos1 - 1);
            found = str.find("\r\n", pos1 + 1);

        }else if ((pos2 != std::string::npos) && (pos2 != found + 2))
        {
            str.erase(found, pos2 - found);
            found = str.find("\r\n", found + 1);

        }else
            found = str.find("\r\n", found + 1);
    }
}

//-------------------------------------------

bool SIP_Functions::match(std::string &str, const std::string &match, std::string &result, bool ignore_special)
{
    std::string::size_type pos = str.find_first_of(match);
    if (pos == std::string::npos)
    {
        result = str;
        return false;
    }

    if (ignore_special)
    {
        result = str.substr(0, pos);
        str.erase(0, pos + 1);
        return true;
    }

    unsigned short counter_double_quotation = 0;
    unsigned short counter_less_than = 0;
    unsigned short counter_greater_than = 0;
    unsigned short counter_left_parenthesis = 0;
    unsigned short counter_right_parenthesis = 0;

    std::string aux = str.substr(0, pos);
    std::string::size_type found;

    while (pos < str.size())
    {
        found = -1;
        do
        {
            found = aux.find('\"', found + 1);
            if (found != std::string::npos)
                counter_double_quotation++;
        }while (found != std::string::npos);

        found = -1;
        do
        {
            found = aux.find('<', found + 1);
            if (found != std::string::npos)
                counter_less_than++;
        }while (found != std::string::npos);

        found = -1;
        do
        {
            found = aux.find('>', found + 1);
            if (found != std::string::npos)
                counter_greater_than++;
        }while (found != std::string::npos);

        found = -1;
        do
        {
            found = aux.find('(', found + 1);
            if (found != std::string::npos)
                counter_left_parenthesis++;
        }while (found != std::string::npos);

        found = -1;
        do
        {
            found = aux.find(')', found + 1);
            if (found != std::string::npos)
                counter_right_parenthesis++;
        }while (found != std::string::npos);

        if ((counter_double_quotation % 2 == 0) && (counter_less_than == counter_greater_than) &&
            (counter_left_parenthesis == counter_right_parenthesis))
        {
            result = str.substr(0, pos);
            str.erase(0, pos + 1);
            return true;
        }

        std::string::size_type old_pos = pos;
        pos = str.find_first_of(match, pos + 1);
        if (pos == std::string::npos)
        {
            result = str;
            return false;
        }

        aux = str.substr(old_pos + 1, pos - old_pos - 1);
    }

    result = str;
    return false;
}

//-------------------------------------------

bool SIP_Functions::get_line(std::string &str, std::string &line)
{
    bool ret = match(str, "\n", line, true);
    if (ret)
    {
        std::string::size_type size = line.size();
        if ((size > 0) && (line.at(size - 1) == '\r'))
            line.erase(size - 1, size);
    }

    return ret;
}

//-------------------------------------------

void SIP_Functions::trim(std::string &str)
{
    std::string::size_type pos = str.find_last_not_of(" \t");
    if (pos != std::string::npos)
    {
        str.erase(pos + 1);
        pos = str.find_first_not_of(" \t");
        if (pos != std::string::npos)
            str.erase(0, pos);
    }else
        str.erase(str.begin(), str.end());
}

//-------------------------------------------

void SIP_Functions::skip(std::string &str, const std::string skip)
{
    std::string::size_type pos = str.find_first_not_of(skip);

    if (pos == std::string::npos)
        str.erase();

    else if (pos > 0)
        str.erase(0, pos);
}

//-------------------------------------------

void SIP_Functions::random(std::string &buffer)
{
#ifdef WINDOWS
    srand((unsigned int) time(NULL));
#endif

    long value = (long)(((double) rand() / (double) RAND_MAX) * 0x7FFFFFFF);
    buffer += std::to_string(value);
}

//-------------------------------------------

unsigned short SIP_Functions::str_to_us(const std::string &str)
{
    unsigned short value = 0;

    for (unsigned short i = 0; i < (unsigned short) str.size(); i++)
    {
        char digit = str.at(i);

        if ((digit < '0') || (digit > '9'))
            return INVALID_UNSIGNED_SHORT;

        unsigned short check_overflow = (INVALID_UNSIGNED_SHORT - (digit - '0')) / 10;
        if (value > check_overflow)
        {
            // Overflow
            return INVALID_UNSIGNED_SHORT;
        }

        value = value * 10 + (digit - '0');
    }

    return value;
}

//-------------------------------------------

unsigned long SIP_Functions::str_to_ul(const std::string &str)
{
    unsigned long value = 0;

    for (unsigned short i = 0; i < (unsigned short) str.size(); i++)
    {
        char digit = str.at(i);

        if ((digit < '0') || (digit > '9'))
            return INVALID_UNSIGNED_LONG;

        unsigned long check_overflow = (INVALID_UNSIGNED_LONG - (digit - '0')) / 10;
        if (value > check_overflow)
        {
            // Overflow
            return INVALID_UNSIGNED_LONG;
        }

        value = value * 10 + (digit - '0');
    }

    return value;
}

//-------------------------------------------

std::string SIP_Functions::add_leading_zeros(unsigned long value, unsigned short digits)
{
    std::string str = std::to_string(value);
    if (str.size() < digits)
        str.insert(0, digits - str.size(), '0');

    return str;
}

//-------------------------------------------
