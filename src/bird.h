#ifndef BIRD_H
#define BIRD_H
#include "raylib.h"

typedef struct {
    Vector2 posi;            
    float vitesseV;           
    float cibleX;            
    float tempsSansGravite;  // chrono 
    float rayon;             
} Bird;

Bird CreerBird(float x, float y);
void DessinerBird(Bird bird);
void MajBird(Bird *bird, int larg_ecran, int haut_ecran);
#endif