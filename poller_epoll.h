#ifndef __HASAKI_POLLER_EPOLL_H__
#define __HASAKI_POLLER_EPOLL_H__

#include "poller.h"
#include <fcntl.h>
#include <memory>
#include <unistd.h>

namespace hasaki {
namespace net {

// An epoll-based poller implementation of hasaki::net::Poller.
// Since Linux kernel 2.6

class EpollPoller : public hasaki::net::Poller {
public:
    // Create a EpollPollers with a owner eventloop.
    EpollPoller(std::shared_ptr<hasaki::net::EventLoop> EventLoop);

    // Destory the EpollPoller.
    ~EpollPoller() {
        if (epfd__ >= 0)
            ::close(epfd__);
    }

    void UpdateChannel(hasaki::net::SocketChannel *channel) override;

    void RemoveChannel(hasaki::net::SocketChannel *channel) override;

    hasaki::base::Timestamp Poll(
        std::vector<hasaki::net::SocketChannel *> *activeChannels,
        int timeoutMs) override;

private:
    int epfd__;
};
} // namespace net
} // namespace hasaki

#endif