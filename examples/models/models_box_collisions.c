/*******************************************************************************************
*
*   raylib [models] example - Detect basic 3d collisions (box vs sphere vs box)
*
*   Example originally created with raylib 1.3, last time updated with raylib 3.5
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - box collisions");

    // Define the camera to look into our 3d world
    RL_Camera camera = { { 0.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

    RL_Vector3 playerPosition = { 0.0f, 1.0f, 2.0f };
    RL_Vector3 playerSize = { 1.0f, 2.0f, 1.0f };
    RL_Color playerColor = RL_GREEN;

    RL_Vector3 enemyBoxPos = { -4.0f, 1.0f, 0.0f };
    RL_Vector3 enemyBoxSize = { 2.0f, 2.0f, 2.0f };

    RL_Vector3 enemySpherePos = { 4.0f, 0.0f, 0.0f };
    float enemySphereSize = 1.5f;

    bool collision = false;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        // Move player
        if (RL_IsKeyDown(KEY_RIGHT)) playerPosition.x += 0.2f;
        else if (RL_IsKeyDown(KEY_LEFT)) playerPosition.x -= 0.2f;
        else if (RL_IsKeyDown(KEY_DOWN)) playerPosition.z += 0.2f;
        else if (RL_IsKeyDown(KEY_UP)) playerPosition.z -= 0.2f;

        collision = false;

        // Check collisions player vs enemy-box
        if (RL_CheckCollisionBoxes(
            (RL_BoundingBox){(RL_Vector3){ playerPosition.x - playerSize.x/2,
                                     playerPosition.y - playerSize.y/2,
                                     playerPosition.z - playerSize.z/2 },
                          (RL_Vector3){ playerPosition.x + playerSize.x/2,
                                     playerPosition.y + playerSize.y/2,
                                     playerPosition.z + playerSize.z/2 }},
            (RL_BoundingBox){(RL_Vector3){ enemyBoxPos.x - enemyBoxSize.x/2,
                                     enemyBoxPos.y - enemyBoxSize.y/2,
                                     enemyBoxPos.z - enemyBoxSize.z/2 },
                          (RL_Vector3){ enemyBoxPos.x + enemyBoxSize.x/2,
                                     enemyBoxPos.y + enemyBoxSize.y/2,
                                     enemyBoxPos.z + enemyBoxSize.z/2 }})) collision = true;

        // Check collisions player vs enemy-sphere
        if (RL_CheckCollisionBoxSphere(
            (RL_BoundingBox){(RL_Vector3){ playerPosition.x - playerSize.x/2,
                                     playerPosition.y - playerSize.y/2,
                                     playerPosition.z - playerSize.z/2 },
                          (RL_Vector3){ playerPosition.x + playerSize.x/2,
                                     playerPosition.y + playerSize.y/2,
                                     playerPosition.z + playerSize.z/2 }},
            enemySpherePos, enemySphereSize)) collision = true;

        if (collision) playerColor = RL_RED;
        else playerColor = RL_GREEN;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                // Draw enemy-box
                RL_DrawCube(enemyBoxPos, enemyBoxSize.x, enemyBoxSize.y, enemyBoxSize.z, RL_GRAY);
                RL_DrawCubeWires(enemyBoxPos, enemyBoxSize.x, enemyBoxSize.y, enemyBoxSize.z, RL_DARKGRAY);

                // Draw enemy-sphere
                RL_DrawSphere(enemySpherePos, enemySphereSize, RL_GRAY);
                RL_DrawSphereWires(enemySpherePos, enemySphereSize, 16, 16, RL_DARKGRAY);

                // Draw player
                RL_DrawCubeV(playerPosition, playerSize, playerColor);

                RL_DrawGrid(10, 1.0f);        // Draw a grid

            RL_EndMode3D();

            RL_DrawText("Move player with arrow keys to collide", 220, 40, 20, RL_GRAY);

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