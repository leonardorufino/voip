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
#include "util/query.h"

Logger SIP_Header::_logger(Log_Manager::LOG_SIP_HEADER);
Logger SIP_Challenge::_logger(Log_Manager::LOG_SIP_HEADER);
Logger SIP_Credential::_logger(Log_Manager::LOG_SIP_HEADER);
Logger SIP_Media_Range::_logger(Log_Manager::LOG_SIP_HEADER);
Logger SIP_Event_Type::_logger(Log_Manager::LOG_SIP_HEADER);

//-------------------------------------------

SIP_Header *SIP_Header::create_header(SIP_Header_Type header_type, const SIP_Header *copy)
{
    SIP_Header *header = NULL;

    switch (header_type)
    {
        case SIP_HEADER_ACCEPT:
            header = (!copy) ? new SIP_Header_Accept()
                             : new SIP_Header_Accept(dynamic_cast<const SIP_Header_Accept &>(*copy));
            break;
        case SIP_HEADER_ACCEPT_ENCODING:
            header = (!copy) ? new SIP_Header_Accept_Encoding()
                             : new SIP_Header_Accept_Encoding(dynamic_cast<const SIP_Header_Accept_Encoding &>(*copy));
            break;
        case SIP_HEADER_ACCEPT_LANGUAGE:
            header = (!copy) ? new SIP_Header_Accept_Language()
                             : new SIP_Header_Accept_Language(dynamic_cast<const SIP_Header_Accept_Language &>(*copy));
            break;
        case SIP_HEADER_ALERT_INFO:
            header = (!copy) ? new SIP_Header_Alert_Info()
                             : new SIP_Header_Alert_Info(dynamic_cast<const SIP_Header_Alert_Info &>(*copy));
            break;
        case SIP_HEADER_ALLOW:
            header = (!copy) ? new SIP_Header_Allow()
                             : new SIP_Header_Allow(dynamic_cast<const SIP_Header_Allow &>(*copy));
            break;
        case SIP_HEADER_ALLOW_EVENTS:
            header = (!copy) ? new SIP_Header_Allow_Events()
                             : new SIP_Header_Allow_Events(dynamic_cast<const SIP_Header_Allow_Events &>(*copy));
            break;
        case SIP_HEADER_AUTHENTICATION_INFO:
            header = (!copy) ? new SIP_Header_Authentication_Info()
                             : new SIP_Header_Authentication_Info(dynamic_cast<const SIP_Header_Authentication_Info &>(*copy));
            break;
        case SIP_HEADER_AUTHORIZATION:
            header = (!copy) ? new SIP_Header_Authorization()
                             : new SIP_Header_Authorization(dynamic_cast<const SIP_Header_Authorization &>(*copy));
            break;
        case SIP_HEADER_CALL_ID:
            header = (!copy) ? new SIP_Header_Call_ID()
                             : new SIP_Header_Call_ID(dynamic_cast<const SIP_Header_Call_ID &>(*copy));
            break;
        case SIP_HEADER_CALL_INFO:
            header = (!copy) ? new SIP_Header_Call_Info()
                             : new SIP_Header_Call_Info(dynamic_cast<const SIP_Header_Call_Info &>(*copy));
            break;
        case SIP_HEADER_CONTACT:
            header = (!copy) ? new SIP_Header_Contact()
                             : new SIP_Header_Contact(dynamic_cast<const SIP_Header_Contact &>(*copy));
            break;
        case SIP_HEADER_CONTENT_DISPOSITION:
            header = (!copy) ? new SIP_Header_Content_Disposition()
                             : new SIP_Header_Content_Disposition(dynamic_cast<const SIP_Header_Content_Disposition &>(*copy));
            break;
        case SIP_HEADER_CONTENT_ENCODING:
            header = (!copy) ? new SIP_Header_Content_Encoding()
                             : new SIP_Header_Content_Encoding(dynamic_cast<const SIP_Header_Content_Encoding &>(*copy));
            break;
        case SIP_HEADER_CONTENT_LANGUAGE:
            header = (!copy) ? new SIP_Header_Content_Language()
                             : new SIP_Header_Content_Language(dynamic_cast<const SIP_Header_Content_Language &>(*copy));
            break;
        case SIP_HEADER_CONTENT_LENGTH:
            header = (!copy) ? new SIP_Header_Content_Length()
                             : new SIP_Header_Content_Length(dynamic_cast<const SIP_Header_Content_Length &>(*copy));
            break;
        case SIP_HEADER_CONTENT_TYPE:
            header = (!copy) ? new SIP_Header_Content_Type()
                             : new SIP_Header_Content_Type(dynamic_cast<const SIP_Header_Content_Type &>(*copy));
            break;
        case SIP_HEADER_CSEQ:
            header = (!copy) ? new SIP_Header_CSeq()
                             : new SIP_Header_CSeq(dynamic_cast<const SIP_Header_CSeq &>(*copy));
            break;
        case SIP_HEADER_DATE:
            header = (!copy) ? new SIP_Header_Date()
                             : new SIP_Header_Date(dynamic_cast<const SIP_Header_Date &>(*copy));
            break;
        case SIP_HEADER_ERROR_INFO:
            header = (!copy) ? new SIP_Header_Error_Info()
                             : new SIP_Header_Error_Info(dynamic_cast<const SIP_Header_Error_Info &>(*copy));
            break;
        case SIP_HEADER_EVENT:
            header = (!copy) ? new SIP_Header_Event()
                             : new SIP_Header_Event(dynamic_cast<const SIP_Header_Event &>(*copy));
            break;
        case SIP_HEADER_EXPIRES:
            header = (!copy) ? new SIP_Header_Expires()
                             : new SIP_Header_Expires(dynamic_cast<const SIP_Header_Expires &>(*copy));
            break;
        case SIP_HEADER_FROM:
            header = (!copy) ? new SIP_Header_From()
                             : new SIP_Header_From(dynamic_cast<const SIP_Header_From &>(*copy));
            break;
        case SIP_HEADER_IN_REPLY_TO:
            header = (!copy) ? new SIP_Header_In_Reply_To()
                             : new SIP_Header_In_Reply_To(dynamic_cast<const SIP_Header_In_Reply_To &>(*copy));
            break;
        case SIP_HEADER_MAX_FORWARDS:
            header = (!copy) ? new SIP_Header_Max_Forwards()
                             : new SIP_Header_Max_Forwards(dynamic_cast<const SIP_Header_Max_Forwards &>(*copy));
            break;
        case SIP_HEADER_MIME_VERSION:
            header = (!copy) ? new SIP_Header_Mime_Version()
                             : new SIP_Header_Mime_Version(dynamic_cast<const SIP_Header_Mime_Version &>(*copy));
            break;
        case SIP_HEADER_MIN_EXPIRES:
            header = (!copy) ? new SIP_Header_Min_Expires()
                             : new SIP_Header_Min_Expires(dynamic_cast<const SIP_Header_Min_Expires &>(*copy));
            break;
        case SIP_HEADER_ORGANIZATION:
            header = (!copy) ? new SIP_Header_Organization()
                             : new SIP_Header_Organization(dynamic_cast<const SIP_Header_Organization &>(*copy));
            break;
        case SIP_HEADER_PRIORITY:
            header = (!copy) ? new SIP_Header_Priority()
                             : new SIP_Header_Priority(dynamic_cast<const SIP_Header_Priority &>(*copy));
            break;
        case SIP_HEADER_PROXY_AUTHENTICATE:
            header = (!copy) ? new SIP_Header_Proxy_Authenticate()
                             : new SIP_Header_Proxy_Authenticate(dynamic_cast<const SIP_Header_Proxy_Authenticate &>(*copy));
            break;
        case SIP_HEADER_PROXY_AUTHORIZATION:
            header = (!copy) ? new SIP_Header_Proxy_Authorization()
                             : new SIP_Header_Proxy_Authorization(dynamic_cast<const SIP_Header_Proxy_Authorization &>(*copy));
            break;
        case SIP_HEADER_PROXY_REQUIRE:
            header = (!copy) ? new SIP_Header_Proxy_Require()
                             : new SIP_Header_Proxy_Require(dynamic_cast<const SIP_Header_Proxy_Require &>(*copy));
            break;
        case SIP_HEADER_RACK:
            header = (!copy) ? new SIP_Header_RAck()
                             : new SIP_Header_RAck(dynamic_cast<const SIP_Header_RAck &>(*copy));
            break;
        case SIP_HEADER_RECORD_ROUTE:
            header = (!copy) ? new SIP_Header_Record_Route()
                             : new SIP_Header_Record_Route(dynamic_cast<const SIP_Header_Record_Route &>(*copy));
            break;
        case SIP_HEADER_REFER_TO:
            header = (!copy) ? new SIP_Header_Refer_To()
                             : new SIP_Header_Refer_To(dynamic_cast<const SIP_Header_Refer_To &>(*copy));
            break;
        case SIP_HEADER_REFERRED_BY:
            header = (!copy) ? new SIP_Header_Referred_By()
                             : new SIP_Header_Referred_By(dynamic_cast<const SIP_Header_Referred_By &>(*copy));
            break;
        case SIP_HEADER_REPLY_TO:
            header = (!copy) ? new SIP_Header_Reply_To()
                             : new SIP_Header_Reply_To(dynamic_cast<const SIP_Header_Reply_To &>(*copy));
            break;
        case SIP_HEADER_REQUIRE:
            header = (!copy) ? new SIP_Header_Require()
                             : new SIP_Header_Require(dynamic_cast<const SIP_Header_Require &>(*copy));
            break;
        case SIP_HEADER_RETRY_AFTER:
            header = (!copy) ? new SIP_Header_Retry_After()
                             : new SIP_Header_Retry_After(dynamic_cast<const SIP_Header_Retry_After &>(*copy));
            break;
        case SIP_HEADER_ROUTE:
            header = (!copy) ? new SIP_Header_Route()
                             : new SIP_Header_Route(dynamic_cast<const SIP_Header_Route &>(*copy));
            break;
        case SIP_HEADER_RSEQ:
            header = (!copy) ? new SIP_Header_RSeq()
                             : new SIP_Header_RSeq(dynamic_cast<const SIP_Header_RSeq &>(*copy));
            break;
        case SIP_HEADER_SERVER:
            header = (!copy) ? new SIP_Header_Server()
                             : new SIP_Header_Server(dynamic_cast<const SIP_Header_Server &>(*copy));
            break;
        case SIP_HEADER_SUBJECT:
            header = (!copy) ? new SIP_Header_Subject()
                             : new SIP_Header_Subject(dynamic_cast<const SIP_Header_Subject &>(*copy));
            break;
        case SIP_HEADER_SUBSCRIPTION_STATE:
            header = (!copy) ? new SIP_Header_Subscription_State()
                             : new SIP_Header_Subscription_State(dynamic_cast<const SIP_Header_Subscription_State &>(*copy));
            break;
        case SIP_HEADER_SUPPORTED:
            header = (!copy) ? new SIP_Header_Supported()
                             : new SIP_Header_Supported(dynamic_cast<const SIP_Header_Supported &>(*copy));
            break;
        case SIP_HEADER_TIMESTAMP:
            header = (!copy) ? new SIP_Header_Timestamp()
                             : new SIP_Header_Timestamp(dynamic_cast<const SIP_Header_Timestamp &>(*copy));
            break;
        case SIP_HEADER_TO:
            header = (!copy) ? new SIP_Header_To()
                             : new SIP_Header_To(dynamic_cast<const SIP_Header_To &>(*copy));
            break;
        case SIP_HEADER_UNKNOWN:
            header = (!copy) ? new SIP_Header_Unknown()
                             : new SIP_Header_Unknown(dynamic_cast<const SIP_Header_Unknown &>(*copy));
            break;
        case SIP_HEADER_UNSUPPORTED:
            header = (!copy) ? new SIP_Header_Unsupported()
                             : new SIP_Header_Unsupported(dynamic_cast<const SIP_Header_Unsupported &>(*copy));
            break;
        case SIP_HEADER_USER_AGENT:
            header = (!copy) ? new SIP_Header_User_Agent()
                             : new SIP_Header_User_Agent(dynamic_cast<const SIP_Header_User_Agent &>(*copy));
            break;
        case SIP_HEADER_VIA:
            header = (!copy) ? new SIP_Header_Via()
                             : new SIP_Header_Via(dynamic_cast<const SIP_Header_Via &>(*copy));
            break;
        case SIP_HEADER_WARNING:
            header = (!copy) ? new SIP_Header_Warning()
                             : new SIP_Header_Warning(dynamic_cast<const SIP_Header_Warning &>(*copy));
            break;
        case SIP_HEADER_WWW_AUTHENTICATE:
            header = (!copy) ? new SIP_Header_WWW_Authenticate()
                             : new SIP_Header_WWW_Authenticate(dynamic_cast<const SIP_Header_WWW_Authenticate &>(*copy));
            break;
        default:
            _logger.warning("Failed to create header: invalid type (type=%d)", header_type);
            break;
    }

    return header;
}

