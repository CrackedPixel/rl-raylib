/*******************************************************************************************
*
*   raylib example - point rendering
*
*   Example originally created with raylib 5.0, last time updated with raylib 5.0
*
*   Example contributed by Reese Gallagher (@satchelfrost) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2024 Reese Gallagher (@satchelfrost)
*
********************************************************************************************/

#include "raylib.h"

#include <stdlib.h>             // Required for: rand()
#include <math.h>               // Required for: cos(), sin()

#define MAX_POINTS 10000000     // 10 million
#define MIN_POINTS 1000         // 1 thousand

// Generate mesh using points
RL_Mesh GenMeshPoints(int numPoints);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - point rendering");

    RL_Camera camera = {
        .position   = { 3.0f, 3.0f, 3.0f },
        .target     = { 0.0f, 0.0f, 0.0f },
        .up         = { 0.0f, 1.0f, 0.0f },
        .fovy       = 45.0f,
        .projection = CAMERA_PERSPECTIVE
    };

    RL_Vector3 position = { 0.0f, 0.0f, 0.0f };
    bool useDrawModelPoints = true;
    bool numPointsChanged = false;
    int numPoints = 1000;
    
    RL_Mesh mesh = GenMeshPoints(numPoints);
    RL_Model model = RL_LoadModelFromMesh(mesh);
    
    //RL_SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while(!RL_WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_ORBITAL);

        if (RL_IsKeyPressed(KEY_SPACE)) useDrawModelPoints = !useDrawModelPoints;
        if (RL_IsKeyPressed(KEY_UP))
        {
            numPoints = (numPoints*10 > MAX_POINTS)? MAX_POINTS : numPoints*10;
            numPointsChanged = true;
        }
        if (RL_IsKeyPressed(KEY_DOWN))
        {
            numPoints = (numPoints/10 < MIN_POINTS)? MIN_POINTS : numPoints/10;
            numPointsChanged = true;
        }

        // Upload a different point cloud size
        if (numPointsChanged)
        {
            RL_UnloadModel(model);
            mesh = GenMeshPoints(numPoints);
            model = RL_LoadModelFromMesh(mesh);
            numPointsChanged = false;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();
            RL_ClearBackground(RL_BLACK);

            RL_BeginMode3D(camera);

                // The new method only uploads the points once to the GPU
                if (useDrawModelPoints)
                {
                    DrawModelPoints(model, position, 1.0f, RL_WHITE);
                }
                else
                {
                    // The old method must continually draw the "points" (lines)
                    for (int i = 0; i < numPoints; i++)
                    {
                        RL_Vector3 pos = {
                            .x = mesh.vertices[i*3 + 0],
                            .y = mesh.vertices[i*3 + 1],
                            .z = mesh.vertices[i*3 + 2],
                        };
                        RL_Color color = {
                            .r = mesh.colors[i*4 + 0],
                            .g = mesh.colors[i*4 + 1],
                            .b = mesh.colors[i*4 + 2],
                            .a = mesh.colors[i*4 + 3],
                        };
                        
                        RL_DrawPoint3D(pos, color);
                    }
                }

                // Draw a unit sphere for reference
                RL_DrawSphereWires(position, 1.0f, 10, 10, RL_YELLOW);
                
            RL_EndMode3D();

            // Draw UI text
            RL_DrawText(RL_TextFormat("Point Count: %d", numPoints), 20, screenHeight - 50, 40, RL_WHITE);
            RL_DrawText("Up - increase points", 20, 70, 20, RL_WHITE);
            RL_DrawText("Down - decrease points", 20, 100, 20, RL_WHITE);
            RL_DrawText("Space - drawing function", 20, 130, 20, RL_WHITE);
            
            if (useDrawModelPoints) RL_DrawText("Using: DrawModelPoints()", 20, 160, 20, RL_GREEN);
            else RL_DrawText("Using: RL_DrawPoint3D()", 20, 160, 20, RL_RED);
            
            RL_DrawFPS(10, 10);
            
        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadModel(model);

    RL_CloseWindow();
    //--------------------------------------------------------------------------------------
    return 0;
}

// Generate a spherical point cloud
RL_Mesh GenMeshPoints(int numPoints)
{
    RL_Mesh mesh = { 
        .triangleCount = 1,
        .vertexCount = numPoints,
        .vertices = (float *)RL_MemAlloc(numPoints*3*sizeof(float)),
        .colors = (unsigned char*)RL_MemAlloc(numPoints*4*sizeof(unsigned char)),
    };

    // https://en.wikipedia.org/wiki/Spherical_coordinate_system
    for (int i = 0; i < numPoints; i++)
    {
        float theta = PI*rand()/RAND_MAX;
        float phi = 2.0f*PI*rand()/RAND_MAX;
        float r = 10.0f*rand()/RAND_MAX;
        
        mesh.vertices[i*3 + 0] = r*sin(theta)*cos(phi);
        mesh.vertices[i*3 + 1] = r*sin(theta)*sin(phi);
        mesh.vertices[i*3 + 2] = r*cos(theta);
        
        RL_Color color = RL_ColorFromHSV(r*360.0f, 1.0f, 1.0f);
        
        mesh.colors[i*4 + 0] = color.r;
        mesh.colors[i*4 + 1] = color.g;
        mesh.colors[i*4 + 2] = color.b;
        mesh.colors[i*4 + 3] = color.a;
    }

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    RL_UploadMesh(&mesh, false);
    
    return mesh;
}
