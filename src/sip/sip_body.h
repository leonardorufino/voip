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

#include "sip_defs.h"
#include "util/log_manager.h"

class SIP_Body
{
public:
    SIP_Body() {}
    virtual ~SIP_Body() {}

    static SIP_Body *create_body(SIP_Body_Type body_type, const SIP_Body *copy = NULL);

    // Virtual functions
    virtual SIP_Body_Type get_body_type() = 0;
    virtual bool decode(const char *body, unsigned short size) = 0;
    virtual bool encode(char *body, unsigned short &size) = 0;

protected:
    static Logger _logger;
};

//-------------------------------------------

class SIP_Body_Unknown : public SIP_Body
{
public:
    SIP_Body_Unknown() : _body(NULL), _size(0) {}
    SIP_Body_Unknown(const SIP_Body_Unknown &body);
    virtual ~SIP_Body_Unknown();

    // Virtual functions
    SIP_Body_Type get_body_type() { return SIP_BODY_UNKNOWN; }
    bool decode(const char *body, unsigned short size);
    bool encode(char *body, unsigned short &size);

    void set_body(const char *body, unsigned short size);
    bool set_body(std::string body);
    char *get_body() { return _body; }
    bool get_body(std::string &body);
    unsigned short get_size() { return _size; }

protected:
    char *_body;
    unsigned short _size;
};

//-------------------------------------------
