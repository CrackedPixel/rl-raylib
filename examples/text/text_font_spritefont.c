/*******************************************************************************************
*
*   raylib [text] example - Sprite font loading
*
*   NOTE: Sprite fonts should be generated following this conventions:
*
*     - Characters must be ordered starting with character 32 (Space)
*     - Every character must be contained within the same RL_Rectangle height
*     - Every character and every line must be separated by the same distance (margin/padding)
*     - Rectangles must be defined by a RL_MAGENTA color background
*
*   Following those constraints, a font can be provided just by an image,
*   this is quite handy to avoid additional font descriptor files (like BMFonts use).
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [text] example - sprite font loading");

    const char msg1[50] = "THIS IS A custom SPRITE FONT...";
    const char msg2[50] = "...and this is ANOTHER CUSTOM font...";
    const char msg3[50] = "...and a THIRD one! GREAT! :D";

    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)
    RL_Font font1 = RL_LoadFont("resources/custom_mecha.png");          // RL_Font loading
    RL_Font font2 = RL_LoadFont("resources/custom_alagard.png");        // RL_Font loading
    RL_Font font3 = RL_LoadFont("resources/custom_jupiter_crash.png");  // RL_Font loading

    RL_Vector2 fontPosition1 = { screenWidth/2.0f - RL_MeasureTextEx(font1, msg1, (float)font1.baseSize, -3).x/2,
                              screenHeight/2.0f - font1.baseSize/2.0f - 80.0f };

    RL_Vector2 fontPosition2 = { screenWidth/2.0f - RL_MeasureTextEx(font2, msg2, (float)font2.baseSize, -2.0f).x/2.0f,
                              screenHeight/2.0f - font2.baseSize/2.0f - 10.0f };

    RL_Vector2 fontPosition3 = { screenWidth/2.0f - RL_MeasureTextEx(font3, msg3, (float)font3.baseSize, 2.0f).x/2.0f,
                              screenHeight/2.0f - font3.baseSize/2.0f + 50.0f };

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update variables here...
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawTextEx(font1, msg1, fontPosition1, (float)font1.baseSize, -3, RL_WHITE);
            RL_DrawTextEx(font2, msg2, fontPosition2, (float)font2.baseSize, -2, RL_WHITE);
            RL_DrawTextEx(font3, msg3, fontPosition3, (float)font3.baseSize, 2, RL_WHITE);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadFont(font1);      // RL_Font unloading
    RL_UnloadFont(font2);      // RL_Font unloading
    RL_UnloadFont(font3);      // RL_Font unloading

    RL_CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}