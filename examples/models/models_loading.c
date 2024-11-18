/*******************************************************************************************
*
*   raylib [models] example - Models loading
*
*   NOTE: raylib supports multiple models file formats:
*
*     - OBJ  > Text file format. Must include vertex position-texcoords-normals information,
*              if files references some .mtl materials file, it will be loaded (or try to).
*     - GLTF > Text/binary file format. Includes lot of information and it could
*              also reference external files, raylib will try loading mesh and materials data.
*     - IQM  > Binary file format. Includes mesh vertex data but also animation data,
*              raylib can load .iqm animations.
*     - VOX  > Binary file format. MagikaVoxel mesh format:
*              https://github.com/ephtracy/voxel-model/blob/master/MagicaVoxel-file-format-vox.txt
*     - M3D  > Binary file format. RL_Model 3D format:
*              https://bztsrc.gitlab.io/model3d
*
*   Example originally created with raylib 2.0, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2024 Ramon Santamaria (@raysan5)
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

    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - models loading");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 50.0f, 50.0f, 50.0f }; // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 10.0f, 0.0f };     // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // RL_Camera mode type

    RL_Model model = RL_LoadModel("resources/models/obj/castle.obj");                 // Load model
    RL_Texture2D texture = RL_LoadTexture("resources/models/obj/castle_diffuse.png"); // Load model texture
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;            // Set map diffuse texture

    RL_Vector3 position = { 0.0f, 0.0f, 0.0f };                    // Set model position

    RL_BoundingBox bounds = RL_GetMeshBoundingBox(model.meshes[0]);   // Set model bounds

    // NOTE: bounds are calculated from the original size of the model,
    // if model is scaled on drawing, bounds must be also scaled

    bool selected = false;          // Selected object flag

    RL_DisableCursor();                // Limit cursor to relative movement inside the window

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        // Load new models/textures on drag&drop
        if (RL_IsFileDropped())
        {
            RL_FilePathList droppedFiles = RL_LoadDroppedFiles();

            if (droppedFiles.count == 1) // Only support one file dropped
            {
                if (RL_IsFileExtension(droppedFiles.paths[0], ".obj") ||
                    RL_IsFileExtension(droppedFiles.paths[0], ".gltf") ||
                    RL_IsFileExtension(droppedFiles.paths[0], ".glb") ||
                    RL_IsFileExtension(droppedFiles.paths[0], ".vox") ||
                    RL_IsFileExtension(droppedFiles.paths[0], ".iqm") ||
                    RL_IsFileExtension(droppedFiles.paths[0], ".m3d"))       // RL_Model file formats supported
                {
                    RL_UnloadModel(model);                         // Unload previous model
                    model = RL_LoadModel(droppedFiles.paths[0]);   // Load new model
                    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Set current map diffuse texture

                    bounds = RL_GetMeshBoundingBox(model.meshes[0]);

                    // TODO: Move camera position from target enough distance to visualize model properly
                }
                else if (RL_IsFileExtension(droppedFiles.paths[0], ".png"))  // RL_Texture file formats supported
                {
                    // Unload current model texture and load new one
                    RL_UnloadTexture(texture);
                    texture = RL_LoadTexture(droppedFiles.paths[0]);
                    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
                }
            }

            RL_UnloadDroppedFiles(droppedFiles);    // Unload filepaths from memory
        }

        // Select model on mouse click
        if (RL_IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // Check collision between ray and box
            if (RL_GetRayCollisionBox(RL_GetScreenToWorldRay(RL_GetMousePosition(), camera), bounds).hit) selected = !selected;
            else selected = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                RL_DrawModel(model, position, 1.0f, RL_WHITE);        // Draw 3d model with texture

                RL_DrawGrid(20, 10.0f);         // Draw a grid

                if (selected) RL_DrawBoundingBox(bounds, RL_GREEN);   // Draw selection box

            RL_EndMode3D();

            RL_DrawText("Drag & drop model to load mesh/texture.", 10, RL_GetScreenHeight() - 20, 10, RL_DARKGRAY);
            if (selected) RL_DrawText("MODEL SELECTED", RL_GetScreenWidth() - 110, 10, 10, RL_GREEN);

            RL_DrawText("(c) Castle 3D model by Alberto Cano", screenWidth - 200, screenHeight - 20, 10, RL_GRAY);

            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(texture);     // Unload texture
    RL_UnloadModel(model);         // Unload model

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}