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

#include "rtp_defs.h"
#include "rtp_packet.h"
#include "util/util_defs.h"
#include "util/log_manager.h"
#include "util/socket.h"

class RTP_Transport
{
public:
    static const unsigned short INVALID_PORT = INVALID_UNSIGNED_SHORT;

    typedef bool (receive_callback)(void *data, RTP_Transport *transport, RTP_Packet *packet, std::string address, unsigned short port);

public:
    RTP_Transport(RTP_Object_ID id);
    virtual ~RTP_Transport();

    void set_receive_callback(receive_callback *callback, void *data);

    virtual bool init(std::string address, unsigned short port);
    virtual bool close();

    void set_id(RTP_Object_ID id) { _id = id; }

    std::string get_address() { return _address; }
    unsigned short get_port() { return _port; }

    bool send_message(const char *buffer, int size, std::string address, unsigned short port);
    virtual bool receive_message(const char *buffer, int size, std::string address, unsigned short port);

    static bool socket_receive_callback(void *data, const char *buffer, int size, std::string address, unsigned short port);

protected:
    RTP_Object_ID _id;

    std::string _address;
    unsigned short _port;

    Socket *_socket;

    receive_callback *_receive_callback;
    void *_receive_callback_data;

    static Logger _logger;
};

//-------------------------------------------

class RTP_Transport_UDP : public RTP_Transport
{
public:
    RTP_Transport_UDP(RTP_Object_ID id) : RTP_Transport(id) {}
    ~RTP_Transport_UDP() {}

    bool init(std::string address, unsigned short port);
};

//-------------------------------------------
