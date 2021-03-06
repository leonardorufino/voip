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
#include "util/util_defs.h"
#include <list>
#include <iomanip>

class SIP_Header_Test
{
public:
    SIP_Header_Test() {}
    virtual ~SIP_Header_Test() {}

    static bool init();
    template<class T> static bool run();
};

//-------------------------------------------

class SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Decode_Encode_Test() {}
    virtual ~SIP_Header_Decode_Encode_Test() {}

    bool run();

protected:
    bool copy_headers(sip_header_list &headers, sip_header_list &copy);
    void clear(sip_header_list &headers);

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

class SIP_Header_Query_Test
{
public:
    SIP_Header_Query_Test(SIP_Header_Type type) : _header_type(type) {}
    virtual ~SIP_Header_Query_Test() {}

    bool run();

protected:
    class SIP_Header_Query
    {
    public:
        QueryCommand _cmd;
        std::string _query;
        std::string _expected_result;
        bool _success;

    public:
        SIP_Header_Query(QueryCommand cmd, std::string query, std::string expected_result, bool success)
            : _cmd(cmd), _query(query), _expected_result(expected_result), _success(success) {}
    };

    SIP_Header_Type _header_type;
    std::list<SIP_Header_Query> _header_query;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Header_Accept_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Accept_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Accept_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Accept_Query_Test();
};

//-------------------------------------------

class SIP_Header_Accept_Encoding_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Accept_Encoding_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Accept_Encoding_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Accept_Encoding_Query_Test();
};

//-------------------------------------------

class SIP_Header_Accept_Language_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Accept_Language_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Accept_Language_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Accept_Language_Query_Test();
};

//-------------------------------------------

class SIP_Header_Alert_Info_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Alert_Info_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Alert_Info_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Alert_Info_Query_Test();
};

//-------------------------------------------

class SIP_Header_Allow_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Allow_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Allow_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Allow_Query_Test();
};

//-------------------------------------------

class SIP_Header_Allow_Events_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Allow_Events_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Allow_Events_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Allow_Events_Query_Test();
};

//-------------------------------------------

class SIP_Header_Authentication_Info_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Authentication_Info_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Authentication_Info_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Authentication_Info_Query_Test();
};

//-------------------------------------------

class SIP_Header_Authorization_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Authorization_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Authorization_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Authorization_Query_Test();
};

//-------------------------------------------

class SIP_Header_Call_ID_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Call_ID_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Call_ID_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Call_ID_Query_Test();
};

//-------------------------------------------

class SIP_Header_Call_Info_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Call_Info_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Call_Info_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Call_Info_Query_Test();
};

//-------------------------------------------

class SIP_Header_Contact_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Contact_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Contact_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Contact_Query_Test();
};

//-------------------------------------------

class SIP_Header_Content_Disposition_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Content_Disposition_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Content_Disposition_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Content_Disposition_Query_Test();
};

//-------------------------------------------

class SIP_Header_Content_Encoding_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Content_Encoding_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Content_Encoding_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Content_Encoding_Query_Test();
};

//-------------------------------------------

class SIP_Header_Content_Language_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Content_Language_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Content_Language_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Content_Language_Query_Test();
};

//-------------------------------------------

class SIP_Header_Content_Length_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Content_Length_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Content_Length_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Content_Length_Query_Test();
};

//-------------------------------------------

class SIP_Header_Content_Type_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Content_Type_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Content_Type_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Content_Type_Query_Test();
};

//-------------------------------------------

class SIP_Header_CSeq_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_CSeq_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_CSeq_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_CSeq_Query_Test();
};

//-------------------------------------------

class SIP_Header_Date_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Date_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Date_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Date_Query_Test();
};

//-------------------------------------------

class SIP_Header_Error_Info_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Error_Info_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Error_Info_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Error_Info_Query_Test();
};

//-------------------------------------------

class SIP_Header_Event_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Event_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Event_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Event_Query_Test();
};

//-------------------------------------------

class SIP_Header_Expires_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Expires_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Expires_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Expires_Query_Test();
};

//-------------------------------------------

class SIP_Header_From_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_From_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_From_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_From_Query_Test();
};

//-------------------------------------------

class SIP_Header_In_Reply_To_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_In_Reply_To_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_In_Reply_To_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_In_Reply_To_Query_Test();
};

