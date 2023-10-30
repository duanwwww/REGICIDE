#include <iostream>

struct SuitList {
    bool suits[4];
};

enum Face {
    None = 0,
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
};

enum Suit {
    Club = 0,
    Diamond,
    Heart,
    Spade,
};

enum Sticker {
    None,
    Circle,   // can be played with any other cards
    Square,   // add another suit
    triangle, // upgrade
};

enum CardBack {
    None,
    Classic,
};

inline int face2num(Face);

class BasicCard {
private:
    Face face;
    SuitList suit; // suit[Club] suit[Diamond] suit[Heart] suit[Spade]
public:
    BasicCard();
    BasicCard(Face, Suit);
    Face get_face();
    SuitList get_suit();
};

class Card : public BasicCard {
private:
    Sticker sticker;

public:
    Card();
    Card(Face, Suit);
    Card(Face, Suit, Sticker);
    bool add_sticker(Sticker);
    Sticker get_sticker();
};