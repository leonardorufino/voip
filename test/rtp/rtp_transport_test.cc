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

#include "rtp_transport_test.h"
#include <iostream>

//-------------------------------------------

bool RTP_Transport_Test::init()
{
    std::cout << "RTP transport test initialized\n";

    Socket::Address_Family family_ipv4 = Socket::ADDRESS_FAMILY_IPv4;
    std::string address_ipv4 = "127.0.0.1";
    unsigned short port_ipv4 = 33445;

    if (check_network_address(family_ipv4, address_ipv4))
    {
        std::cout << "IPv4 RTP transport test initialized\n";

        if (!run<RTP_Transport_UDP_Test>(family_ipv4, address_ipv4, port_ipv4))
            return false;

        std::cout << "IPv4 RTP transport test completed successfully\n";
    }else
        std::cout << "IPv4 RTP transport test disabled\n";


    Socket::Address_Family family_ipv6 = Socket::ADDRESS_FAMILY_IPv6;
    std::string address_ipv6 = "::1";
    unsigned short port_ipv6 = 33445;

    if (check_network_address(family_ipv6, address_ipv6))
    {
        std::cout << "IPv6 RTP transport test initialized\n";

        if (!run<RTP_Transport_UDP_Test>(family_ipv6, address_ipv6, port_ipv6))
            return false;

        std::cout << "IPv6 RTP transport test completed successfully\n";
    }else
        std::cout << "IPv6 RTP transport test disabled\n";

    std::cout << "RTP transport test completed successfully\n";
    return true;
}

//-------------------------------------------

template<class T> bool RTP_Transport_Test::run(Socket::Address_Family family, std::string address, unsigned short port)
{
    T test;
    test._thread = std::thread(thread, &test);

    bool ret = test.run(family, address, port);

    test._stop_thread = true;
    test._thread.join();
    return ret;
}

//-------------------------------------------

void RTP_Transport_Test::thread(RTP_Transport_Test *test)
{
    Socket_Control &socket = Socket_Control::instance();

    while (!test->_stop_thread)
    {
        Util_Functions::delay(THREAD_DELAY);

        std::lock_guard<std::mutex> lock(test->_thread_mutex);
        socket.run();
    }

    Socket_Control::destroy();
}

//-------------------------------------------
//-------------------------------------------

RTP_Transport_Test::RTP_Transport_Test() : _received_port(RTP_Transport::INVALID_PORT), _stop_thread(false)
{
}

//-------------------------------------------

RTP_Transport_Test::~RTP_Transport_Test()
{
    std::list<RTP_Packet *>::iterator it = _received_packets.begin();
    while (it != _received_packets.end())
        delete *it++;
}

//-------------------------------------------

bool RTP_Transport_Test::set_callbacks()
{
    RTP_Transport *transport = get_transport();
    if (!transport)
    {
        std::cout << "RTP_Transport_Test::set_callbacks -> Invalid transport\n";
        return false;
    }

    transport->set_receive_callback(receive_callback, this);
    return true;
}

//-------------------------------------------

void RTP_Transport_Test::clear_callback_params()
{
    std::list<RTP_Packet *>::iterator it = _received_packets.begin();
    while (it != _received_packets.end())
        delete *it++;

    _received_packets.clear();

    _received_address.clear();
    _received_port = RTP_Transport::INVALID_PORT;
}

//-------------------------------------------

unsigned int RTP_Transport_Test::get_next_transport_id()
{
    static unsigned int NEXT_TRANSPORT_ID = 0;
    return NEXT_TRANSPORT_ID++;
}

//-------------------------------------------
//-------------------------------------------

bool RTP_Transport_Test::create_packet(char *packet, int &size)
{
    unsigned short packet_size = 172;

    if ((!packet) || (size < packet_size))
    {
        std::cout << "RTP_Transport_UDP_Test::create_packet -> Invalid parameters:\n";
        std::cout << std::setw(20) << "Size: " << size << "\n";
        std::cout << std::setw(20) << "Expected: " << 20 << "\n";
        return false;
    }

    packet[0] = (char) 0x80;    packet[1] = (char) 0x80;    packet[2] = (char) 0x92;    packet[3] = (char) 0xdb;
    packet[4] = (char) 0x00;    packet[5] = (char) 0x00;    packet[6] = (char) 0x00;    packet[7] = (char) 0xa0;
    packet[8] = (char) 0x34;    packet[9] = (char) 0x3d;    packet[10] = (char) 0xa9;   packet[11] = (char) 0x9b;

    for (unsigned short i = 0; i < (packet_size - 12); i++)
        packet[12 + i] = (char) 0xff;

    size = packet_size;
    return true;
}

