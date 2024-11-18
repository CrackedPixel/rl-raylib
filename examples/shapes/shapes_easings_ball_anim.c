/*******************************************************************************************
*
*   raylib [shapes] example - easings ball anim
*
*   Example originally created with raylib 2.5, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include "reasings.h"                // Required for easing functions

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [shapes] example - easings ball anim");

    // Ball variable value to be animated with easings
    int ballPositionX = -100;
    int ballRadius = 20;
    float ballAlpha = 0.0f;

    int state = 0;
    int framesCounter = 0;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (state == 0)             // Move ball position X with easing
        {
            framesCounter++;
            ballPositionX = (int)EaseElasticOut((float)framesCounter, -100, screenWidth/2.0f + 100, 120);

            if (framesCounter >= 120)
            {
                framesCounter = 0;
                state = 1;
            }
        }
        else if (state == 1)        // Increase ball radius with easing
        {
            framesCounter++;
            ballRadius = (int)EaseElasticIn((float)framesCounter, 20, 500, 200);

            if (framesCounter >= 200)
            {
                framesCounter = 0;
                state = 2;
            }
        }
        else if (state == 2)        // Change ball alpha with easing (background color blending)
        {
            framesCounter++;
            ballAlpha = EaseCubicOut((float)framesCounter, 0.0f, 1.0f, 200);

            if (framesCounter >= 200)
            {
                framesCounter = 0;
                state = 3;
            }
        }
        else if (state == 3)        // Reset state to play again
        {
            if (RL_IsKeyPressed(KEY_ENTER))
            {
                // Reset required variables to play again
                ballPositionX = -100;
                ballRadius = 20;
                ballAlpha = 0.0f;
                state = 0;
            }
        }

        if (RL_IsKeyPressed(KEY_R)) framesCounter = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            if (state >= 2) RL_DrawRectangle(0, 0, screenWidth, screenHeight, RL_GREEN);
            RL_DrawCircle(ballPositionX, 200, (float)ballRadius, RL_Fade(RL_RED, 1.0f - ballAlpha));

            if (state == 3) RL_DrawText("PRESS [ENTER] TO PLAY AGAIN!", 240, 200, 20, RL_BLACK);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}