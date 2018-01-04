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

#include "sip/sip_transport.h"
#include "util/util_functions.h"
#include "util/socket.h"
#include <iomanip>
#include <thread>

class SIP_Transport_Test
{
public:
    static const unsigned long THREAD_DELAY = 10;
    static const unsigned long MAX_WAIT_TIME = 5000;
    static const unsigned long DELAY = 25;

public:
    static bool init();
    template<class T> static bool run(Socket::Address_Family family, std::string address, unsigned short port);

    static void thread(SIP_Transport_Test *test);

protected:
    SIP_Transport_Test();
    virtual ~SIP_Transport_Test();

    virtual bool run(Socket::Address_Family family, std::string address, unsigned short port) = 0;
    virtual SIP_Transport *get_transport() = 0;
    virtual bool set_callbacks();
    virtual void clear_callback_params();

    unsigned int get_next_transport_id();

    std::string create_request();
    std::string create_request(unsigned short fragment);

    static bool connect_callback(void *data, SIP_Transport *transport, bool success);
    static bool accept_callback(void *data, SIP_Transport *transport, SIP_Transport_TCP_Client *accepted, std::string address,
                                unsigned short port);
    static bool receive_callback(void *data, SIP_Transport *transport, SIP_Message *msg, std::string address, unsigned short port);

    static bool get_network_addresses(std::list<Socket::Network_Address> &addresses);
    static bool check_network_address(Socket::Address_Family family, std::string address);

protected:
    bool _connected;

    SIP_Transport_TCP_Client *_accepted_transport;
    std::string _accepted_address;
    unsigned short _accepted_port;

    std::list<SIP_Message *> _received_messages;
    std::string _received_address;
    unsigned short _received_port;

    std::mutex _thread_mutex;

private:
    std::thread _thread;
    bool _stop_thread;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Transport_UDP_Test : public SIP_Transport_Test
{
public:
    SIP_Transport_UDP_Test();
    virtual ~SIP_Transport_UDP_Test();

    bool init(std::string address, unsigned short port);
    bool send_message(const char *buffer, int size, std::string address, unsigned short port);
    bool close();

    bool run(Socket::Address_Family family, std::string address, unsigned short port);
    SIP_Transport *get_transport() { return _transport_udp; }

protected:
    SIP_Transport_UDP *_transport_udp;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Transport_TCP_Test : public SIP_Transport_Test
{
public:
    SIP_Transport_TCP_Test();
    virtual ~SIP_Transport_TCP_Test();

    bool init(std::string address, unsigned short port);
    bool listen(int backlog);
    bool connect(std::string address, unsigned short port);
    bool send_message(const char *buffer, int size, std::string address, unsigned short port);
    bool close();

    SIP_Transport *get_transport() { return _current_transport; }

protected:
    SIP_Transport_TCP_Client *_transport_tcp_client;
    SIP_Transport_TCP_Server *_transport_tcp_server;

    SIP_Transport *_current_transport;
};

//-------------------------------------------

class SIP_Transport_TCP_Complete_Test : public SIP_Transport_TCP_Test
{
public:
    SIP_Transport_TCP_Complete_Test() {}
    virtual ~SIP_Transport_TCP_Complete_Test() {}

    bool run(Socket::Address_Family family, std::string address, unsigned short port);
};

//-------------------------------------------

class SIP_Transport_TCP_Fragment_Test : public SIP_Transport_TCP_Test
{
public:
    SIP_Transport_TCP_Fragment_Test() {}
    virtual ~SIP_Transport_TCP_Fragment_Test() {}

    bool run(Socket::Address_Family family, std::string address, unsigned short port);
};

//-------------------------------------------
