#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "mafile.h"

/*Fichier contenant les fonctions insérer et supprimer
On suppose les listes doublement chainées.*/

void
supprimer (PMAFILE pf, PCELLULE p)
{
  if (p->sui != NULL)
    {
      (p->pre)->sui = p->sui;
      (p->sui)->pre = p->pre;
    }
  else
    {
      pf->fin = p->pre;
    }
  free (p);
}

/*on insere x juste apres p*/
void
inserer (PMAFILE pf, int x, PCELLULE p)
{
  PCELLULE PPRIME;
  PPRIME = malloc (sizeof (CELLULE));
  PPRIME->val = x;

  p->sui->pre = PPRIME;
  PPRIME->sui = p->sui;

  p->sui= PPRIME;
  PPRIME->pre = p;
}
