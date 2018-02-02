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

#include "sip_body.h"
#include "sdp/sdp_description.h"

Logger SIP_Body::_logger(Log_Manager::LOG_SIP_BODY);

//-------------------------------------------

SIP_Body *SIP_Body::create_body(SIP_Body_Type body_type, const SIP_Body *copy)
{
    SIP_Body *body = NULL;

    switch (body_type)
    {
        case SIP_BODY_SDP:
            body = (!copy) ? new SDP_Description()
                           : new SDP_Description(dynamic_cast<const SDP_Description &>(*copy));
            break;
        case SIP_BODY_UNKNOWN:
            body = (!copy) ? new SIP_Body_Unknown()
                           : new SIP_Body_Unknown(dynamic_cast<const SIP_Body_Unknown &>(*copy));
            break;
        default:
            _logger.warning("Failed to create body: invalid type (type=%d)", body_type);
            break;
    }

    return body;
}

//-------------------------------------------
//-------------------------------------------

SIP_Body_Unknown::SIP_Body_Unknown(const SIP_Body_Unknown &body)
{
    _size = body._size;
    _body = new char[_size + 1];
    memcpy(_body, body._body, _size);
    _body[_size] = 0;
}

//-------------------------------------------

SIP_Body_Unknown::~SIP_Body_Unknown()
{
    if (_body)
        delete _body;
}

//-------------------------------------------

bool SIP_Body_Unknown::decode(const char *body, unsigned short size)
{
    if ((!body) || (size == 0))
    {
        _logger.warning("Failed to decode: invalid parameters");
        return false;
    }

    _size = size;
    _body = new char[_size + 1];
    memcpy(_body, body, _size);
    _body[_size] = 0;
    return true;
}

//-------------------------------------------

bool SIP_Body_Unknown::encode(char *body, unsigned short &size)
{
    if ((!body) || (size <= _size))
    {
        _logger.warning("Failed to encode: invalid parameters");
        return false;
    }

    size = _size;
    memcpy(body, _body, size);
    body[size] = 0;
    return true;
}

//-------------------------------------------
