#ifndef __HASAKI_BLOCKING_QUEUE_H__
#define __HASAKI_BLOCKING_QUEUE_H__

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <type_traits>

namespace hasaki {
namespace base {

template <typename Tp, typename Alloc = std::allocator<Tp> /*FOR CXX03 ERROR*/>
class BlockingQueue {
public:
    /// <summary>
    /// Construct a BlockingQueue with a default capacity.
    /// Default capacity is `std::numeric_limits<int>::max()`
    ///  You'd better to construct a blocking queue with a suitable capacity.
    /// </summary>
    /// <returns></returns>
    BlockingQueue() : cap__(std::numeric_limits<int>::max()) {}

    /// <summary>
    ///  Construct a BlockingQueue with a given capactity.
    /// </summary>
    /// <param name="cap">the capactity of this blocking queue.</param>
    /// <returns></returns>
    explicit BlockingQueue(int cap) : cap__(cap) {}

    /// <summary>
    ///  Get the capactity of this queue.
    /// </summary>
    /// <returns>the capactity.</returns>
    std::size_t Capacity() const { return cap__; }

    /// <summary>
    ///  Get the current size of this queue.
    /// </summary>
    /// <returns>current size.</returns>
    std::size_t Size();

    /// <summary>
    /// Put a element to the queue.
    /// The put thread will be blocked if the queue has no capacity util
    /// a element taken by a consumer thread.
    /// </summary>
    /// <param name="t"></param>
    void Put(const Tp &t);

    /// <summary>
    ///  It's behavior likes Put(const Tp &t).
    /// </summary>
    /// <param name="t"></param>
    void Put(Tp &&t);

    /// <summary>
    /// Take a element from the queue.
    /// The take thread will be blocked if the queue has no element util
    /// a element was added to the queue by a producer thread.
    /// </summary>
    /// <returns></returns>
    Tp Take();

    /// <summary>
    /// Take a element in the given timeout.
    /// It will returns true if the a element was success taken in the given
    /// timeout and filled to the given pointer `Tp*`, or else return false.
    /// you should use it like:
    /// User user;
    /// if(queue.Take(&user, std::chrono::milliseconds(100))) {
    ///    // user is valid.
    /// }
    /// </summary>
    /// <typeparam name="_Rep"></typeparam>
    /// <typeparam name="_Period"></typeparam>
    /// <param name="pt"></param>
    /// <param name="timeout"></param>
    /// <returns></returns>
    template <typename _Rep, typename _Period>
    bool Take(Tp *pt, std::chrono::duration<_Rep, _Period> timeout);

private:
    std::queue<Tp, std::deque<Tp, Alloc> /*FOR CXX03 ERROR*/> queue__;
    std::mutex mtx__;
    std::condition_variable notFull__;
    std::condition_variable notEmpty__;
    const std::size_t cap__;
};

template <typename Tp, typename Alloc>
inline std::size_t BlockingQueue<Tp, Alloc>::Size() {
    std::unique_lock<std::mutex> lock(mtx__);
    return queue__.size();
}

template <typename Tp, typename Alloc>
inline void BlockingQueue<Tp, Alloc>::Put(const Tp &t) {
    std::unique_lock<std::mutex> lock(mtx__);
    while (queue__.size() >= cap__) {
        notFull__.wait(lock);
    }
    queue__.push(t);
    notEmpty__.notify_one();
}

template <typename Tp, typename Alloc>
inline void BlockingQueue<Tp, Alloc>::Put(Tp &&t) {
    std::unique_lock<std::mutex> lock(mtx__);
    while (queue__.size() >= cap__) {
        notFull__.wait(lock);
    }
    queue__.push(t);
    notEmpty__.notify_one();
}

template <typename Tp, typename Alloc>
inline Tp BlockingQueue<Tp, Alloc>::Take() {
    std::unique_lock<std::mutex> lock(mtx__);
    while (queue__.empty()) {
        notEmpty__.wait(lock);
    }
    Tp t = queue__.front();
    queue__.pop();
    notFull__.notify_one();
    return std::move(t);
}

template <typename Tp, typename Alloc>
template <typename _Rep, typename _Period>
inline bool BlockingQueue<Tp, Alloc>::Take(
    Tp *pt, std::chrono::duration<_Rep, _Period> timeout) {
    if (pt == nullptr) {
        return false;
    }
    std::unique_lock<std::mutex> lock(mtx__);
    if (queue__.empty()) {
        notEmpty__.wait_for(lock, timeout);
        if (queue__.empty()) {
            return false;
        }
    }
    *pt = queue__.front();
    queue__.pop();
    return true;
}

}  // namespace base
}  // namespace hasaki

#endif