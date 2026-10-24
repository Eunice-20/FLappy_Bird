#ifndef PIPES_H
#define PIPES_H
#include "raylib.h"

typedef struct {
    float x;         // posi HZ tuyau
    float HtrouY;     // Debut trou
    float largTu;      // largeur du tuyau
    float trouHaut;  // (l'espace pour passer)
    float vitesseD;   
} Pipe;

Pipe CreerPipe(int larg_ecran);
void DessinerPipe(Pipe pipes, int haut_ecran);
void MajPipe(Pipe *pipes, int larg_ecran, int haut_ecran);
#endif