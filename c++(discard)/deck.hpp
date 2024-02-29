#include <card.hpp>
#include <list>
#include <vector>
class Pile {
protected:
    std::list<Card *> cards;

private:
    CardBack card_back;

public:
    Pile();
    Pile(std::list<Card *>);
    void set_card_back(CardBack);
    void add(Card *);
    void add(std::list<Card *>);
    void add(Pile *);
    void clear();
    void shuffle();
    int size();
    std::list<Card *> erase_front(int);
};

class SettlePile : public Pile {
public:
    int sum();        // sum of faces
    SuitList suits(); // union of suits
    std::vector<int> all();
};

class DrawPile : public Pile {
public:
    Card *draw_cards(); // YOU SHOULD CHECK NULLPTR
};

class Deck; // HAVE NOT FINISHED YET