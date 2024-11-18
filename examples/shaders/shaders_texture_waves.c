/*******************************************************************************************
*
*   raylib [shaders] example - RL_Texture Waves
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3), to test this example
*         on OpenGL ES 2.0 platforms (Android, Raspberry Pi, HTML5), use #version 100 shaders
*         raylib comes with shaders ready for both versions, check raylib/shaders install folder
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.7
*
*   Example contributed by Anata (@anatagawa) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Anata (@anatagawa) and Ramon Santamaria (@raysan5)
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - texture waves");

    // Load texture texture to apply shaders
    RL_Texture2D texture = RL_LoadTexture("resources/space.png");

    // Load shader and setup location points and values
    RL_Shader shader = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/wave.fs", GLSL_VERSION));

    int secondsLoc = RL_GetShaderLocation(shader, "seconds");
    int freqXLoc = RL_GetShaderLocation(shader, "freqX");
    int freqYLoc = RL_GetShaderLocation(shader, "freqY");
    int ampXLoc = RL_GetShaderLocation(shader, "ampX");
    int ampYLoc = RL_GetShaderLocation(shader, "ampY");
    int speedXLoc = RL_GetShaderLocation(shader, "speedX");
    int speedYLoc = RL_GetShaderLocation(shader, "speedY");

    // RL_Shader uniform values that can be updated at any time
    float freqX = 25.0f;
    float freqY = 25.0f;
    float ampX = 5.0f;
    float ampY = 5.0f;
    float speedX = 8.0f;
    float speedY = 8.0f;

    float screenSize[2] = { (float)RL_GetScreenWidth(), (float)RL_GetScreenHeight() };
    RL_SetShaderValue(shader, RL_GetShaderLocation(shader, "size"), &screenSize, SHADER_UNIFORM_VEC2);
    RL_SetShaderValue(shader, freqXLoc, &freqX, SHADER_UNIFORM_FLOAT);
    RL_SetShaderValue(shader, freqYLoc, &freqY, SHADER_UNIFORM_FLOAT);
    RL_SetShaderValue(shader, ampXLoc, &ampX, SHADER_UNIFORM_FLOAT);
    RL_SetShaderValue(shader, ampYLoc, &ampY, SHADER_UNIFORM_FLOAT);
    RL_SetShaderValue(shader, speedXLoc, &speedX, SHADER_UNIFORM_FLOAT);
    RL_SetShaderValue(shader, speedYLoc, &speedY, SHADER_UNIFORM_FLOAT);

    float seconds = 0.0f;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    // -------------------------------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        seconds += RL_GetFrameTime();

        RL_SetShaderValue(shader, secondsLoc, &seconds, SHADER_UNIFORM_FLOAT);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginShaderMode(shader);

                RL_DrawTexture(texture, 0, 0, RL_WHITE);
                RL_DrawTexture(texture, texture.width, 0, RL_WHITE);

            RL_EndShaderMode();

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadShader(shader);         // Unload shader
    RL_UnloadTexture(texture);       // Unload texture

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
