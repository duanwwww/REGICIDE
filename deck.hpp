#include <card.hpp>
#include <List>
#include <vector>
class Deck
{
private:
    std::list<Card *> cards;
    CardBack card_back;

public:
    Deck();
    Deck(std::list<Card *>);
    Deck(const Deck &);
    void add(Card *);
    void add(std::list<Card *>);
    void shuffle();
    Card *draw_card();
    void set_top(Card *);
    void set_bottom(Card *);
    void set_card_back(CardBack);
    ~Deck();
};

class Pile
{
private:
    std::vector<Card *> cards;
    CardBack card_back;

public:
    Pile();
    Pile(std::vector<Card *>);
    void add(Card *);
    void add(std::vector<Card *>);
    void clear();
    void set_card_back(CardBack);
    int size();
    Card *erase(int);
};
