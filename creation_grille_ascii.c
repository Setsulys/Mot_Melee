#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "creation_grille_ascii.h"
#define TAILLE_MAX 20

char** creation_grille(int taille){
	int i,j;
  char **grille = NULL;

	grille = (char **)malloc(taille*sizeof(char *));
  	for(i=0;i<taille;i++)
  		grille[i]=(char *)malloc(taille*sizeof(char));

	for(i=0; i<taille; i++){
		for(j=0; j<taille; j++){
			grille[i][j] = ' ';
		}
	}
	return grille;
}

void affiche_grille( int taille, char **grille){
	int i, j;
	printf("\n");
	for(i=0;i<taille;i++){
		printf("|");
		for (j=0;j<taille;j++){
			printf(" %c |",grille[i][j]);
		}
		printf("\n");
	}
}

char* selection_mot_crea(int taille, char *mot){
	int i;
	mot = malloc((taille+1)*sizeof(char));
	do{
		printf("Choisir un mot a inserer de longueur maximale %d : \n", taille);
		scanf(" %s", mot);
	}while(strlen(mot)>taille);

	for(i=0; i<taille; i++){
		mot[i] = toupper(mot[i]);
	}
	return mot;
}

char* remplit_grille(char **grille, int taille, char *alphabet){
	int i, j, lettre;
	for(i=0; i<taille; i++){
		for(j=0; j<taille; j++){
			if(grille[i][j] == ' '){
				lettre = rand()%26;
				grille[i][j] = alphabet[lettre];
			}
		}
	}
	return *grille;
}

int choix_position_x(int taille){
	int position_x;

	printf("Choisisez une position en x : \n");
	do{
		scanf(" %d",&position_x);
		if(position_x>=taille || position_x<0)
				printf("Valeur erroné Re-chosisez une position en x : \n");
	}while(position_x>=taille || position_x<0);

	return position_x;
}

int choix_position_y(int taille){
	int position_y;

	printf("Choisisez une position en y : \n");
	do{
		scanf(" %d",&position_y);
		if(position_y>=taille || position_y<0)
				printf("Valeur erroné Re-chosisez une position en y : \n");
	}while(position_y>=taille || position_y<0);
	printf("\n");

	return position_y;
}

int choix_direction(){
	int direction; 

	printf("Choisisez une direction  parmis : \n");
	printf("[Nord-Ouest]:0\n[Nord]:1\n[Nord-Est]:2\n[Ouest]:3\n[Est]:4\n[Sud-Ouest]:5\n[Sud]:6\n[Sud-Est]:7\n");
	printf("Entrez la valeur choisis : ");	
	scanf("%d",&direction);
	printf("\n");

	return direction;
}

char* place_mot_NO(int taille, char **grille, int position_x, int position_y, char *mot, int **verification){/*ok*/
	int i = position_x, j = position_y, p = 0;
	for(p = 0; p<strlen(mot); p++){
		if(i-p>=0 && j-p>=0){
			if(grille[i-p][j-p] != ' ' ){
				printf("--le mot n'a pas pu etre place car il passe sur un autre mot--\n");
				return *grille;
			}
		}
	}
	if(strlen(mot)-2<position_x && strlen(mot)-2<position_y){
		for(p = 0; p<strlen(mot); p++){
			grille[i-p][j-p] = mot[p];
		}
		**verification=1;
	}
	else{
		printf("---!!!Le mot sort de la grille!!!---\n");
	}
	return *grille;
} 

char* place_mot_N(int taille, char **grille, int position_x, int position_y, char *mot,int **verification){/*ok*/
	int i = position_x, j = position_y, p = 0;
	for(p = 0; p<strlen(mot); p++){
		if(i-p>=0){
			if(grille[i-p][j] != ' '){
				printf("--le mot n'a pas pu etre place car il passe sur un autre mot--\n");
				return *grille;
			}
		}
	}
	if(strlen(mot)-2<position_x){
		for(p = 0; p<strlen(mot); p++){
			grille[i-p][j] = mot[p];
		}
		**verification=1;
	}
	else{
		printf("---!!!Le mot sort de la grille!!!---\n");
	}
	return *grille;/*ok*/
}

