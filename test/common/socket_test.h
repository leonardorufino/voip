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

    bool create(Socket &socket, Socket::Address_Family family);
    bool close(Socket &socket);

    bool set_so_snd_buf(Socket &socket);
    bool set_so_rcv_buf(Socket &socket);
    bool set_so_reuse_addr(Socket &socket);

    bool bind(Socket &socket, std::string address, unsigned short port);
    bool connect(Socket &socket, std::string address, unsigned short port);
    bool send(Socket &socket, const char *buffer, int size);
    bool send(Socket &socket, const char *buffer, int size, std::string address, unsigned short port);
    bool receive(Socket &socket, char *buffer, int size);
    bool receive(Socket &socket, char *buffer, int size, std::string &address, unsigned short &port);
    bool select_read(Socket &socket);

    static bool get_network_addresses(std::list<Socket::Network_Address> &addresses);
    static bool check_network_address(Socket::Address_Family family, std::string address);
};

//-------------------------------------------
