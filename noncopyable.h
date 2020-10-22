#ifndef __HASAKI_NONCOPYABLE_H__
#define __HASAKI_NONCOPYABLE_H__

///
/// hasaki::base::noncopyable likes boost::noncopyable.
///
namespace hasaki {
namespace base {

class noncopyable {
public:
// constructor and destrutor
#if __cplusplus < 201103L
    noncopyable() {}
    ~noncopyable() {}
#else
    constexpr noncopyable() = default;
    ~noncopyable() = default;
#endif

// disable copy and assign
#if __cplusplus < 201103L
private:
    noncopyable(const noncopyable &);
    noncopyable &operator=(const noncopyable &);
#else
    noncopyable(const noncopyable &) = delete;
    noncopyable &operator=(const noncopyable &) = delete;
#endif
};

}  // namespace  base
typedef base::noncopyable noncopyable;
}  // namespace hasaki

#endif