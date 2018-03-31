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

#include "query.h"

//-------------------------------------------

Query::Query(const std::string &query)
{
    std::string::size_type pos = query.find_first_of('.');

    if (pos != std::string::npos)
    {
        _command = query.substr(0, pos);
        _remaining = query.substr(pos + 1);
    }else
        _command = query;
}

//-------------------------------------------
