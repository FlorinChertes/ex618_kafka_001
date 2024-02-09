
#include "in_kafka_writer.h"

#include "kafka_producer.h"


void In_kafka_writer::send() const
{
	kafka_producer_send();
}

void In_kafka_writer::send(const std::string& line) const
{
	kafka_producer_send(line);
}

