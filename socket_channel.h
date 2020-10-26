#ifndef __HASAKI_SOCKET_CHANNEL_H__
#define __HASAKI_SOCKET_CHANNEL_H__

#include "noncopyable.h"
#include "timestamp.h"
#include <functional>
#include <memory>
#include <vector>

namespace hasaki {
namespace net {

// Forward declarations.
class EventLoop;

// SocketChannel is a wrapper for client fd and it's events.
class SocketChannel : public hasaki::noncopyable {
public:
    using SocketChannelList = std::vector<SocketChannel>;
    using EventCallbackFn = std::function<void()>;
    using ReadEventCallbackFn = std::function<void(hasaki::base::Timestamp)>;

public:
    SocketChannel(std::shared_ptr<hasaki::net::EventLoop> &eventloop);
    ~SocketChannel();

private:
    const int fd__;
    int interestEvents__;
    int readyEvents__;

    std::shared_ptr<hasaki::net::EventLoop> eventLoop__;
    EventCallbackFn errorEventCallbackFn__;
    EventCallbackFn writeEventCallbackFn__;
    ReadEventCallbackFn readEventCallbackFn__;
};

} // namespace net
} // namespace hasaki

#endif