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

#pragma once

#include "util/util_defs.h"
#include <string>

#define SIP_VERSION     "SIP/2.0"

enum SIP_Method_Type
{
    SIP_REQUEST_ACK,
    SIP_REQUEST_BYE,
    SIP_REQUEST_CANCEL,
    SIP_REQUEST_INFO,
    SIP_REQUEST_INVITE,
    SIP_REQUEST_MESSAGE,
    SIP_REQUEST_NOTIFY,
    SIP_REQUEST_OPTIONS,
    SIP_REQUEST_PRACK,
    SIP_REQUEST_PUBLISH,
    SIP_REQUEST_REFER,
    SIP_REQUEST_REGISTER,
    SIP_REQUEST_SUBSCRIBE,
    SIP_REQUEST_UPDATE,
    SIP_RESPONSE,
    SIP_METHOD_INVALID
};

enum SIP_Header_Type
{
    SIP_HEADER_ACCEPT,
    SIP_HEADER_ACCEPT_ENCODING,
    SIP_HEADER_ACCEPT_LANGUAGE,
    SIP_HEADER_ALERT_INFO,
    SIP_HEADER_ALLOW,
    SIP_HEADER_ALLOW_EVENTS,
    SIP_HEADER_AUTHENTICATION_INFO,
    SIP_HEADER_AUTHORIZATION,
    SIP_HEADER_CALL_ID,
    SIP_HEADER_CALL_INFO,
    SIP_HEADER_CONTACT,
    SIP_HEADER_CONTENT_DISPOSITION,
    SIP_HEADER_CONTENT_ENCODING,
    SIP_HEADER_CONTENT_LANGUAGE,
    SIP_HEADER_CONTENT_LENGTH,
    SIP_HEADER_CONTENT_TYPE,
    SIP_HEADER_CSEQ,
    SIP_HEADER_DATE,
    SIP_HEADER_ERROR_INFO,
    SIP_HEADER_EVENT,
    SIP_HEADER_EXPIRES,
    SIP_HEADER_FROM,
    SIP_HEADER_IN_REPLY_TO,
    SIP_HEADER_MAX_FORWARDS,
    SIP_HEADER_MIME_VERSION,
    SIP_HEADER_MIN_EXPIRES,
    SIP_HEADER_ORGANIZATION,
    SIP_HEADER_PRIORITY,
    SIP_HEADER_PROXY_AUTHENTICATE,
    SIP_HEADER_PROXY_AUTHORIZATION,
    SIP_HEADER_PROXY_REQUIRE,
    SIP_HEADER_RACK,
    SIP_HEADER_RECORD_ROUTE,
    SIP_HEADER_REFER_TO,
    SIP_HEADER_REFERRED_BY,
    SIP_HEADER_REPLY_TO,
    SIP_HEADER_REQUIRE,
    SIP_HEADER_RETRY_AFTER,
    SIP_HEADER_ROUTE,
    SIP_HEADER_RSEQ,
    SIP_HEADER_SERVER,
    SIP_HEADER_SUBJECT,
    SIP_HEADER_SUBSCRIPTION_STATE,
    SIP_HEADER_SUPPORTED,
    SIP_HEADER_TIMESTAMP,
    SIP_HEADER_TO,
    SIP_HEADER_UNKNOWN,
    SIP_HEADER_UNSUPPORTED,
    SIP_HEADER_USER_AGENT,
    SIP_HEADER_VIA,
    SIP_HEADER_WARNING,
    SIP_HEADER_WWW_AUTHENTICATE,
    SIP_HEADER_INVALID
};

enum SIP_Body_Type
{
    SIP_BODY_SDP,
    SIP_BODY_UNKNOWN,
    SIP_BODY_INVALID
};

enum SIP_Transport_Type
{
    SIP_TRANSPORT_UDP,
    SIP_TRANSPORT_TCP,
    SIP_TRANSPORT_TLS,
    SIP_TRANSPORT_WS,
    SIP_TRANSPORT_WSS,
    SIP_TRANSPORT_SCTP,
    SIP_TRANSPORT_INVALID
};

class SIP_Object_ID
{
public:
    static const unsigned int INVALID_USER_AGENT = INVALID_UNSIGNED_INT;
    static const unsigned int INVALID_CALL = INVALID_UNSIGNED_INT;
    static const unsigned int INVALID_DIALOG = INVALID_UNSIGNED_INT;
    static const unsigned int INVALID_TRANSACTION = INVALID_UNSIGNED_INT;
    static const unsigned int INVALID_TRANSPORT = INVALID_UNSIGNED_INT;

public:
    SIP_Object_ID() : _user_agent(INVALID_USER_AGENT), _call(INVALID_CALL), _dialog(INVALID_DIALOG),
        _transaction(INVALID_TRANSACTION), _transport(INVALID_TRANSPORT) {}

    std::string to_string()
    {
        std::string str;

        if (_user_agent != INVALID_USER_AGENT)
        {
            str += "user_agent=";
            str += std::to_string(_user_agent);
        }

        if (_call != INVALID_CALL)
        {
            if (!str.empty())
                str += ", ";
            str += "call=";
            str += std::to_string(_call);
        }

        if (_dialog != INVALID_DIALOG)
        {
            if (!str.empty())
                str += ", ";
            str += "dialog=";
            str += std::to_string(_dialog);
        }

        if (_transaction != INVALID_TRANSACTION)
        {
            if (!str.empty())
                str += ", ";
            str += "transaction=";
            str += std::to_string(_transaction);
        }

        if (_transport != INVALID_TRANSPORT)
        {
            if (!str.empty())
                str += ", ";
            str += "transport=";
            str += std::to_string(_transport);
        }

        return str;
    }

public:
    unsigned int _user_agent;
    unsigned int _call;
    unsigned int _dialog;
    unsigned int _transaction;
    unsigned int _transport;
};
