#pragma once

#include "collable_class.h"

#include <thread>

template <typename T>
concept CollableType = requires(T collable) {
    collable.invoke();
};

template <CollableType Collable>
class BackgroundWorker {
public:
    explicit BackgroundWorker(Collable& callable)
        : callable_{ callable }
        , worker_thread_ { std::jthread(&BackgroundWorker::workerFunction, this) } {
    }

    BackgroundWorker(const BackgroundWorker&) = delete;
    BackgroundWorker& operator=(const BackgroundWorker&) = delete;

private:
    Collable& callable_;
    std::jthread worker_thread_;

    void workerFunction() {
        std::cout << "Working..." << std::endl;
        callable_.invoke();
        std::cout << "Worker thread stopping." << std::endl;
    }
};
