/*******************************************************************************************
*
*   raylib [shaders] example - Basic PBR
*
*   Example originally created with raylib 5.0, last time updated with raylib 5.1-dev
*
*   Example contributed by Afan OLOVCIC (@_DevDad) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2023-2024 Afan OLOVCIC (@_DevDad)
*
*   RL_Model: "Old Rusty Car" (https://skfb.ly/LxRy) by Renafox, 
*   licensed under Creative Commons Attribution-NonCommercial 
*   (http://creativecommons.org/licenses/by-nc/4.0/)
*
********************************************************************************************/

#include "raylib.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            120
#endif

#include <stdlib.h>             // Required for: NULL

#define MAX_LIGHTS  4           // Max dynamic lights supported by shader

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

// Light type
typedef enum {
    LIGHT_DIRECTIONAL = 0,
    LIGHT_POINT,
    LIGHT_SPOT
} LightType;

// Light data
typedef struct {
    int type;
    int enabled;
    RL_Vector3 position;
    RL_Vector3 target;
    float color[4];
    float intensity;

    // RL_Shader light parameters locations
    int typeLoc;
    int enabledLoc;
    int positionLoc;
    int targetLoc;
    int colorLoc;
    int intensityLoc;
} Light;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
static int lightCount = 0;     // Current number of dynamic lights that have been created

//----------------------------------------------------------------------------------
// Module specific Functions Declaration
//----------------------------------------------------------------------------------
// Create a light and get shader locations
static Light CreateLight(int type, RL_Vector3 position, RL_Vector3 target, RL_Color color, float intensity, RL_Shader shader);

// Update light properties on shader
// NOTE: Light shader locations should be available
static void UpdateLight(RL_Shader shader, Light light);