//-------------------------------------------

class SIP_Header_Max_Forwards_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Max_Forwards_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Max_Forwards_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Max_Forwards_Query_Test();
};

//-------------------------------------------

class SIP_Header_Mime_Version_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Mime_Version_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Mime_Version_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Mime_Version_Query_Test();
};

//-------------------------------------------

class SIP_Header_Min_Expires_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Min_Expires_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Min_Expires_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Min_Expires_Query_Test();
};

//-------------------------------------------

class SIP_Header_Organization_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Organization_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Organization_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Organization_Query_Test();
};

//-------------------------------------------

class SIP_Header_Priority_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Priority_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Priority_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Priority_Query_Test();
};

//-------------------------------------------

class SIP_Header_Proxy_Authenticate_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Proxy_Authenticate_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Proxy_Authenticate_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Proxy_Authenticate_Query_Test();
};

//-------------------------------------------

class SIP_Header_Proxy_Authorization_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Proxy_Authorization_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Proxy_Authorization_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Proxy_Authorization_Query_Test();
};

//-------------------------------------------

class SIP_Header_Proxy_Require_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Proxy_Require_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Proxy_Require_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Proxy_Require_Query_Test();
};

//-------------------------------------------

class SIP_Header_RAck_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_RAck_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_RAck_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_RAck_Query_Test();
};

//-------------------------------------------

class SIP_Header_Record_Route_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Record_Route_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Record_Route_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Record_Route_Query_Test();
};

//-------------------------------------------

class SIP_Header_Refer_To_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Refer_To_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Refer_To_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Refer_To_Query_Test();
};

//-------------------------------------------

class SIP_Header_Referred_By_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Referred_By_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Referred_By_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Referred_By_Query_Test();
};

//-------------------------------------------

class SIP_Header_Reply_To_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Reply_To_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Reply_To_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Reply_To_Query_Test();
};

//-------------------------------------------

class SIP_Header_Require_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Require_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Require_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Require_Query_Test();
};

//-------------------------------------------

class SIP_Header_Retry_After_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Retry_After_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Retry_After_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Retry_After_Query_Test();
};

//-------------------------------------------

class SIP_Header_Route_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Route_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Route_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Route_Query_Test();
};

//-------------------------------------------

class SIP_Header_RSeq_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_RSeq_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_RSeq_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_RSeq_Query_Test();
};

//-------------------------------------------

class SIP_Header_Server_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Server_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Server_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Server_Query_Test();
};

//-------------------------------------------

class SIP_Header_Subject_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Subject_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Subject_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Subject_Query_Test();
};

//-------------------------------------------

class SIP_Header_Subscription_State_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Subscription_State_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Subscription_State_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Subscription_State_Query_Test();
};

//-------------------------------------------

class SIP_Header_Supported_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Supported_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Supported_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Supported_Query_Test();
};

//-------------------------------------------

class SIP_Header_Timestamp_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Timestamp_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Timestamp_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Timestamp_Query_Test();
};

//-------------------------------------------

class SIP_Header_To_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_To_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_To_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_To_Query_Test();
};

//-------------------------------------------

class SIP_Header_Unknown_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Unknown_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Unknown_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Unknown_Query_Test();
};

//-------------------------------------------

class SIP_Header_Unsupported_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Unsupported_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Unsupported_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Unsupported_Query_Test();
};

//-------------------------------------------

class SIP_Header_User_Agent_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_User_Agent_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_User_Agent_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_User_Agent_Query_Test();
};

//-------------------------------------------

class SIP_Header_Via_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Via_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Via_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Via_Query_Test();
};

//-------------------------------------------

class SIP_Header_Warning_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_Warning_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_Warning_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_Warning_Query_Test();
};

//-------------------------------------------

class SIP_Header_WWW_Authenticate_Decode_Encode_Test : public SIP_Header_Decode_Encode_Test
{
public:
    SIP_Header_WWW_Authenticate_Decode_Encode_Test();
};

//-------------------------------------------

class SIP_Header_WWW_Authenticate_Query_Test : public SIP_Header_Query_Test
{
public:
    SIP_Header_WWW_Authenticate_Query_Test();
};

//-------------------------------------------
