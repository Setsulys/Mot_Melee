#include <stdio.h>
#include <stdlib.h>
int affiche_mot(FILE* fichier);

int main(int argc, char *argv[]){
  FILE* fichier;
  fichier = fopen("dico_mot_meles.txt","r");
  affiche_mot(fichier);
  return 0;
}

int affiche_mot(FILE* fichier){
  int i, j;
  char lettre;

  while((lettre = fgetc(fichier)) != EOF){
    printf("%c", lettre);
  }
   
  return 0;
}