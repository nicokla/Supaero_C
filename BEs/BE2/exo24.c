
/*Exercice 24
char, table des caractères ascii */

#include <stdio.h>
#define NOM_FICHIER "ascii.txt"

int main ()
{
  printf("Ex.24 : Table des caractères ascii\n\
Ouvrez le fichier ascii.txt pour voir la table.\n");
  FILE * pFile = fopen (NOM_FICHIER,"w");;
  char c=0;

  if (pFile!=NULL)
  {
    do 
    { c++;fprintf ( pFile , "%d %c\n", c,c); 
    }while(c<127);

 /*for(c = '!' ; c <= '~' ; c++){fprintf ( pFile , "%d %c\n", c,c); }*/

    fclose (pFile);
  }
  return 0;
}

