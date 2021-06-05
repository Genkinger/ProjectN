#pragma once
#include "types.h"
#include "util.h"
#include <epoxy/gl.h>

typedef struct ntexture_s
{
    i32 width;
    i32 height;
    i32 components;
    GLuint id;
} ntexture_t;


ntexture_t N_CreateTexture(i32 width, i32 height, GLenum target = GL_TEXTURE_2D, GLenum iformat = GL_RGB, GLenum format = GL_RGB);
ntexture_t N_LoadTextureFromFile(const char* path, GLenum target = GL_TEXTURE_2D, GLenum iformat = GL_RGB, GLenum format = GL_RGB);
ntexture_t N_LoadTextureFromMemory(u8 *buffer, i32 width, i32 height, GLenum target = GL_TEXTURE_2D, GLenum iformat = GL_RGB, GLenum format = GL_RGB, GLenum minfilter = GL_NEAREST,GLenum magfilter = GL_NEAREST);
