#include "principal.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

All gAll;
int running = 1;

// Fonction pour gérer une frame du rendu
void main_loop(void)
{
    SDL_Event event;

    // Gestion des événements
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = 0;

            #ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
            #endif
        }
    }

    // Définition de la couleur rouge
    SDL_SetRenderDrawColor(gAll.renderer, 255, 0, 0, 255);

    // Nettoyage de l'écran avec la couleur définie
    SDL_RenderClear(gAll.renderer);

    // Mise à jour de l'affichage
    SDL_RenderPresent(gAll.renderer);
}

int main(int argc, char *argv[])
{
    // Initialisation de la SDL (vidéo uniquement)
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Erreur SDL_Init : %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre
    gAll.window = SDL_CreateWindow(
        "Fenêtre Rouge SDL2 (Emscripten Compatible)",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    if (gAll.window == NULL)
    {
        printf("Erreur SDL_CreateWindow : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création du gAll.renderer
    gAll.renderer = SDL_CreateRenderer(gAll.window, -1, SDL_RENDERER_ACCELERATED);
    if (gAll.renderer == NULL)
    {
        printf("Erreur SDL_CreateRenderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(gAll.window);
        SDL_Quit();
        return 1;
    }

    #ifdef __EMSCRIPTEN__
    // Boucle principale via emscripten (pour web)
    emscripten_set_main_loop(main_loop, 0, 1);
    #else
    // Boucle principale classique (Mac, Linux, Windows)
    while (running)
    {
        main_loop();
        SDL_Delay(16); // ~60 FPS
    }
    #endif

    // Libération des ressources
    SDL_DestroyRenderer(gAll.renderer);
    SDL_DestroyWindow(gAll.window);
    SDL_Quit();

    return 0;
}
