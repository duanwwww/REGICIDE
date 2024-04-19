from manager import character_manager, card_manager, group_manager
from basic_board import BasicBoard
from card import Card, CardType
from suit import Suit
from pile import Deck, Pile
from character import Character, CharacterState

# create a card first
club_two = Card(rank=2, card_ID=0, suit=Suit.Club, type=CardType.Middle)
# print(club_two)
club_three = Card(rank=3, card_ID=1, suit=Suit.Club, type=CardType.Middle)
club_four = Card(rank=4, card_ID=2, suit=Suit.Club, type=CardType.Middle)
card_manager.add(key=0, value=club_two)
card_manager.add(key=1, value=club_three)
card_manager.add(key=2, value=club_four)

# create a deck and a pile
deck = Deck(card_IDs=[0, 1], name="test")
deck.add_card(card_id=2)
pile = deck.create_draw_deck(max_card_num=100)
print(pile)

# create a Effect
# print(pile.draw().suit.value[0].activate(board=None))

# # create a character
# character_state = CharacterState()
# def f():
#     return True
# character = Character(skills=[], current_skill_ID=0, name='duanw', character_ID=0, max_HP=20, current_HP=20, draw_pile=pile, max_cards_in_hand=10, character_state=character_state, select_target_function=None, valid_play_judgers=[f], judge_survival_effect=)