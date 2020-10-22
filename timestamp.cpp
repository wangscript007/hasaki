#include "timestamp.h"

namespace hasaki
{
    namespace base
    {
        std::string Timestamp::ToString()
        {
            return "";
        }

        Timestamp Timestamp::Now()
        {
            return Timestamp(0);
        }

        Timestamp Timestamp::FromUnixTime()
        {
            return Timestamp(0);
        }

    } // namespace base
} // namespace hasaki
