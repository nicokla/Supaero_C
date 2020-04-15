#include "io_console.h"

int lireMotGeneral(char chaine[], int longueurMax)
{/*comme scanf, mais avec un nombre maximum de lettres*/
  int i=0;
  char c=getchar();
  
  memset(chaine, 0, longueurMax * sizeof(char));
	
	while(c!=EOF && c!= '\n' && i<longueurMax-1){
   chaine[i]=c;
	  i++;c=getchar(); /*conversion d'un int en char*/
	}  
	
  chaine[longueurMax-1]='\0';

  if(i==longueurMax-1 && c!=EOF && c!='\n') /*mot trop long*/{
    while (c != '\n' && c != EOF){  /*on vide le buffer*/
      c = getchar();
    }
    printf("\nLe mot est trop long, seules les %d premieres lettres ont ete enregistrees\n", longueurMax-1);
    return 0; 
  }

  else { /*mot de bonne longueur*/
    while (c != '\n' && c != EOF){ 
	  /*à priori le buffer est déjà vide, mais au cas où*/
      c = getchar(); 
    }
    return 1; 
  }

}

void lireMot30(char chaine[])
{/* on suppose dans zuma que les mots entrés 
  * dans la console ne depassent pas 29 caractères, ie sont des char[30] */

  lireMotGeneral(chaine, 30);
}

/**-------------*/
/*Fonctions pour faire des scanf avec vérification de la validité de l'entrée*/

int condVraiInt(int i){return(1);}
int condVraiFloat(float i){return(1);}
int condVraiMot(char *mot){return(1);}

void demanderEntier (char question[], int *pEntier, int (*pCondition) (int)) 
{ /* Sert à demander un entier en posant une question et en attendant qu'il vérifie
un critère avant de passer à la suite*/
int i=0;
  do {
	i++;
	if(i>1)printf("\nEntree non valide\n");
    printf ("%s",question);
    scanf ("%d", pEntier);
  } while (!((*pCondition) (*pEntier))); /*Tant que la condition n'est pas validée.*/
}

void demanderFlottant (char question[], float *pFlottant, int (*pCondition) (float))
{ /*Pareil que demanderEntier, mais pour un flottant*/
  int i=0;
    do {
	  i++;
	  if(i>1) printf("\nEntree non valide\n");
      printf ("%s",question);
      scanf ("%f", pFlottant);
    } while (!((*pCondition) (*pFlottant)));
}

void demanderMot30 (char question[], char*mot, int (*pCondition)(char[]))
{/*Pareil que pour demanderEntier, mais pour un mot , un char[30], 
d'où le "30"*/
int i=0;
  do {
	i++;
	if(i>1) printf("\nEntree non valide\n");
    printf ("%s", question);
    lireMot30(mot);
  } while (!((*pCondition) (mot)));
}
