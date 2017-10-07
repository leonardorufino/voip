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

#include "util/util_functions.h"
#include "util/timer_manager.h"
#include <iomanip>
#include <thread>

class Timer_Manager_Test
{
public:
    static const unsigned long THREAD_DELAY = 10;

public:
    Timer_Manager_Test() : _stop_thread(false) {}
    virtual ~Timer_Manager_Test() {}

    static bool init();
    template<class T> static bool run();

    static void thread(Timer_Manager_Test *test);

protected:
    virtual bool run() = 0;

private:
    std::thread _thread;
    bool _stop_thread;
};

//-------------------------------------------

class Timer_Manager_Stop_Test : public Timer_Manager_Test
{
public:
    Timer_Manager_Stop_Test() : _start(0), _stop(0), _time(500), _max_wait_time(_time * 3) {}
    virtual ~Timer_Manager_Stop_Test() {}

    bool run();

    static bool callback(void *data);

private:
    unsigned long _start;
    unsigned long _stop;
    unsigned long _time;
    unsigned long _max_wait_time;
};

//-------------------------------------------

class Timer_Manager_Callback_Test : public Timer_Manager_Test
{
public:
    Timer_Manager_Callback_Test() : _start(0), _stop(0), _time(500), _max_wait_time(_time * 3) {}
    virtual ~Timer_Manager_Callback_Test() {}

    bool run();

    static bool callback(void *data);

private:
    unsigned long _start;
    unsigned long _stop;
    unsigned long _time;
    unsigned long _max_wait_time;
};

//-------------------------------------------

class Timer_Manager_Multiple_Timers_Test : public Timer_Manager_Test
{
public:
    Timer_Manager_Multiple_Timers_Test();
    virtual ~Timer_Manager_Multiple_Timers_Test() {}

    bool run();

    static bool callback0(void *data);
    static bool callback1(void *data);
    static bool callback2(void *data);

private:
    static const unsigned short ARRAY_SIZE = 3;

    unsigned long _start[ARRAY_SIZE];
    unsigned long _stop[ARRAY_SIZE];
    unsigned long _time[ARRAY_SIZE];
    unsigned long _max_wait_time[ARRAY_SIZE];
};

//-------------------------------------------
