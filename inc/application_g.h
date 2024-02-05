#pragma once
//#include "in_file_writer.h"

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
    Sender& sender;
public:
    explicit Application_g(Sender& sender_)
        : sender{ sender_ }
    {
    }
    void Process() const
    {
        sender.send();
    }
};


