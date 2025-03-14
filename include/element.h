#ifndef ELEMENT_H
#define ELEMENT_H

typedef struct {
    int x, y;               // Position globale dans la map infinie
    int w, h;               // Taille
    int hitboxX, hitboxY;   // Coordonnées de la hitbox (relative à x, y)
    int hitboxW, hitboxH;   // Taille de la hitbox
    int zIndex;             // Ordre d’affichage
    SDL_Texture *texture;   // Image de l'élément
} Element;



#endif