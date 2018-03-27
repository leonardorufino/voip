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

#include "socket.h"
#include "util_functions.h"

Logger Socket::_logger(Log_Manager::LOG_SOCKET);
Socket_Control *Socket_Control::_instance = NULL;

//-------------------------------------------

Socket::Socket() : _state(STATE_IDLE), _socket(INVALID_SOCKET), _connect_callback(NULL), _connect_callback_data(NULL),
    _accept_callback(NULL), _accept_callback_data(NULL), _receive_callback(NULL), _receive_callback_data(NULL)
{
#ifdef WIN32
    Startup();
#endif
}

//-------------------------------------------

Socket::~Socket()
{
    if ((_state != STATE_IDLE) && (_state != STATE_CLOSED))
        close();
}

//-------------------------------------------

void Socket::set_connect_callback(connect_callback *callback, void *data)
{
    _connect_callback = callback;
    _connect_callback_data = data;
}

//-------------------------------------------

bool Socket::call_connect_callback(bool success)
{
    try
    {
        if (_connect_callback)
        {
            _logger.trace("Calling connect callback (state=%d, socket=%d, success=%d)", _state, _socket, success);
            return _connect_callback(_connect_callback_data, success);
        }

        _logger.trace("Connect callback not configured (state=%d, socket=%d, success=%d)", _state, _socket, success);
        return false;
    }catch (std::exception &e)
    {
        _logger.warning("Exception in call connect callback (state=%d, socket=%d, success=%d, msg=%s)",
                        _state, _socket, success, e.what());
        return false;
    }catch (...)
    {
        _logger.warning("Exception in call connect callback (state=%d, socket=%d, success=%d)", _state, _socket, success);
        return false;
    }
}

//-------------------------------------------

void Socket::set_accept_callback(accept_callback *callback, void *data)
{
    _accept_callback = callback;
    _accept_callback_data = data;
}

//-------------------------------------------

bool Socket::call_accept_callback(Socket_TCP_Client *accepted, std::string address, unsigned short port)
{
    try
    {
        if (_accept_callback)
        {
            _logger.trace("Calling accept callback (state=%d, socket=%d, accepted=%d, address=%s, port=%d)",
                          _state, _socket, accepted->_socket, address.c_str(), port);

            return _accept_callback(_accept_callback_data, accepted, address, port);
        }

        _logger.trace("Accept callback not configured (state=%d, socket=%d, accepted=%d, address=%s, port=%d)",
                      _state, _socket, accepted->_socket, address.c_str(), port);
        return false;
    }catch (std::exception &e)
    {
        _logger.warning("Exception in call accept callback (state=%d, socket=%d, accepted=%d, address=%s, port=%d)",
                        _state, _socket, accepted->_socket, address.c_str(), port, e.what());
        return false;
    }catch (...)
    {
        _logger.warning("Exception in call accept callback (state=%d, socket=%d, accepted=%d, address=%s, port=%d)",
                        _state, _socket, accepted->_socket, address.c_str(), port);
        return false;
    }
}

//-------------------------------------------

void Socket::set_receive_callback(receive_callback *callback, void *data)
{
    _receive_callback = callback;
    _receive_callback_data = data;
}

//-------------------------------------------

bool Socket::call_receive_callback(const char *buffer, int size, std::string address, unsigned short port)
{
    try
    {
        if (_receive_callback)
        {
            _logger.trace("Calling receive callback (state=%d, socket=%d, address=%s, port=%d, size=%d)",
                          _state, _socket, address.c_str(), port, size);
            return _receive_callback(_receive_callback_data, buffer, size, address, port);
        }

        _logger.trace("Receive callback not configured (state=%d, socket=%d, address=%s, port=%d, size=%d)",
                      _state, _socket, address.c_str(), port, size);
        return false;
    }catch (std::exception &e)
    {
        _logger.warning("Exception in call receive callback (state=%d, socket=%d, address=%s, port=%d, size=%d, msg=%s)",
                        _state, _socket, address.c_str(), port, size, e.what());
        return false;
    }catch (...)
    {
        _logger.warning("Exception in call receive callback (state=%d, socket=%d, address=%s, port=%d, size=%d)",
                        _state, _socket, address.c_str(), port, size);
        return false;
    }
}

//-------------------------------------------

bool Socket::create(int af, int type, int protocol)
{
    if (_state != STATE_IDLE)
    {
        _logger.warning("Failed to create: invalid state (state=%d)", _state);
        return false;
    }

    _socket = socket(af, type, protocol);
    if (_socket == INVALID_SOCKET)
    {
        _logger.warning("Failed to create: socket failed (af=%d, type=%d, protocol=%d, error=%d)", af, type, protocol, GET_LAST_ERROR);
        return false;
    }

    _state = STATE_OPEN;
    _logger.trace("Socket created (socket=%d, af=%d, type=%d, protocol=%d)", _socket, af, type, protocol);
    return true;
}

