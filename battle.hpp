#include<board.hpp>
class Battle
{
private:
    Board* board;
public:
    Battle(std::vector<Character*>);
    void turn();
    void start_turn();
    void play_cards();
    void settle_effects();
    void deal_damage();
    void check_death();
    void end_turn();
};