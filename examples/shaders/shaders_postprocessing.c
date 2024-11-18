/*******************************************************************************************
*
*   raylib [shaders] example - Apply a postprocessing shader to a scene
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3), to test this example
*         on OpenGL ES 2.0 platforms (Android, Raspberry Pi, HTML5), use #version 100 shaders
*         raylib comes with shaders ready for both versions, check raylib/shaders install folder
*
*   Example originally created with raylib 1.3, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

#define MAX_POSTPRO_SHADERS         12

typedef enum {
    FX_GRAYSCALE = 0,
    FX_POSTERIZATION,
    FX_DREAM_VISION,
    FX_PIXELIZER,
    FX_CROSS_HATCHING,
    FX_CROSS_STITCHING,
    FX_PREDATOR_VIEW,
    FX_SCANLINES,
    FX_FISHEYE,
    FX_SOBEL,
    FX_BLOOM,
    FX_BLUR,
    //FX_FXAA
} PostproShader;

static const char *postproShaderText[] = {
    "GRAYSCALE",
    "POSTERIZATION",
    "DREAM_VISION",
    "PIXELIZER",
    "CROSS_HATCHING",
    "CROSS_STITCHING",
    "PREDATOR_VIEW",
    "SCANLINES",
    "FISHEYE",
    "SOBEL",
    "BLOOM",
    "BLUR",
    //"FXAA"
};

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_SetConfigFlags(FLAG_MSAA_4X_HINT);      // Enable Multi Sampling Anti Aliasing 4x (if available)

    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - postprocessing shader");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 2.0f, 3.0f, 2.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 1.0f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    RL_Model model = RL_LoadModel("resources/models/church.obj");                 // Load OBJ model
    RL_Texture2D texture = RL_LoadTexture("resources/models/church_diffuse.png"); // Load model texture (diffuse map)
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;        // Set model diffuse texture

    RL_Vector3 position = { 0.0f, 0.0f, 0.0f };            // Set model position

    // Load all postpro shaders
    // NOTE 1: All postpro shader use the base vertex shader (DEFAULT_VERTEX_SHADER)
    // NOTE 2: We load the correct shader depending on GLSL version
    RL_Shader shaders[MAX_POSTPRO_SHADERS] = { 0 };

    // NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
    shaders[FX_GRAYSCALE] = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/grayscale.fs", GLSL_VERSION));
    shaders[FX_POSTERIZATION] = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/posterization.fs", GLSL_VERSION));
    shaders[FX_DREAM_VISION] = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/dream_vision.fs", GLSL_VERSION));
    shaders[FX_PIXELIZER] = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/pixelizer.fs", GLSL_VERSION));
    shaders[FX_CROSS_HATCHING] = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/cross_hatching.fs", GLSL_VERSION));
    shaders[FX_CROSS_STITCHING] = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/cross_stitching.fs", GLSL_VERSION));
    shaders[FX_PREDATOR_VIEW] = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/predator.fs", GLSL_VERSION));
    shaders[FX_SCANLINES] = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/scanlines.fs", GLSL_VERSION));
    shaders[FX_FISHEYE] = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/fisheye.fs", GLSL_VERSION));
    shaders[FX_SOBEL] = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/sobel.fs", GLSL_VERSION));
    shaders[FX_BLOOM] = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/bloom.fs", GLSL_VERSION));
    shaders[FX_BLUR] = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/blur.fs", GLSL_VERSION));

    int currentShader = FX_GRAYSCALE;

    // Create a RL_RenderTexture2D to be used for render to texture
    RL_RenderTexture2D target = RL_LoadRenderTexture(screenWidth, screenHeight);

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_ORBITAL);

        if (RL_IsKeyPressed(KEY_RIGHT)) currentShader++;
        else if (RL_IsKeyPressed(KEY_LEFT)) currentShader--;

        if (currentShader >= MAX_POSTPRO_SHADERS) currentShader = 0;
        else if (currentShader < 0) currentShader = MAX_POSTPRO_SHADERS - 1;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginTextureMode(target);       // Enable drawing to texture
            RL_ClearBackground(RL_RAYWHITE);  // Clear texture background

            RL_BeginMode3D(camera);        // Begin 3d mode drawing
                RL_DrawModel(model, position, 0.1f, RL_WHITE);   // Draw 3d model with texture
                RL_DrawGrid(10, 1.0f);     // Draw a grid
            RL_EndMode3D();                // End 3d mode drawing, returns to orthographic 2d mode
        RL_EndTextureMode();               // End drawing to texture (now we have a texture available for next passes)
        
        RL_BeginDrawing();
            RL_ClearBackground(RL_RAYWHITE);  // Clear screen background

            // Render generated texture using selected postprocessing shader
            RL_BeginShaderMode(shaders[currentShader]);
                // NOTE: Render texture must be y-flipped due to default OpenGL coordinates (left-bottom)
                RL_DrawTextureRec(target.texture, (RL_Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (RL_Vector2){ 0, 0 }, RL_WHITE);
            RL_EndShaderMode();

            // Draw 2d shapes and text over drawn texture
            RL_DrawRectangle(0, 9, 580, 30, RL_Fade(RL_LIGHTGRAY, 0.7f));

            RL_DrawText("(c) Church 3D model by Alberto Cano", screenWidth - 200, screenHeight - 20, 10, RL_GRAY);
            RL_DrawText("CURRENT POSTPRO SHADER:", 10, 15, 20, RL_BLACK);
            RL_DrawText(postproShaderText[currentShader], 330, 15, 20, RL_RED);
            RL_DrawText("< >", 540, 10, 30, RL_DARKBLUE);
            RL_DrawFPS(700, 15);
        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Unload all postpro shaders
    for (int i = 0; i < MAX_POSTPRO_SHADERS; i++) RL_UnloadShader(shaders[i]);

    RL_UnloadTexture(texture);         // Unload texture
    RL_UnloadModel(model);             // Unload model
    RL_UnloadRenderTexture(target);    // Unload render texture

    RL_CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
