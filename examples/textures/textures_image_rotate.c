/*******************************************************************************************
*
*   raylib [textures] example - RL_Image Rotation
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define NUM_TEXTURES  3

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [textures] example - texture rotation");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    RL_Image image45 = RL_LoadImage("resources/raylib_logo.png");
    RL_Image image90 = RL_LoadImage("resources/raylib_logo.png");
    RL_Image imageNeg90 = RL_LoadImage("resources/raylib_logo.png");

    RL_ImageRotate(&image45, 45);
    RL_ImageRotate(&image90, 90);
    RL_ImageRotate(&imageNeg90, -90);

    RL_Texture2D textures[NUM_TEXTURES] = { 0 };

    textures[0] = RL_LoadTextureFromImage(image45);
    textures[1] = RL_LoadTextureFromImage(image90);
    textures[2] = RL_LoadTextureFromImage(imageNeg90);

    int currentTexture = 0;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || RL_IsKeyPressed(KEY_RIGHT))
        {
            currentTexture = (currentTexture + 1)%NUM_TEXTURES; // Cycle between the textures
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawTexture(textures[currentTexture], screenWidth/2 - textures[currentTexture].width/2, screenHeight/2 - textures[currentTexture].height/2, RL_WHITE);

            RL_DrawText("Press LEFT MOUSE BUTTON to rotate the image clockwise", 250, 420, 10, RL_DARKGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    for (int i = 0; i < NUM_TEXTURES; i++) RL_UnloadTexture(textures[i]);

    RL_CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
