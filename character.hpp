#include <deck.hpp>
class BattleInfo;
class Character {
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
    bool draw_card();
    bool full_hand();
    void select_card(bool, int,
                     int); // input:(legal or any?, minimum sum, minimum
                           // number). HAVE NOT FINISHED
    Pile play_cards();
    Pile discard();
    bool selected_none();
    bool is_dead();
    bool is_honour_kill();
    virtual void update_counter(const BattleInfo &) = 0;
    void add_cards(std::vector<Card *>);
    ~Character();
};