/*******************************************************************************************
*
*   raylib [core] example - custom frame control
*
*   NOTE: WARNING: This is an example for advanced users willing to have full control over
*   the frame processes. By default, RL_EndDrawing() calls the following processes:
*       1. Draw remaining batch data: rlDrawRenderBatchActive()
*       2. RL_SwapScreenBuffer()
*       3. Frame time control: RL_WaitTime()
*       4. RL_PollInputEvents()
*
*   To avoid steps 2, 3 and 4, flag SUPPORT_CUSTOM_FRAME_CONTROL can be enabled in
*   config.h (it requires recompiling raylib). This way those steps are up to the user.
*
*   Note that enabling this flag invalidates some functions:
*       - RL_GetFrameTime()
*       - RL_SetTargetFPS()
*       - RL_GetFPS()
*
*   Example originally created with raylib 4.0, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2024 Ramon Santamaria (@raysan5)
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
    
    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - custom frame control");

    // Custom timming variables
    double previousTime = RL_GetTime();    // Previous time measure
    double currentTime = 0.0;           // Current time measure
    double updateDrawTime = 0.0;        // Update + Draw time
    double waitTime = 0.0;              // Wait time (if target fps required)
    float deltaTime = 0.0f;             // Frame time (Update + Draw + Wait time)
    
    float timeCounter = 0.0f;           // Accumulative time counter (seconds)
    float position = 0.0f;              // Circle position
    bool pause = false;                 // Pause control flag
    
    int targetFPS = 60;                 // Our initial target fps
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_PollInputEvents();              // Poll input events (SUPPORT_CUSTOM_FRAME_CONTROL)
        
        if (RL_IsKeyPressed(KEY_SPACE)) pause = !pause;
        
        if (RL_IsKeyPressed(KEY_UP)) targetFPS += 20;
        else if (RL_IsKeyPressed(KEY_DOWN)) targetFPS -= 20;
        
        if (targetFPS < 0) targetFPS = 0;

        if (!pause)
        {
            position += 200*deltaTime;  // We move at 200 pixels per second
            if (position >= RL_GetScreenWidth()) position = 0;
            timeCounter += deltaTime;   // We count time (seconds)
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            for (int i = 0; i < RL_GetScreenWidth()/200; i++) RL_DrawRectangle(200*i, 0, 1, RL_GetScreenHeight(), RL_SKYBLUE);
            
            RL_DrawCircle((int)position, RL_GetScreenHeight()/2 - 25, 50, RL_RED);
            
            RL_DrawText(RL_TextFormat("%03.0f ms", timeCounter*1000.0f), (int)position - 40, RL_GetScreenHeight()/2 - 100, 20, RL_MAROON);
            RL_DrawText(RL_TextFormat("PosX: %03.0f", position), (int)position - 50, RL_GetScreenHeight()/2 + 40, 20, RL_BLACK);
            
            RL_DrawText("Circle is moving at a constant 200 pixels/sec,\nindependently of the frame rate.", 10, 10, 20, RL_DARKGRAY);
            RL_DrawText("PRESS SPACE to PAUSE MOVEMENT", 10, RL_GetScreenHeight() - 60, 20, RL_GRAY);
            RL_DrawText("PRESS UP | DOWN to CHANGE TARGET FPS", 10, RL_GetScreenHeight() - 30, 20, RL_GRAY);
            RL_DrawText(RL_TextFormat("TARGET FPS: %i", targetFPS), RL_GetScreenWidth() - 220, 10, 20, RL_LIME);
            RL_DrawText(RL_TextFormat("CURRENT FPS: %i", (int)(1.0f/deltaTime)), RL_GetScreenWidth() - 220, 40, 20, RL_GREEN);

        RL_EndDrawing();

        // NOTE: In case raylib is configured to SUPPORT_CUSTOM_FRAME_CONTROL, 
        // Events polling, screen buffer swap and frame time control must be managed by the user

        RL_SwapScreenBuffer();         // Flip the back buffer to screen (front buffer)
        
        currentTime = RL_GetTime();
        updateDrawTime = currentTime - previousTime;
        
        if (targetFPS > 0)          // We want a fixed frame rate
        {
            waitTime = (1.0f/(float)targetFPS) - updateDrawTime;
            if (waitTime > 0.0) 
            {
                RL_WaitTime((float)waitTime);
                currentTime = RL_GetTime();
                deltaTime = (float)(currentTime - previousTime);
            }
        }
        else deltaTime = (float)updateDrawTime;    // Framerate could be variable

        previousTime = currentTime;
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
