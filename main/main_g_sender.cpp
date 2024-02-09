#include "application_g.h"

#define KAFKA

#ifdef KAFKA
#include "in_kafka_writer.h"
#else
#include "in_file_writer.h"
#endif

int main ([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
	std::cout << "g_sender" << std::endl;

#ifdef KAFKA
	In_kafka_writer sender{ };
#else
	In_file_writer sender{ };
#endif

	Application_g application_g{ sender };
	application_g.Process(1);

	return 0;
}
