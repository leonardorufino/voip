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

#include "sdp_field.h"
#include "sdp_functions.h"
#include "util/string_functions.h"

Logger SDP_Field::_logger(Log_Manager::LOG_SDP_FIELD);

//-------------------------------------------

SDP_Field *SDP_Field::create_field(SDP_Field_Type field_type, const SDP_Field *copy)
{
    SDP_Field *field = NULL;

    switch (field_type)
    {
        case SDP_FIELD_PROTOCOL_VERSION:
            field = (!copy) ? new SDP_Field_Protocol_Version()
                            : new SDP_Field_Protocol_Version(dynamic_cast<const SDP_Field_Protocol_Version &>(*copy));
            break;
        case SDP_FIELD_ORIGIN:
            field = (!copy) ? new SDP_Field_Origin()
                            : new SDP_Field_Origin(dynamic_cast<const SDP_Field_Origin &>(*copy));
            break;
        case SDP_FIELD_SESSION_NAME:
            field = (!copy) ? new SDP_Field_Session_Name()
                            : new SDP_Field_Session_Name(dynamic_cast<const SDP_Field_Session_Name &>(*copy));
            break;
        case SDP_FIELD_SESSION_INFORMATION:
            field = (!copy) ? new SDP_Field_Session_Information()
                            : new SDP_Field_Session_Information(dynamic_cast<const SDP_Field_Session_Information &>(*copy));
            break;
        case SDP_FIELD_URI:
            field = (!copy) ? new SDP_Field_URI()
                            : new SDP_Field_URI(dynamic_cast<const SDP_Field_URI &>(*copy));
            break;
        case SDP_FIELD_EMAIL_ADDRESS:
            field = (!copy) ? new SDP_Field_Email_Address()
                            : new SDP_Field_Email_Address(dynamic_cast<const SDP_Field_Email_Address &>(*copy));
            break;
        case SDP_FIELD_PHONE_NUMBER:
            field = (!copy) ? new SDP_Field_Phone_Number()
                            : new SDP_Field_Phone_Number(dynamic_cast<const SDP_Field_Phone_Number &>(*copy));
            break;
        case SDP_FIELD_CONNECTION_DATA:
            field = (!copy) ? new SDP_Field_Connection_Data()
                            : new SDP_Field_Connection_Data(dynamic_cast<const SDP_Field_Connection_Data &>(*copy));
            break;
        case SDP_FIELD_BANDWIDTH:
            field = (!copy) ? new SDP_Field_Bandwidth()
                            : new SDP_Field_Bandwidth(dynamic_cast<const SDP_Field_Bandwidth &>(*copy));
            break;
        case SDP_FIELD_TIMING:
            field = (!copy) ? new SDP_Field_Timing()
                            : new SDP_Field_Timing(dynamic_cast<const SDP_Field_Timing &>(*copy));
            break;
        case SDP_FIELD_REPEAT_TIME:
            field = (!copy) ? new SDP_Field_Repeat_Time()
                            : new SDP_Field_Repeat_Time(dynamic_cast<const SDP_Field_Repeat_Time &>(*copy));
            break;
        case SDP_FIELD_TIME_ZONE:
            field = (!copy) ? new SDP_Field_Time_Zone()
                            : new SDP_Field_Time_Zone(dynamic_cast<const SDP_Field_Time_Zone &>(*copy));
            break;
        case SDP_FIELD_ENCRYPTION_KEY:
            field = (!copy) ? new SDP_Field_Encryption_Key()
                            : new SDP_Field_Encryption_Key(dynamic_cast<const SDP_Field_Encryption_Key &>(*copy));
            break;
        case SDP_FIELD_ATTRIBUTE:
            field = (!copy) ? new SDP_Field_Attribute()
                            : new SDP_Field_Attribute(dynamic_cast<const SDP_Field_Attribute &>(*copy));
            break;
        case SDP_FIELD_MEDIA_DESCRIPTION:
            field = (!copy) ? new SDP_Field_Media_Description()
                            : new SDP_Field_Media_Description(dynamic_cast<const SDP_Field_Media_Description &>(*copy));
            break;
        default:
            _logger.warning("Failed to create field: invalid type (type=%d)", field_type);
            break;
    }

    return field;
}

