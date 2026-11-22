#include "raylib.h"
#include "bird.h"
#include "pipes.h"
#include "game.h"
#include "blocs.h"
#include "fleches.h"
//------------------------
#include "bonus.h"



//------------------------
#define NB_TUYAUX 4
#define ESPACE_TUYAUX 280   
//------------------------
#define NB_BLOCS 8
#define ESPACE_BLOCS 220
//------------------------
#define NB_FLECHES 8
//------------------------
#define NB_IMAGES_BIRD 4 
#define NB_IMAGES_PIECE 9 
#define ESPACE_PIECES 150
//#define NB_IMAGES_BURGER 17

//------------------------
#define NB_PIECES 12       

int main(void)
{
    const int larg_ecran = 1000;
    const int haut_ecran = 800;
    float decorX = 0;
    float solX = 0;
    float cielX = 0;
    float zoomSol = 2;    
    float tempsAnim = 0;  
    float tempsAimant = 0;
    float tempsBouclier = 0;
    float tempsX2 = 0;
    float tempsBurger = 0;
    int imageBurger = 0;
    int imageActuelle = 0; 
    int nbPieces = 0;
    int imagePiece = 0;
      

    InitWindow(larg_ecran, haut_ecran, "Flappy Bird");

    Texture2D texCiel = LoadTexture("assets/Sky_Islands/sky_G.png");
    SetTextureFilter(texCiel, TEXTURE_FILTER_POINT);

    Texture2D texOiseau = LoadTexture("assets/Birds_Paid_Carysaurus/YellowBird/YellowBird-Fly.png");
    SetTextureFilter(texOiseau, TEXTURE_FILTER_POINT);

    Texture2D texSol = LoadTexture("assets/hurt_bird/tiles_meadow.png");
    SetTextureFilter(texSol, TEXTURE_FILTER_POINT);

    Texture2D texTuyau = LoadTexture("assets/hurt_bird/pipe.png");
    SetTextureFilter(texTuyau, TEXTURE_FILTER_POINT);

    Texture2D texFleche = LoadTexture("assets/hurt_bird/fleche-pixel-art.png");
    SetTextureFilter(texFleche, TEXTURE_FILTER_POINT);

    Texture2D texBloc = LoadTexture("assets/hurt_bird/blocs.png");
    SetTextureFilter(texBloc, TEXTURE_FILTER_POINT);

    Texture2D texPiece = LoadTexture("assets/bonus/coin2_20x20.png");
    SetTextureFilter(texPiece, TEXTURE_FILTER_POINT);


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
         
          if (i % 2 == 0) 
               blocs[i].rect.y = (haut_ecran - blocs[i].rect.height) / 2;       
    }

    Fleche fleches[NB_FLECHES];
    for (int i = 0; i < NB_FLECHES; i++) {
       fleches[i] = CreerFleche(i, NB_FLECHES, larg_ecran);
    }
   // fleches[i] = CreerFleche(i, NB_FLECHES, larg_ecran);
    
   //-------------------------------------------------------
    Bonus pieces[NB_PIECES];

    Bonus aimant = CreerBonus(larg_ecran, haut_ecran);
    aimant.rect.x += GetRandomValue(3000, 6000); // rare
    Texture2D texAimant = LoadTexture("assets/bonus/magnet.png");

    Bonus bouclier = CreerBonus(larg_ecran, haut_ecran);
    bouclier.rect.x += GetRandomValue(2500, 5000);
    Texture2D texBouclier = LoadTexture("assets/bonus/shield.png");

    Bonus Coinx2 = CreerBonus(larg_ecran, haut_ecran);
    Coinx2.rect.width = Coinx2.rect.height = 64;
    Coinx2.rect.x += GetRandomValue(2000, 4000);
    Texture2D texX2 = LoadTexture("assets/bonus/Coin_x2.png");

    Bonus burger = CreerBonus(larg_ecran, haut_ecran);
    burger.rect.x += GetRandomValue(1500, 3000);
    Texture2D texBurger = LoadTexture("assets/bonus/burger_spritesheet.png");

    for (int i = 0; i < NB_PIECES; i++) {
    pieces[i] = CreerBonus(larg_ecran, haut_ecran);
    pieces[i].rect.x = larg_ecran + i * ESPACE_PIECES;
    }

    while (!WindowShouldClose()){
        MajBird(&bird, larg_ecran, haut_ecran);   
        
        // limite sol
            float limiteSol = texSol.height * zoomSol;
            float ySolLimite = haut_ecran -  limiteSol;
            //------------------------------------
            // la moitié de la hauteur de l'oiseau 
            float demiOiseau = texOiseau.height * 1.5f/ 2;
            //-------------------------------------

            if (bird.posi.y > ySolLimite - demiOiseau) {
                bird.posi.y = ySolLimite - demiOiseau;
            }
        //

        MajGame(&game);
       // MajPipe(&tuyau, larg_ecran, haut_ecran);    

       // float vitesseSol = 60;
        float vitesseSol = tuyaux[0].vitesseD * 60;
        if (game.niveau == 2) vitesseSol = 200;
        if (game.niveau == 3) vitesseSol = 250;
        if (tempsBurger > 0) vitesseSol = vitesseSol * 2;
        solX -= vitesseSol * GetFrameTime();

        if (decorX <= -40) decorX += 40;   
        
        if (solX <= -texSol.width * zoomSol) solX += texSol.width * zoomSol;

        cielX -= 30.0f * GetFrameTime();
        if (cielX <= -larg_ecran) cielX += larg_ecran;

        

        // les deux parties du tuyau, sous forme de rectangles
        //---------------------------------------------------------------------------------------------------------------------------------

        if (game.niveau == 1) {
            for (int i = 0; i < NB_TUYAUX; i++){

                MajPipe(&tuyaux[i], larg_ecran, haut_ecran);
                if (tempsBurger > 0) MajPipe(&tuyaux[i], larg_ecran, haut_ecran);

                Rectangle tuyauHaut = {
                    tuyaux[i].x,
                    0, tuyaux[i].largTu, 
                    tuyaux[i].HtrouY };     
                Rectangle tuyauBas  = { 
                    tuyaux[i].x, 
                    tuyaux[i].HtrouY + tuyaux[i].trouHaut,                // clal fin de trou
                    tuyaux[i].largTu,
                    haut_ecran - tuyaux[i].HtrouY - tuyaux[i].trouHaut }; // clal hauteur tuyau bas

                if (tempsBouclier <= 0 && (CheckCollisionCircleRec(bird.posi, bird.rayon, tuyauHaut) || CheckCollisionCircleRec(bird.posi, bird.rayon, tuyauBas))) {
                    bird.posi.x = tuyaux[i].x - bird.rayon;
                    bird.cibleX = bird.posi.x;
                }
            }
        }

        if (game.niveau == 2) {
            for (int i = 0; i < NB_BLOCS; i++) {

                MajBloc(&blocs[i], larg_ecran, haut_ecran);
                if (tempsBurger > 0) MajBloc(&blocs[i], larg_ecran, haut_ecran);
                
               // if (CheckCollisionCircleRec(bird.posi, bird.rayon, blocs[i].rect)) {
                if (tempsBouclier <= 0 && CheckCollisionCircleRec(bird.posi, bird.rayon, blocs[i].rect)) {
                    bird.posi.x = blocs[i].rect.x - bird.rayon;
                    bird.cibleX = bird.posi.x;
                }
            }
        }

        if (game.niveau == 3) {
            for (int i = 0; i < NB_FLECHES; i++) {
               MajFleche(&fleches[i], larg_ecran, haut_ecran);
               if (tempsBurger > 0) MajFleche(&fleches[i], larg_ecran, haut_ecran);

               // touché -> la flèche disparaît (-1 vie)
               if (tempsBouclier <= 0 && CheckCollisionCircleRec(bird.posi, bird.rayon, RectFleche(fleches[i]))) {
                    fleches[i] = CreerFleche(i, NB_FLECHES, larg_ecran);
                }
            }
        }
        //--------------------------------------------------------------------------------------------------------------------------------- 

        tempsAnim += GetFrameTime();
            if (tempsAnim >= 0.08f) {
                tempsAnim = 0;
                imageActuelle = (imageActuelle + 1) % NB_IMAGES_BIRD;
                imagePiece = (imagePiece + 1) % NB_IMAGES_PIECE;
                imageBurger = (imageBurger + 1) % 6;
               // imageBurger = (imageBurger + 1) % NB_IMAGES_BURGER;
            }

        aimant.rect.x -= vitesseSol * GetFrameTime();
            if (aimant.rect.x < -aimant.rect.width) {
                aimant = CreerBonus(larg_ecran, haut_ecran);
                aimant.rect.x += GetRandomValue(3000, 6000);
            }
            if (aimant.actif && CheckCollisionCircleRec(bird.posi, bird.rayon, aimant.rect)) {
                aimant.actif = false;
                tempsAimant = 6;
            }
            if (tempsAimant > 0) tempsAimant -= GetFrameTime();

        bouclier.rect.x -= vitesseSol * GetFrameTime();
            if (bouclier.rect.x < -bouclier.rect.width) {
                bouclier = CreerBonus(larg_ecran, haut_ecran);
                bouclier.rect.x += GetRandomValue(2000, 4000);
            }
            if (bouclier.actif && CheckCollisionCircleRec(bird.posi, bird.rayon, bouclier.rect)) {
                bouclier.actif = false;
                tempsBouclier = 5;
            }
            if (tempsBouclier > 0) tempsBouclier -= GetFrameTime();

        Coinx2.rect.x -= vitesseSol * GetFrameTime();
            if (Coinx2.rect.x < -Coinx2.rect.width) {
                Coinx2 = CreerBonus(larg_ecran, haut_ecran);
                Coinx2.rect.x += GetRandomValue(1000, 2000);
                Coinx2.rect.width = Coinx2.rect.height = 64;
            }
            if (Coinx2.actif && CheckCollisionCircleRec(bird.posi, bird.rayon, Coinx2.rect)) {
                Coinx2.actif = false;
                nbPieces = nbPieces * 2;
                tempsX2 = 7;
            }
            if (tempsX2 > 0) tempsX2 -= GetFrameTime();

        burger.rect.x -= vitesseSol * GetFrameTime();
            if (burger.rect.x < -burger.rect.width) {
                burger = CreerBonus(larg_ecran, haut_ecran);
                burger.rect.x += GetRandomValue(1500, 3000);
                burger.rect.width = burger.rect.height = 50;
            }
            if (burger.actif && CheckCollisionCircleRec(bird.posi, bird.rayon, burger.rect)) {
                burger.actif = false;
                tempsBurger = 5;
                tempsBouclier = 5;   // traverse les obstacles
            }
            if (tempsBurger > 0) tempsBurger -= GetFrameTime();

        for (int i = 0; i < NB_PIECES; i++) {

            if (pieces[i].rect.x < -pieces[i].rect.width) {
                float x = pieces[i].rect.x + NB_PIECES * ESPACE_PIECES;
                pieces[i] = CreerBonus(larg_ecran, haut_ecran);
                pieces[i].rect.x = x;
            }
                MajBonus(&pieces[i], larg_ecran, haut_ecran, vitesseSol);

                    if (tempsAimant > 0) {
                        pieces[i].rect.x += (bird.posi.x - pieces[i].rect.x) * 0.1f;
                        pieces[i].rect.y += (bird.posi.y - pieces[i].rect.y) * 0.1f;
                    }

                   if (pieces[i].actif && CheckCollisionCircleRec(bird.posi, bird.rayon, pieces[i].rect)) {
                        pieces[i].actif = false;
                        nbPieces++;
                    }
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
            for (int i = 0; i < NB_BLOCS; i++) {

                Rectangle srcBloc = { 0, 0, texBloc.width, texBloc.height };
                DrawTexturePro(texBloc, srcBloc, blocs[i].rect, (Vector2){ 0, 0 }, 0, WHITE);
            }
        }
        if (game.niveau == 3) {
            for (int i = 0; i < NB_FLECHES; i++){ 

                Rectangle src = { 0, 0, texFleche.width, texFleche.height };
                DrawTexturePro(texFleche, src, RectFleche(fleches[i]), (Vector2){ 0, 0 }, 0, WHITE);
            }
        }

        int largImage = texOiseau.width / NB_IMAGES_BIRD;
        Rectangle source = { imageActuelle * largImage, 0, largImage, texOiseau.height };
        float zoom = 1.5f;
        Rectangle dest = { bird.posi.x, bird.posi.y, largImage * zoom, texOiseau.height * zoom };
        Vector2 centre = { dest.width / 2, dest.height / 2 };
        int largP = texPiece.width / NB_IMAGES_PIECE;
        int largB = texBurger.width / 6;
        int hautB = texBurger.height / 5;

        DrawTexturePro(texOiseau, source, dest, centre, 0, WHITE);
          
        for (int i = 0; i < NB_PIECES; i++){
             if (pieces[i].actif)DrawTexturePro(texPiece, (Rectangle){ imagePiece * largP, 0, largP, texPiece.height }, pieces[i].rect, (Vector2){0,0}, 0, WHITE);
            } 
        DrawTexturePro(texPiece, (Rectangle){ imagePiece * largP, 0, largP, texPiece.height }, (Rectangle){ 20, 80, 24, 24 }, (Vector2){0,0}, 0, WHITE);
        DrawTextEx(Police_Df, TextFormat("x %d", nbPieces), (Vector2){ 50, 80 }, 24, 2, PINK);
            if (aimant.actif) DrawTexturePro(texAimant, (Rectangle){0,0,texAimant.width,texAimant.height}, aimant.rect, (Vector2){0,0}, 0, WHITE);
            if (bouclier.actif) DrawTexturePro(texBouclier, (Rectangle){0,0,texBouclier.width,texBouclier.height}, bouclier.rect, (Vector2){0,0}, 0, WHITE);
                 if (tempsBouclier > 0) DrawCircleLines(bird.posi.x, bird.posi.y, 35, SKYBLUE);
            if (Coinx2.actif) DrawTexturePro(texX2, (Rectangle){0,0,texX2.width,texX2.height}, Coinx2.rect, (Vector2){0,0}, 0, WHITE);
                 if (tempsX2 > 0) DrawTextEx(Police_Df, "   Coin x2 !", (Vector2){ 100, 80 }, 24, 2, GOLD);
            if (burger.actif) DrawTexturePro(texBurger, (Rectangle){ imageBurger * largB, hautB, largB, hautB }, burger.rect, (Vector2){0,0}, 0, WHITE);
        
            DrawTextEx(Police_Df, "Espace Game Bird", (Vector2){ 20, 20 }, 24, 2, PINK);
        DrawTextEx(Police_Df, TextFormat("%d m - Niveau %d", (int)game.distance, game.niveau), (Vector2){ 20, 50 }, 24, 2, PINK);
        EndDrawing();
    }

    UnloadTexture(texCiel);
    UnloadTexture(texOiseau);
    UnloadTexture(texSol);
    UnloadTexture(texTuyau);
    UnloadTexture(texFleche);
    UnloadTexture(texBloc);
    UnloadTexture(texPiece);
    UnloadTexture(texAimant);
    UnloadTexture(texBouclier);
    UnloadTexture(texX2);
    UnloadTexture(texBurger);
    UnloadFont(Police_Df);
    CloseWindow();
    return 0;
}