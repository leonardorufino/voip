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
#include <map>
#include <list>

class SIP_Header
{
public:
    SIP_Header() {}
    virtual ~SIP_Header() {}

    static SIP_Header *create_header(SIP_Header_Type header_type, const SIP_Header *copy = NULL);
    static bool decode_headers(std::string &sip_msg, std::map<SIP_Header_Type, std::list<SIP_Header *>> &headers);
    static bool encode_headers(std::string &sip_msg, std::map<SIP_Header_Type, std::list<SIP_Header *>> &headers);

    // Virtual pure functions
    virtual SIP_Header_Type get_header_type() = 0;
    virtual SIP_Header_Separator encode_separator() = 0;
    virtual bool parse(std::string &sip_msg) = 0;
    virtual bool encode(std::string &sip_msg) = 0;

protected:
    std::string _header_line;
};

//-------------------------------------------
//-------------------------------------------

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

    void set_display_name(std::string display_name) { _display_name = display_name; }
    std::string get_display_name() { return _display_name; }

    void set_scheme(SIP_Address_Scheme scheme);
    void set_scheme(std::string scheme) { _scheme = scheme; }
    SIP_Address_Scheme get_scheme();
    std::string get_scheme_str() { return _scheme; }

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
    std::string _display_name;
    std::string _scheme;
    std::string _user;
    std::string _host;
    unsigned short _port;

    bool _lr;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Media_Range
{
public:
    SIP_Media_Range() {}
    SIP_Media_Range(const SIP_Media_Range &value) { *this = value; }
    ~SIP_Media_Range() {}

    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_type(SIP_Media_Type type);
    void set_type(std::string type) { _type = type; }
    SIP_Media_Type get_type();
    std::string get_type_str() { return _type; }

    void set_subtype(SIP_Media_Subtype subtype);
    void set_subtype(std::string subtype) { _subtype = subtype; }
    SIP_Media_Subtype get_subtype();
    std::string get_subtype_str() { return _subtype; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    std::string _type;
    std::string _subtype;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Event_Type
{
public:
    SIP_Event_Type() {}
    SIP_Event_Type(const SIP_Event_Type &value) { *this = value; }
    ~SIP_Event_Type() {}

    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_package(SIP_Event_Package package);
    void set_package(std::string package) { _package = package; }
    SIP_Event_Package get_package();
    std::string get_package_str() { return _package; }

    std::list<std::string> &get_templates() { return _templates; }

private:
    std::string _package;
    std::list<std::string> _templates;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Header_Accept : public SIP_Header
{
public:
    SIP_Header_Accept() {}
    SIP_Header_Accept(const SIP_Header_Accept &header) { *this = header; }
    ~SIP_Header_Accept() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_ACCEPT; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Media_Range &get_media_range() { return _media_range; }

private:
    SIP_Media_Range _media_range;
};

//-------------------------------------------

class SIP_Header_Accept_Encoding : public SIP_Header
{
public:
    SIP_Header_Accept_Encoding() {}
    SIP_Header_Accept_Encoding(const SIP_Header_Accept_Encoding &header) { *this = header; }
    ~SIP_Header_Accept_Encoding() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_ACCEPT_ENCODING; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_coding(std::string coding) { _coding = coding; }
    std::string get_coding() { return _coding; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    std::string _coding;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_Accept_Language : public SIP_Header
{
public:
    SIP_Header_Accept_Language() {}
    SIP_Header_Accept_Language(const SIP_Header_Accept_Language &header) { *this = header; }
    ~SIP_Header_Accept_Language() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_ACCEPT_LANGUAGE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_language(std::string language) { _language = language; }
    std::string get_language() { return _language; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    std::string _language;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_Allow : public SIP_Header
{
public:
    SIP_Header_Allow() {}
    SIP_Header_Allow(const SIP_Header_Allow &header) { *this = header; }
    ~SIP_Header_Allow() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_ALLOW; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_method(SIP_Method_Type method);
    void set_method(std::string method) { _method = method; }
    SIP_Method_Type get_method();
    std::string get_method_str() { return _method; }

private:
    std::string _method;
};

//-------------------------------------------

class SIP_Header_Allow_Events : public SIP_Header
{
public:
    SIP_Header_Allow_Events() {}
    SIP_Header_Allow_Events(const SIP_Header_Allow_Events &header) { *this = header; }
    ~SIP_Header_Allow_Events() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_ALLOW_EVENTS; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Event_Type &get_event_type() { return _event_type; }

private:
    SIP_Event_Type _event_type;
};

//-------------------------------------------

class SIP_Header_Call_ID : public SIP_Header
{
public:
    SIP_Header_Call_ID() {}
    SIP_Header_Call_ID(const SIP_Header_Call_ID &header) { *this = header; }
    ~SIP_Header_Call_ID() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_CALLID; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_call_id(std::string call_id) { _call_id = call_id; }
    std::string get_call_id() { return _call_id; }

private:
    std::string _call_id;
};

//-------------------------------------------

class SIP_Header_Contact : public SIP_Header
{
    static const unsigned int INVALID_EXPIRES = 0xFFFFFFFF;

public:
    SIP_Header_Contact() : _star(false), _expires(INVALID_EXPIRES) {}
    SIP_Header_Contact(const SIP_Header_Contact &header) { *this = header; }
    ~SIP_Header_Contact() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_CONTACT; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_star(bool star) { _star = star; }
    bool is_star() { return _star; }

    SIP_URI &get_address() { return _address; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    bool _star;
    SIP_URI _address;

    unsigned int _expires;
    std::string _q;

    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_Content_Disposition : public SIP_Header
{
public:
    SIP_Header_Content_Disposition() {}
    SIP_Header_Content_Disposition(const SIP_Header_Content_Disposition &header) { *this = header; }
    ~SIP_Header_Content_Disposition() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_CONTENT_DISPOSITION; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_type(SIP_Disposition_Type type);
    void set_type(std::string type) { _type = type; }
    SIP_Disposition_Type get_type();
    std::string get_type_str() { return _type; }

    void set_handling(SIP_Disposition_Handling handling);
    void set_handling(std::string handling) { _handling = handling; }
    SIP_Disposition_Handling get_handling();
    std::string get_handling_str() { return _handling; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    std::string _type;
    std::string _handling;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_Content_Encoding : public SIP_Header
{
public:
    SIP_Header_Content_Encoding() {}
    SIP_Header_Content_Encoding(const SIP_Header_Content_Encoding &header) { *this = header; }
    ~SIP_Header_Content_Encoding() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_CONTENT_ENCODING; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_coding(std::string coding) { _coding = coding; }
    std::string get_coding() { return _coding; }

private:
    std::string _coding;
};

//-------------------------------------------

class SIP_Header_Content_Language : public SIP_Header
{
public:
    SIP_Header_Content_Language() {}
    SIP_Header_Content_Language(const SIP_Header_Content_Language &header) { *this = header; }
    ~SIP_Header_Content_Language() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_CONTENT_LANGUAGE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_language(std::string language) { _language = language; }
    std::string get_language() { return _language; }

private:
    std::string _language;
};

//-------------------------------------------

class SIP_Header_Content_Length : public SIP_Header
{
public:
    static const unsigned int INVALID_LENGTH = 0xFFFFFFFF;

public:
    SIP_Header_Content_Length() : _length(INVALID_LENGTH) {}
    SIP_Header_Content_Length(const SIP_Header_Content_Length &header) { *this = header; }
    ~SIP_Header_Content_Length() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_CONTENT_LENGTH; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_length(unsigned int length) { _length = length; }
    unsigned int get_length() { return _length; }

private:
    unsigned int _length;
};

//-------------------------------------------

class SIP_Header_Content_Type : public SIP_Header
{
public:
    SIP_Header_Content_Type() {}
    SIP_Header_Content_Type(const SIP_Header_Content_Type &header) { *this = header; }
    ~SIP_Header_Content_Type() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_CONTENT_TYPE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Media_Range &get_media_type() { return _media_type; }

private:
    SIP_Media_Range _media_type;
};

//-------------------------------------------

class SIP_Header_CSeq : public SIP_Header
{
public:
    static const unsigned int INVALID_SEQUENCE = 0xFFFFFFFF;

public:
    SIP_Header_CSeq() : _sequence(INVALID_SEQUENCE) {}
    SIP_Header_CSeq(const SIP_Header_CSeq &header) { *this = header; }
    ~SIP_Header_CSeq() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_CSEQ; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_sequence(unsigned int sequence) { _sequence = sequence; }
    unsigned int get_sequence() { return _sequence; }

    void set_method(SIP_Method_Type method);
    void set_method(std::string method) { _method = method; }
    SIP_Method_Type get_method();
    std::string get_method_str() { return _method; }

private:
    unsigned int _sequence;
    std::string _method;
};

//-------------------------------------------

class SIP_Header_Date : public SIP_Header
{
public:
    static const unsigned short INVALID_DAY = 0xFFFF;
    static const unsigned short INVALID_YEAR = 0xFFFF;
    static const unsigned short INVALID_HOUR = 0xFFFF;
    static const unsigned short INVALID_MINUTE = 0xFFFF;
    static const unsigned short INVALID_SECOND = 0xFFFF;

public:
    SIP_Header_Date();
    SIP_Header_Date(const SIP_Header_CSeq &header) { *this = header; }
    ~SIP_Header_Date() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_DATE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_weekday(SIP_Date_Weekday weekday);
    void set_weekday(std::string weekday) { _weekday = weekday; }
    SIP_Date_Weekday get_weekday();
    std::string get_weekday_str() { return _weekday; }

    void set_day(unsigned short day) { _day = day; }
    unsigned short get_day() { return _day; }

    void set_month(SIP_Date_Month month);
    void set_month(std::string month) { _month = month; }
    SIP_Date_Month get_month();
    std::string get_month_str() { return _month; }

    void set_year(unsigned short year) { _year = year; }
    unsigned short get_year() { return _year; }

    void set_hour(unsigned short hour) { _hour = hour; }
    unsigned short get_hour() { return _hour; }

    void set_minute(unsigned short minute) { _minute = minute; }
    unsigned short get_minute() { return _minute; }

    void set_second(unsigned short second) { _second = second; }
    unsigned short get_second() { return _second; }

    void set_time_zone(std::string time_zone) { _time_zone = time_zone; }
    std::string get_time_zone() { return _time_zone; }

private:
    std::string _weekday;
    unsigned short _day;
    std::string _month;
    unsigned short _year;
    unsigned short _hour;
    unsigned short _minute;
    unsigned short _second;
    std::string _time_zone;
};

//-------------------------------------------

class SIP_Header_Event : public SIP_Header
{
public:
    SIP_Header_Event() {}
    SIP_Header_Event(const SIP_Header_Event &header) { *this = header; }
    ~SIP_Header_Event() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_EVENT; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Event_Type &get_event_type() { return _event_type; }

    void set_id(std::string id) { _id = id; }
    std::string get_id() { return _id; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    SIP_Event_Type _event_type;
    std::string _id;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_Expires : public SIP_Header
{
public:
    static const unsigned int INVALID_EXPIRES = 0xFFFFFFFF;

public:
    SIP_Header_Expires() : _expires(INVALID_EXPIRES) {}
    SIP_Header_Expires(const SIP_Header_Expires &header) { *this = header; }
    ~SIP_Header_Expires() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_EXPIRES; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_expires(unsigned int expires) { _expires = expires; }
    unsigned int get_expires() { return _expires; }

private:
    unsigned int _expires;
};

//-------------------------------------------

class SIP_Header_From : public SIP_Header
{
public:
    SIP_Header_From() {}
    SIP_Header_From(const SIP_Header_From &header) { *this = header; }
    ~SIP_Header_From() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_FROM; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_URI &get_address() { return _address; }

    void set_tag(std::string tag) { _tag = tag; }
    std::string get_tag() { return _tag; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    SIP_URI _address;
    std::string _tag;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_In_Reply_To : public SIP_Header
{
public:
    SIP_Header_In_Reply_To() {}
    SIP_Header_In_Reply_To(const SIP_Header_In_Reply_To &header) { *this = header; }
    ~SIP_Header_In_Reply_To() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_IN_REPLY_TO; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_call_id(std::string call_id) { _call_id = call_id; }
    std::string get_call_id() { return _call_id; }

private:
    std::string _call_id;
};

//-------------------------------------------

class SIP_Header_Max_Forwards : public SIP_Header
{
public:
    static const unsigned int INVALID_MAX_FORWARDS = 0xFFFFFFFF;

public:
    SIP_Header_Max_Forwards() : _max_forwards(INVALID_MAX_FORWARDS) {}
    SIP_Header_Max_Forwards(const SIP_Header_Max_Forwards &header) { *this = header; }
    ~SIP_Header_Max_Forwards() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_MAX_FORWARDS; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_max_forwards(unsigned int max_forwards) { _max_forwards = max_forwards; }
    unsigned int get_max_forwards() { return _max_forwards; }

private:
    unsigned int _max_forwards;
};

//-------------------------------------------

class SIP_Header_Mime_Version : public SIP_Header
{
public:
    static const unsigned int INVALID_MIME_VERSION = 0xFFFFFFFF;

public:
    SIP_Header_Mime_Version() : _major_version(INVALID_MIME_VERSION), _minor_version(INVALID_MIME_VERSION) {}
    SIP_Header_Mime_Version(const SIP_Header_Mime_Version &header) { *this = header; }
    ~SIP_Header_Mime_Version() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_MIME_VERSION; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_major_version(unsigned int major_version) { _major_version = major_version; }
    unsigned int get_major_version() { return _major_version; }

    void set_minor_version(unsigned int minor_version) { _minor_version = minor_version; }
    unsigned int get_minor_version() { return _minor_version; }

private:
    unsigned int _major_version;
    unsigned int _minor_version;
};

//-------------------------------------------

class SIP_Header_Min_Expires : public SIP_Header
{
public:
    static const unsigned int INVALID_MIN_EXPIRES = 0xFFFFFFFF;

public:
    SIP_Header_Min_Expires() : _min_expires(INVALID_MIN_EXPIRES) {}
    SIP_Header_Min_Expires(const SIP_Header_Min_Expires &header) { *this = header; }
    ~SIP_Header_Min_Expires() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_MIN_EXPIRES; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_min_expires(unsigned int min_expires) { _min_expires = min_expires; }
    unsigned int get_min_expires() { return _min_expires; }

private:
    unsigned int _min_expires;
};

//-------------------------------------------

class SIP_Header_Organization : public SIP_Header
{
public:
    SIP_Header_Organization() {}
    SIP_Header_Organization(const SIP_Header_Organization &header) { *this = header; }
    ~SIP_Header_Organization() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_ORGANIZATION; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_organization(std::string organization) { _organization = organization; }
    std::string get_organization() { return _organization; }

private:
    std::string _organization;
};

//-------------------------------------------

class SIP_Header_Priority : public SIP_Header
{
public:
    SIP_Header_Priority() {}
    SIP_Header_Priority(const SIP_Header_Priority &header) { *this = header; }
    ~SIP_Header_Priority() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_PRIORITY; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_priority(SIP_Priority_Value priority);
    void set_priority(std::string priority) { _priority = priority; }
    SIP_Priority_Value get_priority();
    std::string get_priority_str() { return _priority; }

private:
    std::string _priority;
};

//-------------------------------------------

class SIP_Header_Proxy_Require : public SIP_Header
{
public:
    SIP_Header_Proxy_Require() {}
    SIP_Header_Proxy_Require(const SIP_Header_Proxy_Require &header) { *this = header; }
    ~SIP_Header_Proxy_Require() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_PROXY_REQUIRE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_option_tag(std::string option_tag) { _option_tag = option_tag; }
    std::string get_option_tag() { return _option_tag; }

private:
    std::string _option_tag;
};

//-------------------------------------------

class SIP_Header_Record_Route : public SIP_Header
{
public:
    SIP_Header_Record_Route() {}
    SIP_Header_Record_Route(const SIP_Header_Record_Route &header) { *this = header; }
    ~SIP_Header_Record_Route() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_RECORD_ROUTE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_URI &get_address() { return _address; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    SIP_URI _address;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_Require : public SIP_Header
{
public:
    SIP_Header_Require() {}
    SIP_Header_Require(const SIP_Header_Require &header) { *this = header; }
    ~SIP_Header_Require() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_REQUIRE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_option_tag(std::string option_tag) { _option_tag = option_tag; }
    std::string get_option_tag() { return _option_tag; }

private:
    std::string _option_tag;
};

//-------------------------------------------

class SIP_Header_Route : public SIP_Header
{
public:
    SIP_Header_Route() {}
    SIP_Header_Route(const SIP_Header_Route &header) { *this = header; }
    ~SIP_Header_Route() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_ROUTE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_URI &get_address() { return _address; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    SIP_URI _address;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_Subscription_State : public SIP_Header
{
public:
    static const unsigned int INVALID_EXPIRES = 0xFFFFFFFF;

public:
    SIP_Header_Subscription_State() : _expires(INVALID_EXPIRES) {}
    SIP_Header_Subscription_State(const SIP_Header_Subscription_State &header) { *this = header; }
    ~SIP_Header_Subscription_State() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_SUBSCRIPTION_STATE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_state(SIP_Subscription_State state);
    void set_state(std::string state) { _state = state; }
    SIP_Subscription_State get_state();
    std::string get_state_str() { return _state; }

    void set_expires(unsigned int expires) { _expires = expires; }
    unsigned int get_expires() { return _expires; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    std::string _state;
    unsigned int _expires;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_To : public SIP_Header
{
public:
    SIP_Header_To() {}
    SIP_Header_To(const SIP_Header_To &header) { *this = header; }
    ~SIP_Header_To() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_TO; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_URI &get_address() { return _address; }

    void set_tag(std::string tag) { _tag = tag; }
    std::string get_tag() { return _tag; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    SIP_URI _address;
    std::string _tag;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_Unsupported : public SIP_Header
{
public:
    SIP_Header_Unsupported() {}
    SIP_Header_Unsupported(const SIP_Header_Unsupported &header) { *this = header; }
    ~SIP_Header_Unsupported() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_UNSUPPORTED; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_option_tag(std::string option_tag) { _option_tag = option_tag; }
    std::string get_option_tag() { return _option_tag; }

private:
    std::string _option_tag;
};

//-------------------------------------------

class SIP_Header_Via : public SIP_Header
{
public:
    static const unsigned short INVALID_PORT = 0xFFFF;

public:
    SIP_Header_Via() : _port(INVALID_PORT) {}
    SIP_Header_Via(const SIP_Header_Via &header) { *this = header; }
    ~SIP_Header_Via() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_VIA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    bool parse(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_protocol_name(std::string protocol_name) { _protocol_name = protocol_name; }
    std::string get_protocol_name() { return _protocol_name; }

    void set_protocol_version(std::string protocol_version) { _protocol_version = protocol_version; }
    std::string get_protocol_version() { return _protocol_version; }

    void set_transport(SIP_Transport_Type transport);
    void set_transport(std::string transport) { _transport = transport; }
    SIP_Transport_Type get_transport();
    std::string get_transport_str() { return _transport; }

    void set_host(std::string host) { _host = host; }
    std::string get_host() { return _host; }

    void set_port(unsigned short port) { _port = port; }
    unsigned short get_port() { return _port; }

    void set_branch(std::string branch) { _branch = branch; }
    std::string get_branch() { return _branch; }

    void set_received(std::string received) { _received = received; }
    std::string get_received() { return _received; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    std::string _protocol_name;
    std::string _protocol_version;
    std::string _transport;
    std::string _host;
    unsigned short _port;
    std::string _branch;
    std::string _received;
    std::list<std::string> _parameters;
};

//-------------------------------------------
