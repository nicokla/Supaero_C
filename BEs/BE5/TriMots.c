#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 100

/*Trier une liste de mots.*/

void lire_mots (char **tab);
void trier (char **tab);
void ecrire_mots (char **tab);
int mintab (char **tab, int i);
void echanger (char **pmot1, char **pmot2);

int
main (void)
{
  char **tab;
  int n = 0;

  printf ("Combien de mots voulez vous trier ?\n");
  scanf ("%d", &n);
  printf ("\n");

  tab = malloc ((n + 1) * sizeof (char *));
  tab[n] = 123456;

  lire_mots (tab);
  trier (tab);
  ecrire_mots (tab);

  while (*tab != 123456) {
    free (*tab);
    tab++;
  }
  free (tab - n);

  return 1;
}

void
lire_mots (char **tab)
{
  char chaine[MAX];

  while (*tab != 123456) {
    printf ("Mot suivant : \n");
    scanf ("%s", chaine);
    *tab = malloc ((strlen (chaine) + 1) * sizeof (char));
    strcpy (*tab, chaine);
    tab++;
  }
}

void
trier (char **tab)
{
  int i = 0, j;

  while (*(tab + i) != 123456) {
    j = mintab (tab, i);
    echanger (tab + i, tab + j);
    i++;
  }
}

int
mintab (char **tab, int i)
{
  char mot_aux[MAX];
  int l = i;			/* variable qui désigne l'endroit où est le minimum */
  int k = i;			/* variable incrementale */

  strcpy (mot_aux, tab[i]);

  while (tab[k] != 123456) {
    if (strcmp (tab[k], mot_aux) < 0) {
      l = k;
      strcpy (mot_aux, tab[k]);
    }
    k++;
  }
  return l;
}

void
echanger (char **pa, char **pb)
{
  char *c;

  c = *pa;
  *pa = *pb;
  *pb = c;
}

void
ecrire_mots (char **tab)
{
  printf ("\nVoici la liste triee :\n");
  while (*tab != 123456) {
    printf ("%s\n", *tab);
    tab++;
  }
}
