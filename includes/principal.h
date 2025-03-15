#ifndef PRINCIPAL_H
#define PRINCIPAL_H

// Inclusion des bibliothèques SDL3
#include <SDL.h>           	  // Pour SDL_Window, SDL_Renderer, etc.
#include <SDL_image.h>     // Pour SDL_image (si nécessaire)
#include <SDL_mixer.h>     // Pour Mix_Music (si nécessaire)

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <stdlib.h>
#include <stdio.h>

//#include "assets.h"
#include "element.h"
// Inclusion des headers internes du projet

typedef struct all
{
	SDL_Window		*window;     // Fenêtre principale
	SDL_Renderer	*renderer; // Renderer principal
	Mix_Music		*music;		// Musique du jeu
	Coor			camera;
	Element			*plan1;
	Element			player;		
}					All;

extern All gAll;

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600

#endif
