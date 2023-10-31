#include <algorithm>
#include <character.hpp>
Character::Character(Deck *_deck, std::vector<Self2TargetEffect *>_effects) {
    this->deck = _deck;
    this->effects = _effects;
}

std::vector<Self2TargetEffect *>Character::get_effect() {
    return this->effects;
}

BoardCharacter::BoardCharacter(Character *_character, int _HP,
                               int _max_cards_in_hand, DrawPile *)
    : max_cards_in_hand(_max_cards_in_hand) {
    this->info.HP = _HP;
    this->info.ATK_buff = 0;
    this->info.ATK_debuff = 0;
    this->info.ATK_coefficient = 1;
    this->info.DEF_buff = 0;
    this->info.DEF_debuff = 0;
    this->info.DEF_coefficient = 1;
    this->draw_deck = _character->set_up_deck();
    this->effects = _character->get_effect();
}

bool BoardCharacter::draw_card() {
    Card *tmp = this->draw_deck->draw_cards();
    if (tmp == nullptr)
        return false;
    if (this->num_hand() >= max_cards_in_hand)
        return false;
    this->cards_in_hand.push_back(tmp);
    return true;
}

int BoardCharacter::num_deck() {
    return this->draw_deck->size();
}

int BoardCharacter::num_hand() {
    return this->cards_in_hand.size();
}

int BoardCharacter::left_HP() {
    return this->info.HP;
}

CharacterInfo BoardCharacter::get_info() {
    return this->info;
}

void BoardCharacter::set_info(CharacterInfo _info) {
    this->info = _info;
}

void BoardCharacter::add_cards_to_deck(std::list<Card *> _cards) {
    this->draw_deck->add(_cards);
}

std::vector<Self2TargetEffect*> BoardCharacter::get_ATK_effects_stack() {
    return this->ATK_effects_stack;
}

std::vector<Self2TargetEffect*> BoardCharacter::get_DEF_effects_stack() {
    return this->DEF_effects_stack;
}

SettlePile *BoardCharacter::play_selected_cards() {
    std::sort(this->selected.begin(), this->selected.end(),
              [](int a, int b) { return a > b; });
    SettlePile *tmp_pile = new SettlePile;
    for (auto it = this->selected.begin(); it != this->selected.end(); it++) {
        if ((*it) >= 0 && (*it) < this->num_hand()) {
            tmp_pile->add(this->cards_in_hand[(*it)]);
            this->cards_in_hand.erase(this->cards_in_hand.begin() + (*it));
        }
    }
    this->selected.clear();
    return tmp_pile;
}

Pile *BoardCharacter::be_damaged(int _damage) {
    if (this->select_cards(false, _damage, 0))
        return this->play_selected_cards();
    return nullptr;
}

void BoardCharacter::new_round(){
    for(auto it = this->ATK_effects_stack.end() - 1; it >= this->ATK_effects_stack.begin(); it--){
        (*it)->new_round();
        if(! (*it)->still_activate()){
            this->ATK_effects_stack.erase(it);
        } 
    }
    for(auto it = this->DEF_effects_stack.end() - 1; it >= this->DEF_effects_stack.begin(); it--){
        (*it)->new_round();
        if(! (*it)->still_activate()){
            this->DEF_effects_stack.erase(it);
        } 
    }
}