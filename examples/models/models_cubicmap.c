/*******************************************************************************************
*
*   raylib [models] example - Cubicmap loading and drawing
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - cubesmap loading and drawing");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 16.0f, 14.0f, 16.0f };     // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.0f, 0.0f };          // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };              // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                    // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                 // RL_Camera projection type

    RL_Image image = RL_LoadImage("resources/cubicmap.png");      // Load cubicmap image (RAM)
    RL_Texture2D cubicmap = RL_LoadTextureFromImage(image);       // Convert image to texture to display (VRAM)

    RL_Mesh mesh = RL_GenMeshCubicmap(image, (RL_Vector3){ 1.0f, 1.0f, 1.0f });
    RL_Model model = RL_LoadModelFromMesh(mesh);

    // NOTE: By default each cube is mapped to one part of texture atlas
    RL_Texture2D texture = RL_LoadTexture("resources/cubicmap_atlas.png");    // Load map texture
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;    // Set map diffuse texture

    RL_Vector3 mapPosition = { -16.0f, 0.0f, -8.0f };          // Set model position

    RL_UnloadImage(image);     // Unload cubesmap image from RAM, already uploaded to VRAM

    bool pause = false;     // Pause camera orbital rotation (and zoom)

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsKeyPressed(KEY_P)) pause = !pause;

        if (!pause) RL_UpdateCamera(&camera, CAMERA_ORBITAL);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                RL_DrawModel(model, mapPosition, 1.0f, RL_WHITE);

            RL_EndMode3D();

            RL_DrawTextureEx(cubicmap, (RL_Vector2){ screenWidth - cubicmap.width*4.0f - 20, 20.0f }, 0.0f, 4.0f, RL_WHITE);
            RL_DrawRectangleLines(screenWidth - cubicmap.width*4 - 20, 20, cubicmap.width*4, cubicmap.height*4, RL_GREEN);

            RL_DrawText("cubicmap image used to", 658, 90, 10, RL_GRAY);
            RL_DrawText("generate map 3d model", 658, 104, 10, RL_GRAY);

            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(cubicmap);    // Unload cubicmap texture
    RL_UnloadTexture(texture);     // Unload map texture
    RL_UnloadModel(model);         // Unload map model

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
