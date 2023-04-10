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
    // �ֳ�ӡ��
    Minion* shitBlizzard = new Minion("��籩ѩ", 1, 2, 1);
    Minion* nomomBlizzard = new Minion("ʯ��ѩ", 2, 3, 2);
    Minion* sbBlizzard = new Minion("��𽱩ѩ", 3, 3, 4);
    Minion* fxxkBlizzard = new Minion("���챩ѩ", 4, 5, 4);
    Minion* holyshit = new Minion("���ȿ��Ͽ�", 6, 6, 6);
    LuckyCoin* coin = new LuckyCoin("���˱�", 0);
    // �������鲢Ϊ�����ӿ��� ÿ��30���ƣ���������Ƹ�6��
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
    // ��������ϴ��
    deck1->shuffle();
    deck2->shuffle();
    // ����������� ��������Ϊ�Է�����
    Player* player1 = new Player("WJGtutu", deck1);
    Player* player2 = new Player("����ح�����ˮ��", deck2);
    player1->setOpponent(player2);
    player2->setOpponent(player1);
    // ����ս��
    Board board(player1, player2);
    player1->setBoard(&board);
    player2->setBoard(&board);
    // ������������Һ�ս������
    player1->setPlayerNum(1); 
    player2->setPlayerNum(2);

    // ȷ���Ⱥ���
    srand((unsigned)time(nullptr));
    int rd = rand() % 2;
    Player* first_player = rd? player1 : player2;
    cout << endl << first_player->getName() << "���������" << endl;
    Player* second_player = first_player->getOpponent();
    for (int i = 0; i < 3; i++) // ���ֳ�������
        first_player->drawCard();
    for (int i = 0; i < 4; i++) // ���ֳ�������
        second_player->drawCard();
    // ������һ�����˱�
    second_player->addCardToHand(coin);
    /*cout << endl << first_player->getName() << "�����ƣ�" << endl;
    first_player->printHand();
    cout << endl << second_player->getName() << "�����ƣ�" << endl;
    second_player->printHand();*/
    Player* current_player = first_player; // ��ǰ�����Ϊ�������

    //board.display();

    // ��ʼ��Ϸ��ѭ��
    while (true) {
        // ��ʼ�غϣ��������ơ���ˮ����������ӿɹ���״̬���߼�
        current_player->startTurn();
        // ��ʾ��ǰ��Ϸ״̬
        board.display();
        // ��ӡ��ǰ�������
        cout << "��ǰ�������:" << endl;
        current_player->printHand();
        while (true)
        {
            // �ȴ���ǰ�������ָ��
            string cmd;
            cout << current_player->getName() << "> ";
            getline(cin, cmd);

            // ����ָ��
            stringstream ss(cmd);
            string op;
            ss >> op;

            if (op == "summon") {
                // �ٻ����
                int index;
                if (ss >> index) {
                    current_player->summonMinion(index - 1);
                } else {
                    cout << "ָ���ʽ: summon <������>" << endl;
                }
            } else if (op == "use") {
                // ʹ�÷���
                int index;
                if (ss >> index) {
                    current_player->castSpell(index - 1);
                } else {
                    cout << "ָ���ʽ: use <�������>" << endl;
                }
            } else if (op == "attack") {
                // ��ӹ���
                int attacker_index, target_index;
                if (ss >> attacker_index >> target_index) {
                    current_player->attackMinion(attacker_index - 1, target_index - 1);
                } else {
                    cout << "ָ���ʽ: attack <���������> <����Ŀ�����>" << endl;
                }
            } else if (op == "face") {
                // ����Ӣ��
                int attacker_index;
                if (ss >> attacker_index) {
                    current_player->attackHero(attacker_index - 1);
                } else {
                    cout << "ָ���ʽ: face <���������>" << endl;
                }
            } else if (op == "display") {
                // ��ʾ��ǰ��Ϸ״̬
                board.display();
            } else if (op == "end") {
                // �����غ�
                current_player->endTurn();
                break;
            } else {
                // ��Чָ��
                cout << "��Чָ�" << endl;
            }
        }
        // ������һ�����
        current_player = current_player->getOpponent();
    }
    // �ͷ���Դ
    delete player1;
    delete player2;
    delete deck1;
    delete deck2;

    return 0;
}
