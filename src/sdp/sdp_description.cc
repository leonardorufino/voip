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

#include "sdp_description.h"
#include "sdp_functions.h"
#include "util/string_functions.h"
#include "util/query.h"

Logger SDP_Description::_logger(Log_Manager::LOG_SDP_DESCRIPTION);
Logger SDP_Description_Fields::_logger(Log_Manager::LOG_SDP_DESCRIPTION);

//-------------------------------------------

SDP_Description::SDP_Description(const SDP_Description &description)
{
    if (description._session)
        _session = new SDP_Description_Session(*description._session);
    else
        _session = NULL;

    std::list<SDP_Description_Media *>::const_iterator it = description._medias.begin();
    while (it != description._medias.end())
    {
        SDP_Description_Media *media = *it++;
        SDP_Description_Media *new_media = new SDP_Description_Media(*media);
        _medias.push_back(new_media);
    }
}

//-------------------------------------------

SDP_Description::~SDP_Description()
{
    clear_session();
    clear_medias();
}

//-------------------------------------------

bool SDP_Description::decode(const char *msg, unsigned short size)
{
    if ((!msg) || (size == 0))
    {
        _logger.warning("Failed to decode: invalid parameters");
        return false;
    }

    if ((_session) || (!_medias.empty()))
    {
        _logger.warning("Failed to decode: invalid session or medias");
        return false;
    }

    const char *p_msg = msg;
    unsigned short session_size;
    bool has_media;

    const char *ptr = strstr(p_msg, "\nm=");
    if (ptr)
    {
        session_size = (unsigned short) (++ptr - p_msg);
        has_media = true;
    }else
    {
        session_size = size;
        has_media = false;
    }

    std::string session_msg;
    session_msg.assign(p_msg, session_size);

    _session = new SDP_Description_Session();
    if (!_session->decode(session_msg))
    {
        _logger.warning("Failed to decode: session decode failed");
        return false;
    }

    p_msg += session_size;

    while (has_media)
    {
        unsigned short media_size;

        const char *ptr = strstr(p_msg + 2, "\nm=");
        if (ptr)
        {
            media_size = (unsigned short) (++ptr - p_msg);
            has_media = true;
        }else
        {
            media_size = (unsigned short) (size - (p_msg - msg));
            has_media = false;
        }

        std::string media_msg;
        media_msg.assign(p_msg, media_size);

        SDP_Description_Media *media = new SDP_Description_Media();
        if (!media->decode(media_msg))
        {
            _logger.warning("Failed to decode: media decode failed");
            delete media;
            return false;
        }

        add_media(media);

        p_msg += media_size;
    }

    return true;
}

//-------------------------------------------

bool SDP_Description::encode(char *msg, unsigned short &size)
{
    std::string sdp;

    if (!_session)
    {
        _logger.warning("Failed to encode: invalid session");
        return false;
    }

    if (!_session->encode(sdp))
        return false;

    std::list<SDP_Description_Media *>::const_iterator it = _medias.begin();
    while (it != _medias.end())
    {
        SDP_Description_Media *media = *it++;
        if (!media->encode(sdp))
            return false;
    }

    if (sdp.size() >= size)
    {
        _logger.warning("Failed to encode: buffer size too small (size=%, sdp=%d)", size, sdp.size());
        return false;
    }

    memcpy(msg, sdp.c_str(), sdp.size());
    size = (unsigned short) sdp.size();
    msg[size] = 0;
    return true;
}

//-------------------------------------------

