/*******************************************************************************************
*
*   rcamera - Basic camera system with support for multiple camera modes
*
*   CONFIGURATION:
*       #define RCAMERA_IMPLEMENTATION
*           Generates the implementation of the library into the included file.
*           If not defined, the library is in header only mode and can be included in other headers
*           or source files without problems. But only ONE file should hold the implementation.
*
*       #define RCAMERA_STANDALONE
*           If defined, the library can be used as standalone as a camera system but some
*           functions must be redefined to manage inputs accordingly.
*
*   CONTRIBUTORS:
*       Ramon Santamaria:   Supervision, review, update and maintenance
*       Christoph Wagner:   Complete redesign, using raymath (2022)
*       Marc Palau:         Initial implementation (2014)
*
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2022-2024 Christoph Wagner (@Crydsch) & Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#ifndef RCAMERA_H
#define RCAMERA_H

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
// Function specifiers definition

// Function specifiers in case library is build/used as a shared library (Windows)
// NOTE: Microsoft specifiers to tell compiler that symbols are imported/exported from a .dll
#if defined(_WIN32)
#if defined(BUILD_LIBTYPE_SHARED)
#if defined(__TINYC__)
#define __declspec(x) __attribute__((x))
#endif
#define RLAPI __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
#elif defined(USE_LIBTYPE_SHARED)
#define RLAPI __declspec(dllimport)     // We are using the library as a Win32 shared library (.dll)
#endif
#endif

#ifndef RLAPI
    #define RLAPI       // Functions defined as 'extern' by default (implicit specifiers)
#endif

#if defined(RCAMERA_STANDALONE)
    #define CAMERA_CULL_DISTANCE_NEAR      0.01
    #define CAMERA_CULL_DISTANCE_FAR    1000.0
#else
    #define CAMERA_CULL_DISTANCE_NEAR   RL_CULL_DISTANCE_NEAR
    #define CAMERA_CULL_DISTANCE_FAR    RL_CULL_DISTANCE_FAR
#endif

//----------------------------------------------------------------------------------
// Types and Structures Definition
// NOTE: Below types are required for standalone usage
//----------------------------------------------------------------------------------
#if defined(RCAMERA_STANDALONE)
    // raylib_vector2, 2 components
    typedef struct raylib_vector2 {
        float x;                // Vector x component
        float y;                // Vector y component
    } raylib_vector2;

    // raylib_vector3, 3 components
    typedef struct raylib_vector3 {
        float x;                // Vector x component
        float y;                // Vector y component
        float z;                // Vector z component
    } raylib_vector3;

    // raylib_matrix, 4x4 components, column major, OpenGL style, right-handed
    typedef struct raylib_matrix {
        float m0, m4, m8, m12;  // raylib_matrix first row (4 components)
        float m1, m5, m9, m13;  // raylib_matrix second row (4 components)
        float m2, m6, m10, m14; // raylib_matrix third row (4 components)
        float m3, m7, m11, m15; // raylib_matrix fourth row (4 components)
    } raylib_matrix;

    // raylib_camera type, defines a camera position/orientation in 3d space
    typedef struct raylib_camera3d {
        raylib_vector3 position;       // raylib_camera position
        raylib_vector3 target;         // raylib_camera target it looks-at
        raylib_vector3 up;             // raylib_camera up vector (rotation over its axis)
        float fovy;             // raylib_camera field-of-view apperture in Y (degrees) in perspective, used as near plane width in orthographic
        int projection;         // raylib_camera projection type: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
    } raylib_camera3d;

    typedef raylib_camera3d raylib_camera;    // raylib_camera type fallback, defaults to raylib_camera3d

    // raylib_camera projection
    typedef enum {
        CAMERA_PERSPECTIVE = 0, // Perspective projection
        CAMERA_ORTHOGRAPHIC     // Orthographic projection
    } raylib_cameraprojection;

    // raylib_camera system modes
    typedef enum {
        CAMERA_CUSTOM = 0,      // raylib_camera custom, controlled by user (raylib_updatecamera() does nothing)
        CAMERA_FREE,            // raylib_camera free mode
        CAMERA_ORBITAL,         // raylib_camera orbital, around target, zoom supported
        CAMERA_FIRST_PERSON,    // raylib_camera first person
        CAMERA_THIRD_PERSON     // raylib_camera third person
    } raylib_cameramode;
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C" {            // Prevents name mangling of functions
#endif

RLAPI raylib_vector3 GetCameraForward(raylib_camera *camera);
RLAPI raylib_vector3 GetCameraUp(raylib_camera *camera);
RLAPI raylib_vector3 GetCameraRight(raylib_camera *camera);

// raylib_camera movement
RLAPI void CameraMoveForward(raylib_camera *camera, float distance, bool moveInWorldPlane);
RLAPI void CameraMoveUp(raylib_camera *camera, float distance);
RLAPI void CameraMoveRight(raylib_camera *camera, float distance, bool moveInWorldPlane);
RLAPI void CameraMoveToTarget(raylib_camera *camera, float delta);

// raylib_camera rotation
RLAPI void CameraYaw(raylib_camera *camera, float angle, bool rotateAroundTarget);
RLAPI void CameraPitch(raylib_camera *camera, float angle, bool lockView, bool rotateAroundTarget, bool rotateUp);
RLAPI void CameraRoll(raylib_camera *camera, float angle);

RLAPI raylib_matrix GetCameraViewMatrix(raylib_camera *camera);
RLAPI raylib_matrix GetCameraProjectionMatrix(raylib_camera* camera, float aspect);

#if defined(__cplusplus)
}
#endif

#endif // RCAMERA_H


/***********************************************************************************
*
*   CAMERA IMPLEMENTATION
*
************************************************************************************/

