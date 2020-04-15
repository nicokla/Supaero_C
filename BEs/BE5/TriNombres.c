#include <stdio.h>

#define MAX 1000

void lire_tab (int tab[MAX], int n);
void ecrire_tab (int tab[MAX], int n);
void trier (int tab[MAX], int n);
void echanger (int *pa, int *pb);
int mintab (int tab[MAX], int i, int j);
//______________________________

int
main (void)
{
  int tab[MAX];
  int j = 0, n = 0;

  printf ("Combien de nombres voulez vous trier ?\n");
  scanf ("%d", &n);
  printf ("\n");

  lire_tab (tab, n);
  trier (tab, n);
  ecrire_tab (tab, n);

  return 1;
}

//______________________________

void
lire_tab (int tab[MAX], int n)
{
  int i;
  for (i = 0; i < n; i++)
    {
      printf ("%d eme nombre ? ", i + 1);
      scanf ("%d", tab + i);
    }
}

//______________________________

void
ecrire_tab (int tab[MAX], int n)
{
  int i;
  for (i = 0; i < n; i++)
    printf ("%d  %d\n", (i + 1), tab[i]);
}

//______________________________

void
echanger (int *pa, int *pb)
{
  int c;
  c = *pa;
  *pa = *pb;
  *pb = c;
}

//______________________________

void
trier (int tab[MAX], int n)
{
  int i, j;
  for (i = 0; i < n - 1; i++)
    {
      j = mintab (tab, i, n - 1);
      if (tab[i] != tab[j])
	echanger (&tab[i], &tab[j]);
    }
}

//______________________________

int
mintab (int tab[MAX], int i, int j)
{
  int x = tab[i];
  int l = i;			/* variable qui désigne l endroit où est le minimum */
  int k = i;			/* variable incrementale */

  for (k = i + 1; k <= j; k++)
    {
      if (tab[k] < x)
	{
	  l = k;
	  x = tab[k];
	}
    }

  return l;
}
