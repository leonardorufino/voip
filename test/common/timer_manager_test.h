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

#include "common/common_functions.h"
#include "common/timer_manager.h"
#include <iomanip>

class Timer_Manager_Test
{
public:
    Timer_Manager_Test() {}
    virtual ~Timer_Manager_Test() {}

    static bool init();

    virtual bool run() = 0;
};

//-------------------------------------------

class Timer_Manager_Test1 : public Timer_Manager_Test
{
public:
    Timer_Manager_Test1() : _start(0), _stop(0), _time(300), _max_wait_time(_time * 3) {}
    virtual ~Timer_Manager_Test1() {}

    bool run();

    static bool callback(void *data);

private:
    unsigned long _start;
    unsigned long _stop;
    unsigned long _time;
    unsigned long _max_wait_time;
};

//-------------------------------------------

class Timer_Manager_Test2 : public Timer_Manager_Test
{
public:
    Timer_Manager_Test2() : _start(0), _stop(0), _time(300), _max_wait_time(_time * 3) {}
    virtual ~Timer_Manager_Test2() {}

    bool run();

    static bool callback(void *data);

private:
    unsigned long _start;
    unsigned long _stop;
    unsigned long _time;
    unsigned long _max_wait_time;
};

//-------------------------------------------

class Timer_Manager_Test3 : public Timer_Manager_Test
{
public:
    Timer_Manager_Test3();
    virtual ~Timer_Manager_Test3() {}

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
