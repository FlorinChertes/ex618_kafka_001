#include "application_c.h"

#include "from_file_reader.h"
#include "from_kafka_reader.h"

#include <string>
#include <iostream>
#include <cassert>

#define KAFKA

int main ([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
	std::cout << "c_receiver" << std::endl;

#ifdef KAFKA
	From_kafka_reader receiver{};
#else
	From_file_reader receiver{};
#endif

	Application_c application_c{ receiver };
	application_c.Process(1);

	return 0;
}




