#pragma once

#include "kafka_producer.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cassert>

class In_kafka_writer
{
public:
	void send() const
	{
		kafka_producer_send();
	}

	void send(const std::string& line) const
	{
		kafka_producer_send(line);
	}
};
