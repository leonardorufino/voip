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

Socket::Socket() : _socket(INVALID_SOCKET)
{
#ifdef WIN32
    Startup();
#endif
}

//-------------------------------------------

Socket::~Socket()
{
    close();
}

//-------------------------------------------

bool Socket::create(int af, int type, int protocol)
{
    _socket = socket(af, type, protocol);
    if (_socket == INVALID_SOCKET)
    {
        _logger.warning("Failed to create socket (af=%d, type=%d, protocol=%d, error=%d)", af, type, protocol, GET_LAST_ERROR);
        return false;
    }

    _logger.trace("Socket created (socket=%d, af=%d, type=%d, protocol=%d)", _socket, af, type, protocol);
    return true;
}

//-------------------------------------------

bool Socket::close()
{
    if (_socket != INVALID_SOCKET)
    {
#ifdef WIN32
        if (::closesocket(_socket))
#else
        if (::close(_socket))
#endif
        {
            _logger.warning("Failed to close socket (socket=%d, error=%d)", _socket, GET_LAST_ERROR);
            _socket = INVALID_SOCKET;
            return false;
        }

        _logger.trace("Socket closed (socket=%d)", _socket);
        _socket = INVALID_SOCKET;
    }

    return true;
}

//-------------------------------------------

bool Socket::set_so_snd_buf(int size)
{
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
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (const char *) &value, sizeof(value)))
    {
        _logger.warning("Failed to set socket option reuse addr (socket=%d, value=%d, error=%d)", _socket, value, GET_LAST_ERROR);
        return false;
    }

    _logger.trace("Set socket option reuse addr (socket=%d, value=%d)", _socket, value);
    return true;
}

//-------------------------------------------

bool Socket::bind(std::string address, unsigned short port)
{
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

bool Socket::connect(std::string address, unsigned short port)
{
    sockaddr_storage ss;
    if (!address_to_sockaddr(address, port, ss))
    {
        _logger.warning("Failed to get socket address to connect (socket=%d, address=%s, port=%d)", _socket, address.c_str(), port);
        return false;
    }

    if (::connect(_socket, (sockaddr *) &ss, sizeof(ss)))
    {
        _logger.warning("Failed to connect (socket=%d, address=%s, port=%d, error=%d)", _socket, address.c_str(), port, GET_LAST_ERROR);
        return false;
    }

    _logger.trace("Socket connected (socket=%d, address=%s, port=%d)", _socket, address.c_str(), port);
    return true;
}

//-------------------------------------------

bool Socket::send(const char *buffer, int size)
{
    if (::send(_socket, buffer, size, 0) != size)
    {
        _logger.warning("Failed to send (socket=%d, error=%d)", _socket, GET_LAST_ERROR);
        return false;
    }

    _logger.trace("Socket message sent (socket=%d, size=%d)", _socket, size);
    return true;
}

//-------------------------------------------

bool Socket::send(const char *buffer, int size, std::string address, unsigned short port)
{
    sockaddr_storage ss;
    if (!address_to_sockaddr(address, port, ss))
    {
        _logger.warning("Failed to get socket address to send (socket=%d, address=%s, port=%d)", _socket, address.c_str(), port);
        return false;
    }

    if (::sendto(_socket, buffer, size, 0, (sockaddr *) &ss, sizeof(ss)) != size)
    {
        _logger.warning("Failed to send (socket=%d, address=%s, port=%d, error=%d)", _socket, address.c_str(), port, GET_LAST_ERROR);
        return false;
    }

    _logger.trace("Socket message sent (socket=%d, address=%s, port=%d, size=%d)", _socket, address.c_str(), port, size);
    return true;
}

//-------------------------------------------

int Socket::receive(char *buffer, int size)
{
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