//-------------------------------------------

bool Socket::close()
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Failed to close: invalid state (state=%d)", _state);
        return false;
    }

    if (::closesocket(_socket))
    {
        _logger.warning("Failed to close: close socket failed(socket=%d, error=%d)", _socket, GET_LAST_ERROR);
        _state = STATE_CLOSED;
        _socket = INVALID_SOCKET;
        return false;
    }

    _logger.trace("Socket closed (socket=%d)", _socket);
    _state = STATE_CLOSED;
    _socket = INVALID_SOCKET;
    return true;
}

//-------------------------------------------

bool Socket::set_so_snd_buf(int size)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Failed to set socket option send buffer: invalid state (state=%d)", _state);
        return false;
    }

    if (setsockopt(_socket, SOL_SOCKET, SO_SNDBUF, (const char *) &size, sizeof(size)))
    {
        _logger.warning("Failed to set socket option send buffer: setsockopt failed (socket=%d, size=%d, error=%d)",
                        _socket, size, GET_LAST_ERROR);
        return false;
    }

    _logger.trace("Set socket option send buffer (socket=%d, size=%d)", _socket, size);
    return true;
}

//-------------------------------------------

bool Socket::set_so_rcv_buf(int size)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Failed to set socket option receive buffer: invalid state (state=%d)", _state);
        return false;
    }

    if (setsockopt(_socket, SOL_SOCKET, SO_RCVBUF, (const char * ) &size, sizeof(size)))
    {
        _logger.warning("Failed to set socket option receive buffer: setsockopt failed (socket=%d, size=%d, error=%d)", _socket, size, GET_LAST_ERROR);
        return false;
    }

    _logger.trace("Set socket option receive buffer (socket=%d, size=%d)", _socket, size);
    return true;
}

//-------------------------------------------

bool Socket::set_so_reuse_addr(int value)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Failed to set socket option reuse address: invalid state (state=%d)", _state);
        return false;
    }

    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (const char *) &value, sizeof(value)))
    {
        _logger.warning("Failed to set socket option reuse address: setsockopt failed (socket=%d, value=%d, error=%d)",
                        _socket, value, GET_LAST_ERROR);
        return false;
    }

    _logger.trace("Set socket option reuse address (socket=%d, value=%d)", _socket, value);
    return true;
}

//-------------------------------------------

bool Socket::set_tcp_no_delay(int value)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Failed to set tcp no delay: invalid state (state=%d)", _state);
        return false;
    }

    if (setsockopt(_socket, IPPROTO_TCP, TCP_NODELAY, (const char *) &value, sizeof(value)))
    {
        _logger.warning("Failed to set tcp no delay: setsockopt failed (socket=%d, value=%d, error=%d)",
            _socket, value, GET_LAST_ERROR);
        return false;
    }

    _logger.trace("Set tcp no delay (socket=%d, value=%d)", _socket, value);
    return true;
}

//-------------------------------------------

bool Socket::set_non_blocking(bool non_blocking)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Failed to set non-blocking: invalid state (state=%d)", _state);
        return false;
    }

#ifdef WIN32
    unsigned long arg = non_blocking ? 1 : 0;
    if (ioctlsocket(_socket, FIONBIO, &arg))
    {
        _logger.warning("Failed to set non-blocking: ioctlsocket failed (socket=%d, non_blocking=%d, error=%d)",
                        _socket, non_blocking, GET_LAST_ERROR);
        return false;
    }
#else
    int flags = fcntl(_socket, F_GETFL, 0);
    if (flags < 0)
    {
        _logger.warning("Failed to set non-blocking: fcntl get failed (socket=%d, non_blocking=%d, error=%d)",
                        _socket, non_blocking, GET_LAST_ERROR);
        return false;
    }

    if (non_blocking)
        flags |= O_NONBLOCK;
    else
        flags &= ~O_NONBLOCK;

    if (fcntl(_socket, F_SETFL, flags))
    {
        _logger.warning("Failed to set non-blocking: fcntl set failed (socket=%d, non_blocking=%d, error=%d)",
                        _socket, non_blocking, GET_LAST_ERROR);
        return false;
    }
#endif

    _logger.trace("Set non-blocking (socket=%d, non_blocking=%d)", _socket, non_blocking);
    return true;
}

//-------------------------------------------

bool Socket::get_so_error(int &value)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Failed to get socket option error: invalid state (state=%d)", _state);
        return false;
    }

    socklen_t len = sizeof(value);
    if (getsockopt(_socket, SOL_SOCKET, SO_ERROR, (char *) &value, &len))
    {
        _logger.warning("Failed to get socket option error: getsockopt failed (socket=%d, value=%d, error=%d)",
                        _socket, value, GET_LAST_ERROR);
        return false;
    }

    _logger.trace("Get socket option error (socket=%d, value=%d)", _socket, value);
    return true;
}

