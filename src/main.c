#include "raylib.h"

int main(void)
{
    const int larg_ecran = 800;
    const int haut_ecran = 600;

    InitWindow(larg_ecran, haut_ecran, "Flappy Bird");
    SetTargetFPS(60);

    Font Police_Df = LoadFontEx("Police_Dafont/LSD.otf", 64, 0, 0);
    SetTextureFilter(Police_Df.texture, TEXTURE_FILTER_BILINEAR);

    // L'oiseau
    Vector2 birdPosi = { 200, haut_ecran / 2.0f };
    float birdVitesse = 0.0f;
    float tempsSansGravite = 0.0f; 
     float cibleX = birdPosi.x;    
    //--------------------------------
    const float douceurX = 0.2f;        
    const float pasX = 40.0f; // un pas 
    //--------------------------------
    const float birdRayon = 20.0f;
    const float gravite = 0.5f;
    const float birdsaut = -8.0f;   // négatif = vers le haut

    while (!WindowShouldClose())
    {
        // option : l'oiseau peut se déplacer horizontalement 
        if (IsKeyPressed(KEY_RIGHT)) cibleX += pasX;
        if (IsKeyPressed(KEY_LEFT))  cibleX -= pasX;

        if (cibleX > larg_ecran - birdRayon) cibleX = larg_ecran - birdRayon;
        if (cibleX < birdRayon) cibleX = birdRayon;

        // l'oiseau avance un peu vers la cible à chaque image
        birdPosi.x += (cibleX - birdPosi.x) * douceurX;

    // pour l'empêcher de sortir de l'écran horizontal  
        if (birdPosi.x > larg_ecran - birdRayon) {
            birdPosi.x = larg_ecran - birdRayon;
        }
        if (birdPosi.x < birdRayon) {
            birdPosi.x = birdRayon;
        }

//---------------------------------------------------------------------------

     // mise à jour de la physique de l'oiseau pour gere son deplacement dans l'nvironement
         //if (IsKeyPressed(KEY_UP)|| IsKeyPressed(KEY_SPACE)) birdVitesse = birdsaut;
         //birdVitesse += gravite;

        bool deplacementLen = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT);
            
        if (deplacementLen)
            {
                tempsSansGravite = 1.0f;   
                birdVitesse = 0.0f;        //  hauteur fixe 1s
            }
            else if (tempsSansGravite > 0.0f)
            {
                tempsSansGravite -= GetFrameTime(); // chronomètre 
                birdVitesse = 0.0f; 
            }
            else
            {
                birdVitesse += gravite; 
            }

            // le saut reste prioritaire
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE))
            {
                birdVitesse = birdsaut;
                tempsSansGravite = 0.0f;
            }   

        birdPosi.y += birdVitesse; // deplacement de l'oiseau

        // ppour l'empêcher de sortir de l'écran vertical
        if (birdPosi.y > haut_ecran - birdRayon)
        {
            birdPosi.y = haut_ecran - birdRayon;
            birdVitesse = 0;
        }
        if (birdPosi.y < birdRayon)
        {
            birdPosi.y = birdRayon;
            birdVitesse = 0;
        }

        // dessin  simulation de l'oiseau/textes
        BeginDrawing();
        ClearBackground((Color){ 64, 224, 208, 255 });

        DrawCircleV(birdPosi, birdRayon, YELLOW);
        DrawTextEx(Police_Df, "Espace Game Bird", (Vector2){ 20, 20 }, 24, 2, PINK);

        EndDrawing();
    }

    UnloadFont(Police_Df);
    CloseWindow();
    return 0;
}