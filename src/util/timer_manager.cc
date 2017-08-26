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
#include "util_functions.h"

Logger Timer::_logger(Log_Manager::LOG_TIMER);

//-------------------------------------------

Timer::Timer()
{
    _timer_id = INVALID_TIMER_ID;
    _callback = NULL;
    _callback_data = NULL;

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
        _logger.warning("Timer::start -> Failed to create timer queue timer (timer=%d, error=%d)", _timer_id, GetLastError());
        return false;
    }
#else
    _sig_action.sa_flags = SA_SIGINFO;
    _sig_action.sa_sigaction = Timer_Manager::timer_handler;
    sigemptyset(&_sig_action.sa_mask);

    if (sigaction(SIGRTMIN, &_sig_action, NULL))
    {
        _logger.warning("Timer::start -> Failed to call sigaction (timer=%d, error=%d)", _timer_id, errno);
        return false;
    }

    _sig_event.sigev_notify = SIGEV_SIGNAL;
    _sig_event.sigev_signo = SIGRTMIN;
    _sig_event.sigev_value.sival_ptr = &_timer;

    if (timer_create(CLOCK_MONOTONIC, &_sig_event, &_timer))
    {
        _logger.warning("Timer::start -> Failed to create timer (timer=%d, error=%d)", _timer_id, errno);
        return false;
    }

    _timer_spec.it_value.tv_sec = time / 1000;
    _timer_spec.it_value.tv_nsec = (time % 1000) * 1000 * 1000;

    if (timer_settime(_timer, 0, &_timer_spec, NULL))
    {
        _logger.warning("Timer::start -> Failed to set time (timer=%d, error=%d)", _timer_id, errno);
        return false;
    }
#endif

    _logger.trace("Timer::start -> Timer started (timer=%d)", _timer_id);
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
            _logger.warning("Timer::stop -> Failed to delete timer (timer=%d, error=%d)", _timer_id, GetLastError());
            _timer = NULL;
            return false;
        }

        _timer = NULL;

        _logger.trace("Timer::stop -> Timer stopped (timer=%d)", _timer_id);
    }
#else
    if (_timer)
    {
        _timer_spec.it_value.tv_sec = 0;
        _timer_spec.it_value.tv_nsec = 0;

        if (timer_settime(_timer, 0, &_timer_spec, NULL))
        {
            _logger.warning("Timer::stop -> Failed to set time (timer=%d, error=%d)", _timer_id, errno);
            return false;
        }

        if (timer_delete(_timer))
        {
            _logger.warning("Timer::stop -> Failed to delete timer (timer=%d, error=%d)", _timer_id, errno);
            return false;
        }

        _timer = 0;

        _logger.trace("Timer::stop -> Timer stopped (timer=%d)", _timer_id);
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

        _logger.trace("Timer::expired -> Timer expired (timer=%d)", _timer_id);
        return _callback(_callback_data);

    }catch (std::exception &e)
    {
        _logger.warning("Timer::expired -> Exception in timer callback (timer=%d, msg=%s)", _timer_id, e.what());
        return false;
    }catch (...)
    {
        _logger.warning("Timer::expired -> Unknown exception in timer callback (timer=%d)", _timer_id);
        return false;
    }
}

//-------------------------------------------

timer_id_t Timer::next_timer_id()
{
    static timer_id_t NEXT_TIMER_ID = 0;
    static std::mutex NEXT_TIMER_ID_MUTEX;

    std::lock_guard<std::mutex> lock(NEXT_TIMER_ID_MUTEX);

    timer_id_t id = NEXT_TIMER_ID++;

    if (NEXT_TIMER_ID >= INVALID_TIMER_ID)
        NEXT_TIMER_ID = 0;

    return id;
}

//-------------------------------------------

void Timer::set_callback(timer_callback *callback, void *data)
{
    _callback = callback;
    _callback_data = data;
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

timer_id_t Timer_Manager::start_timer(unsigned long time, void *data, Timer::timer_callback *callback)
{
    std::lock_guard<std::recursive_mutex> lock(_timer_list_mutex);

    timer_id_t id = Timer::next_timer_id();

    Timer *timer = new Timer();
    timer->set_timer_id(id);
    timer->set_callback(callback, data);

    timer->start(time);

    _timer_list.push_back(timer);

    return id;
}

//-------------------------------------------

void Timer_Manager::stop_timer(timer_id_t timer_id)
{
    std::lock_guard<std::recursive_mutex> lock(_timer_list_mutex);

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

    std::lock_guard<std::recursive_mutex> lock(manager._timer_list_mutex);

#ifdef WIN32
    timer_id_t timer_id = (timer_id_t) id;
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

Timer *Timer_Manager::get_timer(timer_id_t timer_id)
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
