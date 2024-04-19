from enum import Enum
from basic_board import BasicBoard, RoundState
from manager import (group_manager, character_manager) # a dict, from ID to object
from effect import (Effect, Counter, CounterType)
from buff import (Buff, BuffType)

# 此文件定义花色及其效果

def get_current_group(board: BasicBoard): # -> Group
    # 获取当前的group
    return group_manager[board.groups_IDs[board.current_group_ID_index]]

def get_current_character(group): # (: Group) -> Group
    # 获取当前的character
    return character_manager[group.character_IDs[group.current_character_ID_index]]

def club_effect_function(board: BasicBoard) -> BasicBoard:
    # 梅花的效果：向棋盘上的伤害列表中添加一次等同于此次出牌点数之和的伤害
    board.damage_list.append(board.settle_rank_sum)
    return board

def diamond_effect_function(board: BasicBoard) -> BasicBoard:
    # 方片的效果：当前group从当前角色开始抽等同于此次出牌点数之和张牌
    get_current_group().draw(board.settle_rank_sum)
    return board

def heart_effect_function(board: BasicBoard) -> BasicBoard:
    # 红桃的效果：洗混棋盘堆，并从中取等同于此次出牌点数之和张牌置入当前group抽牌堆的底部
    get_current_group(board).discard_area.shuffle()
    get_current_character(get_current_group()).draw_pile.add_to_bottom(get_current_group(board).discard_area.remove(board.settle_rank_sum))
    return board

def spade_buff_function(rank_sum: int):
    # 黑桃buff的效果：向当前角色的攻击区增加一个debuff
    def real_buff_function(character_state):
        character_state.ATK_buff -= rank_sum
        return character_state

    return real_buff_function

def spade_effect_function(board: BasicBoard) -> BasicBoard:
    # 黑桃的效果：向当前所有目标的攻击区增加一个黑桃buff
    for character_ID in board.targets_list:
        character_manager(character_ID).buffs.append(Buff(buff_type=BuffType.ATKDebuff, function=spade_buff_function(board.settle_rank_sum), counter=Counter(counter_type=CounterType.ParamentCounter, remaining=1, count_down_when=RoundState.ATKBuffUpdate)))    
    return board

club_effect = Effect(function=club_effect_function, name="Club Effect Function")
club_effect.set_counter(counter=Counter(counter_type=CounterType.TimeBasedCounter, remaining=1, count_down_when=RoundState.Time))

diamond_effect = Effect(function=diamond_effect_function, name="Diamond Effect Function")
diamond_effect.set_counter(counter=Counter(counter_type=CounterType.TimeBasedCounter, remaining=1, count_down_when=RoundState.Time))

heart_effect = Effect(function=heart_effect_function, name="Heart Effect Function")
heart_effect.set_order(order=1) # 红桃先于方片
heart_effect.set_counter(counter=Counter(counter_type=CounterType.TimeBasedCounter, remaining=1, count_down_when=RoundState.Time))


spade_effect = Effect(function=spade_effect_function, name="Spade Effect Function")
spade_effect.set_counter(counter=Counter(counter_type=CounterType.TimeBasedCounter, remaining=1, count_down_when=RoundState.Time))

class Suit(Enum):
    Club = club_effect,
    Diamond = diamond_effect,
    Heart = heart_effect,
    Spade = spade_effect,