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

#include <iostream>
#include <fstream>
#include <mutex>
#include <cstdio>
#include <cstdarg>
#include <chrono>
#include <ctime>

typedef bool (log_callback)(const std::string &msg);

class Log_Manager
{
public:
    static const unsigned short MAX_LINE_LEN = 512;

    enum Log_Level
    {
        LOG_ERROR   = 0x01,
        LOG_WARNING = 0x02,
        LOG_INFO    = 0x04,
        LOG_TRACE   = 0x08
    };

    enum Log_Source
    {
        LOG_TIMER_MANAGER   = 0x0001,
        LOG_SIP_HEADER      = 0x0002,
        LOG_SIP_MESSAGE     = 0x0004,
        LOG_SIP_TRANSACTION = 0x0008,
    };

public:
    Log_Manager();
    ~Log_Manager() {}

    static Log_Manager &instance();

    void set_level(Log_Level level) { _level = level; }
    void set_source(Log_Source source) { _source = source; }
    void set_callback(log_callback *callback) { _callback = callback; }

    void log(Log_Level level, Log_Source source, const std::string &msg);
    void log(Log_Level level, Log_Source source, const char *format, ...);

private:
    bool is_active(Log_Level level, Log_Source source);

    std::string prefix(Log_Level level, Log_Source source);
    std::string get_level(Log_Level level);
    std::string get_source(Log_Source source);
    std::string get_datetime();

public:
    static bool log_cout_callback(const std::string &msg);
    static bool log_file_callback(const std::string &msg);

private:
    unsigned char _level;
    unsigned short _source;
    log_callback *_callback;
};
