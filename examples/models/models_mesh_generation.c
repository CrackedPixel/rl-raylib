/*******************************************************************************************
*
*   raylib example - procedural mesh generation
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

#define NUM_MODELS  9               // Parametric 3d shapes to generate

static RL_Mesh GenMeshCustom(void);    // Generate a simple triangle mesh from code

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - mesh generation");

    // We generate a checked image for texturing
    RL_Image checked = RL_GenImageChecked(2, 2, 1, 1, RL_RED, RL_GREEN);
    RL_Texture2D texture = RL_LoadTextureFromImage(checked);
    RL_UnloadImage(checked);

    RL_Model models[NUM_MODELS] = { 0 };

    models[0] = RL_LoadModelFromMesh(RL_GenMeshPlane(2, 2, 4, 3));
    models[1] = RL_LoadModelFromMesh(RL_GenMeshCube(2.0f, 1.0f, 2.0f));
    models[2] = RL_LoadModelFromMesh(RL_GenMeshSphere(2, 32, 32));
    models[3] = RL_LoadModelFromMesh(RL_GenMeshHemiSphere(2, 16, 16));
    models[4] = RL_LoadModelFromMesh(RL_GenMeshCylinder(1, 2, 16));
    models[5] = RL_LoadModelFromMesh(RL_GenMeshTorus(0.25f, 4.0f, 16, 32));
    models[6] = RL_LoadModelFromMesh(RL_GenMeshKnot(1.0f, 2.0f, 16, 128));
    models[7] = RL_LoadModelFromMesh(RL_GenMeshPoly(5, 2.0f));
    models[8] = RL_LoadModelFromMesh(GenMeshCustom());
    
    // Generated meshes could be exported as .obj files
    //RL_ExportMesh(models[0].meshes[0], "plane.obj");
    //RL_ExportMesh(models[1].meshes[0], "cube.obj");
    //RL_ExportMesh(models[2].meshes[0], "sphere.obj");
    //RL_ExportMesh(models[3].meshes[0], "hemisphere.obj");
    //RL_ExportMesh(models[4].meshes[0], "cylinder.obj");
    //RL_ExportMesh(models[5].meshes[0], "torus.obj");
    //RL_ExportMesh(models[6].meshes[0], "knot.obj");
    //RL_ExportMesh(models[7].meshes[0], "poly.obj");
    //RL_ExportMesh(models[8].meshes[0], "custom.obj");

    // Set checked texture as default diffuse component for all models material
    for (int i = 0; i < NUM_MODELS; i++) models[i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    // Define the camera to look into our 3d world
    RL_Camera camera = { { 5.0f, 5.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

    // RL_Model drawing position
    RL_Vector3 position = { 0.0f, 0.0f, 0.0f };

    int currentModel = 0;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_ORBITAL);

        if (RL_IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            currentModel = (currentModel + 1)%NUM_MODELS; // Cycle between the textures
        }

        if (RL_IsKeyPressed(KEY_RIGHT))
        {
            currentModel++;
            if (currentModel >= NUM_MODELS) currentModel = 0;
        }
        else if (RL_IsKeyPressed(KEY_LEFT))
        {
            currentModel--;
            if (currentModel < 0) currentModel = NUM_MODELS - 1;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

               RL_DrawModel(models[currentModel], position, 1.0f, RL_WHITE);
               RL_DrawGrid(10, 1.0);

            RL_EndMode3D();

            RL_DrawRectangle(30, 400, 310, 30, RL_Fade(RL_SKYBLUE, 0.5f));
            RL_DrawRectangleLines(30, 400, 310, 30, RL_Fade(RL_DARKBLUE, 0.5f));
            RL_DrawText("MOUSE LEFT BUTTON to CYCLE PROCEDURAL MODELS", 40, 410, 10, RL_BLUE);

            switch(currentModel)
            {
                case 0: RL_DrawText("PLANE", 680, 10, 20, RL_DARKBLUE); break;
                case 1: RL_DrawText("CUBE", 680, 10, 20, RL_DARKBLUE); break;
                case 2: RL_DrawText("SPHERE", 680, 10, 20, RL_DARKBLUE); break;
                case 3: RL_DrawText("HEMISPHERE", 640, 10, 20, RL_DARKBLUE); break;
                case 4: RL_DrawText("CYLINDER", 680, 10, 20, RL_DARKBLUE); break;
                case 5: RL_DrawText("TORUS", 680, 10, 20, RL_DARKBLUE); break;
                case 6: RL_DrawText("KNOT", 680, 10, 20, RL_DARKBLUE); break;
                case 7: RL_DrawText("POLY", 680, 10, 20, RL_DARKBLUE); break;
                case 8: RL_DrawText("Custom (triangle)", 580, 10, 20, RL_DARKBLUE); break;
                default: break;
            }

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(texture); // Unload texture

    // Unload models data (GPU VRAM)
    for (int i = 0; i < NUM_MODELS; i++) RL_UnloadModel(models[i]);

    RL_CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Generate a simple triangle mesh from code
static RL_Mesh GenMeshCustom(void)
{
    RL_Mesh mesh = { 0 };
    mesh.triangleCount = 1;
    mesh.vertexCount = mesh.triangleCount*3;
    mesh.vertices = (float *)RL_MemAlloc(mesh.vertexCount*3*sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)
    mesh.texcoords = (float *)RL_MemAlloc(mesh.vertexCount*2*sizeof(float));   // 3 vertices, 2 coordinates each (x, y)
    mesh.normals = (float *)RL_MemAlloc(mesh.vertexCount*3*sizeof(float));     // 3 vertices, 3 coordinates each (x, y, z)

    // Vertex at (0, 0, 0)
    mesh.vertices[0] = 0;
    mesh.vertices[1] = 0;
    mesh.vertices[2] = 0;
    mesh.normals[0] = 0;
    mesh.normals[1] = 1;
    mesh.normals[2] = 0;
    mesh.texcoords[0] = 0;
    mesh.texcoords[1] = 0;

    // Vertex at (1, 0, 2)
    mesh.vertices[3] = 1;
    mesh.vertices[4] = 0;
    mesh.vertices[5] = 2;
    mesh.normals[3] = 0;
    mesh.normals[4] = 1;
    mesh.normals[5] = 0;
    mesh.texcoords[2] = 0.5f;
    mesh.texcoords[3] = 1.0f;

    // Vertex at (2, 0, 0)
    mesh.vertices[6] = 2;
    mesh.vertices[7] = 0;
    mesh.vertices[8] = 0;
    mesh.normals[6] = 0;
    mesh.normals[7] = 1;
    mesh.normals[8] = 0;
    mesh.texcoords[4] = 1;
    mesh.texcoords[5] =0;

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    RL_UploadMesh(&mesh, false);

    return mesh;
}
