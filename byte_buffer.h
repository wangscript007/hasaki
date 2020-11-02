#ifndef __HASAKI_BYTE_BUFFER_H__
#define __HASAKI_BYTE_BUFFER_H__

#include <vector>

namespace hasaki {
namespace base {

/// <summary>
/// ByteBuffer is a not thread-safe buffer with a read index and write index.
/// The readIndex will go forward when the method family start with 'ReadXX' was called, and
/// the writeIndex will go forward when the method family start with 'WriteXX' was called.
/// The readIndex must be less or equal to the writeIndex, when you use 'ReadXX'-like methods,
/// you'd better call the `ReadableBytes() `method first to ensure the safe, or else it will be panic
/// if the ByteBuffer has no so many bytes to read.
/// </summary>
class ByteBuffer {
public:
    /// <summary>
    /// Construct a Bytebuffer and reset the readIndex and writeIndex starts from position 0.
    /// </summary>
    /// <returns></returns>
    ByteBuffer() : readIndex__(0), writeIndex__(0) {
    }

    /// <summary>
    /// Write a int8_t to the ByteBuffer.
    /// </summary>
    /// <param name="x">the int8_t data to write.</param>
    void WriteInt8(int8_t x);

    /// <summary>
    /// Write a int16_t to the ByteBuffer with little endian.
    /// </summary>
    /// <param name="x"></param>
    void WriteInt16(int16_t x);

    /// <summary>
    /// Write a int32_t to the ByteBuffer with little endian.
    /// </summary>
    /// <param name="x"></param>
    void WriteInt32(int32_t x);

    /// <summary>
    /// Write a int64_t to the ByteBuffer with little endian.
    /// </summary>
    /// <param name="x"></param>
    void WriteInt64(int64_t x);

    /// <summary>
    /// Read 1 bytes from the BuyteBuffer by little endian and convert to a int8_t.
    /// </summary>
    /// <returns></returns>
    int8_t ReadInt8();

    /// <summary>
    /// Read 2  bytes from the BuyteBuffer by little endian and convert to a int16_t.
    /// </summary>
    /// <returns></returns>
    int16_t ReadInt16();

    /// <summary>
    ///  Read 4  bytes from the BuyteBuffer by little endian and convert to a int32_t.
    /// </summary>
    /// <returns></returns>
    int32_t ReadInt32();

    /// <summary>
    ///  Read 8  bytes from the BuyteBuffer by little endian and convert to a int64_t.
    /// </summary>
    /// <returns></returns>
    int64_t ReadInt64();

    /// <summary>
    /// Read byte data from the ByteBuffer to the given address with the given length.
    /// </summary>
    /// <param name="dst"></param>
    /// <param name="readlen"></param>
    void Read(void *dst, std::size_t readlen);

    /// <summary>
    /// Write byte data to from the given address to ByteBuffer with the given length.
    /// </summary>
    /// <param name="src"></param>
    /// <param name="writelen"></param>
    void Write(void *src, std::size_t writelen);

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    std::size_t CapacityOfBuffer() const;

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    std::size_t SizeOfBuffer() const;

    /// <summary>
    /// Returns the number of readble bytes in this ByteBuffer.
    /// </summary>
    /// <returns></returns>
    std::size_t ReadableBytes() const;

    /// <summary>
    /// 
    /// </summary>
    void CleanAndShrink();

private:
    std::vector<char> buf__;
    std::size_t readIndex__;
    std::size_t writeIndex__;
};

} // namespace base
} // namespace hasaki

#endif
