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

class SIP_Body
{
public:
    SIP_Body() : _body(NULL), _size(0) {}
    SIP_Body(const SIP_Body &body);
    virtual ~SIP_Body();

    static SIP_Body *create_body(SIP_Body_Type body_type, const SIP_Body *copy = NULL);

    // Virtual functions
    virtual SIP_Body_Type get_body_type() { return SIP_BODY_UNKNOWN; }
    virtual bool decode(const char *body, unsigned short size);
    virtual bool encode(char *body, unsigned short &size);

protected:
    char *_body;
    unsigned short _size;
};

//-------------------------------------------
