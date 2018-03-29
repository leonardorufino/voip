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
#include "util/string_functions.h"

Logger SIP_Parameter_List::_logger(Log_Manager::LOG_SIP_ADDRESS);

//-------------------------------------------

bool SIP_Parameter_List::add_parameter(std::string parameter, unsigned short pos)
{
    if (parameter.empty())
    {
        _logger.warning("Failed to add parameter: invalid parameter");
        return false;
    }

    unsigned short count = 0;

    std::list<std::string>::const_iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        if (count++ == pos)
            break;

        it++;
    }

    _parameters.insert(it, parameter);
    return true;
}

//-------------------------------------------

bool SIP_Parameter_List::remove_parameter(unsigned short pos)
{
    unsigned short count = 0;

    std::list<std::string>::const_iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        if (count++ == pos)
        {
            _parameters.erase(it);
            return true;
        }

        it++;
    }

    _logger.warning("Failed to remove parameter: invalid position (pos=%d, count=%d)", pos, count);
    return false;
}

//-------------------------------------------

std::string SIP_Parameter_List::get_parameter(unsigned short pos)
{
    unsigned short count = 0;

    std::list<std::string>::const_iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        if (count++ == pos)
            return *it;

        it++;
    }

    _logger.warning("Failed to get parameter: invalid position (pos=%d, count=%d)", pos, count);
    return "";
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Host::decode(std::string &sip_msg)
{
    std::string result;

    String_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    if ((sip_msg.size() > 2) && (sip_msg.front() == '[') && (sip_msg.back() == ']'))
        _address = sip_msg.substr(1, sip_msg.size() - 2);
    else
        _address = sip_msg;

    return true;
}

//-------------------------------------------

bool SIP_Host::encode(std::string &sip_msg)
{
    if (_address.empty())
        return false;

    if (Socket::address_to_address_family(_address) == Socket::ADDRESS_FAMILY_IPv6)
    {
        sip_msg += "[";
        sip_msg += _address;
        sip_msg += "]";
    }else
        sip_msg += _address;

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_URI::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);

    std::string user_host;
    bool has_parameter = String_Functions::match(sip_msg, ";", user_host);
    String_Functions::trim(user_host);

    std::string parameters;
    bool has_headers = String_Functions::match(sip_msg, "?", (has_parameter ? parameters : user_host));

    std::string user_password;
    if (String_Functions::match(user_host, "@", user_password))
    {
        String_Functions::trim(user_password);
        if (user_password.empty())
            return false;

        std::string user;
        if (String_Functions::match(user_password, ":", user))
        {
            String_Functions::trim(user);
            if (user.empty())
                return false;

            String_Functions::trim(user_password);

            _user = user;
            _password = user_password;
        }else
            _user = user_password;
    }

    std::string host;
    if (String_Functions::match(user_host, ":", host))
    {
        String_Functions::trim(host);
        if (host.empty())
            return false;

        if (!_host.decode(host))
            return false;

        String_Functions::trim(user_host);
        _port = String_Functions::str_to_us(user_host);
        if (_port == INVALID_PORT)
            return false;
    }else
    {
        String_Functions::trim(user_host);
        if (user_host.empty())
            return false;

        if (!_host.decode(user_host))
            return false;

        _port = INVALID_PORT;
    }

    while (has_parameter)
    {
        std::string param;
        has_parameter = String_Functions::match(parameters, ";", param);
        String_Functions::trim(param);

        if (String_Functions::start_with(param, "transport="))
        {
            _transport = param.substr(10);
            String_Functions::trim(_transport);
            if (_transport.empty())
                return false;

        }else if (String_Functions::start_with(param, "user="))
        {
            _user_param = param.substr(5);
            String_Functions::trim(_user_param);
            if (_user_param.empty())
                return false;

        }else if (String_Functions::start_with(param, "method="))
        {
            _method = param.substr(7);
            String_Functions::trim(_method);
            if (_method.empty())
                return false;

        }else if (String_Functions::start_with(param, "ttl="))
        {
            std::string ttl = param.substr(4);
            String_Functions::trim(ttl);
            if (ttl.empty())
                return false;

            _ttl = String_Functions::str_to_us(ttl);
            if (_ttl == INVALID_TTL)
                return false;

        }else if (String_Functions::start_with(param, "maddr="))
        {
            std::string maddr = param.substr(6);
            String_Functions::trim(maddr);
            if (maddr.empty())
                return false;

            if (!_maddr.decode(maddr))
                return false;

        }else if (param == "lr")
            _lr = true;
        else
            _parameters.push_back(param);
    }

    while (has_headers)
    {
        std::string header;
        has_headers = String_Functions::match(sip_msg, "&", header);
        String_Functions::trim(header);
        _headers.push_back(header);
    }

    return true;
}

//-------------------------------------------

