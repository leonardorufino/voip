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

#include "rtp/rtp_session.h"
#include "util/util_functions.h"
#include <iomanip>
#include <thread>
#include <mutex>

class RTP_Session_Test
{
public:
    static const unsigned long THREAD_DELAY = 10;
    static const unsigned long MAX_WAIT_TIME = 5000;
    static const unsigned long DELAY = 25;

public:
    RTP_Session_Test();
    virtual ~RTP_Session_Test();

    static bool init();
    template<class T> static bool run(Socket::Address_Family family, std::string address, unsigned short port,
                                      RTP_Transport_Type transport);

    static void thread(RTP_Session_Test *test);

protected:
    virtual bool run(Socket::Address_Family family, std::string address, unsigned short port, RTP_Transport_Type transport) = 0;

    virtual bool init_session(std::string local_address, unsigned short local_port, std::string remote_address,
                              unsigned short remote_port, RTP_Transport_Type transport);
    virtual bool close_session();
    virtual bool set_callbacks();
    virtual void clear_callback_params();

    bool send_packet();
    bool receive_packet();

    static bool receive_packet_callback(void *data, RTP_Session *session, RTP_Packet *packet);

    static bool get_network_addresses(std::list<Socket::Network_Address> &addresses);
    static bool check_network_address(Socket::Address_Family family, std::string address);

protected:
    RTP_Session *_session;

    RTP_Packet *_send_packet;
    RTP_Packet *_packet_callback;

    std::mutex _thread_mutex;

private:
    std::thread _thread;
    bool _stop_thread;
};

//-------------------------------------------