#if defined(RCAMERA_IMPLEMENTATION)

#include "raymath.h"        // Required for vector maths:
                            // Vector3Add()
                            // Vector3Subtract()
                            // Vector3Scale()
                            // Vector3Normalize()
                            // Vector3Distance()
                            // Vector3CrossProduct()
                            // Vector3RotateByAxisAngle()
                            // Vector3Angle()
                            // Vector3Negate()
                            // MatrixLookAt()
                            // MatrixPerspective()
                            // MatrixOrtho()
                            // MatrixIdentity()

// raylib required functionality:
                            // raylib_getmousedelta()
                            // raylib_getmousewheelmove()
                            // raylib_iskeydown()
                            // raylib_iskeypressed()
                            // raylib_getframetime()

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
#define CAMERA_MOVE_SPEED                               0.09f
#define CAMERA_ROTATION_SPEED                           0.03f
#define CAMERA_PAN_SPEED                                0.2f

// raylib_camera mouse movement sensitivity
#define CAMERA_MOUSE_MOVE_SENSITIVITY                   0.003f     // TODO: it should be independant of framerate

// raylib_camera orbital speed in CAMERA_ORBITAL mode
#define CAMERA_ORBITAL_SPEED                            0.5f       // Radians per second

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module specific Functions Declaration
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
// Returns the cameras forward vector (normalized)
raylib_vector3 GetCameraForward(raylib_camera *camera)
{
    return Vector3Normalize(Vector3Subtract(camera->target, camera->position));
}

// Returns the cameras up vector (normalized)
// Note: The up vector might not be perpendicular to the forward vector
raylib_vector3 GetCameraUp(raylib_camera *camera)
{
    return Vector3Normalize(camera->up);
}

// Returns the cameras right vector (normalized)
raylib_vector3 GetCameraRight(raylib_camera *camera)
{
    raylib_vector3 forward = GetCameraForward(camera);
    raylib_vector3 up = GetCameraUp(camera);

    return Vector3Normalize(Vector3CrossProduct(forward, up));
}

// Moves the camera in its forward direction
void CameraMoveForward(raylib_camera *camera, float distance, bool moveInWorldPlane)
{
    raylib_vector3 forward = GetCameraForward(camera);

    if (moveInWorldPlane)
    {
        // Project vector onto world plane
        forward.y = 0;
        forward = Vector3Normalize(forward);
    }

    // Scale by distance
    forward = Vector3Scale(forward, distance);

    // Move position and target
    camera->position = Vector3Add(camera->position, forward);
    camera->target = Vector3Add(camera->target, forward);
}

// Moves the camera in its up direction
void CameraMoveUp(raylib_camera *camera, float distance)
{
    raylib_vector3 up = GetCameraUp(camera);

    // Scale by distance
    up = Vector3Scale(up, distance);

    // Move position and target
    camera->position = Vector3Add(camera->position, up);
    camera->target = Vector3Add(camera->target, up);
}

