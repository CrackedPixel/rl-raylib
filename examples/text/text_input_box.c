/*******************************************************************************************
*
*   raylib [text] example - Input Box
*
*   Example originally created with raylib 1.7, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_INPUT_CHARS     9

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [text] example - input box");

    char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;

    RL_Rectangle textBox = { screenWidth/2.0f - 100, 180, 225, 50 };
    bool mouseOnText = false;

    int framesCounter = 0;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_CheckCollisionPointRec(RL_GetMousePosition(), textBox)) mouseOnText = true;
        else mouseOnText = false;

        if (mouseOnText)
        {
            // Set the window's cursor to the I-Beam
            RL_SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = RL_GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
                {
                    name[letterCount] = (char)key;
                    name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
                    letterCount++;
                }

                key = RL_GetCharPressed();  // Check next character in the queue
            }

            if (RL_IsKeyPressed(KEY_BACKSPACE))
            {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                name[letterCount] = '\0';
            }
        }
        else RL_SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawText("PLACE MOUSE OVER INPUT BOX!", 240, 140, 20, RL_GRAY);

            RL_DrawRectangleRec(textBox, RL_LIGHTGRAY);
            if (mouseOnText) RL_DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RL_RED);
            else RL_DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RL_DARKGRAY);

            RL_DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, RL_MAROON);

            RL_DrawText(RL_TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, RL_DARKGRAY);

            if (mouseOnText)
            {
                if (letterCount < MAX_INPUT_CHARS)
                {
                    // Draw blinking underscore char
                    if (((framesCounter/20)%2) == 0) RL_DrawText("_", (int)textBox.x + 8 + RL_MeasureText(name, 40), (int)textBox.y + 12, 40, RL_MAROON);
                }
                else RL_DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, RL_GRAY);
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

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = RL_GetKeyPressed();

    if ((key >= 32) && (key <= 126)) keyPressed = true;

    return keyPressed;
}
