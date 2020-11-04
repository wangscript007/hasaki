#include "socket.h"

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

 }

void Socket::SetReuseAddr(bool on) {
}

void Socket::SetReusePort(bool on) {
}

void Socket::SetKeepAlive(bool on) {
}

}