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
        default:
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

    _version = String_Functions::str_to_us(msg);
    if (_version == INVALID_VERSION)
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
