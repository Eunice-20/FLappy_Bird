#include "fleches.h"

// Chaque flèche tombe dans sa colonne, à un endroit au hasard dedans
Fleche CreerFleche(int colonne, int nbColonnes, int larg_ecran)
{
    Fleche fleche;
    int largCol = larg_ecran / nbColonnes;
    fleche.posi = (Vector2){ colonne * largCol + GetRandomValue(10, largCol - 10), GetRandomValue(-600, -50) };
    fleche.vitesseCh = GetRandomValue(200, 350);
    return fleche;
}

void MajFleche(Fleche *fleche, int larg_ecran, int haut_ecran)
{
    fleche->posi.y += fleche->vitesseCh * GetFrameTime();   // tombe tout droit
    if (fleche->posi.y - 60 > haut_ecran) {
        fleche->posi.y = GetRandomValue(-1200, -50);  // remonte, dans la même colonne
        fleche->vitesseCh = GetRandomValue(200, 350);
    }
}

// Le rectangle qui sert aux collisions
Rectangle RectFleche(Fleche fleche)
{
    return (Rectangle){ fleche.posi.x - 6, fleche.posi.y - 60, 12, 60 };
}

void DessinerFleche(Fleche fleche)
{
    DrawRectangle(fleche.posi.x - 3, fleche.posi.y - 60, 6, 45, BROWN);          // le bâton
    DrawTriangle((Vector2){ fleche.posi.x - 10, fleche.posi.y - 18 },
                 (Vector2){ fleche.posi.x, fleche.posi.y },
                 (Vector2){ fleche.posi.x + 10, fleche.posi.y - 18 }, GRAY);     // la pointe
}