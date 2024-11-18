/*******************************************************************************************
*
*   raylib [text] example - Draw 3d
*
*   NOTE: Draw a 2D text in 3D space, each letter is drawn in a quad (or 2 quads if backface is set)
*   where the texture coodinates of each quad map to the texture coordinates of the glyphs
*   inside the font texture.
*
*   A more efficient approach, i believe, would be to render the text in a render texture and
*   map that texture to a plane and render that, or maybe a shader but my method allows more
*   flexibility...for example to change position of each letter individually to make somethink
*   like a wavy text effect.
*    
*   Special thanks to:
*        @Nighten for the DrawTextStyle() code https://github.com/NightenDushi/Raylib_DrawTextStyle
*        Chris Camacho (codifies - http://bedroomcoders.co.uk/) for the alpha discard shader
*
*   Example originally created with raylib 3.5, last time updated with raylib 4.0
*
*   Example contributed by Vlad Adrian (@demizdor) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2024 Vlad Adrian (@demizdor)
*
********************************************************************************************/

#include "raylib.h"
#include "rlgl.h"

#include <stddef.h>     // Required for: NULL
#include <math.h>       // Required for: sinf()

// To make it work with the older RLGL module just comment the line below
#define RAYLIB_NEW_RLGL

//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
#define LETTER_BOUNDRY_SIZE     0.25f
#define TEXT_MAX_LAYERS         32
#define LETTER_BOUNDRY_COLOR    RL_VIOLET

bool SHOW_LETTER_BOUNDRY = false;
bool SHOW_TEXT_BOUNDRY = false;

//--------------------------------------------------------------------------------------
// Data Types definition
//--------------------------------------------------------------------------------------

// Configuration structure for waving the text
typedef struct WaveTextConfig {
    RL_Vector3 waveRange;
    RL_Vector3 waveSpeed;
    RL_Vector3 waveOffset;
} WaveTextConfig;

//--------------------------------------------------------------------------------------
// Module Functions Declaration
//--------------------------------------------------------------------------------------
// Draw a codepoint in 3D space
static void DrawTextCodepoint3D(RL_Font font, int codepoint, RL_Vector3 position, float fontSize, bool backface, RL_Color tint);
// Draw a 2D text in 3D space
static void DrawText3D(RL_Font font, const char *text, RL_Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, RL_Color tint);
// Measure a text in 3D. For some reason `RL_MeasureTextEx()` just doesn't seem to work so i had to use this instead.
static RL_Vector3 MeasureText3D(RL_Font font, const char *text, float fontSize, float fontSpacing, float lineSpacing);

