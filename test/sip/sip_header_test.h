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
#include <list>
#include <utility>
#include <iomanip>

class SIP_Header_Test
{
public:
    SIP_Header_Test() {}
    virtual ~SIP_Header_Test() {}

    static bool init();

    bool run();
    void clear(std::map<SIP_Header_Type, std::list<SIP_Header *>> &headers);

protected:
    class SIP_Header_Input_Output
    {
    public:
        SIP_Header_Input_Output(SIP_Header_Type header_type, std::string input, std::string output, short header_nb)
            : _header_type(header_type), _input(input), _output(output), _header_nb(header_nb) {}

        SIP_Header_Type _header_type;
        std::string _input;
        std::string _output;
        unsigned short _header_nb;
    };

    std::list<SIP_Header_Input_Output> _header_input_output;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Header_Accept_Test : public SIP_Header_Test
{
public:
    SIP_Header_Accept_Test();
};

//-------------------------------------------

class SIP_Header_Accept_Encoding_Test : public SIP_Header_Test
{
public:
    SIP_Header_Accept_Encoding_Test();
};

//-------------------------------------------

class SIP_Header_Accept_Language_Test : public SIP_Header_Test
{
public:
    SIP_Header_Accept_Language_Test();
};

//-------------------------------------------

class SIP_Header_Allow_Test : public SIP_Header_Test
{
public:
    SIP_Header_Allow_Test();
};

//-------------------------------------------

class SIP_Header_Allow_Events_Test : public SIP_Header_Test
{
public:
    SIP_Header_Allow_Events_Test();
};

//-------------------------------------------

class SIP_Header_Call_ID_Test : public SIP_Header_Test
{
public:
    SIP_Header_Call_ID_Test();
};

//-------------------------------------------

class SIP_Header_Contact_Test : public SIP_Header_Test
{
public:
    SIP_Header_Contact_Test();
};

//-------------------------------------------

class SIP_Header_Content_Disposition_Test : public SIP_Header_Test
{
public:
    SIP_Header_Content_Disposition_Test();
};

//-------------------------------------------

class SIP_Header_Content_Encoding_Test : public SIP_Header_Test
{
public:
    SIP_Header_Content_Encoding_Test();
};

//-------------------------------------------

class SIP_Header_Content_Language_Test : public SIP_Header_Test
{
public:
    SIP_Header_Content_Language_Test();
};

//-------------------------------------------

class SIP_Header_Content_Length_Test : public SIP_Header_Test
{
public:
    SIP_Header_Content_Length_Test();
};

//-------------------------------------------

class SIP_Header_Content_Type_Test : public SIP_Header_Test
{
public:
    SIP_Header_Content_Type_Test();
};

//-------------------------------------------

class SIP_Header_CSeq_Test : public SIP_Header_Test
{
public:
    SIP_Header_CSeq_Test();
};

//-------------------------------------------

class SIP_Header_Date_Test : public SIP_Header_Test
{
public:
    SIP_Header_Date_Test();
};

//-------------------------------------------

class SIP_Header_Event_Test : public SIP_Header_Test
{
public:
    SIP_Header_Event_Test();
};

//-------------------------------------------

class SIP_Header_Expires_Test : public SIP_Header_Test
{
public:
    SIP_Header_Expires_Test();
};

//-------------------------------------------

class SIP_Header_From_Test : public SIP_Header_Test
{
public:
    SIP_Header_From_Test();
};

//-------------------------------------------

class SIP_Header_In_Reply_To_Test : public SIP_Header_Test
{
public:
    SIP_Header_In_Reply_To_Test();
};

//-------------------------------------------

class SIP_Header_Max_Forwards_Test : public SIP_Header_Test
{
public:
    SIP_Header_Max_Forwards_Test();
};

//-------------------------------------------

class SIP_Header_Mime_Version_Test : public SIP_Header_Test
{
public:
    SIP_Header_Mime_Version_Test();
};

//-------------------------------------------

class SIP_Header_Min_Expires_Test : public SIP_Header_Test
{
public:
    SIP_Header_Min_Expires_Test();
};

//-------------------------------------------

class SIP_Header_Organization_Test : public SIP_Header_Test
{
public:
    SIP_Header_Organization_Test();
};

//-------------------------------------------

class SIP_Header_Priority_Test : public SIP_Header_Test
{
public:
    SIP_Header_Priority_Test();
};

//-------------------------------------------

class SIP_Header_Proxy_Require_Test : public SIP_Header_Test
{
public:
    SIP_Header_Proxy_Require_Test();
};

//-------------------------------------------

class SIP_Header_Record_Route_Test : public SIP_Header_Test
{
public:
    SIP_Header_Record_Route_Test();
};

//-------------------------------------------

class SIP_Header_Require_Test : public SIP_Header_Test
{
public:
    SIP_Header_Require_Test();
};

//-------------------------------------------

class SIP_Header_Route_Test : public SIP_Header_Test
{
public:
    SIP_Header_Route_Test();
};

//-------------------------------------------

class SIP_Header_Server_Test : public SIP_Header_Test
{
public:
    SIP_Header_Server_Test();
};

//-------------------------------------------

class SIP_Header_Subject_Test : public SIP_Header_Test
{
public:
    SIP_Header_Subject_Test();
};

//-------------------------------------------

class SIP_Header_Subscription_State_Test : public SIP_Header_Test
{
public:
    SIP_Header_Subscription_State_Test();
};

//-------------------------------------------

class SIP_Header_Supported_Test : public SIP_Header_Test
{
public:
    SIP_Header_Supported_Test();
};

//-------------------------------------------

class SIP_Header_To_Test : public SIP_Header_Test
{
public:
    SIP_Header_To_Test();
};

//-------------------------------------------

class SIP_Header_Unsupported_Test : public SIP_Header_Test
{
public:
    SIP_Header_Unsupported_Test();
};

//-------------------------------------------

class SIP_Header_User_Agent_Test : public SIP_Header_Test
{
public:
    SIP_Header_User_Agent_Test();
};

//-------------------------------------------

class SIP_Header_Via_Test : public SIP_Header_Test
{
public:
    SIP_Header_Via_Test();
};

//-------------------------------------------
