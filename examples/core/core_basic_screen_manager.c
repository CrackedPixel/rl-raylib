/*******************************************************************************************
*
*   raylib [core] examples - basic screen manager
*
*   NOTE: This example illustrates a very simple screen manager based on a states machines
*
*   Example originally created with raylib 4.0, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------------
// Types and Structures Definition
//------------------------------------------------------------------------------------------
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - basic screen manager");

    GameScreen currentScreen = LOGO;

    // TODO: Initialize all required variables and load all required data here!

    int framesCounter = 0;          // Useful to count frames

    RL_SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        switch(currentScreen)
        {
            case LOGO:
            {
                // TODO: Update LOGO screen variables here!

                framesCounter++;    // Count frames

                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (framesCounter > 120)
                {
                    currentScreen = TITLE;
                }
            } break;
            case TITLE:
            {
                // TODO: Update TITLE screen variables here!

                // Press enter to change to GAMEPLAY screen
                if (RL_IsKeyPressed(KEY_ENTER) || RL_IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                // TODO: Update GAMEPLAY screen variables here!

                // Press enter to change to ENDING screen
                if (RL_IsKeyPressed(KEY_ENTER) || RL_IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = ENDING;
                }
            } break;
            case ENDING:
            {
                // TODO: Update ENDING screen variables here!

                // Press enter to return to TITLE screen
                if (RL_IsKeyPressed(KEY_ENTER) || RL_IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = TITLE;
                }
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            switch(currentScreen)
            {
                case LOGO:
                {
                    // TODO: Draw LOGO screen here!
                    RL_DrawText("LOGO SCREEN", 20, 20, 40, RL_LIGHTGRAY);
                    RL_DrawText("WAIT for 2 SECONDS...", 290, 220, 20, RL_GRAY);

                } break;
                case TITLE:
                {
                    // TODO: Draw TITLE screen here!
                    RL_DrawRectangle(0, 0, screenWidth, screenHeight, RL_GREEN);
                    RL_DrawText("TITLE SCREEN", 20, 20, 40, RL_DARKGREEN);
                    RL_DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, RL_DARKGREEN);

                } break;
                case GAMEPLAY:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    RL_DrawRectangle(0, 0, screenWidth, screenHeight, RL_PURPLE);
                    RL_DrawText("GAMEPLAY SCREEN", 20, 20, 40, RL_MAROON);
                    RL_DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, RL_MAROON);

                } break;
                case ENDING:
                {
                    // TODO: Draw ENDING screen here!
                    RL_DrawRectangle(0, 0, screenWidth, screenHeight, RL_BLUE);
                    RL_DrawText("ENDING SCREEN", 20, 20, 40, RL_DARKBLUE);
                    RL_DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, RL_DARKBLUE);

                } break;
                default: break;
            }

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
