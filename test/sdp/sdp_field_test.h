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

#include "sdp/sdp_field.h"
#include <list>
#include <iomanip>

class SDP_Field_Test
{
public:
    SDP_Field_Test() {}
    virtual ~SDP_Field_Test() {}

    static bool init();
    template<class T> static bool run();

protected:
    bool run();

    bool copy_fields(sdp_field_list &fields, sdp_field_list &copy);
    void clear(sdp_field_list &fields);

protected:
    class SDP_Field_Input_Output
    {
    public:
        SDP_Field_Type _field_type;
        std::string _input;
        std::string _output;
        unsigned short _field_nb;
        bool _decode_success;
        bool _encode_success;
    };

    std::list<SDP_Field_Input_Output> _field_input_output;
};

//-------------------------------------------
//-------------------------------------------

class SDP_Field_Protocol_Version_Test : public SDP_Field_Test
{
public:
    SDP_Field_Protocol_Version_Test();
};

//-------------------------------------------
