/*******************************************************************************************
*
*   raylib [models] example - Draw some basic geometric shapes (cube, sphere, cylinder...)
*
*   Example originally created with raylib 1.0, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2024 Ramon Santamaria (@raysan5)
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - geometric shapes");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 0.0f, 10.0f, 10.0f };
    camera.target = (RL_Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                RL_DrawCube((RL_Vector3){-4.0f, 0.0f, 2.0f}, 2.0f, 5.0f, 2.0f, RL_RED);
                RL_DrawCubeWires((RL_Vector3){-4.0f, 0.0f, 2.0f}, 2.0f, 5.0f, 2.0f, RL_GOLD);
                RL_DrawCubeWires((RL_Vector3){-4.0f, 0.0f, -2.0f}, 3.0f, 6.0f, 2.0f, RL_MAROON);

                RL_DrawSphere((RL_Vector3){-1.0f, 0.0f, -2.0f}, 1.0f, RL_GREEN);
                RL_DrawSphereWires((RL_Vector3){1.0f, 0.0f, 2.0f}, 2.0f, 16, 16, RL_LIME);

                RL_DrawCylinder((RL_Vector3){4.0f, 0.0f, -2.0f}, 1.0f, 2.0f, 3.0f, 4, RL_SKYBLUE);
                RL_DrawCylinderWires((RL_Vector3){4.0f, 0.0f, -2.0f}, 1.0f, 2.0f, 3.0f, 4, RL_DARKBLUE);
                RL_DrawCylinderWires((RL_Vector3){4.5f, -1.0f, 2.0f}, 1.0f, 1.0f, 2.0f, 6, RL_BROWN);

                RL_DrawCylinder((RL_Vector3){1.0f, 0.0f, -4.0f}, 0.0f, 1.5f, 3.0f, 8, RL_GOLD);
                RL_DrawCylinderWires((RL_Vector3){1.0f, 0.0f, -4.0f}, 0.0f, 1.5f, 3.0f, 8, RL_PINK);

                RL_DrawCapsule     ((RL_Vector3){-3.0f, 1.5f, -4.0f}, (RL_Vector3){-4.0f, -1.0f, -4.0f}, 1.2f, 8, 8, RL_VIOLET);
                RL_DrawCapsuleWires((RL_Vector3){-3.0f, 1.5f, -4.0f}, (RL_Vector3){-4.0f, -1.0f, -4.0f}, 1.2f, 8, 8, RL_PURPLE);

                RL_DrawGrid(10, 1.0f);        // Draw a grid

            RL_EndMode3D();

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