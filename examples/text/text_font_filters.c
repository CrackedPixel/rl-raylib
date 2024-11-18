/*******************************************************************************************
*
*   raylib [text] example - RL_Font filters
*
*   NOTE: After font loading, font texture atlas filter could be configured for a softer
*   display of the font when scaling it to different sizes, that way, it's not required
*   to generate multiple fonts at multiple sizes (as long as the scaling is not very different)
*
*   Example originally created with raylib 1.3, last time updated with raylib 4.2
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [text] example - font filters");

    const char msg[50] = "Loaded RL_Font";

    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)

    // TTF RL_Font loading with custom generation parameters
    RL_Font font = RL_LoadFontEx("resources/KAISG.ttf", 96, 0, 0);

    // Generate mipmap levels to use trilinear filtering
    // NOTE: On 2D drawing it won't be noticeable, it looks like FILTER_BILINEAR
    RL_GenTextureMipmaps(&font.texture);

    float fontSize = (float)font.baseSize;
    RL_Vector2 fontPosition = { 40.0f, screenHeight/2.0f - 80.0f };
    RL_Vector2 textSize = { 0.0f, 0.0f };

    // Setup texture scaling filter
    RL_SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
    int currentFontFilter = 0;      // TEXTURE_FILTER_POINT

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        fontSize += RL_GetMouseWheelMove()*4.0f;

        // Choose font texture filter method
        if (RL_IsKeyPressed(KEY_ONE))
        {
            RL_SetTextureFilter(font.texture, TEXTURE_FILTER_POINT);
            currentFontFilter = 0;
        }
        else if (RL_IsKeyPressed(KEY_TWO))
        {
            RL_SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
            currentFontFilter = 1;
        }
        else if (RL_IsKeyPressed(KEY_THREE))
        {
            // NOTE: Trilinear filter won't be noticed on 2D drawing
            RL_SetTextureFilter(font.texture, TEXTURE_FILTER_TRILINEAR);
            currentFontFilter = 2;
        }

        textSize = RL_MeasureTextEx(font, msg, fontSize, 0);

        if (RL_IsKeyDown(KEY_LEFT)) fontPosition.x -= 10;
        else if (RL_IsKeyDown(KEY_RIGHT)) fontPosition.x += 10;

        // Load a dropped TTF file dynamically (at current fontSize)
        if (RL_IsFileDropped())
        {
            RL_FilePathList droppedFiles = RL_LoadDroppedFiles();

            // NOTE: We only support first ttf file dropped
            if (RL_IsFileExtension(droppedFiles.paths[0], ".ttf"))
            {
                RL_UnloadFont(font);
                font = RL_LoadFontEx(droppedFiles.paths[0], (int)fontSize, 0, 0);
            }
            
            RL_UnloadDroppedFiles(droppedFiles);    // Unload filepaths from memory
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawText("Use mouse wheel to change font size", 20, 20, 10, RL_GRAY);
            RL_DrawText("Use KEY_RIGHT and KEY_LEFT to move text", 20, 40, 10, RL_GRAY);
            RL_DrawText("Use 1, 2, 3 to change texture filter", 20, 60, 10, RL_GRAY);
            RL_DrawText("Drop a new TTF font for dynamic loading", 20, 80, 10, RL_DARKGRAY);

            RL_DrawTextEx(font, msg, fontPosition, fontSize, 0, RL_BLACK);

            // TODO: It seems texSize measurement is not accurate due to chars offsets...
            //RL_DrawRectangleLines(fontPosition.x, fontPosition.y, textSize.x, textSize.y, RL_RED);

            RL_DrawRectangle(0, screenHeight - 80, screenWidth, 80, RL_LIGHTGRAY);
            RL_DrawText(RL_TextFormat("RL_Font size: %02.02f", fontSize), 20, screenHeight - 50, 10, RL_DARKGRAY);
            RL_DrawText(RL_TextFormat("Text size: [%02.02f, %02.02f]", textSize.x, textSize.y), 20, screenHeight - 30, 10, RL_DARKGRAY);
            RL_DrawText("CURRENT TEXTURE FILTER:", 250, 400, 20, RL_GRAY);

            if (currentFontFilter == 0) RL_DrawText("POINT", 570, 400, 20, RL_BLACK);
            else if (currentFontFilter == 1) RL_DrawText("BILINEAR", 570, 400, 20, RL_BLACK);
            else if (currentFontFilter == 2) RL_DrawText("TRILINEAR", 570, 400, 20, RL_BLACK);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadFont(font);           // RL_Font unloading

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}