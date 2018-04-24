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

#include "sip_address_test.h"
#include "sip_header_test.h"
#include "sip_message_test.h"
#include "sip_body_test.h"
#include "sip_transaction_test.h"
#include "sip_transport_test.h"
#include "sip_call_test.h"
#include "sip_user_agent_test.h"
#include "sip_manager_test.h"
#include <iostream>

//-------------------------------------------

int main()
{
    std::cout << "SIP test initialized\n";

    if (!SIP_Address_Test::init())
    {
        std::cout << "SIP address test FAILED!\n";
        return 1;
    }

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

    if (!SIP_Body_Test::init())
    {
        std::cout << "SIP body test FAILED!\n";
        return 1;
    }

    if (!SIP_Transaction_Test::init())
    {
        std::cout << "SIP transaction test FAILED!\n";
        return 1;
    }

    if (!SIP_Transport_Test::init())
    {
        std::cout << "SIP transport test FAILED!\n";
        return 1;
    }

    if (!SIP_Call_Test::init())
    {
        std::cout << "SIP call test FAILED!\n";
        return 1;
    }

    if (!SIP_User_Agent_Test::init())
    {
        std::cout << "SIP user agent test FAILED!\n";
        return 1;
    }

    if (!SIP_Manager_Test::init())
    {
        std::cout << "SIP manager test FAILED!\n";
        return 1;
    }

    std::cout << "SIP test completed successfully\n";
    return 0;
}

//-------------------------------------------
