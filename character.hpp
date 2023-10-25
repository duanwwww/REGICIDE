#include <deck.hpp>
#include <board.hpp>
class Character
{
private:
    Deck *cards_in_deck;
    std::vector<Card *> cards_in_hand;
    int hp;
    int max_cards_in_hand;
    Board *board;
    bool not_full_hand();
    std::vector<int> selected;

public:
    Character(Deck *, int, int, Board *);
    void set_hp(int);
    void set_deck(Deck *);
    void set_board(Board *);
    void set_max_cards_in_hand(int);
    void draw_card();
    void select_card(bool, int, int); // legal or any?, minimum sum, minimum number
    void play_cards();
    void discard();
    bool is_dead();
    bool is_honour_kill();
    ~Character();
};