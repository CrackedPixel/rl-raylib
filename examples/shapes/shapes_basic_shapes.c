/*******************************************************************************************
*
*   raylib [shapes] example - Draw basic shapes 2d (rectangle, circle, line...)
*
*   Example originally created with raylib 1.0, last time updated with raylib 4.2
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [shapes] example - basic shapes drawing");

    float rotation = 0.0f;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        rotation += 0.2f;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawText("some basic shapes available on raylib", 20, 20, 20, RL_DARKGRAY);

            // Circle shapes and lines
            RL_DrawCircle(screenWidth/5, 120, 35, RL_DARKBLUE);
            RL_DrawCircleGradient(screenWidth/5, 220, 60, RL_GREEN, RL_SKYBLUE);
            RL_DrawCircleLines(screenWidth/5, 340, 80, RL_DARKBLUE);

            // RL_Rectangle shapes and lines
            RL_DrawRectangle(screenWidth/4*2 - 60, 100, 120, 60, RL_RED);
            RL_DrawRectangleGradientH(screenWidth/4*2 - 90, 170, 180, 130, RL_MAROON, RL_GOLD);
            RL_DrawRectangleLines(screenWidth/4*2 - 40, 320, 80, 60, RL_ORANGE);  // NOTE: Uses QUADS internally, not lines

            // Triangle shapes and lines
            RL_DrawTriangle((RL_Vector2){ screenWidth/4.0f *3.0f, 80.0f },
                         (RL_Vector2){ screenWidth/4.0f *3.0f - 60.0f, 150.0f },
                         (RL_Vector2){ screenWidth/4.0f *3.0f + 60.0f, 150.0f }, RL_VIOLET);

            RL_DrawTriangleLines((RL_Vector2){ screenWidth/4.0f*3.0f, 160.0f },
                              (RL_Vector2){ screenWidth/4.0f*3.0f - 20.0f, 230.0f },
                              (RL_Vector2){ screenWidth/4.0f*3.0f + 20.0f, 230.0f }, RL_DARKBLUE);

            // Polygon shapes and lines
            RL_DrawPoly((RL_Vector2){ screenWidth/4.0f*3, 330 }, 6, 80, rotation, RL_BROWN);
            RL_DrawPolyLines((RL_Vector2){ screenWidth/4.0f*3, 330 }, 6, 90, rotation, RL_BROWN);
            RL_DrawPolyLinesEx((RL_Vector2){ screenWidth/4.0f*3, 330 }, 6, 85, rotation, 6, RL_BEIGE);

            // NOTE: We draw all LINES based shapes together to optimize internal drawing,
            // this way, all LINES are rendered in a single draw pass
            RL_DrawLine(18, 42, screenWidth - 18, 42, RL_BLACK);
        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
