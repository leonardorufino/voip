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
    #include <time.h>
    #include <unistd.h>
#endif

class Util_Functions
{
public:
    static void delay(unsigned int time);
    static unsigned long get_tick();
};