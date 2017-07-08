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

#include "sip/sip_header.h"
#include "sip/sip_message.h"
#include <list>
#include <iomanip>

class SIP_Message_Test
{
public:
    SIP_Message_Test() {}
    virtual ~SIP_Message_Test() {}

    static bool init();

    bool run();

    SIP_Message *copy_message(SIP_Message &message);

protected:
    class SIP_Message_Input_Output
    {
    public:
        std::string _input;
        std::string _output;
    };

    std::list<SIP_Message_Input_Output> _message_input_output;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Request_Test : public SIP_Message_Test
{
public:
    SIP_Request_Test();
};

//-------------------------------------------

class SIP_Response_Test : public SIP_Message_Test
{
public:
    SIP_Response_Test();
};

//-------------------------------------------
