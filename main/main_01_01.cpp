#include "kafka_producer.h"

#include <vector>
#include <string>

#include <iostream>
#include <cassert>

int main ([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
	std::cout << "kafka producer" << std::endl;

	kafka_producer_send();

	return 0;
}
