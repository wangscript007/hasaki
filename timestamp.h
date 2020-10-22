#ifndef __HASAKI_TIMESTAMP_H__
#define __HASAKI_TIMESTAMP_H__

#include <cstdint>
#include <string>
#include <ctime>

namespace hasaki {
namespace base{

// A wrapper of the msSinceEpoch.

class Timestamp
{

    public:
    ///
    ///
    Timestamp() : msSinceEpoch__(0) {}

    ///
    ///
    explicit Timestamp(uint64_t msSinceEpoch) : msSinceEpoch__(msSinceEpoch) {}

    ///
    ///
    std::string ToString() const;

    ///
    ///
    static Timestamp Now();

    ///
    ///
    static Timestamp FromUnixTime(time_t unixTime);

    private:
    uint64_t msSinceEpoch__;
};

} // namespace base
} // namespace hasaki

#endif