//-------------------------------------------

bool Socket::bind(std::string address, unsigned short port)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Failed to bind: invalid state (state=%d)", _state);
        return false;
    }

    sockaddr_storage ss;
    if (!address_to_sockaddr(address, port, ss))
    {
        _logger.warning("Failed to bind: address to sockaddr failed (socket=%d, address=%s, port=%d)", _socket, address.c_str(), port);
        return false;
    }

    if (ss.ss_family == AF_INET6)
    {
        sockaddr_in6 *sin = (sockaddr_in6 *) &ss;
        sin->sin6_scope_id = get_scope_id(address);
    }

    if (::bind(_socket, (sockaddr *) &ss, sizeof(ss)))
    {
        _logger.warning("Failed to bind: bind failed (socket=%d, address=%s, port=%d, error=%d)",
                        _socket, address.c_str(), port, GET_LAST_ERROR);
        return false;
    }

    _logger.trace("Socket binded (socket=%d, address=%s, port=%d)", _socket, address.c_str(), port);
    return true;
}

//-------------------------------------------

bool Socket::listen(int backlog)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Failed to listen: invalid state (state=%d)", _state);
        return false;
    }

    if (::listen(_socket, backlog))
    {
        _logger.warning("Failed to listen: listen failed (socket=%d, backlog=%d, error=%d)", _socket, backlog, GET_LAST_ERROR);
        return false;
    }

    _state = STATE_LISTENING;
    _logger.trace("Socket listening (socket=%d, backlog=%d)", _socket, backlog);
    return true;
}

//-------------------------------------------

bool Socket::accept(socket_t &accept_socket, std::string &address, unsigned short &port)
{
    if (_state != STATE_LISTENING)
    {
        _logger.warning("Failed to accept: invalid state (state=%d)", _state);
        return false;
    }

    sockaddr_storage ss;
    socklen_t ss_len = sizeof(ss);

    accept_socket = ::accept(_socket, (sockaddr *) &ss, &ss_len);
    if (accept_socket == INVALID_SOCKET)
    {
        _logger.warning("Failed to accept: accept failed (socket=%d, error=%d)", _socket, GET_LAST_ERROR);
        return false;
    }

    if (!sockaddr_to_address(ss, address, port))
    {
        _logger.warning("Failed to accept: sockaddr to address failed (socket=%d, accepted=%d)", _socket, accept_socket);

        if (::closesocket(accept_socket))
        {
            _logger.warning("Failed to accept: close socket failed (socket=%d, accepted=%d, error=%d)",
                            _socket, accept_socket, GET_LAST_ERROR);
            accept_socket = INVALID_SOCKET;
        }

        return false;
    }

    _logger.trace("Socket accepted (socket=%d, accepted=%d, address=%s, port=%d)", _socket, accept_socket, address.c_str(), port);
    return true;
}

//-------------------------------------------

bool Socket::connect(std::string address, unsigned short port)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Failed to connect: invalid state (state=%d)", _state);
        return false;
    }

    sockaddr_storage ss;
    if (!address_to_sockaddr(address, port, ss))
    {
        _logger.warning("Failed to connect: address to sockaddr failed (socket=%d, address=%s, port=%d)", _socket, address.c_str(), port);
        return false;
    }

    if (::connect(_socket, (sockaddr *) &ss, sizeof(ss)))
    {
        switch (GET_LAST_ERROR)
        {
#ifdef WIN32
            case WSAEWOULDBLOCK:
#else
            case EINPROGRESS:
            case EWOULDBLOCK:
#endif
            {
                _state = STATE_CONNECTING;
                _logger.trace("Socket connect would block (socket=%d, address=%s, port=%d, param=%d)",
                              _socket, address.c_str(), port, GET_LAST_ERROR);
                return true;
            }

            default:
            {
                _logger.warning("Failed to connect: connect failed (socket=%d, address=%s, port=%d, error=%d)",
                                _socket, address.c_str(), port, GET_LAST_ERROR);
                return false;
            }
        }
    }

    _state = STATE_CONNECTED;
    _logger.trace("Socket connected (socket=%d, address=%s, port=%d)", _socket, address.c_str(), port);
    call_connect_callback(true);
    return true;
}

//-------------------------------------------

