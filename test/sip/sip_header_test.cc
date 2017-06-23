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

    SIP_Header_Accept_Test header_accept;
    if (!header_accept.run())
        return false;

    SIP_Header_Accept_Encoding_Test header_accept_encoding;
    if (!header_accept_encoding.run())
        return false;

    SIP_Header_Accept_Language_Test header_accept_language;
    if (!header_accept_language.run())
        return false;

    SIP_Header_Alert_Info_Test header_alert_info;
    if (!header_alert_info.run())
        return false;

    SIP_Header_Allow_Test header_allow;
    if (!header_allow.run())
        return false;

    SIP_Header_Allow_Events_Test header_allow_events;
    if (!header_allow_events.run())
        return false;

    SIP_Header_Authentication_Info_Test header_authentication_info;
    if (!header_authentication_info.run())
        return false;

    SIP_Header_Authorization_Test header_authorization;
    if (!header_authorization.run())
        return false;

    SIP_Header_Call_ID_Test header_call_id;
    if (!header_call_id.run())
        return false;

    SIP_Header_Call_Info_Test header_call_info;
    if (!header_call_info.run())
        return false;

    SIP_Header_Contact_Test header_contact;
    if (!header_contact.run())
        return false;

    SIP_Header_Content_Disposition_Test header_content_disposition;
    if (!header_content_disposition.run())
        return false;

    SIP_Header_Content_Encoding_Test header_content_encoding;
    if (!header_content_encoding.run())
        return false;

    SIP_Header_Content_Language_Test header_content_language;
    if (!header_content_language.run())
        return false;

    SIP_Header_Content_Length_Test header_content_length;
    if (!header_content_length.run())
        return false;

    SIP_Header_Content_Type_Test header_content_type;
    if (!header_content_type.run())
        return false;

    SIP_Header_CSeq_Test header_cseq;
    if (!header_cseq.run())
        return false;

    SIP_Header_Date_Test header_date;
    if (!header_date.run())
        return false;

    SIP_Header_Error_Info_Test header_error_info;
    if (!header_error_info.run())
        return false;

    SIP_Header_Event_Test header_event;
    if (!header_event.run())
        return false;

    SIP_Header_Expires_Test header_expires;
    if (!header_expires.run())
        return false;

    SIP_Header_From_Test header_from;
    if (!header_from.run())
        return false;

    SIP_Header_In_Reply_To_Test header_in_reply_to;
    if (!header_in_reply_to.run())
        return false;

    SIP_Header_Max_Forwards_Test header_max_forwards;
    if (!header_max_forwards.run())
        return false;

    SIP_Header_Mime_Version_Test header_mime_version;
    if (!header_mime_version.run())
        return false;

    SIP_Header_Min_Expires_Test header_min_expires;
    if (!header_min_expires.run())
        return false;

    SIP_Header_Organization_Test header_organization;
    if (!header_organization.run())
        return false;

    SIP_Header_Priority_Test header_priority;
    if (!header_priority.run())
        return false;

    SIP_Header_Proxy_Authenticate_Test header_proxy_authenticate;
    if (!header_proxy_authenticate.run())
        return false;

    SIP_Header_Proxy_Authorization_Test header_proxy_authorization;
    if (!header_proxy_authorization.run())
        return false;

    SIP_Header_Proxy_Require_Test header_proxy_require;
    if (!header_proxy_require.run())
        return false;

    SIP_Header_Record_Route_Test header_record_route;
    if (!header_record_route.run())
        return false;

    SIP_Header_Reply_To_Test header_reply_to;
    if (!header_reply_to.run())
        return false;

    SIP_Header_Require_Test header_require;
    if (!header_require.run())
        return false;

    SIP_Header_Retry_After_Test header_retry_after;
    if (!header_retry_after.run())
        return false;

    SIP_Header_Route_Test header_route;
    if (!header_route.run())
        return false;

    SIP_Header_Server_Test header_server;
    if (!header_server.run())
        return false;

    SIP_Header_Subject_Test header_subject;
    if (!header_subject.run())
        return false;

    SIP_Header_Subscription_State_Test header_subscription_state;
    if (!header_subscription_state.run())
        return false;

    SIP_Header_Supported_Test header_supported;
    if (!header_supported.run())
        return false;

    SIP_Header_Timestamp_Test header_timestamp;
    if (!header_timestamp.run())
        return false;

    SIP_Header_To_Test header_to;
    if (!header_to.run())
        return false;

    SIP_Header_Unsupported_Test header_unsupported;
    if (!header_unsupported.run())
        return false;

    SIP_Header_User_Agent_Test header_user_agent;
    if (!header_user_agent.run())
        return false;

    SIP_Header_Via_Test header_via;
    if (!header_via.run())
        return false;

    SIP_Header_Warning_Test header_warning;
    if (!header_warning.run())
        return false;

    SIP_Header_WWW_Authenticate_Test header_www_authenticate;
    if (!header_www_authenticate.run())
        return false;

    std::cout << "SIP header test completed successfully\n";
    return true;
}

