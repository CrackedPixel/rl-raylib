/*******************************************************************************************
*
*   raylib [core] example - Mouse input
*
*   Example originally created with raylib 1.0, last time updated with raylib 4.0
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - mouse input");

    RL_Vector2 ballPosition = { -100.0f, -100.0f };
    RL_Color ballColor = RL_DARKBLUE;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        ballPosition = RL_GetMousePosition();

        if (RL_IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) ballColor = RL_MAROON;
        else if (RL_IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) ballColor = RL_LIME;
        else if (RL_IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) ballColor = RL_DARKBLUE;
        else if (RL_IsMouseButtonPressed(MOUSE_BUTTON_SIDE)) ballColor = RL_PURPLE;
        else if (RL_IsMouseButtonPressed(MOUSE_BUTTON_EXTRA)) ballColor = RL_YELLOW;
        else if (RL_IsMouseButtonPressed(MOUSE_BUTTON_FORWARD)) ballColor = RL_ORANGE;
        else if (RL_IsMouseButtonPressed(MOUSE_BUTTON_BACK)) ballColor = RL_BEIGE;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawCircleV(ballPosition, 40, ballColor);

            RL_DrawText("move ball with mouse and click mouse button to change color", 10, 10, 20, RL_DARKGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}