bool Socket::send(const char *buffer, int size)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Failed to send: invalid state (state=%d)", _state);
        return false;
    }

    if (::send(_socket, buffer, size, 0) != size)
    {
        switch (GET_LAST_ERROR)
        {
#ifdef WIN32
            case WSAEWOULDBLOCK:
#else
            case EINPROGRESS:
            case EWOULDBLOCK:
#endif
            {
                _logger.trace("Socket message send would block (socket=%d, size=%d, param=%d)", _socket, size, GET_LAST_ERROR);
                return true;
            }

            default:
            {
                _logger.warning("Failed to send: send failed (socket=%d, error=%d)", _socket, GET_LAST_ERROR);
                return false;
            }
        }
    }

    _logger.trace("Socket message sent (socket=%d, size=%d)", _socket, size);
    return true;
}

//-------------------------------------------

bool Socket::send(const char *buffer, int size, std::string address, unsigned short port)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Failed to send: invalid state (state=%d)", _state);
        return false;
    }

    sockaddr_storage ss;
    if (!address_to_sockaddr(address, port, ss))
    {
        _logger.warning("Failed to send: address to sockaddr failed (socket=%d, address=%s, port=%d)", _socket, address.c_str(), port);
        return false;
    }

    if (::sendto(_socket, buffer, size, 0, (sockaddr *) &ss, sizeof(ss)) != size)
    {
        switch (GET_LAST_ERROR)
        {
#ifdef WIN32
            case WSAEWOULDBLOCK:
#else
            case EINPROGRESS:
            case EWOULDBLOCK:
#endif
            {
                _logger.trace("Socket message send would block (socket=%d, address=%s, port=%d, size=%d, param=%d)",
                              _socket, address.c_str(), port, size, GET_LAST_ERROR);
                return true;
            }

            default:
            {
                _logger.warning("Failed to send: sendto failed (socket=%d, address=%s, port=%d, error=%d)",
                                _socket, address.c_str(), port, GET_LAST_ERROR);
                return false;
            }
        }
    }

    _logger.trace("Socket message sent (socket=%d, address=%s, port=%d, size=%d)", _socket, address.c_str(), port, size);
    return true;
}

//-------------------------------------------

int Socket::receive(char *buffer, int size)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Failed to receive: invalid state (state=%d)", _state);
        return false;
    }

    int len = recv(_socket, buffer, size, 0);
    if (len < 0)
    {
        _logger.warning("Failed to receive: recv failed (socket=%d, error=%d)", _socket, GET_LAST_ERROR);
        return -1;
    }

    _logger.trace("Socket message received (socket=%d, len=%d)", _socket, len);
    return len;
}

//-------------------------------------------

int Socket::receive(char *buffer, int size, std::string &address, unsigned short &port)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Failed to receive: invalid state (state=%d)", _state);
        return false;
    }

    sockaddr_storage ss;
    socklen_t ss_len = sizeof(ss);

    int len = recvfrom(_socket, buffer, size, 0, (sockaddr *) &ss, &ss_len);
    if (len < 0)
    {
        _logger.warning("Failed to receive: recvfrom failed (socket=%d, error=%d)", _socket, GET_LAST_ERROR);
        return -1;
    }

    if (!sockaddr_to_address(ss, address, port))
    {
        _logger.warning("Failed to receive: sockaddr to address failed (socket=%d)", _socket);
        return -1;
    }

    _logger.trace("Socket message received (socket=%d, address=%s, port=%d, len=%d)", _socket, address.c_str(), port, len);
    return len;
}

//-------------------------------------------

int Socket::select(unsigned long timeout, int *read, int *write, int *except)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Failed to select: invalid state (state=%d)", _state);
        return -1;
    }

    timeval tv;
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout - (1000 * tv.tv_sec)) * 1000;

    fd_set read_set, write_set, except_set;

    fd_set *p_read_set = NULL;
    fd_set *p_write_set = NULL;
    fd_set *p_except_set = NULL;

    if (read)
    {
        FD_ZERO(&read_set);
        FD_SET(_socket, &read_set);
        p_read_set = &read_set;
        *read = 0;
    }

    if (write)
    {
        FD_ZERO(&write_set);
        FD_SET(_socket, &write_set);
        p_write_set = &write_set;
        *write = 0;
    }

    if (except)
    {
        FD_ZERO(&except_set);
        FD_SET(_socket, &except_set);
        p_except_set = &except_set;
        *except = 0;
    }

    int ret = ::select((int) _socket + 1, p_read_set, p_write_set, p_except_set, &tv);
    if (ret < 0)
    {
        _logger.warning("Failed to select: select failed (socket=%d, error=%d)", _socket, GET_LAST_ERROR);
        return -1;
    }

    if ((read) && (FD_ISSET(_socket, &read_set)))
        *read = 1;

    if ((write) && (FD_ISSET(_socket, &write_set)))
        *write = 1;

    if ((except) && (FD_ISSET(_socket, &except_set)))
        *except = 1;

    _logger.trace("Socket selected (socket=%d, ret=%d)", _socket, ret);
    return ret;
}

