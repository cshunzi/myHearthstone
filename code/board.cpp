#include <iostream>
#include "board.h"

void Board::resetCanAttack(int playerNum) {
    if (playerNum == 1)
        for (size_t i = 0; i < player1Minions.size(); ++i) player1Minions[i]->setCanAttack(true);
    else
        for (size_t i = 0; i < player2Minions.size(); ++i) player2Minions[i]->setCanAttack(true);
}

void Board::addMinion(Minion* minion, int playerNum) {
    if (playerNum == 1) {
        this->player1Minions.push_back(minion);
    } else if (playerNum == 2) {
        this->player2Minions.push_back(minion);
    }
}

void Board::removeMinion(int index, int playerNum) {
    if (playerNum == 1) {
        this->player1Minions.erase(this->player1Minions.begin() + index);
    } else if (playerNum == 2) {
        this->player2Minions.erase(this->player2Minions.begin() + index);
    }
}

Minion* Board::getMinion(int index, int playerNum) const {
    if (playerNum == 1) {
        if (index >= player1Minions.size()) return nullptr;
        return this->player1Minions[index];
    } else if (playerNum == 2) {
        if (index >= player2Minions.size()) return nullptr;
        return this->player2Minions[index];
    }
    return nullptr;
}

int Board::getNumMinions(int playerNum) const {
    if (playerNum == 1) {
        return this->player1Minions.size();
    } else if (playerNum == 2) {
        return this->player2Minions.size();
    }
    return 0;
}

void Board::display() const {
    std::cout << std::endl << std::endl;
    // ��ӡ���1����Ϣ
    std::cout << "--------------- ���1 ---------------" << std::endl;
    std::cout << "�������: " << player1->getName() << std::endl;
    std::cout << "��ǰ����ˮ��: " << player1->getCurMana() << "/" << player1->getMaxMana() << std::endl;
    std::cout << "Ӣ��Ѫ��: " << player1->getHealth() << std::endl;
    std::cout << "����: ";
    std::vector<Card*> player1_hand = player1->getHandCards();
    for (size_t i = 0; i < player1_hand.size(); ++i) {
        std::cout << "[" << i + 1 << "]" << player1_hand[i]->getName() << " ";
    }
    std::cout << std::endl << std::endl;
    std::cout << "�������: ";
    for (size_t i = 0; i < player1Minions.size(); ++i) {
        std::cout << "[" << i + 1 << "]" << player1Minions[i]->getName() << 
        "(" << player1Minions[i]->getAttack() << '/' << player1Minions[i]->getCurHP() << ") ";
    }
    std::cout << std::endl << std::endl;

    // ��ӡ���2����Ϣ
    std::cout << "--------------- ���2 ---------------" << std::endl;
    std::cout << "�������: " << player2->getName() << std::endl;
    std::cout << "��ǰ����ˮ��: " << player2->getCurMana() << "/" << player2->getMaxMana() << std::endl;
    std::cout << "Ӣ��Ѫ��: " << player2->getHealth() << std::endl;
    std::cout << "����: ";
    std::vector<Card*> player2_hand = player2->getHandCards();
    for (size_t i = 0; i < player2_hand.size(); ++i) {
        std::cout << "[" << i + 1 << "]" << player2_hand[i]->getName() << " ";
    }
    std::cout << std::endl << std::endl;
    std::cout << "�������: ";
    for (size_t i = 0; i < player2Minions.size(); ++i) {
        std::cout << "[" << i + 1 << "]" << player2Minions[i]->getName() << 
        "(" << player2Minions[i]->getAttack() << '/' << player2Minions[i]->getCurHP() << ") ";
    }
    std::cout << std::endl << std::endl;
}