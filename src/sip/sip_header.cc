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

#include "sip_header.h"
#include "sip_functions.h"

//-------------------------------------------

SIP_Header *SIP_Header::create_header(SIP_Header_Type header_type, const SIP_Header *copy)
{
    SIP_Header *header = NULL;

    switch (header_type)
    {
        case SIP_HEADER_ACCEPT:              header = (!copy) ? new SIP_Header_Accept()              : new SIP_Header_Accept(*((SIP_Header_Accept *) copy));                            break;
        case SIP_HEADER_ACCEPT_ENCODING:     header = (!copy) ? new SIP_Header_Accept_Encoding()     : new SIP_Header_Accept_Encoding(*((SIP_Header_Accept_Encoding *) copy));          break;
        case SIP_HEADER_ACCEPT_LANGUAGE:     header = (!copy) ? new SIP_Header_Accept_Language()     : new SIP_Header_Accept_Language(*((SIP_Header_Accept_Language *) copy));          break;
        case SIP_HEADER_ALERT_INFO:          header = (!copy) ? new SIP_Header_Alert_Info()          : new SIP_Header_Alert_Info(*((SIP_Header_Alert_Info *) copy));                    break;
        case SIP_HEADER_ALLOW:               header = (!copy) ? new SIP_Header_Allow()               : new SIP_Header_Allow(*((SIP_Header_Allow *) copy));                              break;
        case SIP_HEADER_ALLOW_EVENTS:        header = (!copy) ? new SIP_Header_Allow_Events()        : new SIP_Header_Allow_Events(*((SIP_Header_Allow_Events *) copy));                break;
        case SIP_HEADER_CALL_ID:             header = (!copy) ? new SIP_Header_Call_ID()             : new SIP_Header_Call_ID(*((SIP_Header_Call_ID *) copy));                          break;
        case SIP_HEADER_CALL_INFO:           header = (!copy) ? new SIP_Header_Call_Info()           : new SIP_Header_Call_Info(*((SIP_Header_Call_Info *) copy));                      break;
        case SIP_HEADER_CONTACT:             header = (!copy) ? new SIP_Header_Contact()             : new SIP_Header_Contact(*((SIP_Header_Contact *) copy));                          break;
        case SIP_HEADER_CONTENT_DISPOSITION: header = (!copy) ? new SIP_Header_Content_Disposition() : new SIP_Header_Content_Disposition(*((SIP_Header_Content_Disposition *) copy));  break;
        case SIP_HEADER_CONTENT_ENCODING:    header = (!copy) ? new SIP_Header_Content_Encoding()    : new SIP_Header_Content_Encoding(*((SIP_Header_Content_Encoding *) copy));        break;
        case SIP_HEADER_CONTENT_LANGUAGE:    header = (!copy) ? new SIP_Header_Content_Language()    : new SIP_Header_Content_Language(*((SIP_Header_Content_Language *) copy));        break;
        case SIP_HEADER_CONTENT_LENGTH:      header = (!copy) ? new SIP_Header_Content_Length()      : new SIP_Header_Content_Length(*((SIP_Header_Content_Length *) copy));            break;
        case SIP_HEADER_CONTENT_TYPE:        header = (!copy) ? new SIP_Header_Content_Type()        : new SIP_Header_Content_Type(*((SIP_Header_Content_Type *) copy));                break;
        case SIP_HEADER_CSEQ:                header = (!copy) ? new SIP_Header_CSeq()                : new SIP_Header_CSeq(*((SIP_Header_CSeq *) copy));                                break;
        case SIP_HEADER_DATE:                header = (!copy) ? new SIP_Header_Date()                : new SIP_Header_Date(*((SIP_Header_Date *) copy));                                break;
        case SIP_HEADER_ERROR_INFO:          header = (!copy) ? new SIP_Header_Error_Info()          : new SIP_Header_Error_Info(*((SIP_Header_Error_Info *) copy));                    break;
        case SIP_HEADER_EVENT:               header = (!copy) ? new SIP_Header_Event()               : new SIP_Header_Event(*((SIP_Header_Event *) copy));                              break;
        case SIP_HEADER_EXPIRES:             header = (!copy) ? new SIP_Header_Expires()             : new SIP_Header_Expires(*((SIP_Header_Expires *) copy));                          break;
        case SIP_HEADER_FROM:                header = (!copy) ? new SIP_Header_From()                : new SIP_Header_From(*((SIP_Header_From *) copy));                                break;
        case SIP_HEADER_IN_REPLY_TO:         header = (!copy) ? new SIP_Header_In_Reply_To()         : new SIP_Header_In_Reply_To(*((SIP_Header_In_Reply_To *) copy));                  break;
        case SIP_HEADER_MAX_FORWARDS:        header = (!copy) ? new SIP_Header_Max_Forwards()        : new SIP_Header_Max_Forwards(*((SIP_Header_Max_Forwards *) copy));                break;
        case SIP_HEADER_MIME_VERSION:        header = (!copy) ? new SIP_Header_Mime_Version()        : new SIP_Header_Mime_Version(*((SIP_Header_Mime_Version *) copy));                break;
        case SIP_HEADER_MIN_EXPIRES:         header = (!copy) ? new SIP_Header_Min_Expires()         : new SIP_Header_Min_Expires(*((SIP_Header_Min_Expires *) copy));                  break;
        case SIP_HEADER_ORGANIZATION:        header = (!copy) ? new SIP_Header_Organization()        : new SIP_Header_Organization(*((SIP_Header_Organization *) copy));                break;
        case SIP_HEADER_PRIORITY:            header = (!copy) ? new SIP_Header_Priority()            : new SIP_Header_Priority(*((SIP_Header_Priority *) copy));                        break;
        case SIP_HEADER_PROXY_REQUIRE:       header = (!copy) ? new SIP_Header_Proxy_Require()       : new SIP_Header_Proxy_Require(*((SIP_Header_Proxy_Require *) copy));              break;
        case SIP_HEADER_RECORD_ROUTE:        header = (!copy) ? new SIP_Header_Record_Route()        : new SIP_Header_Record_Route(*((SIP_Header_Record_Route *) copy));                break;
        case SIP_HEADER_REPLY_TO:            header = (!copy) ? new SIP_Header_Reply_To()            : new SIP_Header_Reply_To(*((SIP_Header_Reply_To *) copy));                        break;
        case SIP_HEADER_REQUIRE:             header = (!copy) ? new SIP_Header_Require()             : new SIP_Header_Require(*((SIP_Header_Require *) copy));                          break;
        case SIP_HEADER_ROUTE:               header = (!copy) ? new SIP_Header_Route()               : new SIP_Header_Route(*((SIP_Header_Route *) copy));                              break;
        case SIP_HEADER_SERVER:              header = (!copy) ? new SIP_Header_Server()              : new SIP_Header_Server(*((SIP_Header_Server *) copy));                            break;
        case SIP_HEADER_SUBJECT:             header = (!copy) ? new SIP_Header_Subject()             : new SIP_Header_Subject(*((SIP_Header_Subject *) copy));                          break;
        case SIP_HEADER_SUBSCRIPTION_STATE:  header = (!copy) ? new SIP_Header_Subscription_State()  : new SIP_Header_Subscription_State(*((SIP_Header_Subscription_State *) copy));    break;
        case SIP_HEADER_SUPPORTED:           header = (!copy) ? new SIP_Header_Supported()           : new SIP_Header_Supported(*((SIP_Header_Supported *) copy));                      break;
        case SIP_HEADER_TIMESTAMP:           header = (!copy) ? new SIP_Header_Timestamp()           : new SIP_Header_Timestamp(*((SIP_Header_Timestamp *) copy));                      break;
        case SIP_HEADER_TO:                  header = (!copy) ? new SIP_Header_To()                  : new SIP_Header_To(*((SIP_Header_To *) copy));                                    break;
        case SIP_HEADER_UNSUPPORTED:         header = (!copy) ? new SIP_Header_Unsupported()         : new SIP_Header_Unsupported(*((SIP_Header_Unsupported *) copy));                  break;
        case SIP_HEADER_USER_AGENT:          header = (!copy) ? new SIP_Header_User_Agent()          : new SIP_Header_User_Agent(*((SIP_Header_User_Agent *) copy));                    break;
        case SIP_HEADER_VIA:                 header = (!copy) ? new SIP_Header_Via()                 : new SIP_Header_Via(*((SIP_Header_Via *) copy));                                  break;
        case SIP_HEADER_WARNING:             header = (!copy) ? new SIP_Header_Warning()             : new SIP_Header_Warning(*((SIP_Header_Warning *) copy));                          break;
        default:                                                                                                                                                                        break;
    }

    return header;
}

