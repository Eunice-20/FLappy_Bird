#include "raylib.h"
#include "bird.h"
#include "pipes.h"
//------------------------
#define NB_TUYAUX 3
#define ESPACE_TUYAUX 290   

int main(void)
{
    const int larg_ecran = 800;
    const int haut_ecran = 600;

    InitWindow(larg_ecran, haut_ecran, "Flappy Bird");
    SetTargetFPS(60);

    Font Police_Df = LoadFontEx("Police_Dafont/LSD.otf", 64, 0, 0);
    SetTextureFilter(Police_Df.texture, TEXTURE_FILTER_BILINEAR);

    Bird bird = CreerBird(200, haut_ecran / 2.0f);   // on crée l'oiseau ( fonction dans bird.c)
    Pipe tuyaux[NB_TUYAUX]; // on crée les tuyau
    for (int i = 0; i < NB_TUYAUX; i++)
    {
        tuyaux[i] = CreerPipe(larg_ecran);
        tuyaux[i].x = larg_ecran + i * ESPACE_TUYAUX;   // chacun un peu plus loin
    }

    while (!WindowShouldClose())
    {
        MajBird(&bird, larg_ecran, haut_ecran);      // attribution de adresse brid.c (met à jour l'oiseau)
       // MajPipe(&tuyau, larg_ecran, haut_ecran);     // le tuyau avance

       for (int i = 0; i < NB_TUYAUX; i++)
        {
            MajPipe(&tuyaux[i], larg_ecran, haut_ecran);
        // les deux parties du tuyau, sous forme de rectangles
        //---------------------------------------------------------------------------------------------------------------------------------

            Rectangle tuyauHaut = {
                 tuyaux[i].x,
                 0, tuyaux[i].largTu, 
                 tuyaux[i].HtrouY };     
            Rectangle tuyauBas  = { 
                tuyaux[i].x, 
                tuyaux[i].HtrouY + tuyaux[i].trouHaut,                // clal fin de trou
                tuyaux[i].largTu,
                haut_ecran - tuyaux[i].HtrouY - tuyaux[i].trouHaut }; // clal hauteur tuyau bas

            if (CheckCollisionCircleRec(bird.posi, bird.rayon, tuyauHaut) || CheckCollisionCircleRec(bird.posi, bird.rayon, tuyauBas))
            {
                bird.posi.x = tuyaux[i].x - bird.rayon;
                bird.cibleX = bird.posi.x;
            }
        //--------------------------------------------------------------------------------------------------------------------------------- 

        }   

        BeginDrawing();
        ClearBackground((Color){ 64, 224, 208, 255 });
        //DessinerPipe(tuyau, haut_ecran);
            for (int i = 0; i < NB_TUYAUX; i++)
            { DessinerPipe(tuyaux[i], haut_ecran);}

        DessinerBird(bird);
        DrawTextEx(Police_Df, "Espace Game Bird", (Vector2){ 20, 20 }, 24, 2, PINK);
        EndDrawing();
    }

    UnloadFont(Police_Df);
    CloseWindow();
    return 0;
}