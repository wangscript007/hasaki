#include "socket.h"

#ifdef OS_WINDOWS
#include <winerror.h>
#include <WS2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#endif

namespace hasaki {
namespace net {

Socket::~Socket() {
#ifdef OS_WINDOWS
    ::closesocket(sockfd__);
#else
    ::close(sockfd__);
#endif
}

void Socket::SetNonblocking() {
#ifdef OS_WINDOWS
    { 
        unsigned long nonblocking = 1;
        ioctlsocket(sockfd__, FIONBIO, &nonblocking);
    }
#else 
    {
    
    }
#endif
}

 void Socket::SetTcpNoDelay(bool on) {
#ifdef OS_WINDOWS
     BOOL tcpNoDelay = TRUE;
     ::setsockopt(sockfd__, SOL_SOCKET, TCP_NODELAY, (const char *)&tcpNoDelay,
                sizeof(BOOL));
#else

#endif
 }

void Socket::SetReuseAddr(bool on) {
}

void Socket::SetReusePort(bool on) {
}

void Socket::SetKeepAlive(bool on) {
}

}