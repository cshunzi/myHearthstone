#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
public:
    Card(std::string name, int cost);
    virtual ~Card() = default;
    std::string getName() const;
    int getCost() const;
    virtual void printCardInfo() const = 0;

private:
    std::string name;
    int cost;
};

#endif
