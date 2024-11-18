/*******************************************************************************************
*
*   raylib [shapes] example - draw rectangle rounded (with gui options)
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

#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"                 // Required for GUI controls

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [shapes] example - draw rectangle rounded");

    float roundness = 0.2f;
    float width = 200.0f;
    float height = 100.0f;
    float segments = 0.0f;
    float lineThick = 1.0f;

    bool drawRect = false;
    bool drawRoundedRect = true;
    bool drawRoundedLines = false;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_Rectangle rec = { ((float)RL_GetScreenWidth() - width - 250)/2, (RL_GetScreenHeight() - height)/2.0f, (float)width, (float)height };
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawLine(560, 0, 560, RL_GetScreenHeight(), RL_Fade(RL_LIGHTGRAY, 0.6f));
            RL_DrawRectangle(560, 0, RL_GetScreenWidth() - 500, RL_GetScreenHeight(), RL_Fade(RL_LIGHTGRAY, 0.3f));

            if (drawRect) RL_DrawRectangleRec(rec, RL_Fade(RL_GOLD, 0.6f));
            if (drawRoundedRect) RL_DrawRectangleRounded(rec, roundness, (int)segments, RL_Fade(RL_MAROON, 0.2f));
            if (drawRoundedLines) RL_DrawRectangleRoundedLinesEx(rec, roundness, (int)segments, lineThick, RL_Fade(RL_MAROON, 0.4f));

            // Draw GUI controls
            //------------------------------------------------------------------------------
            GuiSliderBar((RL_Rectangle){ 640, 40, 105, 20 }, "Width", RL_TextFormat("%.2f", width), &width, 0, (float)RL_GetScreenWidth() - 300);
            GuiSliderBar((RL_Rectangle){ 640, 70, 105, 20 }, "Height", RL_TextFormat("%.2f", height), &height, 0, (float)RL_GetScreenHeight() - 50);
            GuiSliderBar((RL_Rectangle){ 640, 140, 105, 20 }, "Roundness", RL_TextFormat("%.2f", roundness), &roundness, 0.0f, 1.0f);
            GuiSliderBar((RL_Rectangle){ 640, 170, 105, 20 }, "Thickness", RL_TextFormat("%.2f", lineThick), &lineThick, 0, 20);
            GuiSliderBar((RL_Rectangle){ 640, 240, 105, 20}, "Segments", RL_TextFormat("%.2f", segments), &segments, 0, 60);

            GuiCheckBox((RL_Rectangle){ 640, 320, 20, 20 }, "DrawRoundedRect", &drawRoundedRect);
            GuiCheckBox((RL_Rectangle){ 640, 350, 20, 20 }, "DrawRoundedLines", &drawRoundedLines);
            GuiCheckBox((RL_Rectangle){ 640, 380, 20, 20}, "DrawRect", &drawRect);
            //------------------------------------------------------------------------------

            RL_DrawText(RL_TextFormat("MODE: %s", (segments >= 4)? "MANUAL" : "AUTO"), 640, 280, 10, (segments >= 4)? RL_MAROON : RL_DARKGRAY);

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
