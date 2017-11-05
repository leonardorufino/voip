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
