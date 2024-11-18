/*******************************************************************************************
*
*   raylib [audio] example - Module playing (streaming)
*
*   Example originally created with raylib 1.5, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2016-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_CIRCLES  64

typedef struct {
    RL_Vector2 position;
    float radius;
    float alpha;
    float speed;
    RL_Color color;
} CircleWave;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_SetConfigFlags(FLAG_MSAA_4X_HINT);  // NOTE: Try to enable MSAA 4X

    RL_InitWindow(screenWidth, screenHeight, "raylib [audio] example - module playing (streaming)");

    RL_InitAudioDevice();                  // Initialize audio device

    RL_Color colors[14] = { RL_ORANGE, RL_RED, RL_GOLD, RL_LIME, RL_BLUE, RL_VIOLET, RL_BROWN, RL_LIGHTGRAY, RL_PINK,
                         RL_YELLOW, RL_GREEN, RL_SKYBLUE, RL_PURPLE, RL_BEIGE };

    // Creates some circles for visual effect
    CircleWave circles[MAX_CIRCLES] = { 0 };

    for (int i = MAX_CIRCLES - 1; i >= 0; i--)
    {
        circles[i].alpha = 0.0f;
        circles[i].radius = (float)RL_GetRandomValue(10, 40);
        circles[i].position.x = (float)RL_GetRandomValue((int)circles[i].radius, (int)(screenWidth - circles[i].radius));
        circles[i].position.y = (float)RL_GetRandomValue((int)circles[i].radius, (int)(screenHeight - circles[i].radius));
        circles[i].speed = (float)RL_GetRandomValue(1, 100)/2000.0f;
        circles[i].color = colors[RL_GetRandomValue(0, 13)];
    }

    RL_Music music = RL_LoadMusicStream("resources/mini1111.xm");
    music.looping = false;
    float pitch = 1.0f;

    RL_PlayMusicStream(music);

    float timePlayed = 0.0f;
    bool pause = false;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateMusicStream(music);      // Update music buffer with new stream data

        // Restart music playing (stop and play)
        if (RL_IsKeyPressed(KEY_SPACE))
        {
            RL_StopMusicStream(music);
            RL_PlayMusicStream(music);
            pause = false;
        }

        // Pause/Resume music playing
        if (RL_IsKeyPressed(KEY_P))
        {
            pause = !pause;

            if (pause) RL_PauseMusicStream(music);
            else RL_ResumeMusicStream(music);
        }

        if (RL_IsKeyDown(KEY_DOWN)) pitch -= 0.01f;
        else if (RL_IsKeyDown(KEY_UP)) pitch += 0.01f;

        RL_SetMusicPitch(music, pitch);

        // Get timePlayed scaled to bar dimensions
        timePlayed = RL_GetMusicTimePlayed(music)/RL_GetMusicTimeLength(music)*(screenWidth - 40);

        // RL_Color circles animation
        for (int i = MAX_CIRCLES - 1; (i >= 0) && !pause; i--)
        {
            circles[i].alpha += circles[i].speed;
            circles[i].radius += circles[i].speed*10.0f;

            if (circles[i].alpha > 1.0f) circles[i].speed *= -1;

            if (circles[i].alpha <= 0.0f)
            {
                circles[i].alpha = 0.0f;
                circles[i].radius = (float)RL_GetRandomValue(10, 40);
                circles[i].position.x = (float)RL_GetRandomValue((int)circles[i].radius, (int)(screenWidth - circles[i].radius));
                circles[i].position.y = (float)RL_GetRandomValue((int)circles[i].radius, (int)(screenHeight - circles[i].radius));
                circles[i].color = colors[RL_GetRandomValue(0, 13)];
                circles[i].speed = (float)RL_GetRandomValue(1, 100)/2000.0f;
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            for (int i = MAX_CIRCLES - 1; i >= 0; i--)
            {
                RL_DrawCircleV(circles[i].position, circles[i].radius, RL_Fade(circles[i].color, circles[i].alpha));
            }

            // Draw time bar
            RL_DrawRectangle(20, screenHeight - 20 - 12, screenWidth - 40, 12, RL_LIGHTGRAY);
            RL_DrawRectangle(20, screenHeight - 20 - 12, (int)timePlayed, 12, RL_MAROON);
            RL_DrawRectangleLines(20, screenHeight - 20 - 12, screenWidth - 40, 12, RL_GRAY);

            // Draw help instructions
            RL_DrawRectangle(20, 20, 425, 145, RL_WHITE);
            RL_DrawRectangleLines(20, 20, 425, 145, RL_GRAY);
            RL_DrawText("PRESS SPACE TO RESTART MUSIC", 40, 40, 20, RL_BLACK);
            RL_DrawText("PRESS P TO PAUSE/RESUME", 40, 70, 20, RL_BLACK);
            RL_DrawText("PRESS UP/DOWN TO CHANGE SPEED", 40, 100, 20, RL_BLACK);
            RL_DrawText(RL_TextFormat("SPEED: %f", pitch), 40, 130, 20, RL_MAROON);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadMusicStream(music);          // Unload music stream buffers from RAM

    RL_CloseAudioDevice();     // Close audio device (music streaming is automatically stopped)

    RL_CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