// Draw a 2D text in 3D space and wave the parts that start with `~~` and end with `~~`.
// This is a modified version of the original code by @Nighten found here https://github.com/NightenDushi/Raylib_DrawTextStyle
static void DrawTextWave3D(RL_Font font, const char *text, RL_Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, WaveTextConfig *config, float time, RL_Color tint);
// Measure a text in 3D ignoring the `~~` chars.
static RL_Vector3 MeasureTextWave3D(RL_Font font, const char *text, float fontSize, float fontSpacing, float lineSpacing);
// Generates a nice color with a random hue
static RL_Color GenerateRandomColor(float s, float v);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_SetConfigFlags(FLAG_MSAA_4X_HINT|FLAG_VSYNC_HINT);
    RL_InitWindow(screenWidth, screenHeight, "raylib [text] example - draw 2D text in 3D");

    bool spin = true;        // Spin the camera?
    bool multicolor = false; // Multicolor mode

    // Define the camera to look into our 3d world
    RL_Camera3D camera = { 0 };
    camera.position = (RL_Vector3){ -10.0f, 15.0f, -10.0f };   // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.0f, 0.0f };          // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };              // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                    // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                 // RL_Camera projection type

    int camera_mode = CAMERA_ORBITAL;

    RL_Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    RL_Vector3 cubeSize = { 2.0f, 2.0f, 2.0f };

    // Use the default font
    RL_Font font = RL_GetFontDefault();
    float fontSize = 8.0f;
    float fontSpacing = 0.5f;
    float lineSpacing = -1.0f;

    // Set the text (using markdown!)
    char text[64] = "Hello ~~World~~ in 3D!";
    RL_Vector3 tbox = {0};
    int layers = 1;
    int quads = 0;
    float layerDistance = 0.01f;

    WaveTextConfig wcfg;
    wcfg.waveSpeed.x = wcfg.waveSpeed.y = 3.0f; wcfg.waveSpeed.z = 0.5f;
    wcfg.waveOffset.x = wcfg.waveOffset.y = wcfg.waveOffset.z = 0.35f;
    wcfg.waveRange.x = wcfg.waveRange.y = wcfg.waveRange.z = 0.45f;

    float time = 0.0f;

    // Setup a light and dark color
    RL_Color light = RL_MAROON;
    RL_Color dark = RL_RED;

    // Load the alpha discard shader
    RL_Shader alphaDiscard = RL_LoadShader(NULL, "resources/shaders/glsl330/alpha_discard.fs");

    // Array filled with multiple random colors (when multicolor mode is set)
    RL_Color multi[TEXT_MAX_LAYERS] = {0};

    RL_DisableCursor();                    // Limit cursor to relative movement inside the window

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, camera_mode);
        
        // Handle font files dropped
        if (RL_IsFileDropped())
        {
            RL_FilePathList droppedFiles = RL_LoadDroppedFiles();

            // NOTE: We only support first ttf file dropped
            if (RL_IsFileExtension(droppedFiles.paths[0], ".ttf"))
            {
                RL_UnloadFont(font);
                font = RL_LoadFontEx(droppedFiles.paths[0], (int)fontSize, 0, 0);
            }
            else if (RL_IsFileExtension(droppedFiles.paths[0], ".fnt"))
            {
                RL_UnloadFont(font);
                font = RL_LoadFont(droppedFiles.paths[0]);
                fontSize = (float)font.baseSize;
            }
            
            RL_UnloadDroppedFiles(droppedFiles);    // Unload filepaths from memory
        }

        // Handle Events
        if (RL_IsKeyPressed(KEY_F1)) SHOW_LETTER_BOUNDRY = !SHOW_LETTER_BOUNDRY;
        if (RL_IsKeyPressed(KEY_F2)) SHOW_TEXT_BOUNDRY = !SHOW_TEXT_BOUNDRY;
        if (RL_IsKeyPressed(KEY_F3))
        {
            // Handle camera change
            spin = !spin;
            // we need to reset the camera when changing modes
            camera = (RL_Camera3D){ 0 };
            camera.target = (RL_Vector3){ 0.0f, 0.0f, 0.0f };          // RL_Camera looking at point
            camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };              // RL_Camera up vector (rotation towards target)
            camera.fovy = 45.0f;                                    // RL_Camera field-of-view Y
            camera.projection = CAMERA_PERSPECTIVE;                 // RL_Camera mode type

            if (spin)
            {
                camera.position = (RL_Vector3){ -10.0f, 15.0f, -10.0f };   // RL_Camera position
                camera_mode = CAMERA_ORBITAL;
            }
            else
            {
                camera.position = (RL_Vector3){ 10.0f, 10.0f, -10.0f };   // RL_Camera position
                camera_mode = CAMERA_FREE;
            }
        }

        // Handle clicking the cube
        if (RL_IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            RL_Ray ray = RL_GetScreenToWorldRay(RL_GetMousePosition(), camera);

            // Check collision between ray and box
            RL_RayCollision collision = RL_GetRayCollisionBox(ray,
                            (RL_BoundingBox){(RL_Vector3){ cubePosition.x - cubeSize.x/2, cubePosition.y - cubeSize.y/2, cubePosition.z - cubeSize.z/2 },
                                          (RL_Vector3){ cubePosition.x + cubeSize.x/2, cubePosition.y + cubeSize.y/2, cubePosition.z + cubeSize.z/2 }});
            if (collision.hit)
            {
                // Generate new random colors
                light = GenerateRandomColor(0.5f, 0.78f);
                dark = GenerateRandomColor(0.4f, 0.58f);
            }
        }

        // Handle text layers changes
        if (RL_IsKeyPressed(KEY_HOME)) { if (layers > 1) --layers; }
        else if (RL_IsKeyPressed(KEY_END)) { if (layers < TEXT_MAX_LAYERS) ++layers; }

        // Handle text changes
        if (RL_IsKeyPressed(KEY_LEFT)) fontSize -= 0.5f;
        else if (RL_IsKeyPressed(KEY_RIGHT)) fontSize += 0.5f;
        else if (RL_IsKeyPressed(KEY_UP)) fontSpacing -= 0.1f;
        else if (RL_IsKeyPressed(KEY_DOWN)) fontSpacing += 0.1f;
        else if (RL_IsKeyPressed(KEY_PAGE_UP)) lineSpacing -= 0.1f;
        else if (RL_IsKeyPressed(KEY_PAGE_DOWN)) lineSpacing += 0.1f;
        else if (RL_IsKeyDown(KEY_INSERT)) layerDistance -= 0.001f;
        else if (RL_IsKeyDown(KEY_DELETE)) layerDistance += 0.001f;
        else if (RL_IsKeyPressed(KEY_TAB))
        {
            multicolor = !multicolor;   // Enable /disable multicolor mode

            if (multicolor)
            {
                // Fill color array with random colors
                for (int i = 0; i < TEXT_MAX_LAYERS; ++i)
                {
                    multi[i] = GenerateRandomColor(0.5f, 0.8f);
                    multi[i].a = RL_GetRandomValue(0, 255);
                }
            }
        }

        // Handle text input
        int ch = RL_GetCharPressed();
        if (RL_IsKeyPressed(KEY_BACKSPACE))
        {
            // Remove last char
            int len = RL_TextLength(text);
            if (len > 0) text[len - 1] = '\0';
        }
        else if (RL_IsKeyPressed(KEY_ENTER))
        {
            // handle newline
            int len = RL_TextLength(text);
            if (len < sizeof(text) - 1)
            {
                text[len] = '\n';
                text[len+1] ='\0';
            }
        }
        else
        {
            // append only printable chars
            int len = RL_TextLength(text);
            if (len < sizeof(text) - 1)
            {
                text[len] = ch;
                text[len+1] ='\0';
            }
        }

        // Measure 3D text so we can center it
        tbox = MeasureTextWave3D(font, text, fontSize, fontSpacing, lineSpacing);

        quads = 0;                      // Reset quad counter
        time += RL_GetFrameTime();         // Update timer needed by `DrawTextWave3D()`
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);
                RL_DrawCubeV(cubePosition, cubeSize, dark);
                RL_DrawCubeWires(cubePosition, 2.1f, 2.1f, 2.1f, light);

                RL_DrawGrid(10, 2.0f);

                // Use a shader to handle the depth buffer issue with transparent textures
                // NOTE: more info at https://bedroomcoders.co.uk/raylib-billboards-advanced-use/
                RL_BeginShaderMode(alphaDiscard);

                    // Draw the 3D text above the red cube
                    rlPushMatrix();
                        rlRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                        rlRotatef(90.0f, 0.0f, 0.0f, -1.0f);

                        for (int i = 0; i < layers; ++i)
                        {
                            RL_Color clr = light;
                            if (multicolor) clr = multi[i];
                            DrawTextWave3D(font, text, (RL_Vector3){ -tbox.x/2.0f, layerDistance*i, -4.5f }, fontSize, fontSpacing, lineSpacing, true, &wcfg, time, clr);
                        }

                        // Draw the text boundry if set
                        if (SHOW_TEXT_BOUNDRY) RL_DrawCubeWiresV((RL_Vector3){ 0.0f, 0.0f, -4.5f + tbox.z/2 }, tbox, dark);
                    rlPopMatrix();

                    // Don't draw the letter boundries for the 3D text below
                    bool slb = SHOW_LETTER_BOUNDRY;
                    SHOW_LETTER_BOUNDRY = false;

                    // Draw 3D options (use default font)
                    //-------------------------------------------------------------------------
                    rlPushMatrix();
                        rlRotatef(180.0f, 0.0f, 1.0f, 0.0f);
                        char *opt = (char *)RL_TextFormat("< SIZE: %2.1f >", fontSize);
                        quads += RL_TextLength(opt);
                        RL_Vector3 m = MeasureText3D(RL_GetFontDefault(), opt, 8.0f, 1.0f, 0.0f);
                        RL_Vector3 pos = { -m.x/2.0f, 0.01f, 2.0f};
                        DrawText3D(RL_GetFontDefault(), opt, pos, 8.0f, 1.0f, 0.0f, false, RL_BLUE);
                        pos.z += 0.5f + m.z;

                        opt = (char *)RL_TextFormat("< SPACING: %2.1f >", fontSpacing);
                        quads += RL_TextLength(opt);
                        m = MeasureText3D(RL_GetFontDefault(), opt, 8.0f, 1.0f, 0.0f);
                        pos.x = -m.x/2.0f;
                        DrawText3D(RL_GetFontDefault(), opt, pos, 8.0f, 1.0f, 0.0f, false, RL_BLUE);
                        pos.z += 0.5f + m.z;

                        opt = (char *)RL_TextFormat("< LINE: %2.1f >", lineSpacing);
                        quads += RL_TextLength(opt);
                        m = MeasureText3D(RL_GetFontDefault(), opt, 8.0f, 1.0f, 0.0f);
                        pos.x = -m.x/2.0f;
                        DrawText3D(RL_GetFontDefault(), opt, pos, 8.0f, 1.0f, 0.0f, false, RL_BLUE);
                        pos.z += 1.0f + m.z;

                        opt = (char *)RL_TextFormat("< LBOX: %3s >", slb? "ON" : "OFF");
                        quads += RL_TextLength(opt);
                        m = MeasureText3D(RL_GetFontDefault(), opt, 8.0f, 1.0f, 0.0f);
                        pos.x = -m.x/2.0f;
                        DrawText3D(RL_GetFontDefault(), opt, pos, 8.0f, 1.0f, 0.0f, false, RL_RED);
                        pos.z += 0.5f + m.z;

                        opt = (char *)RL_TextFormat("< TBOX: %3s >", SHOW_TEXT_BOUNDRY? "ON" : "OFF");
                        quads += RL_TextLength(opt);
                        m = MeasureText3D(RL_GetFontDefault(), opt, 8.0f, 1.0f, 0.0f);
                        pos.x = -m.x/2.0f;
                        DrawText3D(RL_GetFontDefault(), opt, pos, 8.0f, 1.0f, 0.0f, false, RL_RED);
                        pos.z += 0.5f + m.z;

                        opt = (char *)RL_TextFormat("< LAYER DISTANCE: %.3f >", layerDistance);
                        quads += RL_TextLength(opt);
                        m = MeasureText3D(RL_GetFontDefault(), opt, 8.0f, 1.0f, 0.0f);
                        pos.x = -m.x/2.0f;
                        DrawText3D(RL_GetFontDefault(), opt, pos, 8.0f, 1.0f, 0.0f, false, RL_DARKPURPLE);
                    rlPopMatrix();
                    //-------------------------------------------------------------------------

                    // Draw 3D info text (use default font)
                    //-------------------------------------------------------------------------
                    opt = "All the text displayed here is in 3D";
                    quads += 36;
                    m = MeasureText3D(RL_GetFontDefault(), opt, 10.0f, 0.5f, 0.0f);
                    pos = (RL_Vector3){-m.x/2.0f, 0.01f, 2.0f};
                    DrawText3D(RL_GetFontDefault(), opt, pos, 10.0f, 0.5f, 0.0f, false, RL_DARKBLUE);
                    pos.z += 1.5f + m.z;

                    opt = "press [Left]/[Right] to change the font size";
                    quads += 44;
                    m = MeasureText3D(RL_GetFontDefault(), opt, 6.0f, 0.5f, 0.0f);
                    pos.x = -m.x/2.0f;
                    DrawText3D(RL_GetFontDefault(), opt, pos, 6.0f, 0.5f, 0.0f, false, RL_DARKBLUE);
                    pos.z += 0.5f + m.z;

                    opt = "press [Up]/[Down] to change the font spacing";
                    quads += 44;
                    m = MeasureText3D(RL_GetFontDefault(), opt, 6.0f, 0.5f, 0.0f);
                    pos.x = -m.x/2.0f;
                    DrawText3D(RL_GetFontDefault(), opt, pos, 6.0f, 0.5f, 0.0f, false, RL_DARKBLUE);
                    pos.z += 0.5f + m.z;

                    opt = "press [PgUp]/[PgDown] to change the line spacing";
                    quads += 48;
                    m = MeasureText3D(RL_GetFontDefault(), opt, 6.0f, 0.5f, 0.0f);
                    pos.x = -m.x/2.0f;
                    DrawText3D(RL_GetFontDefault(), opt, pos, 6.0f, 0.5f, 0.0f, false, RL_DARKBLUE);
                    pos.z += 0.5f + m.z;

                    opt = "press [F1] to toggle the letter boundry";
                    quads += 39;
                    m = MeasureText3D(RL_GetFontDefault(), opt, 6.0f, 0.5f, 0.0f);
                    pos.x = -m.x/2.0f;
                    DrawText3D(RL_GetFontDefault(), opt, pos, 6.0f, 0.5f, 0.0f, false, RL_DARKBLUE);
                    pos.z += 0.5f + m.z;

                    opt = "press [F2] to toggle the text boundry";
                    quads += 37;
                    m = MeasureText3D(RL_GetFontDefault(), opt, 6.0f, 0.5f, 0.0f);
                    pos.x = -m.x/2.0f;
                    DrawText3D(RL_GetFontDefault(), opt, pos, 6.0f, 0.5f, 0.0f, false, RL_DARKBLUE);
                    //-------------------------------------------------------------------------

                    SHOW_LETTER_BOUNDRY = slb;
                RL_EndShaderMode();

            RL_EndMode3D();

            // Draw 2D info text & stats
            //-------------------------------------------------------------------------
            RL_DrawText("Drag & drop a font file to change the font!\nType something, see what happens!\n\n"
            "Press [F3] to toggle the camera", 10, 35, 10, RL_BLACK);

            quads += RL_TextLength(text)*2*layers;
            char *tmp = (char *)RL_TextFormat("%2i layer(s) | %s camera | %4i quads (%4i verts)", layers, spin? "ORBITAL" : "FREE", quads, quads*4);
            int width = RL_MeasureText(tmp, 10);
            RL_DrawText(tmp, screenWidth - 20 - width, 10, 10, RL_DARKGREEN);

            tmp = "[Home]/[End] to add/remove 3D text layers";
            width = RL_MeasureText(tmp, 10);
            RL_DrawText(tmp, screenWidth - 20 - width, 25, 10, RL_DARKGRAY);

            tmp = "[Insert]/[Delete] to increase/decrease distance between layers";
            width = RL_MeasureText(tmp, 10);
            RL_DrawText(tmp, screenWidth - 20 - width, 40, 10, RL_DARKGRAY);

            tmp = "click the [CUBE] for a random color";
            width = RL_MeasureText(tmp, 10);
            RL_DrawText(tmp, screenWidth - 20 - width, 55, 10, RL_DARKGRAY);

            tmp = "[Tab] to toggle multicolor mode";
            width = RL_MeasureText(tmp, 10);
            RL_DrawText(tmp, screenWidth - 20 - width, 70, 10, RL_DARKGRAY);
            //-------------------------------------------------------------------------

            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadFont(font);
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//--------------------------------------------------------------------------------------
// Module Functions Definitions
//--------------------------------------------------------------------------------------
// Draw codepoint at specified position in 3D space
static void DrawTextCodepoint3D(RL_Font font, int codepoint, RL_Vector3 position, float fontSize, bool backface, RL_Color tint)
{
    // Character index position in sprite font
    // NOTE: In case a codepoint is not available in the font, index returned points to '?'
    int index = RL_GetGlyphIndex(font, codepoint);
    float scale = fontSize/(float)font.baseSize;

    // Character destination rectangle on screen
    // NOTE: We consider charsPadding on drawing
    position.x += (float)(font.glyphs[index].offsetX - font.glyphPadding)/(float)font.baseSize*scale;
    position.z += (float)(font.glyphs[index].offsetY - font.glyphPadding)/(float)font.baseSize*scale;

    // Character source rectangle from font texture atlas
    // NOTE: We consider chars padding when drawing, it could be required for outline/glow shader effects
    RL_Rectangle srcRec = { font.recs[index].x - (float)font.glyphPadding, font.recs[index].y - (float)font.glyphPadding,
                         font.recs[index].width + 2.0f*font.glyphPadding, font.recs[index].height + 2.0f*font.glyphPadding };

    float width = (float)(font.recs[index].width + 2.0f*font.glyphPadding)/(float)font.baseSize*scale;
    float height = (float)(font.recs[index].height + 2.0f*font.glyphPadding)/(float)font.baseSize*scale;

    if (font.texture.id > 0)
    {
        const float x = 0.0f;
        const float y = 0.0f;
        const float z = 0.0f;

        // normalized texture coordinates of the glyph inside the font texture (0.0f -> 1.0f)
        const float tx = srcRec.x/font.texture.width;
        const float ty = srcRec.y/font.texture.height;
        const float tw = (srcRec.x+srcRec.width)/font.texture.width;
        const float th = (srcRec.y+srcRec.height)/font.texture.height;

        if (SHOW_LETTER_BOUNDRY) RL_DrawCubeWiresV((RL_Vector3){ position.x + width/2, position.y, position.z + height/2}, (RL_Vector3){ width, LETTER_BOUNDRY_SIZE, height }, LETTER_BOUNDRY_COLOR);

        rlCheckRenderBatchLimit(4 + 4*backface);
        rlSetTexture(font.texture.id);

        rlPushMatrix();
            rlTranslatef(position.x, position.y, position.z);

            rlBegin(RL_QUADS);
                rlColor4ub(tint.r, tint.g, tint.b, tint.a);

                // Front Face
                rlNormal3f(0.0f, 1.0f, 0.0f);                                   // Normal Pointing Up
                rlTexCoord2f(tx, ty); rlVertex3f(x,         y, z);              // Top Left Of The RL_Texture and Quad
                rlTexCoord2f(tx, th); rlVertex3f(x,         y, z + height);     // Bottom Left Of The RL_Texture and Quad
                rlTexCoord2f(tw, th); rlVertex3f(x + width, y, z + height);     // Bottom Right Of The RL_Texture and Quad
                rlTexCoord2f(tw, ty); rlVertex3f(x + width, y, z);              // Top Right Of The RL_Texture and Quad

                if (backface)
                {
                    // Back Face
                    rlNormal3f(0.0f, -1.0f, 0.0f);                              // Normal Pointing Down
                    rlTexCoord2f(tx, ty); rlVertex3f(x,         y, z);          // Top Right Of The RL_Texture and Quad
                    rlTexCoord2f(tw, ty); rlVertex3f(x + width, y, z);          // Top Left Of The RL_Texture and Quad
                    rlTexCoord2f(tw, th); rlVertex3f(x + width, y, z + height); // Bottom Left Of The RL_Texture and Quad
                    rlTexCoord2f(tx, th); rlVertex3f(x,         y, z + height); // Bottom Right Of The RL_Texture and Quad
                }
            rlEnd();
        rlPopMatrix();

        rlSetTexture(0);
    }
}

