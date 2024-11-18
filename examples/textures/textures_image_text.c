/*******************************************************************************************
*
*   raylib [texture] example - RL_Image text drawing using TTF generated font
*
*   Example originally created with raylib 1.8, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2024 Ramon Santamaria (@raysan5)
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [texture] example - image text drawing");

    RL_Image parrots = RL_LoadImage("resources/parrots.png"); // Load image in CPU memory (RAM)

    // TTF RL_Font loading with custom generation parameters
    RL_Font font = RL_LoadFontEx("resources/KAISG.ttf", 64, 0, 0);

    // Draw over image using custom font
    RL_ImageDrawTextEx(&parrots, font, "[Parrots font drawing]", (RL_Vector2){ 20.0f, 20.0f }, (float)font.baseSize, 0.0f, RL_RED);

    RL_Texture2D texture = RL_LoadTextureFromImage(parrots);  // RL_Image converted to texture, uploaded to GPU memory (VRAM)
    RL_UnloadImage(parrots);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    RL_Vector2 position = { (float)(screenWidth/2 - texture.width/2), (float)(screenHeight/2 - texture.height/2 - 20) };

    bool showFont = false;

    RL_SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsKeyDown(KEY_SPACE)) showFont = true;
        else showFont = false;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            if (!showFont)
            {
                // Draw texture with text already drawn inside
                RL_DrawTextureV(texture, position, RL_WHITE);

                // Draw text directly using sprite font
                RL_DrawTextEx(font, "[Parrots font drawing]", (RL_Vector2){ position.x + 20,
                           position.y + 20 + 280 }, (float)font.baseSize, 0.0f, RL_WHITE);
            }
            else RL_DrawTexture(font.texture, screenWidth/2 - font.texture.width/2, 50, RL_BLACK);

            RL_DrawText("PRESS SPACE to SHOW FONT ATLAS USED", 290, 420, 10, RL_DARKGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(texture);     // RL_Texture unloading

    RL_UnloadFont(font);           // Unload custom font

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}