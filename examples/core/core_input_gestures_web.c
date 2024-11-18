/*******************************************************************************************
*
*   raylib [core] example - Input Gestures for Web
*
*   Example originally created with raylib 4.6-dev, last time updated with raylib 4.6-dev
*
*   Example contributed by ubkp (@ubkp) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023 ubkp (@ubkp)
*
********************************************************************************************/

#include "raylib.h"

#include "math.h"       // Required for the protractor angle graphic drawing

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h> // Required for the Web/HTML5
#endif

//--------------------------------------------------------------------------------------
// Global definitions and declarations
//--------------------------------------------------------------------------------------

// Common variables definitions
//--------------------------------------------------------------------------------------
int screenWidth = 800;                  // Update depending on web canvas
const int screenHeight = 450;
RL_Vector2 messagePosition = { 160, 7 };

// Last gesture variables definitions
//--------------------------------------------------------------------------------------
int lastGesture = 0;
RL_Vector2 lastGesturePosition = { 165, 130 };

// RL_Gesture log variables definitions and functions declarations
//--------------------------------------------------------------------------------------
#define GESTURE_LOG_SIZE 20
char gestureLog[GESTURE_LOG_SIZE][12] = { "" }; // The gesture log uses an array (as an inverted circular queue) to store the performed gestures
int gestureLogIndex = GESTURE_LOG_SIZE;         // The index for the inverted circular queue (moving from last to first direction, then looping around)
int previousGesture = 0;

char const *GetGestureName(int i)
{
   switch (i)  {
      case 0:   return "None";        break;
      case 1:   return "Tap";         break;
      case 2:   return "Double Tap";  break;
      case 4:   return "Hold";        break;
      case 8:   return "Drag";        break;
      case 16:  return "Swipe Right"; break;
      case 32:  return "Swipe Left";  break;
      case 64:  return "Swipe Up";    break;
      case 128: return "Swipe Down";  break;
      case 256: return "Pinch In";    break;
      case 512: return "Pinch Out";   break;
      default:  return "Unknown";     break;
   }
}

RL_Color GetGestureColor(int i)
{
   switch (i)  {
      case 0:   return RL_BLACK;   break;
      case 1:   return RL_BLUE;    break;
      case 2:   return RL_SKYBLUE; break;
      case 4:   return RL_BLACK;   break;
      case 8:   return RL_LIME;    break;
      case 16:  return RL_RED;     break;
      case 32:  return RL_RED;     break;
      case 64:  return RL_RED;     break;
      case 128: return RL_RED;     break;
      case 256: return RL_VIOLET;  break;
      case 512: return RL_ORANGE;  break;
      default:  return RL_BLACK;   break;
   }
}

int logMode = 1; // Log mode values: 0 shows repeated events; 1 hides repeated events; 2 shows repeated events but hide hold events; 3 hides repeated events and hide hold events

RL_Color gestureColor = { 0, 0, 0, 255 };
RL_Rectangle logButton1 = { 53, 7, 48, 26 };
RL_Rectangle logButton2 = { 108, 7, 36, 26 };
RL_Vector2 gestureLogPosition = { 10, 10 };

// Protractor variables definitions
//--------------------------------------------------------------------------------------
float angleLength = 90.0f;
float currentAngleDegrees = 0.0f;
RL_Vector2 finalVector = { 0.0f, 0.0f };
char currentAngleStr[7] = "";
RL_Vector2 protractorPosition = { 266.0f, 315.0f };

