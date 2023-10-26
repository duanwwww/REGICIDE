#include <deck.hpp>
class Character
{
private:
    Deck *cards_in_deck;
    Pile cards_in_hand;
    int hp;
    int max_cards_in_hand;
    bool not_full_hand();
    std::vector<int> selected;
protected:
    Character(Deck *, int, int);

public:
    void set_hp(int);
    void set_deck(Deck *);
    void set_max_cards_in_hand(int);
    void draw_card();
    void select_card(bool, int, int); // legal or any?, minimum sum, minimum number
    Pile play_cards();
    Pile discard();
    bool is_dead();
    bool is_honour_kill();
    // update_count(info) = 0;
    ~Character();
};