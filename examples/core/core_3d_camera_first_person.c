/*******************************************************************************************
*
*   raylib [core] example - 3d camera first person
*
*   Example originally created with raylib 1.3, last time updated with raylib 1.3
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "rcamera.h"

#define MAX_COLUMNS 20

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");

    // Define the camera to look into our 3d world (position, target, up vector)
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 0.0f, 2.0f, 4.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 2.0f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 60.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    int cameraMode = CAMERA_FIRST_PERSON;

    // Generates some random columns
    float heights[MAX_COLUMNS] = { 0 };
    RL_Vector3 positions[MAX_COLUMNS] = { 0 };
    RL_Color colors[MAX_COLUMNS] = { 0 };

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        heights[i] = (float)RL_GetRandomValue(1, 12);
        positions[i] = (RL_Vector3){ (float)RL_GetRandomValue(-15, 15), heights[i]/2.0f, (float)RL_GetRandomValue(-15, 15) };
        colors[i] = (RL_Color){ RL_GetRandomValue(20, 255), RL_GetRandomValue(10, 55), 30, 255 };
    }

    RL_DisableCursor();                    // Limit cursor to relative movement inside the window

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Switch camera mode
        if (RL_IsKeyPressed(KEY_ONE))
        {
            cameraMode = CAMERA_FREE;
            camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
        }

        if (RL_IsKeyPressed(KEY_TWO))
        {
            cameraMode = CAMERA_FIRST_PERSON;
            camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
        }

        if (RL_IsKeyPressed(KEY_THREE))
        {
            cameraMode = CAMERA_THIRD_PERSON;
            camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
        }

        if (RL_IsKeyPressed(KEY_FOUR))
        {
            cameraMode = CAMERA_ORBITAL;
            camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll
        }

        // Switch camera projection
        if (RL_IsKeyPressed(KEY_P))
        {
            if (camera.projection == CAMERA_PERSPECTIVE)
            {
                // Create isometric view
                cameraMode = CAMERA_THIRD_PERSON;
                // Note: The target distance is related to the render distance in the orthographic projection
                camera.position = (RL_Vector3){ 0.0f, 2.0f, -100.0f };
                camera.target = (RL_Vector3){ 0.0f, 2.0f, 0.0f };
                camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };
                camera.projection = CAMERA_ORTHOGRAPHIC;
                camera.fovy = 20.0f; // near plane width in CAMERA_ORTHOGRAPHIC
                CameraYaw(&camera, -135 * DEG2RAD, true);
                CameraPitch(&camera, -45 * DEG2RAD, true, true, false);
            }
            else if (camera.projection == CAMERA_ORTHOGRAPHIC)
            {
                // Reset to default view
                cameraMode = CAMERA_THIRD_PERSON;
                camera.position = (RL_Vector3){ 0.0f, 2.0f, 10.0f };
                camera.target = (RL_Vector3){ 0.0f, 2.0f, 0.0f };
                camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };
                camera.projection = CAMERA_PERSPECTIVE;
                camera.fovy = 60.0f;
            }
        }

        // Update camera computes movement internally depending on the camera mode
        // Some default standard keyboard/mouse inputs are hardcoded to simplify use
        // For advance camera controls, it's reecommended to compute camera movement manually
        RL_UpdateCamera(&camera, cameraMode);                  // Update camera

/*
        // RL_Camera PRO usage example (EXPERIMENTAL)
        // This new camera function allows custom movement/rotation values to be directly provided
        // as input parameters, with this approach, rcamera module is internally independent of raylib inputs
        RL_UpdateCameraPro(&camera,
            (RL_Vector3){
                (RL_IsKeyDown(KEY_W) || RL_IsKeyDown(KEY_UP))*0.1f -      // Move forward-backward
                (RL_IsKeyDown(KEY_S) || RL_IsKeyDown(KEY_DOWN))*0.1f,    
                (RL_IsKeyDown(KEY_D) || RL_IsKeyDown(KEY_RIGHT))*0.1f -   // Move right-left
                (RL_IsKeyDown(KEY_A) || RL_IsKeyDown(KEY_LEFT))*0.1f,
                0.0f                                                // Move up-down
            },
            (RL_Vector3){
                RL_GetMouseDelta().x*0.05f,                            // Rotation: yaw
                RL_GetMouseDelta().y*0.05f,                            // Rotation: pitch
                0.0f                                                // Rotation: roll
            },
            RL_GetMouseWheelMove()*2.0f);                              // Move to target (zoom)
*/
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                RL_DrawPlane((RL_Vector3){ 0.0f, 0.0f, 0.0f }, (RL_Vector2){ 32.0f, 32.0f }, RL_LIGHTGRAY); // Draw ground
                RL_DrawCube((RL_Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, RL_BLUE);     // Draw a blue wall
                RL_DrawCube((RL_Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, RL_LIME);      // Draw a green wall
                RL_DrawCube((RL_Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, RL_GOLD);      // Draw a yellow wall

                // Draw some cubes around
                for (int i = 0; i < MAX_COLUMNS; i++)
                {
                    RL_DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
                    RL_DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, RL_MAROON);
                }

                // Draw player cube
                if (cameraMode == CAMERA_THIRD_PERSON)
                {
                    RL_DrawCube(camera.target, 0.5f, 0.5f, 0.5f, RL_PURPLE);
                    RL_DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, RL_DARKPURPLE);
                }

            RL_EndMode3D();

            // Draw info boxes
            RL_DrawRectangle(5, 5, 330, 100, RL_Fade(RL_SKYBLUE, 0.5f));
            RL_DrawRectangleLines(5, 5, 330, 100, RL_BLUE);

            RL_DrawText("RL_Camera controls:", 15, 15, 10, RL_BLACK);
            RL_DrawText("- Move keys: W, A, S, D, Space, Left-Ctrl", 15, 30, 10, RL_BLACK);
            RL_DrawText("- Look around: arrow keys or mouse", 15, 45, 10, RL_BLACK);
            RL_DrawText("- RL_Camera mode keys: 1, 2, 3, 4", 15, 60, 10, RL_BLACK);
            RL_DrawText("- Zoom keys: num-plus, num-minus or mouse scroll", 15, 75, 10, RL_BLACK);
            RL_DrawText("- RL_Camera projection key: P", 15, 90, 10, RL_BLACK);

            RL_DrawRectangle(600, 5, 195, 100, RL_Fade(RL_SKYBLUE, 0.5f));
            RL_DrawRectangleLines(600, 5, 195, 100, RL_BLUE);

            RL_DrawText("RL_Camera status:", 610, 15, 10, RL_BLACK);
            RL_DrawText(RL_TextFormat("- Mode: %s", (cameraMode == CAMERA_FREE) ? "FREE" :
                                              (cameraMode == CAMERA_FIRST_PERSON) ? "FIRST_PERSON" :
                                              (cameraMode == CAMERA_THIRD_PERSON) ? "THIRD_PERSON" :
                                              (cameraMode == CAMERA_ORBITAL) ? "ORBITAL" : "CUSTOM"), 610, 30, 10, RL_BLACK);
            RL_DrawText(RL_TextFormat("- Projection: %s", (camera.projection == CAMERA_PERSPECTIVE) ? "PERSPECTIVE" :
                                                    (camera.projection == CAMERA_ORTHOGRAPHIC) ? "ORTHOGRAPHIC" : "CUSTOM"), 610, 45, 10, RL_BLACK);
            RL_DrawText(RL_TextFormat("- Position: (%06.3f, %06.3f, %06.3f)", camera.position.x, camera.position.y, camera.position.z), 610, 60, 10, RL_BLACK);
            RL_DrawText(RL_TextFormat("- Target: (%06.3f, %06.3f, %06.3f)", camera.target.x, camera.target.y, camera.target.z), 610, 75, 10, RL_BLACK);
            RL_DrawText(RL_TextFormat("- Up: (%06.3f, %06.3f, %06.3f)", camera.up.x, camera.up.y, camera.up.z), 610, 90, 10, RL_BLACK);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}