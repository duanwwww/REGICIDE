#include <algorithm>
#include <character.hpp>
Character::Character(Deck *_deck, Self2TargetEffect *_effect) {
    this->deck = _deck;
    this->effect = _effect;
}

Self2TargetEffect *Character::get_effect() {
    return this->effect;
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
    this->effect = _character->get_effect();
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