// Draw a 2D text in 3D space
static void DrawText3D(RL_Font font, const char *text, RL_Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, RL_Color tint)
{
    int length = RL_TextLength(text);          // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0.0f;               // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;               // Offset X to next character to draw

    float scale = fontSize/(float)font.baseSize;

    for (int i = 0; i < length;)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = RL_GetCodepoint(&text[i], &codepointByteCount);
        int index = RL_GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;

        if (codepoint == '\n')
        {
            // NOTE: Fixed line spacing of 1.5 line-height
            // TODO: Support custom line spacing defined by user
            textOffsetY += scale + lineSpacing/(float)font.baseSize*scale;
            textOffsetX = 0.0f;
        }
        else
        {
            if ((codepoint != ' ') && (codepoint != '\t'))
            {
                DrawTextCodepoint3D(font, codepoint, (RL_Vector3){ position.x + textOffsetX, position.y, position.z + textOffsetY }, fontSize, backface, tint);
            }

            if (font.glyphs[index].advanceX == 0) textOffsetX += (float)(font.recs[index].width + fontSpacing)/(float)font.baseSize*scale;
            else textOffsetX += (float)(font.glyphs[index].advanceX + fontSpacing)/(float)font.baseSize*scale;
        }

        i += codepointByteCount;   // Move text bytes counter to next codepoint
    }
}

