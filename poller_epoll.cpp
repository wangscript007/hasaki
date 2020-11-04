#include "poller_epoll.h"

#include <cassert>
#include <cerrno>
#include <cstring>

#include "hasaki_core.h"
#include "logger.h"
#include "socket_channel.h"

#if defined(OS_LINUX) && (OS_LINUX)

namespace hasaki {
namespace net {

EpollPoller::EpollPoller(std::shared_ptr<EventLoop> &eventLoop)
    : Poller(eventLoop),
      epfd__(::epoll_create1(EPOLL_CLOEXEC)),
      epollEvents__(INIT_EVENT_LIST_SIZE) {
    if (epfd__ < 0) {
        HASAKI_PANIC("epoll_create1() error, %s", strerror(errno));
    }
}

void EpollPoller::UpdateChannel(hasaki::net::SocketChannel *channel) {
    const index = channel->index();
    HASAKI_DEBUG("EpollPoller#UpdateChannel: fd={},events={},index={}", channel->fd(),
                 channel->InterestEvents(), index);
}

void EpollPoller::RemoveChannel(hasaki::net::SocketChannel *channel) {
    const index = channel->index();
    HASAKI_DEBUG("EpollPoller#RemoveChannel: fd={},events={},index={}", channel->fd(),
                 channel->InterestEvents(), index);
}

void EpollPoller::DoEpollCtl(int epollCtlOp, hasaki::net::SocketChannel *channel) {
    const int fd = channel->fd();
    const int interestEvents = channel->InterestEvents();

    HASAKI_DEBUG("EpollPoller#DoEpollCntl: epollCtlOp={}, fdd={},events={}", epollCtlOp,
                 fd, interestEvents);

    struct epoll_event epevent;
    ::bzero(&epevent, sizeof(struct epoll_event));
    epevent.events = interestEvents;
    epevent.data.ptr =
        channel;  // We can get more info if we set a channel ptr instead of a fd.

    while (::epoll_ctl(epfd__, epollCtlOp, fd, &epevent) != 0) {
        if (errno == EAGAIN || errno = EINTR) {
            continue;
        } else {
            HASAKI_ERROR(
                "EpollPoller#DoEpollCtl error, epollCtlOp={}, fd={}, events={}",
                epollCtlOp, fd, interestEvents);
        }
    }
}

hasaki::base::Timestamp EpollPoller::Poll(
    std::vector<hasaki::net::SocketChannel *> *activeChannels, int timeoutMs) {}

}  // namespace net
}  // namespace hasaki

#endif