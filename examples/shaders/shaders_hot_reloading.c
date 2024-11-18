/*******************************************************************************************
*
*   raylib [shaders] example - Hot reloading
*
*   NOTE: This example requires raylib OpenGL 3.3 for shaders support and only #version 330
*         is currently supported. OpenGL ES 2.0 platforms are not supported at the moment.
*
*   Example originally created with raylib 3.0, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2020-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "rlgl.h"

#include <time.h>       // Required for: localtime(), asctime()

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

    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - hot reloading");

    const char *fragShaderFileName = "resources/shaders/glsl%i/reload.fs";
    time_t fragShaderFileModTime = RL_GetFileModTime(RL_TextFormat(fragShaderFileName, GLSL_VERSION));

    // Load raymarching shader
    // NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
    RL_Shader shader = RL_LoadShader(0, RL_TextFormat(fragShaderFileName, GLSL_VERSION));

    // Get shader locations for required uniforms
    int resolutionLoc = RL_GetShaderLocation(shader, "resolution");
    int mouseLoc = RL_GetShaderLocation(shader, "mouse");
    int timeLoc = RL_GetShaderLocation(shader, "time");

    float resolution[2] = { (float)screenWidth, (float)screenHeight };
    RL_SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    float totalTime = 0.0f;
    bool shaderAutoReloading = false;

    RL_SetTargetFPS(60);                       // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())            // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        totalTime += RL_GetFrameTime();
        RL_Vector2 mouse = RL_GetMousePosition();
        float mousePos[2] = { mouse.x, mouse.y };

        // Set shader required uniform values
        RL_SetShaderValue(shader, timeLoc, &totalTime, SHADER_UNIFORM_FLOAT);
        RL_SetShaderValue(shader, mouseLoc, mousePos, SHADER_UNIFORM_VEC2);

        // Hot shader reloading
        if (shaderAutoReloading || (RL_IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
        {
            long currentFragShaderModTime = RL_GetFileModTime(RL_TextFormat(fragShaderFileName, GLSL_VERSION));

            // Check if shader file has been modified
            if (currentFragShaderModTime != fragShaderFileModTime)
            {
                // Try reloading updated shader
                RL_Shader updatedShader = RL_LoadShader(0, RL_TextFormat(fragShaderFileName, GLSL_VERSION));

                if (updatedShader.id != rlGetShaderIdDefault())      // It was correctly loaded
                {
                    RL_UnloadShader(shader);
                    shader = updatedShader;

                    // Get shader locations for required uniforms
                    resolutionLoc = RL_GetShaderLocation(shader, "resolution");
                    mouseLoc = RL_GetShaderLocation(shader, "mouse");
                    timeLoc = RL_GetShaderLocation(shader, "time");

                    // Reset required uniforms
                    RL_SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
                }

                fragShaderFileModTime = currentFragShaderModTime;
            }
        }

        if (RL_IsKeyPressed(KEY_A)) shaderAutoReloading = !shaderAutoReloading;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            // We only draw a white full-screen rectangle, frame is generated in shader
            RL_BeginShaderMode(shader);
                RL_DrawRectangle(0, 0, screenWidth, screenHeight, RL_WHITE);
            RL_EndShaderMode();

            RL_DrawText(RL_TextFormat("PRESS [A] to TOGGLE SHADER AUTOLOADING: %s",
                     shaderAutoReloading? "AUTO" : "MANUAL"), 10, 10, 10, shaderAutoReloading? RL_RED : RL_BLACK);
            if (!shaderAutoReloading) RL_DrawText("MOUSE CLICK to SHADER RE-LOADING", 10, 30, 10, RL_BLACK);

            RL_DrawText(RL_TextFormat("RL_Shader last modification: %s", asctime(localtime(&fragShaderFileModTime))), 10, 430, 10, RL_BLACK);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadShader(shader);           // Unload shader

    RL_CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