bool SDP_Description::query_body(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_type(query);
    if (query_type._command == "Session")
    {
        if (query_type._remaining == "Size")
        {
            if (cmd == QUERY_GET)
            {
                result = _session ? "1" : "0";
                return true;
            }else
            {
                _logger.warning("Failed to query: invalid query command (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }
        }

        if (query_type._remaining.empty())
        {
            if (cmd == QUERY_ADD)
            {
                if (_session)
                {
                    _logger.warning("Failed to query: session already exist (cmd=%d, query=%s)", cmd, query.c_str());
                    return false;
                }

                _session = new SDP_Description_Session();
                return true;

            }else if (cmd == QUERY_DEL)
            {
                if (!_session)
                {
                    _logger.warning("Failed to query: invalid session (cmd=%d, query=%s)", cmd, query.c_str());
                    return false;
                }

                clear_session();
                return true;
            }else
            {
                _logger.warning("Failed to query: invalid query command (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }
        }

        if (!_session)
        {
            _logger.warning("Failed to query: invalid session (cmd=%d, query=%s)", cmd, query.c_str());
            return false;
        }

        return _session->query(cmd, query_type._remaining, result);

    }else if (query_type._command == "Media")
    {
        if (query_type._remaining == "Size")
        {
            if (cmd == QUERY_GET)
            {
                result = std::to_string(get_media_size());
                return true;
            }else
            {
                _logger.warning("Failed to query: invalid query command (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }
        }

        Query query_media_position(query_type._remaining);
        unsigned short pos = String_Functions::str_to_us(query_media_position._command);
        if (pos == INVALID_UNSIGNED_SHORT)
        {
            _logger.warning("Failed to query: invalid media position (cmd=%d, query=%s)", cmd, query.c_str());
            return false;
        }

        if (query_media_position._remaining.empty())
        {
            if (cmd == QUERY_ADD)
            {
                SDP_Description_Media *media = new SDP_Description_Media();
                if (!add_media(media, pos))
                {
                    _logger.warning("Failed to query: add media failed (cmd=%d, query=%s)", cmd, query.c_str());
                    delete media;
                    return false;
                }

                return true;

            }else if (cmd == QUERY_DEL)
            {
                if (!remove_media(pos))
                {
                    _logger.warning("Failed to query: remove media failed (cmd=%d, query=%s)", cmd, query.c_str());
                    return false;
                }

                return true;
            }else
            {
                _logger.warning("Failed to query: invalid query command (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }
        }

        SDP_Description_Media *media = get_media(pos);
        if (!media)
        {
            _logger.warning("Failed to query: invalid media (cmd=%d, query=%s)", cmd, query.c_str());
            return false;
        }

        return media->query(cmd, query_media_position._remaining, result);
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

void SDP_Description::set_session(SDP_Description_Session *session)
{
    if (_session)
        delete _session;

    _session = session;
}

//-------------------------------------------

void SDP_Description::clear_session()
{
    if (_session)
    {
        delete _session;
        _session = NULL;
    }
}

//-------------------------------------------

bool SDP_Description::add_media(SDP_Description_Media *media, unsigned short pos)
{
    if (!media)
    {
        _logger.warning("Failed to add media: invalid media");
        return false;
    }

    unsigned short count = 0;

    std::list<SDP_Description_Media *>::iterator it = _medias.begin();
    while (it != _medias.end())
    {
        if (count++ == pos)
            break;

        it++;
    }

    _medias.insert(it, media);
    return true;
}

//-------------------------------------------

SDP_Description_Media *SDP_Description::get_media(unsigned short pos)
{
    unsigned short count = 0;

    std::list<SDP_Description_Media *>::const_iterator it = _medias.begin();
    while (it != _medias.end())
    {
        if (count++ == pos)
            return *it;

        it++;
    }

    _logger.warning("Failed to get media: invalid position (pos=%d, count=%d)", pos, count);
    return NULL;
}

//-------------------------------------------

bool SDP_Description::remove_media(unsigned short pos)
{
    unsigned short count = 0;

    std::list<SDP_Description_Media *>::iterator it = _medias.begin();
    while (it != _medias.end())
    {
        if (count++ == pos)
        {
            _medias.erase(it);
            return true;
        }

        it++;
    }

    _logger.warning("Failed to remove media: invalid position (pos=%d, count=%d)", pos, count);
    return false;
}

//-------------------------------------------

void SDP_Description::clear_medias()
{
    std::list<SDP_Description_Media *>::const_iterator it = _medias.begin();
    while (it != _medias.end())
    {
        SDP_Description_Media *media = *it++;
        delete media;
    }

    _medias.clear();
}

//-------------------------------------------
//-------------------------------------------

SDP_Description_Fields::SDP_Description_Fields(const SDP_Description_Fields &description)
{
    sdp_field_map::const_iterator it1 = description._fields.begin();
    while (it1 != description._fields.end())
    {
        sdp_field_list fields = it1->second;
        it1++;

        sdp_field_list::const_iterator it2 = fields.begin();
        while (it2 != fields.end())
        {
            SDP_Field *field = *it2++;
            SDP_Field *new_field = SDP_Field::create_field(field->get_field_type(), field);
            add_field(new_field);
        }
    }
}

//-------------------------------------------

SDP_Description_Fields::~SDP_Description_Fields()
{
    clear_fields();
}

//-------------------------------------------

bool SDP_Description_Fields::decode(std::string &msg)
{
    while (true)
    {
        if (msg.empty())
            break;

        std::string line;

        if (!String_Functions::get_line(msg, line))
        {
            _logger.warning("Failed to decode: get line failed");
            return false;
        }

        sdp_field_list fields;

        if (!SDP_Field::decode_fields(line, fields))
        {
            sdp_field_list::const_iterator it = fields.begin();
            while (it != fields.end())
                delete *it++;

            fields.clear();
            return false;
        }

        add_fields(fields);
    }

    return true;
}

//-------------------------------------------

bool SDP_Description_Fields::encode(std::string &msg)
{
    sdp_field_map::const_iterator it = _fields.begin();
    while (it != _fields.end())
    {
        sdp_field_list fields = it->second;
        it++;

        if (!SDP_Field::encode_fields(msg, fields))
            return false;
    }

    return true;
}

//-------------------------------------------

bool SDP_Description_Fields::query(QueryCommand cmd, const std::string &query, std::string &result)
{
    Query query_field_name(query);
    std::string field_name = query_field_name._command;

    SDP_Field_Type field_type = SDP_Functions::get_field_type(field_name);
    if (field_type == SDP_FIELD_INVALID)
    {
        _logger.warning("Failed to query: invalid field type (cmd=%d, query=%s)", cmd, query.c_str());
        return false;
    }

    if (query_field_name._remaining == "Size")
    {
        if (cmd == QUERY_GET)
        {
            result = std::to_string(get_field_size(field_type));
            return true;
        }else
        {
            _logger.warning("Failed to query: invalid query command (cmd=%d, query=%s)", cmd, query.c_str());
            return false;
        }
    }

    Query query_field_position(query_field_name._remaining);
    unsigned short pos = String_Functions::str_to_us(query_field_position._command);
    if (pos == INVALID_UNSIGNED_SHORT)
    {
        _logger.warning("Failed to query: invalid field position (cmd=%d, query=%s)", cmd, query.c_str());
        return false;
    }

    if (query_field_position._remaining.empty())
    {
        if (cmd == QUERY_ADD)
        {
            SDP_Field *field = SDP_Field::create_field(field_type);
            if (!field)
            {
                _logger.warning("Failed to query: create field failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            if (!add_field(field, pos))
            {
                _logger.warning("Failed to query: add field failed (cmd=%d, query=%s)", cmd, query.c_str());
                delete field;
                return false;
            }

            return true;

        }else if (cmd == QUERY_DEL)
        {
            if (!remove_field(field_type, pos))
            {
                _logger.warning("Failed to query: remove field failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;
        }else
        {
            _logger.warning("Failed to query: invalid query command (cmd=%d, query=%s)", cmd, query.c_str());
            return false;
        }
    }

    SDP_Field *field = get_field(field_type, pos);
    if (!field)
    {
        _logger.warning("Failed to query: invalid header (cmd=%d, query=%s)", cmd, query.c_str());
        return false;
    }

    return field->query_field(cmd, query_field_position._remaining, result);
}

//-------------------------------------------

bool SDP_Description_Fields::add_field(SDP_Field *field, unsigned short pos)
{
    if (!field)
    {
        _logger.warning("Failed to add field: invalid field");
        return false;
    }

    SDP_Field_Type field_type = field->get_field_type();

    if (_fields.count(field_type) > 0)
    {
        unsigned short count = 0;

        sdp_field_list &fields = _fields.at(field_type);
        sdp_field_list::iterator it = fields.begin();
        while (it != fields.end())
        {
            if (count++ == pos)
                break;

            it++;
        }

        fields.insert(it, field);
    }else
    {
        sdp_field_list fields;
        fields.push_back(field);
        _fields[field_type] = fields;
    }

    return true;
}

//-------------------------------------------

bool SDP_Description_Fields::add_fields(sdp_field_list &fields)
{
    if (fields.empty())
    {
        _logger.warning("Failed to add fields: invalid fields");
        return false;
    }

    sdp_field_list::const_iterator it = fields.begin();
    while (it != fields.end())
    {
        SDP_Field *field = *it++;
        add_field(field);
    }

    return true;
}

//-------------------------------------------

bool SDP_Description_Fields::remove_field(SDP_Field_Type field_type, unsigned short pos)
{
    if (_fields.count(field_type) == 0)
    {
        _logger.warning("Failed to remove field: invalid field type (type=%d)", field_type);
        return false;
    }

    unsigned short count = 0;

    sdp_field_list &fields = _fields.at(field_type);
    sdp_field_list::iterator it = fields.begin();
    while (it != fields.end())
    {
        if (count++ == pos)
        {
            fields.erase(it);
            return true;
        }

        it++;
    }

    _logger.warning("Failed to remove field: invalid position (type=%d, pos=%d, count=%d)", field_type, pos, count);
    return false;
}

//-------------------------------------------

void SDP_Description_Fields::clear_fields()
{
    sdp_field_map::const_iterator it1 = _fields.begin();
    while (it1 != _fields.end())
    {
        const sdp_field_list &fields = it1->second;
        it1++;

        sdp_field_list::const_iterator it2 = fields.begin();
        while (it2 != fields.end())
        {
            SDP_Field *field = *it2++;
            delete field;
        }
    }

    _fields.clear();
}

//-------------------------------------------

SDP_Field *SDP_Description_Fields::get_field(SDP_Field_Type field_type, unsigned short pos)
{
    if (_fields.count(field_type) == 0)
    {
        //_logger.warning("Failed to get field: invalid field type (type=%d)", field_type);
        return NULL;
    }

    unsigned short count = 0;

    sdp_field_list &fields = _fields.at(field_type);
    sdp_field_list::const_iterator it = fields.begin();
    while (it != fields.end())
    {
        if (count++ == pos)
            return *it;

        it++;
    }

    _logger.warning("Failed to get field: invalid position (type=%d, pos=%d, count=%d)", field_type, pos, count);
    return NULL;
}

//-------------------------------------------

unsigned short SDP_Description_Fields::get_field_size(SDP_Field_Type field_type)
{
    if (_fields.count(field_type) == 0)
        return 0;

    sdp_field_list &fields = _fields.at(field_type);
    return (unsigned short) fields.size();
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Description_Session::decode(std::string &msg)
{
    if (!SDP_Description_Fields::decode(msg))
        return false;

    if ((!get_field(SDP_FIELD_PROTOCOL_VERSION)) || (!get_field(SDP_FIELD_ORIGIN)) || (!get_field(SDP_FIELD_SESSION_NAME)) ||
        (!get_field(SDP_FIELD_TIMING)))
    {
        _logger.warning("Failed to decode: required session fields not present");
        return false;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Description_Media::decode(std::string &msg)
{
    if (!SDP_Description_Fields::decode(msg))
        return false;

    if (!get_field(SDP_FIELD_MEDIA_DESCRIPTION))
    {
        _logger.warning("Failed to decode: required media field not present");
        return false;
    }

    return true;
}

//-------------------------------------------
