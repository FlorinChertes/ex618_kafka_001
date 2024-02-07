#pragma once

#include <string>

template<typename Type>
class ThreadSafeQueue;

void kafka_consumer_receive();
void kafka_consumer_receive(ThreadSafeQueue<std::string>& queue);
