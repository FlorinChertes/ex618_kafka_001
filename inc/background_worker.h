#pragma once

#include "collable_class.h"

#include <iostream>
#include <thread>
#include <chrono>

template <typename T>
concept CollableType = requires(T collable) {
    collable.invoke();
};

template <CollableType T>
class BackgroundWorker {
public:
    explicit BackgroundWorker(T& callable)
        : callable_{ callable }
        , worker_thread_ { std::jthread(&BackgroundWorker::workerFunction, this) } {
    }

    BackgroundWorker(const BackgroundWorker&) = delete;
    BackgroundWorker& operator=(const BackgroundWorker&) = delete;

private:
    T& callable_;
    std::jthread worker_thread_;

    void workerFunction() {
        std::cout << "Working..." << std::endl;
        callable_.invoke();
        std::cout << "Worker thread stopping." << std::endl;
    }
};
