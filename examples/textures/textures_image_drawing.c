/*******************************************************************************************
*
*   raylib [textures] example - RL_Image loading and drawing on it
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   Example originally created with raylib 1.4, last time updated with raylib 1.4
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2016-2024 Ramon Santamaria (@raysan5)
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [textures] example - image drawing");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    RL_Image cat = RL_LoadImage("resources/cat.png");             // Load image in CPU memory (RAM)
    RL_ImageCrop(&cat, (RL_Rectangle){ 100, 10, 280, 380 });      // Crop an image piece
    RL_ImageFlipHorizontal(&cat);                              // Flip cropped image horizontally
    RL_ImageResize(&cat, 150, 200);                            // Resize flipped-cropped image

    RL_Image parrots = RL_LoadImage("resources/parrots.png");     // Load image in CPU memory (RAM)

    // Draw one image over the other with a scaling of 1.5f
    RL_ImageDraw(&parrots, cat, (RL_Rectangle){ 0, 0, (float)cat.width, (float)cat.height }, (RL_Rectangle){ 30, 40, cat.width*1.5f, cat.height*1.5f }, RL_WHITE);
    RL_ImageCrop(&parrots, (RL_Rectangle){ 0, 50, (float)parrots.width, (float)parrots.height - 100 }); // Crop resulting image

    // Draw on the image with a few image draw methods
    RL_ImageDrawPixel(&parrots, 10, 10, RL_RAYWHITE);
    RL_ImageDrawCircleLines(&parrots, 10, 10, 5, RL_RAYWHITE);
    RL_ImageDrawRectangle(&parrots, 5, 20, 10, 10, RL_RAYWHITE);

    RL_UnloadImage(cat);       // Unload image from RAM

    // Load custom font for drawing on image
    RL_Font font = RL_LoadFont("resources/custom_jupiter_crash.png");

    // Draw over image using custom font
    RL_ImageDrawTextEx(&parrots, font, "PARROTS & CAT", (RL_Vector2){ 300, 230 }, (float)font.baseSize, -2, RL_WHITE);

    RL_UnloadFont(font);       // Unload custom font (already drawn used on image)

    RL_Texture2D texture = RL_LoadTextureFromImage(parrots);      // RL_Image converted to texture, uploaded to GPU memory (VRAM)
    RL_UnloadImage(parrots);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

    RL_SetTargetFPS(60);
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, RL_WHITE);
            RL_DrawRectangleLines(screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2 - 40, texture.width, texture.height, RL_DARKGRAY);

            RL_DrawText("We are drawing only one texture from various images composed!", 240, 350, 10, RL_DARKGRAY);
            RL_DrawText("Source images have been cropped, scaled, flipped and copied one over the other.", 190, 370, 10, RL_DARKGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(texture);       // RL_Texture unloading

    RL_CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
