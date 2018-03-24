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

typedef unsigned long timer_id_t;

class Timer
{
public:
    static const timer_id_t INVALID_TIMER_ID = 0xFFFFFFFF;

    typedef bool (timer_callback)(void *data);

public:
    Timer() : _timer_id(INVALID_TIMER_ID), _time(0), _flag(false), _callback(NULL), _callback_data(NULL) {}
    ~Timer() {}

    bool check_expired(unsigned long now, bool flag);
    bool expired();

    static timer_id_t next_timer_id();

    void set_timer_id(timer_id_t timer_id) { _timer_id = timer_id; }
    timer_id_t get_timer_id() { return _timer_id; }

    void set_time(unsigned long time) { _time = time; }
    void set_flag(bool flag) { _flag = flag; }
    void set_callback(timer_callback *callback, void *data);
    void *get_callback_data() { return _callback_data; }

    bool operator==(const Timer &other);

private:
    timer_id_t _timer_id;
    unsigned long _time;
    bool _flag;
    timer_callback *_callback;
    void *_callback_data;

    static Logger _logger;
};

//-------------------------------------------

class Timer_Manager
{
private:
    Timer_Manager() : _last_tick(0), _flag(false) {}

public:
    ~Timer_Manager() {}

    static Timer_Manager &instance();

    timer_id_t start_timer(unsigned long time, void *data, Timer::timer_callback *callback);
    void *stop_timer(timer_id_t timer_id);

    void run();

private:
    Timer *get_timer(timer_id_t timer_id);

private:
    std::list<Timer *> _timer_list;
    std::recursive_mutex _timer_list_mutex;

    unsigned long _last_tick;
    bool _flag;
};

//-------------------------------------------
