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

#include <string>
#include <iostream>
#include <fstream>
#include <mutex>
#include <cstdio>
#include <cstdarg>
#include <chrono>
#include <ctime>

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
        LOG_TIMER           = 0x0001,
        LOG_SOCKET          = 0x0002,
        LOG_SIP_HEADER      = 0x0010,
        LOG_SIP_MESSAGE     = 0x0020,
        LOG_SIP_TRANSACTION = 0x0040,
        LOG_SIP_TRANSPORT   = 0x0080,
        LOG_SIP_DIALOG      = 0x0100,
        LOG_SIP_CALL        = 0x0200,
    };

    typedef bool (log_callback)(Log_Level level, Log_Source source, const std::string &msg);

public:
    Log_Manager();
    ~Log_Manager() {}

    static Log_Manager &instance();

    void set_level(unsigned char level) { _level = level; }
    void set_source(unsigned short source) { _source = source; }
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
    static bool log_cout_callback(Log_Level level, Log_Source source, const std::string &msg);
    static bool log_file_callback(Log_Level level, Log_Source source, const std::string &msg);

private:
    unsigned char _level;
    unsigned short _source;
    log_callback *_callback;
};

//-------------------------------------------

class Logger
{
public:
    Logger(Log_Manager::Log_Source source) : _source(source) {}

    void error(const std::string &msg);
    void error(const char *format, ...);

    void warning(const std::string &msg);
    void warning(const char *format, ...);

    void info(const std::string &msg);
    void info(const char *format, ...);

    void trace(const std::string &msg);
    void trace(const char *format, ...);

private:
    Log_Manager::Log_Source _source;
};

//-------------------------------------------
