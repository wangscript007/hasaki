#ifndef __HASAKI_INET_ADDRESS_H__
#define __HASAKI_INET_ADDRESS_H__

#include <cstring>
#include <netinet/in.h>

namespace hasaki {
namespace net {

// Generic InetAddress.
class InetAddress {};

// InetAdress for IPV4
class Inet4Address : public InetAddress {
public:
    Inet4Address() {
        sa_family_t ipv4Val = AF_INET;
        memcpy(&sockAddr__.sin_family, &ipv4Val, sizeof(sa_family_t));
    }

private:
    struct sockaddr_in sockAddr__;
};

// InetAddress for IPV6
class Inet6Address {

public:
    Inet6Address() {
        sa_family_t ipv6Val = AF_INET6;
        memcpy(&sockAddr__.sin_family, &ipv6Val, sizeof(sa_family_t));
    }

private:
    struct sockaddr_in sockAddr__;
};

} // namespace net
} // namespace hasaki

#endif