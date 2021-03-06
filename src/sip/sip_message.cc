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

#include "sip_message.h"
#include "sip_functions.h"
#include "util/string_functions.h"
#include "util/query.h"

Logger SIP_Message::_logger(Log_Manager::LOG_SIP_MESSAGE);

//-------------------------------------------

SIP_Message::SIP_Message(const SIP_Message &message)
{
    sip_header_map::const_iterator it1 = message._headers.begin();
    while (it1 != message._headers.end())
    {
        sip_header_list headers = it1->second;
        it1++;

        sip_header_list::const_iterator it2 = headers.begin();
        while (it2 != headers.end())
        {
            SIP_Header *header = *it2++;
            SIP_Header *new_header = SIP_Header::create_header(header->get_header_type(), header);
            add_header(new_header);
        }
    }

    sip_body_list::const_iterator it3 = message._bodies.begin();
    while (it3 != message._bodies.end())
    {
        SIP_Body *body = *it3++;
        SIP_Body *new_body = SIP_Body::create_body(body->get_body_type(), body);
        add_body(new_body);
    }
}

//-------------------------------------------

SIP_Message::~SIP_Message()
{
    clear_headers();
    clear_bodies();
}

//-------------------------------------------

SIP_Message *SIP_Message::decode_message(const char *msg, unsigned short size, unsigned short &read)
{
    char type[20] = {0};

    const char *ptr = strchr(msg, ' ');
    if ((!ptr) && (size < sizeof(type)))
    {
        _logger.trace("Message may not be complete: invalid method type");
        read = 0;
        return NULL;

    }else if ((!ptr) || (((std::size_t) (ptr - msg)) >= sizeof(type)))
    {
        _logger.warning("Failed to decode message: invalid method type");
        read = size;
        return NULL;
    }

    std::copy(msg, ptr, type);

    SIP_Method_Type method = SIP_Functions::get_method_type(type);
    if (method == SIP_METHOD_INVALID)
    {
        _logger.warning("Failed to decode message: invalid method (method=%s)", type);
        read = size;
        return NULL;
    }

    SIP_Message *message;
    if (method != SIP_RESPONSE)
        message = new SIP_Request(method);
    else
        message = new SIP_Response();

    if (!message->decode(msg, size, read))
    {
        delete message;
        return NULL;
    }

    return message;
}

//-------------------------------------------

bool SIP_Message::decode(const char *msg, unsigned short size, unsigned short &read)
{
    const char *ptr = strstr(msg, "\r\n\r\n");
    if (!ptr)
    {
        _logger.trace("SIP message is not complete: CRLF not found (size=%d)", size);
        read = 0;
        return false;
    }

    ptr += 4;

    unsigned short headers_size = (unsigned short) (ptr - msg);
    std::string headers;
    headers.assign(msg, headers_size);

    const char *body = ptr;
    unsigned short body_size = size - headers_size;

    String_Functions::remove_lws(headers);

    if (!decode_start_line(headers))
    {
        read = size;
        return false;
    }

    if (!decode_header(headers))
    {
        read = size;
        return false;
    }

    SIP_Header_Content_Length *header_content_length = dynamic_cast<SIP_Header_Content_Length *>(get_header(SIP_HEADER_CONTENT_LENGTH));
    if (header_content_length)
    {
        unsigned short length = (unsigned short) header_content_length->get_length();
        if (length > body_size)
        {
            _logger.trace("SIP body is not complete: Content-Length is bigger than message size (length=%d, size=%d)", length, size);
            read = 0;
            return false;
        }

        body_size = length;
    }

    if (!decode_body(body, body_size))
    {
        read = size;
        return false;
    }

    read = headers_size + body_size;
    return true;
}

//-------------------------------------------

