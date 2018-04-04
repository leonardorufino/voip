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

#include "sdp/sdp_description.h"
#include <list>
#include <iomanip>

class SDP_Description_Test
{
public:
    SDP_Description_Test() {}
    virtual ~SDP_Description_Test() {}

    static bool init();
    template<class T> static bool run();
};

//-------------------------------------------

class SDP_Description_Decode_Encode_Test
{
public:
    static const unsigned short MAX_DESCRIPTION_SIZE = 1000;

protected:
    class SDP_Description_Input_Output
    {
    public:
        std::string _input;
        std::string _output;
    };

public:
    SDP_Description_Decode_Encode_Test() {}
    virtual ~SDP_Description_Decode_Encode_Test() {}

    bool run();

protected:
    virtual bool execute(SDP_Description_Input_Output &description_input_output) = 0;

protected:
    std::list<SDP_Description_Input_Output> _description_input_output;
};

//-------------------------------------------

class SDP_Description_Query_Test
{
public:
    SDP_Description_Query_Test() {}
    virtual ~SDP_Description_Query_Test() {}

    bool run();

protected:
    class SDP_Description_Query
    {
    public:
        QueryCommand _cmd;
        std::string _query;
        std::string _expected_result;
        bool _success;

    public:
        SDP_Description_Query(QueryCommand cmd, std::string query, std::string expected_result, bool success)
            : _cmd(cmd), _query(query), _expected_result(expected_result), _success(success) {}
    };

    std::list<SDP_Description_Query> _description_query;
};

//-------------------------------------------
//-------------------------------------------

class SDP_Description_Session_Decode_Encode_Test : public SDP_Description_Decode_Encode_Test
{
public:
    SDP_Description_Session_Decode_Encode_Test();

protected:
    bool execute(SDP_Description_Input_Output &description_input_output);
};

//-------------------------------------------

class SDP_Description_Session_Query_Test : public SDP_Description_Query_Test
{
public:
    SDP_Description_Session_Query_Test();
};

//-------------------------------------------

class SDP_Description_Media_Decode_Encode_Test : public SDP_Description_Decode_Encode_Test
{
public:
    SDP_Description_Media_Decode_Encode_Test();

protected:
    bool execute(SDP_Description_Input_Output &description_input_output);
};

//-------------------------------------------

class SDP_Description_Media_Query_Test : public SDP_Description_Query_Test
{
public:
    SDP_Description_Media_Query_Test();
};

//-------------------------------------------

class SDP_Description_Complete_Decode_Encode_Test : public SDP_Description_Decode_Encode_Test
{
public:
    SDP_Description_Complete_Decode_Encode_Test();

protected:
    bool execute(SDP_Description_Input_Output &description_input_output);
};

//-------------------------------------------
