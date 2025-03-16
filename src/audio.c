#include "principal.h"

int playMusic(const char *filename)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("Erreur d'initialisation de SDL_mixer : %s\n", Mix_GetError());
        return 1;
    }

    Mix_Music *music = Mix_LoadMUS(filename);
    if (!music)
    {
        printf("Erreur de chargement de la musique : %s\n", Mix_GetError());
        Mix_CloseAudio();
        return 1;
    }

    if (Mix_PlayMusic(music, -1) == -1)
    {
        printf("Erreur lors de la lecture de la musique : %s\n", Mix_GetError());
        return 1;
    }
    return 0;
}

void stopMusic()
{
    Mix_HaltMusic();
    Mix_CloseAudio();
    Mix_Quit();
}
