#ifndef __HASAKI_TIMESTAMP_H__
#define __HASAKI_TIMESTAMP_H__

#include <cstdint>
#include <string>

namespace hasaki
{
    namespace base
    {
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
            std::string ToString();

            ///
            ///
            static Timestamp Now();

            ///
            ///
            static Timestamp FromUnixTime();

        private:
            uint64_t msSinceEpoch__;
        };

    } // namespace base
} // namespace hasaki

#endif