char* place_mot_NE(int taille, char **grille, int position_x, int position_y, char *mot,int **verification){/*ok*/
	int i = position_x, j = position_y, p = 0;
	for(p = 0; p<strlen(mot); p++){
		if(i-p>=0 && j+p<taille){
			if(grille[i-p][j+p] != ' '){
				printf("--le mot n'a pas pu etre place car il passe sur un autre mot--\n");
				return *grille;
			}
		}
	}
	if(strlen(mot)-2<position_x ||strlen(mot)-2/*-1*/ + position_x< taille){
		for(p = 0; p<strlen(mot); p++){
			grille[i-p][j+p] = mot[p];
		}
		**verification=1;
	}
	else{
		printf("---!!!Le mot sort de la grille!!!---\n");
	}
	return *grille;
}

char* place_mot_O(int taille, char **grille, int position_x, int position_y, char *mot, int **verification){/*ok*/
	int i = position_x, j = position_y, p = 0;
	for(p = 0; p<strlen(mot); p++){
		if(j-p>=0){
			if(grille[i][j-p] != ' '){
				printf("--le mot n'a pas pu etre place car il passe sur un autre mot--\n");
				return *grille;
			}
		}
	}
	if(strlen(mot)-2<position_y){
		for(p = 0; p<strlen(mot); p++){
			grille[i][j-p] = mot[p];
		}
		**verification=1;
	}
	else{
		printf("---!!!Le mot sort de la grille!!!---\n\n");
	}
	return *grille;/*ok*/
}

char* place_mot_E(int taille, char **grille, int position_x, int position_y, char *mot, int **verification){/*ok*/
	int i = position_x, j = position_y, p = 0;
	for(p = 0; p<strlen(mot); p++){
		if(j+p<taille){
			if(grille[i][j+p] != ' '){
				printf("--le mot n'a pas pu etre place car il passe sur un autre mot--\n");
				return *grille;
			}
		}
	}
	if(strlen(mot)-1+position_y<taille){
		for(p = 0; p<strlen(mot); p++){
			grille[i][j+p] = mot[p];
		}
		**verification=1;
	}
	else{
		printf("---!!!Le mot sort de la grille!!!---\n");
	}
	return *grille;
}

char* place_mot_SO(int taille, char **grille, int position_x, int position_y, char *mot, int **verification){/*ok*/
	int i = position_x, j = position_y, p = 0;
	for(p = 0; p<strlen(mot); p++){
		if(i+p<taille && j-p>=0){
			if(grille[i+p][j-p] != ' '){
				printf("--le mot n'a pas pu etre place car il passe sur un autre mot--\n");
				return *grille;
			}
		}
	}
	if(strlen(mot)-2<position_y && strlen(mot)-1+position_x<taille){
		for(p = 0; p<strlen(mot); p++){
			grille[i+p][j-p] = mot[p];
		}
		**verification=1;
	}
	else{
		printf("---!!!Le mot sort de la grille!!!---\n");
	}
	return *grille;
}

char* place_mot_S(int taille, char **grille, int position_x, int position_y, char *mot, int **verification){/*ok*/
	int i = position_x, j = position_y, p = 0;
	for(p = 0; p<strlen(mot); p++){
		if(i+p<taille){
			if(grille[i+p][j] != ' '){
				printf("--le mot n'a pas pu etre place car il passe sur un autre mot--\n");
				return *grille;
			}
		}
	}
	if(strlen(mot)-1+position_x<taille){
		for(p = 0; p<strlen(mot); p++){
			grille[i+p][j] = mot[p];
		}
		**verification=1;
	}
	else{
		printf("---!!!Le mot sort de la grille!!!---\n");
	}
	return *grille;
}

