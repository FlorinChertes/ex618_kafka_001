#pragma once

#include <string>
#include <iostream>
#include <cassert>

template <typename T>
concept BasicReceiver = requires(T br) {
    br.receive();
};

template <BasicReceiver Receiver>
class Application_c
{
    Receiver& receiver_;
public:
    explicit Application_c(Receiver& receiver)
        : receiver_{ receiver }
    {
    }

    void Process() const
    {
        receiver_.receive();
    }

    void Process(int i) const
    {
        std::cout << "start receive" << std::endl;
        while (true)
        {
            auto&& line{ receiver_.receive(i) };
            std::cout << "Consuming: " << line << std::endl;
        }
        receiver_.receive(i);
    }
};


