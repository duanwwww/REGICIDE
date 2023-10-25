#include<character.hpp>
Character::Character(Deck* _deck, int _hp, int _max_cards_in_hand, Board* _board){
    this->cards_in_deck = new Deck(*_deck);
    this->hp = _hp;
    this->max_cards_in_hand = _max_cards_in_hand;
    this->cards_in_hand.clear();
    this->board = _board;
}

bool Character::not_full_hand(){
    return this->cards_in_hand.size() < this->max_cards_in_hand;
}

void Character::set_hp(int _hp){
    this->hp = _hp;
}

void Character::set_deck(Deck* _deck){
    if(this->cards_in_deck != nullptr) delete this->cards_in_deck;
    this->cards_in_hand.clear();
    this->cards_in_deck = new Deck(*_deck);
}

void Character::set_board(Board* _board){
    this->board = _board;
}

void  Character::set_max_cards_in_hand(int _max_cards_in_hand){
    this->max_cards_in_hand = _max_cards_in_hand;
    if (this->cards_in_hand.size() > this->max_cards_in_hand){
        this->select_card(false, 0, cards_in_hand.size() - this->max_cards_in_hand);
        discard();
    }
}

void Character::draw_card(){
    if(this->not_full_hand())    this->cards_in_hand.push_back(this->cards_in_deck->draw_card());
}
