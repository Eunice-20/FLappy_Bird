#ifndef FLECHES_H
#define FLECHES_H
#include "raylib.h"

typedef struct {
    Vector2 posi;     // pointe
    float vitesseCh;    // vitesse de chute
} Fleche;


Fleche CreerFleche(int colonne, int nbColonnes, int larg_ecran);
void MajFleche(Fleche *fleche, int larg_ecran, int haut_ecran);
void DessinerFleche(Fleche fleche);
Rectangle RectFleche(Fleche fleche);

#endif