//-------------------------------------------
//-------------------------------------------

int Socket::address_family_to_af(Address_Family family)
{
    switch (family)
    {
        case ADDRESS_FAMILY_IPv4:   return AF_INET;
        case ADDRESS_FAMILY_IPv6:   return AF_INET6;
        default:                    return 0;
    }
}

//-------------------------------------------

Socket::Address_Family Socket::address_to_address_family(std::string address)
{
    in_addr addr4;
    if (inet_pton(AF_INET, address.c_str(), &addr4) > 0)
        return ADDRESS_FAMILY_IPv4;

    in6_addr addr6;
    if (inet_pton(AF_INET6, address.c_str(), &addr6) > 0)
        return ADDRESS_FAMILY_IPv6;

    return ADDRESS_FAMILY_INVALID;
}

//-------------------------------------------

bool Socket::address_to_sockaddr(std::string address, unsigned short port, sockaddr_storage &ss)
{
    if (address.empty())
        return false;

    std::string addr;

    memset(&ss, 0, sizeof(ss));

    in_addr addr4;
    if (inet_pton(AF_INET, address.c_str(), &addr4) > 0)
    {
        sockaddr_in *sin = (sockaddr_in *) &ss;
        sin->sin_family = AF_INET;
        sin->sin_port = htons(port);
        memcpy(&sin->sin_addr, &addr4, sizeof(sin->sin_addr));
        return true;
    }

    in6_addr addr6;
    if (inet_pton(AF_INET6, address.c_str(), &addr6) > 0)
    {
        sockaddr_in6 *sin = (sockaddr_in6 *) &ss;
        sin->sin6_family = AF_INET6;
        sin->sin6_port = htons(port);
        memcpy(&sin->sin6_addr, &addr6, sizeof(sin->sin6_addr));
        return true;
    }

    return false;
}

//-------------------------------------------

bool Socket::sockaddr_to_address(sockaddr_storage &ss, std::string &address, unsigned short &port)
{
    if (!sockaddr_to_address(ss, address))
        return false;

    sockaddr_in *sin = (sockaddr_in *) &ss;
    port = ntohs(sin->sin_port);
    return true;
}

//-------------------------------------------

bool Socket::sockaddr_to_address(sockaddr_storage &ss, std::string &address)
{
    if (ss.ss_family == AF_INET)
    {
        sockaddr_in *sin = (sockaddr_in *) &ss;
        char buf[50] = {0};

        if (!inet_ntop(ss.ss_family, &sin->sin_addr, buf, sizeof(buf)))
        {
            _logger.warning("Failed in sockaddr to address: IPv4 inet_ntop failed (error=%d)", GET_LAST_ERROR);
            return false;
        }

        address = buf;
        return true;
    }

    if (ss.ss_family == AF_INET6)
    {
        sockaddr_in6 *sin = (sockaddr_in6 *) &ss;
        char buf[50] = {0};

        if (!inet_ntop(ss.ss_family, &sin->sin6_addr, buf, sizeof(buf)))
        {
            _logger.warning("Failed in sockaddr to address: IPv6 inet_ntop failed (error=%d)", GET_LAST_ERROR);
            return false;
        }

        address = buf;
        return true;
    }

    return false;
}

//-------------------------------------------

