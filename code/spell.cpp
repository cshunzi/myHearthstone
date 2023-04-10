#include "Spell.h"
#include <iostream>

Spell::Spell(std::string name, int cost) : Card(name, cost) {}

void Spell::printCardInfo() const {
    std::cout << "�������ƣ� " << getName() << ", ";
    std::cout << "���ͣ�����" << ", ";
    std::cout << "����ֵ���ģ� " << getCost() << std::endl;
}
