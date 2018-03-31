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

#include "util/util_defs.h"
#include "util/log_manager.h"
#include <string>
#include <list>

class Parameter_List
{
public:
    Parameter_List() {}
    Parameter_List(const Parameter_List &value) { *this = value; }
    ~Parameter_List() {}

    bool query(QueryCommand cmd, const std::string &query, std::string &result);

    void set_parameters(std::list<std::string> &parameters) { _parameters = parameters; }
    bool add_parameter(std::string parameter, unsigned short pos = 0xFFFF);
    bool remove_parameter(unsigned short pos);
    void clear_parameters() { _parameters.clear(); }
    std::list<std::string> &get_parameters() { return _parameters; }
    std::string get_parameter(unsigned short pos = 0);
    unsigned short get_parameter_size() { return (unsigned short) _parameters.size(); }

private:
    std::list<std::string> _parameters;

    static Logger _logger;
};
