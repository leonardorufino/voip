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

class SDP_Field_Origin_Test : public SDP_Field_Test
{
public:
    SDP_Field_Origin_Test();
};

//-------------------------------------------

class SDP_Field_Session_Name_Test : public SDP_Field_Test
{
public:
    SDP_Field_Session_Name_Test();
};

//-------------------------------------------

class SDP_Field_Session_Information_Test : public SDP_Field_Test
{
public:
    SDP_Field_Session_Information_Test();
};

//-------------------------------------------

class SDP_Field_URI_Test : public SDP_Field_Test
{
public:
    SDP_Field_URI_Test();
};

//-------------------------------------------

class SDP_Field_Email_Address_Test : public SDP_Field_Test
{
public:
    SDP_Field_Email_Address_Test();
};

//-------------------------------------------

class SDP_Field_Phone_Number_Test : public SDP_Field_Test
{
public:
    SDP_Field_Phone_Number_Test();
};

//-------------------------------------------

class SDP_Field_Connection_Data_Test : public SDP_Field_Test
{
public:
    SDP_Field_Connection_Data_Test();
};

//-------------------------------------------

class SDP_Field_Bandwidth_Test : public SDP_Field_Test
{
public:
    SDP_Field_Bandwidth_Test();
};

//-------------------------------------------

class SDP_Field_Timing_Test : public SDP_Field_Test
{
public:
    SDP_Field_Timing_Test();
};

//-------------------------------------------

class SDP_Field_Repeat_Time_Test : public SDP_Field_Test
{
public:
    SDP_Field_Repeat_Time_Test();
};

//-------------------------------------------

class SDP_Field_Time_Zone_Test : public SDP_Field_Test
{
public:
    SDP_Field_Time_Zone_Test();
};

//-------------------------------------------

class SDP_Field_Encryption_Key_Test : public SDP_Field_Test
{
public:
    SDP_Field_Encryption_Key_Test();
};

//-------------------------------------------

class SDP_Field_Attribute_Test : public SDP_Field_Test
{
public:
    SDP_Field_Attribute_Test();
};

//-------------------------------------------
