/*******************************************************************************************
*
*   raylib [models] example - Drawing billboards
*
*   Example originally created with raylib 1.3, last time updated with raylib 3.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - drawing billboards");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 5.0f, 4.0f, 5.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 2.0f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    RL_Texture2D bill = RL_LoadTexture("resources/billboard.png");    // Our billboard texture
    RL_Vector3 billPositionStatic = { 0.0f, 2.0f, 0.0f };          // Position of static billboard
    RL_Vector3 billPositionRotating = { 1.0f, 2.0f, 1.0f };        // Position of rotating billboard

    // Entire billboard texture, source is used to take a segment from a larger texture.
    RL_Rectangle source = { 0.0f, 0.0f, (float)bill.width, (float)bill.height };

    // NOTE: Billboard locked on axis-Y
    RL_Vector3 billUp = { 0.0f, 1.0f, 0.0f };

    // Set the height of the rotating billboard to 1.0 with the aspect ratio fixed
    RL_Vector2 size = { source.width/source.height, 1.0f };

    // Rotate around origin
    // Here we choose to rotate around the image center
    RL_Vector2 origin = Vector2Scale(size, 0.5f);

    // Distance is needed for the correct billboard draw order
    // Larger distance (further away from the camera) should be drawn prior to smaller distance.
    float distanceStatic;
    float distanceRotating;
    float rotation = 0.0f;

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_ORBITAL);

        rotation += 0.4f;
        distanceStatic = Vector3Distance(camera.position, billPositionStatic);
        distanceRotating = Vector3Distance(camera.position, billPositionRotating);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                RL_DrawGrid(10, 1.0f);        // Draw a grid

                // Draw order matters!
                if (distanceStatic > distanceRotating) 
                {
                    RL_DrawBillboard(camera, bill, billPositionStatic, 2.0f, RL_WHITE);
                    RL_DrawBillboardPro(camera, bill, source, billPositionRotating, billUp, size, origin, rotation, RL_WHITE);
                } 
                else
                {
                    RL_DrawBillboardPro(camera, bill, source, billPositionRotating, billUp, size, origin, rotation, RL_WHITE);
                    RL_DrawBillboard(camera, bill, billPositionStatic, 2.0f, RL_WHITE);
                }
                
            RL_EndMode3D();

            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(bill);        // Unload texture

    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
