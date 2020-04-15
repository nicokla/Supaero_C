#include <stdio.h>
#define N 10

/*Exercice 21
Recouvrement ?*/

int main (void)
{
printf("Exercice 21 : Recouvrement ?\n");

int a,b;
int tab[N];
int c,d;

a=1;b=2;c=3;d=4; tab[N]=500;
printf("%d %d %d %d %d",a,b,c,d,tab[N]);
printf("\n %d %d %d %d %d\n",&a,&b,&c,&d,&tab[N]);
return 1;
}
