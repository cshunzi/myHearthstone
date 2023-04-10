#include "spell.h"

class LuckyCoin : public Spell {
public:
    LuckyCoin(std::string name, int manaCost) : Spell(name, manaCost) {}

    void use(Player* player) override {
        // increase the player's current mana by 1
        int cur_mana = player->getCurMana();
        player->setCurMana(cur_mana + 1);
    }
};