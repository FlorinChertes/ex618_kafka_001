#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>

template <typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    mutable std::mutex mutex;
    std::condition_variable condVar;

public:
    ThreadSafeQueue() = default;

    void push(T value) {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(std::move(value));
        condVar.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mutex);
        condVar.wait(lock, [this]{ return !queue.empty(); });
        T value = std::move(queue.front());
        queue.pop();
        return value;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }
};
