from enum import Enum
from counter import Counter, CounterType
from basic_board import RoundState
from types import FunctionType as function

# 此文件定义Buff类，与Effect类类似

class BuffType(Enum):
    ATKBuff = 0
    ATKDebuff = 1
    DEFBuff = 2
    DEFDebuff = 3
    OtherBuff = 4
    OtherDebuff = 5

class Buff:
    def __init__(self, *, type: BuffType, function: function, counter: Counter, name: str):
        self.type = type
        self.function = function
        self.counter = counter
        self.is_abandon = (counter.remaining > 0)
        self.name = name

    def activate(self, *, character_state):
        if (self.function is not None) and (self.counter is not None):
            if self.counter.counter_type == CounterType.TimeBasedCounter:
                if not self.is_abandon:
                    self.is_abandon = not self.counter.count_down(RoundState.Time)
                    return self.function(character_state)
            elif not self.is_abandon:
                return self.function(character_state)
        return character_state
    
    def count_down(self, *, round_state: RoundState):
        if self.counter is not None:
            self.is_abandon = not self.counter.count_down(round_state=round_state)
        else:
            self.is_abandon = True

    def __str__(self) -> str:
        return "\n\
                [Buff] | name: {name} \n\
                [Buff] | type: {type} \n\
                [Buff] | counter: {counter} \n\
                [Buff] | is_abandon: {is_abandon}".format(
                    name = self.name,
                    type = self.type,
                    counter = str(self.counter),
                    is_abandon = self.is_abandon
                )