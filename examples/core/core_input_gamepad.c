/*******************************************************************************************
*
*   raylib [core] example - Gamepad input
*
*   NOTE: This example requires a Gamepad connected to the system
*         raylib is configured to work with the following gamepads:
*                - Xbox 360 Controller (Xbox 360, Xbox One)
*                - PLAYSTATION(R)3 Controller
*         Check raylib.h for buttons configuration
*
*   Example originally created with raylib 1.1, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

// NOTE: Gamepad name ID depends on drivers and OS
#define XBOX_ALIAS_1 "xbox"
#define XBOX_ALIAS_2 "x-box"
#define PS_ALIAS     "playstation"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_SetConfigFlags(FLAG_MSAA_4X_HINT);  // Set MSAA 4X hint before windows creation

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - gamepad input");

    RL_Texture2D texPs3Pad = RL_LoadTexture("resources/ps3.png");
    RL_Texture2D texXboxPad = RL_LoadTexture("resources/xbox.png");

    // Set axis deadzones
    const float leftStickDeadzoneX = 0.1f;
    const float leftStickDeadzoneY = 0.1f;
    const float rightStickDeadzoneX = 0.1f;
    const float rightStickDeadzoneY = 0.1f;
    const float leftTriggerDeadzone = -0.9f;
    const float rightTriggerDeadzone = -0.9f;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    int gamepad = 0; // which gamepad to display

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // ...
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            if (RL_IsKeyPressed(KEY_LEFT) && gamepad > 0) gamepad--;
            if (RL_IsKeyPressed(KEY_RIGHT)) gamepad++;

            if (RL_IsGamepadAvailable(gamepad))
            {
                RL_DrawText(RL_TextFormat("GP%d: %s", gamepad, RL_GetGamepadName(gamepad)), 10, 10, 10, RL_BLACK);

                // Get axis values
                float leftStickX = RL_GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X);
                float leftStickY = RL_GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y);
                float rightStickX = RL_GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X);
                float rightStickY = RL_GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y);
                float leftTrigger = RL_GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER);
                float rightTrigger = RL_GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER);

                // Calculate deadzones
                if (leftStickX > -leftStickDeadzoneX && leftStickX < leftStickDeadzoneX) leftStickX = 0.0f;
                if (leftStickY > -leftStickDeadzoneY && leftStickY < leftStickDeadzoneY) leftStickY = 0.0f;
                if (rightStickX > -rightStickDeadzoneX && rightStickX < rightStickDeadzoneX) rightStickX = 0.0f;
                if (rightStickY > -rightStickDeadzoneY && rightStickY < rightStickDeadzoneY) rightStickY = 0.0f;
                if (leftTrigger < leftTriggerDeadzone) leftTrigger = -1.0f;
                if (rightTrigger < rightTriggerDeadzone) rightTrigger = -1.0f;

                if (RL_TextFindIndex(RL_TextToLower(RL_GetGamepadName(gamepad)), XBOX_ALIAS_1) > -1 || RL_TextFindIndex(RL_TextToLower(RL_GetGamepadName(gamepad)), XBOX_ALIAS_2) > -1)
                {
                    RL_DrawTexture(texXboxPad, 0, 0, RL_DARKGRAY);

                    // Draw buttons: xbox home
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE)) RL_DrawCircle(394, 89, 19, RL_RED);

                    // Draw buttons: basic
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT)) RL_DrawCircle(436, 150, 9, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_LEFT)) RL_DrawCircle(352, 150, 9, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) RL_DrawCircle(501, 151, 15, RL_BLUE);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) RL_DrawCircle(536, 187, 15, RL_LIME);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) RL_DrawCircle(572, 151, 15, RL_MAROON);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP)) RL_DrawCircle(536, 115, 15, RL_GOLD);

                    // Draw buttons: d-pad
                    RL_DrawRectangle(317, 202, 19, 71, RL_BLACK);
                    RL_DrawRectangle(293, 228, 69, 19, RL_BLACK);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP)) RL_DrawRectangle(317, 202, 19, 26, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) RL_DrawRectangle(317, 202 + 45, 19, 26, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) RL_DrawRectangle(292, 228, 25, 19, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) RL_DrawRectangle(292 + 44, 228, 26, 19, RL_RED);

                    // Draw buttons: left-right back
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) RL_DrawCircle(259, 61, 20, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) RL_DrawCircle(536, 61, 20, RL_RED);

                    // Draw axis: left joystick
                    RL_Color leftGamepadColor = RL_BLACK;
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_THUMB)) leftGamepadColor = RL_RED;
                    RL_DrawCircle(259, 152, 39, RL_BLACK);
                    RL_DrawCircle(259, 152, 34, RL_LIGHTGRAY);
                    RL_DrawCircle(259 + (int)(leftStickX*20),
                               152 + (int)(leftStickY*20), 25, leftGamepadColor);

                    // Draw axis: right joystick
                    RL_Color rightGamepadColor = RL_BLACK;
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_THUMB)) rightGamepadColor = RL_RED;
                    RL_DrawCircle(461, 237, 38, RL_BLACK);
                    RL_DrawCircle(461, 237, 33, RL_LIGHTGRAY);
                    RL_DrawCircle(461 + (int)(rightStickX*20),
                               237 + (int)(rightStickY*20), 25, rightGamepadColor);

                    // Draw axis: left-right triggers
                    RL_DrawRectangle(170, 30, 15, 70, RL_GRAY);
                    RL_DrawRectangle(604, 30, 15, 70, RL_GRAY);
                    RL_DrawRectangle(170, 30, 15, (int)(((1 + leftTrigger)/2)*70), RL_RED);
                    RL_DrawRectangle(604, 30, 15, (int)(((1 + rightTrigger)/2)*70), RL_RED);

                    //RL_DrawText(RL_TextFormat("Xbox axis LT: %02.02f", RL_GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_TRIGGER)), 10, 40, 10, RL_BLACK);
                    //RL_DrawText(RL_TextFormat("Xbox axis RT: %02.02f", RL_GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_TRIGGER)), 10, 60, 10, RL_BLACK);
                }
                else if (RL_TextFindIndex(RL_TextToLower(RL_GetGamepadName(gamepad)), PS_ALIAS) > -1)
                {
                    RL_DrawTexture(texPs3Pad, 0, 0, RL_DARKGRAY);

                    // Draw buttons: ps
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE)) RL_DrawCircle(396, 222, 13, RL_RED);

                    // Draw buttons: basic
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_LEFT)) RL_DrawRectangle(328, 170, 32, 13, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT)) RL_DrawTriangle((RL_Vector2){ 436, 168 }, (RL_Vector2){ 436, 185 }, (RL_Vector2){ 464, 177 }, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP)) RL_DrawCircle(557, 144, 13, RL_LIME);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) RL_DrawCircle(586, 173, 13, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) RL_DrawCircle(557, 203, 13, RL_VIOLET);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) RL_DrawCircle(527, 173, 13, RL_PINK);

                    // Draw buttons: d-pad
                    RL_DrawRectangle(225, 132, 24, 84, RL_BLACK);
                    RL_DrawRectangle(195, 161, 84, 25, RL_BLACK);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP)) RL_DrawRectangle(225, 132, 24, 29, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) RL_DrawRectangle(225, 132 + 54, 24, 30, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) RL_DrawRectangle(195, 161, 30, 25, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) RL_DrawRectangle(195 + 54, 161, 30, 25, RL_RED);

                    // Draw buttons: left-right back buttons
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) RL_DrawCircle(239, 82, 20, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) RL_DrawCircle(557, 82, 20, RL_RED);

                    // Draw axis: left joystick
                    RL_Color leftGamepadColor = RL_BLACK;
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_THUMB)) leftGamepadColor = RL_RED;
                    RL_DrawCircle(319, 255, 35, RL_BLACK);
                    RL_DrawCircle(319, 255, 31, RL_LIGHTGRAY);
                    RL_DrawCircle(319 + (int)(leftStickX*20),
                               255 + (int)(leftStickY*20), 25, leftGamepadColor);

                    // Draw axis: right joystick
                    RL_Color rightGamepadColor = RL_BLACK;
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_THUMB)) rightGamepadColor = RL_RED;
                    RL_DrawCircle(475, 255, 35, RL_BLACK);
                    RL_DrawCircle(475, 255, 31, RL_LIGHTGRAY);
                    RL_DrawCircle(475 + (int)(rightStickX*20),
                               255 + (int)(rightStickY*20), 25, rightGamepadColor);

                    // Draw axis: left-right triggers
                    RL_DrawRectangle(169, 48, 15, 70, RL_GRAY);
                    RL_DrawRectangle(611, 48, 15, 70, RL_GRAY);
                    RL_DrawRectangle(169, 48, 15, (int)(((1 + leftTrigger)/2)*70), RL_RED);
                    RL_DrawRectangle(611, 48, 15, (int)(((1 + rightTrigger)/2)*70), RL_RED);
                }
                else
                {

                    // Draw background: generic
                    RL_DrawRectangleRounded((RL_Rectangle){ 175, 110, 460, 220}, 0.3f, 16, RL_DARKGRAY);

                    // Draw buttons: basic
                    RL_DrawCircle(365, 170, 12, RL_RAYWHITE);
                    RL_DrawCircle(405, 170, 12, RL_RAYWHITE);
                    RL_DrawCircle(445, 170, 12, RL_RAYWHITE);
                    RL_DrawCircle(516, 191, 17, RL_RAYWHITE);
                    RL_DrawCircle(551, 227, 17, RL_RAYWHITE);
                    RL_DrawCircle(587, 191, 17, RL_RAYWHITE);
                    RL_DrawCircle(551, 155, 17, RL_RAYWHITE);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_LEFT)) RL_DrawCircle(365, 170, 10, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE)) RL_DrawCircle(405, 170, 10, RL_GREEN);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_MIDDLE_RIGHT)) RL_DrawCircle(445, 170, 10, RL_BLUE);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) RL_DrawCircle(516, 191, 15, RL_GOLD);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) RL_DrawCircle(551, 227, 15, RL_BLUE);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) RL_DrawCircle(587, 191, 15, RL_GREEN);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_FACE_UP)) RL_DrawCircle(551, 155, 15, RL_RED);

                    // Draw buttons: d-pad
                    RL_DrawRectangle(245, 145, 28, 88, RL_RAYWHITE);
                    RL_DrawRectangle(215, 174, 88, 29, RL_RAYWHITE);
                    RL_DrawRectangle(247, 147, 24, 84, RL_BLACK);
                    RL_DrawRectangle(217, 176, 84, 25, RL_BLACK);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_UP)) RL_DrawRectangle(247, 147, 24, 29, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) RL_DrawRectangle(247, 147 + 54, 24, 30, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) RL_DrawRectangle(217, 176, 30, 25, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) RL_DrawRectangle(217 + 54, 176, 30, 25, RL_RED);

                    // Draw buttons: left-right back
                    RL_DrawRectangleRounded((RL_Rectangle){ 215, 98, 100, 10}, 0.5f, 16, RL_DARKGRAY);
                    RL_DrawRectangleRounded((RL_Rectangle){ 495, 98, 100, 10}, 0.5f, 16, RL_DARKGRAY);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_TRIGGER_1)) RL_DrawRectangleRounded((RL_Rectangle){ 215, 98, 100, 10}, 0.5f, 16, RL_RED);
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_TRIGGER_1)) RL_DrawRectangleRounded((RL_Rectangle){ 495, 98, 100, 10}, 0.5f, 16, RL_RED);

                    // Draw axis: left joystick
                    RL_Color leftGamepadColor = RL_BLACK;
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_LEFT_THUMB)) leftGamepadColor = RL_RED;
                    RL_DrawCircle(345, 260, 40, RL_BLACK);
                    RL_DrawCircle(345, 260, 35, RL_LIGHTGRAY);
                    RL_DrawCircle(345 + (int)(leftStickX*20),
                               260 + (int)(leftStickY*20), 25, leftGamepadColor);

                    // Draw axis: right joystick
                    RL_Color rightGamepadColor = RL_BLACK;
                    if (RL_IsGamepadButtonDown(gamepad, GAMEPAD_BUTTON_RIGHT_THUMB)) rightGamepadColor = RL_RED;
                    RL_DrawCircle(465, 260, 40, RL_BLACK);
                    RL_DrawCircle(465, 260, 35, RL_LIGHTGRAY);
                    RL_DrawCircle(465 + (int)(rightStickX*20),
                               260 + (int)(rightStickY*20), 25, rightGamepadColor);

                    // Draw axis: left-right triggers
                    RL_DrawRectangle(151, 110, 15, 70, RL_GRAY);
                    RL_DrawRectangle(644, 110, 15, 70, RL_GRAY);
                    RL_DrawRectangle(151, 110, 15, (int)(((1 + leftTrigger)/2)*70), RL_RED);
                    RL_DrawRectangle(644, 110, 15, (int)(((1 + rightTrigger)/2)*70), RL_RED);

                }

                RL_DrawText(RL_TextFormat("DETECTED AXIS [%i]:", RL_GetGamepadAxisCount(0)), 10, 50, 10, RL_MAROON);

                for (int i = 0; i < RL_GetGamepadAxisCount(0); i++)
                {
                    RL_DrawText(RL_TextFormat("AXIS %i: %.02f", i, RL_GetGamepadAxisMovement(0, i)), 20, 70 + 20*i, 10, RL_DARKGRAY);
                }

                if (RL_GetGamepadButtonPressed() != GAMEPAD_BUTTON_UNKNOWN) RL_DrawText(RL_TextFormat("DETECTED BUTTON: %i", RL_GetGamepadButtonPressed()), 10, 430, 10, RL_RED);
                else RL_DrawText("DETECTED BUTTON: NONE", 10, 430, 10, RL_GRAY);
            }
            else
            {
                RL_DrawText(RL_TextFormat("GP%d: NOT DETECTED", gamepad), 10, 10, 10, RL_GRAY);

                RL_DrawTexture(texXboxPad, 0, 0, RL_LIGHTGRAY);
            }

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_UnloadTexture(texPs3Pad);
    RL_UnloadTexture(texXboxPad);

    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
