#include "bird.h"
#define GRAVITE    0.5f
#define SAUT      -8.0f
#define PAS_X     40.0f
#define DOUCEUR_X  0.2f

//  position  oiseau 
Bird CreerBird(float x, float y)
{
    Bird bird;
    bird.posi.x = x; // posi init oiseau en horizontal
    bird.posi.y = y; // Posi init oiseau en vertical
    bird.vitesseV = 0.0f;
    bird.cibleX = x; 
    bird.tempsSansGravite = 0.0f; 
    bird.rayon = 20.0f;
    return bird;
}

// fonction dessine l'oiseau
void DessinerBird(Bird bird)
{
    DrawCircleV(bird.posi, bird.rayon, YELLOW);
}

void MajBird(Bird *bird, int larg_ecran, int haut_ecran)
{
    // déplacement pas lent
    if (IsKeyPressed(KEY_RIGHT)) bird->cibleX += PAS_X; // add 40 unités à cibleX à chaque appui
    if (IsKeyPressed(KEY_LEFT))  bird->cibleX -= PAS_X; 

    if (bird->cibleX > larg_ecran - bird->rayon) 
     { bird->cibleX = larg_ecran - bird->rayon;}
    
    if (bird->cibleX < bird->rayon) 
     { bird->cibleX = bird->rayon;}

    bird->posi.x += (bird->cibleX - bird->posi.x) * DOUCEUR_X;

    // gravité fixe 1s après un déplacement
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT))
    {
        bird->tempsSansGravite = 1.0f;
        bird->vitesseV = 0.0f;
    }
    else if (bird->tempsSansGravite > 0.0f)
    {
        bird->tempsSansGravite -= GetFrameTime();
        bird->vitesseV = 0.0f;
    }
    else
    {
        bird->vitesseV += GRAVITE;
    }

    //Gestion du saut
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE))
    {
        bird->vitesseV = SAUT;
        bird->tempsSansGravite = 0.0f;
    }

    bird->posi.y += bird->vitesseV;

    // bords haut et bas
    if (bird->posi.y > haut_ecran - bird->rayon) { 
        bird->posi.y = haut_ecran - bird->rayon; 
        bird->vitesseV = 0; 
    }

    if (bird->posi.y < bird->rayon) { 
        bird->posi.y = bird->rayon;      
        bird->vitesseV = 0;
     }
}