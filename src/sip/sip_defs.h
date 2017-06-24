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

#define SIP_VERSION             "SIP/2.0"
#define INVALID_UNSIGNED_SHORT  0xFFFF
#define INVALID_UNSIGNED_LONG   0xFFFFFFFF

enum SIP_Method_Type
{
    SIP_REQUEST_ACK,
    SIP_REQUEST_BYE,
    SIP_REQUEST_CANCEL,
    SIP_REQUEST_INFO,
    SIP_REQUEST_INVITE,
    SIP_REQUEST_MESSAGE,
    SIP_REQUEST_NOTIFY,
    SIP_REQUEST_OPTIONS,
    SIP_REQUEST_PRACK,
    SIP_REQUEST_PUBLISH,
    SIP_REQUEST_REFER,
    SIP_REQUEST_REGISTER,
    SIP_REQUEST_SUBSCRIBE,
    SIP_REQUEST_UPDATE,
    SIP_RESPONSE,
    SIP_METHOD_TYPE_INVALID
};

enum SIP_Header_Type
{
    SIP_HEADER_ACCEPT,
    SIP_HEADER_ACCEPT_ENCODING,
    SIP_HEADER_ACCEPT_LANGUAGE,
    SIP_HEADER_ALERT_INFO,
    SIP_HEADER_ALLOW,
    SIP_HEADER_ALLOW_EVENTS,
    SIP_HEADER_AUTHENTICATION_INFO,
    SIP_HEADER_AUTHORIZATION,
    SIP_HEADER_CALL_ID,
    SIP_HEADER_CALL_INFO,
    SIP_HEADER_CONTACT,
    SIP_HEADER_CONTENT_DISPOSITION,
    SIP_HEADER_CONTENT_ENCODING,
    SIP_HEADER_CONTENT_LANGUAGE,
    SIP_HEADER_CONTENT_LENGTH,
    SIP_HEADER_CONTENT_TYPE,
    SIP_HEADER_CSEQ,
    SIP_HEADER_DATE,
    SIP_HEADER_ERROR_INFO,
    SIP_HEADER_EVENT,
    SIP_HEADER_EXPIRES,
    SIP_HEADER_FROM,
    SIP_HEADER_IN_REPLY_TO,
    SIP_HEADER_MAX_FORWARDS,
    SIP_HEADER_MIME_VERSION,
    SIP_HEADER_MIN_EXPIRES,
    SIP_HEADER_ORGANIZATION,
    SIP_HEADER_PRIORITY,
    SIP_HEADER_PROXY_AUTHENTICATE,
    SIP_HEADER_PROXY_AUTHORIZATION,
    SIP_HEADER_PROXY_REQUIRE,
    SIP_HEADER_RECORD_ROUTE,
    SIP_HEADER_REPLY_TO,
    SIP_HEADER_REQUIRE,
    SIP_HEADER_RETRY_AFTER,
    SIP_HEADER_ROUTE,
    SIP_HEADER_SERVER,
    SIP_HEADER_SUBJECT,
    SIP_HEADER_SUBSCRIPTION_STATE,
    SIP_HEADER_SUPPORTED,
    SIP_HEADER_TIMESTAMP,
    SIP_HEADER_TO,
    SIP_HEADER_UNSUPPORTED,
    SIP_HEADER_USER_AGENT,
    SIP_HEADER_VIA,
    SIP_HEADER_WARNING,
    SIP_HEADER_WWW_AUTHENTICATE,
    SIP_HEADER_TYPE_INVALID
};

enum SIP_Address_Scheme
{
    SIP_ADDRESS_SCHEME_SIP,
    SIP_ADDRESS_SCHEME_SIPS,
    SIP_ADDRESS_SCHEME_INVALID,
};

enum SIP_User_Param
{
    SIP_USER_PARAM_PHONE,
    SIP_USER_PARAM_IP,
    SIP_USER_PARAM_INVALID,
};

enum SIP_Body_Type
{
    SIP_BODY_APPLICATION_SDP,
    SIP_BODY_APPLICATION_PIDF_XML,
    SIP_BODY_TEXT_PLAIN,
    SIP_BODY_TYPE_INVALID
};

enum SIP_Call_Info_Purpose
{
    SIP_CALL_INFO_PURPOSE_ICON,
    SIP_CALL_INFO_PURPOSE_INFO,
    SIP_CALL_INFO_PURPOSE_CARD,
    SIP_CALL_INFO_PURPOSE_INVALID
};

enum SIP_Media_Type
{
    SIP_MEDIA_TEXT,
    SIP_MEDIA_IMAGE,
    SIP_MEDIA_AUDIO,
    SIP_MEDIA_VIDEO,
    SIP_MEDIA_APPLICATION,
    SIP_MEDIA_MESSAGE,
    SIP_MEDIA_MULTIPART,
    SIP_MEDIA_TYPE_ASTERISK,
    SIP_MEDIA_TYPE_INVALID
};

enum SIP_Media_Subtype
{
    SIP_MEDIA_TEXT_PLAIN,
    SIP_MEDIA_TEXT_HTML,
    SIP_MEDIA_APPLICATION_SDP,
    SIP_MEDIA_APPLICATION_PIDF_XML,
    SIP_MEDIA_SUBTYPE_ASTERISK,
    SIP_MEDIA_SUBTYPE_INVALID
};

