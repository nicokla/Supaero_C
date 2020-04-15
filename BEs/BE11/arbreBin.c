#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "arbreBin.h"

void SUPPRIME (PCELLULE pc){
  if (pc!=NULL){
    SUPPRIME((*pc).ga);
    SUPPRIME((*pc).dr);
    free(pc);}
}

/*On suppose que a n'est pas dans l'arbre, si il y est déjà on ne fait rien*/
void INSERER(PCELLULE *ppc, int a){
  if(*ppc==NULL){
    PCELLULE pc=malloc(sizeof(CELLULE));
    pc->val=a;
    pc->ga=NULL;
    pc->dr=NULL;
    *ppc=pc;}
  else if(a<(**ppc).val){
    PCELLULE *ppc2=&((**ppc).ga);
    INSERER(ppc2,a);}
  else if(a>(**ppc).val){
    PCELLULE *ppc2=&((**ppc).dr);
    INSERER(ppc2,a);}
}

void PARCOURS(PCELLULE pc){
  if(pc!=NULL){
    PARCOURS(pc->ga);
    printf("%d, ",pc->val);
    PARCOURS(pc->dr);
  }
}

void PREFIXE(PCELLULE pc){
  if(pc!=NULL){
    printf("%d, ",pc->val);
    PREFIXE(pc->ga);
    PREFIXE(pc->dr);
  }
}

void POSTFIXE(PCELLULE pc){
  if(pc!=NULL){
    POSTFIXE(pc->ga);
    POSTFIXE(pc->dr);
    printf("%d, ",pc->val);
  }
}