// Moves the camera target in its current right direction
void CameraMoveRight(raylib_camera *camera, float distance, bool moveInWorldPlane)
{
    raylib_vector3 right = GetCameraRight(camera);

    if (moveInWorldPlane)
    {
        // Project vector onto world plane
        right.y = 0;
        right = Vector3Normalize(right);
    }

    // Scale by distance
    right = Vector3Scale(right, distance);

    // Move position and target
    camera->position = Vector3Add(camera->position, right);
    camera->target = Vector3Add(camera->target, right);
}

// Moves the camera position closer/farther to/from the camera target
void CameraMoveToTarget(raylib_camera *camera, float delta)
{
    float distance = Vector3Distance(camera->position, camera->target);

    // Apply delta
    distance += delta;

    // Distance must be greater than 0
    if (distance <= 0) distance = 0.001f;

    // Set new distance by moving the position along the forward vector
    raylib_vector3 forward = GetCameraForward(camera);
    camera->position = Vector3Add(camera->target, Vector3Scale(forward, -distance));
}

// Rotates the camera around its up vector
// Yaw is "looking left and right"
// If rotateAroundTarget is false, the camera rotates around its position
// Note: angle must be provided in radians
void CameraYaw(raylib_camera *camera, float angle, bool rotateAroundTarget)
{
    // Rotation axis
    raylib_vector3 up = GetCameraUp(camera);

    // View vector
    raylib_vector3 targetPosition = Vector3Subtract(camera->target, camera->position);

    // Rotate view vector around up axis
    targetPosition = Vector3RotateByAxisAngle(targetPosition, up, angle);

    if (rotateAroundTarget)
    {
        // Move position relative to target
        camera->position = Vector3Subtract(camera->target, targetPosition);
    }
    else // rotate around camera.position
    {
        // Move target relative to position
        camera->target = Vector3Add(camera->position, targetPosition);
    }
}

// Rotates the camera around its right vector, pitch is "looking up and down"
//  - lockView prevents camera overrotation (aka "somersaults")
//  - rotateAroundTarget defines if rotation is around target or around its position
//  - rotateUp rotates the up direction as well (typically only usefull in CAMERA_FREE)
// NOTE: angle must be provided in radians
void CameraPitch(raylib_camera *camera, float angle, bool lockView, bool rotateAroundTarget, bool rotateUp)
{
    // Up direction
    raylib_vector3 up = GetCameraUp(camera);

    // View vector
    raylib_vector3 targetPosition = Vector3Subtract(camera->target, camera->position);

    if (lockView)
    {
        // In these camera modes we clamp the Pitch angle
        // to allow only viewing straight up or down.

        // Clamp view up
        float maxAngleUp = Vector3Angle(up, targetPosition);
        maxAngleUp -= 0.001f; // avoid numerical errors
        if (angle > maxAngleUp) angle = maxAngleUp;

        // Clamp view down
        float maxAngleDown = Vector3Angle(Vector3Negate(up), targetPosition);
        maxAngleDown *= -1.0f; // downwards angle is negative
        maxAngleDown += 0.001f; // avoid numerical errors
        if (angle < maxAngleDown) angle = maxAngleDown;
    }

    // Rotation axis
    raylib_vector3 right = GetCameraRight(camera);

    // Rotate view vector around right axis
    targetPosition = Vector3RotateByAxisAngle(targetPosition, right, angle);

    if (rotateAroundTarget)
    {
        // Move position relative to target
        camera->position = Vector3Subtract(camera->target, targetPosition);
    }
    else // rotate around camera.position
    {
        // Move target relative to position
        camera->target = Vector3Add(camera->position, targetPosition);
    }

    if (rotateUp)
    {
        // Rotate up direction around right axis
        camera->up = Vector3RotateByAxisAngle(camera->up, right, angle);
    }
}

// Rotates the camera around its forward vector
// Roll is "turning your head sideways to the left or right"
// Note: angle must be provided in radians
void CameraRoll(raylib_camera *camera, float angle)
{
    // Rotation axis
    raylib_vector3 forward = GetCameraForward(camera);

    // Rotate up direction around forward axis
    camera->up = Vector3RotateByAxisAngle(camera->up, forward, angle);
}

