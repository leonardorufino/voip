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

class SIP_Transport_Test
{
public:
    SIP_Transport_Test();
    virtual ~SIP_Transport_Test() {}

    static bool init();

protected:
    virtual bool run(Socket::Address_Family family, std::string address, unsigned short port) = 0;
    virtual SIP_Transport &get_transport() = 0;

    virtual bool set_callbacks();

    std::string create_request();

    static bool connect_callback(void *data, SIP_Transport *transport, bool success);
    static bool accept_callback(void *data, SIP_Transport *transport, SIP_Transport_TCP_Client *accepted,
                                std::string address, unsigned short port);
    static bool receive_callback(void *data, SIP_Transport *transport, const char *buffer, int size,
                                 std::string address, unsigned short port);

    static bool get_network_addresses(std::list<Socket::Network_Address> &addresses);
    static bool check_network_address(Socket::Address_Family family, std::string address);

protected:
    bool _connected;

    SIP_Transport_TCP_Client *_accepted_transport;
    std::string _accepted_address;
    unsigned short _accepted_port;

    char _received_buffer[Socket_Control::RECEIVE_BUFFER_SIZE + 1];
    int _received_size;
    std::string _received_address;
    unsigned short _received_port;
};
