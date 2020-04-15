#include <stdio.h>

/*Exercice 18
Moyenne de 3 nombres*/

int main (void)
{
int a,b,c;
float moyenne;
printf("Rentrez trois nombres entiers \n");
scanf("%d%d%d",&a,&b,&c);
moyenne=(a+b+c)/3.0;
printf("La moyenne est %f. \n \n",moyenne);
return 1;
}
