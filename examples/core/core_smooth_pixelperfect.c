/*******************************************************************************************
*
*   raylib [core] example - Smooth Pixel-perfect camera
*
*   Example originally created with raylib 3.7, last time updated with raylib 4.0
*   
*   Example contributed by Giancamillo Alessandroni (@NotManyIdeasDev) and
*   reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2024 Giancamillo Alessandroni (@NotManyIdeasDev) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include <math.h>       // Required for: sinf(), cosf()

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    const int virtualScreenWidth = 160;
    const int virtualScreenHeight = 90;

    const float virtualRatio = (float)screenWidth/(float)virtualScreenWidth;

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - smooth pixel-perfect camera");

    RL_Camera2D worldSpaceCamera = { 0 };  // Game world camera
    worldSpaceCamera.zoom = 1.0f;

    RL_Camera2D screenSpaceCamera = { 0 }; // Smoothing camera
    screenSpaceCamera.zoom = 1.0f;

    RL_RenderTexture2D target = RL_LoadRenderTexture(virtualScreenWidth, virtualScreenHeight); // This is where we'll draw all our objects.

    RL_Rectangle rec01 = { 70.0f, 35.0f, 20.0f, 20.0f };
    RL_Rectangle rec02 = { 90.0f, 55.0f, 30.0f, 10.0f };
    RL_Rectangle rec03 = { 80.0f, 65.0f, 15.0f, 25.0f };

    // The target's height is flipped (in the source RL_Rectangle), due to OpenGL reasons
    RL_Rectangle sourceRec = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height };
    RL_Rectangle destRec = { -virtualRatio, -virtualRatio, screenWidth + (virtualRatio*2), screenHeight + (virtualRatio*2) };

    RL_Vector2 origin = { 0.0f, 0.0f };

    float rotation = 0.0f;

    float cameraX = 0.0f;
    float cameraY = 0.0f;

    RL_SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        rotation += 60.0f*RL_GetFrameTime();   // Rotate the rectangles, 60 degrees per second

        // Make the camera move to demonstrate the effect
        cameraX = (sinf((float)RL_GetTime())*50.0f) - 10.0f;
        cameraY = cosf((float)RL_GetTime())*30.0f;

        // Set the camera's target to the values computed above
        screenSpaceCamera.target = (RL_Vector2){ cameraX, cameraY };

        // Round worldSpace coordinates, keep decimals into screenSpace coordinates
        worldSpaceCamera.target.x = truncf(screenSpaceCamera.target.x);
        screenSpaceCamera.target.x -= worldSpaceCamera.target.x;
        screenSpaceCamera.target.x *= virtualRatio;

        worldSpaceCamera.target.y = truncf(screenSpaceCamera.target.y);
        screenSpaceCamera.target.y -= worldSpaceCamera.target.y;
        screenSpaceCamera.target.y *= virtualRatio;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginTextureMode(target);
            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode2D(worldSpaceCamera);
                RL_DrawRectanglePro(rec01, origin, rotation, RL_BLACK);
                RL_DrawRectanglePro(rec02, origin, -rotation, RL_RED);
                RL_DrawRectanglePro(rec03, origin, rotation + 45.0f, RL_BLUE);
            RL_EndMode2D();
        RL_EndTextureMode();

        RL_BeginDrawing();
            RL_ClearBackground(RL_RED);

            RL_BeginMode2D(screenSpaceCamera);
                RL_DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, RL_WHITE);
            RL_EndMode2D();

            RL_DrawText(RL_TextFormat("Screen resolution: %ix%i", screenWidth, screenHeight), 10, 10, 20, RL_DARKBLUE);
            RL_DrawText(RL_TextFormat("World resolution: %ix%i", virtualScreenWidth, virtualScreenHeight), 10, 40, 20, RL_DARKGREEN);
            RL_DrawFPS(RL_GetScreenWidth() - 95, 10);
        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadRenderTexture(target);    // Unload render texture

    RL_CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}