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
    std::cout << this->name << " �ܵ��� " << damage << " ���˺�. ";
    std::cout << this->name << " ������ " << this->health << " ����ֵ." << std::endl;
    if (this->isDead()) {
        std::cout << this->name << " ʧ����." << std::endl;
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
        std::cout << this->name << " �ٻ��� " << minion->getName() << "." << std::endl;
        this->hand.erase(this->hand.begin() + handIndex);
    }
    else
        std::cout << "��û���㹻�ķ���ֵ��" << std::endl;
}

void Player::castSpell(int handIndex) {
    if (handIndex < 0 || (size_t)handIndex >= this->hand.size()) {
        std::cout << "Invalid hand index!" << std::endl;
        return;
    }
    Card* card = this->hand[handIndex];
    Spell* spell = dynamic_cast<Spell*>(card); // ����ת������
    if (spell)
    {
        spell->use(this); // Ϊ��ǰ���ʹ�ô˷���
        if (cur_mana >= spell->getCost())
        {
            cur_mana -= spell->getCost();
            this->hand.erase(this->hand.begin() + handIndex);
        }
        else
            std::cout << "��û���㹻�ķ���ֵ��" << std::endl;
    }
    else
        std::cout << "���Ʋ��Ƿ�����" << std::endl;
}

void Player::attackHero(int minionIndex) {
    // ��ȡ�������
    Minion* attacker = this->board->getMinion(minionIndex, playerNum);
    if (!attacker) {
        std::cout << "û�������ӣ�" << std::endl;
        return;
    }
    // ��鹥��״̬
    if (attacker->getCanAttack())
    {
        // �۳������������ֵ
        opponent->takeDamage(attacker->getAttack());

        // ��ӡ���������Ϣ
        std::cout << "��� " << attacker->getName() << " ������Ӣ�ۣ���� " << attacker->getAttack() << " ���˺���\n";

        // ���¹���״̬
        attacker->setCanAttack(false); // һ�غ�ֻ�ܹ���һ��

        // �����������������������Ϸ
        if (opponent->health <= 0) {
            std::cout << "����Ӣ����������Ӯ����ʤ����\n";
            //this->board->endGame();
        }
    }
    else
        std::cout << "����ӻ����ܹ������߱��غ��Ѿ���������" << std::endl;
}

void Player::attackMinion(int attackerIndex, int targetIndex) {
    // ��ȡ�������
    Minion* attacker = this->board->getMinion(attackerIndex, playerNum);
    if (!attacker) {
        std::cout << "û�������ӣ�" << std::endl;
        return;
    }
    //��鹥��״̬
    if (attacker->getCanAttack())
    {
        // ��ȡĿ�����
        Minion* target = this->board->getMinion(targetIndex, this->getOpponent()->getPlayerNum());
        if (!target) {
            std::cout << "û�������ӣ�" << std::endl;
            return;
        }
        // �۳�Ŀ���������ֵ
        target->setCurHP(target->getCurHP()-attacker->getAttack());

        // �۳������������ֵ
        attacker->setCurHP(attacker->getCurHP()- target->getAttack());

        // ��ӡ���������Ϣ
        std::cout << "��� " << attacker->getName() << " ������ " << target->getName() << "," << target->getName() << " �ܵ��� " << attacker->getAttack() << " ���˺���" << attacker->getName() << " �ܵ��� " << target->getAttack() << " ���˺���\n";

        // �������������������ս�����Ƴ�
        if (attacker->getCurHP() <= 0) {
            std::cout << attacker->getName() << " ������\n";
            this->board->removeMinion(attackerIndex, playerNum);
        }

        // ���Ŀ��������������ս�����Ƴ�
        if (target->getCurHP() <= 0) {
            std::cout << target->getName() << " ������\n";
            this->board->removeMinion(targetIndex, this->getOpponent()->getPlayerNum());
        }
    }
    else
        std::cout << "����ӻ����ܹ������߱��غ��Ѿ���������" << std::endl;
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
