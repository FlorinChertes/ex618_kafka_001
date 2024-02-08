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

    ~BackgroundWorker() {
        // Signal the worker thread to stop
        stopSignal = true;

        // Join the worker thread in the destructor to ensure it completes before the object is destroyed
        if (workerThread.joinable()) {
            workerThread.join();
        }
    }

    // Deleted copy constructor and assignment operator to prevent copying
    BackgroundWorker(const BackgroundWorker&) = delete;
    BackgroundWorker& operator=(const BackgroundWorker&) = delete;

    // Optionally, define move constructor and assignment operator if needed

private:
    std::jthread workerThread;
    std::atomic_bool stopSignal {false};

    T& callable_;

    void workerFunction() {
        while (!stopSignal) {
            std::cout << "Working..." << std::endl;

            callable_.invoke();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "Worker thread stopping." << std::endl;
    }
};
