/*******************************************************************************************
*
*   raylib [shapes] example - rectangle scaling by mouse
*
*   Example originally created with raylib 2.5, last time updated with raylib 2.5
*
*   Example contributed by Vlad Adrian (@demizdor) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2024 Vlad Adrian (@demizdor) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MOUSE_SCALE_MARK_SIZE   12

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [shapes] example - rectangle scaling mouse");

    RL_Rectangle rec = { 100, 100, 200, 80 };

    RL_Vector2 mousePosition = { 0 };

    bool mouseScaleReady = false;
    bool mouseScaleMode = false;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mousePosition = RL_GetMousePosition();

        if (RL_CheckCollisionPointRec(mousePosition, (RL_Rectangle){ rec.x + rec.width - MOUSE_SCALE_MARK_SIZE, rec.y + rec.height - MOUSE_SCALE_MARK_SIZE, MOUSE_SCALE_MARK_SIZE, MOUSE_SCALE_MARK_SIZE }))
        {
            mouseScaleReady = true;
            if (RL_IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseScaleMode = true;
        }
        else mouseScaleReady = false;

        if (mouseScaleMode)
        {
            mouseScaleReady = true;

            rec.width = (mousePosition.x - rec.x);
            rec.height = (mousePosition.y - rec.y);

            // Check minimum rec size
            if (rec.width < MOUSE_SCALE_MARK_SIZE) rec.width = MOUSE_SCALE_MARK_SIZE;
            if (rec.height < MOUSE_SCALE_MARK_SIZE) rec.height = MOUSE_SCALE_MARK_SIZE;
            
            // Check maximum rec size
            if (rec.width > (RL_GetScreenWidth() - rec.x)) rec.width = RL_GetScreenWidth() - rec.x;
            if (rec.height > (RL_GetScreenHeight() - rec.y)) rec.height = RL_GetScreenHeight() - rec.y;

            if (RL_IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) mouseScaleMode = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawText("Scale rectangle dragging from bottom-right corner!", 10, 10, 20, RL_GRAY);

            RL_DrawRectangleRec(rec, RL_Fade(RL_GREEN, 0.5f));

            if (mouseScaleReady)
            {
                RL_DrawRectangleLinesEx(rec, 1, RL_RED);
                RL_DrawTriangle((RL_Vector2){ rec.x + rec.width - MOUSE_SCALE_MARK_SIZE, rec.y + rec.height },
                             (RL_Vector2){ rec.x + rec.width, rec.y + rec.height },
                             (RL_Vector2){ rec.x + rec.width, rec.y + rec.height - MOUSE_SCALE_MARK_SIZE }, RL_RED);
            }

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}