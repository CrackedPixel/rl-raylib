/*******************************************************************************************
*
*   raylib [text] example - RL_Font SDF loading
*
*   Example originally created with raylib 1.3, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

#include <stdlib.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [text] example - SDF fonts");

    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)

    const char msg[50] = "Signed Distance Fields";

    // Loading file to memory
    int fileSize = 0;
    unsigned char *fileData = RL_LoadFileData("resources/anonymous_pro_bold.ttf", &fileSize);

    // Default font generation from TTF font
    RL_Font fontDefault = { 0 };
    fontDefault.baseSize = 16;
    fontDefault.glyphCount = 95;

    // Loading font data from memory data
    // Parameters > font size: 16, no glyphs array provided (0), glyphs count: 95 (autogenerate chars array)
    fontDefault.glyphs = RL_LoadFontData(fileData, fileSize, 16, 0, 95, FONT_DEFAULT);
    // Parameters > glyphs count: 95, font size: 16, glyphs padding in image: 4 px, pack method: 0 (default)
    RL_Image atlas = RL_GenImageFontAtlas(fontDefault.glyphs, &fontDefault.recs, 95, 16, 4, 0);
    fontDefault.texture = RL_LoadTextureFromImage(atlas);
    RL_UnloadImage(atlas);

    // SDF font generation from TTF font
    RL_Font fontSDF = { 0 };
    fontSDF.baseSize = 16;
    fontSDF.glyphCount = 95;
    // Parameters > font size: 16, no glyphs array provided (0), glyphs count: 0 (defaults to 95)
    fontSDF.glyphs = RL_LoadFontData(fileData, fileSize, 16, 0, 0, FONT_SDF);
    // Parameters > glyphs count: 95, font size: 16, glyphs padding in image: 0 px, pack method: 1 (Skyline algorythm)
    atlas = RL_GenImageFontAtlas(fontSDF.glyphs, &fontSDF.recs, 95, 16, 0, 1);
    fontSDF.texture = RL_LoadTextureFromImage(atlas);
    RL_UnloadImage(atlas);

    RL_UnloadFileData(fileData);      // Free memory from loaded file

    // Load SDF required shader (we use default vertex shader)
    RL_Shader shader = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/sdf.fs", GLSL_VERSION));
    RL_SetTextureFilter(fontSDF.texture, TEXTURE_FILTER_BILINEAR);    // Required for SDF font

    RL_Vector2 fontPosition = { 40, screenHeight/2.0f - 50 };
    RL_Vector2 textSize = { 0.0f, 0.0f };
    float fontSize = 16.0f;
    int currentFont = 0;            // 0 - fontDefault, 1 - fontSDF

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        fontSize += RL_GetMouseWheelMove()*8.0f;

        if (fontSize < 6) fontSize = 6;

        if (RL_IsKeyDown(KEY_SPACE)) currentFont = 1;
        else currentFont = 0;

        if (currentFont == 0) textSize = RL_MeasureTextEx(fontDefault, msg, fontSize, 0);
        else textSize = RL_MeasureTextEx(fontSDF, msg, fontSize, 0);

        fontPosition.x = RL_GetScreenWidth()/2 - textSize.x/2;
        fontPosition.y = RL_GetScreenHeight()/2 - textSize.y/2 + 80;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            if (currentFont == 1)
            {
                // NOTE: SDF fonts require a custom SDf shader to compute fragment color
                RL_BeginShaderMode(shader);    // Activate SDF font shader
                    RL_DrawTextEx(fontSDF, msg, fontPosition, fontSize, 0, RL_BLACK);
                RL_EndShaderMode();            // Activate our default shader for next drawings

                RL_DrawTexture(fontSDF.texture, 10, 10, RL_BLACK);
            }
            else
            {
                RL_DrawTextEx(fontDefault, msg, fontPosition, fontSize, 0, RL_BLACK);
                RL_DrawTexture(fontDefault.texture, 10, 10, RL_BLACK);
            }

            if (currentFont == 1) RL_DrawText("SDF!", 320, 20, 80, RL_RED);
            else RL_DrawText("default font", 315, 40, 30, RL_GRAY);

            RL_DrawText("FONT SIZE: 16.0", RL_GetScreenWidth() - 240, 20, 20, RL_DARKGRAY);
            RL_DrawText(RL_TextFormat("RENDER SIZE: %02.02f", fontSize), RL_GetScreenWidth() - 240, 50, 20, RL_DARKGRAY);
            RL_DrawText("Use MOUSE WHEEL to SCALE TEXT!", RL_GetScreenWidth() - 240, 90, 10, RL_DARKGRAY);

            RL_DrawText("HOLD SPACE to USE SDF FONT VERSION!", 340, RL_GetScreenHeight() - 30, 20, RL_MAROON);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadFont(fontDefault);    // Default font unloading
    RL_UnloadFont(fontSDF);        // SDF font unloading

    RL_UnloadShader(shader);       // Unload SDF shader

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}