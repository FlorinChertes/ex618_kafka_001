#pragma once

#include "background_worker.h"

#include "th_s_queue.h"
#include "kafka_consumer.h"

#include "background_worker.h"
#include "th_s_queue.h"

#include <thread>
#include <chrono>

#include <string>
#include <fstream>
#include <iostream>
#include <cassert>

class From_kafka_reader
{
    ThreadSafeQueue<std::string> queue_;
    BackgroundWorker<Kafka_consumer_receive, ThreadSafeQueue<std::string>> worker_;

public:

    From_kafka_reader()
        : queue_ {}
        , worker_{ Kafka_consumer_receive {}, queue_ }
    {}

    void receive() const
    {
        kafka_consumer_receive();
    }

    void receive([[maybe_unused]] int i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "start receive" << std::endl;

        while (true) {
            const auto& line = queue_.pop();
            std::cout << "Consuming: " << line << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    }
};