#include "poller.h"
#include "socket_channel.h"

namespace hasaki {
namespace net {

Poller::Poller(std::shared_ptr<EventLoop> &ownerLoop) {
}

Poller::~Poller() {
}

bool Poller::HasChannel(hasaki::net::SocketChannel *channel) const {
    if (channel == nullptr) {
        return false;
    }
    int fd = channel->fd();
    return channels__.find(fd) != channels__.cend();
}

} // namespace net
} // namespace hasaki
