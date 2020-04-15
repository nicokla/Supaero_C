#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "mafile.h"

/* On définit les files chainées avec une case inutile, puis
la tête, qui pointe vers le suivant etc. jusqu'à la dernière case qui pointe eventuellement vers 
NULL, mais ce n'est pas nécessaire pour que tout fonctionne.*/

void
INIT_FILE (PMAFILE pf)
{
  pf->tete = malloc (sizeof (MAFILE));
  pf->queue = pf->tete;
}

void
RAZ (PMAFILE pf)
{
  /*(pf->tete)->psuivant = NULL;
     (pf->queue)->psuivant = NULL; */
  while ((pf->queue) != (pf->tete))
    {
      DEFILER (pf);
    };
  /*-->(pour faire les free, ou sinon de manière "sale", sans faire les free :
  (pf->queue)=(pf->tete);*/
}

int
VIDE (MAFILE f)
{
  return (f.tete == f.queue);
}

void
ENFILER (PMAFILE pf, int x)
{
  PCELLULE pc = malloc (sizeof (PCELLULE));
  (pc->valeur) = x;
  /*pc->psuivant=NULL; */
  ((pf->queue)->psuivant) = pc;
  pf->queue = pc;
}

void
DEFILER (PMAFILE pf)
{				/*ne change rien si file vide */
  PCELLULE pc = (pf->tete);
  if (VIDE (*pf) == 0)
    {
      (pf->tete) = ((pf->tete)->psuivant);
      free (pc);
      /*ou directement de manière "sale" la deuxième ligne, sans free. */
    }				/*else {
				   printf("Impossible de defiler une file vide.");
				   } */
}


int
TETE (MAFILE f)
{
  if (VIDE (f) == 0)
    {
      return ((f.tete)->valeur);
    }
  else
    {
      printf ("Pas de tete, la file est vide.");
      return (0);
    }
}

void
AFFICHER_FILE (MAFILE f)
{
  /*Affiche les éléments en partant de la tête. */
  CELLULE *pc = f.tete;

  printf ("\n[");
  if (VIDE (f) == 0)
    {
      do
	{
	  pc = (pc->psuivant);
	  printf ("%d; ", (pc->valeur));
	}
      while (pc != f.queue);
    }
  printf ("]");
}
