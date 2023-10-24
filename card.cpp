#include <card.hpp>
Card::Card()
{
    this->face = Face::None;
    this->suit = Suit::None;
    this->sticker = Sticker::None;
}

Card::Card(Face _face, Suit _suit, Sticker _sticker)
{
    this->face = _face;
    this->suit = _suit;
    this->sticker = _sticker;
}

void Card::set_face(Face _face){
    this->face = _face;
}

void Card::set_suit(Suit _suit){
    this->suit = _suit;
}

void Card::set_sticker(Sticker _sticker){
    this->sticker = _sticker;
}

Card::~Card(){}