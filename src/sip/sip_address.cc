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

bool SIP_URI::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);

    std::string user_host;
    bool has_parameter = SIP_Functions::match(sip_msg, ";", user_host);
    SIP_Functions::trim(user_host);

    std::string user;
    if (SIP_Functions::match(user_host, "@", user))
        _user = user;

    std::string host;
    if (SIP_Functions::match(user_host, ":", host))
    {
        SIP_Functions::trim(host);
        if (host.empty())
            return false;

        _host = host;

        SIP_Functions::trim(user_host);
        _port = (unsigned short) atol(user_host.c_str());
    }else
    {
        SIP_Functions::trim(user_host);
        if (host.empty())
            return false;

        _host = user_host;
        _port = INVALID_PORT;
    }

    while (has_parameter)
    {
        std::string param;
        has_parameter = SIP_Functions::match(sip_msg, ";", param);
        SIP_Functions::trim(param);

        if (param == "lr")
            _lr = true;
        else
            _parameters.push_back(param);
    }

    return true;
}

//-------------------------------------------

bool SIP_URI::encode(std::string &sip_msg)
{
    if (_host.empty())
        return false;

    if (!_user.empty())
    {
        sip_msg += _user;
        sip_msg += "@";
    }

    sip_msg += _host;

    if (_port != INVALID_PORT)
    {
        sip_msg += ":";
        sip_msg += std::to_string(_port);
    }

    if (_lr)
        sip_msg += ";lr";

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

bool SIP_Absolute_URI::parse(std::string &sip_msg)
{
    SIP_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _address = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Absolute_URI::encode(std::string &sip_msg)
{
    if (_address.empty())
        return false;

    sip_msg += _address;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Address::parse(std::string &sip_msg)
{
    std::string display_name;
    std::string uri;

    if (SIP_Functions::match(sip_msg, "<", display_name, true))
    {
        SIP_Functions::trim(display_name);
        _display_name = display_name;

        if (!SIP_Functions::match(sip_msg, ">", uri, true))
            return false;
    }else
        uri = sip_msg;

    SIP_Functions::trim(uri);

    std::string scheme;
    if (!SIP_Functions::match(uri, ":", scheme))
        return false;

    SIP_Functions::trim(scheme);
    if (scheme.empty())
        return false;

    _scheme = scheme;

    switch (get_scheme())
    {
        case SIP_ADDRESS_SCHEME_SIP:
        case SIP_ADDRESS_SCHEME_SIPS:
        {
            if (!_sip_uri.parse(uri))
                return false;
            break;
        }

        default:
        {
            if (!_absolute_uri.parse(uri))
                return false;
            break;
        }
    }

    return true;
}

//-------------------------------------------

bool SIP_Address::encode(std::string &sip_msg)
{
    if (_scheme.empty())
        return false;

    if (!_display_name.empty())
    {
        sip_msg += _display_name;
        sip_msg += " ";
    }

    sip_msg += "<";
    sip_msg += _scheme;
    sip_msg += ":";

    switch (get_scheme())
    {
        case SIP_ADDRESS_SCHEME_SIP:
        case SIP_ADDRESS_SCHEME_SIPS:
        {
            if (!_sip_uri.encode(sip_msg))
                return false;
            break;
        }

        default:
        {
            if (!_absolute_uri.encode(sip_msg))
                return false;
            break;
        }
    }

    sip_msg += ">";
    return true;
}

//-------------------------------------------

void SIP_Address::set_scheme(SIP_Address_Scheme scheme)
{
    switch (scheme)
    {
        case SIP_ADDRESS_SCHEME_SIP:    _scheme = "sip";    break;
        case SIP_ADDRESS_SCHEME_SIPS:   _scheme = "sips";   break;
        default:                                            break;
    }
}

//-------------------------------------------

SIP_Address_Scheme SIP_Address::get_scheme()
{
    if (_scheme == "sip")
        return SIP_ADDRESS_SCHEME_SIP;
    else if (_scheme == "sips")
        return SIP_ADDRESS_SCHEME_SIPS;

    return SIP_ADDRESS_SCHEME_INVALID;
}

//-------------------------------------------
