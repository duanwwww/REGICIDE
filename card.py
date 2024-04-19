from suit import Suit
from enum import Enum
from effect import Effect
from sticker import Sticker
from basic_board import BasicBoard

# 此文件定义Card类

class CardType(Enum):
    Top = 0
    Middle = 1
    Bottom = 2
    DrawAtStart = 3

class Card:
    def __init__(self, *, rank: int, card_ID: int, suit: Suit, type: CardType):
        self.rank = rank
        self.card_ID = card_ID
        self.suit = suit
        self.type = type
        self.sticker = None
        self.effect = Effect(function=None, name='Do nothing')
    
    def set_sticker(self, sticker: Sticker):
        self.sticker = sticker
        
    def set_effect(self, effect: Effect):
        self.effect = effect

    def set_type(self, type: CardType):
        self.type = type
    
    def activate_effect(self, board: BasicBoard) -> BasicBoard:
        # 触发卡牌的效果
        return self.effect.activate(board)
    
    def __str__(self) -> str:
        return "\n\
                [Card] | id: {id} \n\
                [Card] | suit: {suit} \n\
                [Card] | rank: {rank} \n\
                [Card] | sticker: {sticker} \n\
                [Card] | type: {type} \n".format(
                    id = self.card_ID,
                    suit = self.suit,
                    rank = self.rank,
                    sticker = self.sticker,
                    type = self.type
                )