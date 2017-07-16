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
#include "common/log_manager.h"
#include <string>
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

protected:
    static Logger _logger;
};

//-------------------------------------------

class SIP_Request : public SIP_Message
{
public:
    SIP_Request(SIP_Method_Type method_type) : _method(method_type) {}
    SIP_Request(const SIP_Request &request);
    ~SIP_Request() {}

    // Virtual pure functions
    bool decode_start_line(std::string &sip_msg);
    bool encode_start_line(std::string &sip_msg);
    SIP_Method_Type get_message_type() { return _method; }

    void set_method(SIP_Method_Type method) { _method = method; }

    SIP_Address &get_request_uri() { return _request_uri; }

    void set_sip_version(std::string sip_version) { _sip_version = sip_version; }
    std::string get_sip_version() { return _sip_version; }

    void set_request_line(SIP_Method_Type msg_type, const SIP_Address &request_uri, std::string sip_version);

private:
    SIP_Method_Type _method;
    SIP_Address _request_uri;
    std::string _sip_version;
};

//-------------------------------------------

class SIP_Response : public SIP_Message
{
public:
    static const unsigned short INVALID_STATUS_CODE = INVALID_UNSIGNED_SHORT;

public:
    SIP_Response() : _status_code(INVALID_STATUS_CODE) {}
    SIP_Response(unsigned short status_code);
    SIP_Response(const SIP_Response &response);
    ~SIP_Response() {}

    // Virtual pure functions
    bool decode_start_line(std::string &sip_msg);
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

//-------------------------------------------
