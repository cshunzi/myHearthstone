#include "Card.h"

Card::Card(std::string name, int cost) : name(name), cost(cost) {}

std::string Card::getName() const {
    return name;
}

int Card::getCost() const {
    return cost;
}
