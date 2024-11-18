return {
  defines = {
    {
      name = "RAYLIB_H",
      type = "GUARD",
      value = "",
      description = ""
    },
    {
      name = "RAYLIB_VERSION_MAJOR",
      type = "INT",
      value = 5,
      description = ""
    },
    {
      name = "RAYLIB_VERSION_MINOR",
      type = "INT",
      value = 5,
      description = ""
    },
    {
      name = "RAYLIB_VERSION_PATCH",
      type = "INT",
      value = 0,
      description = ""
    },
    {
      name = "RAYLIB_VERSION",
      type = "STRING",
      value = "5.5",
      description = ""
    },
    {
      name = "__declspec(x)",
      type = "MACRO",
      value = "__attribute__((x))",
      description = ""
    },
    {
      name = "RLAPI",
      type = "UNKNOWN",
      value = "__declspec(dllexport)",
      description = "We are building the library as a Win32 shared library (.dll)"
    },
    {
      name = "PI",
      type = "FLOAT",
      value = 3.14159265358979323846,
      description = ""
    },
    {
      name = "DEG2RAD",
      type = "FLOAT_MATH",
      value = "(PI/180.0f)",
      description = ""
    },
    {
      name = "RAD2DEG",
      type = "FLOAT_MATH",
      value = "(180.0f/PI)",
      description = ""
    },
    {
      name = "RL_MALLOC(sz)",
      type = "MACRO",
      value = "malloc(sz)",
      description = ""
    },
    {
      name = "RL_CALLOC(n,sz)",
      type = "MACRO",
      value = "calloc(n,sz)",
      description = ""
    },
    {
      name = "RL_REALLOC(ptr,sz)",
      type = "MACRO",
      value = "realloc(ptr,sz)",
      description = ""
    },
    {
      name = "RL_FREE(ptr)",
      type = "MACRO",
      value = "free(ptr)",
      description = ""
    },
    {
      name = "CLITERAL(type)",
      type = "MACRO",
      value = "type",
      description = ""
    },
    {
      name = "RL_COLOR_TYPE",
      type = "GUARD",
      value = "",
      description = ""
    },
    {
      name = "RL_RECTANGLE_TYPE",
      type = "GUARD",
      value = "",
      description = ""
    },
    {
      name = "RL_VECTOR2_TYPE",
      type = "GUARD",
      value = "",
      description = ""
    },
    {
      name = "RL_VECTOR3_TYPE",
      type = "GUARD",
      value = "",
      description = ""
    },
    {
      name = "RL_VECTOR4_TYPE",
      type = "GUARD",
      value = "",
      description = ""
    },
    {
      name = "RL_QUATERNION_TYPE",
      type = "GUARD",
      value = "",
      description = ""
    },
    {
      name = "RL_MATRIX_TYPE",
      type = "GUARD",
      value = "",
      description = ""
    },
    {
      name = "RL_LIGHTGRAY",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 200, 200, 200, 255 }",
      description = "Light Gray"
    },
    {
      name = "RL_GRAY",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 130, 130, 130, 255 }",
      description = "Gray"
    },
    {
      name = "RL_DARKGRAY",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 80, 80, 80, 255 }",
      description = "Dark Gray"
    },
    {
      name = "RL_YELLOW",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 253, 249, 0, 255 }",
      description = "Yellow"
    },
    {
      name = "RL_GOLD",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 255, 203, 0, 255 }",
      description = "Gold"
    },
    {
      name = "RL_ORANGE",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 255, 161, 0, 255 }",
      description = "Orange"
    },
    {
      name = "RL_PINK",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 255, 109, 194, 255 }",
      description = "Pink"
    },
    {
      name = "RL_RED",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 230, 41, 55, 255 }",
      description = "Red"
    },
    {
      name = "RL_MAROON",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 190, 33, 55, 255 }",
      description = "Maroon"
    },
    {
      name = "RL_GREEN",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 0, 228, 48, 255 }",
      description = "Green"
    },
    {
      name = "RL_LIME",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 0, 158, 47, 255 }",
      description = "Lime"
    },
    {
      name = "RL_DARKGREEN",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 0, 117, 44, 255 }",
      description = "Dark Green"
    },
    {
      name = "RL_SKYBLUE",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 102, 191, 255, 255 }",
      description = "Sky Blue"
    },
    {
      name = "RL_BLUE",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 0, 121, 241, 255 }",
      description = "Blue"
    },
    {
      name = "RL_DARKBLUE",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 0, 82, 172, 255 }",
      description = "Dark Blue"
    },
    {
      name = "RL_PURPLE",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 200, 122, 255, 255 }",
      description = "Purple"
    },
    {
      name = "RL_VIOLET",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 135, 60, 190, 255 }",
      description = "Violet"
    },
    {
      name = "RL_DARKPURPLE",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 112, 31, 126, 255 }",
      description = "Dark Purple"
    },
    {
      name = "RL_BEIGE",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 211, 176, 131, 255 }",
      description = "Beige"
    },
    {
      name = "RL_BROWN",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 127, 106, 79, 255 }",
      description = "Brown"
    },
    {
      name = "RL_DARKBROWN",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 76, 63, 47, 255 }",
      description = "Dark Brown"
    },
    {
      name = "RL_WHITE",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 255, 255, 255, 255 }",
      description = "White"
    },
    {
      name = "RL_BLACK",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 0, 0, 0, 255 }",
      description = "Black"
    },
    {
      name = "RL_BLANK",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 0, 0, 0, 0 }",
      description = "Blank (Transparent)"
    },
    {
      name = "RL_MAGENTA",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 255, 0, 255, 255 }",
      description = "Magenta"
    },
    {
      name = "RL_RAYWHITE",
      type = "COLOR",
      value = "CLITERAL(RL_Color){ 245, 245, 245, 255 }",
      description = "My own White (raylib logo)"
    },
    {
      name = "RL_BOOL_TYPE",
      type = "GUARD",
      value = "",
      description = ""
    },
    {
      name = "MOUSE_LEFT_BUTTON",
      type = "UNKNOWN",
      value = "MOUSE_BUTTON_LEFT",
      description = ""
    },
    {
      name = "MOUSE_RIGHT_BUTTON",
      type = "UNKNOWN",
      value = "MOUSE_BUTTON_RIGHT",
      description = ""
    },
    {
      name = "MOUSE_MIDDLE_BUTTON",
      type = "UNKNOWN",
      value = "MOUSE_BUTTON_MIDDLE",
      description = ""
    },
    {
      name = "MATERIAL_MAP_DIFFUSE",
      type = "UNKNOWN",
      value = "MATERIAL_MAP_ALBEDO",
      description = ""
    },
    {
      name = "MATERIAL_MAP_SPECULAR",
      type = "UNKNOWN",
      value = "MATERIAL_MAP_METALNESS",
      description = ""
    },
    {
      name = "SHADER_LOC_MAP_DIFFUSE",
      type = "UNKNOWN",
      value = "SHADER_LOC_MAP_ALBEDO",
      description = ""
    },
    {
      name = "SHADER_LOC_MAP_SPECULAR",
      type = "UNKNOWN",
      value = "SHADER_LOC_MAP_METALNESS",
      description = ""
    },
    {
      name = "RL_GetMouseRay",
      type = "UNKNOWN",
      value = "RL_GetScreenToWorldRay",
      description = "Compatibility hack for previous raylib versions"
    }
  },
  structs = {
    {
      name = "RL_Vector2",
      description = "RL_Vector2, 2 components",
      fields = {
        {
          type = "float",
          name = "x",
          description = "Vector x component"
        },
        {
          type = "float",
          name = "y",
          description = "Vector y component"
        }
      }
    },
    {
      name = "RL_Vector3",
      description = "RL_Vector3, 3 components",
      fields = {
        {
          type = "float",
          name = "x",
          description = "Vector x component"
        },
        {
          type = "float",
          name = "y",
          description = "Vector y component"
        },
        {
          type = "float",
          name = "z",
          description = "Vector z component"
        }
      }
    },
    {
      name = "RL_Vector4",
      description = "RL_Vector4, 4 components",
      fields = {
        {
          type = "float",
          name = "x",
          description = "Vector x component"
        },
        {
          type = "float",
          name = "y",
          description = "Vector y component"
        },
        {
          type = "float",
          name = "z",
          description = "Vector z component"
        },
        {
          type = "float",
          name = "w",
          description = "Vector w component"
        }
      }
    },
    {
      name = "RL_Matrix",
      description = "RL_Matrix, 4x4 components, column major, OpenGL style, right-handed",
      fields = {
        {
          type = "float",
          name = "m0",
          description = "RL_Matrix first row (4 components)"
        },
        {
          type = "float",
          name = "m4",
          description = "RL_Matrix first row (4 components)"
        },
        {
          type = "float",
          name = "m8",
          description = "RL_Matrix first row (4 components)"
        },
        {
          type = "float",
          name = "m12",
          description = "RL_Matrix first row (4 components)"
        },
        {
          type = "float",
          name = "m1",
          description = "RL_Matrix second row (4 components)"
        },
        {
          type = "float",
          name = "m5",
          description = "RL_Matrix second row (4 components)"
        },
        {
          type = "float",
          name = "m9",
          description = "RL_Matrix second row (4 components)"
        },
        {
          type = "float",
          name = "m13",
          description = "RL_Matrix second row (4 components)"
        },
        {
          type = "float",
          name = "m2",
          description = "RL_Matrix third row (4 components)"
        },
        {
          type = "float",
          name = "m6",
          description = "RL_Matrix third row (4 components)"
        },
        {
          type = "float",
          name = "m10",
          description = "RL_Matrix third row (4 components)"
        },
        {
          type = "float",
          name = "m14",
          description = "RL_Matrix third row (4 components)"
        },
        {
          type = "float",
          name = "m3",
          description = "RL_Matrix fourth row (4 components)"
        },
        {
          type = "float",
          name = "m7",
          description = "RL_Matrix fourth row (4 components)"
        },
        {
          type = "float",
          name = "m11",
          description = "RL_Matrix fourth row (4 components)"
        },
        {
          type = "float",
          name = "m15",
          description = "RL_Matrix fourth row (4 components)"
        }
      }
    },
    {
      name = "RL_Color",
      description = "RL_Color, 4 components, R8G8B8A8 (32bit)",
      fields = {
        {
          type = "unsigned char",
          name = "r",
          description = "RL_Color red value"
        },
        {
          type = "unsigned char",
          name = "g",
          description = "RL_Color green value"
        },
        {
          type = "unsigned char",
          name = "b",
          description = "RL_Color blue value"
        },
        {
          type = "unsigned char",
          name = "a",
          description = "RL_Color alpha value"
        }
      }
    },
    {
      name = "RL_Rectangle",
      description = "RL_Rectangle, 4 components",
      fields = {
        {
          type = "float",
          name = "x",
          description = "RL_Rectangle top-left corner position x"
        },
        {
          type = "float",
          name = "y",
          description = "RL_Rectangle top-left corner position y"
        },
        {
          type = "float",
          name = "width",
          description = "RL_Rectangle width"
        },
        {
          type = "float",
          name = "height",
          description = "RL_Rectangle height"
        }
      }
    },
    {
      name = "RL_Image",
      description = "RL_Image, pixel data stored in CPU memory (RAM)",
      fields = {
        {
          type = "void *",
          name = "data",
          description = "RL_Image raw data"
        },
        {
          type = "int",
          name = "width",
          description = "RL_Image base width"
        },
        {
          type = "int",
          name = "height",
          description = "RL_Image base height"
        },
        {
          type = "int",
          name = "mipmaps",
          description = "Mipmap levels, 1 by default"
        },
        {
          type = "int",
          name = "format",
          description = "Data format (RL_PixelFormat type)"
        }
      }
    },
    {
      name = "RL_Texture",
      description = "RL_Texture, tex data stored in GPU memory (VRAM)",
      fields = {
        {
          type = "unsigned int",
          name = "id",
          description = "OpenGL texture id"
        },
        {
          type = "int",
          name = "width",
          description = "RL_Texture base width"
        },
        {
          type = "int",
          name = "height",
          description = "RL_Texture base height"
        },
        {
          type = "int",
          name = "mipmaps",
          description = "Mipmap levels, 1 by default"
        },
        {
          type = "int",
          name = "format",
          description = "Data format (RL_PixelFormat type)"
        }
      }
    },
    {
      name = "RL_RenderTexture",
      description = "RL_RenderTexture, fbo for texture rendering",
      fields = {
        {
          type = "unsigned int",
          name = "id",
          description = "OpenGL framebuffer object id"
        },
        {
          type = "RL_Texture",
          name = "texture",
          description = "RL_Color buffer attachment texture"
        },
        {
          type = "RL_Texture",
          name = "depth",
          description = "Depth buffer attachment texture"
        }
      }
    },
    {
      name = "RL_NPatchInfo",
      description = "RL_NPatchInfo, n-patch layout info",
      fields = {
        {
          type = "RL_Rectangle",
          name = "source",
          description = "RL_Texture source rectangle"
        },
        {
          type = "int",
          name = "left",
          description = "Left border offset"
        },
        {
          type = "int",
          name = "top",
          description = "Top border offset"
        },
        {
          type = "int",
          name = "right",
          description = "Right border offset"
        },
        {
          type = "int",
          name = "bottom",
          description = "Bottom border offset"
        },
        {
          type = "int",
          name = "layout",
          description = "Layout of the n-patch: 3x3, 1x3 or 3x1"
        }
      }
    },
    {
      name = "RL_GlyphInfo",
      description = "RL_GlyphInfo, font characters glyphs info",
      fields = {
        {
          type = "int",
          name = "value",
          description = "Character value (Unicode)"
        },
        {
          type = "int",
          name = "offsetX",
          description = "Character offset X when drawing"
        },
        {
          type = "int",
          name = "offsetY",
          description = "Character offset Y when drawing"
        },
        {
          type = "int",
          name = "advanceX",
          description = "Character advance position X"
        },
        {
          type = "RL_Image",
          name = "image",
          description = "Character image data"
        }
      }
    },
    {
      name = "RL_Font",
      description = "RL_Font, font texture and RL_GlyphInfo array data",
      fields = {
        {
          type = "int",
          name = "baseSize",
          description = "Base size (default chars height)"
        },
        {
          type = "int",
          name = "glyphCount",
          description = "Number of glyph characters"
        },
        {
          type = "int",
          name = "glyphPadding",
          description = "Padding around the glyph characters"
        },
        {
          type = "RL_Texture2D",
          name = "texture",
          description = "RL_Texture atlas containing the glyphs"
        },
        {
          type = "RL_Rectangle *",
          name = "recs",
          description = "Rectangles in texture for the glyphs"
        },
        {
          type = "RL_GlyphInfo *",
          name = "glyphs",
          description = "Glyphs info data"
        }
      }
    },
    {
      name = "RL_Camera3D",
      description = "RL_Camera, defines position/orientation in 3d space",
      fields = {
        {
          type = "RL_Vector3",
          name = "position",
          description = "RL_Camera position"
        },
        {
          type = "RL_Vector3",
          name = "target",
          description = "RL_Camera target it looks-at"
        },
        {
          type = "RL_Vector3",
          name = "up",
          description = "RL_Camera up vector (rotation over its axis)"
        },
        {
          type = "float",
          name = "fovy",
          description = "RL_Camera field-of-view aperture in Y (degrees) in perspective, used as near plane width in orthographic"
        },
        {
          type = "int",
          name = "projection",
          description = "RL_Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC"
        }
      }
    },
    {
      name = "RL_Camera2D",
      description = "RL_Camera2D, defines position/orientation in 2d space",
      fields = {
        {
          type = "RL_Vector2",
          name = "offset",
          description = "RL_Camera offset (displacement from target)"
        },
        {
          type = "RL_Vector2",
          name = "target",
          description = "RL_Camera target (rotation and zoom origin)"
        },
        {
          type = "float",
          name = "rotation",
          description = "RL_Camera rotation in degrees"
        },
        {
          type = "float",
          name = "zoom",
          description = "RL_Camera zoom (scaling), should be 1.0f by default"
        }
      }
    },
    {
      name = "RL_Mesh",
      description = "RL_Mesh, vertex data and vao/vbo",
      fields = {
        {
          type = "int",
          name = "vertexCount",
          description = "Number of vertices stored in arrays"
        },
        {
          type = "int",
          name = "triangleCount",
          description = "Number of triangles stored (indexed or not)"
        },
        {
          type = "float *",
          name = "vertices",
          description = "Vertex position (XYZ - 3 components per vertex) (shader-location = 0)"
        },
        {
          type = "float *",
          name = "texcoords",
          description = "Vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1)"
        },
        {
          type = "float *",
          name = "texcoords2",
          description = "Vertex texture second coordinates (UV - 2 components per vertex) (shader-location = 5)"
        },
        {
          type = "float *",
          name = "normals",
          description = "Vertex normals (XYZ - 3 components per vertex) (shader-location = 2)"
        },
        {
          type = "float *",
          name = "tangents",
          description = "Vertex tangents (XYZW - 4 components per vertex) (shader-location = 4)"
        },
        {
          type = "unsigned char *",
          name = "colors",
          description = "Vertex colors (RGBA - 4 components per vertex) (shader-location = 3)"
        },
        {
          type = "unsigned short *",
          name = "indices",
          description = "Vertex indices (in case vertex data comes indexed)"
        },
        {
          type = "float *",
          name = "animVertices",
          description = "Animated vertex positions (after bones transformations)"
        },
        {
          type = "float *",
          name = "animNormals",
          description = "Animated normals (after bones transformations)"
        },
        {
          type = "unsigned char *",
          name = "boneIds",
          description = "Vertex bone ids, max 255 bone ids, up to 4 bones influence by vertex (skinning) (shader-location = 6)"
        },
        {
          type = "float *",
          name = "boneWeights",
          description = "Vertex bone weight, up to 4 bones influence by vertex (skinning) (shader-location = 7)"
        },
        {
          type = "RL_Matrix *",
          name = "boneMatrices",
          description = "Bones animated transformation matrices"
        },
        {
          type = "int",
          name = "boneCount",
          description = "Number of bones"
        },
        {
          type = "unsigned int",
          name = "vaoId",
          description = "OpenGL Vertex Array Object id"
        },
        {
          type = "unsigned int *",
          name = "vboId",
          description = "OpenGL Vertex Buffer Objects id (default vertex data)"
        }
      }
    },
    {
      name = "RL_Shader",
      description = "RL_Shader",
      fields = {
        {
          type = "unsigned int",
          name = "id",
          description = "RL_Shader program id"
        },
        {
          type = "int *",
          name = "locs",
          description = "RL_Shader locations array (RL_MAX_SHADER_LOCATIONS)"
        }
      }
    },
    {
      name = "RL_MaterialMap",
      description = "RL_MaterialMap",
      fields = {
        {
          type = "RL_Texture2D",
          name = "texture",
          description = "RL_Material map texture"
        },
        {
          type = "RL_Color",
          name = "color",
          description = "RL_Material map color"
        },
        {
          type = "float",
          name = "value",
          description = "RL_Material map value"
        }
      }
    },
    {
      name = "RL_Material",
      description = "RL_Material, includes shader and maps",
      fields = {
        {
          type = "RL_Shader",
          name = "shader",
          description = "RL_Material shader"
        },
        {
          type = "RL_MaterialMap *",
          name = "maps",
          description = "RL_Material maps array (MAX_MATERIAL_MAPS)"
        },
        {
          type = "float[4]",
          name = "params",
          description = "RL_Material generic parameters (if required)"
        }
      }
    },
    {
      name = "RL_Transform",
      description = "RL_Transform, vertex transformation data",
      fields = {
        {
          type = "RL_Vector3",
          name = "translation",
          description = "Translation"
        },
        {
          type = "RL_Quaternion",
          name = "rotation",
          description = "Rotation"
        },
        {
          type = "RL_Vector3",
          name = "scale",
          description = "Scale"
        }
      }
    },
    {
      name = "RL_BoneInfo",
      description = "Bone, skeletal animation bone",
      fields = {
        {
          type = "char[32]",
          name = "name",
          description = "Bone name"
        },
        {
          type = "int",
          name = "parent",
          description = "Bone parent"
        }
      }
    },
    {
      name = "RL_Model",
      description = "RL_Model, meshes, materials and animation data",
      fields = {
        {
          type = "RL_Matrix",
          name = "transform",
          description = "Local transform matrix"
        },
        {
          type = "int",
          name = "meshCount",
          description = "Number of meshes"
        },
        {
          type = "int",
          name = "materialCount",
          description = "Number of materials"
        },
        {
          type = "RL_Mesh *",
          name = "meshes",
          description = "Meshes array"
        },
        {
          type = "RL_Material *",
          name = "materials",
          description = "Materials array"
        },
        {
          type = "int *",
          name = "meshMaterial",
          description = "RL_Mesh material number"
        },
        {
          type = "int",
          name = "boneCount",
          description = "Number of bones"
        },
        {
          type = "RL_BoneInfo *",
          name = "bones",
          description = "Bones information (skeleton)"
        },
        {
          type = "RL_Transform *",
          name = "bindPose",
          description = "Bones base transformation (pose)"
        }
      }
    },
    {
      name = "RL_ModelAnimation",
      description = "RL_ModelAnimation",
      fields = {
        {
          type = "int",
          name = "boneCount",
          description = "Number of bones"
        },
        {
          type = "int",
          name = "frameCount",
          description = "Number of animation frames"
        },
        {
          type = "RL_BoneInfo *",
          name = "bones",
          description = "Bones information (skeleton)"
        },
        {
          type = "RL_Transform **",
          name = "framePoses",
          description = "Poses array by frame"
        },
        {
          type = "char[32]",
          name = "name",
          description = "Animation name"
        }
      }
    },
    {
      name = "RL_Ray",
      description = "RL_Ray, ray for raycasting",
      fields = {
        {
          type = "RL_Vector3",
          name = "position",
          description = "RL_Ray position (origin)"
        },
        {
          type = "RL_Vector3",
          name = "direction",
          description = "RL_Ray direction (normalized)"
        }
      }
    },
    {
      name = "RL_RayCollision",
      description = "RL_RayCollision, ray hit information",
      fields = {
        {
          type = "bool",
          name = "hit",
          description = "Did the ray hit something?"
        },
        {
          type = "float",
          name = "distance",
          description = "Distance to the nearest hit"
        },
        {
          type = "RL_Vector3",
          name = "point",
          description = "Point of the nearest hit"
        },
        {
          type = "RL_Vector3",
          name = "normal",
          description = "Surface normal of hit"
        }
      }
    },
    {
      name = "RL_BoundingBox",
      description = "RL_BoundingBox",
      fields = {
        {
          type = "RL_Vector3",
          name = "min",
          description = "Minimum vertex box-corner"
        },
        {
          type = "RL_Vector3",
          name = "max",
          description = "Maximum vertex box-corner"
        }
      }
    },
    {
      name = "RL_Wave",
      description = "RL_Wave, audio wave data",
      fields = {
        {
          type = "unsigned int",
          name = "frameCount",
          description = "Total number of frames (considering channels)"
        },
        {
          type = "unsigned int",
          name = "sampleRate",
          description = "Frequency (samples per second)"
        },
        {
          type = "unsigned int",
          name = "sampleSize",
          description = "Bit depth (bits per sample): 8, 16, 32 (24 not supported)"
        },
        {
          type = "unsigned int",
          name = "channels",
          description = "Number of channels (1-mono, 2-stereo, ...)"
        },
        {
          type = "void *",
          name = "data",
          description = "Buffer data pointer"
        }
      }
    },
    {
      name = "RL_AudioStream",
      description = "RL_AudioStream, custom audio stream",
      fields = {
        {
          type = "RL_rAudioBuffer *",
          name = "buffer",
          description = "Pointer to internal data used by the audio system"
        },
        {
          type = "RL_rAudioProcessor *",
          name = "processor",
          description = "Pointer to internal data processor, useful for audio effects"
        },
        {
          type = "unsigned int",
          name = "sampleRate",
          description = "Frequency (samples per second)"
        },
        {
          type = "unsigned int",
          name = "sampleSize",
          description = "Bit depth (bits per sample): 8, 16, 32 (24 not supported)"
        },
        {
          type = "unsigned int",
          name = "channels",
          description = "Number of channels (1-mono, 2-stereo, ...)"
        }
      }
    },
    {
      name = "RL_Sound",
      description = "RL_Sound",
      fields = {
        {
          type = "RL_AudioStream",
          name = "stream",
          description = "Audio stream"
        },
        {
          type = "unsigned int",
          name = "frameCount",
          description = "Total number of frames (considering channels)"
        }
      }
    },
    {
      name = "RL_Music",
      description = "RL_Music, audio stream, anything longer than ~10 seconds should be streamed",
      fields = {
        {
          type = "RL_AudioStream",
          name = "stream",
          description = "Audio stream"
        },
        {
          type = "unsigned int",
          name = "frameCount",
          description = "Total number of frames (considering channels)"
        },
        {
          type = "bool",
          name = "looping",
          description = "RL_Music looping enable"
        },
        {
          type = "int",
          name = "ctxType",
          description = "Type of music context (audio filetype)"
        },
        {
          type = "void *",
          name = "ctxData",
          description = "Audio context data, depends on type"
        }
      }
    },
    {
      name = "RL_VrDeviceInfo",
      description = "RL_VrDeviceInfo, Head-Mounted-Display device parameters",
      fields = {
        {
          type = "int",
          name = "hResolution",
          description = "Horizontal resolution in pixels"
        },
        {
          type = "int",
          name = "vResolution",
          description = "Vertical resolution in pixels"
        },
        {
          type = "float",
          name = "hScreenSize",
          description = "Horizontal size in meters"
        },
        {
          type = "float",
          name = "vScreenSize",
          description = "Vertical size in meters"
        },
        {
          type = "float",
          name = "eyeToScreenDistance",
          description = "Distance between eye and display in meters"
        },
        {
          type = "float",
          name = "lensSeparationDistance",
          description = "Lens separation distance in meters"
        },
        {
          type = "float",
          name = "interpupillaryDistance",
          description = "IPD (distance between pupils) in meters"
        },
        {
          type = "float[4]",
          name = "lensDistortionValues",
          description = "Lens distortion constant parameters"
        },
        {
          type = "float[4]",
          name = "chromaAbCorrection",
          description = "Chromatic aberration correction parameters"
        }
      }
    },
    {
      name = "RL_VrStereoConfig",
      description = "RL_VrStereoConfig, VR stereo rendering configuration for simulator",
      fields = {
        {
          type = "RL_Matrix[2]",
          name = "projection",
          description = "VR projection matrices (per eye)"
        },
        {
          type = "RL_Matrix[2]",
          name = "viewOffset",
          description = "VR view offset matrices (per eye)"
        },
        {
          type = "float[2]",
          name = "leftLensCenter",
          description = "VR left lens center"
        },
        {
          type = "float[2]",
          name = "rightLensCenter",
          description = "VR right lens center"
        },
        {
          type = "float[2]",
          name = "leftScreenCenter",
          description = "VR left screen center"
        },
        {
          type = "float[2]",
          name = "rightScreenCenter",
          description = "VR right screen center"
        },
        {
          type = "float[2]",
          name = "scale",
          description = "VR distortion scale"
        },
        {
          type = "float[2]",
          name = "scaleIn",
          description = "VR distortion scale in"
        }
      }
    },
    {
      name = "RL_FilePathList",
      description = "File path list",
      fields = {
        {
          type = "unsigned int",
          name = "capacity",
          description = "Filepaths max entries"
        },
        {
          type = "unsigned int",
          name = "count",
          description = "Filepaths entries count"
        },
        {
          type = "char **",
          name = "paths",
          description = "Filepaths entries"
        }
      }
    },
    {
      name = "RL_AutomationEvent",
      description = "Automation event",
      fields = {
        {
          type = "unsigned int",
          name = "frame",
          description = "Event frame"
        },
        {
          type = "unsigned int",
          name = "type",
          description = "Event type (AutomationEventType)"
        },
        {
          type = "int[4]",
          name = "params",
          description = "Event parameters (if required)"
        }
      }
    },
    {
      name = "RL_AutomationEventList",
      description = "Automation event list",
      fields = {
        {
          type = "unsigned int",
          name = "capacity",
          description = "Events max entries (MAX_AUTOMATION_EVENTS)"
        },
        {
          type = "unsigned int",
          name = "count",
          description = "Events entries count"
        },
        {
          type = "RL_AutomationEvent *",
          name = "events",
          description = "Events entries"
        }
      }
    }
  },
  aliases = {
    {
      type = "RL_Vector4",
      name = "RL_Quaternion",
      description = "RL_Quaternion, 4 components (RL_Vector4 alias)"
    },
    {
      type = "RL_Texture",
      name = "RL_Texture2D",
      description = "RL_Texture2D, same as RL_Texture"
    },
    {
      type = "RL_Texture",
      name = "RL_TextureCubemap",
      description = "RL_TextureCubemap, same as RL_Texture"
    },
    {
      type = "RL_RenderTexture",
      name = "RL_RenderTexture2D",
      description = "RL_RenderTexture2D, same as RL_RenderTexture"
    },
    {
      type = "RL_Camera3D",
      name = "RL_Camera",
      description = "RL_Camera type fallback, defaults to RL_Camera3D"
    }
  },
  enums = {
    {
      name = "RL_ConfigFlags",
      description = "System/Window config flags",
      values = {
        {
          name = "FLAG_VSYNC_HINT",
          value = 64,
          description = "Set to try enabling V-Sync on GPU"
        },
        {
          name = "FLAG_FULLSCREEN_MODE",
          value = 2,
          description = "Set to run program in fullscreen"
        },
        {
          name = "FLAG_WINDOW_RESIZABLE",
          value = 4,
          description = "Set to allow resizable window"
        },
        {
          name = "FLAG_WINDOW_UNDECORATED",
          value = 8,
          description = "Set to disable window decoration (frame and buttons)"
        },
        {
          name = "FLAG_WINDOW_HIDDEN",
          value = 128,
          description = "Set to hide window"
        },
        {
          name = "FLAG_WINDOW_MINIMIZED",
          value = 512,
          description = "Set to minimize window (iconify)"
        },
        {
          name = "FLAG_WINDOW_MAXIMIZED",
          value = 1024,
          description = "Set to maximize window (expanded to monitor)"
        },
        {
          name = "FLAG_WINDOW_UNFOCUSED",
          value = 2048,
          description = "Set to window non focused"
        },
        {
          name = "FLAG_WINDOW_TOPMOST",
          value = 4096,
          description = "Set to window always on top"
        },
        {
          name = "FLAG_WINDOW_ALWAYS_RUN",
          value = 256,
          description = "Set to allow windows running while minimized"
        },
        {
          name = "FLAG_WINDOW_TRANSPARENT",
          value = 16,
          description = "Set to allow transparent framebuffer"
        },
        {
          name = "FLAG_WINDOW_HIGHDPI",
          value = 8192,
          description = "Set to support HighDPI"
        },
        {
          name = "FLAG_WINDOW_MOUSE_PASSTHROUGH",
          value = 16384,
          description = "Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED"
        },
        {
          name = "FLAG_BORDERLESS_WINDOWED_MODE",
          value = 32768,
          description = "Set to run program in borderless windowed mode"
        },
        {
          name = "FLAG_MSAA_4X_HINT",
          value = 32,
          description = "Set to try enabling MSAA 4X"
        },
        {
          name = "FLAG_INTERLACED_HINT",
          value = 65536,
          description = "Set to try enabling interlaced video format (for V3D)"
        }
      }
    },
    {
      name = "RL_TraceLogLevel",
      description = "Trace log level",
      values = {
        {
          name = "LOG_ALL",
          value = 0,
          description = "Display all logs"
        },
        {
          name = "LOG_TRACE",
          value = 1,
          description = "Trace logging, intended for internal use only"
        },
        {
          name = "LOG_DEBUG",
          value = 2,
          description = "Debug logging, used for internal debugging, it should be disabled on release builds"
        },
        {
          name = "LOG_INFO",
          value = 3,
          description = "Info logging, used for program execution info"
        },
        {
          name = "LOG_WARNING",
          value = 4,
          description = "Warning logging, used on recoverable failures"
        },
        {
          name = "LOG_ERROR",
          value = 5,
          description = "Error logging, used on unrecoverable failures"
        },
        {
          name = "LOG_FATAL",
          value = 6,
          description = "Fatal logging, used to abort program: exit(EXIT_FAILURE)"
        },
        {
          name = "LOG_NONE",
          value = 7,
          description = "Disable logging"
        }
      }
    },
    {
      name = "RL_KeyboardKey",
      description = "Keyboard keys (US keyboard layout)",
      values = {
        {
          name = "KEY_NULL",
          value = 0,
          description = "Key: NULL, used for no key pressed"
        },
        {
          name = "KEY_APOSTROPHE",
          value = 39,
          description = "Key: '"
        },
        {
          name = "KEY_COMMA",
          value = 44,
          description = "Key: ,"
        },
        {
          name = "KEY_MINUS",
          value = 45,
          description = "Key: -"
        },
        {
          name = "KEY_PERIOD",
          value = 46,
          description = "Key: ."
        },
        {
          name = "KEY_SLASH",
          value = 47,
          description = "Key: /"
        },
        {
          name = "KEY_ZERO",
          value = 48,
          description = "Key: 0"
        },
        {
          name = "KEY_ONE",
          value = 49,
          description = "Key: 1"
        },
        {
          name = "KEY_TWO",
          value = 50,
          description = "Key: 2"
        },
        {
          name = "KEY_THREE",
          value = 51,
          description = "Key: 3"
        },
        {
          name = "KEY_FOUR",
          value = 52,
          description = "Key: 4"
        },
        {
          name = "KEY_FIVE",
          value = 53,
          description = "Key: 5"
        },
        {
          name = "KEY_SIX",
          value = 54,
          description = "Key: 6"
        },
        {
          name = "KEY_SEVEN",
          value = 55,
          description = "Key: 7"
        },
        {
          name = "KEY_EIGHT",
          value = 56,
          description = "Key: 8"
        },
        {
          name = "KEY_NINE",
          value = 57,
          description = "Key: 9"
        },
        {
          name = "KEY_SEMICOLON",
          value = 59,
          description = "Key: ;"
        },
        {
          name = "KEY_EQUAL",
          value = 61,
          description = "Key: ="
        },
        {
          name = "KEY_A",
          value = 65,
          description = "Key: A | a"
        },
        {
          name = "KEY_B",
          value = 66,
          description = "Key: B | b"
        },
        {
          name = "KEY_C",
          value = 67,
          description = "Key: C | c"
        },
        {
          name = "KEY_D",
          value = 68,
          description = "Key: D | d"
        },
        {
          name = "KEY_E",
          value = 69,
          description = "Key: E | e"
        },
        {
          name = "KEY_F",
          value = 70,
          description = "Key: F | f"
        },
        {
          name = "KEY_G",
          value = 71,
          description = "Key: G | g"
        },
        {
          name = "KEY_H",
          value = 72,
          description = "Key: H | h"
        },
        {
          name = "KEY_I",
          value = 73,
          description = "Key: I | i"
        },
        {
          name = "KEY_J",
          value = 74,
          description = "Key: J | j"
        },
        {
          name = "KEY_K",
          value = 75,
          description = "Key: K | k"
        },
        {
          name = "KEY_L",
          value = 76,
          description = "Key: L | l"
        },
        {
          name = "KEY_M",
          value = 77,
          description = "Key: M | m"
        },
        {
          name = "KEY_N",
          value = 78,
          description = "Key: N | n"
        },
        {
          name = "KEY_O",
          value = 79,
          description = "Key: O | o"
        },
        {
          name = "KEY_P",
          value = 80,
          description = "Key: P | p"
        },
        {
          name = "KEY_Q",
          value = 81,
          description = "Key: Q | q"
        },
        {
          name = "KEY_R",
          value = 82,
          description = "Key: R | r"
        },
        {
          name = "KEY_S",
          value = 83,
          description = "Key: S | s"
        },
        {
          name = "KEY_T",
          value = 84,
          description = "Key: T | t"
        },
        {
          name = "KEY_U",
          value = 85,
          description = "Key: U | u"
        },
        {
          name = "KEY_V",
          value = 86,
          description = "Key: V | v"
        },
        {
          name = "KEY_W",
          value = 87,
          description = "Key: W | w"
        },
        {
          name = "KEY_X",
          value = 88,
          description = "Key: X | x"
        },
        {
          name = "KEY_Y",
          value = 89,
          description = "Key: Y | y"
        },
        {
          name = "KEY_Z",
          value = 90,
          description = "Key: Z | z"
        },
        {
          name = "KEY_LEFT_BRACKET",
          value = 91,
          description = "Key: ["
        },
        {
          name = "KEY_BACKSLASH",
          value = 92,
          description = "Key: '\\'"
        },
        {
          name = "KEY_RIGHT_BRACKET",
          value = 93,
          description = "Key: ]"
        },
        {
          name = "KEY_GRAVE",
          value = 96,
          description = "Key: `"
        },
        {
          name = "KEY_SPACE",
          value = 32,
          description = "Key: Space"
        },
        {
          name = "KEY_ESCAPE",
          value = 256,
          description = "Key: Esc"
        },
        {
          name = "KEY_ENTER",
          value = 257,
          description = "Key: Enter"
        },
        {
          name = "KEY_TAB",
          value = 258,
          description = "Key: Tab"
        },
        {
          name = "KEY_BACKSPACE",
          value = 259,
          description = "Key: Backspace"
        },
        {
          name = "KEY_INSERT",
          value = 260,
          description = "Key: Ins"
        },
        {
          name = "KEY_DELETE",
          value = 261,
          description = "Key: Del"
        },
        {
          name = "KEY_RIGHT",
          value = 262,
          description = "Key: Cursor right"
        },
        {
          name = "KEY_LEFT",
          value = 263,
          description = "Key: Cursor left"
        },
        {
          name = "KEY_DOWN",
          value = 264,
          description = "Key: Cursor down"
        },
        {
          name = "KEY_UP",
          value = 265,
          description = "Key: Cursor up"
        },
        {
          name = "KEY_PAGE_UP",
          value = 266,
          description = "Key: Page up"
        },
        {
          name = "KEY_PAGE_DOWN",
          value = 267,
          description = "Key: Page down"
        },
        {
          name = "KEY_HOME",
          value = 268,
          description = "Key: Home"
        },
        {
          name = "KEY_END",
          value = 269,
          description = "Key: End"
        },
        {
          name = "KEY_CAPS_LOCK",
          value = 280,
          description = "Key: Caps lock"
        },
        {
          name = "KEY_SCROLL_LOCK",
          value = 281,
          description = "Key: Scroll down"
        },
        {
          name = "KEY_NUM_LOCK",
          value = 282,
          description = "Key: Num lock"
        },
        {
          name = "KEY_PRINT_SCREEN",
          value = 283,
          description = "Key: Print screen"
        },
        {
          name = "KEY_PAUSE",
          value = 284,
          description = "Key: Pause"
        },
        {
          name = "KEY_F1",
          value = 290,
          description = "Key: F1"
        },
        {
          name = "KEY_F2",
          value = 291,
          description = "Key: F2"
        },
        {
          name = "KEY_F3",
          value = 292,
          description = "Key: F3"
        },
        {
          name = "KEY_F4",
          value = 293,
          description = "Key: F4"
        },
        {
          name = "KEY_F5",
          value = 294,
          description = "Key: F5"
        },
        {
          name = "KEY_F6",
          value = 295,
          description = "Key: F6"
        },
        {
          name = "KEY_F7",
          value = 296,
          description = "Key: F7"
        },
        {
          name = "KEY_F8",
          value = 297,
          description = "Key: F8"
        },
        {
          name = "KEY_F9",
          value = 298,
          description = "Key: F9"
        },
        {
          name = "KEY_F10",
          value = 299,
          description = "Key: F10"
        },
        {
          name = "KEY_F11",
          value = 300,
          description = "Key: F11"
        },
        {
          name = "KEY_F12",
          value = 301,
          description = "Key: F12"
        },
        {
          name = "KEY_LEFT_SHIFT",
          value = 340,
          description = "Key: Shift left"
        },
        {
          name = "KEY_LEFT_CONTROL",
          value = 341,
          description = "Key: Control left"
        },
        {
          name = "KEY_LEFT_ALT",
          value = 342,
          description = "Key: Alt left"
        },
        {
          name = "KEY_LEFT_SUPER",
          value = 343,
          description = "Key: Super left"
        },
        {
          name = "KEY_RIGHT_SHIFT",
          value = 344,
          description = "Key: Shift right"
        },
        {
          name = "KEY_RIGHT_CONTROL",
          value = 345,
          description = "Key: Control right"
        },
        {
          name = "KEY_RIGHT_ALT",
          value = 346,
          description = "Key: Alt right"
        },
        {
          name = "KEY_RIGHT_SUPER",
          value = 347,
          description = "Key: Super right"
        },
        {
          name = "KEY_KB_MENU",
          value = 348,
          description = "Key: KB menu"
        },
        {
          name = "KEY_KP_0",
          value = 320,
          description = "Key: Keypad 0"
        },
        {
          name = "KEY_KP_1",
          value = 321,
          description = "Key: Keypad 1"
        },
        {
          name = "KEY_KP_2",
          value = 322,
          description = "Key: Keypad 2"
        },
        {
          name = "KEY_KP_3",
          value = 323,
          description = "Key: Keypad 3"
        },
        {
          name = "KEY_KP_4",
          value = 324,
          description = "Key: Keypad 4"
        },
        {
          name = "KEY_KP_5",
          value = 325,
          description = "Key: Keypad 5"
        },
        {
          name = "KEY_KP_6",
          value = 326,
          description = "Key: Keypad 6"
        },
        {
          name = "KEY_KP_7",
          value = 327,
          description = "Key: Keypad 7"
        },
        {
          name = "KEY_KP_8",
          value = 328,
          description = "Key: Keypad 8"
        },
        {
          name = "KEY_KP_9",
          value = 329,
          description = "Key: Keypad 9"
        },
        {
          name = "KEY_KP_DECIMAL",
          value = 330,
          description = "Key: Keypad ."
        },
        {
          name = "KEY_KP_DIVIDE",
          value = 331,
          description = "Key: Keypad /"
        },
        {
          name = "KEY_KP_MULTIPLY",
          value = 332,
          description = "Key: Keypad *"
        },
        {
          name = "KEY_KP_SUBTRACT",
          value = 333,
          description = "Key: Keypad -"
        },
        {
          name = "KEY_KP_ADD",
          value = 334,
          description = "Key: Keypad +"
        },
        {
          name = "KEY_KP_ENTER",
          value = 335,
          description = "Key: Keypad Enter"
        },
        {
          name = "KEY_KP_EQUAL",
          value = 336,
          description = "Key: Keypad ="
        },
        {
          name = "KEY_BACK",
          value = 4,
          description = "Key: Android back button"
        },
        {
          name = "KEY_MENU",
          value = 5,
          description = "Key: Android menu button"
        },
        {
          name = "KEY_VOLUME_UP",
          value = 24,
          description = "Key: Android volume up button"
        },
        {
          name = "KEY_VOLUME_DOWN",
          value = 25,
          description = "Key: Android volume down button"
        }
      }
    },
    {
      name = "RL_MouseButton",
      description = "Mouse buttons",
      values = {
        {
          name = "MOUSE_BUTTON_LEFT",
          value = 0,
          description = "Mouse button left"
        },
        {
          name = "MOUSE_BUTTON_RIGHT",
          value = 1,
          description = "Mouse button right"
        },
        {
          name = "MOUSE_BUTTON_MIDDLE",
          value = 2,
          description = "Mouse button middle (pressed wheel)"
        },
        {
          name = "MOUSE_BUTTON_SIDE",
          value = 3,
          description = "Mouse button side (advanced mouse device)"
        },
        {
          name = "MOUSE_BUTTON_EXTRA",
          value = 4,
          description = "Mouse button extra (advanced mouse device)"
        },
        {
          name = "MOUSE_BUTTON_FORWARD",
          value = 5,
          description = "Mouse button forward (advanced mouse device)"
        },
        {
          name = "MOUSE_BUTTON_BACK",
          value = 6,
          description = "Mouse button back (advanced mouse device)"
        }
      }
    },
    {
      name = "RL_MouseCursor",
      description = "Mouse cursor",
      values = {
        {
          name = "MOUSE_CURSOR_DEFAULT",
          value = 0,
          description = "Default pointer shape"
        },
        {
          name = "MOUSE_CURSOR_ARROW",
          value = 1,
          description = "Arrow shape"
        },
        {
          name = "MOUSE_CURSOR_IBEAM",
          value = 2,
          description = "Text writing cursor shape"
        },
        {
          name = "MOUSE_CURSOR_CROSSHAIR",
          value = 3,
          description = "Cross shape"
        },
        {
          name = "MOUSE_CURSOR_POINTING_HAND",
          value = 4,
          description = "Pointing hand cursor"
        },
        {
          name = "MOUSE_CURSOR_RESIZE_EW",
          value = 5,
          description = "Horizontal resize/move arrow shape"
        },
        {
          name = "MOUSE_CURSOR_RESIZE_NS",
          value = 6,
          description = "Vertical resize/move arrow shape"
        },
        {
          name = "MOUSE_CURSOR_RESIZE_NWSE",
          value = 7,
          description = "Top-left to bottom-right diagonal resize/move arrow shape"
        },
        {
          name = "MOUSE_CURSOR_RESIZE_NESW",
          value = 8,
          description = "The top-right to bottom-left diagonal resize/move arrow shape"
        },
        {
          name = "MOUSE_CURSOR_RESIZE_ALL",
          value = 9,
          description = "The omnidirectional resize/move cursor shape"
        },
        {
          name = "MOUSE_CURSOR_NOT_ALLOWED",
          value = 10,
          description = "The operation-not-allowed shape"
        }
      }
    },
    {
      name = "RL_GamepadButton",
      description = "Gamepad buttons",
      values = {
        {
          name = "GAMEPAD_BUTTON_UNKNOWN",
          value = 0,
          description = "Unknown button, just for error checking"
        },
        {
          name = "GAMEPAD_BUTTON_LEFT_FACE_UP",
          value = 1,
          description = "Gamepad left DPAD up button"
        },
        {
          name = "GAMEPAD_BUTTON_LEFT_FACE_RIGHT",
          value = 2,
          description = "Gamepad left DPAD right button"
        },
        {
          name = "GAMEPAD_BUTTON_LEFT_FACE_DOWN",
          value = 3,
          description = "Gamepad left DPAD down button"
        },
        {
          name = "GAMEPAD_BUTTON_LEFT_FACE_LEFT",
          value = 4,
          description = "Gamepad left DPAD left button"
        },
        {
          name = "GAMEPAD_BUTTON_RIGHT_FACE_UP",
          value = 5,
          description = "Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)"
        },
        {
          name = "GAMEPAD_BUTTON_RIGHT_FACE_RIGHT",
          value = 6,
          description = "Gamepad right button right (i.e. PS3: Circle, Xbox: B)"
        },
        {
          name = "GAMEPAD_BUTTON_RIGHT_FACE_DOWN",
          value = 7,
          description = "Gamepad right button down (i.e. PS3: Cross, Xbox: A)"
        },
        {
          name = "GAMEPAD_BUTTON_RIGHT_FACE_LEFT",
          value = 8,
          description = "Gamepad right button left (i.e. PS3: Square, Xbox: X)"
        },
        {
          name = "GAMEPAD_BUTTON_LEFT_TRIGGER_1",
          value = 9,
          description = "Gamepad top/back trigger left (first), it could be a trailing button"
        },
        {
          name = "GAMEPAD_BUTTON_LEFT_TRIGGER_2",
          value = 10,
          description = "Gamepad top/back trigger left (second), it could be a trailing button"
        },
        {
          name = "GAMEPAD_BUTTON_RIGHT_TRIGGER_1",
          value = 11,
          description = "Gamepad top/back trigger right (first), it could be a trailing button"
        },
        {
          name = "GAMEPAD_BUTTON_RIGHT_TRIGGER_2",
          value = 12,
          description = "Gamepad top/back trigger right (second), it could be a trailing button"
        },
        {
          name = "GAMEPAD_BUTTON_MIDDLE_LEFT",
          value = 13,
          description = "Gamepad center buttons, left one (i.e. PS3: Select)"
        },
        {
          name = "GAMEPAD_BUTTON_MIDDLE",
          value = 14,
          description = "Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)"
        },
        {
          name = "GAMEPAD_BUTTON_MIDDLE_RIGHT",
          value = 15,
          description = "Gamepad center buttons, right one (i.e. PS3: Start)"
        },
        {
          name = "GAMEPAD_BUTTON_LEFT_THUMB",
          value = 16,
          description = "Gamepad joystick pressed button left"
        },
        {
          name = "GAMEPAD_BUTTON_RIGHT_THUMB",
          value = 17,
          description = "Gamepad joystick pressed button right"
        }
      }
    },
    {
      name = "RL_GamepadAxis",
      description = "Gamepad axis",
      values = {
        {
          name = "GAMEPAD_AXIS_LEFT_X",
          value = 0,
          description = "Gamepad left stick X axis"
        },
        {
          name = "GAMEPAD_AXIS_LEFT_Y",
          value = 1,
          description = "Gamepad left stick Y axis"
        },
        {
          name = "GAMEPAD_AXIS_RIGHT_X",
          value = 2,
          description = "Gamepad right stick X axis"
        },
        {
          name = "GAMEPAD_AXIS_RIGHT_Y",
          value = 3,
          description = "Gamepad right stick Y axis"
        },
        {
          name = "GAMEPAD_AXIS_LEFT_TRIGGER",
          value = 4,
          description = "Gamepad back trigger left, pressure level: [1..-1]"
        },
        {
          name = "GAMEPAD_AXIS_RIGHT_TRIGGER",
          value = 5,
          description = "Gamepad back trigger right, pressure level: [1..-1]"
        }
      }
    },
    {
      name = "RL_MaterialMapIndex",
      description = "RL_Material map index",
      values = {
        {
          name = "MATERIAL_MAP_ALBEDO",
          value = 0,
          description = "Albedo material (same as: MATERIAL_MAP_DIFFUSE)"
        },
        {
          name = "MATERIAL_MAP_METALNESS",
          value = 1,
          description = "Metalness material (same as: MATERIAL_MAP_SPECULAR)"
        },
        {
          name = "MATERIAL_MAP_NORMAL",
          value = 2,
          description = "Normal material"
        },
        {
          name = "MATERIAL_MAP_ROUGHNESS",
          value = 3,
          description = "Roughness material"
        },
        {
          name = "MATERIAL_MAP_OCCLUSION",
          value = 4,
          description = "Ambient occlusion material"
        },
        {
          name = "MATERIAL_MAP_EMISSION",
          value = 5,
          description = "Emission material"
        },
        {
          name = "MATERIAL_MAP_HEIGHT",
          value = 6,
          description = "Heightmap material"
        },
        {
          name = "MATERIAL_MAP_CUBEMAP",
          value = 7,
          description = "Cubemap material (NOTE: Uses GL_TEXTURE_CUBE_MAP)"
        },
        {
          name = "MATERIAL_MAP_IRRADIANCE",
          value = 8,
          description = "Irradiance material (NOTE: Uses GL_TEXTURE_CUBE_MAP)"
        },
        {
          name = "MATERIAL_MAP_PREFILTER",
          value = 9,
          description = "Prefilter material (NOTE: Uses GL_TEXTURE_CUBE_MAP)"
        },
        {
          name = "MATERIAL_MAP_BRDF",
          value = 10,
          description = "Brdf material"
        }
      }
    },
    {
      name = "RL_ShaderLocationIndex",
      description = "RL_Shader location index",
      values = {
        {
          name = "SHADER_LOC_VERTEX_POSITION",
          value = 0,
          description = "RL_Shader location: vertex attribute: position"
        },
        {
          name = "SHADER_LOC_VERTEX_TEXCOORD01",
          value = 1,
          description = "RL_Shader location: vertex attribute: texcoord01"
        },
        {
          name = "SHADER_LOC_VERTEX_TEXCOORD02",
          value = 2,
          description = "RL_Shader location: vertex attribute: texcoord02"
        },
        {
          name = "SHADER_LOC_VERTEX_NORMAL",
          value = 3,
          description = "RL_Shader location: vertex attribute: normal"
        },
        {
          name = "SHADER_LOC_VERTEX_TANGENT",
          value = 4,
          description = "RL_Shader location: vertex attribute: tangent"
        },
        {
          name = "SHADER_LOC_VERTEX_COLOR",
          value = 5,
          description = "RL_Shader location: vertex attribute: color"
        },
        {
          name = "SHADER_LOC_MATRIX_MVP",
          value = 6,
          description = "RL_Shader location: matrix uniform: model-view-projection"
        },
        {
          name = "SHADER_LOC_MATRIX_VIEW",
          value = 7,
          description = "RL_Shader location: matrix uniform: view (camera transform)"
        },
        {
          name = "SHADER_LOC_MATRIX_PROJECTION",
          value = 8,
          description = "RL_Shader location: matrix uniform: projection"
        },
        {
          name = "SHADER_LOC_MATRIX_MODEL",
          value = 9,
          description = "RL_Shader location: matrix uniform: model (transform)"
        },
        {
          name = "SHADER_LOC_MATRIX_NORMAL",
          value = 10,
          description = "RL_Shader location: matrix uniform: normal"
        },
        {
          name = "SHADER_LOC_VECTOR_VIEW",
          value = 11,
          description = "RL_Shader location: vector uniform: view"
        },
        {
          name = "SHADER_LOC_COLOR_DIFFUSE",
          value = 12,
          description = "RL_Shader location: vector uniform: diffuse color"
        },
        {
          name = "SHADER_LOC_COLOR_SPECULAR",
          value = 13,
          description = "RL_Shader location: vector uniform: specular color"
        },
        {
          name = "SHADER_LOC_COLOR_AMBIENT",
          value = 14,
          description = "RL_Shader location: vector uniform: ambient color"
        },
        {
          name = "SHADER_LOC_MAP_ALBEDO",
          value = 15,
          description = "RL_Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE)"
        },
        {
          name = "SHADER_LOC_MAP_METALNESS",
          value = 16,
          description = "RL_Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR)"
        },
        {
          name = "SHADER_LOC_MAP_NORMAL",
          value = 17,
          description = "RL_Shader location: sampler2d texture: normal"
        },
        {
          name = "SHADER_LOC_MAP_ROUGHNESS",
          value = 18,
          description = "RL_Shader location: sampler2d texture: roughness"
        },
        {
          name = "SHADER_LOC_MAP_OCCLUSION",
          value = 19,
          description = "RL_Shader location: sampler2d texture: occlusion"
        },
        {
          name = "SHADER_LOC_MAP_EMISSION",
          value = 20,
          description = "RL_Shader location: sampler2d texture: emission"
        },
        {
          name = "SHADER_LOC_MAP_HEIGHT",
          value = 21,
          description = "RL_Shader location: sampler2d texture: height"
        },
        {
          name = "SHADER_LOC_MAP_CUBEMAP",
          value = 22,
          description = "RL_Shader location: samplerCube texture: cubemap"
        },
        {
          name = "SHADER_LOC_MAP_IRRADIANCE",
          value = 23,
          description = "RL_Shader location: samplerCube texture: irradiance"
        },
        {
          name = "SHADER_LOC_MAP_PREFILTER",
          value = 24,
          description = "RL_Shader location: samplerCube texture: prefilter"
        },
        {
          name = "SHADER_LOC_MAP_BRDF",
          value = 25,
          description = "RL_Shader location: sampler2d texture: brdf"
        },
        {
          name = "SHADER_LOC_VERTEX_BONEIDS",
          value = 26,
          description = "RL_Shader location: vertex attribute: boneIds"
        },
        {
          name = "SHADER_LOC_VERTEX_BONEWEIGHTS",
          value = 27,
          description = "RL_Shader location: vertex attribute: boneWeights"
        },
        {
          name = "SHADER_LOC_BONE_MATRICES",
          value = 28,
          description = "RL_Shader location: array of matrices uniform: boneMatrices"
        }
      }
    },
    {
      name = "RL_ShaderUniformDataType",
      description = "RL_Shader uniform data type",
      values = {
        {
          name = "SHADER_UNIFORM_FLOAT",
          value = 0,
          description = "RL_Shader uniform type: float"
        },
        {
          name = "SHADER_UNIFORM_VEC2",
          value = 1,
          description = "RL_Shader uniform type: vec2 (2 float)"
        },
        {
          name = "SHADER_UNIFORM_VEC3",
          value = 2,
          description = "RL_Shader uniform type: vec3 (3 float)"
        },
        {
          name = "SHADER_UNIFORM_VEC4",
          value = 3,
          description = "RL_Shader uniform type: vec4 (4 float)"
        },
        {
          name = "SHADER_UNIFORM_INT",
          value = 4,
          description = "RL_Shader uniform type: int"
        },
        {
          name = "SHADER_UNIFORM_IVEC2",
          value = 5,
          description = "RL_Shader uniform type: ivec2 (2 int)"
        },
        {
          name = "SHADER_UNIFORM_IVEC3",
          value = 6,
          description = "RL_Shader uniform type: ivec3 (3 int)"
        },
        {
          name = "SHADER_UNIFORM_IVEC4",
          value = 7,
          description = "RL_Shader uniform type: ivec4 (4 int)"
        },
        {
          name = "SHADER_UNIFORM_SAMPLER2D",
          value = 8,
          description = "RL_Shader uniform type: sampler2d"
        }
      }
    },
    {
      name = "RL_ShaderAttributeDataType",
      description = "RL_Shader attribute data types",
      values = {
        {
          name = "SHADER_ATTRIB_FLOAT",
          value = 0,
          description = "RL_Shader attribute type: float"
        },
        {
          name = "SHADER_ATTRIB_VEC2",
          value = 1,
          description = "RL_Shader attribute type: vec2 (2 float)"
        },
        {
          name = "SHADER_ATTRIB_VEC3",
          value = 2,
          description = "RL_Shader attribute type: vec3 (3 float)"
        },
        {
          name = "SHADER_ATTRIB_VEC4",
          value = 3,
          description = "RL_Shader attribute type: vec4 (4 float)"
        }
      }
    },
    {
      name = "RL_PixelFormat",
      description = "Pixel formats",
      values = {
        {
          name = "PIXELFORMAT_UNCOMPRESSED_GRAYSCALE",
          value = 1,
          description = "8 bit per pixel (no alpha)"
        },
        {
          name = "PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA",
          value = 2,
          description = "8*2 bpp (2 channels)"
        },
        {
          name = "PIXELFORMAT_UNCOMPRESSED_R5G6B5",
          value = 3,
          description = "16 bpp"
        },
        {
          name = "PIXELFORMAT_UNCOMPRESSED_R8G8B8",
          value = 4,
          description = "24 bpp"
        },
        {
          name = "PIXELFORMAT_UNCOMPRESSED_R5G5B5A1",
          value = 5,
          description = "16 bpp (1 bit alpha)"
        },
        {
          name = "PIXELFORMAT_UNCOMPRESSED_R4G4B4A4",
          value = 6,
          description = "16 bpp (4 bit alpha)"
        },
        {
          name = "PIXELFORMAT_UNCOMPRESSED_R8G8B8A8",
          value = 7,
          description = "32 bpp"
        },
        {
          name = "PIXELFORMAT_UNCOMPRESSED_R32",
          value = 8,
          description = "32 bpp (1 channel - float)"
        },
        {
          name = "PIXELFORMAT_UNCOMPRESSED_R32G32B32",
          value = 9,
          description = "32*3 bpp (3 channels - float)"
        },
        {
          name = "PIXELFORMAT_UNCOMPRESSED_R32G32B32A32",
          value = 10,
          description = "32*4 bpp (4 channels - float)"
        },
        {
          name = "PIXELFORMAT_UNCOMPRESSED_R16",
          value = 11,
          description = "16 bpp (1 channel - half float)"
        },
        {
          name = "PIXELFORMAT_UNCOMPRESSED_R16G16B16",
          value = 12,
          description = "16*3 bpp (3 channels - half float)"
        },
        {
          name = "PIXELFORMAT_UNCOMPRESSED_R16G16B16A16",
          value = 13,
          description = "16*4 bpp (4 channels - half float)"
        },
        {
          name = "PIXELFORMAT_COMPRESSED_DXT1_RGB",
          value = 14,
          description = "4 bpp (no alpha)"
        },
        {
          name = "PIXELFORMAT_COMPRESSED_DXT1_RGBA",
          value = 15,
          description = "4 bpp (1 bit alpha)"
        },
        {
          name = "PIXELFORMAT_COMPRESSED_DXT3_RGBA",
          value = 16,
          description = "8 bpp"
        },
        {
          name = "PIXELFORMAT_COMPRESSED_DXT5_RGBA",
          value = 17,
          description = "8 bpp"
        },
        {
          name = "PIXELFORMAT_COMPRESSED_ETC1_RGB",
          value = 18,
          description = "4 bpp"
        },
        {
          name = "PIXELFORMAT_COMPRESSED_ETC2_RGB",
          value = 19,
          description = "4 bpp"
        },
        {
          name = "PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA",
          value = 20,
          description = "8 bpp"
        },
        {
          name = "PIXELFORMAT_COMPRESSED_PVRT_RGB",
          value = 21,
          description = "4 bpp"
        },
        {
          name = "PIXELFORMAT_COMPRESSED_PVRT_RGBA",
          value = 22,
          description = "4 bpp"
        },
        {
          name = "PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA",
          value = 23,
          description = "8 bpp"
        },
        {
          name = "PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA",
          value = 24,
          description = "2 bpp"
        }
      }
    },
    {
      name = "RL_TextureFilter",
      description = "RL_Texture parameters: filter mode",
      values = {
        {
          name = "TEXTURE_FILTER_POINT",
          value = 0,
          description = "No filter, just pixel approximation"
        },
        {
          name = "TEXTURE_FILTER_BILINEAR",
          value = 1,
          description = "Linear filtering"
        },
        {
          name = "TEXTURE_FILTER_TRILINEAR",
          value = 2,
          description = "Trilinear filtering (linear with mipmaps)"
        },
        {
          name = "TEXTURE_FILTER_ANISOTROPIC_4X",
          value = 3,
          description = "Anisotropic filtering 4x"
        },
        {
          name = "TEXTURE_FILTER_ANISOTROPIC_8X",
          value = 4,
          description = "Anisotropic filtering 8x"
        },
        {
          name = "TEXTURE_FILTER_ANISOTROPIC_16X",
          value = 5,
          description = "Anisotropic filtering 16x"
        }
      }
    },
    {
      name = "RL_TextureWrap",
      description = "RL_Texture parameters: wrap mode",
      values = {
        {
          name = "TEXTURE_WRAP_REPEAT",
          value = 0,
          description = "Repeats texture in tiled mode"
        },
        {
          name = "TEXTURE_WRAP_CLAMP",
          value = 1,
          description = "Clamps texture to edge pixel in tiled mode"
        },
        {
          name = "TEXTURE_WRAP_MIRROR_REPEAT",
          value = 2,
          description = "Mirrors and repeats the texture in tiled mode"
        },
        {
          name = "TEXTURE_WRAP_MIRROR_CLAMP",
          value = 3,
          description = "Mirrors and clamps to border the texture in tiled mode"
        }
      }
    },
    {
      name = "RL_CubemapLayout",
      description = "Cubemap layouts",
      values = {
        {
          name = "CUBEMAP_LAYOUT_AUTO_DETECT",
          value = 0,
          description = "Automatically detect layout type"
        },
        {
          name = "CUBEMAP_LAYOUT_LINE_VERTICAL",
          value = 1,
          description = "Layout is defined by a vertical line with faces"
        },
        {
          name = "CUBEMAP_LAYOUT_LINE_HORIZONTAL",
          value = 2,
          description = "Layout is defined by a horizontal line with faces"
        },
        {
          name = "CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR",
          value = 3,
          description = "Layout is defined by a 3x4 cross with cubemap faces"
        },
        {
          name = "CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE",
          value = 4,
          description = "Layout is defined by a 4x3 cross with cubemap faces"
        }
      }
    },
    {
      name = "RL_FontType",
      description = "RL_Font type, defines generation method",
      values = {
        {
          name = "FONT_DEFAULT",
          value = 0,
          description = "Default font generation, anti-aliased"
        },
        {
          name = "FONT_BITMAP",
          value = 1,
          description = "Bitmap font generation, no anti-aliasing"
        },
        {
          name = "FONT_SDF",
          value = 2,
          description = "SDF font generation, requires external shader"
        }
      }
    },
    {
      name = "RL_BlendMode",
      description = "RL_Color blending modes (pre-defined)",
      values = {
        {
          name = "BLEND_ALPHA",
          value = 0,
          description = "Blend textures considering alpha (default)"
        },
        {
          name = "BLEND_ADDITIVE",
          value = 1,
          description = "Blend textures adding colors"
        },
        {
          name = "BLEND_MULTIPLIED",
          value = 2,
          description = "Blend textures multiplying colors"
        },
        {
          name = "BLEND_ADD_COLORS",
          value = 3,
          description = "Blend textures adding colors (alternative)"
        },
        {
          name = "BLEND_SUBTRACT_COLORS",
          value = 4,
          description = "Blend textures subtracting colors (alternative)"
        },
        {
          name = "BLEND_ALPHA_PREMULTIPLY",
          value = 5,
          description = "Blend premultiplied textures considering alpha"
        },
        {
          name = "BLEND_CUSTOM",
          value = 6,
          description = "Blend textures using custom src/dst factors (use rlSetBlendFactors())"
        },
        {
          name = "BLEND_CUSTOM_SEPARATE",
          value = 7,
          description = "Blend textures using custom rgb/alpha separate src/dst factors (use rlSetBlendFactorsSeparate())"
        }
      }
    },
    {
      name = "RL_Gesture",
      description = "RL_Gesture",
      values = {
        {
          name = "GESTURE_NONE",
          value = 0,
          description = "No gesture"
        },
        {
          name = "GESTURE_TAP",
          value = 1,
          description = "Tap gesture"
        },
        {
          name = "GESTURE_DOUBLETAP",
          value = 2,
          description = "Double tap gesture"
        },
        {
          name = "GESTURE_HOLD",
          value = 4,
          description = "Hold gesture"
        },
        {
          name = "GESTURE_DRAG",
          value = 8,
          description = "Drag gesture"
        },
        {
          name = "GESTURE_SWIPE_RIGHT",
          value = 16,
          description = "Swipe right gesture"
        },
        {
          name = "GESTURE_SWIPE_LEFT",
          value = 32,
          description = "Swipe left gesture"
        },
        {
          name = "GESTURE_SWIPE_UP",
          value = 64,
          description = "Swipe up gesture"
        },
        {
          name = "GESTURE_SWIPE_DOWN",
          value = 128,
          description = "Swipe down gesture"
        },
        {
          name = "GESTURE_PINCH_IN",
          value = 256,
          description = "Pinch in gesture"
        },
        {
          name = "GESTURE_PINCH_OUT",
          value = 512,
          description = "Pinch out gesture"
        }
      }
    },
    {
      name = "RL_CameraMode",
      description = "RL_Camera system modes",
      values = {
        {
          name = "CAMERA_CUSTOM",
          value = 0,
          description = "RL_Camera custom, controlled by user (RL_UpdateCamera() does nothing)"
        },
        {
          name = "CAMERA_FREE",
          value = 1,
          description = "RL_Camera free mode"
        },
        {
          name = "CAMERA_ORBITAL",
          value = 2,
          description = "RL_Camera orbital, around target, zoom supported"
        },
        {
          name = "CAMERA_FIRST_PERSON",
          value = 3,
          description = "RL_Camera first person"
        },
        {
          name = "CAMERA_THIRD_PERSON",
          value = 4,
          description = "RL_Camera third person"
        }
      }
    },
    {
      name = "RL_CameraProjection",
      description = "RL_Camera projection",
      values = {
        {
          name = "CAMERA_PERSPECTIVE",
          value = 0,
          description = "Perspective projection"
        },
        {
          name = "CAMERA_ORTHOGRAPHIC",
          value = 1,
          description = "Orthographic projection"
        }
      }
    },
    {
      name = "RL_NPatchLayout",
      description = "N-patch layout",
      values = {
        {
          name = "NPATCH_NINE_PATCH",
          value = 0,
          description = "Npatch layout: 3x3 tiles"
        },
        {
          name = "NPATCH_THREE_PATCH_VERTICAL",
          value = 1,
          description = "Npatch layout: 1x3 tiles"
        },
        {
          name = "NPATCH_THREE_PATCH_HORIZONTAL",
          value = 2,
          description = "Npatch layout: 3x1 tiles"
        }
      }
    }
  },
  callbacks = {
    {
      name = "RL_TraceLogCallback",
      description = "Logging: Redirect trace log messages",
      returnType = "void",
      params = {
        {type = "int", name = "logLevel"},
        {type = "const char *", name = "text"},
        {type = "va_list", name = "args"}
      }
    },
    {
      name = "RL_LoadFileDataCallback",
      description = "FileIO: Load binary data",
      returnType = "unsigned char *",
      params = {
        {type = "const char *", name = "fileName"},
        {type = "int *", name = "dataSize"}
      }
    },
    {
      name = "RL_SaveFileDataCallback",
      description = "FileIO: Save binary data",
      returnType = "bool",
      params = {
        {type = "const char *", name = "fileName"},
        {type = "void *", name = "data"},
        {type = "int", name = "dataSize"}
      }
    },
    {
      name = "RL_LoadFileTextCallback",
      description = "FileIO: Load text data",
      returnType = "char *",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_SaveFileTextCallback",
      description = "FileIO: Save text data",
      returnType = "bool",
      params = {
        {type = "const char *", name = "fileName"},
        {type = "char *", name = "text"}
      }
    },
    {
      name = "AudioCallback",
      description = "",
      returnType = "void",
      params = {
        {type = "void *", name = "bufferData"},
        {type = "unsigned int", name = "frames"}
      }
    }
  },
  functions = {
    {
      name = "RL_InitWindow",
      description = "Initialize window and OpenGL context",
      returnType = "void",
      params = {
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "const char *", name = "title"}
      }
    },
    {
      name = "RL_CloseWindow",
      description = "Close window and unload OpenGL context",
      returnType = "void"
    },
    {
      name = "RL_WindowShouldClose",
      description = "Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)",
      returnType = "bool"
    },
    {
      name = "RL_IsWindowReady",
      description = "Check if window has been initialized successfully",
      returnType = "bool"
    },
    {
      name = "RL_IsWindowFullscreen",
      description = "Check if window is currently fullscreen",
      returnType = "bool"
    },
    {
      name = "RL_IsWindowHidden",
      description = "Check if window is currently hidden",
      returnType = "bool"
    },
    {
      name = "RL_IsWindowMinimized",
      description = "Check if window is currently minimized",
      returnType = "bool"
    },
    {
      name = "RL_IsWindowMaximized",
      description = "Check if window is currently maximized",
      returnType = "bool"
    },
    {
      name = "RL_IsWindowFocused",
      description = "Check if window is currently focused",
      returnType = "bool"
    },
    {
      name = "RL_IsWindowResized",
      description = "Check if window has been resized last frame",
      returnType = "bool"
    },
    {
      name = "RL_IsWindowState",
      description = "Check if one specific window flag is enabled",
      returnType = "bool",
      params = {
        {type = "unsigned int", name = "flag"}
      }
    },
    {
      name = "RL_SetWindowState",
      description = "Set window configuration state using flags",
      returnType = "void",
      params = {
        {type = "unsigned int", name = "flags"}
      }
    },
    {
      name = "RL_ClearWindowState",
      description = "Clear window configuration state flags",
      returnType = "void",
      params = {
        {type = "unsigned int", name = "flags"}
      }
    },
    {
      name = "RL_ToggleFullscreen",
      description = "Toggle window state: fullscreen/windowed, resizes monitor to match window resolution",
      returnType = "void"
    },
    {
      name = "RL_ToggleBorderlessWindowed",
      description = "Toggle window state: borderless windowed, resizes window to match monitor resolution",
      returnType = "void"
    },
    {
      name = "RL_MaximizeWindow",
      description = "Set window state: maximized, if resizable",
      returnType = "void"
    },
    {
      name = "RL_MinimizeWindow",
      description = "Set window state: minimized, if resizable",
      returnType = "void"
    },
    {
      name = "RL_RestoreWindow",
      description = "Set window state: not minimized/maximized",
      returnType = "void"
    },
    {
      name = "RL_SetWindowIcon",
      description = "Set icon for window (single image, RGBA 32bit)",
      returnType = "void",
      params = {
        {type = "RL_Image", name = "image"}
      }
    },
    {
      name = "RL_SetWindowIcons",
      description = "Set icon for window (multiple images, RGBA 32bit)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "images"},
        {type = "int", name = "count"}
      }
    },
    {
      name = "RL_SetWindowTitle",
      description = "Set title for window",
      returnType = "void",
      params = {
        {type = "const char *", name = "title"}
      }
    },
    {
      name = "RL_SetWindowPosition",
      description = "Set window position on screen",
      returnType = "void",
      params = {
        {type = "int", name = "x"},
        {type = "int", name = "y"}
      }
    },
    {
      name = "RL_SetWindowMonitor",
      description = "Set monitor for the current window",
      returnType = "void",
      params = {
        {type = "int", name = "monitor"}
      }
    },
    {
      name = "RL_SetWindowMinSize",
      description = "Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)",
      returnType = "void",
      params = {
        {type = "int", name = "width"},
        {type = "int", name = "height"}
      }
    },
    {
      name = "RL_SetWindowMaxSize",
      description = "Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)",
      returnType = "void",
      params = {
        {type = "int", name = "width"},
        {type = "int", name = "height"}
      }
    },
    {
      name = "RL_SetWindowSize",
      description = "Set window dimensions",
      returnType = "void",
      params = {
        {type = "int", name = "width"},
        {type = "int", name = "height"}
      }
    },
    {
      name = "RL_SetWindowOpacity",
      description = "Set window opacity [0.0f..1.0f]",
      returnType = "void",
      params = {
        {type = "float", name = "opacity"}
      }
    },
    {
      name = "RL_SetWindowFocused",
      description = "Set window focused",
      returnType = "void"
    },
    {
      name = "RL_GetWindowHandle",
      description = "Get native window handle",
      returnType = "void *"
    },
    {
      name = "RL_GetScreenWidth",
      description = "Get current screen width",
      returnType = "int"
    },
    {
      name = "RL_GetScreenHeight",
      description = "Get current screen height",
      returnType = "int"
    },
    {
      name = "RL_GetRenderWidth",
      description = "Get current render width (it considers HiDPI)",
      returnType = "int"
    },
    {
      name = "RL_GetRenderHeight",
      description = "Get current render height (it considers HiDPI)",
      returnType = "int"
    },
    {
      name = "RL_GetMonitorCount",
      description = "Get number of connected monitors",
      returnType = "int"
    },
    {
      name = "RL_GetCurrentMonitor",
      description = "Get current monitor where window is placed",
      returnType = "int"
    },
    {
      name = "RL_GetMonitorPosition",
      description = "Get specified monitor position",
      returnType = "RL_Vector2",
      params = {
        {type = "int", name = "monitor"}
      }
    },
    {
      name = "RL_GetMonitorWidth",
      description = "Get specified monitor width (current video mode used by monitor)",
      returnType = "int",
      params = {
        {type = "int", name = "monitor"}
      }
    },
    {
      name = "RL_GetMonitorHeight",
      description = "Get specified monitor height (current video mode used by monitor)",
      returnType = "int",
      params = {
        {type = "int", name = "monitor"}
      }
    },
    {
      name = "RL_GetMonitorPhysicalWidth",
      description = "Get specified monitor physical width in millimetres",
      returnType = "int",
      params = {
        {type = "int", name = "monitor"}
      }
    },
    {
      name = "RL_GetMonitorPhysicalHeight",
      description = "Get specified monitor physical height in millimetres",
      returnType = "int",
      params = {
        {type = "int", name = "monitor"}
      }
    },
    {
      name = "RL_GetMonitorRefreshRate",
      description = "Get specified monitor refresh rate",
      returnType = "int",
      params = {
        {type = "int", name = "monitor"}
      }
    },
    {
      name = "RL_GetWindowPosition",
      description = "Get window position XY on monitor",
      returnType = "RL_Vector2"
    },
    {
      name = "RL_GetWindowScaleDPI",
      description = "Get window scale DPI factor",
      returnType = "RL_Vector2"
    },
    {
      name = "RL_GetMonitorName",
      description = "Get the human-readable, UTF-8 encoded name of the specified monitor",
      returnType = "const char *",
      params = {
        {type = "int", name = "monitor"}
      }
    },
    {
      name = "RL_SetClipboardText",
      description = "Set clipboard text content",
      returnType = "void",
      params = {
        {type = "const char *", name = "text"}
      }
    },
    {
      name = "RL_GetClipboardText",
      description = "Get clipboard text content",
      returnType = "const char *"
    },
    {
      name = "GetClipboardImage",
      description = "Get clipboard image content",
      returnType = "RL_Image"
    },
    {
      name = "RL_EnableEventWaiting",
      description = "Enable waiting for events on RL_EndDrawing(), no automatic event polling",
      returnType = "void"
    },
    {
      name = "RL_DisableEventWaiting",
      description = "Disable waiting for events on RL_EndDrawing(), automatic events polling",
      returnType = "void"
    },
    {
      name = "RL_ShowCursor",
      description = "Shows cursor",
      returnType = "void"
    },
    {
      name = "RL_HideCursor",
      description = "Hides cursor",
      returnType = "void"
    },
    {
      name = "RL_IsCursorHidden",
      description = "Check if cursor is not visible",
      returnType = "bool"
    },
    {
      name = "RL_EnableCursor",
      description = "Enables cursor (unlock cursor)",
      returnType = "void"
    },
    {
      name = "RL_DisableCursor",
      description = "Disables cursor (lock cursor)",
      returnType = "void"
    },
    {
      name = "RL_IsCursorOnScreen",
      description = "Check if cursor is on the screen",
      returnType = "bool"
    },
    {
      name = "RL_ClearBackground",
      description = "Set background color (framebuffer clear color)",
      returnType = "void",
      params = {
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_BeginDrawing",
      description = "Setup canvas (framebuffer) to start drawing",
      returnType = "void"
    },
    {
      name = "RL_EndDrawing",
      description = "End canvas drawing and swap buffers (double buffering)",
      returnType = "void"
    },
    {
      name = "RL_BeginMode2D",
      description = "Begin 2D mode with custom camera (2D)",
      returnType = "void",
      params = {
        {type = "RL_Camera2D", name = "camera"}
      }
    },
    {
      name = "RL_EndMode2D",
      description = "Ends 2D mode with custom camera",
      returnType = "void"
    },
    {
      name = "RL_BeginMode3D",
      description = "Begin 3D mode with custom camera (3D)",
      returnType = "void",
      params = {
        {type = "RL_Camera3D", name = "camera"}
      }
    },
    {
      name = "RL_EndMode3D",
      description = "Ends 3D mode and returns to default 2D orthographic mode",
      returnType = "void"
    },
    {
      name = "RL_BeginTextureMode",
      description = "Begin drawing to render texture",
      returnType = "void",
      params = {
        {type = "RL_RenderTexture2D", name = "target"}
      }
    },
    {
      name = "RL_EndTextureMode",
      description = "Ends drawing to render texture",
      returnType = "void"
    },
    {
      name = "RL_BeginShaderMode",
      description = "Begin custom shader drawing",
      returnType = "void",
      params = {
        {type = "RL_Shader", name = "shader"}
      }
    },
    {
      name = "RL_EndShaderMode",
      description = "End custom shader drawing (use default shader)",
      returnType = "void"
    },
    {
      name = "RL_BeginBlendMode",
      description = "Begin blending mode (alpha, additive, multiplied, subtract, custom)",
      returnType = "void",
      params = {
        {type = "int", name = "mode"}
      }
    },
    {
      name = "RL_EndBlendMode",
      description = "End blending mode (reset to default: alpha blending)",
      returnType = "void"
    },
    {
      name = "RL_BeginScissorMode",
      description = "Begin scissor mode (define screen area for following drawing)",
      returnType = "void",
      params = {
        {type = "int", name = "x"},
        {type = "int", name = "y"},
        {type = "int", name = "width"},
        {type = "int", name = "height"}
      }
    },
    {
      name = "RL_EndScissorMode",
      description = "End scissor mode",
      returnType = "void"
    },
    {
      name = "RL_BeginVrStereoMode",
      description = "Begin stereo rendering (requires VR simulator)",
      returnType = "void",
      params = {
        {type = "RL_VrStereoConfig", name = "config"}
      }
    },
    {
      name = "RL_EndVrStereoMode",
      description = "End stereo rendering (requires VR simulator)",
      returnType = "void"
    },
    {
      name = "RL_LoadVrStereoConfig",
      description = "Load VR stereo config for VR simulator device parameters",
      returnType = "RL_VrStereoConfig",
      params = {
        {type = "RL_VrDeviceInfo", name = "device"}
      }
    },
    {
      name = "RL_UnloadVrStereoConfig",
      description = "Unload VR stereo config",
      returnType = "void",
      params = {
        {type = "RL_VrStereoConfig", name = "config"}
      }
    },
    {
      name = "RL_LoadShader",
      description = "Load shader from files and bind default locations",
      returnType = "RL_Shader",
      params = {
        {type = "const char *", name = "vsFileName"},
        {type = "const char *", name = "fsFileName"}
      }
    },
    {
      name = "RL_LoadShaderFromMemory",
      description = "Load shader from code strings and bind default locations",
      returnType = "RL_Shader",
      params = {
        {type = "const char *", name = "vsCode"},
        {type = "const char *", name = "fsCode"}
      }
    },
    {
      name = "IsShaderValid",
      description = "Check if a shader is valid (loaded on GPU)",
      returnType = "bool",
      params = {
        {type = "RL_Shader", name = "shader"}
      }
    },
    {
      name = "RL_GetShaderLocation",
      description = "Get shader uniform location",
      returnType = "int",
      params = {
        {type = "RL_Shader", name = "shader"},
        {type = "const char *", name = "uniformName"}
      }
    },
    {
      name = "RL_GetShaderLocationAttrib",
      description = "Get shader attribute location",
      returnType = "int",
      params = {
        {type = "RL_Shader", name = "shader"},
        {type = "const char *", name = "attribName"}
      }
    },
    {
      name = "RL_SetShaderValue",
      description = "Set shader uniform value",
      returnType = "void",
      params = {
        {type = "RL_Shader", name = "shader"},
        {type = "int", name = "locIndex"},
        {type = "const void *", name = "value"},
        {type = "int", name = "uniformType"}
      }
    },
    {
      name = "RL_SetShaderValueV",
      description = "Set shader uniform value vector",
      returnType = "void",
      params = {
        {type = "RL_Shader", name = "shader"},
        {type = "int", name = "locIndex"},
        {type = "const void *", name = "value"},
        {type = "int", name = "uniformType"},
        {type = "int", name = "count"}
      }
    },
    {
      name = "RL_SetShaderValueMatrix",
      description = "Set shader uniform value (matrix 4x4)",
      returnType = "void",
      params = {
        {type = "RL_Shader", name = "shader"},
        {type = "int", name = "locIndex"},
        {type = "RL_Matrix", name = "mat"}
      }
    },
    {
      name = "RL_SetShaderValueTexture",
      description = "Set shader uniform value for texture (sampler2d)",
      returnType = "void",
      params = {
        {type = "RL_Shader", name = "shader"},
        {type = "int", name = "locIndex"},
        {type = "RL_Texture2D", name = "texture"}
      }
    },
    {
      name = "RL_UnloadShader",
      description = "Unload shader from GPU memory (VRAM)",
      returnType = "void",
      params = {
        {type = "RL_Shader", name = "shader"}
      }
    },
    {
      name = "RL_GetScreenToWorldRay",
      description = "Get a ray trace from screen position (i.e mouse)",
      returnType = "RL_Ray",
      params = {
        {type = "RL_Vector2", name = "position"},
        {type = "RL_Camera", name = "camera"}
      }
    },
    {
      name = "RL_GetScreenToWorldRayEx",
      description = "Get a ray trace from screen position (i.e mouse) in a viewport",
      returnType = "RL_Ray",
      params = {
        {type = "RL_Vector2", name = "position"},
        {type = "RL_Camera", name = "camera"},
        {type = "int", name = "width"},
        {type = "int", name = "height"}
      }
    },
    {
      name = "RL_GetWorldToScreen",
      description = "Get the screen space position for a 3d world space position",
      returnType = "RL_Vector2",
      params = {
        {type = "RL_Vector3", name = "position"},
        {type = "RL_Camera", name = "camera"}
      }
    },
    {
      name = "RL_GetWorldToScreenEx",
      description = "Get size position for a 3d world space position",
      returnType = "RL_Vector2",
      params = {
        {type = "RL_Vector3", name = "position"},
        {type = "RL_Camera", name = "camera"},
        {type = "int", name = "width"},
        {type = "int", name = "height"}
      }
    },
    {
      name = "RL_GetWorldToScreen2D",
      description = "Get the screen space position for a 2d camera world space position",
      returnType = "RL_Vector2",
      params = {
        {type = "RL_Vector2", name = "position"},
        {type = "RL_Camera2D", name = "camera"}
      }
    },
    {
      name = "RL_GetScreenToWorld2D",
      description = "Get the world space position for a 2d camera screen space position",
      returnType = "RL_Vector2",
      params = {
        {type = "RL_Vector2", name = "position"},
        {type = "RL_Camera2D", name = "camera"}
      }
    },
    {
      name = "RL_GetCameraMatrix",
      description = "Get camera transform matrix (view matrix)",
      returnType = "RL_Matrix",
      params = {
        {type = "RL_Camera", name = "camera"}
      }
    },
    {
      name = "RL_GetCameraMatrix2D",
      description = "Get camera 2d transform matrix",
      returnType = "RL_Matrix",
      params = {
        {type = "RL_Camera2D", name = "camera"}
      }
    },
    {
      name = "RL_SetTargetFPS",
      description = "Set target FPS (maximum)",
      returnType = "void",
      params = {
        {type = "int", name = "fps"}
      }
    },
    {
      name = "RL_GetFrameTime",
      description = "Get time in seconds for last frame drawn (delta time)",
      returnType = "float"
    },
    {
      name = "RL_GetTime",
      description = "Get elapsed time in seconds since RL_InitWindow()",
      returnType = "double"
    },
    {
      name = "RL_GetFPS",
      description = "Get current FPS",
      returnType = "int"
    },
    {
      name = "RL_SwapScreenBuffer",
      description = "Swap back buffer with front buffer (screen drawing)",
      returnType = "void"
    },
    {
      name = "RL_PollInputEvents",
      description = "Register all input events",
      returnType = "void"
    },
    {
      name = "RL_WaitTime",
      description = "Wait for some time (halt program execution)",
      returnType = "void",
      params = {
        {type = "double", name = "seconds"}
      }
    },
    {
      name = "RL_SetRandomSeed",
      description = "Set the seed for the random number generator",
      returnType = "void",
      params = {
        {type = "unsigned int", name = "seed"}
      }
    },
    {
      name = "RL_GetRandomValue",
      description = "Get a random value between min and max (both included)",
      returnType = "int",
      params = {
        {type = "int", name = "min"},
        {type = "int", name = "max"}
      }
    },
    {
      name = "RL_LoadRandomSequence",
      description = "Load random values sequence, no values repeated",
      returnType = "int *",
      params = {
        {type = "unsigned int", name = "count"},
        {type = "int", name = "min"},
        {type = "int", name = "max"}
      }
    },
    {
      name = "RL_UnloadRandomSequence",
      description = "Unload random values sequence",
      returnType = "void",
      params = {
        {type = "int *", name = "sequence"}
      }
    },
    {
      name = "RL_TakeScreenshot",
      description = "Takes a screenshot of current screen (filename extension defines format)",
      returnType = "void",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_SetConfigFlags",
      description = "Setup init configuration flags (view FLAGS)",
      returnType = "void",
      params = {
        {type = "unsigned int", name = "flags"}
      }
    },
    {
      name = "RL_OpenURL",
      description = "Open URL with default system browser (if available)",
      returnType = "void",
      params = {
        {type = "const char *", name = "url"}
      }
    },
    {
      name = "RL_TraceLog",
      description = "Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)",
      returnType = "void",
      params = {
        {type = "int", name = "logLevel"},
        {type = "const char *", name = "text"},
        {type = "...", name = "args"}
      }
    },
    {
      name = "RL_SetTraceLogLevel",
      description = "Set the current threshold (minimum) log level",
      returnType = "void",
      params = {
        {type = "int", name = "logLevel"}
      }
    },
    {
      name = "RL_MemAlloc",
      description = "Internal memory allocator",
      returnType = "void *",
      params = {
        {type = "unsigned int", name = "size"}
      }
    },
    {
      name = "RL_MemRealloc",
      description = "Internal memory reallocator",
      returnType = "void *",
      params = {
        {type = "void *", name = "ptr"},
        {type = "unsigned int", name = "size"}
      }
    },
    {
      name = "RL_MemFree",
      description = "Internal memory free",
      returnType = "void",
      params = {
        {type = "void *", name = "ptr"}
      }
    },
    {
      name = "RL_SetTraceLogCallback",
      description = "Set custom trace log",
      returnType = "void",
      params = {
        {type = "RL_TraceLogCallback", name = "callback"}
      }
    },
    {
      name = "RL_SetLoadFileDataCallback",
      description = "Set custom file binary data loader",
      returnType = "void",
      params = {
        {type = "RL_LoadFileDataCallback", name = "callback"}
      }
    },
    {
      name = "RL_SetSaveFileDataCallback",
      description = "Set custom file binary data saver",
      returnType = "void",
      params = {
        {type = "RL_SaveFileDataCallback", name = "callback"}
      }
    },
    {
      name = "RL_SetLoadFileTextCallback",
      description = "Set custom file text data loader",
      returnType = "void",
      params = {
        {type = "RL_LoadFileTextCallback", name = "callback"}
      }
    },
    {
      name = "RL_SetSaveFileTextCallback",
      description = "Set custom file text data saver",
      returnType = "void",
      params = {
        {type = "RL_SaveFileTextCallback", name = "callback"}
      }
    },
    {
      name = "RL_LoadFileData",
      description = "Load file data as byte array (read)",
      returnType = "unsigned char *",
      params = {
        {type = "const char *", name = "fileName"},
        {type = "int *", name = "dataSize"}
      }
    },
    {
      name = "RL_UnloadFileData",
      description = "Unload file data allocated by RL_LoadFileData()",
      returnType = "void",
      params = {
        {type = "unsigned char *", name = "data"}
      }
    },
    {
      name = "RL_SaveFileData",
      description = "Save data to file from byte array (write), returns true on success",
      returnType = "bool",
      params = {
        {type = "const char *", name = "fileName"},
        {type = "void *", name = "data"},
        {type = "int", name = "dataSize"}
      }
    },
    {
      name = "RL_ExportDataAsCode",
      description = "Export data to code (.h), returns true on success",
      returnType = "bool",
      params = {
        {type = "const unsigned char *", name = "data"},
        {type = "int", name = "dataSize"},
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_LoadFileText",
      description = "Load text data from file (read), returns a '\\0' terminated string",
      returnType = "char *",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_UnloadFileText",
      description = "Unload file text data allocated by RL_LoadFileText()",
      returnType = "void",
      params = {
        {type = "char *", name = "text"}
      }
    },
    {
      name = "RL_SaveFileText",
      description = "Save text data to file (write), string must be '\\0' terminated, returns true on success",
      returnType = "bool",
      params = {
        {type = "const char *", name = "fileName"},
        {type = "char *", name = "text"}
      }
    },
    {
      name = "RL_FileExists",
      description = "Check if file exists",
      returnType = "bool",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_DirectoryExists",
      description = "Check if a directory path exists",
      returnType = "bool",
      params = {
        {type = "const char *", name = "dirPath"}
      }
    },
    {
      name = "RL_IsFileExtension",
      description = "Check file extension (including point: .png, .wav)",
      returnType = "bool",
      params = {
        {type = "const char *", name = "fileName"},
        {type = "const char *", name = "ext"}
      }
    },
    {
      name = "RL_GetFileLength",
      description = "Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)",
      returnType = "int",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_GetFileExtension",
      description = "Get pointer to extension for a filename string (includes dot: '.png')",
      returnType = "const char *",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_GetFileName",
      description = "Get pointer to filename for a path string",
      returnType = "const char *",
      params = {
        {type = "const char *", name = "filePath"}
      }
    },
    {
      name = "RL_GetFileNameWithoutExt",
      description = "Get filename string without extension (uses static string)",
      returnType = "const char *",
      params = {
        {type = "const char *", name = "filePath"}
      }
    },
    {
      name = "RL_GetDirectoryPath",
      description = "Get full path for a given fileName with path (uses static string)",
      returnType = "const char *",
      params = {
        {type = "const char *", name = "filePath"}
      }
    },
    {
      name = "RL_GetPrevDirectoryPath",
      description = "Get previous directory path for a given path (uses static string)",
      returnType = "const char *",
      params = {
        {type = "const char *", name = "dirPath"}
      }
    },
    {
      name = "RL_GetWorkingDirectory",
      description = "Get current working directory (uses static string)",
      returnType = "const char *"
    },
    {
      name = "RL_GetApplicationDirectory",
      description = "Get the directory of the running application (uses static string)",
      returnType = "const char *"
    },
    {
      name = "MakeDirectory",
      description = "Create directories (including full path requested), returns 0 on success",
      returnType = "int",
      params = {
        {type = "const char *", name = "dirPath"}
      }
    },
    {
      name = "RL_ChangeDirectory",
      description = "Change working directory, return true on success",
      returnType = "bool",
      params = {
        {type = "const char *", name = "dir"}
      }
    },
    {
      name = "RL_IsPathFile",
      description = "Check if a given path is a file or a directory",
      returnType = "bool",
      params = {
        {type = "const char *", name = "path"}
      }
    },
    {
      name = "RL_IsFileNameValid",
      description = "Check if fileName is valid for the platform/OS",
      returnType = "bool",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_LoadDirectoryFiles",
      description = "Load directory filepaths",
      returnType = "RL_FilePathList",
      params = {
        {type = "const char *", name = "dirPath"}
      }
    },
    {
      name = "RL_LoadDirectoryFilesEx",
      description = "Load directory filepaths with extension filtering and recursive directory scan. Use 'DIR' in the filter string to include directories in the result",
      returnType = "RL_FilePathList",
      params = {
        {type = "const char *", name = "basePath"},
        {type = "const char *", name = "filter"},
        {type = "bool", name = "scanSubdirs"}
      }
    },
    {
      name = "RL_UnloadDirectoryFiles",
      description = "Unload filepaths",
      returnType = "void",
      params = {
        {type = "RL_FilePathList", name = "files"}
      }
    },
    {
      name = "RL_IsFileDropped",
      description = "Check if a file has been dropped into window",
      returnType = "bool"
    },
    {
      name = "RL_LoadDroppedFiles",
      description = "Load dropped filepaths",
      returnType = "RL_FilePathList"
    },
    {
      name = "RL_UnloadDroppedFiles",
      description = "Unload dropped filepaths",
      returnType = "void",
      params = {
        {type = "RL_FilePathList", name = "files"}
      }
    },
    {
      name = "RL_GetFileModTime",
      description = "Get file modification time (last write time)",
      returnType = "long",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_CompressData",
      description = "Compress data (DEFLATE algorithm), memory must be RL_MemFree()",
      returnType = "unsigned char *",
      params = {
        {type = "const unsigned char *", name = "data"},
        {type = "int", name = "dataSize"},
        {type = "int *", name = "compDataSize"}
      }
    },
    {
      name = "RL_DecompressData",
      description = "Decompress data (DEFLATE algorithm), memory must be RL_MemFree()",
      returnType = "unsigned char *",
      params = {
        {type = "const unsigned char *", name = "compData"},
        {type = "int", name = "compDataSize"},
        {type = "int *", name = "dataSize"}
      }
    },
    {
      name = "RL_EncodeDataBase64",
      description = "Encode data to Base64 string, memory must be RL_MemFree()",
      returnType = "char *",
      params = {
        {type = "const unsigned char *", name = "data"},
        {type = "int", name = "dataSize"},
        {type = "int *", name = "outputSize"}
      }
    },
    {
      name = "RL_DecodeDataBase64",
      description = "Decode Base64 string data, memory must be RL_MemFree()",
      returnType = "unsigned char *",
      params = {
        {type = "const unsigned char *", name = "data"},
        {type = "int *", name = "outputSize"}
      }
    },
    {
      name = "ComputeCRC32",
      description = "Compute CRC32 hash code",
      returnType = "unsigned int",
      params = {
        {type = "unsigned char *", name = "data"},
        {type = "int", name = "dataSize"}
      }
    },
    {
      name = "ComputeMD5",
      description = "Compute MD5 hash code, returns static int[4] (16 bytes)",
      returnType = "unsigned int *",
      params = {
        {type = "unsigned char *", name = "data"},
        {type = "int", name = "dataSize"}
      }
    },
    {
      name = "ComputeSHA1",
      description = "Compute SHA1 hash code, returns static int[5] (20 bytes)",
      returnType = "unsigned int *",
      params = {
        {type = "unsigned char *", name = "data"},
        {type = "int", name = "dataSize"}
      }
    },
    {
      name = "RL_LoadAutomationEventList",
      description = "Load automation events list from file, NULL for empty list, capacity = MAX_AUTOMATION_EVENTS",
      returnType = "RL_AutomationEventList",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_UnloadAutomationEventList",
      description = "Unload automation events list from file",
      returnType = "void",
      params = {
        {type = "RL_AutomationEventList", name = "list"}
      }
    },
    {
      name = "RL_ExportAutomationEventList",
      description = "Export automation events list as text file",
      returnType = "bool",
      params = {
        {type = "RL_AutomationEventList", name = "list"},
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_SetAutomationEventList",
      description = "Set automation event list to record to",
      returnType = "void",
      params = {
        {type = "RL_AutomationEventList *", name = "list"}
      }
    },
    {
      name = "RL_SetAutomationEventBaseFrame",
      description = "Set automation event internal base frame to start recording",
      returnType = "void",
      params = {
        {type = "int", name = "frame"}
      }
    },
    {
      name = "RL_StartAutomationEventRecording",
      description = "Start recording automation events (RL_AutomationEventList must be set)",
      returnType = "void"
    },
    {
      name = "RL_StopAutomationEventRecording",
      description = "Stop recording automation events",
      returnType = "void"
    },
    {
      name = "RL_PlayAutomationEvent",
      description = "Play a recorded automation event",
      returnType = "void",
      params = {
        {type = "RL_AutomationEvent", name = "event"}
      }
    },
    {
      name = "RL_IsKeyPressed",
      description = "Check if a key has been pressed once",
      returnType = "bool",
      params = {
        {type = "int", name = "key"}
      }
    },
    {
      name = "RL_IsKeyPressedRepeat",
      description = "Check if a key has been pressed again",
      returnType = "bool",
      params = {
        {type = "int", name = "key"}
      }
    },
    {
      name = "RL_IsKeyDown",
      description = "Check if a key is being pressed",
      returnType = "bool",
      params = {
        {type = "int", name = "key"}
      }
    },
    {
      name = "RL_IsKeyReleased",
      description = "Check if a key has been released once",
      returnType = "bool",
      params = {
        {type = "int", name = "key"}
      }
    },
    {
      name = "RL_IsKeyUp",
      description = "Check if a key is NOT being pressed",
      returnType = "bool",
      params = {
        {type = "int", name = "key"}
      }
    },
    {
      name = "RL_GetKeyPressed",
      description = "Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty",
      returnType = "int"
    },
    {
      name = "RL_GetCharPressed",
      description = "Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty",
      returnType = "int"
    },
    {
      name = "RL_SetExitKey",
      description = "Set a custom key to exit program (default is ESC)",
      returnType = "void",
      params = {
        {type = "int", name = "key"}
      }
    },
    {
      name = "RL_IsGamepadAvailable",
      description = "Check if a gamepad is available",
      returnType = "bool",
      params = {
        {type = "int", name = "gamepad"}
      }
    },
    {
      name = "RL_GetGamepadName",
      description = "Get gamepad internal name id",
      returnType = "const char *",
      params = {
        {type = "int", name = "gamepad"}
      }
    },
    {
      name = "RL_IsGamepadButtonPressed",
      description = "Check if a gamepad button has been pressed once",
      returnType = "bool",
      params = {
        {type = "int", name = "gamepad"},
        {type = "int", name = "button"}
      }
    },
    {
      name = "RL_IsGamepadButtonDown",
      description = "Check if a gamepad button is being pressed",
      returnType = "bool",
      params = {
        {type = "int", name = "gamepad"},
        {type = "int", name = "button"}
      }
    },
    {
      name = "RL_IsGamepadButtonReleased",
      description = "Check if a gamepad button has been released once",
      returnType = "bool",
      params = {
        {type = "int", name = "gamepad"},
        {type = "int", name = "button"}
      }
    },
    {
      name = "RL_IsGamepadButtonUp",
      description = "Check if a gamepad button is NOT being pressed",
      returnType = "bool",
      params = {
        {type = "int", name = "gamepad"},
        {type = "int", name = "button"}
      }
    },
    {
      name = "RL_GetGamepadButtonPressed",
      description = "Get the last gamepad button pressed",
      returnType = "int"
    },
    {
      name = "RL_GetGamepadAxisCount",
      description = "Get gamepad axis count for a gamepad",
      returnType = "int",
      params = {
        {type = "int", name = "gamepad"}
      }
    },
    {
      name = "RL_GetGamepadAxisMovement",
      description = "Get axis movement value for a gamepad axis",
      returnType = "float",
      params = {
        {type = "int", name = "gamepad"},
        {type = "int", name = "axis"}
      }
    },
    {
      name = "RL_SetGamepadMappings",
      description = "Set internal gamepad mappings (SDL_GameControllerDB)",
      returnType = "int",
      params = {
        {type = "const char *", name = "mappings"}
      }
    },
    {
      name = "RL_SetGamepadVibration",
      description = "Set gamepad vibration for both motors (duration in seconds)",
      returnType = "void",
      params = {
        {type = "int", name = "gamepad"},
        {type = "float", name = "leftMotor"},
        {type = "float", name = "rightMotor"},
        {type = "float", name = "duration"}
      }
    },
    {
      name = "RL_IsMouseButtonPressed",
      description = "Check if a mouse button has been pressed once",
      returnType = "bool",
      params = {
        {type = "int", name = "button"}
      }
    },
    {
      name = "RL_IsMouseButtonDown",
      description = "Check if a mouse button is being pressed",
      returnType = "bool",
      params = {
        {type = "int", name = "button"}
      }
    },
    {
      name = "RL_IsMouseButtonReleased",
      description = "Check if a mouse button has been released once",
      returnType = "bool",
      params = {
        {type = "int", name = "button"}
      }
    },
    {
      name = "RL_IsMouseButtonUp",
      description = "Check if a mouse button is NOT being pressed",
      returnType = "bool",
      params = {
        {type = "int", name = "button"}
      }
    },
    {
      name = "RL_GetMouseX",
      description = "Get mouse position X",
      returnType = "int"
    },
    {
      name = "RL_GetMouseY",
      description = "Get mouse position Y",
      returnType = "int"
    },
    {
      name = "RL_GetMousePosition",
      description = "Get mouse position XY",
      returnType = "RL_Vector2"
    },
    {
      name = "RL_GetMouseDelta",
      description = "Get mouse delta between frames",
      returnType = "RL_Vector2"
    },
    {
      name = "RL_SetMousePosition",
      description = "Set mouse position XY",
      returnType = "void",
      params = {
        {type = "int", name = "x"},
        {type = "int", name = "y"}
      }
    },
    {
      name = "RL_SetMouseOffset",
      description = "Set mouse offset",
      returnType = "void",
      params = {
        {type = "int", name = "offsetX"},
        {type = "int", name = "offsetY"}
      }
    },
    {
      name = "RL_SetMouseScale",
      description = "Set mouse scaling",
      returnType = "void",
      params = {
        {type = "float", name = "scaleX"},
        {type = "float", name = "scaleY"}
      }
    },
    {
      name = "RL_GetMouseWheelMove",
      description = "Get mouse wheel movement for X or Y, whichever is larger",
      returnType = "float"
    },
    {
      name = "RL_GetMouseWheelMoveV",
      description = "Get mouse wheel movement for both X and Y",
      returnType = "RL_Vector2"
    },
    {
      name = "RL_SetMouseCursor",
      description = "Set mouse cursor",
      returnType = "void",
      params = {
        {type = "int", name = "cursor"}
      }
    },
    {
      name = "RL_GetTouchX",
      description = "Get touch position X for touch point 0 (relative to screen size)",
      returnType = "int"
    },
    {
      name = "RL_GetTouchY",
      description = "Get touch position Y for touch point 0 (relative to screen size)",
      returnType = "int"
    },
    {
      name = "RL_GetTouchPosition",
      description = "Get touch position XY for a touch point index (relative to screen size)",
      returnType = "RL_Vector2",
      params = {
        {type = "int", name = "index"}
      }
    },
    {
      name = "RL_GetTouchPointId",
      description = "Get touch point identifier for given index",
      returnType = "int",
      params = {
        {type = "int", name = "index"}
      }
    },
    {
      name = "RL_GetTouchPointCount",
      description = "Get number of touch points",
      returnType = "int"
    },
    {
      name = "RL_SetGesturesEnabled",
      description = "Enable a set of gestures using flags",
      returnType = "void",
      params = {
        {type = "unsigned int", name = "flags"}
      }
    },
    {
      name = "RL_IsGestureDetected",
      description = "Check if a gesture have been detected",
      returnType = "bool",
      params = {
        {type = "unsigned int", name = "gesture"}
      }
    },
    {
      name = "RL_GetGestureDetected",
      description = "Get latest detected gesture",
      returnType = "int"
    },
    {
      name = "RL_GetGestureHoldDuration",
      description = "Get gesture hold time in seconds",
      returnType = "float"
    },
    {
      name = "RL_GetGestureDragVector",
      description = "Get gesture drag vector",
      returnType = "RL_Vector2"
    },
    {
      name = "RL_GetGestureDragAngle",
      description = "Get gesture drag angle",
      returnType = "float"
    },
    {
      name = "RL_GetGesturePinchVector",
      description = "Get gesture pinch delta",
      returnType = "RL_Vector2"
    },
    {
      name = "RL_GetGesturePinchAngle",
      description = "Get gesture pinch angle",
      returnType = "float"
    },
    {
      name = "RL_UpdateCamera",
      description = "Update camera position for selected mode",
      returnType = "void",
      params = {
        {type = "RL_Camera *", name = "camera"},
        {type = "int", name = "mode"}
      }
    },
    {
      name = "RL_UpdateCameraPro",
      description = "Update camera movement/rotation",
      returnType = "void",
      params = {
        {type = "RL_Camera *", name = "camera"},
        {type = "RL_Vector3", name = "movement"},
        {type = "RL_Vector3", name = "rotation"},
        {type = "float", name = "zoom"}
      }
    },
    {
      name = "RL_SetShapesTexture",
      description = "Set texture and rectangle to be used on shapes drawing",
      returnType = "void",
      params = {
        {type = "RL_Texture2D", name = "texture"},
        {type = "RL_Rectangle", name = "source"}
      }
    },
    {
      name = "RL_GetShapesTexture",
      description = "Get texture that is used for shapes drawing",
      returnType = "RL_Texture2D"
    },
    {
      name = "RL_GetShapesTextureRectangle",
      description = "Get texture source rectangle that is used for shapes drawing",
      returnType = "RL_Rectangle"
    },
    {
      name = "RL_DrawPixel",
      description = "Draw a pixel using geometry [Can be slow, use with care]",
      returnType = "void",
      params = {
        {type = "int", name = "posX"},
        {type = "int", name = "posY"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawPixelV",
      description = "Draw a pixel using geometry (Vector version) [Can be slow, use with care]",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "position"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawLine",
      description = "Draw a line",
      returnType = "void",
      params = {
        {type = "int", name = "startPosX"},
        {type = "int", name = "startPosY"},
        {type = "int", name = "endPosX"},
        {type = "int", name = "endPosY"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawLineV",
      description = "Draw a line (using gl lines)",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "startPos"},
        {type = "RL_Vector2", name = "endPos"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawLineEx",
      description = "Draw a line (using triangles/quads)",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "startPos"},
        {type = "RL_Vector2", name = "endPos"},
        {type = "float", name = "thick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawLineStrip",
      description = "Draw lines sequence (using gl lines)",
      returnType = "void",
      params = {
        {type = "const RL_Vector2 *", name = "points"},
        {type = "int", name = "pointCount"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawLineBezier",
      description = "Draw line segment cubic-bezier in-out interpolation",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "startPos"},
        {type = "RL_Vector2", name = "endPos"},
        {type = "float", name = "thick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCircle",
      description = "Draw a color-filled circle",
      returnType = "void",
      params = {
        {type = "int", name = "centerX"},
        {type = "int", name = "centerY"},
        {type = "float", name = "radius"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCircleSector",
      description = "Draw a piece of a circle",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "center"},
        {type = "float", name = "radius"},
        {type = "float", name = "startAngle"},
        {type = "float", name = "endAngle"},
        {type = "int", name = "segments"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCircleSectorLines",
      description = "Draw circle sector outline",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "center"},
        {type = "float", name = "radius"},
        {type = "float", name = "startAngle"},
        {type = "float", name = "endAngle"},
        {type = "int", name = "segments"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCircleGradient",
      description = "Draw a gradient-filled circle",
      returnType = "void",
      params = {
        {type = "int", name = "centerX"},
        {type = "int", name = "centerY"},
        {type = "float", name = "radius"},
        {type = "RL_Color", name = "inner"},
        {type = "RL_Color", name = "outer"}
      }
    },
    {
      name = "RL_DrawCircleV",
      description = "Draw a color-filled circle (Vector version)",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "center"},
        {type = "float", name = "radius"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCircleLines",
      description = "Draw circle outline",
      returnType = "void",
      params = {
        {type = "int", name = "centerX"},
        {type = "int", name = "centerY"},
        {type = "float", name = "radius"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCircleLinesV",
      description = "Draw circle outline (Vector version)",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "center"},
        {type = "float", name = "radius"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawEllipse",
      description = "Draw ellipse",
      returnType = "void",
      params = {
        {type = "int", name = "centerX"},
        {type = "int", name = "centerY"},
        {type = "float", name = "radiusH"},
        {type = "float", name = "radiusV"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawEllipseLines",
      description = "Draw ellipse outline",
      returnType = "void",
      params = {
        {type = "int", name = "centerX"},
        {type = "int", name = "centerY"},
        {type = "float", name = "radiusH"},
        {type = "float", name = "radiusV"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawRing",
      description = "Draw ring",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "center"},
        {type = "float", name = "innerRadius"},
        {type = "float", name = "outerRadius"},
        {type = "float", name = "startAngle"},
        {type = "float", name = "endAngle"},
        {type = "int", name = "segments"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawRingLines",
      description = "Draw ring outline",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "center"},
        {type = "float", name = "innerRadius"},
        {type = "float", name = "outerRadius"},
        {type = "float", name = "startAngle"},
        {type = "float", name = "endAngle"},
        {type = "int", name = "segments"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawRectangle",
      description = "Draw a color-filled rectangle",
      returnType = "void",
      params = {
        {type = "int", name = "posX"},
        {type = "int", name = "posY"},
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawRectangleV",
      description = "Draw a color-filled rectangle (Vector version)",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "position"},
        {type = "RL_Vector2", name = "size"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawRectangleRec",
      description = "Draw a color-filled rectangle",
      returnType = "void",
      params = {
        {type = "RL_Rectangle", name = "rec"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawRectanglePro",
      description = "Draw a color-filled rectangle with pro parameters",
      returnType = "void",
      params = {
        {type = "RL_Rectangle", name = "rec"},
        {type = "RL_Vector2", name = "origin"},
        {type = "float", name = "rotation"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawRectangleGradientV",
      description = "Draw a vertical-gradient-filled rectangle",
      returnType = "void",
      params = {
        {type = "int", name = "posX"},
        {type = "int", name = "posY"},
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "RL_Color", name = "top"},
        {type = "RL_Color", name = "bottom"}
      }
    },
    {
      name = "RL_DrawRectangleGradientH",
      description = "Draw a horizontal-gradient-filled rectangle",
      returnType = "void",
      params = {
        {type = "int", name = "posX"},
        {type = "int", name = "posY"},
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "RL_Color", name = "left"},
        {type = "RL_Color", name = "right"}
      }
    },
    {
      name = "RL_DrawRectangleGradientEx",
      description = "Draw a gradient-filled rectangle with custom vertex colors",
      returnType = "void",
      params = {
        {type = "RL_Rectangle", name = "rec"},
        {type = "RL_Color", name = "topLeft"},
        {type = "RL_Color", name = "bottomLeft"},
        {type = "RL_Color", name = "topRight"},
        {type = "RL_Color", name = "bottomRight"}
      }
    },
    {
      name = "RL_DrawRectangleLines",
      description = "Draw rectangle outline",
      returnType = "void",
      params = {
        {type = "int", name = "posX"},
        {type = "int", name = "posY"},
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawRectangleLinesEx",
      description = "Draw rectangle outline with extended parameters",
      returnType = "void",
      params = {
        {type = "RL_Rectangle", name = "rec"},
        {type = "float", name = "lineThick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawRectangleRounded",
      description = "Draw rectangle with rounded edges",
      returnType = "void",
      params = {
        {type = "RL_Rectangle", name = "rec"},
        {type = "float", name = "roundness"},
        {type = "int", name = "segments"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawRectangleRoundedLines",
      description = "Draw rectangle lines with rounded edges",
      returnType = "void",
      params = {
        {type = "RL_Rectangle", name = "rec"},
        {type = "float", name = "roundness"},
        {type = "int", name = "segments"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawRectangleRoundedLinesEx",
      description = "Draw rectangle with rounded edges outline",
      returnType = "void",
      params = {
        {type = "RL_Rectangle", name = "rec"},
        {type = "float", name = "roundness"},
        {type = "int", name = "segments"},
        {type = "float", name = "lineThick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawTriangle",
      description = "Draw a color-filled triangle (vertex in counter-clockwise order!)",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "v1"},
        {type = "RL_Vector2", name = "v2"},
        {type = "RL_Vector2", name = "v3"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawTriangleLines",
      description = "Draw triangle outline (vertex in counter-clockwise order!)",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "v1"},
        {type = "RL_Vector2", name = "v2"},
        {type = "RL_Vector2", name = "v3"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawTriangleFan",
      description = "Draw a triangle fan defined by points (first vertex is the center)",
      returnType = "void",
      params = {
        {type = "const RL_Vector2 *", name = "points"},
        {type = "int", name = "pointCount"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawTriangleStrip",
      description = "Draw a triangle strip defined by points",
      returnType = "void",
      params = {
        {type = "const RL_Vector2 *", name = "points"},
        {type = "int", name = "pointCount"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawPoly",
      description = "Draw a regular polygon (Vector version)",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "center"},
        {type = "int", name = "sides"},
        {type = "float", name = "radius"},
        {type = "float", name = "rotation"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawPolyLines",
      description = "Draw a polygon outline of n sides",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "center"},
        {type = "int", name = "sides"},
        {type = "float", name = "radius"},
        {type = "float", name = "rotation"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawPolyLinesEx",
      description = "Draw a polygon outline of n sides with extended parameters",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "center"},
        {type = "int", name = "sides"},
        {type = "float", name = "radius"},
        {type = "float", name = "rotation"},
        {type = "float", name = "lineThick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawSplineLinear",
      description = "Draw spline: Linear, minimum 2 points",
      returnType = "void",
      params = {
        {type = "const RL_Vector2 *", name = "points"},
        {type = "int", name = "pointCount"},
        {type = "float", name = "thick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawSplineBasis",
      description = "Draw spline: B-Spline, minimum 4 points",
      returnType = "void",
      params = {
        {type = "const RL_Vector2 *", name = "points"},
        {type = "int", name = "pointCount"},
        {type = "float", name = "thick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawSplineCatmullRom",
      description = "Draw spline: Catmull-Rom, minimum 4 points",
      returnType = "void",
      params = {
        {type = "const RL_Vector2 *", name = "points"},
        {type = "int", name = "pointCount"},
        {type = "float", name = "thick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawSplineBezierQuadratic",
      description = "Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]",
      returnType = "void",
      params = {
        {type = "const RL_Vector2 *", name = "points"},
        {type = "int", name = "pointCount"},
        {type = "float", name = "thick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawSplineBezierCubic",
      description = "Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]",
      returnType = "void",
      params = {
        {type = "const RL_Vector2 *", name = "points"},
        {type = "int", name = "pointCount"},
        {type = "float", name = "thick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawSplineSegmentLinear",
      description = "Draw spline segment: Linear, 2 points",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "p1"},
        {type = "RL_Vector2", name = "p2"},
        {type = "float", name = "thick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawSplineSegmentBasis",
      description = "Draw spline segment: B-Spline, 4 points",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "p1"},
        {type = "RL_Vector2", name = "p2"},
        {type = "RL_Vector2", name = "p3"},
        {type = "RL_Vector2", name = "p4"},
        {type = "float", name = "thick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawSplineSegmentCatmullRom",
      description = "Draw spline segment: Catmull-Rom, 4 points",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "p1"},
        {type = "RL_Vector2", name = "p2"},
        {type = "RL_Vector2", name = "p3"},
        {type = "RL_Vector2", name = "p4"},
        {type = "float", name = "thick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawSplineSegmentBezierQuadratic",
      description = "Draw spline segment: Quadratic Bezier, 2 points, 1 control point",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "p1"},
        {type = "RL_Vector2", name = "c2"},
        {type = "RL_Vector2", name = "p3"},
        {type = "float", name = "thick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawSplineSegmentBezierCubic",
      description = "Draw spline segment: Cubic Bezier, 2 points, 2 control points",
      returnType = "void",
      params = {
        {type = "RL_Vector2", name = "p1"},
        {type = "RL_Vector2", name = "c2"},
        {type = "RL_Vector2", name = "c3"},
        {type = "RL_Vector2", name = "p4"},
        {type = "float", name = "thick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_GetSplinePointLinear",
      description = "Get (evaluate) spline point: Linear",
      returnType = "RL_Vector2",
      params = {
        {type = "RL_Vector2", name = "startPos"},
        {type = "RL_Vector2", name = "endPos"},
        {type = "float", name = "t"}
      }
    },
    {
      name = "RL_GetSplinePointBasis",
      description = "Get (evaluate) spline point: B-Spline",
      returnType = "RL_Vector2",
      params = {
        {type = "RL_Vector2", name = "p1"},
        {type = "RL_Vector2", name = "p2"},
        {type = "RL_Vector2", name = "p3"},
        {type = "RL_Vector2", name = "p4"},
        {type = "float", name = "t"}
      }
    },
    {
      name = "RL_GetSplinePointCatmullRom",
      description = "Get (evaluate) spline point: Catmull-Rom",
      returnType = "RL_Vector2",
      params = {
        {type = "RL_Vector2", name = "p1"},
        {type = "RL_Vector2", name = "p2"},
        {type = "RL_Vector2", name = "p3"},
        {type = "RL_Vector2", name = "p4"},
        {type = "float", name = "t"}
      }
    },
    {
      name = "RL_GetSplinePointBezierQuad",
      description = "Get (evaluate) spline point: Quadratic Bezier",
      returnType = "RL_Vector2",
      params = {
        {type = "RL_Vector2", name = "p1"},
        {type = "RL_Vector2", name = "c2"},
        {type = "RL_Vector2", name = "p3"},
        {type = "float", name = "t"}
      }
    },
    {
      name = "RL_GetSplinePointBezierCubic",
      description = "Get (evaluate) spline point: Cubic Bezier",
      returnType = "RL_Vector2",
      params = {
        {type = "RL_Vector2", name = "p1"},
        {type = "RL_Vector2", name = "c2"},
        {type = "RL_Vector2", name = "c3"},
        {type = "RL_Vector2", name = "p4"},
        {type = "float", name = "t"}
      }
    },
    {
      name = "RL_CheckCollisionRecs",
      description = "Check collision between two rectangles",
      returnType = "bool",
      params = {
        {type = "RL_Rectangle", name = "rec1"},
        {type = "RL_Rectangle", name = "rec2"}
      }
    },
    {
      name = "RL_CheckCollisionCircles",
      description = "Check collision between two circles",
      returnType = "bool",
      params = {
        {type = "RL_Vector2", name = "center1"},
        {type = "float", name = "radius1"},
        {type = "RL_Vector2", name = "center2"},
        {type = "float", name = "radius2"}
      }
    },
    {
      name = "RL_CheckCollisionCircleRec",
      description = "Check collision between circle and rectangle",
      returnType = "bool",
      params = {
        {type = "RL_Vector2", name = "center"},
        {type = "float", name = "radius"},
        {type = "RL_Rectangle", name = "rec"}
      }
    },
    {
      name = "RL_CheckCollisionCircleLine",
      description = "Check if circle collides with a line created betweeen two points [p1] and [p2]",
      returnType = "bool",
      params = {
        {type = "RL_Vector2", name = "center"},
        {type = "float", name = "radius"},
        {type = "RL_Vector2", name = "p1"},
        {type = "RL_Vector2", name = "p2"}
      }
    },
    {
      name = "RL_CheckCollisionPointRec",
      description = "Check if point is inside rectangle",
      returnType = "bool",
      params = {
        {type = "RL_Vector2", name = "point"},
        {type = "RL_Rectangle", name = "rec"}
      }
    },
    {
      name = "RL_CheckCollisionPointCircle",
      description = "Check if point is inside circle",
      returnType = "bool",
      params = {
        {type = "RL_Vector2", name = "point"},
        {type = "RL_Vector2", name = "center"},
        {type = "float", name = "radius"}
      }
    },
    {
      name = "RL_CheckCollisionPointTriangle",
      description = "Check if point is inside a triangle",
      returnType = "bool",
      params = {
        {type = "RL_Vector2", name = "point"},
        {type = "RL_Vector2", name = "p1"},
        {type = "RL_Vector2", name = "p2"},
        {type = "RL_Vector2", name = "p3"}
      }
    },
    {
      name = "RL_CheckCollisionPointLine",
      description = "Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]",
      returnType = "bool",
      params = {
        {type = "RL_Vector2", name = "point"},
        {type = "RL_Vector2", name = "p1"},
        {type = "RL_Vector2", name = "p2"},
        {type = "int", name = "threshold"}
      }
    },
    {
      name = "RL_CheckCollisionPointPoly",
      description = "Check if point is within a polygon described by array of vertices",
      returnType = "bool",
      params = {
        {type = "RL_Vector2", name = "point"},
        {type = "const RL_Vector2 *", name = "points"},
        {type = "int", name = "pointCount"}
      }
    },
    {
      name = "RL_CheckCollisionLines",
      description = "Check the collision between two lines defined by two points each, returns collision point by reference",
      returnType = "bool",
      params = {
        {type = "RL_Vector2", name = "startPos1"},
        {type = "RL_Vector2", name = "endPos1"},
        {type = "RL_Vector2", name = "startPos2"},
        {type = "RL_Vector2", name = "endPos2"},
        {type = "RL_Vector2 *", name = "collisionPoint"}
      }
    },
    {
      name = "RL_GetCollisionRec",
      description = "Get collision rectangle for two rectangles collision",
      returnType = "RL_Rectangle",
      params = {
        {type = "RL_Rectangle", name = "rec1"},
        {type = "RL_Rectangle", name = "rec2"}
      }
    },
    {
      name = "RL_LoadImage",
      description = "Load image from file into CPU memory (RAM)",
      returnType = "RL_Image",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_LoadImageRaw",
      description = "Load image from RAW file data",
      returnType = "RL_Image",
      params = {
        {type = "const char *", name = "fileName"},
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "int", name = "format"},
        {type = "int", name = "headerSize"}
      }
    },
    {
      name = "RL_LoadImageAnim",
      description = "Load image sequence from file (frames appended to image.data)",
      returnType = "RL_Image",
      params = {
        {type = "const char *", name = "fileName"},
        {type = "int *", name = "frames"}
      }
    },
    {
      name = "RL_LoadImageAnimFromMemory",
      description = "Load image sequence from memory buffer",
      returnType = "RL_Image",
      params = {
        {type = "const char *", name = "fileType"},
        {type = "const unsigned char *", name = "fileData"},
        {type = "int", name = "dataSize"},
        {type = "int *", name = "frames"}
      }
    },
    {
      name = "RL_LoadImageFromMemory",
      description = "Load image from memory buffer, fileType refers to extension: i.e. '.png'",
      returnType = "RL_Image",
      params = {
        {type = "const char *", name = "fileType"},
        {type = "const unsigned char *", name = "fileData"},
        {type = "int", name = "dataSize"}
      }
    },
    {
      name = "RL_LoadImageFromTexture",
      description = "Load image from GPU texture data",
      returnType = "RL_Image",
      params = {
        {type = "RL_Texture2D", name = "texture"}
      }
    },
    {
      name = "RL_LoadImageFromScreen",
      description = "Load image from screen buffer and (screenshot)",
      returnType = "RL_Image"
    },
    {
      name = "IsImageValid",
      description = "Check if an image is valid (data and parameters)",
      returnType = "bool",
      params = {
        {type = "RL_Image", name = "image"}
      }
    },
    {
      name = "RL_UnloadImage",
      description = "Unload image from CPU memory (RAM)",
      returnType = "void",
      params = {
        {type = "RL_Image", name = "image"}
      }
    },
    {
      name = "RL_ExportImage",
      description = "Export image data to file, returns true on success",
      returnType = "bool",
      params = {
        {type = "RL_Image", name = "image"},
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_ExportImageToMemory",
      description = "Export image to memory buffer",
      returnType = "unsigned char *",
      params = {
        {type = "RL_Image", name = "image"},
        {type = "const char *", name = "fileType"},
        {type = "int *", name = "fileSize"}
      }
    },
    {
      name = "RL_ExportImageAsCode",
      description = "Export image as code file defining an array of bytes, returns true on success",
      returnType = "bool",
      params = {
        {type = "RL_Image", name = "image"},
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_GenImageColor",
      description = "Generate image: plain color",
      returnType = "RL_Image",
      params = {
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_GenImageGradientLinear",
      description = "Generate image: linear gradient, direction in degrees [0..360], 0=Vertical gradient",
      returnType = "RL_Image",
      params = {
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "int", name = "direction"},
        {type = "RL_Color", name = "start"},
        {type = "RL_Color", name = "end"}
      }
    },
    {
      name = "RL_GenImageGradientRadial",
      description = "Generate image: radial gradient",
      returnType = "RL_Image",
      params = {
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "float", name = "density"},
        {type = "RL_Color", name = "inner"},
        {type = "RL_Color", name = "outer"}
      }
    },
    {
      name = "RL_GenImageGradientSquare",
      description = "Generate image: square gradient",
      returnType = "RL_Image",
      params = {
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "float", name = "density"},
        {type = "RL_Color", name = "inner"},
        {type = "RL_Color", name = "outer"}
      }
    },
    {
      name = "RL_GenImageChecked",
      description = "Generate image: checked",
      returnType = "RL_Image",
      params = {
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "int", name = "checksX"},
        {type = "int", name = "checksY"},
        {type = "RL_Color", name = "col1"},
        {type = "RL_Color", name = "col2"}
      }
    },
    {
      name = "RL_GenImageWhiteNoise",
      description = "Generate image: white noise",
      returnType = "RL_Image",
      params = {
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "float", name = "factor"}
      }
    },
    {
      name = "RL_GenImagePerlinNoise",
      description = "Generate image: perlin noise",
      returnType = "RL_Image",
      params = {
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "int", name = "offsetX"},
        {type = "int", name = "offsetY"},
        {type = "float", name = "scale"}
      }
    },
    {
      name = "RL_GenImageCellular",
      description = "Generate image: cellular algorithm, bigger tileSize means bigger cells",
      returnType = "RL_Image",
      params = {
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "int", name = "tileSize"}
      }
    },
    {
      name = "RL_GenImageText",
      description = "Generate image: grayscale image from text data",
      returnType = "RL_Image",
      params = {
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "const char *", name = "text"}
      }
    },
    {
      name = "RL_ImageCopy",
      description = "Create an image duplicate (useful for transformations)",
      returnType = "RL_Image",
      params = {
        {type = "RL_Image", name = "image"}
      }
    },
    {
      name = "RL_ImageFromImage",
      description = "Create an image from another image piece",
      returnType = "RL_Image",
      params = {
        {type = "RL_Image", name = "image"},
        {type = "RL_Rectangle", name = "rec"}
      }
    },
    {
      name = "RL_ImageFromChannel",
      description = "Create an image from a selected channel of another image (GRAYSCALE)",
      returnType = "RL_Image",
      params = {
        {type = "RL_Image", name = "image"},
        {type = "int", name = "selectedChannel"}
      }
    },
    {
      name = "RL_ImageText",
      description = "Create an image from text (default font)",
      returnType = "RL_Image",
      params = {
        {type = "const char *", name = "text"},
        {type = "int", name = "fontSize"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageTextEx",
      description = "Create an image from text (custom sprite font)",
      returnType = "RL_Image",
      params = {
        {type = "RL_Font", name = "font"},
        {type = "const char *", name = "text"},
        {type = "float", name = "fontSize"},
        {type = "float", name = "spacing"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_ImageFormat",
      description = "Convert image data to desired format",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "int", name = "newFormat"}
      }
    },
    {
      name = "RL_ImageToPOT",
      description = "Convert image to POT (power-of-two)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "RL_Color", name = "fill"}
      }
    },
    {
      name = "RL_ImageCrop",
      description = "Crop an image to a defined rectangle",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "RL_Rectangle", name = "crop"}
      }
    },
    {
      name = "RL_ImageAlphaCrop",
      description = "Crop image depending on alpha value",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "float", name = "threshold"}
      }
    },
    {
      name = "RL_ImageAlphaClear",
      description = "Clear alpha channel to desired color",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "RL_Color", name = "color"},
        {type = "float", name = "threshold"}
      }
    },
    {
      name = "RL_ImageAlphaMask",
      description = "Apply alpha mask to image",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "RL_Image", name = "alphaMask"}
      }
    },
    {
      name = "RL_ImageAlphaPremultiply",
      description = "Premultiply alpha channel",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"}
      }
    },
    {
      name = "RL_ImageBlurGaussian",
      description = "Apply Gaussian blur using a box blur approximation",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "int", name = "blurSize"}
      }
    },
    {
      name = "RL_ImageKernelConvolution",
      description = "Apply custom square convolution kernel to image",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "const float *", name = "kernel"},
        {type = "int", name = "kernelSize"}
      }
    },
    {
      name = "RL_ImageResize",
      description = "Resize image (Bicubic scaling algorithm)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "int", name = "newWidth"},
        {type = "int", name = "newHeight"}
      }
    },
    {
      name = "RL_ImageResizeNN",
      description = "Resize image (Nearest-Neighbor scaling algorithm)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "int", name = "newWidth"},
        {type = "int", name = "newHeight"}
      }
    },
    {
      name = "RL_ImageResizeCanvas",
      description = "Resize canvas and fill with color",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "int", name = "newWidth"},
        {type = "int", name = "newHeight"},
        {type = "int", name = "offsetX"},
        {type = "int", name = "offsetY"},
        {type = "RL_Color", name = "fill"}
      }
    },
    {
      name = "RL_ImageMipmaps",
      description = "Compute all mipmap levels for a provided image",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"}
      }
    },
    {
      name = "RL_ImageDither",
      description = "Dither image data to 16bpp or lower (Floyd-Steinberg dithering)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "int", name = "rBpp"},
        {type = "int", name = "gBpp"},
        {type = "int", name = "bBpp"},
        {type = "int", name = "aBpp"}
      }
    },
    {
      name = "RL_ImageFlipVertical",
      description = "Flip image vertically",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"}
      }
    },
    {
      name = "RL_ImageFlipHorizontal",
      description = "Flip image horizontally",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"}
      }
    },
    {
      name = "RL_ImageRotate",
      description = "Rotate image by input angle in degrees (-359 to 359)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "int", name = "degrees"}
      }
    },
    {
      name = "RL_ImageRotateCW",
      description = "Rotate image clockwise 90deg",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"}
      }
    },
    {
      name = "RL_ImageRotateCCW",
      description = "Rotate image counter-clockwise 90deg",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"}
      }
    },
    {
      name = "RL_ImageColorTint",
      description = "Modify image color: tint",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageColorInvert",
      description = "Modify image color: invert",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"}
      }
    },
    {
      name = "RL_ImageColorGrayscale",
      description = "Modify image color: grayscale",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"}
      }
    },
    {
      name = "RL_ImageColorContrast",
      description = "Modify image color: contrast (-100 to 100)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "float", name = "contrast"}
      }
    },
    {
      name = "RL_ImageColorBrightness",
      description = "Modify image color: brightness (-255 to 255)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "int", name = "brightness"}
      }
    },
    {
      name = "RL_ImageColorReplace",
      description = "Modify image color: replace color",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "image"},
        {type = "RL_Color", name = "color"},
        {type = "RL_Color", name = "replace"}
      }
    },
    {
      name = "RL_LoadImageColors",
      description = "Load color data from image as a RL_Color array (RGBA - 32bit)",
      returnType = "RL_Color *",
      params = {
        {type = "RL_Image", name = "image"}
      }
    },
    {
      name = "RL_LoadImagePalette",
      description = "Load colors palette from image as a RL_Color array (RGBA - 32bit)",
      returnType = "RL_Color *",
      params = {
        {type = "RL_Image", name = "image"},
        {type = "int", name = "maxPaletteSize"},
        {type = "int *", name = "colorCount"}
      }
    },
    {
      name = "RL_UnloadImageColors",
      description = "Unload color data loaded with RL_LoadImageColors()",
      returnType = "void",
      params = {
        {type = "RL_Color *", name = "colors"}
      }
    },
    {
      name = "RL_UnloadImagePalette",
      description = "Unload colors palette loaded with RL_LoadImagePalette()",
      returnType = "void",
      params = {
        {type = "RL_Color *", name = "colors"}
      }
    },
    {
      name = "RL_GetImageAlphaBorder",
      description = "Get image alpha border rectangle",
      returnType = "RL_Rectangle",
      params = {
        {type = "RL_Image", name = "image"},
        {type = "float", name = "threshold"}
      }
    },
    {
      name = "RL_GetImageColor",
      description = "Get image pixel color at (x, y) position",
      returnType = "RL_Color",
      params = {
        {type = "RL_Image", name = "image"},
        {type = "int", name = "x"},
        {type = "int", name = "y"}
      }
    },
    {
      name = "RL_ImageClearBackground",
      description = "Clear image background with given color",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawPixel",
      description = "Draw pixel within an image",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "int", name = "posX"},
        {type = "int", name = "posY"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawPixelV",
      description = "Draw pixel within an image (Vector version)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Vector2", name = "position"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawLine",
      description = "Draw line within an image",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "int", name = "startPosX"},
        {type = "int", name = "startPosY"},
        {type = "int", name = "endPosX"},
        {type = "int", name = "endPosY"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawLineV",
      description = "Draw line within an image (Vector version)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Vector2", name = "start"},
        {type = "RL_Vector2", name = "end"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawLineEx",
      description = "Draw a line defining thickness within an image",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Vector2", name = "start"},
        {type = "RL_Vector2", name = "end"},
        {type = "int", name = "thick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawCircle",
      description = "Draw a filled circle within an image",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "int", name = "centerX"},
        {type = "int", name = "centerY"},
        {type = "int", name = "radius"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawCircleV",
      description = "Draw a filled circle within an image (Vector version)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Vector2", name = "center"},
        {type = "int", name = "radius"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawCircleLines",
      description = "Draw circle outline within an image",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "int", name = "centerX"},
        {type = "int", name = "centerY"},
        {type = "int", name = "radius"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawCircleLinesV",
      description = "Draw circle outline within an image (Vector version)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Vector2", name = "center"},
        {type = "int", name = "radius"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawRectangle",
      description = "Draw rectangle within an image",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "int", name = "posX"},
        {type = "int", name = "posY"},
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawRectangleV",
      description = "Draw rectangle within an image (Vector version)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Vector2", name = "position"},
        {type = "RL_Vector2", name = "size"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawRectangleRec",
      description = "Draw rectangle within an image",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Rectangle", name = "rec"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawRectangleLines",
      description = "Draw rectangle lines within an image",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Rectangle", name = "rec"},
        {type = "int", name = "thick"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawTriangle",
      description = "Draw triangle within an image",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Vector2", name = "v1"},
        {type = "RL_Vector2", name = "v2"},
        {type = "RL_Vector2", name = "v3"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawTriangleEx",
      description = "Draw triangle with interpolated colors within an image",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Vector2", name = "v1"},
        {type = "RL_Vector2", name = "v2"},
        {type = "RL_Vector2", name = "v3"},
        {type = "RL_Color", name = "c1"},
        {type = "RL_Color", name = "c2"},
        {type = "RL_Color", name = "c3"}
      }
    },
    {
      name = "RL_ImageDrawTriangleLines",
      description = "Draw triangle outline within an image",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Vector2", name = "v1"},
        {type = "RL_Vector2", name = "v2"},
        {type = "RL_Vector2", name = "v3"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawTriangleFan",
      description = "Draw a triangle fan defined by points within an image (first vertex is the center)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Vector2 *", name = "points"},
        {type = "int", name = "pointCount"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawTriangleStrip",
      description = "Draw a triangle strip defined by points within an image",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Vector2 *", name = "points"},
        {type = "int", name = "pointCount"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDraw",
      description = "Draw a source image within a destination image (tint applied to source)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Image", name = "src"},
        {type = "RL_Rectangle", name = "srcRec"},
        {type = "RL_Rectangle", name = "dstRec"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_ImageDrawText",
      description = "Draw text (using default font) within an image (destination)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "const char *", name = "text"},
        {type = "int", name = "posX"},
        {type = "int", name = "posY"},
        {type = "int", name = "fontSize"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ImageDrawTextEx",
      description = "Draw text (custom sprite font) within an image (destination)",
      returnType = "void",
      params = {
        {type = "RL_Image *", name = "dst"},
        {type = "RL_Font", name = "font"},
        {type = "const char *", name = "text"},
        {type = "RL_Vector2", name = "position"},
        {type = "float", name = "fontSize"},
        {type = "float", name = "spacing"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_LoadTexture",
      description = "Load texture from file into GPU memory (VRAM)",
      returnType = "RL_Texture2D",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_LoadTextureFromImage",
      description = "Load texture from image data",
      returnType = "RL_Texture2D",
      params = {
        {type = "RL_Image", name = "image"}
      }
    },
    {
      name = "RL_LoadTextureCubemap",
      description = "Load cubemap from image, multiple image cubemap layouts supported",
      returnType = "RL_TextureCubemap",
      params = {
        {type = "RL_Image", name = "image"},
        {type = "int", name = "layout"}
      }
    },
    {
      name = "RL_LoadRenderTexture",
      description = "Load texture for rendering (framebuffer)",
      returnType = "RL_RenderTexture2D",
      params = {
        {type = "int", name = "width"},
        {type = "int", name = "height"}
      }
    },
    {
      name = "IsTextureValid",
      description = "Check if a texture is valid (loaded in GPU)",
      returnType = "bool",
      params = {
        {type = "RL_Texture2D", name = "texture"}
      }
    },
    {
      name = "RL_UnloadTexture",
      description = "Unload texture from GPU memory (VRAM)",
      returnType = "void",
      params = {
        {type = "RL_Texture2D", name = "texture"}
      }
    },
    {
      name = "IsRenderTextureValid",
      description = "Check if a render texture is valid (loaded in GPU)",
      returnType = "bool",
      params = {
        {type = "RL_RenderTexture2D", name = "target"}
      }
    },
    {
      name = "RL_UnloadRenderTexture",
      description = "Unload render texture from GPU memory (VRAM)",
      returnType = "void",
      params = {
        {type = "RL_RenderTexture2D", name = "target"}
      }
    },
    {
      name = "RL_UpdateTexture",
      description = "Update GPU texture with new data",
      returnType = "void",
      params = {
        {type = "RL_Texture2D", name = "texture"},
        {type = "const void *", name = "pixels"}
      }
    },
    {
      name = "RL_UpdateTextureRec",
      description = "Update GPU texture rectangle with new data",
      returnType = "void",
      params = {
        {type = "RL_Texture2D", name = "texture"},
        {type = "RL_Rectangle", name = "rec"},
        {type = "const void *", name = "pixels"}
      }
    },
    {
      name = "RL_GenTextureMipmaps",
      description = "Generate GPU mipmaps for a texture",
      returnType = "void",
      params = {
        {type = "RL_Texture2D *", name = "texture"}
      }
    },
    {
      name = "RL_SetTextureFilter",
      description = "Set texture scaling filter mode",
      returnType = "void",
      params = {
        {type = "RL_Texture2D", name = "texture"},
        {type = "int", name = "filter"}
      }
    },
    {
      name = "RL_SetTextureWrap",
      description = "Set texture wrapping mode",
      returnType = "void",
      params = {
        {type = "RL_Texture2D", name = "texture"},
        {type = "int", name = "wrap"}
      }
    },
    {
      name = "RL_DrawTexture",
      description = "Draw a RL_Texture2D",
      returnType = "void",
      params = {
        {type = "RL_Texture2D", name = "texture"},
        {type = "int", name = "posX"},
        {type = "int", name = "posY"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_DrawTextureV",
      description = "Draw a RL_Texture2D with position defined as RL_Vector2",
      returnType = "void",
      params = {
        {type = "RL_Texture2D", name = "texture"},
        {type = "RL_Vector2", name = "position"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_DrawTextureEx",
      description = "Draw a RL_Texture2D with extended parameters",
      returnType = "void",
      params = {
        {type = "RL_Texture2D", name = "texture"},
        {type = "RL_Vector2", name = "position"},
        {type = "float", name = "rotation"},
        {type = "float", name = "scale"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_DrawTextureRec",
      description = "Draw a part of a texture defined by a rectangle",
      returnType = "void",
      params = {
        {type = "RL_Texture2D", name = "texture"},
        {type = "RL_Rectangle", name = "source"},
        {type = "RL_Vector2", name = "position"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_DrawTexturePro",
      description = "Draw a part of a texture defined by a rectangle with 'pro' parameters",
      returnType = "void",
      params = {
        {type = "RL_Texture2D", name = "texture"},
        {type = "RL_Rectangle", name = "source"},
        {type = "RL_Rectangle", name = "dest"},
        {type = "RL_Vector2", name = "origin"},
        {type = "float", name = "rotation"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_DrawTextureNPatch",
      description = "Draws a texture (or part of it) that stretches or shrinks nicely",
      returnType = "void",
      params = {
        {type = "RL_Texture2D", name = "texture"},
        {type = "RL_NPatchInfo", name = "nPatchInfo"},
        {type = "RL_Rectangle", name = "dest"},
        {type = "RL_Vector2", name = "origin"},
        {type = "float", name = "rotation"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_ColorIsEqual",
      description = "Check if two colors are equal",
      returnType = "bool",
      params = {
        {type = "RL_Color", name = "col1"},
        {type = "RL_Color", name = "col2"}
      }
    },
    {
      name = "RL_Fade",
      description = "Get color with alpha applied, alpha goes from 0.0f to 1.0f",
      returnType = "RL_Color",
      params = {
        {type = "RL_Color", name = "color"},
        {type = "float", name = "alpha"}
      }
    },
    {
      name = "RL_ColorToInt",
      description = "Get hexadecimal value for a RL_Color (0xRRGGBBAA)",
      returnType = "int",
      params = {
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ColorNormalize",
      description = "Get RL_Color normalized as float [0..1]",
      returnType = "RL_Vector4",
      params = {
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ColorFromNormalized",
      description = "Get RL_Color from normalized values [0..1]",
      returnType = "RL_Color",
      params = {
        {type = "RL_Vector4", name = "normalized"}
      }
    },
    {
      name = "RL_ColorToHSV",
      description = "Get HSV values for a RL_Color, hue [0..360], saturation/value [0..1]",
      returnType = "RL_Vector3",
      params = {
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_ColorFromHSV",
      description = "Get a RL_Color from HSV values, hue [0..360], saturation/value [0..1]",
      returnType = "RL_Color",
      params = {
        {type = "float", name = "hue"},
        {type = "float", name = "saturation"},
        {type = "float", name = "value"}
      }
    },
    {
      name = "RL_ColorTint",
      description = "Get color multiplied with another color",
      returnType = "RL_Color",
      params = {
        {type = "RL_Color", name = "color"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_ColorBrightness",
      description = "Get color with brightness correction, brightness factor goes from -1.0f to 1.0f",
      returnType = "RL_Color",
      params = {
        {type = "RL_Color", name = "color"},
        {type = "float", name = "factor"}
      }
    },
    {
      name = "RL_ColorContrast",
      description = "Get color with contrast correction, contrast values between -1.0f and 1.0f",
      returnType = "RL_Color",
      params = {
        {type = "RL_Color", name = "color"},
        {type = "float", name = "contrast"}
      }
    },
    {
      name = "RL_ColorAlpha",
      description = "Get color with alpha applied, alpha goes from 0.0f to 1.0f",
      returnType = "RL_Color",
      params = {
        {type = "RL_Color", name = "color"},
        {type = "float", name = "alpha"}
      }
    },
    {
      name = "RL_ColorAlphaBlend",
      description = "Get src alpha-blended into dst color with tint",
      returnType = "RL_Color",
      params = {
        {type = "RL_Color", name = "dst"},
        {type = "RL_Color", name = "src"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "ColorLerp",
      description = "Get color lerp interpolation between two colors, factor [0.0f..1.0f]",
      returnType = "RL_Color",
      params = {
        {type = "RL_Color", name = "color1"},
        {type = "RL_Color", name = "color2"},
        {type = "float", name = "factor"}
      }
    },
    {
      name = "RL_GetColor",
      description = "Get RL_Color structure from hexadecimal value",
      returnType = "RL_Color",
      params = {
        {type = "unsigned int", name = "hexValue"}
      }
    },
    {
      name = "RL_GetPixelColor",
      description = "Get RL_Color from a source pixel pointer of certain format",
      returnType = "RL_Color",
      params = {
        {type = "void *", name = "srcPtr"},
        {type = "int", name = "format"}
      }
    },
    {
      name = "RL_SetPixelColor",
      description = "Set color formatted into destination pixel pointer",
      returnType = "void",
      params = {
        {type = "void *", name = "dstPtr"},
        {type = "RL_Color", name = "color"},
        {type = "int", name = "format"}
      }
    },
    {
      name = "RL_GetPixelDataSize",
      description = "Get pixel data size in bytes for certain format",
      returnType = "int",
      params = {
        {type = "int", name = "width"},
        {type = "int", name = "height"},
        {type = "int", name = "format"}
      }
    },
    {
      name = "RL_GetFontDefault",
      description = "Get the default RL_Font",
      returnType = "RL_Font"
    },
    {
      name = "RL_LoadFont",
      description = "Load font from file into GPU memory (VRAM)",
      returnType = "RL_Font",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_LoadFontEx",
      description = "Load font from file with extended parameters, use NULL for codepoints and 0 for codepointCount to load the default character set, font size is provided in pixels height",
      returnType = "RL_Font",
      params = {
        {type = "const char *", name = "fileName"},
        {type = "int", name = "fontSize"},
        {type = "int *", name = "codepoints"},
        {type = "int", name = "codepointCount"}
      }
    },
    {
      name = "RL_LoadFontFromImage",
      description = "Load font from RL_Image (XNA style)",
      returnType = "RL_Font",
      params = {
        {type = "RL_Image", name = "image"},
        {type = "RL_Color", name = "key"},
        {type = "int", name = "firstChar"}
      }
    },
    {
      name = "RL_LoadFontFromMemory",
      description = "Load font from memory buffer, fileType refers to extension: i.e. '.ttf'",
      returnType = "RL_Font",
      params = {
        {type = "const char *", name = "fileType"},
        {type = "const unsigned char *", name = "fileData"},
        {type = "int", name = "dataSize"},
        {type = "int", name = "fontSize"},
        {type = "int *", name = "codepoints"},
        {type = "int", name = "codepointCount"}
      }
    },
    {
      name = "IsFontValid",
      description = "Check if a font is valid (font data loaded, WARNING: GPU texture not checked)",
      returnType = "bool",
      params = {
        {type = "RL_Font", name = "font"}
      }
    },
    {
      name = "RL_LoadFontData",
      description = "Load font data for further use",
      returnType = "RL_GlyphInfo *",
      params = {
        {type = "const unsigned char *", name = "fileData"},
        {type = "int", name = "dataSize"},
        {type = "int", name = "fontSize"},
        {type = "int *", name = "codepoints"},
        {type = "int", name = "codepointCount"},
        {type = "int", name = "type"}
      }
    },
    {
      name = "RL_GenImageFontAtlas",
      description = "Generate image font atlas using chars info",
      returnType = "RL_Image",
      params = {
        {type = "const RL_GlyphInfo *", name = "glyphs"},
        {type = "RL_Rectangle **", name = "glyphRecs"},
        {type = "int", name = "glyphCount"},
        {type = "int", name = "fontSize"},
        {type = "int", name = "padding"},
        {type = "int", name = "packMethod"}
      }
    },
    {
      name = "RL_UnloadFontData",
      description = "Unload font chars info data (RAM)",
      returnType = "void",
      params = {
        {type = "RL_GlyphInfo *", name = "glyphs"},
        {type = "int", name = "glyphCount"}
      }
    },
    {
      name = "RL_UnloadFont",
      description = "Unload font from GPU memory (VRAM)",
      returnType = "void",
      params = {
        {type = "RL_Font", name = "font"}
      }
    },
    {
      name = "RL_ExportFontAsCode",
      description = "Export font as code file, returns true on success",
      returnType = "bool",
      params = {
        {type = "RL_Font", name = "font"},
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_DrawFPS",
      description = "Draw current FPS",
      returnType = "void",
      params = {
        {type = "int", name = "posX"},
        {type = "int", name = "posY"}
      }
    },
    {
      name = "RL_DrawText",
      description = "Draw text (using default font)",
      returnType = "void",
      params = {
        {type = "const char *", name = "text"},
        {type = "int", name = "posX"},
        {type = "int", name = "posY"},
        {type = "int", name = "fontSize"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawTextEx",
      description = "Draw text using font and additional parameters",
      returnType = "void",
      params = {
        {type = "RL_Font", name = "font"},
        {type = "const char *", name = "text"},
        {type = "RL_Vector2", name = "position"},
        {type = "float", name = "fontSize"},
        {type = "float", name = "spacing"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_DrawTextPro",
      description = "Draw text using RL_Font and pro parameters (rotation)",
      returnType = "void",
      params = {
        {type = "RL_Font", name = "font"},
        {type = "const char *", name = "text"},
        {type = "RL_Vector2", name = "position"},
        {type = "RL_Vector2", name = "origin"},
        {type = "float", name = "rotation"},
        {type = "float", name = "fontSize"},
        {type = "float", name = "spacing"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_DrawTextCodepoint",
      description = "Draw one character (codepoint)",
      returnType = "void",
      params = {
        {type = "RL_Font", name = "font"},
        {type = "int", name = "codepoint"},
        {type = "RL_Vector2", name = "position"},
        {type = "float", name = "fontSize"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_DrawTextCodepoints",
      description = "Draw multiple character (codepoint)",
      returnType = "void",
      params = {
        {type = "RL_Font", name = "font"},
        {type = "const int *", name = "codepoints"},
        {type = "int", name = "codepointCount"},
        {type = "RL_Vector2", name = "position"},
        {type = "float", name = "fontSize"},
        {type = "float", name = "spacing"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_SetTextLineSpacing",
      description = "Set vertical line spacing when drawing with line-breaks",
      returnType = "void",
      params = {
        {type = "int", name = "spacing"}
      }
    },
    {
      name = "RL_MeasureText",
      description = "Measure string width for default font",
      returnType = "int",
      params = {
        {type = "const char *", name = "text"},
        {type = "int", name = "fontSize"}
      }
    },
    {
      name = "RL_MeasureTextEx",
      description = "Measure string size for RL_Font",
      returnType = "RL_Vector2",
      params = {
        {type = "RL_Font", name = "font"},
        {type = "const char *", name = "text"},
        {type = "float", name = "fontSize"},
        {type = "float", name = "spacing"}
      }
    },
    {
      name = "RL_GetGlyphIndex",
      description = "Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found",
      returnType = "int",
      params = {
        {type = "RL_Font", name = "font"},
        {type = "int", name = "codepoint"}
      }
    },
    {
      name = "RL_GetGlyphInfo",
      description = "Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found",
      returnType = "RL_GlyphInfo",
      params = {
        {type = "RL_Font", name = "font"},
        {type = "int", name = "codepoint"}
      }
    },
    {
      name = "RL_GetGlyphAtlasRec",
      description = "Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found",
      returnType = "RL_Rectangle",
      params = {
        {type = "RL_Font", name = "font"},
        {type = "int", name = "codepoint"}
      }
    },
    {
      name = "RL_LoadUTF8",
      description = "Load UTF-8 text encoded from codepoints array",
      returnType = "char *",
      params = {
        {type = "const int *", name = "codepoints"},
        {type = "int", name = "length"}
      }
    },
    {
      name = "RL_UnloadUTF8",
      description = "Unload UTF-8 text encoded from codepoints array",
      returnType = "void",
      params = {
        {type = "char *", name = "text"}
      }
    },
    {
      name = "RL_LoadCodepoints",
      description = "Load all codepoints from a UTF-8 text string, codepoints count returned by parameter",
      returnType = "int *",
      params = {
        {type = "const char *", name = "text"},
        {type = "int *", name = "count"}
      }
    },
    {
      name = "RL_UnloadCodepoints",
      description = "Unload codepoints data from memory",
      returnType = "void",
      params = {
        {type = "int *", name = "codepoints"}
      }
    },
    {
      name = "RL_GetCodepointCount",
      description = "Get total number of codepoints in a UTF-8 encoded string",
      returnType = "int",
      params = {
        {type = "const char *", name = "text"}
      }
    },
    {
      name = "RL_GetCodepoint",
      description = "Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure",
      returnType = "int",
      params = {
        {type = "const char *", name = "text"},
        {type = "int *", name = "codepointSize"}
      }
    },
    {
      name = "RL_GetCodepointNext",
      description = "Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure",
      returnType = "int",
      params = {
        {type = "const char *", name = "text"},
        {type = "int *", name = "codepointSize"}
      }
    },
    {
      name = "RL_GetCodepointPrevious",
      description = "Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure",
      returnType = "int",
      params = {
        {type = "const char *", name = "text"},
        {type = "int *", name = "codepointSize"}
      }
    },
    {
      name = "RL_CodepointToUTF8",
      description = "Encode one codepoint into UTF-8 byte array (array length returned as parameter)",
      returnType = "const char *",
      params = {
        {type = "int", name = "codepoint"},
        {type = "int *", name = "utf8Size"}
      }
    },
    {
      name = "RL_TextCopy",
      description = "Copy one string to another, returns bytes copied",
      returnType = "int",
      params = {
        {type = "char *", name = "dst"},
        {type = "const char *", name = "src"}
      }
    },
    {
      name = "RL_TextIsEqual",
      description = "Check if two text string are equal",
      returnType = "bool",
      params = {
        {type = "const char *", name = "text1"},
        {type = "const char *", name = "text2"}
      }
    },
    {
      name = "RL_TextLength",
      description = "Get text length, checks for '\\0' ending",
      returnType = "unsigned int",
      params = {
        {type = "const char *", name = "text"}
      }
    },
    {
      name = "RL_TextFormat",
      description = "Text formatting with variables (sprintf() style)",
      returnType = "const char *",
      params = {
        {type = "const char *", name = "text"},
        {type = "...", name = "args"}
      }
    },
    {
      name = "RL_TextSubtext",
      description = "Get a piece of a text string",
      returnType = "const char *",
      params = {
        {type = "const char *", name = "text"},
        {type = "int", name = "position"},
        {type = "int", name = "length"}
      }
    },
    {
      name = "RL_TextReplace",
      description = "Replace text string (WARNING: memory must be freed!)",
      returnType = "char *",
      params = {
        {type = "const char *", name = "text"},
        {type = "const char *", name = "replace"},
        {type = "const char *", name = "by"}
      }
    },
    {
      name = "RL_TextInsert",
      description = "Insert text in a position (WARNING: memory must be freed!)",
      returnType = "char *",
      params = {
        {type = "const char *", name = "text"},
        {type = "const char *", name = "insert"},
        {type = "int", name = "position"}
      }
    },
    {
      name = "RL_TextJoin",
      description = "Join text strings with delimiter",
      returnType = "const char *",
      params = {
        {type = "const char **", name = "textList"},
        {type = "int", name = "count"},
        {type = "const char *", name = "delimiter"}
      }
    },
    {
      name = "RL_TextSplit",
      description = "Split text into multiple strings",
      returnType = "const char **",
      params = {
        {type = "const char *", name = "text"},
        {type = "char", name = "delimiter"},
        {type = "int *", name = "count"}
      }
    },
    {
      name = "RL_TextAppend",
      description = "Append text at specific position and move cursor!",
      returnType = "void",
      params = {
        {type = "char *", name = "text"},
        {type = "const char *", name = "append"},
        {type = "int *", name = "position"}
      }
    },
    {
      name = "RL_TextFindIndex",
      description = "Find first text occurrence within a string",
      returnType = "int",
      params = {
        {type = "const char *", name = "text"},
        {type = "const char *", name = "find"}
      }
    },
    {
      name = "RL_TextToUpper",
      description = "Get upper case version of provided string",
      returnType = "const char *",
      params = {
        {type = "const char *", name = "text"}
      }
    },
    {
      name = "RL_TextToLower",
      description = "Get lower case version of provided string",
      returnType = "const char *",
      params = {
        {type = "const char *", name = "text"}
      }
    },
    {
      name = "RL_TextToPascal",
      description = "Get Pascal case notation version of provided string",
      returnType = "const char *",
      params = {
        {type = "const char *", name = "text"}
      }
    },
    {
      name = "RL_TextToSnake",
      description = "Get Snake case notation version of provided string",
      returnType = "const char *",
      params = {
        {type = "const char *", name = "text"}
      }
    },
    {
      name = "RL_TextToCamel",
      description = "Get Camel case notation version of provided string",
      returnType = "const char *",
      params = {
        {type = "const char *", name = "text"}
      }
    },
    {
      name = "RL_TextToInteger",
      description = "Get integer value from text (negative values not supported)",
      returnType = "int",
      params = {
        {type = "const char *", name = "text"}
      }
    },
    {
      name = "RL_TextToFloat",
      description = "Get float value from text (negative values not supported)",
      returnType = "float",
      params = {
        {type = "const char *", name = "text"}
      }
    },
    {
      name = "RL_DrawLine3D",
      description = "Draw a line in 3D world space",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "startPos"},
        {type = "RL_Vector3", name = "endPos"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawPoint3D",
      description = "Draw a point in 3D space, actually a small line",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "position"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCircle3D",
      description = "Draw a circle in 3D world space",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "center"},
        {type = "float", name = "radius"},
        {type = "RL_Vector3", name = "rotationAxis"},
        {type = "float", name = "rotationAngle"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawTriangle3D",
      description = "Draw a color-filled triangle (vertex in counter-clockwise order!)",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "v1"},
        {type = "RL_Vector3", name = "v2"},
        {type = "RL_Vector3", name = "v3"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawTriangleStrip3D",
      description = "Draw a triangle strip defined by points",
      returnType = "void",
      params = {
        {type = "const RL_Vector3 *", name = "points"},
        {type = "int", name = "pointCount"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCube",
      description = "Draw cube",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "position"},
        {type = "float", name = "width"},
        {type = "float", name = "height"},
        {type = "float", name = "length"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCubeV",
      description = "Draw cube (Vector version)",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "position"},
        {type = "RL_Vector3", name = "size"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCubeWires",
      description = "Draw cube wires",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "position"},
        {type = "float", name = "width"},
        {type = "float", name = "height"},
        {type = "float", name = "length"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCubeWiresV",
      description = "Draw cube wires (Vector version)",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "position"},
        {type = "RL_Vector3", name = "size"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawSphere",
      description = "Draw sphere",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "centerPos"},
        {type = "float", name = "radius"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawSphereEx",
      description = "Draw sphere with extended parameters",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "centerPos"},
        {type = "float", name = "radius"},
        {type = "int", name = "rings"},
        {type = "int", name = "slices"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawSphereWires",
      description = "Draw sphere wires",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "centerPos"},
        {type = "float", name = "radius"},
        {type = "int", name = "rings"},
        {type = "int", name = "slices"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCylinder",
      description = "Draw a cylinder/cone",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "position"},
        {type = "float", name = "radiusTop"},
        {type = "float", name = "radiusBottom"},
        {type = "float", name = "height"},
        {type = "int", name = "slices"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCylinderEx",
      description = "Draw a cylinder with base at startPos and top at endPos",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "startPos"},
        {type = "RL_Vector3", name = "endPos"},
        {type = "float", name = "startRadius"},
        {type = "float", name = "endRadius"},
        {type = "int", name = "sides"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCylinderWires",
      description = "Draw a cylinder/cone wires",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "position"},
        {type = "float", name = "radiusTop"},
        {type = "float", name = "radiusBottom"},
        {type = "float", name = "height"},
        {type = "int", name = "slices"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCylinderWiresEx",
      description = "Draw a cylinder wires with base at startPos and top at endPos",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "startPos"},
        {type = "RL_Vector3", name = "endPos"},
        {type = "float", name = "startRadius"},
        {type = "float", name = "endRadius"},
        {type = "int", name = "sides"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCapsule",
      description = "Draw a capsule with the center of its sphere caps at startPos and endPos",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "startPos"},
        {type = "RL_Vector3", name = "endPos"},
        {type = "float", name = "radius"},
        {type = "int", name = "slices"},
        {type = "int", name = "rings"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawCapsuleWires",
      description = "Draw capsule wireframe with the center of its sphere caps at startPos and endPos",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "startPos"},
        {type = "RL_Vector3", name = "endPos"},
        {type = "float", name = "radius"},
        {type = "int", name = "slices"},
        {type = "int", name = "rings"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawPlane",
      description = "Draw a plane XZ",
      returnType = "void",
      params = {
        {type = "RL_Vector3", name = "centerPos"},
        {type = "RL_Vector2", name = "size"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawRay",
      description = "Draw a ray line",
      returnType = "void",
      params = {
        {type = "RL_Ray", name = "ray"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawGrid",
      description = "Draw a grid (centered at (0, 0, 0))",
      returnType = "void",
      params = {
        {type = "int", name = "slices"},
        {type = "float", name = "spacing"}
      }
    },
    {
      name = "RL_LoadModel",
      description = "Load model from files (meshes and materials)",
      returnType = "RL_Model",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_LoadModelFromMesh",
      description = "Load model from generated mesh (default material)",
      returnType = "RL_Model",
      params = {
        {type = "RL_Mesh", name = "mesh"}
      }
    },
    {
      name = "IsModelValid",
      description = "Check if a model is valid (loaded in GPU, VAO/VBOs)",
      returnType = "bool",
      params = {
        {type = "RL_Model", name = "model"}
      }
    },
    {
      name = "RL_UnloadModel",
      description = "Unload model (including meshes) from memory (RAM and/or VRAM)",
      returnType = "void",
      params = {
        {type = "RL_Model", name = "model"}
      }
    },
    {
      name = "RL_GetModelBoundingBox",
      description = "Compute model bounding box limits (considers all meshes)",
      returnType = "RL_BoundingBox",
      params = {
        {type = "RL_Model", name = "model"}
      }
    },
    {
      name = "RL_DrawModel",
      description = "Draw a model (with texture if set)",
      returnType = "void",
      params = {
        {type = "RL_Model", name = "model"},
        {type = "RL_Vector3", name = "position"},
        {type = "float", name = "scale"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_DrawModelEx",
      description = "Draw a model with extended parameters",
      returnType = "void",
      params = {
        {type = "RL_Model", name = "model"},
        {type = "RL_Vector3", name = "position"},
        {type = "RL_Vector3", name = "rotationAxis"},
        {type = "float", name = "rotationAngle"},
        {type = "RL_Vector3", name = "scale"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_DrawModelWires",
      description = "Draw a model wires (with texture if set)",
      returnType = "void",
      params = {
        {type = "RL_Model", name = "model"},
        {type = "RL_Vector3", name = "position"},
        {type = "float", name = "scale"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_DrawModelWiresEx",
      description = "Draw a model wires (with texture if set) with extended parameters",
      returnType = "void",
      params = {
        {type = "RL_Model", name = "model"},
        {type = "RL_Vector3", name = "position"},
        {type = "RL_Vector3", name = "rotationAxis"},
        {type = "float", name = "rotationAngle"},
        {type = "RL_Vector3", name = "scale"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "DrawModelPoints",
      description = "Draw a model as points",
      returnType = "void",
      params = {
        {type = "RL_Model", name = "model"},
        {type = "RL_Vector3", name = "position"},
        {type = "float", name = "scale"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "DrawModelPointsEx",
      description = "Draw a model as points with extended parameters",
      returnType = "void",
      params = {
        {type = "RL_Model", name = "model"},
        {type = "RL_Vector3", name = "position"},
        {type = "RL_Vector3", name = "rotationAxis"},
        {type = "float", name = "rotationAngle"},
        {type = "RL_Vector3", name = "scale"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_DrawBoundingBox",
      description = "Draw bounding box (wires)",
      returnType = "void",
      params = {
        {type = "RL_BoundingBox", name = "box"},
        {type = "RL_Color", name = "color"}
      }
    },
    {
      name = "RL_DrawBillboard",
      description = "Draw a billboard texture",
      returnType = "void",
      params = {
        {type = "RL_Camera", name = "camera"},
        {type = "RL_Texture2D", name = "texture"},
        {type = "RL_Vector3", name = "position"},
        {type = "float", name = "scale"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_DrawBillboardRec",
      description = "Draw a billboard texture defined by source",
      returnType = "void",
      params = {
        {type = "RL_Camera", name = "camera"},
        {type = "RL_Texture2D", name = "texture"},
        {type = "RL_Rectangle", name = "source"},
        {type = "RL_Vector3", name = "position"},
        {type = "RL_Vector2", name = "size"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_DrawBillboardPro",
      description = "Draw a billboard texture defined by source and rotation",
      returnType = "void",
      params = {
        {type = "RL_Camera", name = "camera"},
        {type = "RL_Texture2D", name = "texture"},
        {type = "RL_Rectangle", name = "source"},
        {type = "RL_Vector3", name = "position"},
        {type = "RL_Vector3", name = "up"},
        {type = "RL_Vector2", name = "size"},
        {type = "RL_Vector2", name = "origin"},
        {type = "float", name = "rotation"},
        {type = "RL_Color", name = "tint"}
      }
    },
    {
      name = "RL_UploadMesh",
      description = "Upload mesh vertex data in GPU and provide VAO/VBO ids",
      returnType = "void",
      params = {
        {type = "RL_Mesh *", name = "mesh"},
        {type = "bool", name = "dynamic"}
      }
    },
    {
      name = "RL_UpdateMeshBuffer",
      description = "Update mesh vertex data in GPU for a specific buffer index",
      returnType = "void",
      params = {
        {type = "RL_Mesh", name = "mesh"},
        {type = "int", name = "index"},
        {type = "const void *", name = "data"},
        {type = "int", name = "dataSize"},
        {type = "int", name = "offset"}
      }
    },
    {
      name = "RL_UnloadMesh",
      description = "Unload mesh data from CPU and GPU",
      returnType = "void",
      params = {
        {type = "RL_Mesh", name = "mesh"}
      }
    },
    {
      name = "RL_DrawMesh",
      description = "Draw a 3d mesh with material and transform",
      returnType = "void",
      params = {
        {type = "RL_Mesh", name = "mesh"},
        {type = "RL_Material", name = "material"},
        {type = "RL_Matrix", name = "transform"}
      }
    },
    {
      name = "RL_DrawMeshInstanced",
      description = "Draw multiple mesh instances with material and different transforms",
      returnType = "void",
      params = {
        {type = "RL_Mesh", name = "mesh"},
        {type = "RL_Material", name = "material"},
        {type = "const RL_Matrix *", name = "transforms"},
        {type = "int", name = "instances"}
      }
    },
    {
      name = "RL_GetMeshBoundingBox",
      description = "Compute mesh bounding box limits",
      returnType = "RL_BoundingBox",
      params = {
        {type = "RL_Mesh", name = "mesh"}
      }
    },
    {
      name = "RL_GenMeshTangents",
      description = "Compute mesh tangents",
      returnType = "void",
      params = {
        {type = "RL_Mesh *", name = "mesh"}
      }
    },
    {
      name = "RL_ExportMesh",
      description = "Export mesh data to file, returns true on success",
      returnType = "bool",
      params = {
        {type = "RL_Mesh", name = "mesh"},
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_ExportMeshAsCode",
      description = "Export mesh as code file (.h) defining multiple arrays of vertex attributes",
      returnType = "bool",
      params = {
        {type = "RL_Mesh", name = "mesh"},
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_GenMeshPoly",
      description = "Generate polygonal mesh",
      returnType = "RL_Mesh",
      params = {
        {type = "int", name = "sides"},
        {type = "float", name = "radius"}
      }
    },
    {
      name = "RL_GenMeshPlane",
      description = "Generate plane mesh (with subdivisions)",
      returnType = "RL_Mesh",
      params = {
        {type = "float", name = "width"},
        {type = "float", name = "length"},
        {type = "int", name = "resX"},
        {type = "int", name = "resZ"}
      }
    },
    {
      name = "RL_GenMeshCube",
      description = "Generate cuboid mesh",
      returnType = "RL_Mesh",
      params = {
        {type = "float", name = "width"},
        {type = "float", name = "height"},
        {type = "float", name = "length"}
      }
    },
    {
      name = "RL_GenMeshSphere",
      description = "Generate sphere mesh (standard sphere)",
      returnType = "RL_Mesh",
      params = {
        {type = "float", name = "radius"},
        {type = "int", name = "rings"},
        {type = "int", name = "slices"}
      }
    },
    {
      name = "RL_GenMeshHemiSphere",
      description = "Generate half-sphere mesh (no bottom cap)",
      returnType = "RL_Mesh",
      params = {
        {type = "float", name = "radius"},
        {type = "int", name = "rings"},
        {type = "int", name = "slices"}
      }
    },
    {
      name = "RL_GenMeshCylinder",
      description = "Generate cylinder mesh",
      returnType = "RL_Mesh",
      params = {
        {type = "float", name = "radius"},
        {type = "float", name = "height"},
        {type = "int", name = "slices"}
      }
    },
    {
      name = "RL_GenMeshCone",
      description = "Generate cone/pyramid mesh",
      returnType = "RL_Mesh",
      params = {
        {type = "float", name = "radius"},
        {type = "float", name = "height"},
        {type = "int", name = "slices"}
      }
    },
    {
      name = "RL_GenMeshTorus",
      description = "Generate torus mesh",
      returnType = "RL_Mesh",
      params = {
        {type = "float", name = "radius"},
        {type = "float", name = "size"},
        {type = "int", name = "radSeg"},
        {type = "int", name = "sides"}
      }
    },
    {
      name = "RL_GenMeshKnot",
      description = "Generate trefoil knot mesh",
      returnType = "RL_Mesh",
      params = {
        {type = "float", name = "radius"},
        {type = "float", name = "size"},
        {type = "int", name = "radSeg"},
        {type = "int", name = "sides"}
      }
    },
    {
      name = "RL_GenMeshHeightmap",
      description = "Generate heightmap mesh from image data",
      returnType = "RL_Mesh",
      params = {
        {type = "RL_Image", name = "heightmap"},
        {type = "RL_Vector3", name = "size"}
      }
    },
    {
      name = "RL_GenMeshCubicmap",
      description = "Generate cubes-based map mesh from image data",
      returnType = "RL_Mesh",
      params = {
        {type = "RL_Image", name = "cubicmap"},
        {type = "RL_Vector3", name = "cubeSize"}
      }
    },
    {
      name = "RL_LoadMaterials",
      description = "Load materials from model file",
      returnType = "RL_Material *",
      params = {
        {type = "const char *", name = "fileName"},
        {type = "int *", name = "materialCount"}
      }
    },
    {
      name = "RL_LoadMaterialDefault",
      description = "Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)",
      returnType = "RL_Material"
    },
    {
      name = "IsMaterialValid",
      description = "Check if a material is valid (shader assigned, map textures loaded in GPU)",
      returnType = "bool",
      params = {
        {type = "RL_Material", name = "material"}
      }
    },
    {
      name = "RL_UnloadMaterial",
      description = "Unload material from GPU memory (VRAM)",
      returnType = "void",
      params = {
        {type = "RL_Material", name = "material"}
      }
    },
    {
      name = "RL_SetMaterialTexture",
      description = "Set texture for a material map type (MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_SPECULAR...)",
      returnType = "void",
      params = {
        {type = "RL_Material *", name = "material"},
        {type = "int", name = "mapType"},
        {type = "RL_Texture2D", name = "texture"}
      }
    },
    {
      name = "RL_SetModelMeshMaterial",
      description = "Set material for a mesh",
      returnType = "void",
      params = {
        {type = "RL_Model *", name = "model"},
        {type = "int", name = "meshId"},
        {type = "int", name = "materialId"}
      }
    },
    {
      name = "RL_LoadModelAnimations",
      description = "Load model animations from file",
      returnType = "RL_ModelAnimation *",
      params = {
        {type = "const char *", name = "fileName"},
        {type = "int *", name = "animCount"}
      }
    },
    {
      name = "RL_UpdateModelAnimation",
      description = "Update model animation pose (CPU)",
      returnType = "void",
      params = {
        {type = "RL_Model", name = "model"},
        {type = "RL_ModelAnimation", name = "anim"},
        {type = "int", name = "frame"}
      }
    },
    {
      name = "UpdateModelAnimationBones",
      description = "Update model animation mesh bone matrices (GPU skinning)",
      returnType = "void",
      params = {
        {type = "RL_Model", name = "model"},
        {type = "RL_ModelAnimation", name = "anim"},
        {type = "int", name = "frame"}
      }
    },
    {
      name = "RL_UnloadModelAnimation",
      description = "Unload animation data",
      returnType = "void",
      params = {
        {type = "RL_ModelAnimation", name = "anim"}
      }
    },
    {
      name = "RL_UnloadModelAnimations",
      description = "Unload animation array data",
      returnType = "void",
      params = {
        {type = "RL_ModelAnimation *", name = "animations"},
        {type = "int", name = "animCount"}
      }
    },
    {
      name = "RL_IsModelAnimationValid",
      description = "Check model animation skeleton match",
      returnType = "bool",
      params = {
        {type = "RL_Model", name = "model"},
        {type = "RL_ModelAnimation", name = "anim"}
      }
    },
    {
      name = "RL_CheckCollisionSpheres",
      description = "Check collision between two spheres",
      returnType = "bool",
      params = {
        {type = "RL_Vector3", name = "center1"},
        {type = "float", name = "radius1"},
        {type = "RL_Vector3", name = "center2"},
        {type = "float", name = "radius2"}
      }
    },
    {
      name = "RL_CheckCollisionBoxes",
      description = "Check collision between two bounding boxes",
      returnType = "bool",
      params = {
        {type = "RL_BoundingBox", name = "box1"},
        {type = "RL_BoundingBox", name = "box2"}
      }
    },
    {
      name = "RL_CheckCollisionBoxSphere",
      description = "Check collision between box and sphere",
      returnType = "bool",
      params = {
        {type = "RL_BoundingBox", name = "box"},
        {type = "RL_Vector3", name = "center"},
        {type = "float", name = "radius"}
      }
    },
    {
      name = "RL_GetRayCollisionSphere",
      description = "Get collision info between ray and sphere",
      returnType = "RL_RayCollision",
      params = {
        {type = "RL_Ray", name = "ray"},
        {type = "RL_Vector3", name = "center"},
        {type = "float", name = "radius"}
      }
    },
    {
      name = "RL_GetRayCollisionBox",
      description = "Get collision info between ray and box",
      returnType = "RL_RayCollision",
      params = {
        {type = "RL_Ray", name = "ray"},
        {type = "RL_BoundingBox", name = "box"}
      }
    },
    {
      name = "RL_GetRayCollisionMesh",
      description = "Get collision info between ray and mesh",
      returnType = "RL_RayCollision",
      params = {
        {type = "RL_Ray", name = "ray"},
        {type = "RL_Mesh", name = "mesh"},
        {type = "RL_Matrix", name = "transform"}
      }
    },
    {
      name = "RL_GetRayCollisionTriangle",
      description = "Get collision info between ray and triangle",
      returnType = "RL_RayCollision",
      params = {
        {type = "RL_Ray", name = "ray"},
        {type = "RL_Vector3", name = "p1"},
        {type = "RL_Vector3", name = "p2"},
        {type = "RL_Vector3", name = "p3"}
      }
    },
    {
      name = "RL_GetRayCollisionQuad",
      description = "Get collision info between ray and quad",
      returnType = "RL_RayCollision",
      params = {
        {type = "RL_Ray", name = "ray"},
        {type = "RL_Vector3", name = "p1"},
        {type = "RL_Vector3", name = "p2"},
        {type = "RL_Vector3", name = "p3"},
        {type = "RL_Vector3", name = "p4"}
      }
    },
    {
      name = "RL_InitAudioDevice",
      description = "Initialize audio device and context",
      returnType = "void"
    },
    {
      name = "RL_CloseAudioDevice",
      description = "Close the audio device and context",
      returnType = "void"
    },
    {
      name = "RL_IsAudioDeviceReady",
      description = "Check if audio device has been initialized successfully",
      returnType = "bool"
    },
    {
      name = "RL_SetMasterVolume",
      description = "Set master volume (listener)",
      returnType = "void",
      params = {
        {type = "float", name = "volume"}
      }
    },
    {
      name = "RL_GetMasterVolume",
      description = "Get master volume (listener)",
      returnType = "float"
    },
    {
      name = "RL_LoadWave",
      description = "Load wave data from file",
      returnType = "RL_Wave",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_LoadWaveFromMemory",
      description = "Load wave from memory buffer, fileType refers to extension: i.e. '.wav'",
      returnType = "RL_Wave",
      params = {
        {type = "const char *", name = "fileType"},
        {type = "const unsigned char *", name = "fileData"},
        {type = "int", name = "dataSize"}
      }
    },
    {
      name = "IsWaveValid",
      description = "Checks if wave data is valid (data loaded and parameters)",
      returnType = "bool",
      params = {
        {type = "RL_Wave", name = "wave"}
      }
    },
    {
      name = "RL_LoadSound",
      description = "Load sound from file",
      returnType = "RL_Sound",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_LoadSoundFromWave",
      description = "Load sound from wave data",
      returnType = "RL_Sound",
      params = {
        {type = "RL_Wave", name = "wave"}
      }
    },
    {
      name = "RL_LoadSoundAlias",
      description = "Create a new sound that shares the same sample data as the source sound, does not own the sound data",
      returnType = "RL_Sound",
      params = {
        {type = "RL_Sound", name = "source"}
      }
    },
    {
      name = "IsSoundValid",
      description = "Checks if a sound is valid (data loaded and buffers initialized)",
      returnType = "bool",
      params = {
        {type = "RL_Sound", name = "sound"}
      }
    },
    {
      name = "RL_UpdateSound",
      description = "Update sound buffer with new data",
      returnType = "void",
      params = {
        {type = "RL_Sound", name = "sound"},
        {type = "const void *", name = "data"},
        {type = "int", name = "sampleCount"}
      }
    },
    {
      name = "RL_UnloadWave",
      description = "Unload wave data",
      returnType = "void",
      params = {
        {type = "RL_Wave", name = "wave"}
      }
    },
    {
      name = "RL_UnloadSound",
      description = "Unload sound",
      returnType = "void",
      params = {
        {type = "RL_Sound", name = "sound"}
      }
    },
    {
      name = "RL_UnloadSoundAlias",
      description = "Unload a sound alias (does not deallocate sample data)",
      returnType = "void",
      params = {
        {type = "RL_Sound", name = "alias"}
      }
    },
    {
      name = "RL_ExportWave",
      description = "Export wave data to file, returns true on success",
      returnType = "bool",
      params = {
        {type = "RL_Wave", name = "wave"},
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_ExportWaveAsCode",
      description = "Export wave sample data to code (.h), returns true on success",
      returnType = "bool",
      params = {
        {type = "RL_Wave", name = "wave"},
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_PlaySound",
      description = "Play a sound",
      returnType = "void",
      params = {
        {type = "RL_Sound", name = "sound"}
      }
    },
    {
      name = "RL_StopSound",
      description = "Stop playing a sound",
      returnType = "void",
      params = {
        {type = "RL_Sound", name = "sound"}
      }
    },
    {
      name = "RL_PauseSound",
      description = "Pause a sound",
      returnType = "void",
      params = {
        {type = "RL_Sound", name = "sound"}
      }
    },
    {
      name = "RL_ResumeSound",
      description = "Resume a paused sound",
      returnType = "void",
      params = {
        {type = "RL_Sound", name = "sound"}
      }
    },
    {
      name = "RL_IsSoundPlaying",
      description = "Check if a sound is currently playing",
      returnType = "bool",
      params = {
        {type = "RL_Sound", name = "sound"}
      }
    },
    {
      name = "RL_SetSoundVolume",
      description = "Set volume for a sound (1.0 is max level)",
      returnType = "void",
      params = {
        {type = "RL_Sound", name = "sound"},
        {type = "float", name = "volume"}
      }
    },
    {
      name = "RL_SetSoundPitch",
      description = "Set pitch for a sound (1.0 is base level)",
      returnType = "void",
      params = {
        {type = "RL_Sound", name = "sound"},
        {type = "float", name = "pitch"}
      }
    },
    {
      name = "RL_SetSoundPan",
      description = "Set pan for a sound (0.5 is center)",
      returnType = "void",
      params = {
        {type = "RL_Sound", name = "sound"},
        {type = "float", name = "pan"}
      }
    },
    {
      name = "RL_WaveCopy",
      description = "Copy a wave to a new wave",
      returnType = "RL_Wave",
      params = {
        {type = "RL_Wave", name = "wave"}
      }
    },
    {
      name = "RL_WaveCrop",
      description = "Crop a wave to defined frames range",
      returnType = "void",
      params = {
        {type = "RL_Wave *", name = "wave"},
        {type = "int", name = "initFrame"},
        {type = "int", name = "finalFrame"}
      }
    },
    {
      name = "RL_WaveFormat",
      description = "Convert wave data to desired format",
      returnType = "void",
      params = {
        {type = "RL_Wave *", name = "wave"},
        {type = "int", name = "sampleRate"},
        {type = "int", name = "sampleSize"},
        {type = "int", name = "channels"}
      }
    },
    {
      name = "RL_LoadWaveSamples",
      description = "Load samples data from wave as a 32bit float data array",
      returnType = "float *",
      params = {
        {type = "RL_Wave", name = "wave"}
      }
    },
    {
      name = "RL_UnloadWaveSamples",
      description = "Unload samples data loaded with RL_LoadWaveSamples()",
      returnType = "void",
      params = {
        {type = "float *", name = "samples"}
      }
    },
    {
      name = "RL_LoadMusicStream",
      description = "Load music stream from file",
      returnType = "RL_Music",
      params = {
        {type = "const char *", name = "fileName"}
      }
    },
    {
      name = "RL_LoadMusicStreamFromMemory",
      description = "Load music stream from data",
      returnType = "RL_Music",
      params = {
        {type = "const char *", name = "fileType"},
        {type = "const unsigned char *", name = "data"},
        {type = "int", name = "dataSize"}
      }
    },
    {
      name = "IsMusicValid",
      description = "Checks if a music stream is valid (context and buffers initialized)",
      returnType = "bool",
      params = {
        {type = "RL_Music", name = "music"}
      }
    },
    {
      name = "RL_UnloadMusicStream",
      description = "Unload music stream",
      returnType = "void",
      params = {
        {type = "RL_Music", name = "music"}
      }
    },
    {
      name = "RL_PlayMusicStream",
      description = "Start music playing",
      returnType = "void",
      params = {
        {type = "RL_Music", name = "music"}
      }
    },
    {
      name = "RL_IsMusicStreamPlaying",
      description = "Check if music is playing",
      returnType = "bool",
      params = {
        {type = "RL_Music", name = "music"}
      }
    },
    {
      name = "RL_UpdateMusicStream",
      description = "Updates buffers for music streaming",
      returnType = "void",
      params = {
        {type = "RL_Music", name = "music"}
      }
    },
    {
      name = "RL_StopMusicStream",
      description = "Stop music playing",
      returnType = "void",
      params = {
        {type = "RL_Music", name = "music"}
      }
    },
    {
      name = "RL_PauseMusicStream",
      description = "Pause music playing",
      returnType = "void",
      params = {
        {type = "RL_Music", name = "music"}
      }
    },
    {
      name = "RL_ResumeMusicStream",
      description = "Resume playing paused music",
      returnType = "void",
      params = {
        {type = "RL_Music", name = "music"}
      }
    },
    {
      name = "RL_SeekMusicStream",
      description = "Seek music to a position (in seconds)",
      returnType = "void",
      params = {
        {type = "RL_Music", name = "music"},
        {type = "float", name = "position"}
      }
    },
    {
      name = "RL_SetMusicVolume",
      description = "Set volume for music (1.0 is max level)",
      returnType = "void",
      params = {
        {type = "RL_Music", name = "music"},
        {type = "float", name = "volume"}
      }
    },
    {
      name = "RL_SetMusicPitch",
      description = "Set pitch for a music (1.0 is base level)",
      returnType = "void",
      params = {
        {type = "RL_Music", name = "music"},
        {type = "float", name = "pitch"}
      }
    },
    {
      name = "RL_SetMusicPan",
      description = "Set pan for a music (0.5 is center)",
      returnType = "void",
      params = {
        {type = "RL_Music", name = "music"},
        {type = "float", name = "pan"}
      }
    },
    {
      name = "RL_GetMusicTimeLength",
      description = "Get music time length (in seconds)",
      returnType = "float",
      params = {
        {type = "RL_Music", name = "music"}
      }
    },
    {
      name = "RL_GetMusicTimePlayed",
      description = "Get current music time played (in seconds)",
      returnType = "float",
      params = {
        {type = "RL_Music", name = "music"}
      }
    },
    {
      name = "RL_LoadAudioStream",
      description = "Load audio stream (to stream raw audio pcm data)",
      returnType = "RL_AudioStream",
      params = {
        {type = "unsigned int", name = "sampleRate"},
        {type = "unsigned int", name = "sampleSize"},
        {type = "unsigned int", name = "channels"}
      }
    },
    {
      name = "IsAudioStreamValid",
      description = "Checks if an audio stream is valid (buffers initialized)",
      returnType = "bool",
      params = {
        {type = "RL_AudioStream", name = "stream"}
      }
    },
    {
      name = "RL_UnloadAudioStream",
      description = "Unload audio stream and free memory",
      returnType = "void",
      params = {
        {type = "RL_AudioStream", name = "stream"}
      }
    },
    {
      name = "RL_UpdateAudioStream",
      description = "Update audio stream buffers with data",
      returnType = "void",
      params = {
        {type = "RL_AudioStream", name = "stream"},
        {type = "const void *", name = "data"},
        {type = "int", name = "frameCount"}
      }
    },
    {
      name = "RL_IsAudioStreamProcessed",
      description = "Check if any audio stream buffers requires refill",
      returnType = "bool",
      params = {
        {type = "RL_AudioStream", name = "stream"}
      }
    },
    {
      name = "RL_PlayAudioStream",
      description = "Play audio stream",
      returnType = "void",
      params = {
        {type = "RL_AudioStream", name = "stream"}
      }
    },
    {
      name = "RL_PauseAudioStream",
      description = "Pause audio stream",
      returnType = "void",
      params = {
        {type = "RL_AudioStream", name = "stream"}
      }
    },
    {
      name = "RL_ResumeAudioStream",
      description = "Resume audio stream",
      returnType = "void",
      params = {
        {type = "RL_AudioStream", name = "stream"}
      }
    },
    {
      name = "RL_IsAudioStreamPlaying",
      description = "Check if audio stream is playing",
      returnType = "bool",
      params = {
        {type = "RL_AudioStream", name = "stream"}
      }
    },
    {
      name = "RL_StopAudioStream",
      description = "Stop audio stream",
      returnType = "void",
      params = {
        {type = "RL_AudioStream", name = "stream"}
      }
    },
    {
      name = "RL_SetAudioStreamVolume",
      description = "Set volume for audio stream (1.0 is max level)",
      returnType = "void",
      params = {
        {type = "RL_AudioStream", name = "stream"},
        {type = "float", name = "volume"}
      }
    },
    {
      name = "RL_SetAudioStreamPitch",
      description = "Set pitch for audio stream (1.0 is base level)",
      returnType = "void",
      params = {
        {type = "RL_AudioStream", name = "stream"},
        {type = "float", name = "pitch"}
      }
    },
    {
      name = "RL_SetAudioStreamPan",
      description = "Set pan for audio stream (0.5 is centered)",
      returnType = "void",
      params = {
        {type = "RL_AudioStream", name = "stream"},
        {type = "float", name = "pan"}
      }
    },
    {
      name = "RL_SetAudioStreamBufferSizeDefault",
      description = "Default size for new audio streams",
      returnType = "void",
      params = {
        {type = "int", name = "size"}
      }
    },
    {
      name = "RL_SetAudioStreamCallback",
      description = "Audio thread callback to request new data",
      returnType = "void",
      params = {
        {type = "RL_AudioStream", name = "stream"},
        {type = "AudioCallback", name = "callback"}
      }
    },
    {
      name = "RL_AttachAudioStreamProcessor",
      description = "Attach audio stream processor to stream, receives the samples as 'float'",
      returnType = "void",
      params = {
        {type = "RL_AudioStream", name = "stream"},
        {type = "AudioCallback", name = "processor"}
      }
    },
    {
      name = "RL_DetachAudioStreamProcessor",
      description = "Detach audio stream processor from stream",
      returnType = "void",
      params = {
        {type = "RL_AudioStream", name = "stream"},
        {type = "AudioCallback", name = "processor"}
      }
    },
    {
      name = "RL_AttachAudioMixedProcessor",
      description = "Attach audio stream processor to the entire audio pipeline, receives the samples as 'float'",
      returnType = "void",
      params = {
        {type = "AudioCallback", name = "processor"}
      }
    },
    {
      name = "RL_DetachAudioMixedProcessor",
      description = "Detach audio stream processor from the entire audio pipeline",
      returnType = "void",
      params = {
        {type = "AudioCallback", name = "processor"}
      }
    }
  }
}
