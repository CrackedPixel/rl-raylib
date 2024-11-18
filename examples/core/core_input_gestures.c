/*******************************************************************************************
*
*   raylib [core] example - Input Gestures Detection
*
*   Example originally created with raylib 1.4, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2016-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_GESTURE_STRINGS   20

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - input gestures");

    RL_Vector2 touchPosition = { 0, 0 };
    RL_Rectangle touchArea = { 220, 10, screenWidth - 230.0f, screenHeight - 20.0f };

    int gesturesCount = 0;
    char gestureStrings[MAX_GESTURE_STRINGS][32];

    int currentGesture = GESTURE_NONE;
    int lastGesture = GESTURE_NONE;

    //RL_SetGesturesEnabled(0b0000000000001001);   // Enable only some gestures to be detected

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        lastGesture = currentGesture;
        currentGesture = RL_GetGestureDetected();
        touchPosition = RL_GetTouchPosition(0);

        if (RL_CheckCollisionPointRec(touchPosition, touchArea) && (currentGesture != GESTURE_NONE))
        {
            if (currentGesture != lastGesture)
            {
                // Store gesture string
                switch (currentGesture)
                {
                    case GESTURE_TAP: RL_TextCopy(gestureStrings[gesturesCount], "GESTURE TAP"); break;
                    case GESTURE_DOUBLETAP: RL_TextCopy(gestureStrings[gesturesCount], "GESTURE DOUBLETAP"); break;
                    case GESTURE_HOLD: RL_TextCopy(gestureStrings[gesturesCount], "GESTURE HOLD"); break;
                    case GESTURE_DRAG: RL_TextCopy(gestureStrings[gesturesCount], "GESTURE DRAG"); break;
                    case GESTURE_SWIPE_RIGHT: RL_TextCopy(gestureStrings[gesturesCount], "GESTURE SWIPE RIGHT"); break;
                    case GESTURE_SWIPE_LEFT: RL_TextCopy(gestureStrings[gesturesCount], "GESTURE SWIPE LEFT"); break;
                    case GESTURE_SWIPE_UP: RL_TextCopy(gestureStrings[gesturesCount], "GESTURE SWIPE UP"); break;
                    case GESTURE_SWIPE_DOWN: RL_TextCopy(gestureStrings[gesturesCount], "GESTURE SWIPE DOWN"); break;
                    case GESTURE_PINCH_IN: RL_TextCopy(gestureStrings[gesturesCount], "GESTURE PINCH IN"); break;
                    case GESTURE_PINCH_OUT: RL_TextCopy(gestureStrings[gesturesCount], "GESTURE PINCH OUT"); break;
                    default: break;
                }

                gesturesCount++;

                // Reset gestures strings
                if (gesturesCount >= MAX_GESTURE_STRINGS)
                {
                    for (int i = 0; i < MAX_GESTURE_STRINGS; i++) RL_TextCopy(gestureStrings[i], "\0");

                    gesturesCount = 0;
                }
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawRectangleRec(touchArea, RL_GRAY);
            RL_DrawRectangle(225, 15, screenWidth - 240, screenHeight - 30, RL_RAYWHITE);

            RL_DrawText("GESTURES TEST AREA", screenWidth - 270, screenHeight - 40, 20, RL_Fade(RL_GRAY, 0.5f));

            for (int i = 0; i < gesturesCount; i++)
            {
                if (i%2 == 0) RL_DrawRectangle(10, 30 + 20*i, 200, 20, RL_Fade(RL_LIGHTGRAY, 0.5f));
                else RL_DrawRectangle(10, 30 + 20*i, 200, 20, RL_Fade(RL_LIGHTGRAY, 0.3f));

                if (i < gesturesCount - 1) RL_DrawText(gestureStrings[i], 35, 36 + 20*i, 10, RL_DARKGRAY);
                else RL_DrawText(gestureStrings[i], 35, 36 + 20*i, 10, RL_MAROON);
            }

            RL_DrawRectangleLines(10, 29, 200, screenHeight - 50, RL_GRAY);
            RL_DrawText("DETECTED GESTURES", 50, 15, 10, RL_GRAY);

            if (currentGesture != GESTURE_NONE) RL_DrawCircleV(touchPosition, 30, RL_MAROON);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}