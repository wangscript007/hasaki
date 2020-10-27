#include <algorithm>
#include <functional>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "byte_buffer.h"
#include "inet_address.h"
#include "logger.h"
#include "timestamp.h"

// clang++ main.cpp -std=c++11

class A {
public:
    A() {
        HASAKI_INFO("A() wall called...");
    }

    A(const A &r) {
        HASAKI_INFO("A(const A&) wall called...");
    }

    A &operator=(const A &r) {
        HASAKI_INFO("A& operator=(const A &r) wall called...");
        return *this;
    }
};

class B {
public:
    B() {
        HASAKI_INFO("B() wall called...");
    }

    B(const B &r) : a__(r.a__) {
        HASAKI_INFO("B(const B&) wall called...");
    }

    // B &operator=(const B &r) {
    //     HASAKI_INFO("B& operator=(const B&) wall called...");
    //     return *this;
    // }

private:
    A a__;
};

// ====================================================================================================

class User {};

class Teacher {
public:
    Teacher() = default;

public:
    std::shared_ptr<User> faUser__;
};

static std::string SQL_FORMAT =
    "INSERT INTO user_grant_qualify_tag SET `name` = '%s',uid = %ld,"
    "expire_time = DATE_ADD( NOW( ), INTERVAL %d DAY ),"
    "type = 15,"
    "ctime = NOW( ) "
    "ON DUPLICATE KEY UPDATE expire_time = DATE_ADD( expire_time, INTERVAL %d DAY );\n";

int main(int argc, char **args) {
    // hasaki::net::InetAddress ineAddress;

    int days = 30;
    const char *tagName = std::string("sp180502").c_str();
    std::vector<long> uids__ = {42564073, 1000534082};

    for (auto uid : uids__) {
        printf(SQL_FORMAT.c_str(), tagName, uid, days, days);
    }
    // 00000000 10000001
    // hasaki::base::ByteBuffer byteBuffer;
    // byteBuffer.WriteInt16(129);  // 00000000 10000001   // vector:  10000001 00000000
    // std::cout << byteBuffer.ReadInt16() << std::endl;
    // 10000001  00000000
    //
    using Bf = hasaki::base::ByteBuffer;
    Bf bf;
    bf.WriteInt64(123333L);
    bf.WriteInt64(123333L);
    bf.WriteInt64(123333L);
    bf.WriteInt64(123333L);
    bf.WriteInt64(123333L);
    bf.WriteInt64(123333L);
    HASAKI_INFO("size:{}, cap:{}", bf.SizeOfBuffer(), bf.CapacityOfBuffer());
    bf.CleanAndShrink();
    HASAKI_INFO("size:{}, cap:{}", bf.SizeOfBuffer(), bf.CapacityOfBuffer());
    // for (int64_t i = -12323312334; i < 981233; i++) {
    //     HASAKI_INFO("i = {}, bufferSize:{}, bufferCap:{}", i, bf.SizeOfBuffer(),
    //                 bf.CapacityOfBuffer());
    //     bf.WriteInt64(i);
    //     if (bf.ReadInt64() != i) {
    //         HASAKI_ERROR("error, i = {}", i);
    //         break;
    //     }
    // }
    // std::less<int> less;
    // auto x = std::bind(less, 1, 1, 2);
    // std::cout << x(100, 2, 3, 4, 5) << std::endl;
    return 0;
}
