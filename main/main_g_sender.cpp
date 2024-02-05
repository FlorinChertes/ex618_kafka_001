#include "application_g.h"

#include "in_file_writer.h"
#include "in_kafka_writer.h"

#include <string>
#include <iostream>
#include <cassert>

#define KAFKA

int main ([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
	std::cout << "g_sender" << std::endl;

#ifdef KAFKA
	In_kafka_writer sender{ };
#else
	In_file_writer sender{ };
#endif

	Application_g application_g{ sender };
	application_g.Process();

	return 0;
}
