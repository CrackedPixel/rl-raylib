/*******************************************************************************************
*
*   raylib [shapes] example - Cubic-bezier lines
*
*   Example originally created with raylib 1.7, last time updated with raylib 1.7
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2024 Ramon Santamaria (@raysan5)
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

    RL_SetConfigFlags(FLAG_MSAA_4X_HINT);
    RL_InitWindow(screenWidth, screenHeight, "raylib [shapes] example - cubic-bezier lines");

    RL_Vector2 startPoint = { 30, 30 };
    RL_Vector2 endPoint = { (float)screenWidth - 30, (float)screenHeight - 30 };
    bool moveStartPoint = false;
    bool moveEndPoint = false;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_Vector2 mouse = RL_GetMousePosition();

        if (RL_CheckCollisionPointCircle(mouse, startPoint, 10.0f) && RL_IsMouseButtonDown(MOUSE_BUTTON_LEFT)) moveStartPoint = true;
        else if (RL_CheckCollisionPointCircle(mouse, endPoint, 10.0f) && RL_IsMouseButtonDown(MOUSE_BUTTON_LEFT)) moveEndPoint = true;

        if (moveStartPoint)
        {
            startPoint = mouse;
            if (RL_IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) moveStartPoint = false;
        }

        if (moveEndPoint)
        {
            endPoint = mouse;
            if (RL_IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) moveEndPoint = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawText("MOVE START-END POINTS WITH MOUSE", 15, 20, 20, RL_GRAY);

            // Draw line Cubic Bezier, in-out interpolation (easing), no control points
            RL_DrawLineBezier(startPoint, endPoint, 4.0f, RL_BLUE);
            
            // Draw start-end spline circles with some details
            RL_DrawCircleV(startPoint, RL_CheckCollisionPointCircle(mouse, startPoint, 10.0f)? 14.0f : 8.0f, moveStartPoint? RL_RED : RL_BLUE);
            RL_DrawCircleV(endPoint, RL_CheckCollisionPointCircle(mouse, endPoint, 10.0f)? 14.0f : 8.0f, moveEndPoint? RL_RED : RL_BLUE);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
