#include "Spell.h"
#include <iostream>

Spell::Spell(std::string name, int cost) : Card(name, cost) {}

void Spell::printCardInfo() const {
    std::cout << "卡牌名称： " << getName() << ", ";
    std::cout << "类型：法术" << ", ";
    std::cout << "法力值消耗： " << getCost() << std::endl;
}
