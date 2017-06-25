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
