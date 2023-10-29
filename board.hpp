#include <card.hpp>
#include <character.hpp>
#include <effects.hpp>
#include <vector>
class SubBoard {
private:
    Character *character;
    Pile activate_pile;
    int attack_bias_buff;
    int attack_coefficient;
    int id;
    SubBoard(Character *);

public:
    friend Board;
};

class Board {
private:
    std::vector<SubBoard *>
        sub_boards; // the first in vector will be the first to act
    Pile discard_area;
    Pile settle_area;
    int current_character;
    int target_character; // -1 for none
    std::vector<Effect> effects;
    std::vector<int> damage_list;
    std::vector<bool> available_suit;
    void settle_suits(std::vector<bool>, int);
    void settle_club(int);
    void settle_diamond(int);
    void settle_heart(int);
    void settle_spade(int); // HAVE NOT FINISHED
public:
    Board(std::vector<Character *>);
    void set_id();
    int select_target(); // HAVE NOT FINISHED
    void play_cards();
    void settle_effects();
    void deal_damage(); // HAVE NOT FINISHED
    void
    update_counter(); // share board info to all characters so they can
                      // update counters and push effects. HAVE NOT FINISHED
    /*e.g.
    character1.check_counter(info);
    this->effects.push_back(character1.effect());
    */
};

class BoardInfo { // HAVE NOT FINISHED
private:
    BoardInfo(Board *);

public:
    friend Board;
};