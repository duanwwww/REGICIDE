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
};

class Board
{
private:
    std::vector<SubBoard*> sub_boards;
    Pile discard_area;
    Pile settle_area;
public:
    Board(std::vector<Character*>);
};