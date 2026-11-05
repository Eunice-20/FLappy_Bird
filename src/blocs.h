#ifndef BLOCS_H
#define BLOCS_H
#include "raylib.h"

typedef struct {
    Rectangle rect;   // posi et taille du bloc
    float vitesse;    // vitesse vers la gauche
} Bloc;

Bloc CreerBloc(int larg_ecran, int haut_ecran);
void MajBloc(Bloc *bloc, int larg_ecran, int haut_ecran);
void DessinerBloc(Bloc bloc);

#endif