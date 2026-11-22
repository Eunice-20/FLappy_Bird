#include "bonus.h"

Bonus CreerBonus(int larg, int haut) {
    return (Bonus){ { larg + GetRandomValue(0, 600), GetRandomValue(50, haut - 150), 32, 32 }, true };
}
void MajBonus(Bonus *bonus, int larg, int haut, float vitesse) {
    bonus->rect.x -= vitesse * GetFrameTime();
    if (bonus->rect.x < -bonus->rect.width) *bonus = CreerBonus(larg, haut);
}