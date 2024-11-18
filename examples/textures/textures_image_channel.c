/*******************************************************************************************
*
*   raylib [textures] example - Retrive image channel (mask)
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   Example originally created with raylib 5.1-dev, last time updated with raylib 5.1-dev
*
*   Example contributed by Bruno Cabral (github.com/brccabral) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2024-2024 Bruno Cabral (github.com/brccabral) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <raylib.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [textures] example - extract channel from image");

    RL_Image fudesumiImage = RL_LoadImage("resources/fudesumi.png");

    RL_Image imageAlpha = RL_ImageFromChannel(fudesumiImage, 3);
    RL_ImageAlphaMask(&imageAlpha, imageAlpha);

    RL_Image imageRed = RL_ImageFromChannel(fudesumiImage, 0);
    RL_ImageAlphaMask(&imageRed, imageAlpha);

    RL_Image imageGreen = RL_ImageFromChannel(fudesumiImage, 1);
    RL_ImageAlphaMask(&imageGreen, imageAlpha);

    RL_Image imageBlue = RL_ImageFromChannel(fudesumiImage, 2);
    RL_ImageAlphaMask(&imageBlue, imageAlpha);

    RL_Image backgroundImage = RL_GenImageChecked(screenWidth, screenHeight, screenWidth/20, screenHeight/20, RL_ORANGE, RL_YELLOW);

    RL_Texture2D fudesumiTexture = RL_LoadTextureFromImage(fudesumiImage);
    RL_Texture2D textureAlpha = RL_LoadTextureFromImage(imageAlpha);
    RL_Texture2D textureRed = RL_LoadTextureFromImage(imageRed);
    RL_Texture2D textureGreen = RL_LoadTextureFromImage(imageGreen);
    RL_Texture2D textureBlue = RL_LoadTextureFromImage(imageBlue);
    RL_Texture2D backgroundTexture = RL_LoadTextureFromImage(backgroundImage);

    RL_UnloadImage(fudesumiImage);
    RL_UnloadImage(imageAlpha);
    RL_UnloadImage(imageRed);
    RL_UnloadImage(imageGreen);
    RL_UnloadImage(imageBlue);
    RL_UnloadImage(backgroundImage);

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    RL_Rectangle fudesumiRec = {0, 0, fudesumiImage.width, fudesumiImage.height};

    RL_Rectangle fudesumiPos = {50, 10, fudesumiImage.width*0.8f, fudesumiImage.height*0.8f};
    RL_Rectangle redPos = { 410, 10, fudesumiPos.width / 2, fudesumiPos.height / 2 };
    RL_Rectangle greenPos = { 600, 10, fudesumiPos.width / 2, fudesumiPos.height / 2 };
    RL_Rectangle bluePos = { 410, 230, fudesumiPos.width / 2, fudesumiPos.height / 2 };
    RL_Rectangle alphaPos = { 600, 230, fudesumiPos.width / 2, fudesumiPos.height / 2 };

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_DrawTexture(backgroundTexture, 0, 0, RL_WHITE);
            RL_DrawTexturePro(fudesumiTexture, fudesumiRec, fudesumiPos, (RL_Vector2) {0, 0}, 0, RL_WHITE);

            RL_DrawTexturePro(textureRed, fudesumiRec, redPos, (RL_Vector2) {0, 0}, 0, RL_RED);
            RL_DrawTexturePro(textureGreen, fudesumiRec, greenPos, (RL_Vector2) {0, 0}, 0, RL_GREEN);
            RL_DrawTexturePro(textureBlue, fudesumiRec, bluePos, (RL_Vector2) {0, 0}, 0, RL_BLUE);
            RL_DrawTexturePro(textureAlpha, fudesumiRec, alphaPos, (RL_Vector2) {0, 0}, 0, RL_WHITE);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(backgroundTexture);
    RL_UnloadTexture(fudesumiTexture);
    RL_UnloadTexture(textureRed);
    RL_UnloadTexture(textureGreen);
    RL_UnloadTexture(textureBlue);
    RL_UnloadTexture(textureAlpha);
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
