// Collisions, score et états du jeu.

#include "game.h"
// Une nouvelle partie commence à 0 m, niveau 1
Game CreerGame(void)
{
    Game game;
    game.distance = 0.0f;
    game.niveau = 1;
    return game;
}
// Fait avancer la partie
void MajGame(Game *game)
{
    game->distance += 10.0f * GetFrameTime();   // 10 mètres par seconde

    if (game->distance >= 200) game->niveau = 3;
    else if (game->distance >= 100) game->niveau = 2;
    else game->niveau = 1;
}