/*******************************************************************************************
*
*   raylib [shaders] example - Hybrid Rendering
*
*   Example originally created with raylib 4.2, last time updated with raylib 4.2
*
*   Example contributed by Buğra Alptekin Sarı (@BugraAlptekinSari) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2024 Buğra Alptekin Sarı (@BugraAlptekinSari)
*
********************************************************************************************/

#include "raylib.h"
#include "rlgl.h"
#include "math.h" // Used for tan()
#include "raymath.h" // Used to calculate camera Direction

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

//------------------------------------------------------------------------------------
// Declare custom functions required for the example
//------------------------------------------------------------------------------------
// Load custom render texture, create a writable depth texture buffer
static RL_RenderTexture2D LoadRenderTextureDepthTex(int width, int height);
// Unload render texture from GPU memory (VRAM)
static void UnloadRenderTextureDepthTex(RL_RenderTexture2D target);

//------------------------------------------------------------------------------------
// Declare custom Structs
//------------------------------------------------------------------------------------

typedef struct {
    unsigned int camPos, camDir, screenCenter;
}RayLocs ;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - write depth buffer");

    // This RL_Shader calculates pixel depth and color using raymarch
    RL_Shader shdrRaymarch = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/hybrid_raymarch.fs", GLSL_VERSION));

    // This RL_Shader is a standard rasterization fragment shader with the addition of depth writing
    // You are required to write depth for all shaders if one shader does it
    RL_Shader shdrRaster = RL_LoadShader(0, RL_TextFormat("resources/shaders/glsl%i/hybrid_raster.fs", GLSL_VERSION));

    // Declare Struct used to store camera locs.
    RayLocs marchLocs = {0};

    // Fill the struct with shader locs.
    marchLocs.camPos = RL_GetShaderLocation(shdrRaymarch, "camPos");
    marchLocs.camDir = RL_GetShaderLocation(shdrRaymarch, "camDir");
    marchLocs.screenCenter = RL_GetShaderLocation(shdrRaymarch, "screenCenter");

    // Transfer screenCenter position to shader. Which is used to calculate ray direction. 
    RL_Vector2 screenCenter = {.x = screenWidth/2.0f, .y = screenHeight/2.0f};
    RL_SetShaderValue(shdrRaymarch, marchLocs.screenCenter , &screenCenter , SHADER_UNIFORM_VEC2);

    // Use Customized function to create writable depth texture buffer
    RL_RenderTexture2D target = LoadRenderTextureDepthTex(screenWidth, screenHeight);

    // Define the camera to look into our 3d world
    RL_Camera camera = {
        .position = (RL_Vector3){ 0.5f, 1.0f, 1.5f },    // RL_Camera position
        .target = (RL_Vector3){ 0.0f, 0.5f, 0.0f },      // RL_Camera looking at point
        .up = (RL_Vector3){ 0.0f, 1.0f, 0.0f },          // RL_Camera up vector (rotation towards target)
        .fovy = 45.0f,                                // RL_Camera field-of-view Y
        .projection = CAMERA_PERSPECTIVE              // RL_Camera projection type
    };
    
    // RL_Camera FOV is pre-calculated in the camera Distance.
    float camDist = 1.0f/(tanf(camera.fovy*0.5f*DEG2RAD));
    
    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_ORBITAL);

        // Update RL_Camera Postion in the ray march shader.
        RL_SetShaderValue(shdrRaymarch, marchLocs.camPos, &(camera.position), RL_SHADER_UNIFORM_VEC3);
        
        // Update RL_Camera Looking Vector. Vector length determines FOV.
        RL_Vector3 camDir = Vector3Scale( Vector3Normalize( Vector3Subtract(camera.target, camera.position)) , camDist);
        RL_SetShaderValue(shdrRaymarch, marchLocs.camDir, &(camDir), RL_SHADER_UNIFORM_VEC3);
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        // Draw into our custom render texture (framebuffer)
        RL_BeginTextureMode(target);
            RL_ClearBackground(RL_WHITE);

            // Raymarch Scene
            rlEnableDepthTest(); //Manually enable Depth Test to handle multiple rendering methods.
            RL_BeginShaderMode(shdrRaymarch);
                RL_DrawRectangleRec((RL_Rectangle){0,0, (float)screenWidth, (float)screenHeight},RL_WHITE);
            RL_EndShaderMode();
            
            // Rasterize Scene
            RL_BeginMode3D(camera);
                RL_BeginShaderMode(shdrRaster);
                    RL_DrawCubeWiresV((RL_Vector3){ 0.0f, 0.5f, 1.0f }, (RL_Vector3){ 1.0f, 1.0f, 1.0f }, RL_RED);
                    RL_DrawCubeV((RL_Vector3){ 0.0f, 0.5f, 1.0f }, (RL_Vector3){ 1.0f, 1.0f, 1.0f }, RL_PURPLE);
                    RL_DrawCubeWiresV((RL_Vector3){ 0.0f, 0.5f, -1.0f }, (RL_Vector3){ 1.0f, 1.0f, 1.0f }, RL_DARKGREEN);
                    RL_DrawCubeV((RL_Vector3) { 0.0f, 0.5f, -1.0f }, (RL_Vector3){ 1.0f, 1.0f, 1.0f }, RL_YELLOW);
                    RL_DrawGrid(10, 1.0f);
                RL_EndShaderMode();
            RL_EndMode3D();
        RL_EndTextureMode();

        // Draw into screen our custom render texture 
        RL_BeginDrawing();
            RL_ClearBackground(RL_RAYWHITE);
        
            RL_DrawTextureRec(target.texture, (RL_Rectangle) { 0, 0, (float)screenWidth, (float)-screenHeight }, (RL_Vector2) { 0, 0 }, RL_WHITE);
            RL_DrawFPS(10, 10);
        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTextureDepthTex(target);
    RL_UnloadShader(shdrRaymarch);
    RL_UnloadShader(shdrRaster);

    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Define custom functions required for the example
