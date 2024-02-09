#pragma once

template<typename F, typename Arg>
class CollableClass
{
    F func_;
    Arg& arg_;

public:
    // Constructor to initialize the function object and arguments
    CollableClass(F&& func, Arg& arg)
        : func_{ std::move(func) }
        , arg_{ arg }
    {}

    void invoke()
    {
        func_(arg_);
    }
};
