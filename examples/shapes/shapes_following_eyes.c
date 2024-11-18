/*******************************************************************************************
*
*   raylib [shapes] example - following eyes
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

#include <math.h>       // Required for: atan2f()

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [shapes] example - following eyes");

    RL_Vector2 scleraLeftPosition = { RL_GetScreenWidth()/2.0f - 100.0f, RL_GetScreenHeight()/2.0f };
    RL_Vector2 scleraRightPosition = { RL_GetScreenWidth()/2.0f + 100.0f, RL_GetScreenHeight()/2.0f };
    float scleraRadius = 80;

    RL_Vector2 irisLeftPosition = { RL_GetScreenWidth()/2.0f - 100.0f, RL_GetScreenHeight()/2.0f };
    RL_Vector2 irisRightPosition = { RL_GetScreenWidth()/2.0f + 100.0f, RL_GetScreenHeight()/2.0f };
    float irisRadius = 24;

    float angle = 0.0f;
    float dx = 0.0f, dy = 0.0f, dxx = 0.0f, dyy = 0.0f;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        irisLeftPosition = RL_GetMousePosition();
        irisRightPosition = RL_GetMousePosition();

        // Check not inside the left eye sclera
        if (!RL_CheckCollisionPointCircle(irisLeftPosition, scleraLeftPosition, scleraRadius - irisRadius))
        {
            dx = irisLeftPosition.x - scleraLeftPosition.x;
            dy = irisLeftPosition.y - scleraLeftPosition.y;

            angle = atan2f(dy, dx);

            dxx = (scleraRadius - irisRadius)*cosf(angle);
            dyy = (scleraRadius - irisRadius)*sinf(angle);

            irisLeftPosition.x = scleraLeftPosition.x + dxx;
            irisLeftPosition.y = scleraLeftPosition.y + dyy;
        }

        // Check not inside the right eye sclera
        if (!RL_CheckCollisionPointCircle(irisRightPosition, scleraRightPosition, scleraRadius - irisRadius))
        {
            dx = irisRightPosition.x - scleraRightPosition.x;
            dy = irisRightPosition.y - scleraRightPosition.y;

            angle = atan2f(dy, dx);

            dxx = (scleraRadius - irisRadius)*cosf(angle);
            dyy = (scleraRadius - irisRadius)*sinf(angle);

            irisRightPosition.x = scleraRightPosition.x + dxx;
            irisRightPosition.y = scleraRightPosition.y + dyy;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawCircleV(scleraLeftPosition, scleraRadius, RL_LIGHTGRAY);
            RL_DrawCircleV(irisLeftPosition, irisRadius, RL_BROWN);
            RL_DrawCircleV(irisLeftPosition, 10, RL_BLACK);

            RL_DrawCircleV(scleraRightPosition, scleraRadius, RL_LIGHTGRAY);
            RL_DrawCircleV(irisRightPosition, irisRadius, RL_DARKGREEN);
            RL_DrawCircleV(irisRightPosition, 10, RL_BLACK);

            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}