enum SIP_Date_Weekday
{
    SIP_DATE_WEEKDAY_MON,
    SIP_DATE_WEEKDAY_TUE,
    SIP_DATE_WEEKDAY_WED,
    SIP_DATE_WEEKDAY_THU,
    SIP_DATE_WEEKDAY_FRI,
    SIP_DATE_WEEKDAY_SAT,
    SIP_DATE_WEEKDAY_SUN,
    SIP_DATE_WEEKDAY_INVALID
};

enum SIP_Date_Month
{
    SIP_DATE_MONTH_JAN,
    SIP_DATE_MONTH_FEB,
    SIP_DATE_MONTH_MAR,
    SIP_DATE_MONTH_APR,
    SIP_DATE_MONTH_MAY,
    SIP_DATE_MONTH_JUN,
    SIP_DATE_MONTH_JUL,
    SIP_DATE_MONTH_AUG,
    SIP_DATE_MONTH_SEP,
    SIP_DATE_MONTH_OCT,
    SIP_DATE_MONTH_NOV,
    SIP_DATE_MONTH_DEC,
    SIP_DATE_MONTH_INVALID
};

enum SIP_Disposition_Type
{
    SIP_DISPOSITION_RENDER,
    SIP_DISPOSITION_SESSION,
    SIP_DISPOSITION_ICON,
    SIP_DISPOSITION_ALERT,
    SIP_DISPOSITION_TYPE_INVALID
};

enum SIP_Disposition_Handling
{
    SIP_DISPOSITION_HANDLING_OPTIONAL,
    SIP_DISPOSITION_HANDLING_REQUIRED,
    SIP_DISPOSITION_HANDLING_INVALID
};

enum SIP_Priority_Value
{
    SIP_PRIORITY_EMERGENCY,
    SIP_PRIORITY_URGENT,
    SIP_PRIORITY_NORMAL,
    SIP_PRIORITY_NON_URGENT,
    SIP_PRIORITY_VALUE_INVALID
};

enum SIP_Transaction_Type
{
    SIP_TRANSACTION_CLIENT_INVITE,
    SIP_TRANSACTION_CLIENT_NON_INVITE,
    SIP_TRANSACTION_SERVER_INVITE,
    SIP_TRANSACTION_SERVER_NON_INVITE,
    SIP_TRANSACTION_TYPE_INVALID
};

enum SIP_Transport_Type
{
    SIP_TRANSPORT_UDP,
    SIP_TRANSPORT_TCP,
    SIP_TRANSPORT_TLS,
    SIP_TRANSPORT_WS,
    SIP_TRANSPORT_WSS,
    SIP_TRANSPORT_SCTP,
    SIP_TRANSPORT_TYPE_INVALID
};

enum SIP_Event_Package
{
    SIP_EVENT_PRESENCE,
    SIP_EVENT_PACKAGE_INVALID
};

enum SIP_Subscription_State
{
    SIP_SUBSCRIPTION_STATE_ACTIVE,
    SIP_SUBSCRIPTION_STATE_PENDING,
    SIP_SUBSCRIPTION_STATE_TERMINATED,
    SIP_SUBSCRIPTION_STATE_INVALID
};

enum SIP_Subscription_State_Reason
{
    SIP_SUBSCRIPTION_STATE_REASON_DEACTIVATED,
    SIP_SUBSCRIPTION_STATE_REASON_PROBATION,
    SIP_SUBSCRIPTION_STATE_REASON_REJECTED,
    SIP_SUBSCRIPTION_STATE_REASON_TIMEOUT,
    SIP_SUBSCRIPTION_STATE_REASON_GIVEUP,
    SIP_SUBSCRIPTION_STATE_REASON_NORESOURCE,
    SIP_SUBSCRIPTION_STATE_REASON_INVARIANT,
    SIP_SUBSCRIPTION_STATE_REASON_INVALID,
};

enum SIP_Pidf_Xml_Basic_Element
{
    SIP_PIDF_XML_OPEN,
    SIP_PIDF_XML_CLOSED,
    SIP_PIDF_XML_BASIC_ELEMENT_INVALID
};

enum SIP_Event_Callback
{
    SIP_SESSION_INVITATION,
    SIP_SESSION_INITIATED,
    SIP_SESSION_TERMINATED,
    SIP_SUBSCRIPTION_INITIATED,
    SIP_SUBSCRIPTION_TERMINATED,
    SIP_MESSAGE_RECEIVED,
    SIP_EVENT_CALLBACK_INVALID
};

enum SIP_Call_Status
{
    SIP_CALL_STATUS_INACTIVE,
    SIP_CALL_STATUS_INCOMING,
    SIP_CALL_STATUS_OUTGOING
};

enum SIP_Timer
{
    SIP_TIMER_A,
    SIP_TIMER_B,
    SIP_TIMER_C,
    SIP_TIMER_D,
    SIP_TIMER_E,
    SIP_TIMER_F,
    SIP_TIMER_G,
    SIP_TIMER_H,
    SIP_TIMER_I,
    SIP_TIMER_J,
    SIP_TIMER_K,
    SIP_TIMER_COUNT,

    SIP_TIMER_1 = 500,     //500 millisec
    SIP_TIMER_2 = 4000,    //4 sec
    SIP_TIMER_4 = 5000,    //5 sec
    SIP_TIMER_32s = 32000, //32 sec
};

enum SIP_Header_Separator
{
    SIP_HEADER_SEPARATOR_NONE,
    SIP_HEADER_SEPARATOR_COMMA,
    SIP_HEADER_SEPARATOR_CRLF,
};
