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

#include "timer_manager.h"
#include "common_functions.h"

//-------------------------------------------

Timer::Timer()
{
    _timer_id = INVALID_TIMER_ID;
    _callback = NULL;
    _data = NULL;

#ifdef WIN32
    _timer = NULL;
#else
    _timer = 0;
    memset(&_sig_event, 0, sizeof(_sig_event));
    memset(&_timer_spec, 0, sizeof(_timer_spec));
    memset(&_sig_action, 0, sizeof(_sig_action));
#endif
}

//-------------------------------------------

Timer::~Timer()
{
    stop();
}

//-------------------------------------------

bool Timer::start(unsigned long time)
{
#ifdef WIN32
    if (!CreateTimerQueueTimer(&_timer, NULL, (WAITORTIMERCALLBACK) Timer_Manager::timer_handler, (void *) _timer_id,
                               time, 0, WT_EXECUTEDEFAULT))
    {
        std::cout << "Timer::start -> Failed to create timer queue timer (error=" << GetLastError() << ")\n";
        return false;
    }
#else
    _sig_action.sa_flags = SA_SIGINFO;
    _sig_action.sa_sigaction = Timer_Manager::timer_handler;
    sigemptyset(&_sig_action.sa_mask);

    if (sigaction(SIGRTMIN, &_sig_action, NULL))
    {
        std::cout << "Timer::start -> Failed to call sigaction (error=" << errno << ")\n";
        return false;
    }

    _sig_event.sigev_notify = SIGEV_SIGNAL;
    _sig_event.sigev_signo = SIGRTMIN;
    _sig_event.sigev_value.sival_ptr = &_timer;

    if (timer_create(CLOCK_MONOTONIC, &_sig_event, &_timer))
    {
        std::cout << "Timer::start -> Failed to create timer (error=" << errno << ")\n";
        return false;
    }

    _timer_spec.it_value.tv_sec = time / 1000;
    _timer_spec.it_value.tv_nsec = (time % 1000) * 1000 * 1000;

    if (timer_settime(_timer, 0, &_timer_spec, NULL))
    {
        std::cout << "Timer::start -> Failed to set time (error=" << errno << ")\n";
        return false;
    }
#endif

    //std::cout << "Timer::start -> Timer " << _timer_id << " started\n";
    return true;
}

//-------------------------------------------

bool Timer::stop()
{
#ifdef WIN32
    if (_timer)
    {
        if (!DeleteTimerQueueTimer(NULL, _timer, NULL))
        {
            std::cout << "Timer::stop -> Failed to delete timer (error=" << GetLastError() << ")\n";
            _timer = NULL;
            return false;
        }

        _timer = NULL;

        //std::cout << "Timer::stop -> Timer " << _timer_id << " stopped\n";
    }
#else
    if (_timer)
    {
        _timer_spec.it_value.tv_sec = 0;
        _timer_spec.it_value.tv_nsec = 0;

        if (timer_settime(_timer, 0, &_timer_spec, NULL))
        {
            std::cout << "Timer::stop -> Failed to set time (error=" << errno << ")\n";
            return false;
        }

        if (timer_delete(_timer))
        {
            std::cout << "Timer::stop -> Failed to delete timer (error=" << errno << ")\n";
            return false;
        }

        _timer = 0;

        //std::cout << "Timer::stop -> Timer " << _timer_id << " stopped\n";
    }
#endif

    return true;
}

//-------------------------------------------

bool Timer::expired()
{
    try
    {
#ifdef WIN32
        if (_timer)
            _timer = NULL;
#endif

        //std::cout << "Timer::expired -> Timer " << _timer_id << " expired\n";
        return _callback(_data);
    }catch (...)
    {
        std::cout << "Timer::expired -> Unknown exception in timer callback\n";
        return false;
    }
}

//-------------------------------------------

Timer_Id Timer::next_timer_id()
{
    static Timer_Id NEXT_TIMER_ID = 0;
    static std::mutex NEXT_TIMER_ID_MUTEX;

    std::lock_guard<std::mutex> lock(NEXT_TIMER_ID_MUTEX);

    Timer_Id id = NEXT_TIMER_ID++;

    if (NEXT_TIMER_ID >= INVALID_TIMER_ID)
        NEXT_TIMER_ID = 0;

    return id;
}

//-------------------------------------------

bool Timer::operator==(const Timer &other)
{
    return _timer_id == other._timer_id;
}

//-------------------------------------------
//-------------------------------------------

Timer_Manager &Timer_Manager::instance()
{
    static Timer_Manager manager;
    return manager;
}

//-------------------------------------------

Timer_Id Timer_Manager::start_timer(unsigned long time, void *data, timer_callback *callback)
{
    std::lock_guard<std::mutex> lock(_timer_list_mutex);

    Timer_Id id = Timer::next_timer_id();

    Timer *timer = new Timer();
    timer->set_timer_id(id);
    timer->set_callback(callback);
    timer->set_data(data);

    timer->start(time);

    _timer_list.push_back(timer);

    return id;
}

//-------------------------------------------

void Timer_Manager::stop_timer(Timer_Id timer_id)
{
    std::lock_guard<std::mutex> lock(_timer_list_mutex);

    Timer *timer = get_timer(timer_id);
    if (timer)
    {
        timer->stop();
        _timer_list.remove(timer);
        delete timer;
    }
}

//-------------------------------------------

#ifdef WIN32
    VOID CALLBACK Timer_Manager::timer_handler(PVOID id, BOOLEAN timed_out)
#else
    void Timer_Manager::timer_handler(int sig, siginfo_t *info, void *ucontext)
#endif
{
    Timer_Manager &manager = instance();

    std::lock_guard<std::mutex> lock(manager._timer_list_mutex);

#ifdef WIN32
    Timer_Id timer_id = (Timer_Id) id;
    Timer *timer = manager.get_timer(timer_id);
#else
    timer_t tid = info->si_value.sival_ptr;
    Timer *timer = manager.get_timer_linux(tid);
#endif

    if (timer)
    {
        timer->expired();
        manager._timer_list.remove(timer);
        delete timer;
    }
}

//-------------------------------------------

Timer *Timer_Manager::get_timer(Timer_Id timer_id)
{
    Timer *ret = NULL;

    std::list<Timer *>::iterator it = _timer_list.begin();
    while (it != _timer_list.end())
    {
        Timer *timer = *it++;
        if (timer->get_timer_id() == timer_id)
        {
            ret = timer;
            break;
        }
    }

    return ret;
}

//-------------------------------------------

#ifndef WIN32
Timer *Timer_Manager::get_timer_linux(timer_t &tid)
{
    Timer *ret = NULL;

    std::list<Timer *>::iterator it = _timer_list.begin();
    while (it != _timer_list.end())
    {
        Timer *timer = *it++;
        if (&timer->get_timer() == tid)
        {
            ret = timer;
            break;
        }
    }

    return ret;
}
#endif

//-------------------------------------------
