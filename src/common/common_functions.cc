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

#include "common_functions.h"

//-------------------------------------------

void Common_Functions::delay(unsigned int time)
{
#ifdef WIN32
    Sleep(time);
#else
    usleep(time * 1000);
#endif
}

//-------------------------------------------

unsigned long Common_Functions::get_tick()
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
