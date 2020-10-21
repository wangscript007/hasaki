#ifndef __HASAKI_NONCOPYABLE_H__
#define __HASAKI_NONCOPYABLE_H__

///
/// hasaki::base::noncopyable likes boost::noncopyable.
/// 
namespace hasaki
{
    namespace base
    {
        class noncopyable
        {
            #if __cplusplus < 201103L
            private:
                noncopyable(const noncopyable &);
                noncopyable& operator=(const noncopyable&);
            #else
                noncopyable() = delete;
                noncopyable& operator=(const noncopyable &) = delete;
            #endif
        };

    } // namespace  base
} // namespace hasaki

#endif