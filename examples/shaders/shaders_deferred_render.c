/*******************************************************************************************
*
*   raylib [shaders] example - deferred rendering
*
*   NOTE: This example requires raylib OpenGL 3.3 or OpenGL ES 3.0
*
*   Example originally created with raylib 4.5, last time updated with raylib 4.5
*
*   Example contributed by Justin Andreas Lacoste (@27justin) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023 Justin Andreas Lacoste (@27justin)
*
********************************************************************************************/

#include "raylib.h"

#include "rlgl.h"
#include "raymath.h"

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

#include <stdlib.h>         // Required for: NULL

#define MAX_CUBES   30

// GBuffer data
typedef struct GBuffer {
    unsigned int framebuffer;

    unsigned int positionTexture;
    unsigned int normalTexture;
    unsigned int albedoSpecTexture;
    
    unsigned int depthRenderbuffer;
} GBuffer;

// Deferred mode passes
typedef enum {
   DEFERRED_POSITION,
   DEFERRED_NORMAL,
   DEFERRED_ALBEDO,
   DEFERRED_SHADING
} DeferredMode;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    // -------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - deferred render");

    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 5.0f, 4.0f, 5.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 1.0f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    // Load plane model from a generated mesh
    RL_Model model = RL_LoadModelFromMesh(RL_GenMeshPlane(10.0f, 10.0f, 3, 3));
    RL_Model cube = RL_LoadModelFromMesh(RL_GenMeshCube(2.0f, 2.0f, 2.0f));

    // Load geometry buffer (G-buffer) shader and deferred shader
    RL_Shader gbufferShader = RL_LoadShader("resources/shaders/glsl330/gbuffer.vs",
                               "resources/shaders/glsl330/gbuffer.fs");

    RL_Shader deferredShader = RL_LoadShader("resources/shaders/glsl330/deferred_shading.vs",
                               "resources/shaders/glsl330/deferred_shading.fs");
    deferredShader.locs[SHADER_LOC_VECTOR_VIEW] = RL_GetShaderLocation(deferredShader, "viewPosition");

    // Initialize the G-buffer
    GBuffer gBuffer = { 0 };
    gBuffer.framebuffer = rlLoadFramebuffer();

    if (!gBuffer.framebuffer)
    {
        RL_TraceLog(LOG_WARNING, "Failed to create framebuffer");
        exit(1);
    }
    
    rlEnableFramebuffer(gBuffer.framebuffer);

    // Since we are storing position and normal data in these textures, 
    // we need to use a floating point format.
    gBuffer.positionTexture = rlLoadTexture(NULL, screenWidth, screenHeight, RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32, 1);

    gBuffer.normalTexture = rlLoadTexture(NULL, screenWidth, screenHeight, RL_PIXELFORMAT_UNCOMPRESSED_R32G32B32, 1);
    // Albedo (diffuse color) and specular strength can be combined into one texture.
    // The color in RGB, and the specular strength in the alpha channel.
    gBuffer.albedoSpecTexture = rlLoadTexture(NULL, screenWidth, screenHeight, RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);

    // Activate the draw buffers for our framebuffer
    rlActiveDrawBuffers(3);

    // Now we attach our textures to the framebuffer.
    rlFramebufferAttach(gBuffer.framebuffer, gBuffer.positionTexture, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D, 0);
    rlFramebufferAttach(gBuffer.framebuffer, gBuffer.normalTexture, RL_ATTACHMENT_COLOR_CHANNEL1, RL_ATTACHMENT_TEXTURE2D, 0);
    rlFramebufferAttach(gBuffer.framebuffer, gBuffer.albedoSpecTexture, RL_ATTACHMENT_COLOR_CHANNEL2, RL_ATTACHMENT_TEXTURE2D, 0);

    // Finally we attach the depth buffer.
    gBuffer.depthRenderbuffer = rlLoadTextureDepth(screenWidth, screenHeight, true);
    rlFramebufferAttach(gBuffer.framebuffer, gBuffer.depthRenderbuffer, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER, 0);

    // Make sure our framebuffer is complete.
    // NOTE: rlFramebufferComplete() automatically unbinds the framebuffer, so we don't have
    // to rlDisableFramebuffer() here.
    if (!rlFramebufferComplete(gBuffer.framebuffer))
    {
        RL_TraceLog(LOG_WARNING, "Framebuffer is not complete");
        exit(1);
    }

    // Now we initialize the sampler2D uniform's in the deferred shader.
    // We do this by setting the uniform's value to the color channel slot we earlier
    // bound our textures to.
    rlEnableShader(deferredShader.id);

        rlSetUniformSampler(rlGetLocationUniform(deferredShader.id, "gPosition"), 0);
        rlSetUniformSampler(rlGetLocationUniform(deferredShader.id, "gNormal"), 1);
        rlSetUniformSampler(rlGetLocationUniform(deferredShader.id, "gAlbedoSpec"), 2);

    rlDisableShader();

    // Assign out lighting shader to model
    model.materials[0].shader = gbufferShader;
    cube.materials[0].shader = gbufferShader;

    // Create lights
    //--------------------------------------------------------------------------------------
    Light lights[MAX_LIGHTS] = { 0 };
    lights[0] = CreateLight(LIGHT_POINT, (RL_Vector3){ -2, 1, -2 }, Vector3Zero(), RL_YELLOW, deferredShader);
    lights[1] = CreateLight(LIGHT_POINT, (RL_Vector3){ 2, 1, 2 }, Vector3Zero(), RL_RED, deferredShader);
    lights[2] = CreateLight(LIGHT_POINT, (RL_Vector3){ -2, 1, 2 }, Vector3Zero(), RL_GREEN, deferredShader);
    lights[3] = CreateLight(LIGHT_POINT, (RL_Vector3){ 2, 1, -2 }, Vector3Zero(), RL_BLUE, deferredShader);

    const float CUBE_SCALE = 0.25;
    RL_Vector3 cubePositions[MAX_CUBES] = { 0 };
    float cubeRotations[MAX_CUBES] = { 0 };
    
    for (int i = 0; i < MAX_CUBES; i++)
    {
        cubePositions[i] = (RL_Vector3){
            .x = (float)(rand()%10) - 5,
            .y = (float)(rand()%5),
            .z = (float)(rand()%10) - 5,
        };
        
        cubeRotations[i] = (float)(rand()%360);
    }

    DeferredMode mode = DEFERRED_SHADING;

    rlEnableDepthTest();

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_ORBITAL);

        // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
        float cameraPos[3] = { camera.position.x, camera.position.y, camera.position.z };
        RL_SetShaderValue(deferredShader, deferredShader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);
        
        // Check key inputs to enable/disable lights
        if (RL_IsKeyPressed(KEY_Y)) { lights[0].enabled = !lights[0].enabled; }
        if (RL_IsKeyPressed(KEY_R)) { lights[1].enabled = !lights[1].enabled; }
        if (RL_IsKeyPressed(KEY_G)) { lights[2].enabled = !lights[2].enabled; }
        if (RL_IsKeyPressed(KEY_B)) { lights[3].enabled = !lights[3].enabled; }

        // Check key inputs to switch between G-buffer textures
        if (RL_IsKeyPressed(KEY_ONE)) mode = DEFERRED_POSITION;
        if (RL_IsKeyPressed(KEY_TWO)) mode = DEFERRED_NORMAL;
        if (RL_IsKeyPressed(KEY_THREE)) mode = DEFERRED_ALBEDO;
        if (RL_IsKeyPressed(KEY_FOUR)) mode = DEFERRED_SHADING;

        // Update light values (actually, only enable/disable them)
        for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(deferredShader, lights[i]);
        //----------------------------------------------------------------------------------

        // Draw
        // ---------------------------------------------------------------------------------
        RL_BeginDrawing();
        
            RL_ClearBackground(RL_RAYWHITE);
        
            // Draw to the geometry buffer by first activating it
            rlEnableFramebuffer(gBuffer.framebuffer);
            rlClearScreenBuffers();  // Clear color and depth buffer
            
            rlDisableColorBlend();
            RL_BeginMode3D(camera);
                // NOTE: We have to use rlEnableShader here. `RL_BeginShaderMode` or thus `rlSetShader`
                // will not work, as they won't immediately load the shader program.
                rlEnableShader(gbufferShader.id);
                    // When drawing a model here, make sure that the material's shaders
                    // are set to the gbuffer shader!
                    RL_DrawModel(model, Vector3Zero(), 1.0f, RL_WHITE);
                    RL_DrawModel(cube, (RL_Vector3) { 0.0, 1.0f, 0.0 }, 1.0f, RL_WHITE);

                    for (int i = 0; i < MAX_CUBES; i++)
                    {
                        RL_Vector3 position = cubePositions[i];
                        RL_DrawModelEx(cube, position, (RL_Vector3) { 1, 1, 1 }, cubeRotations[i], (RL_Vector3) { CUBE_SCALE, CUBE_SCALE, CUBE_SCALE }, RL_WHITE);
                    }

                rlDisableShader();
            RL_EndMode3D();
            rlEnableColorBlend();

            // Go back to the default framebuffer (0) and draw our deferred shading.
            rlDisableFramebuffer();
            rlClearScreenBuffers(); // Clear color & depth buffer

            switch (mode)
            {
                case DEFERRED_SHADING:
                {
                    RL_BeginMode3D(camera);
                        rlDisableColorBlend();
                        rlEnableShader(deferredShader.id);
                            // Activate our g-buffer textures
                            // These will now be bound to the sampler2D uniforms `gPosition`, `gNormal`,
                            // and `gAlbedoSpec`
                            rlActiveTextureSlot(0);
                            rlEnableTexture(gBuffer.positionTexture);
                            rlActiveTextureSlot(1);
                            rlEnableTexture(gBuffer.normalTexture);
                            rlActiveTextureSlot(2);
                            rlEnableTexture(gBuffer.albedoSpecTexture);

                            // Finally, we draw a fullscreen quad to our default framebuffer
                            // This will now be shaded using our deferred shader
                            rlLoadDrawQuad();
                        rlDisableShader();
                        rlEnableColorBlend();
                    RL_EndMode3D();

                    // As a last step, we now copy over the depth buffer from our g-buffer to the default framebuffer.
                    rlBindFramebuffer(RL_READ_FRAMEBUFFER, gBuffer.framebuffer);
                    rlBindFramebuffer(RL_DRAW_FRAMEBUFFER, 0);
                    rlBlitFramebuffer(0, 0, screenWidth, screenHeight, 0, 0, screenWidth, screenHeight, 0x00000100);    // GL_DEPTH_BUFFER_BIT
                    rlDisableFramebuffer();

                    // Since our shader is now done and disabled, we can draw our lights in default
                    // forward rendering
                    RL_BeginMode3D(camera);
                        rlEnableShader(rlGetShaderIdDefault());
                            for(int i = 0; i < MAX_LIGHTS; i++)
                            {
                                if (lights[i].enabled) RL_DrawSphereEx(lights[i].position, 0.2f, 8, 8, lights[i].color);
                                else RL_DrawSphereWires(lights[i].position, 0.2f, 8, 8, RL_ColorAlpha(lights[i].color, 0.3f));
                            }
                        rlDisableShader();
                    RL_EndMode3D();
                    
                    RL_DrawText("FINAL RESULT", 10, screenHeight - 30, 20, RL_DARKGREEN);
                } break;
                case DEFERRED_POSITION:
                {
                    RL_DrawTextureRec((RL_Texture2D){
                        .id = gBuffer.positionTexture,
                        .width = screenWidth,
                        .height = screenHeight,
                    }, (RL_Rectangle) { 0, 0, (float)screenWidth, (float)-screenHeight }, Vector2Zero(), RL_RAYWHITE);
                    
                    RL_DrawText("POSITION TEXTURE", 10, screenHeight - 30, 20, RL_DARKGREEN);
                } break;
                case DEFERRED_NORMAL:
                {
                    RL_DrawTextureRec((RL_Texture2D){
                        .id = gBuffer.normalTexture,
                        .width = screenWidth,
                        .height = screenHeight,
                    }, (RL_Rectangle) { 0, 0, (float)screenWidth, (float)-screenHeight }, Vector2Zero(), RL_RAYWHITE);
                    
                    RL_DrawText("NORMAL TEXTURE", 10, screenHeight - 30, 20, RL_DARKGREEN);
                } break;
                case DEFERRED_ALBEDO:
                {
                    RL_DrawTextureRec((RL_Texture2D){
                        .id = gBuffer.albedoSpecTexture,
                        .width = screenWidth,
                        .height = screenHeight,
                    }, (RL_Rectangle) { 0, 0, (float)screenWidth, (float)-screenHeight }, Vector2Zero(), RL_RAYWHITE);
                    
                    RL_DrawText("ALBEDO TEXTURE", 10, screenHeight - 30, 20, RL_DARKGREEN);
                } break;
                default: break;
            }

            RL_DrawText("Toggle lights keys: [Y][R][G][B]", 10, 40, 20, RL_DARKGRAY);
            RL_DrawText("Switch G-buffer textures: [1][2][3][4]", 10, 70, 20, RL_DARKGRAY);

            RL_DrawFPS(10, 10);
            
        RL_EndDrawing();
        // -----------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadModel(model);     // Unload the models
    RL_UnloadModel(cube);

    RL_UnloadShader(deferredShader); // Unload shaders
    RL_UnloadShader(gbufferShader);

    // Unload geometry buffer and all attached textures
    rlUnloadFramebuffer(gBuffer.framebuffer);
    rlUnloadTexture(gBuffer.positionTexture);
    rlUnloadTexture(gBuffer.normalTexture);
    rlUnloadTexture(gBuffer.albedoSpecTexture);
    rlUnloadTexture(gBuffer.depthRenderbuffer);

    RL_CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
