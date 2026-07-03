#define SOKOL_NO_ENTRY
#define SOKOL_IMPL
#define SOKOL_GL_IMPL

#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "sokol_time.h"
#include "sokol_log.h"
#include "sokol_gl.h"

#include "imgui.h"
#include "util/sokol_imgui.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
