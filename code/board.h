#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "minion.h"
#include "player.h"

class Player;

class Board {
public:
    Board(Player* player1, Player* player2) {
        this->player1 = player1; this->player2 = player2;
        // Initialize the board with empty vectors for both players
        this->player1Minions = std::vector<Minion*>(0);
        this->player2Minions = std::vector<Minion*>(0);
    };
    void display() const;
    void resetCanAttack(int playerNum);
    void addMinion(Minion* minion, int playerNum);
    void removeMinion(int index, int playerNum);
    Minion* getMinion(int index, int playerNum) const;
    int getNumMinions(int playerNum) const;
private:
    std::vector<Minion*> player1Minions;
    std::vector<Minion*> player2Minions;
    Player *player1;
    Player *player2;
};

#endif // BOARD_H
