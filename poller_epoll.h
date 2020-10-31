#ifndef __HASAKI_POLLER_EPOLL_H__
#define __HASAKI_POLLER_EPOLL_H__

#include <fcntl.h>
#include <sys/epoll.h>
#include <unistd.h>

#include <memory>
#include <vector>

#include "poller.h"

namespace hasaki {
namespace net {

// An epoll-based poller implementation of hasaki::net::Poller.
// Since Linux kernel 2.6

class EpollPoller : public hasaki::net::Poller {
public:
    // Create a EpollPollers with a owner eventloop.
    EpollPoller(std::shared_ptr<hasaki::net::EventLoop> &eventLoop);

    // Destory the EpollPoller.
    ~EpollPoller() override {
        if (epfd__ >= 0)
            ::close(epfd__);
    }

    void UpdateChannel(hasaki::net::SocketChannel *channel) override;

    void RemoveChannel(hasaki::net::SocketChannel *channel) override;

    hasaki::base::Timestamp Poll(
        std::vector<hasaki::net::SocketChannel *> *activeChannels,
        int timeoutMs) override;

private:
    void FillActiveChannels(int numActives,
                            std::vector<hasaki::net::SocketChannel *> *activeChannels);

    // ADD/DEL/MOD the interest events in fd.
    void DoEpollCtl(int cntl, hasaki::net::SocketChannel *channel);

    int epfd__;
    std::vector<struct epoll_event> epollEvents__;
    static const int INIT_EVENT_LIST_SIZE = 8;
};
}  // namespace net
}  // namespace hasaki

#endif