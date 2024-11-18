/*******************************************************************************************
*
*   raylib [others] example - Embedded files loading (RL_Wave and RL_Image)
*
*   Example originally created with raylib 3.0, last time updated with raylib 2.5
*
*   Example contributed by Kristian Holmgren (@defutura) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2020-2024 Kristian Holmgren (@defutura) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include "resources/audio_data.h"   // RL_Wave file exported with RL_ExportWaveAsCode()
#include "resources/image_data.h"   // RL_Image file exported with RL_ExportImageAsCode()

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [others] example - embedded files loading");

    RL_InitAudioDevice();              // Initialize audio device

    // Loaded in CPU memory (RAM) from header file (audio_data.h)
    // Same as: RL_Wave wave = RL_LoadWave("sound.wav");
    RL_Wave wave = {
        .data = AUDIO_DATA,
        .frameCount = AUDIO_FRAME_COUNT,
        .sampleRate = AUDIO_SAMPLE_RATE,
        .sampleSize = AUDIO_SAMPLE_SIZE,
        .channels = AUDIO_CHANNELS
    };

    // RL_Wave converted to RL_Sound to be played
    RL_Sound sound = RL_LoadSoundFromWave(wave);

    // With a RL_Wave loaded from file, after RL_Sound is loaded, we can unload RL_Wave
    // but in our case, RL_Wave is embedded in executable, in program .data segment
    // we can not (and should not) try to free that private memory region
    //RL_UnloadWave(wave);             // Do not unload wave data!

    // Loaded in CPU memory (RAM) from header file (image_data.h)
    // Same as: RL_Image image = RL_LoadImage("raylib_logo.png");
    RL_Image image = {
        .data = IMAGE_DATA,
        .width = IMAGE_WIDTH,
        .height = IMAGE_HEIGHT,
        .format = IMAGE_FORMAT,
        .mipmaps = 1
    };

    // RL_Image converted to RL_Texture (VRAM) to be drawn
    RL_Texture2D texture = RL_LoadTextureFromImage(image);

    // With an RL_Image loaded from file, after RL_Texture is loaded, we can unload RL_Image
    // but in our case, RL_Image is embedded in executable, in program .data segment
    // we can not (and should not) try to free that private memory region
    //RL_UnloadImage(image);           // Do not unload image data!

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsKeyPressed(KEY_SPACE)) RL_PlaySound(sound);      // Play sound
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawTexture(texture, screenWidth/2 - texture.width/2, 40, RL_WHITE);

            RL_DrawText("raylib logo and sound loaded from header files", 150, 320, 20, RL_LIGHTGRAY);
            RL_DrawText("Press SPACE to PLAY the sound!", 220, 370, 20, RL_LIGHTGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadSound(sound);     // Unload sound from VRAM
    RL_UnloadTexture(texture); // Unload texture from VRAM

    RL_CloseAudioDevice();     // Close audio device

    RL_CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}