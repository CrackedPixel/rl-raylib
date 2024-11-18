/*******************************************************************************************
*
*   raylib [shapes] example - draw ring (with gui options)
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [shapes] example - draw ring");

    RL_Vector2 center = {(RL_GetScreenWidth() - 300)/2.0f, RL_GetScreenHeight()/2.0f };

    float innerRadius = 80.0f;
    float outerRadius = 190.0f;

    float startAngle = 0.0f;
    float endAngle = 360.0f;
    float segments = 0.0f;

    bool drawRing = true;
    bool drawRingLines = false;
    bool drawCircleLines = false;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // NOTE: All variables update happens inside GUI control functions
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawLine(500, 0, 500, RL_GetScreenHeight(), RL_Fade(RL_LIGHTGRAY, 0.6f));
            RL_DrawRectangle(500, 0, RL_GetScreenWidth() - 500, RL_GetScreenHeight(), RL_Fade(RL_LIGHTGRAY, 0.3f));

            if (drawRing) RL_DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, (int)segments, RL_Fade(RL_MAROON, 0.3f));
            if (drawRingLines) RL_DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, (int)segments, RL_Fade(RL_BLACK, 0.4f));
            if (drawCircleLines) RL_DrawCircleSectorLines(center, outerRadius, startAngle, endAngle, (int)segments, RL_Fade(RL_BLACK, 0.4f));

            // Draw GUI controls
            //------------------------------------------------------------------------------
            GuiSliderBar((RL_Rectangle){ 600, 40, 120, 20 }, "StartAngle", RL_TextFormat("%.2f", startAngle), &startAngle, -450, 450);
            GuiSliderBar((RL_Rectangle){ 600, 70, 120, 20 }, "EndAngle", RL_TextFormat("%.2f", endAngle), &endAngle, -450, 450);

            GuiSliderBar((RL_Rectangle){ 600, 140, 120, 20 }, "InnerRadius", RL_TextFormat("%.2f", innerRadius), &innerRadius, 0, 100);
            GuiSliderBar((RL_Rectangle){ 600, 170, 120, 20 }, "OuterRadius", RL_TextFormat("%.2f", outerRadius), &outerRadius, 0, 200);

            GuiSliderBar((RL_Rectangle){ 600, 240, 120, 20 }, "Segments", RL_TextFormat("%.2f", segments), &segments, 0, 100);

            GuiCheckBox((RL_Rectangle){ 600, 320, 20, 20 }, "Draw Ring", &drawRing);
            GuiCheckBox((RL_Rectangle){ 600, 350, 20, 20 }, "Draw RingLines", &drawRingLines);
            GuiCheckBox((RL_Rectangle){ 600, 380, 20, 20 }, "Draw CircleLines", &drawCircleLines);
            //------------------------------------------------------------------------------

            int minSegments = (int)ceilf((endAngle - startAngle)/90);
            RL_DrawText(RL_TextFormat("MODE: %s", (segments >= minSegments)? "MANUAL" : "AUTO"), 600, 270, 10, (segments >= minSegments)? RL_MAROON : RL_DARKGRAY);

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