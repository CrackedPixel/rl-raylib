/*******************************************************************************************
*
*   raylib [models] example - Heightmap loading and drawing
*
*   Example originally created with raylib 1.8, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - heightmap loading and drawing");

    // Define our custom camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 18.0f, 21.0f, 18.0f };     // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.0f, 0.0f };          // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };              // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                    // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                 // RL_Camera projection type

    RL_Image image = RL_LoadImage("resources/heightmap.png");     // Load heightmap image (RAM)
    RL_Texture2D texture = RL_LoadTextureFromImage(image);        // Convert image to texture (VRAM)

    RL_Mesh mesh = RL_GenMeshHeightmap(image, (RL_Vector3){ 16, 8, 16 }); // Generate heightmap mesh (RAM and VRAM)
    RL_Model model = RL_LoadModelFromMesh(mesh);                  // Load model from generated mesh

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Set map diffuse texture
    RL_Vector3 mapPosition = { -8.0f, 0.0f, -8.0f };           // Define model position

    RL_UnloadImage(image);             // Unload heightmap image from RAM, already uploaded to VRAM

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_ORBITAL);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                RL_DrawModel(model, mapPosition, 1.0f, RL_RED);

                RL_DrawGrid(20, 1.0f);

            RL_EndMode3D();

            RL_DrawTexture(texture, screenWidth - texture.width - 20, 20, RL_WHITE);
            RL_DrawRectangleLines(screenWidth - texture.width - 20, 20, texture.width, texture.height, RL_GREEN);

            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(texture);     // Unload texture
    RL_UnloadModel(model);         // Unload model

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}