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
    bool set_version(std::string version);
    unsigned short get_version() { return _version; }
    bool get_version(std::string &version);

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

class SDP_Field_Phone_Number : public SDP_Field
{
public:
    SDP_Field_Phone_Number() {}
    SDP_Field_Phone_Number(const SDP_Field_Phone_Number &field) { *this = field; }
    ~SDP_Field_Phone_Number() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_PHONE_NUMBER; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_phone(std::string phone) { _phone = phone; }
    std::string get_phone() { return _phone; }

private:
    std::string _phone;
};

//-------------------------------------------

class SDP_Field_Connection_Data : public SDP_Field
{
public:
    static const unsigned short INVALID_TTL = INVALID_UNSIGNED_SHORT;
    static const unsigned short INVALID_NUMBER_ADDRESSES = INVALID_UNSIGNED_SHORT;

public:
    SDP_Field_Connection_Data() : _ttl(INVALID_TTL), _number_addresses(INVALID_NUMBER_ADDRESSES) {}
    SDP_Field_Connection_Data(const SDP_Field_Connection_Data &field) { *this = field; }
    ~SDP_Field_Connection_Data() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_CONNECTION_DATA; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_network_type(std::string type) { _network_type = type; }
    std::string get_network_type() { return _network_type; }

    void set_address_type(std::string type) { _address_type = type; }
    std::string get_address_type() { return _address_type; }

    void set_connection_address(std::string address) { _connection_address = address; }
    std::string get_connection_address() { return _connection_address; }

    void set_ttl(unsigned short ttl) { _ttl = ttl; }
    unsigned short get_ttl() { return _ttl; }

    void set_number_addresses(unsigned short addresses) { _number_addresses = addresses; }
    unsigned short get_number_addresses() { return _number_addresses; }

private:
    std::string _network_type;
    std::string _address_type;
    std::string _connection_address;
    unsigned short _ttl;
    unsigned short _number_addresses;
};

//-------------------------------------------

class SDP_Field_Bandwidth : public SDP_Field
{
public:
    static const unsigned long INVALID_BANDWIDTH = INVALID_UNSIGNED_LONG;

public:
    SDP_Field_Bandwidth() : _bandwidth(INVALID_BANDWIDTH) {}
    SDP_Field_Bandwidth(const SDP_Field_Bandwidth &field) { *this = field; }
    ~SDP_Field_Bandwidth() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_BANDWIDTH; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_type(std::string type) { _type = type; }
    std::string get_type() { return _type; }

    void set_bandwidth(unsigned long bandwidth) { _bandwidth = bandwidth; }
    unsigned long get_bandwidth() { return _bandwidth; }

private:
    std::string _type;
    unsigned long _bandwidth;
};

//-------------------------------------------

class SDP_Field_Timing : public SDP_Field
{
public:
    static const unsigned long long INVALID_TIME = INVALID_UNSIGNED_LONG_LONG;

public:
    SDP_Field_Timing() : _start(INVALID_TIME), _stop(INVALID_TIME) {}
    SDP_Field_Timing(const SDP_Field_Timing &field) { *this = field; }
    ~SDP_Field_Timing() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_TIMING; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_start(unsigned long long start) { _start = start; }
    unsigned long long get_start() { return _start; }

    void set_stop(unsigned long long stop) { _stop = stop; }
    unsigned long long get_stop() { return _stop; }

private:
    unsigned long long _start;
    unsigned long long _stop;
};

//-------------------------------------------

class SDP_Field_Repeat_Time : public SDP_Field
{
public:
    SDP_Field_Repeat_Time() {}
    SDP_Field_Repeat_Time(const SDP_Field_Repeat_Time &field) { *this = field; }
    ~SDP_Field_Repeat_Time() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_REPEAT_TIME; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_interval(std::string interval) { _interval = interval; }
    std::string get_interval() { return _interval; }

    void set_duration(std::string duration) { _duration = duration; }
    std::string get_duration() { return _duration; }

    void set_offsets(std::list<std::string> &offsets) { _offsets = offsets; }
    std::list<std::string> &get_offsets() { return _offsets; }

private:
    std::string _interval;
    std::string _duration;
    std::list<std::string> _offsets;
};

//-------------------------------------------

class SDP_Field_Time_Zone : public SDP_Field
{
public:
    SDP_Field_Time_Zone() {}
    SDP_Field_Time_Zone(const SDP_Field_Time_Zone &field) { *this = field; }
    ~SDP_Field_Time_Zone() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_TIME_ZONE; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_adjustments(std::list<std::string> &adjustments) { _adjustments = adjustments; }
    std::list<std::string> &get_adjustments() { return _adjustments; }

