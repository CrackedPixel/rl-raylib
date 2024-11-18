/*******************************************************************************************
*
*   raylib [text] example - Text formatting
*
*   Example originally created with raylib 1.1, last time updated with raylib 3.0
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [text] example - text formatting");

    int score = 100020;
    int hiscore = 200450;
    int lives = 5;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawText(RL_TextFormat("Score: %08i", score), 200, 80, 20, RL_RED);

            RL_DrawText(RL_TextFormat("HiScore: %08i", hiscore), 200, 120, 20, RL_GREEN);

            RL_DrawText(RL_TextFormat("Lives: %02i", lives), 200, 160, 40, RL_BLUE);

            RL_DrawText(RL_TextFormat("Elapsed Time: %02.02f ms", RL_GetFrameTime()*1000), 200, 220, 20, RL_BLACK);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}