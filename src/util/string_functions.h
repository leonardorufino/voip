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
#include <cstdlib>
#include <ctime>

class String_Functions
{
public:
    static bool start_with(const std::string &str1, const std::string &str2);
    static bool contains(const std::string &str1, const std::string &str2);
    static void remove_lws(std::string &str);
    static bool match(std::string &str, const std::string &match, std::string &result, bool ignore_special = false);
    static bool get_line(std::string &str, std::string &line);
    static void trim(std::string &str);
    static void skip(std::string &str, const std::string skip);
    static unsigned short str_to_us(const std::string str);
    static unsigned long str_to_ul(const std::string str);
    static unsigned long long str_to_ull(const std::string str);
    static std::string add_leading_zeros(unsigned long value, unsigned short digits);
    static std::string random(unsigned short len);
};
