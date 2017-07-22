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
#include "common_functions.h"

Logger Socket::_logger(Log_Manager::LOG_SOCKET);

//-------------------------------------------

Socket::Socket() : _state(STATE_IDLE), _socket(INVALID_SOCKET), _connect_callback(NULL), _connect_data(NULL),
    _receive_callback(NULL), _receive_data(NULL)
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
    _connect_data = data;
}

//-------------------------------------------

bool Socket::call_connect_callback(bool success)
{
    try
    {
        if (_connect_callback)
        {
            _logger.trace("Calling connect callback (state=%d, socket=%d, success=%d)", _state, _socket, success);
            return _connect_callback(_connect_data, success);
        }

        return true;
    }catch (std::exception &e)
    {
        _logger.warning("Exception when calling connect callback (state=%d, socket=%d, success=%d, msg=%s)",
                        _state, _socket, success, e.what());
        return false;
    }catch (...)
    {
        _logger.warning("Exception when calling connect callback (state=%d, socket=%d, success=%d)", _state, _socket, success);
        return false;
    }
}

//-------------------------------------------

void Socket::set_receive_callback(receive_callback *callback, void *data)
{
    _receive_callback = callback;
    _receive_data = data;
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
            return _receive_callback(_receive_data, buffer, size, address, port);
        }

        return true;
    }catch (std::exception &e)
    {
        _logger.warning("Exception when calling receive callback (state=%d, socket=%d, address=%s, port=%d, size=%d, msg=%s)",
                        _state, _socket, address.c_str(), port, size, e.what());
        return false;
    }catch (...)
    {
        _logger.warning("Exception when calling receive callback (state=%d, socket=%d, address=%s, port=%d, size=%d)",
                        _state, _socket, address.c_str(), port, size);
        return false;
    }
}

//-------------------------------------------

bool Socket::create(int af, int type, int protocol)
{
    if (_state != STATE_IDLE)
    {
        _logger.warning("Invalid state to create socket (state=%d)", _state);
        return false;
    }

    _socket = socket(af, type, protocol);
    if (_socket == INVALID_SOCKET)
    {
        _logger.warning("Failed to create socket (af=%d, type=%d, protocol=%d, error=%d)", af, type, protocol, GET_LAST_ERROR);
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
        _logger.warning("Invalid state to close socket (state=%d)", _state);
        return false;
    }

#ifdef WIN32
    if (::closesocket(_socket))
#else
    if (::close(_socket))
#endif
    {
        _logger.warning("Failed to close socket (socket=%d, error=%d)", _socket, GET_LAST_ERROR);
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
        _logger.warning("Invalid state to set socket option send buffer size (state=%d)", _state);
        return false;
    }

    if (setsockopt(_socket, SOL_SOCKET, SO_SNDBUF, (const char *) &size, sizeof(size)))
    {
        _logger.warning("Failed to set socket option send buffer size (socket=%d, size=%d, error=%d)", _socket, size, GET_LAST_ERROR);
        return false;
    }

    _logger.trace("Set socket option send buffer size (socket=%d, size=%d)", _socket, size);
    return true;
}

//-------------------------------------------

bool Socket::set_so_rcv_buf(int size)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Invalid state to set socket option receive buffer size (state=%d)", _state);
        return false;
    }

    if (setsockopt(_socket, SOL_SOCKET, SO_RCVBUF, (const char * ) &size, sizeof(size)))
    {
        _logger.warning("Failed to set socket option receive buffer size (socket=%d, size=%d, error=%d)", _socket, size, GET_LAST_ERROR);
        return false;
    }

    _logger.trace("Set socket option receive buffer size (socket=%d, size=%d)", _socket, size);
    return true;
}

//-------------------------------------------

bool Socket::set_so_reuse_addr(int value)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Invalid state to set socket option reuse addr (state=%d)", _state);
        return false;
    }

    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (const char *) &value, sizeof(value)))
    {
        _logger.warning("Failed to set socket option reuse addr (socket=%d, value=%d, error=%d)", _socket, value, GET_LAST_ERROR);
        return false;
    }

    _logger.trace("Set socket option reuse addr (socket=%d, value=%d)", _socket, value);
    return true;
}

