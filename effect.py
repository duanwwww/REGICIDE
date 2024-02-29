from counter import (Counter, CounterType)
class BasicBoard:
    pass
class Effect:
    def __init__(self, *, function: function, name: str):
        self.function = function
        self.name = name
        self.order = 0
        self.counter = None
    
    def set_order(self, *, order: int):
        self.order = order

    def set_counter(self, *, counter: Counter):
        self.counter = counter

    def activate(self, *, Board: BasicBoard) -> BasicBoard:
        if self.function is not None:
            return self.function(Board)
        else:
            return Board
    
    def count_down(self) -> bool:
        if self.counter is not None:
            return self.counter.count_down()
        else:
            return False