char* place_mot_SE(int taille, char **grille, int position_x, int position_y, char *mot,int **verification){/*ok*/
	int i = position_x, j = position_y, p = 0;
	for(p = 0; p<strlen(mot); p++){
		if(i+p<taille && j+p<taille){
			if(grille[i+p][j+p] != ' '){
				printf("--le mot n'a pas pu etre place car il passe sur un autre mot--\n");
				return *grille;
			}
		}
	}
	if(strlen(mot)-1+position_x<taille && strlen(mot)-1+position_y<taille){
		for(p = 0; p<strlen(mot); p++){
			grille[i+p][j+p] = mot[p];
		}
		**verification=1;
	}
	else{
		printf("---!!!Le mot sort de la grille!!!---\n");
	}
	return *grille;
}


int place_mot(int taille ,char **grille, int position_x, int position_y, int direction, char *mot, int *verification){

	switch(direction){
		case 0 : 
			*grille = place_mot_NO(taille, grille, position_x, position_y, mot,&verification);
			break;
		case 1 : 
			*grille = place_mot_N(taille, grille, position_x, position_y, mot,&verification); 
			break;
		case 2 : 
			*grille = place_mot_NE(taille, grille, position_x, position_y, mot,&verification);
			break;
		case 3 : 
			*grille = place_mot_O(taille, grille, position_x, position_y, mot,&verification);
			break;
		case 4 : 
			*grille = place_mot_E(taille, grille, position_x, position_y, mot,&verification);
			break;
		case 5 : 
			*grille = place_mot_SO(taille, grille, position_x, position_y, mot,&verification);
			break;
		case 6 : 
			*grille = place_mot_S(taille, grille, position_x, position_y, mot,&verification);
			break;
		case 7 : 
			*grille = place_mot_SE(taille, grille, position_x, position_y, mot,&verification);
			break;
	}
	return 1;
}

void copie_grille(char **grille, char **tab_mot, int taille){
	int i, j;
	for(i=0; i<taille; i++){
		for(j=0; j<taille; j++){
			tab_mot[i][j] = grille[i][j];
		}
	}
}


int sauvegarde_fichier(FILE* fichier, char **dico, char **grille, int compteur_mot, int taille){
	int i, j;
	fprintf(fichier, "TAILLE : %d\n", taille);
	fprintf(fichier, "NOMBRE DE MOTS : +%d\n", compteur_mot);
	fprintf(fichier, "MOTS : $");
	for(i = 0; i<compteur_mot; i++){
		fprintf(fichier, "%s ", dico[i]);
	}

	fprintf(fichier, "\nGRILLE :*\n");
	for(i=0; i<taille; i++){
		for(j=0; j<taille; j++){
			fprintf(fichier, "%c", tolower(grille[i][j]));
		}
		fprintf(fichier,"\n");
	}
	return 0;
}

int main(int argc, char const *argv[]){
	/* les variables */
	FILE* fichier = NULL;
	int taille, position_x, position_y, direction, compteur_mot = 0;
	char *mot = NULL;
	char **grille = NULL;
	char **tab_mot = NULL;
	char **dico = NULL;
	char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}; /*alphabet pour remplir les cases vides de la grille*/
	int verfication;
	srand(time(NULL));
	fichier = fopen("mot9.txt","w");

	printf("Entrez une taille de grille souhaité, \n");
	printf("cette taille sera le nombre maximum de mots a inserer : ");
	scanf("%d",&taille);
	
	grille = creation_grille(taille); /* grille de depart*/
	tab_mot = creation_grille(taille);
	dico = (char **)malloc(taille*sizeof(char *));

	affiche_grille(taille, grille);

	printf("Lorsque vous ne voudrez plus entrer de mots taper '-1'.\n");
	
	do{
		verfication=0;
		mot = selection_mot_crea(taille, mot);
		if(mot[0] == '-' && mot[1] == '1') break;

		position_x = choix_position_x(taille);
		position_y = choix_position_y(taille);
		direction = choix_direction();
		

		if(place_mot(taille, grille, position_x, position_y, direction, mot, &verfication));
		if(verfication==1)
			dico[compteur_mot] = mot;
		else
			compteur_mot--;
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
	sauvegarde_fichier(fichier, dico, grille, compteur_mot, taille);
	return 0;
}
