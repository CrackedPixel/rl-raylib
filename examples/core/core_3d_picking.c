/*******************************************************************************************
*
*   raylib [core] example - Picking in 3d mode
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

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d picking");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 10.0f, 10.0f, 10.0f }; // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.0f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    RL_Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    RL_Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };

    RL_Ray ray = { 0 };                    // Picking line ray
    RL_RayCollision collision = { 0 };     // RL_Ray collision hit info

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsCursorHidden()) RL_UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        // Toggle camera controls
        if (RL_IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            if (RL_IsCursorHidden()) RL_EnableCursor();
            else RL_DisableCursor();
        }

        if (RL_IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (!collision.hit)
            {
                ray = RL_GetScreenToWorldRay(RL_GetMousePosition(), camera);

                // Check collision between ray and box
                collision = RL_GetRayCollisionBox(ray,
                            (RL_BoundingBox){(RL_Vector3){ cubePosition.x - cubeSize.x/2, cubePosition.y - cubeSize.y/2, cubePosition.z - cubeSize.z/2 },
                                          (RL_Vector3){ cubePosition.x + cubeSize.x/2, cubePosition.y + cubeSize.y/2, cubePosition.z + cubeSize.z/2 }});
            }
            else collision.hit = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                if (collision.hit)
                {
                    RL_DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, RL_RED);
                    RL_DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, RL_MAROON);

                    RL_DrawCubeWires(cubePosition, cubeSize.x + 0.2f, cubeSize.y + 0.2f, cubeSize.z + 0.2f, RL_GREEN);
                }
                else
                {
                    RL_DrawCube(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, RL_GRAY);
                    RL_DrawCubeWires(cubePosition, cubeSize.x, cubeSize.y, cubeSize.z, RL_DARKGRAY);
                }

                RL_DrawRay(ray, RL_MAROON);
                RL_DrawGrid(10, 1.0f);

            RL_EndMode3D();

            RL_DrawText("Try clicking on the box with your mouse!", 240, 10, 20, RL_DARKGRAY);

            if (collision.hit) RL_DrawText("BOX SELECTED", (screenWidth - RL_MeasureText("BOX SELECTED", 30)) / 2, (int)(screenHeight * 0.1f), 30, RL_GREEN);

            RL_DrawText("Right click mouse to toggle camera controls", 10, 430, 10, RL_GRAY);

            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
