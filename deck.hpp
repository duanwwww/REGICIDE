#include <List>
#include <card.hpp>
#include <vector>
class Deck {
private:
    std::list<Card *> cards;
    CardBack card_back;

public:
    Deck();
    Deck(std::list<Card *>);
    Deck(const Deck &);          // copy
    void add(Card *);            // add to bottom
    void add(std::list<Card *>); // add to bottom
    void shuffle();
    Card *draw_card(); // YOU SHOULD CHECK NULLPTR
    void set_top(Card *);
    void set_bottom(Card *);
    void set_card_back(CardBack);
    ~Deck();
};

class Pile {
protected:
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

class SumPile : public Pile {
public:
    int sum();                 // sum of faces
    std::vector<bool> suits(); // union of suits
};