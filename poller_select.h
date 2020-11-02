#ifndef __HASAKI_POLLER_SELECT_H__
#define __HASAKI_POLLER_SELECT_H__

#include "poller.h"

namespace hasaki {
namespace net {

// An select-based implementation of Poller.
// select is a POSIX standard, it cannot be supported on Windows/Linux/MacOS...
class SelectPoller : public hasaki::net::Poller {
public:
   
    /// <summary>
    /// 
    /// </summary>
    /// <param name="channel"></param>
    void UpdateChannel(hasaki::net::SocketChannel *channel) override;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="channel"></param>
    void RemoveChannel(hasaki::net::SocketChannel *channel) override;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="activeChannels"></param>
    /// <param name="timeoutMs"></param>
    /// <returns></returns>
    hasaki::base::Timestamp Poll(
        std::vector<hasaki::net::SocketChannel *> *activeChannels,
        int timeoutMs) override;
};

}  // namespace net
}  // namespace hasaki

#endif