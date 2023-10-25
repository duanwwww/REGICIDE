#include <card.hpp>
Card::Card()
{
    this->face = Face::None;
    this->suit = std::vector<bool>({false, false, false, false});
    this->sticker = Sticker::None;
}

Card::Card(Face _face, Suit _suit, Sticker _sticker)
{
    this->face = _face;
    this->suit = std::vector<bool>({false, false, false, false});
    this->suit[_suit] = true;
    this->sticker = _sticker;
}

Card::Card(const Card& _card){
    this->face = _card.face;
    this->suit = _card.suit;
    this->sticker = _card.sticker;
}

void Card::set_face(Face _face)
{
    this->face = _face;
}

void Card::set_suit(Suit _suit)
{
    this->suit = std::vector<bool>({false, false, false, false});
    this->suit[_suit] = true;
}

void Card::set_suit(std::vector<bool> _suit)
{
    this->suit = _suit;
}

void Card::set_sticker(Sticker _sticker)
{
    this->sticker = _sticker;
}

Card::~Card() {}