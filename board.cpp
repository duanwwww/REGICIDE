#include<board.hpp>
SubBoard::SubBoard(Character* _character){
    this->character = character;
    this->activate_pile.clear();
    this->attack_bias_buff = 0;
    this->attack_coefficient = 1;
}

Board::Board(std::vector<Character*> _characters){
    this->sub_boards.clear();
    for(int i = 0; i<_characters.size();i++){
        this->sub_boards.push_back(new SubBoard(_characters[i]));
    }
    this->discard_area.clear();
    this->settle_area.clear();
    this->current_character = this->sub_boards[0]->character;
    this->target_character = nullptr;
}

void Board::set_id(){
    for(int i = 0;i<(this->sub_boards.size());i++){
        this->sub_boards[i]->id = i;
    }
}

Character* Board::find_id(int target_id){
    for(int i=0;i<this->sub_boards.size();i++){
        if(sub_boards[i]->id == target_id) return sub_boards[i]->character;
    }
    return nullptr;
}

void Board::play_cards(){
    this->current_character->select_card(true, 0, 1); // must select legal cards, at least 1.
    this->current_character->play_cards();
}