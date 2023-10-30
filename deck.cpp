#include <algorithm>
#include <deck.hpp>

Pile::Pile() {
    this->card_back = CardBack::None;
}

Pile::Pile(std::list<Card *> _cards) {
    this->cards = _cards;
    this->card_back = CardBack::None;
}

void Pile::set_card_back(CardBack _card_back) {
    this->card_back = _card_back;
}

void Pile::add(Card *_card) {
    this->cards.push_back(_card);
}

void Pile::add(Pile *_pile) {
    this->cards.insert(this->cards.end(), *_pile->cards.begin(),
                       *_pile->cards.end());
}

void Pile::add(std::list<Card *> _cards) {
    this->cards.insert(this->cards.end(), _cards.begin(), _cards.end());
}

void Pile::clear() {
    this->cards.clear();
}

void Pile::shuffle() {
    std::random_shuffle(this->cards.begin(), this->cards.end());
}

int Pile::size() {
    return this->cards.size();
}

std::list<Card *> Pile::erase_front(int _num) {
    std::list<Card *> tmp;
    while (_num > 0) {
        if (this->cards.empty())
            break;
        _num--;
        tmp.push_back(this->cards.front());
        this->cards.pop_front();
    }
    return tmp;
}

int SettlePile::sum() {
    int _sum = 0;
    for (auto it = this->cards.begin(); it != this->cards.end(); it++) {
        _sum += face2num((*it)->get_face());
    }
    return _sum;
}

SuitList SettlePile::suits() {
    SuitList _suits = {false, false, false, false};
    for (auto it = this->cards.begin(); it != this->cards.end(); it++) {
        _suits.suits[Suit::Club] =
            (*it)->get_suit().suits[Suit::Club] || _suits.suits[Suit::Club];
        _suits.suits[Suit::Diamond] = (*it)->get_suit().suits[Suit::Diamond] ||
                                      _suits.suits[Suit::Diamond];
        _suits.suits[Suit::Heart] =
            (*it)->get_suit().suits[Suit::Heart] || _suits.suits[Suit::Heart];
        _suits.suits[Suit::Spade] =
            (*it)->get_suit().suits[Suit::Spade] || _suits.suits[Suit::Spade];
    }
    return _suits;
}

std::vector<int> SettlePile::all() {
    std::vector<int> tmp;
    for (auto it = this->cards.begin(); it != this->cards.end(); it++) {
        if (face2num((*it)->get_face()) != 0) {
            tmp.push_back(face2num((*it)->get_face()));
        }
    }
    return tmp;
}

Card *DrawPile::draw_cards() {
    if (this->cards.empty())
        return nullptr;
    Card *tmp = this->cards.front();
    this->cards.pop_front();
}