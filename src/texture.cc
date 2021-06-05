#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


ntexture_t N_CreateTexture(i32 width, i32 height, GLenum target, GLenum iformat, GLenum format){
    ntexture_t texture = {width,height,0,0};

    glGenTextures(1, &texture.id);
    glBindTexture(target, texture.id);
    glTexImage2D(target, 0, iformat, width, height, 0, format, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(target, 0);
    return texture;
}

ntexture_t N_LoadTextureFromFile(const char* path, GLenum target, GLenum iformat, GLenum format){
    ntexture_t texture;
    u8 *data = stbi_load(path, &texture.width, &texture.height, &texture.components, 0);
    glGenTextures(1, &texture.id);
    glBindTexture(target, texture.id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glTexImage2D(target, 0, iformat, texture.width, texture.height, 0, format, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenerateMipmap(target);
    glBindTexture(target, 0);
    return texture;
}

ntexture_t N_LoadTextureFromMemory(u8 *buffer, i32 width, i32 height, GLenum target , GLenum iformat , GLenum format, GLenum minfilter, GLenum magfilter){
    ntexture_t texture = {width, height,0,0};
    glGenTextures(1,&texture.id);
    glBindTexture(target,texture.id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glTexImage2D(target, 0, iformat, texture.width, texture.height, 0, format, GL_UNSIGNED_BYTE, buffer);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, minfilter);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, magfilter);
    glGenerateMipmap(target);
    glBindTexture(target,0);
    return texture;
}