unsigned long Socket::get_scope_id(std::string address)
{
    unsigned long scope_id = 0;
    bool found = false;

#ifdef WIN32
    PIP_ADAPTER_ADDRESSES adapter_addresses = NULL;
    ULONG size = 0;
    DWORD ret;

    for (unsigned short i = 0; i < 5; i++)
    {
        ret = GetAdaptersAddresses(AF_INET6, GAA_FLAG_INCLUDE_PREFIX, NULL, adapter_addresses, &size);

        if ((ret == NO_ERROR) || (ret == ERROR_NO_DATA))
            break;

        if (ret == ERROR_BUFFER_OVERFLOW)
        {
            if (adapter_addresses)
                free(adapter_addresses);

            adapter_addresses = (IP_ADAPTER_ADDRESSES *) malloc(size);
            continue;
        }

        if (adapter_addresses)
        {
            free(adapter_addresses);
            adapter_addresses = NULL;
        }

        _logger.warning("Failed to get scope id: get adapters addresses failed (error=%d)", ret);
        return 0;
    }

    if ((ret == NO_ERROR) && (adapter_addresses))
    {
        PIP_ADAPTER_ADDRESSES it = adapter_addresses;
        while ((it) && (!found))
        {
            PIP_ADAPTER_UNICAST_ADDRESS unicast = it->FirstUnicastAddress;
            while ((unicast) && (!found))
            {
                if (unicast->Address.lpSockaddr->sa_family == AF_INET6)
                {
                    sockaddr_in6 *sin = (sockaddr_in6 *) unicast->Address.lpSockaddr;
                    char buf[50] = {0};

                    if (!inet_ntop(sin->sin6_family, &sin->sin6_addr, buf, sizeof(buf)))
                    {
                        _logger.warning("Failed to get scope id: IPv6 inet_ntop failed (error=%d)", GET_LAST_ERROR);
                        return 0;
                    }

                    if (address == buf)
                    {
                        scope_id = sin->sin6_scope_id;
                        found = true;
                    }
                }

                unicast = unicast->Next;
            }

            it = it->Next;
        }
    }

    if (adapter_addresses)
        free(adapter_addresses);
#else
    ifaddrs *interfaces;
    if (getifaddrs(&interfaces))
    {
        _logger.warning("Failed to get scope id: getifaddrs failed (error=%d)", GET_LAST_ERROR);
        return 0;
    }

    ifaddrs *it = interfaces;
    while ((it) && (!found))
    {
        if (!it->ifa_addr)
        {
            it = it->ifa_next;
            continue;
        }

        if (it->ifa_addr->sa_family == AF_INET6)
        {
            sockaddr_in6 *sin = (sockaddr_in6 *) it->ifa_addr;
            char buf[50] = {0};

            if (!inet_ntop(sin->sin6_family, &sin->sin6_addr, buf, sizeof(buf)))
            {
                _logger.warning("Failed to get scope id: IPv6 inet_ntop failed (error=%d)", GET_LAST_ERROR);
                return 0;
            }

            if (address == buf)
            {
                scope_id = sin->sin6_scope_id;
                found = true;
            }
        }

        it = it->ifa_next;
    }

    freeifaddrs(interfaces);
#endif

    if (!found)
    {
        _logger.warning("Failed to get scope id: IP not found (address=%s)", address.c_str());
        return 0;
    }

    return scope_id;
}

//-------------------------------------------

bool Socket::get_network_addresses(std::list<Network_Address> &addresses)
{
#ifdef WIN32
    Startup();

    PIP_ADAPTER_ADDRESSES adapter_addresses = NULL;
    ULONG size = 0;
    DWORD ret;

    for (unsigned short i = 0; i < 5; i++)
    {
        ret = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, adapter_addresses, &size);

        if ((ret == NO_ERROR) || (ret == ERROR_NO_DATA))
            break;

        if (ret == ERROR_BUFFER_OVERFLOW)
        {
            if (adapter_addresses)
                free(adapter_addresses);

            adapter_addresses = (IP_ADAPTER_ADDRESSES *) malloc(size);
            continue;
        }

        if (adapter_addresses)
        {
            free(adapter_addresses);
            adapter_addresses = NULL;
        }

        _logger.warning("Failed to get network addresses: get adapters addresses failed (error=%d)", ret);
        return false;
    }

    if ((ret == NO_ERROR) && (adapter_addresses))
    {
        PIP_ADAPTER_ADDRESSES it = adapter_addresses;
        while (it)
        {
            PIP_ADAPTER_UNICAST_ADDRESS unicast = it->FirstUnicastAddress;
            while (unicast)
            {
                if (unicast->Address.lpSockaddr->sa_family == AF_INET)
                {
                    sockaddr_in *sin = (sockaddr_in *) unicast->Address.lpSockaddr;
                    char buf[50] = {0};

                    if (!inet_ntop(sin->sin_family, &sin->sin_addr, buf, sizeof(buf)))
                    {
                        _logger.warning("Failed to get network addresses: IPv4 inet_ntop failed (error=%d)", GET_LAST_ERROR);
                        return false;
                    }

                    Network_Address netaddr;
                    netaddr._family = ADDRESS_FAMILY_IPv4;
                    netaddr._address = buf;
                    netaddr._scope_id = 0;
                    addresses.push_back(netaddr);

                }else if (unicast->Address.lpSockaddr->sa_family == AF_INET6)
                {
                    sockaddr_in6 *sin = (sockaddr_in6 *) unicast->Address.lpSockaddr;
                    char buf[50] = {0};

                    if (!inet_ntop(sin->sin6_family, &sin->sin6_addr, buf, sizeof(buf)))
                    {
                        _logger.warning("Failed to get network addresses: IPv6 inet_ntop failed (error=%d)", GET_LAST_ERROR);
                        return false;
                    }

                    Network_Address netaddr;
                    netaddr._family = ADDRESS_FAMILY_IPv6;
                    netaddr._address = buf;
                    netaddr._scope_id = sin->sin6_scope_id;
                    addresses.push_back(netaddr);
                }

                unicast = unicast->Next;
            }

            it = it->Next;
        }
    }

    if (adapter_addresses)
        free(adapter_addresses);
