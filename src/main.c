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
#define NB_FLECHES 6
//------------------------
#define NB_IMAGES 4          

int main(void)
{
    const int larg_ecran = 1000;
    const int haut_ecran = 800;
    float decorX = 0;
    float solX = 0;
    float cielX = 0;
    float zoomSol = 2;    
    float tempsAnim = 0;  
    int imageActuelle = 0; 


    InitWindow(larg_ecran, haut_ecran, "Flappy Bird");

    Texture2D texCiel = LoadTexture("assets/Sky_Islands/sky_G.png");
    SetTextureFilter(texCiel, TEXTURE_FILTER_POINT);

    Texture2D texOiseau = LoadTexture("assets/Birds_Paid_Carysaurus/YellowBird/YellowBird-Fly.png");
    SetTextureFilter(texOiseau, TEXTURE_FILTER_POINT);

    Texture2D texSol = LoadTexture("assets/Sky_Islands/tiles_meadow.png");
    SetTextureFilter(texSol, TEXTURE_FILTER_POINT);

    Texture2D texTuyau = LoadTexture("assets/Sky_Islands/pipe.png");
    SetTextureFilter(texTuyau, TEXTURE_FILTER_POINT);


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
        
        // limite sol
            float limiteSol = texSol.height * zoomSol;
            float ySolLimite = haut_ecran -  limiteSol;
            //------------------------------------
            // la moitié de la hauteur de l'oiseau 
            float demiOiseau = texOiseau.height * 3 / 2.0f;
            //-------------------------------------

            if (bird.posi.y > ySolLimite - demiOiseau) {
                bird.posi.y = ySolLimite - demiOiseau;
            }
        //

        MajGame(&game);
       // MajPipe(&tuyau, larg_ecran, haut_ecran);    

        decorX -= 200.0f * GetFrameTime();  
        if (decorX <= -40) decorX += 40;   
        
        solX -= 200.0f * GetFrameTime();
        if (solX <= -texSol.width * zoomSol) solX += texSol.width * zoomSol;

        cielX -= 30.0f * GetFrameTime();
        if (cielX <= -larg_ecran) cielX += larg_ecran;

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

        tempsAnim += GetFrameTime();
        if (tempsAnim >= 0.08f) {
            tempsAnim = 0;
            imageActuelle = (imageActuelle + 1) % NB_IMAGES;
        }

        BeginDrawing();
        ClearBackground((Color){ 64, 224, 208, 255 });

        Rectangle srcCiel = { 0, 0, texCiel.width, texCiel.height };
        DrawTexturePro(texCiel, srcCiel, (Rectangle){ cielX, 0, larg_ecran, haut_ecran }, (Vector2){ 0, 0 }, 0, WHITE);
        DrawTexturePro(texCiel, srcCiel, (Rectangle){ cielX + larg_ecran, 0, larg_ecran, haut_ecran }, (Vector2){ 0, 0 }, 0, WHITE);


        float largSol = texSol.width * zoomSol;
        float hautSol = texSol.height * zoomSol;
        float ySol = haut_ecran - hautSol; //  bas de l'écran
        // x = 0
        for (float x = solX; x < larg_ecran; x += largSol) {
               DrawTextureEx(texSol, (Vector2){ x, ySol }, 0, zoomSol, WHITE);
        }

        //DessinerPipe(tuyau, haut_ecran);
        if (game.niveau == 1) {
            for (int i = 0; i < NB_TUYAUX; i++){ 
                DessinerPipe(tuyaux[i], haut_ecran, texTuyau);
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

        int largImage = texOiseau.width / NB_IMAGES;
        Rectangle source = { imageActuelle * largImage, 0, largImage, texOiseau.height };
        float zoom = 3;
        Rectangle dest = { bird.posi.x, bird.posi.y, largImage * zoom, texOiseau.height * zoom };
        Vector2 centre = { dest.width / 2, dest.height / 2 };
        DrawTexturePro(texOiseau, source, dest, centre, 0, WHITE);
        DrawTextEx(Police_Df, "Espace Game Bird", (Vector2){ 20, 20 }, 24, 2, PINK);
        DrawTextEx(Police_Df, TextFormat("%d m - Niveau %d", (int)game.distance, game.niveau), (Vector2){ 20, 50 }, 24, 2, PINK);
        EndDrawing();
    }

    UnloadTexture(texCiel);
    UnloadTexture(texOiseau);
    UnloadTexture(texSol);
    UnloadTexture(texTuyau);
    UnloadFont(Police_Df);
    CloseWindow();
    return 0;
}