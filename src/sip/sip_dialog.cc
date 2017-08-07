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

#include "sip_dialog.h"

Logger SIP_Dialog::_logger(Log_Manager::LOG_SIP_DIALOG);

//-------------------------------------------

SIP_Dialog::SIP_Dialog() : _state(STATE_IDLE), _local_sequence(SIP_Header_CSeq::INVALID_SEQUENCE),
    _remote_sequence(SIP_Header_CSeq::INVALID_SEQUENCE)
{
}

//-------------------------------------------

SIP_Dialog::~SIP_Dialog()
{
    clear_routes();
}

//-------------------------------------------

bool SIP_Dialog::set_client_dialog(SIP_Request *request, SIP_Response *response)
{
    if ((!request) || (!response))
    {
        _logger.warning("Failed to set client dialog: invalid messages");
        return false;
    }

    SIP_Header_Call_ID *header_call_id = dynamic_cast<SIP_Header_Call_ID *>(request->get_header(SIP_HEADER_CALL_ID));
    SIP_Header_CSeq *header_cseq = dynamic_cast<SIP_Header_CSeq *>(request->get_header(SIP_HEADER_CSEQ));
    SIP_Header_From *header_from = dynamic_cast<SIP_Header_From *>(request->get_header(SIP_HEADER_FROM));

    SIP_Header_To *header_to = dynamic_cast<SIP_Header_To *>(response->get_header(SIP_HEADER_TO));
    SIP_Header_Contact *header_contact = dynamic_cast<SIP_Header_Contact *>(response->get_header(SIP_HEADER_CONTACT));

    if ((!header_call_id) || (!header_cseq) || (!header_from) || (!header_to) || (!header_contact))
    {
        _logger.warning("Failed to set client dialog: invalid headers");
        return false;
    }

    _call_id = header_call_id->get_call_id();

    _local_uri = header_from->get_address();
    _local_tag = header_from->get_tag();

    _remote_uri = header_to->get_address();
    _remote_tag = header_to->get_tag(); // It can be empty: compatibility with RFC 2543

    _remote_target = header_contact->get_address();

    _local_sequence = header_cseq->get_sequence();
    _remote_sequence = SIP_Header_CSeq::INVALID_SEQUENCE;

    if ((_call_id.empty()) || (_local_uri.get_scheme_str().empty()) || (_local_tag.empty()) || (_remote_uri.get_scheme_str().empty()) ||
        (_remote_target.get_scheme_str().empty()) || (_local_sequence == SIP_Header_CSeq::INVALID_SEQUENCE))
    {
        _logger.warning("Failed to set client dialog: invalid header values");
        return false;
    }

    clear_routes();
    unsigned short record_route_size = response->get_header_size(SIP_HEADER_RECORD_ROUTE);
    for (unsigned short i = 0; i < record_route_size; i++)
    {
        SIP_Header_Record_Route *header_record_route = dynamic_cast<SIP_Header_Record_Route *>
                (response->get_header(SIP_HEADER_RECORD_ROUTE, i));

        if (header_record_route)
        {
            SIP_Header_Route *header_route = new SIP_Header_Route();
            header_route->set_address(header_record_route->get_address());
            header_route->set_parameters(header_record_route->get_parameters());
            add_route_front(header_route);
        }
    }

    _logger.trace("Client dialog set");
    return true;
}

//-------------------------------------------

bool SIP_Dialog::set_server_dialog(SIP_Request *request, SIP_Response *response)
{
    if ((!request) || (!response))
    {
        _logger.warning("Failed to set server dialog: invalid messages");
        return false;
    }

    SIP_Header_Call_ID *header_call_id = dynamic_cast<SIP_Header_Call_ID *>(request->get_header(SIP_HEADER_CALL_ID));
    SIP_Header_CSeq *header_cseq = dynamic_cast<SIP_Header_CSeq *>(request->get_header(SIP_HEADER_CSEQ));
    SIP_Header_From *header_from = dynamic_cast<SIP_Header_From *>(request->get_header(SIP_HEADER_FROM));
    SIP_Header_Contact *header_contact = dynamic_cast<SIP_Header_Contact *>(request->get_header(SIP_HEADER_CONTACT));

    SIP_Header_To *header_to = dynamic_cast<SIP_Header_To *>(response->get_header(SIP_HEADER_TO));

    if ((!header_call_id) || (!header_cseq) || (!header_from) || (!header_contact) || (!header_to))
    {
        _logger.warning("Failed to set server dialog: invalid headers");
        return false;
    }

    _call_id = header_call_id->get_call_id();

    _local_uri = header_to->get_address();
    _local_tag = header_to->get_tag();

    _remote_uri = header_from->get_address();
    _remote_tag = header_from->get_tag(); // It can be empty: compatibility with RFC 2543

    _remote_target = header_contact->get_address();

    _local_sequence = SIP_Header_CSeq::INVALID_SEQUENCE;
    _remote_sequence = header_cseq->get_sequence();

    if ((_call_id.empty()) || (_local_uri.get_scheme_str().empty()) || (_local_tag.empty()) || (_remote_uri.get_scheme_str().empty()) ||
        (_remote_target.get_scheme_str().empty()) || (_remote_sequence == SIP_Header_CSeq::INVALID_SEQUENCE))
    {
        _logger.warning("Failed to set server dialog: invalid header values");
        return false;
    }

    clear_routes();
    unsigned short record_route_size = request->get_header_size(SIP_HEADER_RECORD_ROUTE);
    for (unsigned short i = 0; i < record_route_size; i++)
    {
        SIP_Header_Record_Route *header_record_route = dynamic_cast<SIP_Header_Record_Route *>
                (response->get_header(SIP_HEADER_RECORD_ROUTE, i));

        if (header_record_route)
        {
            SIP_Header_Route *header_route = new SIP_Header_Route();
            header_route->set_address(header_record_route->get_address());
            header_route->set_parameters(header_record_route->get_parameters());
            add_route_back(header_route);
        }
    }

    _logger.trace("Server dialog set");
    return true;
}

//-------------------------------------------

void SIP_Dialog::add_route_back(SIP_Header_Route *route)
{
    _routes.push_back(route);
}

//-------------------------------------------

void SIP_Dialog::add_route_front(SIP_Header_Route *route)
{
    _routes.push_front(route);
}

//-------------------------------------------

void SIP_Dialog::clear_routes()
{
    std::list<SIP_Header_Route *>::iterator it = _routes.begin();
    while (it != _routes.end())
    {
        SIP_Header_Route *route = *it++;
        _routes.pop_front();
        delete route;
    }
}

//-------------------------------------------

unsigned short SIP_Dialog::get_route_size()
{
    return (unsigned short) _routes.size();
}

//-------------------------------------------

SIP_Header_Route *SIP_Dialog::get_route(int pos)
{
    int i = 0;
    std::list<SIP_Header_Route *>::iterator it = _routes.begin();
    while (it != _routes.end())
    {
        if (i++ == pos)
            return *it;
        it++;
    }

    return NULL;
}

//-------------------------------------------
