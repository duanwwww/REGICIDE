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
    SumPile settle_area;
    Character *current_character;
    Character *target_character;
    std::vector<Effect> effects;
    void settle_suits(std::vector<bool>, int);
    void settle_club(int);    // HAVE NOT FINISHED
    void settle_diamond(int); // HAVE NOT FINISHED
    void settle_heart(int);   // HAVE NOT FINISHED
    void settle_spade(int);   // HAVE NOT FINISHED
public:
    Board(std::vector<Character *>);
    void set_id();
    Character *find_id(int); // YOU SHOULD CHECK NULLPTR
    int select_target();     // HAVE NOT FINISHED
    void play_cards();       // HAVE NOT FINISHED
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
    // to be fullfill
private:
    BoardInfo(Board *);

public:
    friend Board;
};