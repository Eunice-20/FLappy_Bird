#include "raylib.h"
#include "bird.h"

int main(void)
{
    const int larg_ecran = 800;
    const int haut_ecran = 600;

    InitWindow(larg_ecran, haut_ecran, "Flappy Bird");
    SetTargetFPS(60);

    Font Police_Df = LoadFontEx("Police_Dafont/LSD.otf", 64, 0, 0);
    SetTextureFilter(Police_Df.texture, TEXTURE_FILTER_BILINEAR);

    Bird bird = CreerBird(200, haut_ecran / 2.0f);   // on crée l'oiseau ( fonction dans bird.c)

    while (!WindowShouldClose())
    {
        MajBird(&bird, larg_ecran, haut_ecran);      // attribution de adresse brid.c (met à jour l'oiseau)

        BeginDrawing();
        ClearBackground((Color){ 64, 224, 208, 255 });
        DessinerBird(bird);
        DrawTextEx(Police_Df, "Espace Game Bird", (Vector2){ 20, 20 }, 24, 2, PINK);
        EndDrawing();
    }

    UnloadFont(Police_Df);
    CloseWindow();
    return 0;
}