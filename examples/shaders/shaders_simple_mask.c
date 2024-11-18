/*******************************************************************************************
*
*   raylib [shaders] example - Simple shader mask
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
********************************************************************************************
*
*   After a model is loaded it has a default material, this material can be
*   modified in place rather than creating one from scratch...
*   While all of the maps have particular names, they can be used for any purpose
*   except for three maps that are applied as cubic maps (see below)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

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

    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - simple shader mask");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 0.0f, 1.0f, 2.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.0f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    // Define our three models to show the shader on
    RL_Mesh torus = RL_GenMeshTorus(0.3f, 1, 16, 32);
    RL_Model model1 = RL_LoadModelFromMesh(torus);

    RL_Mesh cube = RL_GenMeshCube(0.8f,0.8f,0.8f);
    RL_Model model2 = RL_LoadModelFromMesh(cube);

    // Generate model to be shaded just to see the gaps in the other two
    RL_Mesh sphere = RL_GenMeshSphere(1, 16, 16);
    RL_Model model3 = RL_LoadModelFromMesh(sphere);

    // Load the shader
    RL_Shader shader = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/mask.fs", GLSL_VERSION));

    // Load and apply the diffuse texture (colour map)
    RL_Texture texDiffuse = RL_LoadTexture("resources/plasma.png");
    model1.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texDiffuse;
    model2.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texDiffuse;

    // Using MATERIAL_MAP_EMISSION as a spare slot to use for 2nd texture
    // NOTE: Don't use MATERIAL_MAP_IRRADIANCE, MATERIAL_MAP_PREFILTER or  MATERIAL_MAP_CUBEMAP as they are bound as cube maps
    RL_Texture texMask = RL_LoadTexture("resources/mask.png");
    model1.materials[0].maps[MATERIAL_MAP_EMISSION].texture = texMask;
    model2.materials[0].maps[MATERIAL_MAP_EMISSION].texture = texMask;
    shader.locs[SHADER_LOC_MAP_EMISSION] = RL_GetShaderLocation(shader, "mask");

    // Frame is incremented each frame to animate the shader
    int shaderFrame = RL_GetShaderLocation(shader, "frame");

    // Apply the shader to the two models
    model1.materials[0].shader = shader;
    model2.materials[0].shader = shader;

    int framesCounter = 0;
    RL_Vector3 rotation = { 0 };           // RL_Model rotation angles

    RL_DisableCursor();                    // Limit cursor to relative movement inside the window
    RL_SetTargetFPS(60);                   // Set  to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        
        framesCounter++;
        rotation.x += 0.01f;
        rotation.y += 0.005f;
        rotation.z -= 0.0025f;

        // Send frames counter to shader for animation
        RL_SetShaderValue(shader, shaderFrame, &framesCounter, SHADER_UNIFORM_INT);

        // Rotate one of the models
        model1.transform = MatrixRotateXYZ(rotation);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_DARKBLUE);

            RL_BeginMode3D(camera);

                RL_DrawModel(model1, (RL_Vector3){ 0.5f, 0.0f, 0.0f }, 1, RL_WHITE);
                RL_DrawModelEx(model2, (RL_Vector3){ -0.5f, 0.0f, 0.0f }, (RL_Vector3){ 1.0f, 1.0f, 0.0f }, 50, (RL_Vector3){ 1.0f, 1.0f, 1.0f }, RL_WHITE);
                RL_DrawModel(model3,(RL_Vector3){ 0.0f, 0.0f, -1.5f }, 1, RL_WHITE);
                RL_DrawGrid(10, 1.0f);        // Draw a grid

            RL_EndMode3D();

            RL_DrawRectangle(16, 698, RL_MeasureText(RL_TextFormat("Frame: %i", framesCounter), 20) + 8, 42, RL_BLUE);
            RL_DrawText(RL_TextFormat("Frame: %i", framesCounter), 20, 700, 20, RL_WHITE);

            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadModel(model1);
    RL_UnloadModel(model2);
    RL_UnloadModel(model3);

    RL_UnloadTexture(texDiffuse);  // Unload default diffuse texture
    RL_UnloadTexture(texMask);     // Unload texture mask

    RL_UnloadShader(shader);       // Unload shader

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
