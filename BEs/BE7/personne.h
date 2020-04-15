#include "date.h"

#define MAXCAR 80

typedef char MOT[MAXCAR];

typedef struct personne{MOT nom;
                        MOT prenom;
                        DATE naissance;} PERSONNE, *PPERSONNE;

void lirep(PPERSONNE ptp);
