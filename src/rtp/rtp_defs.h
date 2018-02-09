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
    static const unsigned int INVALID_TRANSPORT = INVALID_UNSIGNED_INT;

public:
    RTP_Object_ID() : _transport(INVALID_TRANSPORT) {}

    std::string to_string()
    {
        std::string str;

        if (_transport != INVALID_TRANSPORT)
        {
            str += "transport=";
            str += std::to_string(_transport);
        }

        return str;
    }

public:
    unsigned int _transport;
};