// Update
//--------------------------------------------------------------------------------------
void Update(void)
{
    // Handle common
    //--------------------------------------------------------------------------------------
    int i, ii; // Iterators that will be reused by all for loops
    const int currentGesture = RL_GetGestureDetected();
    const float currentDragDegrees = RL_GetGestureDragAngle();
    const float currentPitchDegrees = RL_GetGesturePinchAngle();
    const int touchCount = RL_GetTouchPointCount();

    // Handle last gesture
    //--------------------------------------------------------------------------------------
    if ((currentGesture != 0) && (currentGesture != 4) && (currentGesture != previousGesture)) lastGesture = currentGesture; // Filter the meaningful gestures (1, 2, 8 to 512) for the display

    // Handle gesture log
    //--------------------------------------------------------------------------------------
    if (RL_IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        if (RL_CheckCollisionPointRec(RL_GetMousePosition(), logButton1))
        {
            switch (logMode)
            {
                case 3:  logMode=2; break;
                case 2:  logMode=3; break;
                case 1:  logMode=0; break;
                default: logMode=1; break;
            }
        }
        else if (RL_CheckCollisionPointRec(RL_GetMousePosition(), logButton2))
        {
            switch (logMode)
            {
                case 3:  logMode=1; break;
                case 2:  logMode=0; break;
                case 1:  logMode=3; break;
                default: logMode=2; break;
            }
        }
    }

    int fillLog = 0; // Gate variable to be used to allow or not the gesture log to be filled
    if (currentGesture !=0)
    {
        if (logMode == 3) // 3 hides repeated events and hide hold events
        {
            if (((currentGesture != 4) && (currentGesture != previousGesture)) || (currentGesture < 3)) fillLog = 1;
        }
        else if (logMode == 2) // 2 shows repeated events but hide hold events
        {
            if (currentGesture != 4) fillLog = 1;
        }
        else if (logMode == 1) // 1 hides repeated events
        {
            if (currentGesture != previousGesture) fillLog = 1;
        }
        else  // 0 shows repeated events
        {
            fillLog = 1;
        }
    }

    if (fillLog) // If one of the conditions from logMode was met, fill the gesture log
    {
        previousGesture = currentGesture;
        gestureColor = GetGestureColor(currentGesture);
        if (gestureLogIndex <= 0) gestureLogIndex = GESTURE_LOG_SIZE;
        gestureLogIndex--;

        // Copy the gesture respective name to the gesture log array
        RL_TextCopy(gestureLog[gestureLogIndex], GetGestureName(currentGesture));
    }

    // Handle protractor
    //--------------------------------------------------------------------------------------
    if (currentGesture > 255) // aka Pinch In and Pinch Out
    {
        currentAngleDegrees = currentPitchDegrees;
    }
    else if (currentGesture > 15) // aka Swipe Right, Swipe Left, Swipe Up and Swipe Down
    {
        currentAngleDegrees = currentDragDegrees;
    }
    else if (currentGesture > 0) // aka Tap, Doubletap, Hold and Grab
    {
        currentAngleDegrees = 0.0f;
    }

    float currentAngleRadians = ((currentAngleDegrees +90.0f)*PI/180); // Convert the current angle to Radians
    finalVector = (RL_Vector2){ (angleLength*sinf(currentAngleRadians)) + protractorPosition.x, (angleLength*cosf(currentAngleRadians)) + protractorPosition.y }; // Calculate the final vector for display

    // Handle touch and mouse pointer points
    //--------------------------------------------------------------------------------------
    #define MAX_TOUCH_COUNT     32

    RL_Vector2 touchPosition[MAX_TOUCH_COUNT] = { 0 };
    RL_Vector2 mousePosition = {0, 0};
    if (currentGesture != GESTURE_NONE)
    {
        if (touchCount != 0)
        {
            for (i = 0; i < touchCount; i++) touchPosition[i] = RL_GetTouchPosition(i); // Fill the touch positions
        }
        else mousePosition = RL_GetMousePosition();
    }

    // Draw
    //--------------------------------------------------------------------------------------
    RL_BeginDrawing();

        RL_ClearBackground(RL_RAYWHITE);

        // Draw common
        //--------------------------------------------------------------------------------------
        RL_DrawText("*", messagePosition.x + 5, messagePosition.y + 5, 10, RL_BLACK);
        RL_DrawText("Example optimized for Web/HTML5\non Smartphones with Touch Screen.", messagePosition.x + 15, messagePosition.y + 5, 10, RL_BLACK);
        RL_DrawText("*", messagePosition.x + 5, messagePosition.y + 35, 10, RL_BLACK);
        RL_DrawText("While running on Desktop Web Browsers,\ninspect and turn on Touch Emulation.", messagePosition.x + 15,  messagePosition.y + 35, 10, RL_BLACK);

        // Draw last gesture
        //--------------------------------------------------------------------------------------
        RL_DrawText("Last gesture", lastGesturePosition.x + 33, lastGesturePosition.y - 47, 20, RL_BLACK);
        RL_DrawText("Swipe         Tap       Pinch  Touch", lastGesturePosition.x + 17, lastGesturePosition.y - 18, 10, RL_BLACK);
        RL_DrawRectangle(lastGesturePosition.x + 20, lastGesturePosition.y, 20, 20, lastGesture == GESTURE_SWIPE_UP ? RL_RED : RL_LIGHTGRAY);
        RL_DrawRectangle(lastGesturePosition.x, lastGesturePosition.y + 20, 20, 20, lastGesture == GESTURE_SWIPE_LEFT ? RL_RED : RL_LIGHTGRAY);
        RL_DrawRectangle(lastGesturePosition.x + 40, lastGesturePosition.y + 20, 20, 20, lastGesture == GESTURE_SWIPE_RIGHT ? RL_RED : RL_LIGHTGRAY);
        RL_DrawRectangle(lastGesturePosition.x + 20, lastGesturePosition.y + 40, 20, 20, lastGesture == GESTURE_SWIPE_DOWN ? RL_RED : RL_LIGHTGRAY);
        RL_DrawCircle(lastGesturePosition.x + 80, lastGesturePosition.y + 16, 10, lastGesture == GESTURE_TAP ? RL_BLUE : RL_LIGHTGRAY);
        RL_DrawRing( (RL_Vector2){lastGesturePosition.x + 103, lastGesturePosition.y + 16}, 6.0f, 11.0f, 0.0f, 360.0f, 0, lastGesture == GESTURE_DRAG ? RL_LIME : RL_LIGHTGRAY);
        RL_DrawCircle(lastGesturePosition.x + 80, lastGesturePosition.y + 43, 10, lastGesture == GESTURE_DOUBLETAP ? RL_SKYBLUE : RL_LIGHTGRAY);
        RL_DrawCircle(lastGesturePosition.x + 103, lastGesturePosition.y + 43, 10, lastGesture == GESTURE_DOUBLETAP ? RL_SKYBLUE : RL_LIGHTGRAY);
        RL_DrawTriangle((RL_Vector2){ lastGesturePosition.x + 122, lastGesturePosition.y + 16 }, (RL_Vector2){ lastGesturePosition.x + 137, lastGesturePosition.y + 26 }, (RL_Vector2){ lastGesturePosition.x + 137, lastGesturePosition.y + 6 }, lastGesture == GESTURE_PINCH_OUT? RL_ORANGE : RL_LIGHTGRAY);
        RL_DrawTriangle((RL_Vector2){ lastGesturePosition.x + 147, lastGesturePosition.y + 6 }, (RL_Vector2){ lastGesturePosition.x + 147, lastGesturePosition.y + 26 }, (RL_Vector2){ lastGesturePosition.x + 162, lastGesturePosition.y + 16 }, lastGesture == GESTURE_PINCH_OUT? RL_ORANGE : RL_LIGHTGRAY);
        RL_DrawTriangle((RL_Vector2){ lastGesturePosition.x + 125, lastGesturePosition.y + 33 }, (RL_Vector2){ lastGesturePosition.x + 125, lastGesturePosition.y + 53 }, (RL_Vector2){ lastGesturePosition.x + 140, lastGesturePosition.y + 43 }, lastGesture == GESTURE_PINCH_IN? RL_VIOLET : RL_LIGHTGRAY);
        RL_DrawTriangle((RL_Vector2){ lastGesturePosition.x + 144, lastGesturePosition.y + 43 }, (RL_Vector2){ lastGesturePosition.x + 159, lastGesturePosition.y + 53 }, (RL_Vector2){ lastGesturePosition.x + 159, lastGesturePosition.y + 33 }, lastGesture == GESTURE_PINCH_IN? RL_VIOLET : RL_LIGHTGRAY);
        for (i = 0; i < 4; i++) RL_DrawCircle(lastGesturePosition.x + 180, lastGesturePosition.y + 7 + i*15, 5, touchCount <= i? RL_LIGHTGRAY : gestureColor);

        // Draw gesture log
        //--------------------------------------------------------------------------------------
        RL_DrawText("Log", gestureLogPosition.x, gestureLogPosition.y, 20, RL_BLACK);

        // Loop in both directions to print the gesture log array in the inverted order (and looping around if the index started somewhere in the middle)
        for (i = 0, ii = gestureLogIndex; i < GESTURE_LOG_SIZE; i++, ii = (ii + 1) % GESTURE_LOG_SIZE) RL_DrawText(gestureLog[ii], gestureLogPosition.x, gestureLogPosition.y + 410 - i*20, 20, (i == 0 ? gestureColor : RL_LIGHTGRAY));
        RL_Color logButton1Color, logButton2Color;
        switch (logMode)
        {
            case 3:  logButton1Color=RL_MAROON; logButton2Color=RL_MAROON; break;
            case 2:  logButton1Color=RL_GRAY;   logButton2Color=RL_MAROON; break;
            case 1:  logButton1Color=RL_MAROON; logButton2Color=RL_GRAY;   break;
            default: logButton1Color=RL_GRAY;   logButton2Color=RL_GRAY;   break;
        }
        RL_DrawRectangleRec(logButton1, logButton1Color);
        RL_DrawText("Hide", logButton1.x + 7, logButton1.y + 3, 10, RL_WHITE);
        RL_DrawText("Repeat", logButton1.x + 7, logButton1.y + 13, 10, RL_WHITE);
        RL_DrawRectangleRec(logButton2, logButton2Color);
        RL_DrawText("Hide", logButton1.x + 62, logButton1.y + 3, 10, RL_WHITE);
        RL_DrawText("Hold", logButton1.x + 62, logButton1.y + 13, 10, RL_WHITE);

        // Draw protractor
        //--------------------------------------------------------------------------------------
        RL_DrawText("Angle", protractorPosition.x + 55, protractorPosition.y + 76, 10, RL_BLACK);
        const char *angleString = RL_TextFormat("%f", currentAngleDegrees);
        const int angleStringDot = RL_TextFindIndex(angleString, ".");
        const char *angleStringTrim = RL_TextSubtext(angleString, 0, angleStringDot + 3);
        RL_DrawText( angleStringTrim, protractorPosition.x + 55, protractorPosition.y + 92, 20, gestureColor);
        RL_DrawCircle(protractorPosition.x, protractorPosition.y, 80.0f, RL_WHITE);
        RL_DrawLineEx((RL_Vector2){ protractorPosition.x - 90, protractorPosition.y }, (RL_Vector2){ protractorPosition.x + 90, protractorPosition.y }, 3.0f, RL_LIGHTGRAY);
        RL_DrawLineEx((RL_Vector2){ protractorPosition.x, protractorPosition.y - 90 }, (RL_Vector2){ protractorPosition.x, protractorPosition.y + 90 }, 3.0f, RL_LIGHTGRAY);
        RL_DrawLineEx((RL_Vector2){ protractorPosition.x - 80, protractorPosition.y - 45 }, (RL_Vector2){ protractorPosition.x + 80, protractorPosition.y + 45 }, 3.0f, RL_GREEN);
        RL_DrawLineEx((RL_Vector2){ protractorPosition.x - 80, protractorPosition.y + 45 }, (RL_Vector2){ protractorPosition.x + 80, protractorPosition.y - 45 }, 3.0f, RL_GREEN);
        RL_DrawText("0", protractorPosition.x + 96, protractorPosition.y - 9, 20, RL_BLACK);
        RL_DrawText("30", protractorPosition.x + 74, protractorPosition.y - 68, 20, RL_BLACK);
        RL_DrawText("90", protractorPosition.x - 11, protractorPosition.y - 110, 20, RL_BLACK);
        RL_DrawText("150", protractorPosition.x - 100, protractorPosition.y - 68, 20, RL_BLACK);
        RL_DrawText("180", protractorPosition.x - 124, protractorPosition.y - 9, 20, RL_BLACK);
        RL_DrawText("210", protractorPosition.x - 100, protractorPosition.y + 50, 20, RL_BLACK);
        RL_DrawText("270", protractorPosition.x - 18, protractorPosition.y + 92, 20, RL_BLACK);
        RL_DrawText("330", protractorPosition.x + 72, protractorPosition.y + 50, 20, RL_BLACK);
        if (currentAngleDegrees != 0.0f) RL_DrawLineEx(protractorPosition, finalVector, 3.0f, gestureColor);

        // Draw touch and mouse pointer points
        //--------------------------------------------------------------------------------------
        if (currentGesture != GESTURE_NONE)
        {
            if ( touchCount != 0 )
            {
                for (i = 0; i < touchCount; i++)
                {
                    RL_DrawCircleV(touchPosition[i], 50.0f, RL_Fade(gestureColor, 0.5f));
                    RL_DrawCircleV(touchPosition[i], 5.0f, gestureColor);
                }

                if (touchCount == 2) RL_DrawLineEx(touchPosition[0], touchPosition[1], ((currentGesture == 512)? 8 : 12), gestureColor);
            }
            else
            {
                RL_DrawCircleV(mousePosition, 35.0f, RL_Fade(gestureColor, 0.5f));
                RL_DrawCircleV(mousePosition, 5.0f, gestureColor);
            }
        }

    RL_EndDrawing();
    //--------------------------------------------------------------------------------------

}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - input gestures web");
    //--------------------------------------------------------------------------------------

    // Main game loop
    //--------------------------------------------------------------------------------------
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(Update, 0, 1);
    #else
        RL_SetTargetFPS(60);
        while (!RL_WindowShouldClose()) Update(); // Detect window close button or ESC key
    #endif
    //--------------------------------------------------------------------------------------

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
