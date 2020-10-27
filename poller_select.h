#ifndef __HASAKI_POLLER_SELECT_H__
#define __HASAKI_POLLER_SELECT_H__

#include "poller.h"

namespace hasaki {
namespace net {

// An select-based implementation of Poller.
// select is a POSIX standard, it cannot be supported on Windows/Linux/MacOS...
class SelectPoller : public hasaki::net::Poller {
public:
    void UpdateChannel(hasaki::net::SocketChannel *channel) override;
    void RemoveChannel(hasaki::net::SocketChannel *channel) override;
    hasaki::base::Timestamp Poll(
        std::vector<hasaki::net::SocketChannel *> *activeChannels,
        int timeoutMs) override;
};

}  // namespace net
}  // namespace hasaki

#endif