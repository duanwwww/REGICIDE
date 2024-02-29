#include <card.hpp>
inline int face2num(Face face) {
    switch (face) {
    case Face::Ace:
    case Face::Two:
    case Face::Three:
    case Face::Four:
    case Face::Five:
    case Face::Six:
    case Face::Seven:
    case Face::Eight:
    case Face::Nine:
    case Face::Ten:
        return static_cast<int>(face);
    case Face::Jack:
        return 10;
    case Face::Queen:
        return 15;
    case Face::King:
        return 20;
    default: // Face::None, Face::Joker
        return 0;
    }
}

BasicCard::BasicCard() {
    this->face = Face::None;
    this->suit = SuitList{false, false, false, false};
}

BasicCard::BasicCard(Face _face, Suit _suit) {
    this->face = _face;
    this->suit = SuitList{false, false, false, false};
    this->suit.suits[_suit] = true;
}

Face BasicCard::get_face() {
    return this->face;
}

SuitList BasicCard::get_suit() {
    return this->suit;
}

Card::Card() {
    BasicCard();
    this->sticker = Sticker::None;
}

Card::Card(Face _face, Suit _suit) {
    BasicCard(_face, _suit);
    this->sticker = Sticker::None;
}

Card::Card(Face _face, Suit _suit, Sticker _sticker) {
    BasicCard(_face, _suit);
    this->sticker = _sticker;
}

bool Card::add_sticker(Sticker _sticker) {
    if (this->sticker != Sticker::None)
        return false;
    this->sticker = _sticker;
    return true;
}

Sticker Card::get_sticker() {
    return this->sticker;
}