/*******************************************************************************************
*
*   raylib [core] example - Scissor test
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.0
*
*   Example contributed by Chris Dill (@MysteriousSpace) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Chris Dill (@MysteriousSpace)
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - scissor test");

    RL_Rectangle scissorArea = { 0, 0, 300, 300 };
    bool scissorMode = true;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsKeyPressed(KEY_S)) scissorMode = !scissorMode;

        // Centre the scissor area around the mouse position
        scissorArea.x = RL_GetMouseX() - scissorArea.width/2;
        scissorArea.y = RL_GetMouseY() - scissorArea.height/2;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            if (scissorMode) RL_BeginScissorMode((int)scissorArea.x, (int)scissorArea.y, (int)scissorArea.width, (int)scissorArea.height);

            // Draw full screen rectangle and some text
            // NOTE: Only part defined by scissor area will be rendered
            RL_DrawRectangle(0, 0, RL_GetScreenWidth(), RL_GetScreenHeight(), RL_RED);
            RL_DrawText("Move the mouse around to reveal this text!", 190, 200, 20, RL_LIGHTGRAY);

            if (scissorMode) RL_EndScissorMode();

            RL_DrawRectangleLinesEx(scissorArea, 1, RL_BLACK);
            RL_DrawText("Press S to toggle scissor test", 10, 10, 20, RL_BLACK);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
