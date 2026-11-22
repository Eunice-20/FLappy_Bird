#include "raylib.h"

typedef struct { Rectangle rect; bool actif; } Bonus;
Bonus CreerBonus(int larg, int haut);
void MajBonus(Bonus *bonus, int larg, int haut, float vitesse);