#!/bin/bash

replacements=(
    # colours
    LIGHTGRAY,RL_LIGHTGRAY
    GRAY,RL_GRAY
    DARKGRAY,RL_DARKGRAY
    YELLOW,RL_YELLOW
    GOLD,RL_GOLD
    ORANGE,RL_ORANGE
    PINK,RL_PINK
    RED,RL_RED
    MAROON,RL_MAROON
    GREEN,RL_GREEN
    LIME,RL_LIME
    DARKGREEN,RL_DARKGREEN
    SKYBLUE,RL_SKYBLUE
    BLUE,RL_BLUE
    DARKBLUE,RL_DARKBLUE
    PURPLE,RL_PURPLE
    VIOLET,RL_VIOLET
    DARKPURPLE,RL_DARKPURPLE
    BEIGE,RL_BEIGE
    BROWN,RL_BROWN
    DARKBROWN,RL_DARKBROWN
    WHITE,RL_WHITE
    BLACK,RL_BLACK
    BLANK,RL_BLANK
    MAGENTA,RL_MAGENTA
    RAYWHITE,RL_RAYWHITE

    # types
    Vector2,RL_Vector2
    Vector3,RL_Vector3
    Vector4,RL_Vector4
    Vector4,RL_Vector4
    Quaternion,RL_Quaternion
    Matrix,RL_Matrix
    Color,RL_Color
    Rectangle,RL_Rectangle
    Image,RL_Image
    Texture,RL_Texture
    Texture2D,RL_Texture2D
    TextureCubemap,RL_TextureCubemap
    RenderTexture,RL_RenderTexture
    RenderTexture2D,RL_RenderTexture2D
    NPatchInfo,RL_NPatchInfo
    GlyphInfo,RL_GlyphInfo
    Font,RL_Font
    Camera3D,RL_Camera3D
    Camera,RL_Camera
    Camera2D,RL_Camera2D
    Mesh,RL_Mesh
    Shader,RL_Shader
    MaterialMap,RL_MaterialMap
    Material,RL_Material
    Transform,RL_Transform
    BoneInfo,RL_BoneInfo
    Model,RL_Model
    ModelAnimation,RL_ModelAnimation
    Ray,RL_Ray
    RayCollision,RL_RayCollision
    BoundingBox,RL_BoundingBox
    Wave,RL_Wave
    rAudioBuffer,RL_rAudioBuffer
    rAudioProcessor,RL_rAudioProcessor
    AudioStream,RL_AudioStream
    Sound,RL_Sound
    Music,RL_Music
    VrDeviceInfo,RL_VrDeviceInfo
    VrStereoConfig,RL_VrStereoConfig
    FilePathList,RL_FilePathList
    AutomationEvent,RL_AutomationEvent
    AutomationEventList,RL_AutomationEventList

    # enums
    ConfigFlags,RL_ConfigFlags
    TraceLogLevel,RL_TraceLogLevel
    KeyboardKey,RL_KeyboardKey
    MouseButton,RL_MouseButton
    MouseCursor,RL_MouseCursor
    GamepadButton,RL_GamepadButton
    GamepadAxis,RL_GamepadAxis
    MaterialMapIndex,RL_MaterialMapIndex
    ShaderLocationIndex,RL_ShaderLocationIndex
    ShaderUniformDataType,RL_ShaderUniformDataType
    ShaderAttributeDataType,RL_ShaderAttributeDataType
    PixelFormat,RL_PixelFormat
    TextureFilter,RL_TextureFilter
    TextureWrap,RL_TextureWrap
    CubemapLayout,RL_CubemapLayout
    FontType,RL_FontType
    BlendMode,RL_BlendMode
    Gesture,RL_Gesture
    CameraMode,RL_CameraMode
    CameraProjection,RL_CameraProjection
    NPatchLayout,RL_NPatchLayout

    # callbacks
    TraceLogCallback,RL_TraceLogCallback
    LoadFileDataCallback,RL_LoadFileDataCallback
    SaveFileDataCallback,RL_SaveFileDataCallback
    LoadFileTextCallback,RL_LoadFileTextCallback
    SaveFileTextCallback,RL_SaveFileTextCallback

    #bugfix
    raylib_close_window,RL_raylib_close_window

    # window
    InitWindow,RL_InitWindow
    CloseWindow,RL_CloseWindow
    WindowShouldClose,RL_WindowShouldClose
    IsWindowReady,RL_IsWindowReady
    IsWindowFullscreen,RL_IsWindowFullscreen
    IsWindowHidden,RL_IsWindowHidden
    IsWindowMinimized,RL_IsWindowMinimized
    IsWindowMaximized,RL_IsWindowMaximized
    IsWindowFocused,RL_IsWindowFocused
    IsWindowResized,RL_IsWindowResized
    IsWindowState,RL_IsWindowState
    SetWindowState,RL_SetWindowState
    ClearWindowState,RL_ClearWindowState
    ToggleFullscreen,RL_ToggleFullscreen
    ToggleBorderlessWindowed,RL_ToggleBorderlessWindowed
    MaximizeWindow,RL_MaximizeWindow
    MinimizeWindow,RL_MinimizeWindow
    RestoreWindow,RL_RestoreWindow
    SetWindowIcon,RL_SetWindowIcon
    SetWindowIcons,RL_SetWindowIcons
    SetWindowTitle,RL_SetWindowTitle
    SetWindowPosition,RL_SetWindowPosition
    SetWindowMonitor,RL_SetWindowMonitor
    SetWindowMinSize,RL_SetWindowMinSize
    SetWindowMaxSize,RL_SetWindowMaxSize
    SetWindowSize,RL_SetWindowSize
    SetWindowOpacity,RL_SetWindowOpacity
    SetWindowFocused,RL_SetWindowFocused
    GetWindowHandle,RL_GetWindowHandle
    GetScreenWidth,RL_GetScreenWidth
    GetScreenHeight,RL_GetScreenHeight
    GetRenderWidth,RL_GetRenderWidth
    GetRenderHeight,RL_GetRenderHeight
    GetMonitorCount,RL_GetMonitorCount
    GetCurrentMonitor,RL_GetCurrentMonitor
    GetMonitorPosition,RL_GetMonitorPosition
    GetMonitorWidth,RL_GetMonitorWidth
    GetMonitorHeight,RL_GetMonitorHeight
    GetMonitorPhysicalWidth,RL_GetMonitorPhysicalWidth
    GetMonitorPhysicalHeight,RL_GetMonitorPhysicalHeight
    GetMonitorRefreshRate,RL_GetMonitorRefreshRate
    GetWindowPosition,RL_GetWindowPosition
    GetWindowScaleDPI,RL_GetWindowScaleDPI
    GetMonitorName,RL_GetMonitorName
    SetClipboardText,RL_SetClipboardText
    GetClipboardText,RL_GetClipboardText
    EnableEventWaiting,RL_EnableEventWaiting
    DisableEventWaiting,RL_DisableEventWaiting

    # cursor
    ShowCursor,RL_ShowCursor
    HideCursor,RL_HideCursor
    IsCursorHidden,RL_IsCursorHidden
    EnableCursor,RL_EnableCursor
    DisableCursor,RL_DisableCursor
    IsCursorOnScreen,RL_IsCursorOnScreen

    # drawing
    ClearBackground,RL_ClearBackground
    BeginDrawing,RL_BeginDrawing
    EndDrawing,RL_EndDrawing
    BeginMode2D,RL_BeginMode2D
    EndMode2D,RL_EndMode2D
    BeginMode3D,RL_BeginMode3D
    EndMode3D,RL_EndMode3D
    BeginTextureMode,RL_BeginTextureMode
    EndTextureMode,RL_EndTextureMode
    BeginShaderMode,RL_BeginShaderMode
    EndShaderMode,RL_EndShaderMode
    BeginBlendMode,RL_BeginBlendMode
    EndBlendMode,RL_EndBlendMode
    BeginScissorMode,RL_BeginScissorMode
    EndScissorMode,RL_EndScissorMode
    BeginVrStereoMode,RL_BeginVrStereoMode
    EndVrStereoMode,RL_EndVrStereoMode

    # vr
    LoadVrStereoConfig,RL_LoadVrStereoConfig
    UnloadVrStereoConfig,RL_UnloadVrStereoConfig

    # shader
    LoadShader,RL_LoadShader
    LoadShaderFromMemory,RL_LoadShaderFromMemory
    IsShaderReady,RL_IsShaderReady
    GetShaderLocation,RL_GetShaderLocation
    GetShaderLocationAttrib,RL_GetShaderLocationAttrib
    SetShaderValue,RL_SetShaderValue
    SetShaderValueV,RL_SetShaderValueV
    SetShaderValueMatrix,RL_SetShaderValueMatrix
    SetShaderValueTexture,RL_SetShaderValueTexture
    UnloadShader,RL_UnloadShader

    # screen space
    GetMouseRay,RL_GetMouseRay
    GetScreenToWorldRay,RL_GetScreenToWorldRay
    GetScreenToWorldRay,RL_GetScreenToWorldRay
    GetScreenToWorldRayEx,RL_GetScreenToWorldRayEx
    GetWorldToScreen,RL_GetWorldToScreen
    GetWorldToScreenEx,RL_GetWorldToScreenEx
    GetWorldToScreen2D,RL_GetWorldToScreen2D
    GetScreenToWorld2D,RL_GetScreenToWorld2D
    GetCameraMatrix,RL_GetCameraMatrix
    GetCameraMatrix2D,RL_GetCameraMatrix2D

    # time
    SetTargetFPS,RL_SetTargetFPS
    GetFrameTime,RL_GetFrameTime
    GetTime,RL_GetTime
    GetFPS,RL_GetFPS

    # frame control
    SwapScreenBuffer,RL_SwapScreenBuffer
    PollInputEvents,RL_PollInputEvents
    WaitTime,RL_WaitTime

    # random value generation
    SetRandomSeed,RL_SetRandomSeed
    GetRandomValue,RL_GetRandomValue
    LoadRandomSequence,RL_LoadRandomSequence
    UnloadRandomSequence,RL_UnloadRandomSequence

    # misc
    TakeScreenshot,RL_TakeScreenshot
    SetConfigFlags,RL_SetConfigFlags
    OpenURL,RL_OpenURL

    # utils
    TraceLog,RL_TraceLog
    SetTraceLogLevel,RL_SetTraceLogLevel
    MemAlloc,RL_MemAlloc
    MemRealloc,RL_MemRealloc
    MemFree,RL_MemFree

    # custom callbacks
    SetTraceLogCallback,RL_SetTraceLogCallback
    SetLoadFileDataCallback,RL_SetLoadFileDataCallback
    SetSaveFileDataCallback,RL_SetSaveFileDataCallback
    SetLoadFileTextCallback,RL_SetLoadFileTextCallback
    SetSaveFileTextCallback,RL_SetSaveFileTextCallback

    # file management
    LoadFileData,RL_LoadFileData
    UnloadFileData,RL_UnloadFileData
    SaveFileData,RL_SaveFileData
    ExportDataAsCode,RL_ExportDataAsCode
    LoadFileText,RL_LoadFileText
    UnloadFileText,RL_UnloadFileText
    SaveFileText,RL_SaveFileText

    # file system
    FileExists,RL_FileExists
    DirectoryExists,RL_DirectoryExists
    IsFileExtension,RL_IsFileExtension
    GetFileLength,RL_GetFileLength
    GetFileExtension,RL_GetFileExtension
    GetFileName,RL_GetFileName
    GetFileNameWithoutExt,RL_GetFileNameWithoutExt
    GetDirectoryPath,RL_GetDirectoryPath
    GetPrevDirectoryPath,RL_GetPrevDirectoryPath
    GetWorkingDirectory,RL_GetWorkingDirectory
    GetApplicationDirectory,RL_GetApplicationDirectory
    ChangeDirectory,RL_ChangeDirectory
    IsPathFile,RL_IsPathFile
    IsFileNameValid,RL_IsFileNameValid
    LoadDirectoryFiles,RL_LoadDirectoryFiles
    LoadDirectoryFilesEx,RL_LoadDirectoryFilesEx
    UnloadDirectoryFiles,RL_UnloadDirectoryFiles
    IsFileDropped,RL_IsFileDropped
    LoadDroppedFiles,RL_LoadDroppedFiles
    UnloadDroppedFiles,RL_UnloadDroppedFiles
    GetFileModTime,RL_GetFileModTime
    CompressData,RL_CompressData
    DecompressData,RL_DecompressData
    EncodeDataBase64,RL_EncodeDataBase64
    DecodeDataBase64,RL_DecodeDataBase64

    # compression
    CompressData,RL_CompressData
    DecompressData,RL_DecompressData
    EncodeDataBase64,RL_EncodeDataBase64
    DecodeDataBase64,RL_DecodeDataBase64

    # automation
    LoadAutomationEventList,RL_LoadAutomationEventList
    UnloadAutomationEventList,RL_UnloadAutomationEventList
    ExportAutomationEventList,RL_ExportAutomationEventList
    SetAutomationEventList,RL_SetAutomationEventList
    SetAutomationEventBaseFrame,RL_SetAutomationEventBaseFrame
    StartAutomationEventRecording,RL_StartAutomationEventRecording
    StopAutomationEventRecording,RL_StopAutomationEventRecording
    PlayAutomationEvent,RL_PlayAutomationEvent

    # input - keyboard
    IsKeyPressed,RL_IsKeyPressed
    IsKeyPressedRepeat,RL_IsKeyPressedRepeat
    IsKeyDown,RL_IsKeyDown
    IsKeyReleased,RL_IsKeyReleased
    IsKeyUp,RL_IsKeyUp
    GetKeyPressed,RL_GetKeyPressed
    GetCharPressed,RL_GetCharPressed
    SetExitKey,RL_SetExitKey

    # input - gamepad
    IsGamepadAvailable,RL_IsGamepadAvailable
    GetGamepadName,RL_GetGamepadName
    IsGamepadButtonPressed,RL_IsGamepadButtonPressed
    IsGamepadButtonDown,RL_IsGamepadButtonDown
    IsGamepadButtonReleased,RL_IsGamepadButtonReleased
    IsGamepadButtonUp,RL_IsGamepadButtonUp
    GetGamepadButtonPressed,RL_GetGamepadButtonPressed
    GetGamepadAxisCount,RL_GetGamepadAxisCount
    GetGamepadAxisMovement,RL_GetGamepadAxisMovement
    SetGamepadMappings,RL_SetGamepadMappings
    SetGamepadVibration,RL_SetGamepadVibration

    # input - mouse
    IsMouseButtonPressed,RL_IsMouseButtonPressed
    IsMouseButtonDown,RL_IsMouseButtonDown
    IsMouseButtonReleased,RL_IsMouseButtonReleased
    IsMouseButtonUp,RL_IsMouseButtonUp
    GetMouseX,RL_GetMouseX
    GetMouseY,RL_GetMouseY
    GetMousePosition,RL_GetMousePosition
    GetMouseDelta,RL_GetMouseDelta
    SetMousePosition,RL_SetMousePosition
    SetMouseOffset,RL_SetMouseOffset
    SetMouseScale,RL_SetMouseScale
    GetMouseWheelMove,RL_GetMouseWheelMove
    GetMouseWheelMoveV,RL_GetMouseWheelMoveV
    SetMouseCursor,RL_SetMouseCursor

    # input - touch
    GetTouchX,RL_GetTouchX
    GetTouchY,RL_GetTouchY
    GetTouchPosition,RL_GetTouchPosition
    GetTouchPointId,RL_GetTouchPointId
    GetTouchPointCount,RL_GetTouchPointCount

    # input - gestures
    SetGesturesEnabled,RL_SetGesturesEnabled
    IsGestureDetected,RL_IsGestureDetected
    GetGestureDetected,RL_GetGestureDetected
    GetGestureHoldDuration,RL_GetGestureHoldDuration
    GetGestureDragVector,RL_GetGestureDragVector
    GetGestureDragAngle,RL_GetGestureDragAngle
    GetGesturePinchVector,RL_GetGesturePinchVector
    GetGesturePinchAngle,RL_GetGesturePinchAngle

    # camera
    UpdateCamera,RL_UpdateCamera
    UpdateCameraPro,RL_UpdateCameraPro

    # basic shapes
    SetShapesTexture,RL_SetShapesTexture
    GetShapesTexture,RL_GetShapesTexture
    GetShapesTextureRectangle,RL_GetShapesTextureRectangle
    DrawPixel,RL_DrawPixel
    DrawPixelV,RL_DrawPixelV
    DrawLine,RL_DrawLine
    DrawLineV,RL_DrawLineV
    DrawLineEx,RL_DrawLineEx
    DrawLineStrip,RL_DrawLineStrip
    DrawLineBezier,RL_DrawLineBezier
    DrawCircle,RL_DrawCircle
    DrawCircleSector,RL_DrawCircleSector
    DrawCircleSectorLines,RL_DrawCircleSectorLines
    DrawCircleGradient,RL_DrawCircleGradient
    DrawCircleV,RL_DrawCircleV
    DrawCircleLines,RL_DrawCircleLines
    DrawCircleLinesV,RL_DrawCircleLinesV
    DrawEllipse,RL_DrawEllipse
    DrawEllipseLines,RL_DrawEllipseLines
    DrawRing,RL_DrawRing
    DrawRingLines,RL_DrawRingLines
    DrawRectangle,RL_DrawRectangle
    DrawRectangleV,RL_DrawRectangleV
    DrawRectangleRec,RL_DrawRectangleRec
    DrawRectanglePro,RL_DrawRectanglePro
    DrawRectangleGradientV,RL_DrawRectangleGradientV
    DrawRectangleGradientH,RL_DrawRectangleGradientH
    DrawRectangleGradientEx,RL_DrawRectangleGradientEx
    DrawRectangleLines,RL_DrawRectangleLines
    DrawRectangleLinesEx,RL_DrawRectangleLinesEx
    DrawRectangleRounded,RL_DrawRectangleRounded
    DrawRectangleRoundedLines,RL_DrawRectangleRoundedLines
    DrawRectangleRoundedLinesEx,RL_DrawRectangleRoundedLinesEx
    DrawTriangle,RL_DrawTriangle
    DrawTriangleLines,RL_DrawTriangleLines
    DrawTriangleFan,RL_DrawTriangleFan
    DrawTriangleStrip,RL_DrawTriangleStrip
    DrawPoly,RL_DrawPoly
    DrawPolyLines,RL_DrawPolyLines
    DrawPolyLinesEx,RL_DrawPolyLinesEx

    # splines - drawing
    DrawSplineLinear,RL_DrawSplineLinear
    DrawSplineBasis,RL_DrawSplineBasis
    DrawSplineCatmullRom,RL_DrawSplineCatmullRom
    DrawSplineBezierQuadratic,RL_DrawSplineBezierQuadratic
    DrawSplineBezierCubic,RL_DrawSplineBezierCubic
    DrawSplineSegmentLinear,RL_DrawSplineSegmentLinear
    DrawSplineSegmentBasis,RL_DrawSplineSegmentBasis
    DrawSplineSegmentCatmullRom,RL_DrawSplineSegmentCatmullRom
    DrawSplineSegmentBezierQuadratic,RL_DrawSplineSegmentBezierQuadratic
    DrawSplineSegmentBezierCubic,RL_DrawSplineSegmentBezierCubic

    # splines - segment point evaluation functions
    GetSplinePointLinear,RL_GetSplinePointLinear
    GetSplinePointBasis,RL_GetSplinePointBasis
    GetSplinePointCatmullRom,RL_GetSplinePointCatmullRom
    GetSplinePointBezierQuad,RL_GetSplinePointBezierQuad
    GetSplinePointBezierCubic,RL_GetSplinePointBezierCubic

    # basic shapes collision
    CheckCollisionRecs,RL_CheckCollisionRecs
    CheckCollisionCircles,RL_CheckCollisionCircles
    CheckCollisionCircleRec,RL_CheckCollisionCircleRec
    CheckCollisionPointRec,RL_CheckCollisionPointRec
    CheckCollisionPointCircle,RL_CheckCollisionPointCircle
    CheckCollisionPointTriangle,RL_CheckCollisionPointTriangle
    CheckCollisionPointPoly,RL_CheckCollisionPointPoly
    CheckCollisionLines,RL_CheckCollisionLines
    CheckCollisionPointLine,RL_CheckCollisionPointLine
    CheckCollisionCircleLine,RL_CheckCollisionCircleLine
    GetCollisionRec,RL_GetCollisionRec

    # image loading
    LoadImage,RL_LoadImage
    LoadImageRaw,RL_LoadImageRaw
    LoadImageSvg,RL_LoadImageSvg
    LoadImageAnim,RL_LoadImageAnim
    LoadImageAnimFromMemory,RL_LoadImageAnimFromMemory
    LoadImageFromMemory,RL_LoadImageFromMemory
    LoadImageFromTexture,RL_LoadImageFromTexture
    LoadImageFromScreen,RL_LoadImageFromScreen
    IsImageReady,RL_IsImageReady
    UnloadImage,RL_UnloadImage
    ExportImage,RL_ExportImage
    ExportImageToMemory,RL_ExportImageToMemory
    ExportImageAsCode,RL_ExportImageAsCode

    # image generation
    GenImageColor,RL_GenImageColor
    GenImageGradientLinear,RL_GenImageGradientLinear
    GenImageGradientRadial,RL_GenImageGradientRadial
    GenImageGradientSquare,RL_GenImageGradientSquare
    GenImageChecked,RL_GenImageChecked
    GenImageWhiteNoise,RL_GenImageWhiteNoise
    GenImagePerlinNoise,RL_GenImagePerlinNoise
    GenImageCellular,RL_GenImageCellular
    GenImageText,RL_GenImageText

    # image manipulation
    ImageCopy,RL_ImageCopy
    ImageFromImage,RL_ImageFromImage
    ImageFromChannel,RL_ImageFromChannel
    ImageText,RL_ImageText
    ImageTextEx,RL_ImageTextEx
    ImageFormat,RL_ImageFormat
    ImageToPOT,RL_ImageToPOT
    ImageCrop,RL_ImageCrop
    ImageAlphaCrop,RL_ImageAlphaCrop
    ImageAlphaClear,RL_ImageAlphaClear
    ImageAlphaMask,RL_ImageAlphaMask
    ImageAlphaPremultiply,RL_ImageAlphaPremultiply
    ImageBlurGaussian,RL_ImageBlurGaussian
    ImageKernelConvolution,RL_ImageKernelConvolution
    ImageResize,RL_ImageResize
    ImageResizeNN,RL_ImageResizeNN
    ImageResizeCanvas,RL_ImageResizeCanvas
    ImageMipmaps,RL_ImageMipmaps
    ImageDither,RL_ImageDither
    ImageFlipVertical,RL_ImageFlipVertical
    ImageFlipHorizontal,RL_ImageFlipHorizontal
    ImageRotate,RL_ImageRotate
    ImageRotateCW,RL_ImageRotateCW
    ImageRotateCCW,RL_ImageRotateCCW
    ImageColorTint,RL_ImageColorTint
    ImageColorInvert,RL_ImageColorInvert
    ImageColorGrayscale,RL_ImageColorGrayscale
    ImageColorContrast,RL_ImageColorContrast
    ImageColorBrightness,RL_ImageColorBrightness
    ImageColorReplace,RL_ImageColorReplace
    LoadImageColors,RL_LoadImageColors
    LoadImagePalette,RL_LoadImagePalette
    UnloadImageColors,RL_UnloadImageColors
    UnloadImagePalette,RL_UnloadImagePalette
    GetImageAlphaBorder,RL_GetImageAlphaBorder
    GetImageColor,RL_GetImageColor

    # image drawing
    ImageClearBackground,RL_ImageClearBackground
    ImageDrawPixel,RL_ImageDrawPixel
    ImageDrawPixelV,RL_ImageDrawPixelV
    ImageDrawLine,RL_ImageDrawLine
    ImageDrawLineV,RL_ImageDrawLineV
    ImageDrawLineEx,RL_ImageDrawLineEx
    ImageDrawCircle,RL_ImageDrawCircle
    ImageDrawCircleV,RL_ImageDrawCircleV
    ImageDrawCircleLines,RL_ImageDrawCircleLines
    ImageDrawCircleLinesV,RL_ImageDrawCircleLinesV
    ImageDrawRectangle,RL_ImageDrawRectangle
    ImageDrawRectangleV,RL_ImageDrawRectangleV
    ImageDrawRectangleRec,RL_ImageDrawRectangleRec
    ImageDrawRectangleLines,RL_ImageDrawRectangleLines
    ImageDrawTriangle,RL_ImageDrawTriangle
    ImageDrawTriangleEx,RL_ImageDrawTriangleEx
    ImageDrawTriangleLines,RL_ImageDrawTriangleLines
    ImageDrawTriangleFan,RL_ImageDrawTriangleFan
    ImageDrawTriangleStrip,RL_ImageDrawTriangleStrip
    ImageDraw,RL_ImageDraw
    ImageDrawText,RL_ImageDrawText
    ImageDrawTextEx,RL_ImageDrawTextEx

    # texture loading
    LoadTexture,RL_LoadTexture
    LoadTextureFromImage,RL_LoadTextureFromImage
    LoadTextureCubemap,RL_LoadTextureCubemap
    LoadRenderTexture,RL_LoadRenderTexture
    IsTextureReady,RL_IsTextureReady
    UnloadTexture,RL_UnloadTexture
    IsRenderTextureReady,RL_IsRenderTextureReady
    UnloadRenderTexture,RL_UnloadRenderTexture
    UpdateTexture,RL_UpdateTexture
    UpdateTextureRec,RL_UpdateTextureRec

    # texture configuration
    GenTextureMipmaps,RL_GenTextureMipmaps
    SetTextureFilter,RL_SetTextureFilter
    SetTextureWrap,RL_SetTextureWrap

    # texture drawing
    DrawTexture,RL_DrawTexture
    DrawTextureV,RL_DrawTextureV
    DrawTextureEx,RL_DrawTextureEx
    DrawTextureRec,RL_DrawTextureRec
    DrawTexturePro,RL_DrawTexturePro
    DrawTextureNPatch,RL_DrawTextureNPatch

    # color / pixel functions
    ColorIsEqual,RL_ColorIsEqual
    Fade,RL_Fade
    ColorToInt,RL_ColorToInt
    ColorNormalize,RL_ColorNormalize
    ColorFromNormalized,RL_ColorFromNormalized
    ColorToHSV,RL_ColorToHSV
    ColorFromHSV,RL_ColorFromHSV
    ColorTint,RL_ColorTint
    ColorBrightness,RL_ColorBrightness
    ColorContrast,RL_ColorContrast
    ColorAlpha,RL_ColorAlpha
    ColorAlphaBlend,RL_ColorAlphaBlend
    GetColor,RL_GetColor
    GetPixelColor,RL_GetPixelColor
    SetPixelColor,RL_SetPixelColor
    GetPixelDataSize,RL_GetPixelDataSize

    # font loading
    GetFontDefault,RL_GetFontDefault
    LoadFont,RL_LoadFont
    LoadFontEx,RL_LoadFontEx
    LoadFontFromImage,RL_LoadFontFromImage
    LoadFontFromMemory,RL_LoadFontFromMemory
    IsFontReady,RL_IsFontReady
    LoadFontData,RL_LoadFontData
    GenImageFontAtlas,RL_GenImageFontAtlas
    UnloadFontData,RL_UnloadFontData
    UnloadFont,RL_UnloadFont
    ExportFontAsCode,RL_ExportFontAsCode

    # text drawing
    DrawFPS,RL_DrawFPS
    DrawText,RL_DrawText
    DrawTextEx,RL_DrawTextEx
    DrawTextPro,RL_DrawTextPro
    DrawTextCodepoint,RL_DrawTextCodepoint
    DrawTextCodepoints,RL_DrawTextCodepoints

    # text font info
    SetTextLineSpacing,RL_SetTextLineSpacing
    MeasureText,RL_MeasureText
    MeasureTextEx,RL_MeasureTextEx
    GetGlyphIndex,RL_GetGlyphIndex
    GetGlyphInfo,RL_GetGlyphInfo
    GetGlyphAtlasRec,RL_GetGlyphAtlasRec

    # text codepoints
    LoadUTF8,RL_LoadUTF8
    UnloadUTF8,RL_UnloadUTF8
    LoadCodepoints,RL_LoadCodepoints
    UnloadCodepoints,RL_UnloadCodepoints
    GetCodepointCount,RL_GetCodepointCount
    GetCodepoint,RL_GetCodepoint
    GetCodepointNext,RL_GetCodepointNext
    GetCodepointPrevious,RL_GetCodepointPrevious
    CodepointToUTF8,RL_CodepointToUTF8

    # text strings management
    TextCopy,RL_TextCopy
    TextIsEqual,RL_TextIsEqual
    TextLength,RL_TextLength
    TextFormat,RL_TextFormat
    TextSubtext,RL_TextSubtext
    TextReplace,RL_TextReplace
    TextInsert,RL_TextInsert
    TextJoin,RL_TextJoin
    TextSplit,RL_TextSplit
    TextAppend,RL_TextAppend
    TextFindIndex,RL_TextFindIndex
    TextToUpper,RL_TextToUpper
    TextToLower,RL_TextToLower
    TextToPascal,RL_TextToPascal
    TextToSnake,RL_TextToSnake
    TextToCamel,RL_TextToCamel
    TextToInteger,RL_TextToInteger
    TextToFloat,RL_TextToFloat

    # basic geometric 3d
    DrawLine3D,RL_DrawLine3D
    DrawPoint3D,RL_DrawPoint3D
    DrawCircle3D,RL_DrawCircle3D
    DrawTriangle3D,RL_DrawTriangle3D
    DrawTriangleStrip3D,RL_DrawTriangleStrip3D
    DrawCube,RL_DrawCube
    DrawCubeV,RL_DrawCubeV
    DrawCubeWires,RL_DrawCubeWires
    DrawCubeWiresV,RL_DrawCubeWiresV
    DrawSphere,RL_DrawSphere
    DrawSphereEx,RL_DrawSphereEx
    DrawSphereWires,RL_DrawSphereWires
    DrawCylinder,RL_DrawCylinder
    DrawCylinderEx,RL_DrawCylinderEx
    DrawCylinderWires,RL_DrawCylinderWires
    DrawCylinderWiresEx,RL_DrawCylinderWiresEx
    DrawCapsule,RL_DrawCapsule
    DrawCapsuleWires,RL_DrawCapsuleWires
    DrawPlane,RL_DrawPlane
    DrawRay,RL_DrawRay
    DrawGrid,RL_DrawGrid

    # model management
    LoadModel,RL_LoadModel
    LoadModelFromMesh,RL_LoadModelFromMesh
    IsModelReady,RL_IsModelReady
    UnloadModel,RL_UnloadModel
    GetModelBoundingBox,RL_GetModelBoundingBox

    # model drawing
    DrawModel,RL_DrawModel
    DrawModelEx,RL_DrawModelEx
    DrawModelWires,RL_DrawModelWires
    DrawModelWiresEx,RL_DrawModelWiresEx
    DrawBoundingBox,RL_DrawBoundingBox
    DrawBillboard,RL_DrawBillboard
    DrawBillboardRec,RL_DrawBillboardRec
    DrawBillboardPro,RL_DrawBillboardPro

    # mesh management
    UploadMesh,RL_UploadMesh
    UpdateMeshBuffer,RL_UpdateMeshBuffer
    UnloadMesh,RL_UnloadMesh
    DrawMesh,RL_DrawMesh
    DrawMeshInstanced,RL_DrawMeshInstanced
    GetMeshBoundingBox,RL_GetMeshBoundingBox
    GenMeshTangents,RL_GenMeshTangents
    ExportMesh,RL_ExportMesh
    ExportMeshAsCode,RL_ExportMeshAsCode

    # mesh generation
    GenMeshPoly,RL_GenMeshPoly
    GenMeshPlane,RL_GenMeshPlane
    GenMeshCube,RL_GenMeshCube
    GenMeshSphere,RL_GenMeshSphere
    GenMeshHemiSphere,RL_GenMeshHemiSphere
    GenMeshCylinder,RL_GenMeshCylinder
    GenMeshCone,RL_GenMeshCone
    GenMeshTorus,RL_GenMeshTorus
    GenMeshKnot,RL_GenMeshKnot
    GenMeshHeightmap,RL_GenMeshHeightmap
    GenMeshCubicmap,RL_GenMeshCubicmap

    # material loading
    LoadMaterials,RL_LoadMaterials
    LoadMaterialDefault,RL_LoadMaterialDefault
    IsMaterialReady,RL_IsMaterialReady
    UnloadMaterial,RL_UnloadMaterial
    SetMaterialTexture,RL_SetMaterialTexture
    SetModelMeshMaterial,RL_SetModelMeshMaterial

    # model animation
    LoadModelAnimations,RL_LoadModelAnimations
    UpdateModelAnimation,RL_UpdateModelAnimation
    UnloadModelAnimation,RL_UnloadModelAnimation
    UnloadModelAnimations,RL_UnloadModelAnimations
    IsModelAnimationValid,RL_IsModelAnimationValid

    # collision detection
    CheckCollisionSpheres,RL_CheckCollisionSpheres
    CheckCollisionBoxes,RL_CheckCollisionBoxes
    CheckCollisionBoxSphere,RL_CheckCollisionBoxSphere
    GetRayCollisionSphere,RL_GetRayCollisionSphere
    GetRayCollisionBox,RL_GetRayCollisionBox
    GetRayCollisionMesh,RL_GetRayCollisionMesh
    GetRayCollisionTriangle,RL_GetRayCollisionTriangle
    GetRayCollisionQuad,RL_GetRayCollisionQuad

    # audio device management
    InitAudioDevice,RL_InitAudioDevice
    CloseAudioDevice,RL_CloseAudioDevice
    IsAudioDeviceReady,RL_IsAudioDeviceReady
    SetMasterVolume,RL_SetMasterVolume
    GetMasterVolume,RL_GetMasterVolume

    # wave / sound loading
    LoadWave,RL_LoadWave
    LoadWaveFromMemory,RL_LoadWaveFromMemory
    IsWaveReady,RL_IsWaveReady
    LoadSound,RL_LoadSound
    LoadSoundFromWave,RL_LoadSoundFromWave
    LoadSoundAlias,RL_LoadSoundAlias
    IsSoundReady,RL_IsSoundReady
    UpdateSound,RL_UpdateSound
    UnloadWave,RL_UnloadWave
    UnloadSound,RL_UnloadSound
    UnloadSoundAlias,RL_UnloadSoundAlias
    ExportWave,RL_ExportWave
    ExportWaveAsCode,RL_ExportWaveAsCode

    # wave / sound management
    PlaySound,RL_PlaySound
    StopSound,RL_StopSound
    PauseSound,RL_PauseSound
    ResumeSound,RL_ResumeSound
    IsSoundPlaying,RL_IsSoundPlaying
    SetSoundVolume,RL_SetSoundVolume
    SetSoundPitch,RL_SetSoundPitch
    SetSoundPan,RL_SetSoundPan
    WaveCopy,RL_WaveCopy
    WaveCrop,RL_WaveCrop
    WaveFormat,RL_WaveFormat
    LoadWaveSamples,RL_LoadWaveSamples
    UnloadWaveSamples,RL_UnloadWaveSamples

    # music management
    LoadMusicStream,RL_LoadMusicStream
    LoadMusicStreamFromMemory,RL_LoadMusicStreamFromMemory
    IsMusicReady,RL_IsMusicReady
    UnloadMusicStream,RL_UnloadMusicStream
    PlayMusicStream,RL_PlayMusicStream
    IsMusicStreamPlaying,RL_IsMusicStreamPlaying
    UpdateMusicStream,RL_UpdateMusicStream
    StopMusicStream,RL_StopMusicStream
    PauseMusicStream,RL_PauseMusicStream
    ResumeMusicStream,RL_ResumeMusicStream
    SeekMusicStream,RL_SeekMusicStream
    SetMusicVolume,RL_SetMusicVolume
    SetMusicPitch,RL_SetMusicPitch
    SetMusicPan,RL_SetMusicPan
    GetMusicTimeLength,RL_GetMusicTimeLength
    GetMusicTimePlayed,RL_GetMusicTimePlayed

    # audio stream management
    LoadAudioStream,RL_LoadAudioStream
    IsAudioStreamReady,RL_IsAudioStreamReady
    UnloadAudioStream,RL_UnloadAudioStream
    UpdateAudioStream,RL_UpdateAudioStream
    IsAudioStreamProcessed,RL_IsAudioStreamProcessed
    PlayAudioStream,RL_PlayAudioStream
    PauseAudioStream,RL_PauseAudioStream
    ResumeAudioStream,RL_ResumeAudioStream
    IsAudioStreamPlaying,RL_IsAudioStreamPlaying
    StopAudioStream,RL_StopAudioStream
    SetAudioStreamVolume,RL_SetAudioStreamVolume
    SetAudioStreamPitch,RL_SetAudioStreamPitch
    SetAudioStreamPan,RL_SetAudioStreamPan
    SetAudioStreamBufferSizeDefault,RL_SetAudioStreamBufferSizeDefault
    SetAudioStreamCallback,RL_SetAudioStreamCallback
    AttachAudioStreamProcessor,RL_AttachAudioStreamProcessor
    DetachAudioStreamProcessor,RL_DetachAudioStreamProcessor
    AttachAudioMixedProcessor,RL_AttachAudioMixedProcessor
    DetachAudioMixedProcessor,RL_DetachAudioMixedProcessor
)

for pair in "${replacements[@]}"; do
    search_for=$(echo "$pair" | cut -d',' -f1)
    replace_with=$(echo "$pair" | cut -d',' -f2)

    # source
    sed -i "s/\\<$search_for\\>/$replace_with/g" ./src/*.h
    sed -i "s/\\<$search_for\\>/$replace_with/g" ./src/*.c
    sed -i "s/\\<$search_for\\>/$replace_with/g" ./src/**/*.h
    sed -i "s/\\<$search_for\\>/$replace_with/g" ./src/**/*.c

    # examples
    sed -i "s/\\<$search_for\\>/$replace_with/g" ./examples/*.c
    sed -i "s/\\<$search_for\\>/$replace_with/g" ./examples/*.h
    sed -i "s/\\<$search_for\\>/$replace_with/g" ./examples/**/*.c
    sed -i "s/\\<$search_for\\>/$replace_with/g" ./examples/**/*.h

    # parser
    sed -i "s/\\<$search_for\\>/$replace_with/g" ./parser/**/*.*

    # misc
    sed -i "s/\\<$search_for\\>/$replace_with/g" ./README.md
done
