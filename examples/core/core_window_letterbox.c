/*******************************************************************************************
*
*   raylib [core] example - window scale letterbox (and virtual mouse)
*
*   Example originally created with raylib 2.5, last time updated with raylib 4.0
*
*   Example contributed by Anata (@anatagawa) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Anata (@anatagawa) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include "raymath.h"        // Required for: Vector2Clamp()

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    const int windowWidth = 800;
    const int windowHeight = 450;

    // Enable config flags for resizable window and vertical synchro
    RL_SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    RL_InitWindow(windowWidth, windowHeight, "raylib [core] example - window scale letterbox");
    RL_SetWindowMinSize(320, 240);

    int gameScreenWidth = 640;
    int gameScreenHeight = 480;

    // Render texture initialization, used to hold the rendering result so we can easily resize it
    RL_RenderTexture2D target = RL_LoadRenderTexture(gameScreenWidth, gameScreenHeight);
    RL_SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);  // RL_Texture scale filter to use

    RL_Color colors[10] = { 0 };
    for (int i = 0; i < 10; i++) colors[i] = (RL_Color){ RL_GetRandomValue(100, 250), RL_GetRandomValue(50, 150), RL_GetRandomValue(10, 100), 255 };

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Compute required framebuffer scaling
        float scale = MIN((float)RL_GetScreenWidth()/gameScreenWidth, (float)RL_GetScreenHeight()/gameScreenHeight);

        if (RL_IsKeyPressed(KEY_SPACE))
        {
            // Recalculate random colors for the bars
            for (int i = 0; i < 10; i++) colors[i] = (RL_Color){ RL_GetRandomValue(100, 250), RL_GetRandomValue(50, 150), RL_GetRandomValue(10, 100), 255 };
        }

        // Update virtual mouse (clamped mouse value behind game screen)
        RL_Vector2 mouse = RL_GetMousePosition();
        RL_Vector2 virtualMouse = { 0 };
        virtualMouse.x = (mouse.x - (RL_GetScreenWidth() - (gameScreenWidth*scale))*0.5f)/scale;
        virtualMouse.y = (mouse.y - (RL_GetScreenHeight() - (gameScreenHeight*scale))*0.5f)/scale;
        virtualMouse = Vector2Clamp(virtualMouse, (RL_Vector2){ 0, 0 }, (RL_Vector2){ (float)gameScreenWidth, (float)gameScreenHeight });

        // Apply the same transformation as the virtual mouse to the real mouse (i.e. to work with raygui)
        //RL_SetMouseOffset(-(RL_GetScreenWidth() - (gameScreenWidth*scale))*0.5f, -(RL_GetScreenHeight() - (gameScreenHeight*scale))*0.5f);
        //RL_SetMouseScale(1/scale, 1/scale);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        // Draw everything in the render texture, note this will not be rendered on screen, yet
        RL_BeginTextureMode(target);
            RL_ClearBackground(RL_RAYWHITE);  // Clear render texture background color

            for (int i = 0; i < 10; i++) RL_DrawRectangle(0, (gameScreenHeight/10)*i, gameScreenWidth, gameScreenHeight/10, colors[i]);

            RL_DrawText("If executed inside a window,\nyou can resize the window,\nand see the screen scaling!", 10, 25, 20, RL_WHITE);
            RL_DrawText(RL_TextFormat("Default Mouse: [%i , %i]", (int)mouse.x, (int)mouse.y), 350, 25, 20, RL_GREEN);
            RL_DrawText(RL_TextFormat("Virtual Mouse: [%i , %i]", (int)virtualMouse.x, (int)virtualMouse.y), 350, 55, 20, RL_YELLOW);
        RL_EndTextureMode();
        
        RL_BeginDrawing();
            RL_ClearBackground(RL_BLACK);     // Clear screen background

            // Draw render texture to screen, properly scaled
            RL_DrawTexturePro(target.texture, (RL_Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                           (RL_Rectangle){ (RL_GetScreenWidth() - ((float)gameScreenWidth*scale))*0.5f, (RL_GetScreenHeight() - ((float)gameScreenHeight*scale))*0.5f,
                           (float)gameScreenWidth*scale, (float)gameScreenHeight*scale }, (RL_Vector2){ 0, 0 }, 0.0f, RL_WHITE);
        RL_EndDrawing();
        //--------------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadRenderTexture(target);        // Unload render texture

    RL_CloseWindow();                      // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
