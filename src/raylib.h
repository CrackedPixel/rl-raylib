/**********************************************************************************************
*
*   raylib v5.1-dev - A simple and easy-to-use library to enjoy videogames programming (www.raylib.com)
*
*   FEATURES:
*       - NO external dependencies, all required libraries included with raylib
*       - Multiplatform: Windows, Linux, FreeBSD, OpenBSD, NetBSD, DragonFly,
*                        MacOS, Haiku, Android, Raspberry Pi, DRM native, HTML5.
*       - Written in plain C code (C99) in PascalCase/camelCase notation
*       - Hardware accelerated with OpenGL (1.1, 2.1, 3.3, 4.3 or ES2 - choose at compile)
*       - Unique OpenGL abstraction layer (usable as standalone module): [rlgl]
*       - Multiple Fonts formats supported (TTF, XNA fonts, AngelCode fonts)
*       - Outstanding texture formats support, including compressed formats (DXT, ETC, ASTC)
*       - Full 3d support for 3d Shapes, Models, Billboards, Heightmaps and more!
*       - Flexible Materials system, supporting classic maps and PBR maps
*       - Animated 3D models supported (skeletal bones animation) (IQM)
*       - Shaders support, including raylib_model shaders and Postprocessing shaders
*       - Powerful math module for Vector, raylib_matrix and Quaternion operations: [raymath]
*       - Audio loading and playing with streaming support (WAV, OGG, MP3, FLAC, XM, MOD)
*       - VR stereo rendering with configurable HMD device parameters
*       - Bindings to multiple programming languages available!
*
*   NOTES:
*       - One default raylib_font is loaded on raylib_initwindow()->LoadFontDefault() [core, text]
*       - One default raylib_texture2d is loaded on rlglInit(), 1x1 white pixel R8G8B8A8 [rlgl] (OpenGL 3.3 or ES2)
*       - One default raylib_shader is loaded on rlglInit()->rlLoadShaderDefault() [rlgl] (OpenGL 3.3 or ES2)
*       - One default RenderBatch is loaded on rlglInit()->rlLoadRenderBatch() [rlgl] (OpenGL 3.3 or ES2)
*
*   DEPENDENCIES (included):
*       [rcore] rglfw (Camilla Löwy - github.com/glfw/glfw) for window/context management and input (PLATFORM_DESKTOP)
*       [rlgl] glad (David Herberth - github.com/Dav1dde/glad) for OpenGL 3.3 extensions loading (PLATFORM_DESKTOP)
*       [raudio] miniaudio (David Reid - github.com/mackron/miniaudio) for audio device/context management
*
*   OPTIONAL DEPENDENCIES (included):
*       [rcore] msf_gif (Miles Fogle) for GIF recording
*       [rcore] sinfl (Micha Mettke) for DEFLATE decompression algorithm
*       [rcore] sdefl (Micha Mettke) for DEFLATE compression algorithm
*       [rtextures] stb_image (Sean Barret) for images loading (BMP, TGA, PNG, JPEG, HDR...)
*       [rtextures] stb_image_write (Sean Barret) for image writing (BMP, TGA, PNG, JPG)
*       [rtextures] stb_image_resize (Sean Barret) for image resizing algorithms
*       [rtext] stb_truetype (Sean Barret) for ttf fonts loading
*       [rtext] stb_rect_pack (Sean Barret) for rectangles packing
*       [rmodels] par_shapes (Philip Rideout) for parametric 3d shapes generation
*       [rmodels] tinyobj_loader_c (Syoyo Fujita) for models loading (OBJ, MTL)
*       [rmodels] cgltf (Johannes Kuhlmann) for models loading (glTF)
*       [rmodels] Model3D (bzt) for models loading (M3D, https://bztsrc.gitlab.io/model3d)
*       [raudio] dr_wav (David Reid) for WAV audio file loading
*       [raudio] dr_flac (David Reid) for FLAC audio file loading
*       [raudio] dr_mp3 (David Reid) for MP3 audio file loading
*       [raudio] stb_vorbis (Sean Barret) for OGG audio loading
*       [raudio] jar_xm (Joshua Reisenauer) for XM audio module loading
*       [raudio] jar_mod (Joshua Reisenauer) for MOD audio module loading
*
*
*   LICENSE: zlib/libpng
*
*   raylib is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software:
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
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

#ifndef RAYLIB_H
#define RAYLIB_H

#include <stdarg.h>     // Required for: va_list - Only used by raylib_tracelogcallback

#define RAYLIB_VERSION_MAJOR 5
#define RAYLIB_VERSION_MINOR 1
#define RAYLIB_VERSION_PATCH 0
#define RAYLIB_VERSION  "5.1-dev"

// Function specifiers in case library is build/used as a shared library
// NOTE: Microsoft specifiers to tell compiler that symbols are imported/exported from a .dll
// NOTE: visibility("default") attribute makes symbols "visible" when compiled with -fvisibility=hidden
#if defined(_WIN32)
    #if defined(__TINYC__)
        #define __declspec(x) __attribute__((x))
    #endif
    #if defined(BUILD_LIBTYPE_SHARED)
        #define RLAPI __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
    #elif defined(USE_LIBTYPE_SHARED)
        #define RLAPI __declspec(dllimport)     // We are using the library as a Win32 shared library (.dll)
    #endif
#else
    #if defined(BUILD_LIBTYPE_SHARED)
        #define RLAPI __attribute__((visibility("default"))) // We are building as a Unix shared library (.so/.dylib)
    #endif
#endif

#ifndef RLAPI
    #define RLAPI       // Functions defined as 'extern' by default (implicit specifiers)
#endif

//----------------------------------------------------------------------------------
// Some basic Defines
//----------------------------------------------------------------------------------
#ifndef PI
    #define PI 3.14159265358979323846f
#endif
#ifndef DEG2RAD
    #define DEG2RAD (PI/180.0f)
#endif
#ifndef RAD2DEG
    #define RAD2DEG (180.0f/PI)
#endif

// Allow custom memory allocators
// NOTE: Require recompiling raylib sources
#ifndef RL_MALLOC
    #define RL_MALLOC(sz)       malloc(sz)
#endif
#ifndef RL_CALLOC
    #define RL_CALLOC(n,sz)     calloc(n,sz)
#endif
#ifndef RL_REALLOC
    #define RL_REALLOC(ptr,sz)  realloc(ptr,sz)
#endif
#ifndef RL_FREE
    #define RL_FREE(ptr)        free(ptr)
#endif

// NOTE: MSVC C++ compiler does not support compound literals (C99 feature)
// Plain structures in C++ (without constructors) can be initialized with { }
// This is called aggregate initialization (C++11 feature)
#if defined(__cplusplus)
    #define CLITERAL(type)      type
#else
    #define CLITERAL(type)      (type)
#endif

// Some compilers (mostly macos clang) default to C++98,
// where aggregate initialization can't be used
// So, give a more clear error stating how to fix this
#if !defined(_MSC_VER) && (defined(__cplusplus) && __cplusplus < 201103L)
    #error "C++11 or later is required. Add -std=c++11"
#endif

// NOTE: We set some defines with some data types declared by raylib
// Other modules (raymath, rlgl) also require some of those types, so,
// to be able to use those other modules as standalone (not depending on raylib)
// this defines are very useful for internal check and avoid type (re)definitions
#define RL_COLOR_TYPE
#define RL_RECTANGLE_TYPE
#define RL_VECTOR2_TYPE
#define RL_VECTOR3_TYPE
#define RL_VECTOR4_TYPE
#define RL_QUATERNION_TYPE
#define RL_MATRIX_TYPE

// Some Basic Colors
// NOTE: Custom raylib color palette for amazing visuals on raylib_white background
#define raylib_lightgray  CLITERAL(raylib_color){ 200, 200, 200, 255 }   // Light Gray
#define raylib_gray       CLITERAL(raylib_color){ 130, 130, 130, 255 }   // Gray
#define raylib_darkgray   CLITERAL(raylib_color){ 80, 80, 80, 255 }      // Dark Gray
#define raylib_yellow     CLITERAL(raylib_color){ 253, 249, 0, 255 }     // Yellow
#define raylib_gold       CLITERAL(raylib_color){ 255, 203, 0, 255 }     // Gold
#define raylib_orange     CLITERAL(raylib_color){ 255, 161, 0, 255 }     // Orange
#define raylib_pink       CLITERAL(raylib_color){ 255, 109, 194, 255 }   // Pink
#define raylib_red        CLITERAL(raylib_color){ 230, 41, 55, 255 }     // Red
#define raylib_maroon     CLITERAL(raylib_color){ 190, 33, 55, 255 }     // Maroon
#define raylib_green      CLITERAL(raylib_color){ 0, 228, 48, 255 }      // Green
#define raylib_lime       CLITERAL(raylib_color){ 0, 158, 47, 255 }      // Lime
#define raylib_darkgreen  CLITERAL(raylib_color){ 0, 117, 44, 255 }      // Dark Green
#define raylib_skyblue    CLITERAL(raylib_color){ 102, 191, 255, 255 }   // Sky Blue
#define raylib_blue       CLITERAL(raylib_color){ 0, 121, 241, 255 }     // Blue
#define raylib_darkblue   CLITERAL(raylib_color){ 0, 82, 172, 255 }      // Dark Blue
#define raylib_purple     CLITERAL(raylib_color){ 200, 122, 255, 255 }   // Purple
#define raylib_violet     CLITERAL(raylib_color){ 135, 60, 190, 255 }    // Violet
#define raylib_darkpurple CLITERAL(raylib_color){ 112, 31, 126, 255 }    // Dark Purple
#define raylib_beige      CLITERAL(raylib_color){ 211, 176, 131, 255 }   // Beige
#define raylib_brown      CLITERAL(raylib_color){ 127, 106, 79, 255 }    // Brown
#define raylib_darkbrown  CLITERAL(raylib_color){ 76, 63, 47, 255 }      // Dark Brown

#define raylib_white      CLITERAL(raylib_color){ 255, 255, 255, 255 }   // White
#define raylib_black      CLITERAL(raylib_color){ 0, 0, 0, 255 }         // Black
#define raylib_blank      CLITERAL(raylib_color){ 0, 0, 0, 0 }           // Blank (Transparent)
#define raylib_magenta    CLITERAL(raylib_color){ 255, 0, 255, 255 }     // Magenta
#define raylib_raywhite   CLITERAL(raylib_color){ 245, 245, 245, 255 }   // My own White (raylib logo)

//----------------------------------------------------------------------------------
// Structures Definition
//----------------------------------------------------------------------------------
// Boolean type
#if (defined(__STDC__) && __STDC_VERSION__ >= 199901L) || (defined(_MSC_VER) && _MSC_VER >= 1800)
    #include <stdbool.h>
#elif !defined(__cplusplus) && !defined(bool)
    typedef enum bool { false = 0, true = !false } bool;
    #define RL_BOOL_TYPE
#endif

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

// raylib_vector4, 4 components
typedef struct raylib_vector4 {
    float x;                // Vector x component
    float y;                // Vector y component
    float z;                // Vector z component
    float w;                // Vector w component
} raylib_vector4;

// Quaternion, 4 components (raylib_vector4 alias)
typedef raylib_vector4 Quaternion;

// raylib_matrix, 4x4 components, column major, OpenGL style, right-handed
typedef struct raylib_matrix {
    float m0, m4, m8, m12;  // raylib_matrix first row (4 components)
    float m1, m5, m9, m13;  // raylib_matrix second row (4 components)
    float m2, m6, m10, m14; // raylib_matrix third row (4 components)
    float m3, m7, m11, m15; // raylib_matrix fourth row (4 components)
} raylib_matrix;

// raylib_color, 4 components, R8G8B8A8 (32bit)
typedef struct raylib_color {
    unsigned char r;        // raylib_color red value
    unsigned char g;        // raylib_color green value
    unsigned char b;        // raylib_color blue value
    unsigned char a;        // raylib_color alpha value
} raylib_color;

// raylib_rectangle, 4 components
typedef struct raylib_rectangle {
    float x;                // raylib_rectangle top-left corner position x
    float y;                // raylib_rectangle top-left corner position y
    float width;            // raylib_rectangle width
    float height;           // raylib_rectangle height
} raylib_rectangle;

// raylib_image, pixel data stored in CPU memory (RAM)
typedef struct raylib_image {
    void *data;             // raylib_image raw data
    int width;              // raylib_image base width
    int height;             // raylib_image base height
    int mipmaps;            // Mipmap levels, 1 by default
    int format;             // Data format (raylib_pixelformat type)
} raylib_image;

// raylib_texture, tex data stored in GPU memory (VRAM)
typedef struct raylib_texture {
    unsigned int id;        // OpenGL texture id
    int width;              // raylib_texture base width
    int height;             // raylib_texture base height
    int mipmaps;            // Mipmap levels, 1 by default
    int format;             // Data format (raylib_pixelformat type)
} raylib_texture;

// raylib_texture2d, same as raylib_texture
typedef raylib_texture raylib_texture2d;

// raylib_texturecubemap, same as raylib_texture
typedef raylib_texture raylib_texturecubemap;

// raylib_rendertexture, fbo for texture rendering
typedef struct raylib_rendertexture {
    unsigned int id;        // OpenGL framebuffer object id
    raylib_texture texture;        // raylib_color buffer attachment texture
    raylib_texture depth;          // Depth buffer attachment texture
} raylib_rendertexture;

// raylib_rendertexture2d, same as raylib_rendertexture
typedef raylib_rendertexture raylib_rendertexture2d;

// raylib_npatchinfo, n-patch layout info
typedef struct raylib_npatchinfo {
    raylib_rectangle source;       // raylib_texture source rectangle
    int left;               // Left border offset
    int top;                // Top border offset
    int right;              // Right border offset
    int bottom;             // Bottom border offset
    int layout;             // Layout of the n-patch: 3x3, 1x3 or 3x1
} raylib_npatchinfo;

// raylib_glyphinfo, font characters glyphs info
typedef struct raylib_glyphinfo {
    int value;              // Character value (Unicode)
    int offsetX;            // Character offset X when drawing
    int offsetY;            // Character offset Y when drawing
    int advanceX;           // Character advance position X
    raylib_image image;            // Character image data
} raylib_glyphinfo;

// raylib_font, font texture and raylib_glyphinfo array data
typedef struct raylib_font {
    int baseSize;           // Base size (default chars height)
    int glyphCount;         // Number of glyph characters
    int glyphPadding;       // Padding around the glyph characters
    raylib_texture2d texture;      // raylib_texture atlas containing the glyphs
    raylib_rectangle *recs;        // Rectangles in texture for the glyphs
    raylib_glyphinfo *glyphs;      // Glyphs info data
} raylib_font;

// raylib_camera, defines position/orientation in 3d space
typedef struct raylib_camera3d {
    raylib_vector3 position;       // raylib_camera position
    raylib_vector3 target;         // raylib_camera target it looks-at
    raylib_vector3 up;             // raylib_camera up vector (rotation over its axis)
    float fovy;             // raylib_camera field-of-view aperture in Y (degrees) in perspective, used as near plane width in orthographic
    int projection;         // raylib_camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
} raylib_camera3d;

typedef raylib_camera3d raylib_camera;    // raylib_camera type fallback, defaults to raylib_camera3d

// raylib_camera2d, defines position/orientation in 2d space
typedef struct raylib_camera2d {
    raylib_vector2 offset;         // raylib_camera offset (displacement from target)
    raylib_vector2 target;         // raylib_camera target (rotation and zoom origin)
    float rotation;         // raylib_camera rotation in degrees
    float zoom;             // raylib_camera zoom (scaling), should be 1.0f by default
} raylib_camera2d;

// raylib_mesh, vertex data and vao/vbo
typedef struct raylib_mesh {
    int vertexCount;        // Number of vertices stored in arrays
    int triangleCount;      // Number of triangles stored (indexed or not)

    // Vertex attributes data
    float *vertices;        // Vertex position (XYZ - 3 components per vertex) (shader-location = 0)
    float *texcoords;       // Vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1)
    float *texcoords2;      // Vertex texture second coordinates (UV - 2 components per vertex) (shader-location = 5)
    float *normals;         // Vertex normals (XYZ - 3 components per vertex) (shader-location = 2)
    float *tangents;        // Vertex tangents (XYZW - 4 components per vertex) (shader-location = 4)
    unsigned char *colors;      // Vertex colors (RGBA - 4 components per vertex) (shader-location = 3)
    unsigned short *indices;    // Vertex indices (in case vertex data comes indexed)

    // Animation vertex data
    float *animVertices;    // Animated vertex positions (after bones transformations)
    float *animNormals;     // Animated normals (after bones transformations)
    unsigned char *boneIds; // Vertex bone ids, max 255 bone ids, up to 4 bones influence by vertex (skinning)
    float *boneWeights;     // Vertex bone weight, up to 4 bones influence by vertex (skinning)

    // OpenGL identifiers
    unsigned int vaoId;     // OpenGL Vertex Array Object id
    unsigned int *vboId;    // OpenGL Vertex Buffer Objects id (default vertex data)
} raylib_mesh;

// raylib_shader
typedef struct raylib_shader {
    unsigned int id;        // raylib_shader program id
    int *locs;              // raylib_shader locations array (RL_MAX_SHADER_LOCATIONS)
} raylib_shader;

// raylib_materialmap
typedef struct raylib_materialmap {
    raylib_texture2d texture;      // raylib_material map texture
    raylib_color color;            // raylib_material map color
    float value;            // raylib_material map value
} raylib_materialmap;

// raylib_material, includes shader and maps
typedef struct raylib_material {
    raylib_shader shader;          // raylib_material shader
    raylib_materialmap *maps;      // raylib_material maps array (MAX_MATERIAL_MAPS)
    float params[4];        // raylib_material generic parameters (if required)
} raylib_material;

// raylib_transform, vertex transformation data
typedef struct raylib_transform {
    raylib_vector3 translation;    // Translation
    Quaternion rotation;    // Rotation
    raylib_vector3 scale;          // Scale
} raylib_transform;

// Bone, skeletal animation bone
typedef struct raylib_boneinfo {
    char name[32];          // Bone name
    int parent;             // Bone parent
} raylib_boneinfo;

// raylib_model, meshes, materials and animation data
typedef struct raylib_model {
    raylib_matrix transform;       // Local transform matrix

    int meshCount;          // Number of meshes
    int materialCount;      // Number of materials
    raylib_mesh *meshes;           // Meshes array
    raylib_material *materials;    // Materials array
    int *meshMaterial;      // raylib_mesh material number

    // Animation data
    int boneCount;          // Number of bones
    raylib_boneinfo *bones;        // Bones information (skeleton)
    raylib_transform *bindPose;    // Bones base transformation (pose)
} raylib_model;

// raylib_modelanimation
typedef struct raylib_modelanimation {
    int boneCount;          // Number of bones
    int frameCount;         // Number of animation frames
    raylib_boneinfo *bones;        // Bones information (skeleton)
    raylib_transform **framePoses; // Poses array by frame
    char name[32];          // Animation name
} raylib_modelanimation;

// raylib_ray, ray for raycasting
typedef struct raylib_ray {
    raylib_vector3 position;       // raylib_ray position (origin)
    raylib_vector3 direction;      // raylib_ray direction
} raylib_ray;

// raylib_raycollision, ray hit information
typedef struct raylib_raycollision {
    bool hit;               // Did the ray hit something?
    float distance;         // Distance to the nearest hit
    raylib_vector3 point;          // Point of the nearest hit
    raylib_vector3 normal;         // Surface normal of hit
} raylib_raycollision;

// raylib_boundingbox
typedef struct raylib_boundingbox {
    raylib_vector3 min;            // Minimum vertex box-corner
    raylib_vector3 max;            // Maximum vertex box-corner
} raylib_boundingbox;

// raylib_wave, audio wave data
typedef struct raylib_wave {
    unsigned int frameCount;    // Total number of frames (considering channels)
    unsigned int sampleRate;    // Frequency (samples per second)
    unsigned int sampleSize;    // Bit depth (bits per sample): 8, 16, 32 (24 not supported)
    unsigned int channels;      // Number of channels (1-mono, 2-stereo, ...)
    void *data;                 // Buffer data pointer
} raylib_wave;

// Opaque structs declaration
// NOTE: Actual structs are defined internally in raudio module
typedef struct raylib_raudiobuffer raylib_raudiobuffer;
typedef struct raylib_raudioprocessor raylib_raudioprocessor;

// raylib_audiostream, custom audio stream
typedef struct raylib_audiostream {
    raylib_raudiobuffer *buffer;       // Pointer to internal data used by the audio system
    raylib_raudioprocessor *processor; // Pointer to internal data processor, useful for audio effects

    unsigned int sampleRate;    // Frequency (samples per second)
    unsigned int sampleSize;    // Bit depth (bits per sample): 8, 16, 32 (24 not supported)
    unsigned int channels;      // Number of channels (1-mono, 2-stereo, ...)
} raylib_audiostream;

// raylib_sound
typedef struct raylib_sound {
    raylib_audiostream stream;         // Audio stream
    unsigned int frameCount;    // Total number of frames (considering channels)
} raylib_sound;

// raylib_music, audio stream, anything longer than ~10 seconds should be streamed
typedef struct raylib_music {
    raylib_audiostream stream;         // Audio stream
    unsigned int frameCount;    // Total number of frames (considering channels)
    bool looping;               // raylib_music looping enable

    int ctxType;                // Type of music context (audio filetype)
    void *ctxData;              // Audio context data, depends on type
} raylib_music;

// raylib_vrdeviceinfo, Head-Mounted-Display device parameters
typedef struct raylib_vrdeviceinfo {
    int hResolution;                // Horizontal resolution in pixels
    int vResolution;                // Vertical resolution in pixels
    float hScreenSize;              // Horizontal size in meters
    float vScreenSize;              // Vertical size in meters
    float eyeToScreenDistance;      // Distance between eye and display in meters
    float lensSeparationDistance;   // Lens separation distance in meters
    float interpupillaryDistance;   // IPD (distance between pupils) in meters
    float lensDistortionValues[4];  // Lens distortion constant parameters
    float chromaAbCorrection[4];    // Chromatic aberration correction parameters
} raylib_vrdeviceinfo;

// raylib_vrstereoconfig, VR stereo rendering configuration for simulator
typedef struct raylib_vrstereoconfig {
    raylib_matrix projection[2];           // VR projection matrices (per eye)
    raylib_matrix viewOffset[2];           // VR view offset matrices (per eye)
    float leftLensCenter[2];        // VR left lens center
    float rightLensCenter[2];       // VR right lens center
    float leftScreenCenter[2];      // VR left screen center
    float rightScreenCenter[2];     // VR right screen center
    float scale[2];                 // VR distortion scale
    float scaleIn[2];               // VR distortion scale in
} raylib_vrstereoconfig;

// File path list
typedef struct raylib_filepathlist {
    unsigned int capacity;          // Filepaths max entries
    unsigned int count;             // Filepaths entries count
    char **paths;                   // Filepaths entries
} raylib_filepathlist;

// Automation event
typedef struct raylib_automationevent {
    unsigned int frame;             // Event frame
    unsigned int type;              // Event type (AutomationEventType)
    int params[4];                  // Event parameters (if required)
} raylib_automationevent;

// Automation event list
typedef struct raylib_automationeventlist {
    unsigned int capacity;          // Events max entries (MAX_AUTOMATION_EVENTS)
    unsigned int count;             // Events entries count
    raylib_automationevent *events;        // Events entries
} raylib_automationeventlist;

//----------------------------------------------------------------------------------
// Enumerators Definition
//----------------------------------------------------------------------------------
// System/Window config flags
// NOTE: Every bit registers one state (use it with bit masks)
// By default all flags are set to 0
typedef enum {
    FLAG_VSYNC_HINT         = 0x00000040,   // Set to try enabling V-Sync on GPU
    FLAG_FULLSCREEN_MODE    = 0x00000002,   // Set to run program in fullscreen
    FLAG_WINDOW_RESIZABLE   = 0x00000004,   // Set to allow resizable window
    FLAG_WINDOW_UNDECORATED = 0x00000008,   // Set to disable window decoration (frame and buttons)
    FLAG_WINDOW_HIDDEN      = 0x00000080,   // Set to hide window
    FLAG_WINDOW_MINIMIZED   = 0x00000200,   // Set to minimize window (iconify)
    FLAG_WINDOW_MAXIMIZED   = 0x00000400,   // Set to maximize window (expanded to monitor)
    FLAG_WINDOW_UNFOCUSED   = 0x00000800,   // Set to window non focused
    FLAG_WINDOW_TOPMOST     = 0x00001000,   // Set to window always on top
    FLAG_WINDOW_ALWAYS_RUN  = 0x00000100,   // Set to allow windows running while minimized
    FLAG_WINDOW_TRANSPARENT = 0x00000010,   // Set to allow transparent framebuffer
    FLAG_WINDOW_HIGHDPI     = 0x00002000,   // Set to support HighDPI
    FLAG_WINDOW_MOUSE_PASSTHROUGH = 0x00004000, // Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED
    FLAG_BORDERLESS_WINDOWED_MODE = 0x00008000, // Set to run program in borderless windowed mode
    FLAG_MSAA_4X_HINT       = 0x00000020,   // Set to try enabling MSAA 4X
    FLAG_INTERLACED_HINT    = 0x00010000    // Set to try enabling interlaced video format (for V3D)
} raylib_configflags;

// Trace log level
// NOTE: Organized by priority level
typedef enum {
    LOG_ALL = 0,        // Display all logs
    LOG_TRACE,          // Trace logging, intended for internal use only
    LOG_DEBUG,          // Debug logging, used for internal debugging, it should be disabled on release builds
    LOG_INFO,           // Info logging, used for program execution info
    LOG_WARNING,        // Warning logging, used on recoverable failures
    LOG_ERROR,          // Error logging, used on unrecoverable failures
    LOG_FATAL,          // Fatal logging, used to abort program: exit(EXIT_FAILURE)
    LOG_NONE            // Disable logging
} raylib_traceloglevel;

// Keyboard keys (US keyboard layout)
// NOTE: Use raylib_getkeypressed() to allow redefining
// required keys for alternative layouts
typedef enum {
    KEY_NULL            = 0,        // Key: NULL, used for no key pressed
    // Alphanumeric keys
    KEY_APOSTROPHE      = 39,       // Key: '
    KEY_COMMA           = 44,       // Key: ,
    KEY_MINUS           = 45,       // Key: -
    KEY_PERIOD          = 46,       // Key: .
    KEY_SLASH           = 47,       // Key: /
    KEY_ZERO            = 48,       // Key: 0
    KEY_ONE             = 49,       // Key: 1
    KEY_TWO             = 50,       // Key: 2
    KEY_THREE           = 51,       // Key: 3
    KEY_FOUR            = 52,       // Key: 4
    KEY_FIVE            = 53,       // Key: 5
    KEY_SIX             = 54,       // Key: 6
    KEY_SEVEN           = 55,       // Key: 7
    KEY_EIGHT           = 56,       // Key: 8
    KEY_NINE            = 57,       // Key: 9
    KEY_SEMICOLON       = 59,       // Key: ;
    KEY_EQUAL           = 61,       // Key: =
    KEY_A               = 65,       // Key: A | a
    KEY_B               = 66,       // Key: B | b
    KEY_C               = 67,       // Key: C | c
    KEY_D               = 68,       // Key: D | d
    KEY_E               = 69,       // Key: E | e
    KEY_F               = 70,       // Key: F | f
    KEY_G               = 71,       // Key: G | g
    KEY_H               = 72,       // Key: H | h
    KEY_I               = 73,       // Key: I | i
    KEY_J               = 74,       // Key: J | j
    KEY_K               = 75,       // Key: K | k
    KEY_L               = 76,       // Key: L | l
    KEY_M               = 77,       // Key: M | m
    KEY_N               = 78,       // Key: N | n
    KEY_O               = 79,       // Key: O | o
    KEY_P               = 80,       // Key: P | p
    KEY_Q               = 81,       // Key: Q | q
    KEY_R               = 82,       // Key: R | r
    KEY_S               = 83,       // Key: S | s
    KEY_T               = 84,       // Key: T | t
    KEY_U               = 85,       // Key: U | u
    KEY_V               = 86,       // Key: V | v
    KEY_W               = 87,       // Key: W | w
    KEY_X               = 88,       // Key: X | x
    KEY_Y               = 89,       // Key: Y | y
    KEY_Z               = 90,       // Key: Z | z
    KEY_LEFT_BRACKET    = 91,       // Key: [
    KEY_BACKSLASH       = 92,       // Key: '\'
    KEY_RIGHT_BRACKET   = 93,       // Key: ]
    KEY_GRAVE           = 96,       // Key: `
    // Function keys
    KEY_SPACE           = 32,       // Key: Space
    KEY_ESCAPE          = 256,      // Key: Esc
    KEY_ENTER           = 257,      // Key: Enter
    KEY_TAB             = 258,      // Key: Tab
    KEY_BACKSPACE       = 259,      // Key: Backspace
    KEY_INSERT          = 260,      // Key: Ins
    KEY_DELETE          = 261,      // Key: Del
    KEY_RIGHT           = 262,      // Key: Cursor right
    KEY_LEFT            = 263,      // Key: Cursor left
    KEY_DOWN            = 264,      // Key: Cursor down
    KEY_UP              = 265,      // Key: Cursor up
    KEY_PAGE_UP         = 266,      // Key: Page up
    KEY_PAGE_DOWN       = 267,      // Key: Page down
    KEY_HOME            = 268,      // Key: Home
    KEY_END             = 269,      // Key: End
    KEY_CAPS_LOCK       = 280,      // Key: Caps lock
    KEY_SCROLL_LOCK     = 281,      // Key: Scroll down
    KEY_NUM_LOCK        = 282,      // Key: Num lock
    KEY_PRINT_SCREEN    = 283,      // Key: Print screen
    KEY_PAUSE           = 284,      // Key: Pause
    KEY_F1              = 290,      // Key: F1
    KEY_F2              = 291,      // Key: F2
    KEY_F3              = 292,      // Key: F3
    KEY_F4              = 293,      // Key: F4
    KEY_F5              = 294,      // Key: F5
    KEY_F6              = 295,      // Key: F6
    KEY_F7              = 296,      // Key: F7
    KEY_F8              = 297,      // Key: F8
    KEY_F9              = 298,      // Key: F9
    KEY_F10             = 299,      // Key: F10
    KEY_F11             = 300,      // Key: F11
    KEY_F12             = 301,      // Key: F12
    KEY_LEFT_SHIFT      = 340,      // Key: Shift left
    KEY_LEFT_CONTROL    = 341,      // Key: Control left
    KEY_LEFT_ALT        = 342,      // Key: Alt left
    KEY_LEFT_SUPER      = 343,      // Key: Super left
    KEY_RIGHT_SHIFT     = 344,      // Key: Shift right
    KEY_RIGHT_CONTROL   = 345,      // Key: Control right
    KEY_RIGHT_ALT       = 346,      // Key: Alt right
    KEY_RIGHT_SUPER     = 347,      // Key: Super right
    KEY_KB_MENU         = 348,      // Key: KB menu
    // Keypad keys
    KEY_KP_0            = 320,      // Key: Keypad 0
    KEY_KP_1            = 321,      // Key: Keypad 1
    KEY_KP_2            = 322,      // Key: Keypad 2
    KEY_KP_3            = 323,      // Key: Keypad 3
    KEY_KP_4            = 324,      // Key: Keypad 4
    KEY_KP_5            = 325,      // Key: Keypad 5
    KEY_KP_6            = 326,      // Key: Keypad 6
    KEY_KP_7            = 327,      // Key: Keypad 7
    KEY_KP_8            = 328,      // Key: Keypad 8
    KEY_KP_9            = 329,      // Key: Keypad 9
    KEY_KP_DECIMAL      = 330,      // Key: Keypad .
    KEY_KP_DIVIDE       = 331,      // Key: Keypad /
    KEY_KP_MULTIPLY     = 332,      // Key: Keypad *
    KEY_KP_SUBTRACT     = 333,      // Key: Keypad -
    KEY_KP_ADD          = 334,      // Key: Keypad +
    KEY_KP_ENTER        = 335,      // Key: Keypad Enter
    KEY_KP_EQUAL        = 336,      // Key: Keypad =
    // Android key buttons
    KEY_BACK            = 4,        // Key: Android back button
    KEY_MENU            = 5,        // Key: Android menu button
    KEY_VOLUME_UP       = 24,       // Key: Android volume up button
    KEY_VOLUME_DOWN     = 25        // Key: Android volume down button
} raylib_keyboardkey;

// Add backwards compatibility support for deprecated names
#define MOUSE_LEFT_BUTTON   MOUSE_BUTTON_LEFT
#define MOUSE_RIGHT_BUTTON  MOUSE_BUTTON_RIGHT
#define MOUSE_MIDDLE_BUTTON MOUSE_BUTTON_MIDDLE

// Mouse buttons
typedef enum {
    MOUSE_BUTTON_LEFT    = 0,       // Mouse button left
    MOUSE_BUTTON_RIGHT   = 1,       // Mouse button right
    MOUSE_BUTTON_MIDDLE  = 2,       // Mouse button middle (pressed wheel)
    MOUSE_BUTTON_SIDE    = 3,       // Mouse button side (advanced mouse device)
    MOUSE_BUTTON_EXTRA   = 4,       // Mouse button extra (advanced mouse device)
    MOUSE_BUTTON_FORWARD = 5,       // Mouse button forward (advanced mouse device)
    MOUSE_BUTTON_BACK    = 6,       // Mouse button back (advanced mouse device)
} raylib_mousebutton;

// Mouse cursor
typedef enum {
    MOUSE_CURSOR_DEFAULT       = 0,     // Default pointer shape
    MOUSE_CURSOR_ARROW         = 1,     // Arrow shape
    MOUSE_CURSOR_IBEAM         = 2,     // Text writing cursor shape
    MOUSE_CURSOR_CROSSHAIR     = 3,     // Cross shape
    MOUSE_CURSOR_POINTING_HAND = 4,     // Pointing hand cursor
    MOUSE_CURSOR_RESIZE_EW     = 5,     // Horizontal resize/move arrow shape
    MOUSE_CURSOR_RESIZE_NS     = 6,     // Vertical resize/move arrow shape
    MOUSE_CURSOR_RESIZE_NWSE   = 7,     // Top-left to bottom-right diagonal resize/move arrow shape
    MOUSE_CURSOR_RESIZE_NESW   = 8,     // The top-right to bottom-left diagonal resize/move arrow shape
    MOUSE_CURSOR_RESIZE_ALL    = 9,     // The omnidirectional resize/move cursor shape
    MOUSE_CURSOR_NOT_ALLOWED   = 10     // The operation-not-allowed shape
} raylib_mousecursor;

// Gamepad buttons
typedef enum {
    GAMEPAD_BUTTON_UNKNOWN = 0,         // Unknown button, just for error checking
    GAMEPAD_BUTTON_LEFT_FACE_UP,        // Gamepad left DPAD up button
    GAMEPAD_BUTTON_LEFT_FACE_RIGHT,     // Gamepad left DPAD right button
    GAMEPAD_BUTTON_LEFT_FACE_DOWN,      // Gamepad left DPAD down button
    GAMEPAD_BUTTON_LEFT_FACE_LEFT,      // Gamepad left DPAD left button
    GAMEPAD_BUTTON_RIGHT_FACE_UP,       // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
    GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,    // Gamepad right button right (i.e. PS3: Circle, Xbox: B)
    GAMEPAD_BUTTON_RIGHT_FACE_DOWN,     // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
    GAMEPAD_BUTTON_RIGHT_FACE_LEFT,     // Gamepad right button left (i.e. PS3: Square, Xbox: X)
    GAMEPAD_BUTTON_LEFT_TRIGGER_1,      // Gamepad top/back trigger left (first), it could be a trailing button
    GAMEPAD_BUTTON_LEFT_TRIGGER_2,      // Gamepad top/back trigger left (second), it could be a trailing button
    GAMEPAD_BUTTON_RIGHT_TRIGGER_1,     // Gamepad top/back trigger right (first), it could be a trailing button
    GAMEPAD_BUTTON_RIGHT_TRIGGER_2,     // Gamepad top/back trigger right (second), it could be a trailing button
    GAMEPAD_BUTTON_MIDDLE_LEFT,         // Gamepad center buttons, left one (i.e. PS3: Select)
    GAMEPAD_BUTTON_MIDDLE,              // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
    GAMEPAD_BUTTON_MIDDLE_RIGHT,        // Gamepad center buttons, right one (i.e. PS3: Start)
    GAMEPAD_BUTTON_LEFT_THUMB,          // Gamepad joystick pressed button left
    GAMEPAD_BUTTON_RIGHT_THUMB          // Gamepad joystick pressed button right
} raylib_gamepadbutton;

// Gamepad axis
typedef enum {
    GAMEPAD_AXIS_LEFT_X        = 0,     // Gamepad left stick X axis
    GAMEPAD_AXIS_LEFT_Y        = 1,     // Gamepad left stick Y axis
    GAMEPAD_AXIS_RIGHT_X       = 2,     // Gamepad right stick X axis
    GAMEPAD_AXIS_RIGHT_Y       = 3,     // Gamepad right stick Y axis
    GAMEPAD_AXIS_LEFT_TRIGGER  = 4,     // Gamepad back trigger left, pressure level: [1..-1]
    GAMEPAD_AXIS_RIGHT_TRIGGER = 5      // Gamepad back trigger right, pressure level: [1..-1]
} raylib_gamepadaxis;

// raylib_material map index
typedef enum {
    MATERIAL_MAP_ALBEDO = 0,        // Albedo material (same as: MATERIAL_MAP_DIFFUSE)
    MATERIAL_MAP_METALNESS,         // Metalness material (same as: MATERIAL_MAP_SPECULAR)
    MATERIAL_MAP_NORMAL,            // Normal material
    MATERIAL_MAP_ROUGHNESS,         // Roughness material
    MATERIAL_MAP_OCCLUSION,         // Ambient occlusion material
    MATERIAL_MAP_EMISSION,          // Emission material
    MATERIAL_MAP_HEIGHT,            // Heightmap material
    MATERIAL_MAP_CUBEMAP,           // Cubemap material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
    MATERIAL_MAP_IRRADIANCE,        // Irradiance material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
    MATERIAL_MAP_PREFILTER,         // Prefilter material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
    MATERIAL_MAP_BRDF               // Brdf material
} raylib_materialmapindex;

#define MATERIAL_MAP_DIFFUSE      MATERIAL_MAP_ALBEDO
#define MATERIAL_MAP_SPECULAR     MATERIAL_MAP_METALNESS

// raylib_shader location index
typedef enum {
    SHADER_LOC_VERTEX_POSITION = 0, // raylib_shader location: vertex attribute: position
    SHADER_LOC_VERTEX_TEXCOORD01,   // raylib_shader location: vertex attribute: texcoord01
    SHADER_LOC_VERTEX_TEXCOORD02,   // raylib_shader location: vertex attribute: texcoord02
    SHADER_LOC_VERTEX_NORMAL,       // raylib_shader location: vertex attribute: normal
    SHADER_LOC_VERTEX_TANGENT,      // raylib_shader location: vertex attribute: tangent
    SHADER_LOC_VERTEX_COLOR,        // raylib_shader location: vertex attribute: color
    SHADER_LOC_MATRIX_MVP,          // raylib_shader location: matrix uniform: model-view-projection
    SHADER_LOC_MATRIX_VIEW,         // raylib_shader location: matrix uniform: view (camera transform)
    SHADER_LOC_MATRIX_PROJECTION,   // raylib_shader location: matrix uniform: projection
    SHADER_LOC_MATRIX_MODEL,        // raylib_shader location: matrix uniform: model (transform)
    SHADER_LOC_MATRIX_NORMAL,       // raylib_shader location: matrix uniform: normal
    SHADER_LOC_VECTOR_VIEW,         // raylib_shader location: vector uniform: view
    SHADER_LOC_COLOR_DIFFUSE,       // raylib_shader location: vector uniform: diffuse color
    SHADER_LOC_COLOR_SPECULAR,      // raylib_shader location: vector uniform: specular color
    SHADER_LOC_COLOR_AMBIENT,       // raylib_shader location: vector uniform: ambient color
    SHADER_LOC_MAP_ALBEDO,          // raylib_shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE)
    SHADER_LOC_MAP_METALNESS,       // raylib_shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR)
    SHADER_LOC_MAP_NORMAL,          // raylib_shader location: sampler2d texture: normal
    SHADER_LOC_MAP_ROUGHNESS,       // raylib_shader location: sampler2d texture: roughness
    SHADER_LOC_MAP_OCCLUSION,       // raylib_shader location: sampler2d texture: occlusion
    SHADER_LOC_MAP_EMISSION,        // raylib_shader location: sampler2d texture: emission
    SHADER_LOC_MAP_HEIGHT,          // raylib_shader location: sampler2d texture: height
    SHADER_LOC_MAP_CUBEMAP,         // raylib_shader location: samplerCube texture: cubemap
    SHADER_LOC_MAP_IRRADIANCE,      // raylib_shader location: samplerCube texture: irradiance
    SHADER_LOC_MAP_PREFILTER,       // raylib_shader location: samplerCube texture: prefilter
    SHADER_LOC_MAP_BRDF             // raylib_shader location: sampler2d texture: brdf
} raylib_shaderlocationindex;

#define SHADER_LOC_MAP_DIFFUSE      SHADER_LOC_MAP_ALBEDO
#define SHADER_LOC_MAP_SPECULAR     SHADER_LOC_MAP_METALNESS

// raylib_shader uniform data type
typedef enum {
    SHADER_UNIFORM_FLOAT = 0,       // raylib_shader uniform type: float
    SHADER_UNIFORM_VEC2,            // raylib_shader uniform type: vec2 (2 float)
    SHADER_UNIFORM_VEC3,            // raylib_shader uniform type: vec3 (3 float)
    SHADER_UNIFORM_VEC4,            // raylib_shader uniform type: vec4 (4 float)
    SHADER_UNIFORM_INT,             // raylib_shader uniform type: int
    SHADER_UNIFORM_IVEC2,           // raylib_shader uniform type: ivec2 (2 int)
    SHADER_UNIFORM_IVEC3,           // raylib_shader uniform type: ivec3 (3 int)
    SHADER_UNIFORM_IVEC4,           // raylib_shader uniform type: ivec4 (4 int)
    SHADER_UNIFORM_SAMPLER2D        // raylib_shader uniform type: sampler2d
} raylib_shaderuniformdatatype;

// raylib_shader attribute data types
typedef enum {
    SHADER_ATTRIB_FLOAT = 0,        // raylib_shader attribute type: float
    SHADER_ATTRIB_VEC2,             // raylib_shader attribute type: vec2 (2 float)
    SHADER_ATTRIB_VEC3,             // raylib_shader attribute type: vec3 (3 float)
    SHADER_ATTRIB_VEC4              // raylib_shader attribute type: vec4 (4 float)
} raylib_shaderattributedatatype;

// Pixel formats
// NOTE: Support depends on OpenGL version and platform
typedef enum {
    PIXELFORMAT_UNCOMPRESSED_GRAYSCALE = 1, // 8 bit per pixel (no alpha)
    PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA,    // 8*2 bpp (2 channels)
    PIXELFORMAT_UNCOMPRESSED_R5G6B5,        // 16 bpp
    PIXELFORMAT_UNCOMPRESSED_R8G8B8,        // 24 bpp
    PIXELFORMAT_UNCOMPRESSED_R5G5B5A1,      // 16 bpp (1 bit alpha)
    PIXELFORMAT_UNCOMPRESSED_R4G4B4A4,      // 16 bpp (4 bit alpha)
    PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,      // 32 bpp
    PIXELFORMAT_UNCOMPRESSED_R32,           // 32 bpp (1 channel - float)
    PIXELFORMAT_UNCOMPRESSED_R32G32B32,     // 32*3 bpp (3 channels - float)
    PIXELFORMAT_UNCOMPRESSED_R32G32B32A32,  // 32*4 bpp (4 channels - float)
    PIXELFORMAT_UNCOMPRESSED_R16,           // 16 bpp (1 channel - half float)
    PIXELFORMAT_UNCOMPRESSED_R16G16B16,     // 16*3 bpp (3 channels - half float)
    PIXELFORMAT_UNCOMPRESSED_R16G16B16A16,  // 16*4 bpp (4 channels - half float)
    PIXELFORMAT_COMPRESSED_DXT1_RGB,        // 4 bpp (no alpha)
    PIXELFORMAT_COMPRESSED_DXT1_RGBA,       // 4 bpp (1 bit alpha)
    PIXELFORMAT_COMPRESSED_DXT3_RGBA,       // 8 bpp
    PIXELFORMAT_COMPRESSED_DXT5_RGBA,       // 8 bpp
    PIXELFORMAT_COMPRESSED_ETC1_RGB,        // 4 bpp
    PIXELFORMAT_COMPRESSED_ETC2_RGB,        // 4 bpp
    PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA,   // 8 bpp
    PIXELFORMAT_COMPRESSED_PVRT_RGB,        // 4 bpp
    PIXELFORMAT_COMPRESSED_PVRT_RGBA,       // 4 bpp
    PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA,   // 8 bpp
    PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA    // 2 bpp
} raylib_pixelformat;

// raylib_texture parameters: filter mode
// NOTE 1: Filtering considers mipmaps if available in the texture
// NOTE 2: Filter is accordingly set for minification and magnification
typedef enum {
    TEXTURE_FILTER_POINT = 0,               // No filter, just pixel approximation
    TEXTURE_FILTER_BILINEAR,                // Linear filtering
    TEXTURE_FILTER_TRILINEAR,               // Trilinear filtering (linear with mipmaps)
    TEXTURE_FILTER_ANISOTROPIC_4X,          // Anisotropic filtering 4x
    TEXTURE_FILTER_ANISOTROPIC_8X,          // Anisotropic filtering 8x
    TEXTURE_FILTER_ANISOTROPIC_16X,         // Anisotropic filtering 16x
} raylib_texturefilter;

// raylib_texture parameters: wrap mode
typedef enum {
    TEXTURE_WRAP_REPEAT = 0,                // Repeats texture in tiled mode
    TEXTURE_WRAP_CLAMP,                     // Clamps texture to edge pixel in tiled mode
    TEXTURE_WRAP_MIRROR_REPEAT,             // Mirrors and repeats the texture in tiled mode
    TEXTURE_WRAP_MIRROR_CLAMP               // Mirrors and clamps to border the texture in tiled mode
} raylib_texturewrap;

// Cubemap layouts
typedef enum {
    CUBEMAP_LAYOUT_AUTO_DETECT = 0,         // Automatically detect layout type
    CUBEMAP_LAYOUT_LINE_VERTICAL,           // Layout is defined by a vertical line with faces
    CUBEMAP_LAYOUT_LINE_HORIZONTAL,         // Layout is defined by a horizontal line with faces
    CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR,     // Layout is defined by a 3x4 cross with cubemap faces
    CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE,     // Layout is defined by a 4x3 cross with cubemap faces
    CUBEMAP_LAYOUT_PANORAMA                 // Layout is defined by a panorama image (equirrectangular map)
} raylib_cubemaplayout;

// raylib_font type, defines generation method
typedef enum {
    FONT_DEFAULT = 0,               // Default font generation, anti-aliased
    FONT_BITMAP,                    // Bitmap font generation, no anti-aliasing
    FONT_SDF                        // SDF font generation, requires external shader
} raylib_fonttype;

// raylib_color blending modes (pre-defined)
typedef enum {
    BLEND_ALPHA = 0,                // Blend textures considering alpha (default)
    BLEND_ADDITIVE,                 // Blend textures adding colors
    BLEND_MULTIPLIED,               // Blend textures multiplying colors
    BLEND_ADD_COLORS,               // Blend textures adding colors (alternative)
    BLEND_SUBTRACT_COLORS,          // Blend textures subtracting colors (alternative)
    BLEND_ALPHA_PREMULTIPLY,        // Blend premultiplied textures considering alpha
    BLEND_CUSTOM,                   // Blend textures using custom src/dst factors (use rlSetBlendFactors())
    BLEND_CUSTOM_SEPARATE           // Blend textures using custom rgb/alpha separate src/dst factors (use rlSetBlendFactorsSeparate())
} raylib_blendmode;

// raylib_gesture
// NOTE: Provided as bit-wise flags to enable only desired gestures
typedef enum {
    GESTURE_NONE        = 0,        // No gesture
    GESTURE_TAP         = 1,        // Tap gesture
    GESTURE_DOUBLETAP   = 2,        // Double tap gesture
    GESTURE_HOLD        = 4,        // Hold gesture
    GESTURE_DRAG        = 8,        // Drag gesture
    GESTURE_SWIPE_RIGHT = 16,       // Swipe right gesture
    GESTURE_SWIPE_LEFT  = 32,       // Swipe left gesture
    GESTURE_SWIPE_UP    = 64,       // Swipe up gesture
    GESTURE_SWIPE_DOWN  = 128,      // Swipe down gesture
    GESTURE_PINCH_IN    = 256,      // Pinch in gesture
    GESTURE_PINCH_OUT   = 512       // Pinch out gesture
} raylib_gesture;

// raylib_camera system modes
typedef enum {
    CAMERA_CUSTOM = 0,              // raylib_camera custom, controlled by user (raylib_updatecamera() does nothing)
    CAMERA_FREE,                    // raylib_camera free mode
    CAMERA_ORBITAL,                 // raylib_camera orbital, around target, zoom supported
    CAMERA_FIRST_PERSON,            // raylib_camera first person
    CAMERA_THIRD_PERSON             // raylib_camera third person
} raylib_cameramode;

// raylib_camera projection
typedef enum {
    CAMERA_PERSPECTIVE = 0,         // Perspective projection
    CAMERA_ORTHOGRAPHIC             // Orthographic projection
} raylib_cameraprojection;

// N-patch layout
typedef enum {
    NPATCH_NINE_PATCH = 0,          // Npatch layout: 3x3 tiles
    NPATCH_THREE_PATCH_VERTICAL,    // Npatch layout: 1x3 tiles
    NPATCH_THREE_PATCH_HORIZONTAL   // Npatch layout: 3x1 tiles
} raylib_npatchlayout;

// Callbacks to hook some internal functions
// WARNING: These callbacks are intended for advanced users
typedef void (*raylib_tracelogcallback)(int logLevel, const char *text, va_list args);  // Logging: Redirect trace log messages
typedef unsigned char *(*raylib_loadfiledatacallback)(const char *fileName, int *dataSize);    // FileIO: Load binary data
typedef bool (*raylib_savefiledatacallback)(const char *fileName, void *data, int dataSize);   // FileIO: Save binary data
typedef char *(*raylib_loadfiletextcallback)(const char *fileName);            // FileIO: Load text data
typedef bool (*raylib_savefiletextcallback)(const char *fileName, char *text); // FileIO: Save text data

//------------------------------------------------------------------------------------
// Global Variables Definition
//------------------------------------------------------------------------------------
// It's lonely here...

//------------------------------------------------------------------------------------
// Window and Graphics Device Functions (Module: core)
//------------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C" {            // Prevents name mangling of functions
#endif

// Window-related functions
RLAPI void raylib_initwindow(int width, int height, const char *title);  // Initialize window and OpenGL context
RLAPI void raylib_closewindow(void);                                     // Close window and unload OpenGL context
RLAPI bool raylib_windowshouldclose(void);                               // Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
RLAPI bool raylib_iswindowready(void);                                   // Check if window has been initialized successfully
RLAPI bool raylib_iswindowfullscreen(void);                              // Check if window is currently fullscreen
RLAPI bool raylib_iswindowhidden(void);                                  // Check if window is currently hidden (only PLATFORM_DESKTOP)
RLAPI bool raylib_iswindowminimized(void);                               // Check if window is currently minimized (only PLATFORM_DESKTOP)
RLAPI bool raylib_iswindowmaximized(void);                               // Check if window is currently maximized (only PLATFORM_DESKTOP)
RLAPI bool raylib_iswindowfocused(void);                                 // Check if window is currently focused (only PLATFORM_DESKTOP)
RLAPI bool raylib_iswindowresized(void);                                 // Check if window has been resized last frame
RLAPI bool raylib_iswindowstate(unsigned int flag);                      // Check if one specific window flag is enabled
RLAPI void raylib_setwindowstate(unsigned int flags);                    // Set window configuration state using flags (only PLATFORM_DESKTOP)
RLAPI void raylib_clearwindowstate(unsigned int flags);                  // Clear window configuration state flags
RLAPI void raylib_togglefullscreen(void);                                // Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
RLAPI void raylib_toggleborderlesswindowed(void);                        // Toggle window state: borderless windowed (only PLATFORM_DESKTOP)
RLAPI void raylib_maximizewindow(void);                                  // Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
RLAPI void raylib_minimizewindow(void);                                  // Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
RLAPI void raylib_restorewindow(void);                                   // Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
RLAPI void raylib_setwindowicon(raylib_image image);                            // Set icon for window (single image, RGBA 32bit, only PLATFORM_DESKTOP)
RLAPI void raylib_setwindowicons(raylib_image *images, int count);              // Set icon for window (multiple images, RGBA 32bit, only PLATFORM_DESKTOP)
RLAPI void raylib_setwindowtitle(const char *title);                     // Set title for window (only PLATFORM_DESKTOP and PLATFORM_WEB)
RLAPI void raylib_setwindowposition(int x, int y);                       // Set window position on screen (only PLATFORM_DESKTOP)
RLAPI void raylib_setwindowmonitor(int monitor);                         // Set monitor for the current window
RLAPI void raylib_setwindowminsize(int width, int height);               // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
RLAPI void raylib_setwindowmaxsize(int width, int height);               // Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)
RLAPI void raylib_setwindowsize(int width, int height);                  // Set window dimensions
RLAPI void raylib_setwindowopacity(float opacity);                       // Set window opacity [0.0f..1.0f] (only PLATFORM_DESKTOP)
RLAPI void raylib_setwindowfocused(void);                                // Set window focused (only PLATFORM_DESKTOP)
RLAPI void *GetWindowHandle(void);                                // Get native window handle
RLAPI int raylib_getscreenwidth(void);                                   // Get current screen width
RLAPI int raylib_getscreenheight(void);                                  // Get current screen height
RLAPI int raylib_getrenderwidth(void);                                   // Get current render width (it considers HiDPI)
RLAPI int raylib_getrenderheight(void);                                  // Get current render height (it considers HiDPI)
RLAPI int raylib_getmonitorcount(void);                                  // Get number of connected monitors
RLAPI int raylib_getcurrentmonitor(void);                                // Get current connected monitor
RLAPI raylib_vector2 raylib_getmonitorposition(int monitor);                    // Get specified monitor position
RLAPI int raylib_getmonitorwidth(int monitor);                           // Get specified monitor width (current video mode used by monitor)
RLAPI int raylib_getmonitorheight(int monitor);                          // Get specified monitor height (current video mode used by monitor)
RLAPI int raylib_getmonitorphysicalwidth(int monitor);                   // Get specified monitor physical width in millimetres
RLAPI int raylib_getmonitorphysicalheight(int monitor);                  // Get specified monitor physical height in millimetres
RLAPI int raylib_getmonitorrefreshrate(int monitor);                     // Get specified monitor refresh rate
RLAPI raylib_vector2 raylib_getwindowposition(void);                            // Get window position XY on monitor
RLAPI raylib_vector2 raylib_getwindowscaledpi(void);                            // Get window scale DPI factor
RLAPI const char *raylib_getmonitorname(int monitor);                    // Get the human-readable, UTF-8 encoded name of the specified monitor
RLAPI void raylib_setclipboardtext(const char *text);                    // Set clipboard text content
RLAPI const char *raylib_getclipboardtext(void);                         // Get clipboard text content
RLAPI void raylib_enableeventwaiting(void);                              // Enable waiting for events on raylib_enddrawing(), no automatic event polling
RLAPI void raylib_disableeventwaiting(void);                             // Disable waiting for events on raylib_enddrawing(), automatic events polling

// Cursor-related functions
RLAPI void raylib_show_cursor(void);                                      // Shows cursor
RLAPI void raylib_hidecursor(void);                                      // Hides cursor
RLAPI bool raylib_iscursorhidden(void);                                  // Check if cursor is not visible
RLAPI void raylib_enablecursor(void);                                    // Enables cursor (unlock cursor)
RLAPI void raylib_disablecursor(void);                                   // Disables cursor (lock cursor)
RLAPI bool raylib_iscursoronscreen(void);                                // Check if cursor is on the screen

// Drawing-related functions
RLAPI void raylib_clearbackground(raylib_color color);                          // Set background color (framebuffer clear color)
RLAPI void raylib_begindrawing(void);                                    // Setup canvas (framebuffer) to start drawing
RLAPI void raylib_enddrawing(void);                                      // End canvas drawing and swap buffers (double buffering)
RLAPI void raylib_beginmode2d(raylib_camera2d camera);                          // Begin 2D mode with custom camera (2D)
RLAPI void raylib_endmode2d(void);                                       // Ends 2D mode with custom camera
RLAPI void raylib_beginmode3d(raylib_camera3d camera);                          // Begin 3D mode with custom camera (3D)
RLAPI void raylib_endmode3d(void);                                       // Ends 3D mode and returns to default 2D orthographic mode
RLAPI void raylib_begintexturemode(raylib_rendertexture2d target);              // Begin drawing to render texture
RLAPI void raylib_endtexturemode(void);                                  // Ends drawing to render texture
RLAPI void raylib_beginshadermode(raylib_shader shader);                        // Begin custom shader drawing
RLAPI void raylib_endshadermode(void);                                   // End custom shader drawing (use default shader)
RLAPI void raylib_beginblendmode(int mode);                              // Begin blending mode (alpha, additive, multiplied, subtract, custom)
RLAPI void raylib_endblendmode(void);                                    // End blending mode (reset to default: alpha blending)
RLAPI void raylib_beginscissormode(int x, int y, int width, int height); // Begin scissor mode (define screen area for following drawing)
RLAPI void raylib_endscissormode(void);                                  // End scissor mode
RLAPI void raylib_beginvrstereomode(raylib_vrstereoconfig config);              // Begin stereo rendering (requires VR simulator)
RLAPI void raylib_endvrstereomode(void);                                 // End stereo rendering (requires VR simulator)

// VR stereo config functions for VR simulator
RLAPI raylib_vrstereoconfig raylib_loadvrstereoconfig(raylib_vrdeviceinfo device);     // Load VR stereo config for VR simulator device parameters
RLAPI void raylib_unloadvrstereoconfig(raylib_vrstereoconfig config);           // Unload VR stereo config

// raylib_shader management functions
// NOTE: raylib_shader functionality is not available on OpenGL 1.1
RLAPI raylib_shader raylib_loadshader(const char *vsFileName, const char *fsFileName);   // Load shader from files and bind default locations
RLAPI raylib_shader raylib_loadshaderfrommemory(const char *vsCode, const char *fsCode); // Load shader from code strings and bind default locations
RLAPI bool raylib_isshaderready(raylib_shader shader);                                   // Check if a shader is ready
RLAPI int raylib_getshaderlocation(raylib_shader shader, const char *uniformName);       // Get shader uniform location
RLAPI int raylib_getshaderlocationattrib(raylib_shader shader, const char *attribName);  // Get shader attribute location
RLAPI void raylib_setshadervalue(raylib_shader shader, int locIndex, const void *value, int uniformType);               // Set shader uniform value
RLAPI void raylib_setshadervaluev(raylib_shader shader, int locIndex, const void *value, int uniformType, int count);   // Set shader uniform value vector
RLAPI void raylib_setshadervaluematrix(raylib_shader shader, int locIndex, raylib_matrix mat);         // Set shader uniform value (matrix 4x4)
RLAPI void raylib_setshadervaluetexture(raylib_shader shader, int locIndex, raylib_texture2d texture); // Set shader uniform value for texture (sampler2d)
RLAPI void raylib_unloadshader(raylib_shader shader);                                    // Unload shader from GPU memory (VRAM)

// Screen-space-related functions
#define raylib_getmouseray raylib_getscreentoworldray     // Compatibility hack for previous raylib versions
RLAPI raylib_ray raylib_getscreentoworldray(raylib_vector2 position, raylib_camera camera);         // Get a ray trace from screen position (i.e mouse)
RLAPI raylib_ray raylib_getscreentoworldrayex(raylib_vector2 position, raylib_camera camera, int width, int height); // Get a ray trace from screen position (i.e mouse) in a viewport
RLAPI raylib_vector2 raylib_getworldtoscreen(raylib_vector3 position, raylib_camera camera);        // Get the screen space position for a 3d world space position
RLAPI raylib_vector2 raylib_getworldtoscreenex(raylib_vector3 position, raylib_camera camera, int width, int height); // Get size position for a 3d world space position
RLAPI raylib_vector2 raylib_getworldtoscreen2d(raylib_vector2 position, raylib_camera2d camera);    // Get the screen space position for a 2d camera world space position
RLAPI raylib_vector2 raylib_getscreentoworld2d(raylib_vector2 position, raylib_camera2d camera);    // Get the world space position for a 2d camera screen space position
RLAPI raylib_matrix raylib_getcameramatrix(raylib_camera camera);                            // Get camera transform matrix (view matrix)
RLAPI raylib_matrix raylib_getcameramatrix2d(raylib_camera2d camera);                        // Get camera 2d transform matrix

// Timing-related functions
RLAPI void raylib_settargetfps(int fps);                                 // Set target FPS (maximum)
RLAPI float raylib_getframetime(void);                                   // Get time in seconds for last frame drawn (delta time)
RLAPI double raylib_gettime(void);                                       // Get elapsed time in seconds since raylib_initwindow()
RLAPI int raylib_getfps(void);                                           // Get current FPS

// Custom frame control functions
// NOTE: Those functions are intended for advanced users that want full control over the frame processing
// By default raylib_enddrawing() does this job: draws everything + raylib_swapscreenbuffer() + manage frame timing + raylib_pollinputevents()
// To avoid that behaviour and control frame processes manually, enable in config.h: SUPPORT_CUSTOM_FRAME_CONTROL
RLAPI void raylib_swapscreenbuffer(void);                                // Swap back buffer with front buffer (screen drawing)
RLAPI void raylib_pollinputevents(void);                                 // Register all input events
RLAPI void raylib_waittime(double seconds);                              // Wait for some time (halt program execution)

// Random values generation functions
RLAPI void raylib_setrandomseed(unsigned int seed);                      // Set the seed for the random number generator
RLAPI int raylib_getrandomvalue(int min, int max);                       // Get a random value between min and max (both included)
RLAPI int *raylib_loadrandomsequence(unsigned int count, int min, int max); // Load random values sequence, no values repeated
RLAPI void raylib_unloadrandomsequence(int *sequence);                   // Unload random values sequence

// Misc. functions
RLAPI void raylib_takescreenshot(const char *fileName);                  // Takes a screenshot of current screen (filename extension defines format)
RLAPI void raylib_setconfigflags(unsigned int flags);                    // Setup init configuration flags (view FLAGS)
RLAPI void raylib_openurl(const char *url);                              // Open URL with default system browser (if available)

// NOTE: Following functions implemented in module [utils]
//------------------------------------------------------------------
RLAPI void raylib_tracelog(int logLevel, const char *text, ...);         // Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
RLAPI void raylib_settraceloglevel(int logLevel);                        // Set the current threshold (minimum) log level
RLAPI void *raylib_memalloc(unsigned int size);                          // Internal memory allocator
RLAPI void *raylib_memrealloc(void *ptr, unsigned int size);             // Internal memory reallocator
RLAPI void raylib_memfree(void *ptr);                                    // Internal memory free

// Set custom callbacks
// WARNING: Callbacks setup is intended for advanced users
RLAPI void raylib_settracelogcallback(raylib_tracelogcallback callback);         // Set custom trace log
RLAPI void raylib_setloadfiledatacallback(raylib_loadfiledatacallback callback); // Set custom file binary data loader
RLAPI void raylib_setsavefiledatacallback(raylib_savefiledatacallback callback); // Set custom file binary data saver
RLAPI void raylib_setloadfiletextcallback(raylib_loadfiletextcallback callback); // Set custom file text data loader
RLAPI void raylib_setsavefiletextcallback(raylib_savefiletextcallback callback); // Set custom file text data saver

// Files management functions
RLAPI unsigned char *raylib_loadfiledata(const char *fileName, int *dataSize); // Load file data as byte array (read)
RLAPI void raylib_unloadfiledata(unsigned char *data);                   // Unload file data allocated by raylib_loadfiledata()
RLAPI bool raylib_savefiledata(const char *fileName, void *data, int dataSize); // Save data to file from byte array (write), returns true on success
RLAPI bool raylib_exportdataascode(const unsigned char *data, int dataSize, const char *fileName); // Export data to code (.h), returns true on success
RLAPI char *raylib_loadfiletext(const char *fileName);                   // Load text data from file (read), returns a '\0' terminated string
RLAPI void raylib_unloadfiletext(char *text);                            // Unload file text data allocated by raylib_loadfiletext()
RLAPI bool raylib_savefiletext(const char *fileName, char *text);        // Save text data to file (write), string must be '\0' terminated, returns true on success
//------------------------------------------------------------------

// File system functions
RLAPI bool raylib_fileexists(const char *fileName);                      // Check if file exists
RLAPI bool raylib_directoryexists(const char *dirPath);                  // Check if a directory path exists
RLAPI bool raylib_isfileextension(const char *fileName, const char *ext); // Check file extension (including point: .png, .wav)
RLAPI int raylib_getfilelength(const char *fileName);                    // Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
RLAPI const char *raylib_getfileextension(const char *fileName);         // Get pointer to extension for a filename string (includes dot: '.png')
RLAPI const char *raylib_getfilename(const char *filePath);              // Get pointer to filename for a path string
RLAPI const char *raylib_getfilenamewithoutext(const char *filePath);    // Get filename string without extension (uses static string)
RLAPI const char *raylib_getdirectorypath(const char *filePath);         // Get full path for a given fileName with path (uses static string)
RLAPI const char *raylib_getprevdirectorypath(const char *dirPath);      // Get previous directory path for a given path (uses static string)
RLAPI const char *raylib_getworkingdirectory(void);                      // Get current working directory (uses static string)
RLAPI const char *raylib_getapplicationdirectory(void);                  // Get the directory of the running application (uses static string)
RLAPI bool raylib_changedirectory(const char *dir);                      // Change working directory, return true on success
RLAPI bool raylib_ispathfile(const char *path);                          // Check if a given path is a file or a directory
RLAPI bool raylib_isfilenamevalid(const char *fileName);                 // Check if fileName is valid for the platform/OS
RLAPI raylib_filepathlist raylib_loaddirectoryfiles(const char *dirPath);       // Load directory filepaths
RLAPI raylib_filepathlist raylib_loaddirectoryfilesex(const char *basePath, const char *filter, bool scanSubdirs); // Load directory filepaths with extension filtering and recursive directory scan
RLAPI void raylib_unloaddirectoryfiles(raylib_filepathlist files);              // Unload filepaths
RLAPI bool raylib_isfiledropped(void);                                   // Check if a file has been dropped into window
RLAPI raylib_filepathlist raylib_loaddroppedfiles(void);                        // Load dropped filepaths
RLAPI void raylib_unloaddroppedfiles(raylib_filepathlist files);                // Unload dropped filepaths
RLAPI long raylib_getfilemodtime(const char *fileName);                  // Get file modification time (last write time)

// Compression/Encoding functionality
RLAPI unsigned char *raylib_compressdata(const unsigned char *data, int dataSize, int *compDataSize);        // Compress data (DEFLATE algorithm), memory must be raylib_memfree()
RLAPI unsigned char *raylib_decompressdata(const unsigned char *compData, int compDataSize, int *dataSize);  // Decompress data (DEFLATE algorithm), memory must be raylib_memfree()
RLAPI char *raylib_encodedatabase64(const unsigned char *data, int dataSize, int *outputSize);               // Encode data to Base64 string, memory must be raylib_memfree()
RLAPI unsigned char *raylib_decodedatabase64(const unsigned char *data, int *outputSize);                    // Decode Base64 string data, memory must be raylib_memfree()

// Automation events functionality
RLAPI raylib_automationeventlist raylib_loadautomationeventlist(const char *fileName);                // Load automation events list from file, NULL for empty list, capacity = MAX_AUTOMATION_EVENTS
RLAPI void raylib_unloadautomationeventlist(raylib_automationeventlist list);                         // Unload automation events list from file
RLAPI bool raylib_exportautomationeventlist(raylib_automationeventlist list, const char *fileName);   // Export automation events list as text file
RLAPI void raylib_setautomationeventlist(raylib_automationeventlist *list);                           // Set automation event list to record to
RLAPI void raylib_setautomationeventbaseframe(int frame);                                      // Set automation event internal base frame to start recording
RLAPI void raylib_startautomationeventrecording(void);                                         // Start recording automation events (raylib_automationeventlist must be set)
RLAPI void raylib_stopautomationeventrecording(void);                                          // Stop recording automation events
RLAPI void raylib_playautomationevent(raylib_automationevent event);                                  // Play a recorded automation event

//------------------------------------------------------------------------------------
// Input Handling Functions (Module: core)
//------------------------------------------------------------------------------------

// Input-related functions: keyboard
RLAPI bool raylib_iskeypressed(int key);                             // Check if a key has been pressed once
RLAPI bool raylib_iskeypressedrepeat(int key);                       // Check if a key has been pressed again (Only PLATFORM_DESKTOP)
RLAPI bool raylib_iskeydown(int key);                                // Check if a key is being pressed
RLAPI bool raylib_iskeyreleased(int key);                            // Check if a key has been released once
RLAPI bool raylib_iskeyup(int key);                                  // Check if a key is NOT being pressed
RLAPI int raylib_getkeypressed(void);                                // Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
RLAPI int raylib_getcharpressed(void);                               // Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
RLAPI void raylib_setexitkey(int key);                               // Set a custom key to exit program (default is ESC)

// Input-related functions: gamepads
RLAPI bool raylib_isgamepadavailable(int gamepad);                                        // Check if a gamepad is available
RLAPI const char *raylib_getgamepadname(int gamepad);                                     // Get gamepad internal name id
RLAPI bool raylib_isgamepadbuttonpressed(int gamepad, int button);                        // Check if a gamepad button has been pressed once
RLAPI bool raylib_isgamepadbuttondown(int gamepad, int button);                           // Check if a gamepad button is being pressed
RLAPI bool raylib_isgamepadbuttonreleased(int gamepad, int button);                       // Check if a gamepad button has been released once
RLAPI bool raylib_isgamepadbuttonup(int gamepad, int button);                             // Check if a gamepad button is NOT being pressed
RLAPI int raylib_getgamepadbuttonpressed(void);                                           // Get the last gamepad button pressed
RLAPI int raylib_getgamepadaxiscount(int gamepad);                                        // Get gamepad axis count for a gamepad
RLAPI float raylib_getgamepadaxismovement(int gamepad, int axis);                         // Get axis movement value for a gamepad axis
RLAPI int raylib_setgamepadmappings(const char *mappings);                                // Set internal gamepad mappings (SDL_GameControllerDB)
RLAPI void raylib_setgamepadvibration(int gamepad, float leftMotor, float rightMotor);    // Set gamepad vibration for both motors

// Input-related functions: mouse
RLAPI bool raylib_ismousebuttonpressed(int button);                  // Check if a mouse button has been pressed once
RLAPI bool raylib_ismousebuttondown(int button);                     // Check if a mouse button is being pressed
RLAPI bool raylib_ismousebuttonreleased(int button);                 // Check if a mouse button has been released once
RLAPI bool raylib_ismousebuttonup(int button);                       // Check if a mouse button is NOT being pressed
RLAPI int raylib_getmousex(void);                                    // Get mouse position X
RLAPI int raylib_getmousey(void);                                    // Get mouse position Y
RLAPI raylib_vector2 raylib_getmouseposition(void);                         // Get mouse position XY
RLAPI raylib_vector2 raylib_getmousedelta(void);                            // Get mouse delta between frames
RLAPI void raylib_setmouseposition(int x, int y);                    // Set mouse position XY
RLAPI void raylib_setmouseoffset(int offsetX, int offsetY);          // Set mouse offset
RLAPI void raylib_setmousescale(float scaleX, float scaleY);         // Set mouse scaling
RLAPI float raylib_getmousewheelmove(void);                          // Get mouse wheel movement for X or Y, whichever is larger
RLAPI raylib_vector2 raylib_getmousewheelmovev(void);                       // Get mouse wheel movement for both X and Y
RLAPI void raylib_setmousecursor(int cursor);                        // Set mouse cursor

// Input-related functions: touch
RLAPI int raylib_gettouchx(void);                                    // Get touch position X for touch point 0 (relative to screen size)
RLAPI int raylib_gettouchy(void);                                    // Get touch position Y for touch point 0 (relative to screen size)
RLAPI raylib_vector2 raylib_gettouchposition(int index);                    // Get touch position XY for a touch point index (relative to screen size)
RLAPI int raylib_gettouchpointid(int index);                         // Get touch point identifier for given index
RLAPI int raylib_gettouchpointcount(void);                           // Get number of touch points

//------------------------------------------------------------------------------------
// Gestures and Touch Handling Functions (Module: rgestures)
//------------------------------------------------------------------------------------
RLAPI void raylib_setgesturesenabled(unsigned int flags);      // Enable a set of gestures using flags
RLAPI bool raylib_isgesturedetected(unsigned int gesture);     // Check if a gesture have been detected
RLAPI int raylib_getgesturedetected(void);                     // Get latest detected gesture
RLAPI float raylib_getgestureholdduration(void);               // Get gesture hold time in milliseconds
RLAPI raylib_vector2 raylib_getgesturedragvector(void);               // Get gesture drag vector
RLAPI float raylib_getgesturedragangle(void);                  // Get gesture drag angle
RLAPI raylib_vector2 raylib_getgesturepinchvector(void);              // Get gesture pinch delta
RLAPI float raylib_getgesturepinchangle(void);                 // Get gesture pinch angle

//------------------------------------------------------------------------------------
// raylib_camera System Functions (Module: rcamera)
//------------------------------------------------------------------------------------
RLAPI void raylib_updatecamera(raylib_camera *camera, int mode);      // Update camera position for selected mode
RLAPI void raylib_updatecamerapro(raylib_camera *camera, raylib_vector3 movement, raylib_vector3 rotation, float zoom); // Update camera movement/rotation

//------------------------------------------------------------------------------------
// Basic Shapes Drawing Functions (Module: shapes)
//------------------------------------------------------------------------------------
// Set texture and rectangle to be used on shapes drawing
// NOTE: It can be useful when using basic shapes and one single font,
// defining a font char white rectangle would allow drawing everything in a single draw call
RLAPI void raylib_setshapestexture(raylib_texture2d texture, raylib_rectangle source);       // Set texture and rectangle to be used on shapes drawing
RLAPI raylib_texture2d raylib_getshapestexture(void);                                 // Get texture that is used for shapes drawing
RLAPI raylib_rectangle raylib_getshapestexturerectangle(void);                        // Get texture source rectangle that is used for shapes drawing

// Basic shapes drawing functions
RLAPI void raylib_drawpixel(int posX, int posY, raylib_color color);                                                   // Draw a pixel
RLAPI void raylib_drawpixelv(raylib_vector2 position, raylib_color color);                                                    // Draw a pixel (Vector version)
RLAPI void raylib_drawline(int startPosX, int startPosY, int endPosX, int endPosY, raylib_color color);                // Draw a line
RLAPI void raylib_drawlinev(raylib_vector2 startPos, raylib_vector2 endPos, raylib_color color);                                     // Draw a line (using gl lines)
RLAPI void raylib_drawlineex(raylib_vector2 startPos, raylib_vector2 endPos, float thick, raylib_color color);                       // Draw a line (using triangles/quads)
RLAPI void raylib_drawlinestrip(const raylib_vector2 *points, int pointCount, raylib_color color);                            // Draw lines sequence (using gl lines)
RLAPI void raylib_drawlinebezier(raylib_vector2 startPos, raylib_vector2 endPos, float thick, raylib_color color);                   // Draw line segment cubic-bezier in-out interpolation
RLAPI void raylib_drawcircle(int centerX, int centerY, float radius, raylib_color color);                              // Draw a color-filled circle
RLAPI void raylib_drawcirclesector(raylib_vector2 center, float radius, float startAngle, float endAngle, int segments, raylib_color color);      // Draw a piece of a circle
RLAPI void raylib_drawcirclesectorlines(raylib_vector2 center, float radius, float startAngle, float endAngle, int segments, raylib_color color); // Draw circle sector outline
RLAPI void raylib_drawcirclegradient(int centerX, int centerY, float radius, raylib_color color1, raylib_color color2);       // Draw a gradient-filled circle
RLAPI void raylib_drawcirclev(raylib_vector2 center, float radius, raylib_color color);                                       // Draw a color-filled circle (Vector version)
RLAPI void raylib_drawcirclelines(int centerX, int centerY, float radius, raylib_color color);                         // Draw circle outline
RLAPI void raylib_drawcirclelinesv(raylib_vector2 center, float radius, raylib_color color);                                  // Draw circle outline (Vector version)
RLAPI void raylib_drawellipse(int centerX, int centerY, float radiusH, float radiusV, raylib_color color);             // Draw ellipse
RLAPI void raylib_drawellipselines(int centerX, int centerY, float radiusH, float radiusV, raylib_color color);        // Draw ellipse outline
RLAPI void raylib_drawring(raylib_vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, raylib_color color); // Draw ring
RLAPI void raylib_drawringlines(raylib_vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, raylib_color color);    // Draw ring outline
RLAPI void raylib_drawrectangle(int posX, int posY, int width, int height, raylib_color color);                        // Draw a color-filled rectangle
RLAPI void raylib_drawrectanglev(raylib_vector2 position, raylib_vector2 size, raylib_color color);                                  // Draw a color-filled rectangle (Vector version)
RLAPI void raylib_drawrectanglerec(raylib_rectangle rec, raylib_color color);                                                 // Draw a color-filled rectangle
RLAPI void raylib_drawrectanglepro(raylib_rectangle rec, raylib_vector2 origin, float rotation, raylib_color color);                 // Draw a color-filled rectangle with pro parameters
RLAPI void raylib_drawrectanglegradientv(int posX, int posY, int width, int height, raylib_color color1, raylib_color color2);// Draw a vertical-gradient-filled rectangle
RLAPI void raylib_drawrectanglegradienth(int posX, int posY, int width, int height, raylib_color color1, raylib_color color2);// Draw a horizontal-gradient-filled rectangle
RLAPI void raylib_drawrectanglegradientex(raylib_rectangle rec, raylib_color col1, raylib_color col2, raylib_color col3, raylib_color col4);       // Draw a gradient-filled rectangle with custom vertex colors
RLAPI void raylib_drawrectanglelines(int posX, int posY, int width, int height, raylib_color color);                   // Draw rectangle outline
RLAPI void raylib_drawrectanglelinesex(raylib_rectangle rec, float lineThick, raylib_color color);                            // Draw rectangle outline with extended parameters
RLAPI void raylib_drawrectanglerounded(raylib_rectangle rec, float roundness, int segments, raylib_color color);              // Draw rectangle with rounded edges
RLAPI void raylib_drawrectangleroundedlines(raylib_rectangle rec, float roundness, int segments, raylib_color color);         // Draw rectangle lines with rounded edges
RLAPI void raylib_drawrectangleroundedlinesex(raylib_rectangle rec, float roundness, int segments, float lineThick, raylib_color color); // Draw rectangle with rounded edges outline
RLAPI void raylib_drawtriangle(raylib_vector2 v1, raylib_vector2 v2, raylib_vector2 v3, raylib_color color);                                // Draw a color-filled triangle (vertex in counter-clockwise order!)
RLAPI void raylib_drawtrianglelines(raylib_vector2 v1, raylib_vector2 v2, raylib_vector2 v3, raylib_color color);                           // Draw triangle outline (vertex in counter-clockwise order!)
RLAPI void raylib_drawtrianglefan(const raylib_vector2 *points, int pointCount, raylib_color color);                          // Draw a triangle fan defined by points (first vertex is the center)
RLAPI void raylib_drawtrianglestrip(const raylib_vector2 *points, int pointCount, raylib_color color);                        // Draw a triangle strip defined by points
RLAPI void raylib_drawpoly(raylib_vector2 center, int sides, float radius, float rotation, raylib_color color);               // Draw a regular polygon (Vector version)
RLAPI void raylib_drawpolylines(raylib_vector2 center, int sides, float radius, float rotation, raylib_color color);          // Draw a polygon outline of n sides
RLAPI void raylib_drawpolylinesex(raylib_vector2 center, int sides, float radius, float rotation, float lineThick, raylib_color color); // Draw a polygon outline of n sides with extended parameters

// Splines drawing functions
RLAPI void raylib_drawsplinelinear(const raylib_vector2 *points, int pointCount, float thick, raylib_color color);                  // Draw spline: Linear, minimum 2 points
RLAPI void raylib_drawsplinebasis(const raylib_vector2 *points, int pointCount, float thick, raylib_color color);                   // Draw spline: B-Spline, minimum 4 points
RLAPI void raylib_drawsplinecatmullrom(const raylib_vector2 *points, int pointCount, float thick, raylib_color color);              // Draw spline: Catmull-Rom, minimum 4 points
RLAPI void raylib_drawsplinebezierquadratic(const raylib_vector2 *points, int pointCount, float thick, raylib_color color);         // Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]
RLAPI void raylib_drawsplinebeziercubic(const raylib_vector2 *points, int pointCount, float thick, raylib_color color);             // Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]
RLAPI void raylib_drawsplinesegmentlinear(raylib_vector2 p1, raylib_vector2 p2, float thick, raylib_color color);                    // Draw spline segment: Linear, 2 points
RLAPI void raylib_drawsplinesegmentbasis(raylib_vector2 p1, raylib_vector2 p2, raylib_vector2 p3, raylib_vector2 p4, float thick, raylib_color color); // Draw spline segment: B-Spline, 4 points
RLAPI void raylib_drawsplinesegmentcatmullrom(raylib_vector2 p1, raylib_vector2 p2, raylib_vector2 p3, raylib_vector2 p4, float thick, raylib_color color); // Draw spline segment: Catmull-Rom, 4 points
RLAPI void raylib_drawsplinesegmentbezierquadratic(raylib_vector2 p1, raylib_vector2 c2, raylib_vector2 p3, float thick, raylib_color color); // Draw spline segment: Quadratic Bezier, 2 points, 1 control point
RLAPI void raylib_drawsplinesegmentbeziercubic(raylib_vector2 p1, raylib_vector2 c2, raylib_vector2 c3, raylib_vector2 p4, float thick, raylib_color color); // Draw spline segment: Cubic Bezier, 2 points, 2 control points

// Spline segment point evaluation functions, for a given t [0.0f .. 1.0f]
RLAPI raylib_vector2 raylib_getsplinepointlinear(raylib_vector2 startPos, raylib_vector2 endPos, float t);                           // Get (evaluate) spline point: Linear
RLAPI raylib_vector2 raylib_getsplinepointbasis(raylib_vector2 p1, raylib_vector2 p2, raylib_vector2 p3, raylib_vector2 p4, float t);              // Get (evaluate) spline point: B-Spline
RLAPI raylib_vector2 raylib_getsplinepointcatmullrom(raylib_vector2 p1, raylib_vector2 p2, raylib_vector2 p3, raylib_vector2 p4, float t);         // Get (evaluate) spline point: Catmull-Rom
RLAPI raylib_vector2 raylib_getsplinepointbezierquad(raylib_vector2 p1, raylib_vector2 c2, raylib_vector2 p3, float t);                     // Get (evaluate) spline point: Quadratic Bezier
RLAPI raylib_vector2 raylib_getsplinepointbeziercubic(raylib_vector2 p1, raylib_vector2 c2, raylib_vector2 c3, raylib_vector2 p4, float t);        // Get (evaluate) spline point: Cubic Bezier

// Basic shapes collision detection functions
RLAPI bool raylib_checkcollisionrecs(raylib_rectangle rec1, raylib_rectangle rec2);                                           // Check collision between two rectangles
RLAPI bool raylib_checkcollisioncircles(raylib_vector2 center1, float radius1, raylib_vector2 center2, float radius2);        // Check collision between two circles
RLAPI bool raylib_checkcollisioncirclerec(raylib_vector2 center, float radius, raylib_rectangle rec);                         // Check collision between circle and rectangle
RLAPI bool raylib_checkcollisionpointrec(raylib_vector2 point, raylib_rectangle rec);                                         // Check if point is inside rectangle
RLAPI bool raylib_checkcollisionpointcircle(raylib_vector2 point, raylib_vector2 center, float radius);                       // Check if point is inside circle
RLAPI bool raylib_checkcollisionpointtriangle(raylib_vector2 point, raylib_vector2 p1, raylib_vector2 p2, raylib_vector2 p3);               // Check if point is inside a triangle
RLAPI bool raylib_checkcollisionpointpoly(raylib_vector2 point, const raylib_vector2 *points, int pointCount);                // Check if point is within a polygon described by array of vertices
RLAPI bool raylib_checkcollisionlines(raylib_vector2 startPos1, raylib_vector2 endPos1, raylib_vector2 startPos2, raylib_vector2 endPos2, raylib_vector2 *collisionPoint); // Check the collision between two lines defined by two points each, returns collision point by reference
RLAPI bool raylib_checkcollisionpointline(raylib_vector2 point, raylib_vector2 p1, raylib_vector2 p2, int threshold);                // Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
RLAPI bool raylib_checkcollisioncircleline(raylib_vector2 center, float radius, raylib_vector2 p1, raylib_vector2 p2);               // Check if circle collides with a line created betweeen two points [p1] and [p2]
RLAPI raylib_rectangle raylib_getcollisionrec(raylib_rectangle rec1, raylib_rectangle rec2);                                         // Get collision rectangle for two rectangles collision

//------------------------------------------------------------------------------------
// raylib_texture Loading and Drawing Functions (Module: textures)
//------------------------------------------------------------------------------------

// raylib_image loading functions
// NOTE: These functions do not require GPU access
RLAPI raylib_image raylib_load_image(const char *fileName);                                                             // Load image from file into CPU memory (RAM)
RLAPI raylib_image raylib_loadimageraw(const char *fileName, int width, int height, int format, int headerSize);       // Load image from RAW file data
RLAPI raylib_image raylib_loadimagesvg(const char *fileNameOrString, int width, int height);                           // Load image from SVG file data or string with specified size
RLAPI raylib_image raylib_loadimageanim(const char *fileName, int *frames);                                            // Load image sequence from file (frames appended to image.data)
RLAPI raylib_image raylib_loadimageanimfrommemory(const char *fileType, const unsigned char *fileData, int dataSize, int *frames); // Load image sequence from memory buffer
RLAPI raylib_image raylib_loadimagefrommemory(const char *fileType, const unsigned char *fileData, int dataSize);      // Load image from memory buffer, fileType refers to extension: i.e. '.png'
RLAPI raylib_image raylib_loadimagefromtexture(raylib_texture2d texture);                                                     // Load image from GPU texture data
RLAPI raylib_image raylib_loadimagefromscreen(void);                                                                   // Load image from screen buffer and (screenshot)
RLAPI bool raylib_isimageready(raylib_image image);                                                                    // Check if an image is ready
RLAPI void raylib_unloadimage(raylib_image image);                                                                     // Unload image from CPU memory (RAM)
RLAPI bool raylib_exportimage(raylib_image image, const char *fileName);                                               // Export image data to file, returns true on success
RLAPI unsigned char *raylib_exportimagetomemory(raylib_image image, const char *fileType, int *fileSize);              // Export image to memory buffer
RLAPI bool raylib_exportimageascode(raylib_image image, const char *fileName);                                         // Export image as code file defining an array of bytes, returns true on success

// raylib_image generation functions
RLAPI raylib_image raylib_genimagecolor(int width, int height, raylib_color color);                                           // Generate image: plain color
RLAPI raylib_image raylib_genimagegradientlinear(int width, int height, int direction, raylib_color start, raylib_color end);        // Generate image: linear gradient, direction in degrees [0..360], 0=Vertical gradient
RLAPI raylib_image raylib_genimagegradientradial(int width, int height, float density, raylib_color inner, raylib_color outer);      // Generate image: radial gradient
RLAPI raylib_image raylib_genimagegradientsquare(int width, int height, float density, raylib_color inner, raylib_color outer);      // Generate image: square gradient
RLAPI raylib_image raylib_genimagechecked(int width, int height, int checksX, int checksY, raylib_color col1, raylib_color col2);    // Generate image: checked
RLAPI raylib_image raylib_genimagewhitenoise(int width, int height, float factor);                                     // Generate image: white noise
RLAPI raylib_image raylib_genimageperlinnoise(int width, int height, int offsetX, int offsetY, float scale);           // Generate image: perlin noise
RLAPI raylib_image raylib_genimagecellular(int width, int height, int tileSize);                                       // Generate image: cellular algorithm, bigger tileSize means bigger cells
RLAPI raylib_image raylib_genimagetext(int width, int height, const char *text);                                       // Generate image: grayscale image from text data

// raylib_image manipulation functions
RLAPI raylib_image raylib_imagecopy(raylib_image image);                                                                      // Create an image duplicate (useful for transformations)
RLAPI raylib_image raylib_imagefromimage(raylib_image image, raylib_rectangle rec);                                                  // Create an image from another image piece
RLAPI raylib_image raylib_imagetext(const char *text, int fontSize, raylib_color color);                                      // Create an image from text (default font)
RLAPI raylib_image raylib_imagetextex(raylib_font font, const char *text, float fontSize, float spacing, raylib_color tint);         // Create an image from text (custom sprite font)
RLAPI void raylib_imageformat(raylib_image *image, int newFormat);                                                     // Convert image data to desired format
RLAPI void raylib_imagetopot(raylib_image *image, raylib_color fill);                                                         // Convert image to POT (power-of-two)
RLAPI void raylib_imagecrop(raylib_image *image, raylib_rectangle crop);                                                      // Crop an image to a defined rectangle
RLAPI void raylib_imagealphacrop(raylib_image *image, float threshold);                                                // Crop image depending on alpha value
RLAPI void raylib_imagealphaclear(raylib_image *image, raylib_color color, float threshold);                                  // Clear alpha channel to desired color
RLAPI void raylib_imagealphamask(raylib_image *image, raylib_image alphaMask);                                                // Apply alpha mask to image
RLAPI void raylib_imagealphapremultiply(raylib_image *image);                                                          // Premultiply alpha channel
RLAPI void raylib_imageblurgaussian(raylib_image *image, int blurSize);                                                // Apply Gaussian blur using a box blur approximation
RLAPI void raylib_imagekernelconvolution(raylib_image *image, float *kernel, int kernelSize);                          // Apply Custom Square image convolution kernel
RLAPI void raylib_imageresize(raylib_image *image, int newWidth, int newHeight);                                       // Resize image (Bicubic scaling algorithm)
RLAPI void raylib_imageresizenn(raylib_image *image, int newWidth,int newHeight);                                      // Resize image (Nearest-Neighbor scaling algorithm)
RLAPI void raylib_imageresizecanvas(raylib_image *image, int newWidth, int newHeight, int offsetX, int offsetY, raylib_color fill); // Resize canvas and fill with color
RLAPI void raylib_imagemipmaps(raylib_image *image);                                                                   // Compute all mipmap levels for a provided image
RLAPI void raylib_imagedither(raylib_image *image, int rBpp, int gBpp, int bBpp, int aBpp);                            // Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
RLAPI void raylib_imageflipvertical(raylib_image *image);                                                              // Flip image vertically
RLAPI void raylib_imagefliphorizontal(raylib_image *image);                                                            // Flip image horizontally
RLAPI void raylib_imagerotate(raylib_image *image, int degrees);                                                       // Rotate image by input angle in degrees (-359 to 359)
RLAPI void raylib_imagerotatecw(raylib_image *image);                                                                  // Rotate image clockwise 90deg
RLAPI void raylib_imagerotateccw(raylib_image *image);                                                                 // Rotate image counter-clockwise 90deg
RLAPI void raylib_imagecolortint(raylib_image *image, raylib_color color);                                                    // Modify image color: tint
RLAPI void raylib_imagecolorinvert(raylib_image *image);                                                               // Modify image color: invert
RLAPI void raylib_imagecolorgrayscale(raylib_image *image);                                                            // Modify image color: grayscale
RLAPI void raylib_imagecolorcontrast(raylib_image *image, float contrast);                                             // Modify image color: contrast (-100 to 100)
RLAPI void raylib_imagecolorbrightness(raylib_image *image, int brightness);                                           // Modify image color: brightness (-255 to 255)
RLAPI void raylib_imagecolorreplace(raylib_image *image, raylib_color color, raylib_color replace);                                  // Modify image color: replace color
RLAPI raylib_color *raylib_loadimagecolors(raylib_image image);                                                               // Load color data from image as a raylib_color array (RGBA - 32bit)
RLAPI raylib_color *raylib_loadimagepalette(raylib_image image, int maxPaletteSize, int *colorCount);                         // Load colors palette from image as a raylib_color array (RGBA - 32bit)
RLAPI void raylib_unloadimagecolors(raylib_color *colors);                                                             // Unload color data loaded with raylib_loadimagecolors()
RLAPI void raylib_unloadimagepalette(raylib_color *colors);                                                            // Unload colors palette loaded with raylib_loadimagepalette()
RLAPI raylib_rectangle raylib_getimagealphaborder(raylib_image image, float threshold);                                       // Get image alpha border rectangle
RLAPI raylib_color raylib_getimagecolor(raylib_image image, int x, int y);                                                    // Get image pixel color at (x, y) position

// raylib_image drawing functions
// NOTE: raylib_image software-rendering functions (CPU)
RLAPI void raylib_imageclearbackground(raylib_image *dst, raylib_color color);                                                // Clear image background with given color
RLAPI void raylib_imagedrawpixel(raylib_image *dst, int posX, int posY, raylib_color color);                                  // Draw pixel within an image
RLAPI void raylib_imagedrawpixelv(raylib_image *dst, raylib_vector2 position, raylib_color color);                                   // Draw pixel within an image (Vector version)
RLAPI void raylib_imagedrawline(raylib_image *dst, int startPosX, int startPosY, int endPosX, int endPosY, raylib_color color); // Draw line within an image
RLAPI void raylib_imagedrawlinev(raylib_image *dst, raylib_vector2 start, raylib_vector2 end, raylib_color color);                          // Draw line within an image (Vector version)
RLAPI void raylib_imagedrawcircle(raylib_image *dst, int centerX, int centerY, int radius, raylib_color color);               // Draw a filled circle within an image
RLAPI void raylib_imagedrawcirclev(raylib_image *dst, raylib_vector2 center, int radius, raylib_color color);                        // Draw a filled circle within an image (Vector version)
RLAPI void raylib_imagedrawcirclelines(raylib_image *dst, int centerX, int centerY, int radius, raylib_color color);          // Draw circle outline within an image
RLAPI void raylib_imagedrawcirclelinesv(raylib_image *dst, raylib_vector2 center, int radius, raylib_color color);                   // Draw circle outline within an image (Vector version)
RLAPI void raylib_imagedrawrectangle(raylib_image *dst, int posX, int posY, int width, int height, raylib_color color);       // Draw rectangle within an image
RLAPI void raylib_imagedrawrectanglev(raylib_image *dst, raylib_vector2 position, raylib_vector2 size, raylib_color color);                 // Draw rectangle within an image (Vector version)
RLAPI void raylib_imagedrawrectanglerec(raylib_image *dst, raylib_rectangle rec, raylib_color color);                                // Draw rectangle within an image
RLAPI void raylib_imagedrawrectanglelines(raylib_image *dst, raylib_rectangle rec, int thick, raylib_color color);                   // Draw rectangle lines within an image
RLAPI void raylib_imagedrawtriangle(raylib_image *dst, raylib_vector2 v1, raylib_vector2 v2, raylib_vector2 v3, raylib_color color);               // Draw triangle within an image
RLAPI void raylib_imagedrawtriangleex(raylib_image *dst, raylib_vector2 v1, raylib_vector2 v2, raylib_vector2 v3, raylib_color c1, raylib_color c2, raylib_color c3); // Draw triangle with interpolated colors within an image
RLAPI void raylib_imagedrawtrianglelines(raylib_image *dst, raylib_vector2 v1, raylib_vector2 v2, raylib_vector2 v3, raylib_color color);          // Draw triangle outline within an image
RLAPI void raylib_imagedrawtrianglefan(raylib_image *dst, raylib_vector2 *points, int pointCount, raylib_color color);               // Draw a triangle fan defined by points within an image (first vertex is the center)
RLAPI void raylib_imagedrawtrianglestrip(raylib_image *dst, raylib_vector2 *points, int pointCount, raylib_color color);             // Draw a triangle strip defined by points within an image
RLAPI void raylib_imagedraw(raylib_image *dst, raylib_image src, raylib_rectangle srcRec, raylib_rectangle dstRec, raylib_color tint);             // Draw a source image within a destination image (tint applied to source)
RLAPI void raylib_imagedrawtext(raylib_image *dst, const char *text, int posX, int posY, int fontSize, raylib_color color);   // Draw text (using default font) within an image (destination)
RLAPI void raylib_imagedrawtextex(raylib_image *dst, raylib_font font, const char *text, raylib_vector2 position, float fontSize, float spacing, raylib_color tint); // Draw text (custom sprite font) within an image (destination)

// raylib_texture loading functions
// NOTE: These functions require GPU access
RLAPI raylib_texture2d raylib_loadtexture(const char *fileName);                                                       // Load texture from file into GPU memory (VRAM)
RLAPI raylib_texture2d raylib_loadtexturefromimage(raylib_image image);                                                       // Load texture from image data
RLAPI raylib_texturecubemap raylib_loadtexturecubemap(raylib_image image, int layout);                                        // Load cubemap from image, multiple image cubemap layouts supported
RLAPI raylib_rendertexture2d raylib_loadrendertexture(int width, int height);                                          // Load texture for rendering (framebuffer)
RLAPI bool raylib_istextureready(raylib_texture2d texture);                                                            // Check if a texture is ready
RLAPI void raylib_unloadtexture(raylib_texture2d texture);                                                             // Unload texture from GPU memory (VRAM)
RLAPI bool raylib_isrendertextureready(raylib_rendertexture2d target);                                                 // Check if a render texture is ready
RLAPI void raylib_unloadrendertexture(raylib_rendertexture2d target);                                                  // Unload render texture from GPU memory (VRAM)
RLAPI void raylib_updatetexture(raylib_texture2d texture, const void *pixels);                                         // Update GPU texture with new data
RLAPI void raylib_updatetexturerec(raylib_texture2d texture, raylib_rectangle rec, const void *pixels);                       // Update GPU texture rectangle with new data

// raylib_texture configuration functions
RLAPI void raylib_gentexturemipmaps(raylib_texture2d *texture);                                                        // Generate GPU mipmaps for a texture
RLAPI void raylib_settexturefilter(raylib_texture2d texture, int filter);                                              // Set texture scaling filter mode
RLAPI void raylib_settexturewrap(raylib_texture2d texture, int wrap);                                                  // Set texture wrapping mode

// raylib_texture drawing functions
RLAPI void raylib_drawtexture(raylib_texture2d texture, int posX, int posY, raylib_color tint);                               // Draw a raylib_texture2d
RLAPI void raylib_drawtexturev(raylib_texture2d texture, raylib_vector2 position, raylib_color tint);                                // Draw a raylib_texture2d with position defined as raylib_vector2
RLAPI void raylib_drawtextureex(raylib_texture2d texture, raylib_vector2 position, float rotation, float scale, raylib_color tint);  // Draw a raylib_texture2d with extended parameters
RLAPI void raylib_drawtexturerec(raylib_texture2d texture, raylib_rectangle source, raylib_vector2 position, raylib_color tint);            // Draw a part of a texture defined by a rectangle
RLAPI void raylib_drawtexturepro(raylib_texture2d texture, raylib_rectangle source, raylib_rectangle dest, raylib_vector2 origin, float rotation, raylib_color tint); // Draw a part of a texture defined by a rectangle with 'pro' parameters
RLAPI void raylib_drawtexturenpatch(raylib_texture2d texture, raylib_npatchinfo nPatchInfo, raylib_rectangle dest, raylib_vector2 origin, float rotation, raylib_color tint); // Draws a texture (or part of it) that stretches or shrinks nicely

// raylib_color/pixel related functions
RLAPI bool raylib_colorisequal(raylib_color col1, raylib_color col2);                            // Check if two colors are equal
RLAPI raylib_color raylib_fade(raylib_color color, float alpha);                                 // Get color with alpha applied, alpha goes from 0.0f to 1.0f
RLAPI int raylib_colortoint(raylib_color color);                                          // Get hexadecimal value for a raylib_color (0xRRGGBBAA)
RLAPI raylib_vector4 raylib_colornormalize(raylib_color color);                                  // Get raylib_color normalized as float [0..1]
RLAPI raylib_color raylib_colorfromnormalized(raylib_vector4 normalized);                        // Get raylib_color from normalized values [0..1]
RLAPI raylib_vector3 raylib_colortohsv(raylib_color color);                                      // Get HSV values for a raylib_color, hue [0..360], saturation/value [0..1]
RLAPI raylib_color raylib_colorfromhsv(float hue, float saturation, float value);         // Get a raylib_color from HSV values, hue [0..360], saturation/value [0..1]
RLAPI raylib_color raylib_colortint(raylib_color color, raylib_color tint);                             // Get color multiplied with another color
RLAPI raylib_color raylib_colorbrightness(raylib_color color, float factor);                     // Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
RLAPI raylib_color raylib_colorcontrast(raylib_color color, float contrast);                     // Get color with contrast correction, contrast values between -1.0f and 1.0f
RLAPI raylib_color raylib_coloralpha(raylib_color color, float alpha);                           // Get color with alpha applied, alpha goes from 0.0f to 1.0f
RLAPI raylib_color raylib_coloralphablend(raylib_color dst, raylib_color src, raylib_color tint);              // Get src alpha-blended into dst color with tint
RLAPI raylib_color raylib_getcolor(unsigned int hexValue);                                // Get raylib_color structure from hexadecimal value
RLAPI raylib_color raylib_getpixelcolor(void *srcPtr, int format);                        // Get raylib_color from a source pixel pointer of certain format
RLAPI void raylib_setpixelcolor(void *dstPtr, raylib_color color, int format);            // Set color formatted into destination pixel pointer
RLAPI int raylib_getpixeldatasize(int width, int height, int format);              // Get pixel data size in bytes for certain format

//------------------------------------------------------------------------------------
// raylib_font Loading and Text Drawing Functions (Module: text)
//------------------------------------------------------------------------------------

// raylib_font loading/unloading functions
RLAPI raylib_font raylib_getfontdefault(void);                                                            // Get the default raylib_font
RLAPI raylib_font raylib_loadfont(const char *fileName);                                                  // Load font from file into GPU memory (VRAM)
RLAPI raylib_font raylib_loadfontex(const char *fileName, int fontSize, int *codepoints, int codepointCount); // Load font from file with extended parameters, use NULL for codepoints and 0 for codepointCount to load the default character set
RLAPI raylib_font raylib_loadfontfromimage(raylib_image image, raylib_color key, int firstChar);                        // Load font from raylib_image (XNA style)
RLAPI raylib_font raylib_loadfontfrommemory(const char *fileType, const unsigned char *fileData, int dataSize, int fontSize, int *codepoints, int codepointCount); // Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
RLAPI bool raylib_isfontready(raylib_font font);                                                          // Check if a font is ready
RLAPI raylib_glyphinfo *raylib_loadfontdata(const unsigned char *fileData, int dataSize, int fontSize, int *codepoints, int codepointCount, int type); // Load font data for further use
RLAPI raylib_image raylib_genimagefontatlas(const raylib_glyphinfo *glyphs, raylib_rectangle **glyphRecs, int glyphCount, int fontSize, int padding, int packMethod); // Generate image font atlas using chars info
RLAPI void raylib_unloadfontdata(raylib_glyphinfo *glyphs, int glyphCount);                               // Unload font chars info data (RAM)
RLAPI void raylib_unloadfont(raylib_font font);                                                           // Unload font from GPU memory (VRAM)
RLAPI bool raylib_exportfontascode(raylib_font font, const char *fileName);                               // Export font as code file, returns true on success

// Text drawing functions
RLAPI void raylib_drawfps(int posX, int posY);                                                     // Draw current FPS
RLAPI void raylib_draw_text(const char *text, int posX, int posY, int fontSize, raylib_color color);       // Draw text (using default font)
RLAPI void raylib_draw_text_ex(raylib_font font, const char *text, raylib_vector2 position, float fontSize, float spacing, raylib_color tint); // Draw text using font and additional parameters
RLAPI void raylib_drawtextpro(raylib_font font, const char *text, raylib_vector2 position, raylib_vector2 origin, float rotation, float fontSize, float spacing, raylib_color tint); // Draw text using raylib_font and pro parameters (rotation)
RLAPI void raylib_drawtextcodepoint(raylib_font font, int codepoint, raylib_vector2 position, float fontSize, raylib_color tint); // Draw one character (codepoint)
RLAPI void raylib_drawtextcodepoints(raylib_font font, const int *codepoints, int codepointCount, raylib_vector2 position, float fontSize, float spacing, raylib_color tint); // Draw multiple character (codepoint)

// Text font info functions
RLAPI void raylib_settextlinespacing(int spacing);                                                 // Set vertical line spacing when drawing with line-breaks
RLAPI int raylib_measuretext(const char *text, int fontSize);                                      // Measure string width for default font
RLAPI raylib_vector2 raylib_measuretextex(raylib_font font, const char *text, float fontSize, float spacing);    // Measure string size for raylib_font
RLAPI int raylib_getglyphindex(raylib_font font, int codepoint);                                          // Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
RLAPI raylib_glyphinfo raylib_getglyphinfo(raylib_font font, int codepoint);                                     // Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
RLAPI raylib_rectangle raylib_getglyphatlasrec(raylib_font font, int codepoint);                                 // Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found

// Text codepoints management functions (unicode characters)
RLAPI char *raylib_loadutf8(const int *codepoints, int length);                // Load UTF-8 text encoded from codepoints array
RLAPI void raylib_unloadutf8(char *text);                                      // Unload UTF-8 text encoded from codepoints array
RLAPI int *raylib_loadcodepoints(const char *text, int *count);                // Load all codepoints from a UTF-8 text string, codepoints count returned by parameter
RLAPI void raylib_unloadcodepoints(int *codepoints);                           // Unload codepoints data from memory
RLAPI int raylib_getcodepointcount(const char *text);                          // Get total number of codepoints in a UTF-8 encoded string
RLAPI int raylib_getcodepoint(const char *text, int *codepointSize);           // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
RLAPI int raylib_getcodepointnext(const char *text, int *codepointSize);       // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
RLAPI int raylib_getcodepointprevious(const char *text, int *codepointSize);   // Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
RLAPI const char *raylib_codepointtoutf8(int codepoint, int *utf8Size);        // Encode one codepoint into UTF-8 byte array (array length returned as parameter)

// Text strings management functions (no UTF-8 strings, only byte chars)
// NOTE: Some strings allocate memory internally for returned strings, just be careful!
RLAPI int raylib_textcopy(char *dst, const char *src);                                             // Copy one string to another, returns bytes copied
RLAPI bool raylib_textisequal(const char *text1, const char *text2);                               // Check if two text string are equal
RLAPI unsigned int raylib_textlength(const char *text);                                            // Get text length, checks for '\0' ending
RLAPI const char *raylib_textformat(const char *text, ...);                                        // Text formatting with variables (sprintf() style)
RLAPI const char *raylib_textsubtext(const char *text, int position, int length);                  // Get a piece of a text string
RLAPI char *raylib_textreplace(const char *text, const char *replace, const char *by);             // Replace text string (WARNING: memory must be freed!)
RLAPI char *raylib_textinsert(const char *text, const char *insert, int position);                 // Insert text in a position (WARNING: memory must be freed!)
RLAPI const char *raylib_textjoin(const char **textList, int count, const char *delimiter);        // Join text strings with delimiter
RLAPI const char **TextSplit(const char *text, char delimiter, int *count);                 // Split text into multiple strings
RLAPI void raylib_textappend(char *text, const char *append, int *position);                       // Append text at specific position and move cursor!
RLAPI int raylib_textfindindex(const char *text, const char *find);                                // Find first text occurrence within a string
RLAPI const char *raylib_texttoupper(const char *text);                      // Get upper case version of provided string
RLAPI const char *raylib_texttolower(const char *text);                      // Get lower case version of provided string
RLAPI const char *raylib_texttopascal(const char *text);                     // Get Pascal case notation version of provided string
RLAPI const char *raylib_texttosnake(const char *text);                      // Get Snake case notation version of provided string
RLAPI const char *raylib_texttocamel(const char *text);                      // Get Camel case notation version of provided string

RLAPI int raylib_texttointeger(const char *text);                            // Get integer value from text (negative values not supported)
RLAPI float raylib_texttofloat(const char *text);                            // Get float value from text (negative values not supported)

//------------------------------------------------------------------------------------
// Basic 3d Shapes Drawing Functions (Module: models)
//------------------------------------------------------------------------------------

// Basic geometric 3D shapes drawing functions
RLAPI void raylib_drawline3d(raylib_vector3 startPos, raylib_vector3 endPos, raylib_color color);                                    // Draw a line in 3D world space
RLAPI void raylib_drawpoint3d(raylib_vector3 position, raylib_color color);                                                   // Draw a point in 3D space, actually a small line
RLAPI void raylib_drawcircle3d(raylib_vector3 center, float radius, raylib_vector3 rotationAxis, float rotationAngle, raylib_color color); // Draw a circle in 3D world space
RLAPI void raylib_drawtriangle3d(raylib_vector3 v1, raylib_vector3 v2, raylib_vector3 v3, raylib_color color);                              // Draw a color-filled triangle (vertex in counter-clockwise order!)
RLAPI void raylib_drawtrianglestrip3d(const raylib_vector3 *points, int pointCount, raylib_color color);                      // Draw a triangle strip defined by points
RLAPI void raylib_drawcube(raylib_vector3 position, float width, float height, float length, raylib_color color);             // Draw cube
RLAPI void raylib_drawcubev(raylib_vector3 position, raylib_vector3 size, raylib_color color);                                       // Draw cube (Vector version)
RLAPI void raylib_drawcubewires(raylib_vector3 position, float width, float height, float length, raylib_color color);        // Draw cube wires
RLAPI void raylib_drawcubewiresv(raylib_vector3 position, raylib_vector3 size, raylib_color color);                                  // Draw cube wires (Vector version)
RLAPI void raylib_drawsphere(raylib_vector3 centerPos, float radius, raylib_color color);                                     // Draw sphere
RLAPI void raylib_drawsphereex(raylib_vector3 centerPos, float radius, int rings, int slices, raylib_color color);            // Draw sphere with extended parameters
RLAPI void raylib_drawspherewires(raylib_vector3 centerPos, float radius, int rings, int slices, raylib_color color);         // Draw sphere wires
RLAPI void raylib_drawcylinder(raylib_vector3 position, float radiusTop, float radiusBottom, float height, int slices, raylib_color color); // Draw a cylinder/cone
RLAPI void raylib_drawcylinderex(raylib_vector3 startPos, raylib_vector3 endPos, float startRadius, float endRadius, int sides, raylib_color color); // Draw a cylinder with base at startPos and top at endPos
RLAPI void raylib_drawcylinderwires(raylib_vector3 position, float radiusTop, float radiusBottom, float height, int slices, raylib_color color); // Draw a cylinder/cone wires
RLAPI void raylib_drawcylinderwiresex(raylib_vector3 startPos, raylib_vector3 endPos, float startRadius, float endRadius, int sides, raylib_color color); // Draw a cylinder wires with base at startPos and top at endPos
RLAPI void raylib_drawcapsule(raylib_vector3 startPos, raylib_vector3 endPos, float radius, int slices, int rings, raylib_color color); // Draw a capsule with the center of its sphere caps at startPos and endPos
RLAPI void raylib_drawcapsulewires(raylib_vector3 startPos, raylib_vector3 endPos, float radius, int slices, int rings, raylib_color color); // Draw capsule wireframe with the center of its sphere caps at startPos and endPos
RLAPI void raylib_drawplane(raylib_vector3 centerPos, raylib_vector2 size, raylib_color color);                                      // Draw a plane XZ
RLAPI void raylib_drawray(raylib_ray ray, raylib_color color);                                                                // Draw a ray line
RLAPI void raylib_drawgrid(int slices, float spacing);                                                          // Draw a grid (centered at (0, 0, 0))

//------------------------------------------------------------------------------------
// raylib_model 3d Loading and Drawing Functions (Module: models)
//------------------------------------------------------------------------------------

// raylib_model management functions
RLAPI raylib_model raylib_loadmodel(const char *fileName);                                                // Load model from files (meshes and materials)
RLAPI raylib_model raylib_loadmodelfrommesh(raylib_mesh mesh);                                                   // Load model from generated mesh (default material)
RLAPI bool raylib_ismodelready(raylib_model model);                                                       // Check if a model is ready
RLAPI void raylib_unloadmodel(raylib_model model);                                                        // Unload model (including meshes) from memory (RAM and/or VRAM)
RLAPI raylib_boundingbox raylib_getmodelboundingbox(raylib_model model);                                         // Compute model bounding box limits (considers all meshes)

// raylib_model drawing functions
RLAPI void raylib_drawmodel(raylib_model model, raylib_vector3 position, float scale, raylib_color tint);               // Draw a model (with texture if set)
RLAPI void raylib_drawmodelex(raylib_model model, raylib_vector3 position, raylib_vector3 rotationAxis, float rotationAngle, raylib_vector3 scale, raylib_color tint); // Draw a model with extended parameters
RLAPI void raylib_drawmodelwires(raylib_model model, raylib_vector3 position, float scale, raylib_color tint);          // Draw a model wires (with texture if set)
RLAPI void raylib_drawmodelwiresex(raylib_model model, raylib_vector3 position, raylib_vector3 rotationAxis, float rotationAngle, raylib_vector3 scale, raylib_color tint); // Draw a model wires (with texture if set) with extended parameters
RLAPI void raylib_drawboundingbox(raylib_boundingbox box, raylib_color color);                                   // Draw bounding box (wires)
RLAPI void raylib_drawbillboard(raylib_camera camera, raylib_texture2d texture, raylib_vector3 position, float size, raylib_color tint);   // Draw a billboard texture
RLAPI void raylib_drawbillboardrec(raylib_camera camera, raylib_texture2d texture, raylib_rectangle source, raylib_vector3 position, raylib_vector2 size, raylib_color tint); // Draw a billboard texture defined by source
RLAPI void raylib_drawbillboardpro(raylib_camera camera, raylib_texture2d texture, raylib_rectangle source, raylib_vector3 position, raylib_vector3 up, raylib_vector2 size, raylib_vector2 origin, float rotation, raylib_color tint); // Draw a billboard texture defined by source and rotation

// raylib_mesh management functions
RLAPI void raylib_uploadmesh(raylib_mesh *mesh, bool dynamic);                                            // Upload mesh vertex data in GPU and provide VAO/VBO ids
RLAPI void raylib_updatemeshbuffer(raylib_mesh mesh, int index, const void *data, int dataSize, int offset); // Update mesh vertex data in GPU for a specific buffer index
RLAPI void raylib_unloadmesh(raylib_mesh mesh);                                                           // Unload mesh data from CPU and GPU
RLAPI void raylib_drawmesh(raylib_mesh mesh, raylib_material material, raylib_matrix transform);                        // Draw a 3d mesh with material and transform
RLAPI void raylib_drawmeshinstanced(raylib_mesh mesh, raylib_material material, const raylib_matrix *transforms, int instances); // Draw multiple mesh instances with material and different transforms
RLAPI raylib_boundingbox raylib_getmeshboundingbox(raylib_mesh mesh);                                            // Compute mesh bounding box limits
RLAPI void raylib_genmeshtangents(raylib_mesh *mesh);                                                     // Compute mesh tangents
RLAPI bool raylib_exportmesh(raylib_mesh mesh, const char *fileName);                                     // Export mesh data to file, returns true on success
RLAPI bool raylib_exportmeshascode(raylib_mesh mesh, const char *fileName);                               // Export mesh as code file (.h) defining multiple arrays of vertex attributes

// raylib_mesh generation functions
RLAPI raylib_mesh raylib_genmeshpoly(int sides, float radius);                                            // Generate polygonal mesh
RLAPI raylib_mesh raylib_genmeshplane(float width, float length, int resX, int resZ);                     // Generate plane mesh (with subdivisions)
RLAPI raylib_mesh raylib_genmeshcube(float width, float height, float length);                            // Generate cuboid mesh
RLAPI raylib_mesh raylib_genmeshsphere(float radius, int rings, int slices);                              // Generate sphere mesh (standard sphere)
RLAPI raylib_mesh raylib_genmeshhemisphere(float radius, int rings, int slices);                          // Generate half-sphere mesh (no bottom cap)
RLAPI raylib_mesh raylib_genmeshcylinder(float radius, float height, int slices);                         // Generate cylinder mesh
RLAPI raylib_mesh raylib_genmeshcone(float radius, float height, int slices);                             // Generate cone/pyramid mesh
RLAPI raylib_mesh raylib_genmeshtorus(float radius, float size, int radSeg, int sides);                   // Generate torus mesh
RLAPI raylib_mesh raylib_genmeshknot(float radius, float size, int radSeg, int sides);                    // Generate trefoil knot mesh
RLAPI raylib_mesh raylib_genmeshheightmap(raylib_image heightmap, raylib_vector3 size);                                 // Generate heightmap mesh from image data
RLAPI raylib_mesh raylib_genmeshcubicmap(raylib_image cubicmap, raylib_vector3 cubeSize);                               // Generate cubes-based map mesh from image data

// raylib_material loading/unloading functions
RLAPI raylib_material *raylib_loadmaterials(const char *fileName, int *materialCount);                    // Load materials from model file
RLAPI raylib_material raylib_loadmaterialdefault(void);                                                   // Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)
RLAPI bool raylib_ismaterialready(raylib_material material);                                              // Check if a material is ready
RLAPI void raylib_unloadmaterial(raylib_material material);                                               // Unload material from GPU memory (VRAM)
RLAPI void raylib_setmaterialtexture(raylib_material *material, int mapType, raylib_texture2d texture);          // Set texture for a material map type (MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_SPECULAR...)
RLAPI void raylib_setmodelmeshmaterial(raylib_model *model, int meshId, int materialId);                  // Set material for a mesh

// raylib_model animations loading/unloading functions
RLAPI raylib_modelanimation *raylib_loadmodelanimations(const char *fileName, int *animCount);            // Load model animations from file
RLAPI void raylib_updatemodelanimation(raylib_model model, raylib_modelanimation anim, int frame);               // Update model animation pose
RLAPI void raylib_unloadmodelanimation(raylib_modelanimation anim);                                       // Unload animation data
RLAPI void raylib_unloadmodelanimations(raylib_modelanimation *animations, int animCount);                // Unload animation array data
RLAPI bool raylib_ismodelanimationvalid(raylib_model model, raylib_modelanimation anim);                         // Check model animation skeleton match

// Collision detection functions
RLAPI bool raylib_checkcollisionspheres(raylib_vector3 center1, float radius1, raylib_vector3 center2, float radius2);   // Check collision between two spheres
RLAPI bool raylib_checkcollisionboxes(raylib_boundingbox box1, raylib_boundingbox box2);                                 // Check collision between two bounding boxes
RLAPI bool raylib_checkcollisionboxsphere(raylib_boundingbox box, raylib_vector3 center, float radius);                  // Check collision between box and sphere
RLAPI raylib_raycollision raylib_getraycollisionsphere(raylib_ray ray, raylib_vector3 center, float radius);                    // Get collision info between ray and sphere
RLAPI raylib_raycollision raylib_getraycollisionbox(raylib_ray ray, raylib_boundingbox box);                                    // Get collision info between ray and box
RLAPI raylib_raycollision raylib_getraycollisionmesh(raylib_ray ray, raylib_mesh mesh, raylib_matrix transform);                       // Get collision info between ray and mesh
RLAPI raylib_raycollision raylib_getraycollisiontriangle(raylib_ray ray, raylib_vector3 p1, raylib_vector3 p2, raylib_vector3 p3);            // Get collision info between ray and triangle
RLAPI raylib_raycollision raylib_getraycollisionquad(raylib_ray ray, raylib_vector3 p1, raylib_vector3 p2, raylib_vector3 p3, raylib_vector3 p4);    // Get collision info between ray and quad

//------------------------------------------------------------------------------------
// Audio Loading and Playing Functions (Module: audio)
//------------------------------------------------------------------------------------
typedef void (*AudioCallback)(void *bufferData, unsigned int frames);

// Audio device management functions
RLAPI void raylib_initaudiodevice(void);                                     // Initialize audio device and context
RLAPI void raylib_closeaudiodevice(void);                                    // Close the audio device and context
RLAPI bool raylib_isaudiodeviceready(void);                                  // Check if audio device has been initialized successfully
RLAPI void raylib_setmastervolume(float volume);                             // Set master volume (listener)
RLAPI float raylib_getmastervolume(void);                                    // Get master volume (listener)

// raylib_wave/raylib_sound loading/unloading functions
RLAPI raylib_wave raylib_loadwave(const char *fileName);                            // Load wave data from file
RLAPI raylib_wave raylib_loadwavefrommemory(const char *fileType, const unsigned char *fileData, int dataSize); // Load wave from memory buffer, fileType refers to extension: i.e. '.wav'
RLAPI bool raylib_iswaveready(raylib_wave wave);                                    // Checks if wave data is ready
RLAPI raylib_sound raylib_loadsound(const char *fileName);                          // Load sound from file
RLAPI raylib_sound raylib_loadsoundfromwave(raylib_wave wave);                             // Load sound from wave data
RLAPI raylib_sound raylib_loadsoundalias(raylib_sound source);                             // Create a new sound that shares the same sample data as the source sound, does not own the sound data
RLAPI bool raylib_issoundready(raylib_sound sound);                                 // Checks if a sound is ready
RLAPI void raylib_updatesound(raylib_sound sound, const void *data, int sampleCount); // Update sound buffer with new data
RLAPI void raylib_unloadwave(raylib_wave wave);                                     // Unload wave data
RLAPI void raylib_unloadsound(raylib_sound sound);                                  // Unload sound
RLAPI void raylib_unloadsoundalias(raylib_sound alias);                             // Unload a sound alias (does not deallocate sample data)
RLAPI bool raylib_exportwave(raylib_wave wave, const char *fileName);               // Export wave data to file, returns true on success
RLAPI bool raylib_exportwaveascode(raylib_wave wave, const char *fileName);         // Export wave sample data to code (.h), returns true on success

// raylib_wave/raylib_sound management functions
RLAPI void raylib_play_sound(raylib_sound sound);                                    // Play a sound
RLAPI void raylib_stopsound(raylib_sound sound);                                    // Stop playing a sound
RLAPI void raylib_pausesound(raylib_sound sound);                                   // Pause a sound
RLAPI void raylib_resumesound(raylib_sound sound);                                  // Resume a paused sound
RLAPI bool raylib_issoundplaying(raylib_sound sound);                               // Check if a sound is currently playing
RLAPI void raylib_setsoundvolume(raylib_sound sound, float volume);                 // Set volume for a sound (1.0 is max level)
RLAPI void raylib_setsoundpitch(raylib_sound sound, float pitch);                   // Set pitch for a sound (1.0 is base level)
RLAPI void raylib_setsoundpan(raylib_sound sound, float pan);                       // Set pan for a sound (0.5 is center)
RLAPI raylib_wave raylib_wavecopy(raylib_wave wave);                                       // Copy a wave to a new wave
RLAPI void raylib_wavecrop(raylib_wave *wave, int initFrame, int finalFrame);       // Crop a wave to defined frames range
RLAPI void raylib_waveformat(raylib_wave *wave, int sampleRate, int sampleSize, int channels); // Convert wave data to desired format
RLAPI float *raylib_loadwavesamples(raylib_wave wave);                              // Load samples data from wave as a 32bit float data array
RLAPI void raylib_unloadwavesamples(float *samples);                         // Unload samples data loaded with raylib_loadwavesamples()

// raylib_music management functions
RLAPI raylib_music raylib_loadmusicstream(const char *fileName);                    // Load music stream from file
RLAPI raylib_music raylib_loadmusicstreamfrommemory(const char *fileType, const unsigned char *data, int dataSize); // Load music stream from data
RLAPI bool raylib_ismusicready(raylib_music music);                                 // Checks if a music stream is ready
RLAPI void raylib_unloadmusicstream(raylib_music music);                            // Unload music stream
RLAPI void raylib_playmusicstream(raylib_music music);                              // Start music playing
RLAPI bool raylib_ismusicstreamplaying(raylib_music music);                         // Check if music is playing
RLAPI void raylib_updatemusicstream(raylib_music music);                            // Updates buffers for music streaming
RLAPI void raylib_stopmusicstream(raylib_music music);                              // Stop music playing
RLAPI void raylib_pausemusicstream(raylib_music music);                             // Pause music playing
RLAPI void raylib_resumemusicstream(raylib_music music);                            // Resume playing paused music
RLAPI void raylib_seekmusicstream(raylib_music music, float position);              // Seek music to a position (in seconds)
RLAPI void raylib_setmusicvolume(raylib_music music, float volume);                 // Set volume for music (1.0 is max level)
RLAPI void raylib_setmusicpitch(raylib_music music, float pitch);                   // Set pitch for a music (1.0 is base level)
RLAPI void raylib_setmusicpan(raylib_music music, float pan);                       // Set pan for a music (0.5 is center)
RLAPI float raylib_getmusictimelength(raylib_music music);                          // Get music time length (in seconds)
RLAPI float raylib_getmusictimeplayed(raylib_music music);                          // Get current music time played (in seconds)

// raylib_audiostream management functions
RLAPI raylib_audiostream raylib_loadaudiostream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels); // Load audio stream (to stream raw audio pcm data)
RLAPI bool raylib_isaudiostreamready(raylib_audiostream stream);                    // Checks if an audio stream is ready
RLAPI void raylib_unloadaudiostream(raylib_audiostream stream);                     // Unload audio stream and free memory
RLAPI void raylib_updateaudiostream(raylib_audiostream stream, const void *data, int frameCount); // Update audio stream buffers with data
RLAPI bool raylib_isaudiostreamprocessed(raylib_audiostream stream);                // Check if any audio stream buffers requires refill
RLAPI void raylib_playaudiostream(raylib_audiostream stream);                       // Play audio stream
RLAPI void raylib_pauseaudiostream(raylib_audiostream stream);                      // Pause audio stream
RLAPI void raylib_resumeaudiostream(raylib_audiostream stream);                     // Resume audio stream
RLAPI bool raylib_isaudiostreamplaying(raylib_audiostream stream);                  // Check if audio stream is playing
RLAPI void raylib_stopaudiostream(raylib_audiostream stream);                       // Stop audio stream
RLAPI void raylib_setaudiostreamvolume(raylib_audiostream stream, float volume);    // Set volume for audio stream (1.0 is max level)
RLAPI void raylib_setaudiostreampitch(raylib_audiostream stream, float pitch);      // Set pitch for audio stream (1.0 is base level)
RLAPI void raylib_setaudiostreampan(raylib_audiostream stream, float pan);          // Set pan for audio stream (0.5 is centered)
RLAPI void raylib_setaudiostreambuffersizedefault(int size);                 // Default size for new audio streams
RLAPI void raylib_setaudiostreamcallback(raylib_audiostream stream, AudioCallback callback); // Audio thread callback to request new data

RLAPI void raylib_attachaudiostreamprocessor(raylib_audiostream stream, AudioCallback processor); // Attach audio stream processor to stream, receives the samples as 'float'
RLAPI void raylib_detachaudiostreamprocessor(raylib_audiostream stream, AudioCallback processor); // Detach audio stream processor from stream

RLAPI void raylib_attachaudiomixedprocessor(AudioCallback processor); // Attach audio stream processor to the entire audio pipeline, receives the samples as 'float'
RLAPI void raylib_detachaudiomixedprocessor(AudioCallback processor); // Detach audio stream processor from the entire audio pipeline

#if defined(__cplusplus)
}
#endif

#endif // RAYLIB_H
