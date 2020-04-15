#ifndef DEF_mafile
#define DEF_mafile

typedef struct cellule
{
  int valeur;
  struct cellule *psuivant;
} CELLULE, *PCELLULE;
typedef struct mafile
{
  PCELLULE tete;
  PCELLULE queue;
} MAFILE, *PMAFILE;

void INIT_FILE (PMAFILE pf);
void RAZ (PMAFILE pf);
int VIDE (MAFILE f);
void ENFILER (PMAFILE pf, int x);
void DEFILER (PMAFILE pf);
int TETE (MAFILE f);
void AFFICHER_FILE (MAFILE f);

#endif
