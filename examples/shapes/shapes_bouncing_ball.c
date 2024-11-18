/*******************************************************************************************
*
*   raylib [shapes] example - bouncing ball
*
*   Example originally created with raylib 2.5, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_SetConfigFlags(FLAG_MSAA_4X_HINT);
    RL_InitWindow(screenWidth, screenHeight, "raylib [shapes] example - bouncing ball");

    RL_Vector2 ballPosition = { RL_GetScreenWidth()/2.0f, RL_GetScreenHeight()/2.0f };
    RL_Vector2 ballSpeed = { 5.0f, 4.0f };
    int ballRadius = 20;

    bool pause = 0;
    int framesCounter = 0;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //----------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //-----------------------------------------------------
        if (RL_IsKeyPressed(KEY_SPACE)) pause = !pause;

        if (!pause)
        {
            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;

            // Check walls collision for bouncing
            if ((ballPosition.x >= (RL_GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f;
            if ((ballPosition.y >= (RL_GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -1.0f;
        }
        else framesCounter++;
        //-----------------------------------------------------

        // Draw
        //-----------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawCircleV(ballPosition, (float)ballRadius, RL_MAROON);
            RL_DrawText("PRESS SPACE to PAUSE BALL MOVEMENT", 10, RL_GetScreenHeight() - 25, 20, RL_LIGHTGRAY);

            // On pause, we draw a blinking message
            if (pause && ((framesCounter/30)%2)) RL_DrawText("PAUSED", 350, 200, 30, RL_GRAY);

            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //-----------------------------------------------------
    }

    // De-Initialization
    //---------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}