// Returns the camera view matrix
raylib_matrix GetCameraViewMatrix(raylib_camera *camera)
{
    return MatrixLookAt(camera->position, camera->target, camera->up);
}

// Returns the camera projection matrix
raylib_matrix GetCameraProjectionMatrix(raylib_camera *camera, float aspect)
{
    if (camera->projection == CAMERA_PERSPECTIVE)
    {
        return MatrixPerspective(camera->fovy*DEG2RAD, aspect, CAMERA_CULL_DISTANCE_NEAR, CAMERA_CULL_DISTANCE_FAR);
    }
    else if (camera->projection == CAMERA_ORTHOGRAPHIC)
    {
        double top = camera->fovy/2.0;
        double right = top*aspect;

        return MatrixOrtho(-right, right, -top, top, CAMERA_CULL_DISTANCE_NEAR, CAMERA_CULL_DISTANCE_FAR);
    }

    return MatrixIdentity();
}

#if !defined(RCAMERA_STANDALONE)
// Update camera position for selected mode
// raylib_camera mode: CAMERA_FREE, CAMERA_FIRST_PERSON, CAMERA_THIRD_PERSON, CAMERA_ORBITAL or CUSTOM
void raylib_updatecamera(raylib_camera *camera, int mode)
{
    raylib_vector2 mousePositionDelta = raylib_getmousedelta();

    bool moveInWorldPlane = ((mode == CAMERA_FIRST_PERSON) || (mode == CAMERA_THIRD_PERSON));
    bool rotateAroundTarget = ((mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL));
    bool lockView = ((mode == CAMERA_FREE) || (mode == CAMERA_FIRST_PERSON) || (mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL));
    bool rotateUp = false;

    if (mode == CAMERA_CUSTOM) {}
    else if (mode == CAMERA_ORBITAL)
    {
        // Orbital can just orbit
        raylib_matrix rotation = MatrixRotate(GetCameraUp(camera), CAMERA_ORBITAL_SPEED*raylib_getframetime());
        raylib_vector3 view = Vector3Subtract(camera->position, camera->target);
        view = Vector3Transform(view, rotation);
        camera->position = Vector3Add(camera->target, view);
    }
    else
    {
        // raylib_camera rotation
        if (raylib_iskeydown(KEY_DOWN)) CameraPitch(camera, -CAMERA_ROTATION_SPEED, lockView, rotateAroundTarget, rotateUp);
        if (raylib_iskeydown(KEY_UP)) CameraPitch(camera, CAMERA_ROTATION_SPEED, lockView, rotateAroundTarget, rotateUp);
        if (raylib_iskeydown(KEY_RIGHT)) CameraYaw(camera, -CAMERA_ROTATION_SPEED, rotateAroundTarget);
        if (raylib_iskeydown(KEY_LEFT)) CameraYaw(camera, CAMERA_ROTATION_SPEED, rotateAroundTarget);
        if (raylib_iskeydown(KEY_Q)) CameraRoll(camera, -CAMERA_ROTATION_SPEED);
        if (raylib_iskeydown(KEY_E)) CameraRoll(camera, CAMERA_ROTATION_SPEED);

        // raylib_camera movement
        // raylib_camera pan (for CAMERA_FREE)
        if ((mode == CAMERA_FREE) && (raylib_ismousebuttondown(MOUSE_BUTTON_MIDDLE)))
        {
            const raylib_vector2 mouseDelta = raylib_getmousedelta();
            if (mouseDelta.x > 0.0f) CameraMoveRight(camera, CAMERA_PAN_SPEED, moveInWorldPlane);
            if (mouseDelta.x < 0.0f) CameraMoveRight(camera, -CAMERA_PAN_SPEED, moveInWorldPlane);
            if (mouseDelta.y > 0.0f) CameraMoveUp(camera, -CAMERA_PAN_SPEED);
            if (mouseDelta.y < 0.0f) CameraMoveUp(camera, CAMERA_PAN_SPEED);
        }
        else
        {
            // Mouse support
            CameraYaw(camera, -mousePositionDelta.x*CAMERA_MOUSE_MOVE_SENSITIVITY, rotateAroundTarget);
            CameraPitch(camera, -mousePositionDelta.y*CAMERA_MOUSE_MOVE_SENSITIVITY, lockView, rotateAroundTarget, rotateUp);
        }

        // Keyboard support
        if (raylib_iskeydown(KEY_W)) CameraMoveForward(camera, CAMERA_MOVE_SPEED, moveInWorldPlane);
        if (raylib_iskeydown(KEY_A)) CameraMoveRight(camera, -CAMERA_MOVE_SPEED, moveInWorldPlane);
        if (raylib_iskeydown(KEY_S)) CameraMoveForward(camera, -CAMERA_MOVE_SPEED, moveInWorldPlane);
        if (raylib_iskeydown(KEY_D)) CameraMoveRight(camera, CAMERA_MOVE_SPEED, moveInWorldPlane);

        // Gamepad movement
        if (raylib_isgamepadavailable(0))
        {
            // Gamepad controller support
            CameraYaw(camera, -(raylib_getgamepadaxismovement(0, GAMEPAD_AXIS_RIGHT_X) * 2)*CAMERA_MOUSE_MOVE_SENSITIVITY, rotateAroundTarget);
            CameraPitch(camera, -(raylib_getgamepadaxismovement(0, GAMEPAD_AXIS_RIGHT_Y) * 2)*CAMERA_MOUSE_MOVE_SENSITIVITY, lockView, rotateAroundTarget, rotateUp);

            if (raylib_getgamepadaxismovement(0, GAMEPAD_AXIS_LEFT_Y) <= -0.25f) CameraMoveForward(camera, CAMERA_MOVE_SPEED, moveInWorldPlane);
            if (raylib_getgamepadaxismovement(0, GAMEPAD_AXIS_LEFT_X) <= -0.25f) CameraMoveRight(camera, -CAMERA_MOVE_SPEED, moveInWorldPlane);
            if (raylib_getgamepadaxismovement(0, GAMEPAD_AXIS_LEFT_Y) >= 0.25f) CameraMoveForward(camera, -CAMERA_MOVE_SPEED, moveInWorldPlane);
            if (raylib_getgamepadaxismovement(0, GAMEPAD_AXIS_LEFT_X) >= 0.25f) CameraMoveRight(camera, CAMERA_MOVE_SPEED, moveInWorldPlane);
        }

        if (mode == CAMERA_FREE)
        {
            if (raylib_iskeydown(KEY_SPACE)) CameraMoveUp(camera, CAMERA_MOVE_SPEED);
            if (raylib_iskeydown(KEY_LEFT_CONTROL)) CameraMoveUp(camera, -CAMERA_MOVE_SPEED);
        }
    }

    if ((mode == CAMERA_THIRD_PERSON) || (mode == CAMERA_ORBITAL) || (mode == CAMERA_FREE))
    {
        // Zoom target distance
        CameraMoveToTarget(camera, -raylib_getmousewheelmove());
        if (raylib_iskeypressed(KEY_KP_SUBTRACT)) CameraMoveToTarget(camera, 2.0f);
        if (raylib_iskeypressed(KEY_KP_ADD)) CameraMoveToTarget(camera, -2.0f);
    }
}
#endif // !RCAMERA_STANDALONE

// Update camera movement, movement/rotation values should be provided by user
void raylib_updatecamerapro(raylib_camera *camera, raylib_vector3 movement, raylib_vector3 rotation, float zoom)
{
    // Required values
    // movement.x - Move forward/backward
    // movement.y - Move right/left
    // movement.z - Move up/down
    // rotation.x - yaw
    // rotation.y - pitch
    // rotation.z - roll
    // zoom - Move towards target

    bool lockView = true;
    bool rotateAroundTarget = false;
    bool rotateUp = false;
    bool moveInWorldPlane = true;

    // raylib_camera rotation
    CameraPitch(camera, -rotation.y*DEG2RAD, lockView, rotateAroundTarget, rotateUp);
    CameraYaw(camera, -rotation.x*DEG2RAD, rotateAroundTarget);
    CameraRoll(camera, rotation.z*DEG2RAD);

    // raylib_camera movement
    CameraMoveForward(camera, movement.x, moveInWorldPlane);
    CameraMoveRight(camera, movement.y, moveInWorldPlane);
    CameraMoveUp(camera, movement.z);

    // Zoom target distance
    CameraMoveToTarget(camera, zoom);
}

#endif // RCAMERA_IMPLEMENTATION
