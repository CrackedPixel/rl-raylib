/*******************************************************************************************
*
*   raylib [models] example - Skybox loading and drawing
*
*   Example originally created with raylib 1.8, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include "rlgl.h"
#include "raymath.h"      // Required for: MatrixPerspective(), MatrixLookAt()

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

// Generate cubemap (6 faces) from equirectangular (panorama) texture
static RL_TextureCubemap GenTextureCubemap(RL_Shader shader, RL_Texture2D panorama, int size, int format);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - skybox loading and drawing");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 1.0f, 1.0f, 1.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 4.0f, 1.0f, 4.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    // Load skybox model
    RL_Mesh cube = RL_GenMeshCube(1.0f, 1.0f, 1.0f);
    RL_Model skybox = RL_LoadModelFromMesh(cube);

    // Set this to true to use an HDR RL_Texture, Note that raylib must be built with HDR Support for this to work SUPPORT_FILEFORMAT_HDR
    bool useHDR = false;

    // Load skybox shader and set required locations
    // NOTE: Some locations are automatically set at shader loading
    skybox.materials[0].shader = RL_LoadShader(RL_TextFormat("resources/shaders/glsl%i/skybox.vs", GLSL_VERSION),
                                            RL_TextFormat("resources/shaders/glsl%i/skybox.fs", GLSL_VERSION));

    RL_SetShaderValue(skybox.materials[0].shader, RL_GetShaderLocation(skybox.materials[0].shader, "environmentMap"), (int[1]){ MATERIAL_MAP_CUBEMAP }, SHADER_UNIFORM_INT);
    RL_SetShaderValue(skybox.materials[0].shader, RL_GetShaderLocation(skybox.materials[0].shader, "doGamma"), (int[1]) { useHDR ? 1 : 0 }, SHADER_UNIFORM_INT);
    RL_SetShaderValue(skybox.materials[0].shader, RL_GetShaderLocation(skybox.materials[0].shader, "vflipped"), (int[1]){ useHDR ? 1 : 0 }, SHADER_UNIFORM_INT);

    // Load cubemap shader and setup required shader locations
    RL_Shader shdrCubemap = RL_LoadShader(RL_TextFormat("resources/shaders/glsl%i/cubemap.vs", GLSL_VERSION),
                                    RL_TextFormat("resources/shaders/glsl%i/cubemap.fs", GLSL_VERSION));

    RL_SetShaderValue(shdrCubemap, RL_GetShaderLocation(shdrCubemap, "equirectangularMap"), (int[1]){ 0 }, SHADER_UNIFORM_INT);

    char skyboxFileName[256] = { 0 };
    
    if (useHDR)
    {
        RL_TextCopy(skyboxFileName, "resources/dresden_square_2k.hdr");

        // Load HDR panorama (sphere) texture
        RL_Texture2D panorama = RL_LoadTexture(skyboxFileName);

        // Generate cubemap (texture with 6 quads-cube-mapping) from panorama HDR texture
        // NOTE 1: New texture is generated rendering to texture, shader calculates the sphere->cube coordinates mapping
        // NOTE 2: It seems on some Android devices WebGL, fbo does not properly support a FLOAT-based attachment,
        // despite texture can be successfully created.. so using PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 instead of PIXELFORMAT_UNCOMPRESSED_R32G32B32A32
        skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = GenTextureCubemap(shdrCubemap, panorama, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

        RL_UnloadTexture(panorama);        // RL_Texture not required anymore, cubemap already generated
    }
    else
    {
        RL_Image img = RL_LoadImage("resources/skybox.png");
        skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = RL_LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);    // CUBEMAP_LAYOUT_PANORAMA
        RL_UnloadImage(img);
    }

    RL_DisableCursor();                    // Limit cursor to relative movement inside the window

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        // Load new cubemap texture on drag&drop
        if (RL_IsFileDropped())
        {
            RL_FilePathList droppedFiles = RL_LoadDroppedFiles();

            if (droppedFiles.count == 1)         // Only support one file dropped
            {
                if (RL_IsFileExtension(droppedFiles.paths[0], ".png;.jpg;.hdr;.bmp;.tga"))
                {
                    // Unload current cubemap texture to load new one
                    RL_UnloadTexture(skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);
                    
                    if (useHDR)
                    {
                        // Load HDR panorama (sphere) texture
                        RL_Texture2D panorama = RL_LoadTexture(droppedFiles.paths[0]);

                        // Generate cubemap from panorama texture
                        skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = GenTextureCubemap(shdrCubemap, panorama, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
                        
                        RL_UnloadTexture(panorama);    // RL_Texture not required anymore, cubemap already generated
                    }
                    else
                    {
                        RL_Image img = RL_LoadImage(droppedFiles.paths[0]);
                        skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = RL_LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);
                        RL_UnloadImage(img);
                    }

                    RL_TextCopy(skyboxFileName, droppedFiles.paths[0]);
                }
            }

            RL_UnloadDroppedFiles(droppedFiles);    // Unload filepaths from memory
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                // We are inside the cube, we need to disable backface culling!
                rlDisableBackfaceCulling();
                rlDisableDepthMask();
                    RL_DrawModel(skybox, (RL_Vector3){0, 0, 0}, 1.0f, RL_WHITE);
                rlEnableBackfaceCulling();
                rlEnableDepthMask();

                RL_DrawGrid(10, 1.0f);

            RL_EndMode3D();

            if (useHDR) RL_DrawText(RL_TextFormat("Panorama image from hdrihaven.com: %s", RL_GetFileName(skyboxFileName)), 10, RL_GetScreenHeight() - 20, 10, RL_BLACK);
            else RL_DrawText(RL_TextFormat(": %s", RL_GetFileName(skyboxFileName)), 10, RL_GetScreenHeight() - 20, 10, RL_BLACK);

            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadShader(skybox.materials[0].shader);
    RL_UnloadTexture(skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);

    RL_UnloadModel(skybox);        // Unload skybox model

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Generate cubemap texture from HDR texture
static RL_TextureCubemap GenTextureCubemap(RL_Shader shader, RL_Texture2D panorama, int size, int format)
{
    RL_TextureCubemap cubemap = { 0 };

    rlDisableBackfaceCulling();     // Disable backface culling to render inside the cube

    // STEP 1: Setup framebuffer
    //------------------------------------------------------------------------------------------
    unsigned int rbo = rlLoadTextureDepth(size, size, true);
    cubemap.id = rlLoadTextureCubemap(0, size, format, 1);

    unsigned int fbo = rlLoadFramebuffer();
    rlFramebufferAttach(fbo, rbo, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER, 0);
    rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X, 0);

    // Check if framebuffer is complete with attachments (valid)
    if (rlFramebufferComplete(fbo)) RL_TraceLog(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", fbo);
    //------------------------------------------------------------------------------------------

    // STEP 2: Draw to framebuffer
    //------------------------------------------------------------------------------------------
    // NOTE: RL_Shader is used to convert HDR equirectangular environment map to cubemap equivalent (6 faces)
    rlEnableShader(shader.id);

    // Define projection matrix and send it to shader
    RL_Matrix matFboProjection = MatrixPerspective(90.0*DEG2RAD, 1.0, rlGetCullDistanceNear(), rlGetCullDistanceFar());
    rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_PROJECTION], matFboProjection);

    // Define view matrix for every side of the cubemap
    RL_Matrix fboViews[6] = {
        MatrixLookAt((RL_Vector3){ 0.0f, 0.0f, 0.0f }, (RL_Vector3){  1.0f,  0.0f,  0.0f }, (RL_Vector3){ 0.0f, -1.0f,  0.0f }),
        MatrixLookAt((RL_Vector3){ 0.0f, 0.0f, 0.0f }, (RL_Vector3){ -1.0f,  0.0f,  0.0f }, (RL_Vector3){ 0.0f, -1.0f,  0.0f }),
        MatrixLookAt((RL_Vector3){ 0.0f, 0.0f, 0.0f }, (RL_Vector3){  0.0f,  1.0f,  0.0f }, (RL_Vector3){ 0.0f,  0.0f,  1.0f }),
        MatrixLookAt((RL_Vector3){ 0.0f, 0.0f, 0.0f }, (RL_Vector3){  0.0f, -1.0f,  0.0f }, (RL_Vector3){ 0.0f,  0.0f, -1.0f }),
        MatrixLookAt((RL_Vector3){ 0.0f, 0.0f, 0.0f }, (RL_Vector3){  0.0f,  0.0f,  1.0f }, (RL_Vector3){ 0.0f, -1.0f,  0.0f }),
        MatrixLookAt((RL_Vector3){ 0.0f, 0.0f, 0.0f }, (RL_Vector3){  0.0f,  0.0f, -1.0f }, (RL_Vector3){ 0.0f, -1.0f,  0.0f })
    };

    rlViewport(0, 0, size, size);   // Set viewport to current fbo dimensions
    
    // Activate and enable texture for drawing to cubemap faces
    rlActiveTextureSlot(0);
    rlEnableTexture(panorama.id);

    for (int i = 0; i < 6; i++)
    {
        // Set the view matrix for the current cube face
        rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_VIEW], fboViews[i]);
        
        // Select the current cubemap face attachment for the fbo
        // WARNING: This function by default enables->attach->disables fbo!!!
        rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X + i, 0);
        rlEnableFramebuffer(fbo);

        // Load and draw a cube, it uses the current enabled texture
        rlClearScreenBuffers();
        rlLoadDrawCube();

        // ALTERNATIVE: Try to use internal batch system to draw the cube instead of rlLoadDrawCube
        // for some reason this method does not work, maybe due to cube triangles definition? normals pointing out?
        // TODO: Investigate this issue...
        //rlSetTexture(panorama.id); // WARNING: It must be called after enabling current framebuffer if using internal batch system!
        //rlClearScreenBuffers();
        //RL_DrawCubeV(Vector3Zero(), Vector3One(), RL_WHITE);
        //rlDrawRenderBatchActive();
    }
    //------------------------------------------------------------------------------------------

    // STEP 3: Unload framebuffer and reset state
    //------------------------------------------------------------------------------------------
    rlDisableShader();          // Unbind shader
    rlDisableTexture();         // Unbind texture
    rlDisableFramebuffer();     // Unbind framebuffer
    rlUnloadFramebuffer(fbo);   // Unload framebuffer (and automatically attached depth texture/renderbuffer)

    // Reset viewport dimensions to default
    rlViewport(0, 0, rlGetFramebufferWidth(), rlGetFramebufferHeight());
    rlEnableBackfaceCulling();
    //------------------------------------------------------------------------------------------

    cubemap.width = size;
    cubemap.height = size;
    cubemap.mipmaps = 1;
    cubemap.format = format;

    return cubemap;
}
