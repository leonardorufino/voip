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

#include "rtp_packet.h"
#include "rtp_transport.h"

class RTP_Session
{
public:
    typedef bool (receive_packet_callback)(void *data, RTP_Session *session, RTP_Packet *packet);

    static const unsigned short SEND_BUFFER_SIZE = 5000;
    static const unsigned short INVALID_PORT = INVALID_UNSIGNED_SHORT;

public:
    RTP_Session(RTP_Object_ID id) : _id(id), _local_port(INVALID_PORT), _remote_port(INVALID_PORT), _transport(NULL) {}
    ~RTP_Session();

    void set_receive_packet_callback(receive_packet_callback *callback, void *data);

    bool init(std::string local_address, unsigned short local_port, std::string remote_address, unsigned short remote_port,
              RTP_Transport_Type transport);
    bool close();

    void add_transport(RTP_Transport *transport);
    void remove_transport();

    bool send_packet(RTP_Packet *packet);
    bool receive_packet(RTP_Packet *packet);

public:
    static bool transport_receive_callback(void *data, RTP_Transport *transport, RTP_Packet *packet, std::string address,
                                           unsigned short port);

private:
    RTP_Object_ID _id;

    std::string _local_address;
    unsigned short _local_port;

    std::string _remote_address;
    unsigned short _remote_port;

    receive_packet_callback *_receive_packet_callback;
    void *_receive_packet_callback_data;

    RTP_Transport *_transport;

    char _send_buffer[SEND_BUFFER_SIZE + 1];

    static Logger _logger;
};
