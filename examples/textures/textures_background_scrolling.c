/*******************************************************************************************
*
*   raylib [textures] example - Background scrolling
*
*   Example originally created with raylib 2.0, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Ramon Santamaria (@raysan5)
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [textures] example - background scrolling");

    // NOTE: Be careful, background width must be equal or bigger than screen width
    // if not, texture should be draw more than two times for scrolling effect
    RL_Texture2D background = RL_LoadTexture("resources/cyberpunk_street_background.png");
    RL_Texture2D midground = RL_LoadTexture("resources/cyberpunk_street_midground.png");
    RL_Texture2D foreground = RL_LoadTexture("resources/cyberpunk_street_foreground.png");

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        scrollingBack -= 0.1f;
        scrollingMid -= 0.5f;
        scrollingFore -= 1.0f;

        // NOTE: RL_Texture is scaled twice its size, so it sould be considered on scrolling
        if (scrollingBack <= -background.width*2) scrollingBack = 0;
        if (scrollingMid <= -midground.width*2) scrollingMid = 0;
        if (scrollingFore <= -foreground.width*2) scrollingFore = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_GetColor(0x052c46ff));

            // Draw background image twice
            // NOTE: RL_Texture is scaled twice its size
            RL_DrawTextureEx(background, (RL_Vector2){ scrollingBack, 20 }, 0.0f, 2.0f, RL_WHITE);
            RL_DrawTextureEx(background, (RL_Vector2){ background.width*2 + scrollingBack, 20 }, 0.0f, 2.0f, RL_WHITE);

            // Draw midground image twice
            RL_DrawTextureEx(midground, (RL_Vector2){ scrollingMid, 20 }, 0.0f, 2.0f, RL_WHITE);
            RL_DrawTextureEx(midground, (RL_Vector2){ midground.width*2 + scrollingMid, 20 }, 0.0f, 2.0f, RL_WHITE);

            // Draw foreground image twice
            RL_DrawTextureEx(foreground, (RL_Vector2){ scrollingFore, 70 }, 0.0f, 2.0f, RL_WHITE);
            RL_DrawTextureEx(foreground, (RL_Vector2){ foreground.width*2 + scrollingFore, 70 }, 0.0f, 2.0f, RL_WHITE);

            RL_DrawText("BACKGROUND SCROLLING & PARALLAX", 10, 10, 20, RL_RED);
            RL_DrawText("(c) Cyberpunk Street Environment by Luis Zuno (@ansimuz)", screenWidth - 330, screenHeight - 20, 10, RL_RAYWHITE);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(background);  // Unload background texture
    RL_UnloadTexture(midground);   // Unload midground texture
    RL_UnloadTexture(foreground);  // Unload foreground texture

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}