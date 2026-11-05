#include "blocs.h"

Bloc CreerBloc(int larg_ecran, int haut_ecran)
{
    Bloc bloc;
    float taille = GetRandomValue(50, 90);
    bloc.rect = (Rectangle){ larg_ecran, GetRandomValue(0, haut_ecran - taille), taille, taille };
    bloc.vitesse = 200.0f;
    return bloc;
}

// Le bloc avance vers la gauche, et revient à droite quand il sort

void MajBloc(Bloc *bloc, int larg_ecran, int haut_ecran)
{
    bloc->rect.x -= bloc->vitesse * GetFrameTime();
    if (bloc->rect.x + bloc->rect.width < 0)
        *bloc = CreerBloc(larg_ecran, haut_ecran);
}

void DessinerBloc(Bloc bloc)
{
    DrawRectangleRec(bloc.rect, DARKBLUE);
}