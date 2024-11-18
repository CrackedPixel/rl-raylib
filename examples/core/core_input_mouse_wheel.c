/*******************************************************************************************
*
*   raylib [core] examples - Mouse wheel input
*
*   Example originally created with raylib 1.1, last time updated with raylib 1.3
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - input mouse wheel");

    int boxPositionY = screenHeight/2 - 40;
    int scrollSpeed = 4;            // Scrolling speed in pixels

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        boxPositionY -= (int)(RL_GetMouseWheelMove()*scrollSpeed);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawRectangle(screenWidth/2 - 40, boxPositionY, 80, 80, RL_MAROON);

            RL_DrawText("Use mouse wheel to move the cube up and down!", 10, 10, 20, RL_GRAY);
            RL_DrawText(RL_TextFormat("Box position Y: %03i", boxPositionY), 10, 40, 20, RL_LIGHTGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}