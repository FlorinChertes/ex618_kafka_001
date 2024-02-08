#pragma once

#include <string>

template<typename Type>
class ThreadSafeQueue;

void kafka_consumer_receive();
void kafka_consumer_receive(ThreadSafeQueue<std::string>& queue);

struct Kafka_consumer_receive
{
	void operator()(ThreadSafeQueue<std::string>& queue) const
	{
		kafka_consumer_receive(queue);
	}
};
