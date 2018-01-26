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

#pragma once

#include "sdp_field.h"
#include "sip/sip_defs.h"
#include "sip/sip_body.h"
#include "util/log_manager.h"
#include <string>
#include <cstring>
#include <map>
#include <list>

typedef std::map<SDP_Field_Type, sdp_field_list> sdp_field_map;

class SDP_Description_Session;
class SDP_Description_Media;

class SDP_Description : public SIP_Body
{
public:
    SDP_Description() : _session(NULL) {}
    SDP_Description(const SDP_Description &description);
    ~SDP_Description();

    // Virtual functions
    SIP_Body_Type get_body_type() { return SIP_BODY_SDP; }
    bool decode(const char *body, unsigned short size);
    bool encode(char *body, unsigned short &size);

    void set_session(SDP_Description_Session *session);
    SDP_Description_Session *get_session() { return _session; }
    void clear_session();

    void add_media(SDP_Description_Media *media);
    std::list<SDP_Description_Media *> &get_medias() { return _medias; }
    void clear_medias();

protected:
    SDP_Description_Session *_session;
    std::list<SDP_Description_Media *> _medias;

    static Logger _logger;
};

//-------------------------------------------

class SDP_Description_Fields
{
public:
    SDP_Description_Fields() {}
    SDP_Description_Fields(const SDP_Description_Fields &description);
    virtual ~SDP_Description_Fields();

    virtual bool decode(std::string &msg);
    virtual bool encode(std::string &msg);

    void add_field(SDP_Field *field);
    void add_fields(sdp_field_list &fields);
    void clear_fields();
    SDP_Field *get_field(SDP_Field_Type field_type, unsigned short pos = 0);
    unsigned short get_field_size(SDP_Field_Type field_type);

protected:
    sdp_field_map _fields;

    static Logger _logger;
};

//-------------------------------------------

class SDP_Description_Session : public SDP_Description_Fields
{
public:
    SDP_Description_Session() {}
    SDP_Description_Session(const SDP_Description_Session &session) : SDP_Description_Fields(session) {}
    ~SDP_Description_Session() {}

    bool decode(std::string &msg);
};

//-------------------------------------------

class SDP_Description_Media : public SDP_Description_Fields
{
public:
    SDP_Description_Media() {}
    SDP_Description_Media(const SDP_Description_Media &media) : SDP_Description_Fields(media) {}
    ~SDP_Description_Media() {}

    bool decode(std::string &msg);
};

//-------------------------------------------
