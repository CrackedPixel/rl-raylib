/*******************************************************************************************
*
*   raylib [shapes] example - collision area
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

#include <stdlib.h>     // Required for: abs()

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //---------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [shapes] example - collision area");

    // Box A: Moving box
    RL_Rectangle boxA = { 10, RL_GetScreenHeight()/2.0f - 50, 200, 100 };
    int boxASpeedX = 4;

    // Box B: Mouse moved box
    RL_Rectangle boxB = { RL_GetScreenWidth()/2.0f - 30, RL_GetScreenHeight()/2.0f - 30, 60, 60 };

    RL_Rectangle boxCollision = { 0 }; // Collision rectangle

    int screenUpperLimit = 40;      // Top menu limits

    bool pause = false;             // Movement pause
    bool collision = false;         // Collision detection

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //----------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //-----------------------------------------------------
        // Move box if not paused
        if (!pause) boxA.x += boxASpeedX;

        // Bounce box on x screen limits
        if (((boxA.x + boxA.width) >= RL_GetScreenWidth()) || (boxA.x <= 0)) boxASpeedX *= -1;

        // Update player-controlled-box (box02)
        boxB.x = RL_GetMouseX() - boxB.width/2;
        boxB.y = RL_GetMouseY() - boxB.height/2;

        // Make sure Box B does not go out of move area limits
        if ((boxB.x + boxB.width) >= RL_GetScreenWidth()) boxB.x = RL_GetScreenWidth() - boxB.width;
        else if (boxB.x <= 0) boxB.x = 0;

        if ((boxB.y + boxB.height) >= RL_GetScreenHeight()) boxB.y = RL_GetScreenHeight() - boxB.height;
        else if (boxB.y <= screenUpperLimit) boxB.y = (float)screenUpperLimit;

        // Check boxes collision
        collision = RL_CheckCollisionRecs(boxA, boxB);

        // Get collision rectangle (only on collision)
        if (collision) boxCollision = RL_GetCollisionRec(boxA, boxB);

        // Pause Box A movement
        if (RL_IsKeyPressed(KEY_SPACE)) pause = !pause;
        //-----------------------------------------------------

        // Draw
        //-----------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawRectangle(0, 0, screenWidth, screenUpperLimit, collision? RL_RED : RL_BLACK);

            RL_DrawRectangleRec(boxA, RL_GOLD);
            RL_DrawRectangleRec(boxB, RL_BLUE);

            if (collision)
            {
                // Draw collision area
                RL_DrawRectangleRec(boxCollision, RL_LIME);

                // Draw collision message
                RL_DrawText("COLLISION!", RL_GetScreenWidth()/2 - RL_MeasureText("COLLISION!", 20)/2, screenUpperLimit/2 - 10, 20, RL_BLACK);

                // Draw collision area
                RL_DrawText(RL_TextFormat("Collision Area: %i", (int)boxCollision.width*(int)boxCollision.height), RL_GetScreenWidth()/2 - 100, screenUpperLimit + 10, 20, RL_BLACK);
            }

            // Draw help instructions
            RL_DrawText("Press SPACE to PAUSE/RESUME", 20, screenHeight - 35, 20, RL_LIGHTGRAY);

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
