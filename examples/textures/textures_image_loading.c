/*******************************************************************************************
*
*   raylib [textures] example - RL_Image loading and texture creation
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   Example originally created with raylib 1.3, last time updated with raylib 1.3
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [textures] example - image loading");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    RL_Image image = RL_LoadImage("resources/raylib_logo.png");     // Loaded in CPU memory (RAM)
    RL_Texture2D texture = RL_LoadTextureFromImage(image);          // RL_Image converted to texture, GPU memory (VRAM)
    RL_UnloadImage(image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    RL_SetTargetFPS(60);     // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

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

            RL_DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, RL_WHITE);

            RL_DrawText("this IS a texture loaded from an image!", 300, 370, 10, RL_GRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(texture);       // RL_Texture unloading

    RL_CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
