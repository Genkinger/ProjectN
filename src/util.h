#pragma once
#include "types.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

char *N_LoadTextFile(const char* path, i32 *size);
void N_FreeTextFile(char* text);

void N_Log(const char* format...);
void N_Error(const char* format...);
void N_Warn(const char* format...);