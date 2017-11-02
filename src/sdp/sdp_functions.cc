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

#include "sdp_functions.h"

//-------------------------------------------

SDP_Field_Type SDP_Functions::get_field_type(std::string field)
{
    if (field == "v")
        return SDP_FIELD_PROTOCOL_VERSION;
    else if (field == "o")
        return SDP_FIELD_ORIGIN;
    else if (field == "s")
        return SDP_FIELD_SESSION_NAME;
    else if (field == "i")
        return SDP_FIELD_SESSION_INFORMATION;
    else if (field == "u")
        return SDP_FIELD_URI;
    else if (field == "e")
        return SDP_FIELD_EMAIL_ADDRESS;
    else if (field == "p")
        return SDP_FIELD_PHONE_NUMBER;
    else if (field == "c")
        return SDP_FIELD_CONNECTION_DATA;
    else if (field == "b")
        return SDP_FIELD_BANDWIDTH;
    else if (field == "t")
        return SDP_FIELD_TIMING;
    else if (field == "r")
        return SDP_FIELD_REPEAT_TIME;
    else if (field == "z")
        return SDP_FIELD_TIME_ZONE;
    else if (field == "k")
        return SDP_FIELD_ENCRYPTION_KEY;
    else if (field == "a")
        return SDP_FIELD_ATTRIBUTE;
    else if (field == "m")
        return SDP_FIELD_MEDIA_DESCRIPTION;

    return SDP_FIELD_INVALID;
}

//-------------------------------------------

std::string SDP_Functions::get_field_type(SDP_Field_Type field)
{
    switch (field)
    {
        case SDP_FIELD_PROTOCOL_VERSION:        return "v";
        case SDP_FIELD_ORIGIN:                  return "o";
        case SDP_FIELD_SESSION_NAME:            return "s";
        case SDP_FIELD_SESSION_INFORMATION:     return "i";
        case SDP_FIELD_URI:                     return "u";
        case SDP_FIELD_EMAIL_ADDRESS:           return "e";
        case SDP_FIELD_PHONE_NUMBER:            return "p";
        case SDP_FIELD_CONNECTION_DATA:         return "c";
        case SDP_FIELD_BANDWIDTH:               return "b";
        case SDP_FIELD_TIMING:                  return "t";
        case SDP_FIELD_REPEAT_TIME:             return "r";
        case SDP_FIELD_TIME_ZONE:               return "z";
        case SDP_FIELD_ENCRYPTION_KEY:          return "k";
        case SDP_FIELD_ATTRIBUTE:               return "a";
        case SDP_FIELD_MEDIA_DESCRIPTION:       return "m";
        default:                                return "";
    }
}

//-------------------------------------------
