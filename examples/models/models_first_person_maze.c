/*******************************************************************************************
*
*   raylib [models] example - first person maze
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include <stdlib.h>           // Required for: free()

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - first person maze");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 0.2f, 0.4f, 0.2f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.185f, 0.4f, 0.0f };    // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    RL_Image imMap = RL_LoadImage("resources/cubicmap.png");      // Load cubicmap image (RAM)
    RL_Texture2D cubicmap = RL_LoadTextureFromImage(imMap);       // Convert image to texture to display (VRAM)
    RL_Mesh mesh = RL_GenMeshCubicmap(imMap, (RL_Vector3){ 1.0f, 1.0f, 1.0f });
    RL_Model model = RL_LoadModelFromMesh(mesh);

    // NOTE: By default each cube is mapped to one part of texture atlas
    RL_Texture2D texture = RL_LoadTexture("resources/cubicmap_atlas.png");    // Load map texture
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;    // Set map diffuse texture

    // Get map image data to be used for collision detection
    RL_Color *mapPixels = RL_LoadImageColors(imMap);
    RL_UnloadImage(imMap);             // Unload image from RAM

    RL_Vector3 mapPosition = { -16.0f, 0.0f, -8.0f };  // Set model position

    RL_DisableCursor();                // Limit cursor to relative movement inside the window

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_Vector3 oldCamPos = camera.position;    // Store old camera position

        RL_UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        // Check player collision (we simplify to 2D collision detection)
        RL_Vector2 playerPos = { camera.position.x, camera.position.z };
        float playerRadius = 0.1f;  // Collision radius (player is modelled as a cilinder for collision)

        int playerCellX = (int)(playerPos.x - mapPosition.x + 0.5f);
        int playerCellY = (int)(playerPos.y - mapPosition.z + 0.5f);

        // Out-of-limits security check
        if (playerCellX < 0) playerCellX = 0;
        else if (playerCellX >= cubicmap.width) playerCellX = cubicmap.width - 1;

        if (playerCellY < 0) playerCellY = 0;
        else if (playerCellY >= cubicmap.height) playerCellY = cubicmap.height - 1;

        // Check map collisions using image data and player position
        // TODO: Improvement: Just check player surrounding cells for collision
        for (int y = 0; y < cubicmap.height; y++)
        {
            for (int x = 0; x < cubicmap.width; x++)
            {
                if ((mapPixels[y*cubicmap.width + x].r == 255) &&       // Collision: white pixel, only check R channel
                    (RL_CheckCollisionCircleRec(playerPos, playerRadius,
                    (RL_Rectangle){ mapPosition.x - 0.5f + x*1.0f, mapPosition.z - 0.5f + y*1.0f, 1.0f, 1.0f })))
                {
                    // Collision detected, reset camera position
                    camera.position = oldCamPos;
                }
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);
                RL_DrawModel(model, mapPosition, 1.0f, RL_WHITE);                     // Draw maze map
            RL_EndMode3D();

            RL_DrawTextureEx(cubicmap, (RL_Vector2){ RL_GetScreenWidth() - cubicmap.width*4.0f - 20, 20.0f }, 0.0f, 4.0f, RL_WHITE);
            RL_DrawRectangleLines(RL_GetScreenWidth() - cubicmap.width*4 - 20, 20, cubicmap.width*4, cubicmap.height*4, RL_GREEN);

            // Draw player position radar
            RL_DrawRectangle(RL_GetScreenWidth() - cubicmap.width*4 - 20 + playerCellX*4, 20 + playerCellY*4, 4, 4, RL_RED);

            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadImageColors(mapPixels);   // Unload color array

    RL_UnloadTexture(cubicmap);        // Unload cubicmap texture
    RL_UnloadTexture(texture);         // Unload map texture
    RL_UnloadModel(model);             // Unload map model

    RL_CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
