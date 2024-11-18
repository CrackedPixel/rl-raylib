/*******************************************************************************************
*
*   raylib [core] example - Initialize 3d camera mode
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");

    // Define the camera to look into our 3d world
    RL_Camera3D camera = { 0 };
    camera.position = (RL_Vector3){ 0.0f, 10.0f, 10.0f };  // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.0f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera mode type

    RL_Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

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

                RL_DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RL_RED);
                RL_DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, RL_MAROON);

                RL_DrawGrid(10, 1.0f);

            RL_EndMode3D();

            RL_DrawText("Welcome to the third dimension!", 10, 40, 20, RL_DARKGRAY);

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