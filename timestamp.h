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
    /// <summary>
    /// Construct a new Timestamp with a invalid zero value for internel filed `microsecondsSinceEpoch`.
    /// </summary>
    /// <returns></returns>
    Timestamp() : microsecondSinceEpoch__(0) {
    }

    /// <summary>
    /// Constuct a new Timestamp with a given value of `microsecondSinceEpoch`.
    /// </summary>
    /// <param name="microsecondSinceEpoch"></param>
    /// <returns></returns>
    explicit Timestamp(int64_t microsecondSinceEpoch)
        : microsecondSinceEpoch__(microsecondSinceEpoch) {
    }

    /// <summary>
    /// operator==
    /// </summary>
    /// <param name="rhs"></param>
    /// <returns></returns>
    bool operator==(const Timestamp &rhs) {
        return this->microsecondSinceEpoch__ == rhs.microsecondSinceEpoch__;
    }

    /// <summary>
    /// operator!=
    /// </summary>
    /// <param name="rhs"></param>
    /// <returns></returns>
    bool operator!=(const Timestamp &rhs) {
        return this->microsecondSinceEpoch__ != rhs.microsecondSinceEpoch__;
    }

    /// <summary>
    /// operator<=
    /// </summary>
    /// <param name="rhs"></param>
    /// <returns></returns>
    bool operator<=(const Timestamp &rhs) {
        return this->microsecondSinceEpoch__ <= rhs.microsecondSinceEpoch__;
    }

    /// <summary>
    /// operator<
    /// </summary>
    /// <param name="rhs"></param>
    /// <returns></returns>
    bool operator<(const Timestamp &rhs) {
        return this->microsecondSinceEpoch__ < rhs.microsecondSinceEpoch__;
    }

    /// <summary>
    /// operator>
    /// </summary>
    /// <param name="rhs"></param>
    /// <returns></returns>
    bool operator>(const Timestamp &rhs) {
        return this->microsecondSinceEpoch__ > rhs.microsecondSinceEpoch__;
    }

    /// <summary>
    /// operator>=
    /// </summary>
    /// <param name="rhs"></param>
    /// <returns></returns>
    bool operator>=(const Timestamp &rhs) {
        return this->microsecondSinceEpoch__ >= rhs.microsecondSinceEpoch__;
    }

    /// <summary>
    ///  Convert self to a readable string.
    /// </summary>
    /// <returns></returns>
    std::string ToString() const;

    /// <summary>
    /// Get the microseconds since epoch.
    /// </summary>
    /// <returns></returns>
    int64_t GetMicrosecondSinceEpoch() const {
        return this->microsecondSinceEpoch__;
    }

    /// <summary>
    /// Predicate the timestamp if a valid value.
    /// </summary>
    /// <returns></returns>
    bool IsValid() const {
        return this->microsecondSinceEpoch__ > 0;
    }

    /// <summary>
    /// Get a Timestamp presents now.
    /// </summary>
    /// <returns> Microseconds from 1970</returns>
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
