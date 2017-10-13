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

#include "sip/sip_user_agent.h"
#include "sip/sip_call.h"
#include "util/util_functions.h"
#include <iomanip>
#include <thread>

class SIP_User_Agent_Test
{
public:
    static const unsigned long THREAD_DELAY = 10;
    static const unsigned long MAX_WAIT_TIME = 5000;
    static const unsigned long DELAY = 500;

public:
    SIP_User_Agent_Test();
    virtual ~SIP_User_Agent_Test();

    static bool init();
    template<class T> static bool run(Socket::Address_Family family, std::string address, unsigned short port,
                                      SIP_Transport_Type transport);

    static void thread(SIP_User_Agent_Test *test);

protected:
    virtual bool run(Socket::Address_Family family, std::string address, unsigned short port, SIP_Transport_Type transport) = 0;

    virtual bool init_user_agent(std::string address, unsigned short port);
    virtual bool close_user_agent();
    virtual bool set_callbacks();
    virtual void clear_callback_params();

    bool process_request(unsigned int call_id, SIP_Method_Type method, std::string address = "",
                         unsigned short port = SIP_URI::INVALID_PORT, SIP_Transport_Type transport = SIP_TRANSPORT_INVALID);
    bool process_response(unsigned int call_id, SIP_Method_Type method, unsigned short status_code);
    bool wait_timeout(unsigned int call_id);

    static bool receive_request_callback(void *data, SIP_User_Agent *user_agent, unsigned int call_id, SIP_Request *request);
    static bool receive_response_callback(void *data, SIP_User_Agent *user_agent, unsigned int call_id, SIP_Request *request,
                                          SIP_Response *response);

    static bool get_network_addresses(std::list<Socket::Network_Address> &addresses);
    static bool check_network_address(Socket::Address_Family family, std::string address);

protected:
    SIP_User_Agent *_user_agent;

    unsigned int _call_id_callback;
    std::list<SIP_Request *> _received_requests;
    SIP_Request *_request_callback;
    SIP_Response *_response_callback;

private:
    std::thread _thread;
    bool _stop_thread;
};

//-------------------------------------------
//-------------------------------------------

class SIP_User_Agent_Call_Success_Test : public SIP_User_Agent_Test
{
public:
    SIP_User_Agent_Call_Success_Test() {}
    virtual ~SIP_User_Agent_Call_Success_Test() {}

    bool run(Socket::Address_Family family, std::string address, unsigned short port, SIP_Transport_Type transport);
};

//-------------------------------------------
//-------------------------------------------

class SIP_User_Agent_Call_Success_No_100_Test : public SIP_User_Agent_Test
{
public:
    SIP_User_Agent_Call_Success_No_100_Test() {}
    virtual ~SIP_User_Agent_Call_Success_No_100_Test() {}

    bool run(Socket::Address_Family family, std::string address, unsigned short port, SIP_Transport_Type transport);
};

//-------------------------------------------
//-------------------------------------------

class SIP_User_Agent_Call_Success_No_1xx_Test : public SIP_User_Agent_Test
{
public:
    SIP_User_Agent_Call_Success_No_1xx_Test() {}
    virtual ~SIP_User_Agent_Call_Success_No_1xx_Test() {}

    bool run(Socket::Address_Family family, std::string address, unsigned short port, SIP_Transport_Type transport);
};

//-------------------------------------------
//-------------------------------------------

class SIP_User_Agent_Call_Reject_Test : public SIP_User_Agent_Test
{
public:
    SIP_User_Agent_Call_Reject_Test() {}
    virtual ~SIP_User_Agent_Call_Reject_Test() {}

    bool run(Socket::Address_Family family, std::string address, unsigned short port, SIP_Transport_Type transport);
};

//-------------------------------------------
//-------------------------------------------

class SIP_User_Agent_Call_Reject_No_100_Test : public SIP_User_Agent_Test
{
public:
    SIP_User_Agent_Call_Reject_No_100_Test() {}
    virtual ~SIP_User_Agent_Call_Reject_No_100_Test() {}

    bool run(Socket::Address_Family family, std::string address, unsigned short port, SIP_Transport_Type transport);
};

//-------------------------------------------
//-------------------------------------------

class SIP_User_Agent_Call_Reject_No_1xx_Test : public SIP_User_Agent_Test
{
public:
    SIP_User_Agent_Call_Reject_No_1xx_Test() {}
    virtual ~SIP_User_Agent_Call_Reject_No_1xx_Test() {}

    bool run(Socket::Address_Family family, std::string address, unsigned short port, SIP_Transport_Type transport);
};

//-------------------------------------------
//-------------------------------------------

class SIP_User_Agent_Call_No_Answer_Test : public SIP_User_Agent_Test
{
public:
    SIP_User_Agent_Call_No_Answer_Test() {}
    virtual ~SIP_User_Agent_Call_No_Answer_Test() {}

    bool run(Socket::Address_Family family, std::string address, unsigned short port, SIP_Transport_Type transport);
};

//-------------------------------------------
