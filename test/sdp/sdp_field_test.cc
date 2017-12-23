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

    if (!run<SDP_Field_URI_Test>())
        return false;

    if (!run<SDP_Field_Email_Address_Test>())
        return false;

    if (!run<SDP_Field_Phone_Number_Test>())
        return false;

    if (!run<SDP_Field_Connection_Data_Test>())
        return false;

    if (!run<SDP_Field_Bandwidth_Test>())
        return false;

    if (!run<SDP_Field_Timing_Test>())
        return false;

    if (!run<SDP_Field_Repeat_Time_Test>())
        return false;

    if (!run<SDP_Field_Time_Zone_Test>())
        return false;

    if (!run<SDP_Field_Encryption_Key_Test>())
        return false;

    if (!run<SDP_Field_Attribute_Test>())
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
//-------------------------------------------

SDP_Field_URI_Test::SDP_Field_URI_Test()
{
    SDP_Field_Input_Output field1;
    field1._field_type     = SDP_FIELD_URI;
    field1._input          = "u=http://www.example.com/seminars/sdp.pdf";
    field1._output         = "u=http://www.example.com/seminars/sdp.pdf\r\n";
    field1._field_nb       = 1;
    field1._decode_success = true;
    field1._encode_success = true;
    _field_input_output.push_back(field1);

    SDP_Field_Input_Output field2;
    field2._field_type     = SDP_FIELD_URI;
    field2._input          = "u=www.test.com ";
    field2._output         = "u=www.test.com \r\n";
    field2._field_nb       = 1;
    field2._decode_success = true;
    field2._encode_success = true;
    _field_input_output.push_back(field2);

    SDP_Field_Input_Output field3;
    field3._field_type     = SDP_FIELD_URI;
    field3._input          = "u=";
    field3._output         = "u=\r\n";
    field3._field_nb       = 1;
    field3._decode_success = true;
    field3._encode_success = true;
    _field_input_output.push_back(field3);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Email_Address_Test::SDP_Field_Email_Address_Test()
{
    SDP_Field_Input_Output field1;
    field1._field_type     = SDP_FIELD_EMAIL_ADDRESS;
    field1._input          = "e=j.doe@example.com (Jane Doe)";
    field1._output         = "e=j.doe@example.com (Jane Doe)\r\n";
    field1._field_nb       = 1;
    field1._decode_success = true;
    field1._encode_success = true;
    _field_input_output.push_back(field1);

    SDP_Field_Input_Output field2;
    field2._field_type     = SDP_FIELD_EMAIL_ADDRESS;
    field2._input          = "e=Jane Doe <j.doe@example.com>";
    field2._output         = "e=Jane Doe <j.doe@example.com>\r\n";
    field2._field_nb       = 1;
    field2._decode_success = true;
    field2._encode_success = true;
    _field_input_output.push_back(field2);

    SDP_Field_Input_Output field3;
    field3._field_type     = SDP_FIELD_EMAIL_ADDRESS;
    field3._input          = "e=test@domain.com";
    field3._output         = "e=test@domain.com\r\n";
    field3._field_nb       = 1;
    field3._decode_success = true;
    field3._encode_success = true;
    _field_input_output.push_back(field3);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Phone_Number_Test::SDP_Field_Phone_Number_Test()
{
    SDP_Field_Input_Output field1;
    field1._field_type     = SDP_FIELD_PHONE_NUMBER;
    field1._input          = "p=+1 617 555-6011";
    field1._output         = "p=+1 617 555-6011\r\n";
    field1._field_nb       = 1;
    field1._decode_success = true;
    field1._encode_success = true;
    _field_input_output.push_back(field1);

    SDP_Field_Input_Output field2;
    field2._field_type     = SDP_FIELD_PHONE_NUMBER;
    field2._input          = "p=9876543210 (Jane Doe)";
    field2._output         = "p=9876543210 (Jane Doe)\r\n";
    field2._field_nb       = 1;
    field2._decode_success = true;
    field2._encode_success = true;
    _field_input_output.push_back(field2);

    SDP_Field_Input_Output field3;
    field3._field_type     = SDP_FIELD_PHONE_NUMBER;
    field3._input          = "p=Jane Doe <+1 234 567-8900>";
    field3._output         = "p=Jane Doe <+1 234 567-8900>\r\n";
    field3._field_nb       = 1;
    field3._decode_success = true;
    field3._encode_success = true;
    _field_input_output.push_back(field3);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Connection_Data_Test::SDP_Field_Connection_Data_Test()
{
    SDP_Field_Input_Output field1;
    field1._field_type     = SDP_FIELD_CONNECTION_DATA;
    field1._input          = "c=IN IP4 224.2.1.1";
    field1._output         = "c=IN IP4 224.2.1.1\r\n";
    field1._field_nb       = 1;
    field1._decode_success = true;
    field1._encode_success = true;
    _field_input_output.push_back(field1);

    SDP_Field_Input_Output field2;
    field2._field_type     = SDP_FIELD_CONNECTION_DATA;
    field2._input          = "c=IN IP4 224.2.1.3/127";
    field2._output         = "c=IN IP4 224.2.1.3/127\r\n";
    field2._field_nb       = 1;
    field2._decode_success = true;
    field2._encode_success = true;
    _field_input_output.push_back(field2);

    SDP_Field_Input_Output field3;
    field3._field_type     = SDP_FIELD_CONNECTION_DATA;
    field3._input          = "c=IN IP4 224.2.1.1/127/3";
    field3._output         = "c=IN IP4 224.2.1.1/127/3\r\n";
    field3._field_nb       = 1;
    field3._decode_success = true;
    field3._encode_success = true;
    _field_input_output.push_back(field3);

    SDP_Field_Input_Output field4;
    field4._field_type     = SDP_FIELD_CONNECTION_DATA;
    field4._input          = "c=IN IP6 FF15::102";
    field4._output         = "c=IN IP6 FF15::102\r\n";
    field4._field_nb       = 1;
    field4._decode_success = true;
    field4._encode_success = true;
    _field_input_output.push_back(field4);

    SDP_Field_Input_Output field5;
    field5._field_type     = SDP_FIELD_CONNECTION_DATA;
    field5._input          = "c=IN IP6 FF15::101/3";
    field5._output         = "c=IN IP6 FF15::101/3\r\n";
    field5._field_nb       = 1;
    field5._decode_success = true;
    field5._encode_success = true;
    _field_input_output.push_back(field5);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Bandwidth_Test::SDP_Field_Bandwidth_Test()
{
    SDP_Field_Input_Output field1;
    field1._field_type     = SDP_FIELD_BANDWIDTH;
    field1._input          = "b=CT:64";
    field1._output         = "b=CT:64\r\n";
    field1._field_nb       = 1;
    field1._decode_success = true;
    field1._encode_success = true;
    _field_input_output.push_back(field1);

    SDP_Field_Input_Output field2;
    field2._field_type     = SDP_FIELD_BANDWIDTH;
    field2._input          = "b=AS:9999999";
    field2._output         = "b=AS:9999999\r\n";
    field2._field_nb       = 1;
    field2._decode_success = true;
    field2._encode_success = true;
    _field_input_output.push_back(field2);

    SDP_Field_Input_Output field3;
    field3._field_type     = SDP_FIELD_BANDWIDTH;
    field3._input          = "b=X-YZ:128";
    field3._output         = "b=X-YZ:128\r\n";
    field3._field_nb       = 1;
    field3._decode_success = true;
    field3._encode_success = true;
    _field_input_output.push_back(field3);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Timing_Test::SDP_Field_Timing_Test()
{
    SDP_Field_Input_Output field1;
    field1._field_type     = SDP_FIELD_TIMING;
    field1._input          = "t=2873397496 2873404696";
    field1._output         = "t=2873397496 2873404696\r\n";
    field1._field_nb       = 1;
    field1._decode_success = true;
    field1._encode_success = true;
    _field_input_output.push_back(field1);

    SDP_Field_Input_Output field2;
    field2._field_type     = SDP_FIELD_TIMING;
    field2._input          = "t=3034423619 3042462419";
    field2._output         = "t=3034423619 3042462419\r\n";
    field2._field_nb       = 1;
    field2._decode_success = true;
    field2._encode_success = true;
    _field_input_output.push_back(field2);

    SDP_Field_Input_Output field3;
    field3._field_type     = SDP_FIELD_TIMING;
    field3._input          = "t=9999999999 9999999999";
    field3._output         = "t=9999999999 9999999999\r\n";
    field3._field_nb       = 1;
    field3._decode_success = true;
    field3._encode_success = true;
    _field_input_output.push_back(field3);

    SDP_Field_Input_Output field4;
    field4._field_type     = SDP_FIELD_TIMING;
    field4._input          = "t=1234567890 0";
    field4._output         = "t=1234567890 0\r\n";
    field4._field_nb       = 1;
    field4._decode_success = true;
    field4._encode_success = true;
    _field_input_output.push_back(field4);

    SDP_Field_Input_Output field5;
    field5._field_type     = SDP_FIELD_TIMING;
    field5._input          = "t=0 0";
    field5._output         = "t=0 0\r\n";
    field5._field_nb       = 1;
    field5._decode_success = true;
    field5._encode_success = true;
    _field_input_output.push_back(field5);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Repeat_Time_Test::SDP_Field_Repeat_Time_Test()
{
    SDP_Field_Input_Output field1;
    field1._field_type     = SDP_FIELD_REPEAT_TIME;
    field1._input          = "r=604800 3600 0 90000";
    field1._output         = "r=604800 3600 0 90000\r\n";
    field1._field_nb       = 1;
    field1._decode_success = true;
    field1._encode_success = true;
    _field_input_output.push_back(field1);

    SDP_Field_Input_Output field2;
    field2._field_type     = SDP_FIELD_REPEAT_TIME;
    field2._input          = "r=7d 1h 0 25h";
    field2._output         = "r=7d 1h 0 25h\r\n";
    field2._field_nb       = 1;
    field2._decode_success = true;
    field2._encode_success = true;
    _field_input_output.push_back(field2);

    SDP_Field_Input_Output field3;
    field3._field_type     = SDP_FIELD_REPEAT_TIME;
    field3._input          = "r=999999 999999 999999";
    field3._output         = "r=999999 999999 999999\r\n";
    field3._field_nb       = 1;
    field3._decode_success = true;
    field3._encode_success = true;
    _field_input_output.push_back(field3);

    SDP_Field_Input_Output field4;
    field4._field_type     = SDP_FIELD_REPEAT_TIME;
    field4._input          = "r=123 456 789 123 456 7890";
    field4._output         = "r=123 456 789 123 456 7890\r\n";
    field4._field_nb       = 1;
    field4._decode_success = true;
    field4._encode_success = true;
    _field_input_output.push_back(field4);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Time_Zone_Test::SDP_Field_Time_Zone_Test()
{
    SDP_Field_Input_Output field1;
    field1._field_type     = SDP_FIELD_TIME_ZONE;
    field1._input          = "z=2882844526 -1h 2898848070 0";
    field1._output         = "z=2882844526 -1h 2898848070 0\r\n";
    field1._field_nb       = 1;
    field1._decode_success = true;
    field1._encode_success = true;
    _field_input_output.push_back(field1);

    SDP_Field_Input_Output field2;
    field2._field_type     = SDP_FIELD_TIME_ZONE;
    field2._input          = "z=1288494000 -1h";
    field2._output         = "z=1288494000 -1h\r\n";
    field2._field_nb       = 1;
    field2._decode_success = true;
    field2._encode_success = true;
    _field_input_output.push_back(field2);

    SDP_Field_Input_Output field3;
    field3._field_type     = SDP_FIELD_TIME_ZONE;
    field3._input          = "z=999999999 9 999999999 9h 99999 999";
    field3._output         = "z=999999999 9 999999999 9h 99999 999\r\n";
    field3._field_nb       = 1;
    field3._decode_success = true;
    field3._encode_success = true;
    _field_input_output.push_back(field3);

    SDP_Field_Input_Output field4;
    field4._field_type     = SDP_FIELD_TIME_ZONE;
    field4._input          = "z=123456789 2d 5566778899 120m 987654321 600s";
    field4._output         = "z=123456789 2d 5566778899 120m 987654321 600s\r\n";
    field4._field_nb       = 1;
    field4._decode_success = true;
    field4._encode_success = true;
    _field_input_output.push_back(field4);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Encryption_Key_Test::SDP_Field_Encryption_Key_Test()
{
    SDP_Field_Input_Output field1;
    field1._field_type     = SDP_FIELD_ENCRYPTION_KEY;
    field1._input          = "k=clear:password";
    field1._output         = "k=clear:password\r\n";
    field1._field_nb       = 1;
    field1._decode_success = true;
    field1._encode_success = true;
    _field_input_output.push_back(field1);

    SDP_Field_Input_Output field2;
    field2._field_type     = SDP_FIELD_ENCRYPTION_KEY;
    field2._input          = "k=base64:cGFzc3dvcmQ=";
    field2._output         = "k=base64:cGFzc3dvcmQ=\r\n";
    field2._field_nb       = 1;
    field2._decode_success = true;
    field2._encode_success = true;
    _field_input_output.push_back(field2);

    SDP_Field_Input_Output field3;
    field3._field_type     = SDP_FIELD_ENCRYPTION_KEY;
    field3._input          = "k=uri:www.test.com";
    field3._output         = "k=uri:www.test.com\r\n";
    field3._field_nb       = 1;
    field3._decode_success = true;
    field3._encode_success = true;
    _field_input_output.push_back(field3);

    SDP_Field_Input_Output field4;
    field4._field_type     = SDP_FIELD_ENCRYPTION_KEY;
    field4._input          = "k=prompt";
    field4._output         = "k=prompt\r\n";
    field4._field_nb       = 1;
    field4._decode_success = true;
    field4._encode_success = true;
    _field_input_output.push_back(field4);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Attribute_Test::SDP_Field_Attribute_Test()
{
    SDP_Field_Input_Output field1;
    field1._field_type     = SDP_FIELD_ATTRIBUTE;
    field1._input          = "a=recvonly";
    field1._output         = "a=recvonly\r\n";
    field1._field_nb       = 1;
    field1._decode_success = true;
    field1._encode_success = true;
    _field_input_output.push_back(field1);

    SDP_Field_Input_Output field2;
    field2._field_type     = SDP_FIELD_ATTRIBUTE;
    field2._input          = "a=rtpmap:99 h263-1998/90000";
    field2._output         = "a=rtpmap:99 h263-1998/90000\r\n";
    field2._field_nb       = 1;
    field2._decode_success = true;
    field2._encode_success = true;
    _field_input_output.push_back(field2);

    SDP_Field_Input_Output field3;
    field3._field_type     = SDP_FIELD_ATTRIBUTE;
    field3._input          = "a=ptime:20";
    field3._output         = "a=ptime:20\r\n";
    field3._field_nb       = 1;
    field3._decode_success = true;
    field3._encode_success = true;
    _field_input_output.push_back(field3);

    SDP_Field_Input_Output field4;
    field4._field_type     = SDP_FIELD_ATTRIBUTE;
    field4._input          = "a=rtpmap:98 L16/16000/2";
    field4._output         = "a=rtpmap:98 L16/16000/2\r\n";
    field4._field_nb       = 1;
    field4._decode_success = true;
    field4._encode_success = true;
    _field_input_output.push_back(field4);

    SDP_Field_Input_Output field5;
    field5._field_type     = SDP_FIELD_ATTRIBUTE;
    field5._input          = "a=orient:landscape";
    field5._output         = "a=orient:landscape\r\n";
    field5._field_nb       = 1;
    field5._decode_success = true;
    field5._encode_success = true;
    _field_input_output.push_back(field5);

    SDP_Field_Input_Output field6;
    field6._field_type     = SDP_FIELD_ATTRIBUTE;
    field6._input          = "a=charset:ISO-8859-1";
    field6._output         = "a=charset:ISO-8859-1\r\n";
    field6._field_nb       = 1;
    field6._decode_success = true;
    field6._encode_success = true;
    _field_input_output.push_back(field5);
}

//-------------------------------------------
