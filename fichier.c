
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "fichier.h"

int chargerNiveau(int niveau[][NBRE_BLOCS_HAUTEUR]) {

    FILE* fichier = NULL;

    char ligneFichier[NBRE_BLOCS_LARGEUR * NBRE_BLOCS_HAUTEUR + 1] = {0};
    int i = 0, j = 0;

    fichier = fopen("niveaux.lvl", "r");
    if (fichier == NULL)
        return 0;

    fgets(ligneFichier, NBRE_BLOCS_LARGEUR * NBRE_BLOCS_HAUTEUR + 1, fichier);

    for (i = 0 ; i < NBRE_BLOCS_LARGEUR ; i++) {
        for (j = 0 ; j < NBRE_BLOCS_HAUTEUR ; j++) {
            switch (ligneFichier[(i * NBRE_BLOCS_LARGEUR) + j]) {
                case '0':
                    niveau[j][i] = 0;
                break;
                case '1':
                    niveau[j][i] = 1;
                break;
                case '2':
                    niveau[j][i] = 2;
                break;
                case '3':
                    niveau[j][i] = 3;
                break;
                case '4':
                    niveau[j][i] = 4;
                break;
            }
        }
    }
    fclose(fichier);
    return 1;
}

int sauvegarderNiveau(int niveau[][NBRE_BLOCS_HAUTEUR]) {

    FILE *fichier = NULL;

    int i = 0, j = 0;

    fichier = fopen("niveaux.lvl", "w");
    if(fichier == NULL)
        return 0;

    for(i = 0 ; i < NBRE_BLOCS_LARGEUR ; i++) {
        for (j = 0 ; j < NBRE_BLOCS_HAUTEUR ; j++) {
            fprintf(fichier, "%d", niveau[j][i]);
        }
    }
    fclose(fichier);

    return 1;
}

