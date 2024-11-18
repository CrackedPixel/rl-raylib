/*******************************************************************************************
*
*   raylib [shaders] example - fog
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3).
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.7
*
*   Example contributed by Chris Camacho (@chriscamacho) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Chris Camacho (@chriscamacho) and Ramon Santamaria (@raysan5)
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
    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - fog");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 2.0f, 2.0f, 6.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.5f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    // Load models and texture
    RL_Model modelA = RL_LoadModelFromMesh(RL_GenMeshTorus(0.4f, 1.0f, 16, 32));
    RL_Model modelB = RL_LoadModelFromMesh(RL_GenMeshCube(1.0f, 1.0f, 1.0f));
    RL_Model modelC = RL_LoadModelFromMesh(RL_GenMeshSphere(0.5f, 32, 32));
    RL_Texture texture = RL_LoadTexture("resources/texel_checker.png");

    // Assign texture to default model material
    modelA.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    modelB.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    modelC.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    // Load shader and set up some uniforms
    RL_Shader shader = RL_LoadShader(RL_TextFormat("resources/shaders/glsl%i/lighting.vs", GLSL_VERSION),
                               RL_TextFormat("resources/shaders/glsl%i/fog.fs", GLSL_VERSION));
    shader.locs[SHADER_LOC_MATRIX_MODEL] = RL_GetShaderLocation(shader, "matModel");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = RL_GetShaderLocation(shader, "viewPos");

    // Ambient light level
    int ambientLoc = RL_GetShaderLocation(shader, "ambient");
    RL_SetShaderValue(shader, ambientLoc, (float[4]){ 0.2f, 0.2f, 0.2f, 1.0f }, SHADER_UNIFORM_VEC4);

    float fogDensity = 0.15f;
    int fogDensityLoc = RL_GetShaderLocation(shader, "fogDensity");
    RL_SetShaderValue(shader, fogDensityLoc, &fogDensity, SHADER_UNIFORM_FLOAT);

    // NOTE: All models share the same shader
    modelA.materials[0].shader = shader;
    modelB.materials[0].shader = shader;
    modelC.materials[0].shader = shader;

    // Using just 1 point lights
    CreateLight(LIGHT_POINT, (RL_Vector3){ 0, 2, 6 }, Vector3Zero(), RL_WHITE, shader);

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_ORBITAL);

        if (RL_IsKeyDown(KEY_UP))
        {
            fogDensity += 0.001f;
            if (fogDensity > 1.0f) fogDensity = 1.0f;
        }

        if (RL_IsKeyDown(KEY_DOWN))
        {
            fogDensity -= 0.001f;
            if (fogDensity < 0.0f) fogDensity = 0.0f;
        }

        RL_SetShaderValue(shader, fogDensityLoc, &fogDensity, SHADER_UNIFORM_FLOAT);

        // Rotate the torus
        modelA.transform = MatrixMultiply(modelA.transform, MatrixRotateX(-0.025f));
        modelA.transform = MatrixMultiply(modelA.transform, MatrixRotateZ(0.012f));

        // Update the light shader with the camera view position
        RL_SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], &camera.position.x, SHADER_UNIFORM_VEC3);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_GRAY);

            RL_BeginMode3D(camera);

                // Draw the three models
                RL_DrawModel(modelA, Vector3Zero(), 1.0f, RL_WHITE);
                RL_DrawModel(modelB, (RL_Vector3){ -2.6f, 0, 0 }, 1.0f, RL_WHITE);
                RL_DrawModel(modelC, (RL_Vector3){ 2.6f, 0, 0 }, 1.0f, RL_WHITE);

                for (int i = -20; i < 20; i += 2) RL_DrawModel(modelA,(RL_Vector3){ (float)i, 0, 2 }, 1.0f, RL_WHITE);

            RL_EndMode3D();

            RL_DrawText(RL_TextFormat("Use KEY_UP/KEY_DOWN to change fog density [%.2f]", fogDensity), 10, 10, 20, RL_RAYWHITE);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadModel(modelA);        // Unload the model A
    RL_UnloadModel(modelB);        // Unload the model B
    RL_UnloadModel(modelC);        // Unload the model C
    RL_UnloadTexture(texture);     // Unload the texture
    RL_UnloadShader(shader);       // Unload shader

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
