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

#include "sdp_defs.h"
#include "util/util_defs.h"
#include "util/log_manager.h"
#include <string>
#include <list>

class SDP_Field;
typedef std::list<SDP_Field *> sdp_field_list;

class SDP_Field
{
public:
    SDP_Field() {}
    virtual ~SDP_Field() {}

    static SDP_Field *create_field(SDP_Field_Type field_type, const SDP_Field *copy = NULL);
    static bool decode_fields(std::string &msg, sdp_field_list &fields);
    static bool encode_fields(std::string &msg, sdp_field_list &fields);

    // Virtual pure functions
    virtual SDP_Field_Type get_field_type() = 0;
    virtual bool decode(std::string &msg) = 0;
    virtual bool encode(std::string &msg) = 0;

protected:
    std::string _field_line;

    static Logger _logger;
};

//-------------------------------------------
//-------------------------------------------

class SDP_Field_Protocol_Version : public SDP_Field
{
public:
    static const unsigned short INVALID_VERSION = INVALID_UNSIGNED_SHORT;

public:
    SDP_Field_Protocol_Version() : _version(INVALID_VERSION) {}
    SDP_Field_Protocol_Version(const SDP_Field_Protocol_Version &field) { *this = field; }
    ~SDP_Field_Protocol_Version() {}

    // Virtual pure functions
    SDP_Field_Type get_field_type() { return SDP_FIELD_PROTOCOL_VERSION; }
    bool decode(std::string &msg);
    bool encode(std::string &msg);

    void set_version(unsigned short version) { _version = version; }
    unsigned short get_version() { return _version; }

private:
    unsigned short _version;
};

//-------------------------------------------
