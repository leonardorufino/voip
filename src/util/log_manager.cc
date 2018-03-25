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

#include "log_manager.h"
#include "util_functions.h"

//-------------------------------------------

Log_Manager::Log_Manager()
{
    _level = LOG_LEVEL_ALL;
    _source = LOG_SOURCE_ALL;
    _callback = log_cout_callback;
}

//-------------------------------------------

Log_Manager &Log_Manager::instance()
{
    static Log_Manager manager;
    return manager;
}

//-------------------------------------------

void Log_Manager::log(Log_Level level, Log_Source source, const std::string &msg)
{
    if (!is_active(level, source))
        return;

    if (_callback)
        _callback(level, source, msg);
}

//-------------------------------------------

void Log_Manager::log(Log_Level level, Log_Source source, const char *format, ...)
{
    if (!is_active(level, source))
        return;

    char buffer[Log_Manager::MAX_LINE_LEN];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    std::string msg = buffer;

    if (_callback)
        _callback(level, source, msg);
}

//-------------------------------------------

bool Log_Manager::is_active(Log_Level level, Log_Source source)
{
    if (!(_level & level))
        return false;

    if (!(_source & source))
        return false;

    return true;
}

//-------------------------------------------

std::string Log_Manager::prefix(Log_Level level, Log_Source source)
{
    std::string prefix;
    prefix  = get_level(level);
    prefix += "|";
    prefix += get_datetime();
    prefix += "|";
    prefix += get_source(source);
    prefix += "| ";
    return prefix;
}

//-------------------------------------------

std::string Log_Manager::get_level(Log_Level level)
{
    switch (level)
    {
        case LOG_ERROR:     return "E";
        case LOG_WARNING:   return "W";
        case LOG_INFO:      return "I";
        case LOG_TRACE:     return "T";
        default:            return " ";
    }
}

//-------------------------------------------

std::string Log_Manager::get_source(Log_Source source)
{
    switch (source)
    {
        case LOG_TIMER:             return "TIMER  ";
        case LOG_SOCKET:            return "SOCKET ";
        case LOG_SIP_HEADER:        return "SIP HDR";
        case LOG_SIP_BODY:          return "SIP BOD";
        case LOG_SIP_MESSAGE:       return "SIP MSG";
        case LOG_SIP_TRANSACTION:   return "SIP TRA";
        case LOG_SIP_TRANSPORT:     return "SIP TPT";
        case LOG_SIP_DIALOG:        return "SIP DLG";
        case LOG_SIP_CALL:          return "SIP CAL";
        case LOG_SIP_USER_AGENT:    return "SIP UA ";
        case LOG_SIP_MANAGER:       return "SIP MNG";
        case LOG_SDP_FIELD:         return "SDP FLD";
        case LOG_SDP_DESCRIPTION:   return "SDP DSC";
        case LOG_RTP_HEADER:        return "RTP HDR";
        case LOG_RTP_PACKET:        return "RTP PKT";
        case LOG_RTP_TRANSPORT:     return "RTP TPT";
        case LOG_RTP_SESSION:       return "RTP SES";
        default:                    return "       ";
    }
}

//-------------------------------------------

std::string Log_Manager::get_datetime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    struct tm timeinfo;

#ifdef WIN32
    if (localtime_s(&timeinfo, &time))
#else
    if (!localtime_r(&time, &timeinfo))
#endif
        return "";

    char buffer[30];
    snprintf(buffer, sizeof(buffer), "%04d/%02d/%02d %02d:%02d:%02d", timeinfo.tm_year + 1900,
             timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

    return buffer;
}

//-------------------------------------------

bool Log_Manager::log_cout_callback(Log_Level level, Log_Source source, const std::string &msg)
{
    Log_Manager &manager = Log_Manager::instance();

    static std::mutex LOG_COUT_MUTEX;
    std::lock_guard<std::mutex> lock(LOG_COUT_MUTEX);

    std::string str;
    str = manager.prefix(level, source);
    str += msg;

    std::cout << str.c_str() << std::endl;
    return true;
}

//-------------------------------------------

bool Log_Manager::log_file_callback(Log_Level level, Log_Source source, const std::string &msg)
{
    Log_Manager &manager = Log_Manager::instance();

    static std::mutex LOG_FILE_MUTEX;
    std::lock_guard<std::mutex> lock(LOG_FILE_MUTEX);

    std::ofstream file;
    file.open("voip.log", std::ios_base::out | std::ios_base::app);

    if (!file.good())
        return false;

    std::string str;
    str = manager.prefix(level, source);
    str += msg;

    file << str.c_str() << std::endl;
    file.close();
    return true;
}

//-------------------------------------------
//-------------------------------------------

void Logger::error(const std::string &msg)
{
    Log_Manager &manager = Log_Manager::instance();
    manager.log(Log_Manager::LOG_ERROR, _source, msg);
}

//-------------------------------------------

void Logger::error(const char *format, ...)
{
    Log_Manager &manager = Log_Manager::instance();
    char buffer[Log_Manager::MAX_LINE_LEN];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    std::string msg = buffer;
    manager.log(Log_Manager::LOG_ERROR, _source, msg);
}

//-------------------------------------------

void Logger::warning(const std::string &msg)
{
    Log_Manager &manager = Log_Manager::instance();
    manager.log(Log_Manager::LOG_WARNING, _source, msg);
}

//-------------------------------------------

void Logger::warning(const char *format, ...)
{
    Log_Manager &manager = Log_Manager::instance();
    char buffer[Log_Manager::MAX_LINE_LEN];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    std::string msg = buffer;
    manager.log(Log_Manager::LOG_WARNING, _source, msg);
}

//-------------------------------------------

void Logger::info(const std::string &msg)
{
    Log_Manager &manager = Log_Manager::instance();
    manager.log(Log_Manager::LOG_INFO, _source, msg);
}

//-------------------------------------------

void Logger::info(const char *format, ...)
{
    Log_Manager &manager = Log_Manager::instance();
    char buffer[Log_Manager::MAX_LINE_LEN];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    std::string msg = buffer;
    manager.log(Log_Manager::LOG_INFO, _source, msg);
}

//-------------------------------------------

void Logger::trace(const std::string &msg)
{
    Log_Manager &manager = Log_Manager::instance();
    manager.log(Log_Manager::LOG_TRACE, _source, msg);
}

//-------------------------------------------

void Logger::trace(const char *format, ...)
{
    Log_Manager &manager = Log_Manager::instance();
    char buffer[Log_Manager::MAX_LINE_LEN];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    std::string msg = buffer;
    manager.log(Log_Manager::LOG_TRACE, _source, msg);
}

//-------------------------------------------
