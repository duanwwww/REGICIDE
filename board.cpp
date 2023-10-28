#include <board.hpp>
SubBoard::SubBoard(Character *_character) {
    this->character = character;
    this->activate_pile.clear();
    this->attack_bias_buff = 0;
    this->attack_coefficient = 1;
}

Board::Board(std::vector<Character *> _characters) {
    this->sub_boards.clear();
    for (int i = 0; i < _characters.size(); i++) {
        this->sub_boards.push_back(new SubBoard(_characters[i]));
    }
    this->discard_area.clear();
    this->settle_area.clear();
    this->current_character = 0;
    this->target_character = -1;
    this->set_id();
}

void Board::settle_suits(std::vector<bool> suits, int sum) {
    if (suits[Suit::Club] && this->available_suit[Suit::Club]) {
        this->settle_club(sum);
    }
    if (suits[Suit::Diamond] && this->available_suit[Suit::Diamond]) {
        this->settle_diamond(sum);
    }
    if (suits[Suit::Heart] && this->available_suit[Suit::Heart]) {
        this->settle_heart(sum);
    }
    if (suits[Suit::Spade] && this->available_suit[Suit::Spade]) {
        this->settle_spade(sum);
    }
}

void Board::settle_club(int sum){
    this->damage_list.push_back(sum);
}

void Board::settle_diamond(int sum){
    int id = current_character;
    int flag = 0;
    while(sum > 0){
        if(this->sub_boards[id]->character->draw_card()){
            sum--;
            flag = 0;
        }
        else{
            flag++;
        }
        id = (id+1) % this->sub_boards.size();
        if(flag == this->sub_boards.size()) break;
    }
}

void Board::set_id() {
    for (int i = 0; i < (this->sub_boards.size()); i++) {
        this->sub_boards[i]->id = i;
    }
}

void Board::play_cards() {
    this->sub_boards[current_character]->character->select_card(true, 0, 0);
    if (this->sub_boards[current_character]->character->selected_none()) {
        // warn this!
    }
    this->settle_area = this->sub_boards[current_character]->character->play_cards();
}

void Board::settle_effects() {
    for(auto it = this->settle_area.cards.begin();it != this->settle_area.cards.end();it++){
        int number = face_to_num((*it)->face);
        if( number != 0) this->damage_list.push_back(number);
    }

    BoardInfo *board_info = new BoardInfo(this);
    for (auto it = this->effects.begin(); it != this->effects.end(); it++) {
        (*it).activate(*board_info);
    }

    this->settle_suits(this->settle_area.suits(), this->settle_area.sum());
}