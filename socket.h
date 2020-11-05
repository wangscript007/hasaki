#ifndef __HASASKI_SOCKET_H__
#define __HASASKI_SOCKET_H__

#include "noncopyable"
#include "hasaki_core.h"

#ifdef OS_WINDOWS
#include <WinSock2.h>
#define SOCKET_GET_LAST_ERROR WSAGetLastError()
typedef SOCKET fd_t;
#else
#define SOCKET_GET_LAST_ERROR errno
typedef int fd_t;
#endif

namespace hasaki{
namespace net {

/// <summary>
/// Socket is a wrapper for fd or SOCKET who manage's its lifeclycle.
/// </summary>
class Socket : public hasaki::noncopyable {
public:
    /// <summary>
    /// Construct a Socket with a valid sockfd.
    /// </summary>
    /// <param name="sockfd"></param>
    /// <returns></returns>
    explicit Socket(int sockfd) : sockfd__(sockfd) {}

    /// <summary>
    /// When the socket goes to die, the sockfd internal will be closed.
    /// </summary>
    /// <returns></returns>
    ~Socket();

    /// <summary>
    /// Returns the internal fd or SOCKET.
    /// </summary>
    /// <returns></returns>
    int fd() const { return sockfd__; }

    /// <summary>
    /// Enable or disable the nonblocking option.
    /// </summary>
    void SetNonblocking();

    /// <summary>
    /// Disable or enable nagle.
    /// </summary>
    /// <param name="on"></param>
    void SetTcpNoDelay(bool on);

    /// <summary>
    /// SetReuseAddr has difference means in difference operation system.
    /// In unix-like os such as linux or macos, setReuseAddr was a posix standard.
    /// </summary>
    /// <param name="on"></param>
    void SetReuseAddr(bool on);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="on"></param>
    void SetReusePort(bool on);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="on"></param>
    void SetKeepAlive(bool on);

private:
    const fd_t sockfd__;
};

} // end of namespace net
} // end of namespace hasaki

#endif
