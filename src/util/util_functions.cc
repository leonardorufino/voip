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

#include "util_functions.h"
#include "util_defs.h"
#include "string_functions.h"

//-------------------------------------------

void Util_Functions::delay(unsigned int time)
{
#ifdef WIN32
    Sleep(time);
#else
    usleep(time * 1000);
#endif
}

//-------------------------------------------

unsigned long Util_Functions::get_tick()
{
#ifdef WIN32
    return GetTickCount();
#else
    struct timespec time;

    if (clock_gettime(CLOCK_MONOTONIC, &time))
        return 0;

    return time.tv_sec * 1000 + time.tv_nsec / 1000000;
#endif
}

//-------------------------------------------

int Util_Functions::random()
{
    static bool INITIALIZED = false;

    if (!INITIALIZED)
    {
        srand((unsigned int) time(NULL));
        INITIALIZED = true;
    }

    return rand();
}

//-------------------------------------------

bool Util_Functions::HexToVector(std::string hex, std::vector<char> &vector)
{
    if (hex.empty())
        return false;

    if ((hex.size() % 2) != 0)
        return false;

    for (unsigned int i = 0; i < (unsigned int) hex.size(); i += 2)
    {
        std::string str = hex.substr(i, 2);
        unsigned short value;

        std::stringstream ss;
        ss << std::hex << str;
        ss >> value;

        vector.push_back((char) value);
    }

    return true;
}

//-------------------------------------------

bool Util_Functions::VectorToHex(const std::vector<char> &vector, std::string &hex)
{
    if (vector.empty())
        return false;

    for (unsigned int i = 0; i < vector.size(); i++)
    {
        unsigned short value = ((unsigned short) vector.at(i) & 0xff);
        std::string str;

        std::stringstream ss;
        ss << std::hex << value;
        ss >> str;

        if (str.size() < 2)
            str.insert(0, 2 - str.size(), '0');

        hex += str;
    }

    return true;
}

//-------------------------------------------
