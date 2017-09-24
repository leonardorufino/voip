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

bool SIP_Transport_Test::init()
{
    std::cout << "SIP transport test initialized\n";

    Socket::Address_Family family_ipv4 = Socket::ADDRESS_FAMILY_IPv4;
    std::string address_ipv4 = "127.0.0.1";
    unsigned short port_ipv4 = 33445;

    if (check_network_address(family_ipv4, address_ipv4))
    {
        std::cout << "IPv4 SIP transport test initialized\n";

        if (!run<SIP_Transport_UDP_Test>(family_ipv4, address_ipv4, port_ipv4))
            return false;

        if (!run<SIP_Transport_TCP_Test>(family_ipv4, address_ipv4, port_ipv4))
            return false;
    }else
        std::cout << "IPv4 SIP transport test disabled\n";


    Socket::Address_Family family_ipv6 = Socket::ADDRESS_FAMILY_IPv6;
    std::string address_ipv6 = "::1";
    unsigned short port_ipv6 = 33445;

    if (check_network_address(family_ipv6, address_ipv6))
    {
        std::cout << "IPv6 SIP transport test initialized\n";

        if (!run<SIP_Transport_UDP_Test>(family_ipv6, address_ipv6, port_ipv6))
            return false;

        if (!run<SIP_Transport_TCP_Test>(family_ipv6, address_ipv6, port_ipv6))
            return false;
    }else
        std::cout << "IPv6 SIP transport test disabled\n";

    std::cout << "SIP transport test completed successfully\n";
    return true;
}

//-------------------------------------------

template<class T> bool SIP_Transport_Test::run(Socket::Address_Family family, std::string address, unsigned short port)
{
    T test;
    if (!test.run(family, address, port))
        return false;
    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Transport_Test::SIP_Transport_Test() : _connected(false), _accepted_transport(NULL), _accepted_port(SIP_Transport::INVALID_PORT),
    _received_size(0), _received_port(SIP_Transport::INVALID_PORT)
{
    _received_buffer[0] = 0;
}

//-------------------------------------------

SIP_Transport_Test::~SIP_Transport_Test()
{
    if (_accepted_transport)
        delete _accepted_transport;
}

//-------------------------------------------

bool SIP_Transport_Test::set_callbacks()
{
    SIP_Transport *transport = get_transport();
    if (!transport)
    {
        std::cout << "SIP_Transport_Test::set_callbacks -> Invalid transport\n";
        return false;
    }

    transport->set_connect_callback(connect_callback, this);
    transport->set_accept_callback(accept_callback, this);
    transport->set_receive_callback(receive_callback, this);
    return true;
}

//-------------------------------------------

unsigned int SIP_Transport_Test::get_next_transport_id()
{
    static unsigned int NEXT_TRANSPORT_ID = 0;
    return NEXT_TRANSPORT_ID++;
}

//-------------------------------------------
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

    SIP_Object_ID id;
    id._transport = test->get_next_transport_id();
    accepted->set_id(id);

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
//-------------------------------------------

SIP_Transport_UDP_Test::SIP_Transport_UDP_Test()
{
    SIP_Object_ID id;
    id._transport = get_next_transport_id();
    _transport_udp = new SIP_Transport_UDP(id);
}

//-------------------------------------------

SIP_Transport_UDP_Test::~SIP_Transport_UDP_Test()
{
    if (_transport_udp)
        delete _transport_udp;
}

//-------------------------------------------

bool SIP_Transport_UDP_Test::run(Socket::Address_Family family, std::string address, unsigned short port)
{
    if (!_transport_udp)
    {
        std::cout << "SIP_Transport_UDP_Test::run -> Invalid transport\n";
        return false;
    }

    if (!SIP_Transport::start())
    {
        std::cout << "SIP_Transport_UDP_Test::run -> Failed to start SIP transport\n";
        return false;
    }

    if (!set_callbacks())
        return false;

    if (!_transport_udp->init(address, port))
    {
        std::cout << "SIP_Transport_UDP_Test::run -> Failed to init transport\n";
        return false;
    }

    std::string request = create_request();

    _received_buffer[0] = 0;
    _received_size = 0;
    _received_address.clear();
    _received_port = SIP_Transport::INVALID_PORT;

    if (!_transport_udp->send_message(request.c_str(), (int) request.size(), address, port))
    {
        std::cout << "SIP_Transport_UDP_Test::run -> Failed to send message\n";
        return false;
    }

    unsigned long start = Util_Functions::get_tick();

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if (_received_size == (int) request.size())
            break;

        Util_Functions::delay(DELAY);
    }

    if (_received_size != (int) request.size())
    {
        std::cout << "SIP_Transport_UDP_Test::run -> Message not received:\n";
        std::cout << std::setw(20) << "Expected: " << request.size() << "\n";
        std::cout << std::setw(20) << "Received: " << _received_size << "\n";
        return false;
    }

    if ((address != _received_address) || (port != _received_port))
    {
        std::cout << "SIP_Transport_UDP_Test::run -> Invalid received message parameters:\n";
        std::cout << std::setw(20) << "Local Address: " << address << "\n";
        std::cout << std::setw(20) << "Local Port: " << port << "\n";
        std::cout << std::setw(20) << "Received Address: " << _received_address << "\n";
        std::cout << std::setw(20) << "Received Port: " << _received_port << "\n";
        return false;
    }

    if (memcmp(request.c_str(), _received_buffer, request.size()) != 0)
    {
        std::cout << "SIP_Transport_UDP_Test::run -> Invalid received message\n";
        return false;
    }

    if (!_transport_udp->close())
    {
        std::cout << "SIP_Transport_UDP_Test::run -> Failed to close transport\n";
        return false;
    }

    if (!SIP_Transport::stop())
    {
        std::cout << "SIP_Transport_UDP_Test::run -> Failed to stop SIP transport\n";
        return false;
    }

    return true;
}

