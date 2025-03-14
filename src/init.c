void cleanExit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    //si texture utilisé de SDL_CreateTexture()
    //SDL_DestroyTexture(texture);

    //si surface de SDL_CreateRGBSurface() ou SDL_LoadBMP()
    //SDL_DestroySurface(surface);

    //ferme un périphérique audio ouvert
    //SDL_QuitSubSystem(audioDevice);

    //libère un curseur de SDL_CreateCursor()
    //SDL_FreeCursor(cursor);

    //désactive la saisie de texte de SDL_StartTextInput()
    //SDL_StopTextInput();

    SDL_Quit();
}

int	initSDL()
{
	int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if (result < 0) {
        fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
		cleanExit();
        return 1;
    }

    window = SDL_CreateWindow("SDL3 Multiplatform", 800, 600, 0);
    if (!window) 
    {
        fprintf(stderr, "Erreur fenêtre : %s\n", SDL_GetError());
        cleanExit()
        return 1;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) 
    {
        fprintf(stderr, "Erreur renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        cleanExit();
        return 1;
    }
    return 0;
}