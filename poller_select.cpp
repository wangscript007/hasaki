#include "poller_select.h"
#include "hasaki_core.h"

#if (defined(OS_WINDOWS) && OS_WINDOWS)
#include <WinSock2.h>
#else
#include <sys/select.h>
#endif

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