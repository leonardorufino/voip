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
    #include <windows.h>
#else
    #include <pthread.h>
    #include <unistd.h>
#endif

class Common_Functions
{
public:
    static void delay(unsigned int time);
    static unsigned long get_tick();
};