//------------------------------------------------------------------------------------
// Load custom render texture, create a writable depth texture buffer
RL_RenderTexture2D LoadRenderTextureDepthTex(int width, int height)
{
    RL_RenderTexture2D target = { 0 };

    target.id = rlLoadFramebuffer(); // Load an empty framebuffer

    if (target.id > 0)
    {
        rlEnableFramebuffer(target.id);

        // Create color texture (default to RGBA)
        target.texture.id = rlLoadTexture(0, width, height, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
        target.texture.width = width;
        target.texture.height = height;
        target.texture.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
        target.texture.mipmaps = 1;

        // Create depth texture buffer (instead of raylib default renderbuffer)
        target.depth.id = rlLoadTextureDepth(width, height, false);
        target.depth.width = width;
        target.depth.height = height;
        target.depth.format = 19;       //DEPTH_COMPONENT_24BIT?
        target.depth.mipmaps = 1;

        // Attach color texture and depth texture to FBO
        rlFramebufferAttach(target.id, target.texture.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D, 0);
        rlFramebufferAttach(target.id, target.depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D, 0);

        // Check if fbo is complete with attachments (valid)
        if (rlFramebufferComplete(target.id)) TRACELOG(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", target.id);

        rlDisableFramebuffer();
    }
    else TRACELOG(LOG_WARNING, "FBO: Framebuffer object can not be created");

    return target;
}

// Unload render texture from GPU memory (VRAM)
void UnloadRenderTextureDepthTex(RL_RenderTexture2D target)
{
    if (target.id > 0)
    {
        // RL_Color texture attached to FBO is deleted
        rlUnloadTexture(target.texture.id);
        rlUnloadTexture(target.depth.id);

        // NOTE: Depth texture is automatically
        // queried and deleted before deleting framebuffer
        rlUnloadFramebuffer(target.id);
    }
}