// Measure a text in 3D. For some reason `RL_MeasureTextEx()` just doesn't seem to work so i had to use this instead.
static RL_Vector3 MeasureText3D(RL_Font font, const char* text, float fontSize, float fontSpacing, float lineSpacing)
{
    int len = RL_TextLength(text);
    int tempLen = 0;                // Used to count longer text line num chars
    int lenCounter = 0;

    float tempTextWidth = 0.0f;     // Used to count longer text line width

    float scale = fontSize/(float)font.baseSize;
    float textHeight = scale;
    float textWidth = 0.0f;

    int letter = 0;                 // Current character
    int index = 0;                  // Index position in sprite font

    for (int i = 0; i < len; i++)
    {
        lenCounter++;

        int next = 0;
        letter = RL_GetCodepoint(&text[i], &next);
        index = RL_GetGlyphIndex(font, letter);

        // NOTE: normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol so to not skip any we set next = 1
        if (letter == 0x3f) next = 1;
        i += next - 1;

        if (letter != '\n')
        {
            if (font.glyphs[index].advanceX != 0) textWidth += (font.glyphs[index].advanceX+fontSpacing)/(float)font.baseSize*scale;
            else textWidth += (font.recs[index].width + font.glyphs[index].offsetX)/(float)font.baseSize*scale;
        }
        else
        {
            if (tempTextWidth < textWidth) tempTextWidth = textWidth;
            lenCounter = 0;
            textWidth = 0.0f;
            textHeight += scale + lineSpacing/(float)font.baseSize*scale;
        }

        if (tempLen < lenCounter) tempLen = lenCounter;
    }

    if (tempTextWidth < textWidth) tempTextWidth = textWidth;

    RL_Vector3 vec = { 0 };
    vec.x = tempTextWidth + (float)((tempLen - 1)*fontSpacing/(float)font.baseSize*scale); // Adds chars spacing to measure
    vec.y = 0.25f;
    vec.z = textHeight;

    return vec;
}

