#include "timestamp.h"
#include <sys/time.h>

namespace hasaki {
namespace base {

std::string Timestamp::ToString() const {
    return "";
}

Timestamp Timestamp::Now() {
    struct timeval tv;
    int ret = -1;
    do {
        ret = gettimeofday(&tv, nullptr);
    } while (ret);
    return Timestamp((tv.tv_sec * MICRO_SECONDS_PER_SECOND) + tv.tv_usec);
}

} // namespace base
} // namespace hasaki
