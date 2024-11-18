/*******************************************************************************************
*
*   raylib [shaders] example - Julia sets
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3).
*
*   Example originally created with raylib 2.5, last time updated with raylib 4.0
*
*   Example contributed by Josh Colclough (@joshcol9232) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Josh Colclough (@joshcol9232) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

// A few good julia sets
const float pointsOfInterest[6][2] =
{
    { -0.348827f, 0.607167f },
    { -0.786268f, 0.169728f },
    { -0.8f, 0.156f },
    { 0.285f, 0.0f },
    { -0.835f, -0.2321f },
    { -0.70176f, -0.3842f },
};

const int screenWidth = 800;
const int screenHeight = 450;
const float zoomSpeed = 1.01f;
const float offsetSpeedMul = 2.0f;

const float startingZoom = 0.75f;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - julia sets");

    // Load julia set shader
    // NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
    RL_Shader shader = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/julia_set.fs", GLSL_VERSION));

    // Create a RL_RenderTexture2D to be used for render to texture
    RL_RenderTexture2D target = RL_LoadRenderTexture(RL_GetScreenWidth(), RL_GetScreenHeight());

    // c constant to use in z^2 + c
    float c[2] = { pointsOfInterest[0][0], pointsOfInterest[0][1] };

    // Offset and zoom to draw the julia set at. (centered on screen and default size)
    float offset[2] = { 0.0f, 0.0f };
    float zoom = startingZoom;

    // Get variable (uniform) locations on the shader to connect with the program
    // NOTE: If uniform variable could not be found in the shader, function returns -1
    int cLoc = RL_GetShaderLocation(shader, "c");
    int zoomLoc = RL_GetShaderLocation(shader, "zoom");
    int offsetLoc = RL_GetShaderLocation(shader, "offset");

    // Upload the shader uniform values!
    RL_SetShaderValue(shader, cLoc, c, SHADER_UNIFORM_VEC2);
    RL_SetShaderValue(shader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
    RL_SetShaderValue(shader, offsetLoc, offset, SHADER_UNIFORM_VEC2);

    int incrementSpeed = 0;             // Multiplier of speed to change c value
    bool showControls = true;           // Show controls

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Press [1 - 6] to reset c to a point of interest
        if (RL_IsKeyPressed(KEY_ONE) ||
            RL_IsKeyPressed(KEY_TWO) ||
            RL_IsKeyPressed(KEY_THREE) ||
            RL_IsKeyPressed(KEY_FOUR) ||
            RL_IsKeyPressed(KEY_FIVE) ||
            RL_IsKeyPressed(KEY_SIX))
        {
            if (RL_IsKeyPressed(KEY_ONE)) c[0] = pointsOfInterest[0][0], c[1] = pointsOfInterest[0][1];
            else if (RL_IsKeyPressed(KEY_TWO)) c[0] = pointsOfInterest[1][0], c[1] = pointsOfInterest[1][1];
            else if (RL_IsKeyPressed(KEY_THREE)) c[0] = pointsOfInterest[2][0], c[1] = pointsOfInterest[2][1];
            else if (RL_IsKeyPressed(KEY_FOUR)) c[0] = pointsOfInterest[3][0], c[1] = pointsOfInterest[3][1];
            else if (RL_IsKeyPressed(KEY_FIVE)) c[0] = pointsOfInterest[4][0], c[1] = pointsOfInterest[4][1];
            else if (RL_IsKeyPressed(KEY_SIX)) c[0] = pointsOfInterest[5][0], c[1] = pointsOfInterest[5][1];

            RL_SetShaderValue(shader, cLoc, c, SHADER_UNIFORM_VEC2);
        }

        // If "R" is pressed, reset zoom and offset.
        if (RL_IsKeyPressed(KEY_R))
        {
            zoom = startingZoom;
            offset[0] = 0.0f;
            offset[1] = 0.0f;
            RL_SetShaderValue(shader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
            RL_SetShaderValue(shader, offsetLoc, offset, SHADER_UNIFORM_VEC2);
        }

        if (RL_IsKeyPressed(KEY_SPACE)) incrementSpeed = 0;         // Pause animation (c change)
        if (RL_IsKeyPressed(KEY_F1)) showControls = !showControls;  // Toggle whether or not to show controls

        if (RL_IsKeyPressed(KEY_RIGHT)) incrementSpeed++;
        else if (RL_IsKeyPressed(KEY_LEFT)) incrementSpeed--;

        // If either left or right button is pressed, zoom in/out.
        if (RL_IsMouseButtonDown(MOUSE_BUTTON_LEFT) || RL_IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            // Change zoom. If Mouse left -> zoom in. Mouse right -> zoom out.
            zoom *= RL_IsMouseButtonDown(MOUSE_BUTTON_LEFT)? zoomSpeed : 1.0f/zoomSpeed;

            const RL_Vector2 mousePos = RL_GetMousePosition();
            RL_Vector2 offsetVelocity;
            // Find the velocity at which to change the camera. Take the distance of the mouse
            // from the center of the screen as the direction, and adjust magnitude based on
            // the current zoom.
            offsetVelocity.x = (mousePos.x/(float)screenWidth - 0.5f)*offsetSpeedMul/zoom;
            offsetVelocity.y = (mousePos.y/(float)screenHeight - 0.5f)*offsetSpeedMul/zoom;

            // Apply move velocity to camera
            offset[0] += RL_GetFrameTime()*offsetVelocity.x;
            offset[1] += RL_GetFrameTime()*offsetVelocity.y;

            // Update the shader uniform values!
            RL_SetShaderValue(shader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);
            RL_SetShaderValue(shader, offsetLoc, offset, SHADER_UNIFORM_VEC2);
        }

        // Increment c value with time
        const float dc = RL_GetFrameTime()*(float)incrementSpeed*0.0005f;
        c[0] += dc;
        c[1] += dc;
        RL_SetShaderValue(shader, cLoc, c, SHADER_UNIFORM_VEC2);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        // Using a render texture to draw Julia set
        RL_BeginTextureMode(target);       // Enable drawing to texture
            RL_ClearBackground(RL_BLACK);     // Clear the render texture

            // Draw a rectangle in shader mode to be used as shader canvas
            // NOTE: RL_Rectangle uses font white character texture coordinates,
            // so shader can not be applied here directly because input vertexTexCoord
            // do not represent full screen coordinates (space where want to apply shader)
            RL_DrawRectangle(0, 0, RL_GetScreenWidth(), RL_GetScreenHeight(), RL_BLACK);
        RL_EndTextureMode();
            
        RL_BeginDrawing();
            RL_ClearBackground(RL_BLACK);     // Clear screen background

            // Draw the saved texture and rendered julia set with shader
            // NOTE: We do not invert texture on Y, already considered inside shader
            RL_BeginShaderMode(shader);
                // WARNING: If FLAG_WINDOW_HIGHDPI is enabled, HighDPI monitor scaling should be considered
                // when rendering the RL_RenderTexture2D to fit in the HighDPI scaled Window
                RL_DrawTextureEx(target.texture, (RL_Vector2){ 0.0f, 0.0f }, 0.0f, 1.0f, RL_WHITE);
            RL_EndShaderMode();

            if (showControls)
            {
                RL_DrawText("Press Mouse buttons right/left to zoom in/out and move", 10, 15, 10, RL_RAYWHITE);
                RL_DrawText("Press KEY_F1 to toggle these controls", 10, 30, 10, RL_RAYWHITE);
                RL_DrawText("Press KEYS [1 - 6] to change point of interest", 10, 45, 10, RL_RAYWHITE);
                RL_DrawText("Press KEY_LEFT | KEY_RIGHT to change speed", 10, 60, 10, RL_RAYWHITE);
                RL_DrawText("Press KEY_SPACE to stop movement animation", 10, 75, 10, RL_RAYWHITE);
                RL_DrawText("Press KEY_R to recenter the camera", 10, 90, 10, RL_RAYWHITE);
            }
        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadShader(shader);               // Unload shader
    RL_UnloadRenderTexture(target);        // Unload render texture

    RL_CloseWindow();                      // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
