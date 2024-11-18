/*******************************************************************************************
*
*   raylib [core] example - Generates a random sequence
*
*   Example originally created with raylib 5.0, last time updated with raylib 5.0
*
*   Example contributed by Dalton Overmyer (@REDl3east) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023 Dalton Overmyer (@REDl3east)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

#include <stdlib.h> // Required for: malloc() and free()

typedef struct ColorRect{
  RL_Color c;
  RL_Rectangle r;
} ColorRect;

static RL_Color GenerateRandomColor();
static ColorRect* GenerateRandomColorRectSequence(float rectCount, float rectWidth, float screenWidth, float screenHeight);
static void ShuffleColorRectSequence(ColorRect* rectangles, int rectCount);
static void DrawTextCenterKeyHelp(const char* key, const char* text, int posX, int posY, int fontSize, RL_Color color);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 450;

  RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - Generates a random sequence");

  int rectCount = 20;
  float rectSize = (float)screenWidth/rectCount;
  ColorRect* rectangles = GenerateRandomColorRectSequence((float)rectCount, rectSize, (float)screenWidth, 0.75f * screenHeight);

  RL_SetTargetFPS(60);
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!RL_WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------

    if(RL_IsKeyPressed(KEY_SPACE))
    {
      ShuffleColorRectSequence(rectangles, rectCount);
    }

    if(RL_IsKeyPressed(KEY_UP))
    {
      rectCount++;
      rectSize = (float)screenWidth/rectCount;
      free(rectangles);
      rectangles = GenerateRandomColorRectSequence((float)rectCount, rectSize, (float)screenWidth, 0.75f * screenHeight);
    }

    if(RL_IsKeyPressed(KEY_DOWN))
    {
      if(rectCount >= 4){
        rectCount--;
        rectSize = (float)screenWidth/rectCount;
        free(rectangles);
        rectangles = GenerateRandomColorRectSequence((float)rectCount, rectSize, (float)screenWidth, 0.75f * screenHeight);
      }
    }

    // Draw
    //----------------------------------------------------------------------------------
    RL_BeginDrawing();

    RL_ClearBackground(RL_RAYWHITE);
    
    int fontSize = 20;
    for(int x=0;x<rectCount;x++)
    {
      RL_DrawRectangleRec(rectangles[x].r, rectangles[x].c);
      DrawTextCenterKeyHelp("SPACE", "to shuffle the sequence.", 10, screenHeight - 96, fontSize, RL_BLACK);
      DrawTextCenterKeyHelp("UP", "to add a rectangle and generate a new sequence.", 10, screenHeight - 64, fontSize, RL_BLACK);
      DrawTextCenterKeyHelp("DOWN", "to remove a rectangle and generate a new sequence.", 10, screenHeight - 32, fontSize, RL_BLACK);
    }

    const char* rectCountText = RL_TextFormat("%d rectangles", rectCount);
    int rectCountTextSize = RL_MeasureText(rectCountText, fontSize);
    RL_DrawText(rectCountText, screenWidth - rectCountTextSize - 10, 10, fontSize, RL_BLACK);

    RL_DrawFPS(10, 10);

    RL_EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------

  free(rectangles);
  RL_CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

static RL_Color GenerateRandomColor()
{
  return CLITERAL(RL_Color){
    RL_GetRandomValue(0, 255),
    RL_GetRandomValue(0, 255),
    RL_GetRandomValue(0, 255),
    255,
  };
}

static ColorRect* GenerateRandomColorRectSequence(float rectCount, float rectWidth, float screenWidth, float screenHeight){
  int *seq = RL_LoadRandomSequence((unsigned int)rectCount, 0, (unsigned int)rectCount-1);
  ColorRect* rectangles = (ColorRect *)malloc((int)rectCount*sizeof(ColorRect));

  float rectSeqWidth = rectCount * rectWidth;
  float startX = (screenWidth - rectSeqWidth) * 0.5f;

  for(int x=0;x<rectCount;x++){
    int rectHeight = (int)Remap((float)seq[x], 0, rectCount-1, 0, screenHeight);
    rectangles[x].c = GenerateRandomColor();
    rectangles[x].r = CLITERAL(RL_Rectangle){
      startX + x * rectWidth, screenHeight - rectHeight, rectWidth, (float)rectHeight
    };
  }
  RL_UnloadRandomSequence(seq);
  return rectangles;
}

static void ShuffleColorRectSequence(ColorRect* rectangles, int rectCount)
{
  int *seq = RL_LoadRandomSequence(rectCount, 0, rectCount-1);
  for(int i1=0;i1<rectCount;i1++){
    ColorRect* r1 = &rectangles[i1];
    ColorRect* r2 = &rectangles[seq[i1]];

    // swap only the color and height
    ColorRect tmp = *r1;
    r1->c = r2->c;
    r1->r.height = r2->r.height;
    r1->r.y = r2->r.y;
    r2->c = tmp.c;
    r2->r.height = tmp.r.height;
    r2->r.y = tmp.r.y;

  }
  RL_UnloadRandomSequence(seq);
}

static void DrawTextCenterKeyHelp(const char* key, const char* text, int posX, int posY, int fontSize, RL_Color color)
{
  int spaceSize = RL_MeasureText(" ", fontSize); 
  int pressSize = RL_MeasureText("Press", fontSize); 
  int keySize = RL_MeasureText(key, fontSize); 
  int textSize = RL_MeasureText(text, fontSize); 
  int totalSize = pressSize + 2 * spaceSize + keySize + 2 * spaceSize + textSize;
  int textSizeCurrent = 0;

  RL_DrawText("Press", posX, posY, fontSize, color);
  textSizeCurrent += pressSize + 2 * spaceSize;
  RL_DrawText(key, posX + textSizeCurrent, posY, fontSize, RL_RED);
  RL_DrawRectangle(posX + textSizeCurrent, posY + fontSize, keySize, 3, RL_RED);
  textSizeCurrent += keySize + 2 * spaceSize;
  RL_DrawText(text, posX + textSizeCurrent, posY, fontSize, color);
}