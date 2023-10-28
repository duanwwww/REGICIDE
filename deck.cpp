#include <algorithm>
#include <deck.hpp>
Deck::Deck() {
    this->cards.clear();
}

Deck::Deck(std::list<Card *> _cards) {
    this->cards = _cards;
}

Deck::Deck(const Deck &_deck) {
    this->card_back = _deck.card_back;
    this->cards.clear();
    for (auto it = _deck.cards.begin(); it != _deck.cards.end(); it++) {
        Card *_card = new Card(**it); // copy every card.
        this->cards.push_back(_card);
    }
}

void Deck::add(Card *_card) {
    this->cards.push_back(_card);
}

void Deck::add(std::list<Card *> _cards) {
    this->cards.insert(cards.end(), _cards.begin(), _cards.end());
}

void Deck::shuffle() {
    std::random_shuffle(
        this->cards.begin(),
        this->cards
            .end()); //  this will be overwrite if we want to set random seed
}

Card *Deck::draw_card() { // check nullptr
    if (this->cards.empty())
        return nullptr;
    Card *tmp = this->cards.front();
    this->cards.pop_front();
    return tmp;
}

void Deck::set_top(Card *_card) {
    int count = 0;
    for (auto it = this->cards.begin(); it != this->cards.end(); it++)
        if (*it == _card)
            count++;
    this->cards.remove(_card);
    for (int i = 0; i < count; ++i)
        this->cards.push_front(_card);
}

void Deck::set_bottom(Card *_card) {
    int count = 0;
    for (auto it = this->cards.begin(); it != this->cards.end(); ++it)
        if (*it == _card)
            count++;
    this->cards.remove(_card);
    for (int i = 0; i < count; ++i)
        this->cards.push_back(_card);
}

void Deck::set_card_back(CardBack _card_back) {
    this->card_back = _card_back;
}

Deck::~Deck() {
    this->cards.clear();
}

Pile::Pile() {
    this->card_back = CardBack::None;
    this->cards.clear();
}

Pile::Pile(std::vector<Card *> _cards) {
    this->cards = _cards;
}

void Pile::add(Card *_card) {
    this->cards.push_back(_card);
}

void Pile::add(std::vector<Card *> _cards) {
    this->cards.insert(this->cards.end(), _cards.begin(), _cards.end());
}

void Pile::clear() {
    this->cards.clear();
}

void Pile::set_card_back(CardBack _card_back) {
    this->card_back = _card_back;
}

int Pile::size() {
    return this->cards.size();
}

Card *Pile::erase(int index) {
    if (index >= size())
        return nullptr;
    Card *tmp_card = this->cards[index];
    this->cards.erase(this->cards.begin() + index);
    return tmp_card;
}

int Pile::sum() {
    int _sum = 0;
    for (auto it = this->cards.begin(); it != this->cards.end(); it++) {
        _sum += face_to_num((*it)->face);
    }
    return _sum;
}

std::vector<bool> Pile::suits() {
    std::vector<bool> _suits = {false, false, false, false};
    for (auto it = this->cards.begin(); it != this->cards.end(); it++) {
        _suits[Club] = (*it)->suit[Club] || _suits[Club];
        _suits[Diamond] = (*it)->suit[Diamond] || _suits[Diamond];
        _suits[Heart] = (*it)->suit[Heart] || _suits[Heart];
        _suits[Spade] = (*it)->suit[Spade] || _suits[Spade];
    }
    return _suits;
}

void Pile::shuffle() {
    std::random_shuffle(
        this->cards.begin(),
        this->cards
            .end()); //  this will be overwrite if we want to set random seed
}