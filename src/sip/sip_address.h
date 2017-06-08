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
    static const unsigned short INVALID_PORT = 0xFFFF;

public:
    SIP_URI() : _port(INVALID_PORT), _lr(false) {}
    SIP_URI(const SIP_URI &value) { *this = value; }
    ~SIP_URI() {}

    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_user(std::string user) { _user = user; }
    std::string get_user() { return _user; }

    void set_host(std::string host) { _host = host; }
    std::string get_host() { return _host; }

    void set_port(unsigned short port) { _port = port; }
    unsigned short get_port() { return _port; }

    void set_lr(bool lr) { _lr = lr; }
    bool is_lr() { return _lr; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    std::string _user;
    std::string _host;
    unsigned short _port;

    bool _lr;
    std::list<std::string> _parameters;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Absolute_URI
{
public:
    SIP_Absolute_URI() {}
    SIP_Absolute_URI(const SIP_Absolute_URI &value) { *this = value; }
    ~SIP_Absolute_URI() {}

    bool parse(std::string &sip_msg);
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
    SIP_Address() {}
    SIP_Address(const SIP_Address &value) { *this = value; }
    ~SIP_Address() {}

    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_display_name(std::string display_name) { _display_name = display_name; }
    std::string get_display_name() { return _display_name; }

    void set_scheme(SIP_Address_Scheme scheme);
    void set_scheme(std::string scheme) { _scheme = scheme; }
    SIP_Address_Scheme get_scheme();
    std::string get_scheme_str() { return _scheme; }

    SIP_URI &get_sip_uri() { return _sip_uri; }
    SIP_Absolute_URI &get_absolute_uri() { return _absolute_uri; }

private:
    std::string _display_name;
    std::string _scheme;

    SIP_URI _sip_uri;
    SIP_Absolute_URI _absolute_uri;
};

//-------------------------------------------
