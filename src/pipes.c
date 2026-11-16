#include "pipes.h"

//creation tuyau au bord droit
Pipe CreerPipe(int larg_ecran)
{
    Pipe pipes;
    pipes.x = larg_ecran;
    pipes.HtrouY = 250;
    pipes.largTu = 140;
    pipes.trouHaut = 130;
    pipes.vitesseD = 1.0f;
    return pipes;
}

// Dessine les deux parties du tuyau
void DessinerPipe(Pipe pipes, int haut_ecran, Texture2D tex)
{
    Rectangle src = { 0, 0, tex.width, tex.height };
    Rectangle srcRetourne = { 0, 0, tex.width, -tex.height };

    // haut : bouche vers le bas
    DrawTexturePro(tex, src, (Rectangle){ pipes.x, 0, pipes.largTu, pipes.HtrouY }, (Vector2){0,0}, 0, WHITE);
    // bas : retourné, bouche vers le haut
    DrawTexturePro(tex, srcRetourne, (Rectangle){ pipes.x, pipes.HtrouY + pipes.trouHaut, pipes.largTu, haut_ecran - pipes.HtrouY - pipes.trouHaut }, (Vector2){0,0}, 0, WHITE);
}

// Fait avancer le tuyau vers la gauche
void MajPipe(Pipe *pipes, int larg_ecran, int haut_ecran)
{
    pipes->x -= pipes->vitesseD;

    // Verification,  on le remet à droite
    if (pipes->x < -pipes->largTu)
    {
        pipes->x = larg_ecran;
        // nouveau trou hauteur random
        pipes->HtrouY = GetRandomValue(80, haut_ecran - 80 - (int)pipes->trouHaut);
    }
}