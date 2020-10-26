#include "socket_channel.h"

#include "event_loop.h"

namespace hasaki {
namespace net {

SocketChannel::SocketChannel(std::shared_ptr<hasaki::net::EventLoop> &eventLoop, int fd)
    : eventLoop__(eventLoop), fd__(fd), interestEvents__(0), readyEvents__(0),
      index__(-1), tied__(false) {
}

SocketChannel::~SocketChannel() {
}

void SocketChannel::Tie(const std::shared_ptr<void> &target) {
    tie__ = target;
    tied__ = true;
}

void SocketChannel::HandleEvents(hasaki::base::Timestamp recvTime) {
    // FIXME
}

} // namespace net
} // namespace hasaki