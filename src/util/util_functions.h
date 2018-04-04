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

#ifdef WIN32
    #include <winsock2.h>
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>

class Util_Functions
{
public:
    static void delay(unsigned int time);
    static unsigned long get_tick();
    static int random();
    static bool HexToVector(std::string hex, std::vector<char> &vector);
    static bool VectorToHex(const std::vector<char> &vector, std::string &hex);
};
