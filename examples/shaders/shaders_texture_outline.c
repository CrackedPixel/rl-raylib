/*******************************************************************************************
*
*   raylib [shaders] example - Apply an shdrOutline to a texture
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   Example originally created with raylib 4.0, last time updated with raylib 4.0
*
*   Example contributed by Samuel Skiff (@GoldenThumbs) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2024 Samuel SKiff (@GoldenThumbs) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - Apply an outline to a texture");

    RL_Texture2D texture = RL_LoadTexture("resources/fudesumi.png");

    RL_Shader shdrOutline = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/outline.fs", GLSL_VERSION));

    float outlineSize = 2.0f;
    float outlineColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };     // Normalized RL_RED color
    float textureSize[2] = { (float)texture.width, (float)texture.height };

    // Get shader locations
    int outlineSizeLoc = RL_GetShaderLocation(shdrOutline, "outlineSize");
    int outlineColorLoc = RL_GetShaderLocation(shdrOutline, "outlineColor");
    int textureSizeLoc = RL_GetShaderLocation(shdrOutline, "textureSize");

    // Set shader values (they can be changed later)
    RL_SetShaderValue(shdrOutline, outlineSizeLoc, &outlineSize, SHADER_UNIFORM_FLOAT);
    RL_SetShaderValue(shdrOutline, outlineColorLoc, outlineColor, SHADER_UNIFORM_VEC4);
    RL_SetShaderValue(shdrOutline, textureSizeLoc, textureSize, SHADER_UNIFORM_VEC2);

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        outlineSize += RL_GetMouseWheelMove();
        if (outlineSize < 1.0f) outlineSize = 1.0f;

        RL_SetShaderValue(shdrOutline, outlineSizeLoc, &outlineSize, SHADER_UNIFORM_FLOAT);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginShaderMode(shdrOutline);

                RL_DrawTexture(texture, RL_GetScreenWidth()/2 - texture.width/2, -30, RL_WHITE);

            RL_EndShaderMode();

            RL_DrawText("RL_Shader-based\ntexture\noutline", 10, 10, 20, RL_GRAY);
            RL_DrawText("Scroll mouse wheel to\nchange outline size", 10, 72, 20, RL_GRAY);
            RL_DrawText(RL_TextFormat("Outline size: %i px", (int)outlineSize), 10, 120, 20, RL_MAROON);

            RL_DrawFPS(710, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(texture);
    RL_UnloadShader(shdrOutline);

    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