//-------------------------------------------

bool Socket::set_non_blocking(bool non_blocking)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Invalid state to set non-blocking flag (state=%d)", _state);
        return false;
    }

#ifdef WIN32
    unsigned long arg = non_blocking ? 1 : 0;
    if (ioctlsocket(_socket, FIONBIO, &arg))
    {
        _logger.warning("Failed to set non-blocking flag (socket=%d, non_blocking=%d, error=%d)", _socket, non_blocking, GET_LAST_ERROR);
        return false;
    }
#else
    int flags = fcntl(_socket, F_GETFL, 0);
    if (flags < 0)
    {
        _logger.warning("Failed to get status flags (socket=%d, non_blocking=%d, error=%d)", _socket, non_blocking, GET_LAST_ERROR);
        return false;
    }

    if (non_blocking)
        flags |= O_NONBLOCK;
    else
        flags &= ~O_NONBLOCK;

    if (fcntl(_socket, F_SETFL, flags))
    {
        _logger.warning("Failed to set status flags (socket=%d, non_blocking=%d, error=%d)", _socket, non_blocking, GET_LAST_ERROR);
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
        _logger.warning("Invalid state to get socket option error (state=%d)", _state);
        return false;
    }

    socklen_t len = sizeof(value);
    if (getsockopt(_socket, SOL_SOCKET, SO_ERROR, (char *) &value, &len))
    {
        _logger.warning("Failed to get socket option error (socket=%d, value=%d, error=%d)", _socket, value, GET_LAST_ERROR);
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
        _logger.warning("Invalid state to bind (state=%d)", _state);
        return false;
    }

    sockaddr_storage ss;
    if (!address_to_sockaddr(address, port, ss))
    {
        _logger.warning("Failed to get socket address to bind (socket=%d, address=%s, port=%d)", _socket, address.c_str(), port);
        return false;
    }

    if (::bind(_socket, (sockaddr *) &ss, sizeof(ss)))
    {
        _logger.warning("Failed to bind (socket=%d, address=%s, port=%d, error=%d)", _socket, address.c_str(), port, GET_LAST_ERROR);
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
        _logger.warning("Invalid state to listen (state=%d)", _state);
        return false;
    }

    if (::listen(_socket, backlog))
    {
        _logger.warning("Failed to listen (socket=%d, backlog=%d, error=%d)", _socket, backlog, GET_LAST_ERROR);
        return false;
    }

    _state = STATE_LISTENING;
    _logger.trace("Socket listening (socket=%d, backlog=%d)", _socket, backlog);
    return true;
}

//-------------------------------------------

bool Socket::connect(std::string address, unsigned short port)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Invalid state to connect (state=%d)", _state);
        return false;
    }

    sockaddr_storage ss;
    if (!address_to_sockaddr(address, port, ss))
    {
        _logger.warning("Failed to get socket address to connect (socket=%d, address=%s, port=%d)", _socket, address.c_str(), port);
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
                _logger.warning("Failed to connect (socket=%d, address=%s, port=%d, error=%d)",
                                _socket, address.c_str(), port, GET_LAST_ERROR);
                return false;
            }
        }
    }

    _state = STATE_CONNECTED;
    _logger.trace("Socket connected (socket=%d, address=%s, port=%d)", _socket, address.c_str(), port);
    return call_connect_callback(true);
}

//-------------------------------------------

