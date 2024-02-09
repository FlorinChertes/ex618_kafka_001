#pragma once

template<typename F, typename... Args>
class CollableClass
{
    F func_;
    std::tuple<Args&...> args_;

public:
    // Constructor to initialize the function object and arguments
    CollableClass(F&& func, Args&... args)
        : func_{ std::move(func) }
        , args_{ std::forward<Args&>(args)... }
    {}

    void invoke()
    {
        apply(func_, args_);
    }

private:
    // Helper function to invoke the function object with arguments from a tuple
    template<typename Function, typename Tuple, size_t... Index>
    void apply_impl(Function&& func, Tuple&& tuple, std::index_sequence<Index...>) {
        func(std::get<Index>(std::forward<Tuple>(tuple))...);
    }

    template<typename Function, typename Tuple>
    void apply(Function&& func, Tuple&& tuple) {
        constexpr size_t size = std::tuple_size<std::remove_reference_t<Tuple>>::value;
        apply_impl(std::forward<Function>(func), std::forward<Tuple>(tuple), std::make_index_sequence<size>{});
    }
};
