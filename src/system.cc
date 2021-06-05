#include "system.h"

SDL_Window *g_window;
SDL_GLContext g_context;

void N_Init(const char *title, i32 width, i32 height, bool fullscreen)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        N_Log("Unable to initialize SDL -> %s\n", SDL_GetError());
        exit(-1);
    }
    g_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
    if (g_window == NULL)
    {
        N_Log("Unable to create Window -> %s\n", SDL_GetError());
        exit(-1);
    }
    g_context = SDL_GL_CreateContext(g_window);
}
void N_Deinit()
{
    SDL_GL_DeleteContext(g_context);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
}

nwindow_t N_CreateWindow(const char *title, i32 width, i32 height, bool fullscreen)
{
    nwindow_t window = {};
    window.width = width;
    window.height = height;
    strcpy(window.title,title);

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        N_Log("Unable to initialize SDL -> %s\n", SDL_GetError());
        return window;
    }
    window.handle = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
    if (window.handle == NULL)
    {
        N_Log("Unable to create Window -> %s\n", SDL_GetError());
        return window;
    }
    window.ctx = SDL_GL_CreateContext(window.handle);
    return window;
}
bool N_WindowShouldClose(nwindow_t window, SDL_Event *event)
{
    return SDL_PollEvent(event) ? (event->type == SDL_QUIT) : false;
}
bool N_WindowSwap(nwindow_t window)
{
    SDL_GL_SwapWindow(window.handle);
}
void N_DestroyWindow(nwindow_t window)
{
    SDL_GL_DeleteContext(window.ctx);
    SDL_DestroyWindow(window.handle);
    SDL_Quit(); //TODO: maybe dont do that if we need more than 1 window ?
}
