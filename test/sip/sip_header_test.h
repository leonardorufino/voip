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

    bool copy_headers(std::list<SIP_Header *> &headers, std::list<SIP_Header *> &copy);
    void clear(std::list<SIP_Header *> &headers);

protected:
    class SIP_Header_Input_Output
    {
    public:
        SIP_Header_Type _header_type;
        std::string _input;
        std::string _output;
        unsigned short _header_nb;
        bool _decode_success;
        bool _encode_success;
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

class SIP_Header_Alert_Info_Test : public SIP_Header_Test
{
public:
    SIP_Header_Alert_Info_Test();
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

class SIP_Header_Authentication_Info_Test : public SIP_Header_Test
{
public:
    SIP_Header_Authentication_Info_Test();
};

//-------------------------------------------

class SIP_Header_Authorization_Test : public SIP_Header_Test
{
public:
    SIP_Header_Authorization_Test();
};

//-------------------------------------------

class SIP_Header_Call_ID_Test : public SIP_Header_Test
{
public:
    SIP_Header_Call_ID_Test();
};

//-------------------------------------------

class SIP_Header_Call_Info_Test : public SIP_Header_Test
{
public:
    SIP_Header_Call_Info_Test();
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

class SIP_Header_Error_Info_Test : public SIP_Header_Test
{
public:
    SIP_Header_Error_Info_Test();
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

class SIP_Header_Proxy_Authenticate_Test : public SIP_Header_Test
{
public:
    SIP_Header_Proxy_Authenticate_Test();
};

//-------------------------------------------

class SIP_Header_Proxy_Authorization_Test : public SIP_Header_Test
{
public:
    SIP_Header_Proxy_Authorization_Test();
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

class SIP_Header_Reply_To_Test : public SIP_Header_Test
{
public:
    SIP_Header_Reply_To_Test();
};

//-------------------------------------------

class SIP_Header_Require_Test : public SIP_Header_Test
{
public:
    SIP_Header_Require_Test();
};

//-------------------------------------------

class SIP_Header_Retry_After_Test : public SIP_Header_Test
{
public:
    SIP_Header_Retry_After_Test();
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

class SIP_Header_Timestamp_Test : public SIP_Header_Test
{
public:
    SIP_Header_Timestamp_Test();
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

class SIP_Header_Warning_Test : public SIP_Header_Test
{
public:
    SIP_Header_Warning_Test();
};

//-------------------------------------------

class SIP_Header_WWW_Authenticate_Test : public SIP_Header_Test
{
public:
    SIP_Header_WWW_Authenticate_Test();
};

//-------------------------------------------
