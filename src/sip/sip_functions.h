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

#include "sip_defs.h"
#include <string>

class SIP_Functions
{
public:
    static SIP_Transport_Type get_transport_type(std::string transport);
    static std::string get_transport_type(SIP_Transport_Type transport);

    static SIP_Method_Type get_method_type(std::string method);
    static std::string get_method_type(SIP_Method_Type method);

    static SIP_Header_Type get_header_type(std::string header);
    static std::string get_header_type(SIP_Header_Type header);
};
