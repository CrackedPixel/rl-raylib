/*******************************************************************************************
*
*   raylib [core] example - World to screen
*
*   Example originally created with raylib 1.3, last time updated with raylib 1.4
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - core world screen");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 10.0f, 10.0f, 10.0f }; // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.0f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    RL_Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    RL_Vector2 cubeScreenPosition = { 0.0f, 0.0f };

    RL_DisableCursor();                    // Limit cursor to relative movement inside the window

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        // Calculate cube screen space position (with a little offset to be in top)
        cubeScreenPosition = RL_GetWorldToScreen((RL_Vector3){cubePosition.x, cubePosition.y + 2.5f, cubePosition.z}, camera);
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

            RL_DrawText("Enemy: 100 / 100", (int)cubeScreenPosition.x - RL_MeasureText("Enemy: 100/100", 20)/2, (int)cubeScreenPosition.y, 20, RL_BLACK);
            
            RL_DrawText(RL_TextFormat("Cube position in screen space coordinates: [%i, %i]", (int)cubeScreenPosition.x, (int)cubeScreenPosition.y), 10, 10, 20, RL_LIME);
            RL_DrawText("Text 2d should be always on top of the cube", 10, 40, 20, RL_GRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}