//-------------------------------------------

bool SIP_Header::decode_headers(std::string &sip_msg, std::map<SIP_Header_Type, std::list<SIP_Header *>> &headers)
{
    std::string type;
    bool matched = SIP_Functions::match(sip_msg, ":", type);
    if (!matched)
    {
        std::cout << "SIP_Header::decode_header -> Failed to get \":\" character (msg=" << sip_msg.c_str() << ")\n";
        return false;
    }

    SIP_Functions::trim(type);

    SIP_Header_Type header_type = SIP_Functions::get_header_type(type);
    if (header_type == SIP_HEADER_TYPE_INVALID)
    {
        std::cout << "SIP_Header::decode_header -> Invalid header type (header=" << type.c_str() << ")\n";
        return false;
    }

    std::string result;
    matched = false;

    do
    {
        SIP_Header *header = create_header(header_type);

        if (header->encode_separator() != SIP_HEADER_SEPARATOR_NONE)
        {
            // There may be more than one of these headers
            matched = SIP_Functions::match(sip_msg, ",", result);
        }else
            result = sip_msg;

        SIP_Functions::trim(result);

        header->_header_line = result;

        if (!header->parse(result))
        {
            std::cout << "SIP_Header::decode_header -> Failed to parse header type (header=" << header_type << ")\n";
            delete header;
            return false;
        }

        if (headers.count(header_type) > 0)
        {
            std::list<SIP_Header *> &header_list = headers.at(header_type);
            header_list.push_back(header);
        }else
        {
            std::list<SIP_Header *> header_list;
            header_list.push_back(header);
            headers[header_type] = header_list;
        }
    }while (matched);

    return true;
}

//-------------------------------------------

