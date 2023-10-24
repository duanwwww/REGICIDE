#include <iostream>
enum Face
{
    None,
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
    None,
    Club,
    Diamond,
    Club_and_Diamond,
    Heart,
    Club_and_Heart,
    Diamond_and_Heart,
    Club_and_Diamond_and_Heart,
    Spade,
    Club_and_Spade,
    Diamond_and_Spade,
    Club_and_Diamond_and_Spade,
    Heart_and_Spade,
    Club_and_Heart_and_Spade,
    Diamond_and_Heart_and_Spade,
    Club_and_Diamond_and_Heart_and_Spade,
};

enum Sticker
{
    None,
    Circle,
    Square,
    triangle,
};

class Card
{
private:
    Face face;
    Suit suit;
    Sticker sticker;

public:
    Card();
    Card(Face, Suit, Sticker);
    void set_face(Face);
    void set_suit(Suit);
    void set_sticker(Sticker);
    // void set_effect()
    // void settle_effects(*Board);
    // void deal_damage(*Board);
    ~Card();
};