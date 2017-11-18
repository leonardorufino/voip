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

#include "sdp_defs.h"
#include "util/util_defs.h"
#include "util/log_manager.h"
#include <string>
#include <list>

class SDP_Field;
typedef std::list<SDP_Field *> sdp_field_list;

class SDP_Field
{
public:
    SDP_Field() {}
    virtual ~SDP_Field() {}

    static SDP_Field *create_field(SDP_Field_Type field_type, const SDP_Field *copy = NULL);
    static bool decode_fields(std::string &msg, sdp_field_list &fields);
    static bool encode_fields(std::string &msg, sdp_field_list &fields);

    // Virtual pure functions
    virtual SDP_Field_Type get_field_type() = 0;
    virtual bool decode(std::string &msg) = 0;
    virtual bool encode(std::string &msg) = 0;

protected:
    std::string _field_line;

    static Logger _logger;
};

//-------------------------------------------
//-------------------------------------------

class SDP_Field_Protocol_Version : public SDP_Field
{
public:
    static const unsigned short INVALID_VERSION = INVALID_UNSIGNED_SHORT;

public:
    SDP_Field_Protocol_Version() : _version(INVALID_VERSION) {}
    SDP_Field_Protocol_Version(const SDP_Field_Protocol_Version &field) { *this = field; }
    ~SDP_Field_Protocol_Version() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_PROTOCOL_VERSION; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_version(unsigned short version) { _version = version; }
    unsigned short get_version() { return _version; }

private:
    unsigned short _version;
};

//-------------------------------------------

class SDP_Field_Origin : public SDP_Field
{
public:
    SDP_Field_Origin() {}
    SDP_Field_Origin(const SDP_Field_Origin &field) { *this = field; }
    ~SDP_Field_Origin() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_ORIGIN; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_username(std::string username) { _username = username; }
    std::string get_username() { return _username; }

    void set_session_id(std::string id) { _session_id = id; }
    std::string get_session_id() { return _session_id; }

    void set_session_version(std::string version) { _session_version = version; }
    std::string get_session_version() { return _session_version; }

    void set_network_type(std::string type) { _network_type = type; }
    std::string get_network_type() { return _network_type; }

    void set_address_type(std::string type) { _address_type = type; }
    std::string get_address_type() { return _address_type; }

    void set_unicast_address(std::string address) { _unicast_address = address; }
    std::string get_unicast_address() { return _unicast_address; }

private:
    std::string _username;
    std::string _session_id;
    std::string _session_version;
    std::string _network_type;
    std::string _address_type;
    std::string _unicast_address;
};

//-------------------------------------------

class SDP_Field_Session_Name : public SDP_Field
{
public:
    SDP_Field_Session_Name() {}
    SDP_Field_Session_Name(const SDP_Field_Session_Name &field) { *this = field; }
    ~SDP_Field_Session_Name() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_SESSION_NAME; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_session_name(std::string name) { _session_name = name; }
    std::string get_session_name() { return _session_name; }

private:
    std::string _session_name;
};

//-------------------------------------------

class SDP_Field_Session_Information : public SDP_Field
{
public:
    SDP_Field_Session_Information() {}
    SDP_Field_Session_Information(const SDP_Field_Session_Information &field) { *this = field; }
    ~SDP_Field_Session_Information() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_SESSION_INFORMATION; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_session_information(std::string information) { _session_information = information; }
    std::string get_session_information() { return _session_information; }

private:
    std::string _session_information;
};

//-------------------------------------------

class SDP_Field_URI : public SDP_Field
{
public:
    SDP_Field_URI() {}
    SDP_Field_URI(const SDP_Field_URI &field) { *this = field; }
    ~SDP_Field_URI() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_URI; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_uri(std::string uri) { _uri = uri; }
    std::string get_uri() { return _uri; }

private:
    std::string _uri;
};

//-------------------------------------------

class SDP_Field_Email_Address : public SDP_Field
{
public:
    SDP_Field_Email_Address() {}
    SDP_Field_Email_Address(const SDP_Field_Email_Address &field) { *this = field; }
    ~SDP_Field_Email_Address() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_EMAIL_ADDRESS; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_email(std::string email) { _email = email; }
    std::string get_email() { return _email; }

private:
    std::string _email;
};

//-------------------------------------------
