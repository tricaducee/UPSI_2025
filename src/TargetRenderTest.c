#include "principal.h"

SDL_Surface* surface = SDL_LoadBMP("image.bmp");  // Charger une image en surface
SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);  // Convertir en texture
SDL_FreeSurface(surface);  // Libérer la surface, plus nécessaire

SDL_Texture* render_target = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);

SDL_SetRenderTarget(renderer, render_target); // On définit la texture comme cible de rendu

// Dessiner un rectangle rouge sur cette texture
SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
SDL_RenderClear(renderer); // Remplir la texture avec la couleur définie

SDL_SetRenderTarget(renderer, NULL); // Revenir au rendu normal (la fenêtre)

SDL_RenderCopy(renderer, render_target, NULL, NULL);
SDL_RenderPresent(renderer);
