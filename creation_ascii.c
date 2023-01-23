#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "creation_grille_ascii.h"
#define TAILLE_MAX 20

int main(int argc, char const *argv[]){
	/* les variables */

	int taille, position_x, position_y, direction, compteur_mot = 0;
	char *mot = NULL;
	char ** grille = NULL;
	char **tab_mot = NULL;
	char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; /*alphabet pour remplir les cases vides de la grille*/
	srand(time(NULL));

	printf("Entrez une taille de grille souhaité, \n");
	printf("cette taille sera le nombre maximum de mots a inserer : ");
	scanf("%d",&taille);
	
	grille = creation_grille(taille, grille); /* grille de depart*/
	affiche_grille(taille, grille);
	tab_mot = creation_grille(taille, tab_mot);

	printf("Lorsque vous ne voudrez plus entrer de mots taper '-1'.\n");

	do{
		mot = selection_mot(taille, mot);
		if(mot[0] == '-' && mot[1] == '1') break;

		position_x = choix_position_x(taille);
		position_y = choix_position_y(taille);
		direction = choix_direction();
		
		place_mot(taille, grille, position_x, position_y, direction, mot);

		printf("Etat de la grille : \n");
		affiche_grille(taille, grille);

		compteur_mot++;
	}while(compteur_mot != taille);

	if(compteur_mot != taille)
		printf("\n\n\nVous avez decide d'arreter la saisie voici la grille complète : \n");
	else
		printf("Voici la grille finale que vous avez construite : \n");
	
	copie_grille(grille, tab_mot, taille);
	remplit_grille(grille, taille, alphabet);
	affiche_grille(taille, grille);
	printf("\nLa grille de comparaison\n");
	affiche_grille(taille, tab_mot);

	return 0;
}
