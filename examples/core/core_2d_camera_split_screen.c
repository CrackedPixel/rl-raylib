/*******************************************************************************************
*
*   raylib [core] example - 2d camera split screen
*
*   Addapted from the core_3d_camera_split_screen example: 
*       https://github.com/raysan5/raylib/blob/master/examples/core/core_3d_camera_split_screen.c
*
*   Example originally created with raylib 4.5, last time updated with raylib 4.5
*
*   Example contributed by Gabriel dos Santos Sanches (@gabrielssanches) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023 Gabriel dos Santos Sanches (@gabrielssanches)
*
********************************************************************************************/

#include "raylib.h"

#define PLAYER_SIZE 40

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 440;

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera split screen");

    RL_Rectangle player1 = { 200, 200, PLAYER_SIZE, PLAYER_SIZE };
    RL_Rectangle player2 = { 250, 200, PLAYER_SIZE, PLAYER_SIZE };

    RL_Camera2D camera1 = { 0 };
    camera1.target = (RL_Vector2){ player1.x, player1.y };
    camera1.offset = (RL_Vector2){ 200.0f, 200.0f };
    camera1.rotation = 0.0f;
    camera1.zoom = 1.0f;

    RL_Camera2D camera2 = { 0 };
    camera2.target = (RL_Vector2){ player2.x, player2.y };
    camera2.offset = (RL_Vector2){ 200.0f, 200.0f };
    camera2.rotation = 0.0f;
    camera2.zoom = 1.0f;

    RL_RenderTexture screenCamera1 = RL_LoadRenderTexture(screenWidth/2, screenHeight);
    RL_RenderTexture screenCamera2 = RL_LoadRenderTexture(screenWidth/2, screenHeight);

    // Build a flipped rectangle the size of the split view to use for drawing later
    RL_Rectangle splitScreenRect = { 0.0f, 0.0f, (float)screenCamera1.texture.width, (float)-screenCamera1.texture.height };

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsKeyDown(KEY_S)) player1.y += 3.0f;
        else if (RL_IsKeyDown(KEY_W)) player1.y -= 3.0f;
        if (RL_IsKeyDown(KEY_D)) player1.x += 3.0f;
        else if (RL_IsKeyDown(KEY_A)) player1.x -= 3.0f;

        if (RL_IsKeyDown(KEY_UP)) player2.y -= 3.0f;
        else if (RL_IsKeyDown(KEY_DOWN)) player2.y += 3.0f;
        if (RL_IsKeyDown(KEY_RIGHT)) player2.x += 3.0f;
        else if (RL_IsKeyDown(KEY_LEFT)) player2.x -= 3.0f;

        camera1.target = (RL_Vector2){ player1.x, player1.y };
        camera2.target = (RL_Vector2){ player2.x, player2.y };
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginTextureMode(screenCamera1);
            RL_ClearBackground(RL_RAYWHITE);
            
            RL_BeginMode2D(camera1);
            
                // Draw full scene with first camera
                for (int i = 0; i < screenWidth/PLAYER_SIZE + 1; i++)
                {
                    RL_DrawLineV((RL_Vector2){(float)PLAYER_SIZE*i, 0}, (RL_Vector2){ (float)PLAYER_SIZE*i, (float)screenHeight}, RL_LIGHTGRAY);
                }

                for (int i = 0; i < screenHeight/PLAYER_SIZE + 1; i++)
                {
                    RL_DrawLineV((RL_Vector2){0, (float)PLAYER_SIZE*i}, (RL_Vector2){ (float)screenWidth, (float)PLAYER_SIZE*i}, RL_LIGHTGRAY);
                }

                for (int i = 0; i < screenWidth/PLAYER_SIZE; i++)
                {
                    for (int j = 0; j < screenHeight/PLAYER_SIZE; j++)
                    {
                        RL_DrawText(RL_TextFormat("[%i,%i]", i, j), 10 + PLAYER_SIZE*i, 15 + PLAYER_SIZE*j, 10, RL_LIGHTGRAY);
                    }
                }

                RL_DrawRectangleRec(player1, RL_RED);
                RL_DrawRectangleRec(player2, RL_BLUE);
            RL_EndMode2D();
            
            RL_DrawRectangle(0, 0, RL_GetScreenWidth()/2, 30, RL_Fade(RL_RAYWHITE, 0.6f));
            RL_DrawText("PLAYER1: W/S/A/D to move", 10, 10, 10, RL_MAROON);
            
        RL_EndTextureMode();

        RL_BeginTextureMode(screenCamera2);
            RL_ClearBackground(RL_RAYWHITE);
            
            RL_BeginMode2D(camera2);
            
                // Draw full scene with second camera
                for (int i = 0; i < screenWidth/PLAYER_SIZE + 1; i++)
                {
                    RL_DrawLineV((RL_Vector2){ (float)PLAYER_SIZE*i, 0}, (RL_Vector2){ (float)PLAYER_SIZE*i, (float)screenHeight}, RL_LIGHTGRAY);
                }

                for (int i = 0; i < screenHeight/PLAYER_SIZE + 1; i++)
                {
                    RL_DrawLineV((RL_Vector2){0, (float)PLAYER_SIZE*i}, (RL_Vector2){ (float)screenWidth, (float)PLAYER_SIZE*i}, RL_LIGHTGRAY);
                }

                for (int i = 0; i < screenWidth/PLAYER_SIZE; i++)
                {
                    for (int j = 0; j < screenHeight/PLAYER_SIZE; j++)
                    {
                        RL_DrawText(RL_TextFormat("[%i,%i]", i, j), 10 + PLAYER_SIZE*i, 15 + PLAYER_SIZE*j, 10, RL_LIGHTGRAY);
                    }
                }

                RL_DrawRectangleRec(player1, RL_RED);
                RL_DrawRectangleRec(player2, RL_BLUE);
                
            RL_EndMode2D();
            
            RL_DrawRectangle(0, 0, RL_GetScreenWidth()/2, 30, RL_Fade(RL_RAYWHITE, 0.6f));
            RL_DrawText("PLAYER2: UP/DOWN/LEFT/RIGHT to move", 10, 10, 10, RL_DARKBLUE);
            
        RL_EndTextureMode();

        // Draw both views render textures to the screen side by side
        RL_BeginDrawing();
            RL_ClearBackground(RL_BLACK);
            
            RL_DrawTextureRec(screenCamera1.texture, splitScreenRect, (RL_Vector2){ 0, 0 }, RL_WHITE);
            RL_DrawTextureRec(screenCamera2.texture, splitScreenRect, (RL_Vector2){ screenWidth/2.0f, 0 }, RL_WHITE);
            
            RL_DrawRectangle(RL_GetScreenWidth()/2 - 2, 0, 4, RL_GetScreenHeight(), RL_LIGHTGRAY);
        RL_EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadRenderTexture(screenCamera1); // Unload render texture
    RL_UnloadRenderTexture(screenCamera2); // Unload render texture

    RL_CloseWindow();                      // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
