/*******************************************************************************************
*
*   raylib [textures] example - blend modes
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   Example originally created with raylib 3.5, last time updated with raylib 3.5
*
*   Example contributed by Karlo Licudine (@accidentalrebel) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2020-2024 Karlo Licudine (@accidentalrebel)
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [textures] example - blend modes");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    RL_Image bgImage = RL_LoadImage("resources/cyberpunk_street_background.png");     // Loaded in CPU memory (RAM)
    RL_Texture2D bgTexture = RL_LoadTextureFromImage(bgImage);          // RL_Image converted to texture, GPU memory (VRAM)

    RL_Image fgImage = RL_LoadImage("resources/cyberpunk_street_foreground.png");     // Loaded in CPU memory (RAM)
    RL_Texture2D fgTexture = RL_LoadTextureFromImage(fgImage);          // RL_Image converted to texture, GPU memory (VRAM)

    // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM
    RL_UnloadImage(bgImage);
    RL_UnloadImage(fgImage);

    const int blendCountMax = 4;
    RL_BlendMode blendMode = 0;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsKeyPressed(KEY_SPACE))
        {
            if (blendMode >= (blendCountMax - 1)) blendMode = 0;
            else blendMode++;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawTexture(bgTexture, screenWidth/2 - bgTexture.width/2, screenHeight/2 - bgTexture.height/2, RL_WHITE);

            // Apply the blend mode and then draw the foreground texture
            RL_BeginBlendMode(blendMode);
                RL_DrawTexture(fgTexture, screenWidth/2 - fgTexture.width/2, screenHeight/2 - fgTexture.height/2, RL_WHITE);
            RL_EndBlendMode();

            // Draw the texts
            RL_DrawText("Press SPACE to change blend modes.", 310, 350, 10, RL_GRAY);

            switch (blendMode)
            {
                case BLEND_ALPHA: RL_DrawText("Current: BLEND_ALPHA", (screenWidth / 2) - 60, 370, 10, RL_GRAY); break;
                case BLEND_ADDITIVE: RL_DrawText("Current: BLEND_ADDITIVE", (screenWidth / 2) - 60, 370, 10, RL_GRAY); break;
                case BLEND_MULTIPLIED: RL_DrawText("Current: BLEND_MULTIPLIED", (screenWidth / 2) - 60, 370, 10, RL_GRAY); break;
                case BLEND_ADD_COLORS: RL_DrawText("Current: BLEND_ADD_COLORS", (screenWidth / 2) - 60, 370, 10, RL_GRAY); break;
                default: break;
            }

            RL_DrawText("(c) Cyberpunk Street Environment by Luis Zuno (@ansimuz)", screenWidth - 330, screenHeight - 20, 10, RL_GRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(fgTexture); // Unload foreground texture
    RL_UnloadTexture(bgTexture); // Unload background texture

    RL_CloseWindow();            // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
