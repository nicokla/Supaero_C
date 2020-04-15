//#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include "date.h"
#include "personne.h"

int compared(PDATE,PDATE);
int comparep(PPERSONNE,PPERSONNE);
char plusGrand(PDATE ptd1,PDATE ptd2);
void ajouterJour(PDATE ptd1);
void wait(int milliseconds);// Utile uniquement pour les tests.

int main(int argc, char** argv){
PERSONNE p1, p2;

printf("\n\t\tComparaison de l'age de deux personnes\n\n\tPersonne 1\n");
lirep(&p1);
printf("\n\tPersonne 2\n");
lirep(&p2);

ecrirep(&p1);
ecrirep(&p2);
printf("\n");
printf("\nLes personnes ont %d jours d'ecart.\n",comparep(&p1,&p2));
}
//______________________________________________

void wait ( int milliseconds )//Utile uniquement pour les tests
{
  clock_t endwait;
  endwait = clock () + (milliseconds * CLOCKS_PER_SEC/1000) ;
  while (clock() < endwait) {}
}
//_____________________________________________
void ajouterJour(PDATE ptd){
if(ptd->mois== 12 && ptd->jour==31){(ptd->jour)=1;
                                   (ptd->mois)=1;
                                   (ptd->annee)++;}

 else if(ptd->mois != 2 && ptd->mois != 4 && ptd->mois != 6 && ptd->mois != 9 && ptd->mois != 11){
  if( (ptd->jour)<=30 ) (ptd->jour)++;
  else {(ptd->mois)++; ptd->jour = 1;}
 }

 else if(ptd->mois == 4 || ptd->mois == 6 || ptd->mois == 9 || ptd->mois == 11){
  if( (ptd->jour)<=29 ) (ptd->jour)++;
  else {(ptd->mois)++; ptd->jour = 1;}
 }

 else if((ptd->mois)==2){
  if( (ptd->jour)<=27 ) (ptd->jour)++;
  else if ((ptd->annee)%400 == 100 || (ptd->annee)%400 == 200 ||(ptd->annee)%400 == 300 || (ptd->annee)%4 != 0 || (ptd->jour) == 29){  
  ptd->jour=1; (ptd->mois)=3;
  }
  else (ptd->jour)=29;
 }
}
//______________________________________________

int compared(PDATE ptd1,PDATE ptd2){
int i=0;

 if(plusGrand(ptd1,ptd2)){
  while(plusGrand(ptd1,ptd2)){
   i++;ajouterJour(ptd1);
//Test :
//ecrired(ptd1);printf("\n");wait(10);
  }
  return i;
 }
else compared(ptd2,ptd1);
}
//______________________________________________

char plusGrand(PDATE ptd1,PDATE ptd2)
//renvoie 1 si ptd2 est plus jeune,(ou a le mm age)
// ie si sa date est plus grande, sinon renvoie 0
{
 if ( (ptd1->annee) > (ptd2->annee) ) return 0;
   else if ((ptd1->annee) == (ptd2->annee)){
     if((ptd1->mois) > (ptd2->mois)) return 0;
       else if ((ptd1->mois) == (ptd2->mois)){
          if((ptd1->jour) >= (ptd2->jour)) return 0;
       }
   }
else return 1;
}
//______________________________________________

int comparep(PPERSONNE ptp1,PPERSONNE ptp2){
 compared( &(ptp1->naissance), &(ptp2->naissance) );
}
