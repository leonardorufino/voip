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
