/*

*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "jeux.h"

int main(int argc, char *argv[]) {

    SDL_Surface *screen = NULL;
    SDL_Surface *home = NULL;
    SDL_Rect positionHome;
    SDL_Event event;

    int wait = 1;

    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "impossible de charger la sdl : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetIcon(IMG_Load("mur.jpg"), NULL);
    SDL_WM_SetCaption("MARIO SOKOBAN", NULL);

    screen = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if(screen == NULL) {
        fprintf(stderr, "impossible demarer la fenetre : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    Uint32 black = SDL_MapRGB(screen->format, 0, 0, 0);

    home = IMG_Load("menu.jpg");
    positionHome.x = 0;
    positionHome.y = 0;

    while(wait) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT :
                wait = 0;
            break;
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE :
                        wait = 0;
                    break;
                    case SDLK_KP1 :
                        jouer(screen);
                    break;
                    case SDLK_KP2 :
                        wait = 0;
                    break;
                }
            break;
        }
        SDL_FillRect(screen, NULL, black);
        SDL_BlitSurface(home, NULL, screen, &positionHome);
        SDL_Flip(screen);
    }
    SDL_Quit();
    return EXIT_SUCCESS;
}
