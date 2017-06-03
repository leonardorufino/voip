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

#include "sip_message.h"
#include "sip_functions.h"
#include "sip_request.h"
#include "sip_response.h"

//-------------------------------------------

SIP_Message::SIP_Message(const SIP_Message &message)
{
    std::map<SIP_Header_Type, std::list<SIP_Header *>>::const_iterator it1 = message._headers.begin();
    while (it1 != message._headers.end())
    {
        std::list<SIP_Header *> header_list = it1->second;
        it1++;

        std::list<SIP_Header *>::iterator it2 = header_list.begin();
        while (it2 != header_list.end())
        {
            SIP_Header *header = *it2++;
            SIP_Header *new_header = SIP_Header::create_header(header->get_header_type(), header);
            add_header(new_header);
        }
    }
}

//-------------------------------------------

SIP_Message::~SIP_Message()
{
    std::map<SIP_Header_Type, std::list<SIP_Header *>>::iterator it1 = _headers.begin();
    while (it1 != _headers.end())
    {
        std::list<SIP_Header *> header_list = it1->second;
        it1++;

        std::list<SIP_Header *>::iterator it2 = header_list.begin();
        while (it2 != header_list.end())
            delete *it2++;
    }

    _headers.clear();
}

//-------------------------------------------

SIP_Message *SIP_Message::decode_msg(std::string sip_msg)
{
    SIP_Functions::remove_lws(sip_msg);

    std::string msg;
    SIP_Functions::match(sip_msg, " ", msg);
    SIP_Functions::trim(msg);

    SIP_Method_Type method = SIP_Functions::get_method_type(msg);
    if (method == SIP_METHOD_TYPE_INVALID)
    {
        std::cout << "SIP_Message::decode_msg -> Invalid method (method=" << msg.c_str() << ")\n";
        return NULL;
    }

    SIP_Message *message;
    if (method != SIP_RESPONSE)
        message = new SIP_Request(method);
    else
        message = new SIP_Response();

    if (!message->parse(sip_msg))
    {
        std::cout << "SIP_Message::decode_msg -> Failed to parse message (method=" << msg.c_str() << ")\n";
        delete message;
        return NULL;
    }

    return message;
}

//-------------------------------------------

bool SIP_Message::parse(std::string &sip_msg)
{
    if (!parse_start_line(sip_msg))
        return false;

    if (!parse_header(sip_msg))
        return false;

    if (!parse_body(sip_msg))
        return false;

    return true;
}

//-------------------------------------------

bool SIP_Message::parse_header(std::string &sip_msg)
{
    std::string line;
    while (true)
    {
        bool ret = SIP_Functions::get_line(sip_msg, line);
        if ((!ret) || (line.empty()))
            return true;

        if (!SIP_Header::decode_headers(line, _headers))
            return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Message::parse_body(std::string &sip_msg)
{
    SIP_Header_Content_Type *content_type = (SIP_Header_Content_Type *) get_header(SIP_HEADER_CONTENT_TYPE);
    if (content_type)
    {
        //TODO: Decode body
    }

    return true;
}

//-------------------------------------------

bool SIP_Message::encode(std::string &sip_msg)
{
    std::string body_msg;

    if (!encode_start_line(sip_msg))
        return false;

    if (!encode_body(body_msg))
        return false;

    if (!encode_header(sip_msg, body_msg))
        return false;

    return true;
}

//-------------------------------------------

bool SIP_Message::encode_header(std::string &sip_msg, std::string &body_msg)
{
    if (!SIP_Header::encode_headers(sip_msg, _headers))
        return false;

    sip_msg += "\r\n";
    sip_msg += body_msg;
    return true;
}

//-------------------------------------------

bool SIP_Message::encode_body(std::string &sip_msg)
{
    //TODO: Encode body
    return true;
}

//-------------------------------------------

void SIP_Message::add_header(SIP_Header *header)
{
    if (!header)
        return;

    SIP_Header_Type header_type = header->get_header_type();

    if (_headers.count(header_type) > 0)
    {
        std::list<SIP_Header *> &header_list = _headers.at(header_type);
        header_list.push_back(header);
    }else
    {
        std::list<SIP_Header *> header_list;
        header_list.push_back(header);
        _headers[header_type] = header_list;
    }
}

//-------------------------------------------

SIP_Header *SIP_Message::get_header(SIP_Header_Type header_type, unsigned short pos)
{
    if (_headers.count(header_type) == 0)
        return NULL;

    unsigned int count = 0;

    std::list<SIP_Header *> &header_list = _headers.at(header_type);
    std::list<SIP_Header *>::iterator it = header_list.begin();
    while (it != header_list.end())
    {
        SIP_Header *header = *it++;

        if (count++ == pos)
            return header;
    }

    return NULL;
}

//-------------------------------------------

unsigned int SIP_Message::get_num_header(SIP_Header_Type header_type)
{
    if (_headers.count(header_type) == 0)
        return 0;

    std::list<SIP_Header *> &header_list = _headers.at(header_type);
    return (unsigned int) header_list.size();
}

//-------------------------------------------
