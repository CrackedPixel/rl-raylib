/*******************************************************************************************
*
*   raylib [textures] example - Sprite animation
*
*   Example originally created with raylib 1.3, last time updated with raylib 1.3
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [texture] example - sprite anim");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    RL_Texture2D scarfy = RL_LoadTexture("resources/scarfy.png");        // RL_Texture loading

    RL_Vector2 position = { 350.0f, 280.0f };
    RL_Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width/6, (float)scarfy.height };
    int currentFrame = 0;

    int framesCounter = 0;
    int framesSpeed = 8;            // Number of spritesheet frames shown by second

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        framesCounter++;

        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            frameRec.x = (float)currentFrame*(float)scarfy.width/6;
        }

        // Control frames speed
        if (RL_IsKeyPressed(KEY_RIGHT)) framesSpeed++;
        else if (RL_IsKeyPressed(KEY_LEFT)) framesSpeed--;

        if (framesSpeed > MAX_FRAME_SPEED) framesSpeed = MAX_FRAME_SPEED;
        else if (framesSpeed < MIN_FRAME_SPEED) framesSpeed = MIN_FRAME_SPEED;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawTexture(scarfy, 15, 40, RL_WHITE);
            RL_DrawRectangleLines(15, 40, scarfy.width, scarfy.height, RL_LIME);
            RL_DrawRectangleLines(15 + (int)frameRec.x, 40 + (int)frameRec.y, (int)frameRec.width, (int)frameRec.height, RL_RED);

            RL_DrawText("FRAME SPEED: ", 165, 210, 10, RL_DARKGRAY);
            RL_DrawText(RL_TextFormat("%02i FPS", framesSpeed), 575, 210, 10, RL_DARKGRAY);
            RL_DrawText("PRESS RIGHT/LEFT KEYS to CHANGE SPEED!", 290, 240, 10, RL_DARKGRAY);

            for (int i = 0; i < MAX_FRAME_SPEED; i++)
            {
                if (i < framesSpeed) RL_DrawRectangle(250 + 21*i, 205, 20, 20, RL_RED);
                RL_DrawRectangleLines(250 + 21*i, 205, 20, 20, RL_MAROON);
            }

            RL_DrawTextureRec(scarfy, frameRec, position, RL_WHITE);  // Draw part of the texture

            RL_DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, RL_GRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(scarfy);       // RL_Texture unloading

    RL_CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}