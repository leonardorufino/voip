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
#include "sip_message.h"

class SIP_Response : public SIP_Message
{
public:
    static const unsigned short INVALID_STATUS_CODE = 0xFFFF;

public:
    SIP_Response() : _status_code(INVALID_STATUS_CODE) {}
    SIP_Response(unsigned short status_code);
    SIP_Response(const SIP_Response &response);
    ~SIP_Response() {}

    // Virtual pure functions
    bool parse_start_line(std::string &sip_msg);
    bool encode_start_line(std::string &sip_msg);
    SIP_Method_Type get_message_type() { return SIP_RESPONSE; }

    void set_sip_version(std::string sip_version) { _sip_version = sip_version; }
    std::string get_sip_version() { return _sip_version; }

    void set_status_code(unsigned short status_code) { _status_code = status_code; }
    unsigned short get_status_code() { return _status_code; }

    void set_reason_phraseip_version(std::string reason_phrase) { _reason_phrase = reason_phrase; }
    std::string get_reason_phrase() { return _reason_phrase; }

    void set_status_line(const std::string sip_version, unsigned short status_code, const std::string reason_phrase);

private:
    std::string _sip_version;
    unsigned short _status_code;
    std::string _reason_phrase;

private:
    struct SIP_Status_Code
    {
        unsigned short _code;
        std::string _reason_phrase;
    };

    static SIP_Status_Code _status_codes[];
};
