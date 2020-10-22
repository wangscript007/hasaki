#ifndef __HASAKI_BYTE_BUFFER_H__
#define __HASAKI_BYTE_BUFFER_H__

#include <vector>

namespace hasaki {
namespace base {

class ByteBuffer {
public:
private:
    std::vector<char> buf__;
    std::size_t readIndex__;
    std::size_t writeIndex__;
};

}  // namespace base
}  // namespace hasaki

#endif
