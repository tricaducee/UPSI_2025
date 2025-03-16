#ifndef PRINCIPAL_H
#define PRINCIPAL_H

// Inclusion des bibliothèques SDL3
#include <SDL.h>           	  // Pour SDL_Window, SDL_Renderer, etc.
#include <SDL_image.h>     // Pour SDL_image (si nécessaire)
#include <SDL_mixer.h>     // Pour Mix_Music (si nécessaire)
#include <SDL_ttf.h>       // Pour SDL_ttf

#include <stdlib.h>
#include <stdio.h>

enum
{
	IMG_CHRISTIAN,
	IMG_EGO,
	IMG_AVIS,
	IMG_TOTAL
};

enum
{
	AUDIO_BASE,
	AUDIO_TOTAL
};

typedef struct windowsList
{
	SDL_Window			*window;     // Fenêtre principale
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	int					id;
	int					pngId;
	int					oggId;
	struct windowsList	*next;
	struct windowsList	*previous;
}						WindowsList;

typedef struct all
{	
	SDL_Renderer		*renderer; // Renderer principal
	Mix_Music			*music;		// Musique du jeu
	//TTF_Font			*font; // Police pour le texte
	//SDL_Texture			*textTexture; // Texture pour le texte "H
	int					windowsCount;
	int					nextWinId;
	int					score;
	SDL_Surface 		*img[IMG_TOTAL];
	WindowsList			*windows;
	WindowsList			*winCursor;
}						All;

extern All	gAll;
extern int	running;

int playMusic(const char *filename);
void stopMusic();
// void text_cleanup();
// void text_render();

#endif
