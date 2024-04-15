from pile import Pile
from typing import List
from buff import Buff
import copy
from manager import group_manager, character_manager
from basic_board import BasicBoard
from effect import Effect

# 此文件定义角色阵营group类

class Group:
    def __init__(self, *, character_IDs: List[int], group_ID: int, group_buffes: List[Buff], discard_area: Pile, round_start_effects: List[Effect], judge_win_effects: List[Effect]):
        self.winning_mark = False
        self.character_IDs = character_IDs
        self.current_character_ID_index = 0
        self.group_ID = group_ID
        self.group_buffes = group_buffes
        self.discard_area = discard_area
        self.round_start_effects = round_start_effects
        self.judge_win_effects = judge_win_effects

    def add_buff(self, *, buff: Buff):
        self.group_buffes.append(buff)
    
    def clear_buff(self):
        self.group_buffes = [ available_buff for available_buff in self.group_buffes if not available_buff.abandoned ]

    def judge_win(self, *, board: BasicBoard) -> bool:
        for judger in self.judge_win_effects:
            board = judger.activate(board)
            if group_manager[self.group_ID].winnning_mark:
                return True
        return False
    
    def draw(self, *, num: int):
        current_draw_num = 0
        pass_num = 0
        drawer_index = copy.deepcopy(self.current_character_ID_index)
        while current_draw_num < num and pass_num < len(self.character_IDs):
            if character_manager[self.character_IDs[drawer_index]].draw():
                current_draw_num += 1
                pass_num = 0
            else:
                pass_num += 1
            drawer_index = (drawer_index + 1) % len(self.character_IDs)
