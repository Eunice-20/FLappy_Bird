
// #include "raylib.h"

// int main(void)
// {
//     const int screenWidth = 800;
//     const int screenHeight = 600;
//     // int largeur = MeasureText("Eunice", 40);

//     InitWindow(screenWidth, screenHeight, "Flappy Bird");
//     SetTargetFPS(60);

//     Font Police_Df = LoadFontEx("Police_Dafont/LSD.otf", 64, 0, 0);
//     SetTextureFilter(Police_Df.texture, TEXTURE_FILTER_BILINEAR);

//     while (!WindowShouldClose())
//     {
//         BeginDrawing();

//         ClearBackground((Color){ 64, 224, 208, 255 });
//         DrawTextEx(Police_Df, "Eunice", (Vector2){ 20, 20 }, 20, 2, PINK);
//         //DrawText("Eunice", screenWidth - largeur - 20, 20, 40, PINK);
//         // DrawText("FLAPPY BIRD", 250, 180, 40, WHITE);
//         //DrawTextEx(Police_Df, "Eunice", (Vector2){ 20, 20 }, 250, 180, WHITE);
//         DrawTextEx(Police_Df, "FLAPPY BIRD", (Vector2){ 250, 180 }, 40, 2, WHITE);
//         DrawTextEx(Police_Df, " Yessssss ma goooo ca marche!", (Vector2){ 190, 250 }, 22, 2, DARKBLUE);
//         DrawTextEx(Police_Df, "Click sur 'echap' pour quitter", (Vector2){ 220, 500 }, 20, 2, DARKBLUE);

//         EndDrawing();
//     }
    
//     UnloadFont(Police_Df); // pour éviter les fuites de mémoire
//     CloseWindow();
//     return 0;
// }



//Ancien  main.c code ensemble 

// #include "raylib.h"

// int main(void)
// {
//     const int larg_ecran = 800;
//     const int haut_ecran = 600;

//     InitWindow(larg_ecran, haut_ecran, "Flappy Bird");
//     SetTargetFPS(60);

//     Font Police_Df = LoadFontEx("Police_Dafont/LSD.otf", 64, 0, 0);
//     SetTextureFilter(Police_Df.texture, TEXTURE_FILTER_BILINEAR);

//     // L'oiseau
//     Vector2 birdPosi = { 200, haut_ecran / 2.0f };
//     float birdVitesse = 0.0f;
//     float tempsSansGravite = 0.0f; 
//      float cibleX = birdPosi.x;    
//     //--------------------------------
//     const float douceurX = 0.2f;        
//     const float pasX = 40.0f; // un pas 
//     //--------------------------------
//     const float birdRayon = 20.0f;
//     const float gravite = 0.5f;
//     const float birdsaut = -8.0f;   // négatif = vers le haut

//     while (!WindowShouldClose())
//     {
//         // option : l'oiseau peut se déplacer horizontalement 
//         if (IsKeyPressed(KEY_RIGHT)) cibleX += pasX;
//         if (IsKeyPressed(KEY_LEFT))  cibleX -= pasX;

//         if (cibleX > larg_ecran - birdRayon) cibleX = larg_ecran - birdRayon;
//         if (cibleX < birdRayon) cibleX = birdRayon;

//         // l'oiseau avance un peu vers la cible à chaque image
//         birdPosi.x += (cibleX - birdPosi.x) * douceurX;

//     // pour l'empêcher de sortir de l'écran horizontal  
//         if (birdPosi.x > larg_ecran - birdRayon) {
//             birdPosi.x = larg_ecran - birdRayon;
//         }
//         if (birdPosi.x < birdRayon) {
//             birdPosi.x = birdRayon;
//         }

// //---------------------------------------------------------------------------

//      // mise à jour de la physique de l'oiseau pour gere son deplacement dans l'nvironement
//          //if (IsKeyPressed(KEY_UP)|| IsKeyPressed(KEY_SPACE)) birdVitesse = birdsaut;
//          //birdVitesse += gravite;

//         bool deplacementLen = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT);
            
//         if (deplacementLen)
//             {
//                 tempsSansGravite = 1.0f;   
//                 birdVitesse = 0.0f;        //  hauteur fixe 1s
//             }
//             else if (tempsSansGravite > 0.0f)
//             {
//                 tempsSansGravite -= GetFrameTime(); // chronomètre 
//                 birdVitesse = 0.0f; 
//             }
//             else
//             {
//                 birdVitesse += gravite; 
//             }

//             // le saut reste prioritaire
//             if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE))
//             {
//                 birdVitesse = birdsaut;
//                 tempsSansGravite = 0.0f;
//             }   

//         birdPosi.y += birdVitesse; // deplacement de l'oiseau

//         // ppour l'empêcher de sortir de l'écran vertical
//         if (birdPosi.y > haut_ecran - birdRayon)
//         {
//             birdPosi.y = haut_ecran - birdRayon;
//             birdVitesse = 0;
//         }
//         if (birdPosi.y < birdRayon)
//         {
//             birdPosi.y = birdRayon;
//             birdVitesse = 0;
//         }

//         // dessin  simulation de l'oiseau/textes
//         BeginDrawing();
//         ClearBackground((Color){ 64, 224, 208, 255 });

//         DrawCircleV(birdPosi, birdRayon, YELLOW);
//         DrawTextEx(Police_Df, "Espace Game Bird", (Vector2){ 20, 20 }, 24, 2, PINK);

//         EndDrawing();
//     }

//     UnloadFont(Police_Df);
//     CloseWindow();
//     return 0;
// }