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

#include "util/util_defs.h"
#include <string>

enum SDP_Field_Type
{
    SDP_FIELD_PROTOCOL_VERSION,
    SDP_FIELD_ORIGIN,
    SDP_FIELD_SESSION_NAME,
    SDP_FIELD_SESSION_INFORMATION,
    SDP_FIELD_URI,
    SDP_FIELD_EMAIL_ADDRESS,
    SDP_FIELD_PHONE_NUMBER,
    SDP_FIELD_CONNECTION_DATA,
    SDP_FIELD_BANDWIDTH,
    SDP_FIELD_TIMING,
    SDP_FIELD_REPEAT_TIME,
    SDP_FIELD_TIME_ZONE,
    SDP_FIELD_ENCRYPTION_KEY,
    SDP_FIELD_ATTRIBUTE,
    SDP_FIELD_MEDIA_DESCRIPTION,
    SDP_FIELD_INVALID
};
