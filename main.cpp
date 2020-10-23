#include "logger.h"
#include "timestamp.h"
#include <iostream>
#include <memory>

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

int main(int argc, char **args) {
    // B b1;
    // B b2 = b1; // copy constructor.
    // B b2;
    // b2 = b1;

    B b1;
    // std::cout << "------------------------------" << std::endl;
    // B b2 = b1;
    B b2;
    b2 = b1;

    // xxxxxx
    Teacher t;
    t.faUser__.reset(new User);
    std::cout << t.faUser__.use_count() << std::endl;

    Teacher t2 = t;
    std::cout << t.faUser__.use_count() << std::endl;
    std::cout << t2.faUser__.use_count() << std::endl;

    // Teacher t3;
    // t3 = t;
    // std::cout << t.faUser__.use_count() << std::endl;
    hasaki::base::Timestamp tt1;
    hasaki::base::Timestamp tt2;
    tt1 < tt2;
    return 0;
}
