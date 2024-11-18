/*******************************************************************************************
*
*   raylib [text] example - raylib fonts loading
*
*   NOTE: raylib is distributed with some free to use fonts (even for commercial pourposes!)
*         To view details and credits for those fonts, check raylib license file
*
*   Example originally created with raylib 1.7, last time updated with raylib 3.7
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_FONTS   8

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [text] example - raylib fonts");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    RL_Font fonts[MAX_FONTS] = { 0 };

    fonts[0] = RL_LoadFont("resources/fonts/alagard.png");
    fonts[1] = RL_LoadFont("resources/fonts/pixelplay.png");
    fonts[2] = RL_LoadFont("resources/fonts/mecha.png");
    fonts[3] = RL_LoadFont("resources/fonts/setback.png");
    fonts[4] = RL_LoadFont("resources/fonts/romulus.png");
    fonts[5] = RL_LoadFont("resources/fonts/pixantiqua.png");
    fonts[6] = RL_LoadFont("resources/fonts/alpha_beta.png");
    fonts[7] = RL_LoadFont("resources/fonts/jupiter_crash.png");

    const char *messages[MAX_FONTS] = { "ALAGARD FONT designed by Hewett Tsoi",
                                "PIXELPLAY FONT designed by Aleksander Shevchuk",
                                "MECHA FONT designed by Captain Falcon",
                                "SETBACK FONT designed by Brian Kent (AEnigma)",
                                "ROMULUS FONT designed by Hewett Tsoi",
                                "PIXANTIQUA FONT designed by Gerhard Grossmann",
                                "ALPHA_BETA FONT designed by Brian Kent (AEnigma)",
                                "JUPITER_CRASH FONT designed by Brian Kent (AEnigma)" };

    const int spacings[MAX_FONTS] = { 2, 4, 8, 4, 3, 4, 4, 1 };

    RL_Vector2 positions[MAX_FONTS] = { 0 };

    for (int i = 0; i < MAX_FONTS; i++)
    {
        positions[i].x = screenWidth/2.0f - RL_MeasureTextEx(fonts[i], messages[i], fonts[i].baseSize*2.0f, (float)spacings[i]).x/2.0f;
        positions[i].y = 60.0f + fonts[i].baseSize + 45.0f*i;
    }

    // Small Y position corrections
    positions[3].y += 8;
    positions[4].y += 2;
    positions[7].y -= 8;

    RL_Color colors[MAX_FONTS] = { RL_MAROON, RL_ORANGE, RL_DARKGREEN, RL_DARKBLUE, RL_DARKPURPLE, RL_LIME, RL_GOLD, RL_RED };

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

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

            RL_DrawText("free fonts included with raylib", 250, 20, 20, RL_DARKGRAY);
            RL_DrawLine(220, 50, 590, 50, RL_DARKGRAY);

            for (int i = 0; i < MAX_FONTS; i++)
            {
                RL_DrawTextEx(fonts[i], messages[i], positions[i], fonts[i].baseSize*2.0f, (float)spacings[i], colors[i]);
            }

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // Fonts unloading
    for (int i = 0; i < MAX_FONTS; i++) RL_UnloadFont(fonts[i]);

    RL_CloseWindow();                 // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}