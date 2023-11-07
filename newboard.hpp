#include <character.hpp>
class Group{
private:
    int current_character;
public:
    std::vector<BoardCharacter*> characters;
    Pile* discard_area;
    Character* get_current();
    Group(std::vector<Character*>,int, int);
    void draw(int);
    void collect(int);
};

class Board{
private:
    std::vector<Group*> groups;
    SettlePile *settle_area;
    std::vector<int> damage_list;
    SuitList available_suit;
    int current_group;
    void settle_suits(SuitList, int);
    void settle_club(int);
    void settle_diamond(int);
    void settle_heart(int);
    void settle_spade(int);
    void update_counter(std::vector<int>);
public:
    Board(std::vector<Group *>, int, int, SuitList);
    int select_target();
    void play_cards();
    void settle_effects();
    void deal_damage();
    void end_round();
    int left_HP();
    void start_round();
    virtual bool check_end_battle() = 0;
};