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

//-------------------------------------------

bool SIP_Header_Test::init()
{
    std::cout << "SIP header test initialized\n";

    if (!run<SIP_Header_Accept_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Accept_Encoding_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Accept_Language_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Alert_Info_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Allow_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Allow_Events_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Authentication_Info_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Authorization_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Call_ID_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Call_Info_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Contact_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Content_Disposition_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Content_Encoding_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Content_Language_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Content_Length_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Content_Type_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_CSeq_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Date_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Error_Info_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Event_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Expires_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_From_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_In_Reply_To_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Max_Forwards_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Mime_Version_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Min_Expires_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Organization_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Priority_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Proxy_Authenticate_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Proxy_Authorization_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Proxy_Require_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_RAck_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Record_Route_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Refer_To_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Referred_By_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Reply_To_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Require_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Retry_After_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Route_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_RSeq_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Server_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Subject_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Subscription_State_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Supported_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Timestamp_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_To_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Unknown_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Unsupported_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_User_Agent_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Via_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_Warning_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Header_WWW_Authenticate_Decode_Encode_Test>())
        return false;


    if (!run<SIP_Header_Accept_Query_Test>())
        return false;

    if (!run<SIP_Header_Accept_Encoding_Query_Test>())
        return false;

    if (!run<SIP_Header_Accept_Language_Query_Test>())
        return false;

    if (!run<SIP_Header_Alert_Info_Query_Test>())
        return false;

    if (!run<SIP_Header_Allow_Query_Test>())
        return false;

    if (!run<SIP_Header_Allow_Events_Query_Test>())
        return false;

    if (!run<SIP_Header_Authentication_Info_Query_Test>())
        return false;

    if (!run<SIP_Header_Authorization_Query_Test>())
        return false;

    if (!run<SIP_Header_Call_ID_Query_Test>())
        return false;

    if (!run<SIP_Header_Call_Info_Query_Test>())
        return false;

    if (!run<SIP_Header_Contact_Query_Test>())
        return false;

    if (!run<SIP_Header_Content_Disposition_Query_Test>())
        return false;

    if (!run<SIP_Header_Content_Encoding_Query_Test>())
        return false;

    if (!run<SIP_Header_Content_Language_Query_Test>())
        return false;

    if (!run<SIP_Header_Content_Length_Query_Test>())
        return false;

    if (!run<SIP_Header_Content_Type_Query_Test>())
        return false;

    if (!run<SIP_Header_CSeq_Query_Test>())
        return false;

    if (!run<SIP_Header_Date_Query_Test>())
        return false;

    if (!run<SIP_Header_Error_Info_Query_Test>())
        return false;

    if (!run<SIP_Header_Event_Query_Test>())
        return false;

    if (!run<SIP_Header_Expires_Query_Test>())
        return false;

    if (!run<SIP_Header_From_Query_Test>())
        return false;

    if (!run<SIP_Header_In_Reply_To_Query_Test>())
        return false;

    if (!run<SIP_Header_Max_Forwards_Query_Test>())
        return false;

    if (!run<SIP_Header_Mime_Version_Query_Test>())
        return false;

    if (!run<SIP_Header_Min_Expires_Query_Test>())
        return false;

    if (!run<SIP_Header_Organization_Query_Test>())
        return false;

    if (!run<SIP_Header_Priority_Query_Test>())
        return false;

    if (!run<SIP_Header_Proxy_Authenticate_Query_Test>())
        return false;

    if (!run<SIP_Header_Proxy_Authorization_Query_Test>())
        return false;

    if (!run<SIP_Header_Proxy_Require_Query_Test>())
        return false;

    if (!run<SIP_Header_RAck_Query_Test>())
        return false;

    if (!run<SIP_Header_Record_Route_Query_Test>())
        return false;

    if (!run<SIP_Header_Refer_To_Query_Test>())
        return false;

    if (!run<SIP_Header_Referred_By_Query_Test>())
        return false;

    if (!run<SIP_Header_Reply_To_Query_Test>())
        return false;

    if (!run<SIP_Header_Require_Query_Test>())
        return false;

    if (!run<SIP_Header_Retry_After_Query_Test>())
        return false;

    if (!run<SIP_Header_Route_Query_Test>())
        return false;

    if (!run<SIP_Header_RSeq_Query_Test>())
        return false;

    if (!run<SIP_Header_Server_Query_Test>())
        return false;

    if (!run<SIP_Header_Subject_Query_Test>())
        return false;

    if (!run<SIP_Header_Subscription_State_Query_Test>())
        return false;

    if (!run<SIP_Header_Supported_Query_Test>())
        return false;

    if (!run<SIP_Header_Timestamp_Query_Test>())
        return false;

    if (!run<SIP_Header_To_Query_Test>())
        return false;

    if (!run<SIP_Header_Unknown_Query_Test>())
        return false;

    if (!run<SIP_Header_Unsupported_Query_Test>())
        return false;

    if (!run<SIP_Header_User_Agent_Query_Test>())
        return false;

    if (!run<SIP_Header_Via_Query_Test>())
        return false;

    if (!run<SIP_Header_Warning_Query_Test>())
        return false;

    if (!run<SIP_Header_WWW_Authenticate_Query_Test>())
        return false;

    std::cout << "SIP header test completed successfully\n";
    return true;
}

//-------------------------------------------

