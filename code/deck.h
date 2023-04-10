#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"

class Deck {
private:
    std::vector<Card*> cards;
public:
    void addCard(Card* c);
    void removeCard(Card* c);
    int getSize() const;
    void shuffle();
    Card* drawCard();
    ~Deck();
};

#endif
