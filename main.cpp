#include "logger.h"
#include "timestamp.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

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
    int days = 10;
    const char *tagName = std::string("sp180584").c_str();
    std::vector<long> uids__ = {45084387, 1000409587, 18826590, 24967602,  39597782,
                                44798517, 44001061,   41218670, 21357758,  43078084,
                                42191246, 39161779,   48509085, 1000341736};

    for (auto uid : uids__) {
        printf(SQL_FORMAT.c_str(), tagName, uid, days, days);
    }
    return 0;
}
