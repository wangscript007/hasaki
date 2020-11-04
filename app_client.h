#ifndef __HASAKI_APP_CLIENT_H__
#define __HASAKI_APP_CLIENT_H__

#include <memory>

namespace hasaki {
namespace net {

/// <summary>
/// AppClient
/// </summary>
class AppClient : public std::enable_shared_from_this<AppClient> {
public:
    AppClient() = default;
    virtual ~AppClient() = default;
};

}   // namespace net
}  // namespace hasaki


#endif