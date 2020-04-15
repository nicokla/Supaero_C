#ifndef IO_CONSOLE_CTE
#define IO_CONSOLE_CTE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int lireMotGeneral(char chaine[], int longueurMax);
void lireMot30(char chaine[]);

int condVraiInt(int i);
int condVraiFloat(float i);
int condVraiMot(char *mot);
void demanderEntier (char question[], int *pEntier, int (*pCondition) (int)); 
void demanderFlottant (char question[], float *pFlottant, int (*pCondition) (float));
void demanderMot30 (char question[], char*mot, int (*pCondition)(char[]));

#endif
