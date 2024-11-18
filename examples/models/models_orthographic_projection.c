/*******************************************************************************************
*
*   raylib [models] example - Show the difference between perspective and orthographic projection
*
*   Example originally created with raylib 2.0, last time updated with raylib 3.7
*
*   Example contributed by Max Danielsson (@autious) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2024 Max Danielsson (@autious) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define FOVY_PERSPECTIVE    45.0f
#define WIDTH_ORTHOGRAPHIC  10.0f

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
    RL_Camera camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, FOVY_PERSPECTIVE, CAMERA_PERSPECTIVE };

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsKeyPressed(KEY_SPACE))
        {
            if (camera.projection == CAMERA_PERSPECTIVE)
            {
                camera.fovy = WIDTH_ORTHOGRAPHIC;
                camera.projection = CAMERA_ORTHOGRAPHIC;
            }
            else
            {
                camera.fovy = FOVY_PERSPECTIVE;
                camera.projection = CAMERA_PERSPECTIVE;
            }
        }
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

                RL_DrawGrid(10, 1.0f);        // Draw a grid

            RL_EndMode3D();

            RL_DrawText("Press Spacebar to switch camera type", 10, RL_GetScreenHeight() - 30, 20, RL_DARKGRAY);

            if (camera.projection == CAMERA_ORTHOGRAPHIC) RL_DrawText("ORTHOGRAPHIC", 10, 40, 20, RL_BLACK);
            else if (camera.projection == CAMERA_PERSPECTIVE) RL_DrawText("PERSPECTIVE", 10, 40, 20, RL_BLACK);

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
