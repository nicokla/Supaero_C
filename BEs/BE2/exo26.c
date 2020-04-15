/* Exercice 26 :
comptage du nombre de caractères dans un fichier */
//-----------------------------------------------

#include <stdio.h>
#define FICHIER1 "test1.txt"

int main ()
{ printf ("Ex.26 : Compte le nombre de caracteres dans un fichier\n");
 
  int i=0,j=0,k=0;
  char c=' ';
  FILE* fichier1 = fopen(FICHIER1 ,"r");

//__________________________________________________

// option 1 : les sauts à la ligne sont comptés séparément du reste

do{ 
c=fgetc(fichier1); if(c>='!' && c<='~'){i++;}
else if(c=='\n'){j++;}
}while (c != -1);

// option 2 : avec les fonctions du langage C (mais on ne connait pas le nombre d'espaces)

fseek(fichier1, 0, SEEK_END);
k = ftell(fichier1);

//__________________________________________________
  
  fclose(fichier1);
  printf("\nNombre de caractères ascii (sans compter les espaces) : %d",i);
  printf("\nNombre d'espaces : %d",j);
  printf("\nNombre total d'octets : %d\n",k);
  return 0;
}
