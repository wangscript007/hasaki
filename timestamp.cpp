#include "timestamp.h"

namespace hasaki {
namespace base {

std::string Timestamp::ToString() const
{
    
    return "";
}

Timestamp Timestamp::Now()
{
    return Timestamp(0);
}

Timestamp Timestamp::FromUnixTime(time_t unixTime)
{
    return Timestamp(0);
}

} // namespace base
} // namespace hasaki
