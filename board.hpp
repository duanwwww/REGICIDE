#include <vector>
#include <card.hpp>
#include <character.hpp>
class SubBoard
{
private:
    Character* character; 
    Pile activate_pile;
    int attack_bias_buff;
    int attack_coefficient;
    int id;
    SubBoard(Character*);
public:
    friend Board;
};

class Board
{
private:
    std::vector<SubBoard*> sub_boards; // the first in vector will be the first to act
    Pile discard_area;
    Pile settle_area;
    Character* current_character;
    Character* target_character;
    // Need: a place for effects. maybe a std::vector<std::function>
public:
    Board(std::vector<Character*>);
    void set_id();
    Character* find_id(int);
    int select_target(); 
    void play_cards(); 
    void settle_effects(); 
    void deal_damage();
    void update_counter(); // share board info to all characters so they can update counters and push effects.
    /*e.g.
    character1.check_counter(info); 
    this->effects.push_back(character1.effect());
    */ 
};