/*******************************************************************************************
*
*   raylib [textures] example - Procedural images generation
*
*   Example originally created with raylib 1.8, last time updated with raylib 1.8
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2O17-2024 Wilhem Barbier (@nounoursheureux) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define NUM_TEXTURES  9      // Currently we have 8 generation algorithms but some have multiple purposes (Linear and Square Gradients)

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [textures] example - procedural images generation");

    RL_Image verticalGradient = RL_GenImageGradientLinear(screenWidth, screenHeight, 0, RL_RED, RL_BLUE);
    RL_Image horizontalGradient = RL_GenImageGradientLinear(screenWidth, screenHeight, 90, RL_RED, RL_BLUE);
    RL_Image diagonalGradient = RL_GenImageGradientLinear(screenWidth, screenHeight, 45, RL_RED, RL_BLUE);
    RL_Image radialGradient = RL_GenImageGradientRadial(screenWidth, screenHeight, 0.0f, RL_WHITE, RL_BLACK);
    RL_Image squareGradient = RL_GenImageGradientSquare(screenWidth, screenHeight, 0.0f, RL_WHITE, RL_BLACK);
    RL_Image checked = RL_GenImageChecked(screenWidth, screenHeight, 32, 32, RL_RED, RL_BLUE);
    RL_Image whiteNoise = RL_GenImageWhiteNoise(screenWidth, screenHeight, 0.5f);
    RL_Image perlinNoise = RL_GenImagePerlinNoise(screenWidth, screenHeight, 50, 50, 4.0f);
    RL_Image cellular = RL_GenImageCellular(screenWidth, screenHeight, 32);

    RL_Texture2D textures[NUM_TEXTURES] = { 0 };

    textures[0] = RL_LoadTextureFromImage(verticalGradient);
    textures[1] = RL_LoadTextureFromImage(horizontalGradient);
    textures[2] = RL_LoadTextureFromImage(diagonalGradient);
    textures[3] = RL_LoadTextureFromImage(radialGradient);
    textures[4] = RL_LoadTextureFromImage(squareGradient);
    textures[5] = RL_LoadTextureFromImage(checked);
    textures[6] = RL_LoadTextureFromImage(whiteNoise);
    textures[7] = RL_LoadTextureFromImage(perlinNoise);
    textures[8] = RL_LoadTextureFromImage(cellular);

    // Unload image data (CPU RAM)
    RL_UnloadImage(verticalGradient);
    RL_UnloadImage(horizontalGradient);
    RL_UnloadImage(diagonalGradient);
    RL_UnloadImage(radialGradient);
    RL_UnloadImage(squareGradient);
    RL_UnloadImage(checked);
    RL_UnloadImage(whiteNoise);
    RL_UnloadImage(perlinNoise);
    RL_UnloadImage(cellular);

    int currentTexture = 0;

    RL_SetTargetFPS(60);
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || RL_IsKeyPressed(KEY_RIGHT))
        {
            currentTexture = (currentTexture + 1)%NUM_TEXTURES; // Cycle between the textures
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawTexture(textures[currentTexture], 0, 0, RL_WHITE);

            RL_DrawRectangle(30, 400, 325, 30, RL_Fade(RL_SKYBLUE, 0.5f));
            RL_DrawRectangleLines(30, 400, 325, 30, RL_Fade(RL_WHITE, 0.5f));
            RL_DrawText("MOUSE LEFT BUTTON to CYCLE PROCEDURAL TEXTURES", 40, 410, 10, RL_WHITE);

            switch(currentTexture)
            {
                case 0: RL_DrawText("VERTICAL GRADIENT", 560, 10, 20, RL_RAYWHITE); break;
                case 1: RL_DrawText("HORIZONTAL GRADIENT", 540, 10, 20, RL_RAYWHITE); break;
                case 2: RL_DrawText("DIAGONAL GRADIENT", 540, 10, 20, RL_RAYWHITE); break;
                case 3: RL_DrawText("RADIAL GRADIENT", 580, 10, 20, RL_LIGHTGRAY); break;
                case 4: RL_DrawText("SQUARE GRADIENT", 580, 10, 20, RL_LIGHTGRAY); break;
                case 5: RL_DrawText("CHECKED", 680, 10, 20, RL_RAYWHITE); break;
                case 6: RL_DrawText("RL_WHITE NOISE", 640, 10, 20, RL_RED); break;
                case 7: RL_DrawText("PERLIN NOISE", 640, 10, 20, RL_RED); break;
                case 8: RL_DrawText("CELLULAR", 670, 10, 20, RL_RAYWHITE); break;
                default: break;
            }

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // Unload textures data (GPU VRAM)
    for (int i = 0; i < NUM_TEXTURES; i++) RL_UnloadTexture(textures[i]);

    RL_CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
