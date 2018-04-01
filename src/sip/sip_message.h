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
#include "sip_body.h"
#include "util/util_defs.h"
#include "util/log_manager.h"
#include <string>
#include <map>
#include <list>

typedef std::map<SIP_Header_Type, sip_header_list> sip_header_map;
typedef std::list<SIP_Body *> sip_body_list;

class SIP_Message
{
public:
    SIP_Message() {}
    SIP_Message(const SIP_Message &message);
    virtual ~SIP_Message();

    static SIP_Message *decode_message(const char *msg, unsigned short size, unsigned short &read);

    virtual SIP_Method_Type get_message_type() = 0;

    bool decode(const char *msg, unsigned short size, unsigned short &read);
    virtual bool decode_start_line(std::string &msg) = 0;
    bool decode_header(std::string &msg);
    bool decode_body(const char *body, unsigned short size);

    bool encode(char *msg, unsigned short &size);
    virtual bool encode_start_line(std::string &msg) = 0;
    bool encode_header(std::string &msg);
    bool encode_body(char *body, unsigned short &size);

    bool add_header(SIP_Header *header, unsigned short pos = 0xFFFF);
    bool add_headers(sip_header_list &headers);
    bool remove_header(SIP_Header_Type header_type, unsigned short pos);
    void clear_headers();
    SIP_Header *get_header(SIP_Header_Type header_type, unsigned short pos = 0);
    unsigned short get_header_size(SIP_Header_Type header_type);

    bool add_body(SIP_Body *body, unsigned short pos = 0xFFFF);
    bool remove_body(unsigned short pos);
    void clear_bodies();
    SIP_Body *get_body(unsigned short pos = 0);
    unsigned short get_body_size() { return (unsigned short) _bodies.size(); }

private:
    sip_header_map _headers;
    sip_body_list _bodies;

protected:
    static Logger _logger;
};

//-------------------------------------------

class SIP_Request : public SIP_Message
{
public:
    SIP_Request(SIP_Method_Type method);
    SIP_Request(const SIP_Request &request);
    ~SIP_Request() {}

    // Virtual pure functions
    SIP_Method_Type get_message_type() { return get_method_enum(); }
    bool decode_start_line(std::string &msg);
    bool encode_start_line(std::string &msg);

    void set_request_line(SIP_Method_Type method, const SIP_Address &request_uri, std::string sip_version);

    void set_method(SIP_Method_Type method);
    void set_method(std::string method) { _method = method; }
    SIP_Method_Type get_method_enum();
    std::string get_method() { return _method; }

    void set_request_uri(const SIP_Address &request_uri);
    SIP_Address &get_request_uri() { return _request_uri; }

    void set_sip_version(std::string sip_version) { _sip_version = sip_version; }
    std::string get_sip_version() { return _sip_version; }

private:
    std::string _method;
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
    SIP_Response(const SIP_Response &response);
    SIP_Response(unsigned short status_code);
    SIP_Response(unsigned short status_code, SIP_Request &request);
    ~SIP_Response() {}

    // Virtual pure functions
    SIP_Method_Type get_message_type() { return SIP_RESPONSE; }
    bool decode_start_line(std::string &msg);
    bool encode_start_line(std::string &msg);

    void set_status_line(const std::string sip_version, unsigned short status_code, const std::string reason_phrase);

    void set_sip_version(std::string sip_version) { _sip_version = sip_version; }
    std::string get_sip_version() { return _sip_version; }

    void set_status_code(unsigned short status_code) { _status_code = status_code; }
    bool set_status_code(std::string status_code);
    unsigned short get_status_code() { return _status_code; }
    bool get_status_code(std::string &status_code);

    void set_reason_phrase(std::string reason_phrase) { _reason_phrase = reason_phrase; }
    std::string get_reason_phrase() { return _reason_phrase; }

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
