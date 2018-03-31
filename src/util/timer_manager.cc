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
Timer_Manager *Timer_Manager::_instance = NULL;
std::mutex Timer_Manager::_instance_mutex;

//-------------------------------------------

bool Timer::check_expired(unsigned long now, bool flag)
{
    if (((_time <= now) && (_flag == flag)) || ((_time > now) && (_flag != flag)))
        return true;

    return false;
}

//-------------------------------------------

bool Timer::expired()
{
    try
    {
        _logger.trace("Timer expired (timer=%d)", _timer_id);
        return _callback(_callback_data);

    }catch (std::exception &e)
    {
        _logger.warning("Exception in timer expired (timer=%d, msg=%s)", _timer_id, e.what());
        return false;
    }catch (...)
    {
        _logger.warning("Exception in timer expired (timer=%d)", _timer_id);
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
    std::lock_guard<std::mutex> lock(_instance_mutex);

    if (_instance == NULL)
        _instance = new Timer_Manager();

    return *_instance;
}

//-------------------------------------------

void Timer_Manager::destroy()
{
    std::lock_guard<std::mutex> lock(_instance_mutex);

    delete _instance;
    _instance = NULL;
}

//-------------------------------------------

timer_id_t Timer_Manager::start_timer(unsigned long time, void *data, Timer::timer_callback *callback)
{
    timer_id_t id = Timer::next_timer_id();
    unsigned long now = Util_Functions::get_tick();
    unsigned long expire = now + time;

    std::lock_guard<std::recursive_mutex> lock(_timer_list_mutex);

    Timer *timer = new Timer();
    timer->set_timer_id(id);
    timer->set_time(expire);
    timer->set_flag((expire < _last_tick) ? !_flag : _flag);
    timer->set_callback(callback, data);

    _timer_list.push_back(timer);
    return id;
}

//-------------------------------------------

void *Timer_Manager::stop_timer(timer_id_t timer_id)
{
    std::lock_guard<std::recursive_mutex> lock(_timer_list_mutex);

    void *data = NULL;
    Timer *timer = get_timer(timer_id);
    if (timer)
    {
        _timer_list.remove(timer);
        data = timer->get_callback_data();
        delete timer;
    }

    return data;
}

//-------------------------------------------

void Timer_Manager::run()
{
    unsigned long now = Util_Functions::get_tick();
    if (now < _last_tick)
        _flag = !_flag;

    _last_tick = now;

    std::lock_guard<std::recursive_mutex> lock(_timer_list_mutex);

    std::list<Timer *>::iterator it = _timer_list.begin();
    while (it != _timer_list.end())
    {
        Timer *timer = *it;
        if (timer->check_expired(now, _flag))
        {
            timer->expired();
            it = _timer_list.erase(it);
        }else
            it++;
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
