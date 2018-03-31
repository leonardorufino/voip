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
        LOG_ERROR       = 0x01,
        LOG_WARNING     = 0x02,
        LOG_INFO        = 0x04,
        LOG_TRACE       = 0x08,
        LOG_LEVEL_ALL   = 0xFF
    };

    enum Log_Source
    {
        LOG_TIMER           = 0x00000001,
        LOG_SOCKET          = 0x00000002,
        LOG_SIP_ADDRESS     = 0x00000010,
        LOG_SIP_HEADER      = 0x00000020,
        LOG_SIP_BODY        = 0x00000040,
        LOG_SIP_MESSAGE     = 0x00000080,
        LOG_SIP_TRANSACTION = 0x00000100,
        LOG_SIP_TRANSPORT   = 0x00000200,
        LOG_SIP_DIALOG      = 0x00000400,
        LOG_SIP_CALL        = 0x00000800,
        LOG_SIP_USER_AGENT  = 0x00001000,
        LOG_SIP_MANAGER     = 0x00002000,
        LOG_SDP_FIELD       = 0x00010000,
        LOG_SDP_DESCRIPTION = 0x00020000,
        LOG_RTP_HEADER      = 0x00100000,
        LOG_RTP_PACKET      = 0x00200000,
        LOG_RTP_TRANSPORT   = 0x00400000,
        LOG_RTP_SESSION     = 0x00800000,
        LOG_SOURCE_ALL      = 0xFFFFFFFF
    };

    typedef bool (log_callback)(Log_Level level, Log_Source source, const std::string &msg);

private:
    Log_Manager();
    ~Log_Manager() {}

public:
    static Log_Manager &instance();
    static void destroy();

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
    unsigned int _source;
    log_callback *_callback;

    static Log_Manager *_instance;
    static std::mutex _instance_mutex;
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
