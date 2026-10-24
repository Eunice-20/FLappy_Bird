#include "bird.h"
#define GRAVITE    0.5f
#define SAUT      -8.0f
#define PAS_X     40.0f
#define DOUCEUR_X  0.2f

// Fabrique un oiseau à la position (x, y)
Bird CreerBird(float x, float y)
{
    Bird bird;
    bird.posi.x = x;
    bird.posi.y = y;
    bird.vitesseV = 0.0f;
    bird.cibleX = x;
    bird.tempsSansGravite = 0.0f;
    bird.rayon = 20.0f;
    return bird;
}

// Dessine l'oiseau
void DessinerBird(Bird bird)
{
    DrawCircleV(bird.posi, bird.rayon, YELLOW);
}