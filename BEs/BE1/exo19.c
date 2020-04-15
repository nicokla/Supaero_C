#include <stdio.h>

/*Exercice 19
Element le plus grand et le plus petit parmi n nombres entiers */

int main (void)
{
int petit, grand, n,nombre,i=2;
printf("Combien de nombres allez vous rentrer (au moins 1) ? \n");
scanf("%d",&n);

printf("Nombre 1 ? ");
scanf("%d",&nombre);
petit=nombre;
grand=nombre;

  while(i<=n)
  { printf("Nombre %d ? ",i);
    scanf("%d",&nombre);
    if (nombre < petit) petit=nombre;
    if (nombre > grand) grand=nombre;
    i++;
  }

/*ou bien
for(i=2;i<=n;i++)*/

printf("\nLe plus petit nombre rentré est %d.  \n",petit);
printf("Le plus grand nombre rentré est %d. \n \n",grand);
return 1;
}