//-------------------------------------------

bool SIP_Header_Test::run()
{
    std::list<SIP_Header_Input_Output>::iterator it = _header_input_output.begin();
    while (it != _header_input_output.end())
    {
        SIP_Header_Input_Output header_input_output = *it++;

        std::map<SIP_Header_Type, std::list<SIP_Header *>> headers;

        std::string input = header_input_output._input;
        bool decode = SIP_Header::decode_headers(input, headers);

        if (header_input_output._decode_success != decode)
        {
            std::cout << "SIP_Header_Test::run -> Failed to decode headers:\n";
            std::cout << std::setw(12) << "Type: " << header_input_output._header_type << "\n";
            std::cout << std::setw(12) << "Input: " << header_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << (header_input_output._decode_success ? "true" : "false") << "\n";
            std::cout << std::setw(12) << "Success: " << (decode ? "true" : "false") << "\n";
            return false;
        }

        if (!decode)
        {
            clear(headers);
            continue;
        }

        unsigned short size = (headers.count(header_input_output._header_type) ?
            (unsigned short) headers.at(header_input_output._header_type).size() : 0);

        if (header_input_output._header_nb != size)
        {
            std::cout << "SIP_Header_Test::run -> Invalid size of headers:\n";
            std::cout << std::setw(12) << "Type: " << header_input_output._header_type << "\n";
            std::cout << std::setw(12) << "Input: " << header_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << header_input_output._header_nb << "\n";
            std::cout << std::setw(12) << "Size: " << size << "\n";
            return false;
        }

        std::string output;
        bool encode = SIP_Header::encode_headers(output, headers);

        if (header_input_output._encode_success != encode)
        {
            std::cout << "SIP_Header_Test::run -> Failed to encode headers:\n";
            std::cout << std::setw(12) << "Type: " << header_input_output._header_type << "\n";
            std::cout << std::setw(12) << "Input: " << header_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << (header_input_output._encode_success ? "true" : "false") << "\n";
            std::cout << std::setw(12) << "Success: " << (encode ? "true" : "false") << "\n";
            return false;
        }

        if (!encode)
        {
            clear(headers);
            continue;
        }

        if (output != header_input_output._output)
        {
            std::cout << "SIP_Header_Test::run -> Invalid encoded header:\n";
            std::cout << std::setw(12) << "Type: " << header_input_output._header_type << "\n";
            std::cout << std::setw(12) << "Input: " << header_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << header_input_output._output.c_str() << "\n";
            std::cout << std::setw(12) << "Output: " << output.c_str() << "\n";
            return false;
        }

        clear(headers);
    }

    return true;
}

//-------------------------------------------

