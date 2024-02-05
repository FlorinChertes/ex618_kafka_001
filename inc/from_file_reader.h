#pragma once

#include "kafka_consumer.h"

#include <thread>
#include <chrono>

#include <string>
#include <fstream>
#include <iostream>
#include <cassert>

class From_file_reader
{
public:
    void receive() const
    {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));

            const std::string filename = "message_box.txt";
            std::ifstream fileStream(filename);

            if (fileStream.is_open())
            {
                std::string line;
                while (getline(fileStream, line)) { // Read the file line by line
                    std::cout << line << std::endl; // Print each line to the console
                }
            }
            else {
                std::cerr << "Unable to open file for reading." << std::endl; // Error handling
            }
        }
    }
};
