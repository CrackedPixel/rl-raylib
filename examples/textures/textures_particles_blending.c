/*******************************************************************************************
*
*   raylib example - particles blending
*
*   Example originally created with raylib 1.7, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_PARTICLES 200

// Particle structure with basic data
typedef struct {
    RL_Vector2 position;
    RL_Color color;
    float alpha;
    float size;
    float rotation;
    bool active;        // NOTE: Use it to activate/deactive particle
} Particle;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [textures] example - particles blending");

    // Particles pool, reuse them!
    Particle mouseTail[MAX_PARTICLES] = { 0 };

    // Initialize particles
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        mouseTail[i].position = (RL_Vector2){ 0, 0 };
        mouseTail[i].color = (RL_Color){ RL_GetRandomValue(0, 255), RL_GetRandomValue(0, 255), RL_GetRandomValue(0, 255), 255 };
        mouseTail[i].alpha = 1.0f;
        mouseTail[i].size = (float)RL_GetRandomValue(1, 30)/20.0f;
        mouseTail[i].rotation = (float)RL_GetRandomValue(0, 360);
        mouseTail[i].active = false;
    }

    float gravity = 3.0f;

    RL_Texture2D smoke = RL_LoadTexture("resources/spark_flame.png");

    int blending = BLEND_ALPHA;

    RL_SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        // Activate one particle every frame and Update active particles
        // NOTE: Particles initial position should be mouse position when activated
        // NOTE: Particles fall down with gravity and rotation... and disappear after 2 seconds (alpha = 0)
        // NOTE: When a particle disappears, active = false and it can be reused.
        for (int i = 0; i < MAX_PARTICLES; i++)
        {
            if (!mouseTail[i].active)
            {
                mouseTail[i].active = true;
                mouseTail[i].alpha = 1.0f;
                mouseTail[i].position = RL_GetMousePosition();
                i = MAX_PARTICLES;
            }
        }

        for (int i = 0; i < MAX_PARTICLES; i++)
        {
            if (mouseTail[i].active)
            {
                mouseTail[i].position.y += gravity/2;
                mouseTail[i].alpha -= 0.005f;

                if (mouseTail[i].alpha <= 0.0f) mouseTail[i].active = false;

                mouseTail[i].rotation += 2.0f;
            }
        }

        if (RL_IsKeyPressed(KEY_SPACE))
        {
            if (blending == BLEND_ALPHA) blending = BLEND_ADDITIVE;
            else blending = BLEND_ALPHA;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_DARKGRAY);

            RL_BeginBlendMode(blending);

                // Draw active particles
                for (int i = 0; i < MAX_PARTICLES; i++)
                {
                    if (mouseTail[i].active) RL_DrawTexturePro(smoke, (RL_Rectangle){ 0.0f, 0.0f, (float)smoke.width, (float)smoke.height },
                                                           (RL_Rectangle){ mouseTail[i].position.x, mouseTail[i].position.y, smoke.width*mouseTail[i].size, smoke.height*mouseTail[i].size },
                                                           (RL_Vector2){ (float)(smoke.width*mouseTail[i].size/2.0f), (float)(smoke.height*mouseTail[i].size/2.0f) }, mouseTail[i].rotation,
                                                           RL_Fade(mouseTail[i].color, mouseTail[i].alpha));
                }

            RL_EndBlendMode();

            RL_DrawText("PRESS SPACE to CHANGE BLENDING MODE", 180, 20, 20, RL_BLACK);

            if (blending == BLEND_ALPHA) RL_DrawText("ALPHA BLENDING", 290, screenHeight - 40, 20, RL_BLACK);
            else RL_DrawText("ADDITIVE BLENDING", 280, screenHeight - 40, 20, RL_RAYWHITE);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(smoke);

    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}