template<class T> bool SIP_Header_Test::run()
{
    T test;
    if (!test.run())
        return false;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Decode_Encode_Test::run()
{
    std::list<SIP_Header_Input_Output>::const_iterator it = _header_input_output.begin();
    while (it != _header_input_output.end())
    {
        SIP_Header_Input_Output header_input_output = *it++;

        std::cout << "SIP header decode encode test initialized (type: " << header_input_output._header_type << ")\n";

        sip_header_list headers;

        std::string input = header_input_output._input;
        bool decode = SIP_Header::decode_headers(input, headers);

        if (header_input_output._decode_success != decode)
        {
            std::cout << "SIP_Header_Decode_Encode_Test::run -> Failed to decode headers:\n";
            std::cout << std::setw(12) << "Type: " << header_input_output._header_type << "\n";
            std::cout << std::setw(12) << "Input: " << header_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << (header_input_output._decode_success ? "true" : "false") << "\n";
            std::cout << std::setw(12) << "Success: " << (decode ? "true" : "false") << "\n";
            return false;
        }

        if (!decode)
        {
            std::cout << "SIP header decode encode test completed successfully (type: " << header_input_output._header_type << ")\n";
            clear(headers);
            continue;
        }

        if (header_input_output._header_nb != (unsigned short) headers.size())
        {
            std::cout << "SIP_Header_Decode_Encode_Test::run -> Invalid size of headers:\n";
            std::cout << std::setw(12) << "Type: " << header_input_output._header_type << "\n";
            std::cout << std::setw(12) << "Input: " << header_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << header_input_output._header_nb << "\n";
            std::cout << std::setw(12) << "Size: " << headers.size() << "\n";
            clear(headers);
            return false;
        }

        sip_header_list::iterator it2 = headers.begin();
        while (it2 != headers.end())
        {
            SIP_Header *header = *it2++;
            if (header->get_header_type() != header_input_output._header_type)
            {
                std::cout << "SIP_Header_Decode_Encode_Test::run -> Invalid decoded header type:\n";
                std::cout << std::setw(12) << "Type: " << header_input_output._header_type << "\n";
                std::cout << std::setw(12) << "Input: " << header_input_output._input.c_str() << "\n";
                std::cout << std::setw(12) << "Result: " << header->get_header_type() << "\n";
                clear(headers);
                return false;
            }
        }

        sip_header_list copy;
        if (!copy_headers(headers, copy))
        {
            std::cout << "SIP_Header_Decode_Encode_Test::run -> Failed to copy headers:\n";
            std::cout << std::setw(12) << "Type: " << header_input_output._header_type << "\n";
            std::cout << std::setw(12) << "Input: " << header_input_output._input.c_str() << "\n";
            clear(headers);
            return false;
        }

        clear(headers);

        std::string output;
        bool encode = SIP_Header::encode_headers(output, copy);

        if (header_input_output._encode_success != encode)
        {
            std::cout << "SIP_Header_Decode_Encode_Test::run -> Failed to encode headers:\n";
            std::cout << std::setw(12) << "Type: " << header_input_output._header_type << "\n";
            std::cout << std::setw(12) << "Input: " << header_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << (header_input_output._encode_success ? "true" : "false") << "\n";
            std::cout << std::setw(12) << "Success: " << (encode ? "true" : "false") << "\n";
            clear(copy);
            return false;
        }

        if (!encode)
        {
            std::cout << "SIP header decode encode test completed successfully (type: " << header_input_output._header_type << ")\n";
            clear(copy);
            continue;
        }

        if (output != header_input_output._output)
        {
            std::cout << "SIP_Header_Decode_Encode_Test::run -> Invalid encoded header:\n";
            std::cout << std::setw(12) << "Type: " << header_input_output._header_type << "\n";
            std::cout << std::setw(12) << "Input: " << header_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << header_input_output._output.c_str() << "\n";
            std::cout << std::setw(12) << "Output: " << output.c_str() << "\n";
            clear(copy);
            return false;
        }

        clear(copy);

        std::cout << "SIP header decode encode test completed successfully (type: " << header_input_output._header_type << ")\n";
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Decode_Encode_Test::copy_headers(sip_header_list &headers, sip_header_list &copy)
{
    sip_header_list::const_iterator it = headers.begin();
    while (it != headers.end())
    {
        SIP_Header *header = *it++;

        SIP_Header *new_header = SIP_Header::create_header(header->get_header_type(), header);
        if (!new_header)
            return false;

        copy.push_back(new_header);
    }

    return true;
}

//-------------------------------------------

void SIP_Header_Decode_Encode_Test::clear(sip_header_list &headers)
{
    sip_header_list::const_iterator it = headers.begin();
    while (it != headers.end())
        delete *it++;

    headers.clear();
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Query_Test::run()
{
    SIP_Header *header = SIP_Header::create_header(_header_type);
    if (!header)
    {
        std::cout << "SIP_Header_Query_Test::run -> create header failed:\n";
        std::cout << std::setw(12) << "Type: " << _header_type << "\n";
        return false;
    }

    std::list<SIP_Header_Query>::const_iterator it = _header_query.begin();
    while (it != _header_query.end())
    {
        SIP_Header_Query header_query = *it++;

        std::cout << "SIP header query test initialized (type: " << _header_type << ")\n";

        std::string result;
        bool success = header->query(header_query._cmd, header_query._query, result);

        if (header_query._success != success)
        {
            std::cout << "SIP_Header_Query_Test::run -> Query failed:\n";
            std::cout << std::setw(12) << "Type: " << _header_type << "\n";
            std::cout << std::setw(12) << "Cmd: " << header_query._cmd << "\n";
            std::cout << std::setw(12) << "Query: " << header_query._query.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << (header_query._success ? "true" : "false") << "\n";
            std::cout << std::setw(12) << "Success: " << (success ? "true" : "false") << "\n";
            delete header;
            return false;
        }

        if ((!header_query._expected_result.empty()) && (result != header_query._expected_result))
        {
            std::cout << "SIP_Header_Query_Test::run -> Query result failed:\n";
            std::cout << std::setw(12) << "Type: " << _header_type << "\n";
            std::cout << std::setw(12) << "Cmd: " << header_query._cmd << "\n";
            std::cout << std::setw(12) << "Query: " << header_query._query.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << header_query._expected_result.c_str() << "\n";
            std::cout << std::setw(12) << "Result: " << result.c_str() << "\n";
            delete header;
            return false;
        }

        std::cout << "SIP header query test completed successfully (type: " << _header_type << ")\n";
    }

    delete header;
    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Accept_Decode_Encode_Test::SIP_Header_Accept_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_ACCEPT;
    hdr1._input          = "Accept: application/sdp";
    hdr1._output         = "Accept: application/sdp\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_ACCEPT;
    hdr2._input          = "Accept:application/sdp;level=1, application/x-private, text/html";
    hdr2._output         = "Accept: application/sdp;level=1, application/x-private, text/html\r\n";
    hdr2._header_nb      = 3;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_ACCEPT;
    hdr3._input          = "Accept: */*;q=0.75,application/*,   text/html,test1/test2";
    hdr3._output         = "Accept: */*;q=0.75, application/*, text/html, test1/test2\r\n";
    hdr3._header_nb      = 4;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_ACCEPT;
    hdr4._input          = "Accept:";
    hdr4._output         = "Accept: \r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Accept_Query_Test::SIP_Header_Accept_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_ACCEPT)
{
    _header_query.emplace_back(QUERY_SET, "Media-Range.Type.application", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Range.Type", "application", true);
    _header_query.emplace_back(QUERY_SET, "Media-Range.Type.*", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Range.Type", "*", true);
    _header_query.emplace_back(QUERY_SET, "Media-Range.Subtype.sdp", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Range.Subtype", "sdp", true);
    _header_query.emplace_back(QUERY_SET, "Media-Range.Subtype.*", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Range.Subtype", "*", true);
    _header_query.emplace_back(QUERY_SET, "Media-Range.Q.0.001", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Range.Q", "0.001", true);
    _header_query.emplace_back(QUERY_SET, "Media-Range.Q.1.000", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Range.Q", "1.000", true);
    _header_query.emplace_back(QUERY_ADD, "Media-Range.Parameters.0.level=1", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Range.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Media-Range.Parameters.0", "level=1", true);
    _header_query.emplace_back(QUERY_DEL, "Media-Range.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Range.Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Accept_Encoding_Decode_Encode_Test::SIP_Header_Accept_Encoding_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_ACCEPT_ENCODING;
    hdr1._input          = "Accept-Encoding: gzip, text/plain";
    hdr1._output         = "Accept-Encoding: gzip, text/plain\r\n";
    hdr1._header_nb      = 2;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_ACCEPT_ENCODING;
    hdr2._input          = "Accept-Encoding: ";
    hdr2._output         = "Accept-Encoding: \r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_ACCEPT_ENCODING;
    hdr3._input          = "Accept-Encoding: *;q=0.75,code1,   code2;par1,code3";
    hdr3._output         = "Accept-Encoding: *;q=0.75, code1, code2;par1, code3\r\n";
    hdr3._header_nb      = 4;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_ACCEPT_ENCODING;
    hdr4._input          = "Accept-Encoding: *;par1=test; q=1.000  ; par2=test";
    hdr4._output         = "Accept-Encoding: *;q=1.000;par1=test;par2=test\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_ACCEPT_ENCODING;
    hdr5._input          = "Accept-Encoding: gzip";
    hdr5._output         = "Accept-Encoding: gzip\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Accept_Encoding_Query_Test::SIP_Header_Accept_Encoding_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_ACCEPT_ENCODING)
{
    _header_query.emplace_back(QUERY_SET, "Coding.text/plain", "", true);
    _header_query.emplace_back(QUERY_GET, "Coding", "text/plain", true);
    _header_query.emplace_back(QUERY_SET, "Coding.gzip", "", true);
    _header_query.emplace_back(QUERY_GET, "Coding", "gzip", true);
    _header_query.emplace_back(QUERY_SET, "Coding.", "", true);
    _header_query.emplace_back(QUERY_GET, "Coding", "", true);
    _header_query.emplace_back(QUERY_SET, "Q.1.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Q", "1.0", true);
    _header_query.emplace_back(QUERY_SET, "Q.0.3", "", true);
    _header_query.emplace_back(QUERY_GET, "Q", "0.3", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.parameter1", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "parameter1", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Accept_Language_Decode_Encode_Test::SIP_Header_Accept_Language_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_ACCEPT_LANGUAGE;
    hdr1._input          = "Accept-Language: pt";
    hdr1._output         = "Accept-Language: pt\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_ACCEPT_LANGUAGE;
    hdr2._input          = "Accept-Language:";
    hdr2._output         = "Accept-Language: \r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_ACCEPT_LANGUAGE;
    hdr3._input          = "Accept-Language: da, en-gb;q=0.8, en ;q=0.7, *";
    hdr3._output         = "Accept-Language: da, en-gb;q=0.8, en;q=0.7, *\r\n";
    hdr3._header_nb      = 4;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_ACCEPT_LANGUAGE;
    hdr4._input          = "Accept-Language: en-us, en-gb; par1 = test ; q=0.8;par2";
    hdr4._output         = "Accept-Language: en-us, en-gb;q=0.8;par1 = test;par2\r\n";
    hdr4._header_nb      = 2;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Accept_Language_Query_Test::SIP_Header_Accept_Language_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_ACCEPT_LANGUAGE)
{
    _header_query.emplace_back(QUERY_SET, "Language.en-us", "", true);
    _header_query.emplace_back(QUERY_GET, "Language", "en-us", true);
    _header_query.emplace_back(QUERY_SET, "Language.fr", "", true);
    _header_query.emplace_back(QUERY_GET, "Language", "fr", true);
    _header_query.emplace_back(QUERY_SET, "Language.", "", true);
    _header_query.emplace_back(QUERY_GET, "Language", "", true);
    _header_query.emplace_back(QUERY_SET, "Q.0.1", "", true);
    _header_query.emplace_back(QUERY_GET, "Q", "0.1", true);
    _header_query.emplace_back(QUERY_SET, "Q.0.999", "", true);
    _header_query.emplace_back(QUERY_GET, "Q", "0.999", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.parameter1=test", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "parameter1=test", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Alert_Info_Decode_Encode_Test::SIP_Header_Alert_Info_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_ALERT_INFO;
    hdr1._input          = "Alert-Info: <http://www.example.com/sounds/moo.wav>";
    hdr1._output         = "Alert-Info: <http://www.example.com/sounds/moo.wav>\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_ALERT_INFO;
    hdr2._input          = "Alert-Info: <mailto:user@host.com;par1; par2 ;par3>;param1 ; param2 ;param3 ";
    hdr2._output         = "Alert-Info: <mailto:user@host.com;par1; par2 ;par3>;param1;param2;param3\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_ALERT_INFO;
    hdr3._input          = "Alert-Info: <sips:user@host.com;par1> ; param1 ; param2 ;param3, <abc:user;par1> ; param2";
    hdr3._output         = "Alert-Info: <sips:user@host.com;par1>;param1;param2;param3, <abc:user;par1>;param2\r\n";
    hdr3._header_nb      = 2;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Alert_Info_Query_Test::SIP_Header_Alert_Info_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_ALERT_INFO)
{
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name.Bob", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name", "Bob", true);
    _header_query.emplace_back(QUERY_SET, "Address.Scheme.mailto", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Scheme", "mailto", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User.bob", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User", "bob", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Password.mypass", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Password", "mypass", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Host.Address.host.com", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Host.Address", "host.com", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Port.7700", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Port", "7700", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Transport.UDP", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Transport", "UDP", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User-Param.phone", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User-Param", "phone", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Method.INFO", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Method", "INFO", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.TTL.1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.TTL", "1", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Multicast-Address.Address.1111::2222", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Multicast-Address.Address", "1111::2222", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "True", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Parameters.0.par1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.0", "par1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "0", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.par=1234", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "par=1234", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Allow_Decode_Encode_Test::SIP_Header_Allow_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_ALLOW;
    hdr1._input          = "Allow: INVITE";
    hdr1._output         = "Allow: INVITE\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_ALLOW;
    hdr2._input          = "Allow: INVITE, ACK,  OPTIONS, CANCEL,BYE";
    hdr2._output         = "Allow: INVITE, ACK, OPTIONS, CANCEL, BYE\r\n";
    hdr2._header_nb      = 5;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_ALLOW;
    hdr3._input          = "Allow:NOTIFY,REFER,   TEST  ";
    hdr3._output         = "Allow: NOTIFY, REFER, TEST\r\n";
    hdr3._header_nb      = 3;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_ALLOW;
    hdr4._input          = "Allow:";
    hdr4._output         = "Allow: \r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Allow_Query_Test::SIP_Header_Allow_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_ALLOW)
{
    _header_query.emplace_back(QUERY_SET, "Method.INVITE", "", true);
    _header_query.emplace_back(QUERY_GET, "Method", "INVITE", true);
    _header_query.emplace_back(QUERY_SET, "Method.TEST", "", true);
    _header_query.emplace_back(QUERY_GET, "Method", "TEST", true);
    _header_query.emplace_back(QUERY_SET, "Method.", "", true);
    _header_query.emplace_back(QUERY_GET, "Method", "", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Allow_Events_Decode_Encode_Test::SIP_Header_Allow_Events_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_ALLOW_EVENTS;
    hdr1._input          = "Allow-Events: presence";
    hdr1._output         = "Allow-Events: presence\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_ALLOW_EVENTS;
    hdr2._input          = "Allow-Events:presence, test1.test2";
    hdr2._output         = "Allow-Events: presence, test1.test2\r\n";
    hdr2._header_nb      = 2;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_ALLOW_EVENTS;
    hdr3._input          = "u: presence.template1.template2 , test.template,package-xyz";
    hdr3._output         = "Allow-Events: presence.template1.template2, test.template, package-xyz\r\n";
    hdr3._header_nb      = 3;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Allow_Events_Query_Test::SIP_Header_Allow_Events_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_ALLOW_EVENTS)
{
    _header_query.emplace_back(QUERY_SET, "Event-Type.Package.presence", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Package", "presence", true);
    _header_query.emplace_back(QUERY_SET, "Event-Type.Package.package1", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Package", "package1", true);
    _header_query.emplace_back(QUERY_ADD, "Event-Type.Templates.0.template1", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.0", "template1", true);
    _header_query.emplace_back(QUERY_ADD, "Event-Type.Templates.1.template2", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.Size", "2", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.1", "template2", true);
    _header_query.emplace_back(QUERY_ADD, "Event-Type.Templates.0.template0", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.Size", "3", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.0", "template0", true);
    _header_query.emplace_back(QUERY_DEL, "Event-Type.Templates.2", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.Size", "2", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.0", "template0", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.1", "template1", true);
    _header_query.emplace_back(QUERY_DEL, "Event-Type.Templates.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.0", "template1", true);
    _header_query.emplace_back(QUERY_DEL, "Event-Type.Templates.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Authentication_Info_Decode_Encode_Test::SIP_Header_Authentication_Info_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_AUTHENTICATION_INFO;
    hdr1._input          = "Authentication-Info: nextnonce=\"47364c23432d2e131a5fb210812c\"";
    hdr1._output         = "Authentication-Info: nextnonce=\"47364c23432d2e131a5fb210812c\"\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_AUTHENTICATION_INFO;
    hdr2._input          = "Authentication-Info: qop=auth, rspauth=\"1234567890abcdef1234567890\", cnonce=\"11223344\", nc=00000001";
    hdr2._output         = "Authentication-Info: qop=auth, rspauth=\"1234567890abcdef1234567890\", cnonce=\"11223344\", nc=00000001\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_AUTHENTICATION_INFO;
    hdr3._input          = "Authentication-Info:   rspauth=\"1234567890abcdef1234567890\",cnonce=\"11223344\", \t ";
    hdr3._input         += "nextnonce=\"47364c23432d2e131a5fb210812c\",nc=00000001,qop=auth";
    hdr3._output         = "Authentication-Info: nextnonce=\"47364c23432d2e131a5fb210812c\", qop=auth, ";
    hdr3._output        += "rspauth=\"1234567890abcdef1234567890\", cnonce=\"11223344\", nc=00000001\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Authentication_Info_Query_Test::SIP_Header_Authentication_Info_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_AUTHENTICATION_INFO)
{
    _header_query.emplace_back(QUERY_SET, "Next-Nonce.47364c23432d2e131a5fb210812c", "", true);
    _header_query.emplace_back(QUERY_GET, "Next-Nonce", "47364c23432d2e131a5fb210812c", true);
    _header_query.emplace_back(QUERY_SET, "QoP.auth", "", true);
    _header_query.emplace_back(QUERY_GET, "QoP", "auth", true);
    _header_query.emplace_back(QUERY_SET, "Response.1234567890abcdef1234567890", "", true);
    _header_query.emplace_back(QUERY_GET, "Response", "1234567890abcdef1234567890", true);
    _header_query.emplace_back(QUERY_SET, "CNonce.11223344", "", true);
    _header_query.emplace_back(QUERY_GET, "CNonce", "11223344", true);
    _header_query.emplace_back(QUERY_SET, "Nonce-Count.00000001", "", true);
    _header_query.emplace_back(QUERY_GET, "Nonce-Count", "00000001", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.param1", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "param1", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Authorization_Decode_Encode_Test::SIP_Header_Authorization_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_AUTHORIZATION;
    hdr1._input          = "Authorization: Digest username=\"Alice\", realm=\"atlanta.com\", nonce=\"84a4cc6f3082121f32b42a2187831a9e\", ";
    hdr1._input         += "nonce=\"84a4cc6f3082121f32b42a2187831a9e\", response=\"7587245234b3434cc3412213e5f113a5432\"";
    hdr1._output         = "Authorization: Digest username=\"Alice\", realm=\"atlanta.com\", nonce=\"84a4cc6f3082121f32b42a2187831a9e\", ";
    hdr1._output        += "response=\"7587245234b3434cc3412213e5f113a5432\"\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_AUTHORIZATION;
    hdr2._input          = "Authorization: Digest username=\"bob\", realm=\"biloxi.com\", nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\", ";
    hdr2._input         += "uri=\"sip:bob@biloxi.com\", qop=auth, nc=00000001, cnonce=\"0a4f113b\", ";
    hdr2._input         += "response=\"6629fae49393a05397450978507c4ef1\", opaque=\"5ccc069c403ebaf9f0171e9517f40e41\"";
    hdr2._output         = "Authorization: Digest username=\"bob\", realm=\"biloxi.com\", nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\", ";
    hdr2._output        += "uri=\"sip:bob@biloxi.com\", response=\"6629fae49393a05397450978507c4ef1\", cnonce=\"0a4f113b\", ";
    hdr2._output        += "opaque=\"5ccc069c403ebaf9f0171e9517f40e41\", qop=auth, nc=00000001\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_AUTHORIZATION;
    hdr3._input          = "Authorization: Digest username=\"bob\",realm=\"atlanta.example.com\",";
    hdr3._input         += "nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\" ,   opaque=\"\",   uri=\"sips:ss2.biloxi.example.com\",";
    hdr3._input         += "response=\"dfe56131d1958046689d83306477ecc\"";
    hdr3._output         = "Authorization: Digest username=\"bob\", realm=\"atlanta.example.com\", ";
    hdr3._output        += "nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\", uri=\"sips:ss2.biloxi.example.com\", ";
    hdr3._output        += "response=\"dfe56131d1958046689d83306477ecc\", opaque=\"\"\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_AUTHORIZATION;
    hdr4._input          = "Authorization: Digest\tusername=\"name\",realm=\"myrealm.com\",nonce=\"123456789012345678901\", ";
    hdr4._input         += "uri=\"sip:myrealm.com\",response=\"12345678901234567890123456789012\",algorithm=MD5";
    hdr4._output         = "Authorization: Digest username=\"name\", realm=\"myrealm.com\", nonce=\"123456789012345678901\", ";
    hdr4._output        += "uri=\"sip:myrealm.com\", response=\"12345678901234567890123456789012\", algorithm=MD5\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_AUTHORIZATION;
    hdr5._input          = "Authorization: Scheme1 param1, param2=test, nonce=\"123456789012345678901\",realm=\"server.com\",";
    hdr5._input         += "response=\"12345678901234567890123456789012\", username=\"1234\", uri=\"sip:server.com\",qop=auth, ";
    hdr5._input         += "nc=00000001, cnonce=\"0a4f113b\", opaque=\"11223344556677889900aabbccddeeff\", par3=\"test\", algorithm=XYZ";
    hdr5._output         = "Authorization: Scheme1 username=\"1234\", realm=\"server.com\", nonce=\"123456789012345678901\", ";
    hdr5._output        += "uri=\"sip:server.com\", response=\"12345678901234567890123456789012\", algorithm=XYZ, cnonce=\"0a4f113b\", ";
    hdr5._output        += "opaque=\"11223344556677889900aabbccddeeff\", qop=auth, nc=00000001, param1, param2=test, par3=\"test\"\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6;
    hdr6._header_type    = SIP_HEADER_AUTHORIZATION;
    hdr6._input          = "Authorization: scheme2 param1, param2=test,par3=\"test\"";
    hdr6._output         = "Authorization: scheme2 param1, param2=test, par3=\"test\"\r\n";
    hdr6._header_nb      = 1;
    hdr6._decode_success = true;
    hdr6._encode_success = true;
    _header_input_output.push_back(hdr6);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Authorization_Query_Test::SIP_Header_Authorization_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_AUTHORIZATION)
{
    _header_query.emplace_back(QUERY_SET, "Credential.Scheme.scheme1", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Scheme", "scheme1", true);
    _header_query.emplace_back(QUERY_SET, "Credential.Username.1234", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Username", "1234", true);
    _header_query.emplace_back(QUERY_SET, "Credential.Realm.myrealm.com", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Realm", "myrealm.com", true);
    _header_query.emplace_back(QUERY_SET, "Credential.Nonce.123456789012345678901", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Nonce", "123456789012345678901", true);
    _header_query.emplace_back(QUERY_SET, "Credential.URI.sip:myrealm.com", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.URI", "sip:myrealm.com", true);
    _header_query.emplace_back(QUERY_SET, "Credential.Response.12345678901234567890123456789012", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Response", "12345678901234567890123456789012", true);
    _header_query.emplace_back(QUERY_SET, "Credential.Algorithm.MD5", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Algorithm", "MD5", true);
    _header_query.emplace_back(QUERY_SET, "Credential.CNonce.0a4f113b", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.CNonce", "0a4f113b", true);
    _header_query.emplace_back(QUERY_SET, "Credential.Opaque.11223344556677889900aabbccddeeff", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Opaque", "11223344556677889900aabbccddeeff", true);
    _header_query.emplace_back(QUERY_SET, "Credential.QoP.auth", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.QoP", "auth", true);
    _header_query.emplace_back(QUERY_SET, "Credential.Nonce-Count.00000001", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Nonce-Count", "00000001", true);
    _header_query.emplace_back(QUERY_ADD, "Credential.Parameters.0.param1", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Parameters.0", "param1", true);
    _header_query.emplace_back(QUERY_DEL, "Credential.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Call_ID_Decode_Encode_Test::SIP_Header_Call_ID_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_CALL_ID;
    hdr1._input          = "Call-ID: 123456789@my-domain.org";
    hdr1._output         = "Call-ID: 123456789@my-domain.org\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_CALL_ID;
    hdr2._input          = "Call-ID: 123456789";
    hdr2._output         = "Call-ID: 123456789\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_CALL_ID;
    hdr3._input          = "i:my-domain.org ";
    hdr3._output         = "Call-ID: my-domain.org\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_CALL_ID;
    hdr4._input          = "Call-ID: f81d4fae-7dec-11d0-a765-00a0c91e6bf6@biloxi.com";
    hdr4._output         = "Call-ID: f81d4fae-7dec-11d0-a765-00a0c91e6bf6@biloxi.com\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_CALL_ID;
    hdr5._input          = "i:f81d4fae-7dec-11d0-a765-00a0c91e6bf6@192.0.2.4";
    hdr5._output         = "Call-ID: f81d4fae-7dec-11d0-a765-00a0c91e6bf6@192.0.2.4\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Call_ID_Query_Test::SIP_Header_Call_ID_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_CALL_ID)
{
    _header_query.emplace_back(QUERY_SET, "Call-ID.123456789@my-domain.org", "", true);
    _header_query.emplace_back(QUERY_GET, "Call-ID", "123456789@my-domain.org", true);
    _header_query.emplace_back(QUERY_SET, "Call-ID.my-domain.org", "", true);
    _header_query.emplace_back(QUERY_GET, "Call-ID", "my-domain.org", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Call_Info_Decode_Encode_Test::SIP_Header_Call_Info_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_CALL_INFO;
    hdr1._input          = "Call-Info: <http://wwww.example.com/alice/photo.jpg> ;purpose=icon, <http://www.example.com/alice/> ";
    hdr1._input         += ";purpose=info";
    hdr1._output         = "Call-Info: <http://wwww.example.com/alice/photo.jpg>;purpose=icon, <http://www.example.com/alice/>";
    hdr1._output        += ";purpose=info\r\n";
    hdr1._header_nb      = 2;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_CALL_INFO;
    hdr2._input          = "Call-Info: <mailto:user@host.com;par1; par2 ;par3>;param1 ; param2 ;param3 ";
    hdr2._output         = "Call-Info: <mailto:user@host.com;par1; par2 ;par3>;param1;param2;param3\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_CALL_INFO;
    hdr3._input          = "Call-Info: <sips:user@host.com;par1> ; param1 ; purpose= card; param2 ;param3,<abc:user;par1> ; param2";
    hdr3._output         = "Call-Info: <sips:user@host.com;par1>;purpose=card;param1;param2;param3, <abc:user;par1>;param2\r\n";
    hdr3._header_nb      = 2;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Call_Info_Query_Test::SIP_Header_Call_Info_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_CALL_INFO)
{
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name.User123", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name", "User123", true);
    _header_query.emplace_back(QUERY_SET, "Address.Scheme.sip", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Scheme", "sip", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User.test1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User", "test1", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Password.mypass", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Password", "mypass", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Host.Address.10.10.10.10", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Host.Address", "10.10.10.10", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Port.5000", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Port", "5000", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Transport.UDP", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Transport", "UDP", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User-Param.phone", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User-Param", "phone", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Method.INVITE", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Method", "INVITE", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.TTL.20", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.TTL", "20", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Multicast-Address.Address.1111::2222", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Multicast-Address.Address", "1111::2222", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "True", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Parameters.0.par1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.0", "par1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "0", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Headers.0.header1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.0", "header1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Headers.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "0", true);
    _header_query.emplace_back(QUERY_SET, "Address.Absolute-URI.Address.11.22.33.44", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Absolute-URI.Address", "11.22.33.44", true);
    _header_query.emplace_back(QUERY_SET, "Purpose.info", "", true);
    _header_query.emplace_back(QUERY_GET, "Purpose", "info", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.par1234", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "par1234", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Contact_Decode_Encode_Test::SIP_Header_Contact_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_CONTACT;
    hdr1._input          = "Contact: sip:123456789@my-domain.org";
    hdr1._output         = "Contact: sip:123456789@my-domain.org\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_CONTACT;
    hdr2._input          = "Contact: sips:my-domain.org:5060;parameter1;parameter2;expires=60;parameter3;q=1.0";
    hdr2._output         = "Contact: sips:my-domain.org:5060;expires=60;q=1.0;parameter1;parameter2;parameter3\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_CONTACT;
    hdr3._input          = "Contact:   Display name here <sip:my-domain.org;par;lr;ttl=160>;parameter1  ;q=0.5;  parameter2,";
    hdr3._input         += "tel:+123456789;par";
    hdr3._output         = "Contact: Display name here <sip:my-domain.org;ttl=160;lr;par>;q=0.5;parameter1;parameter2\r\n";
    hdr3._output        += "Contact: tel:+123456789;par\r\n";
    hdr3._header_nb      = 2;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_CONTACT;
    hdr4._input          = "Contact: \"Mr. Watson\" <sip:watson@worcester.bell-telephone.com;lr;par1? header=hdr1 > ;q=0.7 ;expires=3600, ";
    hdr4._input         += "\"Mr. Watson\" <mailto:watson@bell-telephone.com> ;q=0.1";
    hdr4._output         = "Contact: \"Mr. Watson\" <sip:watson@worcester.bell-telephone.com;lr;par1?header=hdr1>;expires=3600;q=0.7\r\n";
    hdr4._output        += "Contact: \"Mr. Watson\" <mailto:watson@bell-telephone.com>;q=0.1\r\n";
    hdr4._header_nb      = 2;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_CONTACT;
    hdr5._input          = "m: *";
    hdr5._output         = "Contact: *\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6;
    hdr6._header_type    = SIP_HEADER_CONTACT;
    hdr6._input          = "Contact: sip:123456789:password@my-domain.org";
    hdr6._output         = "Contact: sip:123456789:password@my-domain.org\r\n";
    hdr6._header_nb      = 1;
    hdr6._decode_success = true;
    hdr6._encode_success = true;
    _header_input_output.push_back(hdr6);

    SIP_Header_Input_Output hdr7;
    hdr7._header_type    = SIP_HEADER_CONTACT;
    hdr7._input          = "m: <sips:bob@192.0.2.4>;expires=60";
    hdr7._output         = "Contact: <sips:bob@192.0.2.4>;expires=60\r\n";
    hdr7._header_nb      = 1;
    hdr7._decode_success = true;
    hdr7._encode_success = true;
    _header_input_output.push_back(hdr7);

    SIP_Header_Input_Output hdr8;
    hdr8._header_type    = SIP_HEADER_CONTACT;
    hdr8._input          = "Contact: \"John\" <sip:john@[fe80::64e1:3325:bef6:093e];lr;par1? header=hdr1 > ;q=0.7 ;expires=0, ";
    hdr8._input         += "<mailto:john@[fe80::64e1:3325:bef6:093e]:12345> ;q=0.1";
    hdr8._output         = "Contact: \"John\" <sip:john@[fe80::64e1:3325:bef6:093e];lr;par1?header=hdr1>;expires=0;q=0.7\r\n";
    hdr8._output        += "Contact: <mailto:john@[fe80::64e1:3325:bef6:093e]:12345>;q=0.1\r\n";
    hdr8._header_nb      = 2;
    hdr8._decode_success = true;
    hdr8._encode_success = true;
    _header_input_output.push_back(hdr8);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Contact_Query_Test::SIP_Header_Contact_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_CONTACT)
{
    _header_query.emplace_back(QUERY_SET, "Star.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Star", "True", true);
    _header_query.emplace_back(QUERY_SET, "Star.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Star", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name.Bob", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name", "Bob", true);
    _header_query.emplace_back(QUERY_SET, "Address.Scheme.mailto", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Scheme", "mailto", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User.bob", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User", "bob", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Password.mypass", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Password", "mypass", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Host.Address.host.com", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Host.Address", "host.com", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Port.7700", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Port", "7700", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Transport.UDP", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Transport", "UDP", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User-Param.phone", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User-Param", "phone", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Method.INFO", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Method", "INFO", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.TTL.1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.TTL", "1", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Multicast-Address.Address.1111::2222", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Multicast-Address.Address", "1111::2222", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "True", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Parameters.0.par1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.0", "par1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "0", true);
    _header_query.emplace_back(QUERY_SET, "Expires.3600", "", true);
    _header_query.emplace_back(QUERY_GET, "Expires", "3600", true);
    _header_query.emplace_back(QUERY_SET, "Expires.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Expires", "0", true);
    _header_query.emplace_back(QUERY_SET, "Q.1.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Q", "1.0", true);
    _header_query.emplace_back(QUERY_SET, "Q.0.3", "", true);
    _header_query.emplace_back(QUERY_GET, "Q", "0.3", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.par=1234", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "par=1234", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Disposition_Decode_Encode_Test::SIP_Header_Content_Disposition_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_CONTENT_DISPOSITION;
    hdr1._input          = "Content-Disposition: session;handling=required;par1";
    hdr1._output         = "Content-Disposition: session;handling=required;par1\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_CONTENT_DISPOSITION;
    hdr2._input          = "Content-Disposition:   alert  ;  handling=  optional ; par1 ; par2;par3";
    hdr2._output         = "Content-Disposition: alert;handling=optional;par1;par2;par3\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_CONTENT_DISPOSITION;
    hdr3._input          = "Content-Disposition: attachment; filename=smime.p7s;handling=required";
    hdr3._output         = "Content-Disposition: attachment;handling=required;filename=smime.p7s\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_CONTENT_DISPOSITION;
    hdr4._input          = "Content-Disposition: render";
    hdr4._output         = "Content-Disposition: render\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Disposition_Query_Test::SIP_Header_Content_Disposition_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_CONTENT_DISPOSITION)
{
    _header_query.emplace_back(QUERY_SET, "Type.session", "", true);
    _header_query.emplace_back(QUERY_GET, "Type", "session", true);
    _header_query.emplace_back(QUERY_SET, "Type.alert", "", true);
    _header_query.emplace_back(QUERY_GET, "Type", "alert", true);
    _header_query.emplace_back(QUERY_SET, "Handling.required", "", true);
    _header_query.emplace_back(QUERY_GET, "Handling", "required", true);
    _header_query.emplace_back(QUERY_SET, "Handling.optional", "", true);
    _header_query.emplace_back(QUERY_GET, "Handling", "optional", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.filename=smime.p7s", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "filename=smime.p7s", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Encoding_Decode_Encode_Test::SIP_Header_Content_Encoding_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_CONTENT_ENCODING;
    hdr1._input          = "Content-Encoding: text/plain, gzip";
    hdr1._output         = "Content-Encoding: text/plain, gzip\r\n";
    hdr1._header_nb      = 2;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_CONTENT_ENCODING;
    hdr2._input          = "Content-Encoding:   code1 ";
    hdr2._output         = "Content-Encoding: code1\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_CONTENT_ENCODING;
    hdr3._input          = "Content-Encoding: code1,code2 , code3";
    hdr3._output         = "Content-Encoding: code1, code2, code3\r\n";
    hdr3._header_nb      = 3;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_CONTENT_ENCODING;
    hdr4._input          = "e: tar";
    hdr4._output         = "Content-Encoding: tar\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_CONTENT_ENCODING;
    hdr5._input          = "Content-Encoding:gzip";
    hdr5._output         = "Content-Encoding: gzip\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Encoding_Query_Test::SIP_Header_Content_Encoding_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_CONTENT_ENCODING)
{
    _header_query.emplace_back(QUERY_SET, "Coding.text/plain", "", true);
    _header_query.emplace_back(QUERY_GET, "Coding", "text/plain", true);
    _header_query.emplace_back(QUERY_SET, "Coding.gzip", "", true);
    _header_query.emplace_back(QUERY_GET, "Coding", "gzip", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Language_Decode_Encode_Test::SIP_Header_Content_Language_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_CONTENT_LANGUAGE;
    hdr1._input          = "Content-Language: pt";
    hdr1._output         = "Content-Language: pt\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_CONTENT_LANGUAGE;
    hdr2._input          = "Content-Language:  en,fr ";
    hdr2._output         = "Content-Language: en, fr\r\n";
    hdr2._header_nb      = 2;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_CONTENT_LANGUAGE;
    hdr3._input          = "Content-Language:pt,en, fr";
    hdr3._output         = "Content-Language: pt, en, fr\r\n";
    hdr3._header_nb      = 3;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Language_Query_Test::SIP_Header_Content_Language_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_CONTENT_LANGUAGE)
{
    _header_query.emplace_back(QUERY_SET, "Language.pt", "", true);
    _header_query.emplace_back(QUERY_GET, "Language", "pt", true);
    _header_query.emplace_back(QUERY_SET, "Language.en", "", true);
    _header_query.emplace_back(QUERY_GET, "Language", "en", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Length_Decode_Encode_Test::SIP_Header_Content_Length_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_CONTENT_LENGTH;
    hdr1._input          = "Content-Length: 0";
    hdr1._output         = "Content-Length: 0\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_CONTENT_LENGTH;
    hdr2._input          = "Content-Length: 5678";
    hdr2._output         = "Content-Length: 5678\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_CONTENT_LENGTH;
    hdr3._input          = "l:50 ";
    hdr3._output         = "Content-Length: 50\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_CONTENT_LENGTH;
    hdr4._input          = "Content-Length:2147483647";
    hdr4._output         = "Content-Length: 2147483647\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_CONTENT_LENGTH;
    hdr5._input          = "l: 4294967294";
    hdr5._output         = "Content-Length: 4294967294\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6;
    hdr6._header_type    = SIP_HEADER_CONTENT_LENGTH;
    hdr6._input          = "Content-Length: 4294967295";
    hdr6._output         = "";
    hdr6._header_nb      = 0;
    hdr6._decode_success = false;
    hdr6._encode_success = false;
    _header_input_output.push_back(hdr6);

    SIP_Header_Input_Output hdr7;
    hdr7._header_type    = SIP_HEADER_CONTENT_LENGTH;
    hdr7._input          = "l: 4294967296";
    hdr7._output         = "";
    hdr7._header_nb      = 0;
    hdr7._decode_success = false;
    hdr7._encode_success = false;
    _header_input_output.push_back(hdr7);

    SIP_Header_Input_Output hdr8;
    hdr8._header_type    = SIP_HEADER_CONTENT_LENGTH;
    hdr8._input          = "Content-Length: 4294967297";
    hdr8._output         = "";
    hdr8._header_nb      = 0;
    hdr8._decode_success = false;
    hdr8._encode_success = false;
    _header_input_output.push_back(hdr8);

    SIP_Header_Input_Output hdr9;
    hdr9._header_type    = SIP_HEADER_CONTENT_LENGTH;
    hdr9._input          = "Content-Length: 6294967295";
    hdr9._output         = "";
    hdr9._header_nb      = 0;
    hdr9._decode_success = false;
    hdr9._encode_success = false;
    _header_input_output.push_back(hdr9);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Length_Query_Test::SIP_Header_Content_Length_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_CONTENT_LENGTH)
{
    _header_query.emplace_back(QUERY_SET, "Length.365", "", true);
    _header_query.emplace_back(QUERY_GET, "Length", "365", true);
    _header_query.emplace_back(QUERY_SET, "Length.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Length", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Type_Decode_Encode_Test::SIP_Header_Content_Type_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_CONTENT_TYPE;
    hdr1._input          = "Content-Type: application/sdp";
    hdr1._output         = "Content-Type: application/sdp\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_CONTENT_TYPE;
    hdr2._input          = "c: text/html; charset=ISO-8859-4";
    hdr2._output         = "Content-Type: text/html;charset=ISO-8859-4\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_CONTENT_TYPE;
    hdr3._input          = "Content-Type:type1/sub1  ;par1;par2  ;  par3 ";
    hdr3._output         = "Content-Type: type1/sub1;par1;par2;par3\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Type_Query_Test::SIP_Header_Content_Type_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_CONTENT_TYPE)
{
    _header_query.emplace_back(QUERY_SET, "Media-Type.Type.application", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Type.Type", "application", true);
    _header_query.emplace_back(QUERY_SET, "Media-Type.Type.text", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Type.Type", "text", true);
    _header_query.emplace_back(QUERY_SET, "Media-Type.Subtype.sdp", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Type.Subtype", "sdp", true);
    _header_query.emplace_back(QUERY_SET, "Media-Type.Subtype.html", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Type.Subtype", "html", true);
    _header_query.emplace_back(QUERY_SET, "Media-Type.Q.0.001", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Type.Q", "0.001", true);
    _header_query.emplace_back(QUERY_SET, "Media-Type.Q.1.000", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Type.Q", "1.000", true);
    _header_query.emplace_back(QUERY_ADD, "Media-Type.Parameters.0.charset=ISO-8859-4", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Type.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Media-Type.Parameters.0", "charset=ISO-8859-4", true);
    _header_query.emplace_back(QUERY_DEL, "Media-Type.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Media-Type.Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_CSeq_Decode_Encode_Test::SIP_Header_CSeq_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_CSEQ;
    hdr1._input          = "CSeq: 1 INVITE";
    hdr1._output         = "CSeq: 1 INVITE\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_CSEQ;
    hdr2._input          = "CSeq: 9876 TEST";
    hdr2._output         = "CSeq: 9876 TEST\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_CSEQ;
    hdr3._input          = "CSeq:0    ACK   ";
    hdr3._output         = "CSeq: 0 ACK\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_CSEQ;
    hdr4._input          = "CSeq: 4711 INVITE";
    hdr4._output         = "CSeq: 4711 INVITE\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_CSeq_Query_Test::SIP_Header_CSeq_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_CSEQ)
{
    _header_query.emplace_back(QUERY_SET, "Sequence.9876", "", true);
    _header_query.emplace_back(QUERY_GET, "Sequence", "9876", true);
    _header_query.emplace_back(QUERY_SET, "Sequence.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Sequence", "0", true);
    _header_query.emplace_back(QUERY_SET, "Method.INVITE", "", true);
    _header_query.emplace_back(QUERY_GET, "Method", "INVITE", true);
    _header_query.emplace_back(QUERY_SET, "Method.TEST", "", true);
    _header_query.emplace_back(QUERY_GET, "Method", "TEST", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Date_Decode_Encode_Test::SIP_Header_Date_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_DATE;
    hdr1._input          = "Date: Fri, 1 Oct 1990 00:10:59 GMT";
    hdr1._output         = "Date: Fri, 01 Oct 1990 00:10:59 GMT\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_DATE;
    hdr2._input          = "Date: Wed, 10 Feb 2001 23:00:20 GMT";
    hdr2._output         = "Date: Wed, 10 Feb 2001 23:00:20 GMT\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_DATE;
    hdr3._input          = "Date: Mon, 31 Dec 2010 12:59:05 GM";
    hdr3._output         = "Date: Mon, 31 Dec 2010 12:59:05 GM\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_DATE;
    hdr4._input          = "Date: Sat, 13 Nov 2010 23:29:00 GMT";
    hdr4._output         = "Date: Sat, 13 Nov 2010 23:29:00 GMT\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Date_Query_Test::SIP_Header_Date_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_DATE)
{
    _header_query.emplace_back(QUERY_SET, "Weekday.Fri", "", true);
    _header_query.emplace_back(QUERY_GET, "Weekday", "Fri", true);
    _header_query.emplace_back(QUERY_SET, "Day.13", "", true);
    _header_query.emplace_back(QUERY_GET, "Day", "13", true);
    _header_query.emplace_back(QUERY_SET, "Month.Nov", "", true);
    _header_query.emplace_back(QUERY_GET, "Month", "Nov", true);
    _header_query.emplace_back(QUERY_SET, "Year.2018", "", true);
    _header_query.emplace_back(QUERY_GET, "Year", "2018", true);
    _header_query.emplace_back(QUERY_SET, "Hour.12", "", true);
    _header_query.emplace_back(QUERY_GET, "Hour", "12", true);
    _header_query.emplace_back(QUERY_SET, "Minute.50", "", true);
    _header_query.emplace_back(QUERY_GET, "Minute", "50", true);
    _header_query.emplace_back(QUERY_SET, "Second.33", "", true);
    _header_query.emplace_back(QUERY_GET, "Second", "33", true);
    _header_query.emplace_back(QUERY_SET, "Time-Zone.GMT", "", true);
    _header_query.emplace_back(QUERY_GET, "Time-Zone", "GMT", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Error_Info_Decode_Encode_Test::SIP_Header_Error_Info_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_ERROR_INFO;
    hdr1._input          = "Error-Info: <sip:not-in-service-recording@atlanta.com>";
    hdr1._output         = "Error-Info: <sip:not-in-service-recording@atlanta.com>\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_ERROR_INFO;
    hdr2._input          = "Error-Info: <mailto:user@host.com;par1; par2 ;par3>;param1 ; param2 ;param3 , ";
    hdr2._input         += "<http://wwww.example.com/alice/photo.jpg>";
    hdr2._output         = "Error-Info: <mailto:user@host.com;par1; par2 ;par3>;param1;param2;param3, ";
    hdr2._output        += "<http://wwww.example.com/alice/photo.jpg>\r\n";
    hdr2._header_nb      = 2;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_ERROR_INFO;
    hdr3._input          = "Error-Info: <sips:user@host.com;par1> ; param1 ; param2 ;param3,<abc:user;par1> ; param2";
    hdr3._output         = "Error-Info: <sips:user@host.com;par1>;param1;param2;param3, <abc:user;par1>;param2\r\n";
    hdr3._header_nb      = 2;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Error_Info_Query_Test::SIP_Header_Error_Info_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_ERROR_INFO)
{
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name.Bob", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name", "Bob", true);
    _header_query.emplace_back(QUERY_SET, "Address.Scheme.mailto", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Scheme", "mailto", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User.bob", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User", "bob", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Password.mypass", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Password", "mypass", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Host.Address.host.com", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Host.Address", "host.com", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Port.7700", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Port", "7700", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Transport.UDP", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Transport", "UDP", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User-Param.phone", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User-Param", "phone", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Method.INFO", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Method", "INFO", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.TTL.1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.TTL", "1", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Multicast-Address.Address.1111::2222", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Multicast-Address.Address", "1111::2222", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "True", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Parameters.0.par1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.0", "par1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "0", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.par=1234", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "par=1234", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Event_Decode_Encode_Test::SIP_Header_Event_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_EVENT;
    hdr1._input          = "Event: presence";
    hdr1._output         = "Event: presence\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_EVENT;
    hdr2._input          = "Event: test; id=1234";
    hdr2._output         = "Event: test;id=1234\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_EVENT;
    hdr3._input          = "Event:  package.template1.template2  ; par1 ; id= 567 ;par2 ";
    hdr3._output         = "Event: package.template1.template2;id=567;par1;par2\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Event_Query_Test::SIP_Header_Event_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_EVENT)
{
    _header_query.emplace_back(QUERY_SET, "Event-Type.Package.presence", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Package", "presence", true);
    _header_query.emplace_back(QUERY_SET, "Event-Type.Package.package", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Package", "package", true);
    _header_query.emplace_back(QUERY_ADD, "Event-Type.Templates.0.template1", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.0", "template1", true);
    _header_query.emplace_back(QUERY_ADD, "Event-Type.Templates.1.template2", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.Size", "2", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.1", "template2", true);
    _header_query.emplace_back(QUERY_ADD, "Event-Type.Templates.0.template0", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.Size", "3", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.0", "template0", true);
    _header_query.emplace_back(QUERY_DEL, "Event-Type.Templates.2", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.Size", "2", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.0", "template0", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.1", "template1", true);
    _header_query.emplace_back(QUERY_DEL, "Event-Type.Templates.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.0", "template1", true);
    _header_query.emplace_back(QUERY_DEL, "Event-Type.Templates.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Event-Type.Templates.Size", "0", true);
    _header_query.emplace_back(QUERY_SET, "ID.1234", "", true);
    _header_query.emplace_back(QUERY_GET, "ID", "1234", true);
    _header_query.emplace_back(QUERY_SET, "ID.567", "", true);
    _header_query.emplace_back(QUERY_GET, "ID", "567", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.par=1234", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "par=1234", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Expires_Decode_Encode_Test::SIP_Header_Expires_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_EXPIRES;
    hdr1._input          = "Expires: 3600";
    hdr1._output         = "Expires: 3600\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_EXPIRES;
    hdr2._input          = "Expires: 0";
    hdr2._output         = "Expires: 0\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_EXPIRES;
    hdr3._input          = "Expires:    567890 ";
    hdr3._output         = "Expires: 567890\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_EXPIRES;
    hdr4._input          = "Expires: 4294967296";
    hdr4._output         = "";
    hdr4._header_nb      = 0;
    hdr4._decode_success = false;
    hdr4._encode_success = false;
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Expires_Query_Test::SIP_Header_Expires_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_EXPIRES)
{
    _header_query.emplace_back(QUERY_SET, "Expires.3600", "", true);
    _header_query.emplace_back(QUERY_GET, "Expires", "3600", true);
    _header_query.emplace_back(QUERY_SET, "Expires.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Expires", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_From_Decode_Encode_Test::SIP_Header_From_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_FROM;
    hdr1._input          = "From: Nikola Tesla <sip:n.tesla@high-voltage.org>;tag=76341";
    hdr1._output         = "From: Nikola Tesla <sip:n.tesla@high-voltage.org>;tag=76341\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_FROM;
    hdr2._input          = "f: Anonymous <sip:c8oqz84zk7z@privacy.org>";
    hdr2._output         = "From: Anonymous <sip:c8oqz84zk7z@privacy.org>\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_FROM;
    hdr3._input          = "From:  \"Nikola Tesla\"   <sip:n.tesla@high-voltage.org;par1 ;transport=tcp ; par2  ;par3>;parameter1;tag=76341 ";
    hdr3._output         = "From: \"Nikola Tesla\" <sip:n.tesla@high-voltage.org;transport=tcp;par1;par2;par3>;tag=76341;parameter1\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_FROM;
    hdr4._input          = "f: Anonymous <sip: c8oqz84zk7z:pass123@privacy.org;method=INVITE ? header=hdr1 & name=value&name2=value2>";
    hdr4._output         = "From: Anonymous <sip:c8oqz84zk7z:pass123@privacy.org;method=INVITE?header=hdr1&name=value&name2=value2>\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_FROM;
    hdr5._input          = "From: \"A. G. Bell\" <sip:agb@bell-telephone.com> ;tag=a48s";
    hdr5._output         = "From: \"A. G. Bell\" <sip:agb@bell-telephone.com>;tag=a48s\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6;
    hdr6._header_type    = SIP_HEADER_FROM;
    hdr6._input          = "From: sip:+12125551212@server.phone2net.com;tag=887s";
    hdr6._output         = "From: sip:+12125551212@server.phone2net.com;tag=887s\r\n";
    hdr6._header_nb      = 1;
    hdr6._decode_success = true;
    hdr6._encode_success = true;
    _header_input_output.push_back(hdr6);

    SIP_Header_Input_Output hdr7;
    hdr7._header_type    = SIP_HEADER_FROM;
    hdr7._input          = "From: Carlos <sip:[::1]:5060;par1;par2>;tag=76341";
    hdr7._output         = "From: Carlos <sip:[::1]:5060;par1;par2>;tag=76341\r\n";
    hdr7._header_nb      = 1;
    hdr7._decode_success = true;
    hdr7._encode_success = true;
    _header_input_output.push_back(hdr7);

    SIP_Header_Input_Output hdr8;
    hdr8._header_type    = SIP_HEADER_FROM;
    hdr8._input          = "From: sip:[fe80::10:0:0:10];tag=76341";
    hdr8._output         = "From: sip:[fe80::10:0:0:10];tag=76341\r\n";
    hdr8._header_nb      = 1;
    hdr8._decode_success = true;
    hdr8._encode_success = true;
    _header_input_output.push_back(hdr8);

    SIP_Header_Input_Output hdr9;
    hdr9._header_type    = SIP_HEADER_FROM;
    hdr9._input          = "f: \"Test 1\" <sip:[2001:2003:2004::] ; maddr= [1111:2:3333:44:5:6666:777:8] >;tag=123abc";
    hdr9._output         = "From: \"Test 1\" <sip:[2001:2003:2004::];maddr=[1111:2:3333:44:5:6666:777:8]>;tag=123abc\r\n";
    hdr9._header_nb      = 1;
    hdr9._decode_success = true;
    hdr9._encode_success = true;
    _header_input_output.push_back(hdr9);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_From_Query_Test::SIP_Header_From_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_FROM)
{
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name.User123", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name", "User123", true);
    _header_query.emplace_back(QUERY_SET, "Address.Scheme.sip", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Scheme", "sip", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User.test1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User", "test1", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Password.mypass", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Password", "mypass", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Host.Address.10.10.10.10", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Host.Address", "10.10.10.10", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Port.5000", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Port", "5000", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Transport.UDP", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Transport", "UDP", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User-Param.phone", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User-Param", "phone", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Method.INVITE", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Method", "INVITE", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.TTL.20", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.TTL", "20", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Multicast-Address.Address.1111::2222", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Multicast-Address.Address", "1111::2222", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "True", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Parameters.0.par1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.0", "par1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "0", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Headers.0.header1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.0", "header1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Headers.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "0", true);
    _header_query.emplace_back(QUERY_SET, "Address.Absolute-URI.Address.11.22.33.44", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Absolute-URI.Address", "11.22.33.44", true);
    _header_query.emplace_back(QUERY_SET, "Tag.83jewjd83", "", true);
    _header_query.emplace_back(QUERY_GET, "Tag", "83jewjd83", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.par1234", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "par1234", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_In_Reply_To_Decode_Encode_Test::SIP_Header_In_Reply_To_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_IN_REPLY_TO;
    hdr1._input          = "In-Reply-To: 70710@saturn.bell-tel.com, 17320@saturn.bell-tel.com";
    hdr1._output         = "In-Reply-To: 70710@saturn.bell-tel.com, 17320@saturn.bell-tel.com\r\n";
    hdr1._header_nb      = 2;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_IN_REPLY_TO;
    hdr2._input          = "In-Reply-To: 123456789";
    hdr2._output         = "In-Reply-To: 123456789\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_IN_REPLY_TO;
    hdr3._input          = "In-Reply-To:my-domain.org , test@domain.com:1234";
    hdr3._output         = "In-Reply-To: my-domain.org, test@domain.com:1234\r\n";
    hdr3._header_nb      = 2;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_In_Reply_To_Query_Test::SIP_Header_In_Reply_To_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_IN_REPLY_TO)
{
    _header_query.emplace_back(QUERY_SET, "Call-ID.17320@saturn.bell-tel.com", "", true);
    _header_query.emplace_back(QUERY_GET, "Call-ID", "17320@saturn.bell-tel.com", true);
    _header_query.emplace_back(QUERY_SET, "Call-ID.test@domain.com:1234", "", true);
    _header_query.emplace_back(QUERY_GET, "Call-ID", "test@domain.com:1234", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Max_Forwards_Decode_Encode_Test::SIP_Header_Max_Forwards_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_MAX_FORWARDS;
    hdr1._input          = "Max-Forwards: 70";
    hdr1._output         = "Max-Forwards: 70\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_MAX_FORWARDS;
    hdr2._input          = "Max-Forwards:   56789  ";
    hdr2._output         = "Max-Forwards: 56789\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_MAX_FORWARDS;
    hdr3._input          = "Max-Forwards:1";
    hdr3._output         = "Max-Forwards: 1\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_MAX_FORWARDS;
    hdr4._input          = "Max-Forwards: 65534";
    hdr4._output         = "Max-Forwards: 65534\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_MAX_FORWARDS;
    hdr5._input          = "Max-Forwards: 65535";
    hdr5._output         = "";
    hdr5._header_nb      = 0;
    hdr5._decode_success = false;
    hdr5._encode_success = false;
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6;
    hdr6._header_type    = SIP_HEADER_MAX_FORWARDS;
    hdr6._input          = "Max-Forwards: 65536";
    hdr6._output         = "";
    hdr6._header_nb      = 0;
    hdr6._decode_success = false;
    hdr6._encode_success = false;
    _header_input_output.push_back(hdr6);

    SIP_Header_Input_Output hdr7;
    hdr7._header_type    = SIP_HEADER_MAX_FORWARDS;
    hdr7._input          = "Max-Forwards: 268435455";
    hdr7._output         = "";
    hdr7._header_nb      = 0;
    hdr7._decode_success = false;
    hdr7._encode_success = false;
    _header_input_output.push_back(hdr7);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Max_Forwards_Query_Test::SIP_Header_Max_Forwards_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_MAX_FORWARDS)
{
    _header_query.emplace_back(QUERY_SET, "Max-Forwards.70", "", true);
    _header_query.emplace_back(QUERY_GET, "Max-Forwards", "70", true);
    _header_query.emplace_back(QUERY_SET, "Max-Forwards.1", "", true);
    _header_query.emplace_back(QUERY_GET, "Max-Forwards", "1", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Mime_Version_Decode_Encode_Test::SIP_Header_Mime_Version_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_MIME_VERSION;
    hdr1._input          = "MIME-Version: 1.0";
    hdr1._output         = "MIME-Version: 1.0\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_MIME_VERSION;
    hdr2._input          = "MIME-Version:   2.5  ";
    hdr2._output         = "MIME-Version: 2.5\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_MIME_VERSION;
    hdr3._input          = "MIME-Version:0.0";
    hdr3._output         = "MIME-Version: 0.0\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Mime_Version_Query_Test::SIP_Header_Mime_Version_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_MIME_VERSION)
{
    _header_query.emplace_back(QUERY_SET, "Major-Version.1", "", true);
    _header_query.emplace_back(QUERY_GET, "Major-Version", "1", true);
    _header_query.emplace_back(QUERY_SET, "Major-Version.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Major-Version", "0", true);
    _header_query.emplace_back(QUERY_SET, "Minor-Version.1", "", true);
    _header_query.emplace_back(QUERY_GET, "Minor-Version", "1", true);
    _header_query.emplace_back(QUERY_SET, "Minor-Version.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Minor-Version", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Min_Expires_Decode_Encode_Test::SIP_Header_Min_Expires_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_MIN_EXPIRES;
    hdr1._input          = "Min-Expires: 3600";
    hdr1._output         = "Min-Expires: 3600\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_MIN_EXPIRES;
    hdr2._input          = "Min-Expires:0";
    hdr2._output         = "Min-Expires: 0\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_MIN_EXPIRES;
    hdr3._input          = "Min-Expires:    567890 ";
    hdr3._output         = "Min-Expires: 567890\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_MIN_EXPIRES;
    hdr4._input          = "Min-Expires: 60";
    hdr4._output         = "Min-Expires: 60\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_MIN_EXPIRES;
    hdr5._input          = "Min-Expires: 7834990190";
    hdr5._output         = "";
    hdr5._header_nb      = 0;
    hdr5._decode_success = false;
    hdr5._encode_success = false;
    _header_input_output.push_back(hdr5);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Min_Expires_Query_Test::SIP_Header_Min_Expires_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_MIN_EXPIRES)
{
    _header_query.emplace_back(QUERY_SET, "Min-Expires.3600", "", true);
    _header_query.emplace_back(QUERY_GET, "Min-Expires", "3600", true);
    _header_query.emplace_back(QUERY_SET, "Min-Expires.120", "", true);
    _header_query.emplace_back(QUERY_GET, "Min-Expires", "120", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Organization_Decode_Encode_Test::SIP_Header_Organization_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_ORGANIZATION;
    hdr1._input          = "Organization: Boxes by Bob";
    hdr1._output         = "Organization: Boxes by Bob\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_ORGANIZATION;
    hdr2._input          = "Organization:";
    hdr2._output         = "Organization: \r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_ORGANIZATION;
    hdr3._input          = "Organization:   ABC ";
    hdr3._output         = "Organization: ABC\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_ORGANIZATION;
    hdr4._input          = "Organization:   ";
    hdr4._output         = "Organization: \r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Organization_Query_Test::SIP_Header_Organization_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_ORGANIZATION)
{
    _header_query.emplace_back(QUERY_SET, "Organization.Boxes by Bob", "", true);
    _header_query.emplace_back(QUERY_GET, "Organization", "Boxes by Bob", true);
    _header_query.emplace_back(QUERY_SET, "Organization.TEST", "", true);
    _header_query.emplace_back(QUERY_GET, "Organization", "TEST", true);
    _header_query.emplace_back(QUERY_SET, "Organization.", "", true);
    _header_query.emplace_back(QUERY_GET, "Organization", "", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Priority_Decode_Encode_Test::SIP_Header_Priority_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_PRIORITY;
    hdr1._input          = "Priority: normal";
    hdr1._output         = "Priority: normal\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_PRIORITY;
    hdr2._input          = "Priority:urgent  ";
    hdr2._output         = "Priority: urgent\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_PRIORITY;
    hdr3._input          = "Priority:my-priority";
    hdr3._output         = "Priority: my-priority\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_PRIORITY;
    hdr4._input          = "Priority: emergency";
    hdr4._output         = "Priority: emergency\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Priority_Query_Test::SIP_Header_Priority_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_PRIORITY)
{
    _header_query.emplace_back(QUERY_SET, "Priority.urgent", "", true);
    _header_query.emplace_back(QUERY_GET, "Priority", "urgent", true);
    _header_query.emplace_back(QUERY_SET, "Priority.normal", "", true);
    _header_query.emplace_back(QUERY_GET, "Priority", "normal", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Proxy_Authenticate_Decode_Encode_Test::SIP_Header_Proxy_Authenticate_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_PROXY_AUTHENTICATE;
    hdr1._input          = "Proxy-Authenticate: Digest realm=\"atlanta.com\", domain=\"sip:ss1.carrier.com\", qop=\"auth\", ";
    hdr1._input         += "nonce=\"f84f1cec41e6cbe5aea9c8e88d359\", opaque=\"\", stale=FALSE, algorithm=MD5";
    hdr1._output         = "Proxy-Authenticate: Digest realm=\"atlanta.com\", domain=\"sip:ss1.carrier.com\", ";
    hdr1._output        += "nonce=\"f84f1cec41e6cbe5aea9c8e88d359\", opaque=\"\", stale=FALSE, algorithm=MD5, qop=\"auth\"\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_PROXY_AUTHENTICATE;
    hdr2._input          = "Proxy-Authenticate: Digest realm=\"atlanta.example.com\",qop=\"auth\",   ";
    hdr2._input         += "nonce=\"wf84f1cczx41ae6cbeaea9ce88d359\",opaque=\"\",stale=FALSE,algorithm=MD5";
    hdr2._output         = "Proxy-Authenticate: Digest realm=\"atlanta.example.com\", ";
    hdr2._output        += "nonce=\"wf84f1cczx41ae6cbeaea9ce88d359\", opaque=\"\", stale=FALSE, algorithm=MD5, qop=\"auth\"\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_PROXY_AUTHENTICATE;
    hdr3._input          = "Proxy-Authenticate: Digest nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\" ,   realm=\"atlanta.example.com\"";
    hdr3._output         = "Proxy-Authenticate: Digest realm=\"atlanta.example.com\", nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\"\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_PROXY_AUTHENTICATE;
    hdr4._input          = "Proxy-Authenticate: Digest\trealm=\"myrealm.com\",nonce=\"123456789012345678901\", ";
    hdr4._input         += "domain=\"sip:myrealm.com\",algorithm=MD5";
    hdr4._output         = "Proxy-Authenticate: Digest realm=\"myrealm.com\", domain=\"sip:myrealm.com\", ";
    hdr4._output        += "nonce=\"123456789012345678901\", algorithm=MD5\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_PROXY_AUTHENTICATE;
    hdr5._input          = "Proxy-Authenticate: Scheme1 param1, param2=test, nonce=\"123456789012345678901\",";
    hdr5._input         += "realm=\"server.com\",domain=\"sip:server.com\",qop=\"auth, auth-int, value\", ";
    hdr5._input         += "opaque=\"11223344556677889900aabbccddeeff\", stale=true, par3=\"test\", algorithm=XYZ";
    hdr5._output         = "Proxy-Authenticate: Scheme1 realm=\"server.com\", domain=\"sip:server.com\", ";
    hdr5._output        += "nonce=\"123456789012345678901\", opaque=\"11223344556677889900aabbccddeeff\", stale=true, ";
    hdr5._output        += "algorithm=XYZ, qop=\"auth, auth-int, value\", param1, param2=test, par3=\"test\"\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6;
    hdr6._header_type    = SIP_HEADER_PROXY_AUTHENTICATE;
    hdr6._input          = "Proxy-Authenticate: scheme2 param1, param2=test,par3=\"test\"";
    hdr6._output         = "Proxy-Authenticate: scheme2 param1, param2=test, par3=\"test\"\r\n";
    hdr6._header_nb      = 1;
    hdr6._decode_success = true;
    hdr6._encode_success = true;
    _header_input_output.push_back(hdr6);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Proxy_Authenticate_Query_Test::SIP_Header_Proxy_Authenticate_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_PROXY_AUTHENTICATE)
{
    _header_query.emplace_back(QUERY_SET, "Challenge.Scheme.scheme1", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Scheme", "scheme1", true);
    _header_query.emplace_back(QUERY_SET, "Challenge.Realm.myrealm.com", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Realm", "myrealm.com", true);
    _header_query.emplace_back(QUERY_SET, "Challenge.Domain.sip:server.com", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Domain", "sip:server.com", true);
    _header_query.emplace_back(QUERY_SET, "Challenge.Nonce.123456789012345678901", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Nonce", "123456789012345678901", true);
    _header_query.emplace_back(QUERY_SET, "Challenge.Opaque.11223344556677889900aabbccddeeff", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Opaque", "11223344556677889900aabbccddeeff", true);
    _header_query.emplace_back(QUERY_SET, "Challenge.Stale.true", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Stale", "true", true);
    _header_query.emplace_back(QUERY_SET, "Challenge.Algorithm.MD5", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Algorithm", "MD5", true);
    _header_query.emplace_back(QUERY_SET, "Challenge.QoP.auth, auth-int, value", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.QoP", "auth, auth-int, value", true);
    _header_query.emplace_back(QUERY_ADD, "Challenge.Parameters.0.par1=test", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Parameters.0", "par1=test", true);
    _header_query.emplace_back(QUERY_DEL, "Challenge.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Proxy_Authorization_Decode_Encode_Test::SIP_Header_Proxy_Authorization_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_PROXY_AUTHORIZATION;
    hdr1._input          = "Proxy-Authorization: Digest username=\"Alice\", realm=\"atlanta.com\", ";
    hdr1._input         += "nonce=\"c60f3082ee1212b402a21831ae\", response=\"245f23415f11432b3434341c022\"";
    hdr1._output         = "Proxy-Authorization: Digest username=\"Alice\", realm=\"atlanta.com\", ";
    hdr1._output        += "nonce=\"c60f3082ee1212b402a21831ae\", response=\"245f23415f11432b3434341c022\"\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_PROXY_AUTHORIZATION;
    hdr2._input          = "Proxy-Authorization: Digest username=\"alice\",realm=\"atlanta.example.com\",   ";
    hdr2._input         += "nonce=\"wf84f1ceczx41ae6cbe5aea9c8e88d359\",opaque=\"\", uri=\"sip:bob@biloxi.example.com\", ";
    hdr2._input         += "response=\"42ce3cef44b22f50c6a6071bc8\"";
    hdr2._output         = "Proxy-Authorization: Digest username=\"alice\", realm=\"atlanta.example.com\", ";
    hdr2._output        += "nonce=\"wf84f1ceczx41ae6cbe5aea9c8e88d359\", uri=\"sip:bob@biloxi.example.com\", ";
    hdr2._output        += "response=\"42ce3cef44b22f50c6a6071bc8\", opaque=\"\"\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_PROXY_AUTHORIZATION;
    hdr3._input          = "Proxy-Authorization: Digest username=\"bob\",realm=\"atlanta.example.com\",";
    hdr3._input         += "nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\" ,   opaque=\"\",   ";
    hdr3._input         += "uri=\"sips:ss2.biloxi.example.com\",response=\"dfe56131d1958046689d83306477ecc\"";
    hdr3._output         = "Proxy-Authorization: Digest username=\"bob\", realm=\"atlanta.example.com\", ";
    hdr3._output        += "nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\", uri=\"sips:ss2.biloxi.example.com\", ";
    hdr3._output        += "response=\"dfe56131d1958046689d83306477ecc\", opaque=\"\"\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_PROXY_AUTHORIZATION;
    hdr4._input          = "Proxy-Authorization: Digest\tusername=\"name\",realm=\"myrealm.com\",nonce=\"123456789012345678901\",";
    hdr4._input         += "uri=\"sip:myrealm.com\",response=\"12345678901234567890123456789012\",algorithm=MD5";
    hdr4._output         = "Proxy-Authorization: Digest username=\"name\", realm=\"myrealm.com\", nonce=\"123456789012345678901\", ";
    hdr4._output        += "uri=\"sip:myrealm.com\", response=\"12345678901234567890123456789012\", algorithm=MD5\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_PROXY_AUTHORIZATION;
    hdr5._input          = "Proxy-Authorization: Scheme1 param1, param2=test, nonce=\"123456789012345678901\",realm=\"server.com\",";
    hdr5._input         += "response=\"12345678901234567890123456789012\", username=\"1234\", uri=\"sip:server.com\",qop=auth, ";
    hdr5._input         += "nc=00000001, cnonce=\"0a4f113b\", opaque=\"11223344556677889900aabbccddeeff\", par3=\"test\", algorithm=XYZ";
    hdr5._output         = "Proxy-Authorization: Scheme1 username=\"1234\", realm=\"server.com\", nonce=\"123456789012345678901\", ";
    hdr5._output        += "uri=\"sip:server.com\", response=\"12345678901234567890123456789012\", algorithm=XYZ, cnonce=\"0a4f113b\", ";
    hdr5._output        += "opaque=\"11223344556677889900aabbccddeeff\", qop=auth, nc=00000001, param1, param2=test, par3=\"test\"\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6;
    hdr6._header_type    = SIP_HEADER_PROXY_AUTHORIZATION;
    hdr6._input          = "Proxy-Authorization: scheme2 param1, param2=test,par3=\"test\"";
    hdr6._output         = "Proxy-Authorization: scheme2 param1, param2=test, par3=\"test\"\r\n";
    hdr6._header_nb      = 1;
    hdr6._decode_success = true;
    hdr6._encode_success = true;
    _header_input_output.push_back(hdr6);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Proxy_Authorization_Query_Test::SIP_Header_Proxy_Authorization_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_PROXY_AUTHORIZATION)
{
    _header_query.emplace_back(QUERY_SET, "Credential.Scheme.scheme1", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Scheme", "scheme1", true);
    _header_query.emplace_back(QUERY_SET, "Credential.Username.1234", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Username", "1234", true);
    _header_query.emplace_back(QUERY_SET, "Credential.Realm.myrealm.com", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Realm", "myrealm.com", true);
    _header_query.emplace_back(QUERY_SET, "Credential.Nonce.123456789012345678901", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Nonce", "123456789012345678901", true);
    _header_query.emplace_back(QUERY_SET, "Credential.URI.sip:myrealm.com", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.URI", "sip:myrealm.com", true);
    _header_query.emplace_back(QUERY_SET, "Credential.Response.12345678901234567890123456789012", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Response", "12345678901234567890123456789012", true);
    _header_query.emplace_back(QUERY_SET, "Credential.Algorithm.MD5", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Algorithm", "MD5", true);
    _header_query.emplace_back(QUERY_SET, "Credential.CNonce.0a4f113b", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.CNonce", "0a4f113b", true);
    _header_query.emplace_back(QUERY_SET, "Credential.Opaque.11223344556677889900aabbccddeeff", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Opaque", "11223344556677889900aabbccddeeff", true);
    _header_query.emplace_back(QUERY_SET, "Credential.QoP.auth", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.QoP", "auth", true);
    _header_query.emplace_back(QUERY_SET, "Credential.Nonce-Count.00000001", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Nonce-Count", "00000001", true);
    _header_query.emplace_back(QUERY_ADD, "Credential.Parameters.0.param1", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Parameters.0", "param1", true);
    _header_query.emplace_back(QUERY_DEL, "Credential.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Credential.Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Proxy_Require_Decode_Encode_Test::SIP_Header_Proxy_Require_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_PROXY_REQUIRE;
    hdr1._input          = "Proxy-Require: foo";
    hdr1._output         = "Proxy-Require: foo\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_PROXY_REQUIRE;
    hdr2._input          = "Proxy-Require: req1, req2,req3";
    hdr2._output         = "Proxy-Require: req1, req2, req3\r\n";
    hdr2._header_nb      = 3;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_PROXY_REQUIRE;
    hdr3._input          = "Proxy-Require:req1,req2";
    hdr3._output         = "Proxy-Require: req1, req2\r\n";
    hdr3._header_nb      = 2;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Proxy_Require_Query_Test::SIP_Header_Proxy_Require_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_PROXY_REQUIRE)
{
    _header_query.emplace_back(QUERY_SET, "Option-Tag.foo", "", true);
    _header_query.emplace_back(QUERY_GET, "Option-Tag", "foo", true);
    _header_query.emplace_back(QUERY_SET, "Option-Tag.req1", "", true);
    _header_query.emplace_back(QUERY_GET, "Option-Tag", "req1", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_RAck_Decode_Encode_Test::SIP_Header_RAck_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_RACK;
    hdr1._input          = "RAck: 776656 1 INVITE";
    hdr1._output         = "RAck: 776656 1 INVITE\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_RACK;
    hdr2._input          = "RAck:1   23456    INVITE  ";
    hdr2._output         = "RAck: 1 23456 INVITE\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_RACK;
    hdr3._input          = "RAck:   349940055  99988877   INVITE";
    hdr3._output         = "RAck: 349940055 99988877 INVITE\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_RAck_Query_Test::SIP_Header_RAck_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_RACK)
{
    _header_query.emplace_back(QUERY_SET, "RSeq.776656", "", true);
    _header_query.emplace_back(QUERY_GET, "RSeq", "776656", true);
    _header_query.emplace_back(QUERY_SET, "RSeq.349940055", "", true);
    _header_query.emplace_back(QUERY_GET, "RSeq", "349940055", true);
    _header_query.emplace_back(QUERY_SET, "CSeq.1", "", true);
    _header_query.emplace_back(QUERY_GET, "CSeq", "1", true);
    _header_query.emplace_back(QUERY_SET, "CSeq.23456", "", true);
    _header_query.emplace_back(QUERY_GET, "CSeq", "23456", true);
    _header_query.emplace_back(QUERY_SET, "Method.INVITE", "", true);
    _header_query.emplace_back(QUERY_GET, "Method", "INVITE", true);
    _header_query.emplace_back(QUERY_SET, "Method.TEST", "", true);
    _header_query.emplace_back(QUERY_GET, "Method", "TEST", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Record_Route_Decode_Encode_Test::SIP_Header_Record_Route_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_RECORD_ROUTE;
    hdr1._input          = "Record-Route: <sip:server10.biloxi.com;lr>, <sip:bigbox3.site3.atlanta.com;lr>";
    hdr1._output         = "Record-Route: <sip:server10.biloxi.com;lr>\r\nRecord-Route: <sip:bigbox3.site3.atlanta.com;lr>\r\n";
    hdr1._header_nb      = 2;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_RECORD_ROUTE;
    hdr2._input          = "Record-Route:   <sip:user@server10.biloxi.com;par1;user= phone >;parameter1, ";
    hdr2._input         += "<sip:bigbox3.site3.atlanta.com;par1;lr;par2>";
    hdr2._output         = "Record-Route: <sip:user@server10.biloxi.com;user=phone;par1>;parameter1\r\n";
    hdr2._output        += "Record-Route: <sip:bigbox3.site3.atlanta.com;lr;par1;par2>\r\n";
    hdr2._header_nb      = 2;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_RECORD_ROUTE;
    hdr3._input          = "Record-Route: <sip:n.tesla@high-voltage.org;par1 ; maddr= 10.0.0.10 ; par2  ;par3> ;  parameter1;parameter2 , ";
    hdr3._input         += "<sip:c8oqz84zk7z@privacy.org> ; parameter1";
    hdr3._output         = "Record-Route: <sip:n.tesla@high-voltage.org;maddr=10.0.0.10;par1;par2;par3>;parameter1;parameter2\r\n";
    hdr3._output        += "Record-Route: <sip:c8oqz84zk7z@privacy.org>;parameter1\r\n";
    hdr3._header_nb      = 2;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_RECORD_ROUTE;
    hdr4._input          = "Record-Route: <sip:[1111:2222::3333];lr ; maddr= [fe80::1]>, <sip:[9999::]:5060;lr>";
    hdr4._output         = "Record-Route: <sip:[1111:2222::3333];maddr=[fe80::1];lr>\r\nRecord-Route: <sip:[9999::]:5060;lr>\r\n";
    hdr4._header_nb      = 2;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Record_Route_Query_Test::SIP_Header_Record_Route_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_RECORD_ROUTE)
{
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name.User123", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name", "User123", true);
    _header_query.emplace_back(QUERY_SET, "Address.Scheme.sip", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Scheme", "sip", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User.test1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User", "test1", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Password.mypass", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Password", "mypass", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Host.Address.10.10.10.10", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Host.Address", "10.10.10.10", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Port.5000", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Port", "5000", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Transport.UDP", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Transport", "UDP", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User-Param.phone", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User-Param", "phone", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Method.INVITE", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Method", "INVITE", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.TTL.20", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.TTL", "20", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Multicast-Address.Address.1111::2222", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Multicast-Address.Address", "1111::2222", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "True", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Parameters.0.par1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.0", "par1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "0", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Headers.0.header1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.0", "header1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Headers.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "0", true);
    _header_query.emplace_back(QUERY_SET, "Address.Absolute-URI.Address.11.22.33.44", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Absolute-URI.Address", "11.22.33.44", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.par1234", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "par1234", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Refer_To_Decode_Encode_Test::SIP_Header_Refer_To_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_REFER_TO;
    hdr1._input          = "Refer-To: sip:alice@atlanta.example.com";
    hdr1._output         = "Refer-To: sip:alice@atlanta.example.com\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_REFER_TO;
    hdr2._input          = "Refer-To: <sip:bob@biloxi.example.net?Accept-Contact=sip:bobsdesk.biloxi.example.net";
    hdr2._input         += "&Call-ID%3D55432%40alicepc.atlanta.example.com>";
    hdr2._output         = "Refer-To: <sip:bob@biloxi.example.net?Accept-Contact=sip:bobsdesk.biloxi.example.net";
    hdr2._output        += "&Call-ID%3D55432%40alicepc.atlanta.example.com>\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_REFER_TO;
    hdr3._input          = "Refer-To: <sip:dave@denver.example.org?Replaces=12345%40192.168.118.3%3Bto-tag%3D12345";
    hdr3._input         += "%3Bfrom-tag%3D5FFE-3994>";
    hdr3._output         = "Refer-To: <sip:dave@denver.example.org?Replaces=12345%40192.168.118.3%3Bto-tag%3D12345";
    hdr3._output        += "%3Bfrom-tag%3D5FFE-3994>\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_REFER_TO;
    hdr4._input          = "Refer-To: <sip:carol@cleveland.example.org;method=SUBSCRIBE>";
    hdr4._output         = "Refer-To: <sip:carol@cleveland.example.org;method=SUBSCRIBE>\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_REFER_TO;
    hdr5._input          = "Refer-To: http://www.ietf.org";
    hdr5._output         = "Refer-To: http://www.ietf.org\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6;
    hdr6._header_type    = SIP_HEADER_REFER_TO;
    hdr6._input          = "Refer-To: sip:+12125551212@server.phone2net.com;par=123";
    hdr6._output         = "Refer-To: sip:+12125551212@server.phone2net.com;par=123\r\n";
    hdr6._header_nb      = 1;
    hdr6._decode_success = true;
    hdr6._encode_success = true;
    _header_input_output.push_back(hdr6);

    SIP_Header_Input_Output hdr7;
    hdr7._header_type    = SIP_HEADER_REFER_TO;
    hdr7._input          = "Refer-To: <sip:user:password@server.phone2net.com ; par=123> ; parameter1 ;parameter2=123";
    hdr7._output         = "Refer-To: <sip:user:password@server.phone2net.com;par=123>;parameter1;parameter2=123\r\n";
    hdr7._header_nb      = 1;
    hdr7._decode_success = true;
    hdr7._encode_success = true;
    _header_input_output.push_back(hdr7);

    SIP_Header_Input_Output hdr8;
    hdr8._header_type    = SIP_HEADER_REFER_TO;
    hdr8._input          = "Refer-To: sip:alice@[::1234]";
    hdr8._output         = "Refer-To: sip:alice@[::1234]\r\n";
    hdr8._header_nb      = 1;
    hdr8._decode_success = true;
    hdr8._encode_success = true;
    _header_input_output.push_back(hdr8);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Refer_To_Query_Test::SIP_Header_Refer_To_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_REFER_TO)
{
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name.User123", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name", "User123", true);
    _header_query.emplace_back(QUERY_SET, "Address.Scheme.sip", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Scheme", "sip", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User.test1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User", "test1", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Password.mypass", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Password", "mypass", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Host.Address.10.10.10.10", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Host.Address", "10.10.10.10", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Port.5000", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Port", "5000", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Transport.UDP", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Transport", "UDP", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User-Param.phone", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User-Param", "phone", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Method.INVITE", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Method", "INVITE", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.TTL.20", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.TTL", "20", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Multicast-Address.Address.1111::2222", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Multicast-Address.Address", "1111::2222", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "True", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Parameters.0.par1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.0", "par1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "0", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Headers.0.header1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.0", "header1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Headers.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "0", true);
    _header_query.emplace_back(QUERY_SET, "Address.Absolute-URI.Address.11.22.33.44", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Absolute-URI.Address", "11.22.33.44", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.par1234", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "par1234", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Referred_By_Decode_Encode_Test::SIP_Header_Referred_By_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_REFERRED_BY;
    hdr1._input          = "Referred-By:sip:r@ref.example;cid=\"2UWQFN309shb3@ref.example\"";
    hdr1._output         = "Referred-By: sip:r@ref.example;cid=\"2UWQFN309shb3@ref.example\"\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_REFERRED_BY;
    hdr2._input          = "Referred-By: <sip:referrer@referrer.example>;cid=\"20398823.2UWQFN309shb3@referrer.example\"";
    hdr2._output         = "Referred-By: <sip:referrer@referrer.example>;cid=\"20398823.2UWQFN309shb3@referrer.example\"\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_REFERRED_BY;
    hdr3._input          = "Referred-By: <sip:referrer@referrer.example>";
    hdr3._output         = "Referred-By: <sip:referrer@referrer.example>\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_REFERRED_BY;
    hdr4._input          = "Referred-By:   <sip:A.example>; par1=test; cid=\"23094202342.10123091233@A.example\"; par2";
    hdr4._output         = "Referred-By: <sip:A.example>;cid=\"23094202342.10123091233@A.example\";par1=test;par2\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_REFERRED_BY;
    hdr5._input          = "Referred-By: http://www.ietf.org";
    hdr5._output         = "Referred-By: http://www.ietf.org\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6;
    hdr6._header_type    = SIP_HEADER_REFERRED_BY;
    hdr6._input          = "Referred-By: sip:+12345@server.phone2net.com;par=123;par2;cid=\"abc@123\"";
    hdr6._output         = "Referred-By: sip:+12345@server.phone2net.com;cid=\"abc@123\";par=123;par2\r\n";
    hdr6._header_nb      = 1;
    hdr6._decode_success = true;
    hdr6._encode_success = true;
    _header_input_output.push_back(hdr6);

    SIP_Header_Input_Output hdr7;
    hdr7._header_type    = SIP_HEADER_REFERRED_BY;
    hdr7._input          = "Referred-By: <sip:user:password@server.phone2net.com ; par=123> ; parameter1 ;parameter2=123";
    hdr7._output         = "Referred-By: <sip:user:password@server.phone2net.com;par=123>;parameter1;parameter2=123\r\n";
    hdr7._header_nb      = 1;
    hdr7._decode_success = true;
    hdr7._encode_success = true;
    _header_input_output.push_back(hdr7);

    SIP_Header_Input_Output hdr8;
    hdr8._header_type    = SIP_HEADER_REFERRED_BY;
    hdr8._input          = "Referred-By: sip:+12345@[1234:5678:9012:3456::7890]:9988 ;par=123 ; par2  ;  cid=\"abc@123\"";
    hdr8._output         = "Referred-By: sip:+12345@[1234:5678:9012:3456::7890]:9988;cid=\"abc@123\";par=123;par2\r\n";
    hdr8._header_nb      = 1;
    hdr8._decode_success = true;
    hdr8._encode_success = true;
    _header_input_output.push_back(hdr8);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Referred_By_Query_Test::SIP_Header_Referred_By_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_REFERRED_BY)
{
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name.User123", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name", "User123", true);
    _header_query.emplace_back(QUERY_SET, "Address.Scheme.sip", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Scheme", "sip", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User.test1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User", "test1", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Password.mypass", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Password", "mypass", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Host.Address.10.10.10.10", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Host.Address", "10.10.10.10", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Port.5000", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Port", "5000", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Transport.UDP", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Transport", "UDP", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User-Param.phone", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User-Param", "phone", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Method.INVITE", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Method", "INVITE", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.TTL.20", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.TTL", "20", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Multicast-Address.Address.1111::2222", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Multicast-Address.Address", "1111::2222", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "True", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Parameters.0.par1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.0", "par1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "0", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Headers.0.header1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.0", "header1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Headers.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "0", true);
    _header_query.emplace_back(QUERY_SET, "Address.Absolute-URI.Address.11.22.33.44", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Absolute-URI.Address", "11.22.33.44", true);
    _header_query.emplace_back(QUERY_SET, "CID.2UWQFN309shb3@ref.example", "", true);
    _header_query.emplace_back(QUERY_GET, "CID", "2UWQFN309shb3@ref.example", true);
    _header_query.emplace_back(QUERY_SET, "CID.abc@123", "", true);
    _header_query.emplace_back(QUERY_GET, "CID", "abc@123", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.par1234", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "par1234", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Reply_To_Decode_Encode_Test::SIP_Header_Reply_To_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_REPLY_TO;
    hdr1._input          = "Reply-To: Bob <sip:bob@biloxi.com>";
    hdr1._output         = "Reply-To: Bob <sip:bob@biloxi.com>\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_REPLY_TO;
    hdr2._input          = "Reply-To:   <sip:user@server10.biloxi.com;par1;user= phone >;parameter1";
    hdr2._output         = "Reply-To: <sip:user@server10.biloxi.com;user=phone;par1>;parameter1\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_REPLY_TO;
    hdr3._input          = "Reply-To: <sip:n.tesla@high-voltage.org;par1 ; maddr= 10.0.0.10 ; par2  ;ttl=70;par3> ;  parameter1;parameter2 ";
    hdr3._output         = "Reply-To: <sip:n.tesla@high-voltage.org;ttl=70;maddr=10.0.0.10;par1;par2;par3>;parameter1;parameter2\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_REPLY_TO;
    hdr4._input          = "Reply-To: sip:bob@[::1] ; par1; par2";
    hdr4._output         = "Reply-To: sip:bob@[::1];par1;par2\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Reply_To_Query_Test::SIP_Header_Reply_To_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_REPLY_TO)
{
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name.User123", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name", "User123", true);
    _header_query.emplace_back(QUERY_SET, "Address.Scheme.sip", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Scheme", "sip", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User.test1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User", "test1", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Password.mypass", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Password", "mypass", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Host.Address.10.10.10.10", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Host.Address", "10.10.10.10", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Port.5000", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Port", "5000", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Transport.UDP", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Transport", "UDP", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User-Param.phone", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User-Param", "phone", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Method.INVITE", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Method", "INVITE", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.TTL.20", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.TTL", "20", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Multicast-Address.Address.1111::2222", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Multicast-Address.Address", "1111::2222", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "True", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Parameters.0.par1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.0", "par1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "0", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Headers.0.header1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.0", "header1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Headers.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "0", true);
    _header_query.emplace_back(QUERY_SET, "Address.Absolute-URI.Address.11.22.33.44", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Absolute-URI.Address", "11.22.33.44", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.par1234", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "par1234", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Require_Decode_Encode_Test::SIP_Header_Require_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_REQUIRE;
    hdr1._input          = "Require: foo";
    hdr1._output         = "Require: foo\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_REQUIRE;
    hdr2._input          = "Require: req1, req2,req3";
    hdr2._output         = "Require: req1, req2, req3\r\n";
    hdr2._header_nb      = 3;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_REQUIRE;
    hdr3._input          = "Require:req1,req2";
    hdr3._output         = "Require: req1, req2\r\n";
    hdr3._header_nb      = 2;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_REQUIRE;
    hdr4._input          = "Require: 100rel";
    hdr4._output         = "Require: 100rel\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Require_Query_Test::SIP_Header_Require_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_REQUIRE)
{
    _header_query.emplace_back(QUERY_SET, "Option-Tag.foo", "", true);
    _header_query.emplace_back(QUERY_GET, "Option-Tag", "foo", true);
    _header_query.emplace_back(QUERY_SET, "Option-Tag.100rel", "", true);
    _header_query.emplace_back(QUERY_GET, "Option-Tag", "100rel", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Retry_After_Decode_Encode_Test::SIP_Header_Retry_After_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_RETRY_AFTER;
    hdr1._input          = "Retry-After: 18000;duration=3600";
    hdr1._output         = "Retry-After: 18000;duration=3600\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_RETRY_AFTER;
    hdr2._input          = "Retry-After: 120 (I'm in a meeting)";
    hdr2._output         = "Retry-After: 120 (I'm in a meeting)\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_RETRY_AFTER;
    hdr3._input          = "Retry-After:10( I'm in a meeting );par1=test;duration= 100 ; par2";
    hdr3._output         = "Retry-After: 10 ( I'm in a meeting );duration=100;par1=test;par2\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_RETRY_AFTER;
    hdr4._input          = "Retry-After: 99999999 (This (\"is a\") comment); par1";
    hdr4._output         = "Retry-After: 99999999 (This (\"is a\") comment);par1\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Retry_After_Query_Test::SIP_Header_Retry_After_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_RETRY_AFTER)
{
    _header_query.emplace_back(QUERY_SET, "Retry-After.18000", "", true);
    _header_query.emplace_back(QUERY_GET, "Retry-After", "18000", true);
    _header_query.emplace_back(QUERY_SET, "Retry-After.10", "", true);
    _header_query.emplace_back(QUERY_GET, "Retry-After", "10", true);
    _header_query.emplace_back(QUERY_SET, "Comment.I'm in a meeting", "", true);
    _header_query.emplace_back(QUERY_GET, "Comment", "I'm in a meeting", true);
    _header_query.emplace_back(QUERY_SET, "Comment.This (\"is a\") comment", "", true);
    _header_query.emplace_back(QUERY_GET, "Comment", "This (\"is a\") comment", true);
    _header_query.emplace_back(QUERY_SET, "Duration.3600", "", true);
    _header_query.emplace_back(QUERY_GET, "Duration", "3600", true);
    _header_query.emplace_back(QUERY_SET, "Duration.100", "", true);
    _header_query.emplace_back(QUERY_GET, "Duration", "100", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.parameter=test", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "parameter=test", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Route_Decode_Encode_Test::SIP_Header_Route_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_ROUTE;
    hdr1._input          = "Route: <sip:bigbox3.site3.atlanta.com;lr>, <sip:server10.biloxi.com;lr>";
    hdr1._output         = "Route: <sip:bigbox3.site3.atlanta.com;lr>\r\nRoute: <sip:server10.biloxi.com;lr>\r\n";
    hdr1._header_nb      = 2;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_ROUTE;
    hdr2._input          = "Route: <sip:server13.atlanta.com;lr>";
    hdr2._output         = "Route: <sip:server13.atlanta.com;lr>\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_ROUTE;
    hdr3._input          = "Route:   <sip:server1.atlanta.com ; transport=udp ; user=phone  ;  lr > ";
    hdr3._output         = "Route: <sip:server1.atlanta.com;transport=udp;user=phone;lr>\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_ROUTE;
    hdr4._input          = "Route: <sip:server2.atlanta.com;transport=udp;user=phone>;lr";
    hdr4._output         = "Route: <sip:server2.atlanta.com;transport=udp;user=phone>;lr\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_ROUTE;
    hdr5._input          = "Route: <sip:server3.atlanta.com ; transport=udp;lr?header=hdr1& name=value > ; teste ; lr ";
    hdr5._output         = "Route: <sip:server3.atlanta.com;transport=udp;lr?header=hdr1&name=value>;teste;lr\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6;
    hdr6._header_type    = SIP_HEADER_ROUTE;
    hdr6._input          = "Route: <sip:[fe80::7788:1122:333]:5060 ; transport=udp ; user=phone>";
    hdr6._output         = "Route: <sip:[fe80::7788:1122:333]:5060;transport=udp;user=phone>\r\n";
    hdr6._header_nb      = 1;
    hdr6._decode_success = true;
    hdr6._encode_success = true;
    _header_input_output.push_back(hdr6);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Route_Query_Test::SIP_Header_Route_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_ROUTE)
{
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name.User123", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name", "User123", true);
    _header_query.emplace_back(QUERY_SET, "Address.Scheme.sip", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Scheme", "sip", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User.test1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User", "test1", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Password.mypass", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Password", "mypass", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Host.Address.10.10.10.10", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Host.Address", "10.10.10.10", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Port.5000", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Port", "5000", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Transport.UDP", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Transport", "UDP", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User-Param.phone", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User-Param", "phone", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Method.INVITE", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Method", "INVITE", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.TTL.20", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.TTL", "20", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Multicast-Address.Address.1111::2222", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Multicast-Address.Address", "1111::2222", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "True", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Parameters.0.par1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.0", "par1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "0", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Headers.0.header1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.0", "header1", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Headers.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "0", true);
    _header_query.emplace_back(QUERY_SET, "Address.Absolute-URI.Address.11.22.33.44", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Absolute-URI.Address", "11.22.33.44", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.par1234", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "par1234", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_RSeq_Decode_Encode_Test::SIP_Header_RSeq_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_RSEQ;
    hdr1._input          = "RSeq: 988789";
    hdr1._output         = "RSeq: 988789\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_RSEQ;
    hdr2._input          = "RSeq:1";
    hdr2._output         = "RSeq: 1\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_RSEQ;
    hdr3._input          = "RSeq:   349940055  ";
    hdr3._output         = "RSeq: 349940055\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_RSeq_Query_Test::SIP_Header_RSeq_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_RSEQ)
{
    _header_query.emplace_back(QUERY_SET, "RSeq.988789", "", true);
    _header_query.emplace_back(QUERY_GET, "RSeq", "988789", true);
    _header_query.emplace_back(QUERY_SET, "RSeq.349940055", "", true);
    _header_query.emplace_back(QUERY_GET, "RSeq", "349940055", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Server_Decode_Encode_Test::SIP_Header_Server_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_SERVER;
    hdr1._input          = "Server: HomeServer v2";
    hdr1._output         = "Server: HomeServer v2\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_SERVER;
    hdr2._input          = "Server:My Server/1.5.0 Pro";
    hdr2._output         = "Server: My Server/1.5.0 Pro\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_SERVER;
    hdr3._input          = "Server:  server1 ";
    hdr3._output         = "Server: server1\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Server_Query_Test::SIP_Header_Server_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_SERVER)
{
    _header_query.emplace_back(QUERY_SET, "Server.HomeServer v2", "", true);
    _header_query.emplace_back(QUERY_GET, "Server", "HomeServer v2", true);
    _header_query.emplace_back(QUERY_SET, "Server.My Server/1.5.0 Pro", "", true);
    _header_query.emplace_back(QUERY_GET, "Server", "My Server/1.5.0 Pro", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Subject_Decode_Encode_Test::SIP_Header_Subject_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_SUBJECT;
    hdr1._input          = "Subject : lunch";
    hdr1._output         = "Subject: lunch\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_SUBJECT;
    hdr2._input          = "Subject:Need more boxes ";
    hdr2._output         = "Subject: Need more boxes\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_SUBJECT;
    hdr3._input          = "s: Tech Support ";
    hdr3._output         = "Subject: Tech Support\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_SUBJECT;
    hdr4._input          = "s:";
    hdr4._output         = "Subject: \r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Subject_Query_Test::SIP_Header_Subject_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_SUBJECT)
{
    _header_query.emplace_back(QUERY_SET, "Subject.lunch", "", true);
    _header_query.emplace_back(QUERY_GET, "Subject", "lunch", true);
    _header_query.emplace_back(QUERY_SET, "Subject.Need more boxes", "", true);
    _header_query.emplace_back(QUERY_GET, "Subject", "Need more boxes", true);
    _header_query.emplace_back(QUERY_SET, "Subject.", "", true);
    _header_query.emplace_back(QUERY_GET, "Subject", "", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Subscription_State_Decode_Encode_Test::SIP_Header_Subscription_State_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_SUBSCRIPTION_STATE;
    hdr1._input          = "Subscription-State: active;expires=600";
    hdr1._output         = "Subscription-State: active;expires=600\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_SUBSCRIPTION_STATE;
    hdr2._input          = "Subscription-State: state1 ; expires= 500";
    hdr2._output         = "Subscription-State: state1;expires=500\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_SUBSCRIPTION_STATE;
    hdr3._input          = "Subscription-State: terminated; reason=timeout ; retry-after=400 ";
    hdr3._output         = "Subscription-State: terminated;reason=timeout;retry-after=400\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_SUBSCRIPTION_STATE;
    hdr4._input          = "Subscription-State: pending; expires= 500 ; retry-after=9999 ;reason=deactivated ";
    hdr4._output         = "Subscription-State: pending;reason=deactivated;expires=500;retry-after=9999\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_SUBSCRIPTION_STATE;
    hdr5._input          = "Subscription-State: state; reason=giveup  ";
    hdr5._output         = "Subscription-State: state;reason=giveup\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6;
    hdr6._header_type    = SIP_HEADER_SUBSCRIPTION_STATE;
    hdr6._input          = "Subscription-State:active";
    hdr6._output         = "Subscription-State: active\r\n";
    hdr6._header_nb      = 1;
    hdr6._decode_success = true;
    hdr6._encode_success = true;
    _header_input_output.push_back(hdr6);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Subscription_State_Query_Test::SIP_Header_Subscription_State_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_SUBSCRIPTION_STATE)
{
    _header_query.emplace_back(QUERY_SET, "State.active", "", true);
    _header_query.emplace_back(QUERY_GET, "State", "active", true);
    _header_query.emplace_back(QUERY_SET, "State.terminated", "", true);
    _header_query.emplace_back(QUERY_GET, "State", "terminated", true);
    _header_query.emplace_back(QUERY_SET, "Reason.timeout", "", true);
    _header_query.emplace_back(QUERY_GET, "Reason", "timeout", true);
    _header_query.emplace_back(QUERY_SET, "Reason.giveup", "", true);
    _header_query.emplace_back(QUERY_GET, "Reason", "giveup", true);
    _header_query.emplace_back(QUERY_SET, "Expires.600", "", true);
    _header_query.emplace_back(QUERY_GET, "Expires", "600", true);
    _header_query.emplace_back(QUERY_SET, "Expires.100", "", true);
    _header_query.emplace_back(QUERY_GET, "Expires", "100", true);
    _header_query.emplace_back(QUERY_SET, "Retry-After.9999", "", true);
    _header_query.emplace_back(QUERY_GET, "Retry-After", "9999", true);
    _header_query.emplace_back(QUERY_SET, "Retry-After.666", "", true);
    _header_query.emplace_back(QUERY_GET, "Retry-After", "666", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.parameter=111", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "parameter=111", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Supported_Decode_Encode_Test::SIP_Header_Supported_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_SUPPORTED;
    hdr1._input          = "Supported: 100rel, foo";
    hdr1._output         = "Supported: 100rel, foo\r\n";
    hdr1._header_nb      = 2;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_SUPPORTED;
    hdr2._input          = "Supported:foo1";
    hdr2._output         = "Supported: foo1\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_SUPPORTED;
    hdr3._input          = "Supported: 100rel, foo, bar  ";
    hdr3._output         = "Supported: 100rel, foo, bar\r\n";
    hdr3._header_nb      = 3;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_SUPPORTED;
    hdr4._input          = "k:";
    hdr4._output         = "Supported: \r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_SUPPORTED;
    hdr5._input          = "Supported: 100rel";
    hdr5._output         = "Supported: 100rel\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Supported_Query_Test::SIP_Header_Supported_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_SUPPORTED)
{
    _header_query.emplace_back(QUERY_SET, "Option-Tag.foo", "", true);
    _header_query.emplace_back(QUERY_GET, "Option-Tag", "foo", true);
    _header_query.emplace_back(QUERY_SET, "Option-Tag.100rel", "", true);
    _header_query.emplace_back(QUERY_GET, "Option-Tag", "100rel", true);
    _header_query.emplace_back(QUERY_SET, "Option-Tag.", "", true);
    _header_query.emplace_back(QUERY_GET, "Option-Tag", "", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Timestamp_Decode_Encode_Test::SIP_Header_Timestamp_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_TIMESTAMP;
    hdr1._input          = "Timestamp: 54";
    hdr1._output         = "Timestamp: 54\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_TIMESTAMP;
    hdr2._input          = "Timestamp:10.20";
    hdr2._output         = "Timestamp: 10.20\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_TIMESTAMP;
    hdr3._input          = "Timestamp: 10.20   7.90  ";
    hdr3._output         = "Timestamp: 10.20 7.90\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_TIMESTAMP;
    hdr4._input          = "Timestamp: 99.88\t77.666  ";
    hdr4._output         = "Timestamp: 99.88 77.666\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_TIMESTAMP;
    hdr5._input          = "Timestamp: 12345678901234.1001  \t \t 55666778899.123  ";
    hdr5._output         = "Timestamp: 12345678901234.1001 55666778899.123\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Timestamp_Query_Test::SIP_Header_Timestamp_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_TIMESTAMP)
{
    _header_query.emplace_back(QUERY_SET, "Timestamp.10.20", "", true);
    _header_query.emplace_back(QUERY_GET, "Timestamp", "10.20", true);
    _header_query.emplace_back(QUERY_SET, "Timestamp.12345678901234.1001", "", true);
    _header_query.emplace_back(QUERY_GET, "Timestamp", "12345678901234.1001", true);
    _header_query.emplace_back(QUERY_SET, "Delay.77.666", "", true);
    _header_query.emplace_back(QUERY_GET, "Delay", "77.666", true);
    _header_query.emplace_back(QUERY_SET, "Delay.55666778899.123", "", true);
    _header_query.emplace_back(QUERY_GET, "Delay", "55666778899.123", true);
    _header_query.emplace_back(QUERY_SET, "Delay.", "", true);
    _header_query.emplace_back(QUERY_GET, "Delay", "", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_To_Decode_Encode_Test::SIP_Header_To_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_TO;
    hdr1._input          = "To: G. Marconi <sip:Marconi@radio.org>";
    hdr1._output         = "To: G. Marconi <sip:Marconi@radio.org>\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_TO;
    hdr2._input          = "t: sip:+12125551212@server.phone2net.com;tag=287447";
    hdr2._output         = "To: sip:+12125551212@server.phone2net.com;tag=287447\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_TO;
    hdr3._input          = "To: \" Name  \" <sip:+12125551212@server.phone2net.com ;par1 ;par2> ; tag=287447;parameter1 ";
    hdr3._output         = "To: \"Name\" <sip:+12125551212@server.phone2net.com;par1;par2>;tag=287447;parameter1\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_TO;
    hdr4._input          = "To: <sip:server.phone2net.com ;par1 ; lr ; maddr= 10.10.10.10 ;ttl=20; method= BYE; ";
    hdr4._input         += "user=ip;transport= udp ;par2> ; tag=287447;parameter1 ";
    hdr4._output         = "To: <sip:server.phone2net.com;transport=udp;user=ip;method=BYE;ttl=20";
    hdr4._output        += ";maddr=10.10.10.10;lr;par1;par2>;tag=287447;parameter1\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_TO;
    hdr5._input          = "To: The Operator <sip:operator@cs.columbia.edu>;tag=287447";
    hdr5._output         = "To: The Operator <sip:operator@cs.columbia.edu>;tag=287447\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6;
    hdr6._header_type    = SIP_HEADER_TO;
    hdr6._input          = "To: \"  \" <sip:operator:123456@cs.columbia.edu ; par1> ; par2";
    hdr6._output         = "To: <sip:operator:123456@cs.columbia.edu;par1>;par2\r\n";
    hdr6._header_nb      = 1;
    hdr6._decode_success = true;
    hdr6._encode_success = true;
    _header_input_output.push_back(hdr6);

    SIP_Header_Input_Output hdr7;
    hdr7._header_type    = SIP_HEADER_TO;
    hdr7._input          = "To: G. Marconi <sip:Marconi@[1111:2222:3333:4444:5555:6666:7777:8888];maddr=[fe80::10fe:234f]>";
    hdr7._output         = "To: G. Marconi <sip:Marconi@[1111:2222:3333:4444:5555:6666:7777:8888];maddr=[fe80::10fe:234f]>\r\n";
    hdr7._header_nb      = 1;
    hdr7._decode_success = true;
    hdr7._encode_success = true;
    _header_input_output.push_back(hdr7);

    SIP_Header_Input_Output hdr8;
    hdr8._header_type    = SIP_HEADER_TO;
    hdr8._input          = "To: sip:[2001:0db8:85a3:08d3:1319:8a2e:0370:7344]:5060;par1>;par2";
    hdr8._output         = "To: sip:[2001:0db8:85a3:08d3:1319:8a2e:0370:7344]:5060;par1>;par2\r\n";
    hdr8._header_nb      = 1;
    hdr8._decode_success = true;
    hdr8._encode_success = true;
    _header_input_output.push_back(hdr8);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_To_Query_Test::SIP_Header_To_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_TO)
{
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name-Double-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name-Double-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.Display-Name.Test User", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Display-Name", "Test User", true);
    _header_query.emplace_back(QUERY_SET, "Address.Scheme.tel", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Scheme", "tel", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.URI-Angle-Quote.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.URI-Angle-Quote", "True", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User.test1", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User", "test1", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Password.mypass", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Password", "mypass", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Host.Address.10.10.10.10", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Host.Address", "10.10.10.10", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Port.65000", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Port", "65000", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Transport.TCP", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Transport", "TCP", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.User-Param.phone", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.User-Param", "phone", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Method.BYE", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Method", "BYE", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.TTL.2", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.TTL", "2", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.Multicast-Address.Address.1111::2222", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Multicast-Address.Address", "1111::2222", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.False", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "False", true);
    _header_query.emplace_back(QUERY_SET, "Address.SIP-URI.LR.True", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.LR", "True", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Parameters.0.transport=tcp", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.0", "transport=tcp", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Parameters.Size", "0", true);
    _header_query.emplace_back(QUERY_ADD, "Address.SIP-URI.Headers.0.header1=test", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.0", "header1=test", true);
    _header_query.emplace_back(QUERY_DEL, "Address.SIP-URI.Headers.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.SIP-URI.Headers.Size", "0", true);
    _header_query.emplace_back(QUERY_SET, "Address.Absolute-URI.Address.192.168.1.240", "", true);
    _header_query.emplace_back(QUERY_GET, "Address.Absolute-URI.Address", "192.168.1.240", true);
    _header_query.emplace_back(QUERY_SET, "Tag.jd3939dk", "", true);
    _header_query.emplace_back(QUERY_GET, "Tag", "jd3939dk", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.par1=1234", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "par1=1234", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Unknown_Decode_Encode_Test::SIP_Header_Unknown_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_UNKNOWN;
    hdr1._input          = "X-Header: abc def";
    hdr1._output         = "X-Header: abc def\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_UNKNOWN;
    hdr2._input          = "Newheader:123456  ";
    hdr2._output         = "Newheader: 123456\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_UNKNOWN;
    hdr3._input          = "Unknown: foo, bar, xyz";
    hdr3._output         = "Unknown: foo, bar, xyz\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Unknown_Query_Test::SIP_Header_Unknown_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_UNKNOWN)
{
    _header_query.emplace_back(QUERY_SET, "Header.X-Header", "", true);
    _header_query.emplace_back(QUERY_GET, "Header", "X-Header", true);
    _header_query.emplace_back(QUERY_SET, "Header.Unknown", "", true);
    _header_query.emplace_back(QUERY_GET, "Header", "Unknown", true);
    _header_query.emplace_back(QUERY_SET, "Value.foo, bar, xyz", "", true);
    _header_query.emplace_back(QUERY_GET, "Value", "foo, bar, xyz", true);
    _header_query.emplace_back(QUERY_SET, "Value.123456", "", true);
    _header_query.emplace_back(QUERY_GET, "Value", "123456", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Unsupported_Decode_Encode_Test::SIP_Header_Unsupported_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_UNSUPPORTED;
    hdr1._input          = "Unsupported: 100rel, foo";
    hdr1._output         = "Unsupported: 100rel, foo\r\n";
    hdr1._header_nb      = 2;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_UNSUPPORTED;
    hdr2._input          = "Unsupported:foo1";
    hdr2._output         = "Unsupported: foo1\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_UNSUPPORTED;
    hdr3._input          = "Unsupported: 100rel, foo, bar  ";
    hdr3._output         = "Unsupported: 100rel, foo, bar\r\n";
    hdr3._header_nb      = 3;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Unsupported_Query_Test::SIP_Header_Unsupported_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_UNSUPPORTED)
{
    _header_query.emplace_back(QUERY_SET, "Option-Tag.foo", "", true);
    _header_query.emplace_back(QUERY_GET, "Option-Tag", "foo", true);
    _header_query.emplace_back(QUERY_SET, "Option-Tag.100rel", "", true);
    _header_query.emplace_back(QUERY_GET, "Option-Tag", "100rel", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_User_Agent_Decode_Encode_Test::SIP_Header_User_Agent_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_USER_AGENT;
    hdr1._input          = "User-Agent: Softphone Beta1.5";
    hdr1._output         = "User-Agent: Softphone Beta1.5\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_USER_AGENT;
    hdr2._input          = "User-Agent:UA/1.5.0 Pro";
    hdr2._output         = "User-Agent: UA/1.5.0 Pro\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_USER_AGENT;
    hdr3._input          = "User-Agent:  user agent 1 ";
    hdr3._output         = "User-Agent: user agent 1\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_User_Agent_Query_Test::SIP_Header_User_Agent_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_USER_AGENT)
{
    _header_query.emplace_back(QUERY_SET, "User-Agent.Softphone Beta1.5", "", true);
    _header_query.emplace_back(QUERY_GET, "User-Agent", "Softphone Beta1.5", true);
    _header_query.emplace_back(QUERY_SET, "User-Agent.UA/1.5.0 Pro", "", true);
    _header_query.emplace_back(QUERY_GET, "User-Agent", "UA/1.5.0 Pro", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Via_Decode_Encode_Test::SIP_Header_Via_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_VIA;
    hdr1._input          = "Via: SIP/2.0/UDP lab.high-voltage.org:5060;branch=z9hG4bKfw19b";
    hdr1._output         = "Via: SIP/2.0/UDP lab.high-voltage.org:5060;branch=z9hG4bKfw19b\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_VIA;
    hdr2._input          = "Via: SIP / 2.0 / UDP first.example.com: 4000  ;par1;maddr=224.2.0.1 ;ttl=16;branch=z9hG4bKa7c6a8dlze.1, ";
    hdr2._input         += "SIP/2.0/UDP first.example.com";
    hdr2._output         = "Via: SIP/2.0/UDP first.example.com:4000;branch=z9hG4bKa7c6a8dlze.1;ttl=16;maddr=224.2.0.1;par1\r\n";
    hdr2._output        += "Via: SIP/2.0/UDP first.example.com\r\n";
    hdr2._header_nb      = 2;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_VIA;
    hdr3._input          = "v: SIP/2.0/UDP lab.high-voltage.org;received=10.10.10.10;branch=z9hG4bKfw19b,";
    hdr3._input         += "SIP/2.0/UDP 11.11.11.11:5070;branch=z9hG4bKfw19b;parameter1 ";
    hdr3._output         = "Via: SIP/2.0/UDP lab.high-voltage.org;branch=z9hG4bKfw19b;received=10.10.10.10\r\n";
    hdr3._output        += "Via: SIP/2.0/UDP 11.11.11.11:5070;branch=z9hG4bKfw19b;parameter1\r\n";
    hdr3._header_nb      = 2;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_VIA;
    hdr4._input          = "Via: SIP/2.0/UDP erlang.bell-telephone.com:5060;branch=z9hG4bK87asdks7";
    hdr4._output         = "Via: SIP/2.0/UDP erlang.bell-telephone.com:5060;branch=z9hG4bK87asdks7\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_VIA;
    hdr5._input          = "Via: SIP/2.0/UDP 192.0.2.1:5060 ;received=192.0.2.207;branch=z9hG4bK77asjd";
    hdr5._output         = "Via: SIP/2.0/UDP 192.0.2.1:5060;branch=z9hG4bK77asjd;received=192.0.2.207\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6;
    hdr6._header_type    = SIP_HEADER_VIA;
    hdr6._input          = "Via: SIP / 2.0 / UDP first.example.com: 4000;ttl=16 ;maddr=224.2.0.1 ;branch=z9hG4bKa7c6a8dlze.1";
    hdr6._output         = "Via: SIP/2.0/UDP first.example.com:4000;branch=z9hG4bKa7c6a8dlze.1;ttl=16;maddr=224.2.0.1\r\n";
    hdr6._header_nb      = 1;
    hdr6._decode_success = true;
    hdr6._encode_success = true;
    _header_input_output.push_back(hdr6);

    SIP_Header_Input_Output hdr7;
    hdr7._header_type    = SIP_HEADER_VIA;
    hdr7._input          = "Via: SIP / 2.0 / UDP [fe80::2345:6789]: 4002;ttl=16 ;maddr=[::1] ;branch=z9hG4bKa7c6a8dlze.1";
    hdr7._output         = "Via: SIP/2.0/UDP [fe80::2345:6789]:4002;branch=z9hG4bKa7c6a8dlze.1;ttl=16;maddr=[::1]\r\n";
    hdr7._header_nb      = 1;
    hdr7._decode_success = true;
    hdr7._encode_success = true;
    _header_input_output.push_back(hdr7);

    SIP_Header_Input_Output hdr8;
    hdr8._header_type    = SIP_HEADER_VIA;
    hdr8._input          = "Via: SIP/2.0/UDP [2001:1111:2222::5555] ;branch=z9hG4bKa767890fds";
    hdr8._output         = "Via: SIP/2.0/UDP [2001:1111:2222::5555];branch=z9hG4bKa767890fds\r\n";
    hdr8._header_nb      = 1;
    hdr8._decode_success = true;
    hdr8._encode_success = true;
    _header_input_output.push_back(hdr8);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Via_Query_Test::SIP_Header_Via_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_VIA)
{
    _header_query.emplace_back(QUERY_SET, "Protocol-Name.SIP", "", true);
    _header_query.emplace_back(QUERY_GET, "Protocol-Name", "SIP", true);
    _header_query.emplace_back(QUERY_SET, "Protocol-Version.2.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Protocol-Version", "2.0", true);
    _header_query.emplace_back(QUERY_SET, "Transport.TLS", "", true);
    _header_query.emplace_back(QUERY_GET, "Transport", "TLS", true);
    _header_query.emplace_back(QUERY_SET, "Host.Address.1111:2222:33::5555", "", true);
    _header_query.emplace_back(QUERY_GET, "Host.Address", "1111:2222:33::5555", true);
    _header_query.emplace_back(QUERY_SET, "Host.Address.10.0.10.2", "", true);
    _header_query.emplace_back(QUERY_GET, "Host.Address", "10.0.10.2", true);
    _header_query.emplace_back(QUERY_SET, "Port.12345", "", true);
    _header_query.emplace_back(QUERY_GET, "Port", "12345", true);
    _header_query.emplace_back(QUERY_SET, "Branch.z9hG4bKKw83ur", "", true);
    _header_query.emplace_back(QUERY_GET, "Branch", "z9hG4bKKw83ur", true);
    _header_query.emplace_back(QUERY_SET, "Received.1111:2222:33::5555", "", true);
    _header_query.emplace_back(QUERY_GET, "Received", "1111:2222:33::5555", true);
    _header_query.emplace_back(QUERY_SET, "TTL.40", "", true);
    _header_query.emplace_back(QUERY_GET, "TTL", "40", true);
    _header_query.emplace_back(QUERY_SET, "Multicast-Address.Address.1234:5678:90::999", "", true);
    _header_query.emplace_back(QUERY_GET, "Multicast-Address.Address", "1234:5678:90::999", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.parameter1", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "parameter1", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.1.par2=test", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "2", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.1", "par2=test", true);
    _header_query.emplace_back(QUERY_ADD, "Parameters.0.parameter0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "3", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "parameter0", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "parameter0", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.1", "parameter1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.2", "par2=test", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.1", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "2", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "parameter0", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.1", "par2=test", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.0", "par2=test", true);
    _header_query.emplace_back(QUERY_DEL, "Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Parameters.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Warning_Decode_Encode_Test::SIP_Header_Warning_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_WARNING;
    hdr1._input          = "Warning: 370 devnull \"Choose a bigger pipe\"";
    hdr1._output         = "Warning: 370 devnull \"Choose a bigger pipe\"\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_WARNING;
    hdr2._input          = "Warning: 307 isi.edu \"Session parameter ’foo’ not understood\", ";
    hdr2._input         += "301 isi.edu \"Incompatible network address type ’E.164’\"";
    hdr2._output         = "Warning: 307 isi.edu \"Session parameter ’foo’ not understood\"\r\n";
    hdr2._output        += "Warning: 301 isi.edu \"Incompatible network address type ’E.164’\"\r\n";
    hdr2._header_nb      = 2;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_WARNING;
    hdr3._input          = "Warning:  600 10.10.10.10 \"text\" ";
    hdr3._output         = "Warning: 600 10.10.10.10 \"text\"\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Warning_Query_Test::SIP_Header_Warning_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_WARNING)
{
    _header_query.emplace_back(QUERY_SET, "Code.307", "", true);
    _header_query.emplace_back(QUERY_GET, "Code", "307", true);
    _header_query.emplace_back(QUERY_SET, "Code.370", "", true);
    _header_query.emplace_back(QUERY_GET, "Code", "370", true);
    _header_query.emplace_back(QUERY_SET, "Agent.isi.edu", "", true);
    _header_query.emplace_back(QUERY_GET, "Agent", "isi.edu", true);
    _header_query.emplace_back(QUERY_SET, "Agent.devnull", "", true);
    _header_query.emplace_back(QUERY_GET, "Agent", "devnull", true);
    _header_query.emplace_back(QUERY_SET, "Text.Session parameter 'foo' not understood", "", true);
    _header_query.emplace_back(QUERY_GET, "Text", "Session parameter 'foo' not understood", true);
    _header_query.emplace_back(QUERY_SET, "Text.Choose a bigger pipe", "", true);
    _header_query.emplace_back(QUERY_GET, "Text", "Choose a bigger pipe", true);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_WWW_Authenticate_Decode_Encode_Test::SIP_Header_WWW_Authenticate_Decode_Encode_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_WWW_AUTHENTICATE;
    hdr1._input          = "WWW-Authenticate: Digest realm=\"atlanta.com\", domain=\"sip:boxesbybob.com\", qop=\"auth\", ";
    hdr1._input         += "nonce=\"f84f1cec41e6cbe5aea9c8e88d359\", opaque=\"\", stale=FALSE, algorithm=MD5";
    hdr1._output         = "WWW-Authenticate: Digest realm=\"atlanta.com\", domain=\"sip:boxesbybob.com\", ";
    hdr1._output        += "nonce=\"f84f1cec41e6cbe5aea9c8e88d359\", opaque=\"\", stale=FALSE, algorithm=MD5, qop=\"auth\"\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_WWW_AUTHENTICATE;
    hdr2._input          = "WWW-Authenticate: Digest realm=\"biloxi.com\",qop=\"auth,auth-int\",  ";
    hdr2._input         += "nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\",opaque=\"5ccc069c403ebaf9f0171e9517f40e41\"";
    hdr2._output         = "WWW-Authenticate: Digest realm=\"biloxi.com\", nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\", ";
    hdr2._output        += "opaque=\"5ccc069c403ebaf9f0171e9517f40e41\", qop=\"auth,auth-int\"\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_WWW_AUTHENTICATE;
    hdr3._input          = "WWW-Authenticate: Digest nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\" ,   realm=\"atlanta.example.com\"";
    hdr3._output         = "WWW-Authenticate: Digest realm=\"atlanta.example.com\", nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\"\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_WWW_AUTHENTICATE;
    hdr4._input          = "WWW-Authenticate: Digest\trealm=\"myrealm.com\",nonce=\"123456789012345678901\", ";
    hdr4._input         += "domain=\"sip:myrealm.com\",algorithm=MD5";
    hdr4._output         = "WWW-Authenticate: Digest realm=\"myrealm.com\", domain=\"sip:myrealm.com\", ";
    hdr4._output        += "nonce=\"123456789012345678901\", algorithm=MD5\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_WWW_AUTHENTICATE;
    hdr5._input          = "WWW-Authenticate: Scheme1 param1, param2=test, nonce=\"123456789012345678901\",";
    hdr5._input         += "realm=\"server.com\",domain=\"sip:server.com\",qop=\"auth, auth-int, value\", ";
    hdr5._input         += "opaque=\"11223344556677889900aabbccddeeff\", stale=true, par3=\"test\", algorithm=XYZ";
    hdr5._output         = "WWW-Authenticate: Scheme1 realm=\"server.com\", domain=\"sip:server.com\", ";
    hdr5._output        += "nonce=\"123456789012345678901\", opaque=\"11223344556677889900aabbccddeeff\", stale=true, ";
    hdr5._output        += "algorithm=XYZ, qop=\"auth, auth-int, value\", param1, param2=test, par3=\"test\"\r\n";
    hdr5._header_nb      = 1;
    hdr5._decode_success = true;
    hdr5._encode_success = true;
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6;
    hdr6._header_type    = SIP_HEADER_WWW_AUTHENTICATE;
    hdr6._input          = "WWW-Authenticate: scheme2 param1, param2=test,par3=\"test\"";
    hdr6._output         = "WWW-Authenticate: scheme2 param1, param2=test, par3=\"test\"\r\n";
    hdr6._header_nb      = 1;
    hdr6._decode_success = true;
    hdr6._encode_success = true;
    _header_input_output.push_back(hdr6);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_WWW_Authenticate_Query_Test::SIP_Header_WWW_Authenticate_Query_Test() : SIP_Header_Query_Test(SIP_HEADER_WWW_AUTHENTICATE)
{
    _header_query.emplace_back(QUERY_SET, "Challenge.Scheme.scheme1", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Scheme", "scheme1", true);
    _header_query.emplace_back(QUERY_SET, "Challenge.Realm.myrealm.com", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Realm", "myrealm.com", true);
    _header_query.emplace_back(QUERY_SET, "Challenge.Domain.sip:server.com", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Domain", "sip:server.com", true);
    _header_query.emplace_back(QUERY_SET, "Challenge.Nonce.123456789012345678901", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Nonce", "123456789012345678901", true);
    _header_query.emplace_back(QUERY_SET, "Challenge.Opaque.11223344556677889900aabbccddeeff", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Opaque", "11223344556677889900aabbccddeeff", true);
    _header_query.emplace_back(QUERY_SET, "Challenge.Stale.true", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Stale", "true", true);
    _header_query.emplace_back(QUERY_SET, "Challenge.Algorithm.MD5", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Algorithm", "MD5", true);
    _header_query.emplace_back(QUERY_SET, "Challenge.QoP.auth, auth-int, value", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.QoP", "auth, auth-int, value", true);
    _header_query.emplace_back(QUERY_ADD, "Challenge.Parameters.0.par1=test", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Parameters.Size", "1", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Parameters.0", "par1=test", true);
    _header_query.emplace_back(QUERY_DEL, "Challenge.Parameters.0", "", true);
    _header_query.emplace_back(QUERY_GET, "Challenge.Parameters.Size", "0", true);
}

//-------------------------------------------
