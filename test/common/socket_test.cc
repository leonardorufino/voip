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

#include "socket_test.h"
#include <iostream>

//-------------------------------------------

bool Socket_Test::init()
{
    std::cout << "Socket test initialized\n";

    Socket::Address_Family family_ipv4 = Socket::ADDRESS_FAMILY_IPv4;
    std::string address_ipv4 = "127.0.0.1";
    unsigned short port_ipv4 = 33445;

    if (check_network_address(family_ipv4, address_ipv4))
    {
        std::cout << "IPv4 socket test initialized\n";

        Socket_UDP_Blocking_Test udp_blocking_test;
        if (!udp_blocking_test.run(family_ipv4, address_ipv4, port_ipv4))
            return false;
    }else
        std::cout << "IPv4 socket test disabled\n";

    Socket::Address_Family family_ipv6 = Socket::ADDRESS_FAMILY_IPv6;
    std::string address_ipv6 = "::1";
    unsigned short port_ipv6 = 33445;

    if (check_network_address(family_ipv6, address_ipv6))
    {
        std::cout << "IPv6 socket test initialized\n";

        Socket_UDP_Blocking_Test udp_blocking_test;
        if (!udp_blocking_test.run(family_ipv6, address_ipv6, port_ipv6))
            return false;
    }else
        std::cout << "IPv6 socket test disabled\n";

    std::cout << "Socket test completed successfully\n";
    return true;
}

//-------------------------------------------

bool Socket_Test::create(Socket &socket, Socket::Address_Family family)
{
    if (!socket.create(family))
    {
        std::cout << "Socket_Test::create -> Failed to create socket:\n";
        std::cout << std::setw(12) << "Family: " << family << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::close(Socket &socket)
{
    if (!socket.close())
    {
        std::cout << "Socket_Test::close -> Failed to close\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::set_so_snd_buf(Socket &socket)
{
    if (!socket.set_so_snd_buf())
    {
        std::cout << "Socket_Test::set_so_snd_buf -> Failed to set socket option send buffer size\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::set_so_rcv_buf(Socket &socket)
{
    if (!socket.set_so_rcv_buf())
    {
        std::cout << "Socket_Test::set_so_rcv_buf -> Failed to set socket option receive buffer size\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::set_so_reuse_addr(Socket &socket)
{
    if (!socket.set_so_reuse_addr())
    {
        std::cout << "Socket_Test::set_so_reuse_addr -> Failed to set socket option reuse addr\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::bind(Socket &socket, std::string address, unsigned short port)
{
    if (!socket.bind(address, port))
    {
        std::cout << "Socket_Test::bind -> Failed to bind:\n";
        std::cout << std::setw(12) << "Address: " << address.c_str() << "\n";
        std::cout << std::setw(12) << "Port: " << port << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::connect(Socket &socket, std::string address, unsigned short port)
{
    if (!socket.connect(address, port))
    {
        std::cout << "Socket_Test::connect -> Failed to connect:\n";
        std::cout << std::setw(12) << "Address: " << address.c_str() << "\n";
        std::cout << std::setw(12) << "Port: " << port << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::send(Socket &socket, const char *buffer, int size)
{
    if (!socket.send(buffer, size))
    {
        std::cout << "Socket_Test::send -> Failed to send message:\n";
        std::cout << std::setw(12) << "Size: " << size << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::send(Socket &socket, const char *buffer, int size, std::string address, unsigned short port)
{
    if (!socket.send(buffer, size, address, port))
    {
        std::cout << "Socket_Test::send -> Failed to send message:\n";
        std::cout << std::setw(12) << "Address: " << address.c_str() << "\n";
        std::cout << std::setw(12) << "Port: " << port << "\n";
        std::cout << std::setw(12) << "Size: " << size << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::receive(Socket &socket, char *buffer, int size)
{
    int ret = socket.receive(buffer, size);
    if (ret != size)
    {
        std::cout << "Socket_Test::receive -> Failed to receive message:\n";
        std::cout << std::setw(12) << "Expected: " << size << "\n";
        std::cout << std::setw(12) << "Received: " << ret << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::receive(Socket &socket, char *buffer, int size, std::string &address, unsigned short &port)
{
    int ret = socket.receive(buffer, size, address, port);
    if (ret != size)
    {
        std::cout << "Socket_Test::receive -> Failed to receive message:\n";
        std::cout << std::setw(12) << "Expected: " << size << "\n";
        std::cout << std::setw(12) << "Received: " << ret << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::select_read(Socket &socket)
{
    if (socket.select_read() <= 0)
    {
        std::cout << "Socket_Test::select_read -> Failed to select read\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::get_network_addresses(std::list<Socket::Network_Address> &addresses)
{
    if (!Socket::get_network_addresses(addresses))
    {
        std::cout << "Socket_Test::get_network_addresses -> Failed to get network addresses\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::check_network_address(Socket::Address_Family family, std::string address)
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

bool Socket_UDP_Blocking_Test::run(Socket::Address_Family family, std::string address, unsigned short port)
{
    if (!create(_socket_udp, family))
        return false;

    if (!set_so_snd_buf(_socket_udp))
        return false;

    if (!set_so_rcv_buf(_socket_udp))
        return false;

    if (!set_so_reuse_addr(_socket_udp))
        return false;

    if (!bind(_socket_udp, address, port))
        return false;

    const int MSG_SIZE = 256;
    char send_buffer[MSG_SIZE];

    for (int i = 0; i < MSG_SIZE; i++)
        send_buffer[i] = i;

    if (!send(_socket_udp, send_buffer, sizeof(send_buffer), address, port))
        return false;

    if (!select_read(_socket_udp))
        return false;

    char receive_buffer[MSG_SIZE];
    std::string received_address;
    unsigned short received_port;

    if (!receive(_socket_udp, receive_buffer, sizeof(receive_buffer), received_address, received_port))
        return false;

    if ((address != received_address) || (port != received_port))
    {
        std::cout << "Socket_UDP_Blocking_Test::run -> Invalid received message\n";
        std::cout << std::setw(20) << "Local Address: " << address << "\n";
        std::cout << std::setw(20) << "Local Port: " << port << "\n";
        std::cout << std::setw(20) << "Received Address: " << received_address << "\n";
        std::cout << std::setw(20) << "Received Port: " << received_port << "\n";
        return false;
    }

    if (memcmp(send_buffer, receive_buffer, MSG_SIZE) != 0)
    {
        std::cout << "Socket_UDP_Blocking_Test::run -> Invalid received message\n";
        return false;
    }

    if (!close(_socket_udp))
        return false;

    return true;
}

//-------------------------------------------
