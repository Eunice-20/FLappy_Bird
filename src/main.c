#include "raylib.h"
#include "bird.h"
#include "pipes.h"
#include "game.h"
#include "blocs.h"
#include "fleches.h"
//------------------------
#define NB_TUYAUX 3
#define ESPACE_TUYAUX 290   
//------------------------
#define NB_BLOCS 4
#define ESPACE_BLOCS 220
//------------------------
#define NB_FLECHES 10

int main(void)
{
    const int larg_ecran = 800;
    const int haut_ecran = 600;
    float decorX = 0;   

    InitWindow(larg_ecran, haut_ecran, "Flappy Bird");
    SetTargetFPS(60);

    Font Police_Df = LoadFontEx("Police_Dafont/LSD.otf", 64, 0, 0);
    SetTextureFilter(Police_Df.texture, TEXTURE_FILTER_BILINEAR);

    Bird bird = CreerBird(200, haut_ecran / 2.0f);   // on crée l'oiseau ( fonction dans bird.c)
    Pipe tuyaux[NB_TUYAUX]; // on crée les tuyau
    for (int i = 0; i < NB_TUYAUX; i++){
        tuyaux[i] = CreerPipe(larg_ecran);
        tuyaux[i].x = larg_ecran + i * ESPACE_TUYAUX;   
    }

    Game game = CreerGame();  

    Bloc blocs[NB_BLOCS];
    for (int i = 0; i < NB_BLOCS; i++) {
        blocs[i] = CreerBloc(larg_ecran, haut_ecran);
        blocs[i].rect.x = larg_ecran + i * ESPACE_BLOCS;   //écart blocS
    }
    Fleche fleches[NB_FLECHES];
    for (int i = 0; i < NB_FLECHES; i++) {
       fleches[i] = CreerFleche(i, NB_FLECHES, larg_ecran);
    }
   // fleches[i] = CreerFleche(i, NB_FLECHES, larg_ecran);
    
    while (!WindowShouldClose()){
        MajBird(&bird, larg_ecran, haut_ecran);      
        MajGame(&game);
       // MajPipe(&tuyau, larg_ecran, haut_ecran);     // le tuyau avance

     decorX -= 200.0f * GetFrameTime();  
        if (decorX <= -40) decorX += 40;    

        // les deux parties du tuyau, sous forme de rectangles
        //---------------------------------------------------------------------------------------------------------------------------------

        if (game.niveau == 1) {
            for (int i = 0; i < NB_TUYAUX; i++){

                MajPipe(&tuyaux[i], larg_ecran, haut_ecran);

                Rectangle tuyauHaut = {
                    tuyaux[i].x,
                    0, tuyaux[i].largTu, 
                    tuyaux[i].HtrouY };     
                Rectangle tuyauBas  = { 
                    tuyaux[i].x, 
                    tuyaux[i].HtrouY + tuyaux[i].trouHaut,                // clal fin de trou
                    tuyaux[i].largTu,
                    haut_ecran - tuyaux[i].HtrouY - tuyaux[i].trouHaut }; // clal hauteur tuyau bas

                if (CheckCollisionCircleRec(bird.posi, bird.rayon, tuyauHaut) || CheckCollisionCircleRec(bird.posi, bird.rayon, tuyauBas)){
                    bird.posi.x = tuyaux[i].x - bird.rayon;
                    bird.cibleX = bird.posi.x;
                }
            }
        }

        if (game.niveau == 2) {
            for (int i = 0; i < NB_BLOCS; i++) {
                MajBloc(&blocs[i], larg_ecran, haut_ecran);

                if (CheckCollisionCircleRec(bird.posi, bird.rayon, blocs[i].rect)) {
                    bird.posi.x = blocs[i].rect.x - bird.rayon;
                    bird.cibleX = bird.posi.x;
                }
            }
        }

        if (game.niveau == 3) {
            for (int i = 0; i < NB_FLECHES; i++) {
               MajFleche(&fleches[i], larg_ecran, haut_ecran);

               // touché -> la flèche disparaît (-1 vie)
               if (CheckCollisionCircleRec(bird.posi, bird.rayon, RectFleche(fleches[i]))) {
                    fleches[i] = CreerFleche(i, NB_FLECHES, larg_ecran);
                 }
            }
        }
        //--------------------------------------------------------------------------------------------------------------------------------- 

        BeginDrawing();
        ClearBackground((Color){ 64, 224, 208, 255 });

        DrawRectangle(0, haut_ecran - 30, larg_ecran, 30, DARKGREEN);
          for (int x = decorX; x < larg_ecran; x += 40)
                DrawRectangle(x, haut_ecran - 30, 20, 30, GREEN);


        //DessinerPipe(tuyau, haut_ecran);
        if (game.niveau == 1) {
            for (int i = 0; i < NB_TUYAUX; i++){ 
                DessinerPipe(tuyaux[i], haut_ecran);
            }
        }
        if (game.niveau == 2) {
            for (int i = 0; i < NB_BLOCS; i++)
                DessinerBloc(blocs[i]);
        }
        if (game.niveau == 3) {
            for (int i = 0; i < NB_FLECHES; i++)
                DessinerFleche(fleches[i]);
        }

        DessinerBird(bird);
        DrawTextEx(Police_Df, "Espace Game Bird", (Vector2){ 20, 20 }, 24, 2, PINK);
        DrawTextEx(Police_Df, TextFormat("%d m - Niveau %d", (int)game.distance, game.niveau), (Vector2){ 20, 50 }, 24, 2, PINK);
        EndDrawing();
    }

    UnloadFont(Police_Df);
    CloseWindow();
    return 0;
}