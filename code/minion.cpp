#include "Minion.h"
#include <iostream>

Minion::Minion(std::string name, int cost, int attack, int health) :
    Card(name, cost), attack(attack), health(health) {curHP = health; canAttack = false;}

void Minion::printCardInfo() const {
    std::cout << "卡牌名称: " << getName() << ", ";
    std::cout << "类型：随从" << ", ";
    std::cout << "法力值消耗： " << getCost() << ", ";
    std::cout << "攻击力： " << attack << ", ";
    std::cout << "生命值： " << health << std::endl;
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
