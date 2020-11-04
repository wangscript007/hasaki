#ifndef __HASAKI_SOCKET_CHANNEL_H__
#define __HASAKI_SOCKET_CHANNEL_H__

#include "hasaki_core.h"
#include "noncopyable.h"
#include "timestamp.h"

#include <functional>
#include <memory>
#include <vector>

namespace hasaki {
namespace net {

// Forward declarations.
class Poller;
class EventLoop;

namespace {
const int NONE_EVENT = 0;
const int READ_EVENT = 1;
const int WRITE_EVENT = 2;
} // namespace

// SocketChannel is a wrapper for client fd and it's events.
class SocketChannel : public hasaki::noncopyable {
public:
    using SocketChannelList       = std::vector<SocketChannel>;
    using EventCallbackFn         = std::function<void()>;
    using ReadEventCallbackFn     = std::function<void(hasaki::base::Timestamp)>;

public:
    SocketChannel(std::shared_ptr<hasaki::net::EventLoop> &eventloop, int fd);

    ~SocketChannel();

    int fd() const { return fd__; }

    int index() const { return index__; }

    void SetIndex(int index) { index__ = index; }

    void SetReadyEvents(int readyEvents) { readyEvents__ = readyEvents; }

    int InterestEvents() const { return interestEvents__; }

    void HandleEvents(hasaki::base::Timestamp recvTime);

    void Tie(const std::shared_ptr<void> &);

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

    void DisableAll() {
        interestEvents__ = NONE_EVENT;
        Update();
    }

    bool IsInterestWithRead() const {
        return interestEvents__ & READ_EVENT;
    }

    bool IsInterestWithWrite() const {
        return interestEvents__ & WRITE_EVENT;
    }

    void SetWriteEventCallback(EventCallbackFn &callbackFn) {
        writeEventCallbackFn__ = callbackFn;
    }

    void SetCloseEventCallback(EventCallbackFn &callbackFn) {
        closeEventCallbackFn__ = callbackFn;
    }

    void SetErrorEventCallback(EventCallbackFn &callbackFn) {
        errorEventCallbackFn__ = callbackFn;
    }

    void SetReadEventCallback(ReadEventCallbackFn &callbackFn) {
        readEventCallbackFn__ = callbackFn;
    }

private:
    void Update();
    void HandleEventsWithGuard(hasaki::base::Timestamp recvTime);

private:
    const int fd__;       // the file descriptor
    int interestEvents__; // interest events the fd registed
    int readyEvents__;    // real ready events when events occured behind the fd
    int index__;          // for business op.

    std::shared_ptr<hasaki::net::EventLoop> eventLoop__; // event loop ptr
    std::shared_ptr<hasaki::net::Poller> poller__;       // poller ptr

    std::weak_ptr<void> tie__;
    bool tied__;

    EventCallbackFn errorEventCallbackFn__;
    EventCallbackFn closeEventCallbackFn__;
    EventCallbackFn writeEventCallbackFn__;
    ReadEventCallbackFn readEventCallbackFn__;
};

} // namespace net
} // namespace hasaki

#endif
