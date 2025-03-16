#ifndef PRINCIPAL_H
#define PRINCIPAL_H

// Inclusion des bibliothèques SDL3
#include <SDL.h>           	  // Pour SDL_Window, SDL_Renderer, etc.
#include <SDL_image.h>     // Pour SDL_image (si nécessaire)
#include <SDL_mixer.h>     // Pour Mix_Music (si nécessaire)
#include <SDL_ttf.h>       // Pour SDL_ttf

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

# define TIME_TO_WAIT 2000
# define ACCELERATION 10
# define MIN_TIME_TO_WAIT 200
# define WINDOWS_COUNT_END 10

enum
{
	F_SIMPLE,
	F_CHRISTIAN,
	F_YAMETE,
	F_GOAT,
	F_TOTAL
};

enum
{
	IMG_CHRISTIAN,
	IMG_EGO,
	IMG_AVIS,
	IMG_GAMEOVER,
	IMG_YAMETE1,
	IMG_YAMETE2,
	IMG_GOAT1,
	IMG_GOAT2,
	IMG_TOTAL
};

enum
{
	AUDIO_BASE,
	AUDIO_TOTAL
};

typedef struct coor
{
	int	x;
	int	y;
}		Coor;

typedef struct windowsList
{
	SDL_Window			*window;     // Fenêtre principale
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	Mix_Chunk			*audio1;
	Mix_Chunk			*audio2;
	int					id;
	int					funcID;
	int					pngId;
	struct windowsList	*next;
	struct windowsList	*previous;
}						WindowsList;

int	simpleWindowCreate();
int	simpleWindowEvent(SDL_Event *event, WindowsList *eventWindow);
int christianWindowCreate();
int	christianWindowEvent(SDL_Event *event, WindowsList *eventWindow);
int yameteWindowCreate();
int	yameteWindowEvent(SDL_Event *event, WindowsList *eventWindow);
int goatWindowCreate();
int	goatWindowEvent(SDL_Event *event, WindowsList *eventWindow);

typedef struct all
{	
	SDL_Renderer		*renderer; // Renderer principal
	Mix_Music			*music;		// Musique du jeu
	//TTF_Font			*font; // Police pour le texte
	//SDL_Texture			*textTexture; // Texture pour le texte "H
	int					windowsCount;
	int					nextWinId;
	int					score;
	Coor				screenSize;
	Uint32				time;
	Uint32				waitingTime;
	int 				(*newWindow[F_TOTAL])();
	int 				(*eventWindow[F_TOTAL])(SDL_Event *, WindowsList *);
	SDL_Surface 		*img[IMG_TOTAL];
	WindowsList			*windows;
	WindowsList			*winCursor;
}						All;

extern All	gAll;
extern int	running;

// void text_cleanup();
// void text_render();

#endif
