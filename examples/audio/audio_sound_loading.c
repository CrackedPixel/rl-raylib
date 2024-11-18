/*******************************************************************************************
*
*   raylib [audio] example - RL_Sound loading and playing
*
*   Example originally created with raylib 1.1, last time updated with raylib 3.5
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [audio] example - sound loading and playing");

    RL_InitAudioDevice();      // Initialize audio device

    RL_Sound fxWav = RL_LoadSound("resources/sound.wav");         // Load WAV audio file
    RL_Sound fxOgg = RL_LoadSound("resources/target.ogg");        // Load OGG audio file

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsKeyPressed(KEY_SPACE)) RL_PlaySound(fxWav);      // Play WAV sound
        if (RL_IsKeyPressed(KEY_ENTER)) RL_PlaySound(fxOgg);      // Play OGG sound
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawText("Press SPACE to PLAY the WAV sound!", 200, 180, 20, RL_LIGHTGRAY);
            RL_DrawText("Press ENTER to PLAY the OGG sound!", 200, 220, 20, RL_LIGHTGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadSound(fxWav);     // Unload sound data
    RL_UnloadSound(fxOgg);     // Unload sound data

    RL_CloseAudioDevice();     // Close audio device

    RL_CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}