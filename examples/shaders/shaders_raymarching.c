/*******************************************************************************************
*
*   raylib [shaders] example - Raymarching shapes generation
*
*   NOTE: This example requires raylib OpenGL 3.3 for shaders support and only #version 330
*         is currently supported. OpenGL ES 2.0 platforms are not supported at the moment.
*
*   Example originally created with raylib 2.0, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB -> Not supported at this moment
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

    RL_SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - raymarching shapes");

    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 2.5f, 2.5f, 3.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.0f, 0.7f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 65.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    // Load raymarching shader
    // NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
    RL_Shader shader = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/raymarching.fs", GLSL_VERSION));

    // Get shader locations for required uniforms
    int viewEyeLoc = RL_GetShaderLocation(shader, "viewEye");
    int viewCenterLoc = RL_GetShaderLocation(shader, "viewCenter");
    int runTimeLoc = RL_GetShaderLocation(shader, "runTime");
    int resolutionLoc = RL_GetShaderLocation(shader, "resolution");

    float resolution[2] = { (float)screenWidth, (float)screenHeight };
    RL_SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    float runTime = 0.0f;

    RL_DisableCursor();                    // Limit cursor to relative movement inside the window
    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        float cameraTarget[3] = { camera.target.x, camera.target.y, camera.target.z };

        float deltaTime = RL_GetFrameTime();
        runTime += deltaTime;

        // Set shader required uniform values
        RL_SetShaderValue(shader, viewEyeLoc, cameraPos, SHADER_UNIFORM_VEC3);
        RL_SetShaderValue(shader, viewCenterLoc, cameraTarget, SHADER_UNIFORM_VEC3);
        RL_SetShaderValue(shader, runTimeLoc, &runTime, SHADER_UNIFORM_FLOAT);

        // Check if screen is resized
        if (RL_IsWindowResized())
        {
            resolution[0] = (float)RL_GetScreenWidth();
            resolution[1] = (float)RL_GetScreenHeight();
            RL_SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            // We only draw a white full-screen rectangle,
            // frame is generated in shader using raymarching
            RL_BeginShaderMode(shader);
                RL_DrawRectangle(0, 0, RL_GetScreenWidth(), RL_GetScreenHeight(), RL_WHITE);
            RL_EndShaderMode();

            RL_DrawText("(c) Raymarching shader by Iñigo Quilez. MIT License.", RL_GetScreenWidth() - 280, RL_GetScreenHeight() - 20, 10, RL_BLACK);

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
