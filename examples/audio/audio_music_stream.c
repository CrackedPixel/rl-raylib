/*******************************************************************************************
*
*   raylib [audio] example - RL_Music playing (streaming)
*
*   Example originally created with raylib 1.3, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [audio] example - music playing (streaming)");

    RL_InitAudioDevice();              // Initialize audio device

    RL_Music music = RL_LoadMusicStream("resources/country.mp3");

    RL_PlayMusicStream(music);

    float timePlayed = 0.0f;        // Time played normalized [0.0f..1.0f]
    bool pause = false;             // RL_Music playing paused

    RL_SetTargetFPS(30);               // Set our game to run at 30 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateMusicStream(music);   // Update music buffer with new stream data
        
        // Restart music playing (stop and play)
        if (RL_IsKeyPressed(KEY_SPACE))
        {
            RL_StopMusicStream(music);
            RL_PlayMusicStream(music);
        }

        // Pause/Resume music playing
        if (RL_IsKeyPressed(KEY_P))
        {
            pause = !pause;

            if (pause) RL_PauseMusicStream(music);
            else RL_ResumeMusicStream(music);
        }

        // Get normalized time played for current music stream
        timePlayed = RL_GetMusicTimePlayed(music)/RL_GetMusicTimeLength(music);

        if (timePlayed > 1.0f) timePlayed = 1.0f;   // Make sure time played is no longer than music
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawText("MUSIC SHOULD BE PLAYING!", 255, 150, 20, RL_LIGHTGRAY);

            RL_DrawRectangle(200, 200, 400, 12, RL_LIGHTGRAY);
            RL_DrawRectangle(200, 200, (int)(timePlayed*400.0f), 12, RL_MAROON);
            RL_DrawRectangleLines(200, 200, 400, 12, RL_GRAY);

            RL_DrawText("PRESS SPACE TO RESTART MUSIC", 215, 250, 20, RL_LIGHTGRAY);
            RL_DrawText("PRESS P TO PAUSE/RESUME MUSIC", 208, 280, 20, RL_LIGHTGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadMusicStream(music);   // Unload music stream buffers from RAM

    RL_CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
