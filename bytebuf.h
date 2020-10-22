#ifndef __HASAKI_BYTEBUF_H__
#define __HASAKI_BYTEBUF_H__

#include <vector>

class ByteBuf {
public:
    
private:
    std::vector<char> buf__;
    std::size_t readIndex__;
    std::size_t writeIndex__;
};

#endif
