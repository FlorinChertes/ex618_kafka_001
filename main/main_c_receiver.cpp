#include "application_c.h"

#define KAFKA

#ifdef KAFKA
#include "from_kafka_reader.h"
#else
#include "from_file_reader.h"
#endif

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




