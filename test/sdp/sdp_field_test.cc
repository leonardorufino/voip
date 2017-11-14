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

#include "sdp_field_test.h"

//-------------------------------------------

bool SDP_Field_Test::init()
{
    std::cout << "SDP field test initialized\n";

    if (!run<SDP_Field_Protocol_Version_Test>())
        return false;

    if (!run<SDP_Field_Origin_Test>())
        return false;

    if (!run<SDP_Field_Session_Name_Test>())
        return false;

    if (!run<SDP_Field_Session_Information_Test>())
        return false;

    std::cout << "SDP field test completed successfully\n";
    return true;
}

//-------------------------------------------

template<class T> bool SDP_Field_Test::run()
{
    T test;
    if (!test.run())
        return false;
    return true;
}

//-------------------------------------------

bool SDP_Field_Test::run()
{
    std::list<SDP_Field_Input_Output>::const_iterator it = _field_input_output.begin();
    while (it != _field_input_output.end())
    {
        SDP_Field_Input_Output field_input_output = *it++;

        std::cout << "SDP field test initialized (type: " << field_input_output._field_type << ")\n";

        sdp_field_list fields;

        std::string input = field_input_output._input;
        bool decode = SDP_Field::decode_fields(input, fields);

        if (field_input_output._decode_success != decode)
        {
            std::cout << "SDP_Field_Test::run -> Failed to decode fields:\n";
            std::cout << std::setw(12) << "Type: " << field_input_output._field_type << "\n";
            std::cout << std::setw(12) << "Input: " << field_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << (field_input_output._decode_success ? "true" : "false") << "\n";
            std::cout << std::setw(12) << "Success: " << (decode ? "true" : "false") << "\n";
            return false;
        }

        if (!decode)
        {
            clear(fields);
            std::cout << "SDP field test completed successfully (type: " << field_input_output._field_type << ")\n";
            continue;
        }

        if (field_input_output._field_nb != (unsigned short) fields.size())
        {
            std::cout << "SDP_Field_Test::run -> Invalid size of fields:\n";
            std::cout << std::setw(12) << "Type: " << field_input_output._field_type << "\n";
            std::cout << std::setw(12) << "Input: " << field_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << field_input_output._field_nb << "\n";
            std::cout << std::setw(12) << "Size: " << fields.size() << "\n";
            return false;
        }

        sdp_field_list::iterator it2 = fields.begin();
        while (it2 != fields.end())
        {
            SDP_Field *field = *it2++;
            if (field->get_field_type() != field_input_output._field_type)
            {
                std::cout << "SDP_Field_Test::run -> Invalid decoded field type:\n";
                std::cout << std::setw(12) << "Type: " << field_input_output._field_type << "\n";
                std::cout << std::setw(12) << "Input: " << field_input_output._input.c_str() << "\n";
                std::cout << std::setw(12) << "Result: " << field->get_field_type() << "\n";
                return false;
            }
        }

        sdp_field_list copy;
        if (!copy_fields(fields, copy))
        {
            std::cout << "SDP_Field_Test::run -> Failed to copy fields:\n";
            std::cout << std::setw(12) << "Type: " << field_input_output._field_type << "\n";
            std::cout << std::setw(12) << "Input: " << field_input_output._input.c_str() << "\n";
            return false;
        }

        clear(fields);

        std::string output;
        bool encode = SDP_Field::encode_fields(output, copy);

        if (field_input_output._encode_success != encode)
        {
            std::cout << "SDP_Field_Test::run -> Failed to encode fields:\n";
            std::cout << std::setw(12) << "Type: " << field_input_output._field_type << "\n";
            std::cout << std::setw(12) << "Input: " << field_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << (field_input_output._encode_success ? "true" : "false") << "\n";
            std::cout << std::setw(12) << "Success: " << (encode ? "true" : "false") << "\n";
            return false;
        }

        if (!encode)
        {
            clear(copy);
            std::cout << "SDP field test completed successfully (type: " << field_input_output._field_type << ")\n";
            continue;
        }

        if (output != field_input_output._output)
        {
            std::cout << "SDP_Field_Test::run -> Invalid encoded field:\n";
            std::cout << std::setw(12) << "Type: " << field_input_output._field_type << "\n";
            std::cout << std::setw(12) << "Input: " << field_input_output._input.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << field_input_output._output.c_str() << "\n";
            std::cout << std::setw(12) << "Output: " << output.c_str() << "\n";
            return false;
        }

        clear(copy);

        std::cout << "SDP field test completed successfully (type: " << field_input_output._field_type << ")\n";
    }

    return true;
}

//-------------------------------------------

bool SDP_Field_Test::copy_fields(sdp_field_list &fields, sdp_field_list &copy)
{
    sdp_field_list::const_iterator it = fields.begin();
    while (it != fields.end())
    {
        SDP_Field *field = *it++;

        SDP_Field *new_field = SDP_Field::create_field(field->get_field_type(), field);
        if (!new_field)
            return false;

        copy.push_back(new_field);
    }

    return true;
}

