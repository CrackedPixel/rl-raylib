#!/bin/bash

replacements=(
    # colours
    LIGHTGRAY,raylib_lightgray
    GRAY,raylib_gray
    DARKGRAY,raylib_darkgray
    YELLOW,raylib_yellow
    GOLD,raylib_gold
    ORANGE,raylib_orange
    PINK,raylib_pink
    RED,raylib_red
    MAROON,raylib_maroon
    GREEN,raylib_green
    LIME,raylib_lime
    DARKGREEN,raylib_darkgreen
    SKYBLUE,raylib_skyblue
    BLUE,raylib_blue
    DARKBLUE,raylib_darkblue
    PURPLE,raylib_purple
    VIOLET,raylib_violet
    DARKPURPLE,raylib_darkpurple
    BEIGE,raylib_beige
    BROWN,raylib_brown
    DARKBROWN,raylib_darkbrown
    WHITE,raylib_white
    BLACK,raylib_black
    BLANK,raylib_blank
    MAGENTA,raylib_magenta
    RAYWHITE,raylib_raywhite

    # types
    Vector2,raylib_vector2
    Vector3,raylib_vector3
    Vector4,raylib_vector4
    Vector4,raylib_vector4
    Matrix,raylib_matrix
    Color,raylib_color
    Rectangle,raylib_rectangle
    Image,raylib_image
    Texture,raylib_texture
    Texture2D,raylib_texture2d
    TextureCubemap,raylib_texturecubemap
    RenderTexture,raylib_rendertexture
    RenderTexture2D,raylib_rendertexture2d
    NPatchInfo,raylib_npatchinfo
    GlyphInfo,raylib_glyphinfo
    Font,raylib_font
    Camera3D,raylib_camera3d
    Camera,raylib_camera
    Camera2D,raylib_camera2d
    Mesh,raylib_mesh
    Shader,raylib_shader
    MaterialMap,raylib_materialmap
    Material,raylib_material
    Transform,raylib_transform
    BoneInfo,raylib_boneinfo
    Model,raylib_model
    ModelAnimation,raylib_modelanimation
    Ray,raylib_ray
    RayCollision,raylib_raycollision
    BoundingBox,raylib_boundingbox
    Wave,raylib_wave
    rAudioBuffer,raylib_raudiobuffer
    rAudioProcessor,raylib_raudioprocessor
    AudioStream,raylib_audiostream
    Sound,raylib_sound
    Music,raylib_music
    VrDeviceInfo,raylib_vrdeviceinfo
    VrStereoConfig,raylib_vrstereoconfig
    FilePathList,raylib_filepathlist
    AutomationEvent,raylib_automationevent
    AutomationEventList,raylib_automationeventlist

    # enums
    ConfigFlags,raylib_configflags
    TraceLogLevel,raylib_traceloglevel
    KeyboardKey,raylib_keyboardkey
    MouseButton,raylib_mousebutton
    MouseCursor,raylib_mousecursor
    GamepadButton,raylib_gamepadbutton
    GamepadAxis,raylib_gamepadaxis
    MaterialMapIndex,raylib_materialmapindex
    ShaderLocationIndex,raylib_shaderlocationindex
    ShaderUniformDataType,raylib_shaderuniformdatatype
    ShaderAttributeDataType,raylib_shaderattributedatatype
    PixelFormat,raylib_pixelformat
    TextureFilter,raylib_texturefilter
    TextureWrap,raylib_texturewrap
    CubemapLayout,raylib_cubemaplayout
    FontType,raylib_fonttype
    BlendMode,raylib_blendmode
    Gesture,raylib_gesture
    CameraMode,raylib_cameramode
    CameraProjection,raylib_cameraprojection
    NPatchLayout,raylib_npatchlayout

    # callbacks
    TraceLogCallback,raylib_tracelogcallback
    LoadFileDataCallback,raylib_loadfiledatacallback
    SaveFileDataCallback,raylib_savefiledatacallback
    LoadFileTextCallback,raylib_loadfiletextcallback
    SaveFileTextCallback,raylib_savefiletextcallback

    #bugfix
    raylib_close_window,raylib_closewindow

    # window
    InitWindow,raylib_initwindow
    CloseWindow,raylib_closewindow
    WindowShouldClose,raylib_windowshouldclose
    IsWindowReady,raylib_iswindowready
    IsWindowFullscreen,raylib_iswindowfullscreen
    IsWindowHidden,raylib_iswindowhidden
    IsWindowMinimized,raylib_iswindowminimized
    IsWindowMaximized,raylib_iswindowmaximized
    IsWindowFocused,raylib_iswindowfocused
    IsWindowResized,raylib_iswindowresized
    IsWindowState,raylib_iswindowstate
    SetWindowState,raylib_setwindowstate
    ClearWindowState,raylib_clearwindowstate
    ToggleFullscreen,raylib_togglefullscreen
    ToggleBorderlessWindowed,raylib_toggleborderlesswindowed
    MaximizeWindow,raylib_maximizewindow
    MinimizeWindow,raylib_minimizewindow
    RestoreWindow,raylib_restorewindow
    SetWindowIcon,raylib_setwindowicon
    SetWindowIcons,raylib_setwindowicons
    SetWindowTitle,raylib_setwindowtitle
    SetWindowPosition,raylib_setwindowposition
    SetWindowMonitor,raylib_setwindowmonitor
    SetWindowMinSize,raylib_setwindowminsize
    SetWindowMaxSize,raylib_setwindowmaxsize
    SetWindowSize,raylib_setwindowsize
    SetWindowOpacity,raylib_setwindowopacity
    SetWindowFocused,raylib_setwindowfocused
    GetScreenWidth,raylib_getscreenwidth
    GetScreenHeight,raylib_getscreenheight
    GetRenderWidth,raylib_getrenderwidth
    GetRenderHeight,raylib_getrenderheight
    GetMonitorCount,raylib_getmonitorcount
    GetCurrentMonitor,raylib_getcurrentmonitor
    GetMonitorPosition,raylib_getmonitorposition
    GetMonitorWidth,raylib_getmonitorwidth
    GetMonitorHeight,raylib_getmonitorheight
    GetMonitorPhysicalWidth,raylib_getmonitorphysicalwidth
    GetMonitorPhysicalHeight,raylib_getmonitorphysicalheight
    GetMonitorRefreshRate,raylib_getmonitorrefreshrate
    GetWindowPosition,raylib_getwindowposition
    GetWindowScaleDPI,raylib_getwindowscaledpi
    GetMonitorName,raylib_getmonitorname
    SetClipboardText,raylib_setclipboardtext
    GetClipboardText,raylib_getclipboardtext
    EnableEventWaiting,raylib_enableeventwaiting
    DisableEventWaiting,raylib_disableeventwaiting

    # cursor
    ShowCursor,raylib_show_cursor
    HideCursor,raylib_hidecursor
    IsCursorHidden,raylib_iscursorhidden
    EnableCursor,raylib_enablecursor
    DisableCursor,raylib_disablecursor
    IsCursorOnScreen,raylib_iscursoronscreen

    # drawing
    ClearBackground,raylib_clearbackground
    BeginDrawing,raylib_begindrawing
    EndDrawing,raylib_enddrawing
    BeginMode2D,raylib_beginmode2d
    EndMode2D,raylib_endmode2d
    BeginMode3D,raylib_beginmode3d
    EndMode3D,raylib_endmode3d
    BeginTextureMode,raylib_begintexturemode
    EndTextureMode,raylib_endtexturemode
    BeginShaderMode,raylib_beginshadermode
    EndShaderMode,raylib_endshadermode
    BeginBlendMode,raylib_beginblendmode
    EndBlendMode,raylib_endblendmode
    BeginScissorMode,raylib_beginscissormode
    EndScissorMode,raylib_endscissormode
    BeginVrStereoMode,raylib_beginvrstereomode
    EndVrStereoMode,raylib_endvrstereomode

    # vr
    LoadVrStereoConfig,raylib_loadvrstereoconfig
    UnloadVrStereoConfig,raylib_unloadvrstereoconfig

    # shader
    LoadShader,raylib_loadshader
    LoadShaderFromMemory,raylib_loadshaderfrommemory
    IsShaderReady,raylib_isshaderready
    GetShaderLocation,raylib_getshaderlocation
    GetShaderLocationAttrib,raylib_getshaderlocationattrib
    SetShaderValue,raylib_setshadervalue
    SetShaderValueV,raylib_setshadervaluev
    SetShaderValueMatrix,raylib_setshadervaluematrix
    SetShaderValueTexture,raylib_setshadervaluetexture
    UnloadShader,raylib_unloadshader

    # screen space
    GetMouseRay,raylib_getmouseray
    GetScreenToWorldRay,raylib_getscreentoworldray
    GetScreenToWorldRay,raylib_getscreentoworldray
    GetScreenToWorldRayEx,raylib_getscreentoworldrayex
    GetWorldToScreen,raylib_getworldtoscreen
    GetWorldToScreenEx,raylib_getworldtoscreenex
    GetWorldToScreen2D,raylib_getworldtoscreen2d
    GetScreenToWorld2D,raylib_getscreentoworld2d
    GetCameraMatrix,raylib_getcameramatrix
    GetCameraMatrix2D,raylib_getcameramatrix2d

    # time
    SetTargetFPS,raylib_settargetfps
    GetFrameTime,raylib_getframetime
    GetTime,raylib_gettime
    GetFPS,raylib_getfps

    # frame control
    SwapScreenBuffer,raylib_swapscreenbuffer
    PollInputEvents,raylib_pollinputevents
    WaitTime,raylib_waittime

    # random value generation
    SetRandomSeed,raylib_setrandomseed
    GetRandomValue,raylib_getrandomvalue
    LoadRandomSequence,raylib_loadrandomsequence
    UnloadRandomSequence,raylib_unloadrandomsequence

    # misc
    TakeScreenshot,raylib_takescreenshot
    SetConfigFlags,raylib_setconfigflags
    OpenURL,raylib_openurl

    # utils
    TraceLog,raylib_tracelog
    SetTraceLogLevel,raylib_settraceloglevel
    MemAlloc,raylib_memalloc
    MemRealloc,raylib_memrealloc
    MemFree,raylib_memfree

    # custom callbacks
    SetTraceLogCallback,raylib_settracelogcallback
    SetLoadFileDataCallback,raylib_setloadfiledatacallback
    SetSaveFileDataCallback,raylib_setsavefiledatacallback
    SetLoadFileTextCallback,raylib_setloadfiletextcallback
    SetSaveFileTextCallback,raylib_setsavefiletextcallback

    # file management
    LoadFileData,raylib_loadfiledata
    UnloadFileData,raylib_unloadfiledata
    SaveFileData,raylib_savefiledata
    ExportDataAsCode,raylib_exportdataascode
    LoadFileText,raylib_loadfiletext
    UnloadFileText,raylib_unloadfiletext
    SaveFileText,raylib_savefiletext

    # file system
    FileExists,raylib_fileexists
    DirectoryExists,raylib_directoryexists
    IsFileExtension,raylib_isfileextension
    GetFileLength,raylib_getfilelength
    GetFileExtension,raylib_getfileextension
    GetFileName,raylib_getfilename
    GetFileNameWithoutExt,raylib_getfilenamewithoutext
    GetDirectoryPath,raylib_getdirectorypath
    GetPrevDirectoryPath,raylib_getprevdirectorypath
    GetWorkingDirectory,raylib_getworkingdirectory
    GetApplicationDirectory,raylib_getapplicationdirectory
    ChangeDirectory,raylib_changedirectory
    IsPathFile,raylib_ispathfile
    IsFileNameValid,raylib_isfilenamevalid
    LoadDirectoryFiles,raylib_loaddirectoryfiles
    LoadDirectoryFilesEx,raylib_loaddirectoryfilesex
    UnloadDirectoryFiles,raylib_unloaddirectoryfiles
    IsFileDropped,raylib_isfiledropped
    LoadDroppedFiles,raylib_loaddroppedfiles
    UnloadDroppedFiles,raylib_unloaddroppedfiles
    GetFileModTime,raylib_getfilemodtime
    CompressData,raylib_compressdata
    DecompressData,raylib_decompressdata
    EncodeDataBase64,raylib_encodedatabase64
    DecodeDataBase64,raylib_decodedatabase64

    # compression
    CompressData,raylib_compressdata
    DecompressData,raylib_decompressdata
    EncodeDataBase64,raylib_encodedatabase64
    DecodeDataBase64,raylib_decodedatabase64

    # automation
    LoadAutomationEventList,raylib_loadautomationeventlist
    UnloadAutomationEventList,raylib_unloadautomationeventlist
    ExportAutomationEventList,raylib_exportautomationeventlist
    SetAutomationEventList,raylib_setautomationeventlist
    SetAutomationEventBaseFrame,raylib_setautomationeventbaseframe
    StartAutomationEventRecording,raylib_startautomationeventrecording
    StopAutomationEventRecording,raylib_stopautomationeventrecording
    PlayAutomationEvent,raylib_playautomationevent

    # input - keyboard
    IsKeyPressed,raylib_iskeypressed
    IsKeyPressedRepeat,raylib_iskeypressedrepeat
    IsKeyDown,raylib_iskeydown
    IsKeyReleased,raylib_iskeyreleased
    IsKeyUp,raylib_iskeyup
    GetKeyPressed,raylib_getkeypressed
    GetCharPressed,raylib_getcharpressed
    SetExitKey,raylib_setexitkey

    # input - gamepad
    IsGamepadAvailable,raylib_isgamepadavailable
    GetGamepadName,raylib_getgamepadname
    IsGamepadButtonPressed,raylib_isgamepadbuttonpressed
    IsGamepadButtonDown,raylib_isgamepadbuttondown
    IsGamepadButtonReleased,raylib_isgamepadbuttonreleased
    IsGamepadButtonUp,raylib_isgamepadbuttonup
    GetGamepadButtonPressed,raylib_getgamepadbuttonpressed
    GetGamepadAxisCount,raylib_getgamepadaxiscount
    GetGamepadAxisMovement,raylib_getgamepadaxismovement
    SetGamepadMappings,raylib_setgamepadmappings
    SetGamepadVibration,raylib_setgamepadvibration

    # input - mouse
    IsMouseButtonPressed,raylib_ismousebuttonpressed
    IsMouseButtonDown,raylib_ismousebuttondown
    IsMouseButtonReleased,raylib_ismousebuttonreleased
    IsMouseButtonUp,raylib_ismousebuttonup
    GetMouseX,raylib_getmousex
    GetMouseY,raylib_getmousey
    GetMousePosition,raylib_getmouseposition
    GetMouseDelta,raylib_getmousedelta
    SetMousePosition,raylib_setmouseposition
    SetMouseOffset,raylib_setmouseoffset
    SetMouseScale,raylib_setmousescale
    GetMouseWheelMove,raylib_getmousewheelmove
    GetMouseWheelMoveV,raylib_getmousewheelmovev
    SetMouseCursor,raylib_setmousecursor

    # input - touch
    GetTouchX,raylib_gettouchx
    GetTouchY,raylib_gettouchy
    GetTouchPosition,raylib_gettouchposition
    GetTouchPointId,raylib_gettouchpointid
    GetTouchPointCount,raylib_gettouchpointcount

    # input - gestures
    SetGesturesEnabled,raylib_setgesturesenabled
    IsGestureDetected,raylib_isgesturedetected
    GetGestureDetected,raylib_getgesturedetected
    GetGestureHoldDuration,raylib_getgestureholdduration
    GetGestureDragVector,raylib_getgesturedragvector
    GetGestureDragAngle,raylib_getgesturedragangle
    GetGesturePinchVector,raylib_getgesturepinchvector
    GetGesturePinchAngle,raylib_getgesturepinchangle

    # camera
    UpdateCamera,raylib_updatecamera
    UpdateCameraPro,raylib_updatecamerapro

    # basic shapes
    SetShapesTexture,raylib_setshapestexture
    GetShapesTexture,raylib_getshapestexture
    GetShapesTextureRectangle,raylib_getshapestexturerectangle
    DrawPixel,raylib_drawpixel
    DrawPixelV,raylib_drawpixelv
    DrawLine,raylib_drawline
    DrawLineV,raylib_drawlinev
    DrawLineEx,raylib_drawlineex
    DrawLineStrip,raylib_drawlinestrip
    DrawLineBezier,raylib_drawlinebezier
    DrawCircle,raylib_drawcircle
    DrawCircleSector,raylib_drawcirclesector
    DrawCircleSectorLines,raylib_drawcirclesectorlines
    DrawCircleGradient,raylib_drawcirclegradient
    DrawCircleV,raylib_drawcirclev
    DrawCircleLines,raylib_drawcirclelines
    DrawCircleLinesV,raylib_drawcirclelinesv
    DrawEllipse,raylib_drawellipse
    DrawEllipseLines,raylib_drawellipselines
    DrawRing,raylib_drawring
    DrawRingLines,raylib_drawringlines
    DrawRectangle,raylib_drawrectangle
    DrawRectangleV,raylib_drawrectanglev
    DrawRectangleRec,raylib_drawrectanglerec
    DrawRectanglePro,raylib_drawrectanglepro
    DrawRectangleGradientV,raylib_drawrectanglegradientv
    DrawRectangleGradientH,raylib_drawrectanglegradienth
    DrawRectangleGradientEx,raylib_drawrectanglegradientex
    DrawRectangleLines,raylib_drawrectanglelines
    DrawRectangleLinesEx,raylib_drawrectanglelinesex
    DrawRectangleRounded,raylib_drawrectanglerounded
    DrawRectangleRoundedLines,raylib_drawrectangleroundedlines
    DrawRectangleRoundedLinesEx,raylib_drawrectangleroundedlinesex
    DrawTriangle,raylib_drawtriangle
    DrawTriangleLines,raylib_drawtrianglelines
    DrawTriangleFan,raylib_drawtrianglefan
    DrawTriangleStrip,raylib_drawtrianglestrip
    DrawPoly,raylib_drawpoly
    DrawPolyLines,raylib_drawpolylines
    DrawPolyLinesEx,raylib_drawpolylinesex

    # splines - drawing
    DrawSplineLinear,raylib_drawsplinelinear
    DrawSplineBasis,raylib_drawsplinebasis
    DrawSplineCatmullRom,raylib_drawsplinecatmullrom
    DrawSplineBezierQuadratic,raylib_drawsplinebezierquadratic
    DrawSplineBezierCubic,raylib_drawsplinebeziercubic
    DrawSplineSegmentLinear,raylib_drawsplinesegmentlinear
    DrawSplineSegmentBasis,raylib_drawsplinesegmentbasis
    DrawSplineSegmentCatmullRom,raylib_drawsplinesegmentcatmullrom
    DrawSplineSegmentBezierQuadratic,raylib_drawsplinesegmentbezierquadratic
    DrawSplineSegmentBezierCubic,raylib_drawsplinesegmentbeziercubic

    # splines - segment point evaluation functions
    GetSplinePointLinear,raylib_getsplinepointlinear
    GetSplinePointBasis,raylib_getsplinepointbasis
    GetSplinePointCatmullRom,raylib_getsplinepointcatmullrom
    GetSplinePointBezierQuad,raylib_getsplinepointbezierquad
    GetSplinePointBezierCubic,raylib_getsplinepointbeziercubic

    # basic shapes collision
    CheckCollisionRecs,raylib_checkcollisionrecs
    CheckCollisionCircles,raylib_checkcollisioncircles
    CheckCollisionCircleRec,raylib_checkcollisioncirclerec
    CheckCollisionPointRec,raylib_checkcollisionpointrec
    CheckCollisionPointCircle,raylib_checkcollisionpointcircle
    CheckCollisionPointTriangle,raylib_checkcollisionpointtriangle
    CheckCollisionPointPoly,raylib_checkcollisionpointpoly
    CheckCollisionLines,raylib_checkcollisionlines
    CheckCollisionPointLine,raylib_checkcollisionpointline
    CheckCollisionCircleLine,raylib_checkcollisioncircleline
    GetCollisionRec,raylib_getcollisionrec

    # image loading
    LoadImage,raylib_load_image
    LoadImageRaw,raylib_loadimageraw
    LoadImageSvg,raylib_loadimagesvg
    LoadImageAnim,raylib_loadimageanim
    LoadImageAnimFromMemory,raylib_loadimageanimfrommemory
    LoadImageFromMemory,raylib_loadimagefrommemory
    LoadImageFromTexture,raylib_loadimagefromtexture
    LoadImageFromScreen,raylib_loadimagefromscreen
    IsImageReady,raylib_isimageready
    UnloadImage,raylib_unloadimage
    ExportImage,raylib_exportimage
    ExportImageToMemory,raylib_exportimagetomemory
    ExportImageAsCode,raylib_exportimageascode

    # image generation
    GenImageColor,raylib_genimagecolor
    GenImageGradientLinear,raylib_genimagegradientlinear
    GenImageGradientRadial,raylib_genimagegradientradial
    GenImageGradientSquare,raylib_genimagegradientsquare
    GenImageChecked,raylib_genimagechecked
    GenImageWhiteNoise,raylib_genimagewhitenoise
    GenImagePerlinNoise,raylib_genimageperlinnoise
    GenImageCellular,raylib_genimagecellular
    GenImageText,raylib_genimagetext

    # image manipulation
    ImageCopy,raylib_imagecopy
    ImageFromImage,raylib_imagefromimage
    ImageText,raylib_imagetext
    ImageTextEx,raylib_imagetextex
    ImageFormat,raylib_imageformat
    ImageToPOT,raylib_imagetopot
    ImageCrop,raylib_imagecrop
    ImageAlphaCrop,raylib_imagealphacrop
    ImageAlphaClear,raylib_imagealphaclear
    ImageAlphaMask,raylib_imagealphamask
    ImageAlphaPremultiply,raylib_imagealphapremultiply
    ImageBlurGaussian,raylib_imageblurgaussian
    ImageKernelConvolution,raylib_imagekernelconvolution
    ImageResize,raylib_imageresize
    ImageResizeNN,raylib_imageresizenn
    ImageResizeCanvas,raylib_imageresizecanvas
    ImageMipmaps,raylib_imagemipmaps
    ImageDither,raylib_imagedither
    ImageFlipVertical,raylib_imageflipvertical
    ImageFlipHorizontal,raylib_imagefliphorizontal
    ImageRotate,raylib_imagerotate
    ImageRotateCW,raylib_imagerotatecw
    ImageRotateCCW,raylib_imagerotateccw
    ImageColorTint,raylib_imagecolortint
    ImageColorInvert,raylib_imagecolorinvert
    ImageColorGrayscale,raylib_imagecolorgrayscale
    ImageColorContrast,raylib_imagecolorcontrast
    ImageColorBrightness,raylib_imagecolorbrightness
    ImageColorReplace,raylib_imagecolorreplace
    LoadImageColors,raylib_loadimagecolors
    LoadImagePalette,raylib_loadimagepalette
    UnloadImageColors,raylib_unloadimagecolors
    UnloadImagePalette,raylib_unloadimagepalette
    GetImageAlphaBorder,raylib_getimagealphaborder
    GetImageColor,raylib_getimagecolor

    # image drawing
    ImageClearBackground,raylib_imageclearbackground
    ImageDrawPixel,raylib_imagedrawpixel
    ImageDrawPixelV,raylib_imagedrawpixelv
    ImageDrawLine,raylib_imagedrawline
    ImageDrawLineV,raylib_imagedrawlinev
    ImageDrawCircle,raylib_imagedrawcircle
    ImageDrawCircleV,raylib_imagedrawcirclev
    ImageDrawCircleLines,raylib_imagedrawcirclelines
    ImageDrawCircleLinesV,raylib_imagedrawcirclelinesv
    ImageDrawRectangle,raylib_imagedrawrectangle
    ImageDrawRectangleV,raylib_imagedrawrectanglev
    ImageDrawRectangleRec,raylib_imagedrawrectanglerec
    ImageDrawRectangleLines,raylib_imagedrawrectanglelines
    ImageDrawTriangle,raylib_imagedrawtriangle
    ImageDrawTriangleEx,raylib_imagedrawtriangleex
    ImageDrawTriangleLines,raylib_imagedrawtrianglelines
    ImageDrawTriangleFan,raylib_imagedrawtrianglefan
    ImageDrawTriangleStrip,raylib_imagedrawtrianglestrip
    ImageDraw,raylib_imagedraw
    ImageDrawText,raylib_imagedrawtext
    ImageDrawTextEx,raylib_imagedrawtextex

    # texture loading
    LoadTexture,raylib_loadtexture
    LoadTextureFromImage,raylib_loadtexturefromimage
    LoadTextureCubemap,raylib_loadtexturecubemap
    LoadRenderTexture,raylib_loadrendertexture
    IsTextureReady,raylib_istextureready
    UnloadTexture,raylib_unloadtexture
    IsRenderTextureReady,raylib_isrendertextureready
    UnloadRenderTexture,raylib_unloadrendertexture
    UpdateTexture,raylib_updatetexture
    UpdateTextureRec,raylib_updatetexturerec

    # texture configuration
    GenTextureMipmaps,raylib_gentexturemipmaps
    SetTextureFilter,raylib_settexturefilter
    SetTextureWrap,raylib_settexturewrap

    # texture drawing
    DrawTexture,raylib_drawtexture
    DrawTextureV,raylib_drawtexturev
    DrawTextureEx,raylib_drawtextureex
    DrawTextureRec,raylib_drawtexturerec
    DrawTexturePro,raylib_drawtexturepro
    DrawTextureNPatch,raylib_drawtexturenpatch

    # color / pixel functions
    ColorIsEqual,raylib_colorisequal
    Fade,raylib_fade
    ColorToInt,raylib_colortoint
    ColorNormalize,raylib_colornormalize
    ColorFromNormalized,raylib_colorfromnormalized
    ColorToHSV,raylib_colortohsv
    ColorFromHSV,raylib_colorfromhsv
    ColorTint,raylib_colortint
    ColorBrightness,raylib_colorbrightness
    ColorContrast,raylib_colorcontrast
    ColorAlpha,raylib_coloralpha
    ColorAlphaBlend,raylib_coloralphablend
    GetColor,raylib_getcolor
    GetPixelColor,raylib_getpixelcolor
    SetPixelColor,raylib_setpixelcolor
    GetPixelDataSize,raylib_getpixeldatasize

    # font loading
    GetFontDefault,raylib_getfontdefault
    LoadFont,raylib_loadfont
    LoadFontEx,raylib_loadfontex
    LoadFontFromImage,raylib_loadfontfromimage
    LoadFontFromMemory,raylib_loadfontfrommemory
    IsFontReady,raylib_isfontready
    LoadFontData,raylib_loadfontdata
    GenImageFontAtlas,raylib_genimagefontatlas
    UnloadFontData,raylib_unloadfontdata
    UnloadFont,raylib_unloadfont
    ExportFontAsCode,raylib_exportfontascode

    # text drawing
    DrawFPS,raylib_drawfps
    DrawText,raylib_draw_text
    DrawTextEx,raylib_draw_text_ex
    DrawTextPro,raylib_drawtextpro
    DrawTextCodepoint,raylib_drawtextcodepoint
    DrawTextCodepoints,raylib_drawtextcodepoints

    # text font info
    SetTextLineSpacing,raylib_settextlinespacing
    MeasureText,raylib_measuretext
    MeasureTextEx,raylib_measuretextex
    GetGlyphIndex,raylib_getglyphindex
    GetGlyphInfo,raylib_getglyphinfo
    GetGlyphAtlasRec,raylib_getglyphatlasrec

    # text codepoints
    LoadUTF8,raylib_loadutf8
    UnloadUTF8,raylib_unloadutf8
    LoadCodepoints,raylib_loadcodepoints
    UnloadCodepoints,raylib_unloadcodepoints
    GetCodepointCount,raylib_getcodepointcount
    GetCodepoint,raylib_getcodepoint
    GetCodepointNext,raylib_getcodepointnext
    GetCodepointPrevious,raylib_getcodepointprevious
    CodepointToUTF8,raylib_codepointtoutf8

    # text strings management
    TextCopy,raylib_textcopy
    TextIsEqual,raylib_textisequal
    TextLength,raylib_textlength
    TextFormat,raylib_textformat
    TextSubtext,raylib_textsubtext
    TextReplace,raylib_textreplace
    TextInsert,raylib_textinsert
    TextJoin,raylib_textjoin
    TextAppend,raylib_textappend
    TextFindIndex,raylib_textfindindex
    TextToUpper,raylib_texttoupper
    TextToLower,raylib_texttolower
    TextToPascal,raylib_texttopascal
    TextToSnake,raylib_texttosnake
    TextToCamel,raylib_texttocamel
    TextToInteger,raylib_texttointeger
    TextToFloat,raylib_texttofloat

    # basic geometric 3d
    DrawLine3D,raylib_drawline3d
    DrawPoint3D,raylib_drawpoint3d
    DrawCircle3D,raylib_drawcircle3d
    DrawTriangle3D,raylib_drawtriangle3d
    DrawTriangleStrip3D,raylib_drawtrianglestrip3d
    DrawCube,raylib_drawcube
    DrawCubeV,raylib_drawcubev
    DrawCubeWires,raylib_drawcubewires
    DrawCubeWiresV,raylib_drawcubewiresv
    DrawSphere,raylib_drawsphere
    DrawSphereEx,raylib_drawsphereex
    DrawSphereWires,raylib_drawspherewires
    DrawCylinder,raylib_drawcylinder
    DrawCylinderEx,raylib_drawcylinderex
    DrawCylinderWires,raylib_drawcylinderwires
    DrawCylinderWiresEx,raylib_drawcylinderwiresex
    DrawCapsule,raylib_drawcapsule
    DrawCapsuleWires,raylib_drawcapsulewires
    DrawPlane,raylib_drawplane
    DrawRay,raylib_drawray
    DrawGrid,raylib_drawgrid

    # model management
    LoadModel,raylib_loadmodel
    LoadModelFromMesh,raylib_loadmodelfrommesh
    IsModelReady,raylib_ismodelready
    UnloadModel,raylib_unloadmodel
    GetModelBoundingBox,raylib_getmodelboundingbox

    # model drawing
    DrawModel,raylib_drawmodel
    DrawModelEx,raylib_drawmodelex
    DrawModelWires,raylib_drawmodelwires
    DrawModelWiresEx,raylib_drawmodelwiresex
    DrawBoundingBox,raylib_drawboundingbox
    DrawBillboard,raylib_drawbillboard
    DrawBillboardRec,raylib_drawbillboardrec
    DrawBillboardPro,raylib_drawbillboardpro

    # mesh management
    UploadMesh,raylib_uploadmesh
    UpdateMeshBuffer,raylib_updatemeshbuffer
    UnloadMesh,raylib_unloadmesh
    DrawMesh,raylib_drawmesh
    DrawMeshInstanced,raylib_drawmeshinstanced
    GetMeshBoundingBox,raylib_getmeshboundingbox
    GenMeshTangents,raylib_genmeshtangents
    ExportMesh,raylib_exportmesh
    ExportMeshAsCode,raylib_exportmeshascode

    # mesh generation
    GenMeshPoly,raylib_genmeshpoly
    GenMeshPlane,raylib_genmeshplane
    GenMeshCube,raylib_genmeshcube
    GenMeshSphere,raylib_genmeshsphere
    GenMeshHemiSphere,raylib_genmeshhemisphere
    GenMeshCylinder,raylib_genmeshcylinder
    GenMeshCone,raylib_genmeshcone
    GenMeshTorus,raylib_genmeshtorus
    GenMeshKnot,raylib_genmeshknot
    GenMeshHeightmap,raylib_genmeshheightmap
    GenMeshCubicmap,raylib_genmeshcubicmap

    # material loading
    LoadMaterials,raylib_loadmaterials
    LoadMaterialDefault,raylib_loadmaterialdefault
    IsMaterialReady,raylib_ismaterialready
    UnloadMaterial,raylib_unloadmaterial
    SetMaterialTexture,raylib_setmaterialtexture
    SetModelMeshMaterial,raylib_setmodelmeshmaterial

    # model animation
    LoadModelAnimations,raylib_loadmodelanimations
    UpdateModelAnimation,raylib_updatemodelanimation
    UnloadModelAnimation,raylib_unloadmodelanimation
    UnloadModelAnimations,raylib_unloadmodelanimations
    IsModelAnimationValid,raylib_ismodelanimationvalid

    # collision detection
    CheckCollisionSpheres,raylib_checkcollisionspheres
    CheckCollisionBoxes,raylib_checkcollisionboxes
    CheckCollisionBoxSphere,raylib_checkcollisionboxsphere
    GetRayCollisionSphere,raylib_getraycollisionsphere
    GetRayCollisionBox,raylib_getraycollisionbox
    GetRayCollisionMesh,raylib_getraycollisionmesh
    GetRayCollisionTriangle,raylib_getraycollisiontriangle
    GetRayCollisionQuad,raylib_getraycollisionquad

    # audio device management
    InitAudioDevice,raylib_initaudiodevice
    CloseAudioDevice,raylib_closeaudiodevice
    IsAudioDeviceReady,raylib_isaudiodeviceready
    SetMasterVolume,raylib_setmastervolume
    GetMasterVolume,raylib_getmastervolume

    # wave / sound loading
    LoadWave,raylib_loadwave
    LoadWaveFromMemory,raylib_loadwavefrommemory
    IsWaveReady,raylib_iswaveready
    LoadSound,raylib_loadsound
    LoadSoundFromWave,raylib_loadsoundfromwave
    LoadSoundAlias,raylib_loadsoundalias
    IsSoundReady,raylib_issoundready
    UpdateSound,raylib_updatesound
    UnloadWave,raylib_unloadwave
    UnloadSound,raylib_unloadsound
    UnloadSoundAlias,raylib_unloadsoundalias
    ExportWave,raylib_exportwave
    ExportWaveAsCode,raylib_exportwaveascode

    # wave / sound management
    PlaySound,raylib_play_sound
    StopSound,raylib_stopsound
    PauseSound,raylib_pausesound
    ResumeSound,raylib_resumesound
    IsSoundPlaying,raylib_issoundplaying
    SetSoundVolume,raylib_setsoundvolume
    SetSoundPitch,raylib_setsoundpitch
    SetSoundPan,raylib_setsoundpan
    WaveCopy,raylib_wavecopy
    WaveCrop,raylib_wavecrop
    WaveFormat,raylib_waveformat
    LoadWaveSamples,raylib_loadwavesamples
    UnloadWaveSamples,raylib_unloadwavesamples

    # music management
    LoadMusicStream,raylib_loadmusicstream
    LoadMusicStreamFromMemory,raylib_loadmusicstreamfrommemory
    IsMusicReady,raylib_ismusicready
    UnloadMusicStream,raylib_unloadmusicstream
    PlayMusicStream,raylib_playmusicstream
    IsMusicStreamPlaying,raylib_ismusicstreamplaying
    UpdateMusicStream,raylib_updatemusicstream
    StopMusicStream,raylib_stopmusicstream
    PauseMusicStream,raylib_pausemusicstream
    ResumeMusicStream,raylib_resumemusicstream
    SeekMusicStream,raylib_seekmusicstream
    SetMusicVolume,raylib_setmusicvolume
    SetMusicPitch,raylib_setmusicpitch
    SetMusicPan,raylib_setmusicpan
    GetMusicTimeLength,raylib_getmusictimelength
    GetMusicTimePlayed,raylib_getmusictimeplayed

    # audio stream management
    LoadAudioStream,raylib_loadaudiostream
    IsAudioStreamReady,raylib_isaudiostreamready
    UnloadAudioStream,raylib_unloadaudiostream
    UpdateAudioStream,raylib_updateaudiostream
    IsAudioStreamProcessed,raylib_isaudiostreamprocessed
    PlayAudioStream,raylib_playaudiostream
    PauseAudioStream,raylib_pauseaudiostream
    ResumeAudioStream,raylib_resumeaudiostream
    IsAudioStreamPlaying,raylib_isaudiostreamplaying
    StopAudioStream,raylib_stopaudiostream
    SetAudioStreamVolume,raylib_setaudiostreamvolume
    SetAudioStreamPitch,raylib_setaudiostreampitch
    SetAudioStreamPan,raylib_setaudiostreampan
    SetAudioStreamBufferSizeDefault,raylib_setaudiostreambuffersizedefault
    SetAudioStreamCallback,raylib_setaudiostreamcallback
    AttachAudioStreamProcessor,raylib_attachaudiostreamprocessor
    DetachAudioStreamProcessor,raylib_detachaudiostreamprocessor
    AttachAudioMixedProcessor,raylib_attachaudiomixedprocessor
    DetachAudioMixedProcessor,raylib_detachaudiomixedprocessor
)

for pair in "${replacements[@]}"; do
    search_for=$(echo "$pair" | cut -d',' -f1)
    replace_with=$(echo "$pair" | cut -d',' -f2)

    sed -i "s/\\<$search_for\\>/$replace_with/g" ./src/*.h
    sed -i "s/\\<$search_for\\>/$replace_with/g" ./src/*.c
    sed -i "s/\\<$search_for\\>/$replace_with/g" ./src/**/*.h
    sed -i "s/\\<$search_for\\>/$replace_with/g" ./src/**/*.c
done
