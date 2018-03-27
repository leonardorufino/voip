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

#include "sip/sip_manager.h"
#include "util/util_functions.h"
#include <iomanip>
#include <thread>
#include <mutex>

class SIP_Manager_Test
{
public:
    static const unsigned long THREAD_DELAY = 10;
    static const unsigned long MAX_WAIT_TIME = 5000;
    static const unsigned long DELAY = 25;

public:
    SIP_Manager_Test();
    virtual ~SIP_Manager_Test();

    static bool init();
    template<class T> static bool run(Socket::Address_Family family, std::string address, unsigned short port,
                                      SIP_Transport_Type transport);

    static void thread(SIP_Manager_Test *test);

protected:
    virtual bool run(Socket::Address_Family family, std::string address, unsigned short port, SIP_Transport_Type transport) = 0;

    virtual bool create_user_agent(unsigned int user_agent_id, std::string address, unsigned short port);
    virtual bool remove_user_agent(unsigned int user_agent_id);
    virtual void clear_callback_params();

    bool send_request(unsigned int user_agent_id, unsigned int call_id, SIP_Method_Type method, std::string address = "",
                      unsigned short port = SIP_URI::INVALID_PORT, SIP_Transport_Type transport = SIP_TRANSPORT_INVALID);
    bool send_response(unsigned int user_agent_id, unsigned int call_id, SIP_Method_Type method, unsigned short status_code);
    bool receive_request(unsigned int user_agent_id, unsigned int call_id, SIP_Method_Type method);
    bool receive_response(unsigned int user_agent_id, unsigned int call_id, SIP_Method_Type method, unsigned short status_code);
    bool wait_timeout(unsigned int user_agent_id, unsigned int call_id);

    static bool receive_request_callback(void *data, unsigned int user_agent_id, unsigned int call_id, SIP_Request *request);
    static bool receive_response_callback(void *data, unsigned int user_agent_id, unsigned int call_id, SIP_Request *request,
                                          SIP_Response *response);

    static bool get_network_addresses(std::list<Socket::Network_Address> &addresses);
    static bool check_network_address(Socket::Address_Family family, std::string address);

protected:
    unsigned int _user_agent_id_callback;
    unsigned int _call_id_callback;
    std::list<SIP_Request *> _received_requests;
    SIP_Request *_request_callback;
    SIP_Response *_response_callback;

    std::mutex _thread_mutex;

private:
    std::thread _thread;
    bool _stop_thread;
};

//-------------------------------------------
//-------------------------------------------

class SIP_Manager_Call_Success_Test : public SIP_Manager_Test
{
public:
    SIP_Manager_Call_Success_Test() {}
    virtual ~SIP_Manager_Call_Success_Test() {}

    bool run(Socket::Address_Family family, std::string address, unsigned short port, SIP_Transport_Type transport);
};

//-------------------------------------------
