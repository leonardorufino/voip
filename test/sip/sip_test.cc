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

#include "sip_header_test.h"
#include "sip_message_test.h"
#include <iostream>

//-------------------------------------------

int main()
{
    std::cout << "SIP test initialized.\n";

    SIP_Header_Test::init();
    SIP_Message_Test::init();

    std::cout << "SIP test completed successfully.\n";
    return 0;
}

//-------------------------------------------
