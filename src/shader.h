#pragma once
#include "types.h"
#include "util.h"
#include <epoxy/gl.h>


typedef struct nshader_s{
    GLuint id;
} nshader_t;

bool N_CompileShader(GLuint shader, const char* name);
nshader_t N_LoadShaderFromMemory(const char* vertex_source, const char* fragment_source, const char* vertex_name, const char* fragment_name);
nshader_t N_LoadShaderFromFile(const char* vertex_path, const char* fragment_path);
