#ifndef MINION_H
#define MINION_H

#include "Card.h"

class Minion : public Card {
public:
    Minion(std::string name, int cost, int attack, int health);
    void printCardInfo() const override;
    int getAttack() const;
    int getHealth() const;
    int getCurHP() const;
    bool getCanAttack() const;
    void setHealth(int newHealth);
    void setCurHP(int newHP);
    void setCanAttack(bool f);
    bool isDead() const;

private:
    int attack;
    int health;
    int curHP;
    bool canAttack;
};

#endif
