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
#include "util/util_functions.h"

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

SIP_Body_Unknown::SIP_Body_Unknown(const SIP_Body_Unknown &body) : _body(NULL)
{
    set_body(body._body, body._size);
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

    set_body(body, size);
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

void SIP_Body_Unknown::set_body(const char *body, unsigned short size)
{
    if (_body)
        delete _body;

    if (size > 0)
    {
        _body = new char[size + 1];
        memcpy(_body, body, size);
        _body[size] = 0;
        _size = size;
    }else
    {
        _body = NULL;
        _size = 0;
    }
}

//-------------------------------------------

bool SIP_Body_Unknown::set_body(std::string body)
{
    if (body.empty())
    {
        if (_body)
        {
            delete _body;
            _body = NULL;
        }

        _size = 0;
        return true;
    }

    std::vector<char> vector;
    if (!Util_Functions::HexToVector(body, vector))
    {
        _logger.warning("Failed to set body: hex to vector failed (body=%s)", body.c_str());
        return false;
    }

    if (vector.empty())
    {
        _logger.warning("Failed to set body: vector is empty (body=%s)", body.c_str());
        return false;
    }

    if (_body)
        delete _body;

    _size = (unsigned short) vector.size();
    _body = new char[_size];

    for (unsigned int i = 0; i < _size; i++)
        _body[i] = vector.at(i);

    return true;
}

//-------------------------------------------

bool SIP_Body_Unknown::get_body(std::string &body)
{
    if (!_body)
    {
        body.clear();
        return true;
    }

    std::vector<char> vector;
    for (unsigned short i = 0; i < _size; i++)
        vector.push_back(_body[i]);

    if (!Util_Functions::VectorToHex(vector, body))
    {
        _logger.warning("Failed to get body: vector to hex failed");
        return false;
    }

    if (body.empty())
    {
        _logger.warning("Failed to get body: body is empty");
        return false;
    }

    return true;
}

//-------------------------------------------