//-------------------------------------------

bool SIP_Header::decode_headers(std::string &sip_msg, sip_header_list &headers)
{
    std::string line = sip_msg;
    std::string type;

    bool matched = String_Functions::match(sip_msg, ":", type);
    if (!matched)
    {
        _logger.warning("Failed to decode headers: character \":\" not present (msg=%s)", sip_msg.c_str());
        return false;
    }

    String_Functions::trim(type);

    SIP_Header_Type header_type = SIP_Functions::get_header_type(type);
    if (header_type == SIP_HEADER_INVALID)
    {
        header_type = SIP_HEADER_UNKNOWN;
        sip_msg = line;
    }

    std::string result;
    matched = false;

    do
    {
        SIP_Header *header = create_header(header_type);
        if (!header)
        {
            _logger.warning("Failed to decode headers: create header failed (header=%d)", header_type);
            return false;
        }

        if (header->decode_separator() == HEADER_SEPARATOR_COMMA)
        {
            // There may be more than one of these headers
            matched = String_Functions::match(sip_msg, ",", result);
        }else
            result = sip_msg;

        String_Functions::trim(result);

        header->_header_line = result;

        if (!header->decode(result))
        {
            _logger.warning("Failed to decode headers: decode failed (header=%d)", header_type);
            delete header;
            return false;
        }

        headers.push_back(header);

    }while (matched);

    return true;
}

//-------------------------------------------

bool SIP_Header::encode_headers(std::string &sip_msg, sip_header_list &headers)
{
    std::string type;

    sip_header_list::const_iterator it = headers.begin();
    while (it != headers.end())
    {
        SIP_Header *header = *it;
        SIP_Header_Type header_type = header->get_header_type();

        if (it++ == headers.begin())
        {
            if (header_type != SIP_HEADER_UNKNOWN)
            {
                type = SIP_Functions::get_header_type(header_type);

                if (type.empty())
                {
                    _logger.warning("Failed to encode headers: invalid header type (header=%d)", header_type);
                    return false;
                }

                sip_msg += type;
                sip_msg += ": ";
            }
        }else
        {
            switch (header->encode_separator())
            {
                case HEADER_SEPARATOR_NONE:
                    _logger.warning("Failed to encode headers: invalid separator (header=%d)", header->get_header_type());
                    return false;

                case HEADER_SEPARATOR_COMMA:
                    sip_msg += ", ";
                    break;

                case HEADER_SEPARATOR_CRLF:
                    sip_msg += "\r\n";
                    if (header_type != SIP_HEADER_UNKNOWN)
                    {
                        sip_msg += type;
                        sip_msg += ": ";
                    }
                    break;

                default:
                    break;
            }
        }

        if (!header->encode(sip_msg))
        {
            _logger.warning("Failed to encode headers: encode failed (header=%d)", header->get_header_type());
            return false;
        }
    }

    sip_msg += "\r\n";
    return true;
}

//-------------------------------------------

