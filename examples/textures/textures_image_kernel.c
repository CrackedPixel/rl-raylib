/*******************************************************************************************
*
*   raylib [textures] example - RL_Image loading and texture creation
*
*   NOTE: Images are loaded in CPU memory (RAM); textures are loaded in GPU memory (VRAM)
*
*   Example originally created with raylib 1.3, last time updated with raylib 1.3
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Karim Salem (@kimo-s)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
void NormalizeKernel(float *kernel, int size)
{
    float sum = 0.0f;
    for (int i = 0; i < size; i++) sum += kernel[i]; 

    if (sum != 0.0f)
    {
        for (int i = 0; i < size; i++) kernel[i] /= sum; 
    }
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [textures] example - image convolution");
        
    RL_Image image = RL_LoadImage("resources/cat.png");     // Loaded in CPU memory (RAM)

    float gaussiankernel[] = { 
        1.0f, 2.0f, 1.0f,
        2.0f, 4.0f, 2.0f,
        1.0f, 2.0f, 1.0f };

    float sobelkernel[] = {
        1.0f, 0.0f, -1.0f,
        2.0f, 0.0f, -2.0f,
        1.0f, 0.0f, -1.0f };

    float sharpenkernel[] = {
        0.0f, -1.0f, 0.0f,
       -1.0f, 5.0f, -1.0f,
        0.0f, -1.0f, 0.0f };

    NormalizeKernel(gaussiankernel, 9);
    NormalizeKernel(sharpenkernel, 9);
    NormalizeKernel(sobelkernel, 9);

    RL_Image catSharpend = RL_ImageCopy(image);
    RL_ImageKernelConvolution(&catSharpend, sharpenkernel, 9);
 
    RL_Image catSobel = RL_ImageCopy(image);
    RL_ImageKernelConvolution(&catSobel, sobelkernel, 9);

    RL_Image catGaussian = RL_ImageCopy(image);
    
    for (int i = 0; i < 6; i++)
    {
        RL_ImageKernelConvolution(&catGaussian, gaussiankernel, 9);
    }

    RL_ImageCrop(&image, (RL_Rectangle){ 0, 0, (float)200, (float)450 });
    RL_ImageCrop(&catGaussian, (RL_Rectangle){ 0, 0, (float)200, (float)450 });
    RL_ImageCrop(&catSobel, (RL_Rectangle){ 0, 0, (float)200, (float)450 });
    RL_ImageCrop(&catSharpend, (RL_Rectangle){ 0, 0, (float)200, (float)450 });
    
    // Images converted to texture, GPU memory (VRAM)
    RL_Texture2D texture = RL_LoadTextureFromImage(image);
    RL_Texture2D catSharpendTexture = RL_LoadTextureFromImage(catSharpend);
    RL_Texture2D catSobelTexture = RL_LoadTextureFromImage(catSobel);
    RL_Texture2D catGaussianTexture = RL_LoadTextureFromImage(catGaussian);
    
    // Once images have been converted to texture and uploaded to VRAM, 
    // they can be unloaded from RAM
    RL_UnloadImage(image);
    RL_UnloadImage(catGaussian);
    RL_UnloadImage(catSobel);
    RL_UnloadImage(catSharpend);

    RL_SetTargetFPS(60);     // Set our game to run at 60 frames-per-second
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

            RL_DrawTexture(catSharpendTexture, 0, 0, RL_WHITE);
            RL_DrawTexture(catSobelTexture, 200, 0, RL_WHITE);
            RL_DrawTexture(catGaussianTexture, 400, 0, RL_WHITE);
            RL_DrawTexture(texture, 600, 0, RL_WHITE);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(texture);
    RL_UnloadTexture(catGaussianTexture);
    RL_UnloadTexture(catSobelTexture);
    RL_UnloadTexture(catSharpendTexture);

    RL_CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
