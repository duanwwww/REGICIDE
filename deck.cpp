#include <deck.hpp>
#include <algorithm>
Deck::Deck()
{
    this->cards.clear();
}

Deck::Deck(std::list<Card *> _cards)
{
    this->cards = _cards;
}

Deck::Deck(const Deck &_deck)
{
    this->card_back = _deck.card_back;
    this->cards.clear();
    for (auto it = _deck.cards.begin(); it != _deck.cards.end(); it++)
    {
        Card *_card = new Card(**it); // copy every card.
        this->cards.push_back(_card);
    }
}

void Deck::add(Card *_card)
{
    this->cards.push_back(_card);
}

void Deck::add(std::list<Card *> _cards)
{
    this->cards.insert(cards.end(), _cards.begin(), _cards.end());
}

void Deck::shuffle()
{
    std::random_shuffle(this->cards.begin(), this->cards.end());
}

Card *Deck::draw_card()
{
    if (this->cards.empty())
        return nullptr;
    Card *tmp = this->cards.front();
    this->cards.pop_front();
    return tmp;
}

void Deck::set_top(Card *_card)
{
    int count = 0;
    for (auto it = this->cards.begin(); it != this->cards.end(); it++)
        if (*it == _card)
            count++;
    this->cards.remove(_card);
    for (int i = 0; i < count; ++i)
        this->cards.push_front(_card);
}

void Deck::set_bottom(Card *_card)
{
    int count = 0;
    for (auto it = this->cards.begin(); it != this->cards.end(); ++it)
        if (*it == _card)
            count++;
    this->cards.remove(_card);
    for (int i = 0; i < count; ++i)
        this->cards.push_back(_card);
}

void Deck::set_card_back(CardBack _card_back)
{
    this->card_back = _card_back;
}

Deck::~Deck() { this->cards.clear(); }