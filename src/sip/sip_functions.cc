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

    return SIP_TRANSPORT_INVALID;
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

    return SIP_METHOD_INVALID;
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
    else if (header == "RAck")
        return SIP_HEADER_RACK;
    else if (header == "Record-Route")
        return SIP_HEADER_RECORD_ROUTE;
    else if (header == "Refer-To")
        return SIP_HEADER_REFER_TO;
    else if (header == "Referred-By")
        return SIP_HEADER_REFERRED_BY;
    else if (header == "Reply-To")
        return SIP_HEADER_REPLY_TO;
    else if (header == "Require")
        return SIP_HEADER_REQUIRE;
    else if (header == "Retry-After")
        return SIP_HEADER_RETRY_AFTER;
    else if (header == "Route")
        return SIP_HEADER_ROUTE;
    else if (header == "RSeq")
        return SIP_HEADER_RSEQ;
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

    return SIP_HEADER_INVALID;
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
        case SIP_HEADER_PROXY_AUTHENTICATE:     return "Proxy-Authenticate";
        case SIP_HEADER_PROXY_AUTHORIZATION:    return "Proxy-Authorization";
        case SIP_HEADER_PROXY_REQUIRE:          return "Proxy-Require";
        case SIP_HEADER_RACK:                   return "RAck";
        case SIP_HEADER_RECORD_ROUTE:           return "Record-Route";
        case SIP_HEADER_REFER_TO:               return "Refer-To";
        case SIP_HEADER_REFERRED_BY:            return "Referred-By";
        case SIP_HEADER_REPLY_TO:               return "Reply-To";
        case SIP_HEADER_REQUIRE:                return "Require";
        case SIP_HEADER_RETRY_AFTER:            return "Retry-After";
        case SIP_HEADER_ROUTE:                  return "Route";
        case SIP_HEADER_RSEQ:                   return "RSeq";
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
