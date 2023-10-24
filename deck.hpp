#include <card.hpp>
#include <List>
class Deck
{
private:
    std::list<Card *> cards;
    CardBack card_back;

public:
    Deck();
    Deck(std::list<Card *>);
    void add(Card *);
    void add(std::list<Card *>);
    void shuffle();
    Card *draw_card();
    void set_top(Card *);
    void set_bottom(Card *);
    void set_card_back(CardBack);
    ~Deck();
};