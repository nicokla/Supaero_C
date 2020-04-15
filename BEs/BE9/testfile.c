#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include "mafile.h"

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
}
