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

#include "sip/sip_body.h"
#include "util/util_defs.h"
#include <list>
#include <iomanip>

class SIP_Body_Test
{
public:
    SIP_Body_Test() {}
    virtual ~SIP_Body_Test() {}

    static bool init();
    template<class T> static bool run();
};

//-------------------------------------------

class SIP_Body_Decode_Encode_Test
{
public:
    static const unsigned short MAX_BODY_SIZE = 1000;

public:
    SIP_Body_Decode_Encode_Test();
    ~SIP_Body_Decode_Encode_Test() {}

    bool run();

protected:
    class SIP_Body_Input_Output
    {
    public:
        SIP_Body_Type _body_type;
        char _body[MAX_BODY_SIZE];
        unsigned short _size;
    };

    std::list<SIP_Body_Input_Output> _body_input_output;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Body_Query_Test
{
public:
    SIP_Body_Query_Test();
    ~SIP_Body_Query_Test() {}

    bool run();

protected:
    class SIP_Body_Query
    {
    public:
        QueryCommand _cmd;
        std::string _query;
        std::string _expected_result;
        bool _success;

    public:
        SIP_Body_Query(QueryCommand cmd, std::string query, std::string expected_result, bool success)
            : _cmd(cmd), _query(query), _expected_result(expected_result), _success(success) {}
    };

    SIP_Body_Type _body_type;
    std::list<SIP_Body_Query> _body_query;
};

//-------------------------------------------
