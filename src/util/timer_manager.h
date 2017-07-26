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

#include "util/log_manager.h"
#include <string>
#include <list>
#include <mutex>

#ifdef WIN32
    #include <winsock2.h>
    #include <windows.h>
#else
    #include <csignal>
    #include <ctime>
    #include <cstring>
#endif

typedef bool (timer_callback)(void *data);
typedef unsigned int Timer_Id;

class Timer
{
public:
    static const Timer_Id INVALID_TIMER_ID = 0xFFFFFFFF;

public:
    Timer();
    ~Timer();

    bool start(unsigned long time);
    bool stop();
    bool expired();

    static Timer_Id next_timer_id();

    void set_timer_id(Timer_Id timer_id) { _timer_id = timer_id; }
    Timer_Id get_timer_id() { return _timer_id; }

    void set_callback(timer_callback *callback) { _callback = callback; }
    timer_callback *get_callback() { return _callback; }

    void set_data(void *data) { _data = data; }
    void *get_data() { return _data; }

    bool operator==(const Timer &other);

#ifndef WIN32
    timer_t &get_timer() { return _timer; }
#endif

private:
    Timer_Id _timer_id;
    timer_callback *_callback;
    void *_data;

#ifdef WIN32
    HANDLE _timer;
#else
    timer_t _timer;
    struct sigevent _sig_event;
    struct itimerspec _timer_spec;
    struct sigaction _sig_action;
#endif

    static Logger _logger;
};

//-------------------------------------------

class Timer_Manager
{
public:
    Timer_Manager() {}
    ~Timer_Manager() {}

    static Timer_Manager &instance();

    Timer_Id start_timer(unsigned long time, void *data, timer_callback *callback);
    void stop_timer(Timer_Id timer_id);

#ifdef WIN32
    static VOID CALLBACK timer_handler(PVOID id, BOOLEAN timed_out);
#else
    static void timer_handler(int sig, siginfo_t *info, void *ucontext);
#endif

private:
    Timer *get_timer(Timer_Id timer_id);

#ifndef WIN32
    Timer *get_timer_linux(timer_t &tid);
#endif

private:
    std::list<Timer *> _timer_list;
    std::recursive_mutex _timer_list_mutex;
};

//-------------------------------------------
