#include "byte_buffer.h"
#include "hasaki_global.h"

namespace hasaki {
namespace base {

void ByteBuffer::WriteInt8(int8_t x) {
    buf__.push_back(x);
    writeIndex__ += sizeof(int8_t);
}

void ByteBuffer::WriteInt16(int16_t x) {
    buf__.push_back((char)(x >> 8));
    buf__.push_back((char)x);
    writeIndex__ += sizeof(int16_t);
}

void ByteBuffer::WriteInt32(int32_t x) {
    buf__.push_back((char)(x >> 24));
    buf__.push_back((char)(x >> 16));
    buf__.push_back((char)(x >> 8));
    buf__.push_back((char)x);
    writeIndex__ += sizeof(int32_t);
}

void ByteBuffer::WriteInt64(int64_t x) {
    buf__.push_back((char)(x >> 56));
    buf__.push_back((char)(x >> 48));
    buf__.push_back((char)(x >> 40));
    buf__.push_back((char)(x >> 32));
    buf__.push_back((char)(x >> 24));
    buf__.push_back((char)(x >> 16));
    buf__.push_back((char)(x >> 8));
    buf__.push_back((char)x);
    writeIndex__ += sizeof(int64_t);
}

void ByteBuffer::Write(void *src, std::size_t writelen) {
    for (size_t i = 0; i < writelen; i++) {
        buf__.push_back(*((char *)src + i));
    }
    writeIndex__ += writelen;
}

int8_t ByteBuffer::ReadInt8() {
    if (writeIndex__ - readIndex__ < sizeof(int8_t)) {
#ifdef HASAKI_NO_EXCEPTIONS
        HASAKI_PANIC("ByteBuffer have no 8 bytes to read!");
#else
        HASAKI_THROW(std::out_of_range("ByteBuffer have no 8 bytes to read!"));
#endif
    }
    int8_t value = buf__[readIndex__];
    readIndex__ += sizeof(int8_t);
    return value;
}

int16_t ByteBuffer::ReadInt16() {
}

int32_t ByteBuffer::ReadInt32() {
}

int64_t ByteBuffer::ReadInt64() {
}

void ByteBuffer::Read(void *dst, std::size_t readlen) {
}

std::size_t ByteBuffer::ReadableBytes() const {
    return (writeIndex__ - readIndex__);
}

} // namespace base

} // namespace hasaki