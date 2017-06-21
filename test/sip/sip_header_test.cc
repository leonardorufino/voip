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
    SIP_Header_Input_Output hdr1(SIP_HEADER_ALLOW_EVENTS, "Allow-Events: presence", "Allow-Events: presence\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_ALLOW_EVENTS, "Allow-Events:presence, test1.test2", "Allow-Events: presence, test1.test2\r\n", 2, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_ALLOW_EVENTS, "u: presence.template1.template2 , test.template,package-xyz", "Allow-Events: presence.template1.template2, test.template, package-xyz\r\n", 3, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Authentication_Info_Test::SIP_Header_Authentication_Info_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_AUTHENTICATION_INFO, "Authentication-Info: nextnonce=\"47364c23432d2e131a5fb210812c\"", "Authentication-Info: nextnonce=\"47364c23432d2e131a5fb210812c\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_AUTHENTICATION_INFO, "Authentication-Info: qop=auth, rspauth=\"1234567890abcdef1234567890\", cnonce=\"11223344\", nc=00000001", "Authentication-Info: qop=auth, rspauth=\"1234567890abcdef1234567890\", cnonce=\"11223344\", nc=00000001\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_AUTHENTICATION_INFO, "Authentication-Info:   rspauth=\"1234567890abcdef1234567890\",cnonce=\"11223344\", \t nextnonce=\"47364c23432d2e131a5fb210812c\",nc=00000001,qop=auth", "Authentication-Info: nextnonce=\"47364c23432d2e131a5fb210812c\", qop=auth, rspauth=\"1234567890abcdef1234567890\", cnonce=\"11223344\", nc=00000001\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Authorization_Test::SIP_Header_Authorization_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_AUTHORIZATION, "Authorization: Digest username=\"Alice\", realm=\"atlanta.com\", nonce=\"84a4cc6f3082121f32b42a2187831a9e\", response=\"7587245234b3434cc3412213e5f113a5432\"", "Authorization: Digest username=\"Alice\", realm=\"atlanta.com\", nonce=\"84a4cc6f3082121f32b42a2187831a9e\", response=\"7587245234b3434cc3412213e5f113a5432\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_AUTHORIZATION, "Authorization: Digest username=\"bob\", realm=\"biloxi.com\", nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\", uri=\"sip:bob@biloxi.com\", qop=auth, nc=00000001, cnonce=\"0a4f113b\", response=\"6629fae49393a05397450978507c4ef1\", opaque=\"5ccc069c403ebaf9f0171e9517f40e41\"", "Authorization: Digest username=\"bob\", realm=\"biloxi.com\", nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\", uri=\"sip:bob@biloxi.com\", response=\"6629fae49393a05397450978507c4ef1\", cnonce=\"0a4f113b\", opaque=\"5ccc069c403ebaf9f0171e9517f40e41\", qop=auth, nc=00000001\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_AUTHORIZATION, "Authorization: Digest username=\"bob\",realm=\"atlanta.example.com\",nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\" ,   opaque=\"\",   uri=\"sips:ss2.biloxi.example.com\",response=\"dfe56131d1958046689d83306477ecc\"", "Authorization: Digest username=\"bob\", realm=\"atlanta.example.com\", nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\", uri=\"sips:ss2.biloxi.example.com\", response=\"dfe56131d1958046689d83306477ecc\", opaque=\"\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_AUTHORIZATION, "Authorization: Digest\tusername=\"name\",realm=\"myrealm.com\",nonce=\"123456789012345678901\", uri=\"sip:myrealm.com\",response=\"12345678901234567890123456789012\",algorithm=MD5", "Authorization: Digest username=\"name\", realm=\"myrealm.com\", nonce=\"123456789012345678901\", uri=\"sip:myrealm.com\", response=\"12345678901234567890123456789012\", algorithm=MD5\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_AUTHORIZATION, "Authorization: Scheme1 param1, param2=test, nonce=\"123456789012345678901\",realm=\"server.com\",response=\"12345678901234567890123456789012\", username=\"1234\", uri=\"sip:server.com\",qop=auth, nc=00000001, cnonce=\"0a4f113b\", opaque=\"11223344556677889900aabbccddeeff\", par3=\"test\", algorithm=XYZ", "Authorization: Scheme1 username=\"1234\", realm=\"server.com\", nonce=\"123456789012345678901\", uri=\"sip:server.com\", response=\"12345678901234567890123456789012\", algorithm=XYZ, cnonce=\"0a4f113b\", opaque=\"11223344556677889900aabbccddeeff\", qop=auth, nc=00000001, param1, param2=test, par3=\"test\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6(SIP_HEADER_AUTHORIZATION, "Authorization: scheme2 param1, param2=test,par3=\"test\"", "Authorization: scheme2 param1, param2=test, par3=\"test\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr6);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Call_ID_Test::SIP_Header_Call_ID_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CALL_ID, "Call-ID: 123456789@my-domain.org", "Call-ID: 123456789@my-domain.org\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CALL_ID, "Call-ID: 123456789", "Call-ID: 123456789\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CALL_ID, "i:my-domain.org ", "Call-ID: my-domain.org\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_CALL_ID, "Call-ID: f81d4fae-7dec-11d0-a765-00a0c91e6bf6@biloxi.com", "Call-ID: f81d4fae-7dec-11d0-a765-00a0c91e6bf6@biloxi.com\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_CALL_ID, "i:f81d4fae-7dec-11d0-a765-00a0c91e6bf6@192.0.2.4", "Call-ID: f81d4fae-7dec-11d0-a765-00a0c91e6bf6@192.0.2.4\r\n", 1, true, true);
    _header_input_output.push_back(hdr5);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Call_Info_Test::SIP_Header_Call_Info_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CALL_INFO, "Call-Info: <http://wwww.example.com/alice/photo.jpg> ;purpose=icon, <http://www.example.com/alice/> ;purpose=info", "Call-Info: <http://wwww.example.com/alice/photo.jpg>;purpose=icon, <http://www.example.com/alice/>;purpose=info\r\n", 2, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CALL_INFO, "Call-Info: <mailto:user@host.com;par1; par2 ;par3>;param1 ; param2 ;param3 ", "Call-Info: <mailto:user@host.com;par1; par2 ;par3>;param1;param2;param3\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CALL_INFO, "Call-Info: <sips:user@host.com;par1> ; param1 ; purpose= card; param2 ;param3,<abc:user;par1> ; param2", "Call-Info: <sips:user@host.com;par1>;purpose=card;param1;param2;param3, <abc:user;par1>;param2\r\n", 2, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Contact_Test::SIP_Header_Contact_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CONTACT, "Contact: sip:123456789@my-domain.org", "Contact: <sip:123456789@my-domain.org>\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CONTACT, "Contact: sips:my-domain.org:5060;parameter1;parameter2;expires=60;parameter3;q=1.0", "Contact: <sips:my-domain.org:5060>;expires=60;q=1.0;parameter1;parameter2;parameter3\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CONTACT, "Contact:   Display name here <sip:my-domain.org;par;lr;ttl=160>;parameter1  ;q=0.5;  parameter2,tel:+123456789;par", "Contact: Display name here <sip:my-domain.org;ttl=160;lr;par>;q=0.5;parameter1;parameter2\r\nContact: <tel:+123456789>;par\r\n", 2, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_CONTACT, "Contact: \"Mr. Watson\" <sip:watson@worcester.bell-telephone.com;lr;par1? header=hdr1 > ;q=0.7 ;expires=3600, \"Mr. Watson\" <mailto:watson@bell-telephone.com> ;q=0.1", "Contact: \"Mr. Watson\" <sip:watson@worcester.bell-telephone.com;lr;par1?header=hdr1>;expires=3600;q=0.7\r\nContact: \"Mr. Watson\" <mailto:watson@bell-telephone.com>;q=0.1\r\n", 2, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_CONTACT, "m: *", "Contact: *\r\n", 1, true, true);
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6(SIP_HEADER_CONTACT, "Contact: sip:123456789:password@my-domain.org", "Contact: <sip:123456789:password@my-domain.org>\r\n", 1, true, true);
    _header_input_output.push_back(hdr6);

    SIP_Header_Input_Output hdr7(SIP_HEADER_CONTACT, "m: <sips:bob@192.0.2.4>;expires=60", "Contact: <sips:bob@192.0.2.4>;expires=60\r\n", 1, true, true);
    _header_input_output.push_back(hdr7);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Disposition_Test::SIP_Header_Content_Disposition_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CONTENT_DISPOSITION, "Content-Disposition: session;handling=required;par1", "Content-Disposition: session;handling=required;par1\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CONTENT_DISPOSITION, "Content-Disposition:   alert  ;  handling=  optional ; par1 ; par2;par3", "Content-Disposition: alert;handling=optional;par1;par2;par3\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CONTENT_DISPOSITION, "Content-Disposition: attachment; filename=smime.p7s;handling=required", "Content-Disposition: attachment;handling=required;filename=smime.p7s\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_CONTENT_DISPOSITION, "Content-Disposition: render", "Content-Disposition: render\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Encoding_Test::SIP_Header_Content_Encoding_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CONTENT_ENCODING, "Content-Encoding: text/plain, gzip", "Content-Encoding: text/plain, gzip\r\n", 2, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CONTENT_ENCODING, "Content-Encoding:   code1 ", "Content-Encoding: code1\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CONTENT_ENCODING, "Content-Encoding: code1,code2 , code3", "Content-Encoding: code1, code2, code3\r\n", 3, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_CONTENT_ENCODING, "e: tar", "Content-Encoding: tar\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_CONTENT_ENCODING, "Content-Encoding:gzip", "Content-Encoding: gzip\r\n", 1, true, true);
    _header_input_output.push_back(hdr5);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Language_Test::SIP_Header_Content_Language_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CONTENT_LANGUAGE, "Content-Language: pt", "Content-Language: pt\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CONTENT_LANGUAGE, "Content-Language:  en,fr ", "Content-Language: en, fr\r\n", 2, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CONTENT_LANGUAGE, "Content-Language:pt,en, fr", "Content-Language: pt, en, fr\r\n", 3, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Length_Test::SIP_Header_Content_Length_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CONTENT_LENGTH, "Content-Length: 0", "Content-Length: 0\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CONTENT_LENGTH, "Content-Length: 5678", "Content-Length: 5678\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CONTENT_LENGTH, "l:50 ", "Content-Length: 50\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_CONTENT_LENGTH, "Content-Length:2147483647", "Content-Length: 2147483647\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_CONTENT_LENGTH, "l: 4294967294", "Content-Length: 4294967294\r\n", 1, true, true);
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6(SIP_HEADER_CONTENT_LENGTH, "Content-Length: 4294967295", "", 0, false, false);
    _header_input_output.push_back(hdr6);

    SIP_Header_Input_Output hdr7(SIP_HEADER_CONTENT_LENGTH, "l: 4294967296", "", 0, false, false);
    _header_input_output.push_back(hdr7);

    SIP_Header_Input_Output hdr8(SIP_HEADER_CONTENT_LENGTH, "Content-Length: 4294967297", "", 0, false, false);
    _header_input_output.push_back(hdr8);

    SIP_Header_Input_Output hdr9(SIP_HEADER_CONTENT_LENGTH, "Content-Length: 6294967295", "", 0, false, false);
    _header_input_output.push_back(hdr9);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Type_Test::SIP_Header_Content_Type_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CONTENT_TYPE, "Content-Type: application/sdp", "Content-Type: application/sdp\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CONTENT_TYPE, "c: text/html; charset=ISO-8859-4", "Content-Type: text/html;charset=ISO-8859-4\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CONTENT_TYPE, "Content-Type:type1/sub1  ;par1;par2  ;  par3 ", "Content-Type: type1/sub1;par1;par2;par3\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_CSeq_Test::SIP_Header_CSeq_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CSEQ, "CSeq: 1 INVITE", "CSeq: 1 INVITE\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CSEQ, "CSeq: 9876 TEST", "CSeq: 9876 TEST\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CSEQ, "CSeq:0    ACK   ", "CSeq: 0 ACK\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_CSEQ, "CSeq: 4711 INVITE", "CSeq: 4711 INVITE\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Date_Test::SIP_Header_Date_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_DATE, "Date: Fri, 1 Oct 1990 00:10:59 GMT", "Date: Fri, 01 Oct 1990 00:10:59 GMT\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_DATE, "Date: Wed, 10 Feb 2001 23:00:20 GMT", "Date: Wed, 10 Feb 2001 23:00:20 GMT\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_DATE, "Date: Mon, 31 Dec 2010 12:59:05 GM", "Date: Mon, 31 Dec 2010 12:59:05 GM\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_DATE, "Date: Sat, 13 Nov 2010 23:29:00 GMT", "Date: Sat, 13 Nov 2010 23:29:00 GMT\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Error_Info_Test::SIP_Header_Error_Info_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_ERROR_INFO, "Error-Info: <sip:not-in-service-recording@atlanta.com>", "Error-Info: <sip:not-in-service-recording@atlanta.com>\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_ERROR_INFO, "Error-Info: <mailto:user@host.com;par1; par2 ;par3>;param1 ; param2 ;param3 , <http://wwww.example.com/alice/photo.jpg>", "Error-Info: <mailto:user@host.com;par1; par2 ;par3>;param1;param2;param3, <http://wwww.example.com/alice/photo.jpg>\r\n", 2, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_ERROR_INFO, "Error-Info: <sips:user@host.com;par1> ; param1 ; param2 ;param3,<abc:user;par1> ; param2", "Error-Info: <sips:user@host.com;par1>;param1;param2;param3, <abc:user;par1>;param2\r\n", 2, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Event_Test::SIP_Header_Event_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_EVENT, "Event: presence", "Event: presence\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_EVENT, "Event: test; id=1234", "Event: test;id=1234\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_EVENT, "Event:  package.template1.template2  ; par1 ; id= 567 ;par2 ", "Event: package.template1.template2;id=567;par1;par2\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Expires_Test::SIP_Header_Expires_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_EXPIRES, "Expires: 3600", "Expires: 3600\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_EXPIRES, "Expires: 0", "Expires: 0\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_EXPIRES, "Expires:    567890 ", "Expires: 567890\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_EXPIRES, "Expires: 4294967296", "", 0, false, false);
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_From_Test::SIP_Header_From_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_FROM, "From: Nikola Tesla <sip:n.tesla@high-voltage.org>;tag=76341", "From: Nikola Tesla <sip:n.tesla@high-voltage.org>;tag=76341\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_FROM, "f: Anonymous <sip:c8oqz84zk7z@privacy.org>", "From: Anonymous <sip:c8oqz84zk7z@privacy.org>\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_FROM, "From:  \"Nikola Tesla\"   <sip:n.tesla@high-voltage.org;par1 ;transport=tcp ; par2  ;par3>;parameter1;tag=76341 ", "From: \"Nikola Tesla\" <sip:n.tesla@high-voltage.org;transport=tcp;par1;par2;par3>;tag=76341;parameter1\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_FROM, "f: Anonymous <sip: c8oqz84zk7z:pass123@privacy.org;method=INVITE ? header=hdr1 & name=value&name2=value2>", "From: Anonymous <sip:c8oqz84zk7z:pass123@privacy.org;method=INVITE?header=hdr1&name=value&name2=value2>\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_FROM, "From: \"A. G. Bell\" <sip:agb@bell-telephone.com> ;tag=a48s", "From: \"A. G. Bell\" <sip:agb@bell-telephone.com>;tag=a48s\r\n", 1, true, true);
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6(SIP_HEADER_FROM, "From: sip:+12125551212@server.phone2net.com;tag=887s", "From: <sip:+12125551212@server.phone2net.com>;tag=887s\r\n", 1, true, true);
    _header_input_output.push_back(hdr6);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_In_Reply_To_Test::SIP_Header_In_Reply_To_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_IN_REPLY_TO, "In-Reply-To: 70710@saturn.bell-tel.com, 17320@saturn.bell-tel.com", "In-Reply-To: 70710@saturn.bell-tel.com, 17320@saturn.bell-tel.com\r\n", 2, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_IN_REPLY_TO, "In-Reply-To: 123456789", "In-Reply-To: 123456789\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_IN_REPLY_TO, "In-Reply-To:my-domain.org , test@domain.com:1234", "In-Reply-To: my-domain.org, test@domain.com:1234\r\n", 2, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Max_Forwards_Test::SIP_Header_Max_Forwards_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_MAX_FORWARDS, "Max-Forwards: 70", "Max-Forwards: 70\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_MAX_FORWARDS, "Max-Forwards:   56789  ", "Max-Forwards: 56789\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_MAX_FORWARDS, "Max-Forwards:1", "Max-Forwards: 1\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_MAX_FORWARDS, "Max-Forwards: 65534", "Max-Forwards: 65534\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_MAX_FORWARDS, "Max-Forwards: 65535", "", 0, false, false);
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6(SIP_HEADER_MAX_FORWARDS, "Max-Forwards: 65536", "", 0, false, false);
    _header_input_output.push_back(hdr6);

    SIP_Header_Input_Output hdr7(SIP_HEADER_MAX_FORWARDS, "Max-Forwards: 268435455", "", 0, false, false);
    _header_input_output.push_back(hdr7);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Mime_Version_Test::SIP_Header_Mime_Version_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_MIME_VERSION, "MIME-Version: 1.0", "MIME-Version: 1.0\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_MIME_VERSION, "MIME-Version:   2.5  ", "MIME-Version: 2.5\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_MIME_VERSION, "MIME-Version:0.0", "MIME-Version: 0.0\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Min_Expires_Test::SIP_Header_Min_Expires_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_MIN_EXPIRES, "Min-Expires: 3600", "Min-Expires: 3600\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_MIN_EXPIRES, "Min-Expires:0", "Min-Expires: 0\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_MIN_EXPIRES, "Min-Expires:    567890 ", "Min-Expires: 567890\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_MIN_EXPIRES, "Min-Expires: 60", "Min-Expires: 60\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_MIN_EXPIRES, "Min-Expires: 7834990190", "", 0, false, false);
    _header_input_output.push_back(hdr5);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Organization_Test::SIP_Header_Organization_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_ORGANIZATION, "Organization: Boxes by Bob", "Organization: Boxes by Bob\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_ORGANIZATION, "Organization:", "Organization: \r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_ORGANIZATION, "Organization:   ABC ", "Organization: ABC\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_ORGANIZATION, "Organization:   ", "Organization: \r\n", 1, true, true);
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Priority_Test::SIP_Header_Priority_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_PRIORITY, "Priority: normal", "Priority: normal\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_PRIORITY, "Priority:urgent  ", "Priority: urgent\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_PRIORITY, "Priority:my-priority", "Priority: my-priority\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_PRIORITY, "Priority: emergency", "Priority: emergency\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Proxy_Authenticate_Test::SIP_Header_Proxy_Authenticate_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_PROXY_AUTHENTICATE, "Proxy-Authenticate: Digest realm=\"atlanta.com\", domain=\"sip:ss1.carrier.com\", qop=\"auth\", nonce=\"f84f1cec41e6cbe5aea9c8e88d359\", opaque=\"\", stale=FALSE, algorithm=MD5", "Proxy-Authenticate: Digest realm=\"atlanta.com\", domain=\"sip:ss1.carrier.com\", nonce=\"f84f1cec41e6cbe5aea9c8e88d359\", opaque=\"\", stale=FALSE, algorithm=MD5, qop=\"auth\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_PROXY_AUTHENTICATE, "Proxy-Authenticate: Digest realm=\"atlanta.example.com\",qop=\"auth\",   nonce=\"wf84f1cczx41ae6cbeaea9ce88d359\",opaque=\"\",stale=FALSE,algorithm=MD5", "Proxy-Authenticate: Digest realm=\"atlanta.example.com\", nonce=\"wf84f1cczx41ae6cbeaea9ce88d359\", opaque=\"\", stale=FALSE, algorithm=MD5, qop=\"auth\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_PROXY_AUTHENTICATE, "Proxy-Authenticate: Digest nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\" ,   realm=\"atlanta.example.com\"", "Proxy-Authenticate: Digest realm=\"atlanta.example.com\", nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_PROXY_AUTHENTICATE, "Proxy-Authenticate: Digest\trealm=\"myrealm.com\",nonce=\"123456789012345678901\", domain=\"sip:myrealm.com\",algorithm=MD5", "Proxy-Authenticate: Digest realm=\"myrealm.com\", domain=\"sip:myrealm.com\", nonce=\"123456789012345678901\", algorithm=MD5\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_PROXY_AUTHENTICATE, "Proxy-Authenticate: Scheme1 param1, param2=test, nonce=\"123456789012345678901\",realm=\"server.com\",domain=\"sip:server.com\",qop=\"auth, auth-int, value\", opaque=\"11223344556677889900aabbccddeeff\", stale=true, par3=\"test\", algorithm=XYZ", "Proxy-Authenticate: Scheme1 realm=\"server.com\", domain=\"sip:server.com\", nonce=\"123456789012345678901\", opaque=\"11223344556677889900aabbccddeeff\", stale=true, algorithm=XYZ, qop=\"auth, auth-int, value\", param1, param2=test, par3=\"test\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6(SIP_HEADER_PROXY_AUTHENTICATE, "Proxy-Authenticate: scheme2 param1, param2=test,par3=\"test\"", "Proxy-Authenticate: scheme2 param1, param2=test, par3=\"test\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr6);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Proxy_Authorization_Test::SIP_Header_Proxy_Authorization_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_PROXY_AUTHORIZATION, "Proxy-Authorization: Digest username=\"Alice\", realm=\"atlanta.com\", nonce=\"c60f3082ee1212b402a21831ae\", response=\"245f23415f11432b3434341c022\"", "Proxy-Authorization: Digest username=\"Alice\", realm=\"atlanta.com\", nonce=\"c60f3082ee1212b402a21831ae\", response=\"245f23415f11432b3434341c022\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_PROXY_AUTHORIZATION, "Proxy-Authorization: Digest username=\"alice\",realm=\"atlanta.example.com\",   nonce=\"wf84f1ceczx41ae6cbe5aea9c8e88d359\",opaque=\"\", uri=\"sip:bob@biloxi.example.com\", response=\"42ce3cef44b22f50c6a6071bc8\"", "Proxy-Authorization: Digest username=\"alice\", realm=\"atlanta.example.com\", nonce=\"wf84f1ceczx41ae6cbe5aea9c8e88d359\", uri=\"sip:bob@biloxi.example.com\", response=\"42ce3cef44b22f50c6a6071bc8\", opaque=\"\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_PROXY_AUTHORIZATION, "Proxy-Authorization: Digest username=\"bob\",realm=\"atlanta.example.com\",nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\" ,   opaque=\"\",   uri=\"sips:ss2.biloxi.example.com\",response=\"dfe56131d1958046689d83306477ecc\"", "Proxy-Authorization: Digest username=\"bob\", realm=\"atlanta.example.com\", nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\", uri=\"sips:ss2.biloxi.example.com\", response=\"dfe56131d1958046689d83306477ecc\", opaque=\"\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_PROXY_AUTHORIZATION, "Proxy-Authorization: Digest\tusername=\"name\",realm=\"myrealm.com\",nonce=\"123456789012345678901\", uri=\"sip:myrealm.com\",response=\"12345678901234567890123456789012\",algorithm=MD5", "Proxy-Authorization: Digest username=\"name\", realm=\"myrealm.com\", nonce=\"123456789012345678901\", uri=\"sip:myrealm.com\", response=\"12345678901234567890123456789012\", algorithm=MD5\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_PROXY_AUTHORIZATION, "Proxy-Authorization: Scheme1 param1, param2=test, nonce=\"123456789012345678901\",realm=\"server.com\",response=\"12345678901234567890123456789012\", username=\"1234\", uri=\"sip:server.com\",qop=auth, nc=00000001, cnonce=\"0a4f113b\", opaque=\"11223344556677889900aabbccddeeff\", par3=\"test\", algorithm=XYZ", "Proxy-Authorization: Scheme1 username=\"1234\", realm=\"server.com\", nonce=\"123456789012345678901\", uri=\"sip:server.com\", response=\"12345678901234567890123456789012\", algorithm=XYZ, cnonce=\"0a4f113b\", opaque=\"11223344556677889900aabbccddeeff\", qop=auth, nc=00000001, param1, param2=test, par3=\"test\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6(SIP_HEADER_PROXY_AUTHORIZATION, "Proxy-Authorization: scheme2 param1, param2=test,par3=\"test\"", "Proxy-Authorization: scheme2 param1, param2=test, par3=\"test\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr6);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Proxy_Require_Test::SIP_Header_Proxy_Require_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_PROXY_REQUIRE, "Proxy-Require: foo", "Proxy-Require: foo\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_PROXY_REQUIRE, "Proxy-Require: req1, req2,req3", "Proxy-Require: req1, req2, req3\r\n", 3, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_PROXY_REQUIRE, "Proxy-Require:req1,req2", "Proxy-Require: req1, req2\r\n", 2, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Record_Route_Test::SIP_Header_Record_Route_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_RECORD_ROUTE, "Record-Route: <sip:server10.biloxi.com;lr>, <sip:bigbox3.site3.atlanta.com;lr>", "Record-Route: <sip:server10.biloxi.com;lr>\r\nRecord-Route: <sip:bigbox3.site3.atlanta.com;lr>\r\n", 2, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_RECORD_ROUTE, "Record-Route:   <sip:user@server10.biloxi.com;par1;user= phone >;parameter1, <sip:bigbox3.site3.atlanta.com;par1;lr;par2>", "Record-Route: <sip:user@server10.biloxi.com;user=phone;par1>;parameter1\r\nRecord-Route: <sip:bigbox3.site3.atlanta.com;lr;par1;par2>\r\n", 2, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_RECORD_ROUTE, "Record-Route: <sip:n.tesla@high-voltage.org;par1 ; maddr= 10.0.0.10 ; par2  ;par3> ;  parameter1;parameter2 , <sip:c8oqz84zk7z@privacy.org> ; parameter1", "Record-Route: <sip:n.tesla@high-voltage.org;maddr=10.0.0.10;par1;par2;par3>;parameter1;parameter2\r\nRecord-Route: <sip:c8oqz84zk7z@privacy.org>;parameter1\r\n", 2, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Reply_To_Test::SIP_Header_Reply_To_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_REPLY_TO, "Reply-To: Bob <sip:bob@biloxi.com>", "Reply-To: Bob <sip:bob@biloxi.com>\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_REPLY_TO, "Reply-To:   <sip:user@server10.biloxi.com;par1;user= phone >;parameter1", "Reply-To: <sip:user@server10.biloxi.com;user=phone;par1>;parameter1\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_REPLY_TO, "Reply-To: <sip:n.tesla@high-voltage.org;par1 ; maddr= 10.0.0.10 ; par2  ;ttl=70;par3> ;  parameter1;parameter2 ", "Reply-To: <sip:n.tesla@high-voltage.org;ttl=70;maddr=10.0.0.10;par1;par2;par3>;parameter1;parameter2\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Require_Test::SIP_Header_Require_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_REQUIRE, "Require: foo", "Require: foo\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_REQUIRE, "Require: req1, req2,req3", "Require: req1, req2, req3\r\n", 3, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_REQUIRE, "Require:req1,req2", "Require: req1, req2\r\n", 2, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_REQUIRE, "Require: 100rel", "Require: 100rel\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Retry_After_Test::SIP_Header_Retry_After_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_RETRY_AFTER, "Retry-After: 18000;duration=3600", "Retry-After: 18000;duration=3600\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_RETRY_AFTER, "Retry-After: 120 (I'm in a meeting)", "Retry-After: 120 (I'm in a meeting)\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_RETRY_AFTER, "Retry-After:10( I'm in a meeting );par1=test;duration= 100 ; par2", "Retry-After: 10 ( I'm in a meeting );duration=100;par1=test;par2\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_RETRY_AFTER, "Retry-After: 99999999 (This (\"is a\") comment); par1", "Retry-After: 99999999 (This (\"is a\") comment);par1\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Route_Test::SIP_Header_Route_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_ROUTE, "Route: <sip:bigbox3.site3.atlanta.com;lr>, <sip:server10.biloxi.com;lr>", "Route: <sip:bigbox3.site3.atlanta.com;lr>\r\nRoute: <sip:server10.biloxi.com;lr>\r\n", 2, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_ROUTE, "Route: <sip:server13.atlanta.com;lr>", "Route: <sip:server13.atlanta.com;lr>\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_ROUTE, "Route:   <sip:server1.atlanta.com ; transport=udp ; user=phone  ;  lr > ", "Route: <sip:server1.atlanta.com;transport=udp;user=phone;lr>\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_ROUTE, "Route: <sip:server2.atlanta.com;transport=udp;user=phone>;lr", "Route: <sip:server2.atlanta.com;transport=udp;user=phone>;lr\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_ROUTE, "Route: <sip:server3.atlanta.com ; transport=udp;lr?header=hdr1& name=value > ; teste ; lr ", "Route: <sip:server3.atlanta.com;transport=udp;lr?header=hdr1&name=value>;teste;lr\r\n", 1, true, true);
    _header_input_output.push_back(hdr5);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Server_Test::SIP_Header_Server_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_SERVER, "Server: HomeServer v2", "Server: HomeServer v2\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_SERVER, "Server:My Server/1.5.0 Pro", "Server: My Server/1.5.0 Pro\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_SERVER, "Server:  server1 ", "Server: server1\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Subject_Test::SIP_Header_Subject_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_SUBJECT, "Subject : lunch", "Subject: lunch\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_SUBJECT, "Subject:Need more boxes ", "Subject: Need more boxes\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_SUBJECT, "s: Tech Support ", "Subject: Tech Support\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_SUBJECT, "s:", "Subject: \r\n", 1, true, true);
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Subscription_State_Test::SIP_Header_Subscription_State_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_SUBSCRIPTION_STATE, "Subscription-State: active;expires=600", "Subscription-State: active;expires=600\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_SUBSCRIPTION_STATE, "Subscription-State: state1 ; expires= 500", "Subscription-State: state1;expires=500\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_SUBSCRIPTION_STATE, "Subscription-State: terminated; reason=timeout ; retry-after=400 ", "Subscription-State: terminated;reason=timeout;retry-after=400\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_SUBSCRIPTION_STATE, "Subscription-State: pending; expires= 500 ; retry-after=9999 ;reason=deactivated ", "Subscription-State: pending;reason=deactivated;expires=500;retry-after=9999\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_SUBSCRIPTION_STATE, "Subscription-State: state; reason=giveup  ", "Subscription-State: state;reason=giveup\r\n", 1, true, true);
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6(SIP_HEADER_SUBSCRIPTION_STATE, "Subscription-State:active", "Subscription-State: active\r\n", 1, true, true);
    _header_input_output.push_back(hdr6);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Supported_Test::SIP_Header_Supported_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_SUPPORTED, "Supported: 100rel, foo", "Supported: 100rel, foo\r\n", 2, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_SUPPORTED, "Supported:foo1", "Supported: foo1\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_SUPPORTED, "Supported: 100rel, foo, bar  ", "Supported: 100rel, foo, bar\r\n", 3, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_SUPPORTED, "k:", "Supported: \r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_SUPPORTED, "Supported: 100rel", "Supported: 100rel\r\n", 1, true, true);
    _header_input_output.push_back(hdr5);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Timestamp_Test::SIP_Header_Timestamp_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_TIMESTAMP, "Timestamp: 54", "Timestamp: 54\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_TIMESTAMP, "Timestamp:10.20", "Timestamp: 10.20\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_TIMESTAMP, "Timestamp: 10.20   7.90  ", "Timestamp: 10.20 7.90\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_TIMESTAMP, "Timestamp: 99.88\t77.666  ", "Timestamp: 99.88 77.666\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_TIMESTAMP, "Timestamp: 12345678901234.1001  \t \t 55666778899.123  ", "Timestamp: 12345678901234.1001 55666778899.123\r\n", 1, true, true);
    _header_input_output.push_back(hdr5);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_To_Test::SIP_Header_To_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_TO, "To: G. Marconi <sip:Marconi@radio.org>", "To: G. Marconi <sip:Marconi@radio.org>\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_TO, "t: sip:+12125551212@server.phone2net.com;tag=287447", "To: <sip:+12125551212@server.phone2net.com>;tag=287447\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_TO, "To: \"Name\" <sip:+12125551212@server.phone2net.com ;par1 ;par2> ; tag=287447;parameter1 ", "To: \"Name\" <sip:+12125551212@server.phone2net.com;par1;par2>;tag=287447;parameter1\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_TO, "To: <sip:server.phone2net.com ;par1 ; lr ; maddr= 10.10.10.10 ;ttl=20; method= BYE; user=ip;transport= udp ;par2> ; tag=287447;parameter1 ", "To: <sip:server.phone2net.com;transport=udp;user=ip;method=BYE;ttl=20;maddr=10.10.10.10;lr;par1;par2>;tag=287447;parameter1\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_TO, "To: The Operator <sip:operator@cs.columbia.edu>;tag=287447", "To: The Operator <sip:operator@cs.columbia.edu>;tag=287447\r\n", 1, true, true);
    _header_input_output.push_back(hdr5);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Unsupported_Test::SIP_Header_Unsupported_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_UNSUPPORTED, "Unsupported: 100rel, foo", "Unsupported: 100rel, foo\r\n", 2, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_UNSUPPORTED, "Unsupported:foo1", "Unsupported: foo1\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_UNSUPPORTED, "Unsupported: 100rel, foo, bar  ", "Unsupported: 100rel, foo, bar\r\n", 3, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_User_Agent_Test::SIP_Header_User_Agent_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_USER_AGENT, "User-Agent: Softphone Beta1.5", "User-Agent: Softphone Beta1.5\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_USER_AGENT, "User-Agent:UA/1.5.0 Pro", "User-Agent: UA/1.5.0 Pro\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_USER_AGENT, "User-Agent:  user agent 1 ", "User-Agent: user agent 1\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Via_Test::SIP_Header_Via_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_VIA, "Via: SIP/2.0/UDP lab.high-voltage.org:5060;branch=z9hG4bKfw19b", "Via: SIP/2.0/UDP lab.high-voltage.org:5060;branch=z9hG4bKfw19b\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_VIA, "Via: SIP / 2.0 / UDP first.example.com: 4000  ;par1;maddr=224.2.0.1 ;ttl=16;branch=z9hG4bKa7c6a8dlze.1, SIP/2.0/UDP first.example.com", "Via: SIP/2.0/UDP first.example.com:4000;branch=z9hG4bKa7c6a8dlze.1;ttl=16;maddr=224.2.0.1;par1\r\nVia: SIP/2.0/UDP first.example.com\r\n", 2, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_VIA, "v: SIP/2.0/UDP lab.high-voltage.org;received=10.10.10.10;branch=z9hG4bKfw19b,SIP/2.0/UDP 11.11.11.11:5070;branch=z9hG4bKfw19b;parameter1 ", "Via: SIP/2.0/UDP lab.high-voltage.org;branch=z9hG4bKfw19b;received=10.10.10.10\r\nVia: SIP/2.0/UDP 11.11.11.11:5070;branch=z9hG4bKfw19b;parameter1\r\n", 2, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_VIA, "Via: SIP/2.0/UDP erlang.bell-telephone.com:5060;branch=z9hG4bK87asdks7", "Via: SIP/2.0/UDP erlang.bell-telephone.com:5060;branch=z9hG4bK87asdks7\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_VIA, "Via: SIP/2.0/UDP 192.0.2.1:5060 ;received=192.0.2.207;branch=z9hG4bK77asjd", "Via: SIP/2.0/UDP 192.0.2.1:5060;branch=z9hG4bK77asjd;received=192.0.2.207\r\n", 1, true, true);
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6(SIP_HEADER_VIA, "Via: SIP / 2.0 / UDP first.example.com: 4000;ttl=16 ;maddr=224.2.0.1 ;branch=z9hG4bKa7c6a8dlze.1", "Via: SIP/2.0/UDP first.example.com:4000;branch=z9hG4bKa7c6a8dlze.1;ttl=16;maddr=224.2.0.1\r\n", 1, true, true);
    _header_input_output.push_back(hdr6);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Warning_Test::SIP_Header_Warning_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_WARNING, "Warning: 370 devnull \"Choose a bigger pipe\"", "Warning: 370 devnull \"Choose a bigger pipe\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_WARNING, "Warning: 307 isi.edu \"Session parameter ’foo’ not understood\", 301 isi.edu \"Incompatible network address type ’E.164’\"", "Warning: 307 isi.edu \"Session parameter ’foo’ not understood\"\r\nWarning: 301 isi.edu \"Incompatible network address type ’E.164’\"\r\n", 2, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_WARNING, "Warning:  600 10.10.10.10 \"text\" ", "Warning: 600 10.10.10.10 \"text\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_WWW_Authenticate_Test::SIP_Header_WWW_Authenticate_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_WWW_AUTHENTICATE, "WWW-Authenticate: Digest realm=\"atlanta.com\", domain=\"sip:boxesbybob.com\", qop=\"auth\", nonce=\"f84f1cec41e6cbe5aea9c8e88d359\", opaque=\"\", stale=FALSE, algorithm=MD5", "WWW-Authenticate: Digest realm=\"atlanta.com\", domain=\"sip:boxesbybob.com\", nonce=\"f84f1cec41e6cbe5aea9c8e88d359\", opaque=\"\", stale=FALSE, algorithm=MD5, qop=\"auth\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_WWW_AUTHENTICATE, "WWW-Authenticate: Digest realm=\"biloxi.com\",qop=\"auth,auth-int\",  nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\",opaque=\"5ccc069c403ebaf9f0171e9517f40e41\"", "WWW-Authenticate: Digest realm=\"biloxi.com\", nonce=\"dcd98b7102dd2f0e8b11d0f600bfb0c093\", opaque=\"5ccc069c403ebaf9f0171e9517f40e41\", qop=\"auth,auth-int\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_WWW_AUTHENTICATE, "WWW-Authenticate: Digest nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\" ,   realm=\"atlanta.example.com\"", "WWW-Authenticate: Digest realm=\"atlanta.example.com\", nonce=\"ea9c8e88df84f1cec4341ae6cbe5a359\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_WWW_AUTHENTICATE, "WWW-Authenticate: Digest\trealm=\"myrealm.com\",nonce=\"123456789012345678901\", domain=\"sip:myrealm.com\",algorithm=MD5", "WWW-Authenticate: Digest realm=\"myrealm.com\", domain=\"sip:myrealm.com\", nonce=\"123456789012345678901\", algorithm=MD5\r\n", 1, true, true);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_WWW_AUTHENTICATE, "WWW-Authenticate: Scheme1 param1, param2=test, nonce=\"123456789012345678901\",realm=\"server.com\",domain=\"sip:server.com\",qop=\"auth, auth-int, value\", opaque=\"11223344556677889900aabbccddeeff\", stale=true, par3=\"test\", algorithm=XYZ", "WWW-Authenticate: Scheme1 realm=\"server.com\", domain=\"sip:server.com\", nonce=\"123456789012345678901\", opaque=\"11223344556677889900aabbccddeeff\", stale=true, algorithm=XYZ, qop=\"auth, auth-int, value\", param1, param2=test, par3=\"test\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr5);

    SIP_Header_Input_Output hdr6(SIP_HEADER_WWW_AUTHENTICATE, "WWW-Authenticate: scheme2 param1, param2=test,par3=\"test\"", "WWW-Authenticate: scheme2 param1, param2=test, par3=\"test\"\r\n", 1, true, true);
    _header_input_output.push_back(hdr6);
}

//-------------------------------------------
