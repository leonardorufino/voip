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
#include <thread>

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
    #include <unistd.h>
    #include <fcntl.h>

    #define INVALID_SOCKET      -1
    #define GET_LAST_ERROR      errno

    typedef int socket_t;
#endif

class Socket
{
public:
    typedef bool (connect_callback)(void *data, bool success);
    typedef bool (receive_callback)(void *data, const char *buffer, int size, std::string address, unsigned short port);

    enum Address_Family
    {
        ADDRESS_FAMILY_IPv4,
        ADDRESS_FAMILY_IPv6,
        ADDRESS_FAMILY_INVALID,
    };

    enum State
    {
        STATE_IDLE,
        STATE_OPEN,
        STATE_LISTENING,
        STATE_CONNECTING,
        STATE_CONNECTED,
        STATE_CLOSING,
        STATE_CLOSED,
        STATE_INVALID
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

    void set_state(State state) { _state = state; }
    State get_state() { return _state; }

    socket_t &get_socket() { return _socket; }

    void set_connect_callback(connect_callback *callback, void *data);
    bool call_connect_callback(bool success);

    void set_receive_callback(receive_callback *callback, void *data);
    bool call_receive_callback(const char *buffer, int size, std::string address, unsigned short port);

    virtual bool create(Address_Family family) = 0;

    bool create(int af, int type, int protocol);
    bool close();

    bool set_so_snd_buf(int size = 128 * 1024);
    bool set_so_rcv_buf(int size = 128 * 1024);
    bool set_so_reuse_addr(int value = 1);
    bool set_non_blocking(bool non_blocking = true);
    bool get_so_error(int &value);

    bool bind(std::string address, unsigned short port);
    bool listen(int backlog);
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

    static Logger &get_logger() { return _logger; }

protected:
    State _state;
    socket_t _socket;

    connect_callback *_connect_callback;
    void *_connect_data;

    receive_callback *_receive_callback;
    void *_receive_data;

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

class Socket_Control
{
public:
    static const unsigned long SELECT_TIMEOUT = 100; // Milliseconds
    static const unsigned short RECEIVE_BUFFER_SIZE = 5000;

public:
    Socket_Control() : _stopped(true) {}
    ~Socket_Control();

    static Socket_Control &instance();

    bool start();
    bool stop();

    bool add_socket(Socket &socket);
    bool remove_socket(Socket &socket);

private:
    static void control_thread();

protected:
    std::thread _control_thread;

    std::list<Socket *> _socket_list;
    std::mutex _socket_list_mutex;

    char _receive_buffer[RECEIVE_BUFFER_SIZE + 1];
    bool _stopped;
};

//-------------------------------------------
