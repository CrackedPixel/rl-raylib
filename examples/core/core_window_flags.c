/*******************************************************************************************
*
*   raylib [core] example - window flags
*
*   Example originally created with raylib 3.5, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2020-2024 Ramon Santamaria (@raysan5)
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

    // Possible window flags
    /*
    FLAG_VSYNC_HINT
    FLAG_FULLSCREEN_MODE    -> not working properly -> wrong scaling!
    FLAG_WINDOW_RESIZABLE
    FLAG_WINDOW_UNDECORATED
    FLAG_WINDOW_TRANSPARENT
    FLAG_WINDOW_HIDDEN
    FLAG_WINDOW_MINIMIZED   -> Not supported on window creation
    FLAG_WINDOW_MAXIMIZED   -> Not supported on window creation
    FLAG_WINDOW_UNFOCUSED
    FLAG_WINDOW_TOPMOST
    FLAG_WINDOW_HIGHDPI     -> errors after minimize-resize, fb size is recalculated
    FLAG_WINDOW_ALWAYS_RUN
    FLAG_MSAA_4X_HINT
    */

    // Set configuration flags for window creation
    //RL_SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - window flags");

    RL_Vector2 ballPosition = { RL_GetScreenWidth() / 2.0f, RL_GetScreenHeight() / 2.0f };
    RL_Vector2 ballSpeed = { 5.0f, 4.0f };
    float ballRadius = 20;

    int framesCounter = 0;

    //RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //----------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //-----------------------------------------------------
        if (RL_IsKeyPressed(KEY_F)) RL_ToggleFullscreen();  // modifies window size when scaling!

        if (RL_IsKeyPressed(KEY_R))
        {
            if (RL_IsWindowState(FLAG_WINDOW_RESIZABLE)) RL_ClearWindowState(FLAG_WINDOW_RESIZABLE);
            else RL_SetWindowState(FLAG_WINDOW_RESIZABLE);
        }

        if (RL_IsKeyPressed(KEY_D))
        {
            if (RL_IsWindowState(FLAG_WINDOW_UNDECORATED)) RL_ClearWindowState(FLAG_WINDOW_UNDECORATED);
            else RL_SetWindowState(FLAG_WINDOW_UNDECORATED);
        }

        if (RL_IsKeyPressed(KEY_H))
        {
            if (!RL_IsWindowState(FLAG_WINDOW_HIDDEN)) RL_SetWindowState(FLAG_WINDOW_HIDDEN);

            framesCounter = 0;
        }

        if (RL_IsWindowState(FLAG_WINDOW_HIDDEN))
        {
            framesCounter++;
            if (framesCounter >= 240) RL_ClearWindowState(FLAG_WINDOW_HIDDEN); // Show window after 3 seconds
        }

        if (RL_IsKeyPressed(KEY_N))
        {
            if (!RL_IsWindowState(FLAG_WINDOW_MINIMIZED)) RL_MinimizeWindow();

            framesCounter = 0;
        }

        if (RL_IsWindowState(FLAG_WINDOW_MINIMIZED))
        {
            framesCounter++;
            if (framesCounter >= 240) RL_RestoreWindow(); // Restore window after 3 seconds
        }

        if (RL_IsKeyPressed(KEY_M))
        {
            // NOTE: Requires FLAG_WINDOW_RESIZABLE enabled!
            if (RL_IsWindowState(FLAG_WINDOW_MAXIMIZED)) RL_RestoreWindow();
            else RL_MaximizeWindow();
        }

        if (RL_IsKeyPressed(KEY_U))
        {
            if (RL_IsWindowState(FLAG_WINDOW_UNFOCUSED)) RL_ClearWindowState(FLAG_WINDOW_UNFOCUSED);
            else RL_SetWindowState(FLAG_WINDOW_UNFOCUSED);
        }

        if (RL_IsKeyPressed(KEY_T))
        {
            if (RL_IsWindowState(FLAG_WINDOW_TOPMOST)) RL_ClearWindowState(FLAG_WINDOW_TOPMOST);
            else RL_SetWindowState(FLAG_WINDOW_TOPMOST);
        }

        if (RL_IsKeyPressed(KEY_A))
        {
            if (RL_IsWindowState(FLAG_WINDOW_ALWAYS_RUN)) RL_ClearWindowState(FLAG_WINDOW_ALWAYS_RUN);
            else RL_SetWindowState(FLAG_WINDOW_ALWAYS_RUN);
        }

        if (RL_IsKeyPressed(KEY_V))
        {
            if (RL_IsWindowState(FLAG_VSYNC_HINT)) RL_ClearWindowState(FLAG_VSYNC_HINT);
            else RL_SetWindowState(FLAG_VSYNC_HINT);
        }

        // Bouncing ball logic
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;
        if ((ballPosition.x >= (RL_GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f;
        if ((ballPosition.y >= (RL_GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -1.0f;
        //-----------------------------------------------------

        // Draw
        //-----------------------------------------------------
        RL_BeginDrawing();

        if (RL_IsWindowState(FLAG_WINDOW_TRANSPARENT)) RL_ClearBackground(RL_BLANK);
        else RL_ClearBackground(RL_RAYWHITE);

        RL_DrawCircleV(ballPosition, ballRadius, RL_MAROON);
        RL_DrawRectangleLinesEx((RL_Rectangle) { 0, 0, (float)RL_GetScreenWidth(), (float)RL_GetScreenHeight() }, 4, RL_RAYWHITE);

        RL_DrawCircleV(RL_GetMousePosition(), 10, RL_DARKBLUE);

        RL_DrawFPS(10, 10);

        RL_DrawText(RL_TextFormat("Screen Size: [%i, %i]", RL_GetScreenWidth(), RL_GetScreenHeight()), 10, 40, 10, RL_GREEN);

        // Draw window state info
        RL_DrawText("Following flags can be set after window creation:", 10, 60, 10, RL_GRAY);
        if (RL_IsWindowState(FLAG_FULLSCREEN_MODE)) RL_DrawText("[F] FLAG_FULLSCREEN_MODE: on", 10, 80, 10, RL_LIME);
        else RL_DrawText("[F] FLAG_FULLSCREEN_MODE: off", 10, 80, 10, RL_MAROON);
        if (RL_IsWindowState(FLAG_WINDOW_RESIZABLE)) RL_DrawText("[R] FLAG_WINDOW_RESIZABLE: on", 10, 100, 10, RL_LIME);
        else RL_DrawText("[R] FLAG_WINDOW_RESIZABLE: off", 10, 100, 10, RL_MAROON);
        if (RL_IsWindowState(FLAG_WINDOW_UNDECORATED)) RL_DrawText("[D] FLAG_WINDOW_UNDECORATED: on", 10, 120, 10, RL_LIME);
        else RL_DrawText("[D] FLAG_WINDOW_UNDECORATED: off", 10, 120, 10, RL_MAROON);
        if (RL_IsWindowState(FLAG_WINDOW_HIDDEN)) RL_DrawText("[H] FLAG_WINDOW_HIDDEN: on", 10, 140, 10, RL_LIME);
        else RL_DrawText("[H] FLAG_WINDOW_HIDDEN: off", 10, 140, 10, RL_MAROON);
        if (RL_IsWindowState(FLAG_WINDOW_MINIMIZED)) RL_DrawText("[N] FLAG_WINDOW_MINIMIZED: on", 10, 160, 10, RL_LIME);
        else RL_DrawText("[N] FLAG_WINDOW_MINIMIZED: off", 10, 160, 10, RL_MAROON);
        if (RL_IsWindowState(FLAG_WINDOW_MAXIMIZED)) RL_DrawText("[M] FLAG_WINDOW_MAXIMIZED: on", 10, 180, 10, RL_LIME);
        else RL_DrawText("[M] FLAG_WINDOW_MAXIMIZED: off", 10, 180, 10, RL_MAROON);
        if (RL_IsWindowState(FLAG_WINDOW_UNFOCUSED)) RL_DrawText("[G] FLAG_WINDOW_UNFOCUSED: on", 10, 200, 10, RL_LIME);
        else RL_DrawText("[U] FLAG_WINDOW_UNFOCUSED: off", 10, 200, 10, RL_MAROON);
        if (RL_IsWindowState(FLAG_WINDOW_TOPMOST)) RL_DrawText("[T] FLAG_WINDOW_TOPMOST: on", 10, 220, 10, RL_LIME);
        else RL_DrawText("[T] FLAG_WINDOW_TOPMOST: off", 10, 220, 10, RL_MAROON);
        if (RL_IsWindowState(FLAG_WINDOW_ALWAYS_RUN)) RL_DrawText("[A] FLAG_WINDOW_ALWAYS_RUN: on", 10, 240, 10, RL_LIME);
        else RL_DrawText("[A] FLAG_WINDOW_ALWAYS_RUN: off", 10, 240, 10, RL_MAROON);
        if (RL_IsWindowState(FLAG_VSYNC_HINT)) RL_DrawText("[V] FLAG_VSYNC_HINT: on", 10, 260, 10, RL_LIME);
        else RL_DrawText("[V] FLAG_VSYNC_HINT: off", 10, 260, 10, RL_MAROON);

        RL_DrawText("Following flags can only be set before window creation:", 10, 300, 10, RL_GRAY);
        if (RL_IsWindowState(FLAG_WINDOW_HIGHDPI)) RL_DrawText("FLAG_WINDOW_HIGHDPI: on", 10, 320, 10, RL_LIME);
        else RL_DrawText("FLAG_WINDOW_HIGHDPI: off", 10, 320, 10, RL_MAROON);
        if (RL_IsWindowState(FLAG_WINDOW_TRANSPARENT)) RL_DrawText("FLAG_WINDOW_TRANSPARENT: on", 10, 340, 10, RL_LIME);
        else RL_DrawText("FLAG_WINDOW_TRANSPARENT: off", 10, 340, 10, RL_MAROON);
        if (RL_IsWindowState(FLAG_MSAA_4X_HINT)) RL_DrawText("FLAG_MSAA_4X_HINT: on", 10, 360, 10, RL_LIME);
        else RL_DrawText("FLAG_MSAA_4X_HINT: off", 10, 360, 10, RL_MAROON);

        RL_EndDrawing();
        //-----------------------------------------------------
    }

    // De-Initialization
    //---------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}
