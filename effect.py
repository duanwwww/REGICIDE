from counter import (Counter, CounterType)
from basic_board import BasicBoard, RoundState

# 此文件定义Effect类

class Effect:
    def __init__(self, *, function: function, name: str):
        self.function = function
        self.name = name
        self.order = 0
        self.counter = None
        self.abandoned = True
    
    def set_order(self, *, order: int):
        # order用于决定Effect之间的执行顺序
        self.order = order

    def set_counter(self, *, counter: Counter):
        self.counter = counter
        self.abandoned = (self.counter.remaining > 0)

    def activate(self, *, board: BasicBoard) -> BasicBoard:
        # 激活自身的效果，Time计数器会在激活的时候自动消耗次数
        if (self.function is not None) and (self.counter is not None):
            if self.counter.counter_type == CounterType.TimeBasedCounter:
                if not self.abandoned:
                    self.abandoned = not self.counter.count_down(RoundState.Time)
                    return self.function(board)
            elif not self.abandoned:
                return self.function(board)
        return board
    
    def count_down(self, *, round_state: RoundState):
        # 如果没有剩余次数，将abandon设置为True
        if self.counter is not None:
            self.abandoned = not self.counter.count_down(round_state=round_state)
        else:
            self.abandoned = True