bool SIP_Header::encode_headers(std::string &sip_msg, std::map<SIP_Header_Type, std::list<SIP_Header *>> &headers)
{
    std::map<SIP_Header_Type, std::list<SIP_Header *>>::iterator it1 = headers.begin();
    while (it1 != headers.end())
    {
        SIP_Header_Type header_type = it1->first;
        std::list<SIP_Header *> header_list = it1->second;
        it1++;

        std::string type = SIP_Functions::get_header_type(header_type);
        if (type.empty())
        {
            std::cout << "SIP_Header::encode_headers -> Failed to get header type (header=" << header_type << ")\n";
            return false;
        }

        sip_msg += type;
        sip_msg += ": ";

        std::list<SIP_Header *>::iterator it2 = header_list.begin();
        while (it2 != header_list.end())
        {
            SIP_Header *header = *it2;

            if (it2++ != header_list.begin())
            {
                switch (header->encode_separator())
                {
                    case SIP_HEADER_SEPARATOR_NONE:     return false;
                    case SIP_HEADER_SEPARATOR_COMMA:    sip_msg += ", ";                    break;
                    case SIP_HEADER_SEPARATOR_CRLF:     sip_msg += "\r\n" + type + ": ";    break;
                    default:                                                                break;
                }
            }

            if (!header->encode(sip_msg))
                return false;
        }

        sip_msg += "\r\n";
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Media_Range::parse(std::string &sip_msg)
{
    std::string result;
    if (!SIP_Functions::match(sip_msg, "/", result))
        return false;

    SIP_Functions::trim(result);
    if (result.empty())
        return false;

    _type = result;

    bool matched = SIP_Functions::match(sip_msg, ";", result);
    SIP_Functions::trim(result);
    if (result.empty())
        return false;

    _subtype = result;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);

        if (SIP_Functions::start_with(result, "q="))
        {
            _q = result.substr(2);
            SIP_Functions::trim(_q);
            if (_q.empty())
                return false;
        }else
            _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Media_Range::encode(std::string &sip_msg)
{
    if ((_type.empty()) || (_subtype.empty()))
        return false;

    sip_msg += _type;
    sip_msg += "/";
    sip_msg += _subtype;

    if (!_q.empty())
    {
        sip_msg += ";q=";
        sip_msg += _q;
    }

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

void SIP_Media_Range::set_type(SIP_Media_Type type)
{
    switch (type)
    {
        case SIP_MEDIA_TEXT:            _type += "text";            break;
        case SIP_MEDIA_IMAGE:           _type += "image";           break;
        case SIP_MEDIA_AUDIO:           _type += "audio";           break;
        case SIP_MEDIA_VIDEO:           _type += "video";           break;
        case SIP_MEDIA_APPLICATION:     _type += "application";     break;
        case SIP_MEDIA_MESSAGE:         _type += "message";         break;
        case SIP_MEDIA_MULTIPART:       _type += "multipart";       break;
        case SIP_MEDIA_TYPE_ASTERISK:   _type += "*";               break;
        default:                                                    break;
    }
}

//-------------------------------------------

SIP_Media_Type SIP_Media_Range::get_type()
{
    if (_type == "text")
        return SIP_MEDIA_TEXT;
    else if (_type == "image")
        return SIP_MEDIA_IMAGE;
    else if (_type == "audio")
        return SIP_MEDIA_AUDIO;
    else if (_type == "video")
        return SIP_MEDIA_VIDEO;
    else if (_type == "application")
        return SIP_MEDIA_APPLICATION;
    else if (_type == "message")
        return SIP_MEDIA_MESSAGE;
    else if (_type == "multipart")
        return SIP_MEDIA_MULTIPART;
    else if (_type == "*")
        return SIP_MEDIA_TYPE_ASTERISK;

    return SIP_MEDIA_TYPE_INVALID;
}

//-------------------------------------------

void SIP_Media_Range::set_subtype(SIP_Media_Subtype subtype)
{
    switch (subtype)
    {
        case SIP_MEDIA_APPLICATION_SDP:         _subtype = "sdp";       break;
        case SIP_MEDIA_APPLICATION_PIDF_XML:    _subtype = "pidf+xml";  break;
        case SIP_MEDIA_TEXT_PLAIN:              _subtype = "plain";     break;
        case SIP_MEDIA_SUBTYPE_ASTERISK:        _subtype = "*";         break;
        default:                                                        break;
    }
}

//-------------------------------------------

SIP_Media_Subtype SIP_Media_Range::get_subtype()
{
    if (_type == "sdp")
        return SIP_MEDIA_APPLICATION_SDP;
    else if (_type == "pidf+xml")
        return SIP_MEDIA_APPLICATION_PIDF_XML;
    else if (_type == "text/plain")
        return SIP_MEDIA_TEXT_PLAIN;
    else if (_type == "text/html")
        return SIP_MEDIA_TEXT_HTML;
    else if (_type == "*")
        return SIP_MEDIA_SUBTYPE_ASTERISK;

    return SIP_MEDIA_SUBTYPE_INVALID;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Event_Type::parse(std::string &sip_msg)
{
    std::string result;

    bool matched = SIP_Functions::match(sip_msg, ".", result);
    SIP_Functions::trim(result);

    if (result.empty())
        return false;

    _package = result;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ".", result);
        SIP_Functions::trim(result);

        if (result.empty())
            return false;

        _templates.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Event_Type::encode(std::string &sip_msg)
{
    if (_package.empty())
        return false;

    sip_msg += _package;

    std::list<std::string>::iterator it = _templates.begin();
    while (it != _templates.end())
    {
        sip_msg += ".";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

void SIP_Event_Type::set_package(SIP_Event_Package package)
{
    switch (package)
    {
        case SIP_EVENT_PRESENCE: _package = "presence"; break;
        default:                                        break;
    }
}

//-------------------------------------------

SIP_Event_Package SIP_Event_Type::get_package()
{
    if (_package == "presence")
        return SIP_EVENT_PRESENCE;

    return SIP_EVENT_PACKAGE_INVALID;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Accept::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
    {
        // Accept header can be empty
        return true;
    }

    return _media_range.parse(sip_msg);
}

//-------------------------------------------

bool SIP_Header_Accept::encode(std::string &sip_msg)
{
    if ((_media_range.get_type_str().empty()) && (_media_range.get_subtype_str().empty()))
    {
        // Accept header can be empty
        return true;
    }

    if (!_media_range.encode(sip_msg))
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Accept_Encoding::parse(std::string &sip_msg)
{
    std::string result;

    bool matched = SIP_Functions::match(sip_msg, ";", result);
    SIP_Functions::trim(result);

    // Accept-Encoding header can be empty
    _coding = result;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);

        if (SIP_Functions::start_with(result, "q="))
        {
            _q = result.substr(2);
            SIP_Functions::trim(_q);
            if (_q.empty())
                return false;
        }else
            _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Accept_Encoding::encode(std::string &sip_msg)
{
    if (_coding.empty())
    {
        // Accept-Encoding header can be empty
        return true;
    }

    sip_msg += _coding;

    if (!_q.empty())
    {
        sip_msg += ";q=";
        sip_msg += _q;
    }

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Accept_Language::parse(std::string &sip_msg)
{
    std::string result;

    bool matched = SIP_Functions::match(sip_msg, ";", result);
    SIP_Functions::trim(result);

    // Accept-Language header can be empty
    _language = result;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);

        if (SIP_Functions::start_with(result, "q="))
        {
            _q = result.substr(2);
            SIP_Functions::trim(_q);
            if (_q.empty())
                return false;
        }else
            _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Accept_Language::encode(std::string &sip_msg)
{
    if (_language.empty())
    {
        // Accept-Language header can be empty
        return true;
    }

    sip_msg += _language;

    if (!_q.empty())
    {
        sip_msg += ";q=";
        sip_msg += _q;
    }

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Alert_Info::parse(std::string &sip_msg)
{
    std::string result;
    bool matched = SIP_Functions::match(sip_msg, ";", result);

    if (!_address.parse(result))
        return false;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);
        _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Alert_Info::encode(std::string &sip_msg)
{
    if (!_address.encode(sip_msg))
        return false;

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Allow::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);

    // Allow header can be empty
    _method = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Allow::encode(std::string &sip_msg)
{
    if (_method.empty())
    {
        // Allow header can be empty
        return true;
    }

    sip_msg += _method;
    return true;
}

//-------------------------------------------

void SIP_Header_Allow::set_method(SIP_Method_Type method)
{
    _method = SIP_Functions::get_method_type(method);
}

//-------------------------------------------

SIP_Method_Type SIP_Header_Allow::get_method()
{
    return SIP_Functions::get_method_type(_method);
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Allow_Events::parse(std::string &sip_msg)
{
    return _event_type.parse(sip_msg);
}

//-------------------------------------------

bool SIP_Header_Allow_Events::encode(std::string &sip_msg)
{
    if (!_event_type.encode(sip_msg))
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Call_ID::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _call_id = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Call_ID::encode(std::string &sip_msg)
{
    if (_call_id.empty())
        return false;

    sip_msg += _call_id;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Call_Info::parse(std::string &sip_msg)
{
    std::string result;
    bool matched = SIP_Functions::match(sip_msg, ";", result);

    if (!_address.parse(result))
        return false;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);

        if (SIP_Functions::start_with(result, "purpose="))
        {
            _purpose = result.substr(8);
            SIP_Functions::trim(_purpose);
            if (_purpose.empty())
                return false;
        }else
            _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Call_Info::encode(std::string &sip_msg)
{
    if (!_address.encode(sip_msg))
        return false;

    if (!_purpose.empty())
    {
        sip_msg += ";purpose=";
        sip_msg += _purpose;
    }

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

void SIP_Header_Call_Info::set_purpose(SIP_Call_Info_Purpose purpose)
{
    switch (purpose)
    {
        case SIP_CALL_INFO_PURPOSE_ICON: _purpose = "icon";  break;
        case SIP_CALL_INFO_PURPOSE_INFO: _purpose = "info";  break;
        case SIP_CALL_INFO_PURPOSE_CARD: _purpose = "card";  break;
        default:                                             break;
    }
}

//-------------------------------------------

SIP_Call_Info_Purpose SIP_Header_Call_Info::get_purpose()
{
    if (_purpose == "icon")
        return SIP_CALL_INFO_PURPOSE_ICON;
    else if (_purpose == "info")
        return SIP_CALL_INFO_PURPOSE_INFO;
    else if (_purpose == "card")
        return SIP_CALL_INFO_PURPOSE_CARD;

    return SIP_CALL_INFO_PURPOSE_INVALID;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Contact::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);

    // Contact can be an asterisk
    if (sip_msg == "*")
    {
        _star = true;
        return true;
    }else
        _star = false;

    std::string result;
    bool matched = SIP_Functions::match(sip_msg, ";", result);

    if (!_address.parse(result))
        return false;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);

        if (SIP_Functions::start_with(result, "expires="))
        {
            std::string exp = result.substr(8);
            SIP_Functions::trim(exp);
            if (exp.empty())
                return false;

            _expires = (unsigned int) atol(exp.c_str());

        }else if (SIP_Functions::start_with(result, "q="))
        {
            _q = result.substr(2);
            SIP_Functions::trim(_q);
            if (_q.empty())
                return false;
        }else
            _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Contact::encode(std::string &sip_msg)
{
    if (_star)
    {
        sip_msg += "*";
        return true;
    }

    if (!_address.encode(sip_msg))
        return false;

    if (_expires != INVALID_EXPIRES)
    {
        sip_msg += ";expires=";
        sip_msg += std::to_string(_expires);
    }

    if (!_q.empty())
    {
        sip_msg += ";q=";
        sip_msg += _q;
    }

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Content_Disposition::parse(std::string &sip_msg)
{
    std::string result;
    bool matched;

    matched = SIP_Functions::match(sip_msg, ";", result);
    SIP_Functions::trim(result);
    _type = result;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);

        if (SIP_Functions::start_with(result, "handling="))
        {
            std::string handling = result.substr(9);
            SIP_Functions::trim(handling);
            if (handling.empty())
                return false;

            SIP_Functions::trim(handling);
            _handling = handling;
        }else
            _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Content_Disposition::encode(std::string &sip_msg)
{
    if (_type.empty())
        return false;

    sip_msg += _type;

    if (!_handling.empty())
    {
        sip_msg += ";handling=";
        sip_msg += _handling;
    }

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

void SIP_Header_Content_Disposition::set_type(SIP_Disposition_Type type)
{
    switch (type)
    {
        case SIP_DISPOSITION_RENDER:    _type = "render";   break;
        case SIP_DISPOSITION_SESSION:   _type = "session";  break;
        case SIP_DISPOSITION_ICON:      _type = "icon";     break;
        case SIP_DISPOSITION_ALERT:     _type = "alert";    break;
        default:                                            break;
    }
}

//-------------------------------------------

SIP_Disposition_Type SIP_Header_Content_Disposition::get_type()
{
    if (_type == "render")
        return SIP_DISPOSITION_RENDER;
    else if (_type == "session")
        return SIP_DISPOSITION_SESSION;
    else if (_type == "icon")
        return SIP_DISPOSITION_ICON;
    else if (_type == "alert")
        return SIP_DISPOSITION_ALERT;

    return SIP_DISPOSITION_TYPE_INVALID;
}

//-------------------------------------------

void SIP_Header_Content_Disposition::set_handling(SIP_Disposition_Handling handling)
{
    switch (handling)
    {
        case SIP_DISPOSITION_HANDLING_OPTIONAL: _handling = "optional"; break;
        case SIP_DISPOSITION_HANDLING_REQUIRED: _handling = "required"; break;
        default:                                                        break;
    }
}

//-------------------------------------------

SIP_Disposition_Handling SIP_Header_Content_Disposition::get_handling()
{
    if (_handling == "optional")
        return SIP_DISPOSITION_HANDLING_OPTIONAL;
    else if (_handling == "required")
        return SIP_DISPOSITION_HANDLING_REQUIRED;

    return SIP_DISPOSITION_HANDLING_INVALID;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Content_Encoding::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _coding = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Content_Encoding::encode(std::string &sip_msg)
{
    if (_coding.empty())
        return false;

    sip_msg += _coding;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Content_Language::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _language = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Content_Language::encode(std::string &sip_msg)
{
    if (_language.empty())
        return false;

    sip_msg += _language;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Content_Length::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    _length = (unsigned int) atol(sip_msg.c_str());
    return true;
}

//-------------------------------------------

bool SIP_Header_Content_Length::encode(std::string &sip_msg)
{
    if (_length == INVALID_LENGTH)
        return false;

    sip_msg += std::to_string(_length);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Content_Type::parse(std::string &sip_msg)
{
    return _media_type.parse(sip_msg);
}

//-------------------------------------------

bool SIP_Header_Content_Type::encode(std::string &sip_msg)
{
    if (!_media_type.encode(sip_msg))
        return false;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_CSeq::parse(std::string &sip_msg)
{
    std::string result;

    SIP_Functions::trim(sip_msg);
    if (!SIP_Functions::match(sip_msg, " \t", result))
        return false;

    _sequence = (unsigned int) atol(result.c_str());

    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _method = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_CSeq::encode(std::string &sip_msg)
{
    if ((_sequence == INVALID_SEQUENCE) || (_method.empty()))
        return false;

    sip_msg += std::to_string(_sequence);
    sip_msg += " ";
    sip_msg += _method;
    return true;
}

//-------------------------------------------

void SIP_Header_CSeq::set_method(SIP_Method_Type method)
{
    _method = SIP_Functions::get_method_type(method);
}

//-------------------------------------------

SIP_Method_Type SIP_Header_CSeq::get_method()
{
    return SIP_Functions::get_method_type(_method);
}

//-------------------------------------------
//-------------------------------------------

SIP_Header_Date::SIP_Header_Date()
{
    _day = INVALID_DAY;
    _year = INVALID_YEAR;
    _hour = INVALID_HOUR;
    _minute = INVALID_MINUTE;
    _second = INVALID_SECOND;
}

//-------------------------------------------

bool SIP_Header_Date::parse(std::string &sip_msg)
{
    std::string result;

    SIP_Functions::trim(sip_msg);
    if (!SIP_Functions::match(sip_msg, ",", result))
        return false;

    SIP_Functions::trim(result);
    if (result.empty())
        return false;

    _weekday = result;

    SIP_Functions::trim(sip_msg);
    if (!SIP_Functions::match(sip_msg, " ", result))
        return false;

    SIP_Functions::trim(result);
    if (result.empty())
        return false;

    _day = (unsigned short) atol(result.c_str());

    SIP_Functions::trim(sip_msg);
    if (!SIP_Functions::match(sip_msg, " ", result))
        return false;

    SIP_Functions::trim(result);
    if (result.empty())
        return false;

    _month = result;

    SIP_Functions::trim(sip_msg);
    if (!SIP_Functions::match(sip_msg, " ", result))
        return false;

    SIP_Functions::trim(result);
    if (result.empty())
        return false;

    _year = (unsigned short) atol(result.c_str());

    SIP_Functions::trim(sip_msg);
    if (!SIP_Functions::match(sip_msg, ":", result))
        return false;

    SIP_Functions::trim(result);
    if (result.empty())
        return false;

    _hour = (unsigned short) atol(result.c_str());

    SIP_Functions::trim(sip_msg);
    if (!SIP_Functions::match(sip_msg, ":", result))
        return false;

    SIP_Functions::trim(result);
    if (result.empty())
        return false;

    _minute = (unsigned short) atol(result.c_str());

    SIP_Functions::trim(sip_msg);
    if (!SIP_Functions::match(sip_msg, " ", result))
        return false;

    SIP_Functions::trim(result);
    if (result.empty())
        return false;

    _second = (unsigned short) atol(result.c_str());

    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _time_zone = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Date::encode(std::string &sip_msg)
{
    if ((_weekday.empty()) || (_day == INVALID_DAY) || (_month.empty()) || (_year == INVALID_YEAR) ||
        (_hour == INVALID_HOUR) || (_minute == INVALID_MINUTE) || (_second == INVALID_SECOND) ||
        (_time_zone.empty()))
        return false;

    std::string day = std::to_string(_day);
    if (day.size() < 2)
        day.insert(0, 2 - day.size(), '0');

    std::string year = std::to_string(_year);
    if (year.size() < 4)
        year.insert(0, 4 - year.size(), '0');

    std::string hour = std::to_string(_hour);
    if (hour.size() < 2)
        hour.insert(0, 2 - hour.size(), '0');

    std::string minute = std::to_string(_minute);
    if (minute.size() < 2)
        minute.insert(0, 2 - minute.size(), '0');

    std::string second = std::to_string(_second);
    if (second.size() < 2)
        second.insert(0, 2 - second.size(), '0');

    sip_msg += _weekday;
    sip_msg += ", ";
    sip_msg += day;
    sip_msg += " ";
    sip_msg += _month;
    sip_msg += " ";
    sip_msg += year;
    sip_msg += " ";
    sip_msg += hour;
    sip_msg += ":";
    sip_msg += minute;
    sip_msg += ":";
    sip_msg += second;
    sip_msg += " ";
    sip_msg += _time_zone;
    return true;
}

//-------------------------------------------

void SIP_Header_Date::set_weekday(SIP_Date_Weekday weekday)
{
    switch (weekday)
    {
        case SIP_DATE_WEEKDAY_MON: _weekday = "Mon"; break;
        case SIP_DATE_WEEKDAY_TUE: _weekday = "Tue"; break;
        case SIP_DATE_WEEKDAY_WED: _weekday = "Wed"; break;
        case SIP_DATE_WEEKDAY_THU: _weekday = "Thu"; break;
        case SIP_DATE_WEEKDAY_FRI: _weekday = "Fri"; break;
        case SIP_DATE_WEEKDAY_SAT: _weekday = "Sat"; break;
        case SIP_DATE_WEEKDAY_SUN: _weekday = "Sun"; break;
        default:                                     break;
    }
}

//-------------------------------------------

SIP_Date_Weekday SIP_Header_Date::get_weekday()
{
    if (_weekday == "Mon")
        return SIP_DATE_WEEKDAY_MON;
    else if (_weekday == "Tue")
        return SIP_DATE_WEEKDAY_TUE;
    else if (_weekday == "Wed")
        return SIP_DATE_WEEKDAY_WED;
    else if (_weekday == "Thu")
        return SIP_DATE_WEEKDAY_THU;
    else if (_weekday == "Fri")
        return SIP_DATE_WEEKDAY_FRI;
    else if (_weekday == "Sat")
        return SIP_DATE_WEEKDAY_SAT;
    else if (_weekday == "Sun")
        return SIP_DATE_WEEKDAY_SUN;

    return SIP_DATE_WEEKDAY_INVALID;
}

//-------------------------------------------

void SIP_Header_Date::set_month(SIP_Date_Month month)
{
    switch (month)
    {
        case SIP_DATE_MONTH_JAN: _month = "Jan"; break;
        case SIP_DATE_MONTH_FEB: _month = "Feb"; break;
        case SIP_DATE_MONTH_MAR: _month = "Mar"; break;
        case SIP_DATE_MONTH_APR: _month = "Apr"; break;
        case SIP_DATE_MONTH_MAY: _month = "May"; break;
        case SIP_DATE_MONTH_JUN: _month = "Jun"; break;
        case SIP_DATE_MONTH_JUL: _month = "Jul"; break;
        case SIP_DATE_MONTH_AUG: _month = "Aug"; break;
        case SIP_DATE_MONTH_SEP: _month = "Sep"; break;
        case SIP_DATE_MONTH_OCT: _month = "Oct"; break;
        case SIP_DATE_MONTH_NOV: _month = "Nov"; break;
        case SIP_DATE_MONTH_DEC: _month = "Dec"; break;
        default:                                 break;
    }
}

//-------------------------------------------

SIP_Date_Month SIP_Header_Date::get_month()
{
    if (_month == "Jan")
        return SIP_DATE_MONTH_JAN;
    else if (_month == "Feb")
        return SIP_DATE_MONTH_FEB;
    else if (_month == "Mar")
        return SIP_DATE_MONTH_MAR;
    else if (_month == "Apr")
        return SIP_DATE_MONTH_APR;
    else if (_month == "May")
        return SIP_DATE_MONTH_MAY;
    else if (_month == "Jun")
        return SIP_DATE_MONTH_JUN;
    else if (_month == "Jul")
        return SIP_DATE_MONTH_JUL;
    else if (_month == "Aug")
        return SIP_DATE_MONTH_AUG;
    else if (_month == "Sep")
        return SIP_DATE_MONTH_SEP;
    else if (_month == "Oct")
        return SIP_DATE_MONTH_OCT;
    else if (_month == "Nov")
        return SIP_DATE_MONTH_NOV;
    else if (_month == "Dec")
        return SIP_DATE_MONTH_DEC;

    return SIP_DATE_MONTH_INVALID;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Error_Info::parse(std::string &sip_msg)
{
    std::string result;
    bool matched = SIP_Functions::match(sip_msg, ";", result);

    if (!_address.parse(result))
        return false;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);
        _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Error_Info::encode(std::string &sip_msg)
{
    if (!_address.encode(sip_msg))
        return false;

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Event::parse(std::string &sip_msg)
{
    std::string result;
    bool matched = SIP_Functions::match(sip_msg, ";", result);

    if (!_event_type.parse(result))
        return false;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);

        if (SIP_Functions::start_with(result, "id="))
        {
            _id = result.substr(3);
            SIP_Functions::trim(_id);
            if (_id.empty())
                return false;
        }else
            _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Event::encode(std::string &sip_msg)
{
    if (!_event_type.encode(sip_msg))
        return false;

    if (!_id.empty())
    {
        sip_msg += ";id=";
        sip_msg += _id;
    }

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Expires::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    _expires = (unsigned int) atol(sip_msg.c_str());
    return true;
}

//-------------------------------------------

bool SIP_Header_Expires::encode(std::string &sip_msg)
{
    if (_expires == INVALID_EXPIRES)
        return false;

    sip_msg += std::to_string(_expires);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_From::parse(std::string &sip_msg)
{
    std::string result;
    bool matched = SIP_Functions::match(sip_msg, ";", result);

    if (!_address.parse(result))
        return false;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);

        if (SIP_Functions::start_with(result, "tag="))
        {
            _tag = result.substr(4);
            SIP_Functions::trim(_tag);
            if (_tag.empty())
                return false;
        }else
            _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_From::encode(std::string &sip_msg)
{
    if (!_address.encode(sip_msg))
        return false;

    if (!_tag.empty())
    {
        sip_msg += ";tag=";
        sip_msg += _tag;
    }

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_In_Reply_To::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _call_id = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_In_Reply_To::encode(std::string &sip_msg)
{
    if (_call_id.empty())
        return false;

    sip_msg += _call_id;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Max_Forwards::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    _max_forwards = (unsigned int) atol(sip_msg.c_str());
    return true;
}

//-------------------------------------------

bool SIP_Header_Max_Forwards::encode(std::string &sip_msg)
{
    if (_max_forwards == INVALID_MAX_FORWARDS)
        return false;

    sip_msg += std::to_string(_max_forwards);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Mime_Version::parse(std::string &sip_msg)
{
    std::string result;

    SIP_Functions::trim(sip_msg);
    if (!SIP_Functions::match(sip_msg, ".", result))
        return false;

    SIP_Functions::trim(result);
    if (result.empty())
        return false;

    _major_version = (unsigned int) atol(result.c_str());

    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _minor_version = (unsigned int) atol(sip_msg.c_str());
    return true;
}

//-------------------------------------------

bool SIP_Header_Mime_Version::encode(std::string &sip_msg)
{
    if ((_major_version == INVALID_MIME_VERSION) || (_minor_version == INVALID_MIME_VERSION))
        return false;

    sip_msg += std::to_string(_major_version);
    sip_msg += ".";
    sip_msg += std::to_string(_minor_version);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Min_Expires::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    _min_expires = (unsigned int) atol(sip_msg.c_str());
    return true;
}

//-------------------------------------------

bool SIP_Header_Min_Expires::encode(std::string &sip_msg)
{
    if (_min_expires == INVALID_MIN_EXPIRES)
        return false;

    sip_msg += std::to_string(_min_expires);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Organization::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    _organization = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Organization::encode(std::string &sip_msg)
{
    sip_msg += _organization;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Priority::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _priority = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Priority::encode(std::string &sip_msg)
{
    if (_priority.empty())
        return false;

    sip_msg += _priority;
    return true;
}

//-------------------------------------------

void SIP_Header_Priority::set_priority(SIP_Priority_Value priority)
{
    switch (priority)
    {
        case SIP_PRIORITY_EMERGENCY:    _priority = "emergency";    break;
        case SIP_PRIORITY_URGENT:       _priority = "urgent";       break;
        case SIP_PRIORITY_NORMAL:       _priority = "normal";       break;
        case SIP_PRIORITY_NON_URGENT:   _priority = "non-urgent";   break;
        default:                                                    break;
    }
}

//-------------------------------------------

SIP_Priority_Value SIP_Header_Priority::get_priority()
{
    if (_priority == "emergency")
        return SIP_PRIORITY_EMERGENCY;
    else if (_priority == "urgent")
        return SIP_PRIORITY_URGENT;
    else if (_priority == "normal")
        return SIP_PRIORITY_NORMAL;
    else if (_priority == "non-urgent")
        return SIP_PRIORITY_NON_URGENT;

    return SIP_PRIORITY_VALUE_INVALID;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Proxy_Require::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _option_tag = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Proxy_Require::encode(std::string &sip_msg)
{
    if (_option_tag.empty())
        return false;

    sip_msg += _option_tag;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Record_Route::parse(std::string &sip_msg)
{
    std::string result;
    bool matched = SIP_Functions::match(sip_msg, ";", result);

    if (!_address.parse(result))
        return false;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);
        _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Record_Route::encode(std::string &sip_msg)
{
    if (!_address.encode(sip_msg))
        return false;

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Reply_To::parse(std::string &sip_msg)
{
    std::string result;
    bool matched = SIP_Functions::match(sip_msg, ";", result);

    if (!_address.parse(result))
        return false;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);
        _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Reply_To::encode(std::string &sip_msg)
{
    if (!_address.encode(sip_msg))
        return false;

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Require::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _option_tag = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Require::encode(std::string &sip_msg)
{
    if (_option_tag.empty())
        return false;

    sip_msg += _option_tag;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Route::parse(std::string &sip_msg)
{
    std::string result;
    bool matched = SIP_Functions::match(sip_msg, ";", result);

    if (!_address.parse(result))
        return false;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);
        _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Route::encode(std::string &sip_msg)
{
    if (!_address.encode(sip_msg))
        return false;

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Server::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _server = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Server::encode(std::string &sip_msg)
{
    if (_server.empty())
        return false;

    sip_msg += _server;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Subject::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    _subject = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Subject::encode(std::string &sip_msg)
{
    sip_msg += _subject;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Subscription_State::parse(std::string &sip_msg)
{
    std::string result;
    bool matched;

    matched = SIP_Functions::match(sip_msg, ";", result);
    SIP_Functions::trim(result);
    if (result.empty())
        return false;

    _state = result;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);

        if (SIP_Functions::start_with(result, "expires="))
        {
            std::string exp = result.substr(8);
            SIP_Functions::trim(exp);
            if (exp.empty())
                return false;

            _expires = (unsigned int) atol(exp.c_str());
        }else
            _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Subscription_State::encode(std::string &sip_msg)
{
    if (_state.empty())
        return false;

    sip_msg += _state;

    if (_expires != INVALID_EXPIRES)
    {
        sip_msg += ";expires=";
        sip_msg += std::to_string(_expires);
    }

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

void SIP_Header_Subscription_State::set_state(SIP_Subscription_State state)
{
    switch (state)
    {
        case SIP_SUBSCRIPTION_STATE_ACTIVE:     _state = "active";      break;
        case SIP_SUBSCRIPTION_STATE_PENDING:    _state = "pending";     break;
        case SIP_SUBSCRIPTION_STATE_TERMINATED: _state = "terminated";  break;
        default:                                                        break;
    }
}

//-------------------------------------------

SIP_Subscription_State SIP_Header_Subscription_State::get_state()
{
    if (_state == "active")
        return SIP_SUBSCRIPTION_STATE_ACTIVE;
    else if (_state == "pending")
        return SIP_SUBSCRIPTION_STATE_PENDING;
    else if (_state == "terminated")
        return SIP_SUBSCRIPTION_STATE_TERMINATED;

    return SIP_SUBSCRIPTION_STATE_INVALID;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Supported::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    _option_tag = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Supported::encode(std::string &sip_msg)
{
    sip_msg += _option_tag;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Timestamp::parse(std::string &sip_msg)
{
    std::string result;
    bool matched;

    SIP_Functions::trim(sip_msg);

    matched = SIP_Functions::match(sip_msg, " \t", result);
    SIP_Functions::trim(result);
    if (result.empty())
        return false;

    _timestamp = result;

    if (matched)
    {
        SIP_Functions::trim(sip_msg);
        _delay = sip_msg;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Timestamp::encode(std::string &sip_msg)
{
    if (_timestamp.empty())
        return false;

    sip_msg += _timestamp;

    if (!_delay.empty())
    {
        sip_msg += " ";
        sip_msg += _delay;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_To::parse(std::string &sip_msg)
{
    std::string result;
    bool matched = SIP_Functions::match(sip_msg, ";", result);

    if (!_address.parse(result))
        return false;

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);

        if (SIP_Functions::start_with(result, "tag="))
        {
            _tag = result.substr(4);
            SIP_Functions::trim(_tag);
            if (_tag.empty())
                return false;
        }else
            _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_To::encode(std::string &sip_msg)
{
    if (!_address.encode(sip_msg))
        return false;

    if (!_tag.empty())
    {
        sip_msg += ";tag=";
        sip_msg += _tag;
    }

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Unsupported::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _option_tag = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Unsupported::encode(std::string &sip_msg)
{
    if (_option_tag.empty())
        return false;

    sip_msg += _option_tag;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_User_Agent::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _user_agent = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_User_Agent::encode(std::string &sip_msg)
{
    if (_user_agent.empty())
        return false;

    sip_msg += _user_agent;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Via::parse(std::string &sip_msg)
{
    std::string result;
    bool matched;

    matched = SIP_Functions::match(sip_msg, "/", result);
    if (!matched)
        return false;
    SIP_Functions::trim(result);
    _protocol_name = result;
    if (_protocol_name.empty())
        return false;

    matched = SIP_Functions::match(sip_msg, "/", result);
    if (!matched)
        return false;
    SIP_Functions::trim(result);
    _protocol_version = result;
    if (_protocol_version.empty())
        return false;

    SIP_Functions::skip(sip_msg, " \t");
    matched = SIP_Functions::match(sip_msg, " \t", result);
    if (!matched)
        return false;
    SIP_Functions::trim(result);
    _transport = result;
    if (_transport.empty())
        return false;

    matched = SIP_Functions::match(sip_msg, ":", result);
    if (matched)
    {
        SIP_Functions::trim(result);
        _host = result;
        if (_host.empty())
            return false;

        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);
        _port = (unsigned short) atol(result.c_str());
    }else
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);
        _host = result;
        if (_host.empty())
            return false;

        _port = INVALID_PORT;
    }

    while (matched)
    {
        matched = SIP_Functions::match(sip_msg, ";", result);
        SIP_Functions::trim(result);

        if (SIP_Functions::start_with(result, "branch="))
        {
            _branch = &result[7];
            SIP_Functions::trim(_branch);
            if (_branch.empty())
                return false;

        }else if (SIP_Functions::start_with(result, "received="))
        {
            _received = &result[9];
            SIP_Functions::trim(_received);
            if (_received.empty())
                return false;
        }else
            _parameters.push_back(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Via::encode(std::string &sip_msg)
{
    if ((_protocol_name.empty()) || (_protocol_version.empty()) || (_transport.empty()) || (_host.empty()))
        return false;

    sip_msg += _protocol_name;
    sip_msg += "/";
    sip_msg += _protocol_version;
    sip_msg += "/";
    sip_msg += _transport;
    sip_msg += " ";
    sip_msg += _host;

    if (_port != INVALID_PORT)
    {
        sip_msg += ":";
        sip_msg += std::to_string(_port);
    }

    if (!_branch.empty())
    {
        sip_msg += ";branch=";
        sip_msg += _branch;
    }

    if (!_received.empty())
    {
        sip_msg += ";received=";
        sip_msg += _received;
    }

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

void SIP_Header_Via::set_transport(SIP_Transport_Type transport)
{
    _transport = SIP_Functions::get_transport_type(transport);
}

//-------------------------------------------

SIP_Transport_Type SIP_Header_Via::get_transport()
{
    return SIP_Functions::get_transport_type(_transport);
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Warning::parse(std::string &sip_msg)
{
    std::string result;

    SIP_Functions::trim(sip_msg);
    if (!SIP_Functions::match(sip_msg, " ", result))
        return false;

    SIP_Functions::trim(result);
    if (result.empty())
        return false;

    _code = (unsigned short) atol(result.c_str());

    SIP_Functions::trim(sip_msg);
    if (!SIP_Functions::match(sip_msg, " ", result))
        return false;

    SIP_Functions::trim(result);
    if (result.empty())
        return false;

    _agent = result;

    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _text = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Warning::encode(std::string &sip_msg)
{
    if ((_code == INVALID_CODE) || (_agent.empty()) || (_text.empty()))
        return false;

    std::string code = std::to_string(_code);
    if (code.size() < 3)
        code.insert(0, 3 - code.size(), '0');

    sip_msg += code;
    sip_msg += " ";
    sip_msg += _agent;
    sip_msg += " ";
    sip_msg += _text;
    return true;
}

//-------------------------------------------
