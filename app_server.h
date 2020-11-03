#ifndef __HASAKI_APP_SERVER_H__
#define __HASAKI_APP_SERVER_H__

#include <memory>

namespace hasaki {
namespace net {

/// <summary>
/// 
/// </summary>
class AppServer : public std::enable_shared_from_this<AppServer> {
public:
    AppServer() = default;
    virtual ~AppServer() = default;
};
} // namespace net
} // namespace hasaki

#endif