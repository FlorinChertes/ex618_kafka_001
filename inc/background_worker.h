
#include "kafka_consumer.h"

#include "th_s_queue.h"

#include <iostream>
#include <thread>
#include <chrono>

class BackgroundWorker {
public:
    BackgroundWorker(ThreadSafeQueue<std::string>& queue)
        : stopSignal(false)
        , queue_(queue)
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

    ThreadSafeQueue<std::string>& queue_;

    void workerFunction() {
        while (!stopSignal) {
            std::cout << "Working..." << std::endl;

            kafka_consumer_receive(queue_);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "Worker thread stopping." << std::endl;
    }
};
