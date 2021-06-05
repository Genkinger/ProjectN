#pragma once
#include <epoxy/gl.h>
#include <SDL2/SDL.h>
#include "types.h"
#include "util.h"
#define N_MAX_TITLE_LENGTH 256

extern SDL_Window *g_window;


typedef struct nwindow_s{
    char title[N_MAX_TITLE_LENGTH];
    i32 width;
    i32 height;
    SDL_Window *handle;
    SDL_GLContext ctx;
} nwindow_t;

void N_Init(const char* title, i32 width, i32 height, bool fullscreen = false);
void N_Deinit();

template<typename F>
void N_Loop(F function){
        SDL_Event event;
        while (true)
        {
            if (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    break;
                }
            }
            function(0);
            SDL_GL_SwapWindow(g_window);
        }
}


nwindow_t N_CreateWindow(const char* title, i32 width, i32 height, bool fullscreen = false);
bool N_WindowShouldClose(nwindow_t window, SDL_Event *event);
bool N_WindowSwap(nwindow_t window);
void N_DestroyWindow(nwindow_t window);