bool Socket::send(const char *buffer, int size)
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Invalid state to send (state=%d)", _state);
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
                _logger.warning("Failed to send (socket=%d, error=%d)", _socket, GET_LAST_ERROR);
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
        _logger.warning("Invalid state to send (state=%d)", _state);
        return false;
    }

    sockaddr_storage ss;
    if (!address_to_sockaddr(address, port, ss))
    {
        _logger.warning("Failed to get socket address to send (socket=%d, address=%s, port=%d)", _socket, address.c_str(), port);
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
                _logger.warning("Failed to send (socket=%d, address=%s, port=%d, error=%d)",
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
        _logger.warning("Invalid state to receive (state=%d)", _state);
        return false;
    }

    int len = recv(_socket, buffer, size, 0);
    if (len < 0)
    {
        _logger.warning("Failed to receive (socket=%d, error=%d)", _socket, GET_LAST_ERROR);
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
        _logger.warning("Invalid state to receive (state=%d)", _state);
        return false;
    }

    sockaddr_storage ss;
    socklen_t ss_len = sizeof(ss);

    int len = recvfrom(_socket, buffer, size, 0, (sockaddr *) &ss, &ss_len);
    if (len < 0)
    {
        _logger.warning("Failed to receive (socket=%d, error=%d)", _socket, GET_LAST_ERROR);
        return -1;
    }

    if (!sockaddr_to_address(ss, address, port))
    {
        _logger.warning("Failed to get received address (socket=%d)", _socket);
        return -1;
    }

    _logger.trace("Socket message received (socket=%d, address=%s, port=%d, len=%d)", _socket, address.c_str(), port, len);
    return len;
}

//-------------------------------------------

int Socket::select_read()
{
    if ((_state == STATE_IDLE) || (_state == STATE_CLOSED))
    {
        _logger.warning("Invalid state to select read (state=%d)", _state);
        return false;
    }

    timeval tv;
    tv.tv_sec = 4;
    tv.tv_usec = 0;

    fd_set read_set;
    FD_ZERO(&read_set);
    FD_SET(_socket, &read_set);

    int ret = ::select(_socket + 1, &read_set, NULL, NULL, &tv);
    if (ret < 0)
    {
        _logger.warning("Failed to select read (socket=%d, error=%d)", _socket, GET_LAST_ERROR);
        return -1;
    }

    _logger.trace("Socket selected read (socket=%d, ret=%d)", _socket, ret);
    return ret;
}

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
    unsigned long scope = 0; //TODO

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
        sin->sin6_scope_id = scope;
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
            _logger.warning("Failed to convert IPv4 sockaddr to address (error=%d)", GET_LAST_ERROR);
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
            _logger.warning("Failed to convert IPv6 sockaddr to address (error=%d)", GET_LAST_ERROR);
            return false;
        }

        address = buf;
        return true;
    }

    return false;
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

        _logger.warning("Failed to get adapters addresses (error=%d)", ret);
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
                        _logger.warning("Failed to convert IPv4 sockaddr to address (error=%d)", GET_LAST_ERROR);
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
                        _logger.warning("Failed to convert IPv6 sockaddr to address (error=%d)", GET_LAST_ERROR);
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
        _logger.warning("Failed to get interface addresses (error=%d)", GET_LAST_ERROR);
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
                _logger.warning("Failed to convert IPv4 sockaddr to address (error=%d)", GET_LAST_ERROR);
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
                _logger.warning("Failed to convert IPv6 sockaddr to address (error=%d)", GET_LAST_ERROR);
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
        _logger.warning("Failed to get network addresses");
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
            _logger.error("Failed to startup (error=%d)", ret);
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

Socket_Control::~Socket_Control()
{
    if (!_stopped)
        stop();
}

//-------------------------------------------

Socket_Control &Socket_Control::instance()
{
    static Socket_Control control;
    return control;
}

//-------------------------------------------

bool Socket_Control::start()
{
    Logger &logger = Socket::get_logger();

    if (!_stopped)
    {
        logger.warning("Failed to start socket control: already started");
        return false;
    }

    logger.trace("Starting socket control");

    _stopped = false;
    _control_thread = std::thread(control_thread);

    logger.trace("Socket control started");
    return true;
}

//-------------------------------------------

bool Socket_Control::stop()
{
    Logger &logger = Socket::get_logger();

    if (_stopped)
    {
        logger.warning("Failed to stop socket control: already stopped");
        return false;
    }

    logger.trace("Stopping socket control");

    _stopped = true;
    _control_thread.join();

    logger.trace("Socket control stopped");
    return true;
}

