from typing import List
from enum import Enum
from manager import group_manager, character_manager

# 此文件定义基本棋盘类BasicBoard

class RoundState(Enum):
    Time = 0
    RoundStart = 1
    DEFBuffUpdate = 2
    UseSkill = 3
    UseCard = 4
    CalcEffect = 5
    CalcDamage = 6
    DealDamage = 7
    JudgeSurive = 8
    JudgeWinning = 9
    ATKBuffUpdate = 10
    SwitchPlayer = 11
    RoundEnd = 12

    def next_state(self):
        if self.value == 0:
            return RoundState.Time
        next_index = next_index = (self.value + 1) % (len(RoundState) - 1) + 1
        return RoundState(next_index)

class BoardFacade:
    pass

class BasicBoard:
    def __init__(self, *, group_IDs: List[int], current_round: int = 0, current_state: RoundState, next_state: RoundState, board_facade: BoardFacade):
        self.group_IDs = group_IDs
        self.current_group_ID_index = 0
        self.current_round = current_round
        self.current_state = current_state
        self.next_state = next_state
        self.board_facade = board_facade
        self.settle_area = []
        self.settle_rank_sum = 0
        self.damage_list = []
        self.effect_target = None
        self.whom_to_be_settle_list = []
    
    def next_state(self):
        self.current_state = self.next_state
        self.next_state = self.next_state.next_state()

    def select_main_player(self, *, group_ID, character_id):
        main_player = character_manager[group_manager[self.group_IDs[0]].character_IDs[0]]
        if group_ID in self.group_IDs:
            if character_id in group_manager[group_ID].character_IDs:
                main_player = character_manager[character_id]
        main_player.set_round_counter()

    def __str__(self) -> str:
        return "\n\
                [BasicBoard] | group_ids: {my_group_ids} \n\
                [BasicBoard] | current group id: {current_group_id} \n\
                [BasicBoard] | round: No.{round_num} \n\
                [BasicBoard] | state: {current_state} \n\
                [BasicBoard] | settle area: {settle_area} \n\
                [BasicBoard] | settle sum: {rank_sum} \n\
                [BasicBoard] | damage list: {damage_list} \n\
                [BasicBoard] | target: {target} \n\
                [BasicBoard] | whom to be settle list: {settle_list} \n".format(
                    my_group_ids = str([str(x) for x in self.group_IDs]).replace('\\n', '\n'),
                    current_group_id = self.group_IDs[self.current_group_ID_index],
                    round_num = self.current_round,
                    current_state = self.current_state,
                    settle_area = str(self.settle_area),
                    rank_sum = self.settle_rank_sum,
                    damage_list = str(self.damage_list),
                    target = str(self.effect_target),
                    settle_list = str([str(x) for x in self.whom_to_be_settle_list]).replace('\\n', '\n')
                )   