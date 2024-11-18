/*******************************************************************************************
*
*   raylib [text] example - RL_Rectangle bounds
*
*   Example originally created with raylib 2.5, last time updated with raylib 4.0
*
*   Example contributed by Vlad Adrian (@demizdor) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2024 Vlad Adrian (@demizdor) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

static void DrawTextBoxed(RL_Font font, const char *text, RL_Rectangle rec, float fontSize, float spacing, bool wordWrap, RL_Color tint);   // Draw text using font inside rectangle limits
static void DrawTextBoxedSelectable(RL_Font font, const char *text, RL_Rectangle rec, float fontSize, float spacing, bool wordWrap, RL_Color tint, int selectStart, int selectLength, RL_Color selectTint, RL_Color selectBackTint);    // Draw text using font inside rectangle limits with support for text selection

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [text] example - draw text inside a rectangle");

    const char text[] = "Text cannot escape\tthis container\t...word wrap also works when active so here's \
a long text for testing.\n\nLorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod \
tempor incididunt ut labore et dolore magna aliqua. Nec ullamcorper sit amet risus nullam eget felis eget.";

    bool resizing = false;
    bool wordWrap = true;

    RL_Rectangle container = { 25.0f, 25.0f, screenWidth - 50.0f, screenHeight - 250.0f };
    RL_Rectangle resizer = { container.x + container.width - 17, container.y + container.height - 17, 14, 14 };

    // Minimum width and heigh for the container rectangle
    const float minWidth = 60;
    const float minHeight = 60;
    const float maxWidth = screenWidth - 50.0f;
    const float maxHeight = screenHeight - 160.0f;

    RL_Vector2 lastMouse = { 0.0f, 0.0f }; // Stores last mouse coordinates
    RL_Color borderColor = RL_MAROON;         // Container border color
    RL_Font font = RL_GetFontDefault();       // Get default system font

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsKeyPressed(KEY_SPACE)) wordWrap = !wordWrap;

        RL_Vector2 mouse = RL_GetMousePosition();

        // Check if the mouse is inside the container and toggle border color
        if (RL_CheckCollisionPointRec(mouse, container)) borderColor = RL_Fade(RL_MAROON, 0.4f);
        else if (!resizing) borderColor = RL_MAROON;

        // Container resizing logic
        if (resizing)
        {
            if (RL_IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) resizing = false;

            float width = container.width + (mouse.x - lastMouse.x);
            container.width = (width > minWidth)? ((width < maxWidth)? width : maxWidth) : minWidth;

            float height = container.height + (mouse.y - lastMouse.y);
            container.height = (height > minHeight)? ((height < maxHeight)? height : maxHeight) : minHeight;
        }
        else
        {
            // Check if we're resizing
            if (RL_IsMouseButtonDown(MOUSE_BUTTON_LEFT) && RL_CheckCollisionPointRec(mouse, resizer)) resizing = true;
        }

        // Move resizer rectangle properly
        resizer.x = container.x + container.width - 17;
        resizer.y = container.y + container.height - 17;

        lastMouse = mouse; // Update mouse
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawRectangleLinesEx(container, 3, borderColor);    // Draw container border

            // Draw text in container (add some padding)
            DrawTextBoxed(font, text, (RL_Rectangle){ container.x + 4, container.y + 4, container.width - 4, container.height - 4 }, 20.0f, 2.0f, wordWrap, RL_GRAY);

            RL_DrawRectangleRec(resizer, borderColor);             // Draw the resize box

            // Draw bottom info
            RL_DrawRectangle(0, screenHeight - 54, screenWidth, 54, RL_GRAY);
            RL_DrawRectangleRec((RL_Rectangle){ 382.0f, screenHeight - 34.0f, 12.0f, 12.0f }, RL_MAROON);

            RL_DrawText("Word Wrap: ", 313, screenHeight-115, 20, RL_BLACK);
            if (wordWrap) RL_DrawText("ON", 447, screenHeight - 115, 20, RL_RED);
            else RL_DrawText("OFF", 447, screenHeight - 115, 20, RL_BLACK);

            RL_DrawText("Press [SPACE] to toggle word wrap", 218, screenHeight - 86, 20, RL_GRAY);

            RL_DrawText("Click hold & drag the    to resize the container", 155, screenHeight - 38, 20, RL_RAYWHITE);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//--------------------------------------------------------------------------------------
// Module functions definition
//--------------------------------------------------------------------------------------

// Draw text using font inside rectangle limits
static void DrawTextBoxed(RL_Font font, const char *text, RL_Rectangle rec, float fontSize, float spacing, bool wordWrap, RL_Color tint)
{
    DrawTextBoxedSelectable(font, text, rec, fontSize, spacing, wordWrap, tint, 0, 0, RL_WHITE, RL_WHITE);
}

// Draw text using font inside rectangle limits with support for text selection
static void DrawTextBoxedSelectable(RL_Font font, const char *text, RL_Rectangle rec, float fontSize, float spacing, bool wordWrap, RL_Color tint, int selectStart, int selectLength, RL_Color selectTint, RL_Color selectBackTint)
{
    int length = RL_TextLength(text);  // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0;          // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    float scaleFactor = fontSize/(float)font.baseSize;     // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap? MEASURE_STATE : DRAW_STATE;

    int startLine = -1;         // Index where to begin drawing (where a line begins)
    int endLine = -1;           // Index where to stop drawing (where a line ends)
    int lastk = -1;             // Holds last value of the character position

    for (int i = 0, k = 0; i < length; i++, k++)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = RL_GetCodepoint(&text[i], &codepointByteCount);
        int index = RL_GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n')
        {
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;

            if (i + 1 < length) glyphWidth = glyphWidth + spacing;
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again recursively until the end of the text (or until we get outside of the container).
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container.
        if (state == MEASURE_STATE)
        {
            // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth) > rec.width)
            {
                endLine = (endLine < 1)? i : endLine;
                if (i == endLine) endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n') state = !state;

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        }
        else
        {
            if (codepoint == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width))
                {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize*scaleFactor) > rec.height) break;

                // Draw selection background
                bool isGlyphSelected = false;
                if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength)))
                {
                    RL_DrawRectangleRec((RL_Rectangle){ rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize*scaleFactor }, selectBackTint);
                    isGlyphSelected = true;
                }

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                    RL_DrawTextCodepoint(font, codepoint, (RL_Vector2){ rec.x + textOffsetX, rec.y + textOffsetY }, fontSize, isGlyphSelected? selectTint : tint);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' ')) textOffsetX += glyphWidth;  // avoid leading spaces
    }
}
