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

#include "timer_manager_test.h"
#include <iostream>

//-------------------------------------------

bool Timer_Manager_Test::init()
{
    std::cout << "Timer manager test initialized\n";

    if (!run<Timer_Manager_Stop_Test>())
        return false;

    if (!run<Timer_Manager_Callback_Test>())
        return false;

    if (!run<Timer_Manager_Multiple_Timers_Test>())
        return false;

    std::cout << "Timer manager test completed successfully\n";
    return true;
}

//-------------------------------------------

template<class T> bool Timer_Manager_Test::run()
{
    T test;
    test._thread = std::thread(thread, &test);

    bool ret = test.run();

    test._stop_thread = true;
    test._thread.join();
    return ret;
}

//-------------------------------------------

void Timer_Manager_Test::thread(Timer_Manager_Test *test)
{
    Timer_Manager &timer = Timer_Manager::instance();

    while (!test->_stop_thread)
    {
        timer.run();
        Util_Functions::delay(THREAD_DELAY);
    }

    Timer_Manager::destroy();
}

//-------------------------------------------
//-------------------------------------------

bool Timer_Manager_Stop_Test::run()
{
    std::cout << "Timer manager stop test initialized\n";

    Timer_Manager &manager = Timer_Manager::instance();

    timer_id_t id = manager.start_timer(_time, this, callback);
    _start = Util_Functions::get_tick();

    Util_Functions::delay(_time / 10);

    manager.stop_timer(id);

    unsigned long waited = 0;

    while ((_stop == 0) && ((waited = Util_Functions::get_tick() - _start) < _max_wait_time))
        Util_Functions::delay(DELAY);

    if (_stop != 0)
    {
        std::cout << "Timer_Manager_Stop_Test::run -> Callback shouldn't be called:\n";
        std::cout << std::setw(12) << "Time: " << _time << "\n";
        std::cout << std::setw(12) << "Diff: " << (_stop - _start) << "\n";
        return false;
    }

    std::cout << "Timer manager stop test completed successfully\n";
    return true;
}

//-------------------------------------------

bool Timer_Manager_Stop_Test::callback(void *data)
{
    Timer_Manager_Stop_Test *test = reinterpret_cast<Timer_Manager_Stop_Test *>(data);
    if (!test)
    {
        std::cout << "Timer_Manager_Stop_Test::callback -> Invalid data parameter\n";
        return false;
    }

    test->_stop = Util_Functions::get_tick();
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool Timer_Manager_Callback_Test::run()
{
    std::cout << "Timer manager callback test initialized\n";

    Timer_Manager &manager = Timer_Manager::instance();

    timer_id_t id = manager.start_timer(_time, this, callback);
    _start = Util_Functions::get_tick();

    unsigned long waited = 0;

    while ((_stop == 0) && ((waited = Util_Functions::get_tick() - _start) < _max_wait_time))
        Util_Functions::delay(DELAY);

    if (waited >= _max_wait_time)
    {
        manager.stop_timer(id);
        std::cout << "Timer_Manager_Callback_Test::run -> Callback was not called:\n";
        std::cout << std::setw(12) << "Time: " << _time << "\n";
        std::cout << std::setw(12) << "Waited: " << waited << "\n";
        std::cout << std::setw(12) << "Max: " << _max_wait_time << "\n";
        return false;
    }

    std::cout << "Timer manager callback test completed successfully\n";
    return true;
}

//-------------------------------------------

bool Timer_Manager_Callback_Test::callback(void *data)
{
    Timer_Manager_Callback_Test *test = reinterpret_cast<Timer_Manager_Callback_Test *>(data);
    if (!test)
    {
        std::cout << "Timer_Manager_Callback_Test::callback -> Invalid data parameter\n";
        return false;
    }

    test->_stop = Util_Functions::get_tick();
    return true;
}

//-------------------------------------------
//-------------------------------------------

Timer_Manager_Multiple_Timers_Test::Timer_Manager_Multiple_Timers_Test()
{
    for (unsigned short i = 0; i < ARRAY_SIZE; i++)
    {
        _start[i] = 0;
        _stop[i] = 0;
        _time[i] = 500 * (i + 1);
        _max_wait_time[i] = _time[i] * 3;
    }
}

//-------------------------------------------

bool Timer_Manager_Multiple_Timers_Test::run()
{
    std::cout << "Timer manager multiple timers test initialized\n";

    Timer_Manager &manager = Timer_Manager::instance();

    timer_id_t id[ARRAY_SIZE];

    id[0] = manager.start_timer(_time[0], this, callback0);
    _start[0] = Util_Functions::get_tick();

    id[1] = manager.start_timer(_time[1], this, callback1);
    _start[1] = Util_Functions::get_tick();

    id[2] = manager.start_timer(_time[2], this, callback2);
    _start[2] = Util_Functions::get_tick();

    for (unsigned short i = 0; i < ARRAY_SIZE; i++)
    {
        unsigned long waited = 0;

        while ((_stop[i] == 0) && ((waited = Util_Functions::get_tick() - _start[i]) < _max_wait_time[i]))
            Util_Functions::delay(DELAY);

        if (waited >= _max_wait_time[i])
        {
            for (unsigned short j = i; j < ARRAY_SIZE; j++)
                manager.stop_timer(id[j]);

            std::cout << "Timer_Manager_Multiple_Timers_Test::run -> Callback " << i << " was not called:\n";
            std::cout << std::setw(12) << "Time: " << _time[i] << "\n";
            std::cout << std::setw(12) << "Waited: " << waited << "\n";
            std::cout << std::setw(12) << "Max: " << _max_wait_time[i] << "\n";
            return false;
        }
    }

    std::cout << "Timer manager multiple timers test completed successfully\n";
    return true;
}

//-------------------------------------------

bool Timer_Manager_Multiple_Timers_Test::callback0(void *data)
{
    Timer_Manager_Multiple_Timers_Test *test = reinterpret_cast<Timer_Manager_Multiple_Timers_Test *>(data);
    if (!test)
    {
        std::cout << "Timer_Manager_Multiple_Timers_Test::callback0 -> Invalid data parameter\n";
        return false;
    }

    test->_stop[0] = Util_Functions::get_tick();
    return true;
}

//-------------------------------------------

bool Timer_Manager_Multiple_Timers_Test::callback1(void *data)
{
    Timer_Manager_Multiple_Timers_Test *test = reinterpret_cast<Timer_Manager_Multiple_Timers_Test *>(data);
    if (!test)
    {
        std::cout << "Timer_Manager_Multiple_Timers_Test::callback1 -> Invalid data parameter\n";
        return false;
    }

    test->_stop[1] = Util_Functions::get_tick();
    return true;
}

//-------------------------------------------

bool Timer_Manager_Multiple_Timers_Test::callback2(void *data)
{
    Timer_Manager_Multiple_Timers_Test *test = reinterpret_cast<Timer_Manager_Multiple_Timers_Test *>(data);
    if (!test)
    {
        std::cout << "Timer_Manager_Multiple_Timers_Test::callback2 -> Invalid data parameter\n";
        return false;
    }

    test->_stop[2] = Util_Functions::get_tick();
    return true;
}

//-------------------------------------------