#else
    ifaddrs *interfaces;
    if (getifaddrs(&interfaces))
    {
        _logger.warning("Failed to get network addresses: getifaddrs failed (error=%d)", GET_LAST_ERROR);
        return false;
    }

    ifaddrs *it = interfaces;
    while (it)
    {
        if (!it->ifa_addr)
        {
            it = it->ifa_next;
            continue;
        }

        if (it->ifa_addr->sa_family == AF_INET)
        {
            sockaddr_in *sin = (sockaddr_in *) it->ifa_addr;
            char buf[50] = {0};

            if (!inet_ntop(sin->sin_family, &sin->sin_addr, buf, sizeof(buf)))
            {
                _logger.warning("Failed to get network addresses: IPv4 inet_ntop failed (error=%d)", GET_LAST_ERROR);
                return false;
            }

            Network_Address netaddr;
            netaddr._family = ADDRESS_FAMILY_IPv4;
            netaddr._address = buf;
            netaddr._scope_id = 0;
            addresses.push_back(netaddr);

        }else if (it->ifa_addr->sa_family == AF_INET6)
        {
            sockaddr_in6 *sin = (sockaddr_in6 *) it->ifa_addr;
            char buf[50] = {0};

            if (!inet_ntop(sin->sin6_family, &sin->sin6_addr, buf, sizeof(buf)))
            {
                _logger.warning("Failed to get network addresses: IPv6 inet_ntop failed (error=%d)", GET_LAST_ERROR);
                return false;
            }

            Network_Address netaddr;
            netaddr._family = ADDRESS_FAMILY_IPv6;
            netaddr._address = buf;
            netaddr._scope_id = sin->sin6_scope_id;
            addresses.push_back(netaddr);
        }

        it = it->ifa_next;
    }

    freeifaddrs(interfaces);
#endif

    if (addresses.empty())
    {
        _logger.warning("Failed to get network addresses: no address found");
        return false;
    }

    std::string str;
    std::list<Network_Address>::iterator it2 = addresses.begin();
    while (it2 != addresses.end())
    {
        Network_Address &netaddr = *it2++;

        if (!str.empty())
            str += ", ";

        str += netaddr._address;

        if (netaddr._family == ADDRESS_FAMILY_IPv6)
        {
            str += '%';
            str += std::to_string(netaddr._scope_id);
        }
    }

    _logger.trace("Network addresses: %s", str.c_str());
    return true;
}

//-------------------------------------------

#ifdef WIN32
bool Socket::Startup()
{
    static bool initialized = false;

    if (!initialized)
    {
        WORD wVersionRequested = MAKEWORD(2, 2);
        WSADATA wsaData;

        int ret = WSAStartup(wVersionRequested, &wsaData);
        if (ret != 0)
        {
            _logger.error("Failed to startup: WSAStartup failed (error=%d)", ret);
            return false;
        }

        initialized = true;
    }

    return true;
}
#endif

//-------------------------------------------
//-------------------------------------------

bool Socket_UDP::create(Address_Family family)
{
    int af = address_family_to_af(family);
    return Socket::create(af, SOCK_DGRAM, IPPROTO_UDP);
}

//-------------------------------------------
//-------------------------------------------

bool Socket_TCP_Client::create(Address_Family family)
{
    int af = address_family_to_af(family);
    return Socket::create(af, SOCK_STREAM, IPPROTO_TCP);
}

//-------------------------------------------
//-------------------------------------------

bool Socket_TCP_Server::create(Address_Family family)
{
    int af = address_family_to_af(family);
    return Socket::create(af, SOCK_STREAM, IPPROTO_TCP);
}

//-------------------------------------------
//-------------------------------------------

Socket_Control &Socket_Control::instance()
{
    if (_instance == NULL)
        _instance = new Socket_Control();

    return *_instance;
}

//-------------------------------------------

void Socket_Control::destroy()
{
    delete _instance;
    _instance = NULL;
}

//-------------------------------------------

bool Socket_Control::add_socket(Socket &socket)
{
    Logger &logger = Socket::get_logger();

    std::lock_guard<std::recursive_mutex> lock(_socket_list_mutex);

    std::list<Socket *>::iterator it = _socket_list.begin();
    while (it != _socket_list.end())
    {
        Socket *sock = *it++;
        if (sock == &socket)
        {
            logger.warning("Failed to add socket to control: already added (socket=%d)", socket.get_socket());
            return false;
        }
    }

    _socket_list.push_back(&socket);
    logger.trace("Socket added to control (socket=%d)", socket.get_socket());
    return true;
}

//-------------------------------------------

