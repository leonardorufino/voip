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

#include "parameter_list.h"
#include "string_functions.h"
#include "query.h"

Logger Parameter_List::_logger(Log_Manager::LOG_PARAMETER_LIST);

//-------------------------------------------

bool Parameter_List::query(QueryCommand cmd, const std::string &query, std::string &result)
{
    if (query.empty())
    {
        _logger.warning("Failed to query: invalid query (cmd=%d)", cmd);
        return false;
    }

    Query query_position(query);
    unsigned short pos = String_Functions::str_to_us(query_position._command);
    if (pos == INVALID_UNSIGNED_SHORT)
    {
        _logger.warning("Failed to query: invalid parameter position (cmd=%d, query=%s)", cmd, query.c_str());
        return false;
    }

    if (!query_position._remaining.empty())
    {
        if (cmd == QUERY_ADD)
        {
            if (!add_parameter(query_position._remaining, pos))
            {
                _logger.warning("Failed to query: add parameter failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;
        }
    }else
    {
        if (cmd == QUERY_DEL)
        {
            if (!remove_parameter(pos))
            {
                _logger.warning("Failed to query: remove parameter failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            return true;

        }else if (cmd == QUERY_GET)
        {
            std::string parameter = get_parameter(pos);
            if (parameter.empty())
            {
                _logger.warning("Failed to query: get parameter failed (cmd=%d, query=%s)", cmd, query.c_str());
                return false;
            }

            result = parameter;
            return true;
        }
    }

    _logger.warning("Failed to query: invalid query (cmd=%d, query=%s)", cmd, query.c_str());
    return false;
}

//-------------------------------------------

bool Parameter_List::add_parameter(std::string parameter, unsigned short pos)
{
    if (parameter.empty())
    {
        _logger.warning("Failed to add parameter: invalid parameter");
        return false;
    }

    unsigned short count = 0;

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        if (count++ == pos)
            break;

        it++;
    }

    _parameters.insert(it, parameter);
    return true;
}

//-------------------------------------------

bool Parameter_List::remove_parameter(unsigned short pos)
{
    unsigned short count = 0;

    std::list<std::string>::iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        if (count++ == pos)
        {
            _parameters.erase(it);
            return true;
        }

        it++;
    }

    _logger.warning("Failed to remove parameter: invalid position (pos=%d, count=%d)", pos, count);
    return false;
}

//-------------------------------------------

std::string Parameter_List::get_parameter(unsigned short pos)
{
    unsigned short count = 0;

    std::list<std::string>::const_iterator it = _parameters.begin();
    while (it != _parameters.end())
    {
        if (count++ == pos)
            return *it;

        it++;
    }

    _logger.warning("Failed to get parameter: invalid position (pos=%d, count=%d)", pos, count);
    return "";
}

//-------------------------------------------
