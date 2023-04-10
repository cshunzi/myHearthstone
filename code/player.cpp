#include "Player.h"
#include <iostream>

Player::Player(std::string name, Deck* deck) : name(name), health(30), max_mana(0), cur_mana(0), deck(deck) {}

Player::~Player() {
    delete deck;
    for (Card* c : hand) {
        delete c;
    }
}

std::string Player::getName() const {
    return name;
}

int Player::getPlayerNum() const {
    return playerNum;
}

int Player::getHealth() const {
    return health;
}

int Player::getMaxMana() const {
    return max_mana;
}

int Player::getCurMana() const {
    return cur_mana;
}

std::vector<Card*> Player::getHandCards() const {
    return hand;
}

Player* Player::getOpponent() const {
    return opponent;
}

Board* Player::getBoard() const {
    return board;
}

Deck* Player::getDeck() const {
    return deck;
}

void Player::setPlayerNum(int num) {
    this->playerNum = num;
}

void Player::setHealth(int h) {
    this->health = h;
}

void Player::setMaxMana(int mana) {
    this->max_mana = mana;
}

void Player::setCurMana(int mana) {
    this->cur_mana = mana;
}

void Player::setOpponent(Player* p) {
    this->opponent = p;
}

void Player::setBoard(Board *b) {
    this->board = b;
}

void Player::setDeck(Deck* d) {
    this->deck = d;
}

void Player::drawCard() {
    if (deck->getSize() > 0) {
        hand.push_back(deck->drawCard());
    }
}

void Player::addCardToHand(Card* c) {
    hand.push_back(c);
}

void Player::takeDamage(int damage) {
    this->health -= damage;
    std::cout << this->name << " 受到了 " << damage << " 点伤害. ";
    std::cout << this->name << " 现在有 " << this->health << " 生命值." << std::endl;
    if (this->isDead()) {
        std::cout << this->name << " 失败了." << std::endl;
    }
}

void Player::summonMinion(int handIndex) {
    if (handIndex < 0 || (size_t)handIndex >= this->hand.size()) {
        std::cout << "Invalid hand index!" << std::endl;
        return;
    }
    Card* card = this->hand[handIndex];
    Minion* minion = new Minion(*dynamic_cast<Minion*>(card));
    if (cur_mana >= minion->getCost())
    {
        this->board->addMinion(minion, playerNum);
        cur_mana -= minion->getCost();
        std::cout << this->name << " 召唤了 " << minion->getName() << "." << std::endl;
        this->hand.erase(this->hand.begin() + handIndex);
    }
    else
        std::cout << "你没有足够的法力值！" << std::endl;
}

void Player::castSpell(int handIndex) {
    if (handIndex < 0 || (size_t)handIndex >= this->hand.size()) {
        std::cout << "Invalid hand index!" << std::endl;
        return;
    }
    Card* card = this->hand[handIndex];
    Spell* spell = dynamic_cast<Spell*>(card); // 尝试转换类型
    if (spell)
    {
        spell->use(this); // 为当前玩家使用此法术
        if (cur_mana >= spell->getCost())
        {
            cur_mana -= spell->getCost();
            this->hand.erase(this->hand.begin() + handIndex);
        }
        else
            std::cout << "你没有足够的法力值！" << std::endl;
    }
    else
        std::cout << "此牌不是法术！" << std::endl;
}

void Player::attackHero(int minionIndex) {
    // 获取攻击随从
    Minion* attacker = this->board->getMinion(minionIndex, playerNum);
    if (!attacker) {
        std::cout << "没有这个随从！" << std::endl;
        return;
    }
    // 检查攻击状态
    if (attacker->getCanAttack())
    {
        // 扣除对手玩家生命值
        opponent->takeDamage(attacker->getAttack());

        // 打印输出攻击信息
        std::cout << "随从 " << attacker->getName() << " 攻击了英雄，造成 " << attacker->getAttack() << " 点伤害！\n";

        // 更新攻击状态
        attacker->setCanAttack(false); // 一回合只能攻击一次

        // 如果对手玩家死亡，则结束游戏
        if (opponent->health <= 0) {
            std::cout << "对手英雄死亡，你赢得了胜利！\n";
            //this->board->endGame();
        }
    }
    else
        std::cout << "该随从还不能攻击或者本回合已经攻击过！" << std::endl;
}

void Player::attackMinion(int attackerIndex, int targetIndex) {
    // 获取攻击随从
    Minion* attacker = this->board->getMinion(attackerIndex, playerNum);
    if (!attacker) {
        std::cout << "没有这个随从！" << std::endl;
        return;
    }
    //检查攻击状态
    if (attacker->getCanAttack())
    {
        // 获取目标随从
        Minion* target = this->board->getMinion(targetIndex, this->getOpponent()->getPlayerNum());
        if (!target) {
            std::cout << "没有这个随从！" << std::endl;
            return;
        }
        // 扣除目标随从生命值
        target->setCurHP(target->getCurHP()-attacker->getAttack());

        // 扣除攻击随从生命值
        attacker->setCurHP(attacker->getCurHP()- target->getAttack());

        // 打印输出攻击信息
        std::cout << "随从 " << attacker->getName() << " 攻击了 " << target->getName() << "," << target->getName() << " 受到了 " << attacker->getAttack() << " 点伤害，" << attacker->getName() << " 受到了 " << target->getAttack() << " 点伤害！\n";

        // 如果攻击随从死亡，则从战场上移除
        if (attacker->getCurHP() <= 0) {
            std::cout << attacker->getName() << " 死亡！\n";
            this->board->removeMinion(attackerIndex, playerNum);
        }

        // 如果目标随从死亡，则从战场上移除
        if (target->getCurHP() <= 0) {
            std::cout << target->getName() << " 死亡！\n";
            this->board->removeMinion(targetIndex, this->getOpponent()->getPlayerNum());
        }
    }
    else
        std::cout << "该随从还不能攻击或者本回合已经攻击过！" << std::endl;
}


void Player::printHand() {
    for (size_t i = 0; i < hand.size(); i++)
    {
        std::cout << '[' << i + 1 << ']';
        hand[i]->printCardInfo();
    }
}

void Player::startTurn() {
    max_mana++;
    cur_mana = max_mana;
    this->drawCard();
    this->board->resetCanAttack(playerNum);
}

void Player::endTurn() {
    //cur_mana = 0;
}

bool Player::isDead() const {
    return health <= 0;
}
