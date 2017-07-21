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

#include "timer_manager_test.h"
#include "socket_test.h"
#include <iostream>

//-------------------------------------------

int main()
{
    std::cout << "Common test initialized\n";

    if (!Timer_Manager_Test::init())
    {
        std::cout << "Timer manager test FAILED!\n";
        return 1;
    }

    if (!Socket_Test::init())
    {
        std::cout << "Socket test FAILED!\n";
        return 1;
    }

    std::cout << "Common test completed successfully\n";
    return 0;
}

//-------------------------------------------
