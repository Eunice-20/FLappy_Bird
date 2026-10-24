
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
