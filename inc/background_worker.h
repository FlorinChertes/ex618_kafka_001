#pragma once

#include <iostream>
#include <thread>
#include <chrono>

template <typename CollableT, typename QueueT>
class BackgroundWorker {
public:
    BackgroundWorker(CollableT func, QueueT& queue)
        : stopSignal{ false }
        , func_ { func }
        , queue_{ queue }
    {
        // Start the worker thread in the constructor
        workerThread = std::thread(&BackgroundWorker::workerFunction, this);
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
    std::thread workerThread;
    volatile bool stopSignal;

    CollableT& func_;
    QueueT& queue_;

    void workerFunction() {
        while (!stopSignal) {
            std::cout << "Working..." << std::endl;

            func_(queue_);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "Worker thread stopping." << std::endl;
    }
};
