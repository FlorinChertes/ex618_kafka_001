#pragma once

#include <thread>
#include <chrono>

#include <string>
#include <fstream>
#include <iostream>
#include <cassert>

class From_kafka_reader
{
public:
    void receive() const
    {
        kafka_consumer_receive();
    }
};
