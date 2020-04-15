//#include <stdlib.h>
#include "date.h"

void lired(PDATE ptd){
 do{
 printf("\nQuel est le jour ? :");
 scanf("%d",&(ptd->jour));
 }while((ptd->jour)<=0 || (ptd->jour)>=32 );// printf("  OK");
 
 do{
 printf("\nQuel est le mois ? :");
 scanf("%d",&(ptd->mois));
 }while((ptd->mois)<=0 || (ptd->mois)>=13 );// printf("  OK");

 printf("\nQuelle est l'annee ? :");
 scanf("%d",&(ptd->annee));
}

void ecrired(PDATE ptd){
 printf("%d / %d / %d",ptd->jour,ptd->mois,ptd->annee);
}
