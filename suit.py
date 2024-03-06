from enum import Enum
from basicboard import BasicBoard
from manager import (group_manager, character_manager) # a dict, from ID to object
from effect import (Effect, Counter, CounterType)
from buff import (Buff, BuffType)

def get_current_group(board: BasicBoard): # -> Group
    return group_manager[board.groups_IDs[board.current_group_ID_index]]

def get_current_character(group): # (: Group) -> Group
    return character_manager[group.character_IDs[group.current_character_ID_index]]

def club_effect_function(board: BasicBoard) -> BasicBoard:
    board.damage_list.append(board.settle_rank_sum)
    return board

def diamond_effect_function(board: BasicBoard) -> BasicBoard:
    get_current_group().draw(board.settle_rank_sum)
    return board

def heart_effect_function(board: BasicBoard) -> BasicBoard:
    get_current_group(board).discard_area.shuffle()
    get_current_character(get_current_group()).draw_pile.add_to_bottom(get_current_group(board).discard_area.remove(board.settle_rank_sum))
    return board

def spade_buff_function(rank_sum: int):
    def real_buff_function(character_state):
        character_state.ATK_buff -= rank_sum
        return character_state

    return real_buff_function

def spade_effect_function(board: BasicBoard) -> BasicBoard:
    for character_ID in board.targets_list:
        character_manager(character_ID).buffs.append(Buff(buff_type=BuffType.AtkDebuff, function=spade_buff_function(board.settle_rank_sum), counter=Counter(counter_type=CounterType.ParamentCounter, remaining=1)))    


club_effect = Effect(function=club_effect_function, name="Club Effect Function")

diamond_effect = Effect(function=diamond_effect_function, name="Diamond Effect Function")

heart_effect = Effect(function=heart_effect_function, name="Heart Effect Function")

spade_effect = Effect(function=spade_effect_function, name="Spade Effect Function")

class Suit(Enum):
    Club = club_effect,
    Diamond = diamond_effect,
    Heart = heart_effect,
    Spade = spade_effect,