    void set_offsets(std::list<std::string> &offsets) { _offsets = offsets; }
    std::list<std::string> &get_offsets() { return _offsets; }

private:
    std::list<std::string> _adjustments;
    std::list<std::string> _offsets;
};

//-------------------------------------------

class SDP_Field_Encryption_Key : public SDP_Field
{
public:
    enum Method
    {
        METHOD_CLEAR,
        METHOD_BASE64,
        METHOD_URI,
        METHOD_PROMPT,
        METHOD_INVALID
    };

public:
    SDP_Field_Encryption_Key() {}
    SDP_Field_Encryption_Key(const SDP_Field_Encryption_Key &field) { *this = field; }
    ~SDP_Field_Encryption_Key() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_ENCRYPTION_KEY; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_method(Method method);
    void set_method(std::string method) { _method = method; }
    Method get_method_enum();
    std::string get_method() { return _method; }

    void set_key(std::string key) { _key = key; }
    std::string get_key() { return _key; }

private:
    std::string _method;
    std::string _key;
};

//-------------------------------------------

class SDP_Field_Attribute : public SDP_Field
{
public:
    enum Attribute
    {
        ATTRIBUTE_CAT,
        ATTRIBUTE_KEYWDS,
        ATTRIBUTE_TOOL,
        ATTRIBUTE_PTIME,
        ATTRIBUTE_MAXPTIME,
        ATTRIBUTE_RTPMAP,
        ATTRIBUTE_RECVONLY,
        ATTRIBUTE_SENDRECV,
        ATTRIBUTE_SENDONLY,
        ATTRIBUTE_INACTIVE,
        ATTRIBUTE_ORIENT,
        ATTRIBUTE_TYPE,
        ATTRIBUTE_CHARSET,
        ATTRIBUTE_SDPLANG,
        ATTRIBUTE_LANG,
        ATTRIBUTE_FRAMERATE,
        ATTRIBUTE_QUALITY,
        ATTRIBUTE_FMTP,
        ATTRIBUTE_INVALID
    };

public:
    SDP_Field_Attribute() {}
    SDP_Field_Attribute(const SDP_Field_Attribute &field) { *this = field; }
    ~SDP_Field_Attribute() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_ATTRIBUTE; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_attribute(Attribute attribute);
    void set_attribute(std::string attribute) { _attribute = attribute; }
    Attribute get_attribute_enum();
    std::string get_attribute() { return _attribute; }

    void set_value(std::string value) { _value = value; }
    std::string get_value() { return _value; }

private:
    std::string _attribute;
    std::string _value;
};

//-------------------------------------------

class SDP_Field_Media_Description : public SDP_Field
{
public:
    static const unsigned short INVALID_PORT = INVALID_UNSIGNED_SHORT;
    static const unsigned short INVALID_NUMBER_PORTS = INVALID_UNSIGNED_SHORT;

    enum Media
    {
        MEDIA_AUDIO,
        MEDIA_VIDEO,
        MEDIA_TEXT,
        MEDIA_APPLICATION,
        MEDIA_MESSAGE,
        MEDIA_INVALID
    };

    enum Protocol
    {
        PROTOCOL_UDP,
        PROTOCOL_RTP_AVP,
        PROTOCOL_RTP_SAVP,
        PROTOCOL_INVALID
    };

public:
    SDP_Field_Media_Description() : _port(INVALID_PORT), _number_ports(INVALID_NUMBER_PORTS) {}
    SDP_Field_Media_Description(const SDP_Field_Media_Description &field) { *this = field; }
    ~SDP_Field_Media_Description() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_MEDIA_DESCRIPTION; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_media(Media media);
    void set_media(std::string media) { _media = media; }
    Media get_media_enum();
    std::string get_media() { return _media; }

    void set_port(unsigned short port) { _port = port; }
    unsigned short get_port() { return _port; }

    void set_number_ports(unsigned short ports) { _number_ports = ports; }
    unsigned short get_number_ports() { return _number_ports; }

    void set_protocol(Protocol protocol);
    void set_protocol(std::string protocol) { _protocol = protocol; }
    Protocol get_protocol_enum();
    std::string get_protocol() { return _protocol; }

    void set_formats(std::list<std::string> &formats) { _formats = formats; }
    std::list<std::string> &get_formats() { return _formats; }

private:
    std::string _media;
    unsigned short _port;
    unsigned short _number_ports;
    std::string _protocol;
    std::list<std::string> _formats;
};

//-------------------------------------------
