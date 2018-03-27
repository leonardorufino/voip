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

Socket_Test::Socket_Test() : _connected(false), _accepted_socket(NULL), _accepted_port(INVALID_UNSIGNED_SHORT),
    _received_size(0), _received_port(INVALID_UNSIGNED_SHORT), _stop_thread(false)
{
    _received_buffer[0] = 0;
}

//-------------------------------------------

Socket_Test::~Socket_Test()
{
    if (_accepted_socket)
        delete _accepted_socket;
}

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

        if (!run<Socket_UDP_Blocking_Test>(family_ipv4, address_ipv4, port_ipv4))
            return false;

        if (!run<Socket_UDP_Blocking_Connect_Test>(family_ipv4, address_ipv4, port_ipv4))
            return false;

        if (!run<Socket_UDP_Non_Blocking_Test>(family_ipv4, address_ipv4, port_ipv4))
            return false;

        if (!run<Socket_UDP_Non_Blocking_Connect_Test>(family_ipv4, address_ipv4, port_ipv4))
            return false;

        if (!run<Socket_UDP_Non_Blocking_Control_Test>(family_ipv4, address_ipv4, port_ipv4))
            return false;

        if (!run<Socket_TCP_Blocking_Test>(family_ipv4, address_ipv4, port_ipv4))
            return false;

        if (!run<Socket_TCP_Non_Blocking_Test>(family_ipv4, address_ipv4, port_ipv4))
            return false;

        if (!run<Socket_TCP_Non_Blocking_Control_Test>(family_ipv4, address_ipv4, port_ipv4))
            return false;

        std::cout << "IPv4 socket test completed successfully\n";
    }else
        std::cout << "IPv4 socket test disabled\n";


    Socket::Address_Family family_ipv6 = Socket::ADDRESS_FAMILY_IPv6;
    std::string address_ipv6 = "::1";
    unsigned short port_ipv6 = 33445;

    if (check_network_address(family_ipv6, address_ipv6))
    {
        std::cout << "IPv6 socket test initialized\n";

        if (!run<Socket_UDP_Blocking_Test>(family_ipv6, address_ipv6, port_ipv6))
            return false;

        if (!run<Socket_UDP_Blocking_Connect_Test>(family_ipv6, address_ipv6, port_ipv6))
            return false;

        if (!run<Socket_UDP_Non_Blocking_Test>(family_ipv6, address_ipv6, port_ipv6))
            return false;

        if (!run<Socket_UDP_Non_Blocking_Connect_Test>(family_ipv6, address_ipv6, port_ipv6))
            return false;

        if (!run<Socket_UDP_Non_Blocking_Control_Test>(family_ipv6, address_ipv6, port_ipv6))
            return false;

        if (!run<Socket_TCP_Blocking_Test>(family_ipv6, address_ipv6, port_ipv6))
            return false;

        if (!run<Socket_TCP_Non_Blocking_Test>(family_ipv6, address_ipv6, port_ipv6))
            return false;

        if (!run<Socket_TCP_Non_Blocking_Control_Test>(family_ipv6, address_ipv6, port_ipv6))
            return false;

        std::cout << "IPv6 socket test completed successfully\n";
    }else
        std::cout << "IPv6 socket test disabled\n";

    std::cout << "Socket test completed successfully\n";
    return true;
}

//-------------------------------------------

template<class T> bool Socket_Test::run(Socket::Address_Family family, std::string address, unsigned short port)
{
    T test;
    test._thread = std::thread(thread, &test);

    bool ret = test.run(family, address, port);

    test._stop_thread = true;
    test._thread.join();
    return ret;
}

//-------------------------------------------

void Socket_Test::thread(Socket_Test *test)
{
    Socket_Control &socket = Socket_Control::instance();

    while (!test->_stop_thread)
    {
        socket.run();
        Util_Functions::delay(THREAD_DELAY);
    }

    Socket_Control::destroy();
}

//-------------------------------------------

bool Socket_Test::set_callbacks()
{
    Socket &socket = get_socket();

    socket.set_connect_callback(connect_callback, this);
    socket.set_accept_callback(accept_callback, this);
    socket.set_receive_callback(receive_callback, this);
    return true;
}

