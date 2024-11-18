/*******************************************************************************************
*
*   raylib [shaders] example - lightmap
*
*   NOTE: This example requires raylib OpenGL 3.3 or ES2 versions for shaders support,
*         OpenGL 1.1 does not support shaders, recompile raylib to OpenGL 3.3 version.
*
*   NOTE: Shaders used in this example are #version 330 (OpenGL 3.3).
*
*   Example contributed by Jussi Viitala (@nullstare) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Jussi Viitala (@nullstare) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

#define MAP_SIZE 10

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - lightmap");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 4.0f, 6.0f, 8.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.0f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    RL_Mesh mesh = RL_GenMeshPlane((float)MAP_SIZE, (float)MAP_SIZE, 1, 1);

    // RL_GenMeshPlane doesn't generate texcoords2 so we will upload them separately
    mesh.texcoords2 = (float *)RL_MALLOC(mesh.vertexCount*2*sizeof(float));

    // X                          // Y
    mesh.texcoords2[0] = 0.0f;    mesh.texcoords2[1] = 0.0f;
    mesh.texcoords2[2] = 1.0f;    mesh.texcoords2[3] = 0.0f;
    mesh.texcoords2[4] = 0.0f;    mesh.texcoords2[5] = 1.0f;
    mesh.texcoords2[6] = 1.0f;    mesh.texcoords2[7] = 1.0f;

    // Load a new texcoords2 attributes buffer
    mesh.vboId[SHADER_LOC_VERTEX_TEXCOORD02] = rlLoadVertexBuffer(mesh.texcoords2, mesh.vertexCount*2*sizeof(float), false);
    rlEnableVertexArray(mesh.vaoId);
    
    // Index 5 is for texcoords2
    rlSetVertexAttribute(5, 2, RL_FLOAT, 0, 0, 0);
    rlEnableVertexAttribute(5);
    rlDisableVertexArray();

    // Load lightmap shader
    RL_Shader shader = RL_LoadShader(RL_TextFormat("resources/shaders/glsl%i/lightmap.vs", GLSL_VERSION),
                               RL_TextFormat("resources/shaders/glsl%i/lightmap.fs", GLSL_VERSION));

    RL_Texture texture = RL_LoadTexture("resources/cubicmap_atlas.png");
    RL_Texture light = RL_LoadTexture("resources/spark_flame.png");

    RL_GenTextureMipmaps(&texture);
    RL_SetTextureFilter(texture, TEXTURE_FILTER_TRILINEAR);

    RL_RenderTexture lightmap = RL_LoadRenderTexture(MAP_SIZE, MAP_SIZE);

    RL_SetTextureFilter(lightmap.texture, TEXTURE_FILTER_TRILINEAR);

    RL_Material material = RL_LoadMaterialDefault();
    material.shader = shader;
    material.maps[MATERIAL_MAP_ALBEDO].texture = texture;
    material.maps[MATERIAL_MAP_METALNESS].texture = lightmap.texture;

    // Drawing to lightmap
    RL_BeginTextureMode(lightmap);
        RL_ClearBackground(RL_BLACK);

        RL_BeginBlendMode(BLEND_ADDITIVE);
            RL_DrawTexturePro(
                light,
                (RL_Rectangle){ 0, 0, light.width, light.height },
                (RL_Rectangle){ 0, 0, 20, 20 },
                (RL_Vector2){ 10.0, 10.0 },
                0.0,
                RL_RED
            );
            RL_DrawTexturePro(
                light,
                (RL_Rectangle){ 0, 0, light.width, light.height },
                (RL_Rectangle){ 8, 4, 20, 20 },
                (RL_Vector2){ 10.0, 10.0 },
                0.0,
                RL_BLUE
            );
            RL_DrawTexturePro(
                light,
                (RL_Rectangle){ 0, 0, light.width, light.height },
                (RL_Rectangle){ 8, 8, 10, 10 },
                (RL_Vector2){ 5.0, 5.0 },
                0.0,
                RL_GREEN
            );
        RL_BeginBlendMode(BLEND_ALPHA);
    RL_EndTextureMode();

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_ORBITAL);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();
            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);
                RL_DrawMesh(mesh, material, MatrixIdentity());
            RL_EndMode3D();

            RL_DrawFPS(10, 10);

            RL_DrawTexturePro(
                lightmap.texture,
                (RL_Rectangle){ 0, 0, -MAP_SIZE, -MAP_SIZE },
                (RL_Rectangle){ RL_GetRenderWidth() - MAP_SIZE*8 - 10, 10, MAP_SIZE*8, MAP_SIZE*8 },
                (RL_Vector2){ 0.0, 0.0 },
                0.0,
                RL_WHITE);
                
            RL_DrawText("lightmap", RL_GetRenderWidth() - 66, 16 + MAP_SIZE*8, 10, RL_GRAY);
            RL_DrawText("10x10 pixels", RL_GetRenderWidth() - 76, 30 + MAP_SIZE*8, 10, RL_GRAY);
                
        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadMesh(mesh);       // Unload the mesh
    RL_UnloadShader(shader);   // Unload shader
    RL_UnloadTexture(texture); // Unload texture
    RL_UnloadTexture(light);   // Unload texture

    RL_CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