//-------------------------------------------

bool SDP_Field::decode_fields(std::string &msg, sdp_field_list &fields)
{
    std::string type;
    bool matched = String_Functions::match(msg, "=", type);
    if (!matched)
    {
        _logger.warning("Failed to decode fields: character \"=\" not present (msg=%s)", msg.c_str());
        return false;
    }

    SDP_Field_Type field_type = SDP_Functions::get_field_type(type);
    if (field_type == SDP_FIELD_INVALID)
    {
        _logger.warning("Failed to decode fields: invalid field type (field=%s)", type.c_str());
        return false;
    }

    SDP_Field *field = create_field(field_type);
    if (!field)
    {
        _logger.warning("Failed to decode fields: create field failed (field=%d)", field_type);
        return false;
    }

    field->_field_line = msg;

    if (!field->decode(msg))
    {
        _logger.warning("Failed to decode fields: decode failed (field=%d)", field_type);
        delete field;
        return false;
    }

    fields.push_back(field);
    return true;
}

//-------------------------------------------

bool SDP_Field::encode_fields(std::string &msg, sdp_field_list &fields)
{
    std::string type;

    sdp_field_list::const_iterator it = fields.begin();
    while (it != fields.end())
    {
        SDP_Field *field = *it++;

        SDP_Field_Type field_type = field->get_field_type();

        type = SDP_Functions::get_field_type(field_type);
        if (type.empty())
        {
            _logger.warning("Failed to encode fields: invalid field type (field=%d)", field_type);
            return false;
        }

        msg += type;
        msg += "=";

        if (!field->encode(msg))
        {
            _logger.warning("Failed to encode fields: encode failed (field=%d)", field->get_field_type());
            return false;
        }

		msg += "\r\n";
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_Protocol_Version::decode(std::string &msg)
{
    if (msg.empty())
        return false;

    if (!set_version(msg))
        return false;

    return true;
}

//-------------------------------------------

bool SDP_Field_Protocol_Version::encode(std::string &msg)
{
    if (_version == INVALID_VERSION)
        return false;

    msg += std::to_string(_version);
    return true;
}

//-------------------------------------------

bool SDP_Field_Protocol_Version::set_version(std::string version)
{
    _version = String_Functions::str_to_us(version);
    if (_version == INVALID_VERSION)
    {
        _logger.warning("Failed to set version: str to us failed (version=%s)", version.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SDP_Field_Protocol_Version::get_version(std::string &version)
{
    if (_version == INVALID_VERSION)
    {
        _logger.warning("Failed to get version: invalid version");
        return false;
    }

    version = std::to_string(_version);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_Origin::decode(std::string &msg)
{
    std::string result;

    if (!String_Functions::match(msg, " ", result))
        return false;

    if (result.empty())
        return false;

    _username = result;

    if (!String_Functions::match(msg, " ", result))
        return false;

    if (result.empty())
        return false;

    _session_id = result;

    if (!String_Functions::match(msg, " ", result))
        return false;

    if (result.empty())
        return false;

    _session_version = result;

    if (!String_Functions::match(msg, " ", result))
        return false;

    if (result.empty())
        return false;

    _network_type = result;

    if (!String_Functions::match(msg, " ", result))
        return false;

    if (result.empty())
        return false;

    _address_type = result;

    if (msg.empty())
        return false;

    _unicast_address = msg;
    return true;
}

//-------------------------------------------

bool SDP_Field_Origin::encode(std::string &msg)
{
    if ((_username.empty()) || (_session_id.empty()) || (_session_version.empty()) || (_network_type.empty()) ||
        (_address_type.empty()) || (_unicast_address.empty()))
        return false;

    msg += _username;
    msg += " ";
    msg += _session_id;
    msg += " ";
    msg += _session_version;
    msg += " ";
    msg += _network_type;
    msg += " ";
    msg += _address_type;
    msg += " ";
    msg += _unicast_address;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_Session_Name::decode(std::string &msg)
{
    if (msg.empty())
        return false;

    _session_name = msg;
    return true;
}

//-------------------------------------------

bool SDP_Field_Session_Name::encode(std::string &msg)
{
    if (_session_name.empty())
        return false;

    msg += _session_name;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_Session_Information::decode(std::string &msg)
{
    _session_information = msg;
    return true;
}

//-------------------------------------------

bool SDP_Field_Session_Information::encode(std::string &msg)
{
    msg += _session_information;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_URI::decode(std::string &msg)
{
    _uri = msg;
    return true;
}

//-------------------------------------------

bool SDP_Field_URI::encode(std::string &msg)
{
    msg += _uri;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_Email_Address::decode(std::string &msg)
{
    _email = msg;
    return true;
}

//-------------------------------------------

bool SDP_Field_Email_Address::encode(std::string &msg)
{
    msg += _email;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_Phone_Number::decode(std::string &msg)
{
    _phone = msg;
    return true;
}

//-------------------------------------------

bool SDP_Field_Phone_Number::encode(std::string &msg)
{
    msg += _phone;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_Connection_Data::decode(std::string &msg)
{
    std::string result;

    if (!String_Functions::match(msg, " ", result))
        return false;

    if (result.empty())
        return false;

    _network_type = result;

    if (!String_Functions::match(msg, " ", result))
        return false;

    if (result.empty())
        return false;

    _address_type = result;

    bool has_slash = String_Functions::match(msg, "/", result);

    if (result.empty())
        return false;

    _connection_address = result;

    if (has_slash)
    {
        has_slash = String_Functions::match(msg, "/", result);

        if (result.empty())
            return false;

        if (_address_type != "IP6")
        {
            _ttl = String_Functions::str_to_us(result);
            if (_ttl == INVALID_TTL)
                return false;

            if (has_slash)
            {
                if (msg.empty())
                    return false;

                _number_addresses = String_Functions::str_to_us(msg);
                if (_number_addresses == INVALID_NUMBER_ADDRESSES)
                    return false;
            }
        }else
        {
            _number_addresses = String_Functions::str_to_us(result);
            if (_number_addresses == INVALID_NUMBER_ADDRESSES)
                return false;
        }
    }

    return true;
}

//-------------------------------------------

bool SDP_Field_Connection_Data::encode(std::string &msg)
{
    if ((_network_type.empty()) || (_address_type.empty()) || (_connection_address.empty()))
        return false;

    msg += _network_type;
    msg += " ";
    msg += _address_type;
    msg += " ";
    msg += _connection_address;

    if (_ttl != INVALID_TTL)
    {
        msg += "/";
        msg += std::to_string(_ttl);
    }

    if (_number_addresses != INVALID_NUMBER_ADDRESSES)
    {
        msg += "/";
        msg += std::to_string(_number_addresses);
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_Bandwidth::decode(std::string &msg)
{
    std::string result;

    if (!String_Functions::match(msg, ":", result))
        return false;

    if (result.empty())
        return false;

    _type = result;

    if (msg.empty())
        return false;

    _bandwidth = String_Functions::str_to_ul(msg);
    if (_bandwidth == INVALID_BANDWIDTH)
        return false;

    return true;
}

//-------------------------------------------

bool SDP_Field_Bandwidth::encode(std::string &msg)
{
    if ((_type.empty()) || (_bandwidth == INVALID_BANDWIDTH))
        return false;

    msg += _type;
    msg += ":";
    msg += std::to_string(_bandwidth);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_Timing::decode(std::string &msg)
{
    std::string result;

    if (!String_Functions::match(msg, " ", result))
        return false;

    if (result.empty())
        return false;

    _start = String_Functions::str_to_ull(result);
    if (_start == INVALID_TIME)
        return false;

    if (msg.empty())
        return false;

    _stop = String_Functions::str_to_ull(msg);
    if (_stop == INVALID_TIME)
        return false;

    return true;
}

//-------------------------------------------

bool SDP_Field_Timing::encode(std::string &msg)
{
    if ((_start == INVALID_TIME) || (_stop == INVALID_TIME))
        return false;

    msg += std::to_string(_start);
    msg += " ";
    msg += std::to_string(_stop);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_Repeat_Time::decode(std::string &msg)
{
    std::string result;

    if (!String_Functions::match(msg, " ", result))
        return false;

    if (result.empty())
        return false;

    _interval = result;

    if (!String_Functions::match(msg, " ", result))
        return false;

    if (result.empty())
        return false;

    _duration = result;

    if (msg.empty())
        return false;

    bool matched;

    do
    {
        matched = String_Functions::match(msg, " ", result);

        if (result.empty())
            return false;

        _offsets.push_back(result);
    }while (matched);

    return true;
}

//-------------------------------------------

bool SDP_Field_Repeat_Time::encode(std::string &msg)
{
    if ((_interval.empty()) || (_duration.empty()) || (_offsets.empty()))
        return false;

    msg += _interval;
    msg += " ";
    msg += _duration;

    std::list<std::string>::const_iterator it = _offsets.begin();
    while (it != _offsets.end())
    {
        msg += " ";
        msg += *it++;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_Time_Zone::decode(std::string &msg)
{
    std::string result;
    bool matched;

    do
    {
        if (!String_Functions::match(msg, " ", result))
            return false;

        if (result.empty())
            return false;

        _adjustments.push_back(result);

        matched = String_Functions::match(msg, " ", result);

        if (result.empty())
            return false;

        _offsets.push_back(result);
    }while (matched);

    return true;
}

//-------------------------------------------

bool SDP_Field_Time_Zone::encode(std::string &msg)
{
    if ((_adjustments.empty()) || (_offsets.empty()) || (_adjustments.size() != _offsets.size()))
        return false;

    std::list<std::string>::const_iterator it1 = _adjustments.begin();
    std::list<std::string>::const_iterator it2 = _offsets.begin();
    while ((it1 != _adjustments.end()) && (it2 != _offsets.end()))
    {
        if (it1 != _adjustments.begin())
            msg += " ";

        msg += *it1++;
        msg += " ";
        msg += *it2++;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_Encryption_Key::decode(std::string &msg)
{
    std::string result;

    bool matched = String_Functions::match(msg, ":", result);

    if (result.empty())
        return false;

    _method = result;

    if (matched)
    {
        if (msg.empty())
            return false;

        _key = msg;
    }

    return true;
}

//-------------------------------------------

bool SDP_Field_Encryption_Key::encode(std::string &msg)
{
    if (_method.empty())
        return false;

    msg += _method;

    if (!_key.empty())
    {
        msg += ":";
        msg += _key;
    }

    return true;
}

//-------------------------------------------

void SDP_Field_Encryption_Key::set_method(SDP_Field_Encryption_Key::Method method)
{
    switch (method)
    {
        case METHOD_CLEAR:      _method = "clear";      break;
        case METHOD_BASE64:     _method = "base64";     break;
        case METHOD_URI:        _method = "uri";        break;
        case METHOD_PROMPT:     _method = "prompt";     break;
        default:                                        break;
    }
}

//-------------------------------------------

SDP_Field_Encryption_Key::Method SDP_Field_Encryption_Key::get_method_enum()
{
    if (_method == "clear")
        return METHOD_CLEAR;
    else if (_method == "base64")
        return METHOD_BASE64;
    else if (_method == "uri")
        return METHOD_URI;
    else if (_method == "prompt")
        return METHOD_PROMPT;

    return METHOD_INVALID;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_Attribute::decode(std::string &msg)
{
    std::string result;

    bool matched = String_Functions::match(msg, ":", result);

    if (result.empty())
        return false;

    _attribute = result;

    if (matched)
    {
        if (msg.empty())
            return false;

        _value = msg;
    }

    return true;
}

//-------------------------------------------

bool SDP_Field_Attribute::encode(std::string &msg)
{
    if (_attribute.empty())
        return false;

    msg += _attribute;

    if (!_value.empty())
    {
        msg += ":";
        msg += _value;
    }

    return true;
}

//-------------------------------------------

void SDP_Field_Attribute::set_attribute(SDP_Field_Attribute::Attribute attribute)
{
    switch (attribute)
    {
        case ATTRIBUTE_CAT:         _attribute = "cat";         break;
        case ATTRIBUTE_KEYWDS:      _attribute = "keywds";      break;
        case ATTRIBUTE_TOOL:        _attribute = "tool";        break;
        case ATTRIBUTE_PTIME:       _attribute = "ptime";       break;
        case ATTRIBUTE_MAXPTIME:    _attribute = "maxptime";    break;
        case ATTRIBUTE_RTPMAP:      _attribute = "rtpmap";      break;
        case ATTRIBUTE_RECVONLY:    _attribute = "recvonly";    break;
        case ATTRIBUTE_SENDRECV:    _attribute = "sendrecv";    break;
        case ATTRIBUTE_SENDONLY:    _attribute = "sendonly";    break;
        case ATTRIBUTE_INACTIVE:    _attribute = "inactive";    break;
        case ATTRIBUTE_ORIENT:      _attribute = "orient";      break;
        case ATTRIBUTE_TYPE:        _attribute = "type";        break;
        case ATTRIBUTE_CHARSET:     _attribute = "charset";     break;
        case ATTRIBUTE_SDPLANG:     _attribute = "sdplang";     break;
        case ATTRIBUTE_LANG:        _attribute = "lang";        break;
        case ATTRIBUTE_FRAMERATE:   _attribute = "framerate";   break;
        case ATTRIBUTE_QUALITY:     _attribute = "quality";     break;
        case ATTRIBUTE_FMTP:        _attribute = "fmtp";        break;
        default:                                                break;
    }
}

//-------------------------------------------

SDP_Field_Attribute::Attribute SDP_Field_Attribute::get_attribute_enum()
{
    if (_attribute == "cat")
        return ATTRIBUTE_CAT;
    else if (_attribute == "keywds")
        return ATTRIBUTE_KEYWDS;
    else if (_attribute == "tool")
        return ATTRIBUTE_TOOL;
    else if (_attribute == "ptime")
        return ATTRIBUTE_PTIME;
    else if (_attribute == "maxptime")
        return ATTRIBUTE_MAXPTIME;
    else if (_attribute == "rtpmap")
        return ATTRIBUTE_RTPMAP;
    else if (_attribute == "recvonly")
        return ATTRIBUTE_RECVONLY;
    else if (_attribute == "sendrecv")
        return ATTRIBUTE_SENDRECV;
    else if (_attribute == "sendonly")
        return ATTRIBUTE_SENDONLY;
    else if (_attribute == "inactive")
        return ATTRIBUTE_INACTIVE;
    else if (_attribute == "orient")
        return ATTRIBUTE_ORIENT;
    else if (_attribute == "type")
        return ATTRIBUTE_TYPE;
    else if (_attribute == "charset")
        return ATTRIBUTE_CHARSET;
    else if (_attribute == "sdplang")
        return ATTRIBUTE_SDPLANG;
    else if (_attribute == "lang")
        return ATTRIBUTE_LANG;
    else if (_attribute == "framerate")
        return ATTRIBUTE_FRAMERATE;
    else if (_attribute == "quality")
        return ATTRIBUTE_QUALITY;
    else if (_attribute == "fmtp")
        return ATTRIBUTE_FMTP;

    return ATTRIBUTE_INVALID;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_Media_Description::decode(std::string &msg)
{
    std::string result;

    if (!String_Functions::match(msg, " ", result))
        return false;

    if (result.empty())
        return false;

    _media = result;

    if (!String_Functions::match(msg, " ", result))
        return false;

    if (result.empty())
        return false;

    std::string port;
    bool has_slash = String_Functions::match(result, "/", port);

    if (port.empty())
        return false;

    _port = String_Functions::str_to_us(port);
    if (_port == INVALID_PORT)
        return false;

    if (has_slash)
    {
        if (result.empty())
            return false;

        _number_ports = String_Functions::str_to_us(result);
        if (_port == INVALID_NUMBER_PORTS)
            return false;
    }

    if (!String_Functions::match(msg, " ", result))
        return false;

    if (result.empty())
        return false;

    _protocol = result;

    bool matched;

    do
    {
        matched = String_Functions::match(msg, " ", result);

        if (result.empty())
            return false;

        _formats.push_back(result);
    }while (matched);

    return true;
}

//-------------------------------------------

bool SDP_Field_Media_Description::encode(std::string &msg)
{
    if ((_media.empty()) || (_port == INVALID_PORT) || (_protocol.empty()) || (_formats.empty()))
        return false;

    msg += _media;
    msg += " ";
    msg += std::to_string(_port);

    if (_number_ports != INVALID_NUMBER_PORTS)
    {
        msg += "/";
        msg += std::to_string(_number_ports);
    }

    msg += " ";
    msg += _protocol;

    std::list<std::string>::const_iterator it = _formats.begin();
    while (it != _formats.end())
    {
        msg += " ";
        msg += *it++;
    }

    return true;
}

//-------------------------------------------

void SDP_Field_Media_Description::set_media(SDP_Field_Media_Description::Media media)
{
    switch (media)
    {
        case MEDIA_AUDIO:           _media = "audio";           break;
        case MEDIA_VIDEO:           _media = "video";           break;
        case MEDIA_TEXT:            _media = "text";            break;
        case MEDIA_APPLICATION:     _media = "application";     break;
        case MEDIA_MESSAGE:         _media = "message";         break;
        default:                                                break;
    }
}

//-------------------------------------------

SDP_Field_Media_Description::Media SDP_Field_Media_Description::get_media_enum()
{
    if (_media == "audio")
        return MEDIA_AUDIO;
    else if (_media == "video")
        return MEDIA_VIDEO;
    else if (_media == "text")
        return MEDIA_TEXT;
    else if (_media == "application")
        return MEDIA_APPLICATION;
    else if (_media == "message")
        return MEDIA_MESSAGE;

    return MEDIA_INVALID;
}

//-------------------------------------------

void SDP_Field_Media_Description::set_protocol(SDP_Field_Media_Description::Protocol protocol)
{
    switch (protocol)
    {
        case PROTOCOL_UDP:          _protocol = "udp";          break;
        case PROTOCOL_RTP_AVP:      _protocol = "RTP/AVP";      break;
        case PROTOCOL_RTP_SAVP:     _protocol = "RTP/SAVP";     break;
        default:                                                break;
    }
}

//-------------------------------------------

SDP_Field_Media_Description::Protocol SDP_Field_Media_Description::get_protocol_enum()
{
    if (_protocol == "udp")
        return PROTOCOL_UDP;
    else if (_protocol == "RTP/AVP")
        return PROTOCOL_RTP_AVP;
    else if (_protocol == "RTP/SAVP")
        return PROTOCOL_RTP_SAVP;

    return PROTOCOL_INVALID;
}

//-------------------------------------------
