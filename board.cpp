#include <board.hpp>
Board::Board(std::vector<Character *> _characters, int _HP,
             int _max_cards_in_hand, SuitList suit_list) {
    for (auto it = _characters.begin(); it != _characters.end(); it++) {
        this->characters.push_back(
            (*it)->create_board_character(_HP, _max_cards_in_hand));
    }
    this->settle_area = nullptr;
    this->discard_area = new Pile;
    this->current_character = 0;
    this->target_character = -1;
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

void Board::settle_heart(int _sum) {
    this->discard_area->shuffle();
    this->characters[this->current_character]->add_cards_to_deck(
        this->discard_area->erase_front(
            std::min(_sum, this->discard_area->size())));
}

void Board::settle_spade(int _sum) {
    if (this->target_character != -1) {
        CharacterInfo tmp_info =
            this->characters[this->target_character]->get_info();
        tmp_info.ATK_debuff += _sum;
        this->characters[this->target_character]->set_info(tmp_info);
    }
}

void Board::play_cards() {
    this->select_target();

    if (this->characters[this->current_character]->select_cards(true, 0, 0)) {
        this->settle_area =
            this->characters[this->current_character]->play_selected_cards();
        if (this->target_character != -1)
            this->characters[this->target_character]->activate->add(
                this->settle_area);
    }
}

void Board::settle_effects() {
    SuitList tmp_suit = this->available_suit;
    this->damage_list = this->settle_area->all();
    Self2TargetInfo tmp_info;
    tmp_info.available = this->available_suit;
    tmp_info.self = this->characters[this->current_character]->get_info();
    if (this->target_character != -1) {
        tmp_info.target = this->characters[this->target_character]->get_info();
    }
    for (auto it = this->effects.begin(); it != this->effects.end(); it++) {
        tmp_info = ((*it)->activate(tmp_info));
    }

    this->characters[this->current_character]->set_info(tmp_info.self);
    if (this->target_character != -1)
        this->characters[this->target_character]->set_info(tmp_info.target);
    for (int i = 0; i < sizeof(tmp_info.available.suits) /
                            sizeof(tmp_info.available.suits[0]);
         i++) {
        tmp_info.available.suits[i] =
            tmp_info.available.suits[i] && this->settle_area->suits().suits[i];
    }

    this->settle_suits(tmp_info.available, this->settle_area->sum());
    this->settle_area = nullptr;
}

void Board::deal_damage() {
    for (auto it = this->damage_list.begin(); it < this->damage_list.end();
         it++) {
        if (this->target_character != -1) {
            int damage =
                ((*it) +
                 this->characters[this->current_character]
                     ->get_info()
                     .ATK_buff -
                 this->characters[this->current_character]
                     ->get_info()
                     .ATK_debuff -
                 this->characters[this->target_character]->get_info().DEF_buff +
                 this->characters[this->target_character]
                     ->get_info()
                     .DEF_debuff) *
                this->characters[this->current_character]
                    ->get_info()
                    .ATK_coefficient;
            if (this->characters[this->target_character]
                    ->get_info()
                    .DEF_coefficient != 0) {
                damage = damage / this->characters[this->target_character]
                                      ->get_info()
                                      .DEF_coefficient;
            }

            Pile *tmp_ptr =
                this->characters[this->target_character]->be_damaged(damage);
            if (tmp_ptr != nullptr) {
                this->discard_area->add(tmp_ptr);
            }
        }
    }
}

void Board::update_counter(std::vector<int> _damage_list) {
    this->characters[this->current_character]->update_counter(_damage_list);
}