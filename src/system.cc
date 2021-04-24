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