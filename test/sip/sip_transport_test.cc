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

#include "sip_transport_test.h"
#include <iostream>

//-------------------------------------------

SIP_Transport_Test::SIP_Transport_Test()
{
    _connected = false;

    _accepted_transport = NULL;
    _accepted_port = SIP_Transport::INVALID_PORT;

    _received_buffer[0] = 0;
    _received_size = 0;
    _received_port = SIP_Transport::INVALID_PORT;
}

//-------------------------------------------

bool SIP_Transport_Test::init()
{
    std::cout << "SIP transport test initialized\n";

    Socket::Address_Family family_ipv4 = Socket::ADDRESS_FAMILY_IPv4;
    std::string address_ipv4 = "127.0.0.1";
    unsigned short port_ipv4 = 33445;

    if (check_network_address(family_ipv4, address_ipv4))
    {
        std::cout << "IPv4 SIP transport test initialized\n";
    }else
        std::cout << "IPv4 SIP transport test disabled\n";


    Socket::Address_Family family_ipv6 = Socket::ADDRESS_FAMILY_IPv6;
    std::string address_ipv6 = "::1";
    unsigned short port_ipv6 = 33445;

    if (check_network_address(family_ipv6, address_ipv6))
    {
        std::cout << "IPv6 SIP transport test initialized\n";
    }else
        std::cout << "IPv6 SIP transport test disabled\n";

    std::cout << "SIP transport test completed successfully\n";
    return true;
}

//-------------------------------------------

bool SIP_Transport_Test::set_callbacks()
{
    SIP_Transport &transport = get_transport();

    transport.set_connect_callback(connect_callback, this);
    transport.set_accept_callback(accept_callback, this);
    transport.set_receive_callback(receive_callback, this);
    return true;
}

//-------------------------------------------

std::string SIP_Transport_Test::create_request()
{
    std::string str;
    str  = "INVITE sip:bob@biloxi.com SIP/2.0\r\n";
    str += "Via: SIP/2.0/UDP pc33.atlanta.com;branch=z9hG4bK776asdhds\r\n";
    str += "Max-Forwards: 70\r\n";
    str += "To: Bob <sip:bob@biloxi.com>\r\n";
    str += "From: Alice <sip:alice@atlanta.com>;tag=1928301774\r\n";
    str += "Call-ID: a84b4c76e66710@pc33.atlanta.com\r\n";
    str += "CSeq: 314159 INVITE\r\n";
    str += "Contact: <sip:alice@pc33.atlanta.com>\r\n";
    str += "User-Agent: ABC123\r\n";
    str += "Content-Length: 0\r\n";
    return str;
}

//-------------------------------------------

bool SIP_Transport_Test::connect_callback(void *data, SIP_Transport *transport, bool success)
{
    SIP_Transport_Test *test = reinterpret_cast<SIP_Transport_Test *>(data);
    if ((!test) || (!transport))
    {
        std::cout << "Socket_Test::connect_callback -> Invalid parameters\n";
        return false;
    }

    test->_connected = success;
    return true;
}

//-------------------------------------------

bool SIP_Transport_Test::accept_callback(void *data, SIP_Transport *transport, SIP_Transport_TCP_Client *accepted, std::string address, unsigned short port)
{
    SIP_Transport_Test *test = reinterpret_cast<SIP_Transport_Test *>(data);
    if ((!test) || (!transport) || (!accepted))
    {
        std::cout << "SIP_Transport_Test::accept_callback -> Invalid parameters\n";
        return false;
    }

    test->_accepted_transport = accepted;
    test->_accepted_address = address;
    test->_accepted_port = port;
    return true;
}

//-------------------------------------------

bool SIP_Transport_Test::receive_callback(void *data, SIP_Transport *transport, const char *buffer, int size, std::string address, unsigned short port)
{
    SIP_Transport_Test *test = reinterpret_cast<SIP_Transport_Test *>(data);
    if ((!test) || (!transport) || (!buffer) || (size < 0))
    {
        std::cout << "SIP_Transport_Test::receive_callback -> Invalid parameters\n";
        return false;
    }

    memcpy(test->_received_buffer, buffer, size);
    test->_received_size = size;
    test->_received_address = address;
    test->_received_port = port;
    return true;
}

//-------------------------------------------

bool SIP_Transport_Test::get_network_addresses(std::list<Socket::Network_Address> &addresses)
{
    if (!Socket::get_network_addresses(addresses))
    {
        std::cout << "SIP_Transport_Test::get_network_addresses -> Failed to get network addresses\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool SIP_Transport_Test::check_network_address(Socket::Address_Family family, std::string address)
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
