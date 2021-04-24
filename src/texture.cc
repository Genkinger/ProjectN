#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


texture_t N_CreateTexture(i32 width, i32 height, GLenum target, GLenum iformat, GLenum format){
    texture_t t = {width,height,0,0};

    glGenTextures(1, &t.id);
    glBindTexture(target, t.id);
    glTexImage2D(target, 0, iformat, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(target, 0);
    return t;
}

texture_t N_LoadTextureFromFile(const char* path, GLenum target, GLenum iformat, GLenum format){
    texture_t t;
    u8 *data = stbi_load(path, &t.width, &t.height, &t.components, 0);
    glGenTextures(1, &t.id);
    glBindTexture(target, t.id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glTexImage2D(target, 0, iformat, t.width, t.height, 0, format, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(target);
    glBindTexture(target, 0);
    return t;
}

texture_t N_LoadTextureFromMemory(u8 *buffer, i32 width, i32 height, GLenum target , GLenum iformat , GLenum format, GLenum minfilter, GLenum magfilter){
    texture_t t = {width, height,0,0};
    glGenTextures(1,&t.id);
    glBindTexture(target,t.id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glTexImage2D(target, 0, iformat, t.width, t.height, 0, format, GL_UNSIGNED_BYTE, buffer);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minfilter);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magfilter);
    glGenerateMipmap(target);
    glBindTexture(target,0);
    return t;
}