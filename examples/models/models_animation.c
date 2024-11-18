/*******************************************************************************************
*
*   raylib [models] example - Load 3d model with animations and play them
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.5
*
*   Example contributed by Culacant (@culacant) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Culacant (@culacant) and Ramon Santamaria (@raysan5)
*
********************************************************************************************
*
*   NOTE: To export a model from blender, make sure it is not posed, the vertices need to be 
*         in the same position as they would be in edit mode and the scale of your models is 
*         set to 0. Scaling can be done from the export menu.
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - model animation");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 10.0f, 10.0f, 10.0f }; // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.0f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera mode type

    RL_Model model = RL_LoadModel("resources/models/iqm/guy.iqm");                    // Load the animated model mesh and basic data
    RL_Texture2D texture = RL_LoadTexture("resources/models/iqm/guytex.png");         // Load model texture and set material
    RL_SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture);     // Set model material map texture

    RL_Vector3 position = { 0.0f, 0.0f, 0.0f };            // Set model position

    // Load animation data
    int animsCount = 0;
    RL_ModelAnimation *anims = RL_LoadModelAnimations("resources/models/iqm/guyanim.iqm", &animsCount);
    int animFrameCounter = 0;

    RL_DisableCursor();                    // Catch cursor
    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        // Play animation when spacebar is held down
        if (RL_IsKeyDown(KEY_SPACE))
        {
            animFrameCounter++;
            RL_UpdateModelAnimation(model, anims[0], animFrameCounter);
            if (animFrameCounter >= anims[0].frameCount) animFrameCounter = 0;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                RL_DrawModelEx(model, position, (RL_Vector3){ 1.0f, 0.0f, 0.0f }, -90.0f, (RL_Vector3){ 1.0f, 1.0f, 1.0f }, RL_WHITE);

                for (int i = 0; i < model.boneCount; i++)
                {
                    RL_DrawCube(anims[0].framePoses[animFrameCounter][i].translation, 0.2f, 0.2f, 0.2f, RL_RED);
                }

                RL_DrawGrid(10, 1.0f);         // Draw a grid

            RL_EndMode3D();

            RL_DrawText("PRESS SPACE to PLAY MODEL ANIMATION", 10, 10, 20, RL_MAROON);
            RL_DrawText("(c) Guy IQM 3D model by @culacant", screenWidth - 200, screenHeight - 20, 10, RL_GRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(texture);                     // Unload texture
    RL_UnloadModelAnimations(anims, animsCount);   // Unload model animations data
    RL_UnloadModel(model);                         // Unload model

    RL_CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