bool Socket_Control::remove_socket(Socket &socket)
{
    Logger &logger = Socket::get_logger();

    std::lock_guard<std::recursive_mutex> lock(_socket_list_mutex);

    std::list<Socket *>::iterator it = _socket_list.begin();
    while (it != _socket_list.end())
    {
        Socket *sock = *it++;
        if (sock == &socket)
        {
            _socket_list.remove(&socket);
            logger.trace("Socket removed from control (socket=%d)", socket.get_socket());
            return true;
        }
    }

    logger.warning("Failed to remove socket from control: not added (socket=%d)", socket.get_socket());
    return false;
}

//-------------------------------------------

void Socket_Control::run()
{
    Logger &logger = Socket::get_logger();

    timeval tv;
    tv.tv_sec = SELECT_TIMEOUT / 1000;
    tv.tv_usec = (SELECT_TIMEOUT - (1000 * tv.tv_sec)) * 1000;

    fd_set read_set, write_set, except_set;
    FD_ZERO(&read_set);
    FD_ZERO(&write_set);
    FD_ZERO(&except_set);

    int max_fd = -1;

    std::lock_guard<std::recursive_mutex> lock(_socket_list_mutex);

    std::list<Socket *>::iterator it = _socket_list.begin();
    while (it != _socket_list.end())
    {
        Socket *socket = *it++;
        Socket::State state = socket->get_state();
        socket_t &handle = socket->get_socket();

        if ((state == Socket::STATE_OPEN) || (state == Socket::STATE_LISTENING) ||
            (state == Socket::STATE_CONNECTED) || (state == Socket::STATE_CLOSING))
        {
            FD_SET(handle, &read_set);
            max_fd = (max_fd > (int) handle) ? max_fd : (int) handle;

        }else if (state == Socket::STATE_CONNECTING)
        {
            FD_SET(handle, &write_set);
            FD_SET(handle, &except_set);
            max_fd = (max_fd > (int) handle) ? max_fd : (int) handle;
        }
    }

    if (max_fd == -1)
        return;

    int select_nb = ::select(max_fd + 1, &read_set, &write_set, &except_set, &tv);
    if (select_nb < 0)
    {
        logger.warning("Failed in control thread: select failed (error=%d)", GET_LAST_ERROR);
        return;
    }

    if (select_nb == 0)
        return;

    it = _socket_list.begin();
    while (it != _socket_list.end())
    {
        Socket *socket = *it++;
        Socket::State state = socket->get_state();
        socket_t &handle = socket->get_socket();

        if ((state == Socket::STATE_OPEN) || (state == Socket::STATE_CONNECTED) || (state == Socket::STATE_CLOSING))
        {
            if (FD_ISSET(handle, &read_set))
            {
                std::string address;
                unsigned short port = 0;
                int size = -1;

                if (socket->get_socket_type() == Socket::SOCKET_UDP)
                    size = socket->receive(_receive_buffer, sizeof(_receive_buffer), address, port);
                else
                    size = socket->receive(_receive_buffer, sizeof(_receive_buffer));

                if (size < 0)
                {
                    logger.warning("Failed in control thread: receive failed (socket=%d)", socket->get_socket());
                    continue;
                }

                _receive_buffer[size] = 0;

                logger.trace("Message received (socket=%d, address=%s, port=%d, size=%d)",
                                socket->get_socket(), address.c_str(), port, size);

                socket->call_receive_callback(_receive_buffer, size, address, port);
            }
        }else if (state == Socket::STATE_LISTENING)
        {
            if (FD_ISSET(handle, &read_set))
            {
                std::string address;
                unsigned short port;

                socket_t accept_socket;
                if (!socket->accept(accept_socket, address, port))
                {
                    logger.warning("Failed in control thread: accept failed");
                    continue;
                }

                logger.trace("Socket accepted in control thread (accepted=%d, address=%s, port=%d)",
                                accept_socket, address.c_str(), port);

                Socket_TCP_Client *accepted = new Socket_TCP_Client();
                accepted->set_socket(accept_socket);
                accepted->set_state(Socket::STATE_CONNECTED);

                if (!socket->call_accept_callback(accepted, address, port))
                    delete accepted;
            }
        }else if (state == Socket::STATE_CONNECTING)
        {
            if ((FD_ISSET(handle, &write_set)) || (FD_ISSET(handle, &except_set)))
            {
                int value = 0;
                if (!socket->get_so_error(value))
                {
                    logger.warning("Failed in control thread: get socket option error failed");
                    continue;
                }

                if (value == 0)
                {
                    socket->set_state(Socket::STATE_CONNECTED);
                    logger.trace("Socket connected in control thread (socket=%d)", handle);
                    socket->call_connect_callback(true);
                }else
                {
                    logger.warning("Failed in control thread: connect failed (socket=%d, error=%d)", handle, value);
                    socket->call_connect_callback(false);
                }
            }
        }
    }
}

//-------------------------------------------
