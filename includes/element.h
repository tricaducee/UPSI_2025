#ifndef ELEMENT_H
# define ELEMENT_H
# include <SDL.h>

typedef struct coor
{
    int x;
    int y;
}       Coor;

typedef struct {
    Coor position;  // Position globale dans la map infinie
    Coor size;      // Taille
    Coor hitPos;    // Coordonnées de la hitbox (relative à x, y)
    Coor hitSize;   // Taille de la hitbox
    SDL_Texture *texture;   // Image de l'élément
}               Element;

#endif