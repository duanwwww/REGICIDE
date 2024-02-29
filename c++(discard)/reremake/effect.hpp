#pragma once
#include "board_area.hpp"
#include <functional>
enum CounterType{
    Parmenent = 0,// 怎么拼qwq
    RoundSelf,
    Times,
};

class Effect{
    std::function<void(BoardArea*)> f;
    std::string type;
    CounterType counter_type;
    int num;
public:
    virtual void act() = 0;
};