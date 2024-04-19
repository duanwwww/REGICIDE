from card import Card, CardType
from typing import List
from random import shuffle
from manager import card_manager

# 此文件定义套牌类Deck, 牌堆类Pile

class Deck:
    def __init__(self, *, card_IDs: List[int], name: str):
        self.card_IDs = card_IDs
        self.name = name

    def add_card(self, *, card_id: int):
        # 添加一张牌
        self.card_IDs.append(card_id)

    def remove_card(self, *, card_id: int):
        # 去除一张牌
        self.card_IDs.remove(card_id)

    def create_draw_deck(self, *, max_card_num):
        # 创建牌堆
        return Pile(card_IDs=self.card_IDs, max_card_num=max_card_num)
    
    def __str__(self) -> str:
        return "\n\
                [Deck] | name: {name} \n\
                [Deck] | card_ids: {my_card_ids} \n".format(
                    name = self.name,
                    my_card_ids = self.card_IDs
                )

class Pile:
    def __init__(self, *, card_IDs: List[int], max_card_num: int):
        assert len(card_IDs) <= max_card_num # 当前张数不得超过最大张数
        self.card_IDs = card_IDs
        self.max_card_num = max_card_num
        self.card_list, self.draw_at_start = self.reset()
        self.card_num = len(card_IDs) - len(self.draw_at_start)

    def reset(self):
        # 重置牌堆，返回洗混后的牌堆列表和对战开始时抽到手里的牌
        self.card_list = []
        top_cards = [card_manager[id] for id in self.card_IDs if card_manager[id].type == CardType.Top]
        shuffle(top_cards)
        self.card_list += top_cards
        middle_cards = [card_manager[id] for id in self.card_IDs if card_manager[id].type == CardType.Middle]
        shuffle(middle_cards)
        self.card_list += middle_cards
        bottom_cards = [card_manager[id] for id in self.card_IDs if card_manager[id].type == CardType.Bottom]
        shuffle(bottom_cards)
        self.card_list += bottom_cards
        return self.card_list, [card_manager[id] for id in self.card_IDs if card_manager[id].type == CardType.DrawAtStart]
        
    def add_to_top(self, *, cards: List[Card]) -> bool:
        # 在牌堆顶添加
        if len(cards) > self.max_card_num - self.card_num:
            return False
        self.card_list = cards + self.card_list
        self.card_num += len(cards)
        return True
    
    def add_to_bottom(self, *, cards: List[Card]) -> bool:
        # 在牌堆底添加
        if len(cards) > self.max_card_num - self.card_num:
            return False
        self.card_list =self.card_list + cards 
        self.card_num += len(cards)
        return True

    def remove(self, *, number: int) -> List[int]:
        # 移除最前面的一定张数
        if len(self.card_list) < number:
            return []
        tmp = self.card_list[:number]
        self.card_list = self.card_list[number:]
        self.card_num -= number
        return tmp
    
    def draw(self) -> Card: # | None
        # 抽一张牌
        if self.card_num > 0:
            card = self.card_list[0]
            self.card_list = self.card_list[1:]
            self.card_num -= 1
            return card
        return None
    
    def __str__(self) -> str:
        return "\n\
                [Pile] | num: {num} / {max_num} \n\
                [Pile] | card list: {card_list} \n".format(
                    num = self.card_num,
                    max_num = self.max_card_num,
                    card_list = str([str(x) for x in self.card_list]).replace('\\n', '\n')
                )