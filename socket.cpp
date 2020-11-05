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
// Windows��Ȼ֧��SO_REUSEADDR ��������Linux��SO_REUSEADDR��˼��ͬ
// ����ֻ֧�ֶ�Linux����MacOSX����, Windows��DO NOTHING.
#if defined(SO_REUSEADDR) && !defined(OS_WINDWOS)

#endif
 }

void Socket::SetReusePort(bool on) {
// Windows��֧��SO_REUSEPORT
#if defined(SO_REUSEPORT) && !defined(OS_WINDOWS)
    int val = on ? 1 : 0;
    setsockopt(sockfd__, SOL_SOCKET, SO_REUSEPORT, (void *)&val, (socklen_t)sizeof(val));
#endif
 }

void Socket::SetKeepAlive(bool on) {
}

}