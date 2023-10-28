#include <card.hpp>

int face_to_num(Face face) {
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

Card::Card() {
    this->face = Face::None;
    this->suit = std::vector<bool>({false, false, false, false});
    this->sticker = Sticker::None;
}

Card::Card(Face _face, Suit _suit, Sticker _sticker) {
    this->face = _face;
    this->suit = std::vector<bool>({false, false, false, false});
    this->suit[_suit] = true;
    this->sticker = _sticker;
}

Card::Card(const Card &_card) {
    this->face = _card.face;
    this->suit = _card.suit;
    this->sticker = _card.sticker;
}

void Card::set_face(Face _face) {
    this->face = _face;
}

void Card::set_suit(Suit _suit) {
    this->suit = std::vector<bool>({false, false, false, false});
    this->suit[_suit] = true;
}

void Card::set_suit(std::vector<bool> _suit) {
    this->suit = _suit;
}

void Card::set_sticker(Sticker _sticker) {
    this->sticker = _sticker;
}

Card::~Card() {
}