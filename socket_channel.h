#ifndef __HASAKI_SOCKET_CHANNEL_H__
#define __HASAKI_SOCKET_CHANNEL_H__

#include <functional>
#include <memory>
#include <vector>

#include "noncopyable.h"
#include "timestamp.h"

namespace hasaki {
namespace net {

// Forward declarations.
class Poller;
class EventLoop;

namespace {
static const int NONE_EVENT = 0;
static const int READ_EVENT = 1;
static const int WRITE_EVENT = 2;
}  // namespace

// SocketChannel is a wrapper for client fd and it's events.
class SocketChannel : public hasaki::noncopyable {
public:
    using SocketChannelList = std::vector<SocketChannel>;
    using EventCallbackFn = std::function<void()>;
    using ReadEventCallbackFn = std::function<void(hasaki::base::Timestamp)>;

public:
    SocketChannel(std::shared_ptr<hasaki::net::EventLoop>& eventloop, int fd);

    ~SocketChannel();

    int fd() const { return fd__; }

    int InterestEvents() const { return interestEvents__; }

    void SetReadyEvents(int readyEvents) { readyEvents__ = readyEvents; }

    void HandleEvents(hasaki::base::Timestamp recvTime);

    void Update();

    void Tie(const std::shared_ptr<void>&);

    void EnableRead() {
        interestEvents__ |= READ_EVENT;
        Update();
    }

    void EnableWrite() {
        interestEvents__ |= WRITE_EVENT;
        Update();
    }

    void DisableRead() {
        interestEvents__ &= ~READ_EVENT;
        Update();
    }

    void DisableWrite() {
        interestEvents__ &= ~WRITE_EVENT;
        Update();
    }

    void SetWriteEventCallback(EventCallbackFn& callbackFn) {
        writeEventCallbackFn__ = callbackFn;
    }

    void SetCloseEventCallback(EventCallbackFn& callbackFn) {
        closeEventCallbackFn__ = callbackFn;
    }

    void SetErrorEventCallback(EventCallbackFn& callbackFn) {
        errorEventCallbackFn__ = callbackFn;
    }

    void SetReadEventCallback(ReadEventCallbackFn& callbackFn) {
        readEventCallbackFn__ = callbackFn;
    }

private:
    const int fd__;        // the file descriptor
    int interestEvents__;  // interest events the fd registed
    int readyEvents__;     // real ready events when events occured behind the fd
    int index__;           // oops.

    std::shared_ptr<hasaki::net::EventLoop> eventLoop__;  // event loop ptr
    std::shared_ptr<hasaki::net::Poller> poller__;        // poller ptr

    std::weak_ptr<void> tie__;
    bool tied__;

    EventCallbackFn errorEventCallbackFn__;
    EventCallbackFn closeEventCallbackFn__;
    EventCallbackFn writeEventCallbackFn__;
    ReadEventCallbackFn readEventCallbackFn__;
};

}  // namespace net
}  // namespace hasaki

#endif