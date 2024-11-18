/*******************************************************************************************
*
*   raylib [shapes] example - splines drawing
*
*   Example originally created with raylib 5.0, last time updated with raylib 5.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"     // Required for UI controls

#include <stdlib.h>     // Required for: NULL

#define MAX_SPLINE_POINTS      32

// Cubic Bezier spline control points
// NOTE: Every segment has two control points 
typedef struct {
    RL_Vector2 start;
    RL_Vector2 end;
} ControlPoint;

// Spline types
typedef enum {
    SPLINE_LINEAR = 0,      // Linear
    SPLINE_BASIS,           // B-Spline
    SPLINE_CATMULLROM,      // Catmull-Rom
    SPLINE_BEZIER           // Cubic Bezier
} SplineType;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_SetConfigFlags(FLAG_MSAA_4X_HINT);
    RL_InitWindow(screenWidth, screenHeight, "raylib [shapes] example - splines drawing");

    RL_Vector2 points[MAX_SPLINE_POINTS] = {
        {  50.0f, 400.0f },
        { 160.0f, 220.0f },
        { 340.0f, 380.0f },
        { 520.0f, 60.0f },
        { 710.0f, 260.0f },
    };
    
    // Array required for spline bezier-cubic, 
    // including control points interleaved with start-end segment points
    RL_Vector2 pointsInterleaved[3*(MAX_SPLINE_POINTS - 1) + 1] = { 0 };
    
    int pointCount = 5;
    int selectedPoint = -1;
    int focusedPoint = -1;
    RL_Vector2 *selectedControlPoint = NULL;
    RL_Vector2 *focusedControlPoint = NULL;
    
    // Cubic Bezier control points initialization
    ControlPoint control[MAX_SPLINE_POINTS-1] = { 0 };
    for (int i = 0; i < pointCount - 1; i++)
    {
        control[i].start = (RL_Vector2){ points[i].x + 50, points[i].y };
        control[i].end = (RL_Vector2){ points[i + 1].x - 50, points[i + 1].y };
    }

    // Spline config variables
    float splineThickness = 8.0f;
    int splineTypeActive = SPLINE_LINEAR; // 0-Linear, 1-BSpline, 2-CatmullRom, 3-Bezier
    bool splineTypeEditMode = false; 
    bool splineHelpersActive = true;
    
    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Spline points creation logic (at the end of spline)
        if (RL_IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && (pointCount < MAX_SPLINE_POINTS))
        {
            points[pointCount] = RL_GetMousePosition();
            int i = pointCount - 1;
            control[i].start = (RL_Vector2){ points[i].x + 50, points[i].y };
            control[i].end = (RL_Vector2){ points[i + 1].x - 50, points[i + 1].y };
            pointCount++;
        }

        // Spline point focus and selection logic
        for (int i = 0; i < pointCount; i++)
        {
            if (RL_CheckCollisionPointCircle(RL_GetMousePosition(), points[i], 8.0f))
            {
                focusedPoint = i;
                if (RL_IsMouseButtonDown(MOUSE_LEFT_BUTTON)) selectedPoint = i; 
                break;
            }
            else focusedPoint = -1;
        }
        
        // Spline point movement logic
        if (selectedPoint >= 0)
        {
            points[selectedPoint] = RL_GetMousePosition();
            if (RL_IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) selectedPoint = -1;
        }
        
        // Cubic Bezier spline control points logic
        if ((splineTypeActive == SPLINE_BEZIER) && (focusedPoint == -1))
        {
            // Spline control point focus and selection logic
            for (int i = 0; i < pointCount - 1; i++)
            {
                if (RL_CheckCollisionPointCircle(RL_GetMousePosition(), control[i].start, 6.0f))
                {
                    focusedControlPoint = &control[i].start;
                    if (RL_IsMouseButtonDown(MOUSE_LEFT_BUTTON)) selectedControlPoint = &control[i].start; 
                    break;
                }
                else if (RL_CheckCollisionPointCircle(RL_GetMousePosition(), control[i].end, 6.0f))
                {
                    focusedControlPoint = &control[i].end;
                    if (RL_IsMouseButtonDown(MOUSE_LEFT_BUTTON)) selectedControlPoint = &control[i].end; 
                    break;
                }
                else focusedControlPoint = NULL;
            }
            
            // Spline control point movement logic
            if (selectedControlPoint != NULL)
            {
                *selectedControlPoint = RL_GetMousePosition();
                if (RL_IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) selectedControlPoint = NULL;
            }
        }
        
        // Spline selection logic
        if (RL_IsKeyPressed(KEY_ONE)) splineTypeActive = 0;
        else if (RL_IsKeyPressed(KEY_TWO)) splineTypeActive = 1;
        else if (RL_IsKeyPressed(KEY_THREE)) splineTypeActive = 2;
        else if (RL_IsKeyPressed(KEY_FOUR)) splineTypeActive = 3;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);
        
            if (splineTypeActive == SPLINE_LINEAR)
            {
                // Draw spline: linear
                RL_DrawSplineLinear(points, pointCount, splineThickness, RL_RED);
            }
            else if (splineTypeActive == SPLINE_BASIS)
            {
                // Draw spline: basis
                RL_DrawSplineBasis(points, pointCount, splineThickness, RL_RED);  // Provide connected points array

                /*
                for (int i = 0; i < (pointCount - 3); i++)
                {
                    // Drawing individual segments, not considering thickness connection compensation
                    RL_DrawSplineSegmentBasis(points[i], points[i + 1], points[i + 2], points[i + 3], splineThickness, RL_MAROON);
                }
                */
            }
            else if (splineTypeActive == SPLINE_CATMULLROM)
            {
                // Draw spline: catmull-rom
                RL_DrawSplineCatmullRom(points, pointCount, splineThickness, RL_RED); // Provide connected points array
                
                /*
                for (int i = 0; i < (pointCount - 3); i++)
                {
                    // Drawing individual segments, not considering thickness connection compensation
                    RL_DrawSplineSegmentCatmullRom(points[i], points[i + 1], points[i + 2], points[i + 3], splineThickness, RL_MAROON);
                }
                */
            }
            else if (splineTypeActive == SPLINE_BEZIER)
            {
                // NOTE: Cubic-bezier spline requires the 2 control points of each segnment to be 
                // provided interleaved with the start and end point of every segment
                for (int i = 0; i < (pointCount - 1); i++) 
                {
                    pointsInterleaved[3*i] = points[i];
                    pointsInterleaved[3*i + 1] = control[i].start;
                    pointsInterleaved[3*i + 2] = control[i].end;
                }
                
                pointsInterleaved[3*(pointCount - 1)] = points[pointCount - 1];

                // Draw spline: cubic-bezier (with control points)
                RL_DrawSplineBezierCubic(pointsInterleaved, 3*(pointCount - 1) + 1, splineThickness, RL_RED);
                
                /*
                for (int i = 0; i < 3*(pointCount - 1); i += 3)
                {
                    // Drawing individual segments, not considering thickness connection compensation
                    RL_DrawSplineSegmentBezierCubic(pointsInterleaved[i], pointsInterleaved[i + 1], pointsInterleaved[i + 2], pointsInterleaved[i + 3], splineThickness, RL_MAROON);
                }
                */

                // Draw spline control points
                for (int i = 0; i < pointCount - 1; i++)
                {
                    // Every cubic bezier point have two control points
                    RL_DrawCircleV(control[i].start, 6, RL_GOLD);
                    RL_DrawCircleV(control[i].end, 6, RL_GOLD);
                    if (focusedControlPoint == &control[i].start) RL_DrawCircleV(control[i].start, 8, RL_GREEN);
                    else if (focusedControlPoint == &control[i].end) RL_DrawCircleV(control[i].end, 8, RL_GREEN);
                    RL_DrawLineEx(points[i], control[i].start, 1.0f, RL_LIGHTGRAY);
                    RL_DrawLineEx(points[i + 1], control[i].end, 1.0f, RL_LIGHTGRAY);
                
                    // Draw spline control lines
                    RL_DrawLineV(points[i], control[i].start, RL_GRAY);
                    //RL_DrawLineV(control[i].start, control[i].end, RL_LIGHTGRAY);
                    RL_DrawLineV(control[i].end, points[i + 1], RL_GRAY);
                }
            }

            if (splineHelpersActive)
            {
                // Draw spline point helpers
                for (int i = 0; i < pointCount; i++)
                {
                    RL_DrawCircleLinesV(points[i], (focusedPoint == i)? 12.0f : 8.0f, (focusedPoint == i)? RL_BLUE: RL_DARKBLUE);
                    if ((splineTypeActive != SPLINE_LINEAR) &&
                        (splineTypeActive != SPLINE_BEZIER) &&
                        (i < pointCount - 1)) RL_DrawLineV(points[i], points[i + 1], RL_GRAY);

                    RL_DrawText(RL_TextFormat("[%.0f, %.0f]", points[i].x, points[i].y), (int)points[i].x, (int)points[i].y + 10, 10, RL_BLACK);
                }
            }

            // Check all possible UI states that require controls lock
            if (splineTypeEditMode) GuiLock();
            
            // Draw spline config
            GuiLabel((RL_Rectangle){ 12, 62, 140, 24 }, RL_TextFormat("Spline thickness: %i", (int)splineThickness));
            GuiSliderBar((RL_Rectangle){ 12, 60 + 24, 140, 16 }, NULL, NULL, &splineThickness, 1.0f, 40.0f);

            GuiCheckBox((RL_Rectangle){ 12, 110, 20, 20 }, "Show point helpers", &splineHelpersActive);

            GuiUnlock();

            GuiLabel((RL_Rectangle){ 12, 10, 140, 24 }, "Spline type:");
            if (GuiDropdownBox((RL_Rectangle){ 12, 8 + 24, 140, 28 }, "LINEAR;BSPLINE;CATMULLROM;BEZIER", &splineTypeActive, splineTypeEditMode)) splineTypeEditMode = !splineTypeEditMode;

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
