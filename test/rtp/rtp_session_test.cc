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

#include "rtp_session_test.h"
#include <iostream>

//-------------------------------------------

RTP_Session_Test::RTP_Session_Test() : _send_packet(NULL), _packet_callback(NULL), _stop_thread(false)
{
    RTP_Object_ID session_id;
    session_id._session = 0;
    _session = new RTP_Session(session_id);
}

//-------------------------------------------

RTP_Session_Test::~RTP_Session_Test()
{
    if (_session)
        delete _session;

    if (_send_packet)
        delete _send_packet;

    if (_packet_callback)
        delete _packet_callback;
}

//-------------------------------------------

bool RTP_Session_Test::init()
{
    std::cout << "RTP session test initialized\n";

    Socket::Address_Family family_ipv4 = Socket::ADDRESS_FAMILY_IPv4;
    std::string address_ipv4 = "127.0.0.1";
    unsigned short port_ipv4 = 33445;

    if (check_network_address(family_ipv4, address_ipv4))
    {
        std::cout << "IPv4 RTP session test initialized\n";

        if (!run<RTP_Session_UDP_Test>(family_ipv4, address_ipv4, port_ipv4, RTP_TRANSPORT_UDP))
            return false;

        std::cout << "IPv4 RTP session test completed successfully\n";
    }else
        std::cout << "IPv4 RTP session test disabled\n";


    Socket::Address_Family family_ipv6 = Socket::ADDRESS_FAMILY_IPv6;
    std::string address_ipv6 = "::1";
    unsigned short port_ipv6 = 33445;

    if (check_network_address(family_ipv6, address_ipv6))
    {
        std::cout << "IPv6 RTP session test initialized\n";

        if (!run<RTP_Session_UDP_Test>(family_ipv6, address_ipv6, port_ipv6, RTP_TRANSPORT_UDP))
            return false;

        std::cout << "IPv6 RTP session test completed successfully\n";
    }else
        std::cout << "IPv6 RTP session test disabled\n";

    std::cout << "RTP session test completed successfully\n";
    return true;
}

//-------------------------------------------

template<class T> bool RTP_Session_Test::run(Socket::Address_Family family, std::string address, unsigned short port,
                                                RTP_Transport_Type transport)
{
    T test;
    test._thread = std::thread(thread, &test);

    bool ret = test.run(family, address, port, transport);

    test._stop_thread = true;
    test._thread.join();
    return ret;
}

//-------------------------------------------

void RTP_Session_Test::thread(RTP_Session_Test *test)
{
    Socket_Control &socket = Socket_Control::instance();

    while (!test->_stop_thread)
    {
        Util_Functions::delay(THREAD_DELAY);

        std::lock_guard<std::mutex> lock(test->_thread_mutex);
        socket.run();
    }
}

//-------------------------------------------

bool RTP_Session_Test::init_session(std::string local_address, unsigned short local_port, std::string remote_address,
                                    unsigned short remote_port, RTP_Transport_Type transport)
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    set_callbacks();

    if (!_session->init(local_address, local_port, remote_address, remote_port, transport))
    {
        std::cout << "RTP_Session_Test::init_session -> Failed to init session\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool RTP_Session_Test::close_session()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    if (!_session->close())
    {
        std::cout << "RTP_Session_Test::close_session -> Failed to close session\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool RTP_Session_Test::set_callbacks()
{
    _session->set_receive_packet_callback(receive_packet_callback, this);
    return true;
}

//-------------------------------------------

void RTP_Session_Test::clear_callback_params()
{
    if (_packet_callback)
    {
        delete _packet_callback;
        _packet_callback = NULL;
    }
}

//-------------------------------------------
//-------------------------------------------

bool RTP_Session_Test::send_packet()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    if (!_send_packet)
    {
        _send_packet = new RTP_Packet();
        _send_packet->get_header().init_random(RTP_Header::PAYLOAD_PCMA);

        char payload[160];
        memset(payload, 0xD5, sizeof(payload));
        _send_packet->set_payload(payload, sizeof(payload));
    }else
    {
        _send_packet->get_header().set_marker(0);
        _send_packet->get_header().increment_sequence_number();
        _send_packet->get_header().increment_timestamp(160);
    }

    clear_callback_params();

    if (!_session->send_packet(_send_packet))
    {
        std::cout << "RTP_Session_Test::send_packet -> Failed to send packet\n";
        delete _send_packet;
        return false;
    }

    return true;
}

//-------------------------------------------

bool RTP_Session_Test::receive_packet()
{
    unsigned long start = Util_Functions::get_tick();

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if (_packet_callback)
            break;

        Util_Functions::delay(DELAY);
    }

    if (!_packet_callback)
    {
        std::cout << "RTP_Session_Test::receive_packet -> Packet not received\n";
        return false;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

bool RTP_Session_Test::receive_packet_callback(void *data, RTP_Session *session, RTP_Packet *packet)
{
    RTP_Session_Test *test = reinterpret_cast<RTP_Session_Test *>(data);
    if ((!test) || (!session) || (!packet))
    {
        std::cout << "RTP_Session_Test::receive_packet_callback -> Invalid parameters\n";
        return false;
    }

    if (!test->_packet_callback)
        delete test->_packet_callback;

    test->_packet_callback = new RTP_Packet(*packet);
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool RTP_Session_Test::get_network_addresses(std::list<Socket::Network_Address> &addresses)
{
    if (!Socket::get_network_addresses(addresses))
    {
        std::cout << "RTP_Session_Test::get_network_addresses -> Failed to get network addresses\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool RTP_Session_Test::check_network_address(Socket::Address_Family family, std::string address)
{
    std::list<Socket::Network_Address> addresses;
    if (!get_network_addresses(addresses))
        return false;

    std::list<Socket::Network_Address>::iterator it = addresses.begin();
    while (it != addresses.end())
    {
        Socket::Network_Address &netaddr = *it++;
        if ((netaddr._family == family) && (netaddr._address == address))
            return true;
    }

    return false;
}

//-------------------------------------------
//-------------------------------------------

bool RTP_Session_UDP_Test::run(Socket::Address_Family family, std::string address, unsigned short port, RTP_Transport_Type transport)
{
    std::cout << "RTP session call success test initialized\n";

    if (!init_session(address, port, address, port, transport))
        return false;

    for (unsigned short i = 0; i < 5; i++)
    {
        if (!send_packet())
            return false;

        if (!receive_packet())
            return false;
    }

    if (!close_session())
        return false;

    std::cout << "RTP session call success test completed successfully\n";
    return true;
}

//-------------------------------------------
