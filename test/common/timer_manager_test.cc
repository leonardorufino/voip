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

//-------------------------------------------

bool Timer_Manager_Test::init()
{
    std::cout << "Timer manager test initialized\n";

    Timer_Manager_Stop_Test stop_test;
    if (!stop_test.run())
        return false;

    Timer_Manager_Callback_Test callback_test;
    if (!callback_test.run())
        return false;

    Timer_Manager_Multiple_Timers_Test multiple_timers_test;
    if (!multiple_timers_test.run())
        return false;

    std::cout << "Timer manager test completed successfully\n";
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool Timer_Manager_Stop_Test::run()
{
    Timer_Manager &manager = Timer_Manager::instance();

    Timer_Id id = manager.start_timer(_time, this, callback);
    _start = Common_Functions::get_tick();

    Common_Functions::delay(_time / 10);

    manager.stop_timer(id);

    unsigned long waited;

    while ((_stop == 0) && ((waited = Common_Functions::get_tick() - _start) < _max_wait_time))
        Common_Functions::delay(10);

    if (_stop != 0)
    {
        std::cout << "Timer_Manager_Stop_Test::run -> Callback shouldn't be called:\n";
        std::cout << std::setw(12) << "Time: " << _time << "\n";
        std::cout << std::setw(12) << "Diff: " << (_stop - _start) << "\n";
        return false;
    }

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

    test->_stop = Common_Functions::get_tick();
    return true;
}

//-------------------------------------------
//-------------------------------------------

bool Timer_Manager_Callback_Test::run()
{
    Timer_Manager &manager = Timer_Manager::instance();

    Timer_Id id = manager.start_timer(_time, this, callback);
    _start = Common_Functions::get_tick();

    unsigned long waited;

    while ((_stop == 0) && ((waited = Common_Functions::get_tick() - _start) < _max_wait_time))
        Common_Functions::delay(10);

    if (waited >= _max_wait_time)
    {
        manager.stop_timer(id);
        std::cout << "Timer_Manager_Callback_Test::run -> Callback was not called:\n";
        std::cout << std::setw(12) << "Time: " << _time << "\n";
        std::cout << std::setw(12) << "Waited: " << waited << "\n";
        std::cout << std::setw(12) << "Max: " << _max_wait_time << "\n";
        return false;
    }

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

    test->_stop = Common_Functions::get_tick();
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
        _time[i] = 300 * (i + 1);
        _max_wait_time[i] = _time[i] * 3;
    }
}

//-------------------------------------------

bool Timer_Manager_Multiple_Timers_Test::run()
{
    Timer_Manager &manager = Timer_Manager::instance();

    Timer_Id id[ARRAY_SIZE];

    id[0] = manager.start_timer(_time[0], this, callback0);
    _start[0] = Common_Functions::get_tick();

    id[1] = manager.start_timer(_time[1], this, callback1);
    _start[1] = Common_Functions::get_tick();

    id[2] = manager.start_timer(_time[2], this, callback2);
    _start[2] = Common_Functions::get_tick();

    for (unsigned short i = 0; i < ARRAY_SIZE; i++)
    {
        unsigned long waited;

        while ((_stop[i] == 0) && ((waited = Common_Functions::get_tick() - _start[i]) < _max_wait_time[i]))
            Common_Functions::delay(10);

        if (waited >= _max_wait_time[i])
        {
            manager.stop_timer(id[i]);
            std::cout << "Timer_Manager_Multiple_Timers_Test::run -> Callback " << i << " was not called:\n";
            std::cout << std::setw(12) << "Time: " << _time[i] << "\n";
            std::cout << std::setw(12) << "Waited: " << waited << "\n";
            std::cout << std::setw(12) << "Max: " << _max_wait_time[i] << "\n";
            return false;
        }
    }

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

    test->_stop[0] = Common_Functions::get_tick();
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

    test->_stop[1] = Common_Functions::get_tick();
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

    test->_stop[2] = Common_Functions::get_tick();
    return true;
}

//-------------------------------------------
