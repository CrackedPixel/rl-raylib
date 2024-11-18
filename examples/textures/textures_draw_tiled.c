/*******************************************************************************************
*
*   raylib [textures] example - Draw part of the texture tiled
*
*   Example originally created with raylib 3.0, last time updated with raylib 4.2
*
*   Example contributed by Vlad Adrian (@demizdor) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2020-2024 Vlad Adrian (@demizdor) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define SIZEOF(A) (sizeof(A)/sizeof(A[0]))
#define OPT_WIDTH       220       // Max width for the options container
#define MARGIN_SIZE       8       // Size for the margins
#define COLOR_SIZE       16       // Size of the color select buttons

// Draw part of a texture (defined by a rectangle) with rotation and scale tiled into dest.
void DrawTextureTiled(RL_Texture2D texture, RL_Rectangle source, RL_Rectangle dest, RL_Vector2 origin, float rotation, float scale, RL_Color tint);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_SetConfigFlags(FLAG_WINDOW_RESIZABLE); // Make the window resizable
    RL_InitWindow(screenWidth, screenHeight, "raylib [textures] example - Draw part of a texture tiled");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    RL_Texture texPattern = RL_LoadTexture("resources/patterns.png");
    RL_SetTextureFilter(texPattern, TEXTURE_FILTER_TRILINEAR); // Makes the texture smoother when upscaled

    // Coordinates for all patterns inside the texture
    const RL_Rectangle recPattern[] = {
        (RL_Rectangle){ 3, 3, 66, 66 },
        (RL_Rectangle){ 75, 3, 100, 100 },
        (RL_Rectangle){ 3, 75, 66, 66 },
        (RL_Rectangle){ 7, 156, 50, 50 },
        (RL_Rectangle){ 85, 106, 90, 45 },
        (RL_Rectangle){ 75, 154, 100, 60}
    };

    // Setup colors
    const RL_Color colors[] = { RL_BLACK, RL_MAROON, RL_ORANGE, RL_BLUE, RL_PURPLE, RL_BEIGE, RL_LIME, RL_RED, RL_DARKGRAY, RL_SKYBLUE };
    enum { MAX_COLORS = SIZEOF(colors) };
    RL_Rectangle colorRec[MAX_COLORS] = { 0 };

    // Calculate rectangle for each color
    for (int i = 0, x = 0, y = 0; i < MAX_COLORS; i++)
    {
        colorRec[i].x = 2.0f + MARGIN_SIZE + x;
        colorRec[i].y = 22.0f + 256.0f + MARGIN_SIZE + y;
        colorRec[i].width = COLOR_SIZE*2.0f;
        colorRec[i].height = (float)COLOR_SIZE;

        if (i == (MAX_COLORS/2 - 1))
        {
            x = 0;
            y += COLOR_SIZE + MARGIN_SIZE;
        }
        else x += (COLOR_SIZE*2 + MARGIN_SIZE);
    }

    int activePattern = 0, activeCol = 0;
    float scale = 1.0f, rotation = 0.0f;

    RL_SetTargetFPS(60);
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Handle mouse
        if (RL_IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            const RL_Vector2 mouse = RL_GetMousePosition();

            // Check which pattern was clicked and set it as the active pattern
            for (int i = 0; i < SIZEOF(recPattern); i++)
            {
                if (RL_CheckCollisionPointRec(mouse, (RL_Rectangle){ 2 + MARGIN_SIZE + recPattern[i].x, 40 + MARGIN_SIZE + recPattern[i].y, recPattern[i].width, recPattern[i].height }))
                {
                    activePattern = i;
                    break;
                }
            }

            // Check to see which color was clicked and set it as the active color
            for (int i = 0; i < MAX_COLORS; ++i)
            {
                if (RL_CheckCollisionPointRec(mouse, colorRec[i]))
                {
                    activeCol = i;
                    break;
                }
            }
        }

        // Handle keys

        // Change scale
        if (RL_IsKeyPressed(KEY_UP)) scale += 0.25f;
        if (RL_IsKeyPressed(KEY_DOWN)) scale -= 0.25f;
        if (scale > 10.0f) scale = 10.0f;
        else if ( scale <= 0.0f) scale = 0.25f;

        // Change rotation
        if (RL_IsKeyPressed(KEY_LEFT)) rotation -= 25.0f;
        if (RL_IsKeyPressed(KEY_RIGHT)) rotation += 25.0f;

        // Reset
        if (RL_IsKeyPressed(KEY_SPACE)) { rotation = 0.0f; scale = 1.0f; }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();
            RL_ClearBackground(RL_RAYWHITE);

            // Draw the tiled area
            DrawTextureTiled(texPattern, recPattern[activePattern], (RL_Rectangle){(float)OPT_WIDTH+MARGIN_SIZE, (float)MARGIN_SIZE, RL_GetScreenWidth() - OPT_WIDTH - 2.0f*MARGIN_SIZE, RL_GetScreenHeight() - 2.0f*MARGIN_SIZE},
                (RL_Vector2){0.0f, 0.0f}, rotation, scale, colors[activeCol]);

            // Draw options
            RL_DrawRectangle(MARGIN_SIZE, MARGIN_SIZE, OPT_WIDTH - MARGIN_SIZE, RL_GetScreenHeight() - 2*MARGIN_SIZE, RL_ColorAlpha(RL_LIGHTGRAY, 0.5f));

            RL_DrawText("Select Pattern", 2 + MARGIN_SIZE, 30 + MARGIN_SIZE, 10, RL_BLACK);
            RL_DrawTexture(texPattern, 2 + MARGIN_SIZE, 40 + MARGIN_SIZE, RL_BLACK);
            RL_DrawRectangle(2 + MARGIN_SIZE + (int)recPattern[activePattern].x, 40 + MARGIN_SIZE + (int)recPattern[activePattern].y, (int)recPattern[activePattern].width, (int)recPattern[activePattern].height, RL_ColorAlpha(RL_DARKBLUE, 0.3f));

            RL_DrawText("Select RL_Color", 2+MARGIN_SIZE, 10+256+MARGIN_SIZE, 10, RL_BLACK);
            for (int i = 0; i < MAX_COLORS; i++)
            {
                RL_DrawRectangleRec(colorRec[i], colors[i]);
                if (activeCol == i) RL_DrawRectangleLinesEx(colorRec[i], 3, RL_ColorAlpha(RL_WHITE, 0.5f));
            }

            RL_DrawText("Scale (UP/DOWN to change)", 2 + MARGIN_SIZE, 80 + 256 + MARGIN_SIZE, 10, RL_BLACK);
            RL_DrawText(RL_TextFormat("%.2fx", scale), 2 + MARGIN_SIZE, 92 + 256 + MARGIN_SIZE, 20, RL_BLACK);

            RL_DrawText("Rotation (LEFT/RIGHT to change)", 2 + MARGIN_SIZE, 122 + 256 + MARGIN_SIZE, 10, RL_BLACK);
            RL_DrawText(RL_TextFormat("%.0f degrees", rotation), 2 + MARGIN_SIZE, 134 + 256 + MARGIN_SIZE, 20, RL_BLACK);

            RL_DrawText("Press [SPACE] to reset", 2 + MARGIN_SIZE, 164 + 256 + MARGIN_SIZE, 10, RL_DARKBLUE);

            // Draw FPS
            RL_DrawText(RL_TextFormat("%i FPS", RL_GetFPS()), 2 + MARGIN_SIZE, 2 + MARGIN_SIZE, 20, RL_BLACK);
        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(texPattern);        // Unload texture

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Draw part of a texture (defined by a rectangle) with rotation and scale tiled into dest.
void DrawTextureTiled(RL_Texture2D texture, RL_Rectangle source, RL_Rectangle dest, RL_Vector2 origin, float rotation, float scale, RL_Color tint)
{
    if ((texture.id <= 0) || (scale <= 0.0f)) return;  // Wanna see a infinite loop?!...just delete this line!
    if ((source.width == 0) || (source.height == 0)) return;

    int tileWidth = (int)(source.width*scale), tileHeight = (int)(source.height*scale);
    if ((dest.width < tileWidth) && (dest.height < tileHeight))
    {
        // Can fit only one tile
        RL_DrawTexturePro(texture, (RL_Rectangle){source.x, source.y, ((float)dest.width/tileWidth)*source.width, ((float)dest.height/tileHeight)*source.height},
                    (RL_Rectangle){dest.x, dest.y, dest.width, dest.height}, origin, rotation, tint);
    }
    else if (dest.width <= tileWidth)
    {
        // Tiled vertically (one column)
        int dy = 0;
        for (;dy+tileHeight < dest.height; dy += tileHeight)
        {
            RL_DrawTexturePro(texture, (RL_Rectangle){source.x, source.y, ((float)dest.width/tileWidth)*source.width, source.height}, (RL_Rectangle){dest.x, dest.y + dy, dest.width, (float)tileHeight}, origin, rotation, tint);
        }

        // Fit last tile
        if (dy < dest.height)
        {
            RL_DrawTexturePro(texture, (RL_Rectangle){source.x, source.y, ((float)dest.width/tileWidth)*source.width, ((float)(dest.height - dy)/tileHeight)*source.height},
                        (RL_Rectangle){dest.x, dest.y + dy, dest.width, dest.height - dy}, origin, rotation, tint);
        }
    }
    else if (dest.height <= tileHeight)
    {
        // Tiled horizontally (one row)
        int dx = 0;
        for (;dx+tileWidth < dest.width; dx += tileWidth)
        {
            RL_DrawTexturePro(texture, (RL_Rectangle){source.x, source.y, source.width, ((float)dest.height/tileHeight)*source.height}, (RL_Rectangle){dest.x + dx, dest.y, (float)tileWidth, dest.height}, origin, rotation, tint);
        }

        // Fit last tile
        if (dx < dest.width)
        {
            RL_DrawTexturePro(texture, (RL_Rectangle){source.x, source.y, ((float)(dest.width - dx)/tileWidth)*source.width, ((float)dest.height/tileHeight)*source.height},
                        (RL_Rectangle){dest.x + dx, dest.y, dest.width - dx, dest.height}, origin, rotation, tint);
        }
    }
    else
    {
        // Tiled both horizontally and vertically (rows and columns)
        int dx = 0;
        for (;dx+tileWidth < dest.width; dx += tileWidth)
        {
            int dy = 0;
            for (;dy+tileHeight < dest.height; dy += tileHeight)
            {
                RL_DrawTexturePro(texture, source, (RL_Rectangle){dest.x + dx, dest.y + dy, (float)tileWidth, (float)tileHeight}, origin, rotation, tint);
            }

            if (dy < dest.height)
            {
                RL_DrawTexturePro(texture, (RL_Rectangle){source.x, source.y, source.width, ((float)(dest.height - dy)/tileHeight)*source.height},
                    (RL_Rectangle){dest.x + dx, dest.y + dy, (float)tileWidth, dest.height - dy}, origin, rotation, tint);
            }
        }

        // Fit last column of tiles
        if (dx < dest.width)
        {
            int dy = 0;
            for (;dy+tileHeight < dest.height; dy += tileHeight)
            {
                RL_DrawTexturePro(texture, (RL_Rectangle){source.x, source.y, ((float)(dest.width - dx)/tileWidth)*source.width, source.height},
                        (RL_Rectangle){dest.x + dx, dest.y + dy, dest.width - dx, (float)tileHeight}, origin, rotation, tint);
            }

            // Draw final tile in the bottom right corner
            if (dy < dest.height)
            {
                RL_DrawTexturePro(texture, (RL_Rectangle){source.x, source.y, ((float)(dest.width - dx)/tileWidth)*source.width, ((float)(dest.height - dy)/tileHeight)*source.height},
                    (RL_Rectangle){dest.x + dx, dest.y + dy, dest.width - dx, dest.height - dy}, origin, rotation, tint);
            }
        }
    }
}
