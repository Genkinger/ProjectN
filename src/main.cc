#include "system.h"
#include "shader.h"
#include "texture.h"
#include "text.h"
#include "font_basic.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WIDTH 800
#define HEIGHT 800

i32 main(i32 argc, char **argv)
{
    nwindow_t win = N_CreateWindow("Window",WIDTH,HEIGHT);
    nshader_t prog = N_LoadShaderFromFile("../res/quad.vert", "../res/quad.frag");
    u32 vao,vbo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    const char* str = argv[1];
    i32 len = strlen(str);
    nquad_t glyph[len];

    N_GenerateStringQuads(str,FONT8X8BASIC_LENGTH,glyph);
    N_SetupVertexData(vao,vbo,(void*)glyph,sizeof(glyph));
    
    ntexture_t tex = N_PackGlyphs(FONT8X8BASIC_LENGTH,font8x8_basic);
    glm::mat4 mvp = glm::scale(glm::mat4(1.0f),glm::vec3(0.03));
    SDL_Event event;
    while(!N_WindowShouldClose(win,&event)){
        if(event.type == SDL_KEYDOWN){
            if(!event.key.repeat){         
                printf("%c\n",event.key.keysym.sym);
            }
        }
        glViewport(0, 0, win.width, win.height);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(prog.id);
        glUniform1i(glGetUniformLocation(prog.id, "sam"), 0);
        glUniformMatrix4fv(glGetUniformLocation(prog.id, "mvp"),1,GL_FALSE,glm::value_ptr(mvp));
        glBindVertexArray(vao);
        glBindTexture(GL_TEXTURE_2D, tex.id);
        glDrawArrays(GL_QUADS, 0, 4*len);
        N_WindowSwap(win);
    }

    N_DestroyWindow(win);
    return 0;
}