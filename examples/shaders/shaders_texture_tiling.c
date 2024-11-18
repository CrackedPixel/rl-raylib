/*******************************************************************************************
*
*   raylib [shaders] example - texture tiling
*
*   Example demonstrates how to tile a texture on a 3D model using raylib.
*
*   Example contributed by Luis Almeida (@luis605) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023 Luis Almeida (@luis605)
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - texture tiling");

    // Define the camera to look into our 3d world
    RL_Camera3D camera = { 0 };
    camera.position = (RL_Vector3){ 4.0f, 4.0f, 4.0f }; // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.5f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    // Load a cube model
    RL_Mesh cube = RL_GenMeshCube(1.0f, 1.0f, 1.0f);
    RL_Model model = RL_LoadModelFromMesh(cube);
    
    // Load a texture and assign to cube model
    RL_Texture2D texture = RL_LoadTexture("resources/cubicmap_atlas.png");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    // Set the texture tiling using a shader
    float tiling[2] = { 3.0f, 3.0f };
    RL_Shader shader = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/tiling.fs", GLSL_VERSION));
    RL_SetShaderValue(shader, RL_GetShaderLocation(shader, "tiling"), tiling, SHADER_UNIFORM_VEC2);
    model.materials[0].shader = shader;

    RL_DisableCursor();                    // Limit cursor to relative movement inside the window

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_FREE);

        if (RL_IsKeyPressed('Z')) camera.target = (RL_Vector3){ 0.0f, 0.5f, 0.0f };
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();
        
            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);
            
                RL_BeginShaderMode(shader);
                    RL_DrawModel(model, (RL_Vector3){ 0.0f, 0.0f, 0.0f }, 2.0f, RL_WHITE);
                RL_EndShaderMode();

                RL_DrawGrid(10, 1.0f);
                
            RL_EndMode3D();

            RL_DrawText("Use mouse to rotate the camera", 10, 10, 20, RL_DARKGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadModel(model);         // Unload model
    RL_UnloadShader(shader);       // Unload shader
    RL_UnloadTexture(texture);     // Unload texture

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    return 0;
}
