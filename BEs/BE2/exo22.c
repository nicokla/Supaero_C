#include <stdio.h>

/*Exercice 22
Pointeur*/

int main (void)
{
printf("Exercice 22 : Pointeurs\n");

int i=0;
int *k;
k=&i;
*k=2;
printf("%d\n",i);
return 1;
}
