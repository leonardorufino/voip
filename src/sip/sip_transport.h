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

#include "util/util_defs.h"
#include "util/socket.h"
#include <string>

class SIP_Transport
{
public:
    static const unsigned short INVALID_PORT = INVALID_UNSIGNED_SHORT;

    typedef bool (connect_callback)(SIP_Transport *transport, bool success);
    typedef bool (accept_callback)(SIP_Transport *transport, SIP_Transport *accepted, std::string address, unsigned short port);
    typedef bool (receive_callback)(SIP_Transport *transport, const char *buffer, int size, std::string address, unsigned short port);

public:
    SIP_Transport();
    ~SIP_Transport();

    static bool start();
    static bool stop();

    void set_connect_callback(connect_callback *callback) { _connect_callback = callback; }
    void set_accept_callback(accept_callback *callback) { _accept_callback = callback; }
    void set_receive_callback(receive_callback *callback) { _receive_callback = callback; }

    virtual bool init(std::string address, unsigned short port);
    virtual bool close();

    std::string get_address() { return _address; }
    unsigned short get_port() { return _port; }

    bool send_message(const char *buffer, int size, std::string address, unsigned short port);

    static bool socket_connect_callback(void *data, bool success);
    static bool socket_accept_callback(void *data, Socket_TCP_Client *accepted, std::string address, unsigned short port);
    static bool socket_receive_callback(void *data, const char *buffer, int size, std::string address, unsigned short port);

protected:
    std::string _address;
    unsigned short _port;

    Socket *_socket;

    connect_callback *_connect_callback;
    accept_callback *_accept_callback;
    receive_callback *_receive_callback;

    static Logger _logger;
};

//-------------------------------------------

class SIP_Transport_UDP : public SIP_Transport
{
public:
    SIP_Transport_UDP() {}
    ~SIP_Transport_UDP() {}

    bool init(std::string address, unsigned short port);
};

//-------------------------------------------