//-------------------------------------------
//-------------------------------------------

SIP_Transport_TCP_Test::SIP_Transport_TCP_Test() : _current_transport(NULL)
{
    SIP_Object_ID client_id;
    client_id._transport = get_next_transport_id();
    _transport_tcp_client = new SIP_Transport_TCP_Client(client_id);

    SIP_Object_ID server_id;
    server_id._transport = get_next_transport_id();
    _transport_tcp_server = new SIP_Transport_TCP_Server(server_id);
}

//-------------------------------------------

SIP_Transport_TCP_Test::~SIP_Transport_TCP_Test()
{
    if (_transport_tcp_client)
        delete _transport_tcp_client;

    if (_transport_tcp_server)
        delete _transport_tcp_server;
}

//-------------------------------------------

bool SIP_Transport_TCP_Test::run(Socket::Address_Family family, std::string address, unsigned short port)
{
    if ((!_transport_tcp_client) || (!_transport_tcp_server))
    {
        std::cout << "SIP_Transport_TCP_Test::run -> Invalid transports\n";
        return false;
    }

    if (!SIP_Transport::start())
    {
        std::cout << "SIP_Transport_TCP_Test::run -> Failed to start SIP transport\n";
        return false;
    }

    _current_transport = _transport_tcp_client;
    if (!set_callbacks())
        return false;

    if (!_transport_tcp_client->init(address, 0))
    {
        std::cout << "SIP_Transport_TCP_Test::run -> Failed to init TCP client transport\n";
        return false;
    }

    _current_transport = _transport_tcp_server;
    if (!set_callbacks())
        return false;

    if (!_transport_tcp_server->init(address, port))
    {
        std::cout << "SIP_Transport_TCP_Test::run -> Failed to init TCP server transport\n";
        return false;
    }

    if (!_transport_tcp_server->listen(10))
    {
        std::cout << "SIP_Transport_TCP_Test::run -> Failed to listen TCP server transport\n";
        return false;
    }

    unsigned long start = Util_Functions::get_tick();
    _connected = false;
    _accepted_transport = NULL;
    _accepted_address = "";
    _accepted_port = SIP_Transport::INVALID_PORT;

    if (!_transport_tcp_client->connect(address, port))
    {
        std::cout << "SIP_Transport_TCP_Test::run -> Failed to connect TCP client transport\n";
        return false;
    }

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if (_connected)
            break;

        Util_Functions::delay(DELAY);
    }

    if (!_connected)
    {
        std::cout << "SIP_Transport_TCP_Test::run -> Transport not connected\n";
        return false;
    }

    start = Util_Functions::get_tick();

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if (_accepted_transport)
            break;

        Util_Functions::delay(DELAY);
    }

    if (!_accepted_transport)
    {
        std::cout << "SIP_Transport_TCP_Test::run -> Transport not accepted\n";
        return false;
    }

    if (address != _accepted_address)
    {
        std::cout << "SIP_Transport_TCP_Test::run -> Invalid accepted parameters:\n";
        std::cout << std::setw(20) << "Local Address: " << address << "\n";
        std::cout << std::setw(20) << "Accepted Address: " << _accepted_address << "\n";
        return false;
    }

    _current_transport = _accepted_transport;
    if (!set_callbacks())
        return false;

    std::string request = create_request();

    _received_buffer[0] = 0;
    _received_size = 0;
    _received_address.clear();
    _received_port = SIP_Transport::INVALID_PORT;

    if (!_transport_tcp_client->send_message(request.c_str(), (int) request.size(), address, port))
    {
        std::cout << "SIP_Transport_TCP_Test::run -> Failed to send client message\n";
        return false;
    }

    start = Util_Functions::get_tick();

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if (_received_size == (int) request.size())
            break;

        Util_Functions::delay(DELAY);
    }

    if (_received_size != (int) request.size())
    {
        std::cout << "SIP_Transport_TCP_Test::run -> Message not received:\n";
        std::cout << std::setw(20) << "Expected: " << request.size() << "\n";
        std::cout << std::setw(20) << "Received: " << _received_size << "\n";
        return false;
    }

    if (memcmp(request.c_str(), _received_buffer, request.size()) != 0)
    {
        std::cout << "SIP_Transport_TCP_Test::run -> Invalid received message\n";
        return false;
    }

    if (!_transport_tcp_client->close())
    {
        std::cout << "SIP_Transport_UDP_Test::run -> Failed to close TCP client transport\n";
        return false;
    }

    if (!_accepted_transport->close())
    {
        std::cout << "SIP_Transport_UDP_Test::run -> Failed to close TCP accepted transport\n";
        return false;
    }

    if (!_transport_tcp_server->close())
    {
        std::cout << "SIP_Transport_UDP_Test::run -> Failed to close TCP server transport\n";
        return false;
    }

    if (!SIP_Transport::stop())
    {
        std::cout << "SIP_Transport_TCP_Test::run -> Failed to stop SIP transport\n";
        return false;
    }

    return true;
}

//-------------------------------------------
