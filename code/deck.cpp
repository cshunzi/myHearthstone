#include "card.h"
#include "deck.h"
#include <algorithm>
#include <random>
#include <chrono>

Deck::~Deck() {
    for (auto c : cards) {
        delete c;
    }
}

void Deck::addCard(Card* c) {
    cards.push_back(c);
}

void Deck::removeCard(Card* c) {
    cards.erase(std::remove(cards.begin(), cards.end(), c), cards.end());
}

int Deck::getSize() const {
    return cards.size();
}

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}

Card* Deck::drawCard() {
    Card* c = cards.back();
    cards.pop_back();
    return c;
}
