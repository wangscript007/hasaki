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
    //
    BlockingQueue() : cap__(std::numeric_limits<int>::max()) {}

    //
    explicit BlockingQueue(int cap) : cap__(cap) {}

    //
    std::size_t Capacity() const { return cap__; }

    //
    std::size_t Size();

    //
    void Put(const Tp &t);

    //
    Tp Take();

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

}  // namespace base
}  // namespace hasaki

#endif