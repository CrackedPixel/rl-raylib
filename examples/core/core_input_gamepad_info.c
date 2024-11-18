/*******************************************************************************************
*
*   raylib [core] example - Gamepad information
*
*   NOTE: This example requires a Gamepad connected to the system
*         Check raylib.h for buttons configuration
*
*   Example originally created with raylib 4.6, last time updated with raylib 4.6
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
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_SetConfigFlags(FLAG_MSAA_4X_HINT);  // Set MSAA 4X hint before windows creation

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - gamepad information");

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            for (int i = 0, y = 5; i < 4; i++)     // MAX_GAMEPADS = 4
            {
                if (RL_IsGamepadAvailable(i))
                {
                    RL_DrawText(RL_TextFormat("Gamepad name: %s", RL_GetGamepadName(i)), 10, y, 10, RL_BLACK);
                    y += 11;
                    RL_DrawText(RL_TextFormat("\tAxis count:   %d", RL_GetGamepadAxisCount(i)), 10, y, 10, RL_BLACK);
                    y += 11;

                    for (int axis = 0; axis < RL_GetGamepadAxisCount(i); axis++)
                    {
                        RL_DrawText(RL_TextFormat("\tAxis %d = %f", axis, RL_GetGamepadAxisMovement(i, axis)), 10, y, 10, RL_BLACK);
                        y += 11;
                    }

                    for (int button = 0; button < 32; button++)
                    {
                        RL_DrawText(RL_TextFormat("\tButton %d = %d", button, RL_IsGamepadButtonDown(i, button)), 10, y, 10, RL_BLACK);
                        y += 11;
                    }
                }
            }

            RL_DrawFPS(RL_GetScreenWidth() - 100, 100);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
