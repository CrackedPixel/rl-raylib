/*******************************************************************************************
*
*   raylib [models] example - loading gltf with animations
*
*   LIMITATIONS:
*     - Only supports 1 armature per file, and skips loading it if there are multiple armatures
*     - Only supports linear interpolation (default method in Blender when checked
*       "Always Sample Animations" when exporting a GLTF file)
*     - Only supports translation/rotation/scale animation channel.path,
*       weights not considered (i.e. morph targets)
*
*   Example originally created with raylib 3.7, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2020-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - loading gltf animations");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 6.0f, 6.0f, 6.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 2.0f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    // Load gltf model
    RL_Model model = RL_LoadModel("resources/models/gltf/robot.glb");
    RL_Vector3 position = { 0.0f, 0.0f, 0.0f }; // Set model position
    
    // Load gltf model animations
    int animsCount = 0;
    unsigned int animIndex = 0;
    unsigned int animCurrentFrame = 0;
    RL_ModelAnimation *modelAnimations = RL_LoadModelAnimations("resources/models/gltf/robot.glb", &animsCount);

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_ORBITAL);

        // Select current animation
        if (RL_IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) animIndex = (animIndex + 1)%animsCount;
        else if (RL_IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) animIndex = (animIndex + animsCount - 1)%animsCount;

        // Update model animation
        RL_ModelAnimation anim = modelAnimations[animIndex];
        animCurrentFrame = (animCurrentFrame + 1)%anim.frameCount;
        RL_UpdateModelAnimation(model, anim, animCurrentFrame);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);
                RL_DrawModel(model, position, 1.0f, RL_WHITE);    // Draw animated model
                RL_DrawGrid(10, 1.0f);
            RL_EndMode3D();

            RL_DrawText("Use the LEFT/RIGHT mouse buttons to switch animation", 10, 10, 20, RL_GRAY);
            RL_DrawText(RL_TextFormat("Animation: %s", anim.name), 10, RL_GetScreenHeight() - 20, 10, RL_DARKGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadModel(model);         // Unload model and meshes/material

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}



