#include "principal.h"

All	gAll;
int running;

int initImgs() {
    const char *imgPath[IMG_TOTAL] = {
        [IMG_EGO] = "assets/images/ego.png",
        [IMG_AVIS] = "assets/images/avis.png",
        [IMG_CHRISTIAN] = "assets/images/Christian.png"
    };
    for (int i = 0; i < IMG_TOTAL; i++)
    {
        gAll.img[i] = IMG_Load(imgPath[i]);
        if (!gAll.img[i])
        {
            fprintf(stderr, "Erreur chargement surface (%s) : %s\n",
                    imgPath[i], IMG_GetError());
            for (int j = 0; j < i; j++)
            {
                SDL_FreeSurface(gAll.img[j]);
                gAll.img[j] = NULL;
            }
            printf("coucou\n");
            return (-1);
        }
    }
    return (0);
}

int updateImg(WindowsList *windowList, int newImgID)
{
    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(windowList->renderer, gAll.img[newImgID]);
    if (!newTexture)
        return (-1);
    if (windowList->texture)
        SDL_DestroyTexture(windowList->texture);
    windowList->texture = newTexture;
    //Affiché la texture dans la fenêtre
    SDL_RenderClear(windowList->renderer);
    SDL_RenderCopy(windowList->renderer, windowList->texture, NULL, NULL);
    SDL_RenderPresent(windowList->renderer);
    return (0);
    
}

int initGame() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
        return -1;
    }
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		fprintf(stderr, "Erreur IMG_Init : %s\n", IMG_GetError());
		SDL_Quit();
		return -1;
	}
    if (initImgs())
    {
        fprintf(stderr, "Erreur initImgs : %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return -1;
    }
    SDL_Rect    screen;
    SDL_GetDisplayBounds(0, &screen);
    gAll.screenSize.x = screen.w;
    gAll.screenSize.y = screen.h;
    gAll.windows = NULL;
    gAll.windowsCount = 0;
    gAll.nextWinId = 1;
    gAll.score = 0;
    gAll.time = 0;
    gAll.waitingTime = TIME_TO_WAIT;
    return 0;
}

int destroyAll(int code) {
    gAll.winCursor = gAll.windows;
    WindowsList *tmp;

    while (gAll.winCursor) {
        if (gAll.winCursor->window)
            SDL_DestroyWindow(gAll.winCursor->window);
        if (gAll.winCursor->renderer)
            SDL_DestroyRenderer(gAll.winCursor->renderer);
        if (gAll.winCursor->texture)
            SDL_DestroyTexture(gAll.winCursor->texture);
        tmp = gAll.winCursor;
        gAll.winCursor = gAll.winCursor->next;
        free(tmp);
    }
    for (int i = 0; i < IMG_TOTAL; i++)
        SDL_FreeSurface(gAll.img[i]);
	IMG_Quit();
    SDL_Quit();
	return (code);
}

