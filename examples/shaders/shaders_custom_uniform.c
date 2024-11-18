/*******************************************************************************************
*
*   raylib [shaders] example - Postprocessing with custom uniform variable
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3), to test this example
*         on OpenGL ES 2.0 platforms (Android, Raspberry Pi, HTML5), use #version 100 shaders
*         raylib comes with shaders ready for both versions, check raylib/shaders install folder
*
*   Example originally created with raylib 1.3, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - custom uniform variable");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 8.0f, 8.0f, 8.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 1.5f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    RL_Model model = RL_LoadModel("resources/models/barracks.obj");                   // Load OBJ model
    RL_Texture2D texture = RL_LoadTexture("resources/models/barracks_diffuse.png");   // Load model texture (diffuse map)
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;                     // Set model diffuse texture

    RL_Vector3 position = { 0.0f, 0.0f, 0.0f };                                    // Set model position

    // Load postprocessing shader
    // NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
    RL_Shader shader = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/swirl.fs", GLSL_VERSION));

    // Get variable (uniform) location on the shader to connect with the program
    // NOTE: If uniform variable could not be found in the shader, function returns -1
    int swirlCenterLoc = RL_GetShaderLocation(shader, "center");

    float swirlCenter[2] = { (float)screenWidth/2, (float)screenHeight/2 };

    // Create a RL_RenderTexture2D to be used for render to texture
    RL_RenderTexture2D target = RL_LoadRenderTexture(screenWidth, screenHeight);

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_ORBITAL);
        
        RL_Vector2 mousePosition = RL_GetMousePosition();

        swirlCenter[0] = mousePosition.x;
        swirlCenter[1] = screenHeight - mousePosition.y;

        // Send new value to the shader to be used on drawing
        RL_SetShaderValue(shader, swirlCenterLoc, swirlCenter, SHADER_UNIFORM_VEC2);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginTextureMode(target);       // Enable drawing to texture
            RL_ClearBackground(RL_RAYWHITE);  // Clear texture background

            RL_BeginMode3D(camera);        // Begin 3d mode drawing
                RL_DrawModel(model, position, 0.5f, RL_WHITE);   // Draw 3d model with texture
                RL_DrawGrid(10, 1.0f);     // Draw a grid
            RL_EndMode3D();                // End 3d mode drawing, returns to orthographic 2d mode

            RL_DrawText("TEXT DRAWN IN RENDER TEXTURE", 200, 10, 30, RL_RED);
        RL_EndTextureMode();               // End drawing to texture (now we have a texture available for next passes)

        RL_BeginDrawing();
            RL_ClearBackground(RL_RAYWHITE);  // Clear screen background

            // Enable shader using the custom uniform
            RL_BeginShaderMode(shader);
                // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
                RL_DrawTextureRec(target.texture, (RL_Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (RL_Vector2){ 0, 0 }, RL_WHITE);
            RL_EndShaderMode();

            // Draw some 2d text over drawn texture
            RL_DrawText("(c) Barracks 3D model by Alberto Cano", screenWidth - 220, screenHeight - 20, 10, RL_GRAY);
            RL_DrawFPS(10, 10);
        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadShader(shader);               // Unload shader
    RL_UnloadTexture(texture);             // Unload texture
    RL_UnloadModel(model);                 // Unload model
    RL_UnloadRenderTexture(target);        // Unload render texture

    RL_CloseWindow();                      // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}