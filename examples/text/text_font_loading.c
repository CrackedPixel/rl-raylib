/*******************************************************************************************
*
*   raylib [text] example - RL_Font loading
*
*   NOTE: raylib can load fonts from multiple input file formats:
*
*     - TTF/OTF > Sprite font atlas is generated on loading, user can configure
*                 some of the generation parameters (size, characters to include)
*     - BMFonts > Angel code font fileformat, sprite font image must be provided
*                 together with the .fnt file, font generation cna not be configured
*     - XNA Spritefont > Sprite font image, following XNA Spritefont conventions,
*                 Characters in image must follow some spacing and order rules
*
*   Example originally created with raylib 1.4, last time updated with raylib 3.0
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [text] example - font loading");

    // Define characters to draw
    // NOTE: raylib supports UTF-8 encoding, following list is actually codified as UTF8 internally
    const char msg[256] = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHI\nJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmn\nopqrstuvwxyz{|}~¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓ\nÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷\nøùúûüýþÿ";

    // NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)

    // BMFont (AngelCode) : RL_Font data and image atlas have been generated using external program
    RL_Font fontBm = RL_LoadFont("resources/pixantiqua.fnt");

    // TTF font : RL_Font data and atlas are generated directly from TTF
    // NOTE: We define a font base size of 32 pixels tall and up-to 250 characters
    RL_Font fontTtf = RL_LoadFontEx("resources/pixantiqua.ttf", 32, 0, 250);

    RL_SetTextLineSpacing(16);         // Set line spacing for multiline text (when line breaks are included '\n')

    bool useTtf = false;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsKeyDown(KEY_SPACE)) useTtf = true;
        else useTtf = false;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawText("Hold SPACE to use TTF generated font", 20, 20, 20, RL_LIGHTGRAY);

            if (!useTtf)
            {
                RL_DrawTextEx(fontBm, msg, (RL_Vector2){ 20.0f, 100.0f }, (float)fontBm.baseSize, 2, RL_MAROON);
                RL_DrawText("Using BMFont (Angelcode) imported", 20, RL_GetScreenHeight() - 30, 20, RL_GRAY);
            }
            else
            {
                RL_DrawTextEx(fontTtf, msg, (RL_Vector2){ 20.0f, 100.0f }, (float)fontTtf.baseSize, 2, RL_LIME);
                RL_DrawText("Using TTF font generated", 20, RL_GetScreenHeight() - 30, 20, RL_GRAY);
            }

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadFont(fontBm);     // AngelCode RL_Font unloading
    RL_UnloadFont(fontTtf);    // TTF RL_Font unloading

    RL_CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}