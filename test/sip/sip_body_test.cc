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
