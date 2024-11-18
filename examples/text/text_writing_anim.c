/*******************************************************************************************
*
*   raylib [text] example - Text Writing Animation
*
*   Example originally created with raylib 1.4, last time updated with raylib 1.4
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2016-2024 Ramon Santamaria (@raysan5)
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [text] example - text writing anim");

    const char message[128] = "This sample illustrates a text writing\nanimation effect! Check it out! ;)";

    int framesCounter = 0;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsKeyDown(KEY_SPACE)) framesCounter += 8;
        else framesCounter++;

        if (RL_IsKeyPressed(KEY_ENTER)) framesCounter = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawText(RL_TextSubtext(message, 0, framesCounter/10), 210, 160, 20, RL_MAROON);

            RL_DrawText("PRESS [ENTER] to RESTART!", 240, 260, 20, RL_LIGHTGRAY);
            RL_DrawText("HOLD [SPACE] to SPEED UP!", 239, 300, 20, RL_LIGHTGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}