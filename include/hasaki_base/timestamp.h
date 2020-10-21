#ifndef __HASAKI_TIMESTAMP_H__
#define __HASAKI_TIMESTAMP_H__

#include <cstdint>
#include <string>
#include "boost/noncopyable.hpp"
#include "boost/operators.hpp"

namespace hasaki
{

    namespace base
    {

        class Timestamp : boost::equality_comparable<Timestamp>, boost::less_than_comparable<Timestamp>
        {
        public:

            /// 
            /// Construct a default Timestamp.
            ///
            Timestamp() : msSinceEpoch__(0){}

            ///
            /// Construct a Timestamp by a msSinceEpoch given.
            ///
            explicit Timestamp(const uint64_t msSinceEpoch) : msSinceEpoch__(msSinceEpoch){}

            ///
            /// Convert to a std::string.
            ///
            std::string ToString() const;

        private:
            
            /// 
            uint64_t msSinceEpoch__;
        };

    } // namespace base
} // namespace hasaki

#endif