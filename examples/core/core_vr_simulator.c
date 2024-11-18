/*******************************************************************************************
*
*   raylib [core] example - VR Simulator (Oculus Rift CV1 parameters)
*
*   Example originally created with raylib 2.5, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION        330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION        100
#endif

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    // NOTE: screenWidth/screenHeight should match VR device aspect ratio
    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - vr simulator");

    // VR device parameters definition
    RL_VrDeviceInfo device = {
        // Oculus Rift CV1 parameters for simulator
        .hResolution = 2160,                 // Horizontal resolution in pixels
        .vResolution = 1200,                 // Vertical resolution in pixels
        .hScreenSize = 0.133793f,            // Horizontal size in meters
        .vScreenSize = 0.0669f,              // Vertical size in meters
        .eyeToScreenDistance = 0.041f,       // Distance between eye and display in meters
        .lensSeparationDistance = 0.07f,     // Lens separation distance in meters
        .interpupillaryDistance = 0.07f,     // IPD (distance between pupils) in meters

        // NOTE: CV1 uses fresnel-hybrid-asymmetric lenses with specific compute shaders
        // Following parameters are just an approximation to CV1 distortion stereo rendering
        .lensDistortionValues[0] = 1.0f,     // Lens distortion constant parameter 0
        .lensDistortionValues[1] = 0.22f,    // Lens distortion constant parameter 1
        .lensDistortionValues[2] = 0.24f,    // Lens distortion constant parameter 2
        .lensDistortionValues[3] = 0.0f,     // Lens distortion constant parameter 3
        .chromaAbCorrection[0] = 0.996f,     // Chromatic aberration correction parameter 0
        .chromaAbCorrection[1] = -0.004f,    // Chromatic aberration correction parameter 1
        .chromaAbCorrection[2] = 1.014f,     // Chromatic aberration correction parameter 2
        .chromaAbCorrection[3] = 0.0f,       // Chromatic aberration correction parameter 3
    };

    // Load VR stereo config for VR device parameteres (Oculus Rift CV1 parameters)
    RL_VrStereoConfig config = RL_LoadVrStereoConfig(device);

    // Distortion shader (uses device lens distortion and chroma)
    RL_Shader distortion = RL_LoadShader(0, RL_TextFormat("resources/distortion%i.fs", GLSL_VERSION));

    // Update distortion shader with lens and distortion-scale parameters
    RL_SetShaderValue(distortion, RL_GetShaderLocation(distortion, "leftLensCenter"),
                   config.leftLensCenter, SHADER_UNIFORM_VEC2);
    RL_SetShaderValue(distortion, RL_GetShaderLocation(distortion, "rightLensCenter"),
                   config.rightLensCenter, SHADER_UNIFORM_VEC2);
    RL_SetShaderValue(distortion, RL_GetShaderLocation(distortion, "leftScreenCenter"),
                   config.leftScreenCenter, SHADER_UNIFORM_VEC2);
    RL_SetShaderValue(distortion, RL_GetShaderLocation(distortion, "rightScreenCenter"),
                   config.rightScreenCenter, SHADER_UNIFORM_VEC2);

    RL_SetShaderValue(distortion, RL_GetShaderLocation(distortion, "scale"),
                   config.scale, SHADER_UNIFORM_VEC2);
    RL_SetShaderValue(distortion, RL_GetShaderLocation(distortion, "scaleIn"),
                   config.scaleIn, SHADER_UNIFORM_VEC2);
    RL_SetShaderValue(distortion, RL_GetShaderLocation(distortion, "deviceWarpParam"),
                   device.lensDistortionValues, SHADER_UNIFORM_VEC4);
    RL_SetShaderValue(distortion, RL_GetShaderLocation(distortion, "chromaAbParam"),
                   device.chromaAbCorrection, SHADER_UNIFORM_VEC4);

    // Initialize framebuffer for stereo rendering
    // NOTE: Screen size should match HMD aspect ratio
    RL_RenderTexture2D target = RL_LoadRenderTexture(device.hResolution, device.vResolution);

    // The target's height is flipped (in the source RL_Rectangle), due to OpenGL reasons
    RL_Rectangle sourceRec = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height };
    RL_Rectangle destRec = { 0.0f, 0.0f, (float)RL_GetScreenWidth(), (float)RL_GetScreenHeight() };

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 5.0f, 2.0f, 5.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 2.0f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector
    camera.fovy = 60.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    RL_Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    RL_DisableCursor();                    // Limit cursor to relative movement inside the window

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginTextureMode(target);
            RL_ClearBackground(RL_RAYWHITE);
            RL_BeginVrStereoMode(config);
                RL_BeginMode3D(camera);

                    RL_DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RL_RED);
                    RL_DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, RL_MAROON);
                    RL_DrawGrid(40, 1.0f);

                RL_EndMode3D();
            RL_EndVrStereoMode();
        RL_EndTextureMode();
        
        RL_BeginDrawing();
            RL_ClearBackground(RL_RAYWHITE);
            RL_BeginShaderMode(distortion);
                RL_DrawTexturePro(target.texture, sourceRec, destRec, (RL_Vector2){ 0.0f, 0.0f }, 0.0f, RL_WHITE);
            RL_EndShaderMode();
            RL_DrawFPS(10, 10);
        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadVrStereoConfig(config);   // Unload stereo config

    RL_UnloadRenderTexture(target);    // Unload stereo render fbo
    RL_UnloadShader(distortion);       // Unload distortion shader

    RL_CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}