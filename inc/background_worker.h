#pragma once

#include "collable_class.h"

#include <iostream>
#include <thread>
#include <chrono>

template <CollableType T>
class BackgroundWorker {
public:
    explicit BackgroundWorker(T& callable)
        : callable_{ callable }
    {
        // Start the worker thread in the constructor
        workerThread = std::jthread(&BackgroundWorker::workerFunction, this);
    }

    BackgroundWorker(const BackgroundWorker&) = delete;
    BackgroundWorker& operator=(const BackgroundWorker&) = delete;

private:
    std::jthread workerThread;
    T& callable_;

    void workerFunction() {
        std::cout << "Working..." << std::endl;
        callable_.invoke();
        std::cout << "Worker thread stopping." << std::endl;
    }
};
