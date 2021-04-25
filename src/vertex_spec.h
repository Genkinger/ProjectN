#pragma once
#include "types.h"
#include <epoxy/gl.h>

typedef struct vertex_s
{
    r32 pos[3];
    r32 uv[2];
    //r32 norm[3];
} nvertex_t;

typedef struct quad_s
{   
    nvertex_t verts[4];
} nquad_t;

void N_SetupVertexData(GLuint vao, GLuint vbo, void *data, i32 size);


