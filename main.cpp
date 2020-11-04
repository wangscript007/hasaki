#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
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

void product_thr_entry(hasaki::base::BlockingQueue<std::string> &q__) {
    std::stringstream ss;
    ss << 1;
    for (size_t i = 0; i < 50; i++) {
        ss << i;
        std::cout << "producer-thread: Put " << ss.str() << std::endl;
        q__.Put(ss.str());
        std::this_thread::sleep_for(std::chrono::microseconds(800));
    }
}

void consumer_thr_entry(hasaki::base::BlockingQueue<std::string> &q__) {
    for (;;) {
        auto x = q__.Take();
        std::cout << "consumer-thread: Take " << x << std::endl;
    }
}

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

    hasaki::base::BlockingQueue<std::string> bq_;

    std::thread producer(product_thr_entry, std::ref(bq_));
    std::thread consumer(consumer_thr_entry, std::ref(bq_));

    producer.join();
    consumer.join();
    return 0;
}