//----------------------------------------------------------------------------------
// Main Entry Point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    RL_SetConfigFlags(FLAG_MSAA_4X_HINT);
    RL_InitWindow(screenWidth, screenHeight, "raylib [shaders] example - basic pbr");

    // Define the camera to look into our 3d world
    RL_Camera camera = { 0 };
    camera.position = (RL_Vector3){ 2.0f, 2.0f, 6.0f };    // RL_Camera position
    camera.target = (RL_Vector3){ 0.0f, 0.5f, 0.0f };      // RL_Camera looking at point
    camera.up = (RL_Vector3){ 0.0f, 1.0f, 0.0f };          // RL_Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // RL_Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // RL_Camera projection type

    // Load PBR shader and setup all required locations
    RL_Shader shader = RL_LoadShader(RL_TextFormat("resources/shaders/glsl%i/pbr.vs", GLSL_VERSION),
                               RL_TextFormat("resources/shaders/glsl%i/pbr.fs", GLSL_VERSION));
    shader.locs[SHADER_LOC_MAP_ALBEDO] = RL_GetShaderLocation(shader, "albedoMap");
    // WARNING: Metalness, roughness, and ambient occlusion are all packed into a MRA texture
    // They are passed as to the SHADER_LOC_MAP_METALNESS location for convenience,
    // shader already takes care of it accordingly
    shader.locs[SHADER_LOC_MAP_METALNESS] = RL_GetShaderLocation(shader, "mraMap");
    shader.locs[SHADER_LOC_MAP_NORMAL] = RL_GetShaderLocation(shader, "normalMap");
    // WARNING: Similar to the MRA map, the emissive map packs different information 
    // into a single texture: it stores height and emission data
    // It is binded to SHADER_LOC_MAP_EMISSION location an properly processed on shader
    shader.locs[SHADER_LOC_MAP_EMISSION] = RL_GetShaderLocation(shader, "emissiveMap");
    shader.locs[SHADER_LOC_COLOR_DIFFUSE] = RL_GetShaderLocation(shader, "albedoColor");

    // Setup additional required shader locations, including lights data
    shader.locs[SHADER_LOC_VECTOR_VIEW] = RL_GetShaderLocation(shader, "viewPos");
    int lightCountLoc = RL_GetShaderLocation(shader, "numOfLights");
    int maxLightCount = MAX_LIGHTS;
    RL_SetShaderValue(shader, lightCountLoc, &maxLightCount, SHADER_UNIFORM_INT);

    // Setup ambient color and intensity parameters
    float ambientIntensity = 0.02f;
    RL_Color ambientColor = (RL_Color){ 26, 32, 135, 255 };
    RL_Vector3 ambientColorNormalized = (RL_Vector3){ ambientColor.r/255.0f, ambientColor.g/255.0f, ambientColor.b/255.0f };
    RL_SetShaderValue(shader, RL_GetShaderLocation(shader, "ambientColor"), &ambientColorNormalized, SHADER_UNIFORM_VEC3);
    RL_SetShaderValue(shader, RL_GetShaderLocation(shader, "ambient"), &ambientIntensity, SHADER_UNIFORM_FLOAT);

    // Get location for shader parameters that can be modified in real time
    int emissiveIntensityLoc = RL_GetShaderLocation(shader, "emissivePower");
    int emissiveColorLoc = RL_GetShaderLocation(shader, "emissiveColor");
    int textureTilingLoc = RL_GetShaderLocation(shader, "tiling");

    // Load old car model using PBR maps and shader
    // WARNING: We know this model consists of a single model.meshes[0] and
    // that model.materials[0] is by default assigned to that mesh
    // There could be more complex models consisting of multiple meshes and
    // multiple materials defined for those meshes... but always 1 mesh = 1 material
    RL_Model car = RL_LoadModel("resources/models/old_car_new.glb");

    // Assign already setup PBR shader to model.materials[0], used by models.meshes[0]
    car.materials[0].shader = shader;

    // Setup materials[0].maps default parameters
    car.materials[0].maps[MATERIAL_MAP_ALBEDO].color = RL_WHITE;
    car.materials[0].maps[MATERIAL_MAP_METALNESS].value = 0.0f;
    car.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0.0f;
    car.materials[0].maps[MATERIAL_MAP_OCCLUSION].value = 1.0f;
    car.materials[0].maps[MATERIAL_MAP_EMISSION].color = (RL_Color){ 255, 162, 0, 255 };

    // Setup materials[0].maps default textures
    car.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = RL_LoadTexture("resources/old_car_d.png");
    car.materials[0].maps[MATERIAL_MAP_METALNESS].texture = RL_LoadTexture("resources/old_car_mra.png");
    car.materials[0].maps[MATERIAL_MAP_NORMAL].texture = RL_LoadTexture("resources/old_car_n.png");
    car.materials[0].maps[MATERIAL_MAP_EMISSION].texture = RL_LoadTexture("resources/old_car_e.png");
    
    // Load floor model mesh and assign material parameters
    // NOTE: A basic plane shape can be generated instead of being loaded from a model file
    RL_Model floor = RL_LoadModel("resources/models/plane.glb");
    //RL_Mesh floorMesh = RL_GenMeshPlane(10, 10, 10, 10);
    //RL_GenMeshTangents(&floorMesh);      // TODO: Review tangents generation
    //RL_Model floor = RL_LoadModelFromMesh(floorMesh);

    // Assign material shader for our floor model, same PBR shader 
    floor.materials[0].shader = shader;
    
    floor.materials[0].maps[MATERIAL_MAP_ALBEDO].color = RL_WHITE;
    floor.materials[0].maps[MATERIAL_MAP_METALNESS].value = 0.0f;
    floor.materials[0].maps[MATERIAL_MAP_ROUGHNESS].value = 0.0f;
    floor.materials[0].maps[MATERIAL_MAP_OCCLUSION].value = 1.0f;
    floor.materials[0].maps[MATERIAL_MAP_EMISSION].color = RL_BLACK;

    floor.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = RL_LoadTexture("resources/road_a.png");
    floor.materials[0].maps[MATERIAL_MAP_METALNESS].texture = RL_LoadTexture("resources/road_mra.png");
    floor.materials[0].maps[MATERIAL_MAP_NORMAL].texture = RL_LoadTexture("resources/road_n.png");

    // Models texture tiling parameter can be stored in the RL_Material struct if required (CURRENTLY NOT USED)
    // NOTE: RL_Material.params[4] are available for generic parameters storage (float)
    RL_Vector2 carTextureTiling = (RL_Vector2){ 0.5f, 0.5f };
    RL_Vector2 floorTextureTiling = (RL_Vector2){ 0.5f, 0.5f };

    // Create some lights
    Light lights[MAX_LIGHTS] = { 0 };
    lights[0] = CreateLight(LIGHT_POINT, (RL_Vector3){ -1.0f, 1.0f, -2.0f }, (RL_Vector3){ 0.0f, 0.0f, 0.0f }, RL_YELLOW, 4.0f, shader);
    lights[1] = CreateLight(LIGHT_POINT, (RL_Vector3){ 2.0f, 1.0f, 1.0f }, (RL_Vector3){ 0.0f, 0.0f, 0.0f }, RL_GREEN, 3.3f, shader);
    lights[2] = CreateLight(LIGHT_POINT, (RL_Vector3){ -2.0f, 1.0f, 1.0f }, (RL_Vector3){ 0.0f, 0.0f, 0.0f }, RL_RED, 8.3f, shader);
    lights[3] = CreateLight(LIGHT_POINT, (RL_Vector3){ 1.0f, 1.0f, -2.0f }, (RL_Vector3){ 0.0f, 0.0f, 0.0f }, RL_BLUE, 2.0f, shader);

    // Setup material texture maps usage in shader
    // NOTE: By default, the texture maps are always used
    int usage = 1;
    RL_SetShaderValue(shader, RL_GetShaderLocation(shader, "useTexAlbedo"), &usage, SHADER_UNIFORM_INT);
    RL_SetShaderValue(shader, RL_GetShaderLocation(shader, "useTexNormal"), &usage, SHADER_UNIFORM_INT);
    RL_SetShaderValue(shader, RL_GetShaderLocation(shader, "useTexMRA"), &usage, SHADER_UNIFORM_INT);
    RL_SetShaderValue(shader, RL_GetShaderLocation(shader, "useTexEmissive"), &usage, SHADER_UNIFORM_INT);
    
    RL_SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!RL_WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        RL_UpdateCamera(&camera, CAMERA_ORBITAL);

        // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
        float cameraPos[3] = {camera.position.x, camera.position.y, camera.position.z};
        RL_SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

        // Check key inputs to enable/disable lights
        if (RL_IsKeyPressed(KEY_ONE)) { lights[2].enabled = !lights[2].enabled; }
        if (RL_IsKeyPressed(KEY_TWO)) { lights[1].enabled = !lights[1].enabled; }
        if (RL_IsKeyPressed(KEY_THREE)) { lights[3].enabled = !lights[3].enabled; }
        if (RL_IsKeyPressed(KEY_FOUR)) { lights[0].enabled = !lights[0].enabled; }

        // Update light values on shader (actually, only enable/disable them)
        for (int i = 0; i < MAX_LIGHTS; i++) UpdateLight(shader, lights[i]);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        RL_BeginDrawing();
        
            RL_ClearBackground(RL_BLACK);
            
            RL_BeginMode3D(camera);
                
                // Set floor model texture tiling and emissive color parameters on shader
                RL_SetShaderValue(shader, textureTilingLoc, &floorTextureTiling, SHADER_UNIFORM_VEC2);
                RL_Vector4 floorEmissiveColor = RL_ColorNormalize(floor.materials[0].maps[MATERIAL_MAP_EMISSION].color);
                RL_SetShaderValue(shader, emissiveColorLoc, &floorEmissiveColor, SHADER_UNIFORM_VEC4);
                
                RL_DrawModel(floor, (RL_Vector3){ 0.0f, 0.0f, 0.0f }, 5.0f, RL_WHITE);   // Draw floor model

                // Set old car model texture tiling, emissive color and emissive intensity parameters on shader
                RL_SetShaderValue(shader, textureTilingLoc, &carTextureTiling, SHADER_UNIFORM_VEC2);
                RL_Vector4 carEmissiveColor = RL_ColorNormalize(car.materials[0].maps[MATERIAL_MAP_EMISSION].color);
                RL_SetShaderValue(shader, emissiveColorLoc, &carEmissiveColor, SHADER_UNIFORM_VEC4);
                float emissiveIntensity = 0.01f;
                RL_SetShaderValue(shader, emissiveIntensityLoc, &emissiveIntensity, SHADER_UNIFORM_FLOAT);
                
                RL_DrawModel(car, (RL_Vector3){ 0.0f, 0.0f, 0.0f }, 0.25f, RL_WHITE);   // Draw car model

                // Draw spheres to show the lights positions
                for (int i = 0; i < MAX_LIGHTS; i++)
                {
                    RL_Color lightColor = (RL_Color){ lights[i].color[0]*255, lights[i].color[1]*255, lights[i].color[2]*255, lights[i].color[3]*255 };
                    
                    if (lights[i].enabled) RL_DrawSphereEx(lights[i].position, 0.2f, 8, 8, lightColor);
                    else RL_DrawSphereWires(lights[i].position, 0.2f, 8, 8, RL_ColorAlpha(lightColor, 0.3f));
                }
                
            RL_EndMode3D();
            
            RL_DrawText("Toggle lights: [1][2][3][4]", 10, 40, 20, RL_LIGHTGRAY);

            RL_DrawText("(c) Old Rusty Car model by Renafox (https://skfb.ly/LxRy)", screenWidth - 320, screenHeight - 20, 10, RL_LIGHTGRAY);
            
            RL_DrawFPS(10, 10);

        RL_EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    // Unbind (disconnect) shader from car.material[0] 
    // to avoid RL_UnloadMaterial() trying to unload it automatically
    car.materials[0].shader = (RL_Shader){ 0 };
    RL_UnloadMaterial(car.materials[0]);
    car.materials[0].maps = NULL;
    RL_UnloadModel(car);
    
    floor.materials[0].shader = (RL_Shader){ 0 };
    RL_UnloadMaterial(floor.materials[0]);
    floor.materials[0].maps = NULL;
    RL_UnloadModel(floor);
    
    RL_UnloadShader(shader);       // Unload RL_Shader
    
    RL_CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Create light with provided data