bool SIP_Message::decode_header(std::string &msg)
{
    while (true)
    {
        std::string line;

        if (!String_Functions::get_line(msg, line))
        {
            _logger.warning("Failed to decode: get line failed (method=%d)", get_message_type());
            return false;
        }

        if (line.empty())
            break;

        sip_header_list headers;

        if (!SIP_Header::decode_headers(line, headers))
        {
            sip_header_list::const_iterator it = headers.begin();
            while (it != headers.end())
                delete *it++;

            headers.clear();
            return false;
        }

        add_headers(headers);
    }

    if ((!get_header(SIP_HEADER_CALL_ID)) || (!get_header(SIP_HEADER_CSEQ)) || (!get_header(SIP_HEADER_FROM)) ||
        (!get_header(SIP_HEADER_TO)) || (!get_header(SIP_HEADER_VIA)))
    {
        _logger.warning("Failed to decode: required headers not present (method=%d)", get_message_type());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Message::decode_body(const char *body, unsigned short size)
{
    if ((!body) || (size == 0))
        return true;

    SIP_Header_Content_Type *header_content_type = dynamic_cast<SIP_Header_Content_Type *>(get_header(SIP_HEADER_CONTENT_TYPE));
    if (header_content_type)
    {
        SIP_Body_Type type = SIP_BODY_UNKNOWN;

        if ((header_content_type->get_media_type().get_type_enum() == SIP_Media_Range::TYPE_APPLICATION) &&
            (header_content_type->get_media_type().get_subtype_enum() == SIP_Media_Range::SUBTYPE_APPLICATION_SDP))
            type = SIP_BODY_SDP;

        SIP_Body *sip_body = SIP_Body::create_body(type);
        if (!sip_body)
        {
            _logger.warning("Failed to decode body: create body failed (method=%d)", get_message_type());
            return false;
        }

        if (!sip_body->decode(body, size))
        {
            _logger.warning("Failed to decode body: decode failed (method=%d)", get_message_type());
            delete sip_body;
            return false;
        }

        add_body(sip_body);
    }

    return true;
}

//-------------------------------------------

bool SIP_Message::encode(char *msg, unsigned short &size)
{
    std::string headers;
    char *body = msg;
    unsigned short body_size = size;

    if (!encode_start_line(headers))
        return false;

    if (!encode_body(body, body_size))
        return false;

    SIP_Header_Content_Length *header_content_length = dynamic_cast<SIP_Header_Content_Length *>(get_header(SIP_HEADER_CONTENT_LENGTH));
    if (!header_content_length)
    {
        header_content_length = new SIP_Header_Content_Length();
        add_header(header_content_length);
    }

    header_content_length->set_length((unsigned long) body_size);

    if (!encode_header(headers))
        return false;

    headers += "\r\n";

    unsigned short total = (unsigned short) (headers.size() + body_size);
    if (total >= size)
    {
        _logger.warning("Failed to encode: buffer size too small (size=%, header=%d, body=%d)", size, headers.size(), body_size);
        return false;
    }

    if (body_size > 0)
        memmove(&msg[headers.size()], body, body_size);

    memcpy(msg, headers.c_str(), headers.size());

    size = total;
    msg[size] = 0;
    return true;
}

//-------------------------------------------

bool SIP_Message::encode_header(std::string &msg)
{
    sip_header_map::const_iterator it = _headers.begin();
    while (it != _headers.end())
    {
        sip_header_list headers = it->second;
        it++;

        if (!SIP_Header::encode_headers(msg, headers))
            return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Message::encode_body(char *body, unsigned short &size)
{
    if ((!body) || (size == 0))
    {
        _logger.warning("Failed to encode body: invalid parameters (method=%d)", get_message_type());
        return false;
    }

    unsigned short total = 0;

    sip_body_list::const_iterator it = _bodies.begin();
    while (it != _bodies.end())
    {
        SIP_Body *sip_body = *it++;
        unsigned short sz = size - total;

        if (!sip_body->encode(body, sz))
        {
            _logger.warning("Failed to encode body: encode failed (method=%d)", get_message_type());
            return false;
        }

        total += sz;
    }

    size = total;
    return true;
}

//-------------------------------------------

bool SIP_Message::query(QueryCommand cmd, const std::string &query, std::string &result)
{
    if (query.empty())
    {
        _logger.warning("Failed to query: invalid query (cmd=%d)", cmd);
        return false;
    }

    Query query_type(query);
    if (query_type._command == "Request-Line")
    {
        SIP_Request *request = dynamic_cast<SIP_Request *>(this);
        if (!request)
        {
            _logger.warning("Failed to query: message is not a request (cmd=%d, query=%s)", cmd, query.c_str());
            return false;
        }

        return request->query_start_line(cmd, query_type._remaining, result);

    }else if (query_type._command == "Status-Line")
    {
        SIP_Response *response = dynamic_cast<SIP_Response *>(this);
        if (!response)
        {
            _logger.warning("Failed to query: message is not a response (cmd=%d, query=%s)", cmd, query.c_str());
            return false;
        }

        return response->query_start_line(cmd, query_type._remaining, result);

    }else if (query_type._command == "Header")
    {
        Query query_header_name(query_type._remaining);
        std::string header_name = query_header_name._command;

        SIP_Header_Type header_type = SIP_Functions::get_header_type(header_name);
        if (header_type == SIP_HEADER_INVALID)
        {
            _logger.warning("Failed to query: invalid header type (cmd=%d, query=%s)", cmd, query.c_str());
            return false;
        }

        if (query_header_name._remaining == "Size")
        {
            if (cmd == QUERY_GET)
            {
                result = std::to_string(get_header_size(header_type));
                return true;
            }else
            {
                _logger.warning("Failed to query: invalid query command (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }
        }

        Query query_header_position(query_header_name._remaining);
        unsigned short pos = String_Functions::str_to_us(query_header_position._command);
        if (pos == INVALID_UNSIGNED_SHORT)
        {
            _logger.warning("Failed to query: invalid header position (cmd=%d, query=%s)", cmd, query.c_str());
            return false;
        }

        if (query_header_position._remaining.empty())
        {
            if (cmd == QUERY_ADD)
            {
                SIP_Header *header = SIP_Header::create_header(header_type);
                if (!header)
                {
                    _logger.warning("Failed to query: create header failed (cmd=%d, query=%s)", cmd, query.c_str());
                    return false;
                }

                if (!add_header(header, pos))
                {
                    _logger.warning("Failed to query: add header failed (cmd=%d, query=%s)", cmd, query.c_str());
                    delete header;
                    return false;
                }

                return true;

            }else if (cmd == QUERY_DEL)
            {
                if (!remove_header(header_type, pos))
                {
                    _logger.warning("Failed to query: remove header failed (cmd=%d, query=%s)", cmd, query.c_str());
                    return false;
                }

                return true;
            }else
            {
                _logger.warning("Failed to query: invalid query command (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }
        }

        SIP_Header *header = get_header(header_type, pos);
        if (!header)
        {
            _logger.warning("Failed to query: invalid header (cmd=%d, query=%s)", cmd, query.c_str());
            return false;
        }

        return header->query(cmd, query_header_position._remaining, result);

    }else if (query_type._command == "Body")
    {
        if (query_type._remaining == "Size")
        {
            if (cmd == QUERY_GET)
            {
                result = std::to_string(get_body_size());
                return true;
            }else
            {
                _logger.warning("Failed to query: invalid query command (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }
        }

        Query query_body_position(query_type._remaining);
        unsigned short pos = String_Functions::str_to_us(query_body_position._command);
        if (pos == INVALID_UNSIGNED_SHORT)
        {
            _logger.warning("Failed to query: invalid body position (cmd=%d, query=%s)", cmd, query.c_str());
            return false;
        }

        Query query_body_name(query_body_position._remaining);
        std::string body_name = query_body_name._command;

        SIP_Body_Type body_type;

        if (body_name == "SDP")
            body_type = SIP_BODY_SDP;
        else
            body_type = SIP_BODY_UNKNOWN;

        if (query_body_name._remaining.empty())
        {
            if (cmd == QUERY_ADD)
            {
                SIP_Body *body = SIP_Body::create_body(body_type);
                if (!body)
                {
                    _logger.warning("Failed to query: create body failed (cmd=%d, query=%s)", cmd, query.c_str());
                    return false;
                }

                if (!add_body(body, pos))
                {
                    _logger.warning("Failed to query: add body failed (cmd=%d, query=%s)", cmd, query.c_str());
                    delete body;
                    return false;
                }

                return true;

            }else if (cmd == QUERY_DEL)
            {
                if (!remove_body(pos))
                {
                    _logger.warning("Failed to query: remove body failed (cmd=%d, query=%s)", cmd, query.c_str());
                    return false;
                }

                return true;
            }else
            {
                _logger.warning("Failed to query: invalid query command (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }
        }

        SIP_Body *body = get_body(pos);
        if (!body)
        {
            _logger.warning("Failed to query: invalid body (cmd=%d, query=%s)", cmd, query.c_str());
            return false;
        }

        return body->query(cmd, query_body_name._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

bool SIP_Message::add_header(SIP_Header *header, unsigned short pos)
{
    if (!header)
    {
        _logger.warning("Failed to add header: invalid header");
        return false;
    }

    SIP_Header_Type header_type = header->get_header_type();

    if (_headers.count(header_type) > 0)
    {
        unsigned short count = 0;

        sip_header_list &headers = _headers.at(header_type);
        sip_header_list::iterator it = headers.begin();
        while (it != headers.end())
        {
            if (count++ == pos)
                break;

            it++;
        }

        headers.insert(it, header);
    }else
    {
        sip_header_list headers;
        headers.push_back(header);
        _headers[header_type] = headers;
    }

    return true;
}

//-------------------------------------------

bool SIP_Message::add_headers(sip_header_list &headers)
{
    if (headers.empty())
    {
        _logger.warning("Failed to add headers: invalid headers");
        return false;
    }

    sip_header_list::const_iterator it = headers.begin();
    while (it != headers.end())
    {
        SIP_Header *header = *it++;
        add_header(header);
    }

    return true;
}

//-------------------------------------------

bool SIP_Message::remove_header(SIP_Header_Type header_type, unsigned short pos)
{
    if (_headers.count(header_type) == 0)
    {
        _logger.warning("Failed to remove header: invalid header type (type=%d)", header_type);
        return false;
    }

    unsigned short count = 0;

    sip_header_list &headers = _headers.at(header_type);
    sip_header_list::iterator it = headers.begin();
    while (it != headers.end())
    {
        if (count++ == pos)
        {
            headers.erase(it);
            return true;
        }

        it++;
    }

    _logger.warning("Failed to remove header: invalid position (type=%d, pos=%d, count=%d)", header_type, pos, count);
    return false;
}

//-------------------------------------------

void SIP_Message::clear_headers()
{
    sip_header_map::const_iterator it1 = _headers.begin();
    while (it1 != _headers.end())
    {
        const sip_header_list &headers = it1->second;
        it1++;

        sip_header_list::const_iterator it2 = headers.begin();
        while (it2 != headers.end())
        {
            SIP_Header *header = *it2++;
            delete header;
        }
    }

    _headers.clear();
}

//-------------------------------------------

SIP_Header *SIP_Message::get_header(SIP_Header_Type header_type, unsigned short pos)
{
    if (_headers.count(header_type) == 0)
    {
        //_logger.warning("Failed to get header: invalid header type (type=%d)", header_type);
        return NULL;
    }

    unsigned short count = 0;

    sip_header_list &headers = _headers.at(header_type);
    sip_header_list::const_iterator it = headers.begin();
    while (it != headers.end())
    {
        if (count++ == pos)
            return *it;

        it++;
    }

    _logger.warning("Failed to get header: invalid position (type=%d, pos=%d, count=%d)", header_type, pos, count);
    return NULL;
}

//-------------------------------------------

unsigned short SIP_Message::get_header_size(SIP_Header_Type header_type)
{
    if (_headers.count(header_type) == 0)
        return 0;

    sip_header_list &headers = _headers.at(header_type);
    return (unsigned short) headers.size();
}

//-------------------------------------------

bool SIP_Message::add_body(SIP_Body *body, unsigned short pos)
{
    if (!body)
    {
        _logger.warning("Failed to add body: invalid body");
        return false;
    }

    unsigned short count = 0;

    sip_body_list::iterator it = _bodies.begin();
    while (it != _bodies.end())
    {
        if (count++ == pos)
            break;

        it++;
    }

    _bodies.insert(it, body);
    return true;
}

//-------------------------------------------

bool SIP_Message::remove_body(unsigned short pos)
{
    unsigned short count = 0;

    sip_body_list::iterator it = _bodies.begin();
    while (it != _bodies.end())
    {
        if (count++ == pos)
        {
            _bodies.erase(it);
            return true;
        }

        it++;
    }

    _logger.warning("Failed to remove body: invalid position (pos=%d, count=%d)", pos, count);
    return false;
}

//-------------------------------------------

void SIP_Message::clear_bodies()
{
    sip_body_list::const_iterator it = _bodies.begin();
    while (it != _bodies.end())
    {
        SIP_Body *body = *it++;
        delete body;
    }

    _bodies.clear();
}

//-------------------------------------------

SIP_Body *SIP_Message::get_body(unsigned short pos)
{
    unsigned short count = 0;

    sip_body_list::const_iterator it = _bodies.begin();
    while (it != _bodies.end())
    {
        if (count++ == pos)
            return *it;

        it++;
    }

    _logger.warning("Failed to get body: invalid position (pos=%d, count=%d)", pos, count);
    return NULL;
}

//-------------------------------------------
//-------------------------------------------

SIP_Request::SIP_Request(SIP_Method_Type method)
{
    set_method(method);
    _request_uri.set_display_name_double_quote(false);
    _request_uri.set_uri_angle_quote(false);
    _sip_version = SIP_VERSION;
}

//-------------------------------------------

SIP_Request::SIP_Request(const SIP_Request &request) : SIP_Message(request)
{
    _method = request._method;
    _request_uri = request._request_uri;
    _sip_version = request._sip_version;
}

//-------------------------------------------

bool SIP_Request::decode_start_line(std::string &msg)
{
    std::string line;
    String_Functions::get_line(msg, line);
    String_Functions::trim(line);

    std::string result;
    if (!String_Functions::match(line, " ", result))
    {
        _logger.warning("Failed to decode start line: invalid method (method=%s)", line.c_str());
        return false;
    }

    // The method was already decoded by SIP_Message::decode_message

    String_Functions::skip(line, " \t");
    if (!String_Functions::match(line, " ", result))
    {
        _logger.warning("Failed to decode start line: invalid request URI (request_uri=%s)", line.c_str());
        return false;
    }

    if (!_request_uri.decode(result))
        return false;

    String_Functions::skip(line, " \t");
    _sip_version = line;
    if ((_sip_version.empty()) || (_sip_version != SIP_VERSION))
    {
        _logger.warning("Failed to decode start line: invalid SIP version (version=%s)", _sip_version.c_str());
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Request::encode_start_line(std::string &msg)
{
    if ((_method.empty()) || (_sip_version.empty()))
        return false;

    msg += _method;
    msg += " ";

    if (!_request_uri.encode(msg))
        return false;

    msg += " ";
    msg += _sip_version;
    msg += "\r\n";
    return true;
}

//-------------------------------------------

bool SIP_Request::query_start_line(QueryCommand cmd, const std::string &query, std::string &result)
{
    if (query.empty())
    {
        _logger.warning("Failed to query start line: invalid query (cmd=%d)", cmd);
        return false;
    }

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
    }else if (query_type._command == "Request-URI")
    {
        return _request_uri.query(cmd, query_type._remaining, result);

    }else if (query_type._command == "SIP-Version")
    {
        if (cmd == QUERY_SET)
        {
            set_sip_version(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_sip_version();
            return true;
        }
    }

    _logger.warning("Failed to query start line: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

void SIP_Request::set_request_line(SIP_Method_Type method, const SIP_Address &request_uri, std::string sip_version)
{
    set_method(method);
    set_request_uri(request_uri);
    _sip_version = sip_version;
}

//-------------------------------------------

void SIP_Request::set_method(SIP_Method_Type method)
{
    _method = SIP_Functions::get_method_type(method);
}

//-------------------------------------------

SIP_Method_Type SIP_Request::get_method_enum()
{
    return SIP_Functions::get_method_type(_method);
}

//-------------------------------------------

void SIP_Request::set_request_uri(const SIP_Address &request_uri)
{
    _request_uri = request_uri;
    _request_uri.set_display_name_double_quote(false);
    _request_uri.set_display_name("");
    _request_uri.set_uri_angle_quote(false);
}

//-------------------------------------------
//-------------------------------------------

SIP_Response::SIP_Response(const SIP_Response &response) : SIP_Message(response)
{
    _sip_version = response._sip_version;
    _status_code = response._status_code;
    _reason_phrase = response._reason_phrase;
}

//-------------------------------------------

SIP_Response::SIP_Response(unsigned short status_code) : _status_code(INVALID_STATUS_CODE)
{
    unsigned short i = 0;
    while (_status_codes[i]._code != INVALID_STATUS_CODE)
    {
        if (_status_codes[i]._code == status_code)
        {
            set_status_line(SIP_VERSION, status_code, _status_codes[i]._reason_phrase);
            return;
        }
        i++;
    }
}

//-------------------------------------------

SIP_Response::SIP_Response(unsigned short status_code, SIP_Request &request) : SIP_Response(status_code)
{
    SIP_Header_Call_ID *header_call_id = dynamic_cast<SIP_Header_Call_ID *>(request.get_header(SIP_HEADER_CALL_ID));
    if (header_call_id)
        add_header(new SIP_Header_Call_ID(*header_call_id));

    SIP_Header_CSeq *header_cseq = dynamic_cast<SIP_Header_CSeq *>(request.get_header(SIP_HEADER_CSEQ));
    if (header_cseq)
        add_header(new SIP_Header_CSeq(*header_cseq));

    SIP_Header_From *header_from = dynamic_cast<SIP_Header_From *>(request.get_header(SIP_HEADER_FROM));
    if (header_from)
        add_header(new SIP_Header_From(*header_from));

    SIP_Header_To *header_to = dynamic_cast<SIP_Header_To *>(request.get_header(SIP_HEADER_TO));
    if (header_to)
        add_header(new SIP_Header_To(*header_to));

    unsigned short via_size = request.get_header_size(SIP_HEADER_VIA);
    for (unsigned short i = 0; i < via_size; i++)
    {
        SIP_Header_Via *header_via = dynamic_cast<SIP_Header_Via *>(request.get_header(SIP_HEADER_VIA, i));
        if (header_via)
            add_header(new SIP_Header_Via(*header_via));
    }
}

//-------------------------------------------

bool SIP_Response::decode_start_line(std::string &msg)
{
    std::string line;
    String_Functions::get_line(msg, line);
    String_Functions::trim(line);

    std::string result;
    if (!String_Functions::match(line, " ", result))
    {
        _logger.warning("Failed to decode start line: invalid SIP version (version=%s)", line.c_str());
        return false;
    }

    _sip_version = SIP_VERSION; // The version was already decoded by SIP_Message::decode_message

    String_Functions::skip(line, " \t");
    if (!String_Functions::match(line, " ", result))
    {
        _logger.warning("Failed to decode start line: invalid status code (status_code=%s)", line.c_str());
        return false;
    }

    if (!set_status_code(result))
    {
        _logger.warning("Failed to decode start line: set status code failed (status_code=%s)", result.c_str());
        return false;
    }

    String_Functions::skip(line, " \t");
    _reason_phrase = line; //It can be empty!
    return true;
}

//-------------------------------------------

bool SIP_Response::encode_start_line(std::string &msg)
{
    if ((_sip_version.empty()) || (_status_code < 100) || (_status_code > 699))
        return false;

    msg += _sip_version;
    msg += " ";
    msg += std::to_string(_status_code);
    msg += " ";
    msg += _reason_phrase;
    msg += "\r\n";
    return true;
}

//-------------------------------------------

bool SIP_Response::query_start_line(QueryCommand cmd, const std::string &query, std::string &result)
{
    if (query.empty())
    {
        _logger.warning("Failed to query start line: invalid query (cmd=%d)", cmd);
        return false;
    }

    Query query_type(query);
    if (query_type._command == "SIP-Version")
    {
        if (cmd == QUERY_SET)
        {
            set_sip_version(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_sip_version();
            return true;
        }
    }else if (query_type._command == "Status-Code")
    {
        if (cmd == QUERY_SET)
        {
            if (!set_status_code(query_type._remaining))
            {
                _logger.warning("Failed to query start line: set status code failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string status_code;
            if (!get_status_code(status_code))
            {
                _logger.warning("Failed to query start line: get status code failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = status_code;
            return true;
        }
    }else if (query_type._command == "Reason-Phrase")
    {
        if (cmd == QUERY_SET)
        {
            set_reason_phrase(query_type._remaining);
            return true;

        }else if (cmd == QUERY_GET)
        {
            result = get_reason_phrase();
            return true;
        }
    }

    _logger.warning("Failed to query start line: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

void SIP_Response::set_status_line(std::string sip_version, unsigned short status_code, std::string reason_phrase)
{
    _sip_version = sip_version;
    _status_code = status_code;
    _reason_phrase = reason_phrase;
}

//-------------------------------------------

bool SIP_Response::set_status_code(std::string status_code)
{
    _status_code = String_Functions::str_to_us(status_code);
    if (_status_code == INVALID_STATUS_CODE)
    {
        _logger.warning("Failed to set status code: str to us failed (status_code=%s)", status_code.c_str());
        return false;
    }

    if ((_status_code < 100) || (_status_code > 699))
    {
        _logger.warning("Failed to set status code: invalid status code value (status_code=%d)", _status_code);
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Response::get_status_code(std::string &status_code)
{
    if (_status_code == INVALID_STATUS_CODE)
    {
        _logger.warning("Failed to get status code: invalid status code");
        return false;
    }

    status_code = std::to_string(_status_code);
    return true;
}

//-------------------------------------------

SIP_Response::SIP_Status_Code SIP_Response::_status_codes[] =
{
    //Informational
    { 100, "Trying" },
    { 180, "Ringing" },
    { 181, "Call is Being Forwarded" },
    { 182, "Queued" },
    { 183, "Session Progress" },

    //Success
    { 200, "OK" },
    { 202, "Accepted" },

    //Redirection
    { 300, "Multiple Choices" },
    { 301, "Moved Permanently" },
    { 302, "Moved Temporarily" },
    //{ 303, "See Other" },
    { 305, "Use Proxy" },
    { 380, "Alternative Service" },

    //Client-Error
    { 400, "Bad Request" },
    { 401, "Unauthorized" },
    { 402, "Payment Required" },
    { 403, "Forbidden" },
    { 404, "Not Found" },
    { 405, "Method Not Allowed" },
    { 406, "Not Acceptable" },
    { 407, "Proxy Authentication Required" },
    { 408, "Request Timeout" },
    { 409, "Conflict" },
    { 410, "Gone" },
    //{ 411, "Length Required" },
    { 413, "Request Entity Too Large" },
    { 414, "Request-URI Too Large" },
    { 415, "Unsupported Media Type" },
    { 420, "Bad Extension" },
    { 480, "Temporarily Unavailable" },
    { 481, "Call Leg/Transaction Does Not Exist" },
    { 482, "Loop Detected" },
    { 483, "Too Many Hops" },
    { 484, "Address Incomplete" },
    { 485, "Ambiguous" },
    { 486, "Busy Here" },
    { 487, "Request Terminated" },
    { 488, "Not Acceptable Here" },
    { 489, "Bad Event" },

    //Server-Error
    { 500, "Server Internal Error" },
    { 501, "Not Implemented" },
    { 502, "Bad Gateway" },
    { 503, "Service Unavailable" },
    { 504, "Server Timed-out" },
    { 505, "Version Not Supported" },
    { 513, "Message Too Large" },

    //Global-Failure
    { 600, "Busy Everywhere" },
    { 603, "Decline" },
    { 604, "Does Not Exist Anywhere" },
    { 606, "Not Acceptable" },

    { INVALID_STATUS_CODE, "Unknown" },
};

//-------------------------------------------
