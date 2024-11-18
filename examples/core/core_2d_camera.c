/*******************************************************************************************
*
*   raylib [core] example - 2D RL_Camera system
*
*   Example originally created with raylib 1.5, last time updated with raylib 3.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2016-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_BUILDINGS   100

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");

    RL_Rectangle player = { 400, 280, 40, 40 };
    RL_Rectangle buildings[MAX_BUILDINGS] = { 0 };
    RL_Color buildColors[MAX_BUILDINGS] = { 0 };

    int spacing = 0;

    for (int i = 0; i < MAX_BUILDINGS; i++)
    {
        buildings[i].width = (float)RL_GetRandomValue(50, 200);
        buildings[i].height = (float)RL_GetRandomValue(100, 800);
        buildings[i].y = screenHeight - 130.0f - buildings[i].height;
        buildings[i].x = -6000.0f + spacing;

        spacing += (int)buildings[i].width;

        buildColors[i] = (RL_Color){ RL_GetRandomValue(200, 240), RL_GetRandomValue(200, 240), RL_GetRandomValue(200, 250), 255 };
    }

    RL_Camera2D camera = { 0 };
    camera.target = (RL_Vector2){ player.x + 20.0f, player.y + 20.0f };
    camera.offset = (RL_Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Player movement
        if (RL_IsKeyDown(KEY_RIGHT)) player.x += 2;
        else if (RL_IsKeyDown(KEY_LEFT)) player.x -= 2;

        // RL_Camera target follows player
        camera.target = (RL_Vector2){ player.x + 20, player.y + 20 };

        // RL_Camera rotation controls
        if (RL_IsKeyDown(KEY_A)) camera.rotation--;
        else if (RL_IsKeyDown(KEY_S)) camera.rotation++;

        // Limit camera rotation to 80 degrees (-40 to 40)
        if (camera.rotation > 40) camera.rotation = 40;
        else if (camera.rotation < -40) camera.rotation = -40;

        // RL_Camera zoom controls
        camera.zoom += ((float)RL_GetMouseWheelMove()*0.05f);

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

        // RL_Camera reset (zoom and rotation)
        if (RL_IsKeyPressed(KEY_R))
        {
            camera.zoom = 1.0f;
            camera.rotation = 0.0f;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode2D(camera);

                RL_DrawRectangle(-6000, 320, 13000, 8000, RL_DARKGRAY);

                for (int i = 0; i < MAX_BUILDINGS; i++) RL_DrawRectangleRec(buildings[i], buildColors[i]);

                RL_DrawRectangleRec(player, RL_RED);

                RL_DrawLine((int)camera.target.x, -screenHeight*10, (int)camera.target.x, screenHeight*10, RL_GREEN);
                RL_DrawLine(-screenWidth*10, (int)camera.target.y, screenWidth*10, (int)camera.target.y, RL_GREEN);

            RL_EndMode2D();

            RL_DrawText("SCREEN AREA", 640, 10, 20, RL_RED);

            RL_DrawRectangle(0, 0, screenWidth, 5, RL_RED);
            RL_DrawRectangle(0, 5, 5, screenHeight - 10, RL_RED);
            RL_DrawRectangle(screenWidth - 5, 5, 5, screenHeight - 10, RL_RED);
            RL_DrawRectangle(0, screenHeight - 5, screenWidth, 5, RL_RED);

            RL_DrawRectangle( 10, 10, 250, 113, RL_Fade(RL_SKYBLUE, 0.5f));
            RL_DrawRectangleLines( 10, 10, 250, 113, RL_BLUE);

            RL_DrawText("Free 2d camera controls:", 20, 20, 10, RL_BLACK);
            RL_DrawText("- Right/Left to move Offset", 40, 40, 10, RL_DARKGRAY);
            RL_DrawText("- Mouse Wheel to Zoom in-out", 40, 60, 10, RL_DARKGRAY);
            RL_DrawText("- A / S to Rotate", 40, 80, 10, RL_DARKGRAY);
            RL_DrawText("- R to reset Zoom and Rotation", 40, 100, 10, RL_DARKGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
