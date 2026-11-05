#ifndef GAME_H
#define GAME_H
#include "raylib.h"

typedef struct {
    float distance;   // mètres parcourus
    int niveau;       // 1 = tuyaux, 2 = blocs, 3 = flèches
} Game;

Game CreerGame(void);
void MajGame(Game *game);

#endif