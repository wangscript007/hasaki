#ifndef __HASAKI_GLOBAL_H__
#define __HASAKI_GLOBAL_H__

#include <cstdio>
#include <cstdlib>

#define HASAKI_PANIC(...)              \
    do {                               \
        fprintf(stderr, __VAR_ARGS__); \
        abort();                       \
    } while (0)

#define hasaki_nop() asm volatile("nop");

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

#ifdef HASAKI_NO_EXCEPTIONS
#define HASAKI_TRY if (true)
#define HASAKI_CATCH(A) else
#define HASAKI_THROW(A) hasaki_nop()
#define HASAKI_RETHROW hasaki_nop()
#else
#define HASAKI_TRY try
#define HASAKI_CATCH(A) catch (A)
#define HASAKI_THROW(A) throw A
#define HASAKI_RETHROW throw
#endif

///
/// no exception definations of different cpp version.

#if __cplusplus < 201103L
#define NOEXCEPT throw()
#else
#define NOEXCEPT noexcept
#endif

///
/// Operating System Evaluation

// Windows
#if (defined(_WIN32) || defined(_WIN64))
#define OS_WINDOWS 1
#else
#define OS_WINDOWS 0
#endif

// linux
#if (defined(__linux) || defined(__linux__))
#define OS_LINUX 1
#else
#define OS_LINUX 0
#endif

// Apple
#if defined(__APPLE__)
#define OS_APPLE 1
#else
#define OS_APPLE 0
#endif

// FreeBSD
#if (defined(__FreeBSD__) || defined(__FreeBSD_kernel__))
#define OS_FREEBSD 1
#else
#define OS_FREEBSD 0
#endif

// Sun solaris
#if (defined(__sun))
#define OS_SOLARIS 1
#else
#define OS_SOLARIS 0
#endif

// Android
#if (defined(__ANDROID__))
#define OS_ANDROID 1
#else
#define OS_ANDROID 0
#endif

///
/// Compiler Evaluation
///

// g++ gcc
#if (defined(__GNUC__))
#define COMPILER_GCC 1
#else
#define COMPILER_GCC 0
#endif

// VC++
#if defined(_MSC_VER)
#define COMPILER_MSVC 1
#else
#define COMPILER_MSVC 0
#endif

// Clang
#if (defined(__clang__) && (__clang__ == 1))
#define COMPILER_CLANG 1
#else
#define COMPILER_CLANG 0
#endif

#endif