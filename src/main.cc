#include "system.h"
#include "shader.h"
#include "texture.h"
#include "text.h"
#include "font_basic.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WIDTH 1920
#define HEIGHT 1080

void N_SetupVertexData(GLuint vao, GLuint vbo,u8 *components,i32 count, r32 *data, i32 size){
    i32 stride = 0;
    i64 currentOffset = 0;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    for(i32 i = 0; i < count; i++){
        stride += components[i]*sizeof(r32);
    }
    glBindVertexArray(vao);
    for(i32 i = 0; i < count; i++){
        glVertexAttribPointer(i, components[i], GL_FLOAT, GL_FALSE, stride, (void*)currentOffset);
        currentOffset += sizeof(r32)*components[i];
        glEnableVertexAttribArray(i);
    }
    glBindVertexArray(0);
}

i32 main(i32 argc, char **argv)
{
    N_Init("Window", WIDTH, HEIGHT);
    shader_t prog = N_LoadShaderFromFile("../res/quad.vert", "../res/quad.frag");
    u32 vao,vbo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    const char* str = argv[1];
    i32 len = strlen(str);
    r32 glyph[20*len];
    
    N_GenerateStringQuads(str,128,glyph);
    
    u8 components[] = {3,2};
    N_SetupVertexData(vao,vbo,components,2,glyph,sizeof(glyph));
    
    texture_t tex = N_PackGlyphs(128,font8x8_basic);
    
    auto mvp = glm::translate(glm::scale(glm::mat4(1.0f),glm::vec3(0.03)),glm::vec3(-8,0,0));
    N_Loop([&](float delta) {
        glViewport(0, 0, WIDTH, HEIGHT);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(prog.id);
        glUniform1i(glGetUniformLocation(prog.id, "sam"), 0);
        glUniformMatrix4fv(glGetUniformLocation(prog.id, "mvp"),1,GL_FALSE,glm::value_ptr(mvp));
        glBindVertexArray(vao);
        glBindTexture(GL_TEXTURE_2D, tex.id);
        glDrawArrays(GL_QUADS, 0, 4*len);
    });

    N_Deinit();
    return 0;
}