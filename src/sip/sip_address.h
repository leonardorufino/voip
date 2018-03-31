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
#include "util/util_defs.h"
#include "util/log_manager.h"
#include "util/parameter_list.h"
#include "util/socket.h"
#include <string>
#include <list>

class SIP_Host
{
public:
    SIP_Host() {}
    SIP_Host(const SIP_Host &value) { *this = value; }
    ~SIP_Host() {}

    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_address(std::string address) { _address = address; }
    std::string get_address() { return _address; }

private:
    std::string _address;

    static Logger _logger;
};

//-------------------------------------------

class SIP_URI
{
public:
    static const unsigned short INVALID_PORT = INVALID_UNSIGNED_SHORT;
    static const unsigned short INVALID_TTL = INVALID_UNSIGNED_SHORT;

    enum User_Param
    {
        USER_PARAM_PHONE,
        USER_PARAM_IP,
        USER_PARAM_INVALID
    };

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

    void set_host(const SIP_Host &host) { _host = host; }
    SIP_Host &get_host() { return _host; }

    void set_port(unsigned short port) { _port = port; }
    bool set_port(std::string port);
    unsigned short get_port() { return _port; }
    bool get_port(std::string &port);

    void set_transport(SIP_Transport_Type transport);
    void set_transport(std::string transport) { _transport = transport; }
    SIP_Transport_Type get_transport_enum();
    std::string get_transport() { return _transport; }

    void set_user_param(User_Param user_param);
    void set_user_param(std::string user_param) { _user_param = user_param; }
    User_Param get_user_param_enum();
    std::string get_user_param() { return _user_param; }

    void set_method(SIP_Method_Type method);
    void set_method(std::string method) { _method = method; }
    SIP_Method_Type get_method_enum();
    std::string get_method() { return _method; }

    void set_ttl(unsigned short ttl) { _ttl = ttl; }
    bool set_ttl(std::string ttl);
    unsigned short get_ttl() { return _ttl; }
    bool get_ttl(std::string &ttl);

    void set_maddr(const SIP_Host &maddr) { _maddr = maddr; }
    SIP_Host &get_maddr() { return _maddr; }

    void set_lr(bool lr) { _lr = lr; }
    bool is_lr() { return _lr; }

    void set_parameters(const Parameter_List &parameters) { _parameters = parameters; }
    Parameter_List &get_parameters() { return _parameters; }

    void set_headers(const Parameter_List &headers) { _headers = headers; }
    Parameter_List &get_headers() { return _headers; }

private:
    std::string _user;
    std::string _password;
    SIP_Host _host;
    unsigned short _port;

    std::string _transport;
    std::string _user_param;
    std::string _method;
    unsigned short _ttl;
    SIP_Host _maddr;
    bool _lr;
    Parameter_List _parameters;
    Parameter_List _headers;

    static Logger _logger;
};

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

    static Logger _logger;
};

//-------------------------------------------

class SIP_Address
{
public:
    enum Scheme
    {
        SCHEME_SIP,
        SCHEME_SIPS,
        SCHEME_INVALID
    };

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

    void set_scheme(Scheme scheme);
    void set_scheme(std::string scheme) { _scheme = scheme; }
    Scheme get_scheme_enum();
    std::string get_scheme() { return _scheme; }

    void set_uri_angle_quote(bool quote) { _uri_angle_quote = quote; }
    bool get_uri_angle_quote() { return _uri_angle_quote; }

    void set_sip_uri(const SIP_URI &uri) { _sip_uri = uri; }
    SIP_URI &get_sip_uri() { return _sip_uri; }

    void set_absolute_uri(const SIP_Absolute_URI &uri) { _absolute_uri = uri; }
    SIP_Absolute_URI &get_absolute_uri() { return _absolute_uri; }

private:
    bool _display_name_double_quote;
    std::string _display_name;
    std::string _scheme;

    bool _uri_angle_quote;
    SIP_URI _sip_uri;
    SIP_Absolute_URI _absolute_uri;

    static Logger _logger;
};

//-------------------------------------------
