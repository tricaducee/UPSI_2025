#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

// Déclaration UNIQUE des variables globales (important)
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool running = true;

void main_loop(void) {
    SDL_Event event;

    while (SDL_PokllEvent(&event)) 
    {
        if (event.type == SDL_EVENT_QUIT ||
            event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
            running = false;
            #ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
            #endif
        }
    }

    SDL_SetRenderDrawColor(renderer, 50, 50, 200, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
    if (initSDL())
        return 1;

    running = true;

    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(main_loop, 0, true);
    #else
        while (running) {
            main_loop();
            SDL_Delay(16); // ~60 FPS
        }

        cleanExit();
    #endif

    return 0;
}
