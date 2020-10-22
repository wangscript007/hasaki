#ifndef __HASAKI_BYTE_BUFFER_H__
#define __HASAKI_BYTE_BUFFER_H__

#include <vector>

class ByteBuffer {
public:
    
private:
    std::vector<char> buf__;
    std::size_t readIndex__;
    std::size_t writeIndex__;
};

#endif
