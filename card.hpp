#include <iostream>
#include <vector>
enum Face
{
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

enum Suit
{
    Club = 0,
    Diamond,
    Heart,
    Spade,
};

enum Sticker
{
    None,
    Circle,
    Square,
    triangle,
};

enum CardBack
{
    None,
};

class Card
{
private:
    Face face;
    std::vector<bool> suit; // suit[Club] suit[Diamond] suit[Heart] suit[Spade]
    Sticker sticker;

public:
    Card();
    Card(Face, Suit, Sticker);
    Card(const Card&);
    void set_face(Face);
    void set_suit(Suit);
    void set_suit(std::vector<bool>);
    void set_sticker(Sticker);
    ~Card();
};