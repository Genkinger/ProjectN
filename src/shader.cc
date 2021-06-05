#include "shader.h"

bool N_CompileShader(GLuint shader, const char* name){
    i32 compiled;

    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    
    if (compiled == GL_FALSE)
    {
        i32 max_len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_len);
        char log[max_len];
        glGetShaderInfoLog(shader, max_len, &max_len, log);
        N_Warn("SHADER COMPILATION ERROR (%s)\n%s", name, log);
        return false;
    }
    return true;
}

nshader_t N_LoadShaderFromFile(const char* vertex_path, const char* fragment_path){
    i32 vertex_size, fragment_size;
    char *vertex_buffer = N_LoadTextFile(vertex_path, &vertex_size);
    char *fragment_buffer = N_LoadTextFile(fragment_path, &fragment_size);

    nshader_t s = N_LoadShaderFromMemory(vertex_buffer,fragment_buffer,vertex_path,fragment_path);
    
    N_FreeTextFile(vertex_buffer);
    N_FreeTextFile(fragment_buffer);
    return s;
}

nshader_t N_LoadShaderFromMemory(const char* vertex_source, const char* fragment_source, const char* vertex_name, const char* fragment_name){

    u32 vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    u32 fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex_shader, 1, (const char **)(&vertex_source), 0);
    glShaderSource(fragment_shader, 1, (const char **)(&fragment_source), 0);
    
    bool vertex_success = N_CompileShader(vertex_shader, vertex_name);
    bool fragment_success = N_CompileShader(fragment_shader, fragment_name);
    
    if (!vertex_success || !fragment_success)
    {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return (nshader_t){0};
    }

    u32 program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    i32 linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE)
    {
        i32 max_len = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_len);
        char log[max_len];
        glGetProgramInfoLog(program, max_len, &max_len, log);
        N_Warn("PROGRAM LINK ERROR\n%s", log);
        glDeleteProgram(program);
        return (nshader_t){0};
    }

    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    nshader_t s = {program};
    return s;
}