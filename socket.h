#ifndef __HASASKI_SOCKET_H__
#define __HASASKI_SOCKET_H__

#include "noncopyable"
#include "hasaki_core.h"
#if defined(OS_WINDOWS) && OS_WINDOWS
#include <WinSock2.h>
#include <winerror.h>
#include <WS2tcpip.h>
typedef SOCKET fd_t;
#else
typedef int fd_t;
#endif

namespace hasaki{
namespace net {

/// <summary>
/// Socket is a wrapper for fd. with useful methods.
/// </summary>
class Socket : public hasaki::noncopyable {
public:
    explicit Socket(int sockfd) : sockfd__(sockfd) {}

    ~Socket();

    int fd() const { return sockfd__; }

    void SetNonblocking();

    void SetTcpNoDelay(bool on);

    void SetReuseAddr(bool on);

    void SetReusePort(bool on);

    void SetKeepAlive(bool on);

private:
    const fd_t sockfd__;
};

} // end of namespace net
} // end of namespace hasaki

#endif
