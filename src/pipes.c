#include "pipes.h"

//creation tuyau au bord droit
Pipe CreerPipe(int larg_ecran)
{
    Pipe pipes;
    pipes.x = larg_ecran;
    pipes.HtrouY = 250;
    pipes.largTu = 70;
    pipes.trouHaut = 160;
    pipes.vitesseD = 1.0f;
    return pipes;
}

// Dessine les deux parties du tuyau
void DessinerPipe(Pipe pipes, int haut_ecran)
{
    // haut : de 0 jusqu'au début du trou
    DrawRectangle(pipes.x, 0, pipes.largTu, pipes.HtrouY, BROWN );
    // bas : de la fin du trou jusqu'en bas de l'écran
    DrawRectangle(pipes.x, pipes.HtrouY + pipes.trouHaut, pipes.largTu, haut_ecran - pipes.HtrouY - pipes.trouHaut, BROWN);
}

// Fait avancer le tuyau vers la gauche
void MajPipe(Pipe *pipes, int larg_ecran, int haut_ecran)
{
    pipes->x -= pipes->vitesseD;

    // Verification,  on le remet à droite
    if (pipes->x < -pipes->largTu)
    {
        pipes->x = larg_ecran;
        // nouveau trou à une hauteur random
        pipes->HtrouY = GetRandomValue(80, haut_ecran - 80 - (int)pipes->trouHaut);
    }
}