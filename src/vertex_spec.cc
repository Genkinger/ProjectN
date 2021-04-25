#include "vertex_spec.h"

void N_SetupVertexData(GLuint vao, GLuint vbo, void *data, i32 size){
    i32 stride = 0;
    i64 currentOffset = 0;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindVertexArray(vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(nvertex_t),(void*)offsetof(nvertex_t,pos));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(nvertex_t),(void*)offsetof(nvertex_t,uv));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}