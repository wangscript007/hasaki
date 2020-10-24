#ifndef __HASAKI_BYTE_BUFFER_H__
#define __HASAKI_BYTE_BUFFER_H__

#include <vector>

namespace hasaki {
namespace base {

// ByteBuffer is a not thread-safe buffer with little-endian.
class ByteBuffer {
public:
    ByteBuffer() : readIndex__(0), writeIndex__(0) {
    }

    void WriteInt8(int8_t x);

    void WriteInt16(int16_t x);

    void WriteInt32(int32_t x);

    void WriteInt64(int64_t x);

    int8_t ReadInt8();

    int16_t ReadInt16();

    int32_t ReadInt32();

    int64_t ReadInt64();

    void Read(void *dst, std::size_t readlen);

    void Write(void *src, std::size_t writelen);

    std::size_t CapacityOfBuffer() const;

    std::size_t SizeOfBuffer() const;

    std::size_t ReadableBytes() const;

    void CleanAndShrink();

private:
    std::vector<char> buf__;
    std::size_t readIndex__;
    std::size_t writeIndex__;
};

} // namespace base
} // namespace hasaki

#endif
