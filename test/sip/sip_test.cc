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
#include "sip_transaction_test.h"
#include <iostream>

//-------------------------------------------

int main()
{
    std::cout << "SIP test initialized\n";

    if (!SIP_Header_Test::init())
    {
        std::cout << "SIP header test FAILED!\n";
        return 1;
    }

    if (!SIP_Message_Test::init())
    {
        std::cout << "SIP message test FAILED!\n";
        return 1;
    }

    if (!SIP_Transaction_Test::init())
    {
        std::cout << "SIP transaction test FAILED!\n";
        return 1;
    }

    std::cout << "SIP test completed successfully\n";
    return 0;
}

//-------------------------------------------
