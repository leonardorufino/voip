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

    if (!run<SDP_Field_Protocol_Version_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Field_Origin_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Field_Session_Name_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Field_Session_Information_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Field_URI_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Field_Email_Address_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Field_Phone_Number_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Field_Connection_Data_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Field_Bandwidth_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Field_Timing_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Field_Repeat_Time_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Field_Time_Zone_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Field_Encryption_Key_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Field_Attribute_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Field_Media_Description_Decode_Encode_Test>())
        return false;


    if (!run<SDP_Field_Protocol_Version_Query_Test>())
        return false;

    if (!run<SDP_Field_Origin_Query_Test>())
        return false;

    if (!run<SDP_Field_Session_Name_Query_Test>())
        return false;

    if (!run<SDP_Field_Session_Information_Query_Test>())
        return false;

    if (!run<SDP_Field_URI_Query_Test>())
        return false;

    if (!run<SDP_Field_Email_Address_Query_Test>())
        return false;

    if (!run<SDP_Field_Phone_Number_Query_Test>())
        return false;

    if (!run<SDP_Field_Connection_Data_Query_Test>())
        return false;

    if (!run<SDP_Field_Bandwidth_Query_Test>())
        return false;

    if (!run<SDP_Field_Timing_Query_Test>())
        return false;

    if (!run<SDP_Field_Repeat_Time_Query_Test>())
        return false;

    if (!run<SDP_Field_Time_Zone_Query_Test>())
        return false;

    if (!run<SDP_Field_Encryption_Key_Query_Test>())
        return false;

    if (!run<SDP_Field_Attribute_Query_Test>())
        return false;

    if (!run<SDP_Field_Media_Description_Query_Test>())
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

