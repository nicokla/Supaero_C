#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include "mafile.h"

extern void supprimer (PMAFILE pf, PCELLULE p);
extern void inserer (PMAFILE pf, int x, PCELLULE p);


int main(void){
  MAFILE f;
  int i;

  INIT_FILE (&f);
for(i=1;i<=10;i++){ENFILER_A_DROITE(&f,i);}

supprimer(&f , ((f.deb)->sui)->sui ); /*on supprime le deuxieme element*/
AFFICHER_FILE(f);
inserer(&f ,81,((f.deb)->sui));/*on met 81 en 2ème position*/
AFFICHER_FILE(f);
return 1;
}


/*Ancienne version du main :

int
main (void)
{
  MAFILE f;
  int a = 0;
  int x = 0;

  INIT_FILE (&f);

  do
    {
      printf ("\nTapez 0 si vous voulez arreter le test,\n     \
1 si vous voulez rajouter un nombre\n     \
2 si vous voulez enlever un nombre\n     \
3 si vous voulez vider la liste\n");
      scanf ("%d", &a);

      if (a == 1)
	{
	  printf ("Quel nombre voulez-vous rajouter ? :");
	  scanf ("%d", &x);
	  ENFILER (&f, x);
	}
      else if (a == 2)
	{
	  DEFILER (&f);
	}
      else if (a == 3)
	{
	  RAZ (&f);
	}

      AFFICHER_FILE (f);
    }
  while (a != 0);

  return (1);
}*/
