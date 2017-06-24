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
#include "sip_address.h"
#include <list>

class SIP_Header;
typedef std::list<SIP_Header *> sip_header_list;

class SIP_Header
{
public:
    SIP_Header() {}
    virtual ~SIP_Header() {}

    static SIP_Header *create_header(SIP_Header_Type header_type, const SIP_Header *copy = NULL);
    static bool decode_headers(std::string &sip_msg, sip_header_list &headers);
    static bool encode_headers(std::string &sip_msg, sip_header_list &headers);

    // Virtual pure functions
    virtual SIP_Header_Type get_header_type() = 0;
    virtual SIP_Header_Separator decode_separator() = 0;
    virtual SIP_Header_Separator encode_separator() = 0;
    virtual bool decode(std::string &sip_msg) = 0;
    virtual bool encode(std::string &sip_msg) = 0;

protected:
    std::string _header_line;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Challenge
{
public:
    SIP_Challenge() {}
    SIP_Challenge(const SIP_Challenge &value) { *this = value; }
    ~SIP_Challenge() {}

    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_scheme(std::string scheme) { _scheme = scheme; }
    std::string get_scheme_str() { return _scheme; }

    void set_realm(std::string realm) { _realm = realm; }
    std::string get_realm() { return _realm; }

    void set_domain(std::string domain) { _domain = domain; }
    std::string get_domain() { return _domain; }

    void set_nonce(std::string nonce) { _nonce = nonce; }
    std::string get_nonce() { return _nonce; }

    void set_opaque(std::string opaque) { _opaque = opaque; }
    std::string get_opaque() { return _opaque; }

    void set_stale(std::string stale) { _stale = stale; }
    std::string get_stale() { return _stale; }

    void set_algorithm(std::string algorithm) { _algorithm = algorithm; }
    std::string get_algorithm_str() { return _algorithm; }

    void set_qop(std::string qop) { _qop = qop; }
    std::string get_qop() { return _qop; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    std::string _scheme;
    std::string _realm;
    std::string _domain;
    std::string _nonce;
    std::string _opaque;
    std::string _stale;
    std::string _algorithm;
    std::string _qop;
    std::list<std::string> _parameters;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Credential
{
public:
    SIP_Credential() {}
    SIP_Credential(const SIP_Credential &value) { *this = value; }
    ~SIP_Credential() {}

    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_scheme(std::string scheme) { _scheme = scheme; }
    std::string get_scheme_str() { return _scheme; }

    void set_username(std::string username) { _username = username; }
    std::string get_username() { return _username; }

    void set_realm(std::string realm) { _realm = realm; }
    std::string get_realm() { return _realm; }

    void set_nonce(std::string nonce) { _nonce = nonce; }
    std::string get_nonce() { return _nonce; }

    void set_uri(std::string uri) { _uri = uri; }
    std::string get_uri() { return _uri; }

    void set_response(std::string response) { _response = response; }
    std::string get_response() { return _response; }

    void set_algorithm(std::string algorithm) { _algorithm = algorithm; }
    std::string get_algorithm_str() { return _algorithm; }

    void set_cnonce(std::string cnonce) { _cnonce = cnonce; }
    std::string get_cnonce() { return _cnonce; }

    void set_opaque(std::string opaque) { _opaque = opaque; }
    std::string get_opaque() { return _opaque; }

    void set_qop(std::string qop) { _qop = qop; }
    std::string get_qop() { return _qop; }

    void set_nonce_count(std::string nonce_count) { _nonce_count = nonce_count; }
    std::string get_nonce_count() { return _nonce_count; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    std::string _scheme;
    std::string _username;
    std::string _realm;
    std::string _nonce;
    std::string _uri;
    std::string _response;
    std::string _algorithm;
    std::string _cnonce;
    std::string _opaque;
    std::string _qop;
    std::string _nonce_count;
    std::list<std::string> _parameters;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Media_Range
{
public:
    SIP_Media_Range() {}
    SIP_Media_Range(const SIP_Media_Range &value) { *this = value; }
    ~SIP_Media_Range() {}

    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_type(SIP_Media_Type type);
    void set_type(std::string type) { _type = type; }
    SIP_Media_Type get_type();
    std::string get_type_str() { return _type; }

    void set_subtype(SIP_Media_Subtype subtype);
    void set_subtype(std::string subtype) { _subtype = subtype; }
    SIP_Media_Subtype get_subtype();
    std::string get_subtype_str() { return _subtype; }

    void set_q(std::string q) { _q = q; }
    std::string get_q() { return _q; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    std::string _type;
    std::string _subtype;
    std::string _q;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Event_Type
{
public:
    SIP_Event_Type() {}
    SIP_Event_Type(const SIP_Event_Type &value) { *this = value; }
    ~SIP_Event_Type() {}

    bool decode(std::string &sip_msg);
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool decode(std::string &sip_msg);
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_coding(std::string coding) { _coding = coding; }
    std::string get_coding() { return _coding; }

    void set_q(std::string q) { _q = q; }
    std::string get_q() { return _q; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    std::string _coding;
    std::string _q;
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_language(std::string language) { _language = language; }
    std::string get_language() { return _language; }

    void set_q(std::string q) { _q = q; }
    std::string get_q() { return _q; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    std::string _language;
    std::string _q;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_Alert_Info : public SIP_Header
{
public:
    SIP_Header_Alert_Info() {}
    SIP_Header_Alert_Info(const SIP_Header_Alert_Info &header) { *this = header; }
    ~SIP_Header_Alert_Info() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_ALERT_INFO; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Address &get_address() { return _address; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    SIP_Address _address;
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool decode(std::string &sip_msg);
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Event_Type &get_event_type() { return _event_type; }

private:
    SIP_Event_Type _event_type;
};

//-------------------------------------------

class SIP_Header_Authentication_Info : public SIP_Header
{
public:
    SIP_Header_Authentication_Info() {}
    SIP_Header_Authentication_Info(const SIP_Header_Authentication_Info &header) { *this = header; }
    ~SIP_Header_Authentication_Info() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_AUTHENTICATION_INFO; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_next_nonce(std::string next_nonce) { _next_nonce = next_nonce; }
    std::string get_next_nonce() { return _next_nonce; }

    void set_qop(std::string qop) { _qop = qop; }
    std::string get_qop() { return _qop; }

    void set_response(std::string response) { _response = response; }
    std::string get_response() { return _response; }

    void set_cnonce(std::string cnonce) { _cnonce = cnonce; }
    std::string get_cnonce() { return _cnonce; }

    void set_nonce_count(std::string nonce_count) { _nonce_count = nonce_count; }
    std::string get_nonce_count() { return _nonce_count; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    std::string _next_nonce;
    std::string _qop;
    std::string _response;
    std::string _cnonce;
    std::string _nonce_count;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_Authorization : public SIP_Header
{
public:
    SIP_Header_Authorization() {}
    SIP_Header_Authorization(const SIP_Header_Authorization &header) { *this = header; }
    ~SIP_Header_Authorization() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_AUTHORIZATION; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Credential &get_credential() { return _credential; }

private:
    SIP_Credential _credential;
};

//-------------------------------------------

class SIP_Header_Call_ID : public SIP_Header
{
public:
    SIP_Header_Call_ID() {}
    SIP_Header_Call_ID(const SIP_Header_Call_ID &header) { *this = header; }
    ~SIP_Header_Call_ID() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_CALL_ID; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_call_id(std::string call_id) { _call_id = call_id; }
    std::string get_call_id() { return _call_id; }

private:
    std::string _call_id;
};

//-------------------------------------------

class SIP_Header_Call_Info : public SIP_Header
{
public:
    SIP_Header_Call_Info() {}
    SIP_Header_Call_Info(const SIP_Header_Call_Info &header) { *this = header; }
    ~SIP_Header_Call_Info() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_CALL_INFO; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Address &get_address() { return _address; }

    void set_purpose(SIP_Call_Info_Purpose type);
    void set_purpose(std::string purpose) { _purpose = purpose; }
    SIP_Call_Info_Purpose get_purpose();
    std::string get_purpose_str() { return _purpose; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    SIP_Address _address;
    std::string _purpose;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_Contact : public SIP_Header
{
    static const unsigned long INVALID_EXPIRES = INVALID_UNSIGNED_LONG;

public:
    SIP_Header_Contact() : _star(false), _expires(INVALID_EXPIRES) {}
    SIP_Header_Contact(const SIP_Header_Contact &header) { *this = header; }
    ~SIP_Header_Contact() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_CONTACT; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_star(bool star) { _star = star; }
    bool is_star() { return _star; }

    SIP_Address &get_address() { return _address; }

    void set_expires(unsigned long expires) { _expires = expires; }
    unsigned long get_expires() { return _expires; }

    void set_q(std::string q) { _q = q; }
    std::string get_q() { return _q; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    bool _star;
    SIP_Address _address;
    unsigned long _expires;
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool decode(std::string &sip_msg);
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool decode(std::string &sip_msg);
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
    static const unsigned long INVALID_LENGTH = INVALID_UNSIGNED_LONG;

public:
    SIP_Header_Content_Length() : _length(INVALID_LENGTH) {}
    SIP_Header_Content_Length(const SIP_Header_Content_Length &header) { *this = header; }
    ~SIP_Header_Content_Length() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_CONTENT_LENGTH; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_length(unsigned long length) { _length = length; }
    unsigned long get_length() { return _length; }

private:
    unsigned long _length;
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Media_Range &get_media_type() { return _media_type; }

private:
    SIP_Media_Range _media_type;
};

//-------------------------------------------

class SIP_Header_CSeq : public SIP_Header
{
public:
    static const unsigned long INVALID_SEQUENCE = INVALID_UNSIGNED_LONG;

public:
    SIP_Header_CSeq() : _sequence(INVALID_SEQUENCE) {}
    SIP_Header_CSeq(const SIP_Header_CSeq &header) { *this = header; }
    ~SIP_Header_CSeq() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_CSEQ; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_sequence(unsigned long sequence) { _sequence = sequence; }
    unsigned long get_sequence() { return _sequence; }

    void set_method(SIP_Method_Type method);
    void set_method(std::string method) { _method = method; }
    SIP_Method_Type get_method();
    std::string get_method_str() { return _method; }

private:
    unsigned long _sequence;
    std::string _method;
};

//-------------------------------------------

class SIP_Header_Date : public SIP_Header
{
public:
    static const unsigned short INVALID_DAY = INVALID_UNSIGNED_SHORT;
    static const unsigned short INVALID_YEAR = INVALID_UNSIGNED_SHORT;
    static const unsigned short INVALID_HOUR = INVALID_UNSIGNED_SHORT;
    static const unsigned short INVALID_MINUTE = INVALID_UNSIGNED_SHORT;
    static const unsigned short INVALID_SECOND = INVALID_UNSIGNED_SHORT;

public:
    SIP_Header_Date();
    SIP_Header_Date(const SIP_Header_CSeq &header) { *this = header; }
    ~SIP_Header_Date() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_DATE; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
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

class SIP_Header_Error_Info : public SIP_Header
{
public:
    SIP_Header_Error_Info() {}
    SIP_Header_Error_Info(const SIP_Header_Error_Info &header) { *this = header; }
    ~SIP_Header_Error_Info() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_ERROR_INFO; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Address &get_address() { return _address; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    SIP_Address _address;
    std::list<std::string> _parameters;
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
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
    static const unsigned long INVALID_EXPIRES = INVALID_UNSIGNED_LONG;

public:
    SIP_Header_Expires() : _expires(INVALID_EXPIRES) {}
    SIP_Header_Expires(const SIP_Header_Expires &header) { *this = header; }
    ~SIP_Header_Expires() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_EXPIRES; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_expires(unsigned long expires) { _expires = expires; }
    unsigned long get_expires() { return _expires; }

private:
    unsigned long _expires;
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Address &get_address() { return _address; }

    void set_tag(std::string tag) { _tag = tag; }
    std::string get_tag() { return _tag; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    SIP_Address _address;
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool decode(std::string &sip_msg);
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
    static const unsigned short INVALID_MAX_FORWARDS = INVALID_UNSIGNED_SHORT;

public:
    SIP_Header_Max_Forwards() : _max_forwards(INVALID_MAX_FORWARDS) {}
    SIP_Header_Max_Forwards(const SIP_Header_Max_Forwards &header) { *this = header; }
    ~SIP_Header_Max_Forwards() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_MAX_FORWARDS; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_max_forwards(unsigned short max_forwards) { _max_forwards = max_forwards; }
    unsigned short get_max_forwards() { return _max_forwards; }

private:
    unsigned short _max_forwards;
};

//-------------------------------------------

class SIP_Header_Mime_Version : public SIP_Header
{
public:
    static const unsigned long INVALID_MIME_VERSION = INVALID_UNSIGNED_LONG;

public:
    SIP_Header_Mime_Version() : _major_version(INVALID_MIME_VERSION), _minor_version(INVALID_MIME_VERSION) {}
    SIP_Header_Mime_Version(const SIP_Header_Mime_Version &header) { *this = header; }
    ~SIP_Header_Mime_Version() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_MIME_VERSION; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_major_version(unsigned long major_version) { _major_version = major_version; }
    unsigned long get_major_version() { return _major_version; }

    void set_minor_version(unsigned long minor_version) { _minor_version = minor_version; }
    unsigned long get_minor_version() { return _minor_version; }

private:
    unsigned long _major_version;
    unsigned long _minor_version;
};

//-------------------------------------------

class SIP_Header_Min_Expires : public SIP_Header
{
public:
    static const unsigned long INVALID_MIN_EXPIRES = INVALID_UNSIGNED_LONG;

public:
    SIP_Header_Min_Expires() : _min_expires(INVALID_MIN_EXPIRES) {}
    SIP_Header_Min_Expires(const SIP_Header_Min_Expires &header) { *this = header; }
    ~SIP_Header_Min_Expires() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_MIN_EXPIRES; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_min_expires(unsigned long min_expires) { _min_expires = min_expires; }
    unsigned long get_min_expires() { return _min_expires; }

private:
    unsigned long _min_expires;
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_priority(SIP_Priority_Value priority);
    void set_priority(std::string priority) { _priority = priority; }
    SIP_Priority_Value get_priority();
    std::string get_priority_str() { return _priority; }

private:
    std::string _priority;
};

//-------------------------------------------

class SIP_Header_Proxy_Authenticate : public SIP_Header
{
public:
    SIP_Header_Proxy_Authenticate() {}
    SIP_Header_Proxy_Authenticate(const SIP_Header_Proxy_Authenticate &header) { *this = header; }
    ~SIP_Header_Proxy_Authenticate() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_PROXY_AUTHENTICATE; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Challenge &get_challenge() { return _challenge; }

private:
    SIP_Challenge _challenge;
};

//-------------------------------------------

class SIP_Header_Proxy_Authorization : public SIP_Header
{
public:
    SIP_Header_Proxy_Authorization() {}
    SIP_Header_Proxy_Authorization(const SIP_Header_Proxy_Authorization &header) { *this = header; }
    ~SIP_Header_Proxy_Authorization() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_PROXY_AUTHORIZATION; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Credential &get_credential() { return _credential; }

private:
    SIP_Credential _credential;
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool decode(std::string &sip_msg);
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Address &get_address() { return _address; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    SIP_Address _address;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_Reply_To : public SIP_Header
{
public:
    SIP_Header_Reply_To() {}
    SIP_Header_Reply_To(const SIP_Header_Reply_To &header) { *this = header; }
    ~SIP_Header_Reply_To() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_REPLY_TO; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Address &get_address() { return _address; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    SIP_Address _address;
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_option_tag(std::string option_tag) { _option_tag = option_tag; }
    std::string get_option_tag() { return _option_tag; }

private:
    std::string _option_tag;
};

//-------------------------------------------

class SIP_Header_Retry_After : public SIP_Header
{
public:
    static const unsigned long INVALID_RETRY_AFTER = INVALID_UNSIGNED_LONG;
    static const unsigned long INVALID_DURATION = INVALID_UNSIGNED_LONG;

public:
    SIP_Header_Retry_After() : _retry_after(INVALID_RETRY_AFTER), _duration(INVALID_DURATION) {}
    SIP_Header_Retry_After(const SIP_Header_Retry_After &header) { *this = header; }
    ~SIP_Header_Retry_After() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_RETRY_AFTER; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_retry_after(unsigned long retry_after) { _retry_after = retry_after; }
    unsigned long get_retry_after() { return _retry_after; }

    void set_comment(std::string comment) { _comment = comment; }
    std::string get_comment() { return _comment; }

    void set_duration(unsigned long duration) { _duration = duration; }
    unsigned long get_duration() { return _duration; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    unsigned long _retry_after;
    std::string _comment;
    unsigned long _duration;
    std::list<std::string> _parameters;
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Address &get_address() { return _address; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    SIP_Address _address;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_Server : public SIP_Header
{
public:
    SIP_Header_Server() {}
    SIP_Header_Server(const SIP_Header_Server &header) { *this = header; }
    ~SIP_Header_Server() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_SERVER; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_server(std::string server) { _server = server; }
    std::string get_server() { return _server; }

private:
    std::string _server;
};

//-------------------------------------------

class SIP_Header_Subject : public SIP_Header
{
public:
    SIP_Header_Subject() {}
    SIP_Header_Subject(const SIP_Header_Subject &header) { *this = header; }
    ~SIP_Header_Subject() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_SUBJECT; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_subject(std::string subject) { _subject = subject; }
    std::string get_subject() { return _subject; }

private:
    std::string _subject;
};

//-------------------------------------------

class SIP_Header_Subscription_State : public SIP_Header
{
public:
    static const unsigned long INVALID_EXPIRES = INVALID_UNSIGNED_LONG;
    static const unsigned long INVALID_RETRY_AFTER = INVALID_UNSIGNED_LONG;

public:
    SIP_Header_Subscription_State() : _expires(INVALID_EXPIRES), _retry_after(INVALID_RETRY_AFTER) {}
    SIP_Header_Subscription_State(const SIP_Header_Subscription_State &header) { *this = header; }
    ~SIP_Header_Subscription_State() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_SUBSCRIPTION_STATE; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_state(SIP_Subscription_State state);
    void set_state(std::string state) { _state = state; }
    SIP_Subscription_State get_state();
    std::string get_state_str() { return _state; }

    void set_reason(SIP_Subscription_State_Reason reason);
    void set_reason(std::string reason) { _reason = reason; }
    SIP_Subscription_State_Reason get_reason();
    std::string get_reason_str() { return _reason; }

    void set_expires(unsigned long expires) { _expires = expires; }
    unsigned long get_expires() { return _expires; }

    void set_retry_after(unsigned long retry_after) { _retry_after = retry_after; }
    unsigned long get_retry_after() { return _retry_after; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    std::string _state;
    std::string _reason;
    unsigned long _expires;
    unsigned long _retry_after;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_Supported : public SIP_Header
{
public:
    SIP_Header_Supported() {}
    SIP_Header_Supported(const SIP_Header_Supported &header) { *this = header; }
    ~SIP_Header_Supported() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_SUPPORTED; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_option_tag(std::string option_tag) { _option_tag = option_tag; }
    std::string get_option_tag() { return _option_tag; }

private:
    std::string _option_tag;
};

//-------------------------------------------

class SIP_Header_Timestamp : public SIP_Header
{
public:
    SIP_Header_Timestamp() {}
    SIP_Header_Timestamp(const SIP_Header_Timestamp &header) { *this = header; }
    ~SIP_Header_Timestamp() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_TIMESTAMP; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_timestamp(std::string timestamp) { _timestamp = timestamp; }
    std::string get_timestamp() { return _timestamp; }

    void set_delay(std::string delay) { _delay = delay; }
    std::string get_delay() { return _delay; }

private:
    std::string _timestamp;
    std::string _delay;
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Address &get_address() { return _address; }

    void set_tag(std::string tag) { _tag = tag; }
    std::string get_tag() { return _tag; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    SIP_Address _address;
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
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_option_tag(std::string option_tag) { _option_tag = option_tag; }
    std::string get_option_tag() { return _option_tag; }

private:
    std::string _option_tag;
};

//-------------------------------------------

class SIP_Header_User_Agent : public SIP_Header
{
public:
    SIP_Header_User_Agent() {}
    SIP_Header_User_Agent(const SIP_Header_User_Agent &header) { *this = header; }
    ~SIP_Header_User_Agent() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_USER_AGENT; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_NONE; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_user_agent(std::string user_agent) { _user_agent = user_agent; }
    std::string get_user_agent() { return _user_agent; }

private:
    std::string _user_agent;
};

//-------------------------------------------

class SIP_Header_Via : public SIP_Header
{
public:
    static const unsigned short INVALID_PORT = INVALID_UNSIGNED_SHORT;
    static const unsigned short INVALID_TTL = INVALID_UNSIGNED_SHORT;

public:
    SIP_Header_Via() : _port(INVALID_PORT), _ttl(INVALID_TTL) {}
    SIP_Header_Via(const SIP_Header_Via &header) { *this = header; }
    ~SIP_Header_Via() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_VIA; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    bool decode(std::string &sip_msg);
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

    void set_ttl(unsigned short ttl) { _ttl = ttl; }
    unsigned short get_ttl() { return _ttl; }

    void set_maddr(std::string maddr) { _maddr = maddr; }
    std::string get_maddr() { return _maddr; }

    std::list<std::string> &get_parameters() { return _parameters; }

private:
    std::string _protocol_name;
    std::string _protocol_version;
    std::string _transport;
    std::string _host;
    unsigned short _port;
    std::string _branch;
    std::string _received;
    unsigned short _ttl;
    std::string _maddr;
    std::list<std::string> _parameters;
};

//-------------------------------------------

class SIP_Header_Warning : public SIP_Header
{
public:
    static const unsigned short INVALID_CODE = INVALID_UNSIGNED_SHORT;

public:
    SIP_Header_Warning() : _code(INVALID_CODE) {}
    SIP_Header_Warning(const SIP_Header_Warning &header) { *this = header; }
    ~SIP_Header_Warning() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_WARNING; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_COMMA; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    void set_code(unsigned short code) { _code = code; }
    unsigned short get_code() { return _code; }

    void set_agent(std::string agent) { _agent = agent; }
    std::string get_agent() { return _agent; }

    void set_text(std::string text) { _text = text; }
    std::string get_text() { return _text; }

private:
    unsigned short _code;
    std::string _agent;
    std::string _text;
};

//-------------------------------------------

class SIP_Header_WWW_Authenticate : public SIP_Header
{
public:
    SIP_Header_WWW_Authenticate() {}
    SIP_Header_WWW_Authenticate(const SIP_Header_WWW_Authenticate &header) { *this = header; }
    ~SIP_Header_WWW_Authenticate() {}

    // Virtual pure functions
    SIP_Header_Type get_header_type() { return SIP_HEADER_WWW_AUTHENTICATE; }
    SIP_Header_Separator decode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    SIP_Header_Separator encode_separator() { return SIP_HEADER_SEPARATOR_CRLF; }
    bool decode(std::string &sip_msg);
    bool encode(std::string &sip_msg);

    SIP_Challenge &get_challenge() { return _challenge; }

private:
    SIP_Challenge _challenge;
};

//-------------------------------------------
