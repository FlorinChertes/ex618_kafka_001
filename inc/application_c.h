#pragma once
//#include "from_file_reader.h"

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
    Receiver& receiver;
public:
    explicit Application_c(Receiver& receiver_)
        : receiver{ receiver_ }
    {
    }

    void Process() const
    {
        receiver.receive();
    }
};


