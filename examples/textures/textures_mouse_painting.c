/*******************************************************************************************
*
*   raylib [textures] example - Mouse painting
*
*   Example originally created with raylib 3.0, last time updated with raylib 3.0
*
*   Example contributed by Chris Dill (@MysteriousSpace) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Chris Dill (@MysteriousSpace) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define MAX_COLORS_COUNT    23          // Number of colors available

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [textures] example - mouse painting");

    // Colors to choose from
    RL_Color colors[MAX_COLORS_COUNT] = {
        RL_RAYWHITE, RL_YELLOW, RL_GOLD, RL_ORANGE, RL_PINK, RL_RED, RL_MAROON, RL_GREEN, RL_LIME, RL_DARKGREEN,
        RL_SKYBLUE, RL_BLUE, RL_DARKBLUE, RL_PURPLE, RL_VIOLET, RL_DARKPURPLE, RL_BEIGE, RL_BROWN, RL_DARKBROWN,
        RL_LIGHTGRAY, RL_GRAY, RL_DARKGRAY, RL_BLACK };

    // Define colorsRecs data (for every rectangle)
    RL_Rectangle colorsRecs[MAX_COLORS_COUNT] = { 0 };

    for (int i = 0; i < MAX_COLORS_COUNT; i++)
    {
        colorsRecs[i].x = 10 + 30.0f*i + 2*i;
        colorsRecs[i].y = 10;
        colorsRecs[i].width = 30;
        colorsRecs[i].height = 30;
    }

    int colorSelected = 0;
    int colorSelectedPrev = colorSelected;
    int colorMouseHover = 0;
    float brushSize = 20.0f;
    bool mouseWasPressed = false;

    RL_Rectangle btnSaveRec = { 750, 10, 40, 30 };
    bool btnSaveMouseHover = false;
    bool showSaveMessage = false;
    int saveMessageCounter = 0;

    // Create a RL_RenderTexture2D to use as a canvas
    RL_RenderTexture2D target = RL_LoadRenderTexture(screenWidth, screenHeight);

    // Clear render texture before entering the game loop
    RL_BeginTextureMode(target);
    RL_ClearBackground(colors[0]);
    RL_EndTextureMode();

    RL_SetTargetFPS(120);              // Set our game to run at 120 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_Vector2 mousePos = RL_GetMousePosition();

        // Move between colors with keys
        if (RL_IsKeyPressed(KEY_RIGHT)) colorSelected++;
        else if (RL_IsKeyPressed(KEY_LEFT)) colorSelected--;

        if (colorSelected >= MAX_COLORS_COUNT) colorSelected = MAX_COLORS_COUNT - 1;
        else if (colorSelected < 0) colorSelected = 0;

        // Choose color with mouse
        for (int i = 0; i < MAX_COLORS_COUNT; i++)
        {
            if (RL_CheckCollisionPointRec(mousePos, colorsRecs[i]))
            {
                colorMouseHover = i;
                break;
            }
            else colorMouseHover = -1;
        }

        if ((colorMouseHover >= 0) && RL_IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            colorSelected = colorMouseHover;
            colorSelectedPrev = colorSelected;
        }

        // Change brush size
        brushSize += RL_GetMouseWheelMove()*5;
        if (brushSize < 2) brushSize = 2;
        if (brushSize > 50) brushSize = 50;

        if (RL_IsKeyPressed(KEY_C))
        {
            // Clear render texture to clear color
            RL_BeginTextureMode(target);
            RL_ClearBackground(colors[0]);
            RL_EndTextureMode();
        }

        if (RL_IsMouseButtonDown(MOUSE_BUTTON_LEFT) || (RL_GetGestureDetected() == GESTURE_DRAG))
        {
            // Paint circle into render texture
            // NOTE: To avoid discontinuous circles, we could store
            // previous-next mouse points and just draw a line using brush size
            RL_BeginTextureMode(target);
            if (mousePos.y > 50) RL_DrawCircle((int)mousePos.x, (int)mousePos.y, brushSize, colors[colorSelected]);
            RL_EndTextureMode();
        }

        if (RL_IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            if (!mouseWasPressed)
            {
                colorSelectedPrev = colorSelected;
                colorSelected = 0;
            }

            mouseWasPressed = true;

            // Erase circle from render texture
            RL_BeginTextureMode(target);
            if (mousePos.y > 50) RL_DrawCircle((int)mousePos.x, (int)mousePos.y, brushSize, colors[0]);
            RL_EndTextureMode();
        }
        else if (RL_IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && mouseWasPressed)
        {
            colorSelected = colorSelectedPrev;
            mouseWasPressed = false;
        }

        // Check mouse hover save button
        if (RL_CheckCollisionPointRec(mousePos, btnSaveRec)) btnSaveMouseHover = true;
        else btnSaveMouseHover = false;

        // RL_Image saving logic
        // NOTE: Saving painted texture to a default named image
        if ((btnSaveMouseHover && RL_IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) || RL_IsKeyPressed(KEY_S))
        {
            RL_Image image = RL_LoadImageFromTexture(target.texture);
            RL_ImageFlipVertical(&image);
            RL_ExportImage(image, "my_amazing_texture_painting.png");
            RL_UnloadImage(image);
            showSaveMessage = true;
        }

        if (showSaveMessage)
        {
            // On saving, show a full screen message for 2 seconds
            saveMessageCounter++;
            if (saveMessageCounter > 240)
            {
                showSaveMessage = false;
                saveMessageCounter = 0;
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

        RL_ClearBackground(RL_RAYWHITE);

        // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
        RL_DrawTextureRec(target.texture, (RL_Rectangle) { 0, 0, (float)target.texture.width, (float)-target.texture.height }, (RL_Vector2) { 0, 0 }, RL_WHITE);

        // Draw drawing circle for reference
        if (mousePos.y > 50)
        {
            if (RL_IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) RL_DrawCircleLines((int)mousePos.x, (int)mousePos.y, brushSize, RL_GRAY);
            else RL_DrawCircle(RL_GetMouseX(), RL_GetMouseY(), brushSize, colors[colorSelected]);
        }

        // Draw top panel
        RL_DrawRectangle(0, 0, RL_GetScreenWidth(), 50, RL_RAYWHITE);
        RL_DrawLine(0, 50, RL_GetScreenWidth(), 50, RL_LIGHTGRAY);

        // Draw color selection rectangles
        for (int i = 0; i < MAX_COLORS_COUNT; i++) RL_DrawRectangleRec(colorsRecs[i], colors[i]);
        RL_DrawRectangleLines(10, 10, 30, 30, RL_LIGHTGRAY);

        if (colorMouseHover >= 0) RL_DrawRectangleRec(colorsRecs[colorMouseHover], RL_Fade(RL_WHITE, 0.6f));

        RL_DrawRectangleLinesEx((RL_Rectangle){ colorsRecs[colorSelected].x - 2, colorsRecs[colorSelected].y - 2,
                             colorsRecs[colorSelected].width + 4, colorsRecs[colorSelected].height + 4 }, 2, RL_BLACK);

        // Draw save image button
        RL_DrawRectangleLinesEx(btnSaveRec, 2, btnSaveMouseHover ? RL_RED : RL_BLACK);
        RL_DrawText("SAVE!", 755, 20, 10, btnSaveMouseHover ? RL_RED : RL_BLACK);

        // Draw save image message
        if (showSaveMessage)
        {
            RL_DrawRectangle(0, 0, RL_GetScreenWidth(), RL_GetScreenHeight(), RL_Fade(RL_RAYWHITE, 0.8f));
            RL_DrawRectangle(0, 150, RL_GetScreenWidth(), 80, RL_BLACK);
            RL_DrawText("IMAGE SAVED:  my_amazing_texture_painting.png", 150, 180, 20, RL_RAYWHITE);
        }

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadRenderTexture(target);    // Unload render texture

    RL_CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
