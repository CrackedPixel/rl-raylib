/*******************************************************************************************
*
*   raylib [core] example - Doing skinning on the gpu using a vertex shader
* 
*   Example originally created with raylib 4.5, last time updated with raylib 4.5
*
*   Example contributed by Daniel Holden (@orangeduck) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2024 Daniel Holden (@orangeduck)
* 
*   Note: Due to limitations in the Apple OpenGL driver, this feature does not work on MacOS
*
********************************************************************************************/

#include "raylib.h"

#include "raymath.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - GPU skinning");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 5.0f, 5.0f, 5.0f }; // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 2.0f, 0.0f };  // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };      // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                            // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;         // RL_Camera projection type

    // Load gltf model
    RL_Model characterModel = RL_LoadModel("resources/models/gltf/greenman.glb"); // Load character model
    
    // Load skinning shader
    RL_Shader skinningShader = RL_LoadShader(RL_TextFormat("resources/shaders/glsl%i/skinning.vs", GLSL_VERSION),
                                       RL_TextFormat("resources/shaders/glsl%i/skinning.fs", GLSL_VERSION));
    
    characterModel.materials[1].shader = skinningShader;
    
    // Load gltf model animations
    int animsCount = 0;
    unsigned int animIndex = 0;
    unsigned int animCurrentFrame = 0;
    RL_ModelAnimation *modelAnimations = RL_LoadModelAnimations("resources/models/gltf/greenman.glb", &animsCount);

    RL_Vector3 position = { 0.0f, 0.0f, 0.0f }; // Set model position

    RL_DisableCursor();                    // Limit cursor to relative movement inside the window

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        
        // Select current animation
        if (RL_IsKeyPressed(KEY_T)) animIndex = (animIndex + 1)%animsCount;
        else if (RL_IsKeyPressed(KEY_G)) animIndex = (animIndex + animsCount - 1)%animsCount;

        // Update model animation
        RL_ModelAnimation anim = modelAnimations[animIndex];
        animCurrentFrame = (animCurrentFrame + 1)%anim.frameCount;
        characterModel.transform = MatrixTranslate(position.x, position.y, position.z);
        UpdateModelAnimationBones(characterModel, anim, animCurrentFrame);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);
            
                // Draw character mesh, pose calculation is done in shader (GPU skinning)
                RL_DrawMesh(characterModel.meshes[0], characterModel.materials[1], characterModel.transform);

                RL_DrawGrid(10, 1.0f);
                
            RL_EndMode3D();

            RL_DrawText("Use the T/G to switch animation", 10, 10, 20, RL_GRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadModelAnimations(modelAnimations, animsCount); // Unload model animation
    RL_UnloadModel(characterModel);    // Unload model and meshes/material
    RL_UnloadShader(skinningShader);   // Unload GPU skinning shader
    
    RL_CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}