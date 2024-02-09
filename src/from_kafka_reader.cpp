#include "from_kafka_reader.h"

From_kafka_reader::From_kafka_reader()
    : queue_{}
    , callable_{ Kafka_consumer_receive{}, queue_ }
    , worker_{ callable_ }
{}

void From_kafka_reader::receive() const
{
    kafka_consumer_receive();
}

std::string From_kafka_reader::receive([[maybe_unused]] int i)
{
    return queue_.pop();
}