bool SDP_Field_Decode_Encode_Test::run()
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
            std::cout << "SDP_Field_Decode_Encode_Test::run -> Failed to decode fields:\n";
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
            std::cout << "SDP_Field_Decode_Encode_Test::run -> Invalid size of fields:\n";
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
                std::cout << "SDP_Field_Decode_Encode_Test::run -> Invalid decoded field type:\n";
                std::cout << std::setw(12) << "Type: " << field_input_output._field_type << "\n";
                std::cout << std::setw(12) << "Input: " << field_input_output._input.c_str() << "\n";
                std::cout << std::setw(12) << "Result: " << field->get_field_type() << "\n";
                return false;
            }
        }

        sdp_field_list copy;
        if (!copy_fields(fields, copy))
        {
            std::cout << "SDP_Field_Decode_Encode_Test::run -> Failed to copy fields:\n";
            std::cout << std::setw(12) << "Type: " << field_input_output._field_type << "\n";
            std::cout << std::setw(12) << "Input: " << field_input_output._input.c_str() << "\n";
            return false;
        }

        clear(fields);

        std::string output;
        bool encode = SDP_Field::encode_fields(output, copy);

        if (field_input_output._encode_success != encode)
        {
            std::cout << "SDP_Field_Decode_Encode_Test::run -> Failed to encode fields:\n";
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
            std::cout << "SDP_Field_Decode_Encode_Test::run -> Invalid encoded field:\n";
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

bool SDP_Field_Decode_Encode_Test::copy_fields(sdp_field_list &fields, sdp_field_list &copy)
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

void SDP_Field_Decode_Encode_Test::clear(sdp_field_list &fields)
{
    sdp_field_list::const_iterator it = fields.begin();
    while (it != fields.end())
        delete *it++;

    fields.clear();
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Field_Query_Test::run()
{
    SDP_Field *field = SDP_Field::create_field(_field_type);
    if (!field)
    {
        std::cout << "SDP_Field_Query_Test::run -> create field failed:\n";
        std::cout << std::setw(12) << "Type: " << _field_type << "\n";
        return false;
    }

    std::list<SDP_Field_Query>::const_iterator it = _field_query.begin();
    while (it != _field_query.end())
    {
        SDP_Field_Query field_query = *it++;

        std::cout << "SDP field query test initialized (type: " << _field_type << ")\n";

        std::string result;
        bool success = field->query(field_query._cmd, field_query._query, result);

        if (field_query._success != success)
        {
            std::cout << "SDP_Field_Query_Test::run -> Query failed:\n";
            std::cout << std::setw(12) << "Type: " << _field_type << "\n";
            std::cout << std::setw(12) << "Cmd: " << field_query._cmd << "\n";
            std::cout << std::setw(12) << "Query: " << field_query._query.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << (field_query._success ? "true" : "false") << "\n";
            std::cout << std::setw(12) << "Success: " << (success ? "true" : "false") << "\n";
            delete field;
            return false;
        }

        if ((!field_query._expected_result.empty()) && (result != field_query._expected_result))
        {
            std::cout << "SDP_Field_Query_Test::run -> Query result failed:\n";
            std::cout << std::setw(12) << "Type: " << _field_type << "\n";
            std::cout << std::setw(12) << "Cmd: " << field_query._cmd << "\n";
            std::cout << std::setw(12) << "Query: " << field_query._query.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << field_query._expected_result.c_str() << "\n";
            std::cout << std::setw(12) << "Result: " << result.c_str() << "\n";
            delete field;
            return false;
        }

        std::cout << "SDP field query test completed successfully (type: " << _field_type << ")\n";
    }

    delete field;
    return true;
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Protocol_Version_Decode_Encode_Test::SDP_Field_Protocol_Version_Decode_Encode_Test()
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

SDP_Field_Protocol_Version_Query_Test::SDP_Field_Protocol_Version_Query_Test() : SDP_Field_Query_Test(SDP_FIELD_PROTOCOL_VERSION)
{
    _field_query.emplace_back(QUERY_SET, "Version.0", "", true);
    _field_query.emplace_back(QUERY_GET, "Version", "0", true);
    _field_query.emplace_back(QUERY_SET, "Version.9999", "", true);
    _field_query.emplace_back(QUERY_GET, "Version", "9999", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Origin_Decode_Encode_Test::SDP_Field_Origin_Decode_Encode_Test()
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

SDP_Field_Origin_Query_Test::SDP_Field_Origin_Query_Test() : SDP_Field_Query_Test(SDP_FIELD_ORIGIN)
{
    _field_query.emplace_back(QUERY_SET, "Username.-", "", true);
    _field_query.emplace_back(QUERY_GET, "Username", "-", true);
    _field_query.emplace_back(QUERY_SET, "Username.jdoe", "", true);
    _field_query.emplace_back(QUERY_GET, "Username", "jdoe", true);
    _field_query.emplace_back(QUERY_SET, "Session-ID.0", "", true);
    _field_query.emplace_back(QUERY_GET, "Session-ID", "0", true);
    _field_query.emplace_back(QUERY_SET, "Session-ID.2890844526", "", true);
    _field_query.emplace_back(QUERY_GET, "Session-ID", "2890844526", true);
    _field_query.emplace_back(QUERY_SET, "Session-Version.0", "", true);
    _field_query.emplace_back(QUERY_GET, "Session-Version", "0", true);
    _field_query.emplace_back(QUERY_SET, "Session-Version.11223344556677889900", "", true);
    _field_query.emplace_back(QUERY_GET, "Session-Version", "11223344556677889900", true);
    _field_query.emplace_back(QUERY_SET, "Network-Type.IN", "", true);
    _field_query.emplace_back(QUERY_GET, "Network-Type", "IN", true);
    _field_query.emplace_back(QUERY_SET, "Network-Type.TEST", "", true);
    _field_query.emplace_back(QUERY_GET, "Network-Type", "TEST", true);
    _field_query.emplace_back(QUERY_SET, "Address-Type.IP4", "", true);
    _field_query.emplace_back(QUERY_GET, "Address-Type", "IP4", true);
    _field_query.emplace_back(QUERY_SET, "Address-Type.IP6", "", true);
    _field_query.emplace_back(QUERY_GET, "Address-Type", "IP6", true);
    _field_query.emplace_back(QUERY_SET, "Unicast-Address.10.47.16.5", "", true);
    _field_query.emplace_back(QUERY_GET, "Unicast-Address", "10.47.16.5", true);
    _field_query.emplace_back(QUERY_SET, "Unicast-Address.domain.com", "", true);
    _field_query.emplace_back(QUERY_GET, "Unicast-Address", "domain.com", true);
    _field_query.emplace_back(QUERY_SET, "Unicast-Address.2200:05FF::1111:2222:EEFC", "", true);
    _field_query.emplace_back(QUERY_GET, "Unicast-Address", "2200:05FF::1111:2222:EEFC", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Session_Name_Decode_Encode_Test::SDP_Field_Session_Name_Decode_Encode_Test()
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

SDP_Field_Session_Name_Query_Test::SDP_Field_Session_Name_Query_Test() : SDP_Field_Query_Test(SDP_FIELD_SESSION_NAME)
{
    _field_query.emplace_back(QUERY_SET, "Session-Name.This is a session name", "", true);
    _field_query.emplace_back(QUERY_GET, "Session-Name", "This is a session name", true);
    _field_query.emplace_back(QUERY_SET, "Session-Name. ", "", true);
    _field_query.emplace_back(QUERY_GET, "Session-Name", " ", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Session_Information_Decode_Encode_Test::SDP_Field_Session_Information_Decode_Encode_Test()
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

SDP_Field_Session_Information_Query_Test::SDP_Field_Session_Information_Query_Test() : SDP_Field_Query_Test(SDP_FIELD_SESSION_INFORMATION)
{
    _field_query.emplace_back(QUERY_SET, "Session-Information.A Seminar on the session description protocol", "", true);
    _field_query.emplace_back(QUERY_GET, "Session-Information", "A Seminar on the session description protocol", true);
    _field_query.emplace_back(QUERY_SET, "Session-Information.", "", true);
    _field_query.emplace_back(QUERY_GET, "Session-Information", "", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_URI_Decode_Encode_Test::SDP_Field_URI_Decode_Encode_Test()
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

SDP_Field_URI_Query_Test::SDP_Field_URI_Query_Test() : SDP_Field_Query_Test(SDP_FIELD_URI)
{
    _field_query.emplace_back(QUERY_SET, "URI.http://www.example.com/seminars/sdp.pdf", "", true);
    _field_query.emplace_back(QUERY_GET, "URI", "http://www.example.com/seminars/sdp.pdf", true);
    _field_query.emplace_back(QUERY_SET, "URI.", "", true);
    _field_query.emplace_back(QUERY_GET, "URI", "", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Email_Address_Decode_Encode_Test::SDP_Field_Email_Address_Decode_Encode_Test()
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

SDP_Field_Email_Address_Query_Test::SDP_Field_Email_Address_Query_Test() : SDP_Field_Query_Test(SDP_FIELD_EMAIL_ADDRESS)
{
    _field_query.emplace_back(QUERY_SET, "Email.j.doe@example.com (Jane Doe)", "", true);
    _field_query.emplace_back(QUERY_GET, "Email", "j.doe@example.com (Jane Doe)", true);
    _field_query.emplace_back(QUERY_SET, "Email.Jane Doe <j.doe@example.com>", "", true);
    _field_query.emplace_back(QUERY_GET, "Email", "Jane Doe <j.doe@example.com>", true);
    _field_query.emplace_back(QUERY_SET, "Email.test@domain.com", "", true);
    _field_query.emplace_back(QUERY_GET, "Email", "test@domain.com", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Phone_Number_Decode_Encode_Test::SDP_Field_Phone_Number_Decode_Encode_Test()
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

SDP_Field_Phone_Number_Query_Test::SDP_Field_Phone_Number_Query_Test() : SDP_Field_Query_Test(SDP_FIELD_PHONE_NUMBER)
{
    _field_query.emplace_back(QUERY_SET, "Phone.+1 617 555-6011", "", true);
    _field_query.emplace_back(QUERY_GET, "Phone", "+1 617 555-6011", true);
    _field_query.emplace_back(QUERY_SET, "Phone.9876543210 (Jane Doe)", "", true);
    _field_query.emplace_back(QUERY_GET, "Phone", "9876543210 (Jane Doe)", true);
    _field_query.emplace_back(QUERY_SET, "Phone.Jane Doe <+1 234 567-8900>", "", true);
    _field_query.emplace_back(QUERY_GET, "Phone", "Jane Doe <+1 234 567-8900>", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Connection_Data_Decode_Encode_Test::SDP_Field_Connection_Data_Decode_Encode_Test()
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

SDP_Field_Connection_Data_Query_Test::SDP_Field_Connection_Data_Query_Test() : SDP_Field_Query_Test(SDP_FIELD_CONNECTION_DATA)
{
    _field_query.emplace_back(QUERY_SET, "Network-Type.IN", "", true);
    _field_query.emplace_back(QUERY_GET, "Network-Type", "IN", true);
    _field_query.emplace_back(QUERY_SET, "Network-Type.TEST", "", true);
    _field_query.emplace_back(QUERY_GET, "Network-Type", "TEST", true);
    _field_query.emplace_back(QUERY_SET, "Address-Type.IP4", "", true);
    _field_query.emplace_back(QUERY_GET, "Address-Type", "IP4", true);
    _field_query.emplace_back(QUERY_SET, "Address-Type.IP6", "", true);
    _field_query.emplace_back(QUERY_GET, "Address-Type", "IP6", true);
    _field_query.emplace_back(QUERY_SET, "Connection-Address.224.2.1.3", "", true);
    _field_query.emplace_back(QUERY_GET, "Connection-Address", "224.2.1.3", true);
    _field_query.emplace_back(QUERY_SET, "Connection-Address.FF15::101", "", true);
    _field_query.emplace_back(QUERY_GET, "Connection-Address", "FF15::101", true);
    _field_query.emplace_back(QUERY_SET, "TTL.127", "", true);
    _field_query.emplace_back(QUERY_GET, "TTL", "127", true);
    _field_query.emplace_back(QUERY_SET, "TTL.1", "", true);
    _field_query.emplace_back(QUERY_GET, "TTL", "1", true);
    _field_query.emplace_back(QUERY_SET, "Number-Addresses.3", "", true);
    _field_query.emplace_back(QUERY_GET, "Number-Addresses", "3", true);
    _field_query.emplace_back(QUERY_SET, "Number-Addresses.10", "", true);
    _field_query.emplace_back(QUERY_GET, "Number-Addresses", "10", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Bandwidth_Decode_Encode_Test::SDP_Field_Bandwidth_Decode_Encode_Test()
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

SDP_Field_Bandwidth_Query_Test::SDP_Field_Bandwidth_Query_Test() : SDP_Field_Query_Test(SDP_FIELD_BANDWIDTH)
{
    _field_query.emplace_back(QUERY_SET, "Type.CT", "", true);
    _field_query.emplace_back(QUERY_GET, "Type", "CT", true);
    _field_query.emplace_back(QUERY_SET, "Type.X-YZ", "", true);
    _field_query.emplace_back(QUERY_GET, "Type", "X-YZ", true);
    _field_query.emplace_back(QUERY_SET, "Bandwidth.64", "", true);
    _field_query.emplace_back(QUERY_GET, "Bandwidth", "64", true);
    _field_query.emplace_back(QUERY_SET, "Bandwidth.9999999", "", true);
    _field_query.emplace_back(QUERY_GET, "Bandwidth", "9999999", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Timing_Decode_Encode_Test::SDP_Field_Timing_Decode_Encode_Test()
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

SDP_Field_Timing_Query_Test::SDP_Field_Timing_Query_Test() : SDP_Field_Query_Test(SDP_FIELD_TIMING)
{
    _field_query.emplace_back(QUERY_SET, "Start.2873397496", "", true);
    _field_query.emplace_back(QUERY_GET, "Start", "2873397496", true);
    _field_query.emplace_back(QUERY_SET, "Start.0", "", true);
    _field_query.emplace_back(QUERY_GET, "Start", "0", true);
    _field_query.emplace_back(QUERY_SET, "Stop.9999999999", "", true);
    _field_query.emplace_back(QUERY_GET, "Stop", "9999999999", true);
    _field_query.emplace_back(QUERY_SET, "Stop.0", "", true);
    _field_query.emplace_back(QUERY_GET, "Stop", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Repeat_Time_Decode_Encode_Test::SDP_Field_Repeat_Time_Decode_Encode_Test()
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

SDP_Field_Repeat_Time_Query_Test::SDP_Field_Repeat_Time_Query_Test() : SDP_Field_Query_Test(SDP_FIELD_REPEAT_TIME)
{
    _field_query.emplace_back(QUERY_SET, "Interval.604800", "", true);
    _field_query.emplace_back(QUERY_GET, "Interval", "604800", true);
    _field_query.emplace_back(QUERY_SET, "Interval.7d", "", true);
    _field_query.emplace_back(QUERY_GET, "Interval", "7d", true);
    _field_query.emplace_back(QUERY_SET, "Duration.3600", "", true);
    _field_query.emplace_back(QUERY_GET, "Duration", "3600", true);
    _field_query.emplace_back(QUERY_SET, "Duration.1h", "", true);
    _field_query.emplace_back(QUERY_GET, "Duration", "1h", true);
    _field_query.emplace_back(QUERY_ADD, "Offsets.0.0", "", true);
    _field_query.emplace_back(QUERY_GET, "Offsets.Size", "1", true);
    _field_query.emplace_back(QUERY_GET, "Offsets.0", "0", true);
    _field_query.emplace_back(QUERY_ADD, "Offsets.1.90000", "", true);
    _field_query.emplace_back(QUERY_GET, "Offsets.Size", "2", true);
    _field_query.emplace_back(QUERY_GET, "Offsets.1", "90000", true);
    _field_query.emplace_back(QUERY_DEL, "Offsets.0", "", true);
    _field_query.emplace_back(QUERY_GET, "Offsets.Size", "1", true);
    _field_query.emplace_back(QUERY_GET, "Offsets.0", "90000", true);
    _field_query.emplace_back(QUERY_DEL, "Offsets.0", "", true);
    _field_query.emplace_back(QUERY_GET, "Offsets.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Time_Zone_Decode_Encode_Test::SDP_Field_Time_Zone_Decode_Encode_Test()
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

SDP_Field_Time_Zone_Query_Test::SDP_Field_Time_Zone_Query_Test() : SDP_Field_Query_Test(SDP_FIELD_TIME_ZONE)
{
    _field_query.emplace_back(QUERY_ADD, "Adjustments.0.2882844526", "", true);
    _field_query.emplace_back(QUERY_GET, "Adjustments.Size", "1", true);
    _field_query.emplace_back(QUERY_GET, "Adjustments.0", "2882844526", true);
    _field_query.emplace_back(QUERY_ADD, "Adjustments.1.999999999", "", true);
    _field_query.emplace_back(QUERY_GET, "Adjustments.Size", "2", true);
    _field_query.emplace_back(QUERY_GET, "Adjustments.1", "999999999", true);
    _field_query.emplace_back(QUERY_DEL, "Adjustments.1", "", true);
    _field_query.emplace_back(QUERY_GET, "Adjustments.Size", "1", true);
    _field_query.emplace_back(QUERY_GET, "Adjustments.0", "2882844526", true);
    _field_query.emplace_back(QUERY_DEL, "Adjustments.0", "", true);
    _field_query.emplace_back(QUERY_GET, "Adjustments.Size", "0", true);
    _field_query.emplace_back(QUERY_ADD, "Offsets.0.-1h", "", true);
    _field_query.emplace_back(QUERY_GET, "Offsets.Size", "1", true);
    _field_query.emplace_back(QUERY_GET, "Offsets.0", "-1h", true);
    _field_query.emplace_back(QUERY_ADD, "Offsets.1.9", "", true);
    _field_query.emplace_back(QUERY_GET, "Offsets.Size", "2", true);
    _field_query.emplace_back(QUERY_GET, "Offsets.1", "9", true);
    _field_query.emplace_back(QUERY_DEL, "Offsets.0", "", true);
    _field_query.emplace_back(QUERY_GET, "Offsets.Size", "1", true);
    _field_query.emplace_back(QUERY_GET, "Offsets.0", "9", true);
    _field_query.emplace_back(QUERY_DEL, "Offsets.0", "", true);
    _field_query.emplace_back(QUERY_GET, "Offsets.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Encryption_Key_Decode_Encode_Test::SDP_Field_Encryption_Key_Decode_Encode_Test()
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

SDP_Field_Encryption_Key_Query_Test::SDP_Field_Encryption_Key_Query_Test() : SDP_Field_Query_Test(SDP_FIELD_ENCRYPTION_KEY)
{
    _field_query.emplace_back(QUERY_SET, "Method.clear", "", true);
    _field_query.emplace_back(QUERY_GET, "Method", "clear", true);
    _field_query.emplace_back(QUERY_SET, "Method.base64", "", true);
    _field_query.emplace_back(QUERY_GET, "Method", "base64", true);
    _field_query.emplace_back(QUERY_SET, "Key.password", "", true);
    _field_query.emplace_back(QUERY_GET, "Key", "password", true);
    _field_query.emplace_back(QUERY_SET, "Key.cGFzc3dvcmQ=", "", true);
    _field_query.emplace_back(QUERY_GET, "Key", "cGFzc3dvcmQ=", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Attribute_Decode_Encode_Test::SDP_Field_Attribute_Decode_Encode_Test()
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
//-------------------------------------------

SDP_Field_Attribute_Query_Test::SDP_Field_Attribute_Query_Test() : SDP_Field_Query_Test(SDP_FIELD_ATTRIBUTE)
{
    _field_query.emplace_back(QUERY_SET, "Attribute.recvonly", "", true);
    _field_query.emplace_back(QUERY_GET, "Attribute", "recvonly", true);
    _field_query.emplace_back(QUERY_SET, "Attribute.rtpmap", "", true);
    _field_query.emplace_back(QUERY_GET, "Attribute", "rtpmap", true);
    _field_query.emplace_back(QUERY_SET, "Value.99 h263-1998/90000", "", true);
    _field_query.emplace_back(QUERY_GET, "Value", "99 h263-1998/90000", true);
    _field_query.emplace_back(QUERY_SET, "Value.", "", true);
    _field_query.emplace_back(QUERY_GET, "Value", "", true);
    _field_query.emplace_back(QUERY_SET, "Value.ISO-8859-1", "", true);
    _field_query.emplace_back(QUERY_GET, "Value", "ISO-8859-1", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Media_Description_Decode_Encode_Test::SDP_Field_Media_Description_Decode_Encode_Test()
{
    SDP_Field_Input_Output field1;
    field1._field_type     = SDP_FIELD_MEDIA_DESCRIPTION;
    field1._input          = "m=video 49170/2 RTP/AVP 31";
    field1._output         = "m=video 49170/2 RTP/AVP 31\r\n";
    field1._field_nb       = 1;
    field1._decode_success = true;
    field1._encode_success = true;
    _field_input_output.push_back(field1);

    SDP_Field_Input_Output field2;
    field2._field_type     = SDP_FIELD_MEDIA_DESCRIPTION;
    field2._input          = "m=audio 65500 RTP/AVP 0";
    field2._output         = "m=audio 65500 RTP/AVP 0\r\n";
    field2._field_nb       = 1;
    field2._decode_success = true;
    field2._encode_success = true;
    _field_input_output.push_back(field2);

    SDP_Field_Input_Output field3;
    field3._field_type     = SDP_FIELD_MEDIA_DESCRIPTION;
    field3._input          = "m=video 51372 RTP/SAVP 99 100";
    field3._output         = "m=video 51372 RTP/SAVP 99 100\r\n";
    field3._field_nb       = 1;
    field3._decode_success = true;
    field3._encode_success = true;
    _field_input_output.push_back(field3);

    SDP_Field_Input_Output field4;
    field4._field_type     = SDP_FIELD_MEDIA_DESCRIPTION;
    field4._input          = "m=audio 49230 RTP/AVP 96 97 98";
    field4._output         = "m=audio 49230 RTP/AVP 96 97 98\r\n";
    field4._field_nb       = 1;
    field4._decode_success = true;
    field4._encode_success = true;
    _field_input_output.push_back(field4);

    SDP_Field_Input_Output field5;
    field5._field_type     = SDP_FIELD_MEDIA_DESCRIPTION;
    field5._input          = "m=audio 10000 udp 0";
    field5._output         = "m=audio 10000 udp 0\r\n";
    field5._field_nb       = 1;
    field5._decode_success = true;
    field5._encode_success = true;
    _field_input_output.push_back(field5);
}

//-------------------------------------------
//-------------------------------------------

SDP_Field_Media_Description_Query_Test::SDP_Field_Media_Description_Query_Test() : SDP_Field_Query_Test(SDP_FIELD_MEDIA_DESCRIPTION)
{
    _field_query.emplace_back(QUERY_SET, "Media.audio", "", true);
    _field_query.emplace_back(QUERY_GET, "Media", "audio", true);
    _field_query.emplace_back(QUERY_SET, "Media.video", "", true);
    _field_query.emplace_back(QUERY_GET, "Media", "video", true);
    _field_query.emplace_back(QUERY_SET, "Port.10000", "", true);
    _field_query.emplace_back(QUERY_GET, "Port", "10000", true);
    _field_query.emplace_back(QUERY_SET, "Port.65000", "", true);
    _field_query.emplace_back(QUERY_GET, "Port", "65000", true);
    _field_query.emplace_back(QUERY_SET, "Number-Ports.2", "", true);
    _field_query.emplace_back(QUERY_GET, "Number-Ports", "2", true);
    _field_query.emplace_back(QUERY_SET, "Number-Ports.0", "", true);
    _field_query.emplace_back(QUERY_GET, "Number-Ports", "0", true);
    _field_query.emplace_back(QUERY_SET, "Protocol.RTP/AVP", "", true);
    _field_query.emplace_back(QUERY_GET, "Protocol", "RTP/AVP", true);
    _field_query.emplace_back(QUERY_SET, "Protocol.udp", "", true);
    _field_query.emplace_back(QUERY_GET, "Protocol", "udp", true);
    _field_query.emplace_back(QUERY_ADD, "Formats.0.0", "", true);
    _field_query.emplace_back(QUERY_GET, "Formats.Size", "1", true);
    _field_query.emplace_back(QUERY_GET, "Formats.0", "0", true);
    _field_query.emplace_back(QUERY_ADD, "Formats.1.101", "", true);
    _field_query.emplace_back(QUERY_GET, "Formats.Size", "2", true);
    _field_query.emplace_back(QUERY_GET, "Formats.1", "101", true);
    _field_query.emplace_back(QUERY_DEL, "Formats.0", "", true);
    _field_query.emplace_back(QUERY_GET, "Formats.Size", "1", true);
    _field_query.emplace_back(QUERY_GET, "Formats.0", "101", true);
    _field_query.emplace_back(QUERY_DEL, "Formats.0", "", true);
    _field_query.emplace_back(QUERY_GET, "Formats.Size", "0", true);
}

//-------------------------------------------
