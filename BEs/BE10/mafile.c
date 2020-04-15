#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "mafile.h"

/* On définit les files doublement chainées avec une case inutile, puis
la tête, qui pointe vers le suivant etc. jusqu'à la dernière case qui pointe eventuellement vers 
NULL, mais ce n'est pas nécessaire pour que tout fonctionne.
On considère que le début est à gauche, la fin à droite*/

void
INIT_FILE (PMAFILE pf)
{
  pf->deb = malloc (sizeof (CELLULE));
  pf->deb->pre = NULL;
  pf->deb->sui=NULL;
  pf->fin = pf->deb;
}

void
RAZ (PMAFILE pf)
{
  while ((pf->deb) != (pf->fin))
    {
      DEFILER_A_GAUCHE (pf);
    };
}

int
VIDE (MAFILE f)
{
  return (f.deb == f.fin);
}

void
ENFILER_A_DROITE (PMAFILE pf, int x)
{
  PCELLULE pc = malloc (sizeof (CELLULE));

  (pc->val) = x;
  pc->pre = pf->fin;
  pc->sui = NULL;

  ((pf->fin)->sui) = pc;

  pf->fin = pc;
}

void
DEFILER_A_GAUCHE (PMAFILE pf)
{				/*ne change rien si file vide */
  PCELLULE pc = (pf->deb);
  if (VIDE (*pf) == 0)
    {
      (pf->deb) = ((pf->deb)->sui);
      pf->deb->pre = NULL; 
      free (pc);
    }				
/*else {
  printf("Impossible de defiler une file vide.");
} */
}


int
DEB (MAFILE f)
{
  if (VIDE (f) == 0)
    {
      return (((f.deb)->sui)->val);
    }
  else
    {
      printf ("Pas de deb, la file est vide.");
      return (0);
    }
}

void
AFFICHER_FILE (MAFILE f)
{
  /*Affiche les éléments en partant de la tête. */
  CELLULE *pc = f.deb;

  printf ("\n[");
  if (VIDE (f) == 0)
    {
      do
	{
	  pc = (pc->sui);
	  printf ("%d; ", (pc->val));
	}
      while (pc != f.fin);
    }
  printf ("]");
}
