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

#include "sip_body_test.h"

//-------------------------------------------

bool SIP_Body_Test::init()
{
    std::cout << "SIP body test initialized\n";

    if (!run<SIP_Body_Decode_Encode_Test>())
        return false;

    if (!run<SIP_Body_Query_Test>())
        return false;

    std::cout << "SIP body test completed successfully\n";
    return true;
}

//-------------------------------------------

template<class T> bool SIP_Body_Test::run()
{
    T test;
    if (!test.run())
        return false;
    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Body_Decode_Encode_Test::SIP_Body_Decode_Encode_Test()
{
    SIP_Body_Input_Output body1;
    body1._body_type = SIP_BODY_UNKNOWN;
    body1._size = 512;

    for (unsigned short i = 0; i < body1._size; i++)
        body1._body[i] = (char) (i & 0xFF);

    _body_input_output.push_back(body1);
}

//-------------------------------------------

bool SIP_Body_Decode_Encode_Test::run()
{
    std::list<SIP_Body_Input_Output>::const_iterator it = _body_input_output.begin();
    while (it != _body_input_output.end())
    {
        SIP_Body_Input_Output body_input_output = *it++;

        std::cout << "SIP body decode encode test initialized (type: " << body_input_output._body_type << ")\n";

        SIP_Body *sip_body = SIP_Body::create_body(body_input_output._body_type);
        if (!sip_body)
        {
            std::cout << "SIP_Body_Decode_Encode_Test::run -> Failed to create body:\n";
            std::cout << std::setw(12) << "Type: " << body_input_output._body_type << "\n";
            return false;
        }

        if (!sip_body->decode(body_input_output._body, body_input_output._size))
        {
            std::cout << "SIP_Body_Decode_Encode_Test::run -> Failed to decode body:\n";
            std::cout << std::setw(12) << "Type: " << body_input_output._body_type << "\n";
            std::cout << std::setw(12) << "Size: " << body_input_output._size << "\n";
            delete sip_body;
            return false;
        }

        SIP_Body *copy = SIP_Body::create_body(sip_body->get_body_type(), sip_body);
        if (!copy)
        {
            std::cout << "SIP_Body_Decode_Encode_Test::run -> Failed to copy body:\n";
            std::cout << std::setw(12) << "Type: " << body_input_output._body_type << "\n";
            delete sip_body;
            return false;
        }

        delete sip_body;
        sip_body = NULL;

        char output[MAX_BODY_SIZE] = {0};
        unsigned short size = sizeof(output);

        if (!copy->encode(output, size))
        {
            std::cout << "SIP_Body_Decode_Encode_Test::run -> Failed to encode body:\n";
            std::cout << std::setw(12) << "Type: " << body_input_output._body_type << "\n";
            delete copy;
            return false;
        }

        if ((size != body_input_output._size) || (memcmp(output, body_input_output._body, size) != 0))
        {
            std::cout << "SIP_Body_Decode_Encode_Test::run -> Invalid encoded body:\n";
            std::cout << std::setw(12) << "Type: " << body_input_output._body_type << "\n";
            std::cout << std::setw(15) << "Packet Size: " << body_input_output._size << "\n";
            std::cout << std::setw(15) << "Size: " << size << "\n";
            delete copy;
            return false;
        }

        delete copy;
        copy = NULL;

        std::cout << "SIP body decode encode test completed successfully (type: " << body_input_output._body_type << ")\n";
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Body_Query_Test::SIP_Body_Query_Test() : _body_type(SIP_BODY_UNKNOWN)
{
    _body_query.emplace_back(QUERY_GET, "Body.", "", true);
    _body_query.emplace_back(QUERY_SET, "Body.00010210111220213031404150516061707180819091a0aab1bbc0c5cfd0d9dfeeeff0f1faff", "", true);
    _body_query.emplace_back(QUERY_GET, "Body", "00010210111220213031404150516061707180819091a0aab1bbc0c5cfd0d9dfeeeff0f1faff", true);
    _body_query.emplace_back(QUERY_SET, "Body.414243303132", "", true);
    _body_query.emplace_back(QUERY_GET, "Body", "414243303132", true);
    _body_query.emplace_back(QUERY_SET, "Body.", "", true);
    _body_query.emplace_back(QUERY_GET, "Body", "", true);
}

//-------------------------------------------

bool SIP_Body_Query_Test::run()
{
    SIP_Body *body = SIP_Body::create_body(_body_type);
    if (!body)
    {
        std::cout << "SIP_Body_Query_Test::run -> create body failed:\n";
        std::cout << std::setw(12) << "Type: " << _body_type << "\n";
        return false;
    }

    std::list<SIP_Body_Query>::const_iterator it = _body_query.begin();
    while (it != _body_query.end())
    {
        SIP_Body_Query body_query = *it++;

        std::cout << "SIP body query test initialized (type: " << _body_type << ")\n";

        std::string result;
        bool success = body->query(body_query._cmd, body_query._query, result);

        if (body_query._success != success)
        {
            std::cout << "SIP_Body_Query_Test::run -> Query failed:\n";
            std::cout << std::setw(12) << "Type: " << _body_type << "\n";
            std::cout << std::setw(12) << "Cmd: " << body_query._cmd << "\n";
            std::cout << std::setw(12) << "Query: " << body_query._query.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << (body_query._success ? "true" : "false") << "\n";
            std::cout << std::setw(12) << "Success: " << (success ? "true" : "false") << "\n";
            return false;
        }

        if ((!body_query._expected_result.empty()) && (result != body_query._expected_result))
        {
            std::cout << "SIP_Body_Query_Test::run -> Query result failed:\n";
            std::cout << std::setw(12) << "Type: " << _body_type << "\n";
            std::cout << std::setw(12) << "Cmd: " << body_query._cmd << "\n";
            std::cout << std::setw(12) << "Query: " << body_query._query.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << body_query._expected_result.c_str() << "\n";
            std::cout << std::setw(12) << "Result: " << result.c_str() << "\n";
            return false;
        }

        std::cout << "SIP body query test completed successfully (type: " << _body_type << ")\n";
    }

    return true;
}

//-------------------------------------------
