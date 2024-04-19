from basic_board import BasicBoard, RoundState
from typing import List
from effect import Effect
from buff import Buff
from pile import Pile
from card import Card
from counter import Counter, SkillCounter, CounterType
from types import FunctionType as function

class Skill:
    def __init__(self, *, effects: List[Effect], cd_counter: SkillCounter, select_target_function: function, skill_ID: int):
        self.effects = effects
        self.cd_counter = cd_counter
        self.select_target_funtion = select_target_function
        self.skill_ID = skill_ID

    def use_skill(self, *, board: BasicBoard):
        if not self.cd_counter.use_skill():
            return board
        else:
            for effect in self.effects:
                board = effect.activate(board=board)
            return board
        
    def update_counter(self, *, board: BasicBoard):
        self.cd_counter.calc_cd(board=board)

class CharacterState:
    def __init__(self, *, ATK_buff: int = 0, ATK_coefficient: int = 1, DEF_buff: int = 0, DEF_coefficient: int = 1):
        self.ATK_buff = ATK_buff
        self.ATK_coefficient = ATK_coefficient
        self.DEF_buff = DEF_buff
        self.DEF_coefficient = DEF_coefficient

def add_round_counter(board: BasicBoard):
    board.current_round += 1
    return board

class Character:
    def __init__(self, *, skills: List[Skill], current_skill_ID: int, name: str, character_ID: int, max_HP: int, current_HP: int, draw_pile: Pile, max_cards_in_hand: int, character_state: CharacterState, select_target_function: function, valid_play_judgers: List[function], judge_survival_effect: Effect, die_effect: Effect, switch_effect: Effect):
        self.skills = skills
        self.current_skill_ID = current_skill_ID
        self.name = name
        self.character_ID = character_ID
        self.max_HP = max_HP
        self.current_HP = current_HP
        self.buffes = []
        self.draw_pile = draw_pile
        self.max_cards_in_hand = max_cards_in_hand
        self.cards_in_hand = []
        self.character_state = character_state
        self.select_target_function = select_target_function
        self.valid_play_judgers = valid_play_judgers
        self.round_start_effects = []
        self.judge_survival_effect = judge_survival_effect
        self.die_effect = die_effect
        self.switch_effect = switch_effect

    def set_round_counter(self):
        update_effect = Effect(function=add_round_counter, name="round counter update effect")
        update_effect.set_counter(counter=Counter(counter_type=CounterType.ParamentCounter, remaining=1, count_down_when=RoundState.RoundStart))
        self.round_start_effects.append(update_effect)

    def draw(self) -> bool:
        if self.draw_pile is None:
            return False
        if len(self.cards_in_hand) >= self.max_cards_in_hand:
            return False
        card = self.draw_pile.draw()
        if card is None: 
            return False
        self.cards_in_hand.append(card)
        return True
    
    def judge_valid_play(self, *, cards: List[Card]):
        for judger in self.valid_play_judgers:
            if judger(cards):
                return True
        return False

    def play_cards(self, *, indexes: List[int], board: BasicBoard) -> bool:
        indexes.sort(reverse=True)
        cards = []
        for index in indexes:
            if index > len(self.cards_in_hand) or index < 0:
                return False
            cards.append(self.cards_in_hand[index])
        
        if not self.judge_valid_play(cards=cards):
            return False

        for index in indexes:
            self.cards_in_hand.pop(index)
        
        for card in cards:
            board.settle_area.append(card)
        
    def __str__(self) -> str:
        return "\n\
                [Character] | name: {name} \n\
                [Character] | id: {id} \n\
                [Character] | HP: {HP} / {max_HP} \n\
                [Character] | buffes: {buffes} \n\
                [Character] | draw pile: {draw_pile} \n\
                [Character] | max cards in hand: {max_hand} \n\
                [Character] | cards in hand: {cards_in_hand} \n\
                [Character] | state: {character_state} \n\
                [Character] | round start effects: {round_start_effects} \n\
                [Character] | judge survival effect: {survival_effect} \n\
                [Character] | die effect: {die_effect} \n\
                [Character] | switch effect: {switch_effect} \n".format(
                    name = self.name,
                    id = self.character_ID,
                    HP = self.current_HP,
                    max_HP = self.max_HP,
                    buffes = str([str(x) for x in self.buffes]).replace('\\n', '\n'),
                    draw_pile = str(self.draw_pile),
                    max_hand = self.max_cards_in_hand,
                    cards_in_hand = str([str(x) for x in self.cards_in_hand]).replace('\\n', '\n'),
                    character_state = self.character_state,
                    round_start_effects = str([str(x) for x in self.round_start_effects]).replace('\\n', '\n'),
                    survival_effect = self.judge_survival_effect,
                    die_effect = self.die_effect,
                    switch_effect = self.switch_effect
                )
            


