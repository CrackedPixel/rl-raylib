/*******************************************************************************************
*
*   raylib [shaders] example - RL_Mesh instancing
*
*   Example originally created with raylib 3.7, last time updated with raylib 4.2
*
*   Example contributed by @seanpringle and reviewed by Max (@moliad) and Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2020-2024 @seanpringle, Max (@moliad) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/


#include "raylib.h"
#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#include <stdlib.h>         // Required for: calloc(), free()

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

#define MAX_INSTANCES  10000

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - mesh instancing");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ -125.0f, 125.0f, -125.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.0f, 0.0f };              // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };                  // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                        // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                     // RL_Camera projection type

    // Define mesh to be instanced
    RL_Mesh cube = RL_GenMeshCube(1.0f, 1.0f, 1.0f);

    // Define transforms to be uploaded to GPU for instances
    RL_Matrix *transforms = (RL_Matrix *)RL_CALLOC(MAX_INSTANCES, sizeof(RL_Matrix));   // Pre-multiplied transformations passed to rlgl

    // Translate and rotate cubes randomly
    for (int i = 0; i < MAX_INSTANCES; i++)
    {
        RL_Matrix translation = MatrixTranslate((float)RL_GetRandomValue(-50, 50), (float)RL_GetRandomValue(-50, 50), (float)RL_GetRandomValue(-50, 50));
        RL_Vector3 axis = Vector3Normalize((RL_Vector3){ (float)RL_GetRandomValue(0, 360), (float)RL_GetRandomValue(0, 360), (float)RL_GetRandomValue(0, 360) });
        float angle = (float)RL_GetRandomValue(0, 10)*DEG2RAD;
        RL_Matrix rotation = MatrixRotate(axis, angle);
        
        transforms[i] = MatrixMultiply(rotation, translation);
    }

    // Load lighting shader
    RL_Shader shader = RL_LoadShader(RL_TextFormat("resources/shaders/glsl%i/lighting_instancing.vs", GLSL_VERSION),
                               RL_TextFormat("resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));
    // Get shader locations
    shader.locs[SHADER_LOC_MATRIX_MVP] = RL_GetShaderLocation(shader, "mvp");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = RL_GetShaderLocation(shader, "viewPos");
    shader.locs[SHADER_LOC_MATRIX_MODEL] = RL_GetShaderLocationAttrib(shader, "instanceTransform");

    // Set shader value: ambient light level
    int ambientLoc = RL_GetShaderLocation(shader, "ambient");
    RL_SetShaderValue(shader, ambientLoc, (float[4]){ 0.2f, 0.2f, 0.2f, 1.0f }, SHADER_UNIFORM_VEC4);

    // Create one light
    CreateLight(LIGHT_DIRECTIONAL, (RL_Vector3){ 50.0f, 50.0f, 0.0f }, Vector3Zero(), RL_WHITE, shader);

    // NOTE: We are assigning the intancing shader to material.shader
    // to be used on mesh drawing with RL_DrawMeshInstanced()
    RL_Material matInstances = RL_LoadMaterialDefault();
    matInstances.shader = shader;
    matInstances.maps[MATERIAL_MAP_DIFFUSE].color = RL_RED;

    // Load default material (using raylib intenral default shader) for non-instanced mesh drawing
    // WARNING: Default shader enables vertex color attribute BUT RL_GenMeshCube() does not generate vertex colors, so,
    // when drawing the color attribute is disabled and a default color value is provided as input for thevertex attribute
    RL_Material matDefault = RL_LoadMaterialDefault();
    matDefault.maps[MATERIAL_MAP_DIFFUSE].color = RL_BLUE;

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_ORBITAL);

        // Update the light shader with the camera view position
        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        RL_SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                // Draw cube mesh with default material (RL_BLUE)
                RL_DrawMesh(cube, matDefault, MatrixTranslate(-10.0f, 0.0f, 0.0f));

                // Draw meshes instanced using material containing instancing shader (RL_RED + lighting),
                // transforms[] for the instances should be provided, they are dynamically
                // updated in GPU every frame, so we can animate the different mesh instances
                RL_DrawMeshInstanced(cube, matInstances, transforms, MAX_INSTANCES);

                // Draw cube mesh with default material (RL_BLUE)
                RL_DrawMesh(cube, matDefault, MatrixTranslate(10.0f, 0.0f, 0.0f));

            RL_EndMode3D();

            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_FREE(transforms);    // Free transforms

    RL_CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
