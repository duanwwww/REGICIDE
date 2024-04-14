from enum import Enum
from counter import Counter, CounterType
from basic_board import RoundState

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
        self.abandoned = (counter.remaining > 0)

    def activate(self, *, character_state):
        if (self.function is not None) and (self.counter is not None):
            if self.counter.counter_type == CounterType.TimeBasedCounter:
                if not self.abandoned:
                    self.abandoned = not self.counter.count_down(RoundState.Time)
                    return self.function(character_state)
            elif not self.abandoned:
                return self.function(character_state)
        return character_state
    
    def count_down(self, *, round_state: RoundState):
        if self.counter is not None:
            self.abandoned = not self.counter.count_down(round_state=round_state)
        else:
            self.abandoned = True