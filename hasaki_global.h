#ifndef __HASAKI_GLOBAL_H__
#define __HASAKI_GLOBAL_H__

#include <cstdio>
#include <cstdlib>

#define HASAKI_PANIC(...)                                                              \
    do {                                                                               \
        fprintf(stderr, __VAR_ARGS__);                                                 \
        abort();                                                                       \
    } while (0)

#define hasaki_nop() asm volatile("nop");

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

#endif