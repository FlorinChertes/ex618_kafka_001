#pragma once

#include <string>
#include <iostream>
#include <cassert>

template <typename T>
concept BasicSender = requires(T bs) {
    bs.send();
};

template <BasicSender Sender>
class Application_g
{
    Sender& sender_;
public:
    explicit Application_g(Sender& sender)
        : sender_{ sender }
    {
    }
    void Process() const
    {
        sender_.send();
    }

    void Process([[maybe_unused]] int i) const
    {
        for (std::string line; std::getline(std::cin, line);)
        {
            sender_.send(line);
        }
    }
};


