/*******************************************************************************************
*
*   raylib [shaders] example - Shadowmap
*
*   Example originally created with raylib 5.0, last time updated with raylib 5.0
*
*   Example contributed by @TheManTheMythTheGameDev and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            120
#endif

#define SHADOWMAP_RESOLUTION 1024

RL_RenderTexture2D LoadShadowmapRenderTexture(int width, int height);
void UnloadShadowmapRenderTexture(RL_RenderTexture2D target);
void DrawScene(RL_Model cube, RL_Model robot);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_SetConfigFlags(FLAG_MSAA_4X_HINT);
    // Shadows are a HUGE topic, and this example shows an extremely simple implementation of the shadowmapping algorithm,
    // which is the industry standard for shadows. This algorithm can be extended in a ridiculous number of ways to improve
    // realism and also adapt it for different scenes. This is pretty much the simplest possible implementation.
    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - shadowmap");

    RL_Camera3D cam = (RL_Camera3D){ 0 };
    cam.position = (RL_Vector3){ 10.0f, 10.0f, 10.0f };
    cam.target = Vector3Zero();
    cam.projection = CAMERA_PERSPECTIVE;
    cam.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };
    cam.fovy = 45.0f;

    RL_Shader shadowShader = RL_LoadShader(RL_TextFormat("resources/shaders/glsl%i/shadowmap.vs", GLSL_VERSION),
                                     RL_TextFormat("resources/shaders/glsl%i/shadowmap.fs", GLSL_VERSION));
    shadowShader.locs[SHADER_LOC_VECTOR_VIEW] = RL_GetShaderLocation(shadowShader, "viewPos");
    RL_Vector3 lightDir = Vector3Normalize((RL_Vector3){ 0.35f, -1.0f, -0.35f });
    RL_Color lightColor = RL_WHITE;
    RL_Vector4 lightColorNormalized = RL_ColorNormalize(lightColor);
    int lightDirLoc = RL_GetShaderLocation(shadowShader, "lightDir");
    int lightColLoc = RL_GetShaderLocation(shadowShader, "lightColor");
    RL_SetShaderValue(shadowShader, lightDirLoc, &lightDir, SHADER_UNIFORM_VEC3);
    RL_SetShaderValue(shadowShader, lightColLoc, &lightColorNormalized, SHADER_UNIFORM_VEC4);
    int ambientLoc = RL_GetShaderLocation(shadowShader, "ambient");
    float ambient[4] = {0.1f, 0.1f, 0.1f, 1.0f};
    RL_SetShaderValue(shadowShader, ambientLoc, ambient, SHADER_UNIFORM_VEC4);
    int lightVPLoc = RL_GetShaderLocation(shadowShader, "lightVP");
    int shadowMapLoc = RL_GetShaderLocation(shadowShader, "shadowMap");
    int shadowMapResolution = SHADOWMAP_RESOLUTION;
    RL_SetShaderValue(shadowShader, RL_GetShaderLocation(shadowShader, "shadowMapResolution"), &shadowMapResolution, SHADER_UNIFORM_INT);

    RL_Model cube = RL_LoadModelFromMesh(RL_GenMeshCube(1.0f, 1.0f, 1.0f));
    cube.materials[0].shader = shadowShader;
    RL_Model robot = RL_LoadModel("resources/models/robot.glb");
    for (int i = 0; i < robot.materialCount; i++)
    {
        robot.materials[i].shader = shadowShader;
    }
    int animCount = 0;
    RL_ModelAnimation* robotAnimations = RL_LoadModelAnimations("resources/models/robot.glb", &animCount);

    RL_RenderTexture2D shadowMap = LoadShadowmapRenderTexture(SHADOWMAP_RESOLUTION, SHADOWMAP_RESOLUTION);
    // For the shadowmapping algorithm, we will be rendering everything from the light's point of view
    RL_Camera3D lightCam = (RL_Camera3D){ 0 };
    lightCam.position = Vector3Scale(lightDir, -15.0f);
    lightCam.target = Vector3Zero();
    // Use an orthographic projection for directional lights
    lightCam.projection = CAMERA_ORTHOGRAPHIC;
    lightCam.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };
    lightCam.fovy = 20.0f;

    RL_SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    int fc = 0;

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        float dt = RL_GetFrameTime();

        RL_Vector3 cameraPos = cam.position;
        RL_SetShaderValue(shadowShader, shadowShader.locs[SHADER_LOC_VECTOR_VIEW], &cameraPos, SHADER_UNIFORM_VEC3);
        RL_UpdateCamera(&cam, CAMERA_ORBITAL);

        fc++;
        fc %= (robotAnimations[0].frameCount);
        RL_UpdateModelAnimation(robot, robotAnimations[0], fc);

        const float cameraSpeed = 0.05f;
        if (RL_IsKeyDown(KEY_LEFT))
        {
            if (lightDir.x < 0.6f)
                lightDir.x += cameraSpeed * 60.0f * dt;
        }
        if (RL_IsKeyDown(KEY_RIGHT))
        {
            if (lightDir.x > -0.6f)
                lightDir.x -= cameraSpeed * 60.0f * dt;
        }
        if (RL_IsKeyDown(KEY_UP))
        {
            if (lightDir.z < 0.6f)
                lightDir.z += cameraSpeed * 60.0f * dt;
        }
        if (RL_IsKeyDown(KEY_DOWN))
        {
            if (lightDir.z > -0.6f)
                lightDir.z -= cameraSpeed * 60.0f * dt;
        }
        lightDir = Vector3Normalize(lightDir);
        lightCam.position = Vector3Scale(lightDir, -15.0f);
        RL_SetShaderValue(shadowShader, lightDirLoc, &lightDir, SHADER_UNIFORM_VEC3);

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

        // First, render all objects into the shadowmap
        // The idea is, we record all the objects' depths (as rendered from the light source's point of view) in a buffer
        // Anything that is "visible" to the light is in light, anything that isn't is in shadow
        // We can later use the depth buffer when rendering everything from the player's point of view
        // to determine whether a given point is "visible" to the light

        // Record the light matrices for future use!
        RL_Matrix lightView;
        RL_Matrix lightProj;
        RL_BeginTextureMode(shadowMap);
        RL_ClearBackground(RL_WHITE);
        RL_BeginMode3D(lightCam);
            lightView = rlGetMatrixModelview();
            lightProj = rlGetMatrixProjection();
            DrawScene(cube, robot);
        RL_EndMode3D();
        RL_EndTextureMode();
        RL_Matrix lightViewProj = MatrixMultiply(lightView, lightProj);

        RL_ClearBackground(RL_RAYWHITE);

        RL_SetShaderValueMatrix(shadowShader, lightVPLoc, lightViewProj);

        rlEnableShader(shadowShader.id);
        int slot = 10; // Can be anything 0 to 15, but 0 will probably be taken up
        rlActiveTextureSlot(10);
        rlEnableTexture(shadowMap.depth.id);
        rlSetUniform(shadowMapLoc, &slot, SHADER_UNIFORM_INT, 1);

        RL_BeginMode3D(cam);

            // Draw the same exact things as we drew in the shadowmap!
            DrawScene(cube, robot);
        
        RL_EndMode3D();

        RL_DrawText("Shadows in raylib using the shadowmapping algorithm!", screenWidth - 320, screenHeight - 20, 10, RL_GRAY);
        RL_DrawText("Use the arrow keys to rotate the light!", 10, 10, 30, RL_RED);

        RL_EndDrawing();

        if (RL_IsKeyPressed(KEY_F))
        {
            RL_TakeScreenshot("shaders_shadowmap.png");
        }
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    RL_UnloadShader(shadowShader);
    RL_UnloadModel(cube);
    RL_UnloadModel(robot);
    RL_UnloadModelAnimations(robotAnimations, animCount);
    UnloadShadowmapRenderTexture(shadowMap);

    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

RL_RenderTexture2D LoadShadowmapRenderTexture(int width, int height)
{
    RL_RenderTexture2D target = { 0 };

    target.id = rlLoadFramebuffer(); // Load an empty framebuffer
    target.texture.width = width;
    target.texture.height = height;

    if (target.id > 0)
    {
        rlEnableFramebuffer(target.id);

        // Create depth texture
        // We don't need a color texture for the shadowmap
        target.depth.id = rlLoadTextureDepth(width, height, false);
        target.depth.width = width;
        target.depth.height = height;
        target.depth.format = 19;       //DEPTH_COMPONENT_24BIT?
        target.depth.mipmaps = 1;

        // Attach depth texture to FBO
        rlFramebufferAttach(target.id, target.depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D, 0);

        // Check if fbo is complete with attachments (valid)
        if (rlFramebufferComplete(target.id)) TRACELOG(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", target.id);

        rlDisableFramebuffer();
    }
    else TRACELOG(LOG_WARNING, "FBO: Framebuffer object can not be created");

    return target;
}

// Unload shadowmap render texture from GPU memory (VRAM)
void UnloadShadowmapRenderTexture(RL_RenderTexture2D target)
{
    if (target.id > 0)
    {
        // NOTE: Depth texture/renderbuffer is automatically
        // queried and deleted before deleting framebuffer
        rlUnloadFramebuffer(target.id);
    }
}

void DrawScene(RL_Model cube, RL_Model robot)
{
    RL_DrawModelEx(cube, Vector3Zero(), (RL_Vector3) { 0.0f, 1.0f, 0.0f }, 0.0f, (RL_Vector3) { 10.0f, 1.0f, 10.0f }, RL_BLUE);
    RL_DrawModelEx(cube, (RL_Vector3) { 1.5f, 1.0f, -1.5f }, (RL_Vector3) { 0.0f, 1.0f, 0.0f }, 0.0f, Vector3One(), RL_WHITE);
    RL_DrawModelEx(robot, (RL_Vector3) { 0.0f, 0.5f, 0.0f }, (RL_Vector3) { 0.0f, 1.0f, 0.0f }, 0.0f, (RL_Vector3) { 1.0f, 1.0f, 1.0f }, RL_RED);
}
