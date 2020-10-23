#ifndef __HASAKI_TIMESTAMP_H__
#define __HASAKI_TIMESTAMP_H__

#include <cstdint>
#include <ctime>
#include <string>

#define MILLI_SECONDS_PER_SECOND (1000 * 1)
#define MICRO_SECONDS_PER_SECOND (1000 * 1000)

namespace hasaki {
namespace base {

// Timestamp is a wrapper of the msSinceEpoch which can be copied,
// and it has the default copy contructor and default assign method.

class Timestamp {
public:
    //
    //
    Timestamp() : microsecondSinceEpoch__(0) {
    }

    //
    //
    explicit Timestamp(int64_t microsecondSinceEpoch)
        : microsecondSinceEpoch__(microsecondSinceEpoch) {
    }

    bool operator==(const Timestamp &rhs) {
        return this->microsecondSinceEpoch__ == rhs.microsecondSinceEpoch__;
    }

    bool operator!=(const Timestamp &rhs) {
        return this->microsecondSinceEpoch__ != rhs.microsecondSinceEpoch__;
    }

    bool operator<=(const Timestamp &rhs) {
        return this->microsecondSinceEpoch__ <= rhs.microsecondSinceEpoch__;
    }

    bool operator<(const Timestamp &rhs) {
        return this->microsecondSinceEpoch__ < rhs.microsecondSinceEpoch__;
    }

    bool operator>(const Timestamp &rhs) {
        return this->microsecondSinceEpoch__ > rhs.microsecondSinceEpoch__;
    }

    bool operator>=(const Timestamp &rhs) {
        return this->microsecondSinceEpoch__ >= rhs.microsecondSinceEpoch__;
    }

    //
    //
    std::string ToString() const;

    //
    //
    int64_t GetMicrosecondSinceEpoch() const {
        return this->microsecondSinceEpoch__;
    }

    // Is current timestamp object is a valid timestamp holder.
    bool IsValid() const {
        return this->microsecondSinceEpoch__ > 0;
    }

    // Get a Timestamp presents now.
    // Microseconds from 1970
    static Timestamp Now();

private:
    // For history reason, we use int64_t instead of uint64_t.
    // time_t was designed to be a signed long, and mktime can returns
    // a -1 to present the failure. en...
    int64_t microsecondSinceEpoch__;
};

} // namespace base
} // namespace hasaki

#endif
