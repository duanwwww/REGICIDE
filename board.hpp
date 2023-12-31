#include <character.hpp>
class Board {
private:
    std::vector<BoardCharacter *> characters;
    SettlePile *settle_area;
    Pile *discard_area;
    int current_character, target_character;
    std::vector<int> damage_list;
    SuitList available_suit;
    void settle_suits(SuitList, int);
    void settle_club(int);
    void settle_diamond(int);
    void settle_heart(int);
    void settle_spade(int);
    void update_counter(std::vector<int>);

public:
    Board(std::vector<Character *>, int, int, SuitList);
    int select_target();
    void play_cards();
    void settle_effects();
    void deal_damage();
    void end_round();
    int left_HP();
    void start_round();
    virtual bool check_end_battle() = 0;
};