void SIP_Header_Test::clear(std::map<SIP_Header_Type, std::list<SIP_Header *>> &headers)
{
    std::map<SIP_Header_Type, std::list<SIP_Header *>>::iterator it1 = headers.begin();
    while (it1 != headers.end())
    {
        std::list<SIP_Header *> header_list = it1->second;
        it1++;

        std::list<SIP_Header *>::iterator it2 = header_list.begin();
        while (it2 != header_list.end())
            delete *it2++;
    }

    headers.clear();
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Accept_Test::SIP_Header_Accept_Test()
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

SIP_Header_Accept_Encoding_Test::SIP_Header_Accept_Encoding_Test()
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

SIP_Header_Accept_Language_Test::SIP_Header_Accept_Language_Test()
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

SIP_Header_Alert_Info_Test::SIP_Header_Alert_Info_Test()
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

SIP_Header_Allow_Test::SIP_Header_Allow_Test()
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

SIP_Header_Allow_Events_Test::SIP_Header_Allow_Events_Test()
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

SIP_Header_Authentication_Info_Test::SIP_Header_Authentication_Info_Test()
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

SIP_Header_Authorization_Test::SIP_Header_Authorization_Test()
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

SIP_Header_Call_ID_Test::SIP_Header_Call_ID_Test()
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

SIP_Header_Call_Info_Test::SIP_Header_Call_Info_Test()
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

SIP_Header_Contact_Test::SIP_Header_Contact_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_CONTACT;
    hdr1._input          = "Contact: sip:123456789@my-domain.org";
    hdr1._output         = "Contact: <sip:123456789@my-domain.org>\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_CONTACT;
    hdr2._input          = "Contact: sips:my-domain.org:5060;parameter1;parameter2;expires=60;parameter3;q=1.0";
    hdr2._output         = "Contact: <sips:my-domain.org:5060>;expires=60;q=1.0;parameter1;parameter2;parameter3\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_CONTACT;
    hdr3._input          = "Contact:   Display name here <sip:my-domain.org;par;lr;ttl=160>;parameter1  ;q=0.5;  parameter2,";
    hdr3._input         += "tel:+123456789;par";
    hdr3._output         = "Contact: Display name here <sip:my-domain.org;ttl=160;lr;par>;q=0.5;parameter1;parameter2\r\n";
    hdr3._output        += "Contact: <tel:+123456789>;par\r\n";
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
    hdr6._output         = "Contact: <sip:123456789:password@my-domain.org>\r\n";
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
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Disposition_Test::SIP_Header_Content_Disposition_Test()
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

SIP_Header_Content_Encoding_Test::SIP_Header_Content_Encoding_Test()
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

SIP_Header_Content_Language_Test::SIP_Header_Content_Language_Test()
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

SIP_Header_Content_Length_Test::SIP_Header_Content_Length_Test()
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

SIP_Header_Content_Type_Test::SIP_Header_Content_Type_Test()
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

SIP_Header_CSeq_Test::SIP_Header_CSeq_Test()
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

SIP_Header_Date_Test::SIP_Header_Date_Test()
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

SIP_Header_Error_Info_Test::SIP_Header_Error_Info_Test()
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
    hdr2._input          = "Error-Info: <mailto:user@host.com;par1; par2 ;par3>;param1 ; param2 ;param3 , <http://wwww.example.com/alice/photo.jpg>";
    hdr2._output         = "Error-Info: <mailto:user@host.com;par1; par2 ;par3>;param1;param2;param3, <http://wwww.example.com/alice/photo.jpg>\r\n";
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

SIP_Header_Event_Test::SIP_Header_Event_Test()
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

SIP_Header_Expires_Test::SIP_Header_Expires_Test()
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

SIP_Header_From_Test::SIP_Header_From_Test()
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
    hdr6._output         = "From: <sip:+12125551212@server.phone2net.com>;tag=887s\r\n";
    hdr6._header_nb      = 1;
    hdr6._decode_success = true;
    hdr6._encode_success = true;
    _header_input_output.push_back(hdr6);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_In_Reply_To_Test::SIP_Header_In_Reply_To_Test()
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

SIP_Header_Max_Forwards_Test::SIP_Header_Max_Forwards_Test()
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

SIP_Header_Mime_Version_Test::SIP_Header_Mime_Version_Test()
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

SIP_Header_Min_Expires_Test::SIP_Header_Min_Expires_Test()
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

SIP_Header_Organization_Test::SIP_Header_Organization_Test()
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

SIP_Header_Priority_Test::SIP_Header_Priority_Test()
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

SIP_Header_Proxy_Authenticate_Test::SIP_Header_Proxy_Authenticate_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_PROXY_AUTHENTICATE;
    hdr1._input          = "Proxy-Authenticate: Digest realm=\"atlanta.com\", domain=\"sip:ss1.carrier.com\", qop=\"auth\", nonce=\"f84f1cec41e6cbe5aea9c8e88d359\", opaque=\"\", stale=FALSE, algorithm=MD5";
    hdr1._output         = "Proxy-Authenticate: Digest realm=\"atlanta.com\", domain=\"sip:ss1.carrier.com\", nonce=\"f84f1cec41e6cbe5aea9c8e88d359\", opaque=\"\", stale=FALSE, algorithm=MD5, qop=\"auth\"\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_PROXY_AUTHENTICATE;
    hdr2._input          = "Proxy-Authenticate: Digest realm=\"atlanta.example.com\",qop=\"auth\",   nonce=\"wf84f1cczx41ae6cbeaea9ce88d359\",opaque=\"\",stale=FALSE,algorithm=MD5";
    hdr2._output         = "Proxy-Authenticate: Digest realm=\"atlanta.example.com\", nonce=\"wf84f1cczx41ae6cbeaea9ce88d359\", opaque=\"\", stale=FALSE, algorithm=MD5, qop=\"auth\"\r\n";
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
    hdr4._input          = "Proxy-Authenticate: Digest\trealm=\"myrealm.com\",nonce=\"123456789012345678901\", domain=\"sip:myrealm.com\",algorithm=MD5";
    hdr4._output         = "Proxy-Authenticate: Digest realm=\"myrealm.com\", domain=\"sip:myrealm.com\", nonce=\"123456789012345678901\", algorithm=MD5\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_PROXY_AUTHENTICATE;
    hdr5._input          = "Proxy-Authenticate: Scheme1 param1, param2=test, nonce=\"123456789012345678901\",realm=\"server.com\",domain=\"sip:server.com\",qop=\"auth, auth-int, value\", opaque=\"11223344556677889900aabbccddeeff\", stale=true, par3=\"test\", algorithm=XYZ";
    hdr5._output         = "Proxy-Authenticate: Scheme1 realm=\"server.com\", domain=\"sip:server.com\", nonce=\"123456789012345678901\", opaque=\"11223344556677889900aabbccddeeff\", stale=true, algorithm=XYZ, qop=\"auth, auth-int, value\", param1, param2=test, par3=\"test\"\r\n";
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

SIP_Header_Proxy_Authorization_Test::SIP_Header_Proxy_Authorization_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_PROXY_AUTHORIZATION;
    hdr1._input          = "Proxy-Authorization: Digest username=\"Alice\", realm=\"atlanta.com\", nonce=\"c60f3082ee1212b402a21831ae\", response=\"245f23415f11432b3434341c022\"";
    hdr1._output         = "Proxy-Authorization: Digest username=\"Alice\", realm=\"atlanta.com\", nonce=\"c60f3082ee1212b402a21831ae\", response=\"245f23415f11432b3434341c022\"\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_PROXY_AUTHORIZATION;
    hdr2._input          = "Proxy-Authorization: Digest username=\"alice\",realm=\"atlanta.example.com\",   nonce=\"wf84f1ceczx41ae6cbe5aea9c8e88d359\",opaque=\"\", uri=\"sip:bob@biloxi.example.com\", response=\"42ce3cef44b22f50c6a6071bc8\"";
    hdr2._output         = "Proxy-Authorization: Digest username=\"alice\", realm=\"atlanta.example.com\", nonce=\"wf84f1ceczx41ae6cbe5aea9c8e88d359\", uri=\"sip:bob@biloxi.example.com\", response=\"42ce3cef44b22f50c6a6071bc8\", opaque=\"\"\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_PROXY_AUTHORIZATION;
    hdr3._input          = "Proxy-Authorization: Digest username=\"bob\",realm=\"atlanta.example.com\",nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\" ,   opaque=\"\",   uri=\"sips:ss2.biloxi.example.com\",response=\"dfe56131d1958046689d83306477ecc\"";
    hdr3._output         = "Proxy-Authorization: Digest username=\"bob\", realm=\"atlanta.example.com\", nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\", uri=\"sips:ss2.biloxi.example.com\", response=\"dfe56131d1958046689d83306477ecc\", opaque=\"\"\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_PROXY_AUTHORIZATION;
    hdr4._input          = "Proxy-Authorization: Digest\tusername=\"name\",realm=\"myrealm.com\",nonce=\"123456789012345678901\", uri=\"sip:myrealm.com\",response=\"12345678901234567890123456789012\",algorithm=MD5";
    hdr4._output         = "Proxy-Authorization: Digest username=\"name\", realm=\"myrealm.com\", nonce=\"123456789012345678901\", uri=\"sip:myrealm.com\", response=\"12345678901234567890123456789012\", algorithm=MD5\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_PROXY_AUTHORIZATION;
    hdr5._input          = "Proxy-Authorization: Scheme1 param1, param2=test, nonce=\"123456789012345678901\",realm=\"server.com\",response=\"12345678901234567890123456789012\", username=\"1234\", uri=\"sip:server.com\",qop=auth, nc=00000001, cnonce=\"0a4f113b\", opaque=\"11223344556677889900aabbccddeeff\", par3=\"test\", algorithm=XYZ";
    hdr5._output         = "Proxy-Authorization: Scheme1 username=\"1234\", realm=\"server.com\", nonce=\"123456789012345678901\", uri=\"sip:server.com\", response=\"12345678901234567890123456789012\", algorithm=XYZ, cnonce=\"0a4f113b\", opaque=\"11223344556677889900aabbccddeeff\", qop=auth, nc=00000001, param1, param2=test, par3=\"test\"\r\n";
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

SIP_Header_Proxy_Require_Test::SIP_Header_Proxy_Require_Test()
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

SIP_Header_Record_Route_Test::SIP_Header_Record_Route_Test()
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
    hdr2._input          = "Record-Route:   <sip:user@server10.biloxi.com;par1;user= phone >;parameter1, <sip:bigbox3.site3.atlanta.com;par1;lr;par2>";
    hdr2._output         = "Record-Route: <sip:user@server10.biloxi.com;user=phone;par1>;parameter1\r\nRecord-Route: <sip:bigbox3.site3.atlanta.com;lr;par1;par2>\r\n";
    hdr2._header_nb      = 2;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_RECORD_ROUTE;
    hdr3._input          = "Record-Route: <sip:n.tesla@high-voltage.org;par1 ; maddr= 10.0.0.10 ; par2  ;par3> ;  parameter1;parameter2 , <sip:c8oqz84zk7z@privacy.org> ; parameter1";
    hdr3._output         = "Record-Route: <sip:n.tesla@high-voltage.org;maddr=10.0.0.10;par1;par2;par3>;parameter1;parameter2\r\nRecord-Route: <sip:c8oqz84zk7z@privacy.org>;parameter1\r\n";
    hdr3._header_nb      = 2;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Reply_To_Test::SIP_Header_Reply_To_Test()
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
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Require_Test::SIP_Header_Require_Test()
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

SIP_Header_Retry_After_Test::SIP_Header_Retry_After_Test()
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

SIP_Header_Route_Test::SIP_Header_Route_Test()
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
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Server_Test::SIP_Header_Server_Test()
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

SIP_Header_Subject_Test::SIP_Header_Subject_Test()
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

SIP_Header_Subscription_State_Test::SIP_Header_Subscription_State_Test()
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

SIP_Header_Supported_Test::SIP_Header_Supported_Test()
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

SIP_Header_Timestamp_Test::SIP_Header_Timestamp_Test()
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

SIP_Header_To_Test::SIP_Header_To_Test()
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
    hdr2._output         = "To: <sip:+12125551212@server.phone2net.com>;tag=287447\r\n";
    hdr2._header_nb      = 1;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_TO;
    hdr3._input          = "To: \"Name\" <sip:+12125551212@server.phone2net.com ;par1 ;par2> ; tag=287447;parameter1 ";
    hdr3._output         = "To: \"Name\" <sip:+12125551212@server.phone2net.com;par1;par2>;tag=287447;parameter1\r\n";
    hdr3._header_nb      = 1;
    hdr3._decode_success = true;
    hdr3._encode_success = true;
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4;
    hdr4._header_type    = SIP_HEADER_TO;
    hdr4._input          = "To: <sip:server.phone2net.com ;par1 ; lr ; maddr= 10.10.10.10 ;ttl=20; method= BYE; user=ip;transport= udp ;par2> ; tag=287447;parameter1 ";
    hdr4._output         = "To: <sip:server.phone2net.com;transport=udp;user=ip;method=BYE;ttl=20;maddr=10.10.10.10;lr;par1;par2>;tag=287447;parameter1\r\n";
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
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Unsupported_Test::SIP_Header_Unsupported_Test()
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

SIP_Header_User_Agent_Test::SIP_Header_User_Agent_Test()
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

SIP_Header_Via_Test::SIP_Header_Via_Test()
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
    hdr2._input          = "Via: SIP / 2.0 / UDP first.example.com: 4000  ;par1;maddr=224.2.0.1 ;ttl=16;branch=z9hG4bKa7c6a8dlze.1, SIP/2.0/UDP first.example.com";
    hdr2._output         = "Via: SIP/2.0/UDP first.example.com:4000;branch=z9hG4bKa7c6a8dlze.1;ttl=16;maddr=224.2.0.1;par1\r\nVia: SIP/2.0/UDP first.example.com\r\n";
    hdr2._header_nb      = 2;
    hdr2._decode_success = true;
    hdr2._encode_success = true;
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3;
    hdr3._header_type    = SIP_HEADER_VIA;
    hdr3._input          = "v: SIP/2.0/UDP lab.high-voltage.org;received=10.10.10.10;branch=z9hG4bKfw19b,SIP/2.0/UDP 11.11.11.11:5070;branch=z9hG4bKfw19b;parameter1 ";
    hdr3._output         = "Via: SIP/2.0/UDP lab.high-voltage.org;branch=z9hG4bKfw19b;received=10.10.10.10\r\nVia: SIP/2.0/UDP 11.11.11.11:5070;branch=z9hG4bKfw19b;parameter1\r\n";
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
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Warning_Test::SIP_Header_Warning_Test()
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
    hdr2._input          = "Warning: 307 isi.edu \"Session parameter ’foo’ not understood\", 301 isi.edu \"Incompatible network address type ’E.164’\"";
    hdr2._output         = "Warning: 307 isi.edu \"Session parameter ’foo’ not understood\"\r\nWarning: 301 isi.edu \"Incompatible network address type ’E.164’\"\r\n";
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

SIP_Header_WWW_Authenticate_Test::SIP_Header_WWW_Authenticate_Test()
{
    SIP_Header_Input_Output hdr1;
    hdr1._header_type    = SIP_HEADER_WWW_AUTHENTICATE;
    hdr1._input          = "WWW-Authenticate: Digest realm=\"atlanta.com\", domain=\"sip:boxesbybob.com\", qop=\"auth\", nonce=\"f84f1cec41e6cbe5aea9c8e88d359\", opaque=\"\", stale=FALSE, algorithm=MD5";
    hdr1._output         = "WWW-Authenticate: Digest realm=\"atlanta.com\", domain=\"sip:boxesbybob.com\", nonce=\"f84f1cec41e6cbe5aea9c8e88d359\", opaque=\"\", stale=FALSE, algorithm=MD5, qop=\"auth\"\r\n";
    hdr1._header_nb      = 1;
    hdr1._decode_success = true;
    hdr1._encode_success = true;
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2;
    hdr2._header_type    = SIP_HEADER_WWW_AUTHENTICATE;
    hdr2._input          = "WWW-Authenticate: Digest realm=\"biloxi.com\",qop=\"auth,auth-int\",  nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\",opaque=\"5ccc069c403ebaf9f0171e9517f40e41\"";
    hdr2._output         = "WWW-Authenticate: Digest realm=\"biloxi.com\", nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\", opaque=\"5ccc069c403ebaf9f0171e9517f40e41\", qop=\"auth,auth-int\"\r\n";
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
    hdr4._input          = "WWW-Authenticate: Digest\trealm=\"myrealm.com\",nonce=\"123456789012345678901\", domain=\"sip:myrealm.com\",algorithm=MD5";
    hdr4._output         = "WWW-Authenticate: Digest realm=\"myrealm.com\", domain=\"sip:myrealm.com\", nonce=\"123456789012345678901\", algorithm=MD5\r\n";
    hdr4._header_nb      = 1;
    hdr4._decode_success = true;
    hdr4._encode_success = true;
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5;
    hdr5._header_type    = SIP_HEADER_WWW_AUTHENTICATE;
    hdr5._input          = "WWW-Authenticate: Scheme1 param1, param2=test, nonce=\"123456789012345678901\",realm=\"server.com\",domain=\"sip:server.com\",qop=\"auth, auth-int, value\", opaque=\"11223344556677889900aabbccddeeff\", stale=true, par3=\"test\", algorithm=XYZ";
    hdr5._output         = "WWW-Authenticate: Scheme1 realm=\"server.com\", domain=\"sip:server.com\", nonce=\"123456789012345678901\", opaque=\"11223344556677889900aabbccddeeff\", stale=true, algorithm=XYZ, qop=\"auth, auth-int, value\", param1, param2=test, par3=\"test\"\r\n";
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
