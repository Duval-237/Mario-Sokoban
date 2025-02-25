/*


*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "jeux.h"

void deplacer_joueur(int map[][NBRE_BLOCS_HAUTEUR], SDL_Rect *pos, int direction);

void jouer(SDL_Surface *screen) {

    SDL_Surface *mario[4] = {NULL};
    SDL_Surface *caisse = NULL, *mur = NULL, *objectif = NULL,
                *caisse_ok = NULL, *mario_actuel = NULL;
    SDL_Rect position, position_joueur;
    SDL_Event event;

    int wait = 1, j = 0, i = 0, objectif_restant = 0;
    int map[NBRE_BLOCS_LARGEUR][NBRE_BLOCS_HAUTEUR] = {0};

    mario[HAUT] = IMG_Load("mario_haut.gif");
    mario[BAS] = IMG_Load("mario_bas.gif");
    mario[GAUCHE] = IMG_Load("mario_gauche.gif");
    mario[DROITE] = IMG_Load("mario_droite.gif");
    caisse = IMG_Load("caisse.jpg");
    caisse_ok = IMG_Load("caisse_ok.jpg");
    objectif = IMG_Load("objectif.png");
    mur = IMG_Load("mur.jpg");

    mario_actuel = mario[BAS];

    if (!chargerNiveau(map))
        exit(EXIT_FAILURE);

    for(i = 0; i < NBRE_BLOCS_LARGEUR; i++) {
        for(j = 0; j < NBRE_BLOCS_HAUTEUR; j++) {
            if(map[i][j] == MARIO) {
                position_joueur.x = i;
                position_joueur.y = j;
                map[i][j] = VIDE;
            }
        }
    }
    SDL_EnableKeyRepeat(100, 100);

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
                    case SDLK_UP :
                        mario_actuel = mario[HAUT];
                        deplacer_joueur(map, &position_joueur, HAUT);
                    break;
                    case SDLK_DOWN :
                        mario_actuel = mario[BAS];
                        deplacer_joueur(map, &position_joueur,  BAS);
                    break;
                    case SDLK_LEFT :
                        mario_actuel = mario[GAUCHE];
                        deplacer_joueur(map, &position_joueur, GAUCHE);
                    break;
                    case SDLK_RIGHT :
                        mario_actuel = mario[DROITE];
                        deplacer_joueur(map, &position_joueur, DROITE);
                    break;
                }
            break;
        }
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

        objectif_restant = 0;

        for(i = 0; i < NBRE_BLOCS_LARGEUR; i++) {
            for(j = 0; j < NBRE_BLOCS_HAUTEUR; j++) {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(map[i][j]) {
                    case MUR :
                        SDL_BlitSurface(mur, NULL, screen, &position);
                    break;
                    case CAISSE :
                        SDL_BlitSurface(caisse, NULL, screen, &position);
                    break;
                    case CAISSE_OK :
                        SDL_BlitSurface(caisse_ok, NULL, screen, &position);
                    break;
                    case OBJECTIF :
                        SDL_BlitSurface(objectif, NULL, screen, &position);
                        objectif_restant = 1;
                    break;
                }
            }
        }
        if(!objectif_restant)
            wait = 0;

        position.x = position_joueur.x * TAILLE_BLOC;
        position.y = position_joueur.y * TAILLE_BLOC;
        SDL_BlitSurface(mario_actuel, NULL, screen, &position);

        SDL_Flip(screen);
    }

    SDL_EnableKeyRepeat(0, 0);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(caisse_ok);
    SDL_FreeSurface(objectif);

    for(i = 0; i < 4; i++)
        SDL_FreeSurface(mario[i]);
}
void deplacer_joueur(int map[][NBRE_BLOCS_HAUTEUR], SDL_Rect *pos, int direction){
    switch(direction) {
        case HAUT :
            if(pos->y - 1 < 0)
                break;
            if(map[pos->x][pos->y] == MUR)
                break;
            if((map[pos->x][pos->y - 1] == CAISSE  || map[pos->x][pos->y -1] == CAISSE_OK) && (pos->y - 2 < 0 || map[pos->x][pos->y - 2] == MUR ||
            map[pos->x][pos->y - 2] == CAISSE || map[pos->x][pos->y - 2] == CAISSE_OK))
                break;

            deplacerCaisse(&map[pos->x][pos->y - 1], &map[pos->x][pos->y - 2]);

            pos->y--;
        break;

         case BAS:
            if (pos->y + 1 >= NBRE_BLOCS_HAUTEUR)
                break;
            if (map[pos->x][pos->y + 1] == MUR)
                break;
            if ((map[pos->x][pos->y + 1] == CAISSE || map[pos->x][pos->y + 1] == CAISSE_OK) &&
                (pos->y + 2 >= NBRE_BLOCS_HAUTEUR || map[pos->x][pos->y + 2] == MUR ||
                map[pos->x][pos->y + 2] == CAISSE || map[pos->x][pos->y + 2] == CAISSE_OK))
                break;

            deplacerCaisse(&map[pos->x][pos->y + 1], &map[pos->x][pos->y + 2]);

            pos->y++;
        break;
        case GAUCHE:
            if (pos->x - 1 < 0)
                break;
            if (map[pos->x - 1][pos->y] == MUR)
                break;

            if ((map[pos->x - 1][pos->y] == CAISSE || map[pos->x - 1][pos->y] == CAISSE_OK) &&
                (pos->x - 2 < 0 || map[pos->x - 2][pos->y] == MUR ||
                map[pos->x - 2][pos->y] == CAISSE || map[pos->x - 2][pos->y] == CAISSE_OK))
                break;


            deplacerCaisse(&map[pos->x - 1][pos->y], &map[pos->x - 2][pos->y]);

            pos->x--;
        break;
        case DROITE:
            if (pos->x + 1 >= NBRE_BLOCS_LARGEUR)
                break;
            if (map[pos->x + 1][pos->y] == MUR)
                break;

            if ((map[pos->x + 1][pos->y] == CAISSE || map[pos->x + 1][pos->y] == CAISSE_OK) &&
                (pos->x + 2 >= NBRE_BLOCS_LARGEUR || map[pos->x + 2][pos->y] == MUR ||
                map[pos->x + 2][pos->y] == CAISSE || map[pos->x + 2][pos->y] == CAISSE_OK))
                break;

            deplacerCaisse(&map[pos->x + 1][pos->y], &map[pos->x + 2][pos->y]);

            pos->x++;
        break;


    }
}
void deplacerCaisse(int *premiereCase, int *secondeCase) {
    if (*premiereCase == CAISSE || *premiereCase == CAISSE_OK) {
        if (*secondeCase == OBJECTIF)
            *secondeCase = CAISSE_OK;
        else
            *secondeCase = CAISSE;
        if (*premiereCase == CAISSE_OK)
            *premiereCase = OBJECTIF;
        else
            *premiereCase = VIDE;
    }
}


