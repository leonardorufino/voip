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

#include "rtp/rtp_transport.h"
#include "util/util_functions.h"
#include "util/socket.h"
#include <iomanip>
#include <thread>

class RTP_Transport_Test
{
public:
    static const unsigned long THREAD_DELAY = 10;
    static const unsigned long MAX_WAIT_TIME = 5000;
    static const unsigned long DELAY = 25;
    static const unsigned short MAX_PACKET_SIZE = 1000;

public:
    static bool init();
    template<class T> static bool run(Socket::Address_Family family, std::string address, unsigned short port);

    static void thread(RTP_Transport_Test *test);

protected:
    RTP_Transport_Test();
    virtual ~RTP_Transport_Test();

    virtual bool run(Socket::Address_Family family, std::string address, unsigned short port) = 0;
    virtual RTP_Transport *get_transport() = 0;
    virtual bool set_callbacks();
    virtual void clear_callback_params();

    unsigned int get_next_transport_id();

    bool create_packet(char *packet, int &size);

    static bool receive_callback(void *data, RTP_Transport *transport, RTP_Packet *packet, std::string address, unsigned short port);

    static bool get_network_addresses(std::list<Socket::Network_Address> &addresses);
    static bool check_network_address(Socket::Address_Family family, std::string address);

protected:
    std::list<RTP_Packet *> _received_packets;
    std::string _received_address;
    unsigned short _received_port;

    std::mutex _thread_mutex;

private:
    std::thread _thread;
    bool _stop_thread;
};

//-------------------------------------------
//-------------------------------------------

class RTP_Transport_UDP_Test : public RTP_Transport_Test
{
public:
    RTP_Transport_UDP_Test();
    virtual ~RTP_Transport_UDP_Test();

    bool init(std::string address, unsigned short port);
    bool send_packet(const char *buffer, int size, std::string address, unsigned short port);
    bool close();

    bool run(Socket::Address_Family family, std::string address, unsigned short port);
    RTP_Transport *get_transport() { return _transport_udp; }

protected:
    RTP_Transport_UDP *_transport_udp;
};

//-------------------------------------------
