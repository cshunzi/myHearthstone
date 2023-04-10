#ifndef SPELL_H
#define SPELL_H

#include "card.h"
#include "player.h"
class Player;

class Spell : public Card {
public:
    Spell(std::string name, int cost);
    void printCardInfo() const override;
    virtual void use(Player *player) = 0;
};

#endif
