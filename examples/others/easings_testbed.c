/*******************************************************************************************
*
*   raylib [easings] example - Easings Testbed
*
*   Example originally created with raylib 2.5, last time updated with raylib 2.5
*
*   Example contributed by Juan Miguel López (@flashback-fx) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 Juan Miguel López (@flashback-fx ) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include "reasings.h"       // Required for easing functions

#define FONT_SIZE         20

#define D_STEP         20.0f
#define D_STEP_FINE     2.0f
#define D_MIN           1.0f
#define D_MAX       10000.0f

// Easing types
enum EasingTypes {
    EASE_LINEAR_NONE = 0,
    EASE_LINEAR_IN,
    EASE_LINEAR_OUT,
    EASE_LINEAR_IN_OUT,
    EASE_SINE_IN,
    EASE_SINE_OUT,
    EASE_SINE_IN_OUT,
    EASE_CIRC_IN,
    EASE_CIRC_OUT,
    EASE_CIRC_IN_OUT,
    EASE_CUBIC_IN,
    EASE_CUBIC_OUT,
    EASE_CUBIC_IN_OUT,
    EASE_QUAD_IN,
    EASE_QUAD_OUT,
    EASE_QUAD_IN_OUT,
    EASE_EXPO_IN,
    EASE_EXPO_OUT,
    EASE_EXPO_IN_OUT,
    EASE_BACK_IN,
    EASE_BACK_OUT,
    EASE_BACK_IN_OUT,
    EASE_BOUNCE_OUT,
    EASE_BOUNCE_IN,
    EASE_BOUNCE_IN_OUT,
    EASE_ELASTIC_IN,
    EASE_ELASTIC_OUT,
    EASE_ELASTIC_IN_OUT,
    NUM_EASING_TYPES,
    EASING_NONE = NUM_EASING_TYPES
};

static float NoEase(float t, float b, float c, float d);  // NoEase function declaration, function used when "no easing" is selected for any axis

// Easing functions reference data
static const struct {
    const char *name;
    float (*func)(float, float, float, float);
} Easings[] = {
    [EASE_LINEAR_NONE] = { .name = "EaseLinearNone", .func = EaseLinearNone },
    [EASE_LINEAR_IN] = { .name = "EaseLinearIn", .func = EaseLinearIn },
    [EASE_LINEAR_OUT] = { .name = "EaseLinearOut", .func = EaseLinearOut },
    [EASE_LINEAR_IN_OUT] = { .name = "EaseLinearInOut", .func = EaseLinearInOut },
    [EASE_SINE_IN] = { .name = "EaseSineIn", .func = EaseSineIn },
    [EASE_SINE_OUT] = { .name = "EaseSineOut", .func = EaseSineOut },
    [EASE_SINE_IN_OUT] = { .name = "EaseSineInOut", .func = EaseSineInOut },
    [EASE_CIRC_IN] = { .name = "EaseCircIn", .func = EaseCircIn },
    [EASE_CIRC_OUT] = { .name = "EaseCircOut", .func = EaseCircOut },
    [EASE_CIRC_IN_OUT] = { .name = "EaseCircInOut", .func = EaseCircInOut },
    [EASE_CUBIC_IN] = { .name = "EaseCubicIn", .func = EaseCubicIn },
    [EASE_CUBIC_OUT] = { .name = "EaseCubicOut", .func = EaseCubicOut },
    [EASE_CUBIC_IN_OUT] = { .name = "EaseCubicInOut", .func = EaseCubicInOut },
    [EASE_QUAD_IN] = { .name = "EaseQuadIn", .func = EaseQuadIn },
    [EASE_QUAD_OUT] = { .name = "EaseQuadOut", .func = EaseQuadOut },
    [EASE_QUAD_IN_OUT] = { .name = "EaseQuadInOut", .func = EaseQuadInOut },
    [EASE_EXPO_IN] = { .name = "EaseExpoIn", .func = EaseExpoIn },
    [EASE_EXPO_OUT] = { .name = "EaseExpoOut", .func = EaseExpoOut },
    [EASE_EXPO_IN_OUT] = { .name = "EaseExpoInOut", .func = EaseExpoInOut },
    [EASE_BACK_IN] = { .name = "EaseBackIn", .func = EaseBackIn },
    [EASE_BACK_OUT] = { .name = "EaseBackOut", .func = EaseBackOut },
    [EASE_BACK_IN_OUT] = { .name = "EaseBackInOut", .func = EaseBackInOut },
    [EASE_BOUNCE_OUT] = { .name = "EaseBounceOut", .func = EaseBounceOut },
    [EASE_BOUNCE_IN] = { .name = "EaseBounceIn", .func = EaseBounceIn },
    [EASE_BOUNCE_IN_OUT] = { .name = "EaseBounceInOut", .func = EaseBounceInOut },
    [EASE_ELASTIC_IN] = { .name = "EaseElasticIn", .func = EaseElasticIn },
    [EASE_ELASTIC_OUT] = { .name = "EaseElasticOut", .func = EaseElasticOut },
    [EASE_ELASTIC_IN_OUT] = { .name = "EaseElasticInOut", .func = EaseElasticInOut },
    [EASING_NONE] = { .name = "None", .func = NoEase },
};

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [easings] example - easings testbed");

    RL_Vector2 ballPosition = { 100.0f, 100.0f };

    float t = 0.0f;             // Current time (in any unit measure, but same unit as duration)
    float d = 300.0f;           // Total time it should take to complete (duration)
    bool paused = true;
    bool boundedT = true;       // If true, t will stop when d >= td, otherwise t will keep adding td to its value every loop

    int easingX = EASING_NONE;  // Easing selected for x axis
    int easingY = EASING_NONE;  // Easing selected for y axis

    RL_SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsKeyPressed(KEY_T)) boundedT = !boundedT;

        // Choose easing for the X axis
        if (RL_IsKeyPressed(KEY_RIGHT))
        {
            easingX++;

            if (easingX > EASING_NONE) easingX = 0;
        }
        else if (RL_IsKeyPressed(KEY_LEFT))
        {
            if (easingX == 0) easingX = EASING_NONE;
            else easingX--;
        }

        // Choose easing for the Y axis
        if (RL_IsKeyPressed(KEY_DOWN))
        {
            easingY++;

            if (easingY > EASING_NONE) easingY = 0;
        }
        else if (RL_IsKeyPressed(KEY_UP))
        {
            if (easingY == 0) easingY = EASING_NONE;
            else easingY--;
        }

        // Change d (duration) value
        if (RL_IsKeyPressed(KEY_W) && d < D_MAX - D_STEP) d += D_STEP;
        else if (RL_IsKeyPressed(KEY_Q) && d > D_MIN + D_STEP) d -= D_STEP;

        if (RL_IsKeyDown(KEY_S) && d < D_MAX - D_STEP_FINE) d += D_STEP_FINE;
        else if (RL_IsKeyDown(KEY_A) && d > D_MIN + D_STEP_FINE) d -= D_STEP_FINE;

        // Play, pause and restart controls
        if (RL_IsKeyPressed(KEY_SPACE) || RL_IsKeyPressed(KEY_T) ||
            RL_IsKeyPressed(KEY_RIGHT) || RL_IsKeyPressed(KEY_LEFT) ||
            RL_IsKeyPressed(KEY_DOWN) || RL_IsKeyPressed(KEY_UP) ||
            RL_IsKeyPressed(KEY_W) || RL_IsKeyPressed(KEY_Q) ||
            RL_IsKeyDown(KEY_S)  || RL_IsKeyDown(KEY_A) ||
            (RL_IsKeyPressed(KEY_ENTER) && (boundedT == true) && (t >= d)))
        {
            t = 0.0f;
            ballPosition.x = 100.0f;
            ballPosition.y = 100.0f;
            paused = true;
        }

        if (RL_IsKeyPressed(KEY_ENTER)) paused = !paused;

        // Movement computation
        if (!paused && ((boundedT && t < d) || !boundedT))
        {
            ballPosition.x = Easings[easingX].func(t, 100.0f, 700.0f - 170.0f, d);
            ballPosition.y = Easings[easingY].func(t, 100.0f, 400.0f - 170.0f, d);
            t += 1.0f;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            // Draw information text
            RL_DrawText(RL_TextFormat("Easing x: %s", Easings[easingX].name), 20, FONT_SIZE, FONT_SIZE, RL_LIGHTGRAY);
            RL_DrawText(RL_TextFormat("Easing y: %s", Easings[easingY].name), 20, FONT_SIZE*2, FONT_SIZE, RL_LIGHTGRAY);
            RL_DrawText(RL_TextFormat("t (%c) = %.2f d = %.2f", (boundedT == true)? 'b' : 'u', t, d), 20, FONT_SIZE*3, FONT_SIZE, RL_LIGHTGRAY);

            // Draw instructions text
            RL_DrawText("Use ENTER to play or pause movement, use SPACE to restart", 20, RL_GetScreenHeight() - FONT_SIZE*2, FONT_SIZE, RL_LIGHTGRAY);
            RL_DrawText("Use Q and W or A and S keys to change duration", 20, RL_GetScreenHeight() - FONT_SIZE*3, FONT_SIZE, RL_LIGHTGRAY);
            RL_DrawText("Use LEFT or RIGHT keys to choose easing for the x axis", 20, RL_GetScreenHeight() - FONT_SIZE*4, FONT_SIZE, RL_LIGHTGRAY);
            RL_DrawText("Use UP or DOWN keys to choose easing for the y axis", 20, RL_GetScreenHeight() - FONT_SIZE*5, FONT_SIZE, RL_LIGHTGRAY);

            // Draw ball
            RL_DrawCircleV(ballPosition, 16.0f, RL_MAROON);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}


// NoEase function, used when "no easing" is selected for any axis. It just ignores all parameters besides b.
static float NoEase(float t, float b, float c, float d)
{
    float burn = t + b + c + d;  // Hack to avoid compiler warning (about unused variables)
    d += burn;

    return b;
}
