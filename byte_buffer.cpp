#include "byte_buffer.h"

#include "hasaki_core.h"

namespace hasaki {
namespace base {

void ByteBuffer::WriteInt8(int8_t x) {
    buf__.push_back(x);
    writeIndex__ += sizeof(int8_t);
}

void ByteBuffer::WriteInt16(int16_t x) {
    buf__.push_back(static_cast<char>(x >> 0));
    buf__.push_back(static_cast<char>(x >> 8));
    writeIndex__ += sizeof(int16_t);
}

void ByteBuffer::WriteInt32(int32_t x) {
    buf__.push_back(static_cast<char>(x >> 0));
    buf__.push_back(static_cast<char>(x >> 8));
    buf__.push_back(static_cast<char>(x >> 16));
    buf__.push_back(static_cast<char>(x >> 24));
    writeIndex__ += sizeof(int32_t);
}

void ByteBuffer::WriteInt64(int64_t x) {
    buf__.push_back(static_cast<char>(x >> 0));
    buf__.push_back(static_cast<char>(x >> 8));
    buf__.push_back(static_cast<char>(x >> 16));
    buf__.push_back(static_cast<char>(x >> 24));
    buf__.push_back(static_cast<char>(x >> 32));
    buf__.push_back(static_cast<char>(x >> 40));
    buf__.push_back(static_cast<char>(x >> 48));
    buf__.push_back(static_cast<char>(x >> 56));
    writeIndex__ += sizeof(int64_t);
}

int8_t ByteBuffer::ReadInt8() {
    if (writeIndex__ - readIndex__ < sizeof(int8_t)) {
#ifdef HASAKI_NO_EXCEPTIONS
        HASAKI_PANIC("ByteBuffer have no 8 bits to read!");
#else
        HASAKI_THROW(std::out_of_range("ByteBuffer have no 8 bits to read!"));
#endif
    }
    int8_t value = buf__[readIndex__];
    readIndex__ += sizeof(int8_t);
    return value;
}

int16_t ByteBuffer::ReadInt16() {
    if (writeIndex__ - readIndex__ < sizeof(int16_t)) {
#ifdef HASAKI_NO_EXCEPTIONS
        HASAKI_PANIC("ByteBuffer have no 16 bits to read!");
#else
        HASAKI_THROW(std::out_of_range("ByteBuffer have no 16 bits to read!"));
#endif
    }
    int16_t value = static_cast<int16_t>((buf__[readIndex__ + 1] << 8) |
                                         (buf__[readIndex__] & 0xff));
    readIndex__ += sizeof(int16_t);
    return value;
}

int32_t ByteBuffer::ReadInt32() {
    if (writeIndex__ - readIndex__ < sizeof(int32_t)) {
#ifdef HASAKI_NO_EXCEPTIONS
        HASAKI_PANIC("ByteBuffer have no 32 bits to read!");
#else
        HASAKI_THROW(std::out_of_range("ByteBuffer have no 32 bits to read!"));
#endif
    }
    int32_t value =
        (buf__[readIndex__ + 3] << 24) | ((buf__[readIndex__ + 2] & 0xff) << 16) |
        ((buf__[readIndex__ + 1] & 0xff) << 8) | (buf__[readIndex__] & 0xff);

    // MARK
    readIndex__ += sizeof(int32_t);
    return value;
}

int64_t ByteBuffer::ReadInt64() {
    if (writeIndex__ - readIndex__ < sizeof(int64_t)) {
#ifdef HASAKI_NO_EXCEPTIONS
        HASAKI_PANIC("ByteBuffer have no 64 bits to read!");
#else
        HASAKI_THROW(std::out_of_range("ByteBuffer have no 64 bits to read!"));
#endif
    }
    int64_t value = ((static_cast<int64_t>(buf__[readIndex__ + 7])) << 56) |
                    ((static_cast<int64_t>(buf__[readIndex__ + 6] & 0xff)) << 48) |
                    ((static_cast<int64_t>(buf__[readIndex__ + 5] & 0xff)) << 40) |
                    ((static_cast<int64_t>(buf__[readIndex__ + 4] & 0xff)) << 32) |
                    ((static_cast<int64_t>(buf__[readIndex__ + 3] & 0xff)) << 24) |
                    ((static_cast<int64_t>(buf__[readIndex__ + 2] & 0xff)) << 16) |
                    ((static_cast<int64_t>(buf__[readIndex__ + 1] & 0xff)) << 8) |
                    ((static_cast<int64_t>(buf__[readIndex__] & 0xff)));
    readIndex__ += sizeof(int64_t);
    return value;
}

void ByteBuffer::Read(void *dst, std::size_t readlen) {
    if (writeIndex__ - readIndex__ < readlen) {
#ifdef HASAKI_NO_EXCEPTIONS
        HASAKI_PANIC("ByteBuffer have no  bits to read!");
#else
        HASAKI_THROW(std::out_of_range("ByteBuffer have no 64 bits to read!"));
#endif
    }
}

void ByteBuffer::Write(void *src, std::size_t writelen) {
    for (size_t i = 0; i < writelen; i++) {
        buf__.push_back(*((char *)src + i));
    }
    writeIndex__ += writelen;
}

std::size_t ByteBuffer::ReadableBytes() const {
    assert(readIndex__ <= writeIndex__);
    return (writeIndex__ - readIndex__);
}

void ByteBuffer::CleanAndShrink() {
    std::vector<char> stackObj__;
    stackObj__.swap(this->buf__);
    this->readIndex__ = 0;
    this->writeIndex__ = 0;
}

std::size_t ByteBuffer::CapacityOfBuffer() const {
    return buf__.capacity();
}

std::size_t ByteBuffer::SizeOfBuffer() const {
    return buf__.size();
}

} // namespace base

} // namespace hasaki