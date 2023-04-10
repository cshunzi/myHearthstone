#include "Minion.h"
#include <iostream>

Minion::Minion(std::string name, int cost, int attack, int health) :
    Card(name, cost), attack(attack), health(health) {curHP = health; canAttack = false;}

void Minion::printCardInfo() const {
    std::cout << "��������: " << getName() << ", ";
    std::cout << "���ͣ����" << ", ";
    std::cout << "����ֵ���ģ� " << getCost() << ", ";
    std::cout << "�������� " << attack << ", ";
    std::cout << "����ֵ�� " << health << std::endl;
}

int Minion::getAttack() const {
    return attack;
}

int Minion::getHealth() const {
    return health;
}

int Minion::getCurHP() const {
    return curHP;
}

bool Minion::getCanAttack() const {
    return canAttack;
}

void Minion::setHealth(int newHealth) {
    health = newHealth;
}

void Minion::setCurHP(int newHP) {
    curHP = newHP;
}

void Minion::setCanAttack(bool f) {
    canAttack = f;
}

bool Minion::isDead() const {
    return health <= 0;
}
