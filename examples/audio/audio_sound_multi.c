/*******************************************************************************************
*
*   raylib [audio] example - Playing sound multiple times
*
*   Example originally created with raylib 4.6
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023 Jeffery Myers (@JeffM2501)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_SOUNDS 10
RL_Sound soundArray[MAX_SOUNDS] = { 0 };
int currentSound;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [audio] example - playing sound multiple times");

    RL_InitAudioDevice();      // Initialize audio device

    // load the sound list
    soundArray[0] = RL_LoadSound("resources/sound.wav");         // Load WAV audio file into the first slot as the 'source' sound
                                                              // this sound owns the sample data
    for (int i = 1; i < MAX_SOUNDS; i++)
    {
        soundArray[i] = RL_LoadSoundAlias(soundArray[0]);        // Load an alias of the sound into slots 1-9. These do not own the sound data, but can be played
    }
    currentSound = 0;                                         // set the sound list to the start

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsKeyPressed(KEY_SPACE))
        {
            RL_PlaySound(soundArray[currentSound]);            // play the next open sound slot
            currentSound++;                                 // increment the sound slot
            if (currentSound >= MAX_SOUNDS)                 // if the sound slot is out of bounds, go back to 0
                currentSound = 0;

            // Note: a better way would be to look at the list for the first sound that is not playing and use that slot
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawText("Press SPACE to PLAY a WAV sound!", 200, 180, 20, RL_LIGHTGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    for (int i = 1; i < MAX_SOUNDS; i++)
        RL_UnloadSoundAlias(soundArray[i]);     // Unload sound aliases
    RL_UnloadSound(soundArray[0]);              // Unload source sound data

    RL_CloseAudioDevice();     // Close audio device

    RL_CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}