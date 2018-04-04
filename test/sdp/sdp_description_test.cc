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

#include "sdp_description_test.h"
#include <iostream>

//-------------------------------------------

bool SDP_Description_Test::init()
{
    std::cout << "SDP description test initialized\n";

    if (!run<SDP_Description_Session_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Description_Media_Decode_Encode_Test>())
        return false;

    if (!run<SDP_Description_Complete_Decode_Encode_Test>())
        return false;


    if (!run<SDP_Description_Session_Query_Test>())
        return false;

    if (!run<SDP_Description_Media_Query_Test>())
        return false;

    std::cout << "SDP description test completed successfully\n";
    return true;
}

//-------------------------------------------

template<class T> bool SDP_Description_Test::run()
{
    T test;
    if (!test.run())
        return false;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Description_Decode_Encode_Test::run()
{
    std::list<SDP_Description_Input_Output>::const_iterator it = _description_input_output.begin();
    while (it != _description_input_output.end())
    {
        SDP_Description_Input_Output description_input_output = *it++;

        if (!execute(description_input_output))
            return false;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool SDP_Description_Query_Test::run()
{
    SDP_Description description;

    std::list<SDP_Description_Query>::const_iterator it = _description_query.begin();
    while (it != _description_query.end())
    {
        SDP_Description_Query description_query = *it++;

        std::cout << "SDP description query test initialized\n";

        std::string result;
        bool success = description.query_body(description_query._cmd, description_query._query, result);

        if (description_query._success != success)
        {
            std::cout << "SDP_Description_Query_Test::run -> Query failed:\n";
            std::cout << std::setw(12) << "Cmd: " << description_query._cmd << "\n";
            std::cout << std::setw(12) << "Query: " << description_query._query.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << (description_query._success ? "true" : "false") << "\n";
            std::cout << std::setw(12) << "Success: " << (success ? "true" : "false") << "\n";
            return false;
        }

        if ((!description_query._expected_result.empty()) && (result != description_query._expected_result))
        {
            std::cout << "SDP_Description_Query_Test::run -> Query result failed:\n";
            std::cout << std::setw(12) << "Cmd: " << description_query._cmd << "\n";
            std::cout << std::setw(12) << "Query: " << description_query._query.c_str() << "\n";
            std::cout << std::setw(12) << "Expected: " << description_query._expected_result.c_str() << "\n";
            std::cout << std::setw(12) << "Result: " << result.c_str() << "\n";
            return false;
        }

        std::cout << "SDP description query test completed successfully\n";
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

SDP_Description_Session_Decode_Encode_Test::SDP_Description_Session_Decode_Encode_Test()
{
    SDP_Description_Input_Output msg1;

    msg1._input   = "v=0\r\n";
    msg1._input  += "o=jdoe 2890844526 2890842807 IN IP4 10.47.16.5\r\n";
    msg1._input  += "s=SDP Seminar\r\n";
    msg1._input  += "i=A Seminar on the session description protocol\r\n";
    msg1._input  += "u=http://www.example.com/seminars/sdp.pdf\r\n";
    msg1._input  += "e=j.doe@example.com (Jane Doe)\r\n";
    msg1._input  += "c=IN IP4 224.2.17.12/127\r\n";
    msg1._input  += "t=2873397496 2873404696\r\n";
    msg1._input  += "a=recvonly\r\n";

    msg1._output  = "v=0\r\n";
    msg1._output += "o=jdoe 2890844526 2890842807 IN IP4 10.47.16.5\r\n";
    msg1._output += "s=SDP Seminar\r\n";
    msg1._output += "i=A Seminar on the session description protocol\r\n";
    msg1._output += "u=http://www.example.com/seminars/sdp.pdf\r\n";
    msg1._output += "e=j.doe@example.com (Jane Doe)\r\n";
    msg1._output += "c=IN IP4 224.2.17.12/127\r\n";
    msg1._output += "t=2873397496 2873404696\r\n";
    msg1._output += "a=recvonly\r\n";

    _description_input_output.push_back(msg1);


    SDP_Description_Input_Output msg2;

    msg2._input   = "v=0\r\n";
    msg2._input  += "o=UserA 2890844526 2890844526 IN IP4 here.com\r\n";
    msg2._input  += "s=Session SDP\r\n";
    msg2._input  += "c=IN IP4 pc33.atlanta.com\r\n";
    msg2._input  += "t=0 0\r\n";

    msg2._output  = "v=0\r\n";
    msg2._output += "o=UserA 2890844526 2890844526 IN IP4 here.com\r\n";
    msg2._output += "s=Session SDP\r\n";
    msg2._output += "c=IN IP4 pc33.atlanta.com\r\n";
    msg2._output += "t=0 0\r\n";

    _description_input_output.push_back(msg2);


    SDP_Description_Input_Output msg3;

    msg3._input   = "v=0\r\n";
    msg3._input  += "o=alice 53655765 2353687637 IN IP4 pc33.atlanta.com\r\n";
    msg3._input  += "s=Session Test\r\n";
    msg3._input  += "p=+1 617 555-6011\r\n";
    msg3._input  += "c=IN IP6 FF15::101\r\n";
    msg3._input  += "c=IN IP6 FF15::102\r\n";
    msg3._input  += "c=IN IP6 FF15::103\r\n";
    msg3._input  += "b=X-YZ:128\r\n";
    msg3._input  += "t=3034423619 3042462419\r\n";
    msg3._input  += "r=604800 3600 0 90000\r\n";
    msg3._input  += "z=2882844526 -1h 2898848070 0\r\n";
    msg3._input  += "k=clear:password\r\n";
    msg3._input  += "a=sendonly\r\n";
    msg3._input  += "a=tool:Software 1.0\r\n";

    msg3._output  = "v=0\r\n";
    msg3._output += "o=alice 53655765 2353687637 IN IP4 pc33.atlanta.com\r\n";
    msg3._output += "s=Session Test\r\n";
    msg3._output += "p=+1 617 555-6011\r\n";
    msg3._output += "c=IN IP6 FF15::101\r\n";
    msg3._output += "c=IN IP6 FF15::102\r\n";
    msg3._output += "c=IN IP6 FF15::103\r\n";
    msg3._output += "b=X-YZ:128\r\n";
    msg3._output += "t=3034423619 3042462419\r\n";
    msg3._output += "r=604800 3600 0 90000\r\n";
    msg3._output += "z=2882844526 -1h 2898848070 0\r\n";
    msg3._output += "k=clear:password\r\n";
    msg3._output += "a=sendonly\r\n";
    msg3._output += "a=tool:Software 1.0\r\n";

    _description_input_output.push_back(msg3);
}

//-------------------------------------------

bool SDP_Description_Session_Decode_Encode_Test::execute(SDP_Description_Input_Output &description_input_output)
{
    std::cout << "SDP description session decode encode test initialized\n";

    std::string input = description_input_output._input;

    SDP_Description_Session *description = new SDP_Description_Session();
    if (!description->decode(input))
    {
        std::cout << "SDP_Description_Session_Decode_Encode_Test::execute -> Failed to decode description:\n";
        std::cout << std::setw(12) << "Input: " << description_input_output._input.c_str() << "\n";
        delete description;
        return false;
    }

    SDP_Description_Session *copy = new SDP_Description_Session(*description);
    delete description;
    description = NULL;

    std::string output;

    if (!copy->encode(output))
    {
        std::cout << "SDP_Description_Session_Decode_Encode_Test::execute -> Failed to encode description:\n";
        std::cout << std::setw(12) << "Input: " << description_input_output._input.c_str() << "\n";
        delete copy;
        return false;
    }

    if (output != description_input_output._output)
    {
        std::cout << "SDP_Description_Session_Decode_Encode_Test::execute -> Invalid encoded description:\n";
        std::cout << std::setw(12) << "Input: " << description_input_output._input.c_str() << "\n";
        std::cout << std::setw(12) << "Expected: " << description_input_output._output.c_str() << "\n";
        std::cout << std::setw(12) << "Output: " << output.c_str() << "\n";
        delete copy;
        return false;
    }

    delete copy;
    copy = NULL;

    std::cout << "SDP description session decode encode test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

SDP_Description_Session_Query_Test::SDP_Description_Session_Query_Test()
{
    _description_query.emplace_back(QUERY_GET, "Session.Size", "0", true);
    _description_query.emplace_back(QUERY_ADD, "Session", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.Size", "1", true);
    _description_query.emplace_back(QUERY_ADD, "Session.v.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.v.Size", "1", true);
    _description_query.emplace_back(QUERY_SET, "Session.v.0.Version.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.v.0.Version", "0", true);
    _description_query.emplace_back(QUERY_DEL, "Session.v.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.v.Size", "0", true);
    _description_query.emplace_back(QUERY_ADD, "Session.o.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.o.Size", "1", true);
    _description_query.emplace_back(QUERY_SET, "Session.o.0.Username.-", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.o.0.Username", "-", true);
    _description_query.emplace_back(QUERY_SET, "Session.o.0.Session-ID.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.o.0.Session-ID", "0", true);
    _description_query.emplace_back(QUERY_SET, "Session.o.0.Session-Version.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.o.0.Session-Version", "0", true);
    _description_query.emplace_back(QUERY_SET, "Session.o.0.Network-Type.IN", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.o.0.Network-Type", "IN", true);
    _description_query.emplace_back(QUERY_SET, "Session.o.0.Address-Type.IP4", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.o.0.Address-Type", "IP4", true);
    _description_query.emplace_back(QUERY_SET, "Session.o.0.Address-Type.IP6", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.o.0.Address-Type", "IP6", true);
    _description_query.emplace_back(QUERY_SET, "Session.o.0.Unicast-Address.10.47.16.5", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.o.0.Unicast-Address", "10.47.16.5", true);
    _description_query.emplace_back(QUERY_SET, "Session.o.0.Unicast-Address.domain.com", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.o.0.Unicast-Address", "domain.com", true);
    _description_query.emplace_back(QUERY_SET, "Session.o.0.Unicast-Address.2200:05FF::1111:2222:EEFC", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.o.0.Unicast-Address", "2200:05FF::1111:2222:EEFC", true);
    _description_query.emplace_back(QUERY_DEL, "Session.o.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.o.Size", "0", true);
    _description_query.emplace_back(QUERY_DEL, "Session", "", true);
    _description_query.emplace_back(QUERY_GET, "Session.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Description_Media_Decode_Encode_Test::SDP_Description_Media_Decode_Encode_Test()
{
    SDP_Description_Input_Output msg1;

    msg1._input   = "m=video 51372 RTP/AVP 99\r\n";
    msg1._input  += "a=rtpmap:99 h263-1998/90000\r\n";

    msg1._output  = "m=video 51372 RTP/AVP 99\r\n";
    msg1._output += "a=rtpmap:99 h263-1998/90000\r\n";

    _description_input_output.push_back(msg1);


    SDP_Description_Input_Output msg2;

    msg2._input   = "m=audio 49172 RTP/AVP 0\r\n";
    msg2._input  += "a=rtpmap:0 PCMU/8000\r\n";
    msg2._input  += "a=sendrecv\r\n";

    msg2._output  = "m=audio 49172 RTP/AVP 0\r\n";
    msg2._output += "a=rtpmap:0 PCMU/8000\r\n";
    msg2._output += "a=sendrecv\r\n";

    _description_input_output.push_back(msg2);


    SDP_Description_Input_Output msg3;

    msg3._input   = "m=audio 49230 RTP/AVP 0 96 97 98\r\n";
    msg3._input  += "i=SDP media line\r\n";
    msg3._input  += "c=IN IP4 224.2.36.42/127\r\n";
    msg3._input  += "b=CT:64\r\n";
    msg3._input  += "k=uri:www.test.com\r\n";
    msg3._input  += "a=rtpmap:0 PCMU/8000\r\n";
    msg3._input  += "a=rtpmap:96 L8/8000\r\n";
    msg3._input  += "a=rtpmap:97 L16/8000\r\n";
    msg3._input  += "a=rtpmap:98 L16/11025/2\r\n";
    msg3._input  += "a=inactive\r\n";

    msg3._output  = "m=audio 49230 RTP/AVP 0 96 97 98\r\n";
    msg3._output += "i=SDP media line\r\n";
    msg3._output += "c=IN IP4 224.2.36.42/127\r\n";
    msg3._output += "b=CT:64\r\n";
    msg3._output += "k=uri:www.test.com\r\n";
    msg3._output += "a=rtpmap:0 PCMU/8000\r\n";
    msg3._output += "a=rtpmap:96 L8/8000\r\n";
    msg3._output += "a=rtpmap:97 L16/8000\r\n";
    msg3._output += "a=rtpmap:98 L16/11025/2\r\n";
    msg3._output += "a=inactive\r\n";

    _description_input_output.push_back(msg3);
}

//-------------------------------------------

bool SDP_Description_Media_Decode_Encode_Test::execute(SDP_Description_Input_Output &description_input_output)
{
    std::cout << "SDP description media decode encode test initialized\n";

    std::string input = description_input_output._input;

    SDP_Description_Media *description = new SDP_Description_Media();
    if (!description->decode(input))
    {
        std::cout << "SDP_Description_Media_Decode_Encode_Test::execute -> Failed to decode description:\n";
        std::cout << std::setw(12) << "Input: " << description_input_output._input.c_str() << "\n";
        delete description;
        return false;
    }

    SDP_Description_Media *copy = new SDP_Description_Media(*description);
    delete description;
    description = NULL;

    std::string output;

    if (!copy->encode(output))
    {
        std::cout << "SDP_Description_Media_Decode_Encode_Test::execute -> Failed to encode description:\n";
        std::cout << std::setw(12) << "Input: " << description_input_output._input.c_str() << "\n";
        delete copy;
        return false;
    }

    if (output != description_input_output._output)
    {
        std::cout << "SDP_Description_Media_Decode_Encode_Test::execute -> Invalid encoded description:\n";
        std::cout << std::setw(12) << "Input: " << description_input_output._input.c_str() << "\n";
        std::cout << std::setw(12) << "Expected: " << description_input_output._output.c_str() << "\n";
        std::cout << std::setw(12) << "Output: " << output.c_str() << "\n";
        delete copy;
        return false;
    }

    delete copy;
    copy = NULL;

    std::cout << "SDP description media decode encode test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

SDP_Description_Media_Query_Test::SDP_Description_Media_Query_Test()
{
    _description_query.emplace_back(QUERY_GET, "Media.Size", "0", true);
    _description_query.emplace_back(QUERY_ADD, "Media.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.Size", "1", true);
    _description_query.emplace_back(QUERY_ADD, "Media.0.m.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.m.Size", "1", true);
    _description_query.emplace_back(QUERY_SET, "Media.0.m.0.Media.audio", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.m.0.Media", "audio", true);
    _description_query.emplace_back(QUERY_SET, "Media.0.m.0.Port.10000", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.m.0.Port", "10000", true);
    _description_query.emplace_back(QUERY_SET, "Media.0.m.0.Number-Ports.2", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.m.0.Number-Ports", "2", true);
    _description_query.emplace_back(QUERY_SET, "Media.0.m.0.Protocol.RTP/AVP", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.m.0.Protocol", "RTP/AVP", true);
    _description_query.emplace_back(QUERY_ADD, "Media.0.m.0.Formats.0.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.m.0.Formats.Size", "1", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.m.0.Formats.0", "0", true);
    _description_query.emplace_back(QUERY_ADD, "Media.0.m.0.Formats.1.101", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.m.0.Formats.Size", "2", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.m.0.Formats.1", "101", true);
    _description_query.emplace_back(QUERY_DEL, "Media.0.m.0.Formats.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.m.0.Formats.Size", "1", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.m.0.Formats.0", "101", true);
    _description_query.emplace_back(QUERY_DEL, "Media.0.m.0.Formats.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.m.0.Formats.Size", "0", true);
    _description_query.emplace_back(QUERY_ADD, "Media.0.a.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.a.Size", "1", true);
    _description_query.emplace_back(QUERY_SET, "Media.0.a.0.Attribute.recvonly", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.a.0.Attribute", "recvonly", true);
    _description_query.emplace_back(QUERY_ADD, "Media.0.a.1", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.a.Size", "2", true);
    _description_query.emplace_back(QUERY_SET, "Media.0.a.1.Attribute.rtpmap", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.a.1.Attribute", "rtpmap", true);
    _description_query.emplace_back(QUERY_SET, "Media.0.a.1.Value.0 PCMU/8000", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.a.1.Value", "0 PCMU/8000", true);
    _description_query.emplace_back(QUERY_DEL, "Media.0.a.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.a.Size", "1", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.a.0.Attribute", "rtpmap", true);
    _description_query.emplace_back(QUERY_DEL, "Media.0.a.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.a.Size", "0", true);
    _description_query.emplace_back(QUERY_ADD, "Media.1", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.Size", "2", true);
    _description_query.emplace_back(QUERY_ADD, "Media.1.m.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.1.m.Size", "1", true);
    _description_query.emplace_back(QUERY_SET, "Media.1.m.0.Media.video", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.1.m.0.Media", "video", true);
    _description_query.emplace_back(QUERY_SET, "Media.1.m.0.Port.65000", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.1.m.0.Port", "65000", true);
    _description_query.emplace_back(QUERY_SET, "Media.1.m.0.Protocol.udp", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.1.m.0.Protocol", "udp", true);
    _description_query.emplace_back(QUERY_ADD, "Media.1.a.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.1.a.Size", "1", true);
    _description_query.emplace_back(QUERY_SET, "Media.1.a.0.Attribute.rtpmap", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.1.a.0.Attribute", "rtpmap", true);
    _description_query.emplace_back(QUERY_SET, "Media.1.a.0.Value.99 h263-1998/90000", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.1.a.0.Value", "99 h263-1998/90000", true);
    _description_query.emplace_back(QUERY_ADD, "Media.1.a.1", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.1.a.Size", "2", true);
    _description_query.emplace_back(QUERY_SET, "Media.1.a.1.Attribute.charset", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.1.a.1.Attribute", "charset", true);
    _description_query.emplace_back(QUERY_SET, "Media.1.a.1.Value.ISO-8859-1", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.1.a.1.Value", "ISO-8859-1", true);
    _description_query.emplace_back(QUERY_DEL, "Media.1.a.1", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.1.a.Size", "1", true);
    _description_query.emplace_back(QUERY_GET, "Media.1.a.0.Attribute", "rtpmap", true);
    _description_query.emplace_back(QUERY_DEL, "Media.1.a.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.1.a.Size", "0", true);
    _description_query.emplace_back(QUERY_DEL, "Media.0.m.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.m.Size", "0", true);
    _description_query.emplace_back(QUERY_DEL, "Media.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.Size", "1", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.m.0.Media", "video", true);
    _description_query.emplace_back(QUERY_DEL, "Media.0.m.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.0.m.Size", "0", true);
    _description_query.emplace_back(QUERY_DEL, "Media.0", "", true);
    _description_query.emplace_back(QUERY_GET, "Media.Size", "0", true);
}

//-------------------------------------------
//-------------------------------------------

SDP_Description_Complete_Decode_Encode_Test::SDP_Description_Complete_Decode_Encode_Test()
{
    SDP_Description_Input_Output msg1;

    msg1._input   = "v=0\r\n";
    msg1._input  += "o=jdoe 2890844526 2890842807 IN IP4 10.47.16.5\r\n";
    msg1._input  += "s=SDP Seminar\r\n";
    msg1._input  += "i=A Seminar on the session description protocol\r\n";
    msg1._input  += "u=http://www.example.com/seminars/sdp.pdf\r\n";
    msg1._input  += "e=j.doe@example.com (Jane Doe)\r\n";
    msg1._input  += "c=IN IP4 224.2.17.12/127\r\n";
    msg1._input  += "t=2873397496 2873404696\r\n";
    msg1._input  += "a=recvonly\r\n";
    msg1._input  += "m=audio 49170 RTP/AVP 0\r\n";
    msg1._input  += "m=video 51372 RTP/AVP 99\r\n";
    msg1._input  += "a=rtpmap:99 h263-1998/90000\r\n";
    msg1._input  += "a=sendrecv\r\n";

    msg1._output  = "v=0\r\n";
    msg1._output += "o=jdoe 2890844526 2890842807 IN IP4 10.47.16.5\r\n";
    msg1._output += "s=SDP Seminar\r\n";
    msg1._output += "i=A Seminar on the session description protocol\r\n";
    msg1._output += "u=http://www.example.com/seminars/sdp.pdf\r\n";
    msg1._output += "e=j.doe@example.com (Jane Doe)\r\n";
    msg1._output += "c=IN IP4 224.2.17.12/127\r\n";
    msg1._output += "t=2873397496 2873404696\r\n";
    msg1._output += "a=recvonly\r\n";
    msg1._output += "m=audio 49170 RTP/AVP 0\r\n";
    msg1._output += "m=video 51372 RTP/AVP 99\r\n";
    msg1._output += "a=rtpmap:99 h263-1998/90000\r\n";
    msg1._output += "a=sendrecv\r\n";

    _description_input_output.push_back(msg1);


    SDP_Description_Input_Output msg2;

    msg2._input   = "v=0\r\n";
    msg2._input  += "o=alice 53655765 2353687637 IN IP4 pc33.atlanta.com\r\n";
    msg2._input  += "s=Session SDP\r\n";
    msg2._input  += "p=Jane Doe <+1 234 567-8900>\r\n";
    msg2._input  += "c=IN IP4 pc33.atlanta.com\r\n";
    msg2._input  += "t=0 0\r\n";
    msg2._input  += "m=audio 3456 RTP/AVP 0 1 3 99\r\n";
    msg2._input  += "a=rtpmap:0 PCMU/8000\r\n";
    msg2._input  += "a=recvonly\r\n";

    msg2._output  = "v=0\r\n";
    msg2._output += "o=alice 53655765 2353687637 IN IP4 pc33.atlanta.com\r\n";
    msg2._output += "s=Session SDP\r\n";
    msg2._output += "p=Jane Doe <+1 234 567-8900>\r\n";
    msg2._output += "c=IN IP4 pc33.atlanta.com\r\n";
    msg2._output += "t=0 0\r\n";
    msg2._output += "m=audio 3456 RTP/AVP 0 1 3 99\r\n";
    msg2._output += "a=rtpmap:0 PCMU/8000\r\n";
    msg2._output += "a=recvonly\r\n";

    _description_input_output.push_back(msg2);


    SDP_Description_Input_Output msg3;

    msg3._input   = "v=0\r\n";
    msg3._input  += "o=alice 53655765 2353687637 IN IP4 pc33.atlanta.com\r\n";
    msg3._input  += "s=-\r\n";
    msg3._input  += "c=IN IP6 FF15::101/3\r\n";
    msg3._input  += "t=0 0\r\n";

    msg3._output  = "v=0\r\n";
    msg3._output += "o=alice 53655765 2353687637 IN IP4 pc33.atlanta.com\r\n";
    msg3._output += "s=-\r\n";
    msg3._output += "c=IN IP6 FF15::101/3\r\n";
    msg3._output += "t=0 0\r\n";

    _description_input_output.push_back(msg3);
}

//-------------------------------------------

bool SDP_Description_Complete_Decode_Encode_Test::execute(SDP_Description_Input_Output &description_input_output)
{
    std::cout << "SDP description complete decode encode test initialized\n";

    std::string input = description_input_output._input;

    SDP_Description *description = new SDP_Description();
    if (!description->decode(input.c_str(), (unsigned short) input.size()))
    {
        std::cout << "SDP_Description_Complete_Decode_Encode_Test::execute -> Failed to decode description:\n";
        std::cout << std::setw(12) << "Input: " << description_input_output._input.c_str() << "\n";
        delete description;
        return false;
    }

    SDP_Description *copy = new SDP_Description(*description);
    delete description;
    description = NULL;

    char output[MAX_DESCRIPTION_SIZE] = {0};
    unsigned short size = sizeof(output);

    if (!copy->encode(output, size))
    {
        std::cout << "SDP_Description_Complete_Decode_Encode_Test::execute -> Failed to encode description:\n";
        std::cout << std::setw(12) << "Input: " << description_input_output._input.c_str() << "\n";
        delete copy;
        return false;
    }

    if (strcmp(output, description_input_output._output.c_str()) != 0)
    {
        std::cout << "SDP_Description_Complete_Decode_Encode_Test::execute -> Invalid encoded description:\n";
        std::cout << std::setw(12) << "Input: " << description_input_output._input.c_str() << "\n";
        std::cout << std::setw(12) << "Expected: " << description_input_output._output.c_str() << "\n";
        std::cout << std::setw(12) << "Output: " << output << "\n";
        delete copy;
        return false;
    }

    delete copy;
    copy = NULL;

    std::cout << "SDP description complete decode encode test completed successfully\n";
    return true;
}

//-------------------------------------------
