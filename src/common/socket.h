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

#include "common/log_manager.h"
#include <string>
#include <cstring>
#include <list>

#ifdef WIN32
    #include <winsock2.h>
    #include <windows.h>
    #include <ws2tcpip.h>
    #include <iphlpapi.h>

    #define GET_LAST_ERROR      GetLastError()

    typedef SOCKET socket_t;
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/udp.h>
    #include <arpa/inet.h>
    #include <ifaddrs.h>

    #define INVALID_SOCKET      -1
    #define GET_LAST_ERROR      errno

    typedef int socket_t;
#endif

class Socket
{
public:
    enum Address_Family
    {
        ADDRESS_FAMILY_IPv4,
        ADDRESS_FAMILY_IPv6,
        ADDRESS_FAMILY_INVALID,
    };

    struct Network_Address
    {
        Address_Family _family;
        std::string _address;
        unsigned long _scope_id;
    };

public:
    Socket();
    ~Socket();

    virtual bool create(Address_Family family) = 0;

    bool create(int af, int type, int protocol);
    bool close();

    bool set_so_snd_buf(int size = 128 * 1024);
    bool set_so_rcv_buf(int size = 128 * 1024);
    bool set_so_reuse_addr(int value = 1);

    bool bind(std::string address, unsigned short port);
    bool connect(std::string address, unsigned short port);
    bool send(const char *buffer, int size);
    bool send(const char *buffer, int size, std::string address, unsigned short port);
    int receive(char *buffer, int size);
    int receive(char *buffer, int size, std::string &address, unsigned short &port);
    int select_read();

    static int address_family_to_af(Address_Family family);
    static Address_Family address_to_address_family(std::string address);
    static bool address_to_sockaddr(std::string address, unsigned short port, sockaddr_storage &ss);
    static bool sockaddr_to_address(sockaddr_storage &ss, std::string &address, unsigned short &port);
    static bool sockaddr_to_address(sockaddr_storage &ss, std::string &address);

    static bool get_network_addresses(std::list<Network_Address> &addresses);

#ifdef WIN32
    static bool Startup();
#endif

protected:
    socket_t _socket;

    static Logger _logger;
};

//-------------------------------------------

class Socket_UDP : public Socket
{
public:
    Socket_UDP() {}
    ~Socket_UDP() {}

    bool create(Address_Family family);
};

//-------------------------------------------
