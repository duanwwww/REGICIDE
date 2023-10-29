#include <algorithm>
#include <character.hpp>
Character::Character(Deck *_deck, int _hp, int _max_cards_in_hand) {
    this->cards_in_deck = _deck;
    this->hp = _hp;
    this->max_cards_in_hand = _max_cards_in_hand;
    this->cards_in_hand.clear();
}

bool Character::not_full_hand() {
    return this->cards_in_hand.size() < this->max_cards_in_hand;
}

bool Character::full_hand() {
    return this->cards_in_hand.size() == this->max_cards_in_hand;
}

void Character::set_hp(int _hp) {
    this->hp = _hp;
}

void Character::set_deck(Deck *_deck) {
    this->cards_in_deck = _deck;
}

bool Character::draw_card() {
    if (this->not_full_hand()) {
        Card *card = this->cards_in_deck->draw_card();
        if (card == nullptr)
            return false;
        this->cards_in_hand.add(card);
        return true;
    }
    return false;
}

Pile Character::play_cards() {
    std::sort(this->selected.begin(), this->selected.end(),
              [](int a, int b) { return a > b; });
    Pile tmp_pile;
    for (auto it = this->selected.begin(); it != this->selected.end(); it++) {
        Card *tmp_pointer = this->cards_in_hand.erase(*it);
        if (tmp_pointer != nullptr)
            tmp_pile.add(tmp_pointer);
    }
    this->selected.clear();
    return tmp_pile;
}

Pile Character::discard() {
    std::sort(this->selected.begin(), this->selected.end(),
              [](int a, int b) { return a > b; });
    Pile tmp_pile;
    for (auto it = this->selected.begin(); it != this->selected.end(); it++) {
        Card *tmp_pointer = this->cards_in_hand.erase(*it);
        if (tmp_pointer != nullptr)
            tmp_pile.add(tmp_pointer);
    }
    this->selected.clear();
    return tmp_pile;
}

bool Character::selected_none() {
    return this->selected.empty();
}

bool Character::is_dead() {
    return this->hp <= 0;
}

bool Character::is_honour_kill() {
    return this->hp == 0;
}

void Character::add_cards(std::vector<Card *> cards) {
    this->cards_in_deck->add(std::list<Card *>(cards.begin(), cards.end()));
}

Character::~Character() {
    delete cards_in_deck;
    cards_in_hand.clear();
    selected.clear();
}