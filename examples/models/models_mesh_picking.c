/*******************************************************************************************
*
*   raylib [models] example - RL_Mesh picking in 3d mode, ground plane, triangle, mesh
*
*   Example originally created with raylib 1.7, last time updated with raylib 4.0
*
*   Example contributed by Joel Davis (@joeld42) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2017-2024 Joel Davis (@joeld42) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

#define FLT_MAX     340282346638528859811704183484516925440.0f     // Maximum value of a float, from bit pattern 01111111011111111111111111111111

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - mesh picking");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 20.0f, 20.0f, 20.0f }; // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 8.0f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.6f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    RL_Ray ray = { 0 };        // Picking ray

    RL_Model tower = RL_LoadModel("resources/models/obj/turret.obj");                 // Load OBJ model
    RL_Texture2D texture = RL_LoadTexture("resources/models/obj/turret_diffuse.png"); // Load model texture
    tower.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;            // Set model diffuse texture

    RL_Vector3 towerPos = { 0.0f, 0.0f, 0.0f };                        // Set model position
    RL_BoundingBox towerBBox = RL_GetMeshBoundingBox(tower.meshes[0]);    // Get mesh bounding box

    // Ground quad
    RL_Vector3 g0 = (RL_Vector3){ -50.0f, 0.0f, -50.0f };
    RL_Vector3 g1 = (RL_Vector3){ -50.0f, 0.0f,  50.0f };
    RL_Vector3 g2 = (RL_Vector3){  50.0f, 0.0f,  50.0f };
    RL_Vector3 g3 = (RL_Vector3){  50.0f, 0.0f, -50.0f };

    // Test triangle
    RL_Vector3 ta = (RL_Vector3){ -25.0f, 0.5f, 0.0f };
    RL_Vector3 tb = (RL_Vector3){ -4.0f, 2.5f, 1.0f };
    RL_Vector3 tc = (RL_Vector3){ -8.0f, 6.5f, 0.0f };

    RL_Vector3 bary = { 0.0f, 0.0f, 0.0f };

    // Test sphere
    RL_Vector3 sp = (RL_Vector3){ -30.0f, 5.0f, 5.0f };
    float sr = 4.0f;

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsCursorHidden()) RL_UpdateCamera(&camera, CAMERA_FIRST_PERSON);          // Update camera

        // Toggle camera controls
        if (RL_IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            if (RL_IsCursorHidden()) RL_EnableCursor();
            else RL_DisableCursor();
        }

        // Display information about closest hit
        RL_RayCollision collision = { 0 };
        char *hitObjectName = "None";
        collision.distance = FLT_MAX;
        collision.hit = false;
        RL_Color cursorColor = RL_WHITE;

        // Get ray and test against objects
        ray = RL_GetScreenToWorldRay(RL_GetMousePosition(), camera);

        // Check ray collision against ground quad
        RL_RayCollision groundHitInfo = RL_GetRayCollisionQuad(ray, g0, g1, g2, g3);

        if ((groundHitInfo.hit) && (groundHitInfo.distance < collision.distance))
        {
            collision = groundHitInfo;
            cursorColor = RL_GREEN;
            hitObjectName = "Ground";
        }

        // Check ray collision against test triangle
        RL_RayCollision triHitInfo = RL_GetRayCollisionTriangle(ray, ta, tb, tc);

        if ((triHitInfo.hit) && (triHitInfo.distance < collision.distance))
        {
            collision = triHitInfo;
            cursorColor = RL_PURPLE;
            hitObjectName = "Triangle";

            bary = Vector3Barycenter(collision.point, ta, tb, tc);
        }

        // Check ray collision against test sphere
        RL_RayCollision sphereHitInfo = RL_GetRayCollisionSphere(ray, sp, sr);

        if ((sphereHitInfo.hit) && (sphereHitInfo.distance < collision.distance))
        {
            collision = sphereHitInfo;
            cursorColor = RL_ORANGE;
            hitObjectName = "Sphere";
        }

        // Check ray collision against bounding box first, before trying the full ray-mesh test
        RL_RayCollision boxHitInfo = RL_GetRayCollisionBox(ray, towerBBox);

        if ((boxHitInfo.hit) && (boxHitInfo.distance < collision.distance))
        {
            collision = boxHitInfo;
            cursorColor = RL_ORANGE;
            hitObjectName = "Box";

            // Check ray collision against model meshes
            RL_RayCollision meshHitInfo = { 0 };
            for (int m = 0; m < tower.meshCount; m++)
            {
                // NOTE: We consider the model.transform for the collision check but 
                // it can be checked against any transform RL_Matrix, used when checking against same
                // model drawn multiple times with multiple transforms
                meshHitInfo = RL_GetRayCollisionMesh(ray, tower.meshes[m], tower.transform);
                if (meshHitInfo.hit)
                {
                    // Save the closest hit mesh
                    if ((!collision.hit) || (collision.distance > meshHitInfo.distance)) collision = meshHitInfo;
                    
                    break;  // Stop once one mesh collision is detected, the colliding mesh is m
                }
            }

            if (meshHitInfo.hit)
            {
                collision = meshHitInfo;
                cursorColor = RL_ORANGE;
                hitObjectName = "RL_Mesh";
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                // Draw the tower
                // WARNING: If scale is different than 1.0f,
                // not considered by GetRayCollisionModel()
                RL_DrawModel(tower, towerPos, 1.0f, RL_WHITE);

                // Draw the test triangle
                RL_DrawLine3D(ta, tb, RL_PURPLE);
                RL_DrawLine3D(tb, tc, RL_PURPLE);
                RL_DrawLine3D(tc, ta, RL_PURPLE);

                // Draw the test sphere
                RL_DrawSphereWires(sp, sr, 8, 8, RL_PURPLE);

                // Draw the mesh bbox if we hit it
                if (boxHitInfo.hit) RL_DrawBoundingBox(towerBBox, RL_LIME);

                // If we hit something, draw the cursor at the hit point
                if (collision.hit)
                {
                    RL_DrawCube(collision.point, 0.3f, 0.3f, 0.3f, cursorColor);
                    RL_DrawCubeWires(collision.point, 0.3f, 0.3f, 0.3f, RL_RED);

                    RL_Vector3 normalEnd;
                    normalEnd.x = collision.point.x + collision.normal.x;
                    normalEnd.y = collision.point.y + collision.normal.y;
                    normalEnd.z = collision.point.z + collision.normal.z;

                    RL_DrawLine3D(collision.point, normalEnd, RL_RED);
                }

                RL_DrawRay(ray, RL_MAROON);

                RL_DrawGrid(10, 10.0f);

            RL_EndMode3D();

            // Draw some debug GUI text
            RL_DrawText(RL_TextFormat("Hit Object: %s", hitObjectName), 10, 50, 10, RL_BLACK);

            if (collision.hit)
            {
                int ypos = 70;

                RL_DrawText(RL_TextFormat("Distance: %3.2f", collision.distance), 10, ypos, 10, RL_BLACK);

                RL_DrawText(RL_TextFormat("Hit Pos: %3.2f %3.2f %3.2f",
                                    collision.point.x,
                                    collision.point.y,
                                    collision.point.z), 10, ypos + 15, 10, RL_BLACK);

                RL_DrawText(RL_TextFormat("Hit Norm: %3.2f %3.2f %3.2f",
                                    collision.normal.x,
                                    collision.normal.y,
                                    collision.normal.z), 10, ypos + 30, 10, RL_BLACK);

                if (triHitInfo.hit && RL_TextIsEqual(hitObjectName, "Triangle"))
                    RL_DrawText(RL_TextFormat("Barycenter: %3.2f %3.2f %3.2f",  bary.x, bary.y, bary.z), 10, ypos + 45, 10, RL_BLACK);
            }

            RL_DrawText("Right click mouse to toggle camera controls", 10, 430, 10, RL_GRAY);

            RL_DrawText("(c) Turret 3D model by Alberto Cano", screenWidth - 200, screenHeight - 20, 10, RL_GRAY);

            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadModel(tower);         // Unload model
    RL_UnloadTexture(texture);     // Unload texture

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}