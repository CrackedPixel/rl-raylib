/**********************************************************************************************
*
*   rcore_<platform> template - Functions to manage window, graphics device and inputs
*
*   PLATFORM: <PLATFORM>
*       - TODO: Define the target platform for the core
*
*   LIMITATIONS:
*       - Limitation 01
*       - Limitation 02
*
*   POSSIBLE IMPROVEMENTS:
*       - Improvement 01
*       - Improvement 02
*
*   ADDITIONAL NOTES:
*       - TRACELOG() function is located in raylib [utils] module
*
*   CONFIGURATION:
*       #define RCORE_PLATFORM_CUSTOM_FLAG
*           Custom flag for rcore on target platform -not used-
*
*   DEPENDENCIES:
*       - <platform-specific SDK dependency>
*       - gestures: Gestures system for touch-ready devices (or simulated from mouse inputs)
*
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5) and contributors
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

// TODO: Include the platform specific libraries

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef struct {
    // TODO: Define the platform specific variables required

    // Display data
    EGLDisplay device;                  // Native display device (physical screen connection)
    EGLSurface surface;                 // Surface to draw on, framebuffers (connected to context)
    EGLContext context;                 // Graphic context, mode in which drawing can be done
    EGLConfig config;                   // Graphic config
} PlatformData;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
extern CoreData CORE;                   // Global CORE state context

static PlatformData platform = { 0 };   // Platform specific data

//----------------------------------------------------------------------------------
// Module Internal Functions Declaration
//----------------------------------------------------------------------------------
int InitPlatform(void);          // Initialize platform (graphics, inputs and more)
bool InitGraphicsDevice(void);   // Initialize graphics device

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
// NOTE: Functions declaration is provided by raylib.h

//----------------------------------------------------------------------------------
// Module Functions Definition: Window and Graphics Device
//----------------------------------------------------------------------------------

// Check if application should close
bool raylib_windowshouldclose(void)
{
    if (CORE.Window.ready) return CORE.Window.shouldClose;
    else return true;
}

// Toggle fullscreen mode
void raylib_togglefullscreen(void)
{
    TRACELOG(LOG_WARNING, "raylib_togglefullscreen() not available on target platform");
}

// Toggle borderless windowed mode
void raylib_toggleborderlesswindowed(void)
{
    TRACELOG(LOG_WARNING, "raylib_toggleborderlesswindowed() not available on target platform");
}

// Set window state: maximized, if resizable
void raylib_maximizewindow(void)
{
    TRACELOG(LOG_WARNING, "raylib_maximizewindow() not available on target platform");
}

// Set window state: minimized
void raylib_minimizewindow(void)
{
    TRACELOG(LOG_WARNING, "raylib_minimizewindow() not available on target platform");
}

// Set window state: not minimized/maximized
void raylib_restorewindow(void)
{
    TRACELOG(LOG_WARNING, "raylib_restorewindow() not available on target platform");
}

// Set window configuration state using flags
void raylib_setwindowstate(unsigned int flags)
{
    TRACELOG(LOG_WARNING, "raylib_setwindowstate() not available on target platform");
}

// Clear window configuration state flags
void raylib_clearwindowstate(unsigned int flags)
{
    TRACELOG(LOG_WARNING, "raylib_clearwindowstate() not available on target platform");
}

// Set icon for window
void raylib_setwindowicon(raylib_image image)
{
    TRACELOG(LOG_WARNING, "raylib_setwindowicon() not available on target platform");
}

// Set icon for window
void raylib_setwindowicons(raylib_image *images, int count)
{
    TRACELOG(LOG_WARNING, "raylib_setwindowicons() not available on target platform");
}

// Set title for window
void raylib_setwindowtitle(const char *title)
{
    CORE.Window.title = title;
}

// Set window position on screen (windowed mode)
void raylib_setwindowposition(int x, int y)
{
    TRACELOG(LOG_WARNING, "raylib_setwindowposition() not available on target platform");
}

// Set monitor for the current window
void raylib_setwindowmonitor(int monitor)
{
    TRACELOG(LOG_WARNING, "raylib_setwindowmonitor() not available on target platform");
}

// Set window minimum dimensions (FLAG_WINDOW_RESIZABLE)
void raylib_setwindowminsize(int width, int height)
{
    CORE.Window.screenMin.width = width;
    CORE.Window.screenMin.height = height;
}

// Set window maximum dimensions (FLAG_WINDOW_RESIZABLE)
void raylib_setwindowmaxsize(int width, int height)
{
    CORE.Window.screenMax.width = width;
    CORE.Window.screenMax.height = height;
}

// Set window dimensions
void raylib_setwindowsize(int width, int height)
{
    TRACELOG(LOG_WARNING, "raylib_setwindowsize() not available on target platform");
}

// Set window opacity, value opacity is between 0.0 and 1.0
void raylib_setwindowopacity(float opacity)
{
    TRACELOG(LOG_WARNING, "raylib_setwindowopacity() not available on target platform");
}

// Set window focused
void raylib_setwindowfocused(void)
{
    TRACELOG(LOG_WARNING, "raylib_setwindowfocused() not available on target platform");
}

// Get native window handle
void *GetWindowHandle(void)
{
    TRACELOG(LOG_WARNING, "GetWindowHandle() not implemented on target platform");
    return NULL;
}

// Get number of monitors
int raylib_getmonitorcount(void)
{
    TRACELOG(LOG_WARNING, "raylib_getmonitorcount() not implemented on target platform");
    return 1;
}

// Get number of monitors
int raylib_getcurrentmonitor(void)
{
    TRACELOG(LOG_WARNING, "raylib_getcurrentmonitor() not implemented on target platform");
    return 0;
}

// Get selected monitor position
raylib_vector2 raylib_getmonitorposition(int monitor)
{
    TRACELOG(LOG_WARNING, "raylib_getmonitorposition() not implemented on target platform");
    return (raylib_vector2){ 0, 0 };
}

// Get selected monitor width (currently used by monitor)
int raylib_getmonitorwidth(int monitor)
{
    TRACELOG(LOG_WARNING, "raylib_getmonitorwidth() not implemented on target platform");
    return 0;
}

// Get selected monitor height (currently used by monitor)
int raylib_getmonitorheight(int monitor)
{
    TRACELOG(LOG_WARNING, "raylib_getmonitorheight() not implemented on target platform");
    return 0;
}

// Get selected monitor physical width in millimetres
int raylib_getmonitorphysicalwidth(int monitor)
{
    TRACELOG(LOG_WARNING, "raylib_getmonitorphysicalwidth() not implemented on target platform");
    return 0;
}

// Get selected monitor physical height in millimetres
int raylib_getmonitorphysicalheight(int monitor)
{
    TRACELOG(LOG_WARNING, "raylib_getmonitorphysicalheight() not implemented on target platform");
    return 0;
}

// Get selected monitor refresh rate
int raylib_getmonitorrefreshrate(int monitor)
{
    TRACELOG(LOG_WARNING, "raylib_getmonitorrefreshrate() not implemented on target platform");
    return 0;
}

// Get the human-readable, UTF-8 encoded name of the selected monitor
const char *raylib_getmonitorname(int monitor)
{
    TRACELOG(LOG_WARNING, "raylib_getmonitorname() not implemented on target platform");
    return "";
}

// Get window position XY on monitor
raylib_vector2 raylib_getwindowposition(void)
{
    TRACELOG(LOG_WARNING, "raylib_getwindowposition() not implemented on target platform");
    return (raylib_vector2){ 0, 0 };
}

// Get window scale DPI factor for current monitor
raylib_vector2 raylib_getwindowscaledpi(void)
{
    TRACELOG(LOG_WARNING, "raylib_getwindowscaledpi() not implemented on target platform");
    return (raylib_vector2){ 1.0f, 1.0f };
}

// Set clipboard text content
void raylib_setclipboardtext(const char *text)
{
    TRACELOG(LOG_WARNING, "raylib_setclipboardtext() not implemented on target platform");
}

// Get clipboard text content
// NOTE: returned string is allocated and freed by GLFW
const char *raylib_getclipboardtext(void)
{
    TRACELOG(LOG_WARNING, "raylib_getclipboardtext() not implemented on target platform");
    return NULL;
}

// Show mouse cursor
void raylib_show_cursor(void)
{
    CORE.Input.Mouse.cursorHidden = false;
}

// Hides mouse cursor
void raylib_hidecursor(void)
{
    CORE.Input.Mouse.cursorHidden = true;
}

// Enables cursor (unlock cursor)
void raylib_enablecursor(void)
{
    // Set cursor position in the middle
    raylib_setmouseposition(CORE.Window.screen.width/2, CORE.Window.screen.height/2);

    CORE.Input.Mouse.cursorHidden = false;
}

// Disables cursor (lock cursor)
void raylib_disablecursor(void)
{
    // Set cursor position in the middle
    raylib_setmouseposition(CORE.Window.screen.width/2, CORE.Window.screen.height/2);

    CORE.Input.Mouse.cursorHidden = true;
}

// Swap back buffer with front buffer (screen drawing)
void raylib_swapscreenbuffer(void)
{
    eglSwapBuffers(platform.device, platform.surface);
}

//----------------------------------------------------------------------------------
// Module Functions Definition: Misc
//----------------------------------------------------------------------------------

// Get elapsed time measure in seconds since InitTimer()
double raylib_gettime(void)
{
    double time = 0.0;
    struct timespec ts = { 0 };
    clock_gettime(CLOCK_MONOTONIC, &ts);
    unsigned long long int nanoSeconds = (unsigned long long int)ts.tv_sec*1000000000LLU + (unsigned long long int)ts.tv_nsec;

    time = (double)(nanoSeconds - CORE.Time.base)*1e-9;  // Elapsed time since InitTimer()

    return time;
}

// Open URL with default system browser (if available)
// NOTE: This function is only safe to use if you control the URL given.
// A user could craft a malicious string performing another action.
// Only call this function yourself not with user input or make sure to check the string yourself.
// Ref: https://github.com/raysan5/raylib/issues/686
void raylib_openurl(const char *url)
{
    // Security check to (partially) avoid malicious code on target platform
    if (strchr(url, '\'') != NULL) TRACELOG(LOG_WARNING, "SYSTEM: Provided URL could be potentially malicious, avoid [\'] character");
    else
    {
        // TODO:
    }
}

//----------------------------------------------------------------------------------
// Module Functions Definition: Inputs
//----------------------------------------------------------------------------------

// Set internal gamepad mappings
int raylib_setgamepadmappings(const char *mappings)
{
    TRACELOG(LOG_WARNING, "raylib_setgamepadmappings() not implemented on target platform");
    return 0;
}

// Set mouse position XY
void raylib_setmouseposition(int x, int y)
{
    CORE.Input.Mouse.currentPosition = (raylib_vector2){ (float)x, (float)y };
    CORE.Input.Mouse.previousPosition = CORE.Input.Mouse.currentPosition;
}

// Set mouse cursor
void raylib_setmousecursor(int cursor)
{
    TRACELOG(LOG_WARNING, "raylib_setmousecursor() not implemented on target platform");
}

// Register all input events
void raylib_pollinputevents(void)
{
#if defined(SUPPORT_GESTURES_SYSTEM)
    // NOTE: Gestures update must be called every frame to reset gestures correctly
    // because ProcessGestureEvent() is just called on an event, not every frame
    UpdateGestures();
#endif

    // Reset keys/chars pressed registered
    CORE.Input.Keyboard.keyPressedQueueCount = 0;
    CORE.Input.Keyboard.charPressedQueueCount = 0;

    // Reset key repeats
    for (int i = 0; i < MAX_KEYBOARD_KEYS; i++) CORE.Input.Keyboard.keyRepeatInFrame[i] = 0;

    // Reset last gamepad button/axis registered state
    CORE.Input.Gamepad.lastButtonPressed = 0; // GAMEPAD_BUTTON_UNKNOWN
    //CORE.Input.Gamepad.axisCount = 0;

    // Register previous touch states
    for (int i = 0; i < MAX_TOUCH_POINTS; i++) CORE.Input.Touch.previousTouchState[i] = CORE.Input.Touch.currentTouchState[i];

    // Reset touch positions
    // TODO: It resets on target platform the mouse position and not filled again until a move-event,
    // so, if mouse is not moved it returns a (0, 0) position... this behaviour should be reviewed!
    //for (int i = 0; i < MAX_TOUCH_POINTS; i++) CORE.Input.Touch.position[i] = (raylib_vector2){ 0, 0 };

    // Register previous keys states
    // NOTE: Android supports up to 260 keys
    for (int i = 0; i < 260; i++)
    {
        CORE.Input.Keyboard.previousKeyState[i] = CORE.Input.Keyboard.currentKeyState[i];
        CORE.Input.Keyboard.keyRepeatInFrame[i] = 0;
    }

    // TODO: Poll input events for current platform
}


//----------------------------------------------------------------------------------
// Module Internal Functions Definition
//----------------------------------------------------------------------------------

// Initialize platform: graphics, inputs and more
int InitPlatform(void)
{
    // TODO: Initialize graphic device: display/window
    // It usually requires setting up the platform display system configuration
    // and connexion with the GPU through some system graphic API
    // raylib uses OpenGL so, platform should create that kind of connection
    // Below example illustrates that process using EGL library
    //----------------------------------------------------------------------------
    CORE.Window.fullscreen = true;
    CORE.Window.flags |= FLAG_FULLSCREEN_MODE;

    EGLint samples = 0;
    EGLint sampleBuffer = 0;
    if (CORE.Window.flags & FLAG_MSAA_4X_HINT)
    {
        samples = 4;
        sampleBuffer = 1;
        TRACELOG(LOG_INFO, "DISPLAY: Trying to enable MSAA x4");
    }

    const EGLint framebufferAttribs[] =
    {
        EGL_RENDERABLE_TYPE, (rlGetVersion() == RL_OPENGL_ES_30)? EGL_OPENGL_ES3_BIT : EGL_OPENGL_ES2_BIT,      // Type of context support
        EGL_RED_SIZE, 8,            // raylib_red color bit depth (alternative: 5)
        EGL_GREEN_SIZE, 8,          // raylib_green color bit depth (alternative: 6)
        EGL_BLUE_SIZE, 8,           // raylib_blue color bit depth (alternative: 5)
        //EGL_TRANSPARENT_TYPE, EGL_NONE, // Request transparent framebuffer (EGL_TRANSPARENT_RGB does not work on RPI)
        EGL_DEPTH_SIZE, 16,         // Depth buffer size (Required to use Depth testing!)
        //EGL_STENCIL_SIZE, 8,      // Stencil buffer size
        EGL_SAMPLE_BUFFERS, sampleBuffer,    // Activate MSAA
        EGL_SAMPLES, samples,       // 4x Antialiasing if activated (Free on MALI GPUs)
        EGL_NONE
    };

    const EGLint contextAttribs[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    EGLint numConfigs = 0;

    // Get an EGL device connection
    platform.device = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (platform.device == EGL_NO_DISPLAY)
    {
        TRACELOG(LOG_WARNING, "DISPLAY: Failed to initialize EGL device");
        return false;
    }

    // Initialize the EGL device connection
    if (eglInitialize(platform.device, NULL, NULL) == EGL_FALSE)
    {
        // If all of the calls to eglInitialize returned EGL_FALSE then an error has occurred.
        TRACELOG(LOG_WARNING, "DISPLAY: Failed to initialize EGL device");
        return false;
    }

    // Get an appropriate EGL framebuffer configuration
    eglChooseConfig(platform.device, framebufferAttribs, &platform.config, 1, &numConfigs);

    // Set rendering API
    eglBindAPI(EGL_OPENGL_ES_API);

    // Create an EGL rendering context
    platform.context = eglCreateContext(platform.device, platform.config, EGL_NO_CONTEXT, contextAttribs);
    if (platform.context == EGL_NO_CONTEXT)
    {
        TRACELOG(LOG_WARNING, "DISPLAY: Failed to create EGL context");
        return -1;
    }

    // Create an EGL window surface
    EGLint displayFormat = 0;

    // EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is guaranteed to be accepted by ANativeWindow_setBuffersGeometry()
    // As soon as we picked a EGLConfig, we can safely reconfigure the ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID
    eglGetConfigAttrib(platform.device, platform.config, EGL_NATIVE_VISUAL_ID, &displayFormat);

    // Android specific call
    ANativeWindow_setBuffersGeometry(platform.app->window, 0, 0, displayFormat);       // Force use of native display size

    platform.surface = eglCreateWindowSurface(platform.device, platform.config, platform.app->window, NULL);

    // There must be at least one frame displayed before the buffers are swapped
    eglSwapInterval(platform.device, 1);

    EGLBoolean result = eglMakeCurrent(platform.device, platform.surface, platform.surface, platform.context);

    // Check surface and context activation
    if (result != EGL_FALSE)
    {
        CORE.Window.ready = true;

        CORE.Window.render.width = CORE.Window.screen.width;
        CORE.Window.render.height = CORE.Window.screen.height;
        CORE.Window.currentFbo.width = CORE.Window.render.width;
        CORE.Window.currentFbo.height = CORE.Window.render.height;

        TRACELOG(LOG_INFO, "DISPLAY: Device initialized successfully");
        TRACELOG(LOG_INFO, "    > Display size: %i x %i", CORE.Window.display.width, CORE.Window.display.height);
        TRACELOG(LOG_INFO, "    > Screen size:  %i x %i", CORE.Window.screen.width, CORE.Window.screen.height);
        TRACELOG(LOG_INFO, "    > Render size:  %i x %i", CORE.Window.render.width, CORE.Window.render.height);
        TRACELOG(LOG_INFO, "    > Viewport offsets: %i, %i", CORE.Window.renderOffset.x, CORE.Window.renderOffset.y);
    }
    else
    {
        TRACELOG(LOG_FATAL, "PLATFORM: Failed to initialize graphics device");
        return -1;
    }
    //----------------------------------------------------------------------------

    // If everything work as expected, we can continue
    CORE.Window.render.width = CORE.Window.screen.width;
    CORE.Window.render.height = CORE.Window.screen.height;
    CORE.Window.currentFbo.width = CORE.Window.render.width;
    CORE.Window.currentFbo.height = CORE.Window.render.height;

    TRACELOG(LOG_INFO, "DISPLAY: Device initialized successfully");
    TRACELOG(LOG_INFO, "    > Display size: %i x %i", CORE.Window.display.width, CORE.Window.display.height);
    TRACELOG(LOG_INFO, "    > Screen size:  %i x %i", CORE.Window.screen.width, CORE.Window.screen.height);
    TRACELOG(LOG_INFO, "    > Render size:  %i x %i", CORE.Window.render.width, CORE.Window.render.height);
    TRACELOG(LOG_INFO, "    > Viewport offsets: %i, %i", CORE.Window.renderOffset.x, CORE.Window.renderOffset.y);

    // TODO: Load OpenGL extensions
    // NOTE: GL procedures address loader is required to load extensions
    //----------------------------------------------------------------------------
    rlLoadExtensions(eglGetProcAddress);
    //----------------------------------------------------------------------------

    // TODO: Initialize input events system
    // It could imply keyboard, mouse, gamepad, touch...
    // Depending on the platform libraries/SDK it could use a callback mechanism
    // For system events and inputs evens polling on a per-frame basis, use raylib_pollinputevents()
    //----------------------------------------------------------------------------
    // ...
    //----------------------------------------------------------------------------

    // TODO: Initialize timing system
    //----------------------------------------------------------------------------
    InitTimer();
    //----------------------------------------------------------------------------

    // TODO: Initialize storage system
    //----------------------------------------------------------------------------
    CORE.Storage.basePath = raylib_getworkingdirectory();
    //----------------------------------------------------------------------------

    TRACELOG(LOG_INFO, "PLATFORM: CUSTOM: Initialized successfully");

    return 0;
}

// Close platform
void ClosePlatform(void)
{
    // TODO: De-initialize graphics, inputs and more
}

// EOF
