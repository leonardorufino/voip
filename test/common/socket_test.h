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

#pragma once

#include "common/common_functions.h"
#include "common/socket.h"
#include <iomanip>
#include <cstring>

class Socket_Test
{
public:
    Socket_Test() {}
    virtual ~Socket_Test() {}

    static bool init();

protected:
    virtual bool run(Socket::Address_Family family, std::string address, unsigned short port) = 0;
    virtual Socket &get_socket() = 0;

    virtual bool set_callbacks();

    bool create(Socket::Address_Family family);
    bool close();

    bool set_so_snd_buf();
    bool set_so_rcv_buf();
    bool set_so_reuse_addr();
    bool set_non_blocking(bool non_blocking = true);

    bool bind(std::string address, unsigned short port);
    bool connect(std::string address, unsigned short port);
    bool send(const char *buffer, int size);
    bool send(const char *buffer, int size, std::string address, unsigned short port);
    bool receive(char *buffer, int size);
    bool receive(char *buffer, int size, std::string &address, unsigned short &port);
    bool select(unsigned long timeout, int *read, int *write, int *except);

    static bool get_network_addresses(std::list<Socket::Network_Address> &addresses);
    static bool check_network_address(Socket::Address_Family family, std::string address);

    static bool connect_callback(void *data, bool success);
    static bool accept_callback(void *data, socket_t socket, std::string address, unsigned short port);
    static bool receive_callback(void *data, const char *buffer, int size, std::string address, unsigned short port);

protected:
    static bool _connected;

    static socket_t _accepted_socket;
    static std::string _accepted_address;
    static unsigned short _accepted_port;

    static char _received_buffer[Socket_Control::RECEIVE_BUFFER_SIZE + 1];
    static int _received_size;
    static std::string _received_address;
    static unsigned short _received_port;
};

//-------------------------------------------

class Socket_UDP_Blocking_Test : public Socket_Test
{
public:
    Socket_UDP_Blocking_Test() {}
    virtual ~Socket_UDP_Blocking_Test() {}

    bool run(Socket::Address_Family family, std::string address, unsigned short port);
    Socket &get_socket() { return _socket_udp; }

private:
    Socket_UDP _socket_udp;
};

//-------------------------------------------

class Socket_UDP_Blocking_Connect_Test : public Socket_Test
{
public:
    Socket_UDP_Blocking_Connect_Test() {}
    virtual ~Socket_UDP_Blocking_Connect_Test() {}

    bool run(Socket::Address_Family family, std::string address, unsigned short port);
    Socket &get_socket() { return _socket_udp; }

private:
    Socket_UDP _socket_udp;
};

//-------------------------------------------

class Socket_UDP_Non_Blocking_Test : public Socket_Test
{
public:
    Socket_UDP_Non_Blocking_Test() {}
    virtual ~Socket_UDP_Non_Blocking_Test() {}

    bool run(Socket::Address_Family family, std::string address, unsigned short port);
    Socket &get_socket() { return _socket_udp; }

private:
    Socket_UDP _socket_udp;
};

//-------------------------------------------

class Socket_UDP_Non_Blocking_Connect_Test : public Socket_Test
{
public:
    Socket_UDP_Non_Blocking_Connect_Test() {}
    virtual ~Socket_UDP_Non_Blocking_Connect_Test() {}

    bool run(Socket::Address_Family family, std::string address, unsigned short port);
    Socket &get_socket() { return _socket_udp; }

private:
    Socket_UDP _socket_udp;
};

//-------------------------------------------

class Socket_UDP_Non_Blocking_Control_Test : public Socket_Test
{
public:
    Socket_UDP_Non_Blocking_Control_Test() {}
    virtual ~Socket_UDP_Non_Blocking_Control_Test() {}

    bool run(Socket::Address_Family family, std::string address, unsigned short port);
    Socket &get_socket() { return _socket_udp; }

private:
    Socket_UDP _socket_udp;
};

//-------------------------------------------
