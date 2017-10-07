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

#include "sip_defs.h"
#include "util/util_defs.h"
#include "util/socket.h"
#include <string>

class SIP_Transport_TCP_Client;

class SIP_Transport
{
public:
    static const unsigned short INVALID_PORT = INVALID_UNSIGNED_SHORT;

    typedef bool (connect_callback)(void *data, SIP_Transport *transport, bool success);
    typedef bool (accept_callback)(void *data, SIP_Transport *transport, SIP_Transport_TCP_Client *accepted, std::string address, unsigned short port);
    typedef bool (receive_callback)(void *data, SIP_Transport *transport, const char *buffer, int size, std::string address, unsigned short port);

public:
    SIP_Transport(SIP_Object_ID id);
    virtual ~SIP_Transport();

    void set_connect_callback(connect_callback *callback, void *data);
    void set_accept_callback(accept_callback *callback, void *data);
    void set_receive_callback(receive_callback *callback, void *data);

    virtual bool init(std::string address, unsigned short port);
    virtual bool close();

    void set_id(SIP_Object_ID id) { _id = id; }

    std::string get_address() { return _address; }
    unsigned short get_port() { return _port; }

    bool send_message(const char *buffer, int size, std::string address, unsigned short port);

    static bool socket_connect_callback(void *data, bool success);
    static bool socket_accept_callback(void *data, Socket_TCP_Client *accepted, std::string address, unsigned short port);
    static bool socket_receive_callback(void *data, const char *buffer, int size, std::string address, unsigned short port);

protected:
    SIP_Object_ID _id;

    std::string _address;
    unsigned short _port;

    Socket *_socket;

    connect_callback *_connect_callback;
    void *_connect_callback_data;

    accept_callback *_accept_callback;
    void *_accept_callback_data;

    receive_callback *_receive_callback;
    void *_receive_callback_data;

    static Logger _logger;
};

//-------------------------------------------

class SIP_Transport_UDP : public SIP_Transport
{
public:
    SIP_Transport_UDP(SIP_Object_ID id) : SIP_Transport(id) {}
    ~SIP_Transport_UDP() {}

    bool init(std::string address, unsigned short port);
};

//-------------------------------------------

class SIP_Transport_TCP_Client : public SIP_Transport
{
public:
    SIP_Transport_TCP_Client(SIP_Object_ID id) : SIP_Transport(id), _remote_port(INVALID_PORT) {}
    ~SIP_Transport_TCP_Client() {}

    bool init(std::string address, unsigned short port);
    bool connect(std::string address, unsigned short port);

    void set_remote_address(std::string address) { _remote_address = address; }
    std::string get_remote_address() { return _remote_address; }

    void set_remote_port(unsigned short port) { _remote_port = port; }
    unsigned short get_remote_port() { return _remote_port; }

    bool is_connected() { return _socket->get_state() == Socket::STATE_CONNECTED; }

private:
    std::string _remote_address;
    unsigned short _remote_port;
};

//-------------------------------------------

class SIP_Transport_TCP_Server : public SIP_Transport
{
public:
    SIP_Transport_TCP_Server(SIP_Object_ID id) : SIP_Transport(id) {}
    ~SIP_Transport_TCP_Server() {}

    bool init(std::string address, unsigned short port);
    bool listen(int backlog);
    bool accept(socket_t &accept_socket, std::string &address, unsigned short &port);

    bool is_listening() { return _socket->get_state() == Socket::STATE_LISTENING; }
};

//-------------------------------------------
