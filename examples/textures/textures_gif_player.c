/*******************************************************************************************
*
*   raylib [textures] example - gif playing
*
*   Example originally created with raylib 4.2, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_FRAME_DELAY     20
#define MIN_FRAME_DELAY      1

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [textures] example - gif playing");

    int animFrames = 0;

    // Load all GIF animation frames into a single RL_Image
    // NOTE: GIF data is always loaded as RGBA (32bit) by default
    // NOTE: Frames are just appended one after another in image.data memory
    RL_Image imScarfyAnim = RL_LoadImageAnim("resources/scarfy_run.gif", &animFrames);

    // Load texture from image
    // NOTE: We will update this texture when required with next frame data
    // WARNING: It's not recommended to use this technique for sprites animation,
    // use spritesheets instead, like illustrated in textures_sprite_anim example
    RL_Texture2D texScarfyAnim = RL_LoadTextureFromImage(imScarfyAnim);

    unsigned int nextFrameDataOffset = 0;  // Current byte offset to next frame in image.data

    int currentAnimFrame = 0;       // Current animation frame to load and draw
    int frameDelay = 8;             // Frame delay to switch between animation frames
    int frameCounter = 0;           // General frames counter

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        frameCounter++;
        if (frameCounter >= frameDelay)
        {
            // Move to next frame
            // NOTE: If final frame is reached we return to first frame
            currentAnimFrame++;
            if (currentAnimFrame >= animFrames) currentAnimFrame = 0;

            // Get memory offset position for next frame data in image.data
            nextFrameDataOffset = imScarfyAnim.width*imScarfyAnim.height*4*currentAnimFrame;

            // Update GPU texture data with next frame image data
            // WARNING: Data size (frame size) and pixel format must match already created texture
            RL_UpdateTexture(texScarfyAnim, ((unsigned char *)imScarfyAnim.data) + nextFrameDataOffset);

            frameCounter = 0;
        }

        // Control frames delay
        if (RL_IsKeyPressed(KEY_RIGHT)) frameDelay++;
        else if (RL_IsKeyPressed(KEY_LEFT)) frameDelay--;

        if (frameDelay > MAX_FRAME_DELAY) frameDelay = MAX_FRAME_DELAY;
        else if (frameDelay < MIN_FRAME_DELAY) frameDelay = MIN_FRAME_DELAY;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawText(RL_TextFormat("TOTAL GIF FRAMES:  %02i", animFrames), 50, 30, 20, RL_LIGHTGRAY);
            RL_DrawText(RL_TextFormat("CURRENT FRAME: %02i", currentAnimFrame), 50, 60, 20, RL_GRAY);
            RL_DrawText(RL_TextFormat("CURRENT FRAME IMAGE.DATA OFFSET: %02i", nextFrameDataOffset), 50, 90, 20, RL_GRAY);

            RL_DrawText("FRAMES DELAY: ", 100, 305, 10, RL_DARKGRAY);
            RL_DrawText(RL_TextFormat("%02i frames", frameDelay), 620, 305, 10, RL_DARKGRAY);
            RL_DrawText("PRESS RIGHT/LEFT KEYS to CHANGE SPEED!", 290, 350, 10, RL_DARKGRAY);

            for (int i = 0; i < MAX_FRAME_DELAY; i++)
            {
                if (i < frameDelay) RL_DrawRectangle(190 + 21*i, 300, 20, 20, RL_RED);
                RL_DrawRectangleLines(190 + 21*i, 300, 20, 20, RL_MAROON);
            }

            RL_DrawTexture(texScarfyAnim, RL_GetScreenWidth()/2 - texScarfyAnim.width/2, 140, RL_WHITE);

            RL_DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, RL_GRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(texScarfyAnim);   // Unload texture
    RL_UnloadImage(imScarfyAnim);      // Unload image (contains all frames)

    RL_CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}