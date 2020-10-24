#ifndef __HASAKI_INET_ADDRESS_H__
#define __HASAKI_INET_ADDRESS_H__

#include <netinet/in.h>

#include <cstring>

namespace hasaki {
namespace net {

// Generic InetAddress.
class InetAddress {
public:
    InetAddress() {}

    virtual ~InetAddress() {}

    virtual sa_family_t GetAddressFamily() const = 0;
};

// InetAdress for IPV4
class Inet4Address : public InetAddress {
public:
    Inet4Address() { sockAddrIpv4__.sin_family = AF_INET; }

    sa_family_t GetAddressFamily() const override { return AF_INET; };

private:
    struct sockaddr_in sockAddrIpv4__;
};

// InetAddress for IPV6
class Inet6Address : public InetAddress {
public:
    Inet6Address() { sockAddrIpv6__.sin6_family = AF_INET6; }

    sa_family_t GetAddressFamily() const override { return AF_INET6; };

private:
    struct sockaddr_in6 sockAddrIpv6__;
};

} // namespace net
} // namespace hasaki

#endif