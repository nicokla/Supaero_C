//#include <stdlib.h>
//#include "date.h"
#include "personne.h"

extern void ecrired(PDATE ptd);

void lirep(PPERSONNE ptp){
 printf("\nQuelle est le prenom ? :");
 scanf("%s",(ptp->prenom));

 printf("\nQuelle est le nom ? :");
 scanf("%s",(ptp->nom));

 printf("\nQuelle est la date de naissance ?");
 lired( &(ptp->naissance) );
}

void ecrirep(PPERSONNE ptp){
 printf("\n%s %s est ne(e) le ",ptp->prenom,ptp->nom);
 ecrired(&(ptp->naissance));
}
