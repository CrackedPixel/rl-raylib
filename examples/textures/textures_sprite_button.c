/*******************************************************************************************
*
*   raylib [textures] example - sprite button
*
*   Example originally created with raylib 2.5, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define NUM_FRAMES  3       // Number of frames (rectangles) for the button sprite texture

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [textures] example - sprite button");

    RL_InitAudioDevice();      // Initialize audio device

    RL_Sound fxButton = RL_LoadSound("resources/buttonfx.wav");   // Load button sound
    RL_Texture2D button = RL_LoadTexture("resources/button.png"); // Load button texture

    // Define frame rectangle for drawing
    float frameHeight = (float)button.height/NUM_FRAMES;
    RL_Rectangle sourceRec = { 0, 0, (float)button.width, frameHeight };

    // Define button bounds on screen
    RL_Rectangle btnBounds = { screenWidth/2.0f - button.width/2.0f, screenHeight/2.0f - button.height/NUM_FRAMES/2.0f, (float)button.width, frameHeight };

    int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    bool btnAction = false;         // Button action should be activated

    RL_Vector2 mousePoint = { 0.0f, 0.0f };

    RL_SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        mousePoint = RL_GetMousePosition();
        btnAction = false;

        // Check button state
        if (RL_CheckCollisionPointRec(mousePoint, btnBounds))
        {
            if (RL_IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
            else btnState = 1;

            if (RL_IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
        }
        else btnState = 0;

        if (btnAction)
        {
            RL_PlaySound(fxButton);

            // TODO: Any desired action
        }

        // Calculate button frame rectangle to draw depending on button state
        sourceRec.y = btnState*frameHeight;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawTextureRec(button, sourceRec, (RL_Vector2){ btnBounds.x, btnBounds.y }, RL_WHITE); // Draw button frame

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(button);  // Unload button texture
    RL_UnloadSound(fxButton);  // Unload sound

    RL_CloseAudioDevice();     // Close audio device

    RL_CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}