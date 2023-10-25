#include <vector>
#include <card.hpp>
#include<character.hpp>
class SubBoard
{
private:
    Character* character;
    Pile activate_pile;
    int attack_bias_buffs;
    int attack_coefficient;
public:
    SubBoard(Character*);
};

class Board
{
private:
    std::vector<SubBoard*> sub_boards;
    Pile discard_area;
    Pile settle_area;
    // Need: a place for effects. maybe a std::vector<std::function>
public:
    Board(std::vector<Character*>);
    int select_target(int); //input current player output: target player 
    void play_cards(int); //input: current player
    void settle_effects(int, int); //input: current player, target player
    void deal_damage(int);// input: target player
    void update_counter(); // share board info to all characters so they can update counters and push effects.
    // e.g. character1.check_counter(); effects.push_back(character1.effect());
};