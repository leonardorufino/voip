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
#include <string>

class SDP_Functions
{
public:
    static SDP_Field_Type get_field_type(std::string field);
    static std::string get_field_type(SDP_Field_Type field);
};
