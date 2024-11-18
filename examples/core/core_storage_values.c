/*******************************************************************************************
*
*   raylib [core] example - Storage save/load values
*
*   Example originally created with raylib 1.4, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include <stdlib.h>         // Required for: calloc(), free()

#define STORAGE_DATA_FILE   "storage.data"   // Storage file

// NOTE: Storage positions must start with 0, directly related to file memory layout
typedef enum {
    STORAGE_POSITION_SCORE      = 0,
    STORAGE_POSITION_HISCORE    = 1
} StorageData;

// Persistent storage functions
static bool SaveStorageValue(unsigned int position, int value);
static int LoadStorageValue(unsigned int position);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - storage save/load values");

    int score = 0;
    int hiscore = 0;
    int framesCounter = 0;

    RL_SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (RL_IsKeyPressed(KEY_R))
        {
            score = RL_GetRandomValue(1000, 2000);
            hiscore = RL_GetRandomValue(2000, 4000);
        }

        if (RL_IsKeyPressed(KEY_ENTER))
        {
            SaveStorageValue(STORAGE_POSITION_SCORE, score);
            SaveStorageValue(STORAGE_POSITION_HISCORE, hiscore);
        }
        else if (RL_IsKeyPressed(KEY_SPACE))
        {
            // NOTE: If requested position could not be found, value 0 is returned
            score = LoadStorageValue(STORAGE_POSITION_SCORE);
            hiscore = LoadStorageValue(STORAGE_POSITION_HISCORE);
        }

        framesCounter++;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_RAYWHITE);

            RL_DrawText(RL_TextFormat("SCORE: %i", score), 280, 130, 40, RL_MAROON);
            RL_DrawText(RL_TextFormat("HI-SCORE: %i", hiscore), 210, 200, 50, RL_BLACK);

            RL_DrawText(RL_TextFormat("frames: %i", framesCounter), 10, 10, 20, RL_LIME);

            RL_DrawText("Press R to generate random numbers", 220, 40, 20, RL_LIGHTGRAY);
            RL_DrawText("Press ENTER to SAVE values", 250, 310, 20, RL_LIGHTGRAY);
            RL_DrawText("Press SPACE to LOAD values", 252, 350, 20, RL_LIGHTGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Save integer value to storage file (to defined position)
// NOTE: Storage positions is directly related to file memory layout (4 bytes each integer)
bool SaveStorageValue(unsigned int position, int value)
{
    bool success = false;
    int dataSize = 0;
    unsigned int newDataSize = 0;
    unsigned char *fileData = RL_LoadFileData(STORAGE_DATA_FILE, &dataSize);
    unsigned char *newFileData = NULL;

    if (fileData != NULL)
    {
        if (dataSize <= (position*sizeof(int)))
        {
            // Increase data size up to position and store value
            newDataSize = (position + 1)*sizeof(int);
            newFileData = (unsigned char *)RL_REALLOC(fileData, newDataSize);

            if (newFileData != NULL)
            {
                // RL_REALLOC succeded
                int *dataPtr = (int *)newFileData;
                dataPtr[position] = value;
            }
            else
            {
                // RL_REALLOC failed
                RL_TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to realloc data (%u), position in bytes (%u) bigger than actual file size", STORAGE_DATA_FILE, dataSize, position*sizeof(int));

                // We store the old size of the file
                newFileData = fileData;
                newDataSize = dataSize;
            }
        }
        else
        {
            // Store the old size of the file
            newFileData = fileData;
            newDataSize = dataSize;

            // Replace value on selected position
            int *dataPtr = (int *)newFileData;
            dataPtr[position] = value;
        }

        success = RL_SaveFileData(STORAGE_DATA_FILE, newFileData, newDataSize);
        RL_FREE(newFileData);

        RL_TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", STORAGE_DATA_FILE, value);
    }
    else
    {
        RL_TraceLog(LOG_INFO, "FILEIO: [%s] File created successfully", STORAGE_DATA_FILE);

        dataSize = (position + 1)*sizeof(int);
        fileData = (unsigned char *)RL_MALLOC(dataSize);
        int *dataPtr = (int *)fileData;
        dataPtr[position] = value;

        success = RL_SaveFileData(STORAGE_DATA_FILE, fileData, dataSize);
        RL_UnloadFileData(fileData);

        RL_TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", STORAGE_DATA_FILE, value);
    }

    return success;
}

// Load integer value from storage file (from defined position)
// NOTE: If requested position could not be found, value 0 is returned
int LoadStorageValue(unsigned int position)
{
    int value = 0;
    int dataSize = 0;
    unsigned char *fileData = RL_LoadFileData(STORAGE_DATA_FILE, &dataSize);

    if (fileData != NULL)
    {
        if (dataSize < ((int)(position*4))) RL_TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i", STORAGE_DATA_FILE, position);
        else
        {
            int *dataPtr = (int *)fileData;
            value = dataPtr[position];
        }

        RL_UnloadFileData(fileData);

        RL_TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i", STORAGE_DATA_FILE, value);
    }

    return value;
}