// Draw a 2D text in 3D space and wave the parts that start with `~~` and end with `~~`.
// This is a modified version of the original code by @Nighten found here https://github.com/NightenDushi/Raylib_DrawTextStyle
static void DrawTextWave3D(RL_Font font, const char *text, RL_Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, WaveTextConfig* config, float time, RL_Color tint)
{
    int length = RL_TextLength(text);          // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0.0f;               // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;               // Offset X to next character to draw

    float scale = fontSize/(float)font.baseSize;

    bool wave = false;

    for (int i = 0, k = 0; i < length; ++k)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = RL_GetCodepoint(&text[i], &codepointByteCount);
        int index = RL_GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;

        if (codepoint == '\n')
        {
            // NOTE: Fixed line spacing of 1.5 line-height
            // TODO: Support custom line spacing defined by user
            textOffsetY += scale + lineSpacing/(float)font.baseSize*scale;
            textOffsetX = 0.0f;
            k = 0;
        }
        else if (codepoint == '~')
        {
            if (RL_GetCodepoint(&text[i+1], &codepointByteCount) == '~')
            {
                codepointByteCount += 1;
                wave = !wave;
            }
        }
        else
        {
            if ((codepoint != ' ') && (codepoint != '\t'))
            {
                RL_Vector3 pos = position;
                if (wave) // Apply the wave effect
                {
                    pos.x += sinf(time*config->waveSpeed.x-k*config->waveOffset.x)*config->waveRange.x;
                    pos.y += sinf(time*config->waveSpeed.y-k*config->waveOffset.y)*config->waveRange.y;
                    pos.z += sinf(time*config->waveSpeed.z-k*config->waveOffset.z)*config->waveRange.z;
                }

                DrawTextCodepoint3D(font, codepoint, (RL_Vector3){ pos.x + textOffsetX, pos.y, pos.z + textOffsetY }, fontSize, backface, tint);
            }

            if (font.glyphs[index].advanceX == 0) textOffsetX += (float)(font.recs[index].width + fontSpacing)/(float)font.baseSize*scale;
            else textOffsetX += (float)(font.glyphs[index].advanceX + fontSpacing)/(float)font.baseSize*scale;
        }

        i += codepointByteCount;   // Move text bytes counter to next codepoint
    }
}

