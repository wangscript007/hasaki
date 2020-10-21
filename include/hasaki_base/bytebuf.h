#ifndef __HASAKI_BYTEBUF_H__
#define __HASAKI_BYTEBUF_H__

#include <vector>

namespace hasaki {

namespace base {

class ByteBuf {
public:
    explicit ByteBuf(size_t initialSize);
    ByteBuf(const ByteBuf &o);
    ByteBuf(ByteBuf &&o);

private:
    std::vector<char> buffer__;
    std::size_t readIndex__;
    std::size_t writeIndex__;
};

} /* end of namespace base */
} /* end of namespace hasaki */

#endif