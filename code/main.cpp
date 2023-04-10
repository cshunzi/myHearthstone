#include "Player.h"
#include "Card.h"
#include "Spell.h"
#include "Minion.h"
#include "Deck.h"
#include "Board.h"
#include "luckycoin.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

int main() {
    // 现场印卡
    Minion* shitBlizzard = new Minion("答辩暴雪", 1, 2, 1);
    Minion* nomomBlizzard = new Minion("石马暴雪", 2, 3, 2);
    Minion* sbBlizzard = new Minion("鲨鸾暴雪", 3, 3, 4);
    Minion* fxxkBlizzard = new Minion("逆天暴雪", 4, 5, 4);
    Minion* holyshit = new Minion("鲍比考迪克", 6, 6, 6);
    LuckyCoin* coin = new LuckyCoin("幸运币", 0);
    // 创建卡组并为玩家添加卡组 每方30张牌，五种随从牌各6张
    Deck* deck1 = new Deck();
    Deck* deck2 = new Deck();
    for (int i = 0; i < 6; i++)
    {
        deck1->addCard(shitBlizzard); deck2->addCard(shitBlizzard);
        deck1->addCard(nomomBlizzard); deck2->addCard(nomomBlizzard);
        deck1->addCard(sbBlizzard); deck2->addCard(sbBlizzard);
        deck1->addCard(fxxkBlizzard); deck2->addCard(fxxkBlizzard);
        deck1->addCard(holyshit), deck2->addCard(holyshit);
    }
    // 将两副牌洗混
    deck1->shuffle();
    deck2->shuffle();
    // 创建两个玩家 各自设置为对方对手
    Player* player1 = new Player("WJGtutu", deck1);
    Player* player2 = new Player("疏星丨启真湖水怪", deck2);
    player1->setOpponent(player2);
    player2->setOpponent(player1);
    // 创建战场
    Board board(player1, player2);
    player1->setBoard(&board);
    player2->setBoard(&board);
    // 玩家序号用于玩家和战场交互
    player1->setPlayerNum(1); 
    player2->setPlayerNum(2);

    // 确定先后手
    srand((unsigned)time(nullptr));
    int rd = rand() % 2;
    Player* first_player = rd? player1 : player2;
    cout << endl << first_player->getName() << "获得了先手" << endl;
    Player* second_player = first_player->getOpponent();
    for (int i = 0; i < 3; i++) // 先手抽三张牌
        first_player->drawCard();
    for (int i = 0; i < 4; i++) // 后手抽四张牌
        second_player->drawCard();
    // 后手玩家获得幸运币
    second_player->addCardToHand(coin);
    /*cout << endl << first_player->getName() << "的手牌：" << endl;
    first_player->printHand();
    cout << endl << second_player->getName() << "的手牌：" << endl;
    second_player->printHand();*/
    Player* current_player = first_player; // 当前玩家设为先手玩家

    //board.display();

    // 开始游戏主循环
    while (true) {
        // 开始回合，包括抽牌、涨水晶、重设随从可攻击状态等逻辑
        current_player->startTurn();
        // 显示当前游戏状态
        board.display();
        // 打印当前玩家手牌
        cout << "当前玩家手牌:" << endl;
        current_player->printHand();
        while (true)
        {
            // 等待当前玩家输入指令
            string cmd;
            cout << current_player->getName() << "> ";
            getline(cin, cmd);

            // 解析指令
            stringstream ss(cmd);
            string op;
            ss >> op;

            if (op == "summon") {
                // 召唤随从
                int index;
                if (ss >> index) {
                    current_player->summonMinion(index - 1);
                } else {
                    cout << "指令格式: summon <随从序号>" << endl;
                }
            } else if (op == "use") {
                // 使用法术
                int index;
                if (ss >> index) {
                    current_player->castSpell(index - 1);
                } else {
                    cout << "指令格式: use <法术序号>" << endl;
                }
            } else if (op == "attack") {
                // 随从攻击
                int attacker_index, target_index;
                if (ss >> attacker_index >> target_index) {
                    current_player->attackMinion(attacker_index - 1, target_index - 1);
                } else {
                    cout << "指令格式: attack <攻击者序号> <攻击目标序号>" << endl;
                }
            } else if (op == "face") {
                // 攻击英雄
                int attacker_index;
                if (ss >> attacker_index) {
                    current_player->attackHero(attacker_index - 1);
                } else {
                    cout << "指令格式: face <攻击者序号>" << endl;
                }
            } else if (op == "display") {
                // 显示当前游戏状态
                board.display();
            } else if (op == "end") {
                // 结束回合
                current_player->endTurn();
                break;
            } else {
                // 无效指令
                cout << "无效指令！" << endl;
            }
        }
        // 更新下一轮玩家
        current_player = current_player->getOpponent();
    }
    // 释放资源
    delete player1;
    delete player2;
    delete deck1;
    delete deck2;

    return 0;
}
