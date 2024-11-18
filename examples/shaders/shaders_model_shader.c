/*******************************************************************************************
*
*   raylib [shaders] example - RL_Model shader
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3), to test this example
*         on OpenGL ES 2.0 platforms (Android, Raspberry Pi, HTML5), use #version 100 shaders
*         raylib comes with shaders ready for both versions, check raylib/shaders install folder
*
*   Example originally created with raylib 1.3, last time updated with raylib 3.7
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2024 Ramon Santamaria (@raysan5)
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

    RL_SetConfigFlags(FLAG_MSAA_4X_HINT);      // Enable Multi Sampling Anti Aliasing 4x (if available)

    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - model shader");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 4.0f, 4.0f, 4.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 1.0f, -1.0f };     // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    RL_Model model = RL_LoadModel("resources/models/watermill.obj");                   // Load OBJ model
    RL_Texture2D texture = RL_LoadTexture("resources/models/watermill_diffuse.png");   // Load model texture

    // Load shader for model
    // NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
    RL_Shader shader = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/grayscale.fs", GLSL_VERSION));

    model.materials[0].shader = shader;                     // Set shader effect to 3d model
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Bind texture to model

    RL_Vector3 position = { 0.0f, 0.0f, 0.0f };    // Set model position

    RL_DisableCursor();                    // Limit cursor to relative movement inside the window
    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_FREE);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                RL_DrawModel(model, position, 0.2f, RL_WHITE);   // Draw 3d model with texture

                RL_DrawGrid(10, 1.0f);     // Draw a grid

            RL_EndMode3D();

            RL_DrawText("(c) Watermill 3D model by Alberto Cano", screenWidth - 210, screenHeight - 20, 10, RL_GRAY);

            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadShader(shader);       // Unload shader
    RL_UnloadTexture(texture);     // Unload texture
    RL_UnloadModel(model);         // Unload model

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}