/*******************************************************************************************
*
*   raylib [core] example - Window should close
*
*   Example originally created with raylib 4.2, last time updated with raylib 4.2
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
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - window should close");
    
    RL_SetExitKey(KEY_NULL);       // Disable KEY_ESCAPE to close window, X-button still works
    
    bool exitWindowRequested = false;   // Flag to request window to exit
    bool exitWindow = false;    // Flag to set window to exit

    RL_SetTargetFPS(60);           // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!exitWindow)
    {
        // Update
        //----------------------------------------------------------------------------------
        // Detect if X-button or KEY_ESCAPE have been pressed to close window
        if (RL_WindowShouldClose() || RL_IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;
        
        if (exitWindowRequested)
        {
            // A request for close window has been issued, we can save data before closing
            // or just show a message asking for confirmation
            
            if (RL_IsKeyPressed(KEY_Y)) exitWindow = true;
            else if (RL_IsKeyPressed(KEY_N)) exitWindowRequested = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            if (exitWindowRequested)
            {
                RL_DrawRectangle(0, 100, screenWidth, 200, RL_BLACK);
                RL_DrawText("Are you sure you want to exit program? [Y/N]", 40, 180, 30, RL_WHITE);
            }
            else RL_DrawText("Try to close the window to get confirmation message!", 120, 200, 20, RL_LIGHTGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
