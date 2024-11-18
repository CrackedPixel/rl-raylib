/*******************************************************************************************
*
*   raylib [core] example - 2D RL_Camera platformer
*
*   Example originally created with raylib 2.5, last time updated with raylib 3.0
*
*   Example contributed by arvyy (@arvyy) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2019-2024 arvyy (@arvyy)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

#define G 400
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f

typedef struct Player {
    RL_Vector2 position;
    float speed;
    bool canJump;
} Player;

typedef struct EnvItem {
    RL_Rectangle rect;
    int blocking;
    RL_Color color;
} EnvItem;

//----------------------------------------------------------------------------------
// Module functions declaration
//----------------------------------------------------------------------------------
void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta);
void UpdateCameraCenter(RL_Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraCenterInsideMap(RL_Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraCenterSmoothFollow(RL_Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraEvenOutOnLanding(RL_Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);
void UpdateCameraPlayerBoundsPush(RL_Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");

    Player player = { 0 };
    player.position = (RL_Vector2){ 400, 280 };
    player.speed = 0;
    player.canJump = false;
    EnvItem envItems[] = {
        {{ 0, 0, 1000, 400 }, 0, RL_LIGHTGRAY },
        {{ 0, 400, 1000, 200 }, 1, RL_GRAY },
        {{ 300, 200, 400, 10 }, 1, RL_GRAY },
        {{ 250, 300, 100, 10 }, 1, RL_GRAY },
        {{ 650, 300, 100, 10 }, 1, RL_GRAY }
    };

    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

    RL_Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = (RL_Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Store pointers to the multiple update camera functions
    void (*cameraUpdaters[])(RL_Camera2D*, Player*, EnvItem*, int, float, int, int) = {
        UpdateCameraCenter,
        UpdateCameraCenterInsideMap,
        UpdateCameraCenterSmoothFollow,
        UpdateCameraEvenOutOnLanding,
        UpdateCameraPlayerBoundsPush
    };

    int cameraOption = 0;
    int cameraUpdatersLength = sizeof(cameraUpdaters)/sizeof(cameraUpdaters[0]);

    char *cameraDescriptions[] = {
        "Follow player center",
        "Follow player center, but clamp to map edges",
        "Follow player center; smoothed",
        "Follow player center horizontally; update player center vertically after landing",
        "Player push camera on getting too close to screen edge"
    };

    RL_SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        float deltaTime = RL_GetFrameTime();

        UpdatePlayer(&player, envItems, envItemsLength, deltaTime);

        camera.zoom += ((float)RL_GetMouseWheelMove()*0.05f);

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.25f) camera.zoom = 0.25f;

        if (RL_IsKeyPressed(KEY_R))
        {
            camera.zoom = 1.0f;
            player.position = (RL_Vector2){ 400, 280 };
        }

        if (RL_IsKeyPressed(KEY_C)) cameraOption = (cameraOption + 1)%cameraUpdatersLength;

        // Call update camera function by its pointer
        cameraUpdaters[cameraOption](&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();

            RL_ClearBackground(RL_LIGHTGRAY);

            RL_BeginMode2D(camera);

                for (int i = 0; i < envItemsLength; i++) RL_DrawRectangleRec(envItems[i].rect, envItems[i].color);

                RL_Rectangle playerRect = { player.position.x - 20, player.position.y - 40, 40.0f, 40.0f };
                RL_DrawRectangleRec(playerRect, RL_RED);
                
                RL_DrawCircleV(player.position, 5.0f, RL_GOLD);

            RL_EndMode2D();

            RL_DrawText("Controls:", 20, 20, 10, RL_BLACK);
            RL_DrawText("- Right/Left to move", 40, 40, 10, RL_DARKGRAY);
            RL_DrawText("- Space to jump", 40, 60, 10, RL_DARKGRAY);
            RL_DrawText("- Mouse Wheel to Zoom in-out, R to reset zoom", 40, 80, 10, RL_DARKGRAY);
            RL_DrawText("- C to change camera mode", 40, 100, 10, RL_DARKGRAY);
            RL_DrawText("Current camera mode:", 20, 120, 10, RL_BLACK);
            RL_DrawText(cameraDescriptions[cameraOption], 40, 140, 10, RL_DARKGRAY);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    RL_CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta)
{
    if (RL_IsKeyDown(KEY_LEFT)) player->position.x -= PLAYER_HOR_SPD*delta;
    if (RL_IsKeyDown(KEY_RIGHT)) player->position.x += PLAYER_HOR_SPD*delta;
    if (RL_IsKeyDown(KEY_SPACE) && player->canJump)
    {
        player->speed = -PLAYER_JUMP_SPD;
        player->canJump = false;
    }

    bool hitObstacle = false;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        RL_Vector2 *p = &(player->position);
        if (ei->blocking &&
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y <= p->y + player->speed*delta)
        {
            hitObstacle = true;
            player->speed = 0.0f;
            p->y = ei->rect.y;
            break;
        }
    }

    if (!hitObstacle)
    {
        player->position.y += player->speed*delta;
        player->speed += G*delta;
        player->canJump = false;
    }
    else player->canJump = true;
}

void UpdateCameraCenter(RL_Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
    camera->offset = (RL_Vector2){ width/2.0f, height/2.0f };
    camera->target = player->position;
}

void UpdateCameraCenterInsideMap(RL_Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
    camera->target = player->position;
    camera->offset = (RL_Vector2){ width/2.0f, height/2.0f };
    float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        minX = fminf(ei->rect.x, minX);
        maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
        minY = fminf(ei->rect.y, minY);
        maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
    }

    RL_Vector2 max = RL_GetWorldToScreen2D((RL_Vector2){ maxX, maxY }, *camera);
    RL_Vector2 min = RL_GetWorldToScreen2D((RL_Vector2){ minX, minY }, *camera);

    if (max.x < width) camera->offset.x = width - (max.x - width/2);
    if (max.y < height) camera->offset.y = height - (max.y - height/2);
    if (min.x > 0) camera->offset.x = width/2 - min.x;
    if (min.y > 0) camera->offset.y = height/2 - min.y;
}

void UpdateCameraCenterSmoothFollow(RL_Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
    static float minSpeed = 30;
    static float minEffectLength = 10;
    static float fractionSpeed = 0.8f;

    camera->offset = (RL_Vector2){ width/2.0f, height/2.0f };
    RL_Vector2 diff = Vector2Subtract(player->position, camera->target);
    float length = Vector2Length(diff);

    if (length > minEffectLength)
    {
        float speed = fmaxf(fractionSpeed*length, minSpeed);
        camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed*delta/length));
    }
}

void UpdateCameraEvenOutOnLanding(RL_Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
    static float evenOutSpeed = 700;
    static int eveningOut = false;
    static float evenOutTarget;

    camera->offset = (RL_Vector2){ width/2.0f, height/2.0f };
    camera->target.x = player->position.x;

    if (eveningOut)
    {
        if (evenOutTarget > camera->target.y)
        {
            camera->target.y += evenOutSpeed*delta;

            if (camera->target.y > evenOutTarget)
            {
                camera->target.y = evenOutTarget;
                eveningOut = 0;
            }
        }
        else
        {
            camera->target.y -= evenOutSpeed*delta;

            if (camera->target.y < evenOutTarget)
            {
                camera->target.y = evenOutTarget;
                eveningOut = 0;
            }
        }
    }
    else
    {
        if (player->canJump && (player->speed == 0) && (player->position.y != camera->target.y))
        {
            eveningOut = 1;
            evenOutTarget = player->position.y;
        }
    }
}

void UpdateCameraPlayerBoundsPush(RL_Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
    static RL_Vector2 bbox = { 0.2f, 0.2f };

    RL_Vector2 bboxWorldMin = RL_GetScreenToWorld2D((RL_Vector2){ (1 - bbox.x)*0.5f*width, (1 - bbox.y)*0.5f*height }, *camera);
    RL_Vector2 bboxWorldMax = RL_GetScreenToWorld2D((RL_Vector2){ (1 + bbox.x)*0.5f*width, (1 + bbox.y)*0.5f*height }, *camera);
    camera->offset = (RL_Vector2){ (1 - bbox.x)*0.5f * width, (1 - bbox.y)*0.5f*height };

    if (player->position.x < bboxWorldMin.x) camera->target.x = player->position.x;
    if (player->position.y < bboxWorldMin.y) camera->target.y = player->position.y;
    if (player->position.x > bboxWorldMax.x) camera->target.x = bboxWorldMin.x + (player->position.x - bboxWorldMax.x);
    if (player->position.y > bboxWorldMax.y) camera->target.y = bboxWorldMin.y + (player->position.y - bboxWorldMax.y);
}
