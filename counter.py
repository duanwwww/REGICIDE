from enum import Enum

class CounterType(Enum):
    TimeBasedCounter = 0
    RoundBasedCounter = 1
    ParamentCounter = 2

class Counter:
    def __init__(self, *, counter_type: CounterType, remaining: int):
        self.counter_type = counter_type
        self.remaining = max(0, remaining)

    def count_down(self) -> bool:
        if self.remaining >= 2:
            self.remaining -= 1
            return True
        else:
            return False

if __name__ == "__main__":
    c = Counter(counter_type= CounterType.TimeBasedCounter, remaining= 20)
    print(c.counter_type == CounterType.RoundBasedCounter)
    print(c.counter_type())
