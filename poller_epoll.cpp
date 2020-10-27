#include "poller_epoll.h"

// #include <sys/epoll.h>

// epoll.h supported in Linux only!!!!!!

namespace hasaki {
namespace net {

void EpollPoller::UpdateChannel(hasaki::net::SocketChannel *channel) {
}

void EpollPoller::RemoveChannel(hasaki::net::SocketChannel *channel) {
}

hasaki::base::Timestamp EpollPoller::Poll(
    std::vector<hasaki::net::SocketChannel *> *activeChannels, int timeoutMs) {
}

} // namespace net

} // namespace hasaki
