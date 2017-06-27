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
