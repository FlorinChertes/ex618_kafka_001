#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <cassert>

class In_file_writer
{
public:
	void send() const
	{
        const std::string filename = "message_box.txt";

        for (std::string line; std::getline(std::cin, line);)
        {
            std::cout << line.c_str() << '\n';

            std::ofstream fileStream(filename);
            if (fileStream.is_open())
            {
                fileStream << line << std::endl;
            }
            else
            {
                std::cerr << "Unable to open file for writing." << std::endl; // Error handling
            }
        }
	}
};
