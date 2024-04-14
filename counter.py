from enum import Enum
from basic_board import RoundState

# 此文件定义用于效果和buff的counter类

class CounterType(Enum):
    TimeBasedCounter = 0 # 按次计数
    RoundBasedCounter = 1 # 按回合计数
    ParamentCounter = 2 # 永久生效

class Counter:
    def __init__(self, *, counter_type: CounterType, remaining: int, count_down_when: RoundState):
        self.counter_type = counter_type
        self.remaining = max(0, remaining)
        self.count_down_when = count_down_when

    def count_down(self, *, round_state = RoundState) -> bool:
        if round_state == self.count_down_when:
            if self.remaining >= 2:
                self.remaining -= 1
                return True
            else:
                self.remaining -= 1
                return False
            
        return True
