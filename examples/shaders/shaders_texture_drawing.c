/*******************************************************************************************
*
*   raylib [textures] example - RL_Texture drawing
*
*   NOTE: This example illustrates how to draw into a blank texture using a shader
*
*   Example originally created with raylib 2.0, last time updated with raylib 3.7
*
*   Example contributed by Michał Ciesielski and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Michał Ciesielski and Ramon Santamaria (@raysan5)
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - texture drawing");

    RL_Image imBlank = RL_GenImageColor(1024, 1024, RL_BLANK);
    RL_Texture2D texture = RL_LoadTextureFromImage(imBlank);  // Load blank texture to fill on shader
    RL_UnloadImage(imBlank);

    // NOTE: Using GLSL 330 shader version, on OpenGL ES 2.0 use GLSL 100 shader version
    RL_Shader shader = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/cubes_panning.fs", GLSL_VERSION));

    float time = 0.0f;
    int timeLoc = RL_GetShaderLocation(shader, "uTime");
    RL_SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    // -------------------------------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        time = (float)RL_GetTime();
        RL_SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginShaderMode(shader);    // Enable our custom shader for next shapes/textures drawings
                RL_DrawTexture(texture, 0, 0, RL_WHITE);  // Drawing RL_BLANK texture, all magic happens on shader
            RL_EndShaderMode();            // Disable our custom shader, return to default shader

            RL_DrawText("BACKGROUND is PAINTED and ANIMATED on SHADER!", 10, 10, 20, RL_MAROON);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadShader(shader);
    RL_UnloadTexture(texture);

    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