// Measure a text in 3D ignoring the `~~` chars.
static RL_Vector3 MeasureTextWave3D(RL_Font font, const char* text, float fontSize, float fontSpacing, float lineSpacing)
{
    int len = RL_TextLength(text);
    int tempLen = 0;                // Used to count longer text line num chars
    int lenCounter = 0;

    float tempTextWidth = 0.0f;     // Used to count longer text line width

    float scale = fontSize/(float)font.baseSize;
    float textHeight = scale;
    float textWidth = 0.0f;

    int letter = 0;                 // Current character
    int index = 0;                  // Index position in sprite font

    for (int i = 0; i < len; i++)
    {
        lenCounter++;

        int next = 0;
        letter = RL_GetCodepoint(&text[i], &next);
        index = RL_GetGlyphIndex(font, letter);

        // NOTE: normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol so to not skip any we set next = 1
        if (letter == 0x3f) next = 1;
        i += next - 1;

        if (letter != '\n')
        {
            if (letter == '~' && RL_GetCodepoint(&text[i+1], &next) == '~')
            {
                i++;
            }
            else
            {
                if (font.glyphs[index].advanceX != 0) textWidth += (font.glyphs[index].advanceX+fontSpacing)/(float)font.baseSize*scale;
                else textWidth += (font.recs[index].width + font.glyphs[index].offsetX)/(float)font.baseSize*scale;
            }
        }
        else
        {
            if (tempTextWidth < textWidth) tempTextWidth = textWidth;
            lenCounter = 0;
            textWidth = 0.0f;
            textHeight += scale + lineSpacing/(float)font.baseSize*scale;
        }

        if (tempLen < lenCounter) tempLen = lenCounter;
    }

    if (tempTextWidth < textWidth) tempTextWidth = textWidth;

    RL_Vector3 vec = { 0 };
    vec.x = tempTextWidth + (float)((tempLen - 1)*fontSpacing/(float)font.baseSize*scale); // Adds chars spacing to measure
    vec.y = 0.25f;
    vec.z = textHeight;

    return vec;
}

// Generates a nice color with a random hue
static RL_Color GenerateRandomColor(float s, float v)
{
    const float Phi = 0.618033988749895f; // Golden ratio conjugate
    float h = (float)RL_GetRandomValue(0, 360);
    h = fmodf((h + h*Phi), 360.0f);
    return RL_ColorFromHSV(h, s, v);
}
