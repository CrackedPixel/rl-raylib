/*******************************************************************************************
*
*   raylib [textures] example - RL_Image processing
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   Example originally created with raylib 1.4, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2016-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include <stdlib.h>             // Required for: free()

#define NUM_PROCESSES    9

typedef enum {
    NONE = 0,
    COLOR_GRAYSCALE,
    COLOR_TINT,
    COLOR_INVERT,
    COLOR_CONTRAST,
    COLOR_BRIGHTNESS,
    GAUSSIAN_BLUR,
    FLIP_VERTICAL,
    FLIP_HORIZONTAL
} ImageProcess;

static const char *processText[] = {
    "NO PROCESSING",
    "COLOR GRAYSCALE",
    "COLOR TINT",
    "COLOR INVERT",
    "COLOR CONTRAST",
    "COLOR BRIGHTNESS",
    "GAUSSIAN BLUR",
    "FLIP VERTICAL",
    "FLIP HORIZONTAL"
};

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [textures] example - image processing");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    RL_Image imOrigin = RL_LoadImage("resources/parrots.png");   // Loaded in CPU memory (RAM)
    RL_ImageFormat(&imOrigin, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);         // Format image to RGBA 32bit (required for texture update) <-- ISSUE
    RL_Texture2D texture = RL_LoadTextureFromImage(imOrigin);    // RL_Image converted to texture, GPU memory (VRAM)

    RL_Image imCopy = RL_ImageCopy(imOrigin);

    int currentProcess = NONE;
    bool textureReload = false;

    RL_Rectangle toggleRecs[NUM_PROCESSES] = { 0 };
    int mouseHoverRec = -1;

    for (int i = 0; i < NUM_PROCESSES; i++) toggleRecs[i] = (RL_Rectangle){ 40.0f, (float)(50 + 32*i), 150.0f, 30.0f };

    RL_SetTargetFPS(60);
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        // Mouse toggle group logic
        for (int i = 0; i < NUM_PROCESSES; i++)
        {
            if (RL_CheckCollisionPointRec(RL_GetMousePosition(), toggleRecs[i]))
            {
                mouseHoverRec = i;

                if (RL_IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    currentProcess = i;
                    textureReload = true;
                }
                break;
            }
            else mouseHoverRec = -1;
        }

        // Keyboard toggle group logic
        if (RL_IsKeyPressed(KEY_DOWN))
        {
            currentProcess++;
            if (currentProcess > (NUM_PROCESSES - 1)) currentProcess = 0;
            textureReload = true;
        }
        else if (RL_IsKeyPressed(KEY_UP))
        {
            currentProcess--;
            if (currentProcess < 0) currentProcess = 7;
            textureReload = true;
        }

        // Reload texture when required
        if (textureReload)
        {
            RL_UnloadImage(imCopy);                // Unload image-copy data
            imCopy = RL_ImageCopy(imOrigin);     // Restore image-copy from image-origin

            // NOTE: RL_Image processing is a costly CPU process to be done every frame,
            // If image processing is required in a frame-basis, it should be done
            // with a texture and by shaders
            switch (currentProcess)
            {
                case COLOR_GRAYSCALE: RL_ImageColorGrayscale(&imCopy); break;
                case COLOR_TINT: RL_ImageColorTint(&imCopy, RL_GREEN); break;
                case COLOR_INVERT: RL_ImageColorInvert(&imCopy); break;
                case COLOR_CONTRAST: RL_ImageColorContrast(&imCopy, -40); break;
                case COLOR_BRIGHTNESS: RL_ImageColorBrightness(&imCopy, -80); break;
                case GAUSSIAN_BLUR: RL_ImageBlurGaussian(&imCopy, 10); break;
                case FLIP_VERTICAL: RL_ImageFlipVertical(&imCopy); break;
                case FLIP_HORIZONTAL: RL_ImageFlipHorizontal(&imCopy); break;
                default: break;
            }

            RL_Color *pixels = RL_LoadImageColors(imCopy);    // Load pixel data from image (RGBA 32bit)
            RL_UpdateTexture(texture, pixels);             // Update texture with new image data
            RL_UnloadImageColors(pixels);                  // Unload pixels data from RAM

            textureReload = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawText("IMAGE PROCESSING:", 40, 30, 10, RL_DARKGRAY);

            // Draw rectangles
            for (int i = 0; i < NUM_PROCESSES; i++)
            {
                RL_DrawRectangleRec(toggleRecs[i], ((i == currentProcess) || (i == mouseHoverRec)) ? RL_SKYBLUE : RL_LIGHTGRAY);
                RL_DrawRectangleLines((int)toggleRecs[i].x, (int) toggleRecs[i].y, (int) toggleRecs[i].width, (int) toggleRecs[i].height, ((i == currentProcess) || (i == mouseHoverRec)) ? RL_BLUE : RL_GRAY);
                RL_DrawText( processText[i], (int)( toggleRecs[i].x + toggleRecs[i].width/2 - RL_MeasureText(processText[i], 10)/2), (int) toggleRecs[i].y + 11, 10, ((i == currentProcess) || (i == mouseHoverRec)) ? RL_DARKBLUE : RL_DARKGRAY);
            }

            RL_DrawTexture(texture, screenWidth - texture.width - 60, screenHeight/2 - texture.height/2, RL_WHITE);
            RL_DrawRectangleLines(screenWidth - texture.width - 60, screenHeight/2 - texture.height/2, texture.width, texture.height, RL_BLACK);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(texture);       // Unload texture from VRAM
    RL_UnloadImage(imOrigin);        // Unload image-origin from RAM
    RL_UnloadImage(imCopy);          // Unload image-copy from RAM

    RL_CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}