//-------------------------------------------

void SDP_Field_Test::clear(sdp_field_list &fields)
{
    sdp_field_list::const_iterator it = fields.begin();
    while (it != fields.end())
        delete *it++;

    fields.clear();
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Protocol_Version_Test::SDP_Field_Protocol_Version_Test()
{
    SDP_Field_Input_Output field1;
    field1._field_type     = SDP_FIELD_PROTOCOL_VERSION;
    field1._input          = "v=0";
    field1._output         = "v=0\r\n";
    field1._field_nb       = 1;
    field1._decode_success = true;
    field1._encode_success = true;
    _field_input_output.push_back(field1);

    SDP_Field_Input_Output field2;
    field2._field_type     = SDP_FIELD_PROTOCOL_VERSION;
    field2._input          = "v=9";
    field2._output         = "v=9\r\n";
    field2._field_nb       = 1;
    field2._decode_success = true;
    field2._encode_success = true;
    _field_input_output.push_back(field2);

    SDP_Field_Input_Output field3;
    field3._field_type     = SDP_FIELD_PROTOCOL_VERSION;
    field3._input          = "v=9999";
    field3._output         = "v=9999\r\n";
    field3._field_nb       = 1;
    field3._decode_success = true;
    field3._encode_success = true;
    _field_input_output.push_back(field3);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Origin_Test::SDP_Field_Origin_Test()
{
    SDP_Field_Input_Output field1;
    field1._field_type     = SDP_FIELD_ORIGIN;
    field1._input          = "o=jdoe 2890844526 2890842807 IN IP4 10.47.16.5";
    field1._output         = "o=jdoe 2890844526 2890842807 IN IP4 10.47.16.5\r\n";
    field1._field_nb       = 1;
    field1._decode_success = true;
    field1._encode_success = true;
    _field_input_output.push_back(field1);

    SDP_Field_Input_Output field2;
    field2._field_type     = SDP_FIELD_ORIGIN;
    field2._input          = "o=- 0 0 IN IP4 domain.com";
    field2._output         = "o=- 0 0 IN IP4 domain.com\r\n";
    field2._field_nb       = 1;
    field2._decode_success = true;
    field2._encode_success = true;
    _field_input_output.push_back(field2);

    SDP_Field_Input_Output field3;
    field3._field_type     = SDP_FIELD_ORIGIN;
    field3._input          = "o=test 99887766554433221100 11223344556677889900 IN IP6 2200:05FF::1111:2222:EEFC";
    field3._output         = "o=test 99887766554433221100 11223344556677889900 IN IP6 2200:05FF::1111:2222:EEFC\r\n";
    field3._field_nb       = 1;
    field3._decode_success = true;
    field3._encode_success = true;
    _field_input_output.push_back(field3);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Session_Name_Test::SDP_Field_Session_Name_Test()
{
    SDP_Field_Input_Output field1;
    field1._field_type     = SDP_FIELD_SESSION_NAME;
    field1._input          = "s=SDP Seminar";
    field1._output         = "s=SDP Seminar\r\n";
    field1._field_nb       = 1;
    field1._decode_success = true;
    field1._encode_success = true;
    _field_input_output.push_back(field1);

    SDP_Field_Input_Output field2;
    field2._field_type     = SDP_FIELD_SESSION_NAME;
    field2._input          = "s= ";
    field2._output         = "s= \r\n";
    field2._field_nb       = 1;
    field2._decode_success = true;
    field2._encode_success = true;
    _field_input_output.push_back(field2);

    SDP_Field_Input_Output field3;
    field3._field_type     = SDP_FIELD_SESSION_NAME;
    field3._input          = "s=This is a session name";
    field3._output         = "s=This is a session name\r\n";
    field3._field_nb       = 1;
    field3._decode_success = true;
    field3._encode_success = true;
    _field_input_output.push_back(field3);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Session_Information_Test::SDP_Field_Session_Information_Test()
{
    SDP_Field_Input_Output field1;
    field1._field_type     = SDP_FIELD_SESSION_INFORMATION;
    field1._input          = "i=A Seminar on the session description protocol";
    field1._output         = "i=A Seminar on the session description protocol\r\n";
    field1._field_nb       = 1;
    field1._decode_success = true;
    field1._encode_success = true;
    _field_input_output.push_back(field1);

    SDP_Field_Input_Output field2;
    field2._field_type     = SDP_FIELD_SESSION_INFORMATION;
    field2._input          = "i=Test ";
    field2._output         = "i=Test \r\n";
    field2._field_nb       = 1;
    field2._decode_success = true;
    field2._encode_success = true;
    _field_input_output.push_back(field2);

    SDP_Field_Input_Output field3;
    field3._field_type     = SDP_FIELD_SESSION_INFORMATION;
    field3._input          = "i=";
    field3._output         = "i=\r\n";
    field3._field_nb       = 1;
    field3._decode_success = true;
    field3._encode_success = true;
    _field_input_output.push_back(field3);
}

//-------------------------------------------
