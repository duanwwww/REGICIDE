#include<battle.hpp>
Battle::Battle(std::vector<Character*> _characters){
    this->board = new Board(_characters);
}

void Battle::turn(){
    this->start_turn();
    this->play_cards();
    this->settle_effects();
    this->deal_damage();
    this->check_death();
    this->end_turn();
}

void Battle::play_cards(){
    this->board->play_cards();
}

void Battle::settle_effects(){
    this->board->settle_effects();
}

void Battle::deal_damage(){
    this->board->deal_damage();
}

void Battle::end_turn(){
    this->board->update_counter();
}