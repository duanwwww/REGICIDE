#include <newboard.hpp>
Group::Group(std::vector<Character*> _characters, int _HP, int _max_cards_in_hand){
    for (auto it = _characters.begin(); it != _characters.end(); it++) {
        this->characters.push_back(
            (*it)->create_board_character(_HP, _max_cards_in_hand));
    }
    this->discard_area = new Pile();
    this->current_character = 0;
}

void Group::draw(int _sum){
    int id = this->current_character;
    int flag = 0;
    while (_sum > 0) {
        if (this->characters[id]->draw_card()) {
            _sum--;
            flag = 0;
        }
        else
            flag++;
        id++;
        id = id % this->characters.size();
        if (flag == this->characters.size())
            break;
    }
}

void Group::collect(int _sum){
    this->discard_area->shuffle();
    this->characters[this->current_character]->add_cards_to_deck(
        this->discard_area->erase_front(
            std::min(_sum, this->discard_area->size())));
}

Board::Board(std::vector<Group *> _groups, int _HP,
             int _max_cards_in_hand, SuitList suit_list) {
    for(auto it = groups.begin();it != groups.end();it ++){
        this->groups.push_back((*it));
    }
    this->current_group=0;
    this->settle_area = nullptr;
    this->available_suit = suit_list;
}

void Board::settle_suits(SuitList _suit_list, int _sum) {
    if (_suit_list.suits[Suit::Heart])
        this->settle_heart(_sum);
    // heart should act before diamond
    if (_suit_list.suits[Suit::Club])
        this->settle_club(_sum);
    if (_suit_list.suits[Suit::Diamond])
        this->settle_diamond(_sum);
    if (_suit_list.suits[Suit::Spade])
        this->settle_spade(_sum);
}

void Board::settle_club(int _sum) {
    this->damage_list.push_back(_sum);
}

void Board::settle_diamond(int _sum) {
    this->groups[this->current_group]->draw(_sum);
}

void Board::settle_heart(int _sum) {
    this->groups[this->current_group]->collect(_sum);
}