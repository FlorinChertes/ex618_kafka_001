#pragma once

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

    CollableClass<
          Kafka_consumer_receive
        , ThreadSafeQueue<std::string>> callable_;

    BackgroundWorker<
        CollableClass<
          Kafka_consumer_receive
        , ThreadSafeQueue<std::string>>
        > worker_;

public:

    From_kafka_reader()
        : queue_ {}
        , callable_{ Kafka_consumer_receive{}, queue_ }
        , worker_{ callable_ }
    {}

    void receive() const
    {
        kafka_consumer_receive();
    }

    [[noreturn]] void receive([[maybe_unused]] int i)
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
