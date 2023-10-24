#include<deck.hpp>
#include<algorithm>
#include<random>
Deck::Deck(){
    this->cards.clear();
}

Deck::Deck(std::list<Card*> _cards){
    this->cards = _cards;
}

void Deck::add(Card* _card){
    this->cards.push_back(_card);
}

void Deck::add(std::list<Card*> _cards){
    this->cards.insert(cards.end(), _cards.begin(),_cards.end());
}

void Deck::shuffle(){
    std::random_shuffle(this->cards.begin(),this->cards.end());
}

void Deck::draw_card(){
}