/*******************************************************************************************
*
*   raylib [core] example - automation events
*
*   Example originally created with raylib 5.0, last time updated with raylib 5.0
*
*   Example based on 2d_camera_platformer example by arvyy (@arvyy)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

#define GRAVITY 400
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f

#define MAX_ENVIRONMENT_ELEMENTS    5

typedef struct Player {
    RL_Vector2 position;
    float speed;
    bool canJump;
} Player;

typedef struct EnvElement {
    RL_Rectangle rect;
    int blocking;
    RL_Color color;
} EnvElement;


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - automation events");

    // Define player
    Player player = { 0 };
    player.position = (RL_Vector2){ 400, 280 };
    player.speed = 0;
    player.canJump = false;
    
    // Define environment elements (platforms)
    EnvElement envElements[MAX_ENVIRONMENT_ELEMENTS] = {
        {{ 0, 0, 1000, 400 }, 0, RL_LIGHTGRAY },
        {{ 0, 400, 1000, 200 }, 1, RL_GRAY },
        {{ 300, 200, 400, 10 }, 1, RL_GRAY },
        {{ 250, 300, 100, 10 }, 1, RL_GRAY },
        {{ 650, 300, 100, 10 }, 1, RL_GRAY }
    };

    // Define camera
    RL_Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = (RL_Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    // Automation events
    RL_AutomationEventList aelist = RL_LoadAutomationEventList(0);  // Initialize list of automation events to record new events
    RL_SetAutomationEventList(&aelist);
    bool eventRecording = false;
    bool eventPlaying = false;
    
    unsigned int frameCounter = 0;
    unsigned int playFrameCounter = 0;
    unsigned int currentPlayFrame = 0;

    RL_SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        float deltaTime = 0.015f;//RL_GetFrameTime();
       
        // Dropped files logic
        //----------------------------------------------------------------------------------
        if (RL_IsFileDropped())
        {
            RL_FilePathList droppedFiles = RL_LoadDroppedFiles();

            // Supports loading .rgs style files (text or binary) and .png style palette images
            if (RL_IsFileExtension(droppedFiles.paths[0], ".txt;.rae"))
            {
                RL_UnloadAutomationEventList(aelist);
                aelist = RL_LoadAutomationEventList(droppedFiles.paths[0]);
                
                eventRecording = false;
                
                // Reset scene state to play
                eventPlaying = true;
                playFrameCounter = 0;
                currentPlayFrame = 0;
                
                player.position = (RL_Vector2){ 400, 280 };
                player.speed = 0;
                player.canJump = false;

                camera.target = player.position;
                camera.offset = (RL_Vector2){ screenWidth/2.0f, screenHeight/2.0f };
                camera.rotation = 0.0f;
                camera.zoom = 1.0f;
            }

            RL_UnloadDroppedFiles(droppedFiles);   // Unload filepaths from memory
        }
        //----------------------------------------------------------------------------------

        // Update player
        //----------------------------------------------------------------------------------
        if (RL_IsKeyDown(KEY_LEFT)) player.position.x -= PLAYER_HOR_SPD*deltaTime;
        if (RL_IsKeyDown(KEY_RIGHT)) player.position.x += PLAYER_HOR_SPD*deltaTime;
        if (RL_IsKeyDown(KEY_SPACE) && player.canJump)
        {
            player.speed = -PLAYER_JUMP_SPD;
            player.canJump = false;
        }

        int hitObstacle = 0;
        for (int i = 0; i < MAX_ENVIRONMENT_ELEMENTS; i++)
        {
            EnvElement *element = &envElements[i];
            RL_Vector2 *p = &(player.position);
            if (element->blocking &&
                element->rect.x <= p->x &&
                element->rect.x + element->rect.width >= p->x &&
                element->rect.y >= p->y &&
                element->rect.y <= p->y + player.speed*deltaTime)
            {
                hitObstacle = 1;
                player.speed = 0.0f;
                p->y = element->rect.y;
            }
        }

        if (!hitObstacle)
        {
            player.position.y += player.speed*deltaTime;
            player.speed += GRAVITY*deltaTime;
            player.canJump = false;
        }
        else player.canJump = true;

        if (RL_IsKeyPressed(KEY_R))
        {
            // Reset game state
            player.position = (RL_Vector2){ 400, 280 };
            player.speed = 0;
            player.canJump = false;

            camera.target = player.position;
            camera.offset = (RL_Vector2){ screenWidth/2.0f, screenHeight/2.0f };
            camera.rotation = 0.0f;
            camera.zoom = 1.0f;
        }
        //----------------------------------------------------------------------------------

        // Events playing
        // NOTE: Logic must be before RL_Camera update because it depends on mouse-wheel value, 
        // that can be set by the played event... but some other inputs could be affected
        //----------------------------------------------------------------------------------
        if (eventPlaying)
        {
            // NOTE: Multiple events could be executed in a single frame
            while (playFrameCounter == aelist.events[currentPlayFrame].frame)
            {
                RL_PlayAutomationEvent(aelist.events[currentPlayFrame]);
                currentPlayFrame++;

                if (currentPlayFrame == aelist.count)
                {
                    eventPlaying = false;
                    currentPlayFrame = 0;
                    playFrameCounter = 0;

                    RL_TraceLog(LOG_INFO, "FINISH PLAYING!");
                    break;
                }
            }

            playFrameCounter++;
        }
        //----------------------------------------------------------------------------------

        // Update camera
        //----------------------------------------------------------------------------------
        camera.target = player.position;
        camera.offset = (RL_Vector2){ screenWidth/2.0f, screenHeight/2.0f };
        float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

        // WARNING: On event replay, mouse-wheel internal value is set
        camera.zoom += ((float)RL_GetMouseWheelMove()*0.05f);
        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.25f) camera.zoom = 0.25f;

        for (int i = 0; i < MAX_ENVIRONMENT_ELEMENTS; i++)
        {
            EnvElement *element = &envElements[i];
            minX = fminf(element->rect.x, minX);
            maxX = fmaxf(element->rect.x + element->rect.width, maxX);
            minY = fminf(element->rect.y, minY);
            maxY = fmaxf(element->rect.y + element->rect.height, maxY);
        }

        RL_Vector2 max = RL_GetWorldToScreen2D((RL_Vector2){ maxX, maxY }, camera);
        RL_Vector2 min = RL_GetWorldToScreen2D((RL_Vector2){ minX, minY }, camera);

        if (max.x < screenWidth) camera.offset.x = screenWidth - (max.x - screenWidth/2);
        if (max.y < screenHeight) camera.offset.y = screenHeight - (max.y - screenHeight/2);
        if (min.x > 0) camera.offset.x = screenWidth/2 - min.x;
        if (min.y > 0) camera.offset.y = screenHeight/2 - min.y;
        //----------------------------------------------------------------------------------
        
        // Events management
        if (RL_IsKeyPressed(KEY_S))    // Toggle events recording
        {
            if (!eventPlaying)
            {
                if (eventRecording)
                {
                    RL_StopAutomationEventRecording();
                    eventRecording = false;
                    
                    RL_ExportAutomationEventList(aelist, "automation.rae");
                    
                    RL_TraceLog(LOG_INFO, "RECORDED FRAMES: %i", aelist.count);
                }
                else 
                {
                    RL_SetAutomationEventBaseFrame(180);
                    RL_StartAutomationEventRecording();
                    eventRecording = true;
                }
            }
        }
        else if (RL_IsKeyPressed(KEY_A)) // Toggle events playing (WARNING: Starts next frame)
        {
            if (!eventRecording && (aelist.count > 0))
            {
                // Reset scene state to play
                eventPlaying = true;
                playFrameCounter = 0;
                currentPlayFrame = 0;

                player.position = (RL_Vector2){ 400, 280 };
                player.speed = 0;
                player.canJump = false;

                camera.target = player.position;
                camera.offset = (RL_Vector2){ screenWidth/2.0f, screenHeight/2.0f };
                camera.rotation = 0.0f;
                camera.zoom = 1.0f;
            }
        }

        if (eventRecording || eventPlaying) frameCounter++;
        else frameCounter = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_LIGHTGRAY);

            RL_BeginMode2D(camera);

                // Draw environment elements
                for (int i = 0; i < MAX_ENVIRONMENT_ELEMENTS; i++)
                {
                    RL_DrawRectangleRec(envElements[i].rect, envElements[i].color);
                }

                // Draw player rectangle
                RL_DrawRectangleRec((RL_Rectangle){ player.position.x - 20, player.position.y - 40, 40, 40 }, RL_RED);

            RL_EndMode2D();
            
            // Draw game controls
            RL_DrawRectangle(10, 10, 290, 145, RL_Fade(RL_SKYBLUE, 0.5f));
            RL_DrawRectangleLines(10, 10, 290, 145, RL_Fade(RL_BLUE, 0.8f));

            RL_DrawText("Controls:", 20, 20, 10, RL_BLACK);
            RL_DrawText("- RIGHT | LEFT: Player movement", 30, 40, 10, RL_DARKGRAY);
            RL_DrawText("- SPACE: Player jump", 30, 60, 10, RL_DARKGRAY);
            RL_DrawText("- R: Reset game state", 30, 80, 10, RL_DARKGRAY);

            RL_DrawText("- S: START/STOP RECORDING INPUT EVENTS", 30, 110, 10, RL_BLACK);
            RL_DrawText("- A: REPLAY LAST RECORDED INPUT EVENTS", 30, 130, 10, RL_BLACK);

            // Draw automation events recording indicator
            if (eventRecording)
            {
                RL_DrawRectangle(10, 160, 290, 30, RL_Fade(RL_RED, 0.3f));
                RL_DrawRectangleLines(10, 160, 290, 30, RL_Fade(RL_MAROON, 0.8f));
                RL_DrawCircle(30, 175, 10, RL_MAROON);

                if (((frameCounter/15)%2) == 1) RL_DrawText(RL_TextFormat("RECORDING EVENTS... [%i]", aelist.count), 50, 170, 10, RL_MAROON);
            }
            else if (eventPlaying)
            {
                RL_DrawRectangle(10, 160, 290, 30, RL_Fade(RL_LIME, 0.3f));
                RL_DrawRectangleLines(10, 160, 290, 30, RL_Fade(RL_DARKGREEN, 0.8f));
                RL_DrawTriangle((RL_Vector2){ 20, 155 + 10 }, (RL_Vector2){ 20, 155 + 30 }, (RL_Vector2){ 40, 155 + 20 }, RL_DARKGREEN);

                if (((frameCounter/15)%2) == 1) RL_DrawText(RL_TextFormat("PLAYING RECORDED EVENTS... [%i]", currentPlayFrame), 50, 170, 10, RL_DARKGREEN);
            }
            

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
