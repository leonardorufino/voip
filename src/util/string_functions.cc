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

#include "string_functions.h"

//-------------------------------------------

bool String_Functions::start_with(const std::string &str1, const std::string &str2)
{
    return (str1.compare(0, str2.size(), str2) == 0);
}

//-------------------------------------------

bool String_Functions::contains(const std::string &str1, const std::string &str2)
{
    return (str1.find(str2) != std::string::npos);
}

//-------------------------------------------

void String_Functions::remove_lws(std::string &str)
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

bool String_Functions::match(std::string &str, const std::string &match, std::string &result, bool ignore_special)
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
    unsigned short counter_left_square_bracket = 0;
    unsigned short counter_right_square_bracket = 0;

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

        found = -1;
        do
        {
            found = aux.find('[', found + 1);
            if (found != std::string::npos)
                counter_left_square_bracket++;
        }while (found != std::string::npos);

        found = -1;
        do
        {
            found = aux.find(']', found + 1);
            if (found != std::string::npos)
                counter_right_square_bracket++;
        }while (found != std::string::npos);

        if ((counter_double_quotation % 2 == 0) && (counter_less_than == counter_greater_than) &&
            (counter_left_parenthesis == counter_right_parenthesis) && (counter_left_square_bracket == counter_right_square_bracket))
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

bool String_Functions::get_line(std::string &str, std::string &line)
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

void String_Functions::trim(std::string &str)
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

void String_Functions::skip(std::string &str, const std::string skip)
{
    std::string::size_type pos = str.find_first_not_of(skip);

    if (pos == std::string::npos)
        str.erase();

    else if (pos > 0)
        str.erase(0, pos);
}

//-------------------------------------------

unsigned short String_Functions::str_to_us(const std::string str)
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

unsigned long String_Functions::str_to_ul(const std::string str)
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

unsigned long long String_Functions::str_to_ull(const std::string str)
{
    unsigned long long value = 0;

    for (unsigned short i = 0; i < (unsigned short) str.size(); i++)
    {
        char digit = str.at(i);

        if ((digit < '0') || (digit > '9'))
            return INVALID_UNSIGNED_LONG_LONG;

        unsigned long long check_overflow = (INVALID_UNSIGNED_LONG_LONG - (digit - '0')) / 10;
        if (value > check_overflow)
        {
            // Overflow
            return INVALID_UNSIGNED_LONG_LONG;
        }

        value = value * 10 + (digit - '0');
    }

    return value;
}

//-------------------------------------------

std::string String_Functions::add_leading_zeros(unsigned long value, unsigned short digits)
{
    std::string str = std::to_string(value);
    if (str.size() < digits)
        str.insert(0, digits - str.size(), '0');

    return str;
}

//-------------------------------------------

std::string String_Functions::random(unsigned short len)
{
    static const char ALPHANUM[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    static bool INITIALIZED = false;

    if (!INITIALIZED)
    {
        srand((unsigned int) time(NULL));
        INITIALIZED = true;
    }

    std::string str;

    for (unsigned short i = 0; i < len; i++)
        str += ALPHANUM[rand() % (sizeof(ALPHANUM) - 1)];

    return str;
}

//-------------------------------------------
