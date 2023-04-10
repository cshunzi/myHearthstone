#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Card.h"
#include "minion.h"
#include "spell.h"
#include "Deck.h"
#include "board.h"

class Board;

class Player {
private:
    std::string name;
    int playerNum;
    Player* opponent;
    Board* board;
    const int max_health = 30;
    int health;
    int max_mana;
    int cur_mana;
    Deck* deck;
    std::vector<Card*> hand;
public:
    Player(std::string name, Deck* deck);
    ~Player();
    std::string getName() const;
    int getPlayerNum() const;
    int getHealth() const;
    int getMaxMana() const;
    int getCurMana() const;
    std::vector<Card*> getHandCards() const;
    Player* getOpponent() const;
    Board* getBoard() const;
    Deck* getDeck() const;
    void setPlayerNum(int num);
    void setHealth(int h); 
    void setMaxMana(int mana);
    void setCurMana(int mana);
    void setOpponent(Player *p);
    void setBoard(Board *b);
    void setDeck(Deck *d);
    void drawCard();
    void addCardToHand(Card* c);
    void takeDamage(int damage);
    void summonMinion(int handIndex);
    void castSpell(int handIndex);
    void attackHero(int MinionIndex);
    void attackMinion(int attackerIndex, int targetIndex);
    void printHand();
    void startTurn();
    void endTurn();
    bool isDead() const;
};

#endif // PLAYER_H