bool SIP_URI::encode(std::string &sip_msg)
{
    if (!_user.empty())
    {
        sip_msg += _user;

        if (!_password.empty())
        {
            sip_msg += ":";
            sip_msg += _password;
        }

        sip_msg += "@";
    }

    if (!_host.encode(sip_msg))
        return false;

    if (_port != INVALID_PORT)
    {
        sip_msg += ":";
        sip_msg += std::to_string(_port);
    }

    if (!_transport.empty())
    {
        sip_msg += ";transport=";
        sip_msg += _transport;
    }

    if (!_user_param.empty())
    {
        sip_msg += ";user=";
        sip_msg += _user_param;
    }

    if (!_method.empty())
    {
        sip_msg += ";method=";
        sip_msg += _method;
    }

    if (_ttl != INVALID_TTL)
    {
        sip_msg += ";ttl=";
        sip_msg += std::to_string(_ttl);
    }

    if (!_maddr.get_address().empty())
    {
        sip_msg += ";maddr=";
        if (!_maddr.encode(sip_msg))
            return false;
    }

    if (_lr)
        sip_msg += ";lr";

    std::list<std::string>::const_iterator it_params = _parameters.begin();
    while (it_params != _parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it_params++;
    }

    std::list<std::string>::const_iterator it_headers = _headers.begin();
    while (it_headers != _headers.end())
    {
        if (it_headers == _headers.begin())
            sip_msg += "?";
        else
            sip_msg += "&";

        sip_msg += *it_headers++;
    }

    return true;
}

//-------------------------------------------

void SIP_URI::set_transport(SIP_Transport_Type transport)
{
    _transport = SIP_Functions::get_transport_type(transport);
}

//-------------------------------------------

SIP_Transport_Type SIP_URI::get_transport_enum()
{
    return SIP_Functions::get_transport_type(_transport);
}

//-------------------------------------------

void SIP_URI::set_user_param(SIP_URI::User_Param user_param)
{
    switch (user_param)
    {
        case USER_PARAM_PHONE:  _user_param = "phone";  break;
        case USER_PARAM_IP:     _user_param = "ip";     break;
        default:                                        break;
    }
}

//-------------------------------------------

SIP_URI::User_Param SIP_URI::get_user_param_enum()
{
    if (_user_param == "phone")
        return USER_PARAM_PHONE;
    else if (_user_param == "ip")
        return USER_PARAM_IP;

    return USER_PARAM_INVALID;
}

//-------------------------------------------

void SIP_URI::set_method(SIP_Method_Type method)
{
    _method = SIP_Functions::get_method_type(method);
}

//-------------------------------------------

SIP_Method_Type SIP_URI::get_method_enum()
{
    return SIP_Functions::get_method_type(_method);
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Absolute_URI::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);
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

bool SIP_Address::decode(std::string &sip_msg)
{
    std::string display;
    std::string uri;

    if (String_Functions::match(sip_msg, "<", display, true))
    {
        String_Functions::trim(display);

        if (!display.empty())
        {
            if ((display.size() >= 2) && (display.front() == '\"') && (display.back() == '\"'))
            {
                _display_name_double_quote = true;

                display.erase(0, 1);
                display.erase(display.size() - 1);

                String_Functions::trim(display);
            }else
                _display_name_double_quote = false;

            _display_name = display;
        }else
            _display_name_double_quote = false;

        if (!String_Functions::match(sip_msg, ">", uri, true))
            return false;

        _uri_angle_quote = true;
    }else
    {
        _display_name_double_quote = false;
        _uri_angle_quote = false;

        uri = sip_msg;
    }

    String_Functions::trim(uri);

    std::string scheme;
    if (!String_Functions::match(uri, ":", scheme))
        return false;

    String_Functions::trim(scheme);
    if (scheme.empty())
        return false;

    _scheme = scheme;

    switch (get_scheme_enum())
    {
        case SCHEME_SIP:
        case SCHEME_SIPS:
        {
            if (!_sip_uri.decode(uri))
                return false;
            break;
        }

        default:
        {
            if (!_absolute_uri.decode(uri))
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
        if (_display_name_double_quote)
            sip_msg += "\"";

        sip_msg += _display_name;

        if (_display_name_double_quote)
            sip_msg += "\"";

        sip_msg += " ";
    }

    if (_uri_angle_quote)
        sip_msg += "<";

    sip_msg += _scheme;
    sip_msg += ":";

    switch (get_scheme_enum())
    {
        case SCHEME_SIP:
        case SCHEME_SIPS:
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

    if (_uri_angle_quote)
        sip_msg += ">";

    return true;
}

//-------------------------------------------

void SIP_Address::set_scheme(SIP_Address::Scheme scheme)
{
    switch (scheme)
    {
        case SCHEME_SIP:    _scheme = "sip";    break;
        case SCHEME_SIPS:   _scheme = "sips";   break;
        default:                                break;
    }
}

//-------------------------------------------

SIP_Address::Scheme SIP_Address::get_scheme_enum()
{
    if (_scheme == "sip")
        return SCHEME_SIP;
    else if (_scheme == "sips")
        return SCHEME_SIPS;

    return SCHEME_INVALID;
}

//-------------------------------------------
