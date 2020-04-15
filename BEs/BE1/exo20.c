#include <stdio.h>

/*Exercice 20
Suite de Fibonacci */

/* Version de base

int main (void)
{
int n,i=0;
printf("Quel terme de la suite de Fibonacci voulez-vous calculer (0 ou plus) ? \n");
scanf("%d",&n);

int tableau[n+1];
tableau[0]=0; tableau[1]=1;

for(i=2;i<=n;i++)
  { 
   tableau[i]=tableau[i-1] + tableau[i-2];
  }
printf("\nLe %d ieme terme de la suite est %d. \n",n,tableau[n]);

return 1;
}

*/


int main (void)
{
int i=1,max=100;

int tableau[max];
tableau[0]=0; tableau[1]=1;

while(tableau[i]>=0 && i+1<max)
  { 
   tableau[i+1]=tableau[i-1] + tableau[i];
   i++;
  }
printf("\nLe %d ieme terme de la suite est %d. \n",i-1,tableau[i-1]);

return 1;
}

/* Le 46 ieme terme de la suite est 1836311903. */
