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

#include "sip/sip_address.h"
#include "util/util_defs.h"
#include <list>
#include <iomanip>

class SIP_Address_Test
{
public:
    SIP_Address_Test() {}
    virtual ~SIP_Address_Test() {}

    static bool init();
    template<class T> static bool run();
};

//-------------------------------------------

class SIP_Address_Decode_Encode_Test
{
public:
    SIP_Address_Decode_Encode_Test();
    ~SIP_Address_Decode_Encode_Test() {}

    bool run();

protected:
    class SIP_Address_Input_Output
    {
    public:
        std::string _input;
        std::string _output;
    };

    std::list<SIP_Address_Input_Output> _address_input_output;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Address_Query_Test
{
public:
    SIP_Address_Query_Test();
    ~SIP_Address_Query_Test() {}

    bool run();

protected:
    class SIP_Address_Query
    {
    public:
        QueryCommand _cmd;
        std::string _query;
        std::string _expected_result;
        bool _success;

    public:
        SIP_Address_Query(QueryCommand cmd, std::string query, std::string expected_result, bool success)
            : _cmd(cmd), _query(query), _expected_result(expected_result), _success(success) {}
    };

    std::list<SIP_Address_Query> _address_query;
};

//-------------------------------------------
