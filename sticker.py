from enum import Enum
import group
from basicboard import BasicBoard


def club_effect():
    club_damage = 0
    for card in BasicBoard.settle_area:
        club_damage += card.rank
    BasicBoard.damage_list.append(club_damage)

def diamond_effect():
    diamond_draw = 0
    for card in BasicBoard.settle_area:
        diamond_draw += card.rank
    for test_group in BasicBoard.groups:
        if test_group.group_ID == BasicBoard.current_group_ID:
            test_group.draw(diamond_draw)

def heart_effect():
    heart_reshuffle = 0
    for card in BasicBoard.settle_area:
        heart_reshuffle += card.rank
    for test_group in BasicBoard.groups:
        if test_group.group_ID == BasicBoard.current_group_ID:
            test_group.discard_area.shuffle()
            cards_reshuffle = []
            for i in range (heart_reshuffle):
                cards_reshuffle.append(discard_area.draw())
            test_group.add_to_bottom(cards_reshuffle)

def spade_effect():
    spade_atk_num = 0
    for card in BasicBoard.settle_area:
        spade_atk_num += card.rank
        for buffnum in range(len(BasicBoard.target.buffes)):
            if BasicBoard.target.buffes[buffnum][0] == "spade_atk":
                BasicBoard.target.buffes[buffnum] += spade_atk_num



class Suit(Enum):
    def __init__(self):
        Club = club_effect


