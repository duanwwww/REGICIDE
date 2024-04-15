from enum import Enum
from basic_board import RoundState, BasicBoard

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

class SkillCounter:
    def __init__(self, *, counter_type: CounterType, cd: int, start_cd: int = 0, max_available: int = 1, start_available:int = 0):
        self.counter_type = counter_type
        self.max_cd = cd
        self.current_cd = start_cd
        self.max_available = max_available
        self.current_available = start_available
        self.is_available = self.current_available > 0
        self.calc_function = None

    def set_calc_function(self, *, function: function):
        self.calc_function = function
    
    def calc_cd(self, *, board: BasicBoard):
        if self.counter_type == CounterType.RoundBasedCounter:
            self.current_cd += 1
        elif self.counter_type == CounterType.RoundBasedCounter:
            if self.calc_function is None:
                return
            self.current_cd += self.calc_function(board)
        elif self.counter_type == CounterType.ParamentCounter:
            self.current_available = 1
        while self.current_cd >= self.max_cd and self.current_available < self.max_available:
            self.current_available += 1
            self.current_cd -= self.max_cd
        if self.current_cd > self.max_cd:
            self.current_cd = self.max_cd
        self.is_available = self.current_available > 0

    def use_skill(self):
        if not self.is_available:
            return False
        if self.counter_type != CounterType.ParamentCounter:
            self.current_available -= 1
            if self.current_cd >= self.max_cd:
                self.current_cd -= self.max_cd
                self.current_available += 1
            self.is_available = self.current_available > 0
        return True