bool SIP_Header::query(QueryCommand cmd, const std::string &query, std::string &result)
{
    if (query.empty())
    {
        _logger.warning("Failed to query: invalid query (cmd=%d)", cmd);
        return false;
    }

    return query_header(cmd, query, result);
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Challenge::decode(std::string &sip_msg)
{
    std::string result;

    String_Functions::trim(sip_msg);
    bool matched = String_Functions::match(sip_msg, " \t", result);
    if (!matched)
        return false;

    String_Functions::trim(result);
    if (result.empty())
        return false;

    _scheme = result;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ",", result);
        String_Functions::trim(result);

        if (String_Functions::start_with(result, "realm="))
        {
            _realm = result.substr(6);
            String_Functions::trim(_realm);
            if (_realm.empty())
                return false;

        }else if (String_Functions::start_with(result, "domain="))
        {
            _domain = result.substr(7);
            String_Functions::trim(_domain);
            if (_domain.empty())
                return false;

        }else if (String_Functions::start_with(result, "nonce="))
        {
            _nonce = result.substr(6);
            String_Functions::trim(_nonce);
            if (_nonce.empty())
                return false;

        }else if (String_Functions::start_with(result, "opaque="))
        {
            _opaque = result.substr(7);
            String_Functions::trim(_opaque);
            if (_opaque.empty())
                return false;

        }else if (String_Functions::start_with(result, "stale="))
        {
            _stale = result.substr(6);
            String_Functions::trim(_stale);
            if (_stale.empty())
                return false;

        }else if (String_Functions::start_with(result, "algorithm="))
        {
            _algorithm = result.substr(10);
            String_Functions::trim(_algorithm);
            if (_algorithm.empty())
                return false;

        }else if (String_Functions::start_with(result, "qop="))
        {
            _qop = result.substr(4);
            String_Functions::trim(_qop);
            if (_qop.empty())
                return false;
        }else
            _parameters.add_parameter(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Challenge::encode(std::string &sip_msg)
{
    if (_scheme.empty())
        return false;

    sip_msg += _scheme;

    bool first_param = true;

    if (!_realm.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "realm=";
        sip_msg += _realm;
        first_param = false;
    }

    if (!_domain.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "domain=";
        sip_msg += _domain;
        first_param = false;
    }

    if (!_nonce.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "nonce=";
        sip_msg += _nonce;
        first_param = false;
    }

    if (!_opaque.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "opaque=";
        sip_msg += _opaque;
        first_param = false;
    }

    if (!_stale.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "stale=";
        sip_msg += _stale;
        first_param = false;
    }

    if (!_algorithm.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "algorithm=";
        sip_msg += _algorithm;
        first_param = false;
    }

    if (!_qop.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "qop=";
        sip_msg += _qop;
        first_param = false;
    }

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += *it++;
        first_param = false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Challenge::query(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Scheme")
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
    }else if (query_type._command == "Realm")
    {
        if (cmd == QUERY_SET)
        {
            set_realm(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_realm();
            return true;
        }
    }else if (query_type._command == "Domain")
    {
        if (cmd == QUERY_SET)
        {
            set_domain(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_domain();
            return true;
        }
    }else if (query_type._command == "Nonce")
    {
        if (cmd == QUERY_SET)
        {
            set_nonce(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_nonce();
            return true;
        }
    }else if (query_type._command == "Opaque")
    {
        if (cmd == QUERY_SET)
        {
            set_opaque(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_opaque();
            return true;
        }
    }else if (query_type._command == "Stale")
    {
        if (cmd == QUERY_SET)
        {
            set_stale(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_stale();
            return true;
        }
    }else if (query_type._command == "Algorithm")
    {
        if (cmd == QUERY_SET)
        {
            set_algorithm(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_algorithm();
            return true;
        }
    }else if (query_type._command == "QoP")
    {
        if (cmd == QUERY_SET)
        {
            set_qop(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_qop();
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Credential::decode(std::string &sip_msg)
{
    std::string result;

    String_Functions::trim(sip_msg);
    bool matched = String_Functions::match(sip_msg, " \t", result);
    if (!matched)
        return false;

    String_Functions::trim(result);
    if (result.empty())
        return false;

    _scheme = result;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ",", result);
        String_Functions::trim(result);

        if (String_Functions::start_with(result, "username="))
        {
            _username = result.substr(9);
            String_Functions::trim(_username);
            if (_username.empty())
                return false;

        }else if (String_Functions::start_with(result, "realm="))
        {
            _realm = result.substr(6);
            String_Functions::trim(_realm);
            if (_realm.empty())
                return false;

        }else if (String_Functions::start_with(result, "nonce="))
        {
            _nonce = result.substr(6);
            String_Functions::trim(_nonce);
            if (_nonce.empty())
                return false;

        }else if (String_Functions::start_with(result, "uri="))
        {
            _uri = result.substr(4);
            String_Functions::trim(_uri);
            if (_uri.empty())
                return false;

        }else if (String_Functions::start_with(result, "response="))
        {
            _response = result.substr(9);
            String_Functions::trim(_response);
            if (_response.empty())
                return false;

        }else if (String_Functions::start_with(result, "algorithm="))
        {
            _algorithm = result.substr(10);
            String_Functions::trim(_algorithm);
            if (_algorithm.empty())
                return false;

        }else if (String_Functions::start_with(result, "cnonce="))
        {
            _cnonce = result.substr(7);
            String_Functions::trim(_cnonce);
            if (_cnonce.empty())
                return false;

        }else if (String_Functions::start_with(result, "opaque="))
        {
            _opaque = result.substr(7);
            String_Functions::trim(_opaque);
            if (_opaque.empty())
                return false;

        }else if (String_Functions::start_with(result, "qop="))
        {
            _qop = result.substr(4);
            String_Functions::trim(_qop);
            if (_qop.empty())
                return false;

        }else if (String_Functions::start_with(result, "nc="))
        {
            _nonce_count = result.substr(3);
            String_Functions::trim(_nonce_count);
            if (_nonce_count.empty())
                return false;
        }else
            _parameters.add_parameter(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Credential::encode(std::string &sip_msg)
{
    if (_scheme.empty())
        return false;

    sip_msg += _scheme;

    bool first_param = true;

    if (!_username.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "username=";
        sip_msg += _username;
        first_param = false;
    }

    if (!_realm.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "realm=";
        sip_msg += _realm;
        first_param = false;
    }

    if (!_nonce.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "nonce=";
        sip_msg += _nonce;
        first_param = false;
    }

    if (!_uri.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "uri=";
        sip_msg += _uri;
        first_param = false;
    }

    if (!_response.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "response=";
        sip_msg += _response;
        first_param = false;
    }

    if (!_algorithm.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "algorithm=";
        sip_msg += _algorithm;
        first_param = false;
    }

    if (!_cnonce.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "cnonce=";
        sip_msg += _cnonce;
        first_param = false;
    }

    if (!_opaque.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "opaque=";
        sip_msg += _opaque;
        first_param = false;
    }

    if (!_qop.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "qop=";
        sip_msg += _qop;
        first_param = false;
    }

    if (!_nonce_count.empty())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += "nc=";
        sip_msg += _nonce_count;
        first_param = false;
    }

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += (first_param) ? " " : ", ";
        sip_msg += *it++;
        first_param = false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Credential::query(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Scheme")
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
    }else if (query_type._command == "Username")
    {
        if (cmd == QUERY_SET)
        {
            set_username(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_username();
            return true;
        }
    }else if (query_type._command == "Realm")
    {
        if (cmd == QUERY_SET)
        {
            set_realm(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_realm();
            return true;
        }
    }else if (query_type._command == "Nonce")
    {
        if (cmd == QUERY_SET)
        {
            set_nonce(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_nonce();
            return true;
        }
    }else if (query_type._command == "URI")
    {
        if (cmd == QUERY_SET)
        {
            set_uri(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_uri();
            return true;
        }
    }else if (query_type._command == "Response")
    {
        if (cmd == QUERY_SET)
        {
            set_response(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_response();
            return true;
        }
    }else if (query_type._command == "Algorithm")
    {
        if (cmd == QUERY_SET)
        {
            set_algorithm(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_algorithm();
            return true;
        }
    }else if (query_type._command == "CNonce")
    {
        if (cmd == QUERY_SET)
        {
            set_cnonce(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_cnonce();
            return true;
        }
    }else if (query_type._command == "Opaque")
    {
        if (cmd == QUERY_SET)
        {
            set_opaque(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_opaque();
            return true;
        }
    }else if (query_type._command == "QoP")
    {
        if (cmd == QUERY_SET)
        {
            set_qop(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_qop();
            return true;
        }
    }else if (query_type._command == "Nonce-Count")
    {
        if (cmd == QUERY_SET)
        {
            set_nonce_count(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_nonce_count();
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Media_Range::decode(std::string &sip_msg)
{
    std::string result;
    if (!String_Functions::match(sip_msg, "/", result))
        return false;

    String_Functions::trim(result);
    if (result.empty())
        return false;

    _type = result;

    bool matched = String_Functions::match(sip_msg, ";", result);
    String_Functions::trim(result);
    if (result.empty())
        return false;

    _subtype = result;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);

        if (String_Functions::start_with(result, "q="))
        {
            _q = result.substr(2);
            String_Functions::trim(_q);
            if (_q.empty())
                return false;
        }else
            _parameters.add_parameter(result);
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

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Media_Range::query(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Type")
    {
        if (cmd == QUERY_SET)
        {
            set_type(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_type();
            return true;
        }
    }else if (query_type._command == "Subtype")
    {
        if (cmd == QUERY_SET)
        {
            set_subtype(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_subtype();
            return true;
        }
    }else if (query_type._command == "Q")
    {
        if (cmd == QUERY_SET)
        {
            set_q(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_q();
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

void SIP_Media_Range::set_type(SIP_Media_Range::Type type)
{
    switch (type)
    {
        case TYPE_TEXT:         _type = "text";         break;
        case TYPE_IMAGE:        _type = "image";        break;
        case TYPE_AUDIO:        _type = "audio";        break;
        case TYPE_VIDEO:        _type = "video";        break;
        case TYPE_APPLICATION:  _type = "application";  break;
        case TYPE_MESSAGE:      _type = "message";      break;
        case TYPE_MULTIPART:    _type = "multipart";    break;
        case TYPE_ASTERISK:     _type = "*";            break;
        default:                                        break;
    }
}

//-------------------------------------------

SIP_Media_Range::Type SIP_Media_Range::get_type_enum()
{
    if (_type == "text")
        return TYPE_TEXT;
    else if (_type == "image")
        return TYPE_IMAGE;
    else if (_type == "audio")
        return TYPE_AUDIO;
    else if (_type == "video")
        return TYPE_VIDEO;
    else if (_type == "application")
        return TYPE_APPLICATION;
    else if (_type == "message")
        return TYPE_MESSAGE;
    else if (_type == "multipart")
        return TYPE_MULTIPART;
    else if (_type == "*")
        return TYPE_ASTERISK;

    return TYPE_INVALID;
}

//-------------------------------------------

void SIP_Media_Range::set_subtype(SIP_Media_Range::Subtype subtype)
{
    switch (subtype)
    {
        case SUBTYPE_APPLICATION_SDP:   _subtype = "sdp";   break;
        case SUBTYPE_ASTERISK:          _subtype = "*";     break;
        default:                                            break;
    }
}

//-------------------------------------------

SIP_Media_Range::Subtype SIP_Media_Range::get_subtype_enum()
{
    if (_subtype == "sdp")
        return SUBTYPE_APPLICATION_SDP;
    else if (_subtype == "*")
        return SUBTYPE_ASTERISK;

    return SUBTYPE_INVALID;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Event_Type::decode(std::string &sip_msg)
{
    std::string result;

    bool matched = String_Functions::match(sip_msg, ".", result);
    String_Functions::trim(result);
    if (result.empty())
        return false;

    _package = result;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ".", result);
        String_Functions::trim(result);
        if (result.empty())
            return false;

        _templates.add_parameter(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Event_Type::encode(std::string &sip_msg)
{
    if (_package.empty())
        return false;

    sip_msg += _package;

    std::list<std::string> &templates = _templates.get_parameters();
    std::list<std::string>::const_iterator it = templates.begin();
    while (it != templates.end())
    {
        sip_msg += ".";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Event_Type::query(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Package")
    {
        if (cmd == QUERY_SET)
        {
            set_package(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_package();
            return true;
        }
    }else if (query_type._command == "Templates")
    {
        return _templates.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

void SIP_Event_Type::set_package(SIP_Event_Type::Package package)
{
    switch (package)
    {
        case PACKAGE_PRESENCE: _package = "presence"; break;
        default:                                      break;
    }
}

//-------------------------------------------

SIP_Event_Type::Package SIP_Event_Type::get_package_enum()
{
    if (_package == "presence")
        return PACKAGE_PRESENCE;

    return PACKAGE_INVALID;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Accept::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);
    if (sip_msg.empty())
    {
        // Accept header can be empty
        return true;
    }

    return _media_range.decode(sip_msg);
}

//-------------------------------------------

bool SIP_Header_Accept::encode(std::string &sip_msg)
{
    if ((_media_range.get_type().empty()) && (_media_range.get_subtype().empty()))
    {
        // Accept header can be empty
        return true;
    }

    if (!_media_range.encode(sip_msg))
        return false;

    return true;
}

//-------------------------------------------

bool SIP_Header_Accept::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Media-Range")
        return _media_range.query(cmd, query_type._remaining, result);

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Accept_Encoding::decode(std::string &sip_msg)
{
    std::string result;

    bool matched = String_Functions::match(sip_msg, ";", result);
    String_Functions::trim(result);

    // Accept-Encoding header can be empty
    _coding = result;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);

        if (String_Functions::start_with(result, "q="))
        {
            _q = result.substr(2);
            String_Functions::trim(_q);
            if (_q.empty())
                return false;
        }else
            _parameters.add_parameter(result);
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

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Accept_Encoding::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Coding")
    {
        if (cmd == QUERY_SET)
        {
            set_coding(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_coding();
            return true;
        }
    }else if (query_type._command == "Q")
    {
        if (cmd == QUERY_SET)
        {
            set_q(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_q();
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Accept_Language::decode(std::string &sip_msg)
{
    std::string result;

    bool matched = String_Functions::match(sip_msg, ";", result);
    String_Functions::trim(result);

    // Accept-Language header can be empty
    _language = result;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);

        if (String_Functions::start_with(result, "q="))
        {
            _q = result.substr(2);
            String_Functions::trim(_q);
            if (_q.empty())
                return false;
        }else
            _parameters.add_parameter(result);
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

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Accept_Language::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Language")
    {
        if (cmd == QUERY_SET)
        {
            set_language(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_language();
            return true;
        }
    }else if (query_type._command == "Q")
    {
        if (cmd == QUERY_SET)
        {
            set_q(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_q();
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Alert_Info::decode(std::string &sip_msg)
{
    std::string result;
    bool matched = String_Functions::match(sip_msg, ";", result);

    if (!_address.decode(result))
        return false;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);
        _parameters.add_parameter(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Alert_Info::encode(std::string &sip_msg)
{
    if (!_address.encode(sip_msg))
        return false;

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Alert_Info::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Address")
    {
        return _address.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Allow::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);

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

bool SIP_Header_Allow::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Method")
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
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

void SIP_Header_Allow::set_method(SIP_Method_Type method)
{
    _method = SIP_Functions::get_method_type(method);
}

//-------------------------------------------

SIP_Method_Type SIP_Header_Allow::get_method_enum()
{
    return SIP_Functions::get_method_type(_method);
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Allow_Events::decode(std::string &sip_msg)
{
    return _event_type.decode(sip_msg);
}

//-------------------------------------------

bool SIP_Header_Allow_Events::encode(std::string &sip_msg)
{
    return _event_type.encode(sip_msg);
}

//-------------------------------------------

bool SIP_Header_Allow_Events::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Event-Type")
        return _event_type.query(cmd, query_type._remaining, result);

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Authentication_Info::decode(std::string &sip_msg)
{
    std::string result;
    bool matched;

    do
    {
        matched = String_Functions::match(sip_msg, ",", result);
        String_Functions::trim(result);
        if (result.empty())
            return false;

        if (String_Functions::start_with(result, "nextnonce="))
        {
            _next_nonce = result.substr(10);
            String_Functions::trim(_next_nonce);
            if (_next_nonce.empty())
                return false;

        }else if (String_Functions::start_with(result, "qop="))
        {
            _qop = result.substr(4);
            String_Functions::trim(_qop);
            if (_qop.empty())
                return false;

        }else if (String_Functions::start_with(result, "rspauth="))
        {
            _response = result.substr(8);
            String_Functions::trim(_response);
            if (_response.empty())
                return false;

        }else if (String_Functions::start_with(result, "cnonce="))
        {
            _cnonce = result.substr(7);
            String_Functions::trim(_cnonce);
            if (_cnonce.empty())
                return false;

        }else if (String_Functions::start_with(result, "nc="))
        {
            _nonce_count = result.substr(3);
            String_Functions::trim(_nonce_count);
            if (_nonce_count.empty())
                return false;
        }else
            _parameters.add_parameter(result);

    }while (matched);

    return true;
}

//-------------------------------------------

bool SIP_Header_Authentication_Info::encode(std::string &sip_msg)
{
    bool first_param = true;

    if (!_next_nonce.empty())
    {
        sip_msg += (first_param) ? "" : ", ";
        sip_msg += "nextnonce=";
        sip_msg += _next_nonce;
        first_param = false;
    }

    if (!_qop.empty())
    {
        sip_msg += (first_param) ? "" : ", ";
        sip_msg += "qop=";
        sip_msg += _qop;
        first_param = false;
    }

    if (!_response.empty())
    {
        sip_msg += (first_param) ? "" : ", ";
        sip_msg += "rspauth=";
        sip_msg += _response;
        first_param = false;
    }

    if (!_cnonce.empty())
    {
        sip_msg += (first_param) ? "" : ", ";
        sip_msg += "cnonce=";
        sip_msg += _cnonce;
        first_param = false;
    }

    if (!_nonce_count.empty())
    {
        sip_msg += (first_param) ? "" : ", ";
        sip_msg += "nc=";
        sip_msg += _nonce_count;
        first_param = false;
    }

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += (first_param) ? "" : ", ";
        sip_msg += *it++;
        first_param = false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Authentication_Info::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Next-Nonce")
    {
        if (cmd == QUERY_SET)
        {
            set_next_nonce(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_next_nonce();
            return true;
        }
    }else if (query_type._command == "QoP")
    {
        if (cmd == QUERY_SET)
        {
            set_qop(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_qop();
            return true;
        }
    }else if (query_type._command == "Response")
    {
        if (cmd == QUERY_SET)
        {
            set_response(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_response();
            return true;
        }
    }else if (query_type._command == "CNonce")
    {
        if (cmd == QUERY_SET)
        {
            set_cnonce(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_cnonce();
            return true;
        }
    }else if (query_type._command == "Nonce-Count")
    {
        if (cmd == QUERY_SET)
        {
            set_nonce_count(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_nonce_count();
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Authorization::decode(std::string &sip_msg)
{
    return _credential.decode(sip_msg);
}

//-------------------------------------------

bool SIP_Header_Authorization::encode(std::string &sip_msg)
{
    return _credential.encode(sip_msg);
}

//-------------------------------------------

bool SIP_Header_Authorization::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Credential")
    {
        return _credential.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Call_ID::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);
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

bool SIP_Header_Call_ID::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Call-ID")
    {
        if (cmd == QUERY_SET)
        {
            set_call_id(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_call_id();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

void SIP_Header_Call_ID::set_random_call_id(std::string host)
{
    _call_id = String_Functions::random(20);

    if (!host.empty())
    {
        _call_id += "@";
        _call_id += host;
    }
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Call_Info::decode(std::string &sip_msg)
{
    std::string result;
    bool matched = String_Functions::match(sip_msg, ";", result);

    if (!_address.decode(result))
        return false;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);

        if (String_Functions::start_with(result, "purpose="))
        {
            _purpose = result.substr(8);
            String_Functions::trim(_purpose);
            if (_purpose.empty())
                return false;
        }else
            _parameters.add_parameter(result);
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

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Call_Info::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Address")
    {
        return _address.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "Purpose")
    {
        if (cmd == QUERY_SET)
        {
            set_purpose(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_purpose();
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

void SIP_Header_Call_Info::set_purpose(SIP_Header_Call_Info::Purpose purpose)
{
    switch (purpose)
    {
        case PURPOSE_ICON: _purpose = "icon"; break;
        case PURPOSE_INFO: _purpose = "info"; break;
        case PURPOSE_CARD: _purpose = "card"; break;
        default:                              break;
    }
}

//-------------------------------------------

SIP_Header_Call_Info::Purpose SIP_Header_Call_Info::get_purpose_enum()
{
    if (_purpose == "icon")
        return PURPOSE_ICON;
    else if (_purpose == "info")
        return PURPOSE_INFO;
    else if (_purpose == "card")
        return PURPOSE_CARD;

    return PURPOSE_INVALID;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Contact::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);

    // Contact can be an asterisk
    if (sip_msg == "*")
    {
        _star = true;
        return true;
    }else
        _star = false;

    std::string result;
    bool matched = String_Functions::match(sip_msg, ";", result);

    if (!_address.decode(result))
        return false;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);

        if (String_Functions::start_with(result, "expires="))
        {
            std::string exp = result.substr(8);
            String_Functions::trim(exp);
            if (exp.empty())
                return false;

            if (!set_expires(exp))
                return false;

        }else if (String_Functions::start_with(result, "q="))
        {
            _q = result.substr(2);
            String_Functions::trim(_q);
            if (_q.empty())
                return false;
        }else
            _parameters.add_parameter(result);
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

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Contact::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Star")
    {
        if (cmd == QUERY_SET)
        {
            bool star = (query_type._remaining == "True") ? true : false;
            set_star(star);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = is_star() ? "True" : "False";
            return true;
        }
    }else if (query_type._command == "Address")
    {
        return _address.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "Expires")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_expires(query_type._remaining))
            {
                _logger.warning("Failed to query: set expires failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string expires;
            if (!get_expires(expires))
            {
                _logger.warning("Failed to query: get expires failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = expires;
            return true;
        }
    }else if (query_type._command == "Q")
    {
        if (cmd == QUERY_SET)
        {
            set_q(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_q();
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

bool SIP_Header_Contact::set_expires(std::string expires)
{
    _expires = String_Functions::str_to_ul(expires);
    if (_expires == INVALID_EXPIRES)
    {
        _logger.warning("Failed to set expires: str to ul failed (expires=%s)", expires.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Contact::get_expires(std::string &expires)
{
    if (_expires == INVALID_EXPIRES)
    {
        _logger.warning("Failed to get expires: invalid expires");
        return false;
    }

    expires = std::to_string(_expires);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Content_Disposition::decode(std::string &sip_msg)
{
    std::string result;

    bool matched = String_Functions::match(sip_msg, ";", result);
    String_Functions::trim(result);
    if (result.empty())
        return false;

    _type = result;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);

        if (String_Functions::start_with(result, "handling="))
        {
            _handling = result.substr(9);
            String_Functions::trim(_handling);
            if (_handling.empty())
                return false;
        }else
            _parameters.add_parameter(result);
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

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Content_Disposition::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Type")
    {
        if (cmd == QUERY_SET)
        {
            set_type(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_type();
            return true;
        }
    }else if (query_type._command == "Handling")
    {
        if (cmd == QUERY_SET)
        {
            set_handling(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_handling();
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

void SIP_Header_Content_Disposition::set_type(SIP_Header_Content_Disposition::Type type)
{
    switch (type)
    {
        case TYPE_RENDER:   _type = "render";   break;
        case TYPE_SESSION:  _type = "session";  break;
        case TYPE_ICON:     _type = "icon";     break;
        case TYPE_ALERT:    _type = "alert";    break;
        default:                                break;
    }
}

//-------------------------------------------

SIP_Header_Content_Disposition::Type SIP_Header_Content_Disposition::get_type_enum()
{
    if (_type == "render")
        return TYPE_RENDER;
    else if (_type == "session")
        return TYPE_SESSION;
    else if (_type == "icon")
        return TYPE_ICON;
    else if (_type == "alert")
        return TYPE_ALERT;

    return TYPE_INVALID;
}

//-------------------------------------------

void SIP_Header_Content_Disposition::set_handling(SIP_Header_Content_Disposition::Handling handling)
{
    switch (handling)
    {
        case HANDLING_OPTIONAL: _handling = "optional"; break;
        case HANDLING_REQUIRED: _handling = "required"; break;
        default:                                        break;
    }
}

//-------------------------------------------

SIP_Header_Content_Disposition::Handling SIP_Header_Content_Disposition::get_handling_enum()
{
    if (_handling == "optional")
        return HANDLING_OPTIONAL;
    else if (_handling == "required")
        return HANDLING_REQUIRED;

    return HANDLING_INVALID;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Content_Encoding::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);
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

bool SIP_Header_Content_Encoding::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Coding")
    {
        if (cmd == QUERY_SET)
        {
            set_coding(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_coding();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Content_Language::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);
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

bool SIP_Header_Content_Language::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Language")
    {
        if (cmd == QUERY_SET)
        {
            set_language(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_language();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Content_Length::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    if (!set_length(sip_msg))
        return false;

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

bool SIP_Header_Content_Length::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Length")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_length(query_type._remaining))
            {
                _logger.warning("Failed to query: set length failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string length;
            if (!get_length(length))
            {
                _logger.warning("Failed to query: get length failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = length;
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

bool SIP_Header_Content_Length::set_length(std::string length)
{
    _length = String_Functions::str_to_ul(length);
    if (_length == INVALID_LENGTH)
    {
        _logger.warning("Failed to set length: str to ul failed (length=%s)", length.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Content_Length::get_length(std::string &length)
{
    if (_length == INVALID_LENGTH)
    {
        _logger.warning("Failed to get length: invalid length");
        return false;
    }

    length = std::to_string(_length);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Content_Type::decode(std::string &sip_msg)
{
    return _media_type.decode(sip_msg);
}

//-------------------------------------------

bool SIP_Header_Content_Type::encode(std::string &sip_msg)
{
    return _media_type.encode(sip_msg);
}

//-------------------------------------------

bool SIP_Header_Content_Type::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Media-Type")
        return _media_type.query(cmd, query_type._remaining, result);

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_CSeq::decode(std::string &sip_msg)
{
    std::string result;

    String_Functions::trim(sip_msg);
    if (!String_Functions::match(sip_msg, " \t", result))
        return false;

    if (!set_sequence(result))
        return false;

    String_Functions::trim(sip_msg);
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

bool SIP_Header_CSeq::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Sequence")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_sequence(query_type._remaining))
            {
                _logger.warning("Failed to query: set sequence failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string sequence;
            if (!get_sequence(sequence))
            {
                _logger.warning("Failed to query: get sequence failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = sequence;
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
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

bool SIP_Header_CSeq::set_sequence(std::string sequence)
{
    _sequence = String_Functions::str_to_ul(sequence);
    if (_sequence == INVALID_SEQUENCE)
    {
        _logger.warning("Failed to set sequence: str to ul failed (sequence=%s)", sequence.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_CSeq::get_sequence(std::string &sequence)
{
    if (_sequence == INVALID_SEQUENCE)
    {
        _logger.warning("Failed to get sequence: invalid sequence");
        return false;
    }

    sequence = std::to_string(_sequence);
    return true;
}

//-------------------------------------------

void SIP_Header_CSeq::set_method(SIP_Method_Type method)
{
    _method = SIP_Functions::get_method_type(method);
}

//-------------------------------------------

SIP_Method_Type SIP_Header_CSeq::get_method_enum()
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

bool SIP_Header_Date::decode(std::string &sip_msg)
{
    std::string result;

    String_Functions::trim(sip_msg);
    if (!String_Functions::match(sip_msg, ",", result))
        return false;

    String_Functions::trim(result);
    if (result.empty())
        return false;

    _weekday = result;

    String_Functions::trim(sip_msg);
    if (!String_Functions::match(sip_msg, " ", result))
        return false;

    String_Functions::trim(result);
    if (result.empty())
        return false;

    if (!set_day(result))
        return false;

    String_Functions::trim(sip_msg);
    if (!String_Functions::match(sip_msg, " ", result))
        return false;

    String_Functions::trim(result);
    if (result.empty())
        return false;

    _month = result;

    String_Functions::trim(sip_msg);
    if (!String_Functions::match(sip_msg, " ", result))
        return false;

    String_Functions::trim(result);
    if (result.empty())
        return false;

    if (!set_year(result))
        return false;

    String_Functions::trim(sip_msg);
    if (!String_Functions::match(sip_msg, ":", result))
        return false;

    String_Functions::trim(result);
    if (result.empty())
        return false;

    if (!set_hour(result))
        return false;

    String_Functions::trim(sip_msg);
    if (!String_Functions::match(sip_msg, ":", result))
        return false;

    String_Functions::trim(result);
    if (result.empty())
        return false;

    if (!set_minute(result))
        return false;

    String_Functions::trim(sip_msg);
    if (!String_Functions::match(sip_msg, " ", result))
        return false;

    String_Functions::trim(result);
    if (result.empty())
        return false;

    if (!set_second(result))
        return false;

    String_Functions::trim(sip_msg);
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

    sip_msg += _weekday;
    sip_msg += ", ";
    sip_msg += String_Functions::add_leading_zeros(_day, 2);
    sip_msg += " ";
    sip_msg += _month;
    sip_msg += " ";
    sip_msg += String_Functions::add_leading_zeros(_year, 4);
    sip_msg += " ";
    sip_msg += String_Functions::add_leading_zeros(_hour, 2);
    sip_msg += ":";
    sip_msg += String_Functions::add_leading_zeros(_minute, 2);
    sip_msg += ":";
    sip_msg += String_Functions::add_leading_zeros(_second, 2);
    sip_msg += " ";
    sip_msg += _time_zone;
    return true;
}

//-------------------------------------------

bool SIP_Header_Date::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Weekday")
    {
        if (cmd == QUERY_SET)
        {
            set_weekday(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_weekday();
            return true;
        }
    }else if (query_type._command == "Day")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_day(query_type._remaining))
            {
                _logger.warning("Failed to query: set day failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string day;
            if (!get_day(day))
            {
                _logger.warning("Failed to query: get day failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = day;
            return true;
        }
    }else if (query_type._command == "Month")
    {
        if (cmd == QUERY_SET)
        {
            set_month(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_month();
            return true;
        }
    }else if (query_type._command == "Year")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_year(query_type._remaining))
            {
                _logger.warning("Failed to query: set year failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string year;
            if (!get_year(year))
            {
                _logger.warning("Failed to query: get year failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = year;
            return true;
        }
    }else if (query_type._command == "Hour")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_hour(query_type._remaining))
            {
                _logger.warning("Failed to query: set hour failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string hour;
            if (!get_hour(hour))
            {
                _logger.warning("Failed to query: get hour failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = hour;
            return true;
        }
    }else if (query_type._command == "Minute")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_minute(query_type._remaining))
            {
                _logger.warning("Failed to query: set minute failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string minute;
            if (!get_minute(minute))
            {
                _logger.warning("Failed to query: get minute failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = minute;
            return true;
        }
    }else if (query_type._command == "Second")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_second(query_type._remaining))
            {
                _logger.warning("Failed to query: set second failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string second;
            if (!get_second(second))
            {
                _logger.warning("Failed to query: get second failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = second;
            return true;
        }
    }else if (query_type._command == "Time-Zone")
    {
        if (cmd == QUERY_SET)
        {
            set_time_zone(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_time_zone();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

void SIP_Header_Date::set_weekday(SIP_Header_Date::Weekday weekday)
{
    switch (weekday)
    {
        case WEEKDAY_MON: _weekday = "Mon"; break;
        case WEEKDAY_TUE: _weekday = "Tue"; break;
        case WEEKDAY_WED: _weekday = "Wed"; break;
        case WEEKDAY_THU: _weekday = "Thu"; break;
        case WEEKDAY_FRI: _weekday = "Fri"; break;
        case WEEKDAY_SAT: _weekday = "Sat"; break;
        case WEEKDAY_SUN: _weekday = "Sun"; break;
        default:                            break;
    }
}

//-------------------------------------------

SIP_Header_Date::Weekday SIP_Header_Date::get_weekday_enum()
{
    if (_weekday == "Mon")
        return WEEKDAY_MON;
    else if (_weekday == "Tue")
        return WEEKDAY_TUE;
    else if (_weekday == "Wed")
        return WEEKDAY_WED;
    else if (_weekday == "Thu")
        return WEEKDAY_THU;
    else if (_weekday == "Fri")
        return WEEKDAY_FRI;
    else if (_weekday == "Sat")
        return WEEKDAY_SAT;
    else if (_weekday == "Sun")
        return WEEKDAY_SUN;

    return WEEKDAY_INVALID;
}

//-------------------------------------------

bool SIP_Header_Date::set_day(std::string day)
{
    _day = String_Functions::str_to_us(day);
    if (_day == INVALID_DAY)
    {
        _logger.warning("Failed to set day: str to us failed (day=%s)", day.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Date::get_day(std::string &day)
{
    if (_day == INVALID_DAY)
    {
        _logger.warning("Failed to get day: invalid day");
        return false;
    }

    day = std::to_string(_day);
    return true;
}

//-------------------------------------------

void SIP_Header_Date::set_month(SIP_Header_Date::Month month)
{
    switch (month)
    {
        case MONTH_JAN: _month = "Jan"; break;
        case MONTH_FEB: _month = "Feb"; break;
        case MONTH_MAR: _month = "Mar"; break;
        case MONTH_APR: _month = "Apr"; break;
        case MONTH_MAY: _month = "May"; break;
        case MONTH_JUN: _month = "Jun"; break;
        case MONTH_JUL: _month = "Jul"; break;
        case MONTH_AUG: _month = "Aug"; break;
        case MONTH_SEP: _month = "Sep"; break;
        case MONTH_OCT: _month = "Oct"; break;
        case MONTH_NOV: _month = "Nov"; break;
        case MONTH_DEC: _month = "Dec"; break;
        default:                        break;
    }
}

//-------------------------------------------

SIP_Header_Date::Month SIP_Header_Date::get_month_enum()
{
    if (_month == "Jan")
        return MONTH_JAN;
    else if (_month == "Feb")
        return MONTH_FEB;
    else if (_month == "Mar")
        return MONTH_MAR;
    else if (_month == "Apr")
        return MONTH_APR;
    else if (_month == "May")
        return MONTH_MAY;
    else if (_month == "Jun")
        return MONTH_JUN;
    else if (_month == "Jul")
        return MONTH_JUL;
    else if (_month == "Aug")
        return MONTH_AUG;
    else if (_month == "Sep")
        return MONTH_SEP;
    else if (_month == "Oct")
        return MONTH_OCT;
    else if (_month == "Nov")
        return MONTH_NOV;
    else if (_month == "Dec")
        return MONTH_DEC;

    return MONTH_INVALID;
}

//-------------------------------------------

bool SIP_Header_Date::set_year(std::string year)
{
    _year = String_Functions::str_to_us(year);
    if (_year == INVALID_YEAR)
    {
        _logger.warning("Failed to set year: str to us failed (year=%s)", year.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Date::get_year(std::string &year)
{
    if (_year == INVALID_YEAR)
    {
        _logger.warning("Failed to get year: invalid year");
        return false;
    }

    year = std::to_string(_year);
    return true;
}

//-------------------------------------------

bool SIP_Header_Date::set_hour(std::string hour)
{
    _hour = String_Functions::str_to_us(hour);
    if (_hour == INVALID_HOUR)
    {
        _logger.warning("Failed to set hour: str to us failed (hour=%s)", hour.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Date::get_hour(std::string &hour)
{
    if (_hour == INVALID_HOUR)
    {
        _logger.warning("Failed to get hour: invalid hour");
        return false;
    }

    hour = std::to_string(_hour);
    return true;
}

//-------------------------------------------

bool SIP_Header_Date::set_minute(std::string minute)
{
    _minute = String_Functions::str_to_us(minute);
    if (_minute == INVALID_MINUTE)
    {
        _logger.warning("Failed to set minute: str to us failed (minute=%s)", minute.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Date::get_minute(std::string &minute)
{
    if (_minute == INVALID_MINUTE)
    {
        _logger.warning("Failed to get minute: invalid minute");
        return false;
    }

    minute = std::to_string(_minute);
    return true;
}

//-------------------------------------------

bool SIP_Header_Date::set_second(std::string second)
{
    _second = String_Functions::str_to_us(second);
    if (_second == INVALID_SECOND)
    {
        _logger.warning("Failed to set second: str to us failed (second=%s)", second.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Date::get_second(std::string &second)
{
    if (_second == INVALID_SECOND)
    {
        _logger.warning("Failed to get second: invalid second");
        return false;
    }

    second = std::to_string(_second);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Error_Info::decode(std::string &sip_msg)
{
    std::string result;
    bool matched = String_Functions::match(sip_msg, ";", result);

    if (!_address.decode(result))
        return false;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);
        _parameters.add_parameter(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Error_Info::encode(std::string &sip_msg)
{
    if (!_address.encode(sip_msg))
        return false;

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Error_Info::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Address")
    {
        return _address.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Event::decode(std::string &sip_msg)
{
    std::string result;
    bool matched = String_Functions::match(sip_msg, ";", result);

    if (!_event_type.decode(result))
        return false;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);

        if (String_Functions::start_with(result, "id="))
        {
            _id = result.substr(3);
            String_Functions::trim(_id);
            if (_id.empty())
                return false;
        }else
            _parameters.add_parameter(result);
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

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Event::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Event-Type")
    {
        return _event_type.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "ID")
    {
        if (cmd == QUERY_SET)
        {
            set_id(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_id();
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Expires::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);

    if (!set_expires(sip_msg))
        return false;

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

bool SIP_Header_Expires::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Expires")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_expires(query_type._remaining))
            {
                _logger.warning("Failed to query: set expires failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string expires;
            if (!get_expires(expires))
            {
                _logger.warning("Failed to query: get expires failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = expires;
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

bool SIP_Header_Expires::set_expires(std::string expires)
{
    _expires = String_Functions::str_to_ul(expires);
    if (_expires == INVALID_EXPIRES)
    {
        _logger.warning("Failed to set expires: str to ul failed (expires=%s)", expires.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Expires::get_expires(std::string &expires)
{
    if (_expires == INVALID_EXPIRES)
    {
        _logger.warning("Failed to get expires: invalid expires");
        return false;
    }

    expires = std::to_string(_expires);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_From::decode(std::string &sip_msg)
{
    std::string result;
    bool matched = String_Functions::match(sip_msg, ";", result);

    if (!_address.decode(result))
        return false;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);

        if (String_Functions::start_with(result, "tag="))
        {
            _tag = result.substr(4);
            String_Functions::trim(_tag);
            if (_tag.empty())
                return false;
        }else
            _parameters.add_parameter(result);
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

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_From::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Address")
    {
        return _address.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "Tag")
    {
        if (cmd == QUERY_SET)
        {
            set_tag(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_tag();
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

void SIP_Header_From::set_random_tag()
{
    _tag = String_Functions::random(20);
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_In_Reply_To::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);
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

bool SIP_Header_In_Reply_To::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Call-ID")
    {
        if (cmd == QUERY_SET)
        {
            set_call_id(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_call_id();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Max_Forwards::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);

    if (!set_max_forwards(sip_msg))
        return false;

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

bool SIP_Header_Max_Forwards::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Max-Forwards")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_max_forwards(query_type._remaining))
            {
                _logger.warning("Failed to query: set max forwards failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string max_forwards;
            if (!get_max_forwards(max_forwards))
            {
                _logger.warning("Failed to query: get max forwards failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = max_forwards;
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

bool SIP_Header_Max_Forwards::set_max_forwards(std::string max_forwards)
{
    _max_forwards = String_Functions::str_to_us(max_forwards);
    if (_max_forwards == INVALID_MAX_FORWARDS)
    {
        _logger.warning("Failed to set max forwards: str to us failed (max_forwards=%s)", max_forwards.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Max_Forwards::get_max_forwards(std::string &max_forwards)
{
    if (_max_forwards == INVALID_MAX_FORWARDS)
    {
        _logger.warning("Failed to get max forwards: invalid max forwards");
        return false;
    }

    max_forwards = std::to_string(_max_forwards);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Mime_Version::decode(std::string &sip_msg)
{
    std::string result;

    String_Functions::trim(sip_msg);
    if (!String_Functions::match(sip_msg, ".", result))
        return false;

    String_Functions::trim(result);
    if (result.empty())
        return false;

    if (!set_major_version(result))
        return false;

    String_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    if (!set_minor_version(sip_msg))
        return false;

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

bool SIP_Header_Mime_Version::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Major-Version")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_major_version(query_type._remaining))
            {
                _logger.warning("Failed to query: set major_version failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string major_version;
            if (!get_major_version(major_version))
            {
                _logger.warning("Failed to query: get major version failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = major_version;
            return true;
        }
    }else if (query_type._command == "Minor-Version")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_minor_version(query_type._remaining))
            {
                _logger.warning("Failed to query: set minor_version failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string minor_version;
            if (!get_minor_version(minor_version))
            {
                _logger.warning("Failed to query: get minor version failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = minor_version;
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

bool SIP_Header_Mime_Version::set_major_version(std::string major_version)
{
    _major_version = String_Functions::str_to_ul(major_version);
    if (_major_version == INVALID_MIME_VERSION)
    {
        _logger.warning("Failed to set major version: str to ul failed (major_version=%s)", major_version.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Mime_Version::get_major_version(std::string &major_version)
{
    if (_major_version == INVALID_MIME_VERSION)
    {
        _logger.warning("Failed to get major version: invalid major version");
        return false;
    }

    major_version = std::to_string(_major_version);
    return true;
}

//-------------------------------------------

bool SIP_Header_Mime_Version::set_minor_version(std::string minor_version)
{
    _minor_version = String_Functions::str_to_ul(minor_version);
    if (_minor_version == INVALID_MIME_VERSION)
    {
        _logger.warning("Failed to set minor version: str to ul failed (minor_version=%s)", minor_version.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Mime_Version::get_minor_version(std::string &minor_version)
{
    if (_minor_version == INVALID_MIME_VERSION)
    {
        _logger.warning("Failed to get minor version: invalid minor version");
        return false;
    }

    minor_version = std::to_string(_minor_version);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Min_Expires::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);

    if (!set_min_expires(sip_msg))
        return false;

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

bool SIP_Header_Min_Expires::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Min-Expires")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_min_expires(query_type._remaining))
            {
                _logger.warning("Failed to query: set min expires failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string min_expires;
            if (!get_min_expires(min_expires))
            {
                _logger.warning("Failed to query: get min expires failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = min_expires;
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

bool SIP_Header_Min_Expires::set_min_expires(std::string min_expires)
{
    _min_expires = String_Functions::str_to_ul(min_expires);
    if (_min_expires == INVALID_MIN_EXPIRES)
    {
        _logger.warning("Failed to set min expires: str to ul failed (min_expires=%s)", min_expires.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Min_Expires::get_min_expires(std::string &min_expires)
{
    if (_min_expires == INVALID_MIN_EXPIRES)
    {
        _logger.warning("Failed to get min expires: invalid min expires");
        return false;
    }

    min_expires = std::to_string(_min_expires);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Organization::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);

    // Organization header can be empty
    _organization = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Organization::encode(std::string &sip_msg)
{
    if (_organization.empty())
    {
        // Organization header can be empty
        return true;
    }

    sip_msg += _organization;
    return true;
}

//-------------------------------------------

bool SIP_Header_Organization::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Organization")
    {
        if (cmd == QUERY_SET)
        {
            set_organization(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_organization();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Priority::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);
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

bool SIP_Header_Priority::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Priority")
    {
        if (cmd == QUERY_SET)
        {
            set_priority(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_priority();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

void SIP_Header_Priority::set_priority(SIP_Header_Priority::Priority priority)
{
    switch (priority)
    {
        case PRIORITY_EMERGENCY:    _priority = "emergency";    break;
        case PRIORITY_URGENT:       _priority = "urgent";       break;
        case PRIORITY_NORMAL:       _priority = "normal";       break;
        case PRIORITY_NON_URGENT:   _priority = "non-urgent";   break;
        default:                                                break;
    }
}

//-------------------------------------------

SIP_Header_Priority::Priority SIP_Header_Priority::get_priority_enum()
{
    if (_priority == "emergency")
        return PRIORITY_EMERGENCY;
    else if (_priority == "urgent")
        return PRIORITY_URGENT;
    else if (_priority == "normal")
        return PRIORITY_NORMAL;
    else if (_priority == "non-urgent")
        return PRIORITY_NON_URGENT;

    return PRIORITY_INVALID;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Proxy_Authenticate::decode(std::string &sip_msg)
{
    return _challenge.decode(sip_msg);
}

//-------------------------------------------

bool SIP_Header_Proxy_Authenticate::encode(std::string &sip_msg)
{
    return _challenge.encode(sip_msg);
}

//-------------------------------------------

bool SIP_Header_Proxy_Authenticate::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Challenge")
    {
        return _challenge.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Proxy_Authorization::decode(std::string &sip_msg)
{
    return _credential.decode(sip_msg);
}

//-------------------------------------------

bool SIP_Header_Proxy_Authorization::encode(std::string &sip_msg)
{
    return _credential.encode(sip_msg);
}

//-------------------------------------------

bool SIP_Header_Proxy_Authorization::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Credential")
    {
        return _credential.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Proxy_Require::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);
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

bool SIP_Header_Proxy_Require::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Option-Tag")
    {
        if (cmd == QUERY_SET)
        {
            set_option_tag(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_option_tag();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_RAck::decode(std::string &sip_msg)
{
    std::string result;

    String_Functions::trim(sip_msg);
    if (!String_Functions::match(sip_msg, " \t", result))
        return false;

    if (!set_rseq(result))
        return false;

    String_Functions::trim(sip_msg);
    if (!String_Functions::match(sip_msg, " \t", result))
        return false;

    if (!set_cseq(result))
        return false;

    String_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _method = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_RAck::encode(std::string &sip_msg)
{
    if ((_rseq == INVALID_RSEQ) || (_cseq == INVALID_CSEQ) || (_method.empty()))
        return false;

    sip_msg += std::to_string(_rseq);
    sip_msg += " ";
    sip_msg += std::to_string(_cseq);
    sip_msg += " ";
    sip_msg += _method;
    return true;
}

//-------------------------------------------

bool SIP_Header_RAck::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "RSeq")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_rseq(query_type._remaining))
            {
                _logger.warning("Failed to query: set rseq failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string rseq;
            if (!get_rseq(rseq))
            {
                _logger.warning("Failed to query: get rseq failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = rseq;
            return true;
        }
    }else if (query_type._command == "CSeq")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_cseq(query_type._remaining))
            {
                _logger.warning("Failed to query: set cseq failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string cseq;
            if (!get_cseq(cseq))
            {
                _logger.warning("Failed to query: get cseq failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = cseq;
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
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

bool SIP_Header_RAck::set_rseq(std::string rseq)
{
    _rseq = String_Functions::str_to_ul(rseq);
    if (_rseq == INVALID_RSEQ)
    {
        _logger.warning("Failed to set rseq: str to ul failed (rseq=%s)", rseq.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_RAck::get_rseq(std::string &rseq)
{
    if (_rseq == INVALID_RSEQ)
    {
        _logger.warning("Failed to get rseq: invalid rseq");
        return false;
    }

    rseq = std::to_string(_rseq);
    return true;
}

//-------------------------------------------

bool SIP_Header_RAck::set_cseq(std::string cseq)
{
    _cseq = String_Functions::str_to_ul(cseq);
    if (_cseq == INVALID_CSEQ)
    {
        _logger.warning("Failed to set cseq: str to ul failed (cseq=%s)", cseq.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_RAck::get_cseq(std::string &cseq)
{
    if (_cseq == INVALID_CSEQ)
    {
        _logger.warning("Failed to get cseq: invalid cseq");
        return false;
    }

    cseq = std::to_string(_cseq);
    return true;
}

//-------------------------------------------

void SIP_Header_RAck::set_method(SIP_Method_Type method)
{
    _method = SIP_Functions::get_method_type(method);
}

//-------------------------------------------

SIP_Method_Type SIP_Header_RAck::get_method_enum()
{
    return SIP_Functions::get_method_type(_method);
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Record_Route::decode(std::string &sip_msg)
{
    std::string result;
    bool matched = String_Functions::match(sip_msg, ";", result);

    if (!_address.decode(result))
        return false;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);
        _parameters.add_parameter(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Record_Route::encode(std::string &sip_msg)
{
    if (!_address.encode(sip_msg))
        return false;

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Record_Route::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Address")
    {
        return _address.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Refer_To::decode(std::string &sip_msg)
{
    std::string result;
    bool matched = String_Functions::match(sip_msg, ";", result);

    if (!_address.decode(result))
        return false;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);
        _parameters.add_parameter(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Refer_To::encode(std::string &sip_msg)
{
    if (!_address.encode(sip_msg))
        return false;

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Refer_To::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Address")
    {
        return _address.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Referred_By::decode(std::string &sip_msg)
{
    std::string result;
    bool matched = String_Functions::match(sip_msg, ";", result);

    if (!_address.decode(result))
        return false;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);

        if (String_Functions::start_with(result, "cid="))
        {
            _cid = result.substr(4);
            String_Functions::trim(_cid);
            if (_cid.empty())
                return false;

        }else
            _parameters.add_parameter(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Referred_By::encode(std::string &sip_msg)
{
    if (!_address.encode(sip_msg))
        return false;

    if (!_cid.empty())
    {
        sip_msg += ";cid=";
        sip_msg += _cid;
    }

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Referred_By::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Address")
    {
        return _address.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "CID")
    {
        if (cmd == QUERY_SET)
        {
            set_cid(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_cid();
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Reply_To::decode(std::string &sip_msg)
{
    std::string result;
    bool matched = String_Functions::match(sip_msg, ";", result);

    if (!_address.decode(result))
        return false;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);
        _parameters.add_parameter(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Reply_To::encode(std::string &sip_msg)
{
    if (!_address.encode(sip_msg))
        return false;

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Reply_To::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Address")
    {
        return _address.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Require::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);
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

bool SIP_Header_Require::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Option-Tag")
    {
        if (cmd == QUERY_SET)
        {
            set_option_tag(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_option_tag();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Retry_After::decode(std::string &sip_msg)
{
    std::string result;
    std::string retry;

    bool has_param = String_Functions::match(sip_msg, ";", result);

    bool has_comment = String_Functions::match(result, "(", retry);
    String_Functions::trim(retry);
    if (retry.empty())
        return false;

    if (!set_retry_after(retry))
        return false;

    if (has_comment)
    {
        if (result.empty())
            return false;

        if (result.back() != ')')
            return false;

        result.pop_back();
        if (result.empty())
            return false;

        _comment = result;
    }

    while (has_param)
    {
        has_param = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);

        if (String_Functions::start_with(result, "duration="))
        {
            std::string duration = result.substr(9);
            String_Functions::trim(duration);
            if (duration.empty())
                return false;

            if (!set_duration(duration))
                return false;
        }else
            _parameters.add_parameter(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Retry_After::encode(std::string &sip_msg)
{
    if (_retry_after == INVALID_RETRY_AFTER)
        return false;

    sip_msg += std::to_string(_retry_after);

    if (!_comment.empty())
    {
        sip_msg += " (";
        sip_msg += _comment;
        sip_msg += ")";
    }

    if (_duration != INVALID_DURATION)
    {
        sip_msg += ";duration=";
        sip_msg += std::to_string(_duration);
    }

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Retry_After::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Retry-After")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_retry_after(query_type._remaining))
            {
                _logger.warning("Failed to query: set retry after failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string retry_after;
            if (!get_retry_after(retry_after))
            {
                _logger.warning("Failed to query: get retry after failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = retry_after;
            return true;
        }
    }else if (query_type._command == "Comment")
    {
        if (cmd == QUERY_SET)
        {
            set_comment(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_comment();
            return true;
        }
    }else if (query_type._command == "Duration")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_duration(query_type._remaining))
            {
                _logger.warning("Failed to query: set duration failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string duration;
            if (!get_duration(duration))
            {
                _logger.warning("Failed to query: get duration failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = duration;
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

bool SIP_Header_Retry_After::set_retry_after(std::string retry_after)
{
    _retry_after = String_Functions::str_to_ul(retry_after);
    if (_retry_after == INVALID_RETRY_AFTER)
    {
        _logger.warning("Failed to set retry after: str to ul failed (retry_after=%s)", retry_after.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Retry_After::get_retry_after(std::string &retry_after)
{
    if (_retry_after == INVALID_RETRY_AFTER)
    {
        _logger.warning("Failed to get retry after: invalid retry after");
        return false;
    }

    retry_after = std::to_string(_retry_after);
    return true;
}

//-------------------------------------------

bool SIP_Header_Retry_After::set_duration(std::string duration)
{
    _duration = String_Functions::str_to_ul(duration);
    if (_duration == INVALID_DURATION)
    {
        _logger.warning("Failed to set duration: str to ul failed (duration=%s)", duration.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Retry_After::get_duration(std::string &duration)
{
    if (_duration == INVALID_DURATION)
    {
        _logger.warning("Failed to get duration: invalid duration");
        return false;
    }

    duration = std::to_string(_duration);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Route::decode(std::string &sip_msg)
{
    std::string result;
    bool matched = String_Functions::match(sip_msg, ";", result);

    if (!_address.decode(result))
        return false;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);
        _parameters.add_parameter(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Route::encode(std::string &sip_msg)
{
    if (!_address.encode(sip_msg))
        return false;

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Route::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Address")
    {
        return _address.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_RSeq::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);

    if (!set_rseq(sip_msg))
        return false;

    return true;
}

//-------------------------------------------

bool SIP_Header_RSeq::encode(std::string &sip_msg)
{
    if (_rseq == INVALID_RSEQ)
        return false;

    sip_msg += std::to_string(_rseq);
    return true;
}

//-------------------------------------------

bool SIP_Header_RSeq::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "RSeq")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_rseq(query_type._remaining))
            {
                _logger.warning("Failed to query: set rseq failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string rseq;
            if (!get_rseq(rseq))
            {
                _logger.warning("Failed to query: get rseq failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = rseq;
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

bool SIP_Header_RSeq::set_rseq(std::string rseq)
{
    _rseq = String_Functions::str_to_ul(rseq);
    if (_rseq == INVALID_RSEQ)
    {
        _logger.warning("Failed to set rseq: str to ul failed (rseq=%s)", rseq.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_RSeq::get_rseq(std::string &rseq)
{
    if (_rseq == INVALID_RSEQ)
    {
        _logger.warning("Failed to get rseq: invalid rseq");
        return false;
    }

    rseq = std::to_string(_rseq);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Server::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);
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

bool SIP_Header_Server::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Server")
    {
        if (cmd == QUERY_SET)
        {
            set_server(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_server();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Subject::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);

    // Subject header can be empty
    _subject = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Subject::encode(std::string &sip_msg)
{
    if (_subject.empty())
    {
        // Subject header can be empty
        return true;
    }

    sip_msg += _subject;
    return true;
}

//-------------------------------------------

bool SIP_Header_Subject::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Subject")
    {
        if (cmd == QUERY_SET)
        {
            set_subject(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_subject();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Subscription_State::decode(std::string &sip_msg)
{
    std::string result;

    bool matched = String_Functions::match(sip_msg, ";", result);
    String_Functions::trim(result);
    if (result.empty())
        return false;

    _state = result;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);

        if (String_Functions::start_with(result, "reason="))
        {
            _reason = result.substr(7);
            String_Functions::trim(_reason);
            if (_reason.empty())
                return false;

        }else if (String_Functions::start_with(result, "expires="))
        {
            std::string exp = result.substr(8);
            String_Functions::trim(exp);
            if (exp.empty())
                return false;

            if (!set_expires(exp))
                return false;

        }else if (String_Functions::start_with(result, "retry-after="))
        {
            std::string retry = result.substr(12);
            String_Functions::trim(retry);
            if (retry.empty())
                return false;

            if (!set_retry_after(retry))
                return false;
        }else
            _parameters.add_parameter(result);
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Subscription_State::encode(std::string &sip_msg)
{
    if (_state.empty())
        return false;

    sip_msg += _state;

    if (!_reason.empty())
    {
        sip_msg += ";reason=";
        sip_msg += _reason;
    }

    if (_expires != INVALID_EXPIRES)
    {
        sip_msg += ";expires=";
        sip_msg += std::to_string(_expires);
    }

    if (_retry_after != INVALID_RETRY_AFTER)
    {
        sip_msg += ";retry-after=";
        sip_msg += std::to_string(_retry_after);
    }

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Subscription_State::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "State")
    {
        if (cmd == QUERY_SET)
        {
            set_state(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_state();
            return true;
        }
    }else if (query_type._command == "Reason")
    {
        if (cmd == QUERY_SET)
        {
            set_reason(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_reason();
            return true;
        }
    }else if (query_type._command == "Expires")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_expires(query_type._remaining))
            {
                _logger.warning("Failed to query: set expires failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string expires;
            if (!get_expires(expires))
            {
                _logger.warning("Failed to query: get expires failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = expires;
            return true;
        }
    }else if (query_type._command == "Retry-After")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_retry_after(query_type._remaining))
            {
                _logger.warning("Failed to query: set retry after failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string retry_after;
            if (!get_retry_after(retry_after))
            {
                _logger.warning("Failed to query: get retry after failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = retry_after;
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

void SIP_Header_Subscription_State::set_state(SIP_Header_Subscription_State::State state)
{
    switch (state)
    {
        case STATE_ACTIVE:     _state = "active";      break;
        case STATE_PENDING:    _state = "pending";     break;
        case STATE_TERMINATED: _state = "terminated";  break;
        default:                                       break;
    }
}

//-------------------------------------------

SIP_Header_Subscription_State::State SIP_Header_Subscription_State::get_state_enum()
{
    if (_state == "active")
        return STATE_ACTIVE;
    else if (_state == "pending")
        return STATE_PENDING;
    else if (_state == "terminated")
        return STATE_TERMINATED;

    return STATE_INVALID;
}

//-------------------------------------------

void SIP_Header_Subscription_State::set_reason(SIP_Header_Subscription_State::Reason reason)
{
    switch (reason)
    {
        case REASON_DEACTIVATED: _state = "deactivated"; break;
        case REASON_PROBATION:   _state = "probation";   break;
        case REASON_REJECTED:    _state = "rejected";    break;
        case REASON_TIMEOUT:     _state = "timeout";     break;
        case REASON_GIVEUP:      _state = "giveup";      break;
        case REASON_NORESOURCE:  _state = "noresource";  break;
        case REASON_INVARIANT:   _state = "invariant";   break;
        default:                                         break;
    }
}

//-------------------------------------------

SIP_Header_Subscription_State::Reason SIP_Header_Subscription_State::get_reason_enum()
{
    if (_reason == "deactivated")
        return REASON_DEACTIVATED;
    else if (_reason == "probation")
        return REASON_PROBATION;
    else if (_reason == "rejected")
        return REASON_REJECTED;
    else if (_reason == "timeout")
        return REASON_TIMEOUT;
    else if (_reason == "giveup")
        return REASON_GIVEUP;
    else if (_reason == "noresource")
        return REASON_NORESOURCE;
    else if (_reason == "invariant")
        return REASON_INVARIANT;

    return REASON_INVALID;
}

//-------------------------------------------

bool SIP_Header_Subscription_State::set_expires(std::string expires)
{
    _expires = String_Functions::str_to_ul(expires);
    if (_expires == INVALID_EXPIRES)
    {
        _logger.warning("Failed to set expires: str to ul failed (expires=%s)", expires.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Subscription_State::get_expires(std::string &expires)
{
    if (_expires == INVALID_EXPIRES)
    {
        _logger.warning("Failed to get expires: invalid expires");
        return false;
    }

    expires = std::to_string(_expires);
    return true;
}

//-------------------------------------------

bool SIP_Header_Subscription_State::set_retry_after(std::string retry_after)
{
    _retry_after = String_Functions::str_to_ul(retry_after);
    if (_retry_after == INVALID_RETRY_AFTER)
    {
        _logger.warning("Failed to set retry after: str to ul failed (retry_after=%s)", retry_after.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Subscription_State::get_retry_after(std::string &retry_after)
{
    if (_retry_after == INVALID_RETRY_AFTER)
    {
        _logger.warning("Failed to get retry after: invalid retry after");
        return false;
    }

    retry_after = std::to_string(_retry_after);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Supported::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);

    // Supported header can be empty
    _option_tag = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Supported::encode(std::string &sip_msg)
{
    if (_option_tag.empty())
    {
        // Supported header can be empty
        return true;
    }

    sip_msg += _option_tag;
    return true;
}

//-------------------------------------------

bool SIP_Header_Supported::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Option-Tag")
    {
        if (cmd == QUERY_SET)
        {
            set_option_tag(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_option_tag();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Timestamp::decode(std::string &sip_msg)
{
    std::string result;

    String_Functions::trim(sip_msg);

    bool matched = String_Functions::match(sip_msg, " \t", result);
    String_Functions::trim(result);
    if (result.empty())
        return false;

    _timestamp = result;

    if (matched)
    {
        String_Functions::trim(sip_msg);
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

bool SIP_Header_Timestamp::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Timestamp")
    {
        if (cmd == QUERY_SET)
        {
            set_timestamp(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_timestamp();
            return true;
        }
    }else if (query_type._command == "Delay")
    {
        if (cmd == QUERY_SET)
        {
            set_delay(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_delay();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_To::decode(std::string &sip_msg)
{
    std::string result;
    bool matched = String_Functions::match(sip_msg, ";", result);

    if (!_address.decode(result))
        return false;

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);

        if (String_Functions::start_with(result, "tag="))
        {
            _tag = result.substr(4);
            String_Functions::trim(_tag);
            if (_tag.empty())
                return false;
        }else
            _parameters.add_parameter(result);
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

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_To::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Address")
    {
        return _address.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "Tag")
    {
        if (cmd == QUERY_SET)
        {
            set_tag(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_tag();
            return true;
        }
    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

void SIP_Header_To::set_random_tag()
{
    _tag = String_Functions::random(20);
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Unknown::decode(std::string &sip_msg)
{
    std::string result;

    if (!String_Functions::match(sip_msg, ":", result))
        return false;

    String_Functions::trim(result);
    if (result.empty())
        return false;

    _header = result;

    String_Functions::trim(sip_msg);
    if (sip_msg.empty())
        return false;

    _value = sip_msg;
    return true;
}

//-------------------------------------------

bool SIP_Header_Unknown::encode(std::string &sip_msg)
{
    if ((_header.empty()) || (_value.empty()))
        return false;

    sip_msg += _header;
    sip_msg += ": ";
    sip_msg += _value;
    return true;
}

//-------------------------------------------

bool SIP_Header_Unknown::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Header")
    {
        if (cmd == QUERY_SET)
        {
            set_header(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_header();
            return true;
        }
    }else if (query_type._command == "Value")
    {
        if (cmd == QUERY_SET)
        {
            set_value(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_value();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_Unsupported::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);
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

bool SIP_Header_Unsupported::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Option-Tag")
    {
        if (cmd == QUERY_SET)
        {
            set_option_tag(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_option_tag();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_User_Agent::decode(std::string &sip_msg)
{
    String_Functions::trim(sip_msg);
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

bool SIP_Header_User_Agent::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "User-Agent")
    {
        if (cmd == QUERY_SET)
        {
            set_user_agent(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_user_agent();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
//-------------------------------------------

const std::string SIP_Header_Via::PROTOCOL_NAME_SIP = "SIP";
const std::string SIP_Header_Via::PROTOCOL_VERSION_2_0 = "2.0";

//-------------------------------------------

bool SIP_Header_Via::decode(std::string &sip_msg)
{
    std::string result;
    bool matched;

    matched = String_Functions::match(sip_msg, "/", result);
    if (!matched)
        return false;
    String_Functions::trim(result);
    _protocol_name = result;
    if (_protocol_name.empty())
        return false;

    matched = String_Functions::match(sip_msg, "/", result);
    if (!matched)
        return false;
    String_Functions::trim(result);
    _protocol_version = result;
    if (_protocol_version.empty())
        return false;

    String_Functions::skip(sip_msg, " \t");
    matched = String_Functions::match(sip_msg, " \t", result);
    if (!matched)
        return false;
    String_Functions::trim(result);
    _transport = result;
    if (_transport.empty())
        return false;

    matched = String_Functions::match(sip_msg, ":", result);
    if (matched)
    {
        String_Functions::trim(result);
        if (result.empty())
            return false;

        if (!_host.decode(result))
            return false;

        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);

        if (!set_port(result))
            return false;
    }else
    {
        matched = String_Functions::match(sip_msg, ";", result);

        String_Functions::trim(result);
        if (result.empty())
            return false;

        if (!_host.decode(result))
            return false;

        _port = INVALID_PORT;
    }

    while (matched)
    {
        matched = String_Functions::match(sip_msg, ";", result);
        String_Functions::trim(result);

        if (String_Functions::start_with(result, "branch="))
        {
            _branch = result.substr(7);
            String_Functions::trim(_branch);
            if (_branch.empty())
                return false;

        }else if (String_Functions::start_with(result, "received="))
        {
            _received = result.substr(9);
            String_Functions::trim(_received);
            if (_received.empty())
                return false;

        }else if (String_Functions::start_with(result, "ttl="))
        {
            std::string ttl = result.substr(4);
            String_Functions::trim(ttl);
            if (ttl.empty())
                return false;

            if (!set_ttl(ttl))
                return false;

        }else if (String_Functions::start_with(result, "maddr="))
        {
            std::string maddr = result.substr(6);
            String_Functions::trim(maddr);
            if (maddr.empty())
                return false;

            if (!_maddr.decode(maddr))
                return false;
        }else
        {
            if (!_parameters.add_parameter(result))
                return false;
        }
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Via::encode(std::string &sip_msg)
{
    if ((_protocol_name.empty()) || (_protocol_version.empty()) || (_transport.empty()))
        return false;

    sip_msg += _protocol_name;
    sip_msg += "/";
    sip_msg += _protocol_version;
    sip_msg += "/";
    sip_msg += _transport;
    sip_msg += " ";

    if (!_host.encode(sip_msg))
        return false;

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

    std::list<std::string> &parameters = _parameters.get_parameters();
    std::list<std::string>::const_iterator it = parameters.begin();
    while (it != parameters.end())
    {
        sip_msg += ";";
        sip_msg += *it++;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Via::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Protocol-Name")
    {
        if (cmd == QUERY_SET)
        {
            set_protocol_name(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_protocol_name();
            return true;
        }
    }else if (query_type._command == "Protocol-Version")
    {
        if (cmd == QUERY_SET)
        {
            set_protocol_version(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_protocol_version();
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
    }else if (query_type._command == "Branch")
    {
        if (cmd == QUERY_SET)
        {
            set_branch(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_branch();
            return true;
        }
    }else if (query_type._command == "Received")
    {
        if (cmd == QUERY_SET)
        {
            set_received(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_received();
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

    }else if (query_type._command == "Parameters")
    {
        return _parameters.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

void SIP_Header_Via::set_transport(SIP_Transport_Type transport)
{
    _transport = SIP_Functions::get_transport_type(transport);
}

//-------------------------------------------

SIP_Transport_Type SIP_Header_Via::get_transport_enum()
{
    return SIP_Functions::get_transport_type(_transport);
}

//-------------------------------------------

bool SIP_Header_Via::set_port(std::string port)
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

bool SIP_Header_Via::get_port(std::string &port)
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

void SIP_Header_Via::set_random_branch()
{
    _branch = "z9hG4bK" + String_Functions::random(20);
}

//-------------------------------------------

bool SIP_Header_Via::set_ttl(std::string ttl)
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

bool SIP_Header_Via::get_ttl(std::string &ttl)
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

bool SIP_Header_Warning::decode(std::string &sip_msg)
{
    std::string result;

    String_Functions::trim(sip_msg);
    if (!String_Functions::match(sip_msg, " ", result))
        return false;

    String_Functions::trim(result);
    if (result.empty())
        return false;

    if (!set_code(result))
        return false;

    String_Functions::trim(sip_msg);
    if (!String_Functions::match(sip_msg, " ", result))
        return false;

    String_Functions::trim(result);
    if (result.empty())
        return false;

    _agent = result;

    String_Functions::trim(sip_msg);
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

    sip_msg += String_Functions::add_leading_zeros(_code, 3);
    sip_msg += " ";
    sip_msg += _agent;
    sip_msg += " ";
    sip_msg += _text;
    return true;
}

//-------------------------------------------

bool SIP_Header_Warning::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Code")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_code(query_type._remaining))
            {
                _logger.warning("Failed to query: set code failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string code;
            if (!get_code(code))
            {
                _logger.warning("Failed to query: get code failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = code;
            return true;
        }
    }else if (query_type._command == "Agent")
    {
        if (cmd == QUERY_SET)
        {
            set_agent(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_agent();
            return true;
        }
    }else if (query_type._command == "Text")
    {
        if (cmd == QUERY_SET)
        {
            set_text(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_text();
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

bool SIP_Header_Warning::set_code(std::string code)
{
    _code = String_Functions::str_to_us(code);
    if (_code == INVALID_CODE)
    {
        _logger.warning("Failed to set code: str to us failed (code=%s)", code.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Header_Warning::get_code(std::string &code)
{
    if (_code == INVALID_CODE)
    {
        _logger.warning("Failed to get code: invalid code");
        return false;
    }

    code = std::to_string(_code);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SIP_Header_WWW_Authenticate::decode(std::string &sip_msg)
{
    return _challenge.decode(sip_msg);
}

//-------------------------------------------

bool SIP_Header_WWW_Authenticate::encode(std::string &sip_msg)
{
    return _challenge.encode(sip_msg);
}

//-------------------------------------------

bool SIP_Header_WWW_Authenticate::query_header(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Challenge")
    {
        return _challenge.query(cmd, query_type._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------
