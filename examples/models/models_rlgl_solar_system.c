/*******************************************************************************************
*
*   raylib [models] example - rlgl module usage with push/pop matrix transformations
*
*   NOTE: This example uses [rlgl] module functionality (pseudo-OpenGL 1.1 style coding)
*
*   Example originally created with raylib 2.5, last time updated with raylib 4.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "rlgl.h"

#include <math.h>           // Required for: cosf(), sinf()

//------------------------------------------------------------------------------------
// Module Functions Declaration
//------------------------------------------------------------------------------------
void DrawSphereBasic(RL_Color color);      // Draw sphere without any matrix transformation

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    const float sunRadius = 4.0f;
    const float earthRadius = 0.6f;
    const float earthOrbitRadius = 8.0f;
    const float moonRadius = 0.16f;
    const float moonOrbitRadius = 1.5f;

    RL_InitWindow(screenWidth, screenHeight, "raylib [models] example - rlgl module usage with push/pop matrix transformations");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 16.0f, 16.0f, 16.0f }; // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.0f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    float rotationSpeed = 0.2f;         // General system rotation speed

    float earthRotation = 0.0f;         // Rotation of earth around itself (days) in degrees
    float earthOrbitRotation = 0.0f;    // Rotation of earth around the Sun (years) in degrees
    float moonRotation = 0.0f;          // Rotation of moon around itself
    float moonOrbitRotation = 0.0f;     // Rotation of moon around earth in degrees

    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_ORBITAL);

        earthRotation += (5.0f*rotationSpeed);
        earthOrbitRotation += (365/360.0f*(5.0f*rotationSpeed)*rotationSpeed);
        moonRotation += (2.0f*rotationSpeed);
        moonOrbitRotation += (8.0f*rotationSpeed);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_BeginMode3D(camera);

                rlPushMatrix();
                    rlScalef(sunRadius, sunRadius, sunRadius);          // Scale Sun
                    DrawSphereBasic(RL_GOLD);                              // Draw the Sun
                rlPopMatrix();

                rlPushMatrix();
                    rlRotatef(earthOrbitRotation, 0.0f, 1.0f, 0.0f);    // Rotation for Earth orbit around Sun
                    rlTranslatef(earthOrbitRadius, 0.0f, 0.0f);         // Translation for Earth orbit

                    rlPushMatrix();
                        rlRotatef(earthRotation, 0.25, 1.0, 0.0);       // Rotation for Earth itself
                        rlScalef(earthRadius, earthRadius, earthRadius);// Scale Earth

                        DrawSphereBasic(RL_BLUE);                          // Draw the Earth
                    rlPopMatrix();

                    rlRotatef(moonOrbitRotation, 0.0f, 1.0f, 0.0f);     // Rotation for Moon orbit around Earth
                    rlTranslatef(moonOrbitRadius, 0.0f, 0.0f);          // Translation for Moon orbit
                    rlRotatef(moonRotation, 0.0f, 1.0f, 0.0f);          // Rotation for Moon itself
                    rlScalef(moonRadius, moonRadius, moonRadius);       // Scale Moon

                    DrawSphereBasic(RL_LIGHTGRAY);                         // Draw the Moon
                rlPopMatrix();

                // Some reference elements (not affected by previous matrix transformations)
                RL_DrawCircle3D((RL_Vector3){ 0.0f, 0.0f, 0.0f }, earthOrbitRadius, (RL_Vector3){ 1, 0, 0 }, 90.0f, RL_Fade(RL_RED, 0.5f));
                RL_DrawGrid(20, 1.0f);

            RL_EndMode3D();

            RL_DrawText("EARTH ORBITING AROUND THE SUN!", 400, 10, 20, RL_MAROON);
            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//--------------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//--------------------------------------------------------------------------------------------

// Draw sphere without any matrix transformation
// NOTE: Sphere is drawn in world position ( 0, 0, 0 ) with radius 1.0f
void DrawSphereBasic(RL_Color color)
{
    int rings = 16;
    int slices = 16;

    // Make sure there is enough space in the internal render batch
    // buffer to store all required vertex, batch is reseted if required
    rlCheckRenderBatchLimit((rings + 2)*slices*6);

    rlBegin(RL_TRIANGLES);
        rlColor4ub(color.r, color.g, color.b, color.a);

        for (int i = 0; i < (rings + 2); i++)
        {
            for (int j = 0; j < slices; j++)
            {
                rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*i))*sinf(DEG2RAD*(j*360/slices)),
                           sinf(DEG2RAD*(270+(180/(rings + 1))*i)),
                           cosf(DEG2RAD*(270+(180/(rings + 1))*i))*cosf(DEG2RAD*(j*360/slices)));
                rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*sinf(DEG2RAD*((j+1)*360/slices)),
                           sinf(DEG2RAD*(270+(180/(rings + 1))*(i+1))),
                           cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*cosf(DEG2RAD*((j+1)*360/slices)));
                rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*sinf(DEG2RAD*(j*360/slices)),
                           sinf(DEG2RAD*(270+(180/(rings + 1))*(i+1))),
                           cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*cosf(DEG2RAD*(j*360/slices)));

                rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*i))*sinf(DEG2RAD*(j*360/slices)),
                           sinf(DEG2RAD*(270+(180/(rings + 1))*i)),
                           cosf(DEG2RAD*(270+(180/(rings + 1))*i))*cosf(DEG2RAD*(j*360/slices)));
                rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i)))*sinf(DEG2RAD*((j+1)*360/slices)),
                           sinf(DEG2RAD*(270+(180/(rings + 1))*(i))),
                           cosf(DEG2RAD*(270+(180/(rings + 1))*(i)))*cosf(DEG2RAD*((j+1)*360/slices)));
                rlVertex3f(cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*sinf(DEG2RAD*((j+1)*360/slices)),
                           sinf(DEG2RAD*(270+(180/(rings + 1))*(i+1))),
                           cosf(DEG2RAD*(270+(180/(rings + 1))*(i+1)))*cosf(DEG2RAD*((j+1)*360/slices)));
            }
        }
    rlEnd();
}
