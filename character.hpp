#include<deck.hpp>
class Boarder;
class Character{
private:
    Deck* cards_in_deck;
    std::vector<Card*> cards_in_hand;
    int hp;
    int max_cards_in_hand;
public:
    Character(Deck*, int, int);
    void set_hp();
    void set_max_cards_in_hand();
    void set_cards_in_deck(Deck*);
    void draw_card();
    void select_card();
    void play_cards(Boarder*);
    bool is_dead();
    bool is_honour_kill();
    ~Character();
};