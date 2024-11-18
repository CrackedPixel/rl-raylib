/*******************************************************************************************
*
*   raylib [shaders] example - basic lighting
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3).
*
*   Example originally created with raylib 3.0, last time updated with raylib 4.2
*
*   Example contributed by Chris Camacho (@codifies) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Chris Camacho (@codifies) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

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

    RL_SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - basic lighting");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 2.0f, 4.0f, 6.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.5f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    // Load basic lighting shader
    RL_Shader shader = RL_LoadShader(RL_TextFormat("resources/shaders/glsl%i/lighting.vs", GLSL_VERSION),
                               RL_TextFormat("resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));
    // Get some required shader locations
    shader.locs[SHADER_LOC_VECTOR_VIEW] = RL_GetShaderLocation(shader, "viewPos");
    // NOTE: "matModel" location name is automatically assigned on shader loading, 
    // no need to get the location again if using that uniform name
    //shader.locs[SHADER_LOC_MATRIX_MODEL] = RL_GetShaderLocation(shader, "matModel");
    
    // Ambient light level (some basic lighting)
    int ambientLoc = RL_GetShaderLocation(shader, "ambient");
    RL_SetShaderValue(shader, ambientLoc, (float[4]){ 0.1f, 0.1f, 0.1f, 1.0f }, SHADER_UNIFORM_VEC4);

    // Create lights
    Light lights[MAX_LIGHTS] = { 0 };
    lights[0] = CreateLight(LIGHT_POINT, (RL_Vector3){ -2, 1, -2 }, Vector3Zero(), RL_YELLOW, shader);
    lights[1] = CreateLight(LIGHT_POINT, (RL_Vector3){ 2, 1, 2 }, Vector3Zero(), RL_RED, shader);
    lights[2] = CreateLight(LIGHT_POINT, (RL_Vector3){ -2, 1, 2 }, Vector3Zero(), RL_GREEN, shader);
    lights[3] = CreateLight(LIGHT_POINT, (RL_Vector3){ 2, 1, -2 }, Vector3Zero(), RL_BLUE, shader);

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_ORBITAL);

        // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        RL_SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
        
        // Check key inputs to enable/disable lights
        if (RL_IsKeyPressed(KEY_Y)) { lights[0].enabled = !lights[0].enabled; }
        if (RL_IsKeyPressed(KEY_R)) { lights[1].enabled = !lights[1].enabled; }
        if (RL_IsKeyPressed(KEY_G)) { lights[2].enabled = !lights[2].enabled; }
        if (RL_IsKeyPressed(KEY_B)) { lights[3].enabled = !lights[3].enabled; }
        
        // Update light values (actually, only enable/disable them)
        for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(shader, lights[i]);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                RL_BeginShaderMode(shader);

                    RL_DrawPlane(Vector3Zero(), (RL_Vector2) { 10.0, 10.0 }, RL_WHITE);
                    RL_DrawCube(Vector3Zero(), 2.0, 4.0, 2.0, RL_WHITE);

                RL_EndShaderMode();

                // Draw spheres to show where the lights are
                for (int i = 0; i < MAX_LIGHTS; i++)
                {
                    if (lights[i].enabled) RL_DrawSphereEx(lights[i].position, 0.2f, 8, 8, lights[i].color);
                    else RL_DrawSphereWires(lights[i].position, 0.2f, 8, 8, RL_ColorAlpha(lights[i].color, 0.3f));
                }

                RL_DrawGrid(10, 1.0f);

            RL_EndMode3D();

            RL_DrawFPS(10, 10);

            RL_DrawText("Use keys [Y][R][G][B] to toggle lights", 10, 40, 20, RL_DARKGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadShader(shader);   // Unload shader

    RL_CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

