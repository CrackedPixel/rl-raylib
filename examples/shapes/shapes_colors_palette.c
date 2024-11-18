/*******************************************************************************************
*
*   raylib [shapes] example - Colors palette
*
*   Example originally created with raylib 1.0, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_COLORS_COUNT    21          // Number of colors available

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [shapes] example - colors palette");

    RL_Color colors[MAX_COLORS_COUNT] = {
        RL_DARKGRAY, RL_MAROON, RL_ORANGE, RL_DARKGREEN, RL_DARKBLUE, RL_DARKPURPLE, RL_DARKBROWN,
        RL_GRAY, RL_RED, RL_GOLD, RL_LIME, RL_BLUE, RL_VIOLET, RL_BROWN, RL_LIGHTGRAY, RL_PINK, RL_YELLOW,
        RL_GREEN, RL_SKYBLUE, RL_PURPLE, RL_BEIGE };

    const char *colorNames[MAX_COLORS_COUNT] = {
        "RL_DARKGRAY", "RL_MAROON", "RL_ORANGE", "RL_DARKGREEN", "RL_DARKBLUE", "RL_DARKPURPLE",
        "RL_DARKBROWN", "RL_GRAY", "RL_RED", "RL_GOLD", "RL_LIME", "RL_BLUE", "RL_VIOLET", "RL_BROWN",
        "RL_LIGHTGRAY", "RL_PINK", "RL_YELLOW", "RL_GREEN", "RL_SKYBLUE", "RL_PURPLE", "RL_BEIGE" };

    RL_Rectangle colorsRecs[MAX_COLORS_COUNT] = { 0 };     // Rectangles array

    // Fills colorsRecs data (for every rectangle)
    for (int i = 0; i < MAX_COLORS_COUNT; i++)
    {
        colorsRecs[i].x = 20.0f + 100.0f *(i%7) + 10.0f *(i%7);
        colorsRecs[i].y = 80.0f + 100.0f *(i/7) + 10.0f *(i/7);
        colorsRecs[i].width = 100.0f;
        colorsRecs[i].height = 100.0f;
    }

    int colorState[MAX_COLORS_COUNT] = { 0 };           // RL_Color state: 0-DEFAULT, 1-MOUSE_HOVER

    RL_Vector2 mousePoint = { 0.0f, 0.0f };

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mousePoint = RL_GetMousePosition();

        for (int i = 0; i < MAX_COLORS_COUNT; i++)
        {
            if (RL_CheckCollisionPointRec(mousePoint, colorsRecs[i])) colorState[i] = 1;
            else colorState[i] = 0;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawText("raylib colors palette", 28, 42, 20, RL_BLACK);
            RL_DrawText("press SPACE to see all colors", RL_GetScreenWidth() - 180, RL_GetScreenHeight() - 40, 10, RL_GRAY);

            for (int i = 0; i < MAX_COLORS_COUNT; i++)    // Draw all rectangles
            {
                RL_DrawRectangleRec(colorsRecs[i], RL_Fade(colors[i], colorState[i]? 0.6f : 1.0f));

                if (RL_IsKeyDown(KEY_SPACE) || colorState[i])
                {
                    RL_DrawRectangle((int)colorsRecs[i].x, (int)(colorsRecs[i].y + colorsRecs[i].height - 26), (int)colorsRecs[i].width, 20, RL_BLACK);
                    RL_DrawRectangleLinesEx(colorsRecs[i], 6, RL_Fade(RL_BLACK, 0.3f));
                    RL_DrawText(colorNames[i], (int)(colorsRecs[i].x + colorsRecs[i].width - RL_MeasureText(colorNames[i], 10) - 12),
                        (int)(colorsRecs[i].y + colorsRecs[i].height - 20), 10, colors[i]);
                }
            }

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}