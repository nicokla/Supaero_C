#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define LARGEUR 900
#define HAUTEUR 600
#define BLEU "0 0 255"
#define BLANC "255 255 255"
#define ROUGE "255 0 0"

//Affiche le drapeau demandé, en proportion 2/3, et 900*600 par défaut.
//Les couleurs par défaut sont celles de la France.

int main(int argn, char** argv){
int i,j;
char couleur1[12], couleur2[12], couleur3[12];
FILE* f;

i=1;j=1;
f=fopen("Drapeau.ppm","w");
strcpy(couleur1,BLEU);
strcpy(couleur2,BLANC);
strcpy(couleur3,ROUGE);

if(argn!=1 && argn!=4){printf("Arguments incorrects");return 0;}

fprintf(f,"P3\n");
fprintf(f,"%d %d\n",LARGEUR,HAUTEUR);
fprintf(f,"255\n");

if(argn==4){
strcpy(couleur1,argv[1]);
strcpy(couleur2,argv[2]);
strcpy(couleur3,argv[3]);
}
 
 for(;i<=HAUTEUR;i++){
  for(j=1;j<=300;j++){fprintf(f,"%s ",couleur1);}
  for(;j<=600;j++){fprintf(f,"%s ",couleur2);}
  for(;j<=900;j++){fprintf(f,"%s ",couleur3);}
 }

fclose(f);
return 1;
}
