#ifndef __HASAKI_POLLER_H__
#define __HASAKI_POLLER_H__

#include <map>
#include <memory>
#include <vector>

#include "noncopyable.h"
#include "timestamp.h"

namespace hasaki {
namespace net {

class EventLoop;
class SocketChannel;

class Poller : public noncopyable {
protected:
    using fd_t = int;

public:
    // Create a poller with its owner eventloop.
    Poller(std::shared_ptr<EventLoop> &ownerLoop);

    // Virtual Destructor.
    virtual ~Poller();

    // Predicate that if the channel given has managered by this eventloop.
    virtual bool HasChannel(hasaki::net::SocketChannel *channel) const;

    // Update the interest events of the fd.
    // NOTE: this method must be called int the loop thread.
    // DO NOT call the epoll_ctl in multi thread who has the same epfd.
    virtual void UpdateChannel(hasaki::net::SocketChannel *channel) = 0;

    // Remove the channel from current eventloop.
    virtual void RemoveChannel(hasaki::net::SocketChannel *channel) = 0;

    // Poll the io events int the channel list.
    virtual hasaki::base::Timestamp Poll(
        std::vector<hasaki::net::SocketChannel *> *activeChannels, int timeoutMs) = 0;

protected:
    std::map<fd_t, SocketChannel *> channels__;

private:
    std::shared_ptr<hasaki::net::EventLoop> ownerEventLoop__;
};

}  // namespace net
}  // namespace hasaki

#endif