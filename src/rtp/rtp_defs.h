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

enum RTP_Transport_Type
{
    RTP_TRANSPORT_UDP,
    RTP_TRANSPORT_INVALID
};

class RTP_Object_ID
{
public:
    static const unsigned int INVALID_SESSION = INVALID_UNSIGNED_INT;
    static const unsigned int INVALID_TRANSPORT = INVALID_UNSIGNED_INT;

public:
    RTP_Object_ID() : _session(INVALID_SESSION), _transport(INVALID_TRANSPORT) {}

    std::string to_string()
    {
        std::string str;

        if (_session != INVALID_SESSION)
        {
            str += "session=";
            str += std::to_string(_session);
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
    unsigned int _session;
    unsigned int _transport;
};
