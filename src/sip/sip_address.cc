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

#include "sip_address.h"
#include "sip_functions.h"
#include "util/string_functions.h"
#include "util/query.h"

Logger SIP_Host::_logger(Log_Manager::LOG_SIP_ADDRESS);
Logger SIP_URI::_logger(Log_Manager::LOG_SIP_ADDRESS);
Logger SIP_Absolute_URI::_logger(Log_Manager::LOG_SIP_ADDRESS);
Logger SIP_Address::_logger(Log_Manager::LOG_SIP_ADDRESS);

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

bool SIP_Host::query(QueryCommand cmd, const std::string &query, std::string &result)
{
    if (query.empty())
    {
        _logger.warning("Failed to query: invalid query (cmd=%d)", cmd);
        return false;
    }

    Query query_type(query);
    if (query_type._command == "Address")
    {
        if (cmd == QUERY_SET)
        {
            set_address(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_address();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
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
        if (!set_port(user_host))
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

            if (!set_ttl(ttl))
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
            _parameters.add_parameter(param);
    }

    while (has_headers)
    {
        std::string header;
        has_headers = String_Functions::match(sip_msg, "&", header);
        String_Functions::trim(header);
        _headers.add_parameter(header);
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

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it_params = parameters.begin();
    while (it_params != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it_params++;
    }

    std::list<std::string> &headers = _headers.get_parameters();
    std::list<std::string>::const_iterator it_headers = headers.begin();
    while (it_headers != headers.end())
    {
        if (it_headers == headers.begin())
            sip_msg += "?";
        else
            sip_msg += "&";

        sip_msg += *it_headers++;
    }

    return true;
}

//-------------------------------------------

bool SIP_URI::query(QueryCommand cmd, const std::string &query, std::string &result)
{
    if (query.empty())
    {
        _logger.warning("Failed to query: invalid query (cmd=%d)", cmd);
        return false;
    }

    Query query_type(query);
    if (query_type._command == "User")
    {
        if (cmd == QUERY_SET)
        {
            set_user(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_user();
            return true;
        }
    }else if (query_type._command == "Password")
    {
        if (cmd == QUERY_SET)
        {
            set_password(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_password();
            return true;
        }
    }else if (query_type._command == "Host")
    {
        return _host.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "Port")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_port(query_type._remaining))
            {
                _logger.warning("Failed to query: set port failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string port;
            if (!get_port(port))
            {
                _logger.warning("Failed to query: get port failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = port;
            return true;
        }
    }else if (query_type._command == "Transport")
    {
        if (cmd == QUERY_SET)
        {
            set_transport(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_transport();
            return true;
        }
    }else if (query_type._command == "User-Param")
    {
        if (cmd == QUERY_SET)
        {
            set_user_param(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_user_param();
            return true;
        }
    }else if (query_type._command == "Method")
    {
        if (cmd == QUERY_SET)
        {
            set_method(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_method();
            return true;
        }
    }else if (query_type._command == "TTL")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_ttl(query_type._remaining))
            {
                _logger.warning("Failed to query: set ttl failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string ttl;
            if (!get_ttl(ttl))
            {
                _logger.warning("Failed to query: get ttl failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = ttl;
            return true;
        }
    }else if (query_type._command == "Multicast-Address")
    {
        return _maddr.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "LR")
    {
        if (cmd == QUERY_SET)
        {
            bool lr = (query_type._remaining == "True") ? true : false;
            set_lr(lr);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = is_lr() ? "True" : "False";
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "Headers")
    {
        return _headers.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

bool SIP_URI::set_port(std::string port)
{
    _port = String_Functions::str_to_us(port);
    if (_port == INVALID_PORT)
    {
        _logger.warning("Failed to set port: str to us failed (port=%s)", port.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_URI::get_port(std::string &port)
{
    if (_port == INVALID_PORT)
    {
        _logger.warning("Failed to get port: invalid port");
        return false;
    }

    port = std::to_string(_port);
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

bool SIP_URI::set_ttl(std::string ttl)
{
    _ttl = String_Functions::str_to_us(ttl);
    if (_ttl == INVALID_TTL)
    {
        _logger.warning("Failed to set ttl: str to us failed (ttl=%s)", ttl.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_URI::get_ttl(std::string &ttl)
{
    if (_ttl == INVALID_TTL)
    {
        _logger.warning("Failed to get ttl: invalid ttl");
        return false;
    }

    ttl = std::to_string(_ttl);
    return true;
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

bool SIP_Absolute_URI::query(QueryCommand cmd, const std::string &query, std::string &result)
{
    if (query.empty())
    {
        _logger.warning("Failed to query: invalid query (cmd=%d)", cmd);
        return false;
    }

    Query query_type(query);
    if (query_type._command == "Address")
    {
        if (cmd == QUERY_SET)
        {
            set_address(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_address();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
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

bool SIP_Address::query(QueryCommand cmd, const std::string &query, std::string &result)
{
    if (query.empty())
    {
        _logger.warning("Failed to query: invalid query (cmd=%d)", cmd);
        return false;
    }

    Query query_type(query);
    if (query_type._command == "Display-Name-Double-Quote")
    {
        if (cmd == QUERY_SET)
        {
            bool quote = (query_type._remaining == "True") ? true : false;
            set_display_name_double_quote(quote);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_display_name_double_quote() ? "True" : "False";
            return true;
        }
    }else if (query_type._command == "Display-Name")
    {
        if (cmd == QUERY_SET)
        {
            set_display_name(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_display_name();
            return true;
        }
    }else if (query_type._command == "Scheme")
    {
        if (cmd == QUERY_SET)
        {
            set_scheme(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_scheme();
            return true;
        }
    }else if (query_type._command == "URI-Angle-Quote")
    {
        if (cmd == QUERY_SET)
        {
            bool quote = (query_type._remaining == "True") ? true : false;
            set_uri_angle_quote(quote);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_uri_angle_quote() ? "True" : "False";
            return true;
        }
    }else if (query_type._command == "SIP-URI")
    {
        return _sip_uri.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "Absolute-URI")
    {
        return _absolute_uri.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
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