//-------------------------------------------

bool Socket_Test::configure_socket(Socket::Address_Family family, std::string address, unsigned short port, bool non_blocking,
                                   bool tcp_no_delay)
{
    if (!set_callbacks())
        return false;

    if (!create(family))
        return false;

    if (!set_so_snd_buf())
        return false;

    if (!set_so_rcv_buf())
        return false;

    if (!set_so_reuse_addr())
        return false;

    if (tcp_no_delay)
    {
        if (!set_tcp_no_delay())
            return false;
    }

    if (!bind(address, port))
        return false;

    if (!set_non_blocking(non_blocking))
        return false;

    return true;
}

//-------------------------------------------

bool Socket_Test::create(Socket::Address_Family family)
{
    Socket &socket = get_socket();

    if (!socket.create(family))
    {
        std::cout << "Socket_Test::create -> Failed to create socket:\n";
        std::cout << std::setw(12) << "Family: " << family << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::close()
{
    Socket &socket = get_socket();

    if (!socket.close())
    {
        std::cout << "Socket_Test::close -> Failed to close\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::set_so_snd_buf()
{
    Socket &socket = get_socket();

    if (!socket.set_so_snd_buf())
    {
        std::cout << "Socket_Test::set_so_snd_buf -> Failed to set socket option send buffer size\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::set_so_rcv_buf()
{
    Socket &socket = get_socket();

    if (!socket.set_so_rcv_buf())
    {
        std::cout << "Socket_Test::set_so_rcv_buf -> Failed to set socket option receive buffer size\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::set_so_reuse_addr()
{
    Socket &socket = get_socket();

    if (!socket.set_so_reuse_addr())
    {
        std::cout << "Socket_Test::set_so_reuse_addr -> Failed to set socket option reuse addr\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::set_tcp_no_delay()
{
    Socket &socket = get_socket();

    if (!socket.set_tcp_no_delay())
    {
        std::cout << "Socket_Test::set_tcp_no_delay -> Failed to set tcp no delay\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::set_non_blocking(bool non_blocking)
{
    Socket &socket = get_socket();

    if (!socket.set_non_blocking(non_blocking))
    {
        std::cout << "Socket_Test::set_non_blocking -> Failed to set non blocking:\n";
        std::cout << std::setw(12) << "Non Block: " << (non_blocking ? "true" : "false") << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::bind(std::string address, unsigned short port)
{
    Socket &socket = get_socket();

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

bool Socket_Test::listen(int backlog)
{
    Socket &socket = get_socket();

    if (!socket.listen(backlog))
    {
        std::cout << "Socket_Test::listen -> Failed to listen:\n";
        std::cout << std::setw(12) << "Backlog: " << backlog << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::accept(socket_t &accept_socket, std::string &address, unsigned short &port)
{
    Socket &socket = get_socket();

    if (!socket.accept(accept_socket, address, port))
    {
        std::cout << "Socket_Test::accept -> Failed to accept\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::connect(std::string address, unsigned short port)
{
    Socket &socket = get_socket();

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

bool Socket_Test::send(const char *buffer, int size)
{
    Socket &socket = get_socket();

    if (!socket.send(buffer, size))
    {
        std::cout << "Socket_Test::send -> Failed to send message:\n";
        std::cout << std::setw(12) << "Size: " << size << "\n";
        return false;
    }

    return true;
}

//-------------------------------------------

bool Socket_Test::send(const char *buffer, int size, std::string address, unsigned short port)
{
    Socket &socket = get_socket();

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

bool Socket_Test::receive(char *buffer, int size)
{
    Socket &socket = get_socket();

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

bool Socket_Test::receive(char *buffer, int size, std::string &address, unsigned short &port)
{
    Socket &socket = get_socket();

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

bool Socket_Test::select(unsigned long timeout, int *read, int *write, int *except)
{
    Socket &socket = get_socket();

    if (socket.select(timeout, read, write, except) <= 0)
    {
        std::cout << "Socket_Test::select -> Failed to select\n";
        return false;
    }

    return true;
}

//-------------------------------------------
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

bool Socket_Test::connect_callback(void *data, bool success)
{
    Socket_Test *test = reinterpret_cast<Socket_Test *>(data);
    if (!test)
    {
        std::cout << "Socket_Test::connect_callback -> Invalid parameter\n";
        return false;
    }

    test->_connected = success;
    return true;
}

//-------------------------------------------

bool Socket_Test::accept_callback(void *data, Socket_TCP_Client *accepted, std::string address, unsigned short port)
{
    Socket_Test *test = reinterpret_cast<Socket_Test *>(data);
    if ((!test) || (!accepted))
    {
        std::cout << "Socket_Test::accept_callback -> Invalid parameters\n";
        return false;
    }

    test->_accepted_socket = accepted;
    test->_accepted_address = address;
    test->_accepted_port = port;
    return true;
}

//-------------------------------------------

bool Socket_Test::receive_callback(void *data, const char *buffer, int size, std::string address, unsigned short port)
{
    Socket_Test *test = reinterpret_cast<Socket_Test *>(data);
    if ((!test) || (!buffer) || (size < 0))
    {
        std::cout << "Socket_Test::receive_callback -> Invalid parameters\n";
        return false;
    }

    memcpy(test->_received_buffer, buffer, size);
    test->_received_size = size;
    test->_received_address = address;
    test->_received_port = port;
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool Socket_UDP_Blocking_Test::run(Socket::Address_Family family, std::string address, unsigned short port)
{
    std::cout << "Socket UDP blocking test initialized\n";

    if (!configure_socket(family, address, port, false, false))
        return false;

    const int MSG_SIZE = 256;
    char send_buffer[MSG_SIZE];

    for (int i = 0; i < MSG_SIZE; i++)
        send_buffer[i] = i;

    if (!send(send_buffer, sizeof(send_buffer), address, port))
        return false;

    int read;

    if (!select(MAX_WAIT_TIME, &read, NULL, NULL))
        return false;

    if (read != 1)
    {
        std::cout << "Socket_UDP_Blocking_Test::run -> Invalid select read counter\n";
        return false;
    }

    char receive_buffer[MSG_SIZE];
    std::string received_address;
    unsigned short received_port;

    if (!receive(receive_buffer, sizeof(receive_buffer), received_address, received_port))
        return false;

    if ((address != received_address) || (port != received_port))
    {
        std::cout << "Socket_UDP_Blocking_Test::run -> Invalid received message parameters:\n";
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

    if (!close())
        return false;

    std::cout << "Socket UDP blocking test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool Socket_UDP_Blocking_Connect_Test::run(Socket::Address_Family family, std::string address, unsigned short port)
{
    std::cout << "Socket UDP blocking connect test initialized\n";

    if (!configure_socket(family, address, port, false, false))
        return false;

    _connected = false;

    if (!connect(address, port))
        return false;

    if (!_connected)
    {
        std::cout << "Socket_UDP_Blocking_Connect_Test::run -> Socket not connected\n";
        return false;
    }

    const int MSG_SIZE = 256;
    char send_buffer[MSG_SIZE];

    for (int i = 0; i < MSG_SIZE; i++)
        send_buffer[i] = i;

    if (!send(send_buffer, sizeof(send_buffer)))
        return false;

    int read;

    if (!select(MAX_WAIT_TIME, &read, NULL, NULL))
        return false;

    if (read != 1)
    {
        std::cout << "Socket_UDP_Blocking_Connect_Test::run -> Invalid select read counter\n";
        return false;
    }

    char receive_buffer[MSG_SIZE];

    if (!receive(receive_buffer, sizeof(receive_buffer)))
        return false;

    if (memcmp(send_buffer, receive_buffer, MSG_SIZE) != 0)
    {
        std::cout << "Socket_UDP_Blocking_Connect_Test::run -> Invalid received message\n";
        return false;
    }

    if (!close())
        return false;

    std::cout << "Socket UDP blocking connect test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool Socket_UDP_Non_Blocking_Test::run(Socket::Address_Family family, std::string address, unsigned short port)
{
    std::cout << "Socket UDP non-blocking test initialized\n";

    if (!configure_socket(family, address, port, true, false))
        return false;

    const int MSG_SIZE = 256;
    char send_buffer[MSG_SIZE];

    for (int i = 0; i < MSG_SIZE; i++)
        send_buffer[i] = i;

    if (!send(send_buffer, sizeof(send_buffer), address, port))
        return false;

    int read;

    if (!select(MAX_WAIT_TIME, &read, NULL, NULL))
        return false;

    if (read != 1)
    {
        std::cout << "Socket_UDP_Non_Blocking_Test::run -> Invalid select read counter\n";
        return false;
    }

    char receive_buffer[MSG_SIZE];
    std::string received_address;
    unsigned short received_port;

    if (!receive(receive_buffer, sizeof(receive_buffer), received_address, received_port))
        return false;

    if ((address != received_address) || (port != received_port))
    {
        std::cout << "Socket_UDP_Non_Blocking_Test::run -> Invalid received message parameters:\n";
        std::cout << std::setw(20) << "Local Address: " << address << "\n";
        std::cout << std::setw(20) << "Local Port: " << port << "\n";
        std::cout << std::setw(20) << "Received Address: " << received_address << "\n";
        std::cout << std::setw(20) << "Received Port: " << received_port << "\n";
        return false;
    }

    if (memcmp(send_buffer, receive_buffer, MSG_SIZE) != 0)
    {
        std::cout << "Socket_UDP_Non_Blocking_Test::run -> Invalid received message\n";
        return false;
    }

    if (!close())
        return false;

    std::cout << "Socket UDP non-blocking test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool Socket_UDP_Non_Blocking_Connect_Test::run(Socket::Address_Family family, std::string address, unsigned short port)
{
    std::cout << "Socket UDP non-blocking connect test initialized\n";

    if (!configure_socket(family, address, port, true, false))
        return false;

    unsigned long start = Util_Functions::get_tick();
    _connected = false;

    if (!connect(address, port))
        return false;

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if (_connected)
            break;

        Util_Functions::delay(DELAY);
    }

    if (!_connected)
    {
        std::cout << "Socket_UDP_Non_Blocking_Connect_Test::run -> Socket not connected\n";
        return false;
    }

    const int MSG_SIZE = 256;
    char send_buffer[MSG_SIZE];

    for (int i = 0; i < MSG_SIZE; i++)
        send_buffer[i] = i;

    if (!send(send_buffer, sizeof(send_buffer)))
        return false;

    int read;

    if (!select(MAX_WAIT_TIME, &read, NULL, NULL))
        return false;

    if (read != 1)
    {
        std::cout << "Socket_UDP_Non_Blocking_Connect_Test::run -> Invalid select read counter\n";
        return false;
    }

    char receive_buffer[MSG_SIZE];

    if (!receive(receive_buffer, sizeof(receive_buffer)))
        return false;

    if (memcmp(send_buffer, receive_buffer, MSG_SIZE) != 0)
    {
        std::cout << "Socket_UDP_Non_Blocking_Connect_Test::run -> Invalid received message\n";
        return false;
    }

    if (!close())
        return false;

    std::cout << "Socket UDP non-blocking connect test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool Socket_UDP_Non_Blocking_Control_Test::run(Socket::Address_Family family, std::string address, unsigned short port)
{
    std::cout << "Socket UDP non-blocking control test initialized\n";

    Socket_Control &control = Socket_Control::instance();

    if (!configure_socket(family, address, port, true, false))
        return false;

    if (!control.add_socket(_socket_udp))
    {
        std::cout << "Socket_UDP_Non_Blocking_Control_Test::run -> Failed to add socket to control\n";
        return false;
    }

    unsigned long start = Util_Functions::get_tick();
    _connected = false;

    if (!connect(address, port))
        return false;

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if (_connected)
            break;

        Util_Functions::delay(DELAY);
    }

    if (!_connected)
    {
        std::cout << "Socket_UDP_Non_Blocking_Control_Test::run -> Socket not connected\n";
        return false;
    }

    const int MSG_SIZE = 256;
    char send_buffer[MSG_SIZE];

    for (int i = 0; i < MSG_SIZE; i++)
        send_buffer[i] = i;

    start = Util_Functions::get_tick();
    _received_buffer[0] = 0;
    _received_size = 0;
    _received_address.clear();
    _received_port = INVALID_UNSIGNED_SHORT;

    if (!send(send_buffer, sizeof(send_buffer)))
        return false;

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if (_received_size == MSG_SIZE)
            break;

        Util_Functions::delay(DELAY);
    }

    if (_received_size != MSG_SIZE)
    {
        std::cout << "Socket_UDP_Non_Blocking_Control_Test::run -> Message not received:\n";
        std::cout << std::setw(20) << "Expected: " << MSG_SIZE << "\n";
        std::cout << std::setw(20) << "Received: " << _received_size << "\n";
        return false;
    }

    if ((address != _received_address) || (port != _received_port))
    {
        std::cout << "Socket_UDP_Non_Blocking_Control_Test::run -> Invalid received message parameters:\n";
        std::cout << std::setw(20) << "Local Address: " << address << "\n";
        std::cout << std::setw(20) << "Local Port: " << port << "\n";
        std::cout << std::setw(20) << "Received Address: " << _received_address << "\n";
        std::cout << std::setw(20) << "Received Port: " << _received_port << "\n";
        return false;
    }

    if (memcmp(send_buffer, _received_buffer, MSG_SIZE) != 0)
    {
        std::cout << "Socket_UDP_Non_Blocking_Control_Test::run -> Invalid received message\n";
        return false;
    }

    if (!control.remove_socket(_socket_udp))
    {
        std::cout << "Socket_UDP_Non_Blocking_Control_Test::run -> Failed to remove socket from control\n";
        return false;
    }

    if (!close())
        return false;

    std::cout << "Socket UDP non-blocking control test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool Socket_TCP_Blocking_Test::run(Socket::Address_Family family, std::string address, unsigned short port)
{
    std::cout << "Socket TCP blocking test initialized\n";

    _current_socket = &_socket_tcp_client;
    if (!configure_socket(family, address, 0, false, true))
        return false;

    _current_socket = &_socket_tcp_server;
    if (!configure_socket(family, address, port, false, true))
        return false;

    if (!listen(10))
        return false;

    _current_socket = &_socket_tcp_client;
    _connected = false;
    _accepted_socket = NULL;
    _accepted_address = "";
    _accepted_port = INVALID_UNSIGNED_SHORT;

    if (!connect(address, port))
        return false;

    if (!_connected)
    {
        std::cout << "Socket_TCP_Blocking_Test::run -> Socket not connected\n";
        return false;
    }

    _current_socket = &_socket_tcp_server;
    int read;

    if (!select(MAX_WAIT_TIME, &read, NULL, NULL))
        return false;

    if (read != 1)
    {
        std::cout << "Socket_TCP_Blocking_Test::run -> Invalid server select read counter\n";
        return false;
    }

    socket_t accepted = INVALID_SOCKET;
    if (!accept(accepted, _accepted_address, _accepted_port))
    {
        std::cout << "Socket_TCP_Blocking_Test::run -> Failed to accept socket\n";
        return false;
    }

    if (address != _accepted_address)
    {
        std::cout << "Socket_TCP_Blocking_Test::run -> Invalid accepted parameters:\n";
        std::cout << std::setw(20) << "Local Address: " << address << "\n";
        std::cout << std::setw(20) << "Accepted Address: " << _accepted_address << "\n";
        return false;
    }

    _accepted_socket = new Socket_TCP_Client();
    _accepted_socket->set_socket(accepted);
    _accepted_socket->set_state(Socket::STATE_CONNECTED);

    _current_socket = &_socket_tcp_client;
    const int MSG_SIZE = 256;
    char send_buffer[MSG_SIZE];

    for (int i = 0; i < MSG_SIZE; i++)
        send_buffer[i] = i;

    if (!send(send_buffer, sizeof(send_buffer)))
        return false;

    _current_socket = _accepted_socket;
    if (!select(MAX_WAIT_TIME, &read, NULL, NULL))
        return false;

    if (read != 1)
    {
        std::cout << "Socket_TCP_Blocking_Test::run -> Invalid accepted select read counter\n";
        return false;
    }

    char receive_buffer[MSG_SIZE];

    if (!receive(receive_buffer, sizeof(receive_buffer)))
        return false;

    if (memcmp(send_buffer, receive_buffer, MSG_SIZE) != 0)
    {
        std::cout << "Socket_TCP_Blocking_Test::run -> Invalid received message\n";
        return false;
    }

    _current_socket = &_socket_tcp_client;
    if (!close())
        return false;

    _current_socket = &_socket_tcp_server;
    if (!close())
        return false;

    _current_socket = _accepted_socket;
    if (!close())
        return false;

    std::cout << "Socket TCP blocking test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool Socket_TCP_Non_Blocking_Test::run(Socket::Address_Family family, std::string address, unsigned short port)
{
    std::cout << "Socket TCP non-blocking test initialized\n";

    _current_socket = &_socket_tcp_client;
    if (!configure_socket(family, address, 0, true, true))
        return false;

    _current_socket = &_socket_tcp_server;
    if (!configure_socket(family, address, port, true, true))
        return false;

    if (!listen(10))
        return false;

    _current_socket = &_socket_tcp_client;
    _accepted_socket = NULL;
    _accepted_address = "";
    _accepted_port = INVALID_UNSIGNED_SHORT;

    if (!connect(address, port))
        return false;

    int write;

    if (!select(MAX_WAIT_TIME, NULL, &write, NULL))
        return false;

    if (write != 1)
    {
        std::cout << "Socket_TCP_Non_Blocking_Test::run -> Invalid client select write counter\n";
        return false;
    }

    _current_socket = &_socket_tcp_server;
    int read;

    if (!select(MAX_WAIT_TIME, &read, NULL, NULL))
        return false;

    if (read != 1)
    {
        std::cout << "Socket_TCP_Non_Blocking_Test::run -> Invalid server select read counter\n";
        return false;
    }

    socket_t accepted = INVALID_SOCKET;
    if (!accept(accepted, _accepted_address, _accepted_port))
    {
        std::cout << "Socket_TCP_Non_Blocking_Test::run -> Failed to accept socket\n";
        return false;
    }

    if (address != _accepted_address)
    {
        std::cout << "Socket_TCP_Non_Blocking_Test::run -> Invalid accepted parameters:\n";
        std::cout << std::setw(20) << "Local Address: " << address << "\n";
        std::cout << std::setw(20) << "Accepted Address: " << _accepted_address << "\n";
        return false;
    }

    _accepted_socket = new Socket_TCP_Client();
    _accepted_socket->set_socket(accepted);
    _accepted_socket->set_state(Socket::STATE_CONNECTED);

    _current_socket = &_socket_tcp_client;
    const int MSG_SIZE = 256;
    char send_buffer[MSG_SIZE];

    for (int i = 0; i < MSG_SIZE; i++)
        send_buffer[i] = i;

    if (!send(send_buffer, sizeof(send_buffer)))
        return false;

    _current_socket = _accepted_socket;
    if (!select(MAX_WAIT_TIME, &read, NULL, NULL))
        return false;

    if (read != 1)
    {
        std::cout << "Socket_TCP_Non_Blocking_Test::run -> Invalid accepted select read counter\n";
        return false;
    }

    char receive_buffer[MSG_SIZE];

    if (!receive(receive_buffer, sizeof(receive_buffer)))
        return false;

    if (memcmp(send_buffer, receive_buffer, MSG_SIZE) != 0)
    {
        std::cout << "Socket_TCP_Non_Blocking_Test::run -> Invalid received message\n";
        return false;
    }

    _current_socket = &_socket_tcp_client;
    if (!close())
        return false;

    _current_socket = &_socket_tcp_server;
    if (!close())
        return false;

    _current_socket = _accepted_socket;
    if (!close())
        return false;

    std::cout << "Socket TCP non-blocking test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool Socket_TCP_Non_Blocking_Control_Test::run(Socket::Address_Family family, std::string address, unsigned short port)
{
    std::cout << "Socket TCP non-blocking control test initialized\n";

    Socket_Control &control = Socket_Control::instance();

    _current_socket = &_socket_tcp_client;
    if (!configure_socket(family, address, 0, true, true))
        return false;

    _current_socket = &_socket_tcp_server;
    if (!configure_socket(family, address, port, true, true))
        return false;

    if (!control.add_socket(_socket_tcp_client))
    {
        std::cout << "Socket_TCP_Non_Blocking_Control_Test::run -> Failed to add client socket to control\n";
        return false;
    }

    if (!control.add_socket(_socket_tcp_server))
    {
        std::cout << "Socket_TCP_Non_Blocking_Control_Test::run -> Failed to add server socket to control\n";
        return false;
    }

    if (!listen(10))
        return false;

    unsigned long start = Util_Functions::get_tick();
    _current_socket = &_socket_tcp_client;
    _connected = false;
    _accepted_socket = NULL;
    _accepted_address = "";
    _accepted_port = INVALID_UNSIGNED_SHORT;

    if (!connect(address, port))
        return false;

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if (_connected)
            break;

        Util_Functions::delay(DELAY);
    }

    if (!_connected)
    {
        std::cout << "Socket_TCP_Non_Blocking_Control_Test::run -> Socket not connected\n";
        return false;
    }

    start = Util_Functions::get_tick();

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if (_accepted_socket)
            break;

        Util_Functions::delay(DELAY);
    }

    if (!_accepted_socket)
    {
        std::cout << "Socket_TCP_Non_Blocking_Control_Test::run -> Socket not accepted\n";
        return false;
    }

    if (address != _accepted_address)
    {
        std::cout << "Socket_TCP_Non_Blocking_Control_Test::run -> Invalid accepted parameters:\n";
        std::cout << std::setw(20) << "Local Address: " << address << "\n";
        std::cout << std::setw(20) << "Accepted Address: " << _accepted_address << "\n";
        return false;
    }

    _current_socket = _accepted_socket;

    if (!set_callbacks())
        return false;

    if (!set_so_snd_buf())
        return false;

    if (!set_so_rcv_buf())
        return false;

    if (!set_so_reuse_addr())
        return false;

    if (!set_non_blocking(true))
        return false;

    if (!control.add_socket(*_accepted_socket))
    {
        std::cout << "Socket_TCP_Non_Blocking_Control_Test::run -> Failed to add accepted socket to control\n";
        return false;
    }

    _current_socket = &_socket_tcp_client;
    const int MSG_SIZE = 256;
    char send_buffer[MSG_SIZE];

    for (int i = 0; i < MSG_SIZE; i++)
        send_buffer[i] = i;

    _received_buffer[0] = 0;
    _received_size = 0;
    _received_address.clear();
    _received_port = INVALID_UNSIGNED_SHORT;

    if (!send(send_buffer, sizeof(send_buffer)))
        return false;

    _current_socket = _accepted_socket;
    start = Util_Functions::get_tick();

    while ((Util_Functions::get_tick() - start) < MAX_WAIT_TIME)
    {
        if (_received_size == MSG_SIZE)
            break;

        Util_Functions::delay(DELAY);
    }

    if (_received_size != MSG_SIZE)
    {
        std::cout << "Socket_TCP_Non_Blocking_Control_Test::run -> Message not received:\n";
        std::cout << std::setw(20) << "Expected: " << MSG_SIZE << "\n";
        std::cout << std::setw(20) << "Received: " << _received_size << "\n";
        return false;
    }

    if (memcmp(send_buffer, _received_buffer, MSG_SIZE) != 0)
    {
        std::cout << "Socket_TCP_Non_Blocking_Control_Test::run -> Invalid received message\n";
        return false;
    }

    if (!control.remove_socket(_socket_tcp_client))
    {
        std::cout << "Socket_TCP_Non_Blocking_Control_Test::run -> Failed to remove client socket from control\n";
        return false;
    }

    if (!control.remove_socket(_socket_tcp_server))
    {
        std::cout << "Socket_TCP_Non_Blocking_Control_Test::run -> Failed to remove server socket from control\n";
        return false;
    }

    if (!control.remove_socket(*_accepted_socket))
    {
        std::cout << "Socket_TCP_Non_Blocking_Control_Test::run -> Failed to remove accepted socket from control\n";
        return false;
    }

    _current_socket = &_socket_tcp_client;
    if (!close())
        return false;

    _current_socket = &_socket_tcp_server;
    if (!close())
        return false;

    _current_socket = _accepted_socket;
    if (!close())
        return false;

    std::cout << "Socket TCP non-blocking control test completed successfully\n";
    return true;
}

//-------------------------------------------
