#include "util.h"

char *N_LoadTextFile(const char* path, i32* size){
    FILE *fd = fopen(path, "rt");
    fseek(fd, 0, SEEK_END);
    *size = ftell(fd);
    char *buffer = new char[*size + 1];
    rewind(fd);
    fread(buffer, 1, *size, fd);
    buffer[*size] = '\0';
    fclose(fd);
    return buffer;
}

void N_FreeTextFile(char* text){
    delete[] text;
}

void N_Log(const char* format...){
    va_list args;
    va_start(args,format);
    const char* tag = "[INFO]: %s";
    size_t fmtlen = strlen(format);
    size_t taglen = strlen(tag);
    char buffer[fmtlen+taglen];
    sprintf(buffer,tag,format);
    vfprintf(stdout,buffer,args);
    va_end(args);
}

void N_Warn(const char* format...){
    va_list args;
    va_start(args,format);
    const char* tag = "[WARNING]: %s";
    size_t fmtlen = strlen(format);
    size_t taglen = strlen(tag);
    char buffer[fmtlen+taglen];
    sprintf(buffer,tag,format);
    vfprintf(stdout,buffer,args);
    va_end(args);
}

void N_Error(const char* format...){
    va_list args;
    va_start(args,format);
    const char* tag = "[ERROR]: %s";
    size_t fmtlen = strlen(format);
    size_t taglen = strlen(tag);
    char buffer[fmtlen+taglen];
    sprintf(buffer,tag,format);
    vfprintf(stderr,buffer,args);
    va_end(args);
}