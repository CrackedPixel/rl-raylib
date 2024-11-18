/*******************************************************************************************
*
*   raylib [textures] example - RL_Texture source and destination rectangles
*
*   Example originally created with raylib 1.3, last time updated with raylib 1.3
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [textures] examples - texture source and destination rectangles");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    RL_Texture2D scarfy = RL_LoadTexture("resources/scarfy.png");        // RL_Texture loading

    int frameWidth = scarfy.width/6;
    int frameHeight = scarfy.height;

    // Source rectangle (part of the texture to use for drawing)
    RL_Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };

    // Destination rectangle (screen rectangle where drawing part of texture)
    RL_Rectangle destRec = { screenWidth/2.0f, screenHeight/2.0f, frameWidth*2.0f, frameHeight*2.0f };

    // Origin of the texture (rotation/scale point), it's relative to destination rectangle size
    RL_Vector2 origin = { (float)frameWidth, (float)frameHeight };

    int rotation = 0;

    RL_SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        rotation++;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            // NOTE: Using RL_DrawTexturePro() we can easily rotate and scale the part of the texture we draw
            // sourceRec defines the part of the texture we use for drawing
            // destRec defines the rectangle where our texture part will fit (scaling it to fit)
            // origin defines the point of the texture used as reference for rotation and scaling
            // rotation defines the texture rotation (using origin as rotation point)
            RL_DrawTexturePro(scarfy, sourceRec, destRec, origin, (float)rotation, RL_WHITE);

            RL_DrawLine((int)destRec.x, 0, (int)destRec.x, screenHeight, RL_GRAY);
            RL_DrawLine(0, (int)destRec.y, screenWidth, (int)destRec.y, RL_GRAY);

            RL_DrawText("(c) Scarfy sprite by Eiden Marsal", screenWidth - 200, screenHeight - 20, 10, RL_GRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(scarfy);        // RL_Texture unloading

    RL_CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}