#include "poller_select.h"

#include <sys/select.h>

namespace hasaki {
namespace net {

void SelectPoller::UpdateChannel(hasaki::net::SocketChannel *channel) {
}

void SelectPoller::RemoveChannel(hasaki::net::SocketChannel *channel) {
}

hasaki::base::Timestamp SelectPoller::Poll(
    std::vector<hasaki::net::SocketChannel *> *activeChannels, int timeoutMs) {
}

} // namespace net
} // namespace hasaki