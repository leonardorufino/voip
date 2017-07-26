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
#include "util/util_defs.h"
#include <string>
#include <cstdlib>
#include <ctime>

class SIP_Functions
{
public:
    static SIP_Transport_Type get_transport_type(std::string transport);
    static std::string get_transport_type(SIP_Transport_Type transport);

    static SIP_Method_Type get_method_type(std::string method);
    static std::string get_method_type(SIP_Method_Type method);

    static SIP_Header_Type get_header_type(std::string header);
    static std::string get_header_type(SIP_Header_Type header);

    static bool start_with(const std::string &str1, const std::string &str2);
    static bool contains(const std::string &str1, const std::string &str2);
    static void remove_lws(std::string &str);
    static bool match(std::string &str, const std::string &match, std::string &result, bool ignore_special = false);
    static bool get_line(std::string &str, std::string &line);
    static void trim(std::string &str);
    static void skip(std::string &str, const std::string skip);
    static void random(std::string &buffer);
    static unsigned short str_to_us(const std::string &str);
    static unsigned long str_to_ul(const std::string &str);
    static std::string add_leading_zeros(unsigned long value, unsigned short digits);
};
