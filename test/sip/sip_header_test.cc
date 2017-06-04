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

    SIP_Header_Allow_Test header_allow;
    if (!header_allow.run())
        return false;

    SIP_Header_Allow_Events_Test header_allow_events;
    if (!header_allow_events.run())
        return false;

    SIP_Header_Call_ID_Test header_call_id;
    if (!header_call_id.run())
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

    SIP_Header_Record_Route_Test header_record_route;
    if (!header_record_route.run())
        return false;

    SIP_Header_Require_Test header_require;
    if (!header_require.run())
        return false;

    SIP_Header_Route_Test header_route;
    if (!header_route.run())
        return false;

    SIP_Header_Subscription_State_Test header_subscription_state;
    if (!header_subscription_state.run())
        return false;

    SIP_Header_To_Test header_to;
    if (!header_to.run())
        return false;

    SIP_Header_Unsupported_Test header_unsupported;
    if (!header_unsupported.run())
        return false;

    SIP_Header_Via_Test header_via;
    if (!header_via.run())
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
        if (!SIP_Header::decode_headers(input, headers))
        {
            std::cout << "SIP_Header_Test::run -> Failed to decode headers:\n";
            std::cout << std::setw(12) << "Type: " << header_input_output._header_type << "\n";
            std::cout << std::setw(12) << "Input: " << header_input_output._input.c_str() << "\n";
            return false;
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
        if (!SIP_Header::encode_headers(output, headers))
        {
            std::cout << "SIP_Header_Test::run -> Failed to encode headers:\n";
            std::cout << std::setw(12) << "Type: " << header_input_output._header_type << "\n";
            std::cout << std::setw(12) << "Input: " << header_input_output._input.c_str() << "\n";
            return false;
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
    SIP_Header_Input_Output hdr1(SIP_HEADER_ACCEPT, "Accept: application/sdp", "Accept: application/sdp\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_ACCEPT, "Accept:application/sdp;level=1, application/x-private, text/html", "Accept: application/sdp;level=1, application/x-private, text/html\r\n", 3);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_ACCEPT, "Accept: */*;q=0.75,application/*,   text/html,test1/test2", "Accept: */*;q=0.75, application/*, text/html, test1/test2\r\n", 4);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Accept_Encoding_Test::SIP_Header_Accept_Encoding_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_ACCEPT_ENCODING, "Accept-Encoding: gzip, text/plain", "Accept-Encoding: gzip, text/plain\r\n", 2);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_ACCEPT_ENCODING, "Accept-Encoding: ", "Accept-Encoding: \r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_ACCEPT_ENCODING, "Accept-Encoding: *;q=0.75,code1,   code2;par1,code3", "Accept-Encoding: *;q=0.75, code1, code2;par1, code3\r\n", 4);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Accept_Language_Test::SIP_Header_Accept_Language_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_ACCEPT_LANGUAGE, "Accept-Language: pt", "Accept-Language: pt\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_ACCEPT_LANGUAGE, "Accept-Language:", "Accept-Language: \r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_ACCEPT_LANGUAGE, "Accept-Language: da, en-gb;q=0.8, en ;q=0.7, *", "Accept-Language: da, en-gb;q=0.8, en;q=0.7, *\r\n", 4);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Allow_Test::SIP_Header_Allow_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_ALLOW, "Allow: INVITE", "Allow: INVITE\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_ALLOW, "Allow: INVITE, ACK,  OPTIONS, CANCEL,BYE", "Allow: INVITE, ACK, OPTIONS, CANCEL, BYE\r\n", 5);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_ALLOW, "Allow:NOTIFY,REFER,   TEST  ", "Allow: NOTIFY, REFER, TEST\r\n", 3);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_ALLOW, "Allow:", "Allow: \r\n", 1);
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Allow_Events_Test::SIP_Header_Allow_Events_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_ALLOW_EVENTS, "Allow-Events: presence", "Allow-Events: presence\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_ALLOW_EVENTS, "Allow-Events:presence, test1.test2", "Allow-Events: presence, test1.test2\r\n", 2);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_ALLOW_EVENTS, "u: presence.template1.template2 , test.template,package-xyz", "Allow-Events: presence.template1.template2, test.template, package-xyz\r\n", 3);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Call_ID_Test::SIP_Header_Call_ID_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CALLID, "Call-ID: 123456789@my-domain.org", "Call-ID: 123456789@my-domain.org\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CALLID, "Call-ID: 123456789", "Call-ID: 123456789\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CALLID, "i:my-domain.org ", "Call-ID: my-domain.org\r\n", 1);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Contact_Test::SIP_Header_Contact_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CONTACT, "Contact: sip:123456789@my-domain.org", "Contact: <sip:123456789@my-domain.org>\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CONTACT, "Contact: sips:my-domain.org:5060;parameter1;parameter2;expires=60;parameter3;q=1.0", "Contact: <sips:my-domain.org:5060>;expires=60;q=1.0;parameter1;parameter2;parameter3\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CONTACT, "Contact:   Display name here <sip:my-domain.org;par;lr>;parameter1  ;q=0.5;  parameter2,tel:+123456789;par", "Contact: Display name here <sip:my-domain.org;lr;par>;q=0.5;parameter1;parameter2\r\nContact: <tel:+123456789>;par\r\n", 2);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_CONTACT, "Contact: \"Mr. Watson\" <sip:watson@worcester.bell-telephone.com;lr;par1> ;q=0.7 ;expires=3600, \"Mr. Watson\" <mailto:watson@bell-telephone.com> ;q=0.1", "Contact: \"Mr. Watson\" <sip:watson@worcester.bell-telephone.com;lr;par1>;expires=3600;q=0.7\r\nContact: \"Mr. Watson\" <mailto:watson@bell-telephone.com>;q=0.1\r\n", 2);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_CONTACT, "m: *", "Contact: *\r\n", 1);
    _header_input_output.push_back(hdr5);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Disposition_Test::SIP_Header_Content_Disposition_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CONTENT_DISPOSITION, "Content-Disposition: session;handling=required;par1", "Content-Disposition: session;handling=required;par1\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CONTENT_DISPOSITION, "Content-Disposition:   alert  ;  handling=  optional ; par1 ; par2;par3", "Content-Disposition: alert;handling=optional;par1;par2;par3\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CONTENT_DISPOSITION, "Content-Disposition: attachment; filename=smime.p7s;handling=required", "Content-Disposition: attachment;handling=required;filename=smime.p7s\r\n", 1);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_CONTENT_DISPOSITION, "Content-Disposition: render", "Content-Disposition: render\r\n", 1);
    _header_input_output.push_back(hdr4);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Encoding_Test::SIP_Header_Content_Encoding_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CONTENT_ENCODING, "Content-Encoding: text/plain, gzip", "Content-Encoding: text/plain, gzip\r\n", 2);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CONTENT_ENCODING, "Content-Encoding:   code1 ", "Content-Encoding: code1\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CONTENT_ENCODING, "Content-Encoding: code1,code2 , code3", "Content-Encoding: code1, code2, code3\r\n", 3);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Language_Test::SIP_Header_Content_Language_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CONTENT_LANGUAGE, "Content-Language: pt", "Content-Language: pt\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CONTENT_LANGUAGE, "Content-Language:  en,fr ", "Content-Language: en, fr\r\n", 2);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CONTENT_LANGUAGE, "Content-Language:pt,en, fr", "Content-Language: pt, en, fr\r\n", 3);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Length_Test::SIP_Header_Content_Length_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CONTENT_LENGTH, "Content-Length: 0", "Content-Length: 0\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CONTENT_LENGTH, "Content-Length: 5678", "Content-Length: 5678\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CONTENT_LENGTH, "l:50 ", "Content-Length: 50\r\n", 1);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Content_Type_Test::SIP_Header_Content_Type_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CONTENT_TYPE, "Content-Type: application/sdp", "Content-Type: application/sdp\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CONTENT_TYPE, "c: text/html; charset=ISO-8859-4", "Content-Type: text/html;charset=ISO-8859-4\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CONTENT_TYPE, "Content-Type:type1/sub1  ;par1;par2  ;  par3 ", "Content-Type: type1/sub1;par1;par2;par3\r\n", 1);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_CSeq_Test::SIP_Header_CSeq_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_CSEQ, "CSeq: 1 INVITE", "CSeq: 1 INVITE\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_CSEQ, "CSeq: 9876 TEST", "CSeq: 9876 TEST\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_CSEQ, "CSeq:0    ACK   ", "CSeq: 0 ACK\r\n", 1);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Date_Test::SIP_Header_Date_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_DATE, "Date: Fri, 1 Oct 1990 00:10:59 GMT", "Date: Fri, 01 Oct 1990 00:10:59 GMT\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_DATE, "Date: Wed, 10 Feb 2001 23:00:20 GMT", "Date: Wed, 10 Feb 2001 23:00:20 GMT\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_DATE, "Date: Mon, 31 Dec 2010 12:59:05 GM", "Date: Mon, 31 Dec 2010 12:59:05 GM\r\n", 1);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Event_Test::SIP_Header_Event_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_EVENT, "Event: presence", "Event: presence\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_EVENT, "Event: test; id=1234", "Event: test;id=1234\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_EVENT, "Event:  package.template1.template2  ; par1 ; id= 567 ;par2 ", "Event: package.template1.template2;id=567;par1;par2\r\n", 1);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Expires_Test::SIP_Header_Expires_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_EXPIRES, "Expires: 3600", "Expires: 3600\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_EXPIRES, "Expires: 0", "Expires: 0\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_EXPIRES, "Expires:    567890 ", "Expires: 567890\r\n", 1);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_From_Test::SIP_Header_From_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_FROM, "From: Nikola Tesla <sip:n.tesla@high-voltage.org>;tag=76341", "From: Nikola Tesla <sip:n.tesla@high-voltage.org>;tag=76341\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_FROM, "f: Anonymous <sip:c8oqz84zk7z@privacy.org>", "From: Anonymous <sip:c8oqz84zk7z@privacy.org>\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_FROM, "From:  \"Nikola Tesla\"   <sip:n.tesla@high-voltage.org;par1  ; par2  ;par3>;parameter1;tag=76341 ", "From: \"Nikola Tesla\" <sip:n.tesla@high-voltage.org;par1;par2;par3>;tag=76341;parameter1\r\n", 1);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_In_Reply_To_Test::SIP_Header_In_Reply_To_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_IN_REPLY_TO, "In-Reply-To: 70710@saturn.bell-tel.com, 17320@saturn.bell-tel.com", "In-Reply-To: 70710@saturn.bell-tel.com, 17320@saturn.bell-tel.com\r\n", 2);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_IN_REPLY_TO, "In-Reply-To: 123456789", "In-Reply-To: 123456789\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_IN_REPLY_TO, "In-Reply-To:my-domain.org , test@domain.com:1234", "In-Reply-To: my-domain.org, test@domain.com:1234\r\n", 2);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Max_Forwards_Test::SIP_Header_Max_Forwards_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_MAX_FORWARDS, "Max-Forwards: 70", "Max-Forwards: 70\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_MAX_FORWARDS, "Max-Forwards:   56789  ", "Max-Forwards: 56789\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_MAX_FORWARDS, "Max-Forwards:1", "Max-Forwards: 1\r\n", 1);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Mime_Version_Test::SIP_Header_Mime_Version_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_MIME_VERSION, "MIME-Version: 1.0", "MIME-Version: 1.0\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_MIME_VERSION, "MIME-Version:   2.5  ", "MIME-Version: 2.5\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_MIME_VERSION, "MIME-Version:0.0", "MIME-Version: 0.0\r\n", 1);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Min_Expires_Test::SIP_Header_Min_Expires_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_MIN_EXPIRES, "Min-Expires: 3600", "Min-Expires: 3600\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_MIN_EXPIRES, "Min-Expires:0", "Min-Expires: 0\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_MIN_EXPIRES, "Min-Expires:    567890 ", "Min-Expires: 567890\r\n", 1);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Organization_Test::SIP_Header_Organization_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_ORGANIZATION, "Organization: Boxes by Bob", "Organization: Boxes by Bob\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_ORGANIZATION, "Organization:", "Organization: \r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_ORGANIZATION, "Organization:   ABC ", "Organization: ABC\r\n", 1);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Priority_Test::SIP_Header_Priority_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_PRIORITY, "Priority: normal", "Priority: normal\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_PRIORITY, "Priority:urgent  ", "Priority: urgent\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_PRIORITY, "Priority:my-priority", "Priority: my-priority\r\n", 1);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Record_Route_Test::SIP_Header_Record_Route_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_RECORD_ROUTE, "Record-Route: <sip:server10.biloxi.com;lr>, <sip:bigbox3.site3.atlanta.com;lr>", "Record-Route: <sip:server10.biloxi.com;lr>\r\nRecord-Route: <sip:bigbox3.site3.atlanta.com;lr>\r\n", 2);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_RECORD_ROUTE, "Record-Route:   <sip:user@server10.biloxi.com;par1>;parameter1, <sip:bigbox3.site3.atlanta.com;par1;lr;par2>", "Record-Route: <sip:user@server10.biloxi.com;par1>;parameter1\r\nRecord-Route: <sip:bigbox3.site3.atlanta.com;lr;par1;par2>\r\n", 2);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_RECORD_ROUTE, "Record-Route: <sip:n.tesla@high-voltage.org;par1  ; par2  ;par3> ;  parameter1;parameter2 , <sip:c8oqz84zk7z@privacy.org> ; parameter1", "Record-Route: <sip:n.tesla@high-voltage.org;par1;par2;par3>;parameter1;parameter2\r\nRecord-Route: <sip:c8oqz84zk7z@privacy.org>;parameter1\r\n", 2);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Require_Test::SIP_Header_Require_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_REQUIRE, "Require: foo", "Require: foo\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_REQUIRE, "Require: req1, req2,req3", "Require: req1, req2, req3\r\n", 3);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_REQUIRE, "Require:req1,req2", "Require: req1, req2\r\n", 2);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Route_Test::SIP_Header_Route_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_ROUTE, "Route: <sip:bigbox3.site3.atlanta.com;lr>, <sip:server10.biloxi.com;lr>", "Route: <sip:bigbox3.site3.atlanta.com;lr>\r\nRoute: <sip:server10.biloxi.com;lr>\r\n", 2);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_ROUTE, "Route: <sip:server13.atlanta.com;lr>", "Route: <sip:server13.atlanta.com;lr>\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_ROUTE, "Route:   <sip:server1.atlanta.com ; transport=udp ; user=phone  ;  lr > ", "Route: <sip:server1.atlanta.com;lr;transport=udp;user=phone>\r\n", 1);
    _header_input_output.push_back(hdr3);

    SIP_Header_Input_Output hdr4(SIP_HEADER_ROUTE, "Route: <sip:server2.atlanta.com;transport=udp;user=phone>;lr", "Route: <sip:server2.atlanta.com;transport=udp;user=phone>;lr\r\n", 1);
    _header_input_output.push_back(hdr4);

    SIP_Header_Input_Output hdr5(SIP_HEADER_ROUTE, "Route: <sip:server3.atlanta.com ; transport=udp;lr> ; teste ; lr ", "Route: <sip:server3.atlanta.com;lr;transport=udp>;teste;lr\r\n", 1);
    _header_input_output.push_back(hdr5);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Subscription_State_Test::SIP_Header_Subscription_State_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_SUBSCRIPTION_STATE, "Subscription-State: active;expires=600", "Subscription-State: active;expires=600\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_SUBSCRIPTION_STATE, "Subscription-State: state1 ; expires= 500", "Subscription-State: state1;expires=500\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_SUBSCRIPTION_STATE, "Subscription-State: terminated; reason=timeout ; retry-after=400 ", "Subscription-State: terminated;reason=timeout;retry-after=400\r\n", 1);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_To_Test::SIP_Header_To_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_TO, "To: G. Marconi <sip:Marconi@radio.org>", "To: G. Marconi <sip:Marconi@radio.org>\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_TO, "t: sip:+12125551212@server.phone2net.com;tag=287447", "To: <sip:+12125551212@server.phone2net.com>;tag=287447\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_TO, "To: \"Name\" <sip:+12125551212@server.phone2net.com ;par1 ;par2> ; tag=287447;parameter1 ", "To: \"Name\" <sip:+12125551212@server.phone2net.com;par1;par2>;tag=287447;parameter1\r\n", 1);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Unsupported_Test::SIP_Header_Unsupported_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_UNSUPPORTED, "Unsupported: 100rel, foo", "Unsupported: 100rel, foo\r\n", 2);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_UNSUPPORTED, "Unsupported:foo1", "Unsupported: foo1\r\n", 1);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_UNSUPPORTED, "Unsupported: 100rel, foo, bar  ", "Unsupported: 100rel, foo, bar\r\n", 3);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Via_Test::SIP_Header_Via_Test()
{
    SIP_Header_Input_Output hdr1(SIP_HEADER_VIA, "Via: SIP/2.0/UDP lab.high-voltage.org:5060;branch=z9hG4bKfw19b", "Via: SIP/2.0/UDP lab.high-voltage.org:5060;branch=z9hG4bKfw19b\r\n", 1);
    _header_input_output.push_back(hdr1);

    SIP_Header_Input_Output hdr2(SIP_HEADER_VIA, "Via: SIP / 2.0 / UDP first.example.com: 4000;ttl=16;maddr=224.2.0.1;branch=z9hG4bKa7c6a8dlze.1, SIP/2.0/UDP first.example.com", "Via: SIP/2.0/UDP first.example.com:4000;branch=z9hG4bKa7c6a8dlze.1;ttl=16;maddr=224.2.0.1\r\nVia: SIP/2.0/UDP first.example.com\r\n", 2);
    _header_input_output.push_back(hdr2);

    SIP_Header_Input_Output hdr3(SIP_HEADER_VIA, "v: SIP/2.0/UDP lab.high-voltage.org;received=10.10.10.10;branch=z9hG4bKfw19b,SIP/2.0/UDP 11.11.11.11:5070;branch=z9hG4bKfw19b;parameter1 ", "Via: SIP/2.0/UDP lab.high-voltage.org;branch=z9hG4bKfw19b;received=10.10.10.10\r\nVia: SIP/2.0/UDP 11.11.11.11:5070;branch=z9hG4bKfw19b;parameter1\r\n", 2);
    _header_input_output.push_back(hdr3);
}

//-------------------------------------------
