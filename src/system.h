#pragma once
#include <epoxy/gl.h>
#include <SDL2/SDL.h>
#include "types.h"
#include "util.h"

extern SDL_Window *g_window;

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
