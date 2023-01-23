#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "jeu_ascii.h"
#define TAILLE_MAX 20

/*---------------forme le nom du fichier en fct de la taille -----------------------*/

char* recup_nom_fichier(int taille){
	char *fich=NULL;

	sprintf(fich, "mot%d.txt", taille);

	return fich;
}

/*-----------------fonctions de creation,affichage,remplissage
----------------------------des objets necessaires---------------------------------*/

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

char** creation_dico(int taille){
	int i;
  char **dico_mot = NULL;

	dico_mot = (char **)malloc(taille*sizeof(char *));
  	for(i=0;i<taille;i++)
  		dico_mot[i]=(char *)malloc(taille*sizeof(char));

	return dico_mot;
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

/*-----------------se deplacer dans le fichier ---------------------*/

void avance_mot(FILE* fichier){
  char lettre;
  while((lettre = fgetc(fichier)) != '$');
}

void avance_grille(FILE* fichier){
  char lettre;
  while((lettre = fgetc(fichier)) != '*');
}

void avance_cpt_mot(FILE* fichier){
  char lettre;
  while((lettre = fgetc(fichier)) != '+');
}

/*------------remplir la grille avec les lettres de la grille precedemment cree ---------------*/

void remplit_grille(char **grille, int taille, FILE* fichier){
	int i, j;
  char lettre;
	avance_grille(fichier);
  for(i=0; i<taille; i++){
		for(j=0; j<taille; j++){
      lettre = fgetc(fichier);
      if(lettre == EOF) return;
      if(lettre == '\n') lettre = fgetc(fichier);
      grille[i][j] = lettre;
		}
	}
}

int selection_nb_mot(FILE* fichier){
  int lettre;
  avance_cpt_mot(fichier);
  lettre = fgetc(fichier);

  return lettre-48;
}

/*---------------------------recuperer les mots du fichier ----------------------------*/

char* selection_mot(int taille, FILE* fichier){
	char *mot = NULL;
  char carac;  
  int i = 0;
	mot = (char *)malloc(taille+1*sizeof(char));

  while((carac = fgetc(fichier)) != ' '){
    mot[i] = carac;
    i++;
  }
  return mot;
}

char *mot_repere(int taille){
    char *chaine = NULL;
    chaine = (char*)malloc(taille+1*sizeof(char));

    do{
        scanf(" %s", chaine);
    }while(strlen(chaine) > taille);
   
    return chaine;
}

int coord_mot_repere_debut(){
    int coord = 0;
    printf("A quelle coordonne avez vous vu votre mot ? ");
    scanf("%d", &coord);

    return coord;
}

int coord_mot_repere_fin(){
    int coord = 0;
    printf("A quelle coordonne avez vous vu la fin de votre mot ? ");
    scanf("%d", &coord);

    return coord;
}

int cherche_dico(char **dico_mot, char *mot, int taille){
  int i, j;
  int cpt = strlen(mot)-1;
  int cmp = 0;
  for(i=0; i<taille; i++){
    for(j=0; j<taille; j++){
      if(dico_mot[i][j] == mot[i]){
        cmp++;
      }
    }
  }
  if(cmp == cpt) return 1; /*mot trouve*/
  
  return 0; /*mot pas trouve*/
}

/*------------------------------main de la partie jeu--------------------------------*/

int main(int argc, char const *argv[]){
	/* les variables */

	FILE* fichier = NULL;
	char **grille = NULL;
	char **dico_mot = NULL;
	char *nom_fichier = NULL;
	int taille=0/*, coord_x0, coord_y0, coord_x1, coord_y1*/;
	int nbre_mot = 0;
  char *mot = NULL;
  int i;

	printf("Quelle taille de grille souhaitez vous ? \n");
	scanf(" %d", &taille);

	nom_fichier ="mot9.txt" /*recup_nom_fichier(taille)*/;

	fichier = fopen(nom_fichier,"r");
	grille = creation_grille(taille);
	dico_mot = creation_dico(taille);

	nbre_mot = selection_nb_mot(fichier);
  avance_mot(fichier);
  for(i=0; i<nbre_mot; i++){
    mot = selection_mot(taille, fichier);
    dico_mot[i] = mot;
  }

	remplit_grille(grille, taille, fichier);
	affiche_grille(taille, grille);

	fclose(fichier);

  /*--------------------------------DEBUT DU JEU------------------------------------*/

  mot = mot_repere(taille);
  printf("%s\n", dico_mot[0]);
  printf("%d",cherche_dico(dico_mot, mot, taille));

	return 0;
}