//-------------------------------------------

bool RTP_Transport_Test::receive_callback(void *data, RTP_Transport *transport, RTP_Packet *packet, std::string address, unsigned short port)
{
    RTP_Transport_Test *test = reinterpret_cast<RTP_Transport_Test *>(data);
    if ((!test) || (!transport) || (!packet))
    {
        std::cout << "RTP_Transport_Test::receive_callback -> Invalid parameters\n";
        return false;
    }

    test->_received_packets.push_back(new RTP_Packet(*packet));
    test->_received_address = address;
    test->_received_port = port;
    return true;
}

//-------------------------------------------

bool RTP_Transport_Test::get_network_addresses(std::list<Socket::Network_Address> &addresses)
{
    if (!Socket::get_network_addresses(addresses))
    {
        std::cout << "RTP_Transport_Test::get_network_addresses -> Failed to get network addresses\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool RTP_Transport_Test::check_network_address(Socket::Address_Family family, std::string address)
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

RTP_Transport_UDP_Test::RTP_Transport_UDP_Test()
{
    RTP_Object_ID id;
    id._transport = get_next_transport_id();
    _transport_udp = new RTP_Transport_UDP(id);
}

//-------------------------------------------

RTP_Transport_UDP_Test::~RTP_Transport_UDP_Test()
{
    if (_transport_udp)
        delete _transport_udp;
}

//-------------------------------------------

bool RTP_Transport_UDP_Test::init(std::string address, unsigned short port)
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    if (!_transport_udp->init(address, port))
    {
        std::cout << "RTP_Transport_UDP_Test::init -> Failed to init transport\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool RTP_Transport_UDP_Test::send_packet(const char *buffer, int size, std::string address, unsigned short port)
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    if (!_transport_udp->send_message(buffer, size, address, port))
    {
        std::cout << "RTP_Transport_UDP_Test::send_message -> Failed to send message\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool RTP_Transport_UDP_Test::close()
{
    std::lock_guard<std::mutex> lock(_thread_mutex);

    if (!_transport_udp->close())
    {
        std::cout << "RTP_Transport_UDP_Test::close -> Failed to close transport\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool RTP_Transport_UDP_Test::run(Socket::Address_Family family, std::string address, unsigned short port)
{
    std::cout << "RTP transport UDP test initialized\n";

    if (!_transport_udp)
    {
        std::cout << "RTP_Transport_UDP_Test::run -> Invalid transport\n";
        return false;
    }

    if (!set_callbacks())
        return false;

    if (!init(address, port))
        return false;

    clear_callback_params();

    char packet[MAX_PACKET_SIZE];
    int size = (int) sizeof(packet);

    if (!create_packet(packet, size))
        return false;

    if (!send_packet(packet, (int) size, address, port))
        return false;

    unsigned long start = Util_Functions::get_tick();

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if (_received_packets.size() == 1)
            break;

        Util_Functions::delay(DELAY);
    }

    if (_received_packets.size() != 1)
    {
        std::cout << "RTP_Transport_UDP_Test::run -> Message not received:\n";
        std::cout << std::setw(20) << "Received: " << _received_packets.size() << "\n";
        std::cout << std::setw(20) << "Expected: " << 1 << "\n";
        return false;
    }

    if ((address != _received_address) || (port != _received_port))
    {
        std::cout << "RTP_Transport_UDP_Test::run -> Invalid received message parameters:\n";
        std::cout << std::setw(20) << "Local Address: " << address << "\n";
        std::cout << std::setw(20) << "Local Port: " << port << "\n";
        std::cout << std::setw(20) << "Received Address: " << _received_address << "\n";
        std::cout << std::setw(20) << "Received Port: " << _received_port << "\n";
        return false;
    }

    if (!close())
        return false;

    std::cout << "RTP transport UDP test completed successfully\n";
    return true;
}

//-------------------------------------------
