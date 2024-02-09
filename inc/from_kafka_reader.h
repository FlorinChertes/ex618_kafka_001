#pragma once

#include "kafka_consumer.h"

#include "background_worker.h"
#include "th_s_queue.h"

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
    From_kafka_reader();

    void receive() const;
    std::string receive([[maybe_unused]] int i);
};
