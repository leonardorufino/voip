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
    template<class T> static bool run();
};

//-------------------------------------------

class SIP_Message_Decode_Encode_Test
{
public:
    static const unsigned short MAX_MESSAGE_SIZE = 1000;

public:
    SIP_Message_Decode_Encode_Test() {}
    virtual ~SIP_Message_Decode_Encode_Test() {}

    bool run();

protected:
    SIP_Message *copy_message(SIP_Message &message, bool response_answer);

protected:
    class SIP_Message_Input_Output
    {
    public:
        SIP_Method_Type _method_type;
        std::string _input;
        std::string _output;
        bool _response_answer;
    };

    std::list<SIP_Message_Input_Output> _message_input_output;
};

//-------------------------------------------

class SIP_Message_Query_Test
{
public:
    SIP_Message_Query_Test(SIP_Method_Type type) : _method_type(type) {}
    virtual ~SIP_Message_Query_Test() {}

    bool run();

protected:
    SIP_Message *create_message();

protected:
    class SIP_Message_Query
    {
    public:
        QueryCommand _cmd;
        std::string _query;
        std::string _expected_result;
        bool _success;

    public:
        SIP_Message_Query(QueryCommand cmd, std::string query, std::string expected_result, bool success)
            : _cmd(cmd), _query(query), _expected_result(expected_result), _success(success) {}
    };

    SIP_Method_Type _method_type;
    std::list<SIP_Message_Query> _message_query;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Request_Decode_Encode_Test : public SIP_Message_Decode_Encode_Test
{
public:
    SIP_Request_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Request_Query_Test : public SIP_Message_Query_Test
{
public:
    SIP_Request_Query_Test();
};

//-------------------------------------------

class SIP_Response_Decode_Encode_Test : public SIP_Message_Decode_Encode_Test
{
public:
    SIP_Response_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Response_Query_Test : public SIP_Message_Query_Test
{
public:
    SIP_Response_Query_Test();
};

//-------------------------------------------

class SIP_Response_Answer_Decode_Encode_Test : public SIP_Message_Decode_Encode_Test
{
public:
    SIP_Response_Answer_Decode_Encode_Test();
};

//-------------------------------------------
