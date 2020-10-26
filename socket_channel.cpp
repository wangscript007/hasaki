#include "socket_channel.h"
#include "event_loop.h"

namespace hasaki {
namespace net {

SocketChannel::SocketChannel(std::shared_ptr<hasaki::net::EventLoop> &eventLoop)
    : fd__(-1) {
    eventLoop__ = eventLoop;
}

SocketChannel::~SocketChannel() {
}

} // namespace net
} // namespace hasaki