//-------------------------------------------

bool Socket_Control::add_socket(Socket &socket)
{
    Logger &logger = Socket::get_logger();

    std::lock_guard<std::mutex> lock(_socket_list_mutex);

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

    std::lock_guard<std::mutex> lock(_socket_list_mutex);

    std::list<Socket *>::iterator it = _socket_list.begin();
    while (it != _socket_list.end())
    {
        Socket *sock = *it++;
        if (sock == &socket)
        {
            _socket_list.remove(&socket);
            logger.warning("Socket removed from control (socket=%d)", socket.get_socket());
            return true;
        }
    }

    logger.warning("Failed to remove socket from control: not added (socket=%d)", socket.get_socket());
    return false;
}

//-------------------------------------------

void Socket_Control::control_thread()
{
    Socket_Control &control = Socket_Control::instance();
    Logger &logger = Socket::get_logger();

    logger.trace("Control thread running");

    timeval tv;
    tv.tv_sec = SELECT_TIMEOUT / 1000;
    tv.tv_usec = (SELECT_TIMEOUT - (1000 * tv.tv_sec)) * 1000;

    while (!control._stopped)
    {
        fd_set read_set, write_set, except_set;
        FD_ZERO(&read_set);
        FD_ZERO(&write_set);
        FD_ZERO(&except_set);

        int max_fd = -1;

        Common_Functions::delay(10);

        std::lock_guard<std::mutex> lock(control._socket_list_mutex);

        std::list<Socket *>::iterator it = control._socket_list.begin();
        while (it != control._socket_list.end())
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

        if (control._stopped)
            break;

        if (max_fd == -1)
        {
            Common_Functions::delay(SELECT_TIMEOUT);
            continue;
        }

        int select_nb = ::select(max_fd + 1, &read_set, &write_set, &except_set, &tv);
        if (select_nb < 0)
        {
            logger.warning("Failed to select in control thread (error=%d)", GET_LAST_ERROR);
            continue;
        }

        if (select_nb == 0)
            continue;

        if (control._stopped)
            break;

        it = control._socket_list.begin();
        while (it != control._socket_list.end())
        {
            Socket *socket = *it++;
            Socket::State state = socket->get_state();
            socket_t &handle = socket->get_socket();

            if ((state == Socket::STATE_OPEN) || (state == Socket::STATE_CONNECTED) || (state == Socket::STATE_CLOSING))
            {
                if (FD_ISSET(handle, &read_set))
                {
                    std::string address;
                    unsigned short port;

                    int size = socket->receive(control._receive_buffer, sizeof(_receive_buffer), address, port);
                    if (size < 0)
                    {
                        logger.warning("Failed to receive message");
                        continue;
                    }

                    control._receive_buffer[size] = 0;

                    logger.trace("Message received (address=%s, port=%d, size=%d)", address.c_str(), port, size);
                    socket->call_receive_callback(control._receive_buffer, size, address, port);
                }
            }else if (state == Socket::STATE_LISTENING)
            {
                if (FD_ISSET(handle, &read_set))
                {
                    //TODO
                }
            }else if (state == Socket::STATE_CONNECTING)
            {
                if ((FD_ISSET(handle, &write_set)) || (FD_ISSET(handle, &except_set)))
                {
                    int value = 0;
                    if (!socket->get_so_error(value))
                    {
                        logger.warning("Failed to get socket option error");
                        continue;
                    }

                    if (value == 0)
                    {
                        socket->set_state(Socket::STATE_CONNECTED);
                        logger.trace("Socket connected in control thread (socket=%d)", handle);
                        socket->call_connect_callback(true);
                    }else
                    {
                        logger.warning("Failed to connect in control thread (socket=%d, error=%d)", handle, value);
                        socket->call_connect_callback(false);
                    }
                }
            }
        }
    }

    logger.trace("Control thread finished");
}

//-------------------------------------------
