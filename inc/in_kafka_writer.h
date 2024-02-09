#pragma once

#include <string>

class In_kafka_writer
{
public:
	void send() const;
	void send(const std::string& line) const;
};
