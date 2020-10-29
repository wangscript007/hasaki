#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <typeinfo>
#include <vector>

#include "blocking_queue.h"
#include "byte_buffer.h"
#include "inet_address.h"
#include "logger.h"
#include "timestamp.h"
// clang++ main.cpp -std=c++11

class A {
public:
    A() { HASAKI_INFO("A() wall called..."); }

    A(const A &r) { HASAKI_INFO("A(const A&) wall called..."); }

    A &operator=(const A &r) {
        HASAKI_INFO("A& operator=(const A &r) wall called...");
        return *this;
    }
};

class B {
public:
    B() { HASAKI_INFO("B() wall called..."); }

    B(const B &r) : a__(r.a__) { HASAKI_INFO("B(const B&) wall called..."); }

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

// ====================================================================================================
template <typename _Tp>
class DynamicArray {
public:
    DynamicArray() {
        this->data__ = new _Tp[16];
        this->size__ = 0;
        this->cap__ = 16;
    }
    DynamicArray(const DynamicArray<_Tp> &rhs) {
        std::cout << "DynamicArray(const DynamicArray<_Tp> &rhs) ..." << std::endl;
        this->data__ = new _Tp[rhs.cap__];
        this->size__ = rhs.size__;
        this->cap__ = rhs.cap__;
    }
    DynamicArray(DynamicArray<_Tp> &&rhs) {
        std::cout << "DynamicArray(DynamicArray<_Tp> &&rhs) {" << std::endl;
        this->data__ = rhs.data__;
        this->size__ = rhs.size__;
        this->cap__ = rhs.cap__;
        rhs.data__ = nullptr;
        rhs.size__ = 0;
        rhs.cap__ = 0;

        // std::cout << typeid(rhs).name() << std::endl;
        test(std::move(rhs));
    }

    void test(DynamicArray<_Tp> &&) {
        std::cout << "test(DynamicArray<_Tp> &&)" << std::endl;
    }

    // void test(DynamicArray<_Tp> t) {
    //     std::cout << "test(DynamicArray<_Tp> t) " << std::endl;
    // }

    // void test(DynamicArray<_Tp> &t) {
    //     std::cout << "test(DynamicArray<_Tp> &t)" << std::endl;
    // }

private:
    _Tp *data__;
    std::size_t size__;
    std::size_t cap__;
};

// ====================================================================================================

static std::string SQL_FORMAT =
    " INSERT INTO user_grant_qualify_tag (`name`, uid, expire_time, type, ctime)"
    " VALUES ('%s', %ld, DATE_ADD(NOW(), INTERVAL %d DAY), 15, NOW())"
    " ON DUPLICATE KEY UPDATE expire_time = DATE_ADD(CASE "
    " WHEN expire_time > NOW() THEN expire_time"
    " ELSE NOW()"
    " END, INTERVAL %d DAY); \n";

int main(int argc, char **args) {
    // hasaki::net::InetAddress ineAddress;

    int days = 10;
    const char *tagName = std::string("sp180584").c_str();
    std::vector<long> uids__ = {35193736, 38828266, 42901411,  1000534082, 46548027,
                                48926289, 44360134, 36946915,  1000545723, 45945465,
                                4788407,  44430092, 46027121,  48032875,   1000317413,
                                45570453, 43989354, 1000620007};

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

    std::vector<int> v;
    int a = 10;
    v.push_back(std::move(a));

    //
    DynamicArray<int> v1;
    DynamicArray<int> v2 = std::move(v1);

    // auto b = std::move(a);

    // std::set<int> set;
    // set.insert(std::move(a));

    std::unique_ptr<int> sp(new int);
    std::unique_ptr<int> sp2(std::move(sp));

    hasaki::base::BlockingQueue<int> queue;
    // queue.Put(123);
    int aaa = -1;
    if (queue.Take(&aaa, std::chrono::seconds(3))) {
        HASAKI_INFO("take, aaaa = {}", aaa);
    } else {
        HASAKI_WARN("take timeout and failed, aaaa = {}", aaa);
    }
    return 0;
}
