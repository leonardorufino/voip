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
};

//-------------------------------------------

class SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_Decode_Encode_Test() {}
    virtual ~SDP_Field_Decode_Encode_Test() {}

    bool run();

protected:
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

class SDP_Field_Protocol_Version_Decode_Encode_Test : public SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_Protocol_Version_Decode_Encode_Test();
};

//-------------------------------------------

class SDP_Field_Origin_Decode_Encode_Test : public SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_Origin_Decode_Encode_Test();
};

//-------------------------------------------

class SDP_Field_Session_Name_Decode_Encode_Test : public SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_Session_Name_Decode_Encode_Test();
};

//-------------------------------------------

class SDP_Field_Session_Information_Decode_Encode_Test : public SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_Session_Information_Decode_Encode_Test();
};

//-------------------------------------------

class SDP_Field_URI_Decode_Encode_Test : public SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_URI_Decode_Encode_Test();
};

//-------------------------------------------

class SDP_Field_Email_Address_Decode_Encode_Test : public SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_Email_Address_Decode_Encode_Test();
};

//-------------------------------------------

class SDP_Field_Phone_Number_Decode_Encode_Test : public SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_Phone_Number_Decode_Encode_Test();
};

//-------------------------------------------

class SDP_Field_Connection_Data_Decode_Encode_Test : public SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_Connection_Data_Decode_Encode_Test();
};

//-------------------------------------------

class SDP_Field_Bandwidth_Decode_Encode_Test : public SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_Bandwidth_Decode_Encode_Test();
};

//-------------------------------------------

class SDP_Field_Timing_Decode_Encode_Test : public SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_Timing_Decode_Encode_Test();
};

//-------------------------------------------

class SDP_Field_Repeat_Time_Decode_Encode_Test : public SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_Repeat_Time_Decode_Encode_Test();
};

//-------------------------------------------

class SDP_Field_Time_Zone_Decode_Encode_Test : public SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_Time_Zone_Decode_Encode_Test();
};

//-------------------------------------------

class SDP_Field_Encryption_Key_Decode_Encode_Test : public SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_Encryption_Key_Decode_Encode_Test();
};

//-------------------------------------------

class SDP_Field_Attribute_Decode_Encode_Test : public SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_Attribute_Decode_Encode_Test();
};

//-------------------------------------------

class SDP_Field_Media_Description_Decode_Encode_Test : public SDP_Field_Decode_Encode_Test
{
public:
    SDP_Field_Media_Description_Decode_Encode_Test();
};

//-------------------------------------------
