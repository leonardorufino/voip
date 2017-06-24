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
#include <list>

class SIP_URI
{
public:
    static const unsigned short INVALID_PORT = INVALID_UNSIGNED_SHORT;
    static const unsigned short INVALID_TTL = INVALID_UNSIGNED_SHORT;

public:
    SIP_URI() : _port(INVALID_PORT), _ttl(INVALID_TTL), _lr(false) {}
    SIP_URI(const SIP_URI &value) { *this = value; }
    ~SIP_URI() {}

    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_user(std::string user) { _user = user; }
    std::string get_user() { return _user; }

    void set_password(std::string password) { _password = password; }
    std::string get_password() { return _password; }

    void set_host(std::string host) { _host = host; }
    std::string get_host() { return _host; }

    void set_port(unsigned short port) { _port = port; }
    unsigned short get_port() { return _port; }

    void set_transport(SIP_Transport_Type transport);
    void set_transport(std::string transport) { _transport = transport; }
    SIP_Transport_Type get_transport();
    std::string get_transport_str() { return _transport; }

    void set_user_param(SIP_User_Param user_param);
    void set_user_param(std::string user_param) { _user_param = user_param; }
    SIP_User_Param get_user_param();
    std::string get_user_param_str() { return _user_param; }

    void set_method(SIP_Method_Type method);
    void set_method(std::string method) { _method = method; }
    SIP_Method_Type get_method();
    std::string get_method_str() { return _method; }

    void set_ttl(unsigned short ttl) { _ttl = ttl; }
    unsigned short get_ttl() { return _ttl; }

    void set_maddr(std::string maddr) { _maddr = maddr; }
    std::string get_maddr() { return _maddr; }

    void set_lr(bool lr) { _lr = lr; }
    bool is_lr() { return _lr; }

    std::list<std::string> &get_parameters() { return _parameters; }

    std::list<std::string> &get_headers() { return _headers; }

private:
    std::string _user;
    std::string _password;
    std::string _host;
    unsigned short _port;

    std::string _transport;
    std::string _user_param;
    std::string _method;
    unsigned short _ttl;
    std::string _maddr;
    bool _lr;
    std::list<std::string> _parameters;
    std::list<std::string> _headers;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Absolute_URI
{
public:
    SIP_Absolute_URI() {}
    SIP_Absolute_URI(const SIP_Absolute_URI &value) { *this = value; }
    ~SIP_Absolute_URI() {}

    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_address(std::string address) { _address = address; }
    std::string get_address() { return _address; }

private:
    std::string _address;
};

//-------------------------------------------

class SIP_Address
{
public:
    SIP_Address() : _display_name_double_quote(true), _uri_angle_quote(true) {}
    SIP_Address(const SIP_Address &value) { *this = value; }
    ~SIP_Address() {}

    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_display_name_double_quote(bool quote) { _display_name_double_quote = quote; }
    bool get_display_name_double_quote() { return _display_name_double_quote; }

    void set_display_name(std::string display_name) { _display_name = display_name; }
    std::string get_display_name() { return _display_name; }

    void set_scheme(SIP_Address_Scheme scheme);
    void set_scheme(std::string scheme) { _scheme = scheme; }
    SIP_Address_Scheme get_scheme();
    std::string get_scheme_str() { return _scheme; }

    void set_uri_angle_quote(bool quote) { _uri_angle_quote = quote; }
    bool get_uri_angle_quote() { return _uri_angle_quote; }

    SIP_URI &get_sip_uri() { return _sip_uri; }
    SIP_Absolute_URI &get_absolute_uri() { return _absolute_uri; }

private:
    bool _display_name_double_quote;
    std::string _display_name;
    std::string _scheme;

    bool _uri_angle_quote;
    SIP_URI _sip_uri;
    SIP_Absolute_URI _absolute_uri;
};

//-------------------------------------------