// NOTE: It updated the global lightCount and it's limited to MAX_LIGHTS
static Light CreateLight(int type, RL_Vector3 position, RL_Vector3 target, RL_Color color, float intensity, RL_Shader shader)
{
    Light light = { 0 };

    if (lightCount < MAX_LIGHTS)
    {
        light.enabled = 1;
        light.type = type;
        light.position = position;
        light.target = target;
        light.color[0] = (float)color.r/255.0f;
        light.color[1] = (float)color.g/255.0f;
        light.color[2] = (float)color.b/255.0f;
        light.color[3] = (float)color.a/255.0f;
        light.intensity = intensity;
        
        // NOTE: RL_Shader parameters names for lights must match the requested ones
        light.enabledLoc = RL_GetShaderLocation(shader, RL_TextFormat("lights[%i].enabled", lightCount));
        light.typeLoc = RL_GetShaderLocation(shader, RL_TextFormat("lights[%i].type", lightCount));
        light.positionLoc = RL_GetShaderLocation(shader, RL_TextFormat("lights[%i].position", lightCount));
        light.targetLoc = RL_GetShaderLocation(shader, RL_TextFormat("lights[%i].target", lightCount));
        light.colorLoc = RL_GetShaderLocation(shader, RL_TextFormat("lights[%i].color", lightCount));
        light.intensityLoc = RL_GetShaderLocation(shader, RL_TextFormat("lights[%i].intensity", lightCount));
        
        UpdateLight(shader, light);

        lightCount++;
    }

    return light;
}

// Send light properties to shader
// NOTE: Light shader locations should be available
static void UpdateLight(RL_Shader shader, Light light)
{
    RL_SetShaderValue(shader, light.enabledLoc, &light.enabled, SHADER_UNIFORM_INT);
    RL_SetShaderValue(shader, light.typeLoc, &light.type, SHADER_UNIFORM_INT);
    
    // Send to shader light position values
    float position[3] = { light.position.x, light.position.y, light.position.z };
    RL_SetShaderValue(shader, light.positionLoc, position, SHADER_UNIFORM_VEC3);

    // Send to shader light target position values
    float target[3] = { light.target.x, light.target.y, light.target.z };
    RL_SetShaderValue(shader, light.targetLoc, target, SHADER_UNIFORM_VEC3);
    RL_SetShaderValue(shader, light.colorLoc, light.color, SHADER_UNIFORM_VEC4);
    RL_SetShaderValue(shader, light.intensityLoc, &light.intensity, SHADER_UNIFORM_FLOAT);
}
