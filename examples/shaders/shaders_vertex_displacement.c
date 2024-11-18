/*******************************************************************************************
*
*   raylib [shaders] example - Vertex displacement
*
*   Example originally created with raylib 5.0, last time updated with raylib 4.5
*
*   Example contributed by <Alex ZH> (@ZzzhHe) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023 <Alex ZH> (@ZzzhHe)
*
********************************************************************************************/

#include "raylib.h"

#include "rlgl.h"

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

    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - vertex displacement");

    // set up camera
    RL_Camera camera = {0};
    camera.position = (RL_Vector3) {20.0f, 5.0f, -20.0f};
    camera.target = (RL_Vector3) {0.0f, 0.0f, 0.0f};
    camera.up = (RL_Vector3) {0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Load vertex and fragment shaders
    RL_Shader shader = RL_LoadShader(
        RL_TextFormat("resources/shaders/glsl%i/vertex_displacement.vs", GLSL_VERSION),
        RL_TextFormat("resources/shaders/glsl%i/vertex_displacement.fs", GLSL_VERSION));
    
    // Load perlin noise texture
    RL_Image perlinNoiseImage = RL_GenImagePerlinNoise(512, 512, 0, 0, 1.0f);
    RL_Texture perlinNoiseMap = RL_LoadTextureFromImage(perlinNoiseImage);
    RL_UnloadImage(perlinNoiseImage);

    // Set shader uniform location
    int perlinNoiseMapLoc = RL_GetShaderLocation(shader, "perlinNoiseMap");
    rlEnableShader(shader.id);
    rlActiveTextureSlot(1);
    rlEnableTexture(perlinNoiseMap.id);
    rlSetUniformSampler(perlinNoiseMapLoc, 1);
    
    // Create a plane mesh and model
    RL_Mesh planeMesh = RL_GenMeshPlane(50, 50, 50, 50);
    RL_Model planeModel = RL_LoadModelFromMesh(planeMesh);
    // Set plane model material
    planeModel.materials[0].shader = shader;

    float time = 0.0f;

    RL_SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_FREE); // Update camera

        time += RL_GetFrameTime(); // Update time variable
        RL_SetShaderValue(shader, RL_GetShaderLocation(shader, "time"), &time, SHADER_UNIFORM_FLOAT); // Send time value to shader

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                RL_BeginShaderMode(shader);
                    // Draw plane model
                    RL_DrawModel(planeModel, (RL_Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, (RL_Color) {255, 255, 255, 255});
                RL_EndShaderMode();

            RL_EndMode3D();

            RL_DrawText("Vertex displacement", 10, 10, 20, RL_DARKGRAY);
            RL_DrawFPS(10, 40);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadShader(shader);
    RL_UnloadModel(planeModel);
    RL_UnloadTexture(perlinNoiseMap);

    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
