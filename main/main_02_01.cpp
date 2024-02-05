#include "kafka_consumer.h"

#include <vector>
#include <string>

#include <iostream>
#include <cassert>

int main ([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
	std::cout << "kafka consumer" << std::endl;

	kafka_consumer_receive();

	return 0;
}