WindowsList *createWindow(char *windowName, int posX, int posY, int imgID)
{
    SDL_Window *newWindow = SDL_CreateWindow(windowName, posX, posY,
        gAll.img[imgID]->w, gAll.img[imgID]->h, SDL_WINDOW_SHOWN);
    if (!newWindow) {
        fprintf(stderr, "Erreur création fenêtre : %s\n", SDL_GetError());
        return NULL;
    }
    SDL_Renderer *newRenderer = SDL_CreateRenderer(newWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!newRenderer) {
        fprintf(stderr, "Erreur création renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(newWindow);
        return NULL;
    }
    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(newRenderer, gAll.img[imgID]);
    if (!newTexture) {
        fprintf(stderr, "Erreur création texture : %s\n", SDL_GetError());
        SDL_DestroyWindow(newWindow);
        SDL_DestroyRenderer(newRenderer);
        return NULL;
    }
    WindowsList *newWinList = malloc(sizeof(WindowsList));
    if (!newWinList) {
        fprintf(stderr, "Erreur malloc fenêtre list\n");
        SDL_DestroyWindow(newWindow);
        SDL_DestroyRenderer(newRenderer);
        SDL_DestroyTexture(newTexture);
        return NULL;
    }
    newWinList->id = gAll.nextWinId++;
    newWinList->window = newWindow;
    newWinList->renderer = newRenderer;
    newWinList->texture = newTexture;
    newWinList->previous = NULL;
    newWinList->next = gAll.windows;  // Insère en tête
    if (gAll.windows)
    gAll.windows->previous = newWinList;
    gAll.windows = newWinList;
    //Affiché la texture dans la fenêtre
    SDL_RenderClear(newWinList->renderer);
    SDL_RenderCopy(newWinList->renderer, newWinList->texture, NULL, NULL);
    SDL_RenderPresent(newWinList->renderer);
    ++gAll.windowsCount;
    return newWinList;
}

// WindowsList	*createWindow(char *windowName, int posX, int posY, int imgID)
// {
// 	SDL_Window	*newWindow = SDL_CreateWindow(windowName, posX, posY, gAll.img[imgID]->w, gAll.img[imgID]->h, SDL_WINDOW_SHOWN);

// 	if (!newWindow) {
//         fprintf(stderr, "Erreur création fenêtre : %s\n", SDL_GetError());
//         return NULL;
//     }
//     SDL_Renderer *newRenderer = SDL_CreateRenderer(newWindow, -1, SDL_RENDERER_ACCELERATED);
//     if (!newRenderer) {
//         fprintf(stderr, "Erreur création renderer : %s\n", SDL_GetError());
//         SDL_DestroyWindow(newWindow);
//         return NULL;
//     }
//     SDL_Texture *newTexture = SDL_CreateTextureFromSurface(newRenderer, gAll.img[imgID]);
//     if (!newTexture)
//     {
//         fprintf(stderr, "Erreur création texture : %s\n", SDL_GetError());
//         SDL_DestroyWindow(newWindow);
//         SDL_DestroyRenderer(newRenderer);
//         return (NULL);
//     }
// 	WindowsList	*newWinList = malloc(sizeof(WindowsList));
// 	if (!newWinList)
// 	{
// 		fprintf(stderr, "Erreur malloc fenêtre list");
// 		SDL_DestroyWindow(newWindow);
//         SDL_DestroyRenderer(newRenderer);
//         SDL_DestroyTexture(newTexture);
// 		return NULL;
// 	}
// 	newWinList->id = gAll.nextWinId++;
// 	newWinList->window = newWindow;
//     newWinList->renderer = newRenderer;
//     newWinList->texture = newTexture;
//     //Affiché la texture dans la fenêtre
//     SDL_RenderClear(newWinList->renderer);
//     SDL_RenderCopy(newWinList->renderer, newWinList->texture, NULL, NULL);
//     SDL_RenderPresent(newWinList->renderer);
// 	newWinList->previous = NULL;
// 	if (!gAll.windows)
// 		gAll.windows = newWinList;
// 	else
// 	{
// 		gAll.winCursor = gAll.windows;
// 		gAll.windows = newWinList;
// 		gAll.windows->next = gAll.winCursor;
// 	}
// 	++gAll.windowsCount;
// 	return (newWinList);
// }

// Fonction pour récupérer une fenêtre à partir de son SDL_WindowID
WindowsList *getWindowById(Uint32 windowID) {
	gAll.winCursor = gAll.windows;
    while (gAll.winCursor) {
        if (SDL_GetWindowID(gAll.winCursor->window) == windowID)
            return gAll.winCursor;
        gAll.winCursor = gAll.winCursor->next;
    }
    return NULL;
}

void closeWindow(WindowsList *windowElem)
{
    if (!windowElem)
        return;

    // Mise à jour des pointeurs de la liste
    if (windowElem->previous)
        windowElem->previous->next = windowElem->next;
    else
        gAll.windows = windowElem->next;  // Si c'est le premier élément, mettre à jour la tête

    if (windowElem->next)
        windowElem->next->previous = windowElem->previous;

    // Libération des ressources SDL associées
    if (windowElem->window)
        SDL_DestroyWindow(windowElem->window);
    if (windowElem->renderer)
        SDL_DestroyRenderer(windowElem->renderer);
    if (windowElem->texture)
        SDL_DestroyTexture(windowElem->texture);

    --gAll.windowsCount;
    ++gAll.score;

    free(windowElem);
}

int    simpleWindowEvent(SDL_Event *event, WindowsList *eventWindow)
{
    switch (event->type) {
        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_ENTER) {
                updateImg(eventWindow, IMG_EGO);
                // Action spécifique ici
            } else if (event->window.event == SDL_WINDOWEVENT_LEAVE) {
                updateImg(eventWindow, IMG_AVIS);
                // Action spécifique ici
                //closeWindow(eventWindow);
            } else if (event->window.event == SDL_WINDOWEVENT_CLOSE)
                closeWindow(eventWindow);
            break ;
        case SDL_MOUSEBUTTONDOWN:
            closeWindow(eventWindow);
            break ;
    }
    return (0);
}

void    eventWhile(SDL_Event *event)
{
    WindowsList *eventWindow;

    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                running = 0;
                break;

            case SDL_WINDOWEVENT:
            {
                eventWindow = getWindowById(event->window.windowID);
                if (!eventWindow)
                    break;
                simpleWindowEvent(event, eventWindow);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                eventWindow = getWindowById(event->button.windowID);
                if (!eventWindow)
                    break;
                    simpleWindowEvent(event, eventWindow);
                break;
            }
        }
    }
}

int    simpleWindowCreate()
{
    if (!createWindow("www.arnaque.com", rand() % (gAll.screenSize.x - gAll.img[IMG_AVIS]->w), rand() % (gAll.screenSize.y - gAll.img[IMG_AVIS]->h), IMG_AVIS))
        return (-1);
    return (0);
}

int main(void) {

    if (initGame())
        return -1;

    if (simpleWindowCreate())
		return (destroyAll(1));
    running = 1;
    SDL_Event   event;
    Uint32      sdlTick;
    gAll.time = SDL_GetTicks();
    while (running) {
        eventWhile(&event);
        sdlTick = SDL_GetTicks();
        if (sdlTick - gAll.time >= gAll.waitingTime)
        {
            simpleWindowCreate();
            gAll.time = sdlTick;
            if (gAll.waitingTime - ACCELERATION <= MIN_TIME_TO_WAIT)
                gAll.waitingTime = MIN_TIME_TO_WAIT;
            else
                gAll.waitingTime -= ACCELERATION;
        }
        SDL_Delay(16); // ~60 FPS
    }
    return (destroyAll(0));
}
