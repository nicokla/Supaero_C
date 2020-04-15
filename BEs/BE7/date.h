#include <stdlib.h>

// 2, 4 6 9 11  2000, 2004, 29 mais pas 1700 1800 1900

typedef struct date {int jour;
                     int mois;
                     int annee;} DATE, *PDATE;

void lired(PDATE ptd);

void ecrired(PDATE ptd);
