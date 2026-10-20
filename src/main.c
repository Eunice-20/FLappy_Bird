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
    float vitesseX = 0.0f;
    //--------------------------------
    const float accelerationX = 0.3f;   // à quelle vitesse on accélère
    const float slow_down_brid = 0.95f;     //  
    const float vitesseMaxX = 6.0f;  
    //--------------------------------
    const float birdRayon = 20.0f;
    const float gravite = 0.5f;
    const float birdsaut = -8.0f;   // négatif = vers le haut

    while (!WindowShouldClose())
    {
        // option : l'oiseau peut se déplacer horizontalement 
        if (IsKeyDown(KEY_RIGHT)) vitesseX  += accelerationX;
        if (IsKeyDown(KEY_LEFT))  vitesseX -= accelerationX;
//--------------------------------------------------------------------------- a corriger , ralenttisement l'oiseau  trop rapide
        vitesseX *= slow_down_brid; // ralentissement de l'oiseau

        if (vitesseX > vitesseMaxX) vitesseX = vitesseMaxX;
        if (vitesseX < -vitesseMaxX) vitesseX = -vitesseMaxX;

        birdPosi.x += vitesseX; // déplacement

        if (birdPosi.x > larg_ecran - birdRayon) {
            birdPosi.x = larg_ecran - birdRayon;
            vitesseX = 0;
        }
        if (birdPosi.x < birdRayon) {
            birdPosi.x = birdRayon;
            vitesseX = 0;
        }

         // pour l'empêcher de sortir de l'écran horizontal
        if (birdPosi.x > larg_ecran - birdRayon) {
            birdPosi.x = larg_ecran - birdRayon;
        }
        if (birdPosi.x < birdRayon) {
            birdPosi.x = birdRayon;
        }
//---------------------------------------------------------------------------

        // mise à jour de la physique de l'oiseau pour gere son deplacement dans l'nvironement
        if (IsKeyPressed(KEY_UP)) birdVitesse = birdsaut;

        birdVitesse += gravite;
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

        // dessin  simulation de l'oiseau et du texte sur l'écran
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