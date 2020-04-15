#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "arbreBin.h"

extern void SUPPRIME (PCELLULE pc);
extern void INSERER(PCELLULE *pc, int a);

extern void PARCOURS(PCELLULE pc);
extern void PREFIXE(PCELLULE pc);
extern void POSTFIXE(PCELLULE pc);
void tri(int tab[], int n);

int main(){
int tab[7] = {2,11,44,3,8,-1,9};
tri(tab,7);
return 1;}

/*Tri les n premiers entiers du tableau, 
qu'on suppose de taille suffisante*/
void tri(int tab[], int n){
int i;
PCELLULE pc=NULL;
for(i=0;i<n;i++){INSERER(&pc,tab[i]);}
PARCOURS(pc);
}
