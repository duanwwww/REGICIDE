#include<board.hpp>
class Battle
{
private:
    Board* board;
    std::vector<Character*> characters; // the first in vector will be the first to act
    int current_player;
    int target_player;
public:
    Battle(std::vector<Character*>);
    void start_turn();
    void play_cards();
    void settle_effects();
    void deal_damage();
    void check_death();
    void end_battle(int); // input: the winner
    void end_turn();
};