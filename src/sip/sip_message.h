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

#include "sip_defs.h"
#include "sip_header.h"
#include <map>
#include <list>

typedef std::map<SIP_Header_Type, sip_header_list> sip_header_map;

class SIP_Message
{
public:
    SIP_Message() {}
    SIP_Message(const SIP_Message &message);
    virtual ~SIP_Message();

    static SIP_Message *decode_msg(std::string sip_msg);

    virtual SIP_Method_Type get_message_type() = 0;

    bool decode(std::string &sip_msg);
    virtual bool decode_start_line(std::string &sip_msg) = 0;
    bool decode_header(std::string &sip_msg);
    bool decode_body(std::string &sip_msg);

    bool encode(std::string &sip_msg);
    virtual bool encode_start_line(std::string &sip_msg) = 0;
    bool encode_header(std::string &sip_msg, std::string &body_msg);
    bool encode_body(std::string &sip_msg);

    void add_header(SIP_Header *header);
    void add_headers(sip_header_list &headers);

    SIP_Header *get_header(SIP_Header_Type header_type, unsigned short pos = 0);
    unsigned short get_num_header(SIP_Header_Type header_type);

